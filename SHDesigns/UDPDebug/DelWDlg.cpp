// DelWDlg.cpp : implementation file
//

#include "stdafx.h"
#include "udpdebug.h"
#include "DelWDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelWDlg dialog


CDelWDlg::CDelWDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelWDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDelWDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDelWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDelWDlg)
	DDX_Control(pDX, IDC_WLIST, m_WList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDelWDlg, CDialog)
	//{{AFX_MSG_MAP(CDelWDlg)
	ON_CBN_SELCHANGE(IDC_WLIST, OnSelchangeWlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelWDlg message handlers

void CDelWDlg::OnSelchangeWlist() 
{
	int index=m_WList.GetCurSel();
	Selected=List[index];
}

BOOL CDelWDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (Title.GetLength())
		SetWindowText(Title);
	for (int i=0;i<List.GetSize();i++)
		m_WList.AddString(List[i]);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
