// MADialog.cpp : implementation file
//

#include "stdafx.h"
#include "MADialog.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMiniAppDialog dialog


CMiniAppDialog::CMiniAppDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMiniAppDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMiniAppDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMiniAppDialog::CMiniAppDialog(int iDlgTmp, CWnd *pParentWnd, char *szText1=NULL, char *szText2=NULL)
:CDialog (iDlgTmp, pParentWnd) 
{

    m_szText1 = szText1;
    m_szText2 = szText2;

}



void CMiniAppDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMiniAppDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMiniAppDialog, CDialog)
	//{{AFX_MSG_MAP(CMiniAppDialog)
	ON_BN_CLICKED(7, OnNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiniAppDialog message handlers


BOOL CMiniAppDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    int iStat = CDialog::OnInitDialog();
    CStatic* pStatic;
    if ((m_szText1 !=NULL) && (m_szText2 !=NULL))
    {
        pStatic = 
            (CStatic*) GetDlgItem (IDC_STATIC1);
        if (pStatic!=NULL)
            pStatic->SetWindowText(m_szText1);

        pStatic = 
            (CStatic*) GetDlgItem (IDC_STATIC2);
        if (pStatic!=NULL)
            pStatic->SetWindowText(m_szText2);     
    }
    


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMiniAppDialog::OnNo() 
{
	// TODO: Add your control notification handler code here
       EndDialog(7);	
}

void CMiniAppDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
}

void CMiniAppDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
    EndDialog(IDCANCEL);	
	//CDialog::OnCancel();
}
