// TextArray.h : header file
//

#ifndef _CTEXTARRAY
#define _CTEXTARRAY

/////////////////////////////////////////////////////////////////////////////
// CTextArray window

class CTextArray 
{
// Construction
public:
	CTextArray();

// Attributes
public:
	int GetSize();
	int GetIndexFor(CString & str);
	int GetIndexFor(char *sz);

// Operations
public:
	char * operator[] (int n);
	BOOL Add(char *p);
	void Forget();
	void Init();

// Implementation
public:
	~CTextArray();

protected:
	char **m_ppText;
	int m_nSize;

};

/////////////////////////////////////////////////////////////////////////////
#endif