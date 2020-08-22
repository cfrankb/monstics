// DlgPasteBmp.cpp : implementation file
//

#include "stdafx.h"
#include "obl4edit.h"
#include "DlgPasteBmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPasteBmp dialog


CDlgPasteBmp::CDlgPasteBmp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasteBmp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPasteBmp)
	m_nMethod = -1;
	//}}AFX_DATA_INIT
}


void CDlgPasteBmp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPasteBmp)
	DDX_Radio(pDX, IDC_RMETHOD1, m_nMethod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPasteBmp, CDialog)
	//{{AFX_MSG_MAP(CDlgPasteBmp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPasteBmp message handlers

BOOL CDlgPasteBmp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CWnd *pRMethod3 = GetDlgItem(IDC_RMETHOD3);
	if (pRMethod3)
	{
		pRMethod3->EnableWindow(m_nBpp==8);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
