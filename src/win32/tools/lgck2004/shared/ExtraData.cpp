// ExtraData.cpp : implementation file
//

#include "stdafx.h"
#include "ExtraData.h"
#include "file.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX EXTRADATASIZE

typedef struct 
{
	char m_szName[32];	
	int m_nSize;
	char m_arrData[256];
} OLDEXTRA;

static OLDEXTRA g_old;

/////////////////////////////////////////////////////////////////////////////
// CExtraData

CExtraData::CExtraData()
{
	Init();
}

CExtraData::~CExtraData()
{
	Forget();
}

/////////////////////////////////////////////////////////////////////////////
// CExtraData message handlers

void CExtraData::Serialize(CArchive & ar)
{
	int nSize;
	if (ar.IsLoading()) // loading
	{
		ar.Read(&nSize, 4);

		if (nSize==0x124)
		{
			ar.Read(&g_old, nSize);
			strcpy(m_szName, g_old.m_szName);
			m_nSize = g_old.m_nSize;
			memcpy(m_arrData, g_old.m_arrData, m_nSize);
			m_nMode = 0;
			ZeroMemory(&m_data, sizeof(COREDATA));
		}
		else
		{
			CString str;
			ar >> str;
			strcpy(m_szName, str.GetBuffer(1));
			ar >> m_nSize;
			ar.Read(m_arrData, m_nSize);

			ar >> m_nMode;

			if (m_nMode)
			{
				ar >> nSize;
				ar.Read(&m_data, nSize);
			}
		}

	}
	else // saving
	{
		nSize = sizeof(CExtraData);
		ar.Write(&nSize, 4);
		ar << CString(m_szName);
		ar << m_nSize;
		ar.Write(m_arrData, m_nSize);

		ar << m_nMode;

		if (m_nMode)
		{
			nSize = sizeof(COREDATA);
			ar << nSize;
			ar.Write(&m_data, nSize);
		}
	}
}

void CExtraData::Write(CFile & file)
{
	int nSize = sizeof(CExtraData);

	file.Write(&nSize, 4);
	file << CString(m_szName);
	file << m_nSize;
	file.Write(m_arrData, m_nSize);

	file << m_nMode;

	if (m_nMode)
	{
		nSize = sizeof(COREDATA);
		file << nSize;
		file.Write(&m_data, nSize);
	}
}

void CExtraData::Read(CFile & file)
{
	Init();
	int nSize = sizeof(CExtraData);

	file.Read(&nSize, 4);
	CString str;
	file >> str;
	strcpy(m_szName, str.GetBuffer(1));
	file.Read(&m_nSize,4);
	file.Read(m_arrData, m_nSize);

	file.Read(&m_nMode,4);
	if (m_nMode)
	{
		file.Read(&nSize,4);
		file.Read(&m_data, nSize);
	}
}

/////////////////////////////////////////////////////////////////////////////
//

void CExtraData::Init()
{
	ZeroMemory(this, sizeof(CExtraData));
}

void CExtraData::Forget()
{
	m_szName[0] =0;
	m_nSize=0;
	m_nMode=0;
}

CExtraData & CExtraData::operator= (CExtraData & data)
{
	memcpy(this, &data, sizeof (CExtraData));
	return *this;
}

char * CExtraData::GetName()
{
	return m_szName;
}

int CExtraData::GetSize()
{
	return m_nSize;
}

/////////////////////////////////////////////////////////////////////////////
//

char & CExtraData::operator[](int n)
{
	return m_arrData[n];
}

int CExtraData::Add(char nValue)
{

	if (m_nSize==MAX)
		return -1;

	m_arrData[m_nSize] = nValue;
	m_nSize++;
	return m_nSize;
}

void CExtraData::RemoveAt(int nIndex)
{
	if (nIndex<0 || nIndex>=m_nSize)
	{
		return;
	}

	for (int i = nIndex + 1; i<m_nSize; i++)
	{
		m_arrData[i-1] = m_arrData[i];
	}

	m_nSize--;
}

void CExtraData::InsertAt(int n, char nValue)
{
	if (m_nSize==MAX)
		return;

	for (int i = m_nSize; i>n ; i--)
	{
		m_arrData[i] = m_arrData[i-1];
	}

	m_arrData[n] = nValue;
	m_nSize++;
}
