#if !defined(AFX_DUMPMEMDLG_H__244AD4A6_AB22_46D6_BE98_02538A3C2D06__INCLUDED_)
#define AFX_DUMPMEMDLG_H__244AD4A6_AB22_46D6_BE98_02538A3C2D06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DumpMemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDumpMemDlg dialog

class CDumpMemDlg : public CDialog
{
// Construction
public:
	CDumpMemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDumpMemDlg)
	enum { IDD = IDD_DUMPRAM };
	CString	m_Size;
	CString	m_Start;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDumpMemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDumpMemDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUMPMEMDLG_H__244AD4A6_AB22_46D6_BE98_02538A3C2D06__INCLUDED_)
