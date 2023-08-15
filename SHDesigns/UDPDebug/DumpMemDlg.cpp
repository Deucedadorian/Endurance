// DumpMemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "udpdebug.h"
#include "DumpMemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDumpMemDlg dialog


CDumpMemDlg::CDumpMemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDumpMemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDumpMemDlg)
	m_Size = _T("");
	m_Start = _T("");
	//}}AFX_DATA_INIT
}


void CDumpMemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDumpMemDlg)
	DDX_Text(pDX, IDC_MEM_SIZE, m_Size);
	DDX_Text(pDX, IDC_MEM_START, m_Start);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDumpMemDlg, CDialog)
	//{{AFX_MSG_MAP(CDumpMemDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumpMemDlg message handlers
