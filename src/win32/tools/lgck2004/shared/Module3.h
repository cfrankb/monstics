// Module3.h : header file
//

#ifndef _MODULE3_H
#define _MODULE3_H

#include "tagarray.h"
#include "LgckArr.h"

/////////////////////////////////////////////////////////////////////////////
// CModule3 window

class CModule3 
{
// Construction
public:
	int GetReal32(int n);
	int MiniAsm(char *szSource, char *pDest, int & nValue, int & nValue2);
	void ParseInt(int n, char *pDest, int & nOffset);
	int ComputeEncode(CLgckCmd & cmd, char *pBuf, int nLine);
	int GetHex(char nChar);
	void ParseText(char *szText, char *szDest, int & nOffset);
	void CompileToAsm();
	void Init();
	CModule3();

// Attributes
public:
	CLgckArr & operator[](int n);
	CLgckArr & operator[] (char *sz);

// Operations
public:
	int ProcessText(char *sz);
	int ProcessFile(char *szFile);
	int GetVar(int nVar);
	int GetVar(char *sz);
	BOOL OutputVars(char *szFile);
	void SetVar(char *sz, int nValue);
	void Verbose(CLgckCmd & cmd, int nLine, char *szCmd);
	void Verbose(CLgckArr & arr, CFile & file);
	BOOL Run(int n, BOOL bFresh=TRUE);
	int Run(char *sz);

protected:	
	int FindElse(CLgckArr & arr, int i, int nSize);
	int eval(char *sz);
	char* ProcessString(char *sz, int &nLevel);
	char * CheckCmd(CLgckCmd & cmd);
	int Add(CLgckCmd & cmd);
	void NewArray(char *sz);
	void Clean(char *sz);
	int WhoIs(char *sz);
	void MakeHeader(char *szFile);

// Implementation
public:
	~CModule3();
	void Forget();
	void Read(CFile &file);
	void Write (CFile &file);

protected:
	CTagArray m_arrStrings;
	CTagArray m_arrVars;

	CLgckArr *m_pData;
	int m_nMax;
	int m_nSize;

	CFile m_fileT;
	BOOL m_bFileT;
	
	BOOL m_bRunning;
};

/////////////////////////////////////////////////////////////////////////////

#endif