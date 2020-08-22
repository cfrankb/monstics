// DlgImportOBL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImportOBL dialog

class CDlgImportOBL : public CDialog
{
// Construction
public:
	void EnableThings();
	CDlgImportOBL(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgImportOBL)
	enum { IDD = IDD_IMPORTOBL };
	CString	m_strFilename;
	int		m_bAppend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImportOBL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgImportOBL)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	afx_msg void OnChangeEfilename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
