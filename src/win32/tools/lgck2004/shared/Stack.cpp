// Stack.cpp : implementation file
//

#include "stdafx.h"
#include "Stack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStack

CStack::CStack()
{
	Init();
}

CStack::~CStack()
{
}

/////////////////////////////////////////////////////////////////////////////
// CStack message handlers

int CStack::GetSize()
{
	return m_nSize;
}

void CStack::Init()
{
	m_nSize = 0;
}

void CStack::Forget()
{
	m_nSize = 0;
}

int CStack::pop()
{
	int r;

	if (m_nSize > 0)
	{
		r = m_arrData[m_nSize-1];
		m_nSize--;
		return r;
	}
	else
	{
		OutputDebugString("CStack::pop Stack overflow\n");
		return 0;
	}			 
}

void CStack::push(int n)
{
	if (m_nSize < MAXSTACK)
	{
		m_arrData[m_nSize]=n;
		m_nSize++;
	}
	else
	{
		OutputDebugString("CStack::push Stack overflow\n");
	}
}
