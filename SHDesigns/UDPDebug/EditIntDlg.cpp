// EditIntDlg.cpp : implementation file
//

#include "stdafx.h"
#include "udpdebug.h"
#include "EditIntDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditIntDlg dialog


CEditIntDlg::CEditIntDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditIntDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditIntDlg)
	m_intval = 0;
	//}}AFX_DATA_INIT
}


void CEditIntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditIntDlg)
	DDX_Text(pDX, IDC_INTVAL, m_intval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditIntDlg, CDialog)
	//{{AFX_MSG_MAP(CEditIntDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditIntDlg message handlers

BOOL CEditIntDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if	(Title.GetLength())
		SetWindowText(Title);
	if (Prompt.GetLength())
		GetDlgItem(IDC_PROMPT)->SetWindowText(Prompt);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
