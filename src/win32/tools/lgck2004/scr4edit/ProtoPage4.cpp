// ProtoPage4.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "ProtoPage4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtoPage4 property page

IMPLEMENT_DYNCREATE(CProtoPage4, CPropertyPage)

CProtoPage4::CProtoPage4() : CPropertyPage(CProtoPage4::IDD)
{
	//{{AFX_DATA_INIT(CProtoPage4)
	m_nAutoBullet = -1;
	m_nAutoProto = -1;
	m_nAutoProtoTime = -1;
	m_nAutoBulletTime = -1;
	m_nAutoSound = -1;
	m_nAutoSoundTime = -1;
	m_nAutoTriggerTime = -1;
	m_bAutoTrigger = FALSE;
	//}}AFX_DATA_INIT
}

CProtoPage4::~CProtoPage4()
{
}

void CProtoPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtoPage4)
	DDX_CBIndex(pDX, IDC_CAUTO_BULLET, m_nAutoBullet);
	DDX_CBIndex(pDX, IDC_CAUTO_CHPROTO, m_nAutoProto);
	DDX_CBIndex(pDX, IDC_CAUTO_CHTIME, m_nAutoProtoTime);
	DDX_CBIndex(pDX, IDC_CAUTO_FIRETIME, m_nAutoBulletTime);
	DDX_CBIndex(pDX, IDC_CAUTO_SOUND, m_nAutoSound);
	DDX_CBIndex(pDX, IDC_CAUTO_STIME, m_nAutoSoundTime);
	DDX_CBIndex(pDX, IDC_CAUTO_TRIGGERTIME, m_nAutoTriggerTime);
	DDX_Check(pDX, IDC_CAUTO_CALLTRIGGER, m_bAutoTrigger);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtoPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CProtoPage4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtoPage4 message handlers

BOOL CProtoPage4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;	
	int n;
	
	// Sound - Combo *******************************
	// IDC_CAUTO_SOUND 

	CComboBox * pComboAutoSound = (CComboBox *)
		GetDlgItem (IDC_CAUTO_SOUND);

	for (n=0; n<m_pDoc->m_game3.m_arrSoundData.GetSize(); 
		n++)
	{
		pComboAutoSound->
			AddString(m_pDoc->m_game3.m_arrSoundData[n].m_szName);
	}

	pComboAutoSound -> SetCurSel (m_nAutoSound);

	// Proto *******************************************
	// IDC_CAUTO_CHPROTO
	// and IDC_CAUTO_BULLET

	CComboBox * pComboAutoProto = (CComboBox *)
		GetDlgItem (IDC_CAUTO_CHPROTO);

	CComboBox * pComboAutoBullet = (CComboBox *)
		GetDlgItem (IDC_CAUTO_BULLET);

	for (n=0; n<arrProto.GetSize(); n++)
	{
		pComboAutoProto->
			AddString(arrProto[n].m_szName);		

		pComboAutoBullet->
			AddString(arrProto[n].m_szName);		
	
	}

	pComboAutoProto -> SetCurSel (m_nAutoProto);
	pComboAutoProto -> SetCurSel (m_nAutoBullet);

	// Timer Frequency ***********************

	CComboBox * pComboAutoSoundTime = (CComboBox *)
		GetDlgItem (IDC_CAUTO_STIME);
	CComboBox * pComboAutoBulletTime = (CComboBox *)
		GetDlgItem (IDC_CAUTO_FIRETIME);
	CComboBox * pComboAutoTriggerTime = (CComboBox *)
		GetDlgItem (IDC_CAUTO_TRIGGERTIME);
	CComboBox * pComboAutoProtoTime = (CComboBox *)
		GetDlgItem (IDC_CAUTO_CHTIME);
		
	for (n=0; n<256; n++)
	{
		char szText[15];
		wsprintf(szText,"Speed %d", n);

		if (n!=0) {
			pComboAutoSoundTime->AddString (szText);
			pComboAutoBulletTime->AddString (szText);
			pComboAutoTriggerTime->AddString (szText);
			pComboAutoProtoTime->AddString (szText);
		}
		else {
			pComboAutoSoundTime->AddString ("(never)");
			pComboAutoBulletTime->AddString ("(never)");
			pComboAutoTriggerTime->AddString ("(never)");
			pComboAutoProtoTime->AddString ( "(never)");
		}
	}

	pComboAutoSoundTime->SetCurSel (m_nAutoSoundTime);
	pComboAutoBulletTime->SetCurSel (m_nAutoBulletTime);
	pComboAutoTriggerTime->SetCurSel (m_nAutoTriggerTime);
	pComboAutoProtoTime->SetCurSel (m_nAutoProtoTime);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
