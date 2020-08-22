// DlgMessageBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMessageBox dialog

class CDlgMessageBox : public CDialog
{
// Construction
public:
	CString m_strCaption;
	void SetCaption (CString str);
	CDlgMessageBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMessageBox)
	enum { IDD = IDD_MESSAGEBOX };
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMessageBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMessageBox)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
