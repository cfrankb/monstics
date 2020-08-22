// DlgLoad.cpp : implementation file
//

#include "stdafx.h"
#include "vlamits3.h"
#include "DlgLoad.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLoad dialog


CDlgLoad::CDlgLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLoad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLoad)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    m_pFirst = NULL;
    m_pLast = NULL;
}

CDlgLoad::~CDlgLoad()
{
    NAME_BLOCK * p= m_pFirst;
    NAME_BLOCK * pp;
    while (p)
    {
        pp = (NAME_BLOCK*) p->m_pNext;
        free(p);      
        p = pp;
    }
    m_pFirst=NULL;
    m_pLast=NULL;
}

void CDlgLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLoad)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLoad, CDialog)
	//{{AFX_MSG_MAP(CDlgLoad)
	ON_CBN_SELCHANGE(IDC_COMBO_GAMES, OnSelchangeComboGames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLoad message handlers

BOOL CDlgLoad::OnInitDialog() 
{
	CDialog::OnInitDialog();

    CComboBox *pCombo = (CComboBox*) GetDlgItem(IDC_COMBO_GAMES);
    if (pCombo)
    {
        FillCombo(pCombo);    
        pCombo->SetCurSel(0);
    }

    UpdateButtons();

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLoad::FillCombo(CComboBox *pCombo)
{
	struct _finddata_t data;
	int handle = _findfirst( "*.sav", &data);

	if (handle!=-1)
	{
        int status = handle;
		while (status!=-1)           
		{
    		pCombo->AddString(data.name);

            NAME_BLOCK * pBlock = (NAME_BLOCK*) malloc(sizeof(NAME_BLOCK));
            strcpy(pBlock->m_szName, data.name);

            if (m_pFirst)
            {
                // next items
                pBlock->m_pNext = NULL;
                m_pLast->m_pNext = pBlock;
                m_pLast = pBlock;
            }
            else
            {
                pBlock->m_pNext = NULL;
                m_pLast = pBlock;
                m_pFirst = pBlock;
                // first item
            }

            status = _findnext (handle, &data);
		} // while
		_findclose( handle );
	} // if
}

void CDlgLoad::UpdateButtons()
{
    CComboBox *pCombo = (CComboBox*) GetDlgItem(IDC_COMBO_GAMES);
	CWnd *pOK = GetDlgItem(IDOK);

    if (pCombo && pOK)
    {
        int nCurSel = pCombo->GetCurSel();
        pOK->EnableWindow(nCurSel!=-1);
    }
    
}

void CDlgLoad::OnSelchangeComboGames() 
{
	// TODO: Add your control notification handler code here
	UpdateButtons();
}

void CDlgLoad::OnOK() 
{
	// TODO: Add extra validation here

    CComboBox *pCombo = (CComboBox*) GetDlgItem(IDC_COMBO_GAMES);
    if (pCombo)
    {
        int i = 0;
        int nValue = pCombo->GetCurSel();
        BOOL bFound = FALSE;
        NAME_BLOCK * p= m_pFirst;

        while (p && !bFound)
        {
            if (i==nValue)
            {
                m_strName = CString(p->m_szName);
                bFound = TRUE;
            }

            p = (NAME_BLOCK*) p->m_pNext;
            i++;
        }

        char szTemp[1024];
        wsprintf(szTemp, "FOUND: %d | %s\n", bFound, m_strName.GetBuffer(1));
        OutputDebugString(szTemp);
    }   

	CDialog::OnOK();
}
