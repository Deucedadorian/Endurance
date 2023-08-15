#include <afxtempl.h>
#if !defined(__Symbols__)
#define __Symbols__

//#include "UDPDebug.h"

#pragma pack(1)
struct err {
unsigned long time; // time error occured
unsigned short p1,p2;
unsigned char p3;
unsigned char type;
};
#pragma pack()

class SegOff
{
public:
	SegOff(): Seg(0),Off(0) {};
	const SegOff& operator -=(int i);
	const SegOff& operator +=(int i);
	const SegOff& operator =(int i);
	bool operator> (const SegOff& s);
	bool operator< (const SegOff& s);
	bool operator>= (const SegOff& s);
	bool operator<= (const SegOff& s);
	bool operator ==(const SegOff& s1);
	bool operator !=(const SegOff& s1);
	unsigned GetLinear() const;
	unsigned Seg,Off;
};

class CSym
{
public:
	bool IsST;
	CString Type;
	SegOff Addr;
	CString Name;
	int Size;
	bool IsBios;
};

class CPopupDlg;
class CSymList
{
public:
	int DATASEG;
	bool m_Updated;
	CArray<CSym,CSym&> Syms;
	CSymList() {};
	void RemoveAll(bool isbios=false);
	bool CompareSym(int index,CSym & Sym);
	void InsertSym(int index,CSym &sym);
	CString & GetSymName(int index);
	SegOff & GetSymAddr(int index);
	int GetNearestIndex(SegOff Addr);
	int GetSize();
	bool EvalSymAdd(SegOff& addr,CString& txt);
	int FindNearest(SegOff addr,CString &txt);
	bool FindAddr(SegOff& addr,CString &name);
	void ReadSymbols(bool OpenLast=false,bool isbios=false,int stack=0,int segsize=0);
};

class SegCPU
{
public:
	CString StructName;
	SegOff Addr;
	bool IsCPUA;
};
#endif


