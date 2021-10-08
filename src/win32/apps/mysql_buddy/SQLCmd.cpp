// SQLCmd.cpp : implementation file
//

#include "stdafx.h"
//#include "mysql_buddy.h"
#include "SQLCmd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Helper functions

static int str2int(char *sz)
{
	int n =0 ;

	while (*sz>='0' && *sz<='9')
	{
		n = n * 10 + *sz-'0';
		sz++;
	}

	return n;
}

/////////////////////////////////////////////////////////////////////////////
// CSQLCmd

CSQLCmd::CSQLCmd(CSQLMother *p)
{
	m_bConnect = FALSE;
	m_pMother = p;

	mysql_init(&m_mysql);
}

CSQLCmd::~CSQLCmd()
{
	Close();
}

/////////////////////////////////////////////////////////////////////////////
// CSQLCmd message handlers

/*
	return mysql_real_connect(
	   &mysql,
	   m_szHost,
	   m_szUser,
	   m_szPassword,
	   0,
	   str2int(m_szPort),
	   NullS,
	   0);
*/

void * CSQLCmd::Connect()
{
	CSQLMother & mother = (* m_pMother);
	CServer & server = (* mother.m_config[mother.m_config.m_nDefault]);
	
	void *p = 
		mysql_real_connect(
			&m_mysql,
			server.m_szHost,
			server.m_szUser,
			server.m_szPassword,
			0,
			str2int(server.m_szPort),
			NullS,
			0);

	m_bConnect = (BOOL) p;
	return p;
}

MYSQL * CSQLCmd::GetMySQL()
{
	return &m_mysql;
}

void CSQLCmd::Close()
{
	if (m_bConnect)
	{
		mysql_close(&m_mysql);	
	}
}
