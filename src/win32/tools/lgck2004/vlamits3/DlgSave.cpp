// DlgSave.cpp : implementation file
//

#include "stdafx.h"
#include "vlamits3.h"
#include "DlgSave.h"
#include "DlgYesNoAbort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSave dialog


CDlgSave::CDlgSave(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSave::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSave)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSave::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSave)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSave, CDialog)
	//{{AFX_MSG_MAP(CDlgSave)
	ON_EN_CHANGE(IDC_ENAME, OnChangeEname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSave message handlers

BOOL CDlgSave::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    UpdateButtons();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSave::OnChangeEname() 
{
	// TODO: Add your control notification handler code here
    UpdateButtons();
}

void CDlgSave::OnFinalRelease() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::OnFinalRelease();
}

void CDlgSave::UpdateButtons()
{
	CWnd *pEdit = GetDlgItem(IDC_ENAME);
	CWnd *pOK = GetDlgItem(IDOK);

    if (pEdit && pOK)
    {
        char szTemp[1024];
        pEdit->GetWindowText(szTemp, 1023);
        pOK->EnableWindow(szTemp[0]);
    }
}

void CDlgSave::OnOK() 
{
	// TODO: Add extra validation here
	CWnd *pEdit = GetDlgItem(IDC_ENAME);
    if (pEdit)
    {
        pEdit->GetWindowText(m_strName);
    }
	
    char szTemp[_MAX_PATH+1];
    wsprintf(szTemp, "%s.sav", m_strName.GetBuffer(1));

    FILE *sfile = fopen(szTemp, "rb");
    if (sfile)
    {
        fclose(sfile);
        CDlgYesNoAbort dlg;
        dlg.SetText("File exists. Overwrite?");
        int nResult = dlg.DoModal();
        switch (nResult)
        {
            case IDYES:
            	CDialog::OnOK();
            break;

            case IDNO:
            break;

            case IDCANCEL:
                CDialog::OnCancel();
            break;
        }
    }
    else
    {
    	CDialog::OnOK();
    }
}
