// IconDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MiniApp Reptel.h"
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
	DDX_Control(pDX, IDC_LIST, m_ctlBidonIconBox);
	DDX_Control(pDX, IDC_OPENUP, m_ctlOpenUp);
	DDX_Control(pDX, IDC_PATH, m_ctlPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIconDlg, CDialog)
	//{{AFX_MSG_MAP(CIconDlg)
	ON_BN_CLICKED(IDC_OPENUP, OnOpenup)
	ON_LBN_DBLCLK(1998, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIconDlg message handlers

void CIconDlg::OnOpenup() 
{
	// TODO: Add your control notification handler code here
 
    static char BASED_CODE szFilter[] = 
        "Fichiers icônes|*.exe;*.dll;*.ico|" \
        "Programmes|*.exe|" \
        "Bibliothèques|*.dll|"\
        "Icônes|*.ico||"; 

    CFileDialog l_Dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
            szFilter,  this ) ;

    l_Dlg.m_ofn.lpstrTitle = "Changement d'icône"; 
    
    int iStatus = l_Dlg.DoModal(); 

    if (iStatus==IDOK)
    {
        CString l_strPath = l_Dlg.GetPathName();
        m_ctlPath.SetWindowText(l_strPath);
        FillListBox(l_strPath);
        if (m_ctlIconBox.GetCount())
            m_ctlIconBox.SetCurSel(0);

        m_nPath = 0;
        m_strPath = l_strPath;
    }
}

void CIconDlg::FillListBox(CString p_StrFilename)
{

        m_ctlIconBox.ResetContent ();

        int nIcons = (int)
            ::ExtractIcon (NULL, p_StrFilename.GetBuffer(512)
                , (UINT) -1);

        if (nIcons) {
            HICON hIcon;
            for (int i=0; i<nIcons; i++) {
                hIcon = ::ExtractIcon (AfxGetInstanceHandle (),
                    p_StrFilename.GetBuffer(512), i);
                m_ctlIconBox.AddIcon (hIcon,"");
            }

        }
}

BOOL CIconDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    int m_cxChar =5;
 	int m_cyChar =10;

    CRect rect;
    m_ctlBidonIconBox.GetWindowRect(&rect);
    m_ctlBidonIconBox.ShowWindow(FALSE);
    this->ScreenToClient (&rect);

    m_ctlIconBox.Create (WS_CHILD | WS_VISIBLE | WS_HSCROLL |
        WS_BORDER | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | LBS_MULTICOLUMN,
        rect,
        this, 1998);	

    CString strFilename;
    if (strFilename.IsEmpty())
    {   strFilename = AfxGetAppName() ;
        strFilename = strFilename+ ".exe"; 
    }

    m_ctlPath.SetWindowText(strFilename);

   FillListBox(strFilename);

   if (m_ctlIconBox.GetCount())
        m_ctlIconBox.SetCurSel(0);
    
	// TODO: Add extra initialization here
	                      
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIconDlg::OnOK() 
{
	// TODO: Add extra validation here
    if (m_ctlIconBox.GetCount())
    {    
        int l_nIndex = m_ctlIconBox.GetCurSel() ;
        USER_ICONTEXT* l_psIconText = 
            (USER_ICONTEXT *) m_ctlIconBox.GetItemData(l_nIndex);

        m_hIcon = l_psIconText->hIcon;
        m_nPath = l_nIndex;
    }

    
    CDialog::OnOK();
}

void CIconDlg::OnDblclkList() 
{
	// TODO: Add your control notification handler code here
	OnOK();

}
