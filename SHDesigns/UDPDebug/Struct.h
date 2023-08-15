#if !defined(AFX_STRUCT_H__FB3E9321_6E1F_11D3_9AD1_0080C87E70D1__INCLUDED_)
#define AFX_STRUCT_H__FB3E9321_6E1F_11D3_9AD1_0080C87E70D1__INCLUDED_

#include "Symbols.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Struct.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStruct window
class CEnumList;
class CStruct;
class CStructList;
typedef CArray<CString,CString&> SArray;

class CStructItem
{
public:
	CStructItem();
	CString Name;
	enum {BYTE,INT16,INT32,NEAR_PTR,FAR_PTR,ENUM16,ENUM8,STRUCT,FLOAT} VarType;
	int NumElements;	// number of elements >1=array
	int Offset;			// offset from base of struct
	int Indent;
	enum {CHAR,SIGNED,UNSIGNED,HEX,STRING,BINARY,COMMENT,FUNC,STRUCTV} ViewType;
public:
	int StructNum;
	int Enum;
//	CEnumList * EnumList;
	bool Link;
	SegOff Next;
	int GetItemDataSize();
	CStructItem & operator = (CStructItem & s);
	CString ItemDataToStr(void * buff,unsigned seg,CSymList * Sym,CArray<CEnumList,CEnumList&> &EList);
	int GetStrSize(CArray<CStruct,CStruct&> &SList);
	void ItemToStr(void * buff,unsigned seg,CSymList * Sym,SArray &sarray,CArray<CStruct,CStruct&> &Slist,CArray<CEnumList,CEnumList&> &EList);
	virtual ~CStructItem();

};


class CStruct
{
// Construction
public:
	CStruct();
// Attributes
public:
	enum StructScope {CPU_BOTH,CPU_186,CPU_188} VarScope;
	CString Name;
	CString Alias;
	CArray<CStructItem,CStructItem&> Elements;

// Operations
public:
	int CalcSize(CArray<CStruct,CStruct&> &slist);	// calculate size of all structure elements

// Implementation
public:
	SegOff GetNext();
	SegOff Next;
	int NumLines();
	CStruct & operator =(CStruct &);
	bool DisplayStruct(SArray&Str,void * buff,unsigned seg,CSymList * Sym,CArray<CStruct,CStruct&> &slist,CArray<CEnumList,CEnumList&> &EList);
	virtual ~CStruct();

protected:
};

class CEnumList
{
public:
	CEnumList & operator =(CEnumList &s);
	CString Name;
	SArray EnumList;
	CArray<int,int&> EnumVal;
};

class CDefine
{
public:
	CString Name;
	CString Replace;
};

class CStructList
{
#define SFile FileStack[FileLevel].fp
public:
	bool ByteEnums;
	CArray<bool,bool> ifflags;
	CString LastFile;
	int Warnings;
	CString GetParsedWord();
	int TotalLines;
	CString GetEOL();
	bool GetEq(int &n);
	int DefineNum;
	int StructIndex(CString &name);
	bool ParseStruct(CStruct &cstruct,bool istypedef);
	bool Expect(char * exp,CString & got);
	int LineLength;
	int NumStructs;
	bool IsLoaded();
	void ReadSlist(bool OpenLast=false);
	CStructList();
	CArray<CStruct,CStruct&> SList;
	CArray<CEnumList,CEnumList&> EList;
	CArray<CDefine,CDefine&> DList;
	virtual ~CStructList();
protected:
	bool NoParse;
	struct _FileStack {
		FILE * fp;
		char fname[256];
		int linenum;
		int iflevel;
		} FileStack[10];
	int FileLevel;
	int Column;
	bool GetNum(int & val);
	bool IsEOF;
	int LineNum;
	void UnGetC(char c);
	void SkipWhite();
	char GetChar();
	int LinePtr;
	char LineBuff[256];
	CString GetWord(bool isnum=false,bool en_def=true);
//	FILE * SFile;
	void GetLine();
private:
	CString DefineBuff;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRUCT_H__FB3E9321_6E1F_11D3_9AD1_0080C87E70D1__INCLUDED_)
