// Struct.cpp : implementation file
//

#include "stdafx.h"
//#include "vwosdbg.h"
#include "Struct.h"
//#include "global.h"
#include "MainFrm.h"
#include "EqParse.h"
#include "UDPDebug.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStructItem
CStructItem::CStructItem()
{
	NumElements=1;
	Indent=Offset=0;
	Link=false;
}

CStructItem::~CStructItem()
{
}

#define OPENB "{"
#define CLOSEB "}"

/////////////////////////////////////////////////////////////////////////////
// CStruct message handlers
CString CStructItem::ItemDataToStr(void * buff,unsigned seg,CSymList * Sym,CArray<CEnumList,CEnumList&> &EList)
{
	int i,j;
	int sseg=seg&0xff;
	int dseg=(seg>>8)&0xff;
	int dstart=0xf000&(seg>>4);
	int sstart=0xf000&(seg>>8);
	CString Str,Tmp,Fmt;
	if (ViewType==COMMENT)
		return Str; // no data
	switch (VarType)
	{
	case FLOAT:
		{
			float * f=(float *)((char*)buff+Offset);	// generic pointer, to data
			for (j=0;j<NumElements;j++)
			{
				float fval=*f++;	// generic pointer, to data
				Tmp.Format("%f",double(fval));
				if ((NumElements>1)&&(j<NumElements-1))
					Tmp+=',';
				Str+=Tmp;
			}
		}
		return Str;
	case ENUM8:
	case ENUM16:
		{
			char * s=((char*)buff+Offset);	// generic pointer, to data
			for (j=0;j<NumElements;j++)
			{
				CEnumList  * EnumList=&EList[Enum];
				unsigned int val=0;
				val=*s++;	// generic pointer, to data
				if (VarType==ENUM8)
					val&=0xff;
				else
					val|=0xff00&(int(*s++)<<8);
				for (int i=0;i<EnumList->EnumList.GetSize();i++)
				{
					if (unsigned(EnumList->EnumVal.GetAt(i))==val)
					{
						Tmp=EnumList->EnumList.GetAt(i);
						break;
					}
				}
				if (i==EnumList->EnumList.GetSize())
					Tmp.Format("Unknown enum val=%d ",val);
				if ((NumElements>1)&&(j<NumElements-1))
					Tmp+=',';
				Str+=Tmp;
			}
		}
		return Str;
	case BYTE:
		{
		char * s=((char*)buff+Offset);	// generic pointer, to data
		for (i=0;i<NumElements;i++)
		{
			switch (ViewType)
			{
			case CHAR:
/*				Str+='\'';
				if (*s)
					Str+=*s;	// show 'c'
				else
					Str+="\\0";
				Str+='\'';
				Tmp.Format(" = %d",*s++);
				Str+=Tmp;
				break;
*/			case SIGNED:
				Str+='\'';
				if (*s)
					Str+=*s;	// show 'c'
				else
					Str+="\\0";
				Str+='\'';
				Tmp.Format(" = %d",(int)(*s));
				s++;
				Str+=Tmp;
				break;
			case UNSIGNED:
				if (*s)
					Tmp.Format("'%c' = %d",(*s)&0xff,(int)((*s)&0xff));
				else
					Tmp="'\\0' = 0";
				s++;
				Str+=Tmp;
				break;
			case HEX:
				Tmp.Format(" 0x%02X",(int)((*s++)&0xff));
				Str+=Tmp;
				break;
			case STRING:
				if (i==0)
					Str+='"';
				if (*s)
				{
					if (*s=='\r')
						Str+="\\r";
					else
						if (*s=='\n')
							Str+="\\n";
						else
							if (*s=='\t')
								Str+="\\t";
							else
								Str+=*s;
				}
				else
					i=NumElements-1; // terminate loop
				if ((*s++=='\0')||(i==NumElements-1))
					Str+='"';
				break;
			case BINARY:
				Str+=' ';
				int c=(int)*s++;
				for (int b=7;b>=0;b--)
					if (c&(1<<b))
						Str+='1';
					else
						Str+='0';
				break;
			}
		}
		return Str;
		}
	case INT16:
	case FUNC:
	case NEAR_PTR:
		{
		short int * s=(short int *)((char*)buff+Offset);	// generic pointer, to data
		for (i=0;i<NumElements;i++)
		{
			if ((VarType==NEAR_PTR)||(VarType==FUNC))
			{
				int ptr=*s;
				if (ptr<dstart)
					seg=0;
				else
				if (ptr<sstart)
					seg=dseg;
				else
					seg=sseg;
				Tmp.Format(" %04X:%04X",0xffff&seg,0xffff&*s);
				SegOff Addr;
				Addr.Seg=seg;
				Addr.Off=*s++;
				Next=Addr;
				if (Sym!=NULL)
				{	
					Tmp+=" - ";
					Sym->FindNearest(Addr,Fmt);
				}
				Tmp+=Fmt;
				if (ViewType==FUNC)
					Tmp+="()";
				Str+=Tmp;
			}
			else
			switch (ViewType)
			{
			case CHAR:
				Str+='\'';
				if (*s)
					Str+=(char)*s;
				else
					Str+="\\0";
				s++;	// show 'c'
				Str+='\'';
				break;
			case SIGNED:
				Tmp.Format(" %d",(int)(*s++));
				Str+=Tmp;
				break;
			case UNSIGNED:
				Tmp.Format(" %d",(int)((*s++)&0xffff));
				Str+=Tmp;
				break;
			case HEX:
				Tmp.Format(" 0x%04X",(int)((*s++)&0xffff));
				Str+=Tmp;
				break;
			case BINARY:
				Str+=' ';
				int c=(int)*s++;
				for (int b=15;b>=0;b--)
					if (c&(1<<b))
						Str+='1';
					else
						Str+='0';
				break;
			}
		}
		return Str;
		}
	case INT32:
	case FAR_PTR:
		{
		int * s=(int *)((char*)buff+Offset);	// generic pointer, to data
		for (i=0;i<NumElements;i++)
		{
			switch (ViewType)
			{
			case CHAR:
				Str+='\'';
				if (*s)
					Str+=(char)*s;
				else
					Str+="\\0";
				s++;
				Str+='\'';
				break;
			case SIGNED:
				Tmp.Format(" %d",(int)(*s++));
				Str+=Tmp;
				return Str;
			case UNSIGNED:
				Tmp.Format(" %d",(int)(*s++));
				Str+=Tmp;
				break;
			case FUNC:
			case HEX:
				{
					int t=*s++;
					if (VarType==FAR_PTR)
					{
						Tmp.Format(" %08",t);
						SegOff Addr;
						Addr.Seg=(t>>16)&0xffff;
						Addr.Off=t&0xffff;
						Next=Addr;
						if (Sym!=NULL)
						{	
							Tmp+=" - ";
							Sym->FindNearest(Addr,Fmt);
						}
						Tmp+=Fmt;
						if (ViewType==FUNC)
							Tmp+="()";
					}
					else
						Tmp.Format(" %08X",t);
					Str+=Tmp;
				}
				break;
			case BINARY:
				Str+=' ';
				int c=(int)*s++;
				for (int b=31;b>=0;b--)
					if (c&(1<<b))
						Str+='1';
					else
						Str+='0';
				break;
			}
		}
		return Str;
		}
	}
	return Str;	// we should never get here

}

void CStructItem::ItemToStr(void * buff,unsigned seg,CSymList * Sym,SArray &sarray,CArray<CStruct,CStruct&> &SList,CArray<CEnumList,CEnumList&> &EList)
{
	CString Str,tmp;
	for (int i=0;i<Indent;i++)
		Str+=" ";	// indent spaces
	Str+=Name;		// show name
	if (ViewType==STRUCTV)
	{
		// a struct always uses an offset of 0 in its itemlist.
		// so offset into the buffer to this itemlist offset
		char * cptr=(char *)buff;
		cptr+=Offset;
		for (int elnum=0;elnum<NumElements;elnum++)
		{
			Str='+';
			for (int j=0;j<Indent;j++)
				Str+=" ";	// indent spaces
			if (NumElements>1)
				tmp.Format("%s[%d] {",Name,elnum);		// show name
			else
				tmp=Name+" {";		// show name
			Str+=tmp;
			sarray.Add(Str);
			Str.Empty();
			for (int i=0;i<Indent;i++)
				Str+=" ";	// indent spaces
			int first=sarray.GetSize();
			SList[StructNum].DisplayStruct(sarray,cptr,seg,Sym,SList,EList);
			for (;first<sarray.GetSize();first++)
			{
				CString str;
				if (first==sarray.GetSize()-1)
					str='-'+Str+sarray[first]+'}';
				else
					str=Str+sarray[first];
				sarray.SetAt(first,str);
			}
			cptr+=SList[StructNum].CalcSize(SList);
		}
	}
	else
	if (ViewType!=COMMENT)
	{
		Str+='=';
		Str+=ItemDataToStr(buff,seg,Sym,EList);
		sarray.Add(Str);
	}
	return ;
}

int CStructItem::GetStrSize(CArray<CStruct,CStruct&> &SList)
{
	int s=1;
	switch (VarType)
	{
	case BYTE:
	case ENUM8:
		s=1;
		break;
	case INT16:
	case ENUM16:
	case NEAR_PTR:
		s=2;
		break;
	case FLOAT:
	case INT32:
	case FAR_PTR:
		s=4;
		break;
	case STRUCT:
		s=SList[StructNum].CalcSize(SList);
		break;
	}
		return (NumElements*s);
}

/////////////////////////////////////////////////////////////////////////////
// CStruct

CStruct::CStruct()
{
	VarScope=CPU_BOTH;
}

CStruct::~CStruct()
{
}

int CStruct::CalcSize(CArray<CStruct,CStruct&> &slist)
{
	int off=-1,size=0;	// offset
	for (int i=0;i<Elements.GetSize();i++)
		if (Elements[i].Offset>off)
		{
			off=Elements[i].Offset;
			size=off+Elements[i].GetStrSize(slist);
		}
	return size;
}


bool CStruct::DisplayStruct(SArray & Str,void *buff,unsigned seg,CSymList * Sym,CArray<CStruct,CStruct&> &slist,CArray<CEnumList,CEnumList&> &EList)
{
	for (int i=0;i<Elements.GetSize();i++)
	{
		Elements[i].ItemToStr(buff,seg,Sym,Str,slist,EList);	// display items
		if (Elements[i].Link)
			Next=Elements[i].Next;	// next addr
	}
	return true;	// no error defined yet
}

//
// CStructList
// 
CStructList::CStructList()
{
	NumStructs=LineNum=0;
	LinePtr=-1;
	TotalLines=FileLevel=0;
	NoParse=false;
}

CStructList::~CStructList()
{
}

void CStructList::ReadSlist(bool OpenLast)
{
	FileStack[0].iflevel=0;
	Warnings=0;
	ByteEnums=IsEOF=false;
	ifflags.RemoveAll();
	ifflags.Add(true);
	bool istypedef=false;
	NoParse=false;
//	CStruct::StructScope Scope=CStruct::CPU_BOTH;
	LastFile=AfxGetApp()->GetProfileString("Files","Structlist","RabbitStrut.str");
	if (!OpenLast)
	{
		CFileDialog dlg(TRUE,"str",LastFile,OFN_HIDEREADONLY,"Source files (*.c,*.h)|*.c;*.h|Struct files (*.str)|*.str|All Files (*.*)|*.*||");
		// only do dlg if ! openlast
		if (dlg.DoModal()!=IDOK)
			return;
		LastFile=dlg.GetPathName();
	}
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->SetMessageText("Reading Stuctures, Enums and typedefs.");
	SList.SetSize(0);	// clear old structs
	DList.SetSize(0);
	int start_time=GetTickCount();
	LineNum=TotalLines=0;
	CDefine def;
	def.Name="UDP_DEBUG_FLAG";
	def.Replace="1";
	DList.Add(def);
	LineNum=NumStructs=0;		// none defined yet
	IsEOF=false;
	EList.SetSize(0);	// clear old enums
	if ((SFile=fopen(LastFile,"rt"))==NULL)	// open file
	{
		CString Err;
		Err.Format("Could not open file: %s",LastFile);
		AfxMessageBox(Err);
		return;
	}
	strcpy(FileStack[0].fname,LastFile);
	if (!OpenLast)
		AfxGetApp()->WriteProfileString("Files","Structlist",LastFile);
	// beleow was moved out of loops so they are only created once
	CString token,temp,utemp,err;
	while (!IsEOF)
	{
		token=GetParsedWord();
		if (IsEOF)
			break;	// we just got end of file
		if (token=="typedef")
		{
			istypedef=true;
			token=GetWord();
		}
		else
			istypedef=false;
		if (token=="struct")	// this is what we want
		{
			CStruct str;
			if (ParseStruct(str,istypedef))
			{
				SList.Add(str);
				NumStructs++;
				if (istypedef)
				{
					CDefine def;
					def.Name=str.Alias;
					def.Replace.Format("struct %s",str.Name);
					DList.Add(def);
				}
			}
			else
			{
				IsEOF=true;
				break;
			}
		}
		else 
		if (token=="enum")
		{
			CEnumList Enum;
			if (!istypedef)
				Enum.Name=GetWord();	// assign name
			temp=GetWord();
			if (temp !="{")
				if (Expect("{",temp))
				{
					IsEOF=true;
					break;
				}
			token=GetWord();
			int val=0;
			while ((token!="}")&&!IsEOF)
			{
				Enum.EnumList.Add(token);	// add name
				token=GetWord();	// GET NEXT
				if (token=="=")
				{
					GetEq(val);
					token=GetWord();	// get ',' or '}'
				}
				Enum.EnumVal.Add(val);
				val++;
				if (token==",")	// another entry?
					token=GetWord();
			}
			if (istypedef)
			{
				Enum.Name=GetWord();	// assign name
				CDefine def;
				def.Name=Enum.Name;
				def.Replace="enum ";
				def.Replace+=Enum.Name;
				DList.Add(def);
			}
			token=GetWord();
			EList.Add(Enum);
			if (token !=";")
				if (Expect(";",token))
				{
					IsEOF=true;
					break;
				}
		}
		else
		if (istypedef)
		{
			// this is typedef for non struct
			CDefine def;
			def.Replace=token;
			token="";
			while (token!=";")
			{
				temp=token;
				token=GetWord();
				if (temp.GetLength()&&token!=';')
				{
					def.Replace+=' ';
					def.Replace+=temp;
				}
			}
			def.Name=temp;
			DList.Add(def);
		}
		else
		if (token==OPENB)
		{
			int bcount=1;
			while (!IsEOF&&bcount)
			{
				int c=GetChar();
				if (c=='{')
					bcount++;
				else
					if (c=='}')
						bcount--;
			}
		}
	}

	fclose(SFile);

	TotalLines+=LineNum;
	double rtime=double(GetTickCount()-start_time)/1000.0+.0005; // round up and prevent divide by 0
	token.Format("Processed %d source lines in %f seconds, %f lines/sec.",TotalLines,
		rtime,double(TotalLines)/rtime);
	((CUDPDebugApp *)AfxGetApp())->AddLog(token);
	token.Format("%d Structs, %d enums, %d typedefs/defines loaded",
		SList.GetSize(),EList.GetSize(),DList.GetSize());
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->SetStatusPane(token);
	temp.Format("#If level at end: %d, File Level: %d",FileStack[FileLevel].iflevel,FileLevel);
	((CUDPDebugApp *)AfxGetApp())->AddLog(temp);
	temp.Format("%s, %d Warnings.",token,Warnings);
	((CUDPDebugApp *)AfxGetApp())->AddLog(temp);
}

CString CStructList::GetWord(bool getnum/*=false*/,bool ena_def/*=true*/)
{
	CString word;
	static CString eqchars("()+-/*");
	char buff[40],*pbuff=buff;	// use mem buff to speed up
	SkipWhite();
	char c=GetChar();	// get first char;
	if ((eqchars.Find(c)==-1)&&(isalpha(c)||(c=='_')||getnum))
	{
		*pbuff++=c;
		c=GetChar();
		while (isalnum(c)||(c=='_')||(c=='.'))
		{
			*pbuff++=c;
			c=GetChar();
		}
		UnGetC(c);	// return first non-word
		*pbuff='\0';
		word=buff;
	}
	else
		word=c;	// this is not a word so return c
	if (c==-1)
		IsEOF=true;
	if (ena_def)
	for (int i=0;i<DList.GetSize();i++)
		if ((i!=DefineNum)&&(word==DList[i].Name))
		{
			DefineBuff=DList[i].Replace+CString(' ')+DefineBuff;
			DefineNum=i;
			return GetWord(getnum);
		}
//	TRACE("GetWord()=%s\r\n",word);
	return word;
}

char CStructList::GetChar()
{
	if (DefineBuff.GetLength())
	{
		char c=DefineBuff[0];
		CString dstr=DefineBuff.Right(DefineBuff.GetLength()-1);
		DefineBuff=dstr;
		return c;
	}
	else
		DefineNum=-1;
	// read ne line if necessary
	if ((LinePtr==-1)||(LinePtr>=LineLength))
		GetLine();
	while ((LineBuff[LinePtr]=='/')&&(LineBuff[LinePtr+1]=='/'))
	{
		GetLine();	// skip rest of line;
		return '\n';
	}
	if ((LineBuff[LinePtr]=='/')&&(LineBuff[LinePtr+1]=='*'))
	{	LinePtr+=2;	// skip /*
		while ((LineBuff[LinePtr]!='*')||(LineBuff[LinePtr+1]!='/'))
		{
			if (LineBuff[LinePtr]=='\n')
				GetLine();
			else
				LinePtr++;	// next char
			if (IsEOF) // bad file no */.
				return -1;
		}
		LinePtr+=2;	// skip */.
	}
//	if (LineBuff[LinePtr]=='\n')
//	return '\n'; // don't go past \n
	if (LineBuff[LinePtr]=='\t')	//tab
		Column=Column-(Column%4)+4;
	else
		Column++;
	return (LineBuff[LinePtr++]);	// get char, point to next
}

void CStructList::GetLine()
{
	LineLength=Column=LinePtr=0;
	LinePtr=0;	// start of line
		
	char * s=fgets(LineBuff,255,SFile);
	if (s==NULL||NoParse)
	{
		if (FileLevel>0)
		{
			TotalLines+=LineNum;
			fclose(SFile);
			FileLevel--;
//			while (ifflags.GetSize()>FileStack[FileLevel].iflevel-1)
//				ifflags.RemoveAt(ifflags.GetSize()-1);
			s=fgets(LineBuff,255,SFile);
			LineNum=FileStack[FileLevel].linenum;
			NoParse=false;
		}
		if (FileLevel==0&&NoParse)
			s=NULL;
		if (s==NULL)
		{
			LineBuff[0]=-1;
			LineBuff[1]='\0';
			IsEOF=true;
			LineLength=0;
			return;
		}
	}
	LineLength=strlen(LineBuff);
	LineNum++;
}

void CStructList::SkipWhite()
{
	char c=' ';
	while (isspace(c))
		c=GetChar();
	UnGetC(c);
}

void CStructList::UnGetC(char c)
{
	if (DefineBuff.GetLength())
	{
		DefineBuff=c+DefineBuff;
		return;
	}
	if (LinePtr>0)
		LineBuff[--LinePtr]=c;
	else
	{
		memmove(LineBuff+1,LineBuff,255);
		LineBuff[0]=c;
		LineLength++;
		Column=1;	// will get decremented below
	}
	Column--;
}

bool CStructList::GetNum(int & val)
{
	CString word;
	int hex=0;
	//char c;
	CString tword=GetWord(true);	// get first char;
	if (tword[0]=='$')
	{	hex=1;
		tword=GetWord(true);
	}
	if (isxdigit(tword[0]))
	{
		int index=1;
		word=tword[0];
		if (tword.GetLength()>1)
		{	
			if (toupper(tword[index])=='X') //this is 0x...
			{
				hex=1;
				index++;	// skip x
			}
			while (index<tword.GetLength()&&isxdigit(tword[index])) //dec or
			{
				word+=tword[index];
				index++;
			}
		}
		if (hex)
			return (sscanf(word,"%x",&val)==1);
		else
			return (sscanf(word,"%d",&val)==1);
	}
	return false; // this is not a word so return err
}

CStruct & CStruct::operator =(CStruct &s)
{	
	Elements.RemoveAll();
	for (int i=0;i<s.Elements.GetSize();i++)
		Elements.Add(s.Elements.GetAt(i));
	Name=s.Name;
	Next=s.Next;
	Alias=s.Alias;
	VarScope=s.VarScope;
	return *this;
}

CStructItem & CStructItem::operator =(CStructItem & s)
{
	Indent=s.Indent;
	Name=s.Name;
	NumElements=s.NumElements;
	Offset=s.Offset;
	VarType=s.VarType;
	ViewType=s.ViewType;
	Link=s.Link;
	Enum=s.Enum;
	Next=s.Next;
	StructNum=s.StructNum;
	return *this;
}

bool CStructList::IsLoaded()
{
	return (NumStructs!=0);
}

int CStruct::NumLines()
{
	return Elements.GetSize();
}

int CStructItem::GetItemDataSize()
{
	switch (VarType)
	{
	case CHAR:
		return 1;
	case INT16:
	case NEAR_PTR:
		return 2;
	case INT32:
	case FAR_PTR:
	case FLOAT:
		return 4;
	};
	return 1;
}

SegOff CStruct::GetNext()
{
	return Next;
}

CEnumList & CEnumList::operator =(CEnumList & s)
{
	int val;
	for (int i=0;i<s.EnumList.GetSize();i++)
	{	EnumList.Add(s.EnumList.GetAt(i));
		val=s.EnumVal.GetAt(i);
		EnumVal.Add(val);
	}
	Name=s.Name;
	return *this;
}

bool CStructList::Expect(char * exp, CString & got)
{
	CString err,tmp;
	tmp.Format("In file: %s",FileStack[FileLevel].fname);
	((CUDPDebugApp *)AfxGetApp())->AddLog(tmp);
	err=tmp;
	err+="\r\n";
	tmp.Format("Line=%d, Expected '%s', found %s",LineNum,exp,got);
	((CUDPDebugApp *)AfxGetApp())->AddLog(tmp);
	err+=tmp;
	err+="\r\nContinue reading file?";
	if (AfxMessageBox(err,MB_OKCANCEL)==IDCANCEL)
		return true;
	return false;
}

// these defines are for the IDE. includeing braces screws up brace logic in editor

bool CStructList::ParseStruct(CStruct &str,bool istypedef)
{
	CString lasttype,token,temp,err;
	int structnum=-1;
	int sametype=0,offset=0;
	int n,sign=1,size=2;	// normally signed, 16 bit
	token=GetParsedWord();
	if (!istypedef)
	{
		str.Name=token;
		token=GetParsedWord();
	}
	else
	{
		if (token!=OPENB)
		{
			str.Alias=str.Name=token;
			token=GetParsedWord();	// struct "name"
		}
	}
//	str.VarScope=Scope;	// sau who has this
	if (token!=OPENB)
	{
		if (Expect(OPENB,token))
			return false;
	}
	while ((token!=CLOSEB)&&!IsEOF)
	{
		CStructItem Item;
		Item.Offset=offset;
		if (!sametype)	//  ,item then dont read type
		{
			token=GetParsedWord();
			sametype=Column-token.GetLength();
			Item.ViewType=CStructItem::SIGNED;	// default
		}
		else
			token=lasttype;
		Item.Indent=sametype;	// has indent if same
#if 0
		if (token=="#")	// comment
		{
			Item.Name=token;
			int c=GetChar();
			while ((c!='\n')&&!IsEOF)
			{
				Item.Name+=(char)c;
				c=GetChar();
			}
			Item.ViewType=CStructItem::COMMENT;
			sametype=0;
		}
		else
#endif
		{
			sign=1;
			bool IsType=true;
			while (IsType)
			{
				if (token==CLOSEB)
					break;
				if (token=="unsigned")
				{
					size=2;	// default to 16-bit
					Item.ViewType=CStructItem::UNSIGNED;	// default
					sign=0;
					token=GetParsedWord();
				}
				else if (token=="short")
				{
					size=2;
					token=GetParsedWord();
				}
				else if (token=="long")
				{
					size=4;
					token=GetParsedWord();
				}
				else
					IsType=false;

			}
			// if no int or char then assume int, float will override later
			if ((token!="char")&&(token!="int"))
				Item.VarType=size==2?CStructItem::INT16:CStructItem::INT32;
			if (token==CLOSEB)
				break;
			
			// token should be type, unless "unsigned varname"
			if ((token=="enum")||(token=="enum8"))
			{
				temp=GetParsedWord();
				for (int i=0;i<EList.GetSize();i++)
					if (EList[i].Name==temp)
					{
						Item.Enum=i;
						break;
					}
				if (i==EList.GetSize())
				{
					err.Format("Could not find enum definition\n%s, at line %d",temp,LineNum);
					if (AfxMessageBox(err,MB_OKCANCEL)==IDCANCEL)
					{
						return false;
					}
				}
				temp=GetParsedWord();
				if (token=="enum"&&!ByteEnums)
				{
					Item.VarType=CStructItem::ENUM16;
					size=2;
				}
				else
				{
					Item.VarType=CStructItem::ENUM8;
					size=1;
				}
			}
			else
			if (token=="char")
			{
				temp=GetParsedWord();
				if (temp=="(") // must be (*func)
					goto func_ptr;
				size=1;
				Item.VarType=CStructItem::BYTE;
			}
			else if (token=="int")
			{
				temp=GetParsedWord();
				if (temp=="(") // must be (*func)
					goto func_ptr;
					if (size==2)
						Item.VarType=CStructItem::INT16;
					else
						if (size==4)
							Item.VarType=CStructItem::INT32;
			}
			else if (token=="float")
			{
				temp=GetParsedWord();
				if (temp=="(") // must be (*func)
				{
func_ptr:
					temp=GetParsedWord();
					if (temp!="*")
						if (Expect("*",temp))
						{
							return false;
						}
					temp=GetParsedWord();
					Item.VarType=CStructItem::NEAR_PTR;
					size=2;
					Item.ViewType=CStructItem::FUNC;
					GetParsedWord();	// suck up ")"
					if (GetParsedWord()!="(")
						if (Expect("*",temp))
						{
							return false;
						}
					while (GetParsedWord()!=")")
						if (IsEOF)
							return false;
				}
				else
				{
					size=4;
					Item.VarType=CStructItem::FLOAT;
				}
			}
			else
			if (token=="struct")
				temp=GetParsedWord();
			else
			{
				temp=token;	// must be "unsigned varname" (no int)
				token="int";
			}
			if (temp==("near *")||(temp=="near")||(temp=="_near")||(temp=="*"))
			{	
				size=2;
				if ((temp!="near *")&&(temp!="*"))
				{
					temp=GetParsedWord();
				
					if (temp!="*")
						if (Expect("*",temp))
						{
							return false;
						}
				}
				Item.VarType=CStructItem::NEAR_PTR;
				Item.ViewType=CStructItem::HEX;
				temp=GetParsedWord();	// get name
				token="near *"; // save type for x,y;
//				offset+=size;
			}
			else if ((temp=="far *")||(temp=="far")||(temp=="_far"))
			{	
				size=4;
				if (temp!="far *")
				{
					temp=GetParsedWord();
					if (temp!="*")
						if (Expect("*",temp))
						{
							return false;
						}
				}
				//	Item.Name=GetParsedWord(); // get name
				Item.VarType=CStructItem::FAR_PTR;
				Item.ViewType=CStructItem::HEX;
				temp=GetParsedWord();  // get name
				token="far *"; // save type for x,y
//				offset+=size;
			}
			if (token=="struct")
			{
				if (structnum>=0)
					Item.StructNum=structnum;
				else
				{
					structnum=Item.StructNum=StructIndex(temp);
				
					if (Item.StructNum<0)
					{
						Expect("Defined structure",temp);
						return false;
					}
					temp=GetParsedWord();
				}
				size=SList[structnum].CalcSize(SList);
				Item.VarType=CStructItem::STRUCT;
				Item.ViewType=CStructItem::STRUCTV;
			}
			Item.Name=temp;	// this should be name
			lasttype=token;	// save for type x,y,z....
			temp=GetParsedWord();	// get '[', view or ';'
			n=1;
			if (temp=="[")
			{
				if (!GetEq(n))
				{
					if (Expect("Equation or constant",CString("Error parsing equation")))
						return false;
				}
				temp=GetParsedWord();
				if (temp!="]"&&Expect("]",temp))
						return false;

				temp=GetParsedWord();	// get view or ';'
			}
			Item.NumElements=n;
			if ((n>1)&&(Item.VarType==CStructItem::BYTE))
					Item.ViewType=CStructItem::STRING;

			offset+=size*n;

			CString utemp=GetEOL();
			if (utemp.Find("HEX")>=0)
				Item.ViewType=CStructItem::HEX;
			else
			if (utemp.Find("BINARY")>=0)
				Item.ViewType=CStructItem::BINARY;
			else
			if (utemp.Find("CHAR")>=0)
				Item.ViewType=CStructItem::CHAR;
			else if (utemp.Find("NEXT")>=0||utemp.Find("LINK")>0)
				Item.Link=true;
			else if (utemp.Find("FUNC")>=0)
				Item.ViewType=CStructItem::FUNC;

			if (temp!=",")
			{
				size=2;	// if unspecified then it is int
				if (temp!=';')
					if (Expect(";",temp))
					{
						return false;
					}
					sametype=0;
					structnum=-1;
			}
			if (ifflags[FileStack[FileLevel].iflevel])
				str.Elements.Add(Item);
		}
	}
	if (istypedef)
		str.Alias=GetParsedWord();
	if (str.Name.GetLength()==0)
		str.Name=str.Alias;
	if (token!=';')
		token=GetParsedWord();	// struct variable "name"
	if (token!=';')
		if (Expect(";",token))
		{
			return false;
		}

	return true;
}

int CStructList::StructIndex(CString &name)
{
	for (int i=0;i<SList.GetSize();i++)
		if ((SList[i].Name==name)||(SList[i].Alias==name))
			return (i);
	return -1;
}	

bool CStructList::GetEq(int &n)
{
	CString eq,temp;
	int lnum=LineNum;
	while (temp!="]"&&temp!=";"&&lnum==LineNum)
	{
		temp=GetWord(true);
		if (temp!="]"&&temp!=";")
		{
			eq+=temp;
			eq+=' ';
		}
	}
	eq+=';';
	CParse parser;
	if (parser.ParseString(eq))
	{
		TRACE("Parser error: %s\r\n",eq);
	}
	else
		parser.Evaluate(n);
	for (int i=temp.GetLength()-1;i>=0;i--)
			UnGetC(temp[i]);
	return true;
}

CString CStructList::GetEOL()
{
	CString s;
	s=LineBuff+LinePtr;
	return s;
}

//
// get text following #ifdef's
//
CString CStructList::GetParsedWord()
{
	int i;
	CString temp,utemp,err,token=GetWord();
	while (token=="#")
	{
		token=GetWord();
		if (token=="include")
		{
			CString incfile;
			SkipWhite();
			int c=GetChar();
			if (c=='<')
			{	
				incfile+=(char)c;
				while (c!='>'&&!IsEOF)
				{
					c=GetChar();
					incfile+=(char)c;
				}
				err.Format("#include %s - ignored.",incfile);
				((CUDPDebugApp *)AfxGetApp())->AddLog(err);
				Warnings++;
			}
			else
			{
				if (c!='\"'&&Expect("\"",CString(c)))
				{
					IsEOF=true;
					break;
				}
				i=LastFile.ReverseFind('\\');
				if (i==-1)
					incfile.Empty();
				else
					incfile=LastFile.Left(i+1);
				c=GetChar();
				utemp.Empty();
				while (c!='"')
				{
					utemp+=(char)c;
					c=GetChar();
				}
				if (ifflags[FileStack[FileLevel].iflevel])
				{
					incfile+=utemp;
					FILE * ifp=fopen(incfile,"rt");
					if (ifp!=NULL)
					{
						int lvl=FileStack[FileLevel].iflevel;
						FileStack[FileLevel].linenum=LineNum;
						FileLevel++;
						SFile=ifp;
						FileStack[FileLevel].iflevel=lvl;
						strcpy(FileStack[FileLevel].fname,incfile);
						FileStack[FileLevel].linenum=LineNum=0;
					}
					else
					{
						err.Format("#include \"%s\" - File not found.",utemp);
						((CUDPDebugApp *)AfxGetApp())->AddLog(err);
						Warnings++;
					}
				}
			}
		}
		else
		if (token=="define")
		{
			CDefine def;
			def.Name=GetWord();
			if (def.Name=="NO_DEBUG_PARSE")
			{
				NoParse=true;
			}
			else
			if (def.Name=="BYTE_ENUMS")
			{
				ByteEnums=true;
			}
			else
			{
				char c;
				c=GetChar();
				while (isspace(c)&&c!='\n')
					c=GetChar();
				if (c!='\n')
				{
					def.Replace.Empty();
						while (c!='\n')
						{
							def.Replace+=c;
							c=GetChar();
						}
						if (ifflags[FileStack[FileLevel].iflevel])
							DList.Add(def);
				}
				else
				if (ifflags[FileStack[FileLevel].iflevel])
					DList.Add(def);	// enpty replace
			}
		}
		else
		if ((token=="ifdef")||(token=="ifndef"))
		{
			temp=GetWord(true,false); // may be a # and don't expand defines
			bool defined=false;
			for (i=0;i<DList.GetSize();i++)
				if (DList[i].Name==temp)
				{	
					defined=true;
					break;
				}
			if (token=="ifndef")
				defined=!defined;
			FileStack[FileLevel].iflevel=ifflags.Add(defined);
		}
		else
		if (token=="if")
		{
			GetEq(i);
			FileStack[FileLevel].iflevel=ifflags.Add(i!=0);
		}
		else
		if (token=="else")
			ifflags[FileStack[FileLevel].iflevel]=!ifflags[FileStack[FileLevel].iflevel];
		else
		if (token=="endif")
		{
			ifflags.RemoveAt(FileStack[FileLevel].iflevel--);
			if (FileStack[FileLevel].iflevel<0)
			{
				temp.Format("#endif at line %d without matching #if",LineNum);
				if (AfxMessageBox(temp)==IDCANCEL)
				{
					fclose(SFile);
					IsEOF=true;
					break;
				}
				FileStack[FileLevel].iflevel=0;
			}
		}
		else
		// must be #pragma
		{
			int c=GetChar();
			while (c!='\n')
				c=GetChar();
		}
		if (!ifflags[FileStack[FileLevel].iflevel])//||NoParse)
		{
			token=GetWord();
			while (token!="#"&&!IsEOF)
				token=GetWord();
		}
		else
			token=GetWord();
	}
	return token;
}
