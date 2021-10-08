// Field.h : header file
//

#ifndef _FIELD_H
#define _FIELD_H

#define MAX_FI_NAME 32
#define MAX_FI_DEFAULT 16
#define MAX_FI_SIZE 4
#define MAX_FI_ARG 32
#define MAX_FI_INFO 1024

typedef struct 
{
	int m_nArgs;
	char m_szName[32];
	int m_nType;
} TYPEINFO;

/////////////////////////////////////////////////////////////////////////////
// CField window

class CField 
{
// Construction
public:
	void Fill(char *sz);
	CField();

// Attributes
public:

// Operations
public:
	void FormatTechDoc(CString & str);
	void FormatField(char *szTemp);
	void Forget();
	void Serialize(CArchive & ar, int nVer);
	void Init(MYSQL_FIELD *pField);
	void Init();

protected:
	int FindType(char *sz);

// Implementation
public:
	 ~CField();

     // *********************************
     // DO NOT MODIFY THIS BLOCK 
	 char m_szName[MAX_FI_NAME];
	 char m_szDefault[MAX_FI_DEFAULT];
	 char m_szArg[MAX_FI_ARG];
	 int m_nType;
	 int m_nSize;

	 BOOL m_bPrimary;
	 BOOL m_bNotNull;
	 BOOL m_bAuto;
	 BOOL m_bKey;
	 BOOL m_bUnique;
	 BOOL m_bUnsigned;

	 CField *m_pNext;
     // ********************************

     char m_szInfo[MAX_FI_INFO];
};

/////////////////////////////////////////////////////////////////////////////

#endif