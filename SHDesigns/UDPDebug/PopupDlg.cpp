// PopupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "udpdebug.h"
#include "PopupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg dialog


CPopupDlg::CPopupDlg(UINT id,CWnd* pParent /*=NULL*/)
	: CDialog(id, pParent)
{
	//{{AFX_DATA_INIT(CPopupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(CPopupDlg, CDialog)
	//{{AFX_MSG_MAP(CPopupDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg message handlers

CPopupDlg::~CPopupDlg()
{
}

void CPopupDlg::PostNcDestroy() 
{
	delete this;
}

