#ifndef _OBL3ARRAY_H
#define _OBL3ARRAY_H

#include "obl3filter.h"
#include "scriptentry.h"

// OBL3Array.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COBL3Array 

class COBL3Array 
{
// Construction
public:
	COBL3Array();

// Attributes
public:
	int GetSize();
	int GetFilePathIndex (const CString & str);
	int GetNameIndex (const CString & str);
	int GetIndexFor (char *sz);

// Operations
public:
	void SetAt (int n, COBL3Filter * pFilter);
	CSS3Frame * GetFrame (CScriptEntry &entry);
	CSS3Frame * GetFrame (int y, int x);
	COBL3Filter * operator [] (int n);
	COBL3Filter * operator []( char *sz);
	void Add(COBL3Filter *pFilter);
	void RemoveAt(int n);
	void Forget();
	BOOL PackImages ();

// Implementation
public:
	~COBL3Array();
	void Serialize (CArchive & ar, int nGameDBVer);
	void Read (CFile & file, int nGameDBVer);

private:	
	int m_nMax;
	int m_nSize;
	COBL3Filter ** m_arrFilters;
};

/////////////////////////////////////////////////////////////////////////////

#endif