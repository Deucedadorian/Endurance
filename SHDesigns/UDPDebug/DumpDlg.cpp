// DumpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "udpdebug.h"
#include "DumpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDumpDlg dialog


CDumpDlg::CDumpDlg(CWnd* pParent /*=NULL*/)
	: CPopupDlg(CDumpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDumpDlg)
	m_Address = _T("");
	m_Size = 0;
	//}}AFX_DATA_INIT
}


void CDumpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDumpDlg)
	DDX_Text(pDX, IDC_ADDRESS, m_Address);
	DDX_Radio(pDX, IDC_MSIZE, m_Size);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDumpDlg, CPopupDlg)
	//{{AFX_MSG_MAP(CDumpDlg)
	ON_BN_CLICKED(IDC_READ, OnRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumpDlg message handlers

void CDumpDlg::OnRead() 
{
	char buff[280];
	UpdateData();
	int addr=strtol(m_Address,NULL,16);
	SegOff saddr;
	CString ascii,tmp,txt("Addr:  "),name=m_Address;
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();

	if (!app->Syms.EvalSymAdd(saddr,name))
	{
		txt.Format("Error in address: %s",m_Address);
		GetDlgItem(IDC_MEMDATA)->SetWindowText(txt);
		return;
	}
	addr=saddr.GetLinear();
	if  (app->ReadData(buff,addr,256))
	{
		for (int i=0;i<16;i++)
		{	
				switch (m_Size)
				{
				case 0: // byte
					tmp.Format("%02X ",(addr+i)&0xff);
					txt+=tmp;
					break;
				case 1: // word
					if ((i%2)==0)
					{
						tmp.Format("%04X  ",(addr+i)&0xffff);
						txt+=tmp;
					}
					break;
				case 2:
					if ((i%4)==0)
					{
						tmp.Format("%04X      ",addr+i);
						txt+=tmp;
					}
					break;
				}
		}
		txt+=" [     Ascii      ]\r\n";
		for (int j=0;j<16;j++)
		{
			ascii.Empty();
			tmp.Format("%05X: ",addr+(j*16));
			txt+=tmp;
			for (int i=0;i<16;i++)
			{	
				switch (m_Size)
				{
				case 0: // byte
					tmp.Format("%02X ",buff[j*16+i]&0xff);
					txt+=tmp;
					break;
				case 1: // word
					if ((i%2)==0)
					{
						tmp.Format("%04X  ",(*(short*)(buff+j*16+i))&0xffff);
						txt+=tmp;
					}
					break;
				case 2:
					if ((i%4)==0)
					{
						tmp.Format("%08X   ",*(int *)(buff+j*16+i));
						txt+=tmp;
					}
					break;
				}

				if (((buff[j*16+i]&0xff)<127)&&((buff[j*16+i]&0xff)>=' '))
					ascii+=buff[j*16+i];
				else
					ascii+='.';
			}
			txt+=" [";
			txt+=ascii;
			txt+="]\r\n";
		}
	}
	else
		txt="Error: No response from target!";
	GetDlgItem(IDC_MEMDATA)->SetWindowText(txt);
}

BOOL CDumpDlg::OnInitDialog() 
{
	CPopupDlg::OnInitDialog();
	CComboBox * box=(CComboBox *)GetDlgItem(IDC_ADDRESS);
	CUDPDebugApp * app=(CUDPDebugApp *)AfxGetApp();
	for (int i=0;i<app->Syms.GetSize();i++)
		box->AddString(app->Syms.Syms[i].Name);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
