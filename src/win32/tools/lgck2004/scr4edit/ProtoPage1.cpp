// ProtoPage1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ProtoPage1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CProtoPage1, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CProtoPage1 property page

CProtoPage1::CProtoPage1() : CPropertyPage(CProtoPage1::IDD)
{
	//{{AFX_DATA_INIT(CProtoPage1)
	m_bAnimate = FALSE;
	m_nClass = -1;
	m_nFrameSet = -1;
	m_nObjectKey = -1;
	m_nTrigger = -1;
	m_strName = _T("");
	m_nFrameNo = -1;
	//}}AFX_DATA_INIT
}

CProtoPage1::~CProtoPage1()
{
}

void CProtoPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtoPage1)
	DDX_Check(pDX, IDC_CANIMATE, m_bAnimate);
	DDX_CBIndex(pDX, IDC_CCLASS, m_nClass);
	DDX_CBIndex(pDX, IDC_CFRAMESET, m_nFrameSet);
	DDX_CBIndex(pDX, IDC_COBJECTKEY, m_nObjectKey);
	DDX_CBIndex(pDX, IDC_CTRIGGER, m_nTrigger);
	DDX_Text(pDX, IDC_ENAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 30);
	DDX_CBIndex(pDX, IDC_CBASEFRAME, m_nFrameNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtoPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CProtoPage1)
	ON_CBN_SELCHANGE(IDC_CFRAMESET, OnSelchangeCframeset)
	ON_EN_CHANGE(IDC_ENAME, OnChangeEname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CProtoPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	// TODO: Add extra initialization here
	
	int n;
	int i;

	CString str;
	str.Format ("Properties for %c%s%c...", 34, m_strName, 34);
	CWnd *pParent = GetParent();
	if (pParent!=NULL) 
	{
		pParent->SetWindowText (str);
	}

	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;

	// FRAME SET *************************************

	CComboBox * pComboFrameSet = (CComboBox *)
		GetDlgItem (IDC_CFRAMESET);

	COBL3Array & arrOBL3 = m_pDoc->m_game3.m_arrOBL3;

	for (n=0; n<arrOBL3.GetSize(); n++)	{
		i= pComboFrameSet->AddString (arrOBL3[n]->m_szName);
		pComboFrameSet->SetItemData (i, n);

	}

	// Frame No ***********************************

	Fill_FrameNoCombo(m_nFrameSet);

	CComboBox * pComboBaseFrame = (CComboBox *)
		GetDlgItem (IDC_CBASEFRAME);

	pComboBaseFrame->SetCurSel (m_nFrameNo);

	// OBJECT CLASS ********************************

	CStrValArray & arrClasses = 
		m_pDoc->m_game3.m_arrClasses;

	CComboBox * pComboClasses = (CComboBox *)
		GetDlgItem (IDC_CCLASS);

	for (n=0; n<arrClasses.GetSize(); n++)	{
		i= pComboClasses->AddString 
			(arrClasses[n]->m_strLabel);
		pComboClasses->SetItemData (i, 
			arrClasses[n]->m_nVal);

		//if (arrClasses[n]->m_nVal==m_nClass)
		//	pComboClasses->SetCurSel (i);
	}

	// Trigger TYPE ********************************

	CComboBox * pComboTriggerType = (CComboBox *)
		GetDlgItem (IDC_CTRIGGER);

	i = pComboTriggerType->AddString ("RECIPIANT");
	pComboFrameSet->SetItemData (i, 0);
	i = pComboTriggerType->AddString ("GENERATOR");
	pComboFrameSet->SetItemData (i, 1);

	pComboTriggerType->SetCurSel (m_nTrigger);

	// Trigger key **********************

	CComboBox * pComboObjectKey = (CComboBox *)
		GetDlgItem (IDC_COBJECTKEY);

	for (n=0; n<128; n++)	{
		char szText[9];
		wsprintf(szText,"0x%x", n);
		
		if (n!=0) {
			i= pComboObjectKey->AddString (szText);}
		else {
			i= pComboObjectKey->AddString ("(No key)");}

		pComboObjectKey->SetItemData (i, n);
	}

	pComboObjectKey->SetCurSel (m_nObjectKey);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProtoPage1::Fill_FrameNoCombo(int nFrameSet)
{
	CComboBox * pComboBaseFrame = (CComboBox *)
		GetDlgItem (IDC_CBASEFRAME);

	COBL3Array & arrOBL3 = m_pDoc->m_game3.m_arrOBL3;
	COBL3Filter & filter = * arrOBL3[nFrameSet];

	char sz[20];
	int n;
	for (n=0; n< filter.GetSize(); n++) {
		wsprintf(sz, "%d [0x%x]", n+1,n+1);
		pComboBaseFrame->AddString (sz);
	}
}

void CProtoPage1::OnSelchangeCframeset() 
{
	// TODO: Add your control notification handler code here
	CComboBox * pComboFrameSet = (CComboBox *)
		GetDlgItem (IDC_CFRAMESET);

	int nFrameSet =  pComboFrameSet->GetCurSel();

	if (nFrameSet!=CB_ERR) {
		CComboBox * pComboBaseFrame = (CComboBox *)
			GetDlgItem (IDC_CBASEFRAME);
		pComboBaseFrame -> ResetContent();
		Fill_FrameNoCombo( nFrameSet);
		pComboBaseFrame->SetCurSel (0);
	}	
}

void CProtoPage1::OnChangeEname() 
{
	// TODO: Add your control notification handler code here
	CWnd *pEdit = GetDlgItem (IDC_ENAME);
	if (pEdit!=NULL)
	{
		CString str;
		CString strEdit;
		pEdit->GetWindowText (strEdit);
		str.Format ("Properties for %c%s%c...", 34, strEdit, 34);
		CWnd *pParent = GetParent();
		if (pParent!=NULL) 
			pParent->SetWindowText (str);
	}
}
