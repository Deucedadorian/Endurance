// ChildTFrame.h: interface for the CChildTFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDTFRAME_H__4BD41746_B361_4DDF_BC3D_427A4CA91E5D__INCLUDED_)
#define AFX_CHILDTFRAME_H__4BD41746_B361_4DDF_BC3D_427A4CA91E5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CChildTFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildTFrame)
public:
	CChildTFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildTFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
public:
	// view for the client area of the frame.
	CChildTView m_wndView;
	virtual ~CChildTFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildTFrame)
	afx_msg void OnFileClose();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextHelp();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_CHILDTFRAME_H__4BD41746_B361_4DDF_BC3D_427A4CA91E5D__INCLUDED_)
