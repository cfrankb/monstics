// StaticEx.cpp : implementation file
//

#include "stdafx.h"
#include "App.h"
#include "StaticEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticEx

CStaticEx::CStaticEx()
{

    m_nBkColor  =  0x00ff0000;
    m_nTextColor = 0xffffffff; 

    m_brBrush.CreateSolidBrush(m_nBkColor);

}

CStaticEx::~CStaticEx()
{
}


BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
	//{{AFX_MSG_MAP(CStaticEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticEx message handlers

void CStaticEx::OnPaint() 
{
    CStatic::OnPaint();
}

HBRUSH CStaticEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// TODO: Return a different brush if the default is not desired
    return ::GetSysColorBrush(COLOR_WINDOW);

}

void CStaticEx::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CStatic::WinHelp(dwData, nCmd);
}

BOOL CStaticEx::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CStatic::OnEraseBkgnd(pDC);
}

HBRUSH CStaticEx::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
    pDC->SetBkColor(m_nBkColor);
    pDC->SetTextColor(m_nTextColor);
    
    HBRUSH hbr = m_brBrush;
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return m_brBrush;
}

void CStaticEx::SetColor(DWORD l_nBkColor, DWORD l_nTextColor )
{

    m_nBkColor = l_nBkColor;
    m_nTextColor = l_nTextColor;

    m_brBrush.DeleteObject();
    m_brBrush.CreateSolidBrush(m_nBkColor);
    

}
