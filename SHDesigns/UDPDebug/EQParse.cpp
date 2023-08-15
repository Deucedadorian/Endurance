#include "EQParse.h"


void CStack::Push(DATA_TYPE val)
{
	stack.InsertAt(0,val);
}

DATA_TYPE CStack::Pop()
{
	DATA_TYPE val=0;
	if (stack.GetSize())
	{
		val=stack.GetAt(0);
		stack.RemoveAt(0);
	}
	return val;
}

bool CEqAdd::Eval(CStack &stack)
{
	DATA_TYPE val=stack.Pop()+stack.Pop();
	stack.Push(val);
	return false;
}

bool CEqSub::Eval(CStack &stack)
{
	DATA_TYPE val,val2=stack.Pop();
	val=stack.Pop()-val2;
	stack.Push(val);
	return false;
}

bool CEqMul::Eval(CStack &stack)
{
	DATA_TYPE val=stack.Pop()*stack.Pop();
	stack.Push(val);
	return false;
}

bool CEqDiv::Eval(CStack &stack)
{
	DATA_TYPE val,val2=stack.Pop();
	val=stack.Pop();
	if (val2!=0) // prevent run-time divide by 0
		val/=val2;
	else
		val=0;
	stack.Push(val);
	return false;
}

bool CEqConst::Eval(CStack &stack)
{
	stack.Push(val);
	return false;
}

bool CParse::ParseString(CString &str)
{
	char * s=(char *)LPCSTR(str);

	if (GetToken(&s,&CurToken))
		if (!Add(&s))
		{
			CEqTerm * term=new CEqTerm;
			AddEq(term);
			return false;
		}
	return true;
}

bool CParse::GetToken(char **s, int *token)
{
	char * sptr=*s;
	while (isspace(*sptr))
		sptr++;
	switch (*sptr)
	{
		case '+':
			*s=++sptr;
			*token=TADD;
			return true;
		case '-':
			*s=++sptr;
			*token=TSUB;
			return true;
		case '/':
			*s=++sptr;
			*token=TDIV;
			return true;
		case '*':
			*s=++sptr;
			*token=TMUL;
			return true;
		case '(':
			*s=++sptr;
			*token=TPARS;
			return true;
		case ')':
			*s=++sptr;
			*token=TPARE;
			return true;
		case ';':
		case '\0':
			*token=TTERM;
			return true;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
			{
				char * e=sptr;
				while (*e=='.'||(*e>='0'&&*e<='9'))
					e++;
				ConstVal=(DATA_TYPE)atof(sptr);
				*s=e;
			}
			*token=TCONST;
			return true;
		case '$':
			*s=++sptr;
			*token=TVAR;
			return true;
	}
	return false;
}

CString CParse::GetWord(char **s)
{
	CString word;
	char * strptr=*s;
	char c;
	c=*strptr++;
	if (c=='\0')
		return(word);
	while (isspace(c))
		c=*strptr++;
	word+=c;
	if (isdigit(c))
    {
		while (isalnum(c)||(c=='.')||(c=='_'))
			word+=c=*strptr++;
		strptr--;        /* put first non alpha back */
	}
	else
	if (isalnum(c))
    {
		while (isalnum(c)||(c=='$'))
			word+=c=*strptr++;
		strptr--;
	}
	*s=strptr;	// return new ptr
  return(word);
}

bool CParse::Add(char **s)
{
	bool retval=false;
	Mult(s);
	while ((CurToken==TADD)||(CurToken==TSUB))
		if (CurToken==TADD)
		{
			retval=GetToken(s,&CurToken);
			if (retval)
				retval=Mult(s);
			CEqAdd * add=new CEqAdd;
			AddEq(add);
		}
		else
		{
			retval=GetToken(s,&CurToken);
			if (retval)
				retval=Mult(s);
			CEqSub * add=new CEqSub;
			AddEq(add);
		}
	return retval;
}

bool CParse::Mult(char **s)
{
	bool retval=false;
	Factor(s);
	while ((CurToken==TMUL)||(CurToken==TDIV))
		if (CurToken==TMUL)
		{
			retval=GetToken(s,&CurToken);
			if (retval)
				retval=Factor(s);
			CEqMul * add=new CEqMul;
			AddEq(add);
		}
		else
		{
			retval=GetToken(s,&CurToken);
			if (retval)
				retval=Factor(s);
			CEqDiv * add=new CEqDiv;
			AddEq(add);
		}
	return retval;
}

void CParse::AddEq(CEqParse * eq)
{
#ifdef _DEBUG
	const char * ttype[]={"NONE","ADD","SUB","MUL",
		"DIV","CONST","TERM"};
	TRACE("Add eq type: %s",ttype[eq->GetType()]);
	if (eq->GetType()==EQ_CONST)
	{
		CEqConst * pconst=(CEqConst *)eq;
		TRACE(" val=%d, type=%d\r\n",pconst->GetValue(),pconst->GetUType());
	}
	else
		TRACE("\r\n");
#endif
		Equation.Add(eq);
}

bool CParse::Factor(char **s)
{
	switch (CurToken) 
	{
	case TVAR:
		{
			CEqConst * pconst=new CEqConst();
			pconst->SetValue(DATA_TYPE(0.0));
			pconst->SetUType(**s);	// put in char as type
			(*s)++;	// next char
			AddEq(pconst);
		}
		return GetToken(s,&CurToken);
	case TCONST:
		{
			CEqConst * pconst=new CEqConst();
			pconst->SetValue(ConstVal);
			AddEq(pconst);
		}
		return GetToken(s,&CurToken);
	case TPARS:
		GetToken(s,&CurToken);	// * assume ok
		if (Add(s))
			return false;			/* evaluate expression in parens */
		if (CurToken!=TPARE)
			return false;
		return GetToken(s,&CurToken);
	case TTERM:
		return true;
		break;
	}
	return false;
}

DATA_TYPE CEqConst::GetValue()
{
	return val;
}

CParse::CParse()
{
}

CParse::~CParse()
{
// free up equation data
	while (Equation.GetSize())
	{
		delete Equation.GetAt(0);
		Equation.RemoveAt(0);
	}
}

bool CParse::Evaluate(DATA_TYPE &result)
{
	bool err=false;
	if (Equation.GetSize()==0)
		return false;
	CEqParse ** parse=Equation.GetData();
	while (!err&&(*parse)->GetType()!=EQ_TERM)
	{
		err|=(*parse)->Eval(stack);
		parse++;
	}
	if (!err)
		result=stack.Pop();
	if (stack.GetSize())
	{
		stack.Empty();
		err=true;
	}
	return err;
}

bool CParse::SetVariable(int vtype, DATA_TYPE val)
{
	int i;
	bool found=false;
	for (i=0;i<Equation.GetSize();i++)
	{
		CEqConst * pconst;
		pconst=(CEqConst *)Equation.GetAt(i); // this may not be valid cast
		if (pconst->GetType()==EQ_CONST&&
			pconst->GetUType()==vtype)
		{
			pconst->SetValue(val);
			found=true;
		}
	}
	return found;
}

int CStack::GetSize()
{
	return stack.GetSize();
}

void CStack::Empty()
{	
	stack.RemoveAll();
}

bool CEqTerm::Eval(CStack &stack)
{
	return true;
}

