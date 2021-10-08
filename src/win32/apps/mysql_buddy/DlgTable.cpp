// DlgTable.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "DlgTable.h"
#include "DlgField.h"
#include "DlgSQL.h"
#include "DlgNewThing.h"
#include "SQLMother.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char *g_arrTypes[];

/////////////////////////////////////////////////////////////////////////////
// CDlgTable dialog


CDlgTable::CDlgTable(CSQLMother *p, CDocument *pDoc, int i)
	: CDialog(CDlgTable::IDD, NULL)
{
	//{{AFX_DATA_INIT(CDlgTable)
	//}}AFX_DATA_INIT

	//m_pTable = p;
	m_pMother = p;
	m_pDoc = pDoc;
	m_nDefault = i;
}


void CDlgTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTable)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTable, CDialog)
	//{{AFX_MSG_MAP(CDlgTable)
	ON_BN_CLICKED(IDC_BADD, OnBadd)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	ON_BN_CLICKED(IDC_BEDIT, OnBedit)
	ON_LBN_SELCHANGE(IDC_LISTBOX, OnSelchangeListbox)
	ON_LBN_DBLCLK(IDC_LISTBOX, OnDblclkListbox)
	ON_EN_CHANGE(IDC_ENAME, OnChangeEname)
	ON_BN_CLICKED(IDC_BSQL, OnBsql)
	ON_BN_CLICKED(IDC_BNEW, OnBnew)
	ON_CBN_CLOSEUP(IDC_CBSWITCH, OnCloseupCbswitch)
	ON_CBN_SELCHANGE(IDC_CBSWITCH, OnSelchangeCbswitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTable message handlers

void CDlgTable::OnBadd() 
{
	// TODO: Add your control notification handler code here

	CTable *pTable = GetCurrTable();
	if (!pTable)
	{
		OnNewTable();
		return ;
	}

	CField *p = (CField *) malloc(sizeof(CField));
	if (!p)
	{
		char szText[128];
		wsprintf(szText, "Allocation failure\n");
		OutputDebugString(szText);	
		return;
	}

	p->Init();
	
	CDlgField dlg(p);
	if (dlg.DoModal()==IDOK)
	{
		SaveField(p, dlg);
		pTable->Add(p);

		CListBox * pListBox = (CListBox *)GetDlgItem(IDC_LISTBOX);
		if (pListBox)
		{
			char szTemp[256];
			FormatField(p, szTemp);
			pListBox->AddString(szTemp);
			pListBox->SetCurSel(pTable->GetSize()-1);
			UpdateButtons();
		}
	}
	else
	{
		free(p);
	}
}

void CDlgTable::OnBdelete() 
{
	// TODO: Add your control notification handler code here
	CListBox * pListBox = (CListBox *)GetDlgItem(IDC_LISTBOX);
	CTable *pTable = GetCurrTable();
	if (pListBox && pTable)
	{
		int i = pListBox->GetCurSel();
		if ( (i != -1) && 
			(AfxMessageBox("Delete field?\nConfirm?", MB_YESNO)==IDYES))
		{
			pTable->RemoveAt(i);
			pListBox->DeleteString(i);
			m_pDoc->SetModifiedFlag(TRUE);

			int nSize = pTable->GetSize();
			if (i<=nSize)
			{
				pListBox->SetCurSel(i);
			}
			else
			{
				pListBox->SetCurSel(i-1);
			}

			UpdateButtons();
		}
	}
}

void CDlgTable::OnBedit() 
{
	// TODO: Add your control notification handler code here

	CTable *pTable = GetCurrTable();
	if (!pTable)
	{
		return ;
	}

	CListBox * pListBox = (CListBox *)GetDlgItem(IDC_LISTBOX);
	if (pListBox)
	{
		int i = pListBox->GetCurSel();
		CTable & table = (*pTable);
		CField *p = table[i];
		if (p)
		{
			CDlgField dlg(p);
			//dlg.m_nSize = p->m_nSize ;

			if (dlg.DoModal()==IDOK)
			{
				SaveField(p, dlg);
				pListBox->DeleteString(i);
				//pListBox->InsertString(i, p->m_szName);
				char szTemp[256];
				FormatField(p, szTemp);
				pListBox->InsertString(i, szTemp);
				pListBox->SetCurSel(i);
				UpdateButtons();
			}
		}
		else
		{
			char szText[128];
			wsprintf(szText, "Cannot access index %d in table\n", i);
			OutputDebugString(szText);	
		}
	}	
}

void CDlgTable::OnSelchangeListbox() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();	
}

void CDlgTable::OnDblclkListbox() 
{
	// TODO: Add your control notification handler code here
	OnBedit();	
}

void CDlgTable::SaveField(CField *pField, CDlgField & dlg)
{
	CField temp;
	memcpy(&temp, pField, sizeof(CField));

	pField->m_nType = dlg.m_nType;
	pField->m_bPrimary = dlg.m_bPrimary;
	pField->m_bNotNull = dlg.m_bNotNull;
	pField->m_bAuto = dlg.m_bAuto;
	pField->m_bKey = dlg.m_bKey;
	pField->m_bUnique = dlg.m_bUnique;
	pField->m_bUnsigned = dlg.m_bUnsigned;

	strcpy(pField->m_szName, dlg.m_strName.GetBuffer(1));
	strcpy(pField->m_szArg, dlg.m_strArg.GetBuffer(1));
	strcpy(pField->m_szDefault, dlg.m_strDefault.GetBuffer(1));
	strcpy(pField->m_szInfo, dlg.m_strInfo.GetBuffer(1));

	if (memcmp(&temp, pField, sizeof(CField)))
	{
		m_pDoc->SetModifiedFlag(TRUE);
	}
}

void CDlgTable::UpdateButtons()
{
	CWnd *pWnd;

	CListBox * pListBox = (CListBox *) GetDlgItem(IDC_LISTBOX);

	if (pListBox)
	{
		int i = pListBox->GetCurSel();

		BOOL bEnabled = (i != -1) ;

		if (bEnabled)
		{
			CComboBox  * pComboBox = (CComboBox*) 
				GetDlgItem(IDC_CBSWITCH);

			if (pComboBox)
			{
				i = pComboBox->GetCurSel();
				bEnabled = (i != -1);
			}
		}

		pWnd = GetDlgItem(IDC_BEDIT);
		if (pWnd)
		{
			pWnd->EnableWindow(bEnabled);
		}

		pWnd = GetDlgItem(IDC_BDELETE);
		if (pWnd)
		{
			pWnd->EnableWindow(bEnabled);
		}	

		pWnd = GetDlgItem(IDC_BSQL);
		if (pWnd)
		{
			pWnd->EnableWindow(bEnabled);
		}

	}
}

BOOL CDlgTable::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	FillComboTables();

	CComboBox  * pComboBox = (CComboBox*) 
		GetDlgItem(IDC_CBSWITCH);

	if (m_pMother && pComboBox)
	{
		CSQLMother & mother = (* m_pMother);

		if (m_pMother->GetSize())
		{
			CTable *pTable = mother[m_nDefault];
			//if ( (m_nDefault>=0) && (m_nDefault<m_pMother->GetSize()))
			if (pTable)
			{
				pComboBox->SetCurSel(m_nDefault);
				FillBox(pTable);

				CListBox * pListBox = (CListBox *)GetDlgItem(IDC_LISTBOX);
				if (pListBox && pTable->GetSize())
				{
					pListBox->SetCurSel(0);
				}
			}
		}
	}

	UpdateButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTable::OnChangeEname() 
{
	// TODO: Add your control notification handler code here
}

void CDlgTable::FormatField(CField *p, char *szTemp)
{
	p->FormatField(szTemp);
}

void CDlgTable::OnBsql() 
{
	// TODO: Add your control notification handler code here

	CTable *pTable = GetCurrTable();
	if (!pTable)
	{
		return ;
	}

	CWnd *pWnd = GetDlgItem(IDC_ENAME);

	if (pWnd)
	{
		CString str;
		pWnd->GetWindowText(str);
		strcpy(pTable->m_szName, str.GetBuffer(1));
	}

	CDlgSQL dlg(pTable);
	dlg.DoModal();
}

void CDlgTable::FillBox(CTable * pTable)
{
	CListBox * pListBox = (CListBox *)GetDlgItem(IDC_LISTBOX);
	if (pListBox && pTable)
	{
		pListBox->ResetContent();
		CTable & table = (* pTable); 

		for (int i=0; i<table.GetSize(); i++)
		{
			CField *p = table[i];
			if (p)
			{
				char szTemp[256];
				FormatField(p, szTemp);
				pListBox->AddString(szTemp);
			}
		}
	}
}

CTable * CDlgTable::GetCurrTable()
{
	CComboBox  * pComboBox = (CComboBox*) 
		GetDlgItem(IDC_CBSWITCH);

	if (pComboBox)
	{
		int i = pComboBox->GetCurSel();
		if (i == -1)
		{
			return NULL;
		}
		else
		{
			CSQLMother & mother = (* m_pMother);
			return mother[i];
		}
	}
	else
	{
		return NULL;
	}
}

void CDlgTable::OnBnew() 
{
	// TODO: Add your control notification handler code here
	OnNewTable();
}

void CDlgTable::FillComboTables()
{
	CComboBox  * pComboBox = (CComboBox*) 
		GetDlgItem(IDC_CBSWITCH);

	if (pComboBox)
	{
		CSQLMother & mother = (*m_pMother);

		for (int i=0; i<mother.GetSize(); i++)
		{
			CTable * pTable = mother[i];
			if (pTable)
			{
				pComboBox->AddString(pTable->m_szName);
			}
		}
	}
}

void CDlgTable::OnCloseupCbswitch() 
{
	// TODO: Add your control notification handler code here
	OnChangeTable();
}

void CDlgTable::OnNewTable()
{
	CDlgNewThing dlg("New table");

	CSQLMother & mother = (*m_pMother);

	if (dlg.DoModal()==IDOK)
	{
		CTable *pTable = (CTable*) malloc(sizeof(CTable));
		pTable->Init();
		strcpy(pTable->m_szName, dlg.m_strName.GetBuffer(1));
		m_pMother->Add(pTable)	;
		m_pDoc->SetModifiedFlag(TRUE); // modified flag

		CComboBox  * pComboBox = (CComboBox*) 
			GetDlgItem(IDC_CBSWITCH);

		if (pComboBox)
		{
			int i = m_pMother->GetSize()-1;
			pComboBox->AddString(pTable->m_szName);
			pComboBox->SetCurSel(i);
			FillBox(mother[i]);
		}
	}
}

void CDlgTable::OnSelchangeCbswitch() 
{
	// TODO: Add your control notification handler code here
	OnChangeTable();	
}

void CDlgTable::OnChangeTable()
{
	CTable *pTable = GetCurrTable();
	if (pTable)	
	{
		FillBox(pTable);

		CListBox * pListBox = (CListBox *)GetDlgItem(IDC_LISTBOX);
		if (pListBox && pTable->GetSize())
		{
			pListBox->SetCurSel(0);
		}
	}			

	UpdateButtons();
}
							   