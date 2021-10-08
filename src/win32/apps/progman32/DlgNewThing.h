// DlgNewTable.h : header file
//

#ifndef _CDLGNEWTHING
#define _CDLGNEWTHING

/////////////////////////////////////////////////////////////////////////////
// CDlgNewThing dialog

class CDlgNewThing : public CDialog
{
// Construction
public:
	CDlgNewThing(char *sz);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNewThing)
	enum { IDD = IDD_NEWTHING };
	CString	m_strName;
	//}}AFX_DATA

	void SetName(char *sz);
	void SetName(CString & str);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewThing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char m_szTitle[128];
	void UpdateButtons();

	// Generated message map functions
	//{{AFX_MSG(CDlgNewThing)
	afx_msg void OnChangeEname();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif