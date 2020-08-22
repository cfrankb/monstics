// DbSheet.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DbSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbSheet

IMPLEMENT_DYNAMIC(CDbSheet, CPropertySheet)

CDbSheet::CDbSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	Build();
}

CDbSheet::CDbSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	Build();
}

CDbSheet::~CDbSheet()
{
}


BEGIN_MESSAGE_MAP(CDbSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CDbSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbSheet message handlers

void CDbSheet::Build()
{
	AddPage(&m_page1);
	AddPage(&m_page2);
	AddPage(&m_page3);
	AddPage(&m_page4);
}
