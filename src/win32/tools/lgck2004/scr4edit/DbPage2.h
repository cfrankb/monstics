// DbPage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDbPage2 dialog

class CDbPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDbPage2)

// Construction
public:
	CDbPage2();
	~CDbPage2();

// Dialog Data
	//{{AFX_DATA(CDbPage2)
	enum { IDD = IDD_DBPAGE2 };
	int		m_nHP;
	int		m_nLives;
	int		m_nMaxHP;
	int		m_nMaxLives;
	CComboBox	m_ctrHP;
	CComboBox	m_ctrLives;
	CComboBox	m_ctrMaxLives;
	CComboBox	m_ctrMaxHP;
	BOOL	m_bAtDeathResetHP;
	BOOL	m_bAtDeathResetLev;
	CButton	m_ctrAtDeathResetHP;
	CButton	m_ctrAtDeathResetLev;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDbPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDbPage2)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCbhp();
	afx_msg void OnSelchangeCblives();
	afx_msg void OnSelchangeCbmaxhp();
	afx_msg void OnSelchangeCbmaxlives();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
