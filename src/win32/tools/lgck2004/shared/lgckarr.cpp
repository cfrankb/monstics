// lgckarr.cpp : implementation file
//

#include "stdafx.h"
#include "lgckarr.h"
#include "file.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZEOF sizeof(CLgckCmd)
#define PTR CLgckCmd*
#define GROWBY 50

/////////////////////////////////////////////////////////////////////////////
// CLgckArr

CLgckArr::CLgckArr()
{
	Init();
}

CLgckArr::~CLgckArr()
{
	Forget();
}

/////////////////////////////////////////////////////////////////////////////
// CLgckArr message handlers

void CLgckArr::Init()
{
	m_nSize =0;
	m_nMax = GROWBY;
	m_pData	= (PTR) malloc(GROWBY *SIZEOF);
	*m_szName=0;
}

int CLgckArr::GetSize()
{
	return m_nSize;
}

void CLgckArr::Add(CLgckCmd & cmd)
{
	if (m_nSize==m_nMax)
	{
		m_nMax = m_nMax + GROWBY ;
		PTR p = (PTR) malloc(m_nMax*SIZEOF);
		memcpy(p, m_pData, m_nSize*SIZEOF);
		free(m_pData);
		m_pData =p;
	}

	m_pData[m_nSize] = cmd;
	m_nSize++;
}

void CLgckArr::Forget()
{
	if (m_pData)
	{
		free(m_pData);
		m_pData=NULL;
	}
	
	m_nMax=0;
	m_nSize=0;
}

static CLgckCmd g_cmd;
CLgckCmd & CLgckArr::operator[](int n)
{
	if (n<0 || n>=m_nSize)
	{
		return g_cmd;
	}
	else
	{
		return m_pData[n];
	}
}

void CLgckArr::SetName(char *sz)
{
	if (sz)
	{
		strcpy(m_szName, sz);
	}
}

char * CLgckArr::GetName()
{
	return m_szName;
}

void CLgckArr::Write(CFile & file)
{
	file << CString(m_szName);	
	file.Write(&m_nSize,4);

	int i;
	for (i=0; i<m_nSize; i++)
	{
		m_pData[i].Write(file);
	}
}

void CLgckArr::Read(CFile &file)
{
	Forget();
	CString str;
	file >> str;
	strcpy(m_szName, str.GetBuffer(0));
	int nSize;
	file.Write(&nSize,4);

	int i;
	for (i=0; i<nSize; i++)
	{
		CLgckCmd cmd  ;
		cmd.Read(file);
		Add(cmd);
	}

}
