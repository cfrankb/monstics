// DlgRun.cpp : implementation file
//

#include "stdafx.h"
#include "progman32.h"
#include "DlgRun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRun dialog


CDlgRun::CDlgRun(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRun::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRun)
	m_bRunMinimize = FALSE;
	m_strCommandLine = _T("");
	//}}AFX_DATA_INIT
}


void CDlgRun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRun)
	DDX_Check(pDX, IDC_CRUNMINIMIZE, m_bRunMinimize);
	DDX_Text(pDX, IDC_ECOMMANDLINE, m_strCommandLine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRun, CDialog)
	//{{AFX_MSG_MAP(CDlgRun)
	ON_BN_CLICKED(IDC_BSEARCH, OnBsearch)
	ON_EN_CHANGE(IDC_ECOMMANDLINE, OnChangeEcommandline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRun message handlers

void CDlgRun::OnBsearch() 
{
	// TODO: Add your control notification handler code here

	CString strFilesFilter =
        "Programmes|*.exe;*.pif;*.com;*.bat|"\
        "Tous (*.*)|*.*|"\
        "|";

    CFileDialog dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY , 
            strFilesFilter,  this ) ;

    dlg.m_ofn.lpstrTitle = "Parcourir"; 
    
    if (dlg.DoModal()==IDOK)
    {
        CWnd *pWnd = GetDlgItem(IDC_ECOMMANDLINE);
        if (pWnd)
        {
            pWnd->SetWindowText(dlg.GetPathName());
        }
    }

    UpdateButtons();

}

void CDlgRun::UpdateButtons()
{
     CWnd *pText = GetDlgItem(IDC_ECOMMANDLINE);
     CWnd *pOK = GetDlgItem(IDOK);
     if (pText && pOK)
     {
         CString str;
         pText->GetWindowText(str);
         pOK->EnableWindow(str!="");
     }
}

BOOL CDlgRun::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    UpdateButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRun::OnChangeEcommandline() 
{
	// TODO: Add your control notification handler code here
    UpdateButtons();	
}
