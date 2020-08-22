// DlgText.cpp : implementation file
//

#include "stdafx.h"
#include "vlamits3.h"
#include "DlgText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgText dialog


CDlgText::CDlgText(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgText::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgText)
	m_strText = _T("");
	//}}AFX_DATA_INIT
}


void CDlgText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgText)
	DDX_Text(pDX, IDC_ETEXT, m_strText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgText, CDialog)
	//{{AFX_MSG_MAP(CDlgText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgText message handlers



void CDlgText::SetData(char *szTitle, char *szContent, char *szButton)
{
    m_strText = szContent;
    m_strTitle = szTitle;
    m_strButton = szButton;
}

BOOL CDlgText::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
    SetWindowText(m_strTitle);

    CWnd *pWnd = GetDlgItem(IDOK);
    if (pWnd)
    {
       pWnd->SetWindowText(m_strButton);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
