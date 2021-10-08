// IconDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIconDlg dialog

class CIconDlg : public CDialog
{
// Construction
public:
	HICON m_hIcon;
	CString m_strPath;
	int m_nPath;
	CIconDlg(CWnd* pParent = NULL);   // standard constructor
	CIconListBox m_ctlIconBox;

// Dialog Data
	//{{AFX_DATA(CIconDlg)
	enum { IDD = IDD_CHANGEICON };
	CListBox	m_ctlBidonIconBox;
	CButton	m_ctlOpenUp;
	CEdit	m_ctlPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillListBox(CString p_StrFilename);

	// Generated message map functions
	//{{AFX_MSG(CIconDlg)
	afx_msg void OnOpenup();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
