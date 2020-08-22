// CDlgClassEdit.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgClassEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgClassEdit dialog


CDlgClassEdit::CDlgClassEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgClassEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgClassEdit)
	m_bSystem = FALSE;
	m_strLabel = _T("");
	m_strValue = _T("");
	m_nValue = -1;
	//}}AFX_DATA_INIT
}


void CDlgClassEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgClassEdit)
	DDX_Check(pDX, IDC_CSYSTEM, m_bSystem);
	DDX_Text(pDX, IDC_ELABEL, m_strLabel);
	DDV_MaxChars(pDX, m_strLabel, 32);
	DDX_CBIndex(pDX, IDC_CVALUE, m_nValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgClassEdit, CDialog)
	//{{AFX_MSG_MAP(CDlgClassEdit)
	ON_CBN_SELCHANGE(IDC_CVALUE, OnSelchangeCvalue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgClassEdit message handlers

BOOL CDlgClassEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CComboBox * pCombo = (CComboBox*)
		GetDlgItem (IDC_CVALUE);

	int n;
	for (n=0; n<256; n++)
	{
		char sz[4];
		wsprintf(sz, "%x", n);
		if ((strlen (sz)<2))
		{ sz[1] = sz[0]; 
			sz[2]=0;
			sz[0]= '0';
		}
		pCombo->AddString (sz);
	}

	pCombo->SetCurSel (m_nValue);
	UpdateB_OK();	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgClassEdit::UpdateB_OK()
{
	CComboBox * pCombo = (CComboBox*)
		GetDlgItem (IDC_CVALUE);

	CButton *pButtonOK =(CButton*) 
		GetDlgItem (IDOK);

	int n = pCombo->GetCurSel ();
	pButtonOK->EnableWindow (n!=CB_ERR);

}	

void CDlgClassEdit::OnSelchangeCvalue() 
{
	// TODO: Add your control notification handler code here
	UpdateB_OK();	
}
