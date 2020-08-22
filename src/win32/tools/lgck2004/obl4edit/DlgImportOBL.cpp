// DlgImportOBL.cpp : implementation file
//

#include "stdafx.h"
#include "obl4edit.h"
#include "DlgImportOBL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImportOBL dialog


CDlgImportOBL::CDlgImportOBL(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImportOBL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImportOBL)
	m_strFilename = _T("");
	m_bAppend = -1;
	//}}AFX_DATA_INIT
}


void CDlgImportOBL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImportOBL)
	DDX_Text(pDX, IDC_EFILENAME, m_strFilename);
	DDX_Radio(pDX, IDC_RAPPEND, m_bAppend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImportOBL, CDialog)
	//{{AFX_MSG_MAP(CDlgImportOBL)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_CHANGE(IDC_EFILENAME, OnChangeEfilename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImportOBL message handlers

BOOL CDlgImportOBL::OnInitDialog() 
{
	CDialog::OnInitDialog();
	EnableThings();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgImportOBL::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
    CString l_strFilesFilter =
        "OBL3/OBL4 Format (*.obl)|*.obl|"\
        "|";

    CFileDialog l_Dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    l_Dlg.m_ofn.lpstrTitle = "Import OBL4"; 
    
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

void CDlgImportOBL::OnChangeEfilename() 
{
	// TODO: Add your control notification handler code here
	EnableThings();	
}

void CDlgImportOBL::EnableThings()
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

}
