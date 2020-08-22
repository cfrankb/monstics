// DbPage3.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DbPage3.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_LEN 640
#define MAX_LEN 4096
#define MIN_HEI 480
#define MAX_HEI 4096

/////////////////////////////////////////////////////////////////////////////
// CDbPage3 property page

IMPLEMENT_DYNCREATE(CDbPage3, CPropertyPage)

CDbPage3::CDbPage3() : CPropertyPage(CDbPage3::IDD)
{
	//{{AFX_DATA_INIT(CDbPage3)
	m_bAtLevelResetHP = FALSE;
	m_bContinuity = FALSE;
	m_bForceDefObj = FALSE;
	m_bInheritPlrObj = FALSE;
	m_bResizeLevel = FALSE;
	m_nLevelHei = 0;
	m_nLevelLen = 0;
	//}}AFX_DATA_INIT
}

CDbPage3::~CDbPage3()
{
}

void CDbPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDbPage3)
	DDX_Control(pDX, IDC_ELEVEL_LEN, m_ctrLevelLen);
	DDX_Control(pDX, IDC_ELEVEL_HEI, m_ctrLevelHei);
	DDX_Control(pDX, IDC_CRESIZELEVEL, m_ctrResizeLevel);
	DDX_Control(pDX, IDC_CINHERITPLROBJ, m_ctrInheritPlrObj);
	DDX_Control(pDX, IDC_CFORCEDEFOBJ, m_ctrForceDefObj);
	DDX_Control(pDX, IDC_CCONTINUITY, m_ctrContinuity);
	DDX_Control(pDX, IDC_C_ATLEVEL_RESETHP, m_ctrAtLevelResetHP);
	DDX_Check(pDX, IDC_C_ATLEVEL_RESETHP, m_bAtLevelResetHP);
	DDX_Check(pDX, IDC_CCONTINUITY, m_bContinuity);
	DDX_Check(pDX, IDC_CFORCEDEFOBJ, m_bForceDefObj);
	DDX_Check(pDX, IDC_CINHERITPLROBJ, m_bInheritPlrObj);
	DDX_Check(pDX, IDC_CRESIZELEVEL, m_bResizeLevel);
	DDX_Text(pDX, IDC_ELEVEL_LEN, m_nLevelLen);
	DDX_Text(pDX, IDC_ELEVEL_HEI, m_nLevelHei);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDbPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CDbPage3)
	ON_BN_CLICKED(IDC_CRESIZELEVEL, OnCresizelevel)
	ON_EN_CHANGE(IDC_ELEVEL_HEI, OnChangeElevelHei)
	ON_EN_CHANGE(IDC_ELEVEL_LEN, OnChangeElevelLen)
	ON_EN_KILLFOCUS(IDC_ELEVEL_HEI, OnKillfocusElevelHei)
	ON_EN_KILLFOCUS(IDC_ELEVEL_LEN, OnKillfocusElevelLen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbPage3 message handlers

BOOL CDbPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_ctrLevelLen.EnableWindow(m_bResizeLevel);
	m_ctrLevelHei.EnableWindow(m_bResizeLevel);

	m_ctrLevelLen.SetLimitText(5);
	m_ctrLevelHei.SetLimitText(5);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDbPage3::OnCresizelevel() 
{
	// TODO: Add your control notification handler code here
	m_bResizeLevel = ! 	m_bResizeLevel;

	m_ctrLevelLen.EnableWindow(m_bResizeLevel);
	m_ctrLevelHei.EnableWindow(m_bResizeLevel);

}

void CDbPage3::OnChangeElevelHei() 
{
	// TODO: Add your control notification handler code here
	//CEdit	m_ctrLevelHei;
}

void CDbPage3::OnChangeElevelLen() 
{
	// TODO: Add your control notification handler code here
	//CEdit	m_ctrLevelLen;
	
}

void CDbPage3::OnKillfocusElevelHei() 
{
	// TODO: Add your control notification handler code here
	TestHei();
}

void CDbPage3::OnKillfocusElevelLen() 
{
	// TODO: Add your control notification handler code here
	TestLen();	
}

void CDbPage3::TestLen()
{
	char szTemp1[16];
	char szTemp2[16];

	m_ctrLevelLen.GetWindowText(szTemp1, 8);
	
	int nTemp = str2int(szTemp1);
	if (nTemp<MIN_LEN)
	{
		nTemp = MIN_LEN;
	}

	if (nTemp>MAX_LEN)
	{
		nTemp = MAX_LEN;
	}

	if (nTemp % 8 != 0)
	{
		nTemp = nTemp - (nTemp % 8);
	}

	wsprintf(szTemp2, "%d", nTemp);

	if (strcmp(szTemp1, szTemp2)!=0)
	{
		m_ctrLevelLen.SetWindowText(szTemp2);	
	}

	m_nLevelLen = nTemp;
}

void CDbPage3::TestHei()
{
	char szTemp1[16];
	char szTemp2[16];

	m_ctrLevelHei.GetWindowText(szTemp1, 8);
	
	int nTemp = str2int(szTemp1);
	if (nTemp<MIN_HEI)
	{
		nTemp = MIN_HEI;
	}

	if (nTemp>MAX_HEI)
	{
		nTemp = MAX_HEI;
	}

	if (nTemp % 8 != 0)
	{
		nTemp = nTemp - (nTemp % 8);
	}

	wsprintf(szTemp2, "%d", nTemp);

	if (strcmp(szTemp1, szTemp2)!=0)
	{
		m_ctrLevelHei.SetWindowText(szTemp2);	
	}

	m_nLevelHei = nTemp;
}
