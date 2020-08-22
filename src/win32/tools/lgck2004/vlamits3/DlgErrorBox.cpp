// DlgErrorBox.cpp : implementation file
//

#include "stdafx.h"
#include "vlamits3.h"
#include "DlgErrorBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgErrorBox dialog


CDlgErrorBox::CDlgErrorBox(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgErrorBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgErrorBox)
	m_strText = _T("");
	//}}AFX_DATA_INIT
}


void CDlgErrorBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgErrorBox)
	DDX_Text(pDX, IDC_TEXT, m_strText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgErrorBox, CDialog)
	//{{AFX_MSG_MAP(CDlgErrorBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgErrorBox message handlers

BOOL CDlgErrorBox::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
