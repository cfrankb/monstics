// StrValArray.cpp : implementation file
//

#include "stdafx.h"
#include "StrValArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZEOF (sizeof (CStrVal*))
#define GROWBY 16

/////////////////////////////////////////////////////////////////////////////
// CStrValArray

CStrValArray::CStrValArray()
{
	m_nMax = GROWBY;
	m_arrStrVals =(CStrVal**) malloc (SIZEOF * m_nMax);
	m_nSize=0;
}

CStrValArray::~CStrValArray()
{
	Forget();
	free (m_arrStrVals);
}

/////////////////////////////////////////////////////////////////////////////
// CStrValArray message handlers

void CStrValArray::Forget()
{
	while (m_nSize)
	{
		delete m_arrStrVals[0];
		RemoveAt (0);
	}
}

int CStrValArray::Add (CStrVal *pStrVal)
{
	AddBlank();
	int n;
	for (n=0; (n<m_nSize-1) && 
		(pStrVal->m_nVal >= m_arrStrVals[n]->m_nVal); n++);

	int i;
	for (i=m_nSize -1; i > n ; i--)
	{
		m_arrStrVals [i] = m_arrStrVals [i-1];
	}

	m_arrStrVals [n]= pStrVal;

	return n;
}

void CStrValArray::RemoveAt (int n)
{
	int i;
	for (i=n; i< m_nSize-1; i++)
	{	
		m_arrStrVals[i] = m_arrStrVals[i+1];
	}

	m_nSize--;
}

void CStrValArray::InsertAt (CStrVal *pStrVal, int n)
{
	AddBlank();
	int i;
	for (i=m_nSize -1; i > n ; i--)
	{
		m_arrStrVals [i] = m_arrStrVals [i-1];
	}

	m_arrStrVals [n]= pStrVal;

}


void CStrValArray::AddBlank()
{
	m_nSize++;
	if (m_nSize==m_nMax)
	{
		m_nMax = m_nMax + GROWBY;
		CStrVal **t = (CStrVal **) malloc (m_nMax * SIZEOF);
		memcpy (t,m_arrStrVals, m_nSize * SIZEOF);
		delete m_arrStrVals;
		m_arrStrVals = t;	
	}
}

void CStrValArray::Serialize (CArchive & ar)
{
	int n;
	int x;
	
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_nSize;
		for (n=0; n<m_nSize; n++)
		{
			m_arrStrVals[n]->Serialize(ar);
		}
	}
	else
	{
		// LOADING
		Forget();
		CStrVal *pStrVal;
		ar >> x;
		for (n=0; n<x; n++)
		{
			pStrVal = new CStrVal;
			pStrVal->Serialize(ar);
			Add (pStrVal);
		}
	}
}

int CStrValArray::GetSize()
{
	return m_nSize;
}

CStrVal * CStrValArray::operator[] (int n)
{
	return m_arrStrVals[n];
}

CString & CStrValArray::StringFor (int nVal)
{
	BOOL bFound = FALSE;
	static CString str;
	str.Format ("Unknown 0x%x", nVal);
	int n;

	for (n=0; n<m_nSize && bFound==FALSE; n++)
	{
		if (nVal == m_arrStrVals[n]->m_nVal)
			bFound = TRUE;
	}

	if (bFound==TRUE)
		return m_arrStrVals[n-1]->m_strLabel;
	else 
		return str;

}

void CStrValArray::Write (CFile & file, BOOL bHead)
{
	if (bHead)
		file.Write ("CIF3", 4);

	file.Write (&m_nSize, 4);

	int n;
	for (n=0; n<m_nSize; n++)
	{
		m_arrStrVals[n]->Write(file);
	}
}

void CStrValArray::Read (CFile & file, BOOL bHead)
{
	char sz[] = "aaaa";
	int nSize;
	
	if (bHead) {
		file.Read (sz, 4);
		CString str = sz;
		if (str!="CIF3") return;
	}

	file.Read (&nSize, 4);
	
	int n;
	for (n=0; n<nSize; n++)
	{
		CStrVal *pStrVal = new CStrVal;
		pStrVal -> Read (file);
		Add (pStrVal);
	}
}

int CStrValArray::GetIndexFor (int nVal)
{
	int n;
	BOOL bFound = FALSE;

	for (n=0; n<m_nSize && bFound==FALSE; n++)
	{
		if (nVal == m_arrStrVals[n]->m_nVal)
			bFound = TRUE;
	}

	if (bFound==TRUE)
		return n-1;
	else 
		return -1;
}
