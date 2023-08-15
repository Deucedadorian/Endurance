#if !defined(AFX_EDITVARDLG_H__443CBB0E_CA1B_4DEA_915D_C60CD945F5DE__INCLUDED_)
#define AFX_EDITVARDLG_H__443CBB0E_CA1B_4DEA_915D_C60CD945F5DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditVarDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditVarDlg dialog

class CEditVarDlg : public CDialog
{
// Construction
public:
	CEditVarDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditVarDlg)
	enum { IDD = IDD_EDITVAR };
	CString	m_VarText;
	CString	m_VarData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditVarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditVarDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITVARDLG_H__443CBB0E_CA1B_4DEA_915D_C60CD945F5DE__INCLUDED_)
