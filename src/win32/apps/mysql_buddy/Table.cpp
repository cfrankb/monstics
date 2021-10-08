// Table.cpp : implementation file
//

#include "stdafx.h"
#include "Table.h"
#include "sqlmother.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTable

CTable::CTable()
{
	Init();
}

CTable::~CTable()
{
	Forget();
}

/////////////////////////////////////////////////////////////////////////////
// CTable message handlers

BOOL CTable::Add(CField * p)
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

BOOL CTable::RemoveAt(int n)
{
	if (m_pHead && m_pTail && 
		!(n<0) && !(n>=m_nSize))
	{
		if (n==0)
		{
			CField *p = m_pHead;
			m_pHead = m_pHead->m_pNext;
			m_nSize--;
			free(p);

			if (!m_pHead)
			{
				m_pTail = NULL;
			}
		}
		else
		{
			CTable & table = (*this);
			CField *p = table[n];
			if (p)
			{
				if (p == m_pTail)
				{
					CField *pp = table[n-1];
					m_pTail = pp;		
					pp->m_pNext = NULL;
					free(p);
				}
				else
				{
					CField *pp = table[n-1];
					pp->m_pNext = table[n+1];
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


CField * CTable::operator[] (int n)
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
			CField *p = m_pHead;
			while (n && p)
			{
				p = p->m_pNext;
				n --;
			}	

			return p;
		}
	}
}

void CTable::Init()
{
	ZeroMemory(this, sizeof(CTable));

	m_nX = 100;
	m_nY = 100;
	m_nLen = 100;
	m_nHei = 100;
}
			   
void CTable::Forget()
{
	CField * p = m_pHead;

	while (p)
	{
		CField * pp = p;
		p = p -> m_pNext;
		free(pp);
	}

	if (m_pWnd)
	{
		//((CWnd*) (m_pWnd))->DestroyWindow();
		//lete (CWnd*) (m_pWnd);
        CSQLMother::DeleteWindow((CWnd*) (m_pWnd));
		m_pWnd = NULL;
	}

	Init();
}

void CTable::Serialize(CArchive & ar, int nVer)
{
	if (ar.IsLoading()) // loading
	{
		Forget();
		int nSize=0;
		ar.Read(&nSize,4);
		ar.Read(m_szName, MAX_TB_NAME);

		ar.Read(&m_nX,4);
		ar.Read(&m_nY,4);
		ar.Read(&m_nLen,4);
		ar.Read(&m_nHei,4);

		CField *p = NULL;
		m_pHead = NULL;

		for (int i=0; i<nSize; i++)
		{
			p = (CField*)malloc(sizeof(CField));
			ZeroMemory(p, sizeof(CField));
			p->Serialize(ar, nVer);
			Add(p);
		}

        int nInfoSize;
        switch (nVer)
        {
            case 0:
            case 1:
            case 2:
                m_szInfo[0]=0;
            break;

            case 3:
                ar.Read(&nInfoSize, 4);
                ar.Read(m_szInfo, nInfoSize);
                m_szInfo[nInfoSize]=0;
            break;
        }

        m_pWnd = NULL;
		m_pNext = NULL;
	}
	else // saving
	{
		ar.Write(&m_nSize, 4);
		ar.Write(m_szName, MAX_TB_NAME);

		ar.Write(&m_nX,4);
		ar.Write(&m_nY,4);
		ar.Write(&m_nLen,4);
		ar.Write(&m_nHei,4);

		CTable & table = (*this);

		for (int i=0; i<m_nSize; i++)
		{
			CField *p = table[i];
			if (p)
			{
				p->Serialize(ar, nVer);
			}
		}

        // version 0.3 & up
        int nInfoSize = strlen(m_szInfo);
        ar.Write(&nInfoSize, 4);
        ar.Write(m_szInfo, nInfoSize);
	}
}

int CTable::GetSize()
{
	return m_nSize;
}

void CTable::ProcessSQL(CString & strSQL, char *szTable)
{
	char szTemp[256];
 	CTable & table = (*this);

	// overide the default table name
	if (!szTable)
	{
		strSQL = "CREATE TABLE " + CString(table.m_szName) + " (\r\n";
	}
	else
	{
		strSQL = "CREATE TABLE " + CString(szTable) + " (\r\n";
	}

	int i;
	BOOL bMore = FALSE;

	CString strMore = "";

	for (i=0; i<table.GetSize(); i++)
	{
		CField *p = table[i];
		if (p)
		{
			CField & field = (*p);

			if (field.m_bPrimary)
			{
				if (strMore!="")
				{
					strMore = strMore + ",\r\n"; 
				}

				strMore = strMore + "    PRIMARY KEY" +  " ("
					+ field.m_szName + ")";
			}

			if (field.m_bUnique)
			{
				if (strMore!="")
				{
					strMore = strMore + ",\r\n"; 
				}

				strMore = strMore + "    UNIQUE " + field.m_szName +  " ("
					+ field.m_szName + ")";
			}

			if (field.m_bKey)
			{
				if (strMore!="")
				{
					strMore = strMore + ",\r\n"; 
				}

				strMore = strMore + "    KEY " + field.m_szName + " ("
					+ field.m_szName + ")";
			}

				bMore = bMore || field.m_bKey ||
					field.m_bPrimary ||
					field.m_bUnique;
		}

	}

	if (strMore!="")
	{
		strMore = strMore + "\r\n"; 
	}

	for (i=0; i<table.GetSize(); i++)
	{
		CField *p = table[i];
		if (p)
		{
			p->FormatField(szTemp);			
			strSQL = strSQL + "    " + CString(szTemp) ;

			if (bMore || ((i+1)!=table.GetSize()))
			{
				strSQL = strSQL + ",\r\n";
			}
			else
			{
				strSQL = strSQL + "\r\n";
			}
		}
	}

	strSQL = strSQL + strMore + ");";
}


void * CTable::GetWndTable()
{
	return m_pWnd;
}

void CTable::SetWndTable(void *pWnd)
{
	m_pWnd = pWnd;
}

void CTable::SetWndSize(int nLen, int nHei)
{
	m_nLen = nLen;
	m_nHei = nHei;
}

void CTable::SetWndXY(int nX, int nY)
{
	m_nX = nX;
	m_nY = nY;
}

void CTable::GetWndSize(int & nLen, int &nHei)
{
	nLen = m_nLen;
	nHei = m_nHei;
}

void CTable::GetWndXY(int & nX, int &nY)
{
	nX = m_nX;
	nY = m_nY;
}

void CTable::FormatTechDoc(CString & str)
{
    CString strTemp;
    CTable & current = *this;
    str = CString("\r\n<p><b>") 
        + m_szName 
        + "</b></p><p><table border=1>\r\n" ;

    for (int i=0; i<m_nSize; i++)
    {
        current[i]->FormatTechDoc(strTemp);
        str = str + strTemp;
    }

    str = str 
        + "\r\n</table>\r\n"
        + "<p>" + CString(m_szInfo) + "\r\n";
}

CField * CTable::FindField(char *sz)
{
    CTable & current = *this;
    for (int i=0; i<m_nSize; i++)
    {
        CField *p = current[i];

        if (strcmpi(p->m_szName, sz)==0) 
        {
            return p;
        }
    }

    return NULL;    
}
