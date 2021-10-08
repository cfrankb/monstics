// DlgSetTimer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetTimer dialog

class CDlgSetTimer : public CDialog
{
// Construction
public:
	int str2int(CString & str);
	CDlgSetTimer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetTimer)
	enum { IDD = IDD_SET_TIMER };
	int		m_nSeconds;
	int		m_nMinutes;
	int		m_nHours;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetTimer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetTimer)
	afx_msg void OnDeltaposShour(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSmin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSsec(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEhour();
	afx_msg void OnUpdateEhour();
	afx_msg void OnChangeEmin();
	afx_msg void OnUpdateEmin();
	afx_msg void OnChangeEsec();
	afx_msg void OnUpdateEsec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
