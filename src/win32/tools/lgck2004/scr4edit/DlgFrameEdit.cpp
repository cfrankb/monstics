// DlgFrameEdit.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgFrameEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFrameEdit dialog


CDlgFrameEdit::CDlgFrameEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFrameEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFrameEdit)
	m_strFilename = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFrameEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFrameEdit)
	DDX_Text(pDX, IDC_EFILENAME, m_strFilename);
	DDV_MaxChars(pDX, m_strFilename, 255);
	DDX_Text(pDX, IDC_ENAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFrameEdit, CDialog)
	//{{AFX_MSG_MAP(CDlgFrameEdit)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_CHANGE(IDC_ENAME, OnChangeEname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFrameEdit message handlers

void CDlgFrameEdit::OnBrowse() 
{
	// TODO: Add your control notification handler code here
    CString l_strFilesFilter =
        "All supported formats|*.obl;*.ima;*.mcx|"\
        "Static Images (*.ima;*.mcx)|*.ima;*.mcx|"\
        "OBL3/OBL4 Format|*.obl|"\
        "|";

	CFileDialog dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Select frame set"; 
    
    if (dlg.DoModal()==IDOK)  {
		m_strFilename = dlg.GetPathName();
		if (m_strName=="")
			m_strName = dlg.GetFileName();

		CWnd *pWnd;
		pWnd = GetDlgItem (IDC_ENAME);
		pWnd->SetWindowText(m_strName);
		pWnd = GetDlgItem (IDC_EFILENAME);
		pWnd->SetWindowText(m_strFilename);
    }			
}

void CDlgFrameEdit::OnChangeEname() 
{
	// TODO: Add your control notification handler code here
	UpdateOK();
}

BOOL CDlgFrameEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateOK();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFrameEdit::UpdateOK()
{
	CWnd *pWnd;
	pWnd = GetDlgItem (IDC_ENAME);

	CString str;
	pWnd -> GetWindowText(str);

	pWnd = GetDlgItem(IDOK);
	pWnd -> EnableWindow(str!="");
}
