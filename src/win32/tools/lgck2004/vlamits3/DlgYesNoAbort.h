// DlgYesNoAbort.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgYesNoAbort dialog

class CDlgYesNoAbort : public CDialog
{
// Construction
public:
	void SetText(CString & str);
	void SetText(char *sz);
	CDlgYesNoAbort(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgYesNoAbort)
	enum { IDD = IDD_YESNOABORT };
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgYesNoAbort)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
//CString m_strText;

	// Generated message map functions
	//{{AFX_MSG(CDlgYesNoAbort)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
	afx_msg void OnNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
