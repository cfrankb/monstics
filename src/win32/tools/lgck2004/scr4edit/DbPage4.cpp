// DbPage4.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DbPage4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbPage4 property page

IMPLEMENT_DYNCREATE(CDbPage4, CPropertyPage)

CDbPage4::CDbPage4() : CPropertyPage(CDbPage4::IDD)
{
	//{{AFX_DATA_INIT(CDbPage4)
	m_strPointsOBL = _T("");
	m_strSignsOBL = _T("");
	m_strSignsSet = _T("");
	//}}AFX_DATA_INIT
}

CDbPage4::~CDbPage4()
{
}

void CDbPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDbPage4)
	DDX_Control(pDX, IDC_CB_SIGNSSET, m_ctrSignsSet);
	DDX_Control(pDX, IDC_CB_SIGNSOBL, m_ctrSignsOBL);
	DDX_Control(pDX, IDC_CB_POINTSOBL, m_ctrPointsOBL);
	DDX_CBString(pDX, IDC_CB_POINTSOBL, m_strPointsOBL);
	DDV_MaxChars(pDX, m_strPointsOBL, 31);
	DDX_CBString(pDX, IDC_CB_SIGNSOBL, m_strSignsOBL);
	DDV_MaxChars(pDX, m_strSignsOBL, 31);
	DDX_CBString(pDX, IDC_CB_SIGNSSET, m_strSignsSet);
	DDV_MaxChars(pDX, m_strSignsSet, 63);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDbPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CDbPage4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbPage4 message handlers

BOOL CDbPage4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
