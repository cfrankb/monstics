// DlgTagEdit.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgTagEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTagEdit dialog


//CDlgTagEdit::CDlgTagEdit(CWnd* pParent /*=NULL*/)
//	: CDialog(CDlgTagEdit::IDD, pParent)
CDlgTagEdit::CDlgTagEdit(UINT nIDD, char **ppChoices, char **ppContent)
	: CDialog(nIDD, NULL)
{
	//{{AFX_DATA_INIT(CDlgTagEdit)
	m_nValue = -1;
	m_strDescription = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT

	m_ppChoices = ppChoices;
	m_ppContent = ppContent;
}


void CDlgTagEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTagEdit)
	DDX_CBIndex(pDX, IDC_CVALUE, m_nValue);
	DDX_Text(pDX, IDC_ECONTENT, m_strDescription);
	DDV_MaxChars(pDX, m_strDescription, 250);
	DDX_Text(pDX, IDC_ENAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 250);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTagEdit, CDialog)
	//{{AFX_MSG_MAP(CDlgTagEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTagEdit message handlers

BOOL CDlgTagEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	char sz[8];
	int n;
	int i;

	CComboBox * pComboValues = (CComboBox *)
		GetDlgItem (IDC_CVALUE);

	if (pComboValues)
	{
		for (n=0; n<255; n++)	{
			wsprintf(sz, "%d", n);
			i= pComboValues->AddString (sz);
		}

		pComboValues->SetCurSel(m_nValue);
	}
	else
	{
		OutputDebugString("Combo not valid\n");
	}

	CComboBox * pComboName = (CComboBox *)
		GetDlgItem (IDC_ENAME);

	if (pComboName && m_ppChoices)
	{
		for (i=0; m_ppChoices[i]; i++)
		{
			n= pComboName->AddString (m_ppChoices[i]);
		}
	}

	CComboBox * pComboContent = (CComboBox *)
		GetDlgItem (IDC_ECONTENT);

	if (pComboContent && m_ppContent)
	{
		for (i=0; m_ppContent[i]; i++)
		{
			n= pComboContent->AddString (m_ppContent[i]);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

