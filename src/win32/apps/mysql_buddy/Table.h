// Table.h : header file
//

#ifndef _TABLE_H
#define _TABLE_H

#include "field.h"
#define MAX_TB_NAME 32
#define MAX_TB_INFO 1024

/////////////////////////////////////////////////////////////////////////////
// CTable window

class CTable 
{
// Construction
public:
	CField * FindField(char *sz);
	void FormatTechDoc(CString & str);
	void GetWndXY(int & nX, int &nY);
	void GetWndSize(int & nLen, int &nHei);
	void SetWndXY(int nX, int nY);
	void SetWndSize(int nLen, int nHei);
	void SetWndTable(void *pWnd);
	void * GetWndTable();
	CTable();

// Attributes
public:
	int GetSize();

// Operations
public:
	void ProcessSQL(CString & strSQL, char *szTable=NULL);
	void Serialize(CArchive & ar, int nVer);
	void Forget();
	void Init();
	CField * operator[] (int n);
	BOOL RemoveAt(int n);
	BOOL Add(CField * p);

// Implementation
public:
	 ~CTable();

	 char m_szName[MAX_TB_NAME];

	 CTable *m_pNext;
	 CField *m_pHead;
	 CField *m_pTail;

     char m_szInfo[MAX_TB_INFO];

protected:
	 int m_nSize;

	 int m_nX;
	 int m_nY;
	 int m_nLen;
	 int m_nHei;

	 void *m_pWnd;
};

/////////////////////////////////////////////////////////////////////////////
#endif