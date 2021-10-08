// ServerArr.cpp : implementation file
//

#include "stdafx.h"
#include "ServerArr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerArr

CServerArr::CServerArr()
{
	Init();
}

CServerArr::~CServerArr()
{
	Forget();
}

/////////////////////////////////////////////////////////////////////////////
// CServerArr message handlers

CServer * CServerArr::operator[] (int n)
{
	if (n<0 || n>=m_nSize)
	{
		return NULL;
	}
	else
	{
		if (!m_pHead)
		{
			return NULL;
		}
		else
		{
			CServer *p = m_pHead;
			while (n && p)
			{
				p = p->m_pNext;
				n --;
			}	

			return p;
		}
	}
	return NULL;	
}

BOOL CServerArr::Add(CServer *p)
{
	if (m_pTail)
	{
		m_pTail -> m_pNext = p;
	}

	if (!m_nSize)
	{
		m_pHead = p;
	}

	m_pTail= p;
	p -> m_pNext = NULL;
	m_nSize++;
	
	return TRUE;
}

BOOL CServerArr::RemoveAt(int n)
{
	if (m_pHead && m_pTail && 
		!(n<0) && !(n>=m_nSize))
	{
		if (n==0)
		{
			CServer *p = m_pHead;
			m_pHead = m_pHead->m_pNext;
			m_nSize--;
			p->Forget();
			free(p);

			if (!m_pHead)
			{
				m_pTail = NULL;
			}
		}
		else
		{
			CServerArr & mother = (*this);
			CServer *p = mother[n];
			if (p)
			{
				if (p == m_pTail)
				{
					CServer *pp = mother[n-1];
					m_pTail = pp;		
					pp->m_pNext = NULL;
					p->Forget();
					free(p);
				}
				else
				{
					CServer *pp = mother[n-1];
					pp->m_pNext = mother[n+1];
					p->Forget();
					free(p);
				}
				m_nSize--;
			}
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CServerArr::Serialize(CArchive & ar)
{
	if (ar.IsLoading()) // loading
	{
		Forget();

		int nSize =0;
		ar.Read(&nSize, 4);
		ar.Read(&m_nDefault, 4);
		
		for (int i=0; i<nSize; i++)
		{
			CServer * pServer =	(CServer*) 
				malloc(sizeof(CServer));

			pServer->Serialize(ar);
			Add(pServer);
		}
	}
	else // saving
	{
		ar.Write(&m_nSize, 4);
		ar.Write(&m_nDefault, 4);

		for (int i=0; i<m_nSize; i++)
		{
			CServerArr & arr = (*this);
			arr[i]->Serialize(ar);
		}
	}
}

void CServerArr::Init()
{
#ifdef _DEBUG
	//OutputDebugString("CServerArr::Init()\n");
#endif 

	m_pHead = NULL;
	m_pTail = NULL;
	m_nDefault = -1;
	m_nSize = 0;

	m_nDefault = 0;
}

void CServerArr::Forget()
{
#ifdef _DEBUG
	//OutputDebugString("CServerArr::Forget()\n");
#endif

	CServer * p = m_pHead;

	while (p)
	{
		CServer * pp = p;
		p = p -> m_pNext;
		pp->Forget();
		free(pp);
	}

	m_pHead = NULL;
	m_pTail = NULL;
	m_nDefault = -1;
	m_nSize = 0;
}

int CServerArr::GetSize()
{
	return m_nSize;
}

void CServerArr::AddDefault()
{
#ifdef _DEBUG
	//OutputDebugString("CServerArr::AddDefault()\n");
#endif

	m_nDefault =0;

	CServer *p = (CServer*) malloc(sizeof(CServer));
	p->Init();
	p->SetDefault();
	Add(p);
}
