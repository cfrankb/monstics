#ifndef _TAGENTRY_H
#define _TAGENTRY_H

// TagEntry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTagEntry 

class CTagEntry 
{
// Construction
public:
	CTagEntry (char *sz, int nVal=0);
	CTagEntry();

// Attributes
public:
	void SetDescription (CString & string);
	void SetName (CString & string);
 	char* GetName();

// Operations
public:

// Implementation
public:
	~CTagEntry();
	void Serialize (CArchive & ar);
	void Read (CFile & file);
	void Write (CFile & file);

	int m_nValue;
	char m_szDescription[_MAX_PATH];
	char m_szName[_MAX_PATH];
};

/////////////////////////////////////////////////////////////////////////////

#endif