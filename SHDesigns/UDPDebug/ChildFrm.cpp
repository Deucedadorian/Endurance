// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "UDPDebug.h"

#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
		ON_WM_SETFOCUS()
		ON_WM_CREATE()
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
void CChildFrame::OnFileClose() 
{
	// To close the frame, just send a WM_CLOSE, which is the equivalent
	// choosing close from the system menu.

	SendMessage(WM_CLOSE);
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	CMenu *pSysMenu = GetSystemMenu(FALSE);
	ASSERT(pSysMenu != NULL);
	VERIFY(pSysMenu->RemoveMenu(SC_CLOSE, MF_BYCOMMAND)); 
	EnableDocking(CBRS_ALIGN_TOP);	
	m_SToolBar.Create(this);
	m_SToolBar.SetSizes(CSize(31,21),CSize(24,15));
	m_SToolBar.LoadToolBar(IDR_STOOLBAR);
	m_SToolBar.SetBarStyle(m_SToolBar.GetBarStyle() |CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|CBRS_FLYBY);
	m_SToolBar.EnableDocking(CBRS_ALIGN_TOP);
	DockControlBar(&m_SToolBar);
	return 0;
}

void CChildFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);

	m_wndView.SetFocus();
}

BOOL CChildFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// let the view have first crack at the command
//	if (nID==ID_VIEW_TOOLBAR)
//		return FALSE;	// don't handle this
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	
	// otherwise, do default handling
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CChildFrame::ActivateFrame(int nCmdShow) 
{
//	CMainFrame * parent=(CMainFrame * )AfxGetApp()->GetMainWnd();
//	if (++(parent->m_NumViews)==1)
//		nCmdShow=SW_MAXIMIZE;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


void CChildFrame::OnContextHelp() 
{
	((CUDPDebugApp *)AfxGetApp())->MyContextHelp();	
}
