// Server.cpp : implementation file
//

#include "stdafx.h"
//nclude "mysql_buddy.h"
#include "Server.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServer

CServer::CServer()
{
	Init();
}

CServer::~CServer()
{
	Forget();
}


/////////////////////////////////////////////////////////////////////////////
// CServer message handlers

void CServer::Init()
{
	ZeroMemory(this, sizeof(CServer));
}

void CServer::Forget()
{
	ZeroMemory(this, sizeof(CServer));
}

void CServer::Serialize(CArchive & ar)
{

	char *arrData[]=
	{
		m_szServer,
		m_szHost,
		m_szPort,
		m_szUser,
		NULL
	};

	if (ar.IsLoading()) // loading
	{
		Init();

		for (int i=0; arrData[i]; i++)
		{
			CString str;
			ar >> str ;
			strcpy(arrData[i], str.GetBuffer(1));
		}	

		//		m_szPassword,

		CString str;
		ar >> str ;
		strcpy(m_szPassword, str.GetBuffer(1));

		ar.Read (&m_bSavePassword,4);

	}
	else // saving
	{
		for (int i=0; arrData[i]; i++)
		{
			CString str = arrData[i];
			ar << str ;
		}	

		if (m_bSavePassword)
		{
			ar << CString(m_szPassword);	
		}
		else
		{
			ar << CString("");			
		}

		ar.Write (&m_bSavePassword,4);
	}
}

void CServer::SetDefault()
{
	strcpy(m_szServer,"(default)");
	strcpy(m_szHost, "localhost");
	strcpy(m_szUser, "root");
	strcpy(m_szPassword, "");
	strcpy(m_szPort, "3306");
	m_bSavePassword = FALSE;
}
