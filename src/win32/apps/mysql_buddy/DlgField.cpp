// DlgField.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "DlgField.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char *g_arrTypes[];

/////////////////////////////////////////////////////////////////////////////
// CDlgField dialog


CDlgField::CDlgField(CField *p)
	: CDialog(CDlgField::IDD, NULL)
{
	//{{AFX_DATA_INIT(CDlgField)
	m_strName = _T("");
	m_nType = -1;
	m_bNotNull = FALSE;
	m_bPrimary = FALSE;
	m_bKey = FALSE;
	m_bAuto = FALSE;
	m_strDefault = _T("");
	m_strArg = _T("");
	m_bUnique = FALSE;
	m_bUnsigned = FALSE;
	m_strInfo = _T("");
	//}}AFX_DATA_INIT

	m_pField = p;

	/*
			dlg.m_nType = p->m_nType ;
			dlg.m_bPrimary = p->m_bPrimary ;
			dlg.m_bNotNull = p->m_bNotNull ;
			dlg.m_bAuto = p->m_bAuto ;
			dlg.m_bKey = p->m_bKey ;
			dlg.m_bUnique = p->m_bUnique ;

			dlg.m_strName = CString(p->m_szName);		
			dlg.m_strArg = CString(p->m_szArg);		
			dlg.m_strDefault = CString(p->m_szDefault);
			*/

	m_nType = p->m_nType ;
	m_bPrimary = (p->m_bPrimary!=0) ;
	m_bNotNull = (p->m_bNotNull!=0) ;
	m_bAuto = (p->m_bAuto!=0) ;
	m_bKey = (p->m_bKey!=0) ;
	m_bUnique = (p->m_bUnique!=0) ;
	m_bUnsigned = (p->m_bUnsigned!=0) ;

	m_strName = CString(p->m_szName);		
	m_strArg = CString(p->m_szArg);		
	m_strDefault = CString(p->m_szDefault);
    m_strInfo = CString(p->m_szInfo);
}

void CDlgField::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgField)
	DDX_Text(pDX, IDC_ENAME, m_strName);
	DDX_CBIndex(pDX, IDC_CBTYPE, m_nType);
	DDX_Check(pDX, IDC_CNOTNULL, m_bNotNull);
	DDX_Check(pDX, IDC_CPRIMARY, m_bPrimary);
	DDX_Check(pDX, IDC_CKEY, m_bKey);
	DDX_Check(pDX, IDC_CAUTO, m_bAuto);
	DDX_Text(pDX, IDC_EDEFAULT, m_strDefault);
	DDX_Text(pDX, IDC_EARG, m_strArg);
	DDX_Check(pDX, IDC_CUNIQUE, m_bUnique);
	DDX_Check(pDX, IDC_CUNSIGNED, m_bUnsigned);
	DDX_Text(pDX, IDC_EINFO, m_strInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgField, CDialog)
	//{{AFX_MSG_MAP(CDlgField)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgField message handlers

BOOL CDlgField::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CComboBox *pCombo =  (CComboBox*) GetDlgItem(IDC_CBTYPE);
	
	int i;

	if (pCombo)
	{
		for (i=0; g_arrTypes[i]; i++)
		{
			pCombo->AddString(g_arrTypes[i]);
			if (m_nType==i)
			{
				pCombo->SetCurSel(i);
			}
		}
	}

	int arrText[]={
		IDC_ENAME, MAX_FI_NAME-1,
		IDC_EDEFAULT, MAX_FI_DEFAULT-1,
		IDC_EARG, MAX_FI_ARG-1,
        IDC_EINFO, MAX_FI_INFO-1,
		NULL, NULL
	};

	for (i=0; arrText[i]; i=i+2)
	{
		CEdit *p = (CEdit*) GetDlgItem(arrText[i]);
		if (p)
		{
			p->SetLimitText(arrText[i+1]-1);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
