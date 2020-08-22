// DbPage1.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DbPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbPage1 property page

IMPLEMENT_DYNCREATE(CDbPage1, CPropertyPage)

CDbPage1::CDbPage1() : CPropertyPage(CDbPage1::IDD)
{
	//{{AFX_DATA_INIT(CDbPage1)
	m_strName = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
}

CDbPage1::~CDbPage1()
{
}

void CDbPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDbPage1)
	DDX_Text(pDX, IDC_ENAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 32);
	DDX_Text(pDX, IDC_ETITLE, m_strTitle);
	DDV_MaxChars(pDX, m_strTitle, 32768);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDbPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CDbPage1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbPage1 message handlers
