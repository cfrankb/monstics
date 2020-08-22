// DlgExportPal.cpp : implementation file
//

#include "stdafx.h"
//#include "scr4edit.h"
#include "DlgExportPal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgExportPal dialog


CDlgExportPal::CDlgExportPal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExportPal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgExportPal)
	m_strName = _T("");
	m_nFormat = -1;
	//}}AFX_DATA_INIT
}


void CDlgExportPal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExportPal)
	DDX_Control(pDX, IDC_FORMATGROUP, m_ctrFormat);
	DDX_Control(pDX, IDC_ENAME, m_ctrName);
	DDX_Control(pDX, IDOK, m_ctrOK);
	DDX_Text(pDX, IDC_ENAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 128);
	DDX_Radio(pDX, IDC_RMSDOS, m_nFormat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgExportPal, CDialog)
	//{{AFX_MSG_MAP(CDlgExportPal)
	ON_BN_CLICKED(IDC_BBROWSE, OnBbrowse)
	ON_EN_CHANGE(IDC_ENAME, OnChangeEname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgExportPal message handlers

void CDlgExportPal::OnBbrowse() 
{
	// TODO: Add your control notification handler code here
  CString l_strFilesFilter =
        "Color palette |*.pal"\
        "|";

	CFileDialog dlg( FALSE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Export color palette"; 
	dlg.m_ofn.lpstrDefExt = ".pal";
    
    if (dlg.DoModal()==IDOK)  {
		CString strFilename = dlg.GetPathName();
		m_ctrName.SetWindowText(strFilename);
		UpdateButtons();
	}
}

void CDlgExportPal::OnChangeEname() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();	
}

void CDlgExportPal::UpdateButtons()
{
	CString str;
	m_ctrName.GetWindowText(str);

	BOOL bEnabled = str!="";
	m_ctrOK.EnableWindow(bEnabled);
}

BOOL CDlgExportPal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	UpdateButtons();	 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
