// DlgGroup.cpp : implementation file
//

#include "stdafx.h"
#include "progman32.h"
#include "DlgGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGroup dialog


CDlgGroup::CDlgGroup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGroup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGroup)
	m_strFile = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGroup)
	DDX_Text(pDX, IDC_EFILE, m_strFile);
	DDX_Text(pDX, IDC_ENAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGroup, CDialog)
	//{{AFX_MSG_MAP(CDlgGroup)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGroup message handlers
