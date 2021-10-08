// DlgRun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRun dialog

class CDlgRun : public CDialog
{
// Construction
public:
	void UpdateButtons();
	CDlgRun(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRun)
	enum { IDD = IDD_RUN };
	BOOL	m_bRunMinimize;
	CString	m_strCommandLine;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRun)
	afx_msg void OnBsearch();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEcommandline();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
