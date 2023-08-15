// UDPDebug.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "UDPDebug.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ChildWFrm.h"
#include "IPAddr.h"
#include "dumpdlg.h"
#include "ChildTView.h"
#include "ChildTFrame.h"
#include "DumpMemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUDPDebugApp

BEGIN_MESSAGE_MAP(CUDPDebugApp, CWinApp)
	//{{AFX_MSG_MAP(CUDPDebugApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_NEWWVIEW, OnNewWView)
	ON_COMMAND(ID_READSYM, OnReadSym)
	ON_COMMAND(ID_READLASTSYM, OnReadLastsym)
	ON_COMMAND(ID_LOADSTRUCT, OnLoadStruct)
	ON_COMMAND(ID_LOADLASTSTRUCT, OnLoadLastStruct)
	ON_COMMAND(ID_DUMP, OnDump)
	ON_COMMAND(ID_SHOWSYM, OnShowSym)
	ON_COMMAND(ID_READBSYM, OnReadBiosSym)
	ON_COMMAND(ID_READLASTBSYM, OnReadlastBiosSym)
	ON_COMMAND(ID_DEF_LIST, OnDefList)
	ON_COMMAND(IDM_DUMP_RAM, OnDumpRam)
	ON_COMMAND(IDM_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDPDebugApp construction

CUDPDebugApp::CUDPDebugApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	ASockInit=false;
	PollEnabled=true;
	LockSem=NULL;
	m_LogView=NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUDPDebugApp object

CUDPDebugApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUDPDebugApp initialization

BOOL CUDPDebugApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("SHDesigns"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMDIFrameWnd* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create main MDI frame window
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	// try to load shared MDI menus and accelerator table
	//TODO: add additional member variables and load calls for
	//	additional menu types your application may need. 

	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_UDPDEBTYPE));
	m_hMDITMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_UDPDEBTYPE));
	m_hMDIWMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_UDPDEBWTYPE));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_UDPDEBTYPE));



	// The main window has been initialized, so show and update it.
	pFrame->ShowWindow(m_nCmdShow);
	pFrame->UpdateWindow();
	CIPAddr dlg;
	if (dlg.DoModal()==IDOK)
	{
		m_SockIP=dlg.m_IP;
	}
	else
	{
		return FALSE;
	}

	OnFileNew();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CUDPDebugApp message handlers

int CUDPDebugApp::ExitInstance() 
{
	//TODO: handle additional resources you may have added
	if (m_hMDIMenu != NULL)
		FreeResource(m_hMDIMenu);
	if (m_hMDIWMenu != NULL)
		FreeResource(m_hMDIWMenu);
	if (m_hMDITMenu != NULL)
		FreeResource(m_hMDITMenu);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	return CWinApp::ExitInstance();
}

void CUDPDebugApp::OnFileNew() 
{
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	// create a new MDI child window
	pFrame->CreateNewChild(
		RUNTIME_CLASS(CChildFrame), IDR_UDPDEBTYPE, m_hMDIMenu, m_hMDIAccel);
}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CUDPDebugApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CUDPDebugApp message handlers


void CUDPDebugApp::OnNewWView() 
{
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	// create a new MDI child window
	pFrame->CreateNewChild(
		RUNTIME_CLASS(CChildWFrame), IDR_UDPDEBWTYPE, m_hMDIWMenu, m_hMDIAccel);
}

void CUDPDebugApp::OnReadSym() 
{
	GetSegs();
	Syms.ReadSymbols(false,false,STACKSEG,SEGSIZE);	
}

void CUDPDebugApp::OnReadLastsym() 
{
	GetSegs();
	Syms.ReadSymbols(true,false,STACKSEG,SEGSIZE);	
}

void CUDPDebugApp::OnLoadStruct() 
{
	Structs.ReadSlist();	
}

void CUDPDebugApp::OnLoadLastStruct() 
{
	Structs.ReadSlist(true);	
}

bool CUDPDebugApp::SendDBG(DBG_CMD *cmd,int size)
{
	if (!ASockInit)
		InitSock();
	unsigned short * crc=(unsigned short *)&cmd->data[size-(sizeof(DBG_CMD)-2)];
	*crc=CRC16((unsigned char *)&cmd->cmd,size,0xffff);
	while ((ASock.SendTo(cmd,size+2,UDPDBG_PORT,m_SockIP)==SOCKET_ERROR)&&
		(GetLastError()==WSAEWOULDBLOCK))
		Sleep(100);
	return true;
}

void CUDPDebugApp::InitSock()
{
	ASock.Create(0,SOCK_DGRAM);
	ASockInit=true;

}

int CUDPDebugApp::DBGReceive(void *buff, int size,bool lock)
{
	if (lock)
		Lock();
	int ret=ASock.Receive(buff,size);
	if (ret<0)
	{
		int err=ASock.GetLastError();
		if (err!=WSAEWOULDBLOCK)
		{
			CString str;
			str.Format("Socket Receive Error: %d",err);
			AddLog(str);
		}
	}
	if (lock)
		Unlock();
	return ret;
}

void CUDPDebugApp::EnablePoll(bool enable)
{
	PollEnabled=enable;
}

void CUDPDebugApp::RegisterViewHandler(CChildView *view)
{
	View=view;
}

void MsgProcess(void)
{

    MSG msg;
    while ( ::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) 
    { 
        if ( !AfxGetApp()->PumpMessage( ) ) 
        { 
            break; 
        } 
    } 
}

int CUDPDebugApp::ProcessDBGCmd(DBG_CMD *cmd, int len,int rxlen)
{
	EnablePoll(false);
	Lock();
	int ret,retry=1000;
	DBG_CMD lcmd=*cmd;
	if (lcmd.cmd==DEBUG_IREAD||lcmd.cmd==DEBUG_EREAD)
		lcmd.paraml+=lcmd.parami;	// these return last addr
	if (len)
		SendDBG(cmd,len);
	while (--retry)
	{
		if ((ret=DBGReceive(cmd,rxlen,false))>0)
		{
			if (cmd->cmd==DEBUG_TEXT)
			{
				if (View!=NULL)
					View->ProcessDbg(cmd);
			}
			else
			if (cmd->cmd==lcmd.cmd&&cmd->paraml==lcmd.paraml)
			{
				EnablePoll(true);
				Unlock();
				return ret;
			}
		}
		else
		{
			if ((retry%250)==0&&len)
				SendDBG(&lcmd,len);
			Sleep(5);
		}
		MsgProcess();
	}
	Unlock();
	EnablePoll(true);
	return 0;
}

bool CUDPDebugApp::ReadData(void *buff, long addr, int size,int type)
{
	char * cbuff=(char *)buff;
	int len,ret,lsize=size;
	char lbuff[280];
	DBG_CMD * cmd=(DBG_CMD *)lbuff;
	bool isodd=(addr&1)!=0;
	if (type!=0)
		isodd=false;
	if (type==0)
		type=DEBUG_READ;
	if (isodd)
	{
		addr--;
		lsize++;
	}
	while (lsize>0)
	{
		if (lsize>256)
			len=256;
		else
			len=lsize;
		cmd->cmd=type;
		cmd->paraml=addr;
		cmd->parami=len;
		ret=ProcessDBGCmd(cmd,sizeof(DBG_CMD)-2,280);
		if (ret>0&&cmd->cmd==type)
		{
			memcpy(cbuff,cmd->data,len);
			lsize-=len;
			cbuff+=len;
			addr+=len;
		}
		else
		{
			AddLog(CString("Read Data Timeout."));
			return false;
		}
	}
	cbuff=(char*)buff;
	if (isodd)
		memmove(cbuff,cbuff+1,size);

	return true;

}

bool CUDPDebugApp::WriteData(void * data, int addr, int len,int type)
{
	char lbuff[280];
	DBG_CMD * cmd=(DBG_CMD *)lbuff;
	bool isodd=(addr&1)!=0;
	if (type!=0)
		isodd=false;
	if (isodd)
	{
		addr--;
		ReadData(cmd->data,addr,2);
		memcpy(cmd->data+1,data,len);
		len++;
	}
	else
		memcpy(cmd->data,data,len);
		if (type==0)
			cmd->cmd=DEBUG_WRITE;
		else
			cmd->cmd=type;
	cmd->paraml=addr;
	cmd->parami=len;
	SendDBG(cmd,sizeof(DBG_CMD)-2+len);
	return true;
}

void CUDPDebugApp::OnDump() 
{
	CDumpDlg * dlg=new CDumpDlg;
	dlg->Create(CDumpDlg::IDD,m_pMainWnd);
}

void CUDPDebugApp::Lock()
{
	if (LockSem==NULL)
		LockSem=new CSingleLock(&DBGSem,TRUE);
	else
	{
		if (LockSem->IsLocked())
			TRACE("Lock wait.\r\n");
		LockSem->Lock();
	}
}

void CUDPDebugApp::Unlock()
{
	if (LockSem!=NULL)
		LockSem->Unlock();

}

CUDPDebugApp::~CUDPDebugApp()
{
	if (LockSem)
		delete LockSem;
}


CChildTView * CUDPDebugApp::CreateTView(CString &name)
{
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	// create a new MDI child window
	CChildTFrame * pTFrame=(CChildTFrame *)pFrame->CreateNewChild(
		RUNTIME_CLASS(CChildTFrame), IDR_UDPDEBTTYPE, m_hMDITMenu, m_hMDIAccel);
	CChildTView * pView=&pTFrame->m_wndView;
	pView->m_Title=name;
	pTFrame->SetWindowText(name);
	return pView;
}

void CUDPDebugApp::OnShowSym() 
{
	CChildTView * pView=CreateTView(CString("Symbol List"));	
	CString txt,txt2;
	txt.Format("%-32s - Seg:off - Type","Symbol Name");
	pView->DisplayText.Add(txt);
	for (int i=0;i<Syms.GetSize();i++)
	{
		txt.Format("%-32s - %02X:%04X - %s",Syms.Syms[i].Name,
			Syms.Syms[i].Addr.Seg,Syms.Syms[i].Addr.Off,Syms.Syms[i].Type);
		pView->DisplayText.Add(txt);
	}
}

void CUDPDebugApp::MyContextHelp()
{
	OnContextHelp();
}

unsigned short CUDPDebugApp::CRC16(unsigned char * pcdataptr,int uslength,unsigned short uscrc)
{
	unsigned usdata;
	if (uslength==0) return(0);
	while(uslength--)
	{
		usdata=(*(pcdataptr++))<<8;
		uscrc=((uscrc&0xff)<<8)+(uscrc>>8);
		uscrc=uscrc^usdata;
		usdata=uscrc& 0xff00;
		usdata=usdata<<4;
		uscrc=uscrc^usdata;
		usdata = uscrc & 0xff00;
		usdata = usdata >> 5;
		uscrc = uscrc ^ usdata;
		usdata = usdata >> 7;
//		uscrc = uscrc ^ usdata;	// this was missing from code, just leave it for compatability
	}
	uscrc = ~(((uscrc & 0x00ff) <<8)+ (uscrc >> 8 ));
	return(uscrc);
}

void CUDPDebugApp::OnReadBiosSym() 
{
	Syms.ReadSymbols(false,true);	
}

void CUDPDebugApp::OnReadlastBiosSym() 
{
	Syms.ReadSymbols(true,true);	
	
}

void CUDPDebugApp::AddLog(CString str)
{
	if (!m_LogView)
		m_LogView=CreateTView(CString("Log View"));
	if (!m_LogView)
		return;
	m_LogView->m_pthis=&m_LogView;
	m_LogView->DisplayText.Add(str);
	m_LogView->Invalidate();
}

void CUDPDebugApp::OnDefList() 
{
	CString temps;
	if (m_DefView)	
		m_DefView->DestroyWindow();
	m_DefView=CreateTView(CString("Define List"));
	m_DefView->m_pthis=&m_DefView;
	for (int i=0;i<Structs.DList.GetSize();i++)
	{
		temps.Format("%s=%s",Structs.DList[i].Name,Structs.DList[i].Replace);
		m_DefView->DisplayText.Add(temps);
	}
	m_DefView->DisplayText.Add(CString("-------- Enums --------"));
	for (i=0;i<Structs.EList.GetSize();i++)
	{
		temps.Format("%s = {",Structs.EList[i].Name);
		m_DefView->DisplayText.Add(temps);
		for (int j=0;j<Structs.EList[i].EnumList.GetSize();j++)
		{
			temps.Format("\t%s=%d",Structs.EList[i].EnumList[j],Structs.EList[i].EnumVal[j]);
			if (j==Structs.EList[i].EnumList.GetSize()-1)
				temps+="};";
			m_DefView->DisplayText.Add(temps);
		}
	}
	
	m_DefView->Invalidate();
}

void CUDPDebugApp::GetSegs()
{
	char buff[280];
	DBG_CMD  * cmd=(DBG_CMD  *)buff;
	cmd->cmd=DEBUG_IREAD;
	cmd->parami=4;
	cmd->paraml=0x10;
	ProcessDBGCmd(cmd,sizeof(DBG_CMD)-2,sizeof(buff));
	CString tmps;
	STACKSEG=cmd->data[1]&0xff;
	DATASEG=cmd->data[2]&0xff;
	if (cmd->data[0]&0x20)
	{
		if (cmd->data[0]&0x8)
			DATASEG^=0x80;
		if (cmd->data[0]&0x4)
			DATASEG^=0x10;
	}
	Syms.DATASEG=DATASEG;
	SEGSIZE=cmd->data[3]&0xff;
	tmps.Format("STACKSEG=0x%x, DATASEG=0x%x,SEGSIZE=0x%x",STACKSEG,DATASEG,SEGSIZE);
	AddLog(tmps);
}

void CUDPDebugApp::OnDumpRam() 
{
	CDumpMemDlg dlg;
	dlg.m_Size=GetProfileString("Settings","Dump Size","2000");
	dlg.m_Start=GetProfileString("Settings","Dump Start","80000");
	if (dlg.DoModal()!=IDOK)
		return;
	WriteProfileString("Settings","Dump Size",dlg.m_Size);
	WriteProfileString("Settings","Dump Start",dlg.m_Start);
	char buff[256],*xxx;
	int addr=strtol(dlg.m_Start,&xxx,16);
	int size=strtol(dlg.m_Size,&xxx,16);
	int osize=size;
	CFileDialog fdlg(FALSE,NULL,GetProfileString("Settings","Dump File",""),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Binary files|*.bin||");
	if (fdlg.DoModal()!=IDOK)
		return;
	DWORD dwStart = GetTickCount();
	WriteProfileString("Settings","Dump File",fdlg.GetPathName());
	CFile fpo;
	fpo.Open(fdlg.GetPathName(),CFile::modeCreate|CFile::modeWrite);
	CMainFrame * pframe=(CMainFrame *)m_pMainWnd;
		CString str;
	while (size)
	{
		int bytes=size;
		if (bytes>256)
			bytes=256;
		if (ReadData(buff,addr,bytes))
		{
			str.Format("Read %x, %x left",addr,size);
			pframe->SetStatusPane(str);
			fpo.Write(buff,bytes);
			addr+=bytes;
			size-=bytes;
		}
	}
	fpo.Close();
	dwStart = GetTickCount()-dwStart;

	str.Format("Read complete %.3f kbytes/sec.",double(osize)/double(dwStart)+.0005);
	pframe->SetStatusPane(str);
}

void CUDPDebugApp::OnReset() 
{
	char buff[280];
	DBG_CMD  * cmd=(DBG_CMD  *)buff;
	cmd->cmd=DEBUG_RESET;
	cmd->parami=0;
	cmd->paraml=0;
	ProcessDBGCmd(cmd,sizeof(DBG_CMD)-2,sizeof(buff));
}
