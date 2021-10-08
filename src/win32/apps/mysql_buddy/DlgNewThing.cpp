// DlgNewTable.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "DlgNewThing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewThing dialog


CDlgNewThing::CDlgNewThing(char *sz)
	: CDialog(CDlgNewThing::IDD, NULL)
{
	//{{AFX_DATA_INIT(CDlgNewThing)
	m_strName = _T("");
	//}}AFX_DATA_INIT

	strcpy(m_szTitle, sz);
}


void CDlgNewThing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewThing)
	DDX_Text(pDX, IDC_ENAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewThing, CDialog)
	//{{AFX_MSG_MAP(CDlgNewThing)
	ON_EN_CHANGE(IDC_ENAME, OnChangeEname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewThing message handlers

void CDlgNewThing::UpdateButtons()
{
	CWnd *pEdit = GetDlgItem(IDC_ENAME);
	CWnd *pButton = GetDlgItem(IDOK);

	if (pEdit && pButton)
	{
		CString str;
		pEdit->GetWindowText(str);
		pButton->EnableWindow(str!="");
	}
}

void CDlgNewThing::OnChangeEname() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();	
}

BOOL CDlgNewThing::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CWnd *pEdit = GetDlgItem(IDC_ENAME);
	if (pEdit)
	{
		if (m_strName!="")
		{
			pEdit->SetWindowText(m_strName);
		}
	}

	UpdateButtons();	

	SetWindowText(m_szTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNewThing::SetName(CString & str)
{
	m_strName = str;
}

void CDlgNewThing::SetName(char *sz)
{
	SetName(CString(sz));
}
