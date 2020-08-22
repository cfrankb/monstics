// ProtoPage3.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "ProtoPage3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtoPage3 property page

IMPLEMENT_DYNCREATE(CProtoPage3, CPropertyPage)

CProtoPage3::CProtoPage3() : CPropertyPage(CProtoPage3::IDD)
{
	//{{AFX_DATA_INIT(CProtoPage3)
	m_nChProto = -1;
	m_nChSound = -1;
	m_nPoints = -1;
	m_nRbDelay = -1;
	m_nRebirths = -1;
	//}}AFX_DATA_INIT
}

CProtoPage3::~CProtoPage3()
{
}

void CProtoPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtoPage3)
	DDX_CBIndex(pDX, IDC_CCHPROTO, m_nChProto);
	DDX_CBIndex(pDX, IDC_CCHSOUND, m_nChSound);
	DDX_CBIndex(pDX, IDC_CPTS, m_nPoints);
	DDX_CBIndex(pDX, IDC_CDELAY, m_nRbDelay);
	DDX_CBIndex(pDX, IDC_CREBIRTHS, m_nRebirths);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtoPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CProtoPage3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtoPage3 message handlers

BOOL CProtoPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	int n;
	int i=0;
	char sz[20];

	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;

	// Points **************************************

	CComboBox * pComboPts = (CComboBox *)
		GetDlgItem (IDC_CPTS);

	for (n=0; n<m_pDoc->m_game3.m_arrPoints.GetSize(); 
		n++)
	{
		pComboPts->
			AddString(m_pDoc->m_game3.m_arrPoints[n].m_szName);
			
	}

	pComboPts->SetCurSel (m_nPoints);	

	
	// Sound - Combos *******************************
	// IDC_CCHSOUND


	CComboBox * pComboChSound = (CComboBox *)
		GetDlgItem (IDC_CCHSOUND);
	
	for (n=0; n<m_pDoc->m_game3.m_arrSoundData.GetSize(); 
		n++)
	{
		pComboChSound->
			AddString(m_pDoc->m_game3.m_arrSoundData[n].m_szName);
	}

	pComboChSound -> SetCurSel (m_nChSound);

	// Proto *******************************************
	// IDC_CCHPROTO

	CComboBox * pComboChProto = (CComboBox *)
		GetDlgItem (IDC_CCHPROTO);

	for (n=0; n<arrProto.GetSize(); n++)
	{
		pComboChProto->
			AddString(arrProto[n].m_szName);		
	}

	pComboChProto -> SetCurSel (m_nChProto);

	// Nbr Rebirth *************************************
	// IDC_CREBIRTHS

	CComboBox * pComboRebirths = (CComboBox *)
		GetDlgItem (IDC_CREBIRTHS);

	for (n=0; n<=40; n++)
	{
		if (n!=0)
			wsprintf(sz,"%d", n);
		else
			strcpy (sz, "(none)");

		pComboRebirths -> AddString(sz);
	}

	// Rebirth delay **********************************
	// IDC_CDELAY

	CComboBox * pComboRbDelay = (CComboBox *)
		GetDlgItem (IDC_CDELAY);

	for (n=0; n<20; n++)
	{
		if (n!=0)
			wsprintf(sz,"Speed %d", n);
		else
			strcpy (sz, "(fast)");

		pComboRbDelay -> AddString(sz);
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
