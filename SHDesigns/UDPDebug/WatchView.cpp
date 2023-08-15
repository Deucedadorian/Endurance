// WatchView.cpp : implementation file
//

#include "stdafx.h"
#include "udpdebug.h"
#include "WatchView.h"
#include "AddWDlg.h"
#include "EditIntDlg.h"
#include "MainFrm.h"
#include "EditVarDlg.h"
#include "ChildWFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWatchView


CWatchView::CWatchView()
{
	AutoTime=0;
	NIList.Create(32,24,ILC_COLOR,3,1);
	NIList.SetBkColor(RGB(255,255,255));
	NIList.Add(AfxGetApp()->LoadIcon(IDI_NONE));
	NIList.Add(AfxGetApp()->LoadIcon(IDI_STRUCT));
	NIList.Add(AfxGetApp()->LoadIcon(IDI_INT));
	NIList.Add(AfxGetApp()->LoadIcon(IDI_CHAR));
	NIList.Add(AfxGetApp()->LoadIcon(IDI_LONG));
	NIList.Add(AfxGetApp()->LoadIcon(IDI_STRING));
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	app->Syms.m_Updated=false; // we vever read them so they are up to date
	char buff[80],*s;
	GetModuleFileName(NULL,buff,255);
	s=strstr(buff,".exe");
	if (s==NULL)
		s=strstr(buff,".EXE");
	if (s)
	{
		strcpy(s,".tmp");
		m_TempFile=buff;
	}
	UpdateInProgress=false;
}

CWatchView::~CWatchView()
{
}


BEGIN_MESSAGE_MAP(CWatchView, CTreeView)
	//{{AFX_MSG_MAP(CWatchView)
	ON_COMMAND(ID_ADDW, OnAddWatch)
	ON_COMMAND(ID_UPDATE, OnUpdate)
	ON_COMMAND(ID_DELETEW, OnDeleteWatch)
	ON_COMMAND(ID_MODIFY, OnModify)
	ON_COMMAND(ID_AUTO, OnAuto)
	ON_UPDATE_COMMAND_UI(ID_AUTO, OnUpdateAuto)
	ON_WM_TIMER()
	ON_COMMAND(ID_SAVEW, OnSaveWatch)
	ON_COMMAND(ID_LOADW, OnLoadWatch)
	ON_COMMAND(ID_EDITDATA, OnEditData)
	ON_UPDATE_COMMAND_UI(ID_EDITDATA, OnUpdateEditData)
	ON_UPDATE_COMMAND_UI(ID_DELETEW, OnUpdateDeleteWatch)
	ON_UPDATE_COMMAND_UI(ID_MODIFY, OnUpdateModify)
	ON_UPDATE_COMMAND_UI(ID_UPDATE, OnUpdateUpdate)
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWatchView drawing


/////////////////////////////////////////////////////////////////////////////
// CWatchView diagnostics

#ifdef _DEBUG
void CWatchView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CWatchView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWatchView message handlers

BOOL CWatchView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.dwExStyle |= WS_EX_CLIENTEDGE;

	cs.style &= ~WS_BORDER;
//	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
//		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);
	return CTreeView::PreCreateWindow(cs);
	

}

void CWatchView::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
//	CTreeView::PostNcDestroy();
}

void CWatchView::OnAddWatch() 
{
	CAddWDlg dlg;
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	dlg.Syms=&app->Syms;
	dlg.Structs=&app->Structs;
	if (dlg.DoModal()==IDOK)
	{
		CWatchVItem item;
		item.Name=dlg.m_Address;
		item.Size=dlg.m_Length;
		item.Type=CWatchItem::WTYPE(dlg.m_Type);
		item.Hex=dlg.m_Hex>0;
		item.Struct=dlg.m_StructList;
		if (item.Hex)
			item.Signed=false;
		else
			item.Signed=dlg.m_Unsigned?false:true;
		item.IsIo=dlg.m_MType==1;
		item.IsEio=dlg.m_MType==2;

		WatchList.Add(item);
	}
	OnUpdate();
	
}

void CWatchView::OnUpdate() 
{
	KillTimer(1);
	CString fmt,tmp,xtmp;
	char * cdata=NULL;
	short int * idata=NULL;
	long int * ldata=NULL;
	float * fdata=NULL;
	int i,j;
	bool redoall=false;
	if (UpdateInProgress)
		return;
	UpdateInProgress=true;
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	CTreeCtrl& ctl=GetTreeCtrl();
	ctl.SetImageList(&NIList,TVSIL_NORMAL);
	ctl.SetImageList(&NIList,TVSIL_STATE);
	for (i=0;i<WatchList.GetSize();i++)
		if (WatchList[i].Modified)
		{
			redoall=true;
			break;
		}
	if (app->Syms.m_Updated||redoall)
	{
		SaveWatch(true);
		while (WatchList.GetSize())
		{
			SelWItem=0;
			DeleteWatch();
		}
		app->Syms.m_Updated=false;
		ctl.DeleteAllItems();
		LoadWatch(true);
	}
	app->Syms.m_Updated=false;
	if (WatchList.GetSize()==0)	// for case where all watches were deleted
		ctl.DeleteAllItems();
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->SetMessageText("Updating watch");

	for (i=0;i<WatchList.GetSize();i++)
	{
		int addr;
		int type=0;
		if (WatchList[i].IsIo)
			type=DEBUG_IREAD;
		if (WatchList[i].IsEio)
			type=DEBUG_EREAD;
		SegOff saddr;
		CString name=WatchList[i].Name;	// eval modifys this!
		bool ok=app->Syms.EvalSymAdd(saddr,name);
		addr=saddr.GetLinear();
		tmp.Format("%s Error: No response from target!",WatchList[i].Name); // overwrite if ok
		if (!ok)
		{
			tmp.Format("Error in address: %s",WatchList[i].Name);
			if (!WatchList[i].Modified)
				ctl.SetItemText(WatchList[i].hTree,tmp);
			else
				WatchList[i].hTree=ctl.InsertItem(tmp,0,0);
		}
		else
		switch (WatchList[i].Type)
		{
		case CWatchItem::TYPE_CHAR:
			cdata=new char[WatchList[i].Size+3];
			if (app->ReadData(cdata,addr,WatchList[i].Size,type))
			{
				if (WatchList[i].Size>1)
				{
					tmp.Format("(%x:%x) %s[%d]",saddr.Seg,saddr.Off,WatchList[i].Name,WatchList[i].Size);
					if (!WatchList[i].Modified)
						ctl.SetItemText(WatchList[i].hTree,tmp);
					else
						WatchList[i].hTree=ctl.InsertItem(tmp,ICON_CHAR,ICON_CHAR);
				}
				if (WatchList[i].Hex)
					fmt="\'%s\' (%02X) ";
				else
					fmt="\'%s\' (%d) ";
				for (j=0;j<WatchList[i].Size;j++)
				{
					CString ctemp;
					if (cdata[j])
						ctemp=cdata[j];
					else
						ctemp="\\0";
					if (WatchList[i].Signed)
						xtmp.Format(fmt,ctemp,cdata[j]);
					else
						xtmp.Format(fmt,ctemp,cdata[j]&0xff);
					
					if (WatchList[i].Size==1)
					{
						tmp.Format("(%x:%x) %s=%s",saddr.Seg,saddr.Off+j,WatchList[i].Name,xtmp);
						if (!WatchList[i].Modified)
							ctl.SetItemText(WatchList[i].hTree,tmp);
						else
							WatchList[i].hTree=ctl.InsertItem(tmp,ICON_CHAR,ICON_CHAR);
					}
					else
					{
						tmp.Format("(%x:%x) [%d]=%s",saddr.Seg,saddr.Off+j,j,xtmp);
						if (!WatchList[i].Modified)
							ctl.SetItemText(WatchList[i].hItems[j],tmp);
						else
						{
							HTREEITEM item=ctl.InsertItem(tmp,0,0,WatchList[i].hTree);
							WatchList[i].hItems.Add(item);
						}
					}
				}
				WatchList[i].Modified=false;
			}
			else
			{
				if (!WatchList[i].Modified)
					ctl.SetItemText(WatchList[i].hTree,tmp);
				else
				{
					WatchList[i].hTree=ctl.InsertItem(tmp,0,0);
				}
				WatchList[i].Modified=true;
			}
			delete [] cdata;
			break;
		case CWatchItem::TYPE_INT:
			if (WatchList[i].Hex)
				fmt="%04X ";
			else
				fmt="%d ";
			idata=new short int[WatchList[i].Size+2];
			if (app->ReadData(idata,addr,2*WatchList[i].Size,type))
			{
				if (WatchList[i].Size>1)
				{
					tmp.Format("(%x:%x) %s[%d]",saddr.Seg,saddr.Off,WatchList[i].Name,WatchList[i].Size);
					if (!WatchList[i].Modified)
						ctl.SetItemText(WatchList[i].hTree,tmp);
					else
						WatchList[i].hTree=ctl.InsertItem(tmp,ICON_INT,ICON_INT);
				}
				for (j=0;j<WatchList[i].Size;j++)
				{
					if ((WatchList[i].Hex)||!WatchList[i].Signed)
						xtmp.Format(fmt,idata[j]&0xffff);
					else
						xtmp.Format(fmt,idata[j]);
					if (WatchList[i].Size==1)
					{
						tmp.Format("(%x:%x) %s=%s",saddr.Seg,saddr.Off+(j*2),WatchList[i].Name,xtmp);
						if (!WatchList[i].Modified)
							ctl.SetItemText(WatchList[i].hTree,tmp);
						else
							WatchList[i].hTree=ctl.InsertItem(tmp,ICON_INT,ICON_INT);
					}
					else
					{
						tmp.Format("(%x:%x) [%d]=%s",saddr.Seg,saddr.Off+j*2,j,xtmp);
						if (!WatchList[i].Modified)
							ctl.SetItemText(WatchList[i].hItems[j],tmp);
						else
						{
							HTREEITEM item=ctl.InsertItem(tmp,0,0,WatchList[i].hTree);
							WatchList[i].hItems.Add(item);
						}
					}
				}
				WatchList[i].Modified=false;
			}
			else
			{
				if (!WatchList[i].Modified)
					ctl.SetItemText(WatchList[i].hTree,tmp);
				else
					WatchList[i].hTree=ctl.InsertItem(tmp,0,0);
					WatchList[i].Modified=true;
			}
			delete [] idata;
			break;
		case CWatchItem::TYPE_LONG:
			if (WatchList[i].Hex)
				fmt="%08X ";
			else
				if (WatchList[i].Signed)
					fmt="%d ";
				else
					fmt="%u ";
			ldata=new long[WatchList[i].Size+1];
			if (app->ReadData(ldata,addr,4*WatchList[i].Size,type))
			{
				if (WatchList[i].Size>1)
				{
					tmp.Format("(%x:%x) %s[%d]",saddr.Seg,saddr.Off,WatchList[i].Name,WatchList[i].Size);
					if (!WatchList[i].Modified)
						ctl.SetItemText(WatchList[i].hTree,tmp);
					else
						WatchList[i].hTree=ctl.InsertItem(tmp,ICON_LONG,ICON_LONG);
				}
				for (j=0;j<WatchList[i].Size;j++)
				{
					xtmp.Format(fmt,ldata[j]);
					if (WatchList[i].Size==1)
					{
						tmp.Format("(%x:%x) %s=%s",saddr.Seg,saddr.Off+j*4,WatchList[i].Name,xtmp);
						if (!WatchList[i].Modified)
							ctl.SetItemText(WatchList[i].hTree,tmp);
						else
							WatchList[i].hTree=ctl.InsertItem(tmp,ICON_LONG,ICON_LONG);
					}
					else
					{
						tmp.Format("(%x:%x) [%d]=%s",saddr.Seg,saddr.Off+j*4,j,xtmp);
						if (!WatchList[i].Modified)
							ctl.SetItemText(WatchList[i].hItems[j],tmp);
						else
						{
							HTREEITEM item=ctl.InsertItem(tmp,0,0,WatchList[i].hTree);
							WatchList[i].hItems.Add(item);
						}
					}
				}
				WatchList[i].Modified=false;
			}
			else
			{
				if (!WatchList[i].Modified)
					ctl.SetItemText(WatchList[i].hTree,tmp);
				else
					WatchList[i].hTree=ctl.InsertItem(tmp,0,0);
				WatchList[i].Modified=true;
			}
			delete [] ldata;
			break;
		case CWatchItem::TYPE_FLOAT:
			fdata = new float[WatchList[i].Size+1];
			if (app->ReadData(fdata,addr,4*WatchList[i].Size,type))
			{
				if (WatchList[i].Size>1)
				{
					tmp.Format("(%x:%x) %s[%d]",saddr.Seg,saddr.Off,WatchList[i].Name,WatchList[i].Size);
					if (!WatchList[i].Modified)
						ctl.SetItemText(WatchList[i].hTree,tmp);
					else
						WatchList[i].hTree=ctl.InsertItem(tmp,0,0);
				}
				for (j=0;j<WatchList[i].Size;j++)
				{
					xtmp.Format("%f",double(fdata[j]));
					if (WatchList[i].Size==1)
					{
						tmp.Format("(%x:%x) %s=%s",saddr.Seg,saddr.Off+j*4,WatchList[i].Name,xtmp);
						if (!WatchList[i].Modified)
							ctl.SetItemText(WatchList[i].hTree,tmp);
						else
							WatchList[i].hTree=ctl.InsertItem(tmp,0,0);
					}
					else
					{
						tmp.Format("[%d]=%s",j,xtmp);
						if (!WatchList[i].Modified)
							ctl.SetItemText(WatchList[i].hItems[j],tmp);
						else
						{
							HTREEITEM item=ctl.InsertItem(tmp,0,0,WatchList[i].hTree);
							WatchList[i].hItems.Add(item);
						}
					}
				}
				WatchList[i].Modified=false;
			}
			else
			{
				if (!WatchList[i].Modified)
					ctl.SetItemText(WatchList[i].hTree,tmp);
				else
					WatchList[i].hTree=ctl.InsertItem(tmp,0,0);
				WatchList[i].Modified=true;
			}
			delete [] fdata;
			break;
		case CWatchItem::TYPE_STRING:
			cdata=new char[WatchList[i].Size+1];
			if (app->ReadData(cdata,addr,WatchList[i].Size,type))
			{
				cdata[WatchList[i].Size-1]='\0';
				tmp.Format("(%x:%x) %s=\"%s\"",saddr.Seg,saddr.Off,WatchList[i].Name,cdata);
				if (!WatchList[i].Modified)
					ctl.SetItemText(WatchList[i].hTree,tmp);
				else
				{
					WatchList[i].hTree=ctl.InsertItem(tmp,ICON_STRING,ICON_STRING);
				}
				WatchList[i].Modified=false;
			}
			else
			{
				if (!WatchList[i].Modified)
					ctl.SetItemText(WatchList[i].hTree,tmp);
				else
					WatchList[i].hTree=ctl.InsertItem(tmp,ICON_STRING,ICON_STRING);
				WatchList[i].Modified=true;
			}
			delete [] cdata;
			break;
		case CWatchItem::TYPE_STRUCT:
			int structnum=app->Structs.StructIndex(WatchList[i].Struct);
			if (structnum>=0)
			{
				HTREEITEM ritem[8];
				int ritemc=0;
				int len=app->Structs.SList[structnum].CalcSize(app->Structs.SList);
				cdata=new char[len*WatchList[i].Size+3];
				if (app->ReadData(cdata,addr,len*WatchList[i].Size,type))
				{
					int count=0;
					if (WatchList[i].Size>1)
						tmp.Format("(%x:%x) %s[%d]",saddr.Seg,saddr.Off,WatchList[i].Name,WatchList[i].Size);
					else
						tmp.Format("(%x:%x) %s {",saddr.Seg,saddr.Off,WatchList[i].Name);
					ritem[0]=WatchList[i].hTree;
					if (!WatchList[i].Modified)
						ctl.SetItemText(WatchList[i].hTree,tmp);
					else
						ritem[0]=WatchList[i].hTree=ctl.InsertItem(tmp,ICON_STRUCT,ICON_STRUCT);
					for (j=0;j<WatchList[i].Size;j++)
					{
						if (WatchList[i].Size>1)
						{
							xtmp.Format("(%x:%x) %s[%d]={",saddr.Seg,saddr.Off+len*j,WatchList[i].Name,j);
							
							if (!WatchList[i].Modified)
							{
								ritem[++ritemc]=WatchList[i].hItems[count];
								ctl.SetItemText(WatchList[i].hItems[count++],xtmp);
							}
							else
							{
								HTREEITEM item=ctl.InsertItem(xtmp,ICON_STRUCT,ICON_STRUCT,ritem[ritemc]);
								ritem[++ritemc]=item;
								WatchList[i].hItems.Add(item);
							}
						}
						CString indent;
						while (indent.GetLength()<(xtmp.GetLength()-7))
							indent+=' ';
						CArray<CString,CString &> tlist;
						int segs=*STACKSEG|(*DATASEG<<8)|(*SEGSIZE<<16);
						app->Structs.SList[structnum].DisplayStruct(tlist,cdata+j*len,segs,&app->Syms,app->Structs.SList,
							app->Structs.EList);
						for (int k=0;k<tlist.GetSize();k++)
						{
							bool newstruct=false,oldstruct=false;;
							int icon=ICON_NONE;
							if (tlist[k].GetAt(0)=='+')
							{
								newstruct=true;
								icon=ICON_STRUCT;
								tmp=indent+tlist[k].Right(tlist[k].GetLength()-1);
							}
							else
							if (tlist[k].GetAt(0)=='-')
							{
								oldstruct=true;
								tmp=indent+tlist[k].Right(tlist[k].GetLength()-1);
							}
							else
								tmp=indent+tlist[k];
							if (k==tlist.GetSize()-1)
								tmp+=" }";
							if (!WatchList[i].Modified)
							{
								ctl.SetItemText(WatchList[i].hItems[count++],tmp);
							}
							else
							{
								HTREEITEM item=ctl.InsertItem(tmp,icon,icon,ritem[ritemc]);
								if (newstruct)
									ritem[++ritemc]=item;
								if (oldstruct)
									ritemc--;
								WatchList[i].hItems.Add(item);
							}
						}
						if (WatchList[i].Size>1)
							ritemc--;

					}
					WatchList[i].Modified=false;
				}
				else
				{
					if (!WatchList[i].Modified)
						ctl.SetItemText(WatchList[i].hTree,tmp);
					else
						WatchList[i].hTree=ctl.InsertItem(tmp,ICON_STRUCT,ICON_STRUCT);
					WatchList[i].Modified=true;
				}
				delete [] cdata;
			}
		}
	}
	UpdateInProgress=false;
	if (AutoTime)
		SetTimer(1,AutoTime*1000,NULL);
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->SetMessageText("Ready.");
}

void CWatchView::OnInitialUpdate() 
{
	GetTreeCtrl().ModifyStyle(NULL,TVS_HASBUTTONS | TVS_HASLINES |TVS_LINESATROOT );
	CTreeView::OnInitialUpdate();
}

void CWatchView::OnDeleteWatch() 
{
	DeleteWatch();
	OnUpdate();
}

void CWatchView::OnModify() 
{
	if ((SelWItem<0)||(WatchList.GetSize()==0))
		return;
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	CAddWDlg edlg;
	edlg.Title="Edit Watch";
	edlg.Syms=&app->Syms;
	edlg.Structs=&app->Structs;
	edlg.m_Address=WatchList[SelWItem].Name;
	edlg.m_Hex=WatchList[SelWItem].Hex;
	edlg.m_Length=WatchList[SelWItem].Size;
	edlg.m_Type=WatchList[SelWItem].Type;
	edlg.m_StructList=WatchList[SelWItem].Struct;
	edlg.m_Unsigned=WatchList[SelWItem].Signed?false:true;
	if (WatchList[SelWItem].IsIo)
		edlg.m_MType=1;
	else
	if (WatchList[SelWItem].IsEio)
		edlg.m_MType=2;
	if (edlg.DoModal()==IDOK)
	{
		CWatchVItem item;
		item=WatchList[SelWItem]; // we need to copy view table
		item.Name=edlg.m_Address;
		item.Size=edlg.m_Length;
		item.Type=CWatchItem::WTYPE(edlg.m_Type);
		item.Hex=edlg.m_Hex>0;
		item.Struct=edlg.m_StructList;
		item.Modified=true;
		if (item.Hex)
			item.Signed=false;
		else
			item.Signed=edlg.m_Unsigned?false:true;
		item.IsIo=edlg.m_MType==1;
		item.IsEio=edlg.m_MType==2;
		WatchList.SetAt(SelWItem,item);
		CTreeCtrl& ctl=GetTreeCtrl();
		ctl.SelectItem(NULL);
		for (int i=0;i<WatchList.GetSize();i++)
			WatchList[i].Modified=true;
		OnUpdate();
	}
}

void CWatchView::OnAuto() 
{
	CEditIntDlg dlg;
	dlg.m_intval=AutoTime;
	if (dlg.DoModal()==IDOK)
	{
		AutoTime=dlg.m_intval;
		if (AutoTime)
			SetTimer(1,AutoTime*1000,NULL);
		else
			KillTimer(1);
	}
}

void CWatchView::OnUpdateAuto(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(AutoTime?1:0);	
	
}

void CWatchView::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==1)
	{
		OnUpdate();
	}
	else
		CTreeView::OnTimer(nIDEvent);
}

void CWatchView::OnSaveWatch() 
{
	SaveWatch(false);
}

void CWatchView::SaveWatch(bool tmpw) 
{
	CString inifile;
	if (tmpw)
		inifile=m_TempFile;
	else
	{
		inifile=AfxGetApp()->GetProfileString("Files","Watch File","*.watch");
		CFileDialog dlg(FALSE,"map",inifile,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Watch files (*.watch)|*.watch|All Files (*.*)|*.*||");
		if (dlg.DoModal()!=IDOK)
		{
			return;
		}
		inifile=dlg.GetPathName();
		AfxGetApp()->WriteProfileString("Files","Watch File",inifile);
	}
	DeleteFile(inifile);
	CString val;
	val.Format("%d",WatchList.GetSize());
	WritePrivateProfileString("Watch List","Watch Count",val,inifile); // clear file
	for (int i=0;i<WatchList.GetSize();i++)
	{
		CString wname,param;
		wname.Format("Watch%dName",i);
		WritePrivateProfileString("Watch List",wname,WatchList[i].Name,inifile);
		wname.Format("Watch%dHex",i);
		WritePrivateProfileString("Watch List",wname,WatchList[i].Hex?"1":"0",inifile);
		wname.Format("Watch%dSigned",i);
		WritePrivateProfileString("Watch List",wname,WatchList[i].Signed?"1":"0",inifile);
		wname.Format("Watch%dSize",i);
		val.Format("%d",WatchList[i].Size);
		WritePrivateProfileString("Watch List",wname,val,inifile);
		wname.Format("Watch%dStruct",i);
		WritePrivateProfileString("Watch List",wname,WatchList[i].Struct,inifile);
		wname.Format("Watch%dType",i);
		val.Format("%d",int(WatchList[i].Type));
		WritePrivateProfileString("Watch List",wname,val,inifile);
		wname.Format("Watch%dIsIo",i);
		param.Format("%d",WatchList[i].IsIo?1:0);
		WritePrivateProfileString("Watch List",wname,param,inifile);
		wname.Format("Watch%dIsEio",i);
		param.Format("%d",WatchList[i].IsEio?1:0);
		WritePrivateProfileString("Watch List",wname,param,inifile);
	}
}

void CWatchView::OnLoadWatch() 
{
	LoadWatch(false);
	OnUpdate();
}

void CWatchView::LoadWatch(bool tmpw) 
{
	CString inifile;
	if (tmpw)
		inifile=m_TempFile;
	else
	{
		inifile=AfxGetApp()->GetProfileString("Files","Watch File","*.watch");
		CFileDialog dlg(TRUE,"map",inifile,OFN_HIDEREADONLY,"Watch files (*.watch)|*.watch|All Files (*.*)|*.*||");
		if (dlg.DoModal()!=IDOK)
		{
			return;
		}
		inifile=dlg.GetPathName();
		AfxGetApp()->WriteProfileString("Files","Watch File",inifile);
	}
	int size=GetPrivateProfileInt("Watch List","Watch Count",0,inifile); // clear file
	for (int i=0;i<size;i++)
	{
		CWatchVItem item;
		char vbuff[80];
		CString wname;
		wname.Format("Watch%dName",i);
		GetPrivateProfileString("Watch List",wname,"error in watch file",vbuff,sizeof(vbuff),inifile);
		item.Name=vbuff;
		wname.Format("Watch%dHex",i);
		item.Hex=GetPrivateProfileInt("Watch List",wname,0,inifile)!=0;
		wname.Format("Watch%dSigned",i);
		item.Signed=GetPrivateProfileInt("Watch List",wname,1,inifile)!=0;
		wname.Format("Watch%dSize",i);
		item.Size=GetPrivateProfileInt("Watch List",wname,1,inifile);
		wname.Format("Watch%dStruct",i);
		GetPrivateProfileString("Watch List",wname,"",vbuff,sizeof(vbuff),inifile);
		item.Struct=vbuff;
		wname.Format("Watch%dType",i);
		item.Type=CWatchItem::WTYPE(GetPrivateProfileInt("Watch List",wname,0,inifile));
		wname.Format("Watch%dIsIo",i);
		item.IsIo=GetPrivateProfileInt("Watch List",wname,0,inifile)!=0;
		wname.Format("Watch%dIsEio",i);
		item.IsEio=GetPrivateProfileInt("Watch List",wname,0,inifile)!=0;
		WatchList.Add(item);
	}
	if (tmpw)
		DeleteFile(inifile);
}

void CWatchView::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hItem=pNMTreeView->itemNew.hItem;
//	bool found=false;
	CString tmp;
	SelWItem=SelWSubItem=-1;
	SelIsRoot=false;
	for (int witem=0;witem<WatchList.GetSize();witem++)
	{
		if (hItem==WatchList[witem].hTree)
		{
			TRACE("Selected root item: %d - %s\r\n",witem,WatchList[witem].Name);
			SelWItem=witem;
			SelIsRoot=true;
			FindItem(SelWItem,SelWSubItem,SelWType,SelWAddr,SelIsRoot,SelWSize,SelWLabel);
			*pResult=0;
			return;
		}
		for (int sitem=0;sitem<WatchList[witem].hItems.GetSize();
		sitem++)
			if (hItem==WatchList[witem].hItems[sitem])
			{
				TRACE("Selected item %d, sub item: %d - %s\r\n",witem,sitem,WatchList[witem].Name);
				SelWItem=witem;
				SelWSubItem=sitem;
				SelIsRoot=false;
				FindItem(SelWItem,SelWSubItem,SelWType,SelWAddr,SelIsRoot,SelWSize,SelWLabel);
				*pResult=0;
				return;
			}
	}
	*pResult = 0;
}

bool CWatchView::FindItem(int item, int sitem, int &type, SegOff &addr, bool isroot,int &arraysize,CString & label)
{
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	CMainFrame * pFrame=(CMainFrame *)app->m_pMainWnd;
	CWatchVItem *pItem=&WatchList[item];
	int count=0;
	CString tmp,tlabel;
	arraysize=1;
	app->Syms.EvalSymAdd(addr,pItem->Name);		// set addr to base
	label=pItem->Name;
	tmp.Format("%X:%X %s",addr.Seg,addr.Off,label);
	pFrame->SetStatusPane(tmp);
	if (isroot)
	{
		type=pItem->Type;
		label=pItem->Name;
		arraysize=pItem->Size;
		return true;
	}
//	while (count<sitem)
//	{
//			if (pItem->Size>1)
//				if (++count==sitem)
//					return false;
		CString index;
		for (int inum=0;inum<pItem->Size;inum++)
		{
			if (inum)
				index.Format("[%d]",inum);
			else
				index.Empty();
			type=pItem->Type;
			switch (pItem->Type)
			{
			case CWatchItem::TYPE_STRUCT:
				if (pItem->Size>1)			// if more than 1 then each struct has root in list
					if (count++==sitem)
					{
						tmp.Format("%X:%X %s%s",addr.Seg,addr.Off,label,index);
						pFrame->SetStatusPane(tmp);
						return false;
					}
				if (FindItemStruct(pItem,sitem,count,addr,type,app->Structs.StructIndex(pItem->Struct),arraysize,tlabel))
				{
					if (label.GetAt(0)=='*')
					{
						if (inum>0)
						{
							label=label.Right(label.GetLength()-1)+index+"."+tlabel;
						}
						else
						{
							label=label.Right(label.GetLength()-1)+"->"+tlabel;
						}
					}
					else
					{
						if (inum>0)
							label+=index;
						label+="."+tlabel;
					}
					tmp.Format("%X:%X %s",addr.Seg,addr.Off,label);
					pFrame->SetStatusPane(tmp);
					return true;
				}
				break;
			case CWatchItem::TYPE_CHAR:
				if (count==sitem)
				{
					if (inum>0)
						label+=index;
					tmp.Format("%X:%X %s",addr.Seg,addr.Off,label);
					pFrame->SetStatusPane(tmp);
					arraysize=1;
					return true;
				}
				addr+=1;
				count++;
				break;
			case CWatchItem::TYPE_INT:
				if (count==sitem)
				{
					if (inum>0)
						label+=index;
					tmp.Format("%X:%X %s",addr.Seg,addr.Off,label);
					pFrame->SetStatusPane(tmp);
					arraysize=2;
					return true;
				}
				addr+=2;
				count++;
				break;
			case CWatchItem::TYPE_LONG:
			case CWatchItem::TYPE_FLOAT:
				if (count==sitem)
				{
					if (inum>0)
						label+=index;
					tmp.Format("%X:%X %s",addr.Seg,addr.Off,label);
					pFrame->SetStatusPane(tmp);
					arraysize=4;
					return true;
				}
				addr+=4;
				count++;
				break;
			}
		}
//	}
	return false;
}

bool CWatchView::FindItemStruct(CWatchVItem * pItem,int sitem, int &count, SegOff &addr,int &type,int structnum,int &arraysize,CString &label)
{
	CString tlabel;
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	if (structnum<0)
		return false;
	CStruct * str=&app->Structs.SList[structnum];
	for (int eitem=0;eitem<str->Elements.GetSize();eitem++)
	{
		label=str->Elements[eitem].Name;
		switch (str->Elements[eitem].VarType)
		{
		case CStructItem::ENUM8:
		case CStructItem::BYTE:
			arraysize=str->Elements[eitem].NumElements;
			type=CWatchItem::TYPE_CHAR;
			if (count==sitem)
				return true;
			addr+=str->Elements[eitem].NumElements;
			count++;
			break;
		case CStructItem::NEAR_PTR:
		case CStructItem::ENUM16:
		case CStructItem::INT16:
			arraysize=str->Elements[eitem].NumElements;
			type=CWatchItem::TYPE_INT;
			if (count==sitem)
				return true;
			addr+=2*str->Elements[eitem].NumElements;
			count++;
			break;
		case CStructItem::FLOAT:
			arraysize=str->Elements[eitem].NumElements;
			type=CWatchItem::TYPE_FLOAT;
			if (count==sitem)
				return true;
			addr+=4*str->Elements[eitem].NumElements;
			count++;
			break;
		case CStructItem::FAR_PTR:
		case CStructItem::INT32:
			arraysize=str->Elements[eitem].NumElements;
			type=CWatchItem::TYPE_LONG;
			if (count==sitem)
				return true;
			addr+=4*str->Elements[eitem].NumElements;
			count++;
			break;
		case CStructItem::STRUCT:
			if (count++==sitem) // skip root of struct
			{
				return true;
			}
			if (FindItemStruct(pItem,sitem,count,addr,type,str->Elements[eitem].StructNum,arraysize,tlabel))
			{
				label+="."+tlabel;
				return true;
			}
			break;
		}
	}
	return false;
}

void CWatchView::OnEditData() 
{
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	SegOff addr=SelWAddr;;
	CString name=SelWLabel;
	int asize=SelWSize; // # elements in array
	int type=SelWType;
	KillTimer(1);
	if (SelWItem>=0)
//		if (FindItem(SelWItem,SelWSubItem,type,addr,SelIsRoot,asize,name))
		{
			int vlen=1;
			switch (type)
			{
			case CWatchItem::TYPE_FLOAT:
			case CWatchItem::TYPE_LONG:
				vlen=4;
				break;
			case CWatchItem::TYPE_INT:
				vlen=2;
				break;
			case CWatchItem::TYPE_STRING:
				vlen=1;
				break;
			}
			if ((type!=CWatchItem::TYPE_STRING)&&(type!=CWatchItem::TYPE_CHAR)&&(asize>1))
			{
				CEditIntDlg dlg;
				dlg.Title="Select index of item";
				dlg.Prompt.Format("Range 0 to %d.",asize-1);
				if (dlg.DoModal()!=IDOK)
				{
					if (AutoTime)
						SetTimer(1,AutoTime*1000,NULL);
					return;
				}
				addr+=dlg.m_intval*vlen;
				asize=1;
			}
			char * vardata=new char[asize*vlen+3]; // allow long it edit
			*vardata=0;
			int iotype=0;
			if (WatchList[SelWItem].IsIo)
				iotype=DEBUG_IREAD;
			if (WatchList[SelWItem].IsEio)
				iotype=DEBUG_EREAD;
			if (app->ReadData(vardata,addr.GetLinear(),asize*vlen,iotype))
			{
				CEditVarDlg dlg;
				dlg.m_VarText=name;
				CString fmt("%d");
				if (WatchList[SelWItem].Hex)
					fmt="0x%X";
				
				int ok=0;
				switch (type)
				{
				case CWatchItem::TYPE_CHAR:
					if (asize==1)
						dlg.m_VarData.Format("%d",*vardata);
					else
					{
						((char *)vardata)[asize]='\0';
						dlg.m_VarData=vardata;
					}
					break;
				case CWatchItem::TYPE_FLOAT:
					dlg.m_VarData.Format("%f",*(float *)vardata);
					break;
				case CWatchItem::TYPE_LONG:
					dlg.m_VarData.Format(fmt,*(long *)vardata);
					break;
				case CWatchItem::TYPE_INT:
					dlg.m_VarData.Format(fmt,*(short *)vardata);
					break;
				case CWatchItem::TYPE_STRING:
					dlg.m_VarData=(char *)vardata;
					break;
				}
				while (!ok&&dlg.DoModal()==IDOK)
				{
					if (type==CWatchItem::TYPE_CHAR)
					{
						if (asize==1)
						{
							if (dlg.m_VarData.Find("0x")>=0)
								fmt="0x%X";
							else 
								fmt="%d";
							ok=sscanf(dlg.m_VarData,fmt,vardata);
						}
						else
						if (dlg.m_VarData.GetLength()<=asize)
						{
							memcpy(vardata,dlg.m_VarData,asize);
							ok=1;
						}
					}
					else
					if (type==CWatchItem::TYPE_STRING)
					{
						vlen=dlg.m_VarData.GetLength()+1;
						strcpy((char *)vardata,dlg.m_VarData);
						ok=1;
					}
					else
					if (type==CWatchItem::TYPE_FLOAT)
					{
						double d;
						d=atof(dlg.m_VarData);
						*(float*)vardata=float(d);
						ok=1;
					}
					else
					{   
						int tdata;
						if (dlg.m_VarData.Find("0x")>=0)
							fmt="0x%X";
						else 
							fmt="%d";
						ok=sscanf(dlg.m_VarData,fmt,&tdata);
						if (type==CWatchItem::TYPE_LONG)
							*((int *)vardata)=tdata;
						else
							if (type==CWatchItem::TYPE_INT)
								*((short int *)vardata)=short(tdata);
						
					}
					if (!ok)
					{
						AfxMessageBox("Error converting data.");
					}
					else
					{
						if (WatchList[SelWItem].IsIo)
							iotype=DEBUG_IWRITE;
						if (WatchList[SelWItem].IsEio)
							iotype=DEBUG_EWRITE;
						app->WriteData(vardata,addr.GetLinear(),vlen*asize,iotype);
					}

				}
			}
			else
			{
				AfxMessageBox("Error reading Data.");
				if (AutoTime)
					SetTimer(1,AutoTime*1000,NULL);
				delete vardata;
				return;
			}
			delete vardata;
		}
	OnUpdate();
}

void CWatchView::OnUpdateEditData(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((SelWItem>=0)?TRUE:FALSE);	
}

void CWatchView::OnUpdateDeleteWatch(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(((SelWItem>=0)&&SelIsRoot)?TRUE:FALSE);	
}

void CWatchView::OnUpdateModify(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(((SelWItem>=0)&&SelIsRoot)?TRUE:FALSE);	
}

void CWatchView::OnUpdateUpdate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UpdateInProgress?1:0);	
}

void CWatchView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	SendMessage(WM_LBUTTONDOWN,MK_LBUTTON,MAKELPARAM(point.x,point.y));
	SendMessage(WM_LBUTTONUP,MK_LBUTTON,MAKELPARAM(point.x,point.y));
	if (SelWItem<0)
		return;
	CMenu Popup;
	Popup.CreatePopupMenu();
	if (SelIsRoot)
	{
		Popup.AppendMenu(MF_STRING,ID_DELETEW,"&Delete Watch");
		Popup.AppendMenu(MF_STRING,ID_MODIFY,"&Modify Watch");
	}
	Popup.AppendMenu(MF_STRING,ID_EDITDATA,"&Edit Data");
	Popup.AppendMenu(MF_STRING,ID_UPDATE,"&Update Data");

	// the font popup is stored in a resource
	ClientToScreen(&point);
	Popup.TrackPopupMenu( TPM_LEFTALIGN, point.x, point.y, this );
}

void CWatchView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE0("CMyTreeCtrl::OnRClick()\n");
	// Send WM_CONTEXTMENU to self
	SendMessage(WM_CONTEXTMENU, (WPARAM) m_hWnd, GetMessagePos());
	// Mark message as handled and suppress default handling
	*pResult = 1;
}

void CWatchView::DeleteWatch()
{
	if ((SelWItem<0)||(SelWItem>WatchList.GetSize()))
		return;
	CTreeCtrl& ctl=GetTreeCtrl();
	WatchList.RemoveAt(SelWItem);
	SelWItem=-1;
	ctl.SelectItem(NULL);
	 for (int i=0;i<WatchList.GetSize();i++)
		WatchList[i].Modified=true;
}
