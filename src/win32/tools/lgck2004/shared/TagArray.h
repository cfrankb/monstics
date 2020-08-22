// TagArray.h : header file
//

#ifndef _TAGARRAY_H
#define _TAGARRAY_H

#include "TagEntry.h"

/////////////////////////////////////////////////////////////////////////////
// CTagArray 

class CTagArray 
{
// Construction
public:
	int Replace(CTagEntry & entry);
	CTagArray();

// Attributes
public:
	int GetSize();

// Operations
public:
	void Forget ();
	void RemoveAt (int n);
	void InsertAt (int n, CTagEntry & entry);
	int Add (CTagEntry & entry);
	int Add(char *sz, int nVal=0);
	CTagArray & operator = (CTagArray & tag);
	CTagEntry & operator[] (int n);

	int GetIndexFor(char *sz);

// Implementation
public:
	~CTagArray();

	void Write (CFile & file);
	void Read (CFile & file);
	void Serialize (CArchive & ar);

protected:	
	CTagEntry * m_arrEntries;
	int m_nMax;
	int m_nSize;
};

/////////////////////////////////////////////////////////////////////////////
#endif