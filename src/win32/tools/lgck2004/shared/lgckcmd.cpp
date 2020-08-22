// LGCKCmd.cpp : implementation file
//

#include "stdafx.h"
#include "lgckcmd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLgckCmd

CLgckCmd::CLgckCmd()
{
	Init();
}

CLgckCmd::~CLgckCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
// CLgckCmd message handlers

void CLgckCmd::operator =(CLgckCmd & cmd)
{
	memcpy(this, &cmd, sizeof(CLgckCmd));
}

void CLgckCmd::Write (CFile & file)
{
	file.Write(this, sizeof(CLgckCmd));
}

void CLgckCmd::Init()
{
	m_nArgs =0;
	m_nLevel = 0;
	m_arrArgs[0] = 0;
	m_arrArgs[1] = 0;
	m_arrArgs[2] = 0;
	m_arrArgs[3] = 0;
}

void CLgckCmd::Read(CFile &file)
{
	file.Read(this, sizeof(CLgckCmd));

}
