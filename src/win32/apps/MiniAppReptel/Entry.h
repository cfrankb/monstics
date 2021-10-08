// Entry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntry window

class CEntry : public CObject
{
// Construction
public:
    BOOL m_nDeleted;
	int m_nImage;
	int m_nEntry;
	CEntry(int p_nEntry);
	CString m_strName;
	CString m_strTel;
	CString m_strAddr;
	CString m_strInfo;
	CEntry();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntry)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEntry();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEntry)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
