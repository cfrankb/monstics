// SQLMother.cpp : implementation file
//

#include "stdafx.h"
#include "SQLMother.h"
#include "WndTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define VERSION 0x0003

/////////////////////////////////////////////////////////////////////////////
// CSQLMother

CSQLMother::CSQLMother()
{
	Init();
}

CSQLMother::~CSQLMother()
{
	Forget();
}

/////////////////////////////////////////////////////////////////////////////
// CSQLMother 

CTable * CSQLMother::operator[] (int n)
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
			CTable *p = m_pHead;
			while (n && p)
			{
				p = p->m_pNext;
				n --;
			}	

			return p;
		}
	}
}

void CSQLMother::Init()
{
	//OutputDebugString("CSQLMother::Init()\n");
	m_pHead =NULL ;
	m_pTail = NULL;
	m_nSize=0;
	m_config.Init();
	m_nSelTable = -1;
    m_szName[0]=0;

	m_pWnd = NULL;
}

void CSQLMother::Forget()
{
	//OutputDebugString("CSQLMother::Forget()\n");
	CTable * p = m_pHead;

	while (p)
	{
		CTable * pp = p;
		p = p -> m_pNext;
		pp->Forget();
		free(pp);
	}

	m_pHead =NULL;
	m_pTail = NULL;
	m_nSize=0;
	m_config.Forget();
}

void CSQLMother::Serialize(CArchive & ar)
{
	char szTemp[]="****";
	int nVer = VERSION;
	
	if (ar.IsLoading()) // loading
	{
		Forget();
		int nSize=0;
		ar.Read(szTemp,4);
		ar.Read(&nVer,4);
		ar.Read(&nSize,4);
		ar.Read(m_szName, MAX_TB_NAME);

        if (m_szName[0]==-51)
        {
            m_szName[0]=0;
        }

		CTable *p = NULL;
		m_pHead = NULL;

		for (int i=0; i<nSize; i++)
		{
			p = (CTable*)malloc(sizeof(CTable));
			p->Init();
			p->Serialize(ar, nVer);
			Add(p);
		}

		switch(nVer)
		{
			case 0:
				m_config.AddDefault();
			break;

			case 1:
			case 2:
            case 3:
				m_config.Serialize(ar);
			break;
		}
	}
	else // saving
	{
		ar.Write("MSBD",4);
		ar.Write(&nVer,4);
		ar.Write(&m_nSize, 4);
		ar.Write(m_szName, DB_MAX_NAME);

		CSQLMother & mother = (*this);

		for (int i=0; i<m_nSize; i++)
		{
			CTable *p = mother[i];
			if (p)
			{
				p->Serialize(ar, nVer);
			}
		}

		m_config.Serialize(ar);
	}
}

BOOL CSQLMother::Add(CTable * p)
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

int CSQLMother::GetSize()
{
	return m_nSize;
}

BOOL CSQLMother::RemoveAt(int n)
{
	if (m_pHead && m_pTail && 
		!(n<0) && !(n>=m_nSize))
	{
		if (n==0)
		{
			CTable *p = m_pHead;
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
			CSQLMother & mother = (*this);
			CTable *p = mother[n];
			if (p)
			{
				if (p == m_pTail)
				{
					CTable *pp = mother[n-1];
					m_pTail = pp;		
					pp->m_pNext = NULL;
					p->Forget();
					free(p);
				}
				else
				{
					CTable *pp = mother[n-1];
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

void CSQLMother::AddDefault()
{
	m_config.AddDefault();
}

void CSQLMother::SetMainWnd(CWnd *pWnd)
{
	m_pWnd = pWnd;
}

BOOL CSQLMother::CreateVisual()
{
	if (!m_pWnd)
	{
		return FALSE;
	}

	HWND hWnd = m_pWnd->m_hWnd; 

	CSQLMother & mother = (*this);

	for (int i=0; i<m_nSize; i++)
	{
		CWndTable * pWnd = new CWndTable(this);

		int nX, nY, nLen, nHei;
		int nOX, nOY;

		GetOffset(nOX, nOY);

		mother[i]->GetWndXY(nX, nY);
		mother[i]->GetWndSize(nLen, nHei);

		if (pWnd->CreateEx(
			 WS_EX_TOOLWINDOW |
			 WS_EX_CLIENTEDGE  ,
							// styleex
			NULL,			// classname
			mother[i]->m_szName,	
							// title
			WS_CHILD |	WS_THICKFRAME|
			WS_CAPTION | WS_CLIPSIBLINGS|
			WS_VISIBLE | WS_TABSTOP, 
							// style
			nX,// + nOX,
			nY,// + nOY,	
			nLen,nHei,		// width height
			hWnd,			// hwndParent
			(HMENU)i+1,		// menu
			NULL			// lpParam
			))
		{
			//OutputDebugString("wndtable created\n");

			pWnd->FillTable(*mother[i], i);
			pWnd->ShowWindow(SW_SHOWNOACTIVATE);
			mother[i]->SetWndTable(pWnd);
		}
	}
	return TRUE;
}

void CSQLMother::RemoveVisual()
{
	CSQLMother & mother = (*this);
	
	for (int i=0; i<m_nSize; i++)
	{
        /*
		CWnd *pWnd = (CWnd*)mother[i]->GetWndTable();
		if (pWnd)
		{
			pWnd->DestroyWindow();
			delete pWnd;
			mother[i]->SetWndTable(NULL);
		} */

	    CWnd *pWnd = (CWnd*)mother[i]->GetWndTable();
        if (pWnd)
        {
            DeleteWindow(pWnd);
            mother[i]->SetWndTable(NULL);
        }
	}
}

void CSQLMother::SetSelTable(int i)
{
	m_nSelTable = i;
}

int CSQLMother::GetSelTable()
{
	return m_nSelTable;
}

void CSQLMother::NotifyTables(int nMsg, int n)
{
	CSQLMother & mother = (*this);

	for (int i=0; i<m_nSize; i++)
	{
		CWnd *pWnd = (CWnd*)mother[i]->GetWndTable();
		if (pWnd)
		{
			pWnd->SendMessage(nMsg, i, n);
		}
	}

}

BOOL CSQLMother::UpdateVisual()
{
	if (!m_pWnd)
	{
		return FALSE;
	}

	HWND hWnd = m_pWnd->m_hWnd; 
	//HWND hWnd = AfxGetMainWnd()->m_hWnd; 

	CSQLMother & mother = (*this);

	for (int i=0; i<m_nSize; i++)
	{
		if (!mother[i]->GetWndTable())
		{
			CWndTable * pWnd = new CWndTable(this);

			int nX, nY, nLen, nHei;
			int nOX, nOY;

			GetOffset(nOX, nOY);

			mother[i]->GetWndXY(nX, nY);
			mother[i]->GetWndSize(nLen, nHei);

			if (pWnd->CreateEx(
				 WS_EX_TOOLWINDOW |
				WS_EX_CLIENTEDGE  ,
								// styleex
				NULL,			// classname
				mother[i]->m_szName,	
								// title
                WS_OVERLAPPED|
				WS_CHILD |	WS_THICKFRAME|
				WS_CAPTION | WS_CLIPSIBLINGS|
				WS_VISIBLE | WS_TABSTOP, 
								// style
				nX,// + nOX,
				nY,// + nOY,	
								// x, y
				nLen,nHei,		// width height
				hWnd,			// hwndParent
				(HMENU)i+1,		// menu
				NULL			// lpParam
				))
			{
				//OutputDebugString("new wndtable created\n");

				pWnd->FillTable(*mother[i], i);
				pWnd->ShowWindow(SW_SHOWNOACTIVATE);
				mother[i]->SetWndTable(pWnd);
			}
		}
	}
	return TRUE;
}

BOOL CSQLMother::GetOffset(int &nOX, int &nOY)
{
	CWnd *pMainWnd = AfxGetMainWnd();

	if (m_pWnd && pMainWnd)
	{
		CRect rectView;
		m_pWnd->GetWindowRect(&rectView);

		CRect rectMain;
		pMainWnd->GetWindowRect(&rectMain);

		nOX = rectView.left - rectMain.left;
		nOY = rectView.top - rectMain.top;
	}

	return (BOOL) (m_pWnd && pMainWnd);
}

void CSQLMother::DeleteWindow(CWnd * pWnd)
{
    if (pWnd)
    {
        CWndTable * pWndTable = (CWndTable *)(pWnd);
        pWndTable->SendMessage(WM_UTABLETERMINATE);
        pWndTable->SendMessage(WM_CLOSE);
        delete pWndTable;
    }
}
