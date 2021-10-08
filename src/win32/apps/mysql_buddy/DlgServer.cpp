// DlgServer.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "DlgServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgServer dialog


CDlgServer::CDlgServer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgServer)
	m_strHost = _T("");
	m_strName = _T("");
	m_strPort = _T("");
	m_strServer = _T("");
	m_strUser = _T("");
	//}}AFX_DATA_INIT
}


void CDlgServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgServer)
	DDX_Text(pDX, IDC_EHOST, m_strHost);
	DDX_Text(pDX, IDC_ENAME, m_strName);
	DDX_Text(pDX, IDC_EPORT, m_strPort);
	DDX_Text(pDX, IDC_ESERVER, m_strServer);
	DDX_Text(pDX, IDC_EUSER, m_strUser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgServer, CDialog)
	//{{AFX_MSG_MAP(CDlgServer)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgServer message handlers
