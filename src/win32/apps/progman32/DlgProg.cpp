// DlgProg.cpp : implementation file
//

#include "stdafx.h"
#include "progman32.h"
#include "DlgProg.h"
#include "icondlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProg dialog


CDlgProg::CDlgProg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProg)
	m_bMinimize = FALSE;
	m_strCommandLine = _T("");
	m_strDescription = _T("");
	m_strDirectory = _T("");
	//}}AFX_DATA_INIT

    m_hIcon = NULL;
}


void CDlgProg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProg)
	DDX_Check(pDX, IDC_CMINIMIZE, m_bMinimize);
	DDX_Text(pDX, IDC_ECOMMANDLINE, m_strCommandLine);
	DDX_Text(pDX, IDC_EDESCRIPTION, m_strDescription);
	DDX_Text(pDX, IDC_EDIRECTORY, m_strDirectory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProg, CDialog)
	//{{AFX_MSG_MAP(CDlgProg)
	ON_BN_CLICKED(IDC_BSEARCH, OnBsearch)
	ON_BN_CLICKED(IDC_BICON, OnBicon)
	ON_EN_UPDATE(IDC_ECOMMANDLINE, OnUpdateEcommandline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProg message handlers

BOOL CDlgProg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    CWnd *pWnd = (CWnd*) GetDlgItem(IDC_EHOTKEY);

    if (pWnd)
    {
        CRect rect;
        pWnd->GetWindowRect(rect);
        this->ScreenToClient (&rect);      

        m_hotkey.Create(
            WS_VISIBLE | WS_CHILD  | WS_TABSTOP /*| WS_BORDER*/, 
            rect,
            this,
            IDC_EHOTKEY
            );
        
        CFont * pFont = CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
        m_hotkey.SetFont(pFont);

    }

    CStatic *pIcon = (CStatic*) GetDlgItem(IDC_SICON);
    if (pIcon && m_hIcon)
    {
        pIcon->SetIcon(m_hIcon);    
    }
	
    UpdateButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProg::UpdateButtons()
{
    CWnd *pOK = GetDlgItem(IDOK);
    CWnd *pIcon = GetDlgItem(IDC_BICON);
    CWnd *pWnd = GetDlgItem(IDC_ECOMMANDLINE);
    if (pWnd && pIcon && pOK)
    {
        CString str;
        pWnd->GetWindowText(str);
        pOK->EnableWindow(str!="");
        pIcon->EnableWindow(str!="");
    }

}

void CDlgProg::OnBsearch() 
{
	// TODO: Add your control notification handler code here
    char szFilter[] = 
        "Programmes|*.exe;*.com;*.pif;*.bat|" \
        "Tous (*.*)|*.*|"\
        "|"; 

    CFileDialog dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
            szFilter,  this ) ;

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

void CDlgProg::OnBicon() 
{
	// TODO: Add your control notification handler code here
    CIconDlg dlg;
    CWnd *pWnd = GetDlgItem(IDC_ECOMMANDLINE);
    if (pWnd)
    {
        CString str;
        pWnd->GetWindowText(str);
        dlg.SetPath(str);
    }

    if (dlg.DoModal()==IDOK)
    {
        CStatic *pStatic = (CStatic*)GetDlgItem(IDC_SICON);
        if (pStatic)
        {
            pStatic->SetIcon(dlg.GetIcon());
        }

        m_hIcon = dlg.GetIcon();
    }
}

void CDlgProg::OnUpdateEcommandline() 
{
	// TODO: Add your control notification handler code here
    UpdateButtons();	
}

HICON CDlgProg::GetIcon()
{
    return m_hIcon;
}

void CDlgProg::SetIcon(HICON hIcon)
{
    m_hIcon = hIcon;
}

void CDlgProg::OnOK() 
{
	// TODO: Add extra validation here
    CString str;
    CWnd *pWnd = GetDlgItem(IDC_ECOMMANDLINE);
    if (pWnd)
    {
        pWnd->GetWindowText(str);
    }

    if (m_hIcon==0)
    {
        int nIcons = 
            (int) ::ExtractIcon (NULL, str , (UINT) -1);

        if (nIcons) 
        {
             m_hIcon = ::ExtractIcon (
                    AfxGetInstanceHandle (),
                    str, 0);
        }
        else
        {    
            m_hIcon = ::LoadIcon(NULL, 
                    MAKEINTRESOURCE(IDI_APPLICATION));
        }
    }
	
	CDialog::OnOK();
}
