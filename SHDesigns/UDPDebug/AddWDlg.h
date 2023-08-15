#if !defined(AFX_ADDWDLG_H__5893E48B_6AA6_4A56_8FE1_DEB9EC5E5609__INCLUDED_)
#define AFX_ADDWDLG_H__5893E48B_6AA6_4A56_8FE1_DEB9EC5E5609__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddWDlg.h : header file
//
#include "Symbols.h"
#include "struct.h"

/////////////////////////////////////////////////////////////////////////////
// CAddWDlg dialog

class CAddWDlg : public CDialog
{
// Construction
public:
	CString Title;
 	CSymList * Syms;
	CStructList * Structs;
	CAddWDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddWDlg)
	enum { IDD = IDD_ADDWATCH };
	CString	m_StructList;
	int		m_Type;
	CString	m_Address;
	int		m_Length;
	BOOL	m_Hex;
	BOOL	m_Unsigned;
	int		m_MType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddWDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddWDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDWDLG_H__5893E48B_6AA6_4A56_8FE1_DEB9EC5E5609__INCLUDED_)
