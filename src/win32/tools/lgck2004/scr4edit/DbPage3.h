// DbPage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDbPage3 dialog

class CDbPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDbPage3)

// Construction
public:
	void TestHei();
	void TestLen();
	CDbPage3();
	~CDbPage3();

// Dialog Data
	//{{AFX_DATA(CDbPage3)
	enum { IDD = IDD_DBPAGE3 };
	CEdit	m_ctrLevelLen;
	CEdit	m_ctrLevelHei;
	CButton	m_ctrResizeLevel;
	CButton	m_ctrInheritPlrObj;
	CButton	m_ctrForceDefObj;
	CButton	m_ctrContinuity;
	CButton	m_ctrAtLevelResetHP;
	BOOL	m_bAtLevelResetHP;
	BOOL	m_bContinuity;
	BOOL	m_bForceDefObj;
	BOOL	m_bInheritPlrObj;
	BOOL	m_bResizeLevel;
	UINT	m_nLevelHei;
	UINT	m_nLevelLen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDbPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDbPage3)
	virtual BOOL OnInitDialog();
	afx_msg void OnCresizelevel();
	afx_msg void OnChangeElevelHei();
	afx_msg void OnChangeElevelLen();
	afx_msg void OnKillfocusElevelHei();
	afx_msg void OnKillfocusElevelLen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
