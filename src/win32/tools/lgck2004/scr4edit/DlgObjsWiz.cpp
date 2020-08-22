// DlgObjsWiz.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgObjsWiz.h"
#include "dlgclassedit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgObjsWiz dialog


CDlgObjsWiz::CDlgObjsWiz(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgObjsWiz::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgObjsWiz)
	m_strFilename = _T("");
	m_nClass = -1;
	//}}AFX_DATA_INIT
}


void CDlgObjsWiz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgObjsWiz)
	DDX_Text(pDX, IDC_EFILENAME, m_strFilename);
	DDV_MaxChars(pDX, m_strFilename, 254);
	DDX_CBIndex(pDX, IDC_CCLASS, m_nClass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgObjsWiz, CDialog)
	//{{AFX_MSG_MAP(CDlgObjsWiz)
	ON_BN_CLICKED(IDC_BBROWSE, OnBbrowse)
	ON_BN_CLICKED(IDC_BNEW, OnBnew)
	ON_EN_CHANGE(IDC_EFILENAME, OnChangeEfilename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgObjsWiz message handlers

BOOL CDlgObjsWiz::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateBCreate();
	FillCombo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgObjsWiz::OnBbrowse() 
{
	// TODO: Add your control notification handler code here
    CString l_strFilesFilter =
        "OBL3/OBL4 Format|*.obl|"\
        "|";

	CFileDialog dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Select specification"; 
    
    if (dlg.DoModal()==IDOK)  {
		m_strFilename = dlg.GetPathName();

		CWnd *pWnd;
		pWnd = GetDlgItem (IDC_EFILENAME);
		pWnd->SetWindowText(m_strFilename);
    }			
	
}

void CDlgObjsWiz::OnBnew() 
{
	// TODO: Add your control notification handler code here
	CDlgClassEdit dlg;

	CComboBox * pCombo = (CComboBox *) 
		GetDlgItem (IDC_CCLASS);

	CStrValArray & arrClasses = 
		(m_pDoc -> m_game3.m_arrClasses) ;

	int n;
	dlg.m_strLabel = "(noname)";		
	dlg.m_nValue = -1;		
	dlg.m_bSystem = FALSE;

	int nStatus = dlg.DoModal();
	if (nStatus==IDOK) {
		n= arrClasses.Add (new CStrVal (dlg.m_nValue,
			dlg.m_strLabel, dlg.m_bSystem));


		m_nClass = dlg.m_nValue;
		pCombo->ResetContent();
		FillCombo();
		//pCombo->SetCurSel(n);
	}
	
}

void CDlgObjsWiz::FillCombo()
{
	// OBJECT CLASS ********************************

	int i;
	int n;

	CStrValArray & arrClasses = 
		m_pDoc->m_game3.m_arrClasses;

	CComboBox * pComboClasses = (CComboBox *)
		GetDlgItem (IDC_CCLASS);

	for (n=0; n<arrClasses.GetSize(); n++)	{
		i= pComboClasses->AddString 
			(arrClasses[n]->m_strLabel);
		pComboClasses->SetItemData (i, 
			arrClasses[n]->m_nVal);

		if (arrClasses[n]->m_nVal==m_nClass)
			pComboClasses->SetCurSel (i);
	}

}

void CDlgObjsWiz::UpdateBCreate()
{
	CString str;
	CWnd *pWnd;
	pWnd = GetDlgItem (IDC_EFILENAME);
	pWnd->GetWindowText(str);

	pWnd = GetDlgItem (IDOK);
	pWnd->EnableWindow(str!="");
}

void CDlgObjsWiz::OnChangeEfilename() 
{
	// TODO: Add your control notification handler code here
	UpdateBCreate();
}
