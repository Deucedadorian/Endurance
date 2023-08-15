// UDPDebug.h : main header file for the UDPDEBUG application
//

#if !defined(AFX_UDPDEBUG_H__E30AE3A6_65DE_4808_A7D5_61AE69A934C9__INCLUDED_)
#define AFX_UDPDEBUG_H__E30AE3A6_65DE_4808_A7D5_61AE69A934C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#define UDPDBG_PORT 2200
#include "Symbols.h"
#include "Struct.h"
#include <afxmt.h>


/////////////////////////////////////////////////////////////////////////////
// CUDPDebugApp:
// See UDPDebug.cpp for the implementation of this class
//

#pragma pack(1)
typedef struct {
	char cmd;
	short int	parami;
	long	paraml;
	char data[2];
	} DBG_CMD;

#pragma pack()

class CWatchItem
{
public:
	bool Signed;
	bool Hex;
	CWatchItem() {Signed=true;IsIo=IsEio=false;};
	virtual ~CWatchItem() {};
	CString Name;
	int Size;
	bool IsIo,IsEio;
	enum WTYPE {TYPE_CHAR,TYPE_INT,TYPE_LONG,TYPE_FLOAT,TYPE_STRING,TYPE_STRUCT} Type;
	CString Struct;
};

class CWatchVItem : public CWatchItem
{
public:
	bool Modified;
	HTREEITEM hTree;
	CWatchVItem()
	{
		Modified=true;
		hTree=NULL;
	};
	
	CArray<HTREEITEM,HTREEITEM&> hItems;
	CWatchVItem & operator =(CWatchVItem &item)
	{
		hTree=item.hTree;
		for (int i=0;i<item.hItems.GetSize();i++)
			hItems.Add(item.hItems[i]);
		Hex=item.Hex;
		Name=item.Name;
		Size=item.Size;
		Struct=item.Struct;
		Type=item.Type;
		Modified=item.Modified;
		Signed=item.Signed;
		IsIo=item.IsIo;
		IsEio=item.IsEio;
		return *this;
	}
};

class CStructList;
class CChildView;
class CChildTView;

class CUDPDebugApp : public CWinApp
{
public:
#define DEBUG_ENABLE 0
#define DEBUG_READ 1
#define DEBUG_WRITE 2
#define DEBUG_TEXT 3
#define DEBUG_RFLOAT 4 //not used, uses DEBUG_READ/WRITE
#define DEBUG_EREAD 5
#define DEBUG_EWRITE 6
#define DEBUG_IREAD 7
#define DEBUG_IWRITE 8
#define DEBUG_RESET 9

	CUDPDebugApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPDebugApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CChildTView * m_LogView,*m_DefView;
	HMENU m_hMDIMenu,m_hMDIWMenu,m_hMDITMenu;
	HACCEL m_hMDIAccel;
	CSingleLock * LockSem;
	CChildView * View;
	void InitSock();
	CAsyncSocket ASock;
	bool ASockInit;
	void Lock();
	void Unlock();
	CSemaphore DBGSem;

public:
	void GetSegs();
	int SEGSIZE;
	int STACKSEG;
	int DATASEG;
	void AddLog(CString str);
//	unsigned short CRC1(unsigned char cchar,unsigned short crc);
	unsigned short CRC16(unsigned char * buff,int len,unsigned short crc);
	void MyContextHelp();
	CChildTView * CreateTView(CString &name);
	bool WriteData(void *,int addr,int len,int type=0);
	virtual ~CUDPDebugApp();
	bool ReadData(void *buff, long addr, int size,int type=0);
	int ProcessDBGCmd(DBG_CMD * cmd,int len,int rxlen);
	void RegisterViewHandler(CChildView * view);
	bool PollEnabled;
	void EnablePoll(bool enable);
	int DBGReceive(void * buff,int size,bool lock=true);
	CString m_SockIP;
	bool SendDBG(DBG_CMD * cmd,int size);
	CStructList Structs;
	CSymList Syms;
	//{{AFX_MSG(CUDPDebugApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnNewWView();
	afx_msg void OnReadSym();
	afx_msg void OnReadLastsym();
	afx_msg void OnLoadStruct();
	afx_msg void OnLoadLastStruct();
	afx_msg void OnDump();
	afx_msg void OnShowSym();
	afx_msg void OnReadBiosSym();
	afx_msg void OnReadlastBiosSym();
	afx_msg void OnDefList();
	afx_msg void OnDumpRam();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPDEBUG_H__E30AE3A6_65DE_4808_A7D5_61AE69A934C9__INCLUDED_)
