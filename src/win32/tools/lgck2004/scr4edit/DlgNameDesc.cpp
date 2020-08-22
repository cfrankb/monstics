// DlgNameDesc.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgNameDesc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNameDesc dialog


CDlgNameDesc::CDlgNameDesc(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNameDesc::IDD, pParent)
{
	m_strCaption = "New level";
	
	//{{AFX_DATA_INIT(CDlgNameDesc)
	m_strName = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
}


void CDlgNameDesc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNameDesc)
	DDX_Text(pDX, IDC_ENAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 254);
	DDX_Text(pDX, IDC_ETITLE, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNameDesc, CDialog)
	//{{AFX_MSG_MAP(CDlgNameDesc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNameDesc message handlers

BOOL CDlgNameDesc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText (m_strCaption);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNameDesc::SetCaption (const CString & string)
{
	m_strCaption = string;
}
