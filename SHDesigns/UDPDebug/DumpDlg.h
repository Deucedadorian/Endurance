#if !defined(AFX_DUMPDLG_H__EA90033C_E52D_4FC7_80B1_7D2699FA3106__INCLUDED_)
#define AFX_DUMPDLG_H__EA90033C_E52D_4FC7_80B1_7D2699FA3106__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DumpDlg.h : header file
//
#include "ChildView.h"
#include "PopupDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDumpDlg dialog

class CDumpDlg : public CPopupDlg
{
// Construction
public:
	CDumpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDumpDlg)
	enum { IDD = IDD_DUMPMEM };
	CString	m_Address;
	int		m_Size;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDumpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDumpDlg)
	afx_msg void OnRead();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUMPDLG_H__EA90033C_E52D_4FC7_80B1_7D2699FA3106__INCLUDED_)
