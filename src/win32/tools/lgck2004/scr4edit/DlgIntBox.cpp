// DlgIntBox.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgIntBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIntBox dialog


CDlgIntBox::CDlgIntBox(char **arrContent=NULL, int *arrValue=NULL, CWnd *pParent=NULL) 
	: CDialog(CDlgIntBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIntBox)
	m_nValue = -1;
	//}}AFX_DATA_INIT

	m_arrContent = arrContent;
	m_arrValue = arrValue;

}


void CDlgIntBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIntBox)
	DDX_Control(pDX, IDC_CINT, m_ctrValue);
	DDX_CBIndex(pDX, IDC_CINT, m_nValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIntBox, CDialog)
	//{{AFX_MSG_MAP(CDlgIntBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIntBox message handlers

BOOL CDlgIntBox::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if (m_arrContent && m_arrValue)
	{
		int i =0;
		while (m_arrContent[i])
		{
			m_ctrValue.AddString(m_arrContent[i]);
			if (m_arrValue[i] == m_nValue)
			{
				m_ctrValue.SetCurSel(i);
			}

			i++;
		}

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
