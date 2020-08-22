// SortArray.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSortArray 

class CSortArray 
{
// Construction
public:
	CSortArray();

// Attributes
public:
	int GetSize();

// Operations
public:
	CString * operator [] (int n);
	void RemoveAt (int n);
	int InsertAt (int n, const CString & str);
	int Add (const CString & str);

// Implementation
public:
	~CSortArray();

private:
	int m_nMax;
	int m_nSize;
	CString **m_arrEntries;

};

/////////////////////////////////////////////////////////////////////////////
