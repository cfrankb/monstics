// DlgIntAll.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgIntAll.h"
#include "DlgIntArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIntAll dialog


CDlgIntAll::CDlgIntAll(char **arrContent=NULL, int *arrValue=NULL, CWnd *pWnd=NULL)
	: CDialog(CDlgIntAll::IDD, pWnd)
{
	//{{AFX_DATA_INIT(CDlgIntAll)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_arrContent = arrContent;
	m_arrValue = arrValue;
	m_pArray = NULL;

	m_pNameIntAll="System paths";
	m_pNameIntArray="Path";
	m_pNameIntBox="Aim";
}

void CDlgIntAll::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIntAll)
	DDX_Control(pDX, IDC_BEDIT, m_bbEdit);
	DDX_Control(pDX, IDC_BDELETE, m_bbDelete);
	DDX_Control(pDX, IDC_BADD, m_bbAdd);
	DDX_Control(pDX, IDC_LIST, m_ctrList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIntAll, CDialog)
	//{{AFX_MSG_MAP(CDlgIntAll)
	ON_BN_CLICKED(IDC_BADD, OnBadd)
	ON_BN_CLICKED(IDC_BEDIT, OnBedit)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_LBN_SELCANCEL(IDC_LIST, OnSelcancelList)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIntAll message handlers

void CDlgIntAll::OnBadd() 
{
	// TODO: Add your control notification handler code here

	if (!m_pArray)
		return;

	CExtraData data;
	data.Init();
	
	CDlgIntArray dlg(m_arrContent, m_arrValue, NULL);
	dlg.m_pExtraData = &data;
	if (dlg.DoModal()==IDOK)
	{
		strcpy(data.GetName(),
			dlg.m_strName.GetBuffer(0));

		m_pArray->Add(data);
		m_ctrList.AddString(data.GetName());
		m_ctrList.SetCurSel(m_pArray->GetSize());
	}

	UpdateButtons();
}

void CDlgIntAll::OnBedit() 
{
	// TODO: Add your control notification handler code here
	if (!m_pArray)
		return;

	int n = m_ctrList.GetCurSel();

	if (n!=-1)
	{
		CExtraData & data = (*m_pArray)[n];
	
		CDlgIntArray dlg(m_arrContent, m_arrValue, NULL);
		dlg.m_pExtraData = &data;
		if (dlg.DoModal()==IDOK)
		{
			strcpy(data.GetName(),
				dlg.m_strName.GetBuffer(0));

			m_ctrList.DeleteString(n);
			m_ctrList.InsertString(n, data.GetName());
			m_ctrList.SetCurSel(n);
		}
	}

	UpdateButtons();
}

void CDlgIntAll::OnBdelete() 
{
	// TODO: Add your control notification handler code here

	int n = m_ctrList.GetCurSel();

	if (n!=-1)
	{
		if (AfxMessageBox("Confirm delete?", MB_YESNO)
			==IDYES)
		{
			m_ctrList.DeleteString(n);
			m_pArray->RemoveAt(n);
			m_ctrList.SetCurSel(n);
		}
	}

	UpdateButtons();

}

void CDlgIntAll::OnDblclkList() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();
	OnBedit();
	
}

void CDlgIntAll::OnSelcancelList() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();
	
}

void CDlgIntAll::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();
	
}

void CDlgIntAll::UpdateButtons()
{

}

BOOL CDlgIntAll::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	UpdateButtons();
	FillBox();

	this->SetWindowText(m_pNameIntAll);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIntAll::FillBox()
{
	for (int n=0; n<m_pArray->GetSize(); n++)
	{
		CExtraData & data = (*m_pArray)[n];
		m_ctrList.AddString(data.GetName());
	}
}
