// SS3Frame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSS3Frame window

class CSS3Frame : public CObject
{
// Construction
public:
	void Serialize(CArchive& ar);

    BOOL m_nDeleted;

    BOOL m_nMapped;
	BOOL m_nMapEnabled;
	int m_nLen;
	int m_nHei;

	CObArray m_arrUndo;
	CObArray m_arrRedo;
    char *m_pBitmap;
    char *m_pMap;

    CSS3Frame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSS3Frame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSS3Frame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSS3Frame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
