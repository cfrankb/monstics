// DlgSelectEpisode.cpp : implementation file
//

#include "stdafx.h"
#include "vlamits3.h"
#include "DlgSelectEpisode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectEpisode dialog


CDlgSelectEpisode::CDlgSelectEpisode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectEpisode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelectEpisode)
	m_nEpisode = -1;
	//}}AFX_DATA_INIT
}


void CDlgSelectEpisode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectEpisode)
	DDX_LBIndex(pDX, IDC_LIST1, m_nEpisode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectEpisode, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectEpisode)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectEpisode message handlers

BOOL CDlgSelectEpisode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    CListBox *pList = (CListBox*) GetDlgItem(IDC_LIST1);
    if (pList)
    {
        int i=0;
        for (i=0; i<m_arrEpisodes.GetSize(); i++)
        {
            pList->AddString(m_arrEpisodes[i]);
        }

        pList->SetCurSel(0);
    }

    UpdateButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelectEpisode::UpdateButtons()
{
    CWnd *pOK = GetDlgItem(IDOK);
    CListBox *pList = (CListBox*) GetDlgItem(IDC_LIST1);
    if (pOK && pList)
    {
        pOK->EnableWindow(pList->GetCurSel()!=-1);
    }

}

void CDlgSelectEpisode::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
    OnOK();	
}
