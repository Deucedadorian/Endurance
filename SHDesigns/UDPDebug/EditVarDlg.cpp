// EditVarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "udpdebug.h"
#include "EditVarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditVarDlg dialog


CEditVarDlg::CEditVarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditVarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditVarDlg)
	m_VarText = _T("");
	m_VarData = _T("");
	//}}AFX_DATA_INIT
}


void CEditVarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditVarDlg)
	DDX_Text(pDX, IDC_VNAME, m_VarText);
	DDX_Text(pDX, IDC_DATA, m_VarData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditVarDlg, CDialog)
	//{{AFX_MSG_MAP(CEditVarDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditVarDlg message handlers
