// ProtoPage5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProtoPage5 dialog

class CProtoPage5 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProtoPage5)

// Construction
public:
	CProtoPage5();
	~CProtoPage5();

// Dialog Data
	//{{AFX_DATA(CProtoPage5)
	enum { IDD = IDD_PROTOPAGE5 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProtoPage5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProtoPage5)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
