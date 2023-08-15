#ifndef __EQPARSE_H
#define __EQPARSE_H
#include "afxtempl.h"

#ifndef DATA_TYPE
#define DATA_TYPE double
#endif

#define EQ_NONE 0
#define EQ_ADD 1
#define EQ_SUB 2
#define EQ_MUL 3
#define EQ_DIV 4
#define EQ_CONST 5
#define EQ_TERM 6

// token values
typedef enum {TTERM,/* end of equation */
	TPARS,		/* open parenthesis '('*/   
	TPARE,		/* close parenthesis ')'*/
	TCONST,		/* constant (immediate) data (0x93nn) */
	TDIV,		/* divide operator */
	TMUL,		/* multiply operator */
	TADD,		/* add operator */
	TSUB,		/* subtract operator */
	TVAR		/* variable */
} TTYPE;

class CStack
{
private:
	CArray<DATA_TYPE,DATA_TYPE &> stack;
public:
	void Empty();
	int GetSize();
	DATA_TYPE Pop();
	void Push(DATA_TYPE val);
};

class CEqParse
{
public:
	virtual bool Eval(CStack &stack) = 0;
	virtual int GetType() {return EQ_NONE;};
};

class CEqAdd : public CEqParse
{
public:
	virtual bool Eval(CStack & stack);
	virtual int GetType() {return EQ_ADD;};
};

class CEqSub : public CEqParse
{
public:
	virtual bool Eval(CStack & stack);
	virtual int GetType() {return EQ_SUB;};
};

class CEqMul : public CEqParse
{
public:
	virtual bool Eval(CStack & stack);
	virtual int GetType() {return EQ_MUL;};
};

class CEqDiv : public CEqParse
{
public:
	virtual bool Eval(CStack & stack);
	virtual int GetType() {return EQ_DIV;};
};

class CEqConst : public CEqParse
{
private:
	DATA_TYPE val;
	int type; // user defined types
public:
	DATA_TYPE GetValue();
	CEqConst() {type=0;}
	virtual bool Eval(CStack & stack);
	virtual int GetType() {return EQ_CONST;}
	void SetValue(DATA_TYPE  nval) {val=nval;}
	void SetUType(int ntype) {type=ntype;}
	int GetUType() { return type;}
};

class CEqTerm : public CEqParse
{
public:
	virtual int GetType() {return EQ_TERM;};
	virtual bool Eval(CStack &stack);
};

class CParse
{
public:
	bool SetVariable(int vtype,DATA_TYPE val);
	bool Evaluate(DATA_TYPE & result);
	CParse();
	virtual ~CParse();
	bool ParseString(CString & str);
protected:
	bool Factor(char **s);
	void AddEq(CEqParse *);
	bool Mult(char **s);
	bool Add(char **s);
	CString GetWord(char ** s);
	bool GetToken(char **s,int * token);
	int CurToken;
	CStack stack;
	DATA_TYPE ConstVal;
	CArray<CEqParse *,CEqParse *&> Equation;
};

#endif