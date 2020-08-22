// StrVal.cpp : implementation file
//

#include "stdafx.h"
#include "StrVal.h"
#include "file.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrVal

CStrVal::CStrVal()
{
	m_strLabel ="";
	m_nVal =0;
	m_bSystem = FALSE;
}

CStrVal::~CStrVal()
{
}

/////////////////////////////////////////////////////////////////////////////
// CStrVal message handlers

CStrVal::CStrVal (int n, const CString &str, BOOL bSystem)
{
	m_nVal = n;
	m_strLabel = str;
	m_bSystem = bSystem;

}

void CStrVal::Serialize (CArchive & ar)
{
	int n=0;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_nVal;
		ar << m_strLabel;
		ar << m_bSystem;
	}
	else
	{
		// LOADING
		ar >> m_nVal;
		ar >> m_strLabel;
		ar >> m_bSystem;
	}
}

void CStrVal::Write (CFile & file)
{
	file.Write (&m_nVal, 4);
	file << m_strLabel;
	file.Write (&m_bSystem, 4);
}


void CStrVal::Read (CFile & file)
{
	file.Read (&m_nVal, sizeof(m_nVal));
	file >> m_strLabel;
	file.Read (&m_bSystem, sizeof(m_bSystem));
}
