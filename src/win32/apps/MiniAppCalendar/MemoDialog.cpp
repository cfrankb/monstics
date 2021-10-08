// MemoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "app.h"
#include "MemoDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemoDialog dialog


CMemoDialog::CMemoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMemoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMemoDialog)
	m_strMemo = _T("");
	//}}AFX_DATA_INIT

    m_strCaption = "Mémo du mois";

}


void CMemoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemoDialog)
	DDX_Control(pDX, IDOK, m_bOk);
	DDX_Text(pDX, IDC_EMEMO, m_strMemo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMemoDialog, CDialog)
	//{{AFX_MSG_MAP(CMemoDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoDialog message handlers

BOOL CMemoDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    SetWindowText (m_strCaption);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
