// DbPage2.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DbPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbPage2 property page

IMPLEMENT_DYNCREATE(CDbPage2, CPropertyPage)

CDbPage2::CDbPage2() : CPropertyPage(CDbPage2::IDD)
{
	//{{AFX_DATA_INIT(CDbPage2)
	m_bAtDeathResetHP = FALSE;
	m_nHP = -1;
	m_nLives = -1;
	m_nMaxHP = -1;
	m_nMaxLives = -1;
	m_bAtDeathResetLev = FALSE;
	//}}AFX_DATA_INIT
}

CDbPage2::~CDbPage2()
{
}

void CDbPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDbPage2)
	DDX_Control(pDX, IDC_C_ATDEATH_RESETLEV, m_ctrAtDeathResetLev);
	DDX_Control(pDX, IDC_CBMAXLIVES, m_ctrMaxLives);
	DDX_Control(pDX, IDC_CBMAXHP, m_ctrMaxHP);
	DDX_Control(pDX, IDC_CBLIVES, m_ctrLives);
	DDX_Control(pDX, IDC_CBHP, m_ctrHP);
	DDX_Control(pDX, IDC_C_ATDEATH_RESETHP, m_ctrAtDeathResetHP);
	DDX_Check(pDX, IDC_C_ATDEATH_RESETHP, m_bAtDeathResetHP);
	DDX_CBIndex(pDX, IDC_CBHP, m_nHP);
	DDX_CBIndex(pDX, IDC_CBLIVES, m_nLives);
	DDX_CBIndex(pDX, IDC_CBMAXHP, m_nMaxHP);
	DDX_CBIndex(pDX, IDC_CBMAXLIVES, m_nMaxLives);
	DDX_Check(pDX, IDC_C_ATDEATH_RESETLEV, m_bAtDeathResetLev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDbPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CDbPage2)
	ON_CBN_SELCHANGE(IDC_CBHP, OnSelchangeCbhp)
	ON_CBN_SELCHANGE(IDC_CBLIVES, OnSelchangeCblives)
	ON_CBN_SELCHANGE(IDC_CBMAXHP, OnSelchangeCbmaxhp)
	ON_CBN_SELCHANGE(IDC_CBMAXLIVES, OnSelchangeCbmaxlives)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbPage2 message handlers

BOOL CDbPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	for (int n=0; n<256; n++)
	{
		char szText[9];
		wsprintf(szText,"%d", n);

		m_ctrHP.AddString(szText);
		m_ctrLives.AddString(szText);
		m_ctrMaxLives.AddString(szText);
		m_ctrMaxHP.AddString(szText);
	}

	m_ctrHP.SetCurSel(m_nHP);
	m_ctrLives.SetCurSel(m_nLives);
	m_ctrMaxLives.SetCurSel(m_nMaxLives);
	m_ctrMaxHP.SetCurSel(m_nMaxHP);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDbPage2::OnSelchangeCbhp() 
{
	// TODO: Add your control notification handler code here
	m_nHP = m_ctrHP.GetCurSel();
}

void CDbPage2::OnSelchangeCblives() 
{
	// TODO: Add your control notification handler code here
	m_nLives = m_ctrLives.GetCurSel();
}

void CDbPage2::OnSelchangeCbmaxhp() 
{
	// TODO: Add your control notification handler code here
	m_nMaxHP = m_ctrMaxHP.GetCurSel();
}

void CDbPage2::OnSelchangeCbmaxlives() 
{
	// TODO: Add your control notification handler code here
	m_nMaxLives = m_ctrMaxLives.GetCurSel();

}
