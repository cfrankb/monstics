// MemoDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMemoDialog dialog

class CMemoDialog : public CDialog
{
// Construction
public:
	CString m_strCaption;
	CMemoDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMemoDialog)
	enum { IDD = IDD_MEMO };
	CButton	m_bOk;
	CString	m_strMemo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMemoDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
