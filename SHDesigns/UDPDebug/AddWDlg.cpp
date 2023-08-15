// AddWDlg.cpp : implementation file
//

#include "stdafx.h"
#include "udpdebug.h"
#include "AddWDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddWDlg dialog


CAddWDlg::CAddWDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddWDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddWDlg)
	m_Type = 0;
	m_Address = _T("");
	m_Length = 1;
	m_Hex = FALSE;
	m_Unsigned = FALSE;
	m_MType = 0;
	//}}AFX_DATA_INIT
}


void CAddWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddWDlg)
	DDX_Text(pDX, IDC_STRUCTLIST, m_StructList);
	DDX_Radio(pDX, IDC_CHAR, m_Type);
	DDX_Text(pDX, IDC_ADDR, m_Address);
	DDX_Text(pDX, IDC_SLENGTH, m_Length);
	DDV_MinMaxInt(pDX, m_Length, 1, 65535);
	DDX_Check(pDX, IDC_HEX, m_Hex);
	DDX_Check(pDX, IDC_SIGNED, m_Unsigned);
	DDX_Radio(pDX, IDC_MTYPE, m_MType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddWDlg, CDialog)
	//{{AFX_MSG_MAP(CAddWDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddWDlg message handlers

BOOL CAddWDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CComboBox * box=(CComboBox *)GetDlgItem(IDC_ADDR);
	for (int i=0;i<Syms->GetSize();i++)
		box->AddString(Syms->Syms[i].Name);
	box=(CComboBox *)GetDlgItem(IDC_STRUCTLIST);
	for (i=0;i<Structs->SList.GetSize();i++)
	{
		int index=box->AddString(Structs->SList[i].Name);
		if (Structs->SList[i].Name==m_StructList)
			box->SetCurSel(index);
	}
	m_Length=1;	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
