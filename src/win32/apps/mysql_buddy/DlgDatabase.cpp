// DlgDatabase.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "DlgDatabase.h"
#include "DlgNewThing.h"
#include "DlgSQL.h"
#include "DlgTable.h"
#include "DlgMySQLTable.h"
#include "sqlcmd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char g_szText[512];

#define MYDEBUG(_INT_) wsprintf(g_szText, "\nError code: %d\n\n", _INT_); \
	OutputDebugString(g_szText);

/////////////////////////////////////////////////////////////////////////////
// CDlgDatabase dialog

CDlgDatabase::CDlgDatabase(CSQLMother *p, CDocument *pDoc)
	: CDialog(CDlgDatabase::IDD, NULL)
{
	//{{AFX_DATA_INIT(CDlgDatabase)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pMother = p;
	m_arrMySQLDB.Init();
	m_arrMySQLTables.Init();
	m_pDoc = pDoc;
}

CDlgDatabase::~CDlgDatabase()
{
	m_arrMySQLDB.Forget();
	m_arrMySQLTables.Forget();
}

void CDlgDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDatabase)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDatabase, CDialog)
	//{{AFX_MSG_MAP(CDlgDatabase)
	ON_CBN_CLOSEUP(IDC_CBLOCAL, OnCloseupCblocal)
	ON_CBN_SELCHANGE(IDC_CBLOCAL, OnSelchangeCblocal)
	ON_CBN_CLOSEUP(IDC_CBMYSQL, OnCloseupCbmysql)
	ON_CBN_SELCHANGE(IDC_CBMYSQL, OnSelchangeCbmysql)
	ON_BN_CLICKED(IDC_BDROPMYSQLDB, OnBdropmysqldb)
	ON_BN_CLICKED(IDC_BDROPTABLELOCAL, OnBdroptablelocal)
	ON_BN_CLICKED(IDC_BDROPTABLEMYSQL, OnBdroptablemysql)
	ON_BN_CLICKED(IDC_BNEWMYSQLDB, OnBnewmysqldb)
	ON_BN_CLICKED(IDC_BTOMYSQL, OnBtomysql)
	ON_LBN_SELCHANGE(IDC_LLOCAL, OnSelchangeLlocal)
	ON_LBN_SELCHANGE(IDC_LMYSQL, OnSelchangeLmysql)
	ON_BN_CLICKED(IDC_BSHOWSQL, OnBshowsql)
	ON_LBN_DBLCLK(IDC_LLOCAL, OnDblclkLlocal)
	ON_BN_CLICKED(IDC_BRENAME, OnBrename)
	ON_LBN_DBLCLK(IDC_LMYSQL, OnDblclkLmysql)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDatabase message handlers

void CDlgDatabase::SetStatus(char *szText)
{
	CWnd *pWnd = GetDlgItem(IDC_STATICTEXT);
	if (pWnd)
	{
		pWnd->SetWindowText(szText);
	}
}

BOOL CDlgDatabase::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// Local side

	CComboBox *p = (CComboBox*) GetDlgItem(IDC_CBLOCAL);
	if (p)
	{
		p->AddString("(default)");
		p->SetCurSel(0);
	}

	FillListLocal();

	// MySQL side

	FillComboMySQL();

	p = (CComboBox*) GetDlgItem(IDC_CBMYSQL);
	if (p)
	{
		p->SetCurSel(0);
	}

	OnChangeMySQLDB();
	UpdateButtons();

	AfxGetMainWnd()->SendMessage(WM_USER+1, (int)" ", 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDatabase::OnCloseupCblocal() 
{
	// TODO: Add your control notification handler code here
	CDlgTable dlg(m_pMother, m_pDoc, 0);			
	dlg.DoModal();
	FillListLocal();

	CListBox * 	p = (CListBox*) GetDlgItem(IDC_LLOCAL);
	if (p)
	{
		p->SetCurSel(0);
	}

	UpdateButtons();
}

void CDlgDatabase::OnSelchangeCblocal() 
{
	// TODO: Add your control notification handler code here
}

void CDlgDatabase::OnCloseupCbmysql() 
{
	// TODO: Add your control notification handler code here
	OnChangeMySQLDB();	
	UpdateButtons();
}

void CDlgDatabase::OnSelchangeCbmysql() 
{
	// TODO: Add your control notification handler code here
	OnChangeMySQLDB();
	UpdateButtons();
}

BOOL CDlgDatabase::FillComboMySQL()
{
	CSQLMother & mother = (*m_pMother);
	int i;
	
	SetStatus ("Connecting...");	

	MYSQL_RES *result;
	CSQLCmd cmd(m_pMother);

	if (cmd.Connect())
	{
		if (!(result=mysql_list_dbs(cmd.GetMySQL(),0)))
		{
		}

		MYSQL_ROW row;	
		CComboBox * p = (CComboBox*) GetDlgItem(IDC_CBMYSQL);
		if (p)
		{
			p->ResetContent();
		}

		m_arrMySQLDB.Forget();
		for (i=0;(row=mysql_fetch_row(result));i++)
		{
			if (p)
			{
				p->AddString(*row);
				char *t = (char*)malloc(strlen(*row)+1);
				strcpy(t, *row);
				m_arrMySQLDB.Add(t);
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

BOOL CDlgDatabase::FillListMySQL()
{
	char *szDB;

	CListBox * p = (CListBox*) GetDlgItem(IDC_LMYSQL);
	CComboBox * t = (CComboBox*) GetDlgItem(IDC_CBMYSQL);
	if (t && m_arrMySQLDB.GetSize())
	{
		int i = t->GetCurSel() ;
		if (i==-1)
		{
			t->SetCurSel(0);
			szDB = m_arrMySQLDB[0];
		}
		else
		{
			szDB = m_arrMySQLDB[i];
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
		if (mysql_select_db(cmd.GetMySQL(), szDB))
        {
				SetStatus ("Failed to select DB");	
				return TRUE;
        }

		if (!(result=mysql_list_tables(cmd.GetMySQL(),0)))
		{
		}

		MYSQL_ROW row;	
		if (p)
		{
			p->ResetContent();
		}

		m_arrMySQLTables.Forget();
		for (i=0;(row=mysql_fetch_row(result));i++)
		{
			if (p)
			{
				p->AddString(*row);
				char *t = (char*)malloc(strlen(*row)+1);
				strcpy(t, *row);
				m_arrMySQLTables.Add(t);
			}		 
		}

		mysql_free_result(result);

		SetStatus ("Ready.");	  
		UpdateButtons();
		return TRUE;

	}
	else // connection failed
	{
		SetStatus ("Failed to connect to database!");	
		return FALSE;
	}
}

BOOL CDlgDatabase::OnChangeMySQLDB()
{
	CComboBox * p = (CComboBox*) GetDlgItem(IDC_CBMYSQL);
	if (p)
	{
		int i = p -> GetCurSel();
		if (i != -1)
		{			
			FillListMySQL();
		}
		else
		{
			CListBox * 	t = (CListBox*) GetDlgItem(IDC_LMYSQL);	
			if (t)
			{
				t->ResetContent();
			}
		}
	}

	//UpdateButtons();
	return TRUE;
}

BOOL CDlgDatabase::FillListLocal()
{
	int i=0;

	CSQLMother & mother = (*m_pMother);
	CListBox * 	p = (CListBox*) GetDlgItem(IDC_LLOCAL);
	if (p)
	{
		p->ResetContent();
	}

	for (i=0; i < mother.GetSize(); i++)
	{
		if (p)
		{
			p->AddString(mother[i]->m_szName);
		}
	}

	//UpdateButtons();
	return TRUE;
}

void CDlgDatabase::OnBdropmysqldb() 
{
	// TODO: Add your control notification handler code here
	int i = -1;

	CComboBox * p = (CComboBox*) GetDlgItem(IDC_CBMYSQL);
	if (p)
	{
		i = p->GetCurSel();			
	}

	CSQLMother & mother = (*m_pMother);
	char *szDB = m_arrMySQLDB[i];

	char szTemp[256];
	wsprintf(szTemp, "Your are about to\ndrop a database %c%s%c\nAre you sure?", 34, szDB, 34);

	if ( (i == -1) || (AfxMessageBox(szTemp, MB_YESNO)!=IDYES))
	{
		return;
	}

	SetStatus ("Connecting...");	

	CSQLCmd cmd(m_pMother);
	if (cmd.Connect())
	{
		if (! mysql_drop_db(cmd.GetMySQL(), szDB))
		{
			// all okay
		}
		
		FillComboMySQL();
		FillListMySQL();
		UpdateButtons();

	}
	else
	{
		SetStatus("Can't connect to DB.");
	}
}

void CDlgDatabase::OnBdroptablelocal() 
{
	// TODO: Add your control notification handler code here
	int i = GetCurrLocalTableId();
	CTable *p = GetCurrLocalTable();
	if (p  && (i!=-1))
	{
		char szTemp[512];
		wsprintf(szTemp, "Remove table %c%s%c? Are you sure?",
			34, p->m_szName, 34);
		if (AfxMessageBox(szTemp, MB_YESNO)==IDYES)
		{

			CSQLMother & mother = (*m_pMother);
			mother.RemoveAt(i);

			CListBox * 	pList = (CListBox*) GetDlgItem(IDC_LLOCAL);
			pList->DeleteString(i);
			//pList->InsertString(i,p->m_szName);
			//pList->SetCurSel(i);	
			UpdateButtons();
			m_pDoc->SetModifiedFlag(TRUE);
		}
	}
}

void CDlgDatabase::OnBdroptablemysql() 
{
	// TODO: Add your control notification handler code here

	CSQLMother & mother = (*m_pMother);

	// Verify if there is a current table
	// Verify if there is a current DB
	char *szTable = GetCurrMySQLTable();
	char *szDB = GetCurrMySQLDB();	

	if ((!szTable) || (!szDB))
	{
		return;
	}

	// ask for confirmation
	char szTemp[2048];
	wsprintf(szTemp, "Your are about to\ndrop table %c%s%c\nAre you sure?",
		34, szTable, 34);

	if (AfxMessageBox(szTemp, MB_YESNO)!=IDYES)
	{
		return;
	}

	char szDrop[256];
	wsprintf(szTemp, "DROP TABLE %s;", szDrop);

	SetStatus ("Connecting...");	

	CSQLCmd cmd(m_pMother);
	if (cmd.Connect())
	{	

		if (mysql_select_db(cmd.GetMySQL(), szDB))
        {
		}

		OutputDebugString(szDrop);
		MYDEBUG(mysql_query(cmd.GetMySQL(), szDrop));	

		FillComboMySQL();
		FillListMySQL();
		UpdateButtons();

	}
	else
	{
		SetStatus("Can't connect to DB.");
	}

	wsprintf(szTemp, "DROP TABLE %s;");
}

void CDlgDatabase::OnBnewmysqldb() 
{
	// TODO: Add your control notification handler code here
	CSQLMother & mother = (*m_pMother);

	CDlgNewThing dlg("New database");
	if (dlg.DoModal()!=IDOK)
	{
		return;		
	}

	char *szDB = dlg.m_strName.GetBuffer(1);

	SetStatus ("Connecting...");	

	CSQLCmd cmd(m_pMother);
	if (cmd.Connect())
	{
		if(! mysql_create_db(cmd.GetMySQL(), szDB))
		{
			// all okay
		}

		SetStatus("Ready.");

		FillComboMySQL();
		FillListMySQL();
		UpdateButtons();

	}
	else
	{
		SetStatus("Can't connect to DB.");
	}
}

void CDlgDatabase::OnBtomysql() 
{
	// TODO: Add your control notification handler code here
	//mysql_query(MYSQL *mysql, const char *query)

	CSQLMother & mother = (*m_pMother);

	// verify if one local table is selected
	// verify if one MySQL DB is selected
	CTable* pTable = GetCurrLocalTable();
	char *szDB = GetCurrMySQLDB();	

	if ((!pTable) || (!szDB))
	{
		return;
	}

	// ask for new table name
	CDlgNewThing dlg("Name of new table");
	dlg.SetName(pTable->m_szName);
	if (dlg.DoModal()!=IDOK)
	{
		return;			
	}

	char szTemp[2048];
	char szDrop[256];

	BOOL bDrop = FALSE;

	// if destination table already exists, ask a
	// confirming before dropping.
	if (m_arrMySQLTables.GetIndexFor(dlg.m_strName)!=-1)
	{
		wsprintf(szTemp, "Table %c%s%c alread exists.\nDo you want to drop it?",
			34, dlg.m_strName.GetBuffer(1), 34);
		if (AfxMessageBox(szTemp, MB_YESNO)!=IDYES)
		{
			// user refused to drop the table
			return;
		}
		else
		{
			wsprintf(szDrop, "DROP TABLE %s;", dlg.m_strName.GetBuffer(1));
			bDrop = TRUE;
		}
	}

	// create sql code (overide the default create table
	// by specifying a new table name)
	CString str;
	pTable->ProcessSQL(str, dlg.m_strName.GetBuffer(1));
	char *pSQL = str.GetBuffer(1);

	SetStatus ("Connecting...");	
	CSQLCmd cmd(m_pMother);
	if (cmd.Connect())
	{
		if (mysql_select_db(cmd.GetMySQL(), szDB))
        {
		}

		if (bDrop)
		{
			OutputDebugString(szTemp);
			MYDEBUG(mysql_query(cmd.GetMySQL(), szDrop));		
		}
		
		OutputDebugString(pSQL);
		MYDEBUG(mysql_query(cmd.GetMySQL(), pSQL));

		dlg.m_strName.GetBuffer(1);
		SetStatus("Ready.");

		FillListMySQL();
		UpdateButtons();

	}
	else	
	{
		SetStatus("Can't connect to DB.");
	}
	
}

CTable * CDlgDatabase::GetCurrLocalTable()
{
	CListBox * 	p = (CListBox*) GetDlgItem(IDC_LLOCAL);
	if (!p)
	{
		return NULL	 ;
	}

	CSQLMother & mother = (*m_pMother);
	int i = p->GetCurSel();

	return mother[i];
}

int CDlgDatabase::GetCurrLocalTableId()
{
	CListBox * 	p = (CListBox*) GetDlgItem(IDC_LLOCAL);
	if (!p)
	{
		return -1;
	}

	int i = p->GetCurSel();

	return i;

}

char * CDlgDatabase::GetCurrMySQLTable()
{
	CListBox *  p = (CListBox*) GetDlgItem(IDC_LMYSQL);

	if (!p)
	{
		return NULL;
	}

	int i = p->GetCurSel();

	return m_arrMySQLTables[i];
}

char* CDlgDatabase::GetCurrMySQLDB()
{
	CComboBox *  p = (CComboBox*) GetDlgItem(IDC_CBMYSQL);

	if (!p)
	{
		return NULL;
	}

	int i = p->GetCurSel();

	return m_arrMySQLDB[i];
}

void CDlgDatabase::UpdateButtons()
{
	int arrStatus[]=
	{
		IDC_BDROPMYSQLDB, IDC_CBMYSQL, 0,
		IDC_BDROPTABLELOCAL, IDC_LLOCAL, 0,
		IDC_BDROPTABLEMYSQL, IDC_LMYSQL, 0,
		IDC_BNEWMYSQLDB, 0, 0,
		IDC_BRENAME, IDC_LLOCAL, 0,
		IDC_BRUNSQL, IDC_CBMYSQL, 0,
		IDC_BOPTIONS, 0, 0,
		IDC_BTOLOCAL, IDC_LMYSQL, IDC_CBLOCAL,
		IDC_BTOMYSQL, IDC_CBMYSQL, IDC_LLOCAL,
		IDC_BSHOWSQL, IDC_LLOCAL, 0,
		NULL, NULL, NULL, 
	};

	int i;

	for (i=0; arrStatus[i]; i = i + 3)
	{
		BOOL bStatus = TRUE;

		CWnd *pWnd = GetDlgItem(arrStatus[i]);
		if (pWnd)
		{
			if (arrStatus[i+1])
			{
				CListBox * p = (CListBox*)GetDlgItem(arrStatus[i+1]);
				if (p)
				{
					bStatus = bStatus && (p->GetCurSel()!=-1);
				}
				else
				{
					bStatus = FALSE;
				}
			}

			if (arrStatus[i+2])
			{
				CListBox * p = (CListBox*)GetDlgItem(arrStatus[i+2]);
				if (p)
				{
					bStatus = bStatus && (p->GetCurSel()!=-1);
				}
				else
				{
					bStatus = FALSE;
				}
			}

			pWnd->EnableWindow(bStatus);
		}
	}
}

void CDlgDatabase::OnSelchangeLlocal() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();
}

void CDlgDatabase::OnSelchangeLmysql() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();
}

void CDlgDatabase::OnBshowsql() 
{
	// TODO: Add your control notification handler code here
	CTable *pTable = GetCurrLocalTable();
	
	if (pTable)
	{
		CDlgSQL dlg(pTable);
		dlg.DoModal();
	}
}

void CDlgDatabase::OnDblclkLlocal() 
{
	// TODO: Add your control notification handler code here
	int i = GetCurrLocalTableId();
	
	if (i != -1)
	{
		CDlgTable dlg(m_pMother, m_pDoc, i);			
		dlg.DoModal();
		FillListLocal();

		CListBox * 	p = (CListBox*) GetDlgItem(IDC_LLOCAL);
		p->SetCurSel(i);

		UpdateButtons();
	}	
	else
	{
		// Should bring up IDD_TABLE but it's not working
	}
}

void CDlgDatabase::OnBrename() 
{
	// TODO: Add your control notification handler code here
	CTable *p = GetCurrLocalTable();
	int i = GetCurrLocalTableId();

	if ((p) && (i!=-1))
	{
		CDlgNewThing dlg("Rename table");
		dlg.SetName(p->m_szName);
		if (dlg.DoModal()==IDOK)
		{
			if (strcmp(p->m_szName, dlg.m_strName.GetBuffer(1)))
			{
				strcpy(p->m_szName, dlg.m_strName.GetBuffer(1));			
				CListBox * 	pList = (CListBox*) GetDlgItem(IDC_LLOCAL);
				pList->DeleteString(i);
				pList->InsertString(i,p->m_szName);
				pList->SetCurSel(i);	
				m_pDoc->SetModifiedFlag(TRUE);
			}
		}
	}
}

LRESULT CDlgDatabase::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	switch (message)
	{
		case WM_USER+1:
			SetStatus((char*)wParam);
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CDlgDatabase::OnDblclkLmysql() 
{
	// TODO: Add your control notification handler code here
	char *szDB = GetCurrMySQLDB();
	char *szTable = GetCurrMySQLTable();
	
	CDlgMySQLTable dlg(m_pMother, this, szDB, szTable);
	SetStatus("Connecting...");
	if (dlg.DoModal()==IDOK)
	{
	}
}
