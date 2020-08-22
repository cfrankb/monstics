// DlgImportBmp.cpp : implementation file
//

#include "stdafx.h"
#include "obl4edit.h"
#include "DlgImportBmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImportBmp dialog


CDlgImportBmp::CDlgImportBmp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImportBmp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImportBmp)
	m_strFilename = _T("");
	m_nMethod = -1;
	//}}AFX_DATA_INIT
}


void CDlgImportBmp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImportBmp)
	DDX_Text(pDX, IDC_EFILENAME, m_strFilename);
	DDX_Radio(pDX, IDC_RMETHOD1, m_nMethod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImportBmp, CDialog)
	//{{AFX_MSG_MAP(CDlgImportBmp)
	ON_BN_CLICKED(IDC_BBROWSE, OnBbrowse)
	ON_EN_CHANGE(IDC_EFILENAME, OnChangeEfilename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImportBmp message handlers


void CDlgImportBmp::OnBbrowse() 
{
	// TODO: Add your control notification handler code here
    CString l_strFilesFilter =
        "Windows Bitmap Files (*.bmp)|*.bmp|"\
        "|";

    CFileDialog l_Dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    l_Dlg.m_ofn.lpstrTitle = "Import bitmap"; 
    
    int iStatus = l_Dlg.DoModal(); 
    if (iStatus==IDOK)
    {
		m_strFilename= l_Dlg.GetPathName();
		CWnd *pEdit = GetDlgItem(IDC_EFILENAME);
		if (pEdit)
		{
			pEdit->SetWindowText(m_strFilename);
		}

		EnableThings();
	}
}

void CDlgImportBmp::EnableThings()
{
	CWnd *pBOk = GetDlgItem(IDOK);
	CWnd *pEdit = GetDlgItem(IDC_EFILENAME);
	CString strFilename;

	if ((pEdit!=NULL))
	{
		pEdit->GetWindowText(strFilename);
		if (pBOk!=NULL)
			pBOk->EnableWindow(strFilename!="");
	}

	CWnd *pRMethod3 = GetDlgItem(IDC_RMETHOD3);
	if (pRMethod3)
	{
		pRMethod3->EnableWindow(m_nBpp==8);
	}
		
}

BOOL CDlgImportBmp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	EnableThings()	;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgImportBmp::OnChangeEfilename() 
{
	// TODO: Add your control notification handler code here
	EnableThings();
}
