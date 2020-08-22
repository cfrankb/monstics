// ExtraArray.cpp : implementation file
//

#include "stdafx.h"
#include "ExtraArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GROWBY 10
#define SIZEOF sizeof(CExtraData)
#define PTR CExtraData *

/////////////////////////////////////////////////////////////////////////////
// CExtraArray

CExtraArray::CExtraArray()
{
	OutputDebugString("CExtraArray::CExtraArray()\n");
	Init();
}

CExtraArray::~CExtraArray()
{
	OutputDebugString("CExtraArray::~CExtraArray()\n");
	Forget();
}

/////////////////////////////////////////////////////////////////////////////
// CExtraArray message handlers

void CExtraArray::Init()
{
	OutputDebugString("CExtraArray::Init()\n");
	m_nSize = 0;
	m_nMax = GROWBY;
	m_pData = (PTR) malloc(m_nMax * SIZEOF);
}

void CExtraArray::Forget()
{
	OutputDebugString("CExtraArray::Forget()\n");
	if (m_pData)
	{
		free(m_pData);
		m_pData = NULL;
	}

	m_nSize =0;
	m_nMax=0;
}

static CExtraData g_data;

CExtraData & CExtraArray::operator[] (int n)
{
	if (n<0 || n>=m_nSize)
	{
		OutputDebugString("CExtraData::operator[n] out of bound\n");
		return g_data;
	}
	else
	{
		return m_pData[n];
	}
}

CExtraData & CExtraArray::operator[] (char *szName)
{
	for (int i=0; i<m_nSize; i++)
	{
		if (stricmp(szName, m_pData[i].GetName())==0)
		{
			return m_pData[i];
		}
	}

	OutputDebugString("CExtraData::operator[char *] string not found\n");
	return g_data;	   
}

void CExtraArray::Add(CExtraData & data)
{
	if (m_nSize == m_nMax)
	{
		m_nMax = m_nMax + GROWBY;
		PTR p = (PTR) malloc(m_nMax * SIZEOF);
		memcpy(p, m_pData, m_nSize * SIZEOF);
		free(m_pData);
		m_pData = p;
	}

	m_pData[m_nSize] = data;
	m_nSize++;
}

void CExtraArray::RemoveAt(int n)
{
	if (n<0 || n>=m_nSize)
		return;

	for (int i = n + 1; i<m_nSize; i++)
	{
		m_pData[i-1] = m_pData[i];
	}

	m_nSize--;
}

int CExtraArray::GetSize()
{
	return m_nSize;
}

void CExtraArray::Serialize(CArchive & ar)
{
	if (ar.IsLoading()) // loading
	{
		Forget();
		ar >> m_nSize;
		m_pData = (PTR) malloc(m_nSize*SIZEOF);
		m_nMax = m_nSize;

		for (int i=0; i<m_nSize; i++)
		{
			m_pData[i].Serialize(ar);
		}
	}
	else	// saving
	{
		ar << m_nSize;

		for (int i=0; i<m_nSize; i++)
		{
			m_pData[i].Serialize(ar);
		}
	}
}

void CExtraArray::Write (CFile & file)
{
	file.Write(&m_nSize, 4);
	for (int i=0; i<m_nSize; i++)
	{
		m_pData[i].Write(file);
	}
}

void CExtraArray::Read(CFile & file)
{
	Forget();
	file.Read(&m_nSize, 4);
	m_pData = (PTR) malloc(m_nSize*SIZEOF);
	m_nMax = m_nSize;
	for (int i=0; i<m_nSize; i++)
	{
		m_pData[i].Read(file);
	}
}
