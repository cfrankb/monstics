// Dot.cpp : implementation file
//

#include "stdafx.h"
#include "Dot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDot

CDot::CDot()
{
	Init();
}

CDot::~CDot()
{
}



/////////////////////////////////////////////////////////////////////////////
// CDot message handlers

void CDot::Init()
{
	m_nColor=-1;
	m_nX=-1;
	m_nY=-1;
}


CDot::CDot (int x, int y)
{
	m_nX = x;
	m_nY = y;
}

CDot::CDot (CDot &dot)
{
	m_nColor= dot.m_nColor;
	m_nX= dot.m_nX;
	m_nY= dot.m_nY;
}


BOOL CDot::operator == (CDot & dot)
{

	return ((m_nX == dot.m_nX) && 
		(m_nY == dot.m_nY));
}


CDot & CDot::operator = (CDot & dot)
{
	m_nColor= dot.m_nColor;
	m_nX= dot.m_nX;
	m_nY= dot.m_nY;
	return *this;
}

CPoint pt;

CPoint & CDot::Point ()
{
	pt = CPoint (m_nX, m_nY);
	return pt;
}
