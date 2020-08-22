// DlgClassList.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgClassList.h"
#include "DlgClassEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgClassList dialog


CDlgClassList::CDlgClassList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgClassList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgClassList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CDlgClassList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgClassList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgClassList, CDialog)
	//{{AFX_MSG_MAP(CDlgClassList)
	ON_BN_CLICKED(IDC_BCLOSE, OnBclose)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_BADD, OnBadd)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	ON_BN_CLICKED(IDC_BEDIT, OnBedit)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgClassList message handlers

void CDlgClassList::OnBclose() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE, 0,0);
}

BOOL CDlgClassList::OnInitDialog() 
{
	CDialog::OnInitDialog();

	FillListBox();
	UpdateBDelete();
	UpdateBEdit();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgClassList::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here
	UpdateBDelete();
	UpdateBEdit();
}

void CDlgClassList::OnBadd() 
{
	// TODO: Add your control notification handler code here
	CDlgClassEdit dlg;

	CListBox * pListBox = (CListBox *) 
		GetDlgItem (IDC_LIST);

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

		pListBox->ResetContent();
		FillListBox();
		//istBox->SetCurSel(n);
		m_pDoc->SetModifiedFlag(TRUE);
	}

}

void CDlgClassList::OnBdelete() 
{
	// TODO: Add your control notification handler code here
	CListBox * pListBox = (CListBox *) 
		GetDlgItem (IDC_LIST);

	CStrValArray & arrClasses = 
		(m_pDoc -> m_game3.m_arrClasses) ;

	int n;
	if (pListBox->GetCurSel()!= LB_ERR)
	{
		n = pListBox->GetCurSel();
		n = pListBox->GetItemData(n);

		delete arrClasses[n];
		arrClasses.RemoveAt(n);

		pListBox->ResetContent();
		FillListBox();
		pListBox->SetCurSel(n);
		
		m_pDoc->SetModifiedFlag(TRUE);
	}
}

void CDlgClassList::OnBedit() 
{
	// TODO: Add your control notification handler code here
	CDlgClassEdit dlg;

	CListBox * pListBox = (CListBox *) 
		GetDlgItem (IDC_LIST);

	CStrValArray & arrClasses = 
		(m_pDoc -> m_game3.m_arrClasses) ;

	int n;
	if (pListBox->GetCurSel()!= LB_ERR)
	{
		n = pListBox->GetCurSel();
		n = pListBox->GetItemData(n);
		dlg.m_strLabel = arrClasses[n]->m_strLabel;		
		dlg.m_nValue = arrClasses[n]->m_nVal;		
		dlg.m_bSystem = arrClasses[n]->m_bSystem;		

		int nStatus = dlg.DoModal();
		if (nStatus==IDOK) {
			delete arrClasses[n];
			arrClasses.RemoveAt(n);
			n= arrClasses.Add (new CStrVal (dlg.m_nValue,
				dlg.m_strLabel, dlg.m_bSystem));

			pListBox->ResetContent();
			FillListBox();
			pListBox->SetCurSel(n);

			m_pDoc->SetModifiedFlag(TRUE);

		}
	}

}

void CDlgClassList::UpdateBDelete()
{
	CListBox * pListBox = (CListBox *) 
		GetDlgItem (IDC_LIST);

	CButton * pButtonDelete = (CButton*)
		GetDlgItem (IDC_BDELETE);

	pButtonDelete -> EnableWindow (pListBox->GetCurSel()!= LB_ERR);

}

void CDlgClassList::UpdateBEdit ()
{
	CListBox * pListBox = (CListBox *) 
		GetDlgItem (IDC_LIST);

	CButton * pButtonEdit = (CButton*)
		GetDlgItem (IDC_BEDIT);

	if (pListBox->GetCurSel()== LB_ERR)
	{
		pButtonEdit -> EnableWindow (FALSE);
	}
	else
	{
		pButtonEdit -> EnableWindow (TRUE);
	}
}

void CDlgClassList::FillListBox()
{
	// TODO: Add extra initialization here
	CListBox * pListBox = (CListBox *) 
		GetDlgItem (IDC_LIST);

	CStrValArray & arrClasses = 
		(m_pDoc -> m_game3.m_arrClasses) ;

	int n;
	int i;
	for (n=0; n<arrClasses.GetSize(); n++)	{
		CString str;
		if (arrClasses[n]->m_nVal>0x0f) {
			str.Format ("%x %s", arrClasses[n]->m_nVal,
							arrClasses[n]-> m_strLabel);
		}
		else {
			str.Format ("0%x %s", arrClasses[n]->m_nVal,
							arrClasses[n]-> m_strLabel);
		}
		
		i = pListBox->AddString (str);
		pListBox->SetItemData (i, n);
	}

}

void CDlgClassList::OnDblclkList() 
{
	// TODO: Add your control notification handler code here
	OnBedit	();
}
