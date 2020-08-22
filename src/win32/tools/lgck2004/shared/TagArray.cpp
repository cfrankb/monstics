// TagArray.cpp : implementation file
//

#include "stdafx.h"
#include "TagArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZEOF sizeof (CTagEntry)
#define GROWBY 16

/////////////////////////////////////////////////////////////////////////////
// CTagArray

CTagArray::CTagArray()
{
	m_nMax = GROWBY;
	m_nSize =0;
	m_arrEntries = (CTagEntry *) malloc (SIZEOF * m_nMax);
	ZeroMemory (m_arrEntries, SIZEOF * m_nMax);
}

CTagArray::~CTagArray()
{
	Forget();
	free (m_arrEntries);
}


/////////////////////////////////////////////////////////////////////////////
// CTagArray message handlers

int CTagArray::Add (CTagEntry & entry)
{
	memcpy (&m_arrEntries[m_nSize], &entry, SIZEOF);
	m_nSize++;
	if (m_nSize==m_nMax)
	{
		m_nMax = m_nMax + GROWBY;
		CTagEntry *t = (CTagEntry *) malloc (SIZEOF * m_nMax);
		memcpy (t, m_arrEntries, SIZEOF * m_nSize);
		free (m_arrEntries);
		m_arrEntries = t;
	}

	return m_nSize-1;
}

int CTagArray::Add(char *sz, int nVal)
{
	if (sz)
	{
		CTagEntry entry;
		entry.m_nValue = nVal;
		entry.SetName(CString(sz));
		Add(entry);
	}

	return m_nSize-1;
}

int CTagArray::Replace(CTagEntry & entry)
{
	int i = GetIndexFor(entry.m_szName);

	if (i==-1)
	{
		return Add(entry);
	}
	else
	{
		m_arrEntries[i].m_nValue = entry.m_nValue;
		return i;
	}
}

void CTagArray::InsertAt (int n, CTagEntry & entry)
{
	// TODO: Implement the InsertAt
}

void CTagArray::RemoveAt (int n)
{
	if ( n>=0 && n<m_nSize)
	{
		memcpy (&m_arrEntries[n], &m_arrEntries[n+1], 
			(m_nSize-n-1)*SIZEOF);

		m_nSize--; // added 2000/2/6
	}
}

void CTagArray::Forget ()
{
	m_nSize =0;
}

void CTagArray::Serialize (CArchive & ar)
{
	int n;
	if (ar.IsStoring()) // saving
	{
		ar << m_nSize;
		for (n=0; n<m_nSize; n++)
		{
			m_arrEntries[n].Serialize(ar);
		}
	}
	else // loading
	{
		int nSize;
		ar >> nSize;
		Forget();
		for (n=0; n<nSize; n++)
		{
			CTagEntry entry;
			entry.Serialize(ar);
			Add (entry);
		}
	}
}

int CTagArray::GetSize()
{
	return m_nSize;
}

void CTagArray::Read (CFile & file)
{
	// loading
	int nSize;
	Forget();
	file.Read(&nSize,4);
	int n;
	for (n=0; n<nSize; n++)
	{
		CTagEntry entry;
		entry.Read(file);
		Add (entry);	
	}
}


void CTagArray::Write (CFile & file)
{
	// saving
	file.Write (&m_nSize, 4);
	int n;
	for (n=0; n<m_nSize; n++)
	{
		m_arrEntries[n].Write(file);
	}
}

CTagEntry & CTagArray::operator[] (int n)
{
	return m_arrEntries[n];
}

CTagArray & CTagArray::operator = (CTagArray & tag)
{
	OutputDebugString ("CTagArray::operator = in TODO list!\n");
	return * this;
}

int CTagArray::GetIndexFor(char *sz)
{
	BOOL bFound = FALSE;
	int i=0;	

	while (i<m_nSize && !bFound)
	{
		bFound = strcmp(m_arrEntries[i].GetName(), sz)==0;
		if (!bFound)
		{
			i++;			
		}
	}

	if (bFound) return i;
	else return -1;
}


