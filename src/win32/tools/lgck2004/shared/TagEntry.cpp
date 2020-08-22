// TagEntry.cpp : implementation file
//

#include "stdafx.h"
#include "TagEntry.h"
#include "file.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTagEntry

CTagEntry::CTagEntry()
{
	m_nValue =0;
	*m_szDescription = 0;
	*m_szName= 0;
}

CTagEntry::CTagEntry (char *sz, int nVal)
{
	strcpy (m_szName, sz);
	strcpy (m_szDescription ,"");
	m_nValue=nVal;
}

CTagEntry::~CTagEntry()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTagEntry message handlers

void CTagEntry::SetName (CString & string)
{
	strcpy ( m_szName, string.GetBuffer(1));
}

void CTagEntry::SetDescription (CString & string)
{
	strcpy ( m_szDescription, string.GetBuffer(1));
}

void CTagEntry::Serialize (CArchive & ar)
{
	if (ar.IsStoring()) // saving
	{
		ar << CString (m_szName);
		ar << CString (m_szDescription);
		ar << m_nValue;
	}
	else // loading
	{
		CString strName;
		CString strDescription;
		ar >> strName;
		ar >> strDescription;
		ar >> m_nValue;

		SetName (strName);
		SetDescription (strDescription);
	}
}

void CTagEntry::Write (CFile & file)
{
	// saving
	file << CString (m_szName);
	file << CString (m_szDescription);
	file.Write(&m_nValue, 4);
}

void CTagEntry::Read (CFile & file)
{
	// loading
	CString strName;
	CString strDescription;

	file >> strName;
	file >> strDescription;

	SetName (strName);
	SetDescription (strDescription);

	file.Read (&m_nValue, 4);
}

char* CTagEntry::GetName()
{
	return m_szName;
}
