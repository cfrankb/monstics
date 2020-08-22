// DlgImageSize.cpp : implementation file
//

#include "stdafx.h"
#include "obl4edit.h"
#include "DlgImageSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImageSize dialog


CDlgImageSize::CDlgImageSize(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImageSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImageSize)
	m_nLen = 0;
	m_nHei = 0;
	m_bAll = FALSE;
	//}}AFX_DATA_INIT

	m_bShowAll = FALSE;
}


void CDlgImageSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImageSize)
	DDX_Control(pDX, IDOK, m_buttonOk);
	DDX_Control(pDX, IDCANCEL, m_buttonCancel);
	DDX_Control(pDX, IDC_SLEN, m_spinLen);
	DDX_Control(pDX, IDC_SHEI, m_spinHei);
	DDX_Text(pDX, IDC_ELEN, m_nLen);
	DDV_MinMaxUInt(pDX, m_nLen, 1, 40);
	DDX_Text(pDX, IDC_EHEI, m_nHei);
	DDV_MinMaxUInt(pDX, m_nHei, 1, 40);
	DDX_Check(pDX, IDC_CALL, m_bAll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImageSize, CDialog)
	//{{AFX_MSG_MAP(CDlgImageSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImageSize message handlers

void CDlgImageSize::UnHideAll ()
{
	m_bShowAll = TRUE;	

}

BOOL CDlgImageSize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_bShowAll)
	{
		CWnd *pWnd;
		pWnd = GetDlgItem (IDC_CALL);
		if (pWnd)
		{
			pWnd->ShowWindow(SW_SHOW);
		}	
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
