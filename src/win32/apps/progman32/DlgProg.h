// DlgProg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProg dialog

class CDlgProg : public CDialog
{
// Construction
public:
	void SetIcon(HICON hIcon);
	HICON GetIcon();
	void UpdateButtons();
	CDlgProg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProg)
	enum { IDD = IDD_PROG_PROPERTIES };
	BOOL	m_bMinimize;
	CString	m_strCommandLine;
	CString	m_strDescription;
	CString	m_strDirectory;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CHotKeyCtrl m_hotkey;
    HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgProg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBsearch();
	afx_msg void OnBicon();
	afx_msg void OnUpdateEcommandline();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
