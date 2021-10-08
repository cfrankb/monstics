// IconDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "MiniApp Reptel.h"
#include "progman32.h"
#include "IconListBox.h"
#include "IconDlg.h"
#include "resource.h"

#define begin_struct typedef struct {
#define end_struct(_struct) } _struct;  
#define uchar unsigned char
#define uint unsigned int

typedef struct {
    HICON hIcon;
    char szText[1024];
} USER_ICONTEXT;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIconDlg dialog


CIconDlg::CIconDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIconDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIconDlg)
	//}}AFX_DATA_INIT
}


void CIconDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIconDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIconDlg, CDialog)
	//{{AFX_MSG_MAP(CIconDlg)
	ON_BN_CLICKED(IDC_OPENUP, OnOpenup)
	ON_LBN_DBLCLK(1998, OnDblclkList)
	ON_LBN_SELCHANGE(1998, OnSelchangeListx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIconDlg message handlers

BOOL CIconDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
    
    int m_cxChar =5;
 	int m_cyChar =10;

    CWnd *pWnd = GetDlgItem(IDC_LISTX);
    if (pWnd)
    {
        CRect rect;
        pWnd->GetWindowRect(&rect);
        pWnd->ShowWindow(FALSE);
        this->ScreenToClient (&rect);

        m_ctlIconBox.Create (WS_CHILD | WS_VISIBLE | WS_HSCROLL |
            WS_BORDER | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | LBS_MULTICOLUMN,
            rect,
            this, 1998);	
    }

    CString strFilename;
    if (m_strPath.IsEmpty())
    {  
        CWinApp* pApp = AfxGetApp();
        if (pApp)
        {
            m_strPath = AfxGetAppName() + CString(".exe");
        }
    }

    OutputDebugString(m_strPath);
    OutputDebugString("\r\n");

    pWnd = GetDlgItem(IDC_EFILENAME);
    if (pWnd)
    {
        pWnd->SetWindowText(m_strPath);
    }
    
    FillListBox(m_strPath);

    if (m_ctlIconBox.GetCount())
    {
        m_ctlIconBox.SetCurSel(0);
    }   
	       
    UpdateButtons();

    m_hIcon = NULL;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIconDlg::OnOpenup() 
{
	// TODO: Add your control notification handler code here
 
    char szFilter[] = 
        "Fichiers icônes|*.exe;*.dll;*.ico|" \
        "Programmes|*.exe|" \
        "Bibliothèques|*.dll|"\
        "Icônes|*.ico|"\
        "Tous|*.*|"\
        "|"; 

    CFileDialog dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
            szFilter,  this ) ;

    dlg.m_ofn.lpstrTitle = "Changement d'icône"; 
    
    if (dlg.DoModal()==IDOK)
    {
        CString m_strPath = dlg.GetPathName();
        CWnd *pWnd = GetDlgItem(IDC_EFILENAME);
        if (pWnd)
        {
            pWnd->SetWindowText(m_strPath);
        }

        FillListBox(m_strPath);
        if (m_ctlIconBox.GetCount())
        {
            m_ctlIconBox.SetCurSel(0);
        }

        m_nIndex = 0;
    }

    UpdateButtons();
}

void CIconDlg::FillListBox(CString strFilename)
{
        m_ctlIconBox.ResetContent ();

        int nIcons = (int)
            ::ExtractIcon (NULL, strFilename.GetBuffer(512)
                , (UINT) -1);

        if (nIcons) {
            HICON hIcon;
            for (int i=0; i<nIcons; i++) {
                hIcon = ::ExtractIcon (
                    AfxGetInstanceHandle (),
                    strFilename.GetBuffer(512), i);
                m_ctlIconBox.AddIcon (hIcon,"");
            }

        }
}

void CIconDlg::OnOK() 
{
	// TODO: Add extra validation here
    if (m_ctlIconBox.GetCurSel()!=-1)
    {    
        int m_nIndex = m_ctlIconBox.GetCurSel() ;
        USER_ICONTEXT* psIconText = 
            (USER_ICONTEXT *) m_ctlIconBox.GetItemData(m_nIndex);

        m_hIcon = psIconText->hIcon;

        //SetActive

        /*
        CWnd *pWnd = GetDlgItem(IDC_EFILENAME);
        if (pWnd)
        {
            pWnd->GetWindowText(m_strPath);
        }
        */

        CDialog::OnOK();
    }   
}

void CIconDlg::OnDblclkList() 
{
	// TODO: Add your control notification handler code here
    UpdateButtons();
    OnOK();
}

void CIconDlg::UpdateButtons()
{
    CWnd *pOK = GetDlgItem(IDOK);
    if (pOK)
    {
        pOK->EnableWindow(m_ctlIconBox.GetCurSel()!=-1);            
    }
}

void CIconDlg::OnSelchangeListx() 
{
	// TODO: Add your control notification handler code here
    UpdateButtons();	
}

HICON CIconDlg::GetIcon()
{
    return m_hIcon;
}

CString & CIconDlg::GetPath()
{
    return m_strPath;
}

int CIconDlg::GetIndex()
{
    return m_nIndex;
}

void CIconDlg::SetPath(CString & strPath)
{
    m_strPath = strPath;

}
