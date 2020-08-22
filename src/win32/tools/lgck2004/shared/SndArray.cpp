// SndArray.cpp : implementation file
//

#include "stdafx.h"
#include "SndArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GROWBY 16
#define SIZEOF (sizeof(CSnd *))

/////////////////////////////////////////////////////////////////////////////
// CSndArray

CSndArray::CSndArray()
{
	m_nMax = GROWBY;
	m_nSize = 0;

	m_arrSnds = (CSnd**) malloc (m_nMax * SIZEOF);
	ZeroMemory(m_arrSnds, m_nMax * SIZEOF);
}

CSndArray::~CSndArray()
{
	Forget();
	free (m_arrSnds);
}

/////////////////////////////////////////////////////////////////////////////
// CSndArray message handlers

int CSndArray::GetSize()
{
	return m_nSize;
}

void CSndArray::Forget()
{
	while (m_nSize)
	{
		if (m_arrSnds[0]!=NULL)
		{
			m_arrSnds[0]->Stop();
			delete m_arrSnds[0];
		}
		RemoveAt (0);
	}
}


void CSndArray::RemoveAt (int n)
{
	int i; 

	for (i=n; i<m_nSize-1; i++)
		m_arrSnds [i] = m_arrSnds[i+1];

	m_nSize--;
	m_arrSnds[m_nSize] = NULL;
}


void CSndArray::Add (CSnd * pSnd)
{
	m_arrSnds [m_nSize] = pSnd;
	m_nSize++;

	if (m_nSize== m_nMax)
	{
		m_nMax = m_nMax + GROWBY;
		CSnd **t = (CSnd**) malloc (m_nMax * SIZEOF);
		ZeroMemory (t, m_nMax *SIZEOF);
		memcpy (t, m_arrSnds, m_nSize* SIZEOF);
		free (m_arrSnds);
		m_arrSnds = t;
	}
}

BOOL CSndArray::Stop ()
{
	int n;
	for (n=0; n< m_nSize; n++)
	{
		if (m_arrSnds[n]!=NULL)
		{
			m_arrSnds[n]->Stop();
		}
	}
	
	return TRUE;

}

CSnd t_Snd;

CSnd * CSndArray::operator [] (int n)
{
	if (n<0 || n>=m_nSize)
	{
		char szTemp[128];
		wsprintf(szTemp, "CSnd: Warning value %c%d%c is out of bound.\n",
			34, n, 34);
		OutputDebugString(szTemp);
		return &t_Snd;
	}
	else
	{
		return m_arrSnds[n];
	}
}

BOOL CSndArray::Stop (int n)
{
	return m_arrSnds[n]->Stop();
}

CSnd * CSndArray::operator [] (char *szName)
{
	if (!szName || !*szName)
	{
		OutputDebugString("CSnd: Warning NAME==NULL\n");
		return &t_Snd;
	}

	int n=0;

	while (n< m_nSize)
	{
		if (!stricmp(szName, m_arrSnds[n]->GetName()))
		{
			return m_arrSnds[n];
		}

		n++;
	}

	char szTemp[128];
	wsprintf(szTemp, "CSnd: Warning no such sound (%c%s%c) in array .\n",
		34, szName, 34);
	OutputDebugString(szTemp);

	return &t_Snd;

}
