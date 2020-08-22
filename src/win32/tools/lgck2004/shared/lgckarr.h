// lgckarr.h : header file
//

#ifndef _LGCKARR_H
#define _LGCKARR_H
#include "LgckCmd.h"

/////////////////////////////////////////////////////////////////////////////
// CLgckArr window

class CLgckArr 
{
// Construction
public:
	void Read(CFile &file);
	void Write(CFile & file);
	char * GetName();
	void SetName(char *sz);
	void Init();
	CLgckArr();

// Attributes
public:
	CLgckCmd & operator[](int n);
	int GetSize();

// Operations
public:
	void Add(CLgckCmd & cmd);

// Implementation
public:
	~CLgckArr();
	void Forget();

protected:
	char m_szName[_MAX_PATH];
	int m_nMax;
	int m_nSize;
	CLgckCmd *m_pData;

};

/////////////////////////////////////////////////////////////////////////////

#endif