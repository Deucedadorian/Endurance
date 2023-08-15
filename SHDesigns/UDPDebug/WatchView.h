#if !defined(AFX_WATCHVIEW_H__F9B34D90_F27C_4097_9F26_3546BAA01B35__INCLUDED_)
#define AFX_WATCHVIEW_H__F9B34D90_F27C_4097_9F26_3546BAA01B35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WatchView.h : header file
//
#include <afxcview.h>
#include "Symbols.h"	// Added by ClassView


/////////////////////////////////////////////////////////////////////////////
// CWatchView view
#define ICON_NONE 0
#define ICON_STRUCT 1
#define ICON_INT 2
#define ICON_CHAR 3
#define ICON_LONG 4
#define ICON_STRING 5


class CWatchView : public CTreeView
{
public:
	CWatchView();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	int *STACKSEG;
	int *DATASEG;
	int *SEGSIZE;
	void DeleteWatch();
	CString m_TempFile;
	CString SelWLabel;
	int SelWSize;
	int SelWType;
	SegOff SelWAddr;
	bool UpdateInProgress;
	bool FindItemStruct(CWatchVItem * pItem,int sitem,int &count,SegOff &addr,int &type,int structnum,int &arraysize,CString & label);
	bool FindItem(int item,int sitem,int &type,SegOff &addr,bool isroot,int &arraysize,CString & label);
	int SelWSubItem;
	int SelWItem;
	bool SelIsRoot;
	int AutoTime;
	virtual ~CWatchView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatchView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CImageList NIList;
	CArray<CWatchVItem,CWatchVItem &> WatchList;
	void LoadWatch(bool tmpw);
	void SaveWatch(bool tmpw);
	// Generated message map functions
protected:
	//{{AFX_MSG(CWatchView)
	afx_msg void OnAddWatch();
	afx_msg void OnUpdate();
	afx_msg void OnDeleteWatch();
	afx_msg void OnModify();
	afx_msg void OnAuto();
	afx_msg void OnUpdateAuto(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSaveWatch();
	afx_msg void OnLoadWatch();
	afx_msg void OnEditData();
	afx_msg void OnUpdateEditData(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteWatch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModify(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUpdate(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATCHVIEW_H__F9B34D90_F27C_4097_9F26_3546BAA01B35__INCLUDED_)
