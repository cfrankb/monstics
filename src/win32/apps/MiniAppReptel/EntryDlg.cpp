// EntryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MiniApp Reptel.h"
#include "EntryDlg.h"
#include "IconListBox.h"
#include "IconDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEntryDlg dialog


CEntryDlg::CEntryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEntryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEntryDlg)
	m_szAddr = _T("");
	m_szInfo = _T("");
	m_szName = _T("");
	m_szTel = _T("");
	//}}AFX_DATA_INIT
}


void CEntryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntryDlg)
	DDX_Control(pDX, IDC_STATICICON, m_ctlStaticIcon);
	DDX_Control(pDX, IDC_NAME, m_ctlName);
	DDX_Control(pDX, IDOK, m_ctlOk);
	DDX_Text(pDX, IDC_ADDR, m_szAddr);
	DDV_MaxChars(pDX, m_szAddr, 256);
	DDX_Text(pDX, IDC_INFO, m_szInfo);
	DDV_MaxChars(pDX, m_szInfo, 4096);
	DDX_Text(pDX, IDC_NAME, m_szName);
	DDV_MaxChars(pDX, m_szName, 128);
	DDX_Text(pDX, IDC_TEL, m_szTel);
	DDV_MaxChars(pDX, m_szTel, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEntryDlg, CDialog)
	//{{AFX_MSG_MAP(CEntryDlg)
	ON_BN_CLICKED(IDC_CHANGEICON, OnChangeicon)
	ON_EN_CHANGE(IDC_NAME, OnChangeName)
	ON_EN_CHANGE(IDC_ADDR, OnChangeAddr)
	ON_EN_CHANGE(IDC_INFO, OnChangeInfo)
	ON_EN_CHANGE(IDC_TEL, OnChangeTel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntryDlg message handlers

void CEntryDlg::OnChangeicon() 
{
	// TODO: Add your control notification handler code here

    CIconDlg l_Dlg;
    
    l_Dlg.m_hIcon = m_hIcon;
    l_Dlg.m_strPath = m_strPath;
    l_Dlg.m_nPath = m_nPath;

    int iStatus = l_Dlg.DoModal();

    if (iStatus==IDOK)
    {
        if (l_Dlg.m_hIcon!=m_hIcon)
        {
            m_hIcon = l_Dlg.m_hIcon;
            HICON l_hOldIcon = m_ctlStaticIcon.SetIcon(m_hIcon );
            EnableOK();
        }

    }

}


void CEntryDlg::OnChangeName() 
{
	// TODO: Add your control notification handler code here
    
    EnableOK();

}



BOOL CEntryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_ctlOk.EnableWindow(FALSE);

    HICON l_hOldIcon = m_ctlStaticIcon.SetIcon( m_hIcon );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEntryDlg::EnableOK()
{
    CString l_strText;
    
    m_ctlName.GetWindowText(l_strText);
    if (l_strText.IsEmpty())
        m_ctlOk.EnableWindow(FALSE);
    else
        m_ctlOk.EnableWindow(TRUE);

}

void CEntryDlg::OnChangeAddr() 
{
	// TODO: Add your control notification handler code here
    EnableOK();
	
}

void CEntryDlg::OnChangeInfo() 
{
	// TODO: Add your control notification handler code here
    EnableOK();
	
}

void CEntryDlg::OnChangeTel() 
{
	// TODO: Add your control notification handler code here
    EnableOK();
	
}
