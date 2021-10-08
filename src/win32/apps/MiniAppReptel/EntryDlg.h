// EntryDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntryDlg dialog

class CEntryDlg : public CDialog
{
// Construction
public:
	int m_nImage;
	HICON m_hIcon;
	void EnableOK();
	int m_nPath;
	CString m_strPath;
	CEntryDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEntryDlg)
	enum { IDD = IDD_PROPRETIES };
	CStatic	m_ctlStaticIcon;
	CEdit	m_ctlName;
	CButton	m_ctlOk;
	CString	m_szAddr;
	CString	m_szInfo;
	CString	m_szName;
	CString	m_szTel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEntryDlg)
	afx_msg void OnChangeicon();
	afx_msg void OnChangeName();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeAddr();
	afx_msg void OnChangeInfo();
	afx_msg void OnChangeTel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
