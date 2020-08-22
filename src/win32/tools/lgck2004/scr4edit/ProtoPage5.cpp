// ProtoPage5.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "ProtoPage5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtoPage5 property page

IMPLEMENT_DYNCREATE(CProtoPage5, CPropertyPage)

CProtoPage5::CProtoPage5() : CPropertyPage(CProtoPage5::IDD)
{
	//{{AFX_DATA_INIT(CProtoPage5)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CProtoPage5::~CProtoPage5()
{
}

void CProtoPage5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtoPage5)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtoPage5, CPropertyPage)
	//{{AFX_MSG_MAP(CProtoPage5)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtoPage5 message handlers
