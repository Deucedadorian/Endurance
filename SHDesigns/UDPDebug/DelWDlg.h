#if !defined(AFX_DELWDLG_H__B1028EAF_7B8C_4E8C_819E_553F0949B931__INCLUDED_)
#define AFX_DELWDLG_H__B1028EAF_7B8C_4E8C_819E_553F0949B931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DelWDlg.h : header file
//
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CDelWDlg dialog

class CDelWDlg : public CDialog
{
// Construction
public:
	CString Title;
	CDelWDlg(CWnd* pParent = NULL);   // standard constructor
	CArray<CString,CString &> List;
	CString Selected;
// Dialog Data
	//{{AFX_DATA(CDelWDlg)
	enum { IDD = IDD_DELETWATCH };
	CComboBox	m_WList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelWDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDelWDlg)
	afx_msg void OnSelchangeWlist();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELWDLG_H__B1028EAF_7B8C_4E8C_819E_553F0949B931__INCLUDED_)
