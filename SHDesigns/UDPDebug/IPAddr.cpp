// IPAddr.cpp : implementation file
//

#include "stdafx.h"
#include "UDPDebug.h"
#include "IPAddr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPAddr dialog


CIPAddr::CIPAddr(CWnd* pParent /*=NULL*/)
	: CDialog(CIPAddr::IDD, pParent)
{
	m_IP=AfxGetApp()->GetProfileString("Settings","LasiIP","");
	//{{AFX_DATA_INIT(CIPAddr)
	//}}AFX_DATA_INIT
}


void CIPAddr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPAddr)
	DDX_Text(pDX, IDC_IP_ADDR, m_IP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIPAddr, CDialog)
	//{{AFX_MSG_MAP(CIPAddr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPAddr message handlers

void CIPAddr::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	AfxGetApp()->WriteProfileString("Settings","LasiIP",m_IP);
	CDialog::OnOK();
}
