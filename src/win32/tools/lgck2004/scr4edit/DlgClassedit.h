// CDlgClassEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgClassEdit dialog

class CDlgClassEdit : public CDialog
{
// Construction
public:
	void UpdateB_OK();
	CDlgClassEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgClassEdit)
	enum { IDD = IDD_CLASSEDIT };
	BOOL	m_bSystem;
	CString	m_strLabel;
	CString	m_strValue;
	int		m_nValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgClassEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgClassEdit)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCvalue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
