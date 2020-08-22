// DbPage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDbPage1 dialog

class CDbPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDbPage1)

// Construction
public:
	CDbPage1();
	~CDbPage1();

// Dialog Data
	//{{AFX_DATA(CDbPage1)
	enum { IDD = IDD_DBPAGE1 };
	CString	m_strName;
	CString	m_strTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDbPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDbPage1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
