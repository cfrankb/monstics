// DlgDescription.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "DlgDescription.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDescription dialog

CDlgDescription::CDlgDescription(CTable *pTable, CWnd* pParent)
:CDialog(CDlgDescription::IDD, pParent)
{

    m_pTable = pTable;

	//{{AFX_DATA_INIT(CDlgDescription)
	m_strDescription = _T("");
	//}}AFX_DATA_INIT   
}                              

void CDlgDescription::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDescription)
	DDX_Text(pDX, IDC_EDESCRIPTION, m_strDescription);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgDescription, CDialog)
	//{{AFX_MSG_MAP(CDlgDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDescription message handlers

BOOL CDlgDescription::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    CWnd *pWnd = GetDlgItem(IDC_EDESCRIPTION);
    if (pWnd)
    {
        ((CEdit*) pWnd)->SetLimitText(MAX_TB_INFO);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
