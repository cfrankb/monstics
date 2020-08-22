// DlgMoveLevel.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgMoveLevel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMoveLevel dialog


CDlgMoveLevel::CDlgMoveLevel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMoveLevel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMoveLevel)
	m_nInsertMode = -1;
	m_nTarget = -1;
	//}}AFX_DATA_INIT
}


void CDlgMoveLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMoveLevel)
	DDX_Radio(pDX, IDC_CBEFORE, m_nInsertMode);
	DDX_LBIndex(pDX, IDC_LISTLEVELS, m_nTarget);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMoveLevel, CDialog)
	//{{AFX_MSG_MAP(CDlgMoveLevel)
	ON_LBN_DBLCLK(IDC_LISTLEVELS, OnDblclkListlevels)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMoveLevel message handlers

BOOL CDlgMoveLevel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	int x;
	CGameFile3 & game = m_pDoc->m_game3;

	CListBox *pListBox = (CListBox *)GetDlgItem (IDC_LISTLEVELS);
	if (pListBox!=NULL) {

		for (x=0; x<game.GetSize(); x++)
		{
			CScriptArray & script = * game.m_arrScripts[x];
			CString str;
			str.Format ("Level %d - %c%s%c",
				x+1,  34, script.m_strName, 34);
			pListBox->AddString(str);
		}

		pListBox->SetCurSel(0);
	}

	CButton *pCBefore = (CButton *)GetDlgItem(IDC_CBEFORE);
	if (pCBefore)
		pCBefore->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMoveLevel::OnDblclkListlevels() 
{
	// TODO: Add your control notification handler code here
	
}
