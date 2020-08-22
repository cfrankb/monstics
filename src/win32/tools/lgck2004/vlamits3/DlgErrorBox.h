// DlgErrorBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgErrorBox dialog

class CDlgErrorBox : public CDialog
{
// Construction
public:
	CDlgErrorBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgErrorBox)
	enum { IDD = IDD_ERRORBOX };
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgErrorBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgErrorBox)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
