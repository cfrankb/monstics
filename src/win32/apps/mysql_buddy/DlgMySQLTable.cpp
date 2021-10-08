// DlgMySQLTable.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "DlgMySQLTable.h"
#include "SQLCmd.h"
#include "DlgSQL.h"
#include "DlgField.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMySQLTable dialog

CDlgMySQLTable::CDlgMySQLTable(CSQLMother *pMother, CWnd *pParent, char *szDB, char *szTable)
	: CDialog(CDlgMySQLTable::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMySQLTable)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pMother = pMother;
	strcpy(m_szDB, szDB);
	strcpy(m_szTable, szTable);

	m_arrTables.Init();
	m_arrFields.Init();
}

void CDlgMySQLTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMySQLTable)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMySQLTable, CDialog)
	//{{AFX_MSG_MAP(CDlgMySQLTable)
	ON_CBN_SELCHANGE(IDC_CBSWITCH, OnSelchangeCbswitch)
	ON_LBN_SELCHANGE(IDC_LISTBOX, OnSelchangeListbox)
	ON_LBN_DBLCLK(IDC_LISTBOX, OnDblclkListbox)
	ON_BN_CLICKED(IDC_BADD, OnBadd)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	ON_BN_CLICKED(IDC_BEDIT, OnBedit)
	ON_BN_CLICKED(IDC_BNEW, OnBnew)
	ON_BN_CLICKED(IDC_BSQL, OnBsql)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMySQLTable message handlers

void CDlgMySQLTable::OnSelchangeCbswitch() 
{
	// TODO: Add your control notification handler code here
	//FillCombo();
	FillList();

	UpdateButtons();
}

BOOL CDlgMySQLTable::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetStatus("Connecting...");
	FillCombo();
	FillList();
	
	this->GetParent()->SendMessage(WM_USER+1, (int)" ", 0);

	UpdateButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMySQLTable::OnSelchangeListbox() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();	
}

void CDlgMySQLTable::OnDblclkListbox() 
{
	// TODO: Add your control notification handler code here
	OnBedit();
}

void CDlgMySQLTable::OnBadd() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgMySQLTable::OnBdelete() 
{
	// TODO: Add your control notification handler code here
	if (GetCurField())	
	{
	}
}

void CDlgMySQLTable::OnBedit() 
{
	// TODO: Add your control notification handler code here
	if (GetCurField())	
	{
		int i = GetCurFieldId();
		CDlgField dlg(m_table[i]);
		if (dlg.DoModal()==IDOK)
		{
		}
	}
}

void CDlgMySQLTable::OnBnew() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgMySQLTable::OnBsql() 
{
	// TODO: Add your control notification handler code here
	CDlgSQL dlg(&m_table);
	if (dlg.DoModal()==IDOK)
	{
		// IDOK
	}
}

BOOL CDlgMySQLTable::FillCombo()
{
	CSQLMother & mother = (*m_pMother);
	int i;
	
	SetStatus ("Connecting...");	

	MYSQL_RES *result;
	CSQLCmd cmd(m_pMother);

	if (cmd.Connect())
	{
		if (mysql_select_db(cmd.GetMySQL(), m_szDB))
        {
			SetStatus ("Failed to select DB");	
			return FALSE;
        }

		if (!(result=mysql_list_tables(cmd.GetMySQL(),0)))
		{
			SetStatus ("Failed to obtain table list...");	
			return FALSE;
		}

		MYSQL_ROW row;	
		CComboBox * p = (CComboBox*) GetDlgItem(IDC_CBSWITCH);
		if (p)
		{
			p->ResetContent();
		}

		m_arrTables.Forget();
		for (i=0;(row=mysql_fetch_row(result));i++)
		{
			if (p)
			{
				p->AddString(*row);
				char *t = (char*)malloc(strlen(*row)+1);
				strcpy(t, *row);
				m_arrTables.Add(t);
			}			
		}

		mysql_free_result(result);

		SetStatus ("Ready.");	  
		UpdateButtons();
		return TRUE;

	}
	else
	{
		SetStatus ("Failed to connect to database!");	
		return FALSE;
}

}

BOOL CDlgMySQLTable::FillList()
{
	char *szTable;

	CListBox * p = (CListBox*) GetDlgItem(IDC_LISTBOX);
	CComboBox * t = (CComboBox*) GetDlgItem(IDC_CBSWITCH);
	if (t && m_arrTables.GetSize())
	{
		int i = t->GetCurSel() ;
		if (i==-1)
		{
			t->SetCurSel(0);
			szTable = m_arrTables[0];
		}
		else
		{
			szTable = m_arrTables[i];
		}
	}
	else
	{
		if (p)
		{
			p->ResetContent();
		}
		UpdateButtons();
		//SetStatus ("Internal error");	
		OutputDebugString("Internal error[1]\n");
		return FALSE;
	}

	CSQLMother & mother = (*m_pMother);
	int i; 

	SetStatus ("Connecting...");	

	MYSQL_RES *result;
	CSQLCmd cmd(m_pMother);
	if (cmd.Connect())
	{
		if (mysql_select_db(cmd.GetMySQL(), m_szDB))
	    {
			SetStatus ("Failed to select DB");	
			return FALSE;
        }

		CString strSQL; 
		//strSQL.Format("SHOW FIELDS FROM %s;",
		//	szTable);
		strSQL.Format("SELECT * FROM %s;",
			szTable);

        if ( mysql_query(cmd.GetMySQL(),strSQL)==0 )
        {
			//MYSQL_ROW row;	
			if (p)
			{
				p->ResetContent();
			}

			m_arrFields.Forget();
			m_table.Forget();
			strcpy(m_table.m_szName, szTable);

			MYSQL *pSQL = cmd.GetMySQL();
            if ((result=mysql_store_result(cmd.GetMySQL())))
	        {
			
				MYSQL_FIELD *field;

				//for (i=0;(row=mysql_fetch_row(result));i++)
				for (i=0; i < (int)result->field_count; i++)
				{
					field=mysql_fetch_field(result);

					int a;
					a ++;

					if (p)
					{		
						char szTemp[256];

						CField *pField = (CField*) malloc(sizeof(CField));
						pField->Init(field);
						pField->FormatField(szTemp);
						m_table.Add(pField);
						
						p->AddString(szTemp);

						char *t = (char*)malloc(strlen(field->name)+1);
						strcpy(t, field->name);
						m_arrFields.Add(t);
					}			
				}
	
				mysql_free_result(result);
		
				SetStatus ("Ready.");	  
				UpdateButtons();
				return TRUE;

			}
			else
			{
				SetStatus("Couldn't store results!");
				return FALSE;
			}
		}
		else
		{
			SetStatus("Query failed!");
			return FALSE;
		}
	}
	else // connection failed
	{
		SetStatus ("Failed to connect to database!");	
		return FALSE;
	}
}

void CDlgMySQLTable::SetStatus(char *sz)
{
	CWnd *pWnd = GetDlgItem(IDC_STATICTEXT);
	if (pWnd)
	{
		pWnd->SetWindowText(sz);
	}
}

void CDlgMySQLTable::UpdateButtons()
{
	CWnd *p;
	BOOL bEnable ;
		
	bEnable = (BOOL) GetCurField();
	p = GetDlgItem(IDC_BEDIT);
	if (p)
	{
		p -> EnableWindow(bEnable);
	}

	p = GetDlgItem(IDC_BDELETE);
	if (p)
	{
		p -> EnableWindow(bEnable);
	}

	bEnable = (BOOL) GetCurTableId()!=-1;

	p = GetDlgItem(IDC_BSQL);
	if (p)
	{
		p -> EnableWindow(bEnable);
	}
	
}

char * CDlgMySQLTable::GetCurField()
{
	CListBox * p = (CListBox*) GetDlgItem(IDC_LISTBOX);
	if (p)
	{
		int i = p->GetCurSel();
		if (i!=-1)
		{
			return m_arrFields[i];
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

int CDlgMySQLTable::GetCurFieldId()
{
	CListBox * p = (CListBox*) GetDlgItem(IDC_LISTBOX);
	if (p)
	{
		int i = p->GetCurSel();
		return i;
	}
	else
	{
		return -1;
	}
}

int CDlgMySQLTable::GetCurTableId()
{
	CComboBox * p = (CComboBox*) GetDlgItem(IDC_CBSWITCH);
	if (p)
	{
		int i = p->GetCurSel();
		return i;
	}
	else
	{
		return -1;
	}
}
