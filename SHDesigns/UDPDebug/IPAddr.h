#if !defined(AFX_IPADDR_H__E86DD65B_7169_4EAB_AFE9_138FB7839F1F__INCLUDED_)
#define AFX_IPADDR_H__E86DD65B_7169_4EAB_AFE9_138FB7839F1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IPAddr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIPAddr dialog

class CIPAddr : public CDialog
{
// Construction
public:
	CIPAddr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIPAddr)
	enum { IDD = IDD_IPADDR };
	CString	m_IP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPAddr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIPAddr)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPADDR_H__E86DD65B_7169_4EAB_AFE9_138FB7839F1F__INCLUDED_)
