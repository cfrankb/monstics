// DbPage4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDbPage4 dialog

class CDbPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDbPage4)

// Construction
public:
	CDbPage4();
	~CDbPage4();

// Dialog Data
	//{{AFX_DATA(CDbPage4)
	enum { IDD = IDD_DBPAGE4 };
	CComboBox	m_ctrSignsSet;
	CComboBox	m_ctrSignsOBL;
	CComboBox	m_ctrPointsOBL;
	CString	m_strPointsOBL;
	CString	m_strSignsOBL;
	CString	m_strSignsSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDbPage4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDbPage4)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
