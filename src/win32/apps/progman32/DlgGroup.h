// DlgGroup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGroup dialog

class CDlgGroup : public CDialog
{
// Construction
public:
	CDlgGroup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGroup)
	enum { IDD = IDD_GROUP_PROPERTIES };
	CString	m_strFile;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGroup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGroup)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
