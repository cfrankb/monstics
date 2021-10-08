// TextArray.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "TextArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZEOF (sizeof(char*))

/////////////////////////////////////////////////////////////////////////////
// CTextArray

CTextArray::CTextArray()
{
	Init();
}

CTextArray::~CTextArray()
{
	Forget();
}

/////////////////////////////////////////////////////////////////////////////
// CTextArray message handlers

static char g_szText[]="(invalid text)";

void CTextArray::Init()
{
	m_nSize = 0;
	m_ppText = NULL;
}

void CTextArray::Forget()
{
	if (m_ppText)
	{
		for (int i=0; i<m_nSize; i++)
		{
			free(m_ppText[i]);
		}
		free(m_ppText);
		m_ppText=NULL;
		m_nSize=0;
	}
}


BOOL CTextArray::Add(char *p)
{
	if (!m_ppText) // first item
	{
		m_ppText = (char**) malloc(SIZEOF);
		m_ppText[0] = p;
		m_nSize = 1;
	}
	else
	{
		char **pp = (char**) malloc(SIZEOF*(m_nSize+1));
		pp[m_nSize] = p; 
		memcpy (pp, m_ppText, SIZEOF*m_nSize);
		m_nSize++;
		free(m_ppText);
		m_ppText = pp;
	}

	return TRUE;
}

char * CTextArray::operator[] (int n)
{
	if (n<0 || n>=m_nSize)
	{
        CString str;
        str.Format("CTextArray::operator[]; n=%d out of bound\r\n", n);
        OutputDebugString(str);

		return g_szText;
	}
	else
	{
		return m_ppText[n];
	}
}

int CTextArray::GetSize()
{
	return m_nSize;
}

int CTextArray::GetIndexFor(char *sz)
{
	int i;
	for (i=0; i<m_nSize; i++)
	{
		if (strcmpi(sz, m_ppText[i])==0)
		{
			return i;
		}
	}		  
	
	return -1;
}

int CTextArray::GetIndexFor(CString & str)
{
	return GetIndexFor(str.GetBuffer(1));
}
