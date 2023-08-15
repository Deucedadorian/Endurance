// ChildTView.h: interface for the CChildTView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDTVIEW_H__67C2F470_EC5B_438B_9ADB_49F8071860FD__INCLUDED_)
#define AFX_CHILDTVIEW_H__67C2F470_EC5B_438B_9ADB_49F8071860FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChildTView : public CWnd
{
// Construction
public:
	CChildTView();
//	CAsyncSocket ASock;

// Attributes
public:

	CArray<CString,CString &> DisplayText;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildTView)
	public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	CChildTView ** m_pthis;
	CFont * SelectFont(CDC * dc,bool SetHeight,CFont &Cfont);
	CString m_Title;
	int m_Lines;
	int m_FirstRow;
	int m_Col;
	virtual ~CChildTView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildTView)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_CHILDTVIEW_H__67C2F470_EC5B_438B_9ADB_49F8071860FD__INCLUDED_)
