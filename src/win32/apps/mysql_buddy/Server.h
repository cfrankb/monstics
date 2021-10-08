// Server.h : header file
//

#ifndef _CSERVER_H
#define _CSERVER_H

#define MAX_NORMAL_STR 128


/////////////////////////////////////////////////////////////////////////////
// CServer window

class CServer 
{
// Construction
public:
	void SetDefault();
	CServer();

// Attributes
public:

// Operations
public:
	void Serialize(CArchive & ar);
	void Forget();
	void Init();

// Implementation
public:
	~CServer();

	char m_szServer[MAX_NORMAL_STR];
	char m_szHost[MAX_NORMAL_STR];
	char m_szUser[MAX_NORMAL_STR];
	char m_szPassword[MAX_NORMAL_STR];
	char m_szPort[MAX_NORMAL_STR];
	BOOL m_bSavePassword;

	CServer *m_pNext;

};

/////////////////////////////////////////////////////////////////////////////
#endif