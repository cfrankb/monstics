// DlgSQL.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "DlgSQL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSQL dialog


CDlgSQL::CDlgSQL(CTable *pTable)
	: CDialog(CDlgSQL::IDD, NULL)
{
	//{{AFX_DATA_INIT(CDlgSQL)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	pTable->ProcessSQL(m_strSQL);
}


void CDlgSQL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSQL)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSQL, CDialog)
	//{{AFX_MSG_MAP(CDlgSQL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSQL message handlers

BOOL CDlgSQL::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CWnd * pWnd = GetDlgItem(IDC_ETEXT);
	if (pWnd)
	{
		pWnd->SetWindowText(m_strSQL);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
