// DlgYesNoAbort.cpp : implementation file
//

#include "stdafx.h"
#include "vlamits3.h"
#include "DlgYesNoAbort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgYesNoAbort dialog


CDlgYesNoAbort::CDlgYesNoAbort(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgYesNoAbort::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgYesNoAbort)
	m_strText = _T("");
	//}}AFX_DATA_INIT
}


void CDlgYesNoAbort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgYesNoAbort)
	DDX_Text(pDX, IDC_TEXT, m_strText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgYesNoAbort, CDialog)
	//{{AFX_MSG_MAP(CDlgYesNoAbort)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_BN_CLICKED(IDNO, OnNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgYesNoAbort message handlers

void CDlgYesNoAbort::SetText(char *sz)
{
    m_strText = CString(sz);
}

void CDlgYesNoAbort::SetText(CString & str)
{
    m_strText = str;
}

BOOL CDlgYesNoAbort::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgYesNoAbort::OnYes() 
{
	// TODO: Add your control notification handler code here
    EndDialog(IDYES);	
}

void CDlgYesNoAbort::OnNo() 
{
	// TODO: Add your control notification handler code here
    EndDialog(IDNO);		
}

int CDlgYesNoAbort::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}

LRESULT CDlgYesNoAbort::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::WindowProc(message, wParam, lParam);
}
