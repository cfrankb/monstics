// ServerArr.h : header file
//

#ifndef _CSERVERARR_H
#define _CSERVERARR_H

#include "server.h"

/////////////////////////////////////////////////////////////////////////////
// CServerArr window

class CServerArr 
{
// Construction
public:
	void AddDefault();
	CServerArr();

// Attributes
public:
	int GetSize();

// Operations
public:
	void Forget();
	void Init();
	void Serialize(CArchive & ar);
	BOOL RemoveAt(int n);
	BOOL Add(CServer *p);
	CServer * operator[] (int n);

// Implementation
public:
	~CServerArr();

	int m_nDefault;
	CServer *m_pHead;
	CServer *m_pTail;

protected:
	int m_nSize;
};

/////////////////////////////////////////////////////////////////////////////
#endif