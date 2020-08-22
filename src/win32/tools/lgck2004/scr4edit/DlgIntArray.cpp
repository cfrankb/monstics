// DlgIntArray.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgIntArray.h"
#include "DlgIntBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX 256

/////////////////////////////////////////////////////////////////////////////
// CDlgIntArray dialog


CDlgIntArray::CDlgIntArray(char **arrContent=NULL, int *arrValue=NULL, CWnd *pWnd=NULL) 
	: CDialog(CDlgIntArray::IDD, pWnd)
{
	//{{AFX_DATA_INIT(CDlgIntArray)
	m_strName = _T("");
	m_nIndex = -1;
	//}}AFX_DATA_INIT

	m_arrContent = arrContent;
	m_arrValue = arrValue;

	//m_pNameIntAll="System paths";
	m_pNameIntArray="Path";
	m_pNameIntBox="";

}


void CDlgIntArray::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIntArray)
	DDX_Control(pDX, IDC_ENAME, m_ctrName);
	DDX_Control(pDX, IDC_BINSERT, m_bbInsert);
	DDX_Control(pDX, IDC_BEDIT, m_bbEdit);
	DDX_Control(pDX, IDC_BDUPLICATE, m_bbDuplicate);
	DDX_Control(pDX, IDC_BDELETE, m_bbDelete);
	DDX_Control(pDX, IDC_BADD, m_bbAdd);
	DDX_Control(pDX, IDC_LIST, m_ctrList);
	DDX_Text(pDX, IDC_ENAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 31);
	DDX_LBIndex(pDX, IDC_LIST, m_nIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIntArray, CDialog)
	//{{AFX_MSG_MAP(CDlgIntArray)
	ON_BN_CLICKED(IDC_BADD, OnBadd)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	ON_BN_CLICKED(IDC_BDUPLICATE, OnBduplicate)
	ON_BN_CLICKED(IDC_BEDIT, OnBedit)
	ON_BN_CLICKED(IDC_BINSERT, OnBinsert)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_LBN_SELCANCEL(IDC_LIST, OnSelcancelList)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_BMORE, OnBmore)
	ON_BN_CLICKED(IDC_BPATH, OnBpath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIntArray message handlers

BOOL CDlgIntArray::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	FillBox();
	UpdateButtons();

	this->SetWindowText(m_pNameIntArray);
	m_ctrName.SetWindowText(m_pExtraData->GetName());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIntArray::OnBadd() 
{
	// TODO: Add your control notification handler code here

	CDlgIntBox dlg(m_arrContent, m_arrValue, NULL);
	dlg.m_nValue = -1;
	if (dlg.DoModal()!= IDOK)
		return;

	char *pName = "-----------" ;
	for (int i=0; m_arrContent[i]; i++)
	{
		if (m_arrValue[i]== dlg.m_nValue)
		{
			pName = m_arrContent[i];
			break;
		}
	}

	int n = m_ctrList.AddString(pName) ;
	m_ctrList.SetCurSel(n);
	m_pExtraData->Add(dlg.m_nValue);
	UpdateButtons();	  
}

void CDlgIntArray::OnBdelete() 
{
	// TODO: Add your control notification handler code here
	int n = m_ctrList.GetCurSel();
	
	if (n != -1)
	{
		m_ctrList.DeleteString(n);
		m_pExtraData->RemoveAt(n);

		if (n!=0)
		{
			m_ctrList.SetCurSel(n-1);
		}
		else
		{
			m_ctrList.SetCurSel(n);
		}

		UpdateButtons();
	}
}

void CDlgIntArray::OnBduplicate() 
{
	// TODO: Add your control notification handler code here
	int n = m_ctrList.GetCurSel();
	
	if (n != -1)
	{
		int nValue = (*m_pExtraData)[n];

		char *pName = "-----------" ;
		for (int i=0; m_arrContent[i]; i++)
		{
			if (m_arrValue[i]== nValue)
			{
				pName = m_arrContent[i];
				break;
			}
		}

		m_ctrList.InsertString(n, pName) ;
		(*m_pExtraData).InsertAt(n, nValue);
		m_ctrList.SetCurSel(n+1);
		UpdateButtons();
	}					  	
}

void CDlgIntArray::OnBedit() 
{
	// TODO: Add your control notification handler code here
	int n = m_ctrList.GetCurSel();
	
	if (n != -1)
	{
		CDlgIntBox dlg(m_arrContent, m_arrValue, NULL);
		dlg.m_nValue = (*m_pExtraData)[n];
		if (dlg.DoModal()!=IDOK)
			return;

		char *pName = "-----------" ;
		for (int i=0; m_arrContent[i]; i++)
		{
			if (m_arrValue[i]== dlg.m_nValue)
			{
				pName = m_arrContent[i];
				break;
			}
		}

		m_ctrList.DeleteString(n);
		m_ctrList.InsertString(n, pName) ;
		(*m_pExtraData)[n] = dlg.m_nValue;
		m_ctrList.SetCurSel(n);
		UpdateButtons();
	}
}

void CDlgIntArray::OnBinsert() 
{
	// TODO: Add your control notification handler code here
	int n = m_ctrList.GetCurSel();
	if (n != -1)
	{
		CDlgIntBox dlg(m_arrContent, m_arrValue, NULL);
		dlg.m_nValue = -1;
		if (dlg.DoModal()!= IDOK)
			return;

		char *pName = "-----------" ;
		for (int i=0; m_arrContent[i]; i++)
		{
			if (m_arrValue[i]== dlg.m_nValue)
			{
				pName = m_arrContent[i];
				break;
			}
		}

		m_ctrList.InsertString(n, pName) ;
		m_pExtraData->InsertAt(n, dlg.m_nValue);
		m_ctrList.SetCurSel(n);
		UpdateButtons();
	}
}

void CDlgIntArray::OnDblclkList() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons()	;
	OnBedit();	
}

void CDlgIntArray::UpdateButtons()
{
	BOOL bActive = m_ctrList.GetCurSel() != -1;

	m_bbEdit.EnableWindow(bActive);
	m_bbInsert.EnableWindow(bActive);
	m_bbDelete.EnableWindow(bActive);
	m_bbDuplicate.EnableWindow(bActive);
}

void CDlgIntArray::OnSelcancelList() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons()	;
}

void CDlgIntArray::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();
}

void CDlgIntArray::ResetContent()
{
	m_ctrList.ResetContent();
}

void CDlgIntArray::FillBox()
{
	for (int n=0; n<m_pExtraData->GetSize(); n++)
	{
		char *pName = "-----------" ;
		for (int i=0; m_arrContent[i]; i++)
		{
			if (m_arrValue[i] == (*m_pExtraData)[n])
			{
				pName = m_arrContent[i];
				break;
			}
		}
		m_ctrList.AddString(pName);
	}
}

void CDlgIntArray::OnBmore() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgIntArray::OnBpath() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgIntArray::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
