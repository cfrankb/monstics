// ProtoSheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ProtoSheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtoSheet

IMPLEMENT_DYNAMIC(CProtoSheet, CPropertySheet)

CProtoSheet::CProtoSheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_Page3);
	AddPage(&m_Page4);
	AddPage(&m_Page5);

    SetTitle("",0);   
	SetActivePage(0);
}

CProtoSheet::~CProtoSheet()
{
}


BEGIN_MESSAGE_MAP(CProtoSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CProtoSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CProtoSheet message handlers


