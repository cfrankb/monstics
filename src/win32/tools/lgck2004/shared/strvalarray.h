#ifndef _STRVALARRAY_H
#define _STRVALARRAY_H

#include "strval.h"

// StrValArray.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CStrValArray 

class CStrValArray 
{
// Construction
public:
	int GetIndexFor (int nVal);
	CStrValArray();

// Attributes
public:
	int GetSize();

// Operations
public:
	int Add (CStrVal *pStrVal);
	void Forget();
	void InsertAt (CStrVal *pStrVal, int n);
	void RemoveAt (int n);
	CStrVal * operator [] (int n);
	CString & StringFor (int nVal);

private:
	void AddBlank();

// Implementation
public:
	~CStrValArray();
	void Serialize (CArchive & ar);
	void Read (CFile & file, BOOL bHead = FALSE);
	void Write (CFile & file, BOOL bHead = FALSE);

private:	
	CStrVal ** m_arrStrVals;
	int m_nMax;
	int m_nSize;
};

/////////////////////////////////////////////////////////////////////////////

#endif