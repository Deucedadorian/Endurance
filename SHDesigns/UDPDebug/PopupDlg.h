#if !defined(AFX_POPUPDLG_H__01597652_7832_400B_976D_81F960B8C99D__INCLUDED_)
#define AFX_POPUPDLG_H__01597652_7832_400B_976D_81F960B8C99D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupDlg.h : header file
//
class CPopupDlg;
#include "ChildView.h"
/////////////////////////////////////////////////////////////////////////////
// CPopupDlg dialog

class CPopupDlg : public CDialog
{
// Construction
public:
	CPopupDlg(UINT id,CWnd* pParent = NULL);   // standard constructor
	virtual ~CPopupDlg();

// Dialog Data
	//{{AFX_DATA(CPopupDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupDlg)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPopupDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPDLG_H__01597652_7832_400B_976D_81F960B8C99D__INCLUDED_)
