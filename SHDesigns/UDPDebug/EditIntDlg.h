#if !defined(AFX_EDITINTDLG_H__CA723996_7D46_4E90_9E15_A055E21D4F51__INCLUDED_)
#define AFX_EDITINTDLG_H__CA723996_7D46_4E90_9E15_A055E21D4F51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditIntDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditIntDlg dialog

class CEditIntDlg : public CDialog
{
// Construction
public:
	CString Prompt;
	CString Title;
	CEditIntDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditIntDlg)
	enum { IDD = IDD_EDITINT };
 	int		m_intval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditIntDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditIntDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITINTDLG_H__CA723996_7D46_4E90_9E15_A055E21D4F51__INCLUDED_)
