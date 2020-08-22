// StrVal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStrVal 

class CStrVal 
{
// Construction
public:
	CStrVal (int n, const CString &str, BOOL bSystem=FALSE);
	CStrVal();

// Attributes
public:

// Operations
public:

// Implementation
public:
	~CStrVal();
	void Serialize (CArchive & ar);
	void Read (CFile & file);
	void Write (CFile & file);

	BOOL m_bSystem;
	int m_nVal;
	CString m_strLabel;
};

/////////////////////////////////////////////////////////////////////////////
