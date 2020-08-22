// DotArray.cpp : implementation file
//

#include "stdafx.h"
#include "DotArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZEOF (sizeof (CDot))
#define GROWBY 400

/////////////////////////////////////////////////////////////////////////////
// CDotArray

CDotArray::CDotArray()
{
	m_nSize =0;
	m_nMax = GROWBY;
	m_arrDots = (CDot *)malloc (SIZEOF* m_nMax);
}

CDotArray::~CDotArray()
{
	Forget();
	free( m_arrDots);

#ifdef _DEBUG
	char sz[128];
	wsprintf (sz, "CDotArray: m_nMax = %i\n", m_nMax);
	OutputDebugString (sz);
#endif

}


/////////////////////////////////////////////////////////////////////////////
// CDotArray message handlers

int CDotArray::Add (CDot & pDot)
{

	m_arrDots[m_nSize] = pDot;
	m_nSize++;
	if (m_nSize>=m_nMax)
	{
		CDot* t= (CDot*) malloc (SIZEOF*(m_nMax+GROWBY));
		int i;
		for (i=0; i<m_nSize; i++)
			t[i] = m_arrDots[i];
		free (m_arrDots);
		m_arrDots = t;
		m_nMax = m_nMax+GROWBY;
	}
	return TRUE;
}


void CDotArray::Forget()
{
	m_nSize =0;
}

