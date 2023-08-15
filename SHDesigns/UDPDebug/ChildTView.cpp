// ChildTView.cpp: implementation of the CChildTView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "udpdebug.h"
#include "ChildTView.h"
#include "ChildTFrame.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildTView

CChildTView::CChildTView()
{
	m_FirstRow=0;
	m_Col=0;
	m_Lines=-1;
	m_pthis=NULL;
}

CChildTView::~CChildTView()
{
	if (m_pthis)
		*m_pthis=NULL;
}


BEGIN_MESSAGE_MAP(CChildTView,CWnd )
	//{{AFX_MSG_MAP(CChildTView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildTView message handlers

BOOL CChildTView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.dwExStyle |= WS_EX_CLIENTEDGE;

	cs.style &= ~WS_BORDER;
	cs.style|= FWS_ADDTOTITLE;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	return TRUE;
}

void CChildTView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	TEXTMETRIC tm;
	CRect winrect;
	GetParent()->SetWindowText(m_Title);
	SetWindowText(m_Title);
	CFont * OldFont,newfont;
	if (dc.IsPrinting())
	{
		dc.GetClipBox(&winrect);
		OldFont=SelectFont(&dc,false,newfont);
	}
	else
	{
		GetClientRect(&winrect);
		OldFont=SelectFont(&dc,true,newfont);
	}
	dc.GetTextMetrics(&tm);
	m_Lines=(winrect.bottom-winrect.top)/tm.tmHeight;
	if (m_Lines<DisplayText.GetSize())
	{
		ShowScrollBar(SB_VERT,TRUE);
		SetScrollRange(SB_VERT,0,DisplayText.GetSize()-m_Lines,false);
	}
	else
		ShowScrollBar(SB_VERT,FALSE);
//	while (DisplayText.GetSize()>m_Lines)
//			DisplayText.RemoveAt(0);
	int CharWidth=tm.tmAveCharWidth;
	if (tm.tmPitchAndFamily&TMPF_FIXED_PITCH)
		CharWidth+=(CharWidth*2)/5;
	CString txt;
	for (int i=m_FirstRow;i<DisplayText.GetSize();i++)
	{
		int col=0;
		for (int j=0;j<DisplayText[i].GetLength();j++)
		{
			char c=DisplayText[i].GetAt(j);
			if (c=='\r')
				txt="\\r";
			else
				if (c=='\n')
					txt="\\n";
				else
					txt=c;
			if (c!='\t')
			{
				dc.TextOut(CharWidth*col,tm.tmHeight*(i-m_FirstRow),txt,txt.GetLength());
				col+=txt.GetLength();
			}
			else
				while (++col&0x3);
		}
		if (tm.tmHeight*(i-m_FirstRow)>winrect.bottom)
			break;
	}
	dc.SelectObject(OldFont);
}

int CChildTView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}



void CChildTView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int Rows=DisplayText.GetSize();
	switch (nSBCode)
	{
	case SB_PAGEDOWN:
		if ((m_FirstRow+m_Lines)<Rows)
			m_FirstRow+=m_Lines-1;
		if ((m_FirstRow+m_Lines)>=Rows)
			m_FirstRow=Rows-m_Lines;
		Invalidate();
		break;
	case SB_LINEDOWN:
		if ((m_FirstRow+m_Lines)<Rows)
			m_FirstRow++;
		Invalidate();
		break;
	case SB_PAGEUP:
		if (m_FirstRow)
			m_FirstRow-=m_Lines-1;
		if (m_FirstRow<0)
			m_FirstRow=0;
		Invalidate();
		break;
	case SB_LINEUP:
		if (m_FirstRow)
			m_FirstRow--;
		Invalidate();
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		if ((int(nPos)>=0)&&(int(nPos)<=Rows-m_Lines))
			m_FirstRow=nPos;
		Invalidate();
		break;
	};
//	if (pScrollBar!=NULL)
//	{
		SetScrollPos(SB_VERT,m_FirstRow);
//	}
//	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CChildTView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
	case VK_NEXT:
		OnVScroll(SB_PAGEDOWN,0,NULL);
		break;
	case VK_PRIOR:
		OnVScroll(SB_PAGEUP,0,NULL);
		break;
	case VK_UP:
		OnVScroll(SB_LINEUP,0,NULL);
		break;
	case VK_DOWN:
		OnVScroll(SB_LINEDOWN,0,NULL);
		break;
	default:
	CWnd ::OnKeyDown(nChar, nRepCnt, nFlags);
	}
	
}

CFont * CChildTView::SelectFont(CDC *dc, bool SetHeight, CFont &Cfont)
{
	CFont *oldfont;
//	TEXTMETRIC tm;
	LOGFONT font;
	memset(&font,0,sizeof(font));
//	if (SetHeight)
//		font.lfHeight=FontHeight; //rect.Height()/Rows;
//	else
		font.lfHeight=0;	// use default
	font.lfWeight=400;
	font.lfCharSet=DEFAULT_CHARSET;
	font.lfOutPrecision=OUT_DEFAULT_PRECIS;
	font.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	font.lfPitchAndFamily=FIXED_PITCH|FF_SWISS;
	strcpy(font.lfFaceName,"Ariel");
//
	if (!Cfont.CreatePointFontIndirect(&font,dc))
		AfxMessageBox("Could not create font",MB_OK);
//	if (!Cfont.CreateFont(SetHeight?FontHeight:0,0,0,0,600,0,0,0,
//		DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
//		DEFAULT_QUALITY,FIXED_PITCH,"Ariel"))
//		AfxMessageBox("Could not create font",MB_OK);
	oldfont=dc->SelectObject(&Cfont);
	return oldfont;

}

void CChildTView::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd ::OnSetFocus(pOldWnd);
	Invalidate();
}
