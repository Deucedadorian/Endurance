#include "stdafx.h"
#include "Symbols.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "PopupDlg.h"

void CSymList::ReadSymbols(bool OpenLast,bool isbios,int stack,int segsize)
{
	int i;
	CSym tSym;
	CString LastFile;
	int xsegsize=0xf000&(segsize<<8);
	if (isbios)
		LastFile=AfxGetApp()->GetProfileString("Files","Bios Map File","*.map");
	else
		LastFile=AfxGetApp()->GetProfileString("Files","Map File","*.map");
	if (!OpenLast)
	{
		CFileDialog dlg(TRUE,"map",LastFile,OFN_HIDEREADONLY,"Map files (*.map)|*.map|All Files (*.*)|*.*||");
		if (dlg.DoModal()!=IDOK)
		{
			return;
		}
		LastFile=dlg.GetPathName();
	}
	FILE * fpi;
	fpi=fopen(LastFile,"rt");
	if (fpi==NULL)
	{	// reuse lastfile
		LastFile.Format("Could not open symbol file: %s",LastFile);
		AfxMessageBox(LastFile);
		return;
	}
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->SetMessageText("Reading symbols.");
	if (!OpenLast)
	{
		if (isbios)
			AfxGetApp()->WriteProfileString("Files","Bios Map File",LastFile);
		else
			AfxGetApp()->WriteProfileString("Files","Map File",LastFile);
	}
	bool is_softools=false;	
	char linebuff[200];
	fgets(linebuff,199,fpi);
	while (!feof(fpi))
	{	
		if (strstr(linebuff,"Global/static")!=NULL)
			break;
		if (strstr(linebuff,"Symbols sorted by address")!=NULL)
		{
			if (segsize&0xf)
				xsegsize=0xf000&(segsize<<12);
			is_softools=true;
			break;			
		}
		fgets(linebuff,199,fpi);
	}
	if (feof(fpi))
	{
		CString result;
		result.Format("Could not fine section: Global/static");
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->SetMessageText(result);
	}
	fgets(linebuff,199,fpi);	// get //addr/sze line
	RemoveAll(isbios);
	bool eof=false;
	while (!feof(fpi)&&!eof)
	{
		fgets(linebuff,199,fpi);	// get //addr/sze line
		if (strlen(linebuff)<2)
			eof=true;
		else
		{
			bool ok=false;
			char * s;
			char temp_name[80];
			int seg=0,off=0,size;
			if (is_softools)
			{
				size=0;
				if (linebuff[0]=='-')
					eof=true;
				else
					ok=sscanf(linebuff,"%x%x%s",&seg,&off,temp_name)==3;
				if (seg!=off)
				{
					if (off<xsegsize)
						seg=0;
					else
						seg=stack;
				}
				else
					seg=0;
			}
			else
			{
				seg=DATASEG;
				s=strchr(linebuff,':');
				if ((s==NULL)||(s>(linebuff+4)))	// no segment
					ok=sscanf(linebuff,"%x%d%s",&off,&size,temp_name)==3;
				else
					ok=sscanf(linebuff,"%x:%x%d%s",&seg,&off,&size,temp_name)==4;
				if (off<xsegsize)
					seg=0;
				else
					seg=stack;
				s=strchr(linebuff,'\n');
				if (s!=NULL)
					*s='\0';
			}
			if (!ok)
				TRACE("Error decoding: %s",linebuff);
			else
			if (!eof)
			{
				SegOff addr;
				tSym.Name.Format("%s",temp_name);
				if (FindAddr(addr,tSym.Name))
					TRACE("Symbol %s repeated\r\n",temp_name);
				else
				{
					tSym.Size=size;
					tSym.Addr.Seg=seg;
					tSym.Addr.Off=off;
					if (is_softools)
						tSym.Type.Empty();
					else
						tSym.Type=linebuff+90;
					tSym.IsBios=isbios;
					tSym.IsST=is_softools;
					i=GetNearestIndex(tSym.Addr);
					if (i>=0)
					{
						if (i==Syms.GetSize())
							Syms.Add(tSym);
						else
						InsertSym(i+1,tSym);
					}
					else
						InsertSym(0,tSym);
				}
			}
		}
	}
	fclose(fpi);
	m_Updated=true;
	CString result;
	result.Format("%d Symbols loaded.",Syms.GetSize());
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->SetStatusPane(result);
	((CUDPDebugApp *)AfxGetApp())->AddLog(result);
}

bool CSymList::FindAddr(SegOff & addr, CString &name)
{
	CString sname(name);
	sname=sname.Left(32);
	int size=Syms.GetSize();
	for (int i=0;i<size;i++)
		// source # load adds names that are not truncated
		if ((Syms[i].Name==sname)||(Syms[i].Name==name))
		{
			addr=Syms[i].Addr;
			return true;
		}
	return false;	// not found
}

int CSymList::FindNearest(SegOff addr, CString & txt)
{
	static char memspace[5]="XYPL";
	int size=Syms.GetSize();
	int proc=-1;
	unsigned oldseg=addr.Seg;
	int i=0;
	if (size)
	{
		i=GetNearestIndex(addr);
	}
	if ((i==size)||(size==0)||(i<0))
	{
		txt.Format("%04X:%04X",oldseg,addr.Off);
		return -1;
	}
	if (Syms[i].Addr==addr)
	{
		if (proc>0)
			txt.Format("%s[%d]",Syms[i].Name,proc);
		else
			txt=Syms[i].Name;
		return i;
	}
	else
	{
		if (proc>0)
			txt.Format("%s[%d] + %X",Syms[i].Name,proc,addr.GetLinear()-Syms[i].Addr.GetLinear());
		else
			txt.Format("%s + %X",Syms[i].Name,addr.GetLinear()-Syms[i].Addr.GetLinear());
		return i;
	}
	return -1;	// not found
	
}

unsigned SegOff::GetLinear() const
{
	return (Seg<<12)+Off;
}

bool SegOff::operator ==(const SegOff& s)
{
	return ((Seg==s.Seg)&&(Off==s.Off));
}

bool SegOff::operator !=(const SegOff& s)
{
	return ((Seg!=s.Seg)||(Off!=s.Off));
}

bool SegOff::operator>(const SegOff & s)
{
	return (GetLinear()>s.GetLinear());
}

bool SegOff::operator<(const SegOff & s)
{
	return (GetLinear()<s.GetLinear());
}

bool SegOff::operator>=(const SegOff & s)
{
	return (GetLinear()>=s.GetLinear());
}

bool SegOff::operator<=(const SegOff & s)
{
	return (GetLinear()<=s.GetLinear());
}

bool CSymList::EvalSymAdd(SegOff & addr, CString & txt)
{
	CString right,left,ltxt=txt;
	bool ishex=false;
	int postop=-1,defer=-1;
	// remove extra whitspace
	ltxt.TrimLeft();
	ltxt.TrimRight();
	if (txt.GetAt(0)=='*')
	{
		defer=1;
		ltxt=ltxt.Right(txt.GetLength()-1);
	}
	postop=ltxt.Find('-');
	if (postop<0)
		postop=ltxt.Find('+');
	if (postop>=0)
	{
		left=ltxt.Left(postop);
		right=ltxt.Right(txt.GetLength()-postop);
	}
	else
		left=ltxt;
	left.TrimRight();	// remove ws
	right.TrimLeft();	// remove ws
	ishex=false;
//	if (ltxt.Find(':')>0)
//		ishex=true;
	if ((ltxt[0]=='0')&&ltxt.GetLength()>1&&(toupper(ltxt[1])=='X'))
		ishex=true;
	if (ishex)
	{	CString tmp;
		int i;
		i=ltxt.Find(':');
		if ((ltxt[0]=='0')&&(toupper(ltxt[1])=='X'))
		{
			ltxt.SetAt(0,' ');
			ltxt.SetAt(1,' ');
		}
		ltxt.TrimLeft();

	
		addr.Seg=0;
		if (i>0)
		{
			if ((ltxt[i+1]=='0')&&(toupper(ltxt[i+2])=='X'))
			{
				ltxt.SetAt(i+1,' ');
				ltxt.SetAt(i+2,' ');
			}
			if (sscanf(ltxt,"%x:%x",&addr.Seg,&addr.Off)!=2)
				TRACE("Error decode x:x - %s\r\n",ltxt);
		}
		else
			if (sscanf(ltxt,"%x",&addr.Off)!=1)
				TRACE("Error decode hexx - %s\r\n",ltxt);
	}
	else
		if (!FindAddr(addr,left))
			return false;
	if (postop>=0)
	{
		bool sub=false;
		right.TrimLeft();
		if (right.GetLength())
		{
		if (right[0]=='-')
			sub=true;
		right=right.Right(right.GetLength()-1);
		sscanf(right,"%x",&postop); // reuse postop
		if (sub)
			addr-=postop;
		else
			addr+=postop;
		}
	}
	if (defer>=0)
	{
		unsigned long data=0;
		CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
		app->ReadData(&data,addr.GetLinear(),2);
		addr.Off=data&0xffff;
	}
	return true;
}

const SegOff & SegOff::operator -=(int i)
{
	Off-=i;
	while (Off&0xffff0000)	//overflow;
	{
		Off+=0x1000;
		Seg-=0x1;
	}
	Seg&=0xffff;	// wrap under
	return *this;
}

const SegOff & SegOff::operator +=(int i)
{
	Off+=i;
	while (Off&0xffff0000)	//overflow;
	{
		Seg+=0x1;
		Off-=0x1000;
	}
	Seg&=0xffff;	// wrap around
	return *this;
}

const SegOff & SegOff::operator =(int i)
{
	Seg=(i>>12)&0xff;
	Off=i&0x0fff;
	return *this;
}

int CSymList::GetSize()
{
	return Syms.GetSize();
}

int CSymList::GetNearestIndex(SegOff Addr)
{
	int i=0;
	int size=Syms.GetSize();
	if (size==0)
		return -1;
	while ((i<size)&&(Syms[i].Addr<Addr))
		i++;
	if ((i<size)&&(Syms[i].Addr>Addr))
		i--;	// move back to last to calculate offset from
	return i;
}

SegOff & CSymList::GetSymAddr(int index)
{
	return Syms[index].Addr;
}

CString & CSymList::GetSymName(int index)
{
	return Syms[index].Name;
}

void CSymList::InsertSym(int index, CSym & sym)
{
	Syms.InsertAt(index,sym);
}

bool CSymList::CompareSym(int index, CSym & Sym)
{
	return ((Sym.Name==Syms[index].Name)&&(Sym.Addr==Syms[index].Addr));
}

void CSymList::RemoveAll(bool isbios)
{
	for (int i=0;i<Syms.GetSize();)
	{
		if (Syms[i].IsBios==isbios)
			Syms.RemoveAt(i);
		else
			i++;
	}
}

