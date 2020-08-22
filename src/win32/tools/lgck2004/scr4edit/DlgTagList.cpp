// DlgTagList.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgTagList.h"
#include "DlgTagEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTagList dialog


CDlgTagList::CDlgTagList(UINT nChildIDD, char **ppChoices, char **ppContent)
	: CDialog(CDlgTagList::IDD, NULL)
{
	//{{AFX_DATA_INIT(CDlgTagList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_ppChoices = ppChoices;
	m_ppContent = ppContent;
	m_pArray = NULL;
	m_strName = "Generic - Tag dialog box";
	m_nChildIDD = nChildIDD;
}


void CDlgTagList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTagList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTagList, CDialog)
	//{{AFX_MSG_MAP(CDlgTagList)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_BADD, OnBadd)
	ON_BN_CLICKED(IDC_BEDIT, OnBedit)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTagList message handlers

BOOL CDlgTagList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CListBox *pListBox = (CListBox*) GetDlgItem (IDC_LIST);

	int n;
	for (n=0; m_pArray !=NULL && 
		n< m_pArray->GetSize(); n++)
	{
		CTagArray & array = * m_pArray;
		CTagEntry & entry = array[n];
		pListBox->AddString (entry.m_szName);
	}
	
	pListBox->SetCurSel(0);

	SetWindowText (m_strName);
	UpdateButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTagList::OnDblclkList() 
{
	// TODO: Add your control notification handler code here
	OnBedit();
}

void CDlgTagList::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();
}

void CDlgTagList::OnBadd() 
{
	// TODO: Add your control notification handler code here
	CListBox *pListBox = (CListBox*) GetDlgItem (IDC_LIST);
	
	CDlgTagEdit dlg(m_nChildIDD, m_ppChoices, m_ppContent);
	if (dlg.DoModal()==IDOK)
	{
		CTagArray & array = * m_pArray;
		CTagEntry entry;
		entry.SetName (dlg.m_strName);
		entry.SetDescription (dlg.m_strDescription);
		entry.m_nValue = dlg.m_nValue;
		array.Add (entry);

		int nIndex = pListBox->AddString(dlg.m_strName);
		if (nIndex!=-1)
			pListBox->SetCurSel(nIndex);
	}
	
}

void CDlgTagList::OnBedit() 
{
	// TODO: Add your control notification handler code here
	CListBox *pListBox = (CListBox*) GetDlgItem (IDC_LIST);
	int nIndex = pListBox->GetCurSel();

	if (nIndex>0 || m_ppChoices && nIndex>=0)
	{
		CTagArray & array = * m_pArray;
		CTagEntry & entry = array [nIndex];

		CDlgTagEdit dlg(m_nChildIDD, m_ppChoices, m_ppContent);
		dlg.m_strName = entry.m_szName;
		dlg.m_strDescription = entry.m_szDescription;
		dlg.m_nValue = entry.m_nValue;
		
		if (dlg.DoModal()==IDOK)
		{
			entry.SetName (dlg.m_strName);
			entry.SetDescription (dlg.m_strDescription);
			entry.m_nValue = dlg.m_nValue;

			pListBox->DeleteString (nIndex);
			pListBox->InsertString(nIndex, dlg.m_strName);
			pListBox->SetCurSel(nIndex);
		
		}
	}
}

void CDlgTagList::OnBdelete() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgTagList::SetTitle (const CString & string)
{
	m_strName = string;
}

void CDlgTagList::UpdateButtons ()
{
	CWnd * pWnd;
	CListBox *pListBox = (CListBox*) GetDlgItem (IDC_LIST);

	BOOL bEnabled = pListBox->GetCurSel()>0 ||
		m_ppChoices && 
		pListBox->GetCurSel()>=0;

	pWnd = GetDlgItem (IDC_BEDIT);
	if (pWnd!=NULL) 
	{
		pWnd->EnableWindow (bEnabled);
	}

	pWnd = GetDlgItem (IDC_BDELETE);
	if (pWnd!=NULL) 
	{
		pWnd->EnableWindow (bEnabled);
		pWnd->ShowWindow (m_ppChoices!=NULL);
	}
/*
	pWnd = GetDlgItem (IDC_SMOVE);
	if (pWnd!=NULL) 
	{
		pWnd->EnableWindow (bEnabled);
		pWnd->ShowWindow (m_ppChoices!=NULL);
	}
	*/
}
