// DlgText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgText dialog

class CDlgText : public CDialog
{
// Construction
public:
	void SetData(char *szTitle, char *szContent, char *szButton);
	CDlgText(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgText)
	enum { IDD = IDD_TEXTBOX };
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strTitle;
	CString m_strButton;

	// Generated message map functions
	//{{AFX_MSG(CDlgText)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
