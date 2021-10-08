// Note.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNote window

class CNote : public CObject
{
// Construction
public:
	int m_iYear;
	int m_iMonth;
	CString m_strNotes[42];
    CString m_strMemo;
	CNote();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNote)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNote();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNote)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
