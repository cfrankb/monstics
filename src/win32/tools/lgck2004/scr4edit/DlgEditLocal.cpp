// DlgEditLocal.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgEditLocal.h"
#include "shared.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditLocal dialog


CDlgEditLocal::CDlgEditLocal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditLocal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditLocal)
	m_nSubClass = -1;
	m_nTriggerKey = -1;
	m_strClass = _T("");
	m_strObject = _T("");
	m_bC10 = FALSE;
	m_bC20 = FALSE;
	m_bC40 = FALSE;
	m_bC80 = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgEditLocal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditLocal)
	DDX_CBIndex(pDX, IDC_CSUBCLASS, m_nSubClass);
	DDX_CBIndex(pDX, IDC_CTRIGGERKEY, m_nTriggerKey);
	DDX_Text(pDX, IDC_ECLASS, m_strClass);
	DDX_Text(pDX, IDC_EOBJECT, m_strObject);
	DDX_Check(pDX, IDC_C10, m_bC10);
	DDX_Check(pDX, IDC_C20, m_bC20);
	DDX_Check(pDX, IDC_C40, m_bC40);
	DDX_Check(pDX, IDC_C80, m_bC80);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditLocal, CDialog)
	//{{AFX_MSG_MAP(CDlgEditLocal)
	ON_BN_CLICKED(IDC_BPROTO, OnBproto)
	ON_BN_CLICKED(IDC_BMORE, OnBmore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditLocal message handlers

BOOL CDlgEditLocal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int n;

	CComboBox * pComboSubClass = (CComboBox *)
		GetDlgItem (IDC_CSUBCLASS);

	CComboBox * pComboTriggerKey = (CComboBox *)
		GetDlgItem (IDC_CTRIGGERKEY);

	char sz[16];
	// 128 64 32 16
	for (n=0; n<255; n++)
	{
		if (n==0)
			strcpy(sz, "(none)");
		else
			wsprintf(sz, "0x%x", n);

		pComboSubClass->AddString(sz);

		if (n<16)
			pComboTriggerKey->AddString(sz);
	}

	pComboSubClass->SetCurSel(m_nSubClass);
	pComboTriggerKey->SetCurSel(m_nTriggerKey);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEditLocal::OnBproto() 
{
	// TODO: Add your control notification handler code here
	CGameFile3 & game = m_pDoc->m_game3; 
	CProto & proto = game.m_arrProto[m_nProto];
	if (DoProtoProps(proto, m_pDoc)==IDOK)
	{
		CWnd *pWnd;

		m_strClass = game.m_arrClasses.StringFor(proto.m_nClass);
		m_strObject = proto.m_szName;
		
		pWnd = GetDlgItem(IDC_ECLASS);
		pWnd->SetWindowText(m_strClass);

		pWnd = GetDlgItem(IDC_EOBJECT);
		pWnd->SetWindowText(m_strObject);
	}
}

void CDlgEditLocal::OnBmore() 
{
	// TODO: Add your control notification handler code here

	if (!m_pEntry->m_pExtraData)
	{
		if (AfxMessageBox("This object doesn't have\nan extended section.\nCreate?",
			MB_YESNO)!=IDYES)
			return;

		// allocate data
	}

	// edit data
}
