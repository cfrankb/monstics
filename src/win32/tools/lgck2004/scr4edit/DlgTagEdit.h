// DlgTagEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTagEdit dialog

class CDlgTagEdit : public CDialog
{
// Construction
public:
	CDlgTagEdit(UINT nIDD=IDD_TAGEDIT, char **ppChoices=NULL, char **ppContent=NULL);   // standard constructor
	char **m_ppChoices;
	char **m_ppContent;

// Dialog Data
	//{{AFX_DATA(CDlgTagEdit)
	enum { IDD = IDD_TAGEDIT };
	int		m_nValue;
	CString	m_strDescription;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTagEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTagEdit)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
