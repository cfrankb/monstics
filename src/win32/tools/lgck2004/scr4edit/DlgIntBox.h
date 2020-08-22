// DlgIntBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIntBox dialog

class CDlgIntBox : public CDialog
{
// Construction
public:
	CDlgIntBox(char **arrContent, int *arrValue, CWnd *pParent);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIntBox)
	enum { IDD = IDD_DINT };
	CComboBox	m_ctrValue;
	int		m_nValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIntBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIntBox)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	char **m_arrContent;
	int *m_arrValue;

};
