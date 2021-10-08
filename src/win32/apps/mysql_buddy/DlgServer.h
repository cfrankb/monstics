// DlgServer.h : header file
//

#ifndef _CDLGSERVER_H
#define _CDLGSERVER_H

/////////////////////////////////////////////////////////////////////////////
// CDlgServer dialog

class CDlgServer : public CDialog
{
// Construction
public:
	CDlgServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgServer)
	enum { IDD = IDD_SERVER };
	CString	m_strHost;
	CString	m_strName;
	CString	m_strPort;
	CString	m_strServer;
	CString	m_strUser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgServer)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif