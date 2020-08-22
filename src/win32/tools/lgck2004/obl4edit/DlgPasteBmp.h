// DlgPasteBmp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPasteBmp dialog

class CDlgPasteBmp : public CDialog
{
// Construction
public:
	CDlgPasteBmp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPasteBmp)
	enum { IDD = IDD_PASTEBMP };
	int		m_nMethod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPasteBmp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nBpp;
	
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPasteBmp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
