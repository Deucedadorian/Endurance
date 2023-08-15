// ChildFrm.cpp : implementation of the CChildTFrame class
//

#include "stdafx.h"
#include "UDPDebug.h"
#include "ChildTView.h"
#include "ChildTFrame.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildTFrame

IMPLEMENT_DYNCREATE(CChildTFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildTFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildTFrame)
		ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
		ON_WM_SETFOCUS()
		ON_WM_CREATE()
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildTFrame construction/destruction

CChildTFrame::CChildTFrame()
{
}

CChildTFrame::~CChildTFrame()
{
}

BOOL CChildTFrame::PreCreateWindow(CREATESTRUCT& cs)
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
// CChildTFrame diagnostics

#ifdef _DEBUG
void CChildTFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildTFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildTFrame message handlers
void CChildTFrame::OnFileClose() 
{
	// To close the frame, just send a WM_CLOSE, which is the equivalent
	// choosing close from the system menu.

	SendMessage(WM_CLOSE);
}

int CChildTFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	return 0;
}

void CChildTFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);

	m_wndView.SetFocus();
	SetWindowText(m_wndView.m_Title);
}

BOOL CChildTFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	
	// otherwise, do default handling
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CChildTFrame::ActivateFrame(int nCmdShow) 
{
//	CMainFrame * parent=(CMainFrame * )AfxGetApp()->GetMainWnd();
//	if (++(parent->m_NumViews)==1)
//		nCmdShow=SW_MAXIMIZE;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
	SetWindowText(m_wndView.m_Title);
}



void CChildTFrame::OnContextHelp() 
{
	((CUDPDebugApp *)AfxGetApp())->MyContextHelp();	
}

void CChildTFrame::OnKillFocus(CWnd* pNewWnd) 
{
	CMDIChildWnd::OnKillFocus(pNewWnd);
	
	SetWindowText(m_wndView.m_Title);
	Invalidate();
}
