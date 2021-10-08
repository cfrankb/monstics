// MADialog.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CMiniAppDialog dialog

class CMiniAppDialog : public CDialog
{
// Construction
public:
	CMiniAppDialog(int, CWnd *, char *, char *);
	CMiniAppDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMiniAppDialog)
	enum { IDD = 100 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMiniAppDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	char * m_szText1;
	char * m_szText2;

	// Generated message map functions
	//{{AFX_MSG(CMiniAppDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnNo();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

