// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__1535FBC0_C711_457C_83F7_686AC90FB41E__INCLUDED_)
#define AFX_CHILDVIEW_H__1535FBC0_C711_457C_83F7_686AC90FB41E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "Symbols.h"	// Added by ClassView
#include "Struct.h"	// Added by ClassView
#include "udpdebug.h"

class CChildView;

//#include "PopupDlg.h"
class CPopupDlg;
/////////////////////////////////////////////////////////////////////////////
// CChildView window


class CChildView : public CWnd
{
// Construction
public:
	CChildView();
	bool Active;
//	CAsyncSocket ASock;

// Attributes
public:

	CArray<CPopupDlg *,CPopupDlg *> Popups;
	CArray<CString,CString &> DisplayText;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	static int m_First;
	bool m_Pause;
	int m_Wrap;
	bool m_Updated;
	bool m_AutoCR;
	void CheckRows();
	void DoClr(int mode);
	void ClrEOL();
	void Cls();
	int m_Row;
	int m_Attr;
	int TimeCount;
	void Newline();
	void VScroll();
	void set_attibute(int attr);
	void ProcANSI(char c);
	CFont * SelectFont(CDC *dc, bool SetHeight, CFont &Cfont);
	int m_FirstRow;
	int m_MaxLines;
	bool TimeStamp;
	bool LogToFile;
	CFile LogFile;
	void ProcessDbg(DBG_CMD * cmd);
	bool m_Maximize;
	bool m_UpdateActive;
	int m_Lines;
	int m_Col;
	void ProcessRx(CString &itxt);
	void InitSock();
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnReconnect();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnLogfile();
	afx_msg void OnUpdateLogfile(CCmdUI* pCmdUI);
	afx_msg void OnTimeStamp();
	afx_msg void OnUpdateTimeStamp(CCmdUI* pCmdUI);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnAutoCR();
	afx_msg void OnUpdateAutoCR(CCmdUI* pCmdUI);
	afx_msg void OnCls();
	afx_msg void OnWrap();
	afx_msg void OnUpdateWrap(CCmdUI* pCmdUI);
	afx_msg void OnPause();
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__1535FBC0_C711_457C_83F7_686AC90FB41E__INCLUDED_)
