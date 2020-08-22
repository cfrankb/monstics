// DlgSave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSave dialog

class CDlgSave : public CDialog
{
// Construction
public:
	void UpdateButtons();
	CDlgSave(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSave)
	enum { IDD = IDD_SAVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSave)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
public:
    CString m_strName;
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSave)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEname();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
