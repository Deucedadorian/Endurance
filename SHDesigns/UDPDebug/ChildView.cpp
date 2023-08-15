// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "UDPDebug.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "DumpDlg.h"
#include "IPAddr.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
	TimeStamp=LogToFile=Active=false;
	m_Row=m_Col=0;
	m_Lines=-1;
	m_MaxLines=500;
	m_Wrap=m_FirstRow=0;
	TimeCount=0;
	m_Pause=m_UpdateActive=false;
	m_AutoCR=true;
}

CChildView::~CChildView()
{
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	app->RegisterViewHandler(NULL);	
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_RECONNECT, OnReconnect)
	ON_WM_CHAR()
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_LOGFILE, OnLogfile)
	ON_UPDATE_COMMAND_UI(ID_LOGFILE, OnUpdateLogfile)
	ON_COMMAND(ID_TIMESTAMP, OnTimeStamp)
	ON_UPDATE_COMMAND_UI(ID_TIMESTAMP, OnUpdateTimeStamp)
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_AUTOCR, OnAutoCR)
	ON_UPDATE_COMMAND_UI(ID_AUTOCR, OnUpdateAutoCR)
	ON_COMMAND(ID_CLS, OnCls)
	ON_COMMAND(IDM_WRAP, OnWrap)
	ON_UPDATE_COMMAND_UI(IDM_WRAP, OnUpdateWrap)
	ON_WM_CLOSE()
	ON_COMMAND(IDM_PAUSE, OnPause)
	ON_UPDATE_COMMAND_UI(IDM_PAUSE, OnUpdatePause)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.dwExStyle |= WS_EX_CLIENTEDGE;

	cs.style &= ~WS_BORDER;
	cs.style|=WS_MAXIMIZE  ;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	app->RegisterViewHandler(this);	
	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	TEXTMETRIC tm;
	CRect winrect;
	//SetWindowText("Debug Console");
	dc.GetTextMetrics(&tm);
	CFont * OldFont,newfont;
	if (dc.IsPrinting())
	{
		dc.GetClipBox(&winrect);
		OldFont=SelectFont(&dc,false,newfont);
	}
	else
	{
		GetClientRect(&winrect);
		OldFont=SelectFont(&dc,true,newfont);
	}
	dc.GetTextMetrics(&tm);
	m_Lines=(winrect.bottom-winrect.top)/tm.tmHeight;
	if (m_Lines<DisplayText.GetSize())
	{
		ShowScrollBar(SB_VERT,TRUE);
		SetScrollRange(SB_VERT,0,DisplayText.GetSize()-m_Lines,false);
	}
	else
		ShowScrollBar(SB_VERT,FALSE);
	int CharWidth=tm.tmAveCharWidth;
	if (tm.tmPitchAndFamily&TMPF_FIXED_PITCH)
		CharWidth+=(CharWidth*2)/5;
	if (!m_UpdateActive)
	{
		while (DisplayText.GetSize()>m_MaxLines)
		{
			DisplayText.RemoveAt(0);
			if (m_FirstRow>0)
				m_FirstRow--;
		}
	}
	for (int i=m_FirstRow;i<DisplayText.GetSize();i++)
	{
		for (int j=0;j<DisplayText[i].GetLength();j++)
		{
			char c=DisplayText[i].GetAt(j);
			dc.TextOut(CharWidth*j,tm.tmHeight*(i-m_FirstRow),&c,1);
		}
		if (tm.tmHeight*(i-m_FirstRow)>winrect.bottom)
			break;
	}
	dc.SelectObject(OldFont);
}


void CChildView::OnTimer(UINT nIDEvent) 
{
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	if (++TimeCount>100)
	{
		DBG_CMD cmd;
		cmd.cmd=DEBUG_ENABLE;
		cmd.parami=-1;
		app->SendDBG(&cmd,sizeof(cmd));
		TimeCount=0;
		// this trims unused memory. 
//		SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);
	}
	char buff[280];
	if (nIDEvent==1)
	{
		if (!Active)
		{
			DBG_CMD cmd;
			cmd.cmd=DEBUG_ENABLE;
			cmd.parami=1;
			app->SendDBG(&cmd,sizeof(cmd));
			Active=true;
		}
		while ((app->PollEnabled)&&(app->DBGReceive(buff,280)>0))
			{
				DBG_CMD * cmd=(DBG_CMD*)buff;
				ProcessDbg(cmd);
			}
		if (m_Updated)
		{
			Invalidate();
			m_Updated=false;
		}
	}
	else
		CWnd ::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(1,100,NULL);
	
	return 0;
}

void CChildView::set_attibute(int attr)
{
	switch (attr)
	{
	case 0:
		m_Attr=0x7; // white text, black background
		break;
	case 1:
		m_Attr|=8;
		break;
	case 2:
		m_Attr&=0xf7;
		break;
	case 5:
	case 6:
		m_Attr|=0x80;
		break;
	case 7:
		m_Attr=0x70;
		break;
	case 8:
		m_Attr=0;
		break;
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
		m_Attr&=0xf8;
		m_Attr|=attr&0x7;
		break;
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
		m_Attr&=0x8f;
		m_Attr|=(attr&0x7)<<4;
		break;
	}
}

void CChildView::VScroll()
{
	if (DisplayText.GetSize()>m_MaxLines)
			DisplayText.RemoveAt(0);
	if (m_Row>=DisplayText.GetSize())
		m_Row=DisplayText.GetSize()-1;
}

void CChildView::Newline()
{
	m_Row++;
	if (m_Row>=m_MaxLines-1)
	{
		CString str;
		str.Empty();
		DisplayText.Add(str);
		VScroll();
		m_Row=m_MaxLines-1;
	}
	if (m_Row>=(m_Lines+m_FirstRow))
		m_FirstRow=1+m_Row-m_Lines;
	CheckRows();
}

void CChildView::ProcANSI(char c)
{
#define M_Norm 0
#define M_ESC 1
#define M_ANSI 2
#define M_ANSI2 3
#define M_ANSI3 4	
	static char mode=0;
	static int p1,p2,p3;
	if (m_Wrap&&(m_Col>=m_Wrap))
	{
		Newline();
		m_Col=0;
	}
	switch (mode)
	{
	case M_Norm:
		if (c== 27)
		{
			mode=M_ESC;
			break;
		}
		else
			switch (c)
			{
			case 8:
				m_Col--;
				if (m_Col<0)
					m_Col=0;
				break;
			case 7:
				MessageBeep(MB_OK);
				break;
			case '\r':
				//ClrEOL();
				m_Col=0;
				break;
			case '\n':
				Newline();
				break;
			case '\t':
				while ((++m_Col%8)!=0);
				break;
			default:
				CheckRows();
				while (DisplayText[m_Row].GetLength()<(m_Col+1))
					DisplayText[m_Row]+=' ';
				DisplayText[m_Row].SetAt(m_Col++,c);
		}
		break;
	case M_ESC:
		p1=p2=0;	// init params
		switch (c)
		{
		case '[':
			mode=M_ANSI;	// ansi sequence
			break;
		default:
			mode=M_Norm;	// unknown, so display
		}
		break;
	case M_ANSI:
		switch (c)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			p1=p1*10+(c-'0'); // convert to bin
			break;
		case 'J':
			DoClr(p1);
			mode=M_Norm;
			break;
		case ';':
			mode=M_ANSI2;
			break;
		case 'K':
			ClrEOL();
			mode=M_Norm;
			break;
		case 'm':
			set_attibute(p1);
			mode=M_Norm;
			break;
		default:
			mode=M_Norm;
		}
		break;
	case M_ANSI2:
		switch (c)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			p2=p2*10+(c-'0'); // convert to bin
			break;
		case 'm': // set video mode
			set_attibute(p1);
			set_attibute(p2);
			mode=M_Norm;
			break;
		case 'H':
		case 'f':
//			GotoRC(p1-1,p2-1);	// goto x/y
			m_Row=p2-1;
			m_Col=p1-1;
			CheckRows();
			mode=M_Norm;
			break;
		case ';':
			mode=M_ANSI3;
			break;
		case 'J':
			DoClr(p1);
			mode=M_Norm;
		}
		break;
	case M_ANSI3:
		switch (c)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			p3=p3*10+(c-'0'); // convert to bin
			break;
		case 'm': // set video mode
			set_attibute(p1);
			set_attibute(p2);
			set_attibute(p3);
			mode=M_Norm;
		default:
			mode=M_Norm;
			break;
		}
		break;
		
	default:
		mode=M_Norm; // in case we get in undefined mode
	}
}

void CChildView::ProcessRx(CString &itxt)
{
	if (TimeStamp)
	{
		CTime tm;
		tm=CTime::GetCurrentTime();
		CString tstr=tm.Format("(%m/%d %H:%M:%S) ");
		itxt=tstr+itxt;
	}
	if (m_AutoCR)
		for (int i=0;i<itxt.GetLength();i++)
			if (i>0&&itxt.GetAt(i)=='\n'&&itxt.GetAt(i-1)!='\r')
				itxt.Insert(i++,'\r'); // inc i or we'll insert endless \r's
	if (LogToFile)
	{	
		LogFile.Write(itxt,itxt.GetLength());
	}
	m_UpdateActive=true;
	for (int j=0;j<itxt.GetLength();j++)
		ProcANSI(itxt.GetAt(j));
	m_UpdateActive=false;
	m_Updated=true;
}

/// this never gets called!!! nor does Close()
BOOL CChildView::DestroyWindow() 
{
//	DBG_CMD cmd;
//	cmd.cmd=DEBUG_ENABLE;
//	cmd.parami=0;
//	while ((ASock.SendTo(&cmd,sizeof(cmd),UDPDBG_PORT,m_SockIP)==SOCKET_ERROR)&&
//		(GetLastError()==WSAEWOULDBLOCK))
//		Sleep(100);
	return CWnd ::DestroyWindow();
}

void CChildView::OnDestroy() 
{
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	DBG_CMD cmd;
	cmd.cmd=DEBUG_ENABLE;
	cmd.parami=0;

	app->SendDBG(&cmd,sizeof(cmd));
	CWnd ::OnDestroy();
//	for (int i=0;i<Popups.GetSize();i++)
//		Popups[i]->DestroyWindow();
//	Popups.RemoveAll();
}

void CChildView::OnReconnect() 
{
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	DBG_CMD cmd;
	cmd.cmd=DEBUG_ENABLE;
	cmd.parami=0;

	app->SendDBG(&cmd,sizeof(cmd));
	CIPAddr dlg;
	if (dlg.DoModal()==IDOK)
	{
		app->m_SockIP=dlg.m_IP;
	}
	Active=false;	
}

void CChildView::ProcessDbg(DBG_CMD *cmd)
{
	CString txt;
	switch (cmd->cmd)
	{
	case DEBUG_TEXT:
		cmd->data[cmd->parami]='\0';
		txt=cmd->data;
		if (!m_Pause)
			ProcessRx(txt);
		break;
	default:
		txt.Format("Unknown data: cmd=%d parami=%d, paraml=%d",cmd->cmd,cmd->parami,cmd->paraml);
		TRACE("%s\r\n",txt);
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->SetMessageText(txt);
	}
}

void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	DBG_CMD cmd;
	cmd.cmd=DEBUG_TEXT;
	cmd.parami=1;
	cmd.data[0]=(char)nChar;
	app->SendDBG(&cmd,sizeof(cmd)-1);
	
//	CWnd ::OnChar(nChar, nRepCnt, nFlags);
}

void CChildView::OnSysCommand(UINT nID, LPARAM lParam) 
{

    if(nID == SC_CLOSE)
        return;
    	
	CWnd ::OnSysCommand(nID, lParam);
}

void CChildView::OnLogfile() 
{
	if (LogToFile)
	{
		LogFile.Close();
		LogToFile=false;
		return;
	}
	CString LastFile;
	LastFile=AfxGetApp()->GetProfileString("Files","Log File","rabbit.log");
	CFileDialog dlg(FALSE,"map",LastFile,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,"Log files (*.log)|*.log|All Files (*.*)|*.*||");
	if (dlg.DoModal()!=IDOK)
	{
		return;
	}
	LastFile=dlg.GetPathName();
	AfxGetApp()->WriteProfileString("Files","Log File",LastFile);
	LogFile.Open(LastFile,CFile::modeWrite|CFile::modeCreate);
	LogToFile=true;
}

void CChildView::OnUpdateLogfile(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(LogToFile?1:0);	
}


void CChildView::OnTimeStamp() 
{
	TimeStamp=!TimeStamp;	
}

void CChildView::OnUpdateTimeStamp(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(TimeStamp?1:0);	
	
}

CFont * CChildView::SelectFont(CDC *dc, bool SetHeight, CFont &Cfont)
{
	CFont *oldfont;
//	TEXTMETRIC tm;
	LOGFONT font;
	memset(&font,0,sizeof(font));
//	if (SetHeight)
//		font.lfHeight=FontHeight; //rect.Height()/Rows;
//	else
		font.lfHeight=0;	// use default
	font.lfWeight=400;
	font.lfCharSet=DEFAULT_CHARSET;
	font.lfOutPrecision=OUT_DEFAULT_PRECIS;
	font.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	font.lfPitchAndFamily=FIXED_PITCH|FF_SWISS;
	strcpy(font.lfFaceName,"Ariel");
//
	if (!Cfont.CreatePointFontIndirect(&font,dc))
		AfxMessageBox("Could not create font",MB_OK);
//	if (!Cfont.CreateFont(SetHeight?FontHeight:0,0,0,0,600,0,0,0,
//		DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
//		DEFAULT_QUALITY,FIXED_PITCH,"Ariel"))
//		AfxMessageBox("Could not create font",MB_OK);
	oldfont=dc->SelectObject(&Cfont);
	return oldfont;

}

void CChildView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int Rows=DisplayText.GetSize();
	switch (nSBCode)
	{
	case SB_PAGEDOWN:
		if ((m_FirstRow+m_Lines)<Rows)
			m_FirstRow+=m_Lines-1;
		if ((m_FirstRow+m_Lines)>=Rows)
			m_FirstRow=Rows-m_Lines;
		Invalidate();
		break;
	case SB_LINEDOWN:
		if ((m_FirstRow+m_Lines)<Rows)
			m_FirstRow++;
		Invalidate();
		break;
	case SB_PAGEUP:
		if (m_FirstRow)
			m_FirstRow-=m_Lines-1;
		if (m_FirstRow<0)
			m_FirstRow=0;
		Invalidate();
		break;
	case SB_LINEUP:
		if (m_FirstRow)
			m_FirstRow--;
		Invalidate();
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		if ((int(nPos)>=0)&&(int(nPos)<=Rows-m_Lines))
			m_FirstRow=nPos;
		Invalidate();
		break;
	};
//	if (pScrollBar!=NULL)
//	{
		SetScrollPos(SB_VERT,m_FirstRow);
//	}
//	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
	case VK_NEXT:
		OnVScroll(SB_PAGEDOWN,0,NULL);
		break;
	case VK_PRIOR:
		OnVScroll(SB_PAGEUP,0,NULL);
		break;
	case VK_UP:
		OnVScroll(SB_LINEUP,0,NULL);
		break;
	case VK_DOWN:
		OnVScroll(SB_LINEDOWN,0,NULL);
		break;
	default:
	CWnd ::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

void CChildView::Cls()
{
	while (DisplayText.GetSize())
		DisplayText.RemoveAt(0);
	m_Row=m_FirstRow=m_Col=0;
}

void CChildView::ClrEOL()
{
	CString tmp=DisplayText[m_Row].Left(m_Col);
	DisplayText[m_Row]=tmp;
}

void CChildView::DoClr(int mode)
{
	CString str;
	str.Empty();
	if (mode==2)
	{
		Cls();
	}
	else
	if (mode==1)
	{	// clr home to cursor
		for (int i=0;i<m_Row;i++)
			DisplayText.SetAt(i,str);
		while (DisplayText[m_Row].GetLength()<m_Col)
			DisplayText[m_Row]+=' ';
		for (i=0;i<m_Col;i++)
			DisplayText[m_Row].SetAt(i,' ');
	}
	else
	{	// clear rest
		ClrEOL();	
		for (int i=m_Row+1;i<DisplayText.GetSize();i++)
			DisplayText.SetAt(i,str);

	}

}

void CChildView::CheckRows()
{
	CString str;
	str.Empty();
	while (DisplayText.GetSize()<(m_Row+1))
	{
		DisplayText.Add(str);
	}
}

void CChildView::OnAutoCR() 
{
	m_AutoCR=!m_AutoCR;	
}

void CChildView::OnUpdateAutoCR(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_AutoCR?1:0);	
}

void CChildView::OnCls() 
{
	Cls();
	Invalidate();
}

void CChildView::OnWrap() 
{
	if (m_Wrap)
		m_Wrap=0;
	else
		m_Wrap=80;
}

void CChildView::OnUpdateWrap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Wrap!=0?1:0);	
}

void CChildView::OnPause() 
{
	m_Pause=!m_Pause;
}

void CChildView::OnUpdatePause(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Pause?1:0);	
	
}
