// SQLCmd.h : header file
//

#ifndef _CSQLCMD_H
#define _CSQLCMD_H

#include "sqlmother.h"

/////////////////////////////////////////////////////////////////////////////
// CSQLCmd window

class CSQLCmd 
{
// Construction
public:
	void Close();
	MYSQL * GetMySQL();
	void * Connect();
	CSQLCmd(CSQLMother *p);

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CSQLCmd();

private:
	BOOL m_bConnect;
	MYSQL m_mysql;
	CSQLMother *m_pMother;
};

/////////////////////////////////////////////////////////////////////////////
#endif