// DlgSelectEpisode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectEpisode dialog

class CDlgSelectEpisode : public CDialog
{
// Construction
public:
	void UpdateButtons();
	void SetList(CStringArray & arr);
	CDlgSelectEpisode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSelectEpisode)
	enum { IDD = IDD_SELECT_EPISODE };
	int		m_nEpisode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelectEpisode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
    CStringArray m_arrEpisodes;
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelectEpisode)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
