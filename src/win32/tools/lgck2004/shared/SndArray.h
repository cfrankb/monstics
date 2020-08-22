// SndArray.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSndArray 

#ifndef _SNDARRAY_H
#define _SNDARRAY_H

#include "snd.h"

class CSndArray 
{
// Construction
public:
	CSndArray();

// Attributes
public:
	int GetSize();

// Operations
public:
	BOOL Stop (int n);
	BOOL Stop ();
	void Add (CSnd * pSnd);
	void RemoveAt (int n);
	void Forget();
	CSnd * operator [] (int n);
	CSnd * operator [] (char *szName);

// Implementation
public:
	~CSndArray();

private:
	CSnd ** m_arrSnds;
	int m_nMax;
	int m_nSize;
};

/////////////////////////////////////////////////////////////////////////////

#endif