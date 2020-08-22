// ProtoPage2.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ProtoPage2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CProtoPage2, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CProtoPage2 property page

CProtoPage2::CProtoPage2() : CPropertyPage(CProtoPage2::IDD)
{
	//{{AFX_DATA_INIT(CProtoPage2)
	m_nDefaultAim = -1;
	m_nAniSpeed = -1;
	m_nMoveSpeed = -1;
	m_nDamages = -1;
	m_nHitPoints = -1;
	m_nUserTag = -1;
	m_nPowerLevel = -1;
	//}}AFX_DATA_INIT
}

CProtoPage2::~CProtoPage2()
{
}

void CProtoPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtoPage2)
	DDX_CBIndex(pDX, IDC_CAIM, m_nDefaultAim);
	DDX_CBIndex(pDX, IDC_CANISPEED, m_nAniSpeed);
	DDX_CBIndex(pDX, IDC_CMOVESPEED, m_nMoveSpeed);
	DDX_CBIndex(pDX, IDC_CDAMAGES, m_nDamages);
	DDX_CBIndex(pDX, IDC_CHITPOINTS, m_nHitPoints);
	DDX_CBIndex(pDX, IDC_CUSERTAG, m_nUserTag);
	DDX_CBIndex(pDX, IDC_CPOWERLEVEL, m_nPowerLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtoPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CProtoPage2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CProtoPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	int n;
	int i;

	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;

	// Speeds ***************************************

	CComboBox * pComboAniSpeed = (CComboBox *)
		GetDlgItem (IDC_CANISPEED);

	CComboBox * pComboMoveSpeed = (CComboBox *)
		GetDlgItem (IDC_CMOVESPEED);

	for (n=0; n<16; n++)
	{
		char szText[9];
		wsprintf(szText,"Speed %d", n);
		
		if (n!=0) {
			i= pComboAniSpeed->AddString (szText);
			i= pComboMoveSpeed->AddString (szText);
		}
		else {
			i= pComboAniSpeed->AddString ("(fast)");
			i= pComboMoveSpeed->AddString ("(fast)");
		}
	
	}

	pComboAniSpeed->SetCurSel (m_nAniSpeed);
	pComboMoveSpeed->SetCurSel (m_nMoveSpeed);

	// Default Aim ********************************

	CComboBox * pComboAim = (CComboBox *)
		GetDlgItem (IDC_CAIM);

	pComboAim->AddString("UP");
	pComboAim->AddString("DOWN");
	pComboAim->AddString("LEFT");
	pComboAim->AddString("RIGHT");
	pComboAim->SetCurSel (m_nDefaultAim);

	// IDC_CUSERTAG ***********************************

	CComboBox * pComboUserTag = (CComboBox *)
		GetDlgItem (IDC_CUSERTAG);

	for (n=0; n<m_pDoc->m_game3.m_arrUserDefs.GetSize(); 
		n++)
	{
		pComboUserTag->
			AddString(m_pDoc->m_game3.m_arrUserDefs[n].m_szName);
	}

	pComboUserTag -> SetCurSel (m_nUserTag);

	// IDC_CDAMAGES 

	CComboBox * pComboDamages = (CComboBox *)
		GetDlgItem (IDC_CDAMAGES);
	
	for (n=0; n<254; n++)
	{
		char szText[9];
		wsprintf(szText,"%d pts", n);
		
		if (n!=0) {
			i= pComboDamages->AddString (szText);
		}
		else {
			i= pComboDamages->AddString ("(none)");
		}

	}

	// IDC_CHITPOINTS

	CComboBox * pComboHitPoints = (CComboBox *)
		GetDlgItem (IDC_CHITPOINTS);
	
	for (n=0; n<255; n++)
	{
		char szText[9];
		wsprintf(szText,"%d pts", n);
		
		if (n!=0) {
			i= pComboHitPoints->AddString (szText);
		}
		else {
			i= pComboHitPoints->AddString ("(none)");
		}

	}

	// IDC_POWERLEVEL

	CComboBox * pComboPowerLevel = (CComboBox *)
		GetDlgItem (IDC_CPOWERLEVEL);

	for (n=0; n<16; n++)
	{
		char szText[9];
		wsprintf(szText,"Level %d", n);
		
		if (n!=0) {
			i= pComboPowerLevel->AddString (szText);
		}
		else {
			i= pComboPowerLevel->AddString ("(ignored)");
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
