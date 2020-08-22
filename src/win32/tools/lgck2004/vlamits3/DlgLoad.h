// DlgLoad.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLoad dialog

typedef struct
{
    char m_szName[_MAX_PATH+1];
    void *m_pNext;
} NAME_BLOCK;

class CDlgLoad : public CDialog
{
// Construction
public:
	void UpdateButtons();
	void FillCombo(CComboBox *pCombo);
	~CDlgLoad();
	CDlgLoad(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLoad)
	enum { IDD = IDD_LOAD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLoad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
    CString m_strName;
    NAME_BLOCK *m_pFirst;
    NAME_BLOCK *m_pLast;

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLoad)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboGames();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
