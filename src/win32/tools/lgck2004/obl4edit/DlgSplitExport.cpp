// DlgSplitExport.cpp : implementation file
//

#include "stdafx.h"
#include "obl4edit.h"
#include "DlgSplitExport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitExport dialog


CDlgSplitExport::CDlgSplitExport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSplitExport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSplitExport)
	m_nFrom = -1;
	m_nSize = -1;
	m_nTo = -1;
	m_bSplit = -1;
	m_strFilename = _T("");
	//}}AFX_DATA_INIT
}


void CDlgSplitExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSplitExport)
	DDX_CBIndex(pDX, IDC_CFROM, m_nFrom);
	DDX_CBIndex(pDX, IDC_CSIZE, m_nSize);
	DDX_CBIndex(pDX, IDC_CTO, m_nTo);
	DDX_Radio(pDX, IDC_RSPLIT, m_bSplit);
	DDX_Text(pDX, IDC_EFILENAME, m_strFilename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSplitExport, CDialog)
	//{{AFX_MSG_MAP(CDlgSplitExport)
	ON_BN_CLICKED(IDC_RSPLIT, OnRsplit)
	ON_BN_CLICKED(IDC_REXTRACT, OnRextract)
	ON_CBN_CLOSEUP(IDC_CFROM, OnCloseupCfrom)
	ON_CBN_CLOSEUP(IDC_CTO, OnCloseupCto)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_CHANGE(IDC_EFILENAME, OnChangeEfilename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitExport message handlers

BOOL CDlgSplitExport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CButton * pButton =(CButton *) GetDlgItem( IDC_RSPLIT);
	pButton ->SetCheck (TRUE);

	pButton =(CButton *) GetDlgItem( IDC_REXTRACT);
	pButton ->SetCheck (FALSE);

	int n=0;

	CComboBox *pComboSize = 
		(CComboBox*) GetDlgItem (IDC_CSIZE);

	CComboBox *pComboFrom = 
		(CComboBox*) GetDlgItem (IDC_CFROM);

	CComboBox *pComboTo = 
		(CComboBox*) GetDlgItem (IDC_CTO);
	
	for (n=0; n<m_pDoc->m_oblData.GetSize(); n++)
	{
		char sz[8];
		wsprintf(sz, "%d", n+1);

		pComboSize->AddString (sz);
		pComboFrom->AddString (sz);
		pComboTo->AddString (sz);
		
	}
	
	pComboSize->SetCurSel (0);
	pComboFrom->SetCurSel (0);
	pComboTo->SetCurSel (0);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSplitExport::OnRsplit() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd;

	pWnd = GetDlgItem (IDC_CSIZE);
	pWnd ->EnableWindow(TRUE);

	pWnd = GetDlgItem (IDC_CFROM);
	pWnd ->EnableWindow(FALSE);

	pWnd = GetDlgItem (IDC_CTO);
	pWnd ->EnableWindow(FALSE);
}

void CDlgSplitExport::OnRextract() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd;

	pWnd = GetDlgItem (IDC_CSIZE);
	pWnd ->EnableWindow(FALSE);

	pWnd = GetDlgItem (IDC_CFROM);
	pWnd ->EnableWindow(TRUE);

	pWnd = GetDlgItem (IDC_CTO);
	pWnd ->EnableWindow(TRUE);
	
}

void CDlgSplitExport::OnCloseupCfrom() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pComboFrom = 
		(CComboBox*) GetDlgItem (IDC_CFROM);

	CComboBox *pComboTo = 
		(CComboBox*) GetDlgItem (IDC_CTO);

	int nFrom = pComboFrom->GetCurSel();
	int nTo = pComboTo->GetCurSel();

	if ((nFrom != CB_ERR) && (nTo!=CB_ERR))
	{
		if (nFrom > nTo)
			pComboTo ->SetCurSel (nFrom);
	}


}

void CDlgSplitExport::OnCloseupCto() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pComboFrom = 
		(CComboBox*) GetDlgItem (IDC_CFROM);

	CComboBox *pComboTo = 
		(CComboBox*) GetDlgItem (IDC_CTO);

	int nFrom = pComboFrom->GetCurSel();
	int nTo = pComboTo->GetCurSel();

	if ((nFrom != CB_ERR) && (nTo!=CB_ERR))
	{
		if (nFrom > nTo)
			pComboFrom ->SetCurSel (nTo);
	}
	
}

void CDlgSplitExport::OnBrowse() 
{
	// TODO: Add your control notification handler code here
    CString l_strFilesFilter =
        "OBL3/OBL4 Format|*.obl|"\
        "|";

	CFileDialog dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER , 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Select output base file name"; 
    
    if (dlg.DoModal()==IDOK)  {
		CWnd * pWnd = GetDlgItem (IDC_EFILENAME);
		pWnd->SetWindowText(dlg.GetPathName());
	}
}

void CDlgSplitExport::OnChangeEfilename() 
{
	// TODO: Add your control notification handler code here
	CString str;
	CWnd * pWnd = GetDlgItem (IDC_EFILENAME);
	pWnd->GetWindowText(str);
	pWnd = GetDlgItem (IDOK);

	pWnd->EnableWindow(str!="");
	
}
