// DlgImportBmp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImportBmp dialog

class CDlgImportBmp : public CDialog
{
// Construction
public:
	void EnableThings();
	int m_nBpp;
	CDlgImportBmp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgImportBmp)
	enum { IDD = IDD_IMPORTBMP };
	CString	m_strFilename;
	int		m_nMethod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImportBmp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgImportBmp)
	afx_msg void OnBbrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEfilename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
