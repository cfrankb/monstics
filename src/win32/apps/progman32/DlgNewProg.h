// DlgNewProg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNewProg dialog

class CDlgNewProg : public CDialog
{
// Construction
public:
	CDlgNewProg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNewProg)
	enum { IDD = IDD_NEW_PROG };
	int		m_nSelection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewProg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewProg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
