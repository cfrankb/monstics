// SortArray.cpp : implementation file
//

#include "stdafx.h"
#include "SortArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GROWBY 16
#define SIZEOF sizeof(CString *)

/////////////////////////////////////////////////////////////////////////////
// CSortArray

CSortArray::CSortArray()
{
	m_nSize=0;
	m_nMax = GROWBY;
	m_arrEntries = (CString**) malloc (SIZEOF * m_nMax);
	ZeroMemory (m_arrEntries, SIZEOF * m_nMax);
}

CSortArray::~CSortArray()
{
	while (m_nSize)
	{
		delete m_arrEntries[0];
		RemoveAt (0);
	}

	free(m_arrEntries);
}


/////////////////////////////////////////////////////////////////////////////
// CSortArray message handlers


CString * CSortArray::operator[] (int n)
{
	return m_arrEntries[n];
}


int CSortArray::Add (const CString & str)
{
	int n=0;
	for (n=0;n<m_nSize && 
		
		str.CompareNoCase(* m_arrEntries[n] ) >=0
			
		; n++);
	return InsertAt (n, str);
}

int CSortArray::InsertAt (int n, const CString & str)
{
	int i;
	for (i=m_nSize; i>n; i--)
	{
		m_arrEntries[i] = m_arrEntries[i-1];	
	}

	m_arrEntries[n] = new CString (str);
	m_nSize++;

	if (m_nSize==m_nMax)
	{
		m_nMax = m_nMax + GROWBY;
		CString ** t = (CString**) malloc (SIZEOF * m_nMax);
		ZeroMemory (t, SIZEOF * m_nMax);	
		memcpy(t, m_arrEntries, SIZEOF * m_nSize);
		free (m_arrEntries);
		m_arrEntries = t;
	}
	return m_nSize;
}

void CSortArray::RemoveAt (int n)
{
	int i;
	for (i=n; i<m_nSize-1; i++)
	{
		m_arrEntries[i] = m_arrEntries[i+1];
	}

	m_arrEntries[m_nSize-1] = NULL;
	m_nSize--;
}

int CSortArray::GetSize()
{
	return m_nSize;
}
