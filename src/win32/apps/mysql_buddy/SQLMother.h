// SQLMother.h : header file
//

#ifndef _SQLMOTHER_H
#define _SQLMOTHER_H

#include "table.h"
#include "server.h"
#include "serverarr.h"

#define DB_MAX_NAME 32

/////////////////////////////////////////////////////////////////////////////
// CSQLMother window

class CSQLMother 
{
// Construction
public:
	static void DeleteWindow(CWnd * pWnd);
	BOOL GetOffset(int &nOX, int &nOY);
	BOOL UpdateVisual();
	void NotifyTables(int nMsg, int n);
	int GetSelTable();
	void SetSelTable(int i);
	void RemoveVisual();
	CSQLMother();

// Attributes
	int GetSize();

// Operations
	BOOL RemoveAt(int n);
	BOOL Add(CTable * p);
	void Serialize(CArchive & ar);
	void Forget();
	void Init();
	CTable * operator[] (int n);
	BOOL CreateVisual();
	void SetMainWnd(CWnd *pWnd);
	void AddDefault();

// Implementation
	~CSQLMother();

	CServerArr m_config;
	char m_szName[DB_MAX_NAME];

protected:
	CTable *m_pHead;
	CTable *m_pTail;
	int m_nSize;
	int m_nSelTable;

	CWnd *m_pWnd;
};

/////////////////////////////////////////////////////////////////////////////
#endif