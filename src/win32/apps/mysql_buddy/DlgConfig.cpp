// DlgConfig.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "DlgConfig.h"
#include "DlgNewThing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConfig dialog


CDlgConfig::CDlgConfig(CServerArr *p, CDocument *pDoc)
	: CDialog(CDlgConfig::IDD, NULL)
{
	//{{AFX_DATA_INIT(CDlgConfig)
	m_nConfig = -1;
	//}}AFX_DATA_INIT

	m_nCurrent = p->m_nDefault;
	m_pServerArr = p;
	m_pDoc = pDoc;
}


void CDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfig)
	DDX_CBIndex(pDX, IDC_CBCONFIG, m_nConfig);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgConfig)
	ON_CBN_CLOSEUP(IDC_CBCONFIG, OnCloseupCbconfig)
	ON_CBN_SELCHANGE(IDC_CBCONFIG, OnSelchangeCbconfig)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	ON_BN_CLICKED(IDC_BDUPLICATE, OnBduplicate)
	ON_BN_CLICKED(IDC_BNEW, OnBnew)
	ON_BN_CLICKED(IDC_BRESET, OnBreset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConfig message handlers

BOOL CDlgConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateForm();
	Load();		
	UpdateButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgConfig::UpdateForm()
{
	int arrCombo[]=
	{
		IDC_CBHOST, // 0
		IDC_CBPORT,	// 1
		IDC_CBUSER,	// 2
		NULL
	};

	char *arrDefault[]=
	{
		"localhost", // 0
		"3306",	// 1
		"root",	// 2
		NULL
	};

	for (int i=0; arrCombo[i]; i++)
	{
		CComboBox *pCombo = (CComboBox *) GetDlgItem(arrCombo[i]);
		if (pCombo)
		{
			pCombo->ResetContent();
			pCombo->AddString(arrDefault[i]);
		}
	}

	CServerArr & arr = *m_pServerArr;

	CComboBox *p = (CComboBox *) GetDlgItem(IDC_CBCONFIG);
	if (p)
	{
		for (int i=0; i < arr.GetSize(); i++)
		{
			CServer & server = (*arr[i]);
			p->AddString(server.m_szServer);
		}
	}
}

void CDlgConfig::OnCloseupCbconfig() 
{
	// TODO: Add your control notification handler code here
}

void CDlgConfig::OnSelchangeCbconfig() 
{
	// TODO: Add your control notification handler code here
	CComboBox *p = (CComboBox *)GetDlgItem(IDC_CBCONFIG);	
	if (p)
	{
		if (Save())
		{
			m_pDoc->SetModifiedFlag(TRUE);
		}

		m_nCurrent = p->GetCurSel();	
		Load();
	}
}

BOOL CDlgConfig::Load()
{
	CServerArr & arr = (*m_pServerArr);
	CServer & server = (*arr[m_nCurrent]);

	int arrFields[]=
	{
		IDC_CBHOST, // 0
		IDC_CBPORT,	// 1
		IDC_CBUSER,	// 2
		IDC_EPASSWORD, // 3
		NULL
	};

	char * arrContent[]=
	{
		server.m_szHost,
		server.m_szPort,
		server.m_szUser,
		server.m_szPassword,
		NULL
	};

	CButton *m_pSavePassword = 
		(CButton*) GetDlgItem(IDC_CSAVEPASSWORD);

	if (m_pSavePassword)
	{
		m_pSavePassword->SetCheck(server.m_bSavePassword);
	}	

	for (int i=0; arrFields[i]; i++) 
	{
		CWnd *p = GetDlgItem(arrFields[i]);
		if (p)
		{
			p->SetWindowText(arrContent[i]);
		}
	}

	CComboBox *p = (CComboBox *) GetDlgItem(IDC_CBCONFIG);
	if (p)
	{
		p->SetCurSel(m_nCurrent);
	}
	
	return FALSE;
}

BOOL CDlgConfig::Save()
{
	CServerArr & arr = (*m_pServerArr);
	CServer & server = (*arr[m_nCurrent]);
	CServer temp;
	memcpy(&temp, &server, sizeof(CServer));

	int arrFields[]=
	{
		IDC_CBHOST, // 0
		IDC_CBPORT,	// 1
		IDC_CBUSER,	// 2
		IDC_EPASSWORD, // 3
		NULL
	};

	char * arrContent[]=
	{
		server.m_szHost,
		server.m_szPort,
		server.m_szUser,
		server.m_szPassword,
		NULL
	};

	CButton *m_pSavePassword = 
		(CButton*) GetDlgItem(IDC_CSAVEPASSWORD);

	if (m_pSavePassword)
	{
		server.m_bSavePassword = 
			m_pSavePassword->GetCheck();
	}	

	for (int i=0; arrFields[i]; i++) 
	{
		CWnd *p = GetDlgItem(arrFields[i]);
		if (p)
		{
			CString str;
			p->GetWindowText(str);
			strcpy(arrContent[i], str.GetBuffer(1));
		}
	}

	return memcmp(&temp, &server, sizeof(CServer));
}

void CDlgConfig::OnBdelete() 
{
	// TODO: Add your control notification handler code here

	if (AfxMessageBox("Delete current server?\nAre you sure?",
		MB_YESNO)!=IDYES)
	{
		return;
	}

	CServerArr & arr = (*m_pServerArr);
	if (arr.GetSize()>1)
	{
		CComboBox *p = (CComboBox *)GetDlgItem(IDC_CBCONFIG);	
		if (p)
		{
			Save();
			int i = p->GetCurSel();
			arr.RemoveAt(i);
			p->DeleteString(i);
			m_nCurrent = 0;
			p->SetCurSel(0);
			Load();
			UpdateButtons();

			if (m_pServerArr->m_nDefault >= 
				m_pServerArr->GetSize())
			{
				m_pServerArr->m_nDefault =
					m_pServerArr->GetSize()-1;
			}

			m_pDoc->SetModifiedFlag(TRUE);
		}		
	}
}

void CDlgConfig::OnBduplicate() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgConfig::OnBnew() 
{
	// TODO: Add your control notification handler code here
	CDlgNewThing dlg("New server");
	if (dlg.DoModal()==IDOK)
	{
		Save();

		CServer *p = (CServer*) malloc(sizeof(CServer));
		p->Init();
		strcpy(p->m_szServer, dlg.m_strName.GetBuffer(1));

		CServerArr & arr = (*m_pServerArr);
		arr.Add(p);
		m_nCurrent = arr.GetSize() -1;

		CComboBox *pCombo = (CComboBox *) GetDlgItem(IDC_CBCONFIG);
		if (pCombo)
		{
			pCombo->AddString(p->m_szServer);
		}

		Load();
		UpdateButtons();
		m_pDoc->SetModifiedFlag(TRUE);
	}
}

void CDlgConfig::OnBreset() 
{
	// TODO: Add your control notification handler code here
	Load();	
}

void CDlgConfig::OnOK() 
{
	// TODO: Add extra validation here
	CComboBox *pCombo = (CComboBox *) GetDlgItem(IDC_CBCONFIG);
	if (pCombo)
	{
		m_pServerArr->m_nDefault = m_nCurrent;
	}

	if (Save())
	{
		m_pDoc->SetModifiedFlag(TRUE);
	}
	
	CDialog::OnOK();
}

void CDlgConfig::UpdateButtons()
{
	int arrButtons[] = 
	{
		IDC_BDELETE,
		IDC_BDUPLICATE,
		IDC_BNEW,
		IDC_BRESET,
		NULL
	};

	int arrMin[] =
	{
		2,
		1,
		0,
		1,
		-1
	};

	CServerArr & arr = *m_pServerArr;

	for (int i=0; arrButtons[i]; i++)
	{
		CWnd *p = GetDlgItem(arrButtons[i]);
		if (p)
		{
			p->EnableWindow(arr.GetSize()>=arrMin[i]);
		}
	}
}

void CDlgConfig::OnCancel() 
{
	// TODO: Add extra cleanup here

	if (Save())
	{
		m_pDoc->SetModifiedFlag(TRUE);
	}

	CDialog::OnCancel();
}
