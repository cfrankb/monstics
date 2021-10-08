// AlarmNode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmNode window

class CAlarmNode : public CObject
{
// Construction
public:
	BOOL m_nDeleted;
	CAlarmNode();
    CTime m_timeRing;
    CString m_strInfo;
    CString m_strSound;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmNode)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAlarmNode();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAlarmNode)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
