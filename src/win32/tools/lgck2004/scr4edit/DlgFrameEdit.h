// DlgFrameEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFrameEdit dialog

class CDlgFrameEdit : public CDialog
{
// Construction
public:
	void UpdateOK();
	CDlgFrameEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFrameEdit)
	enum { IDD = IDD_FRAMEEDIT };
	CString	m_strFilename;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFrameEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFrameEdit)
	afx_msg void OnBrowse();
	afx_msg void OnChangeEname();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
