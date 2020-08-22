// ExtraArray.h : header file
//

#ifndef _EXTRAARRAY_H
#define _EXTRAARRAY_H
#include "extradata.h"
#include "file.h"

/////////////////////////////////////////////////////////////////////////////
// CExtraArray 

class CExtraArray 
{
// Construction
public:
	void Read(CFile & file);
	void Write (CFile & file);
	void Serialize(CArchive & ar);
	int GetSize();
	void Forget();
	void Init();
	void RemoveAt(int n);
	void Add(CExtraData & data);
	CExtraData & operator[] (char *szName);
	CExtraData & operator[] (int n);
	CExtraArray();

// Attributes
public:

// Operations
public:

// Implementation
public:
	~CExtraArray();

protected:
	int m_nSize;
	int m_nMax;
	CExtraData *m_pData;
};

/////////////////////////////////////////////////////////////////////////////
#endif