// ExtraData.h : header file
//

#ifndef _EXTRADATA_H
#define _EXTRADATA_H

typedef struct
{
	short m_nOrgX;
	short m_nOrgY;
	
	short m_nOrgProto;
	short m_nOrgOBL;
	
	short m_nOrgFrame;
	short m_nUnused;

	short nLives;
	short nHitPoints;

} COREDATA;

#define EXTRADATASIZE 256

/////////////////////////////////////////////////////////////////////////////
// CExtraData window

class CExtraData 
{
// Construction
public:
	void InsertAt(int n, char nValue);
	void RemoveAt(int nIndex);
	int Add(char nValue);
	int GetSize();
	void Forget();
	void Init();
	CExtraData();

// Attributes
public:
	char * GetName();

// Operations
public:
	char & operator[](int n);
	CExtraData & operator= (CExtraData & data);
	void Read(CFile & file);
	void Write(CFile & file);


// Implementation
public:
	~CExtraData();
	void Serialize(CArchive & ar);

private:
	char m_szName[32];	
	int m_nSize;
	char m_arrData[EXTRADATASIZE];
	int m_nMode;

	COREDATA m_data;
};

/////////////////////////////////////////////////////////////////////////////

#endif