// ChildWFrm.cpp : implementation of the CChildWFrame class
//

#include "stdafx.h"
#include "UDPDebug.h"

#include "ChildWFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildWFrame

IMPLEMENT_DYNCREATE(CChildWFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildWFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildWFrame)
		ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
		ON_WM_SETFOCUS()
		ON_WM_CREATE()
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildWFrame construction/destruction

CChildWFrame::CChildWFrame()
{
}

CChildWFrame::~CChildWFrame()
{
}

BOOL CChildWFrame::PreCreateWindow(CREATESTRUCT& cs)
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
// CChildWFrame diagnostics

#ifdef _DEBUG
void CChildWFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildWFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildWFrame message handlers
void CChildWFrame::OnFileClose() 
{
	// To close the frame, just send a WM_CLOSE, which is the equivalent
	// choosing close from the system menu.

	SendMessage(WM_CLOSE);
}

int CChildWFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, "Watch Window", AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	EnableDocking(CBRS_ALIGN_TOP);	
	m_WToolBar.Create(this);
	m_WToolBar.SetSizes(CSize(31,21),CSize(24,15));
	m_WToolBar.LoadToolBar(IDR_WTOOLBAR);
	m_WToolBar.SetBarStyle(m_WToolBar.GetBarStyle() |CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|CBRS_FLYBY);
	m_WToolBar.EnableDocking(CBRS_ALIGN_TOP);
	DockControlBar(&m_WToolBar);
	CUDPDebugApp * App=(CUDPDebugApp *)AfxGetApp();
	m_wndView.SEGSIZE=&App->SEGSIZE;
	m_wndView.STACKSEG=&App->STACKSEG;
	m_wndView.DATASEG=&App->DATASEG;
	return 0;
}

void CChildWFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);

	m_wndView.SetFocus();
}

BOOL CChildWFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
//	if (nID==ID_VIEW_TOOLBAR)
//		return FALSE;	// don't handle this
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	
	// otherwise, do default handling
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CChildWFrame::ActivateFrame(int nCmdShow) 
{
//	CMainFrame * parent=(CMainFrame * )AfxGetApp()->GetMainWnd();
//	if (++(parent->m_NumViews)==1)
//		nCmdShow=SW_MAXIMIZE;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


void CChildWFrame::OnContextHelp() 
{
	((CUDPDebugApp *)AfxGetApp())->MyContextHelp();	
}
