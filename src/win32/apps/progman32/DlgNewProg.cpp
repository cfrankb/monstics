// DlgNewProg.cpp : implementation file
//

#include "stdafx.h"
#include "progman32.h"
#include "DlgNewProg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewProg dialog


CDlgNewProg::CDlgNewProg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewProg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewProg)
	m_nSelection = -1;
	//}}AFX_DATA_INIT
}


void CDlgNewProg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewProg)
	DDX_Radio(pDX, IDC_RADIO_GROUP, m_nSelection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewProg, CDialog)
	//{{AFX_MSG_MAP(CDlgNewProg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewProg message handlers
