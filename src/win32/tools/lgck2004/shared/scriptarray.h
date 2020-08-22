#ifndef _SCRIPTARRAY_H
#define _SCRIPTARRAY_H

#include "scriptentry.h"
#include "extradata.h"

// ScriptArray.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScriptArray 

class CScriptArray
{
// Construction
public:
	CScriptArray();

// Attributes
public:
	int GetSize();

// Operations
public:
	void Forget();
	int Add (CScriptEntry &entry);
	CScriptEntry & operator [] (int n) ;
	void RemoveAt(int n);
	void InsertAt (int n, CScriptEntry &entry);
	void MoveBy (int nByX, int nByY);
	int FindProto (int nProto, int nStartAt=0);
	void KillProto(int nProto);
	void KillFrameSet (int nFrameSet);

	CExtraData *AllocExtraData(int nEntryTarget);
	CScriptArray & operator = (CScriptArray & source);

// Implementation
public:
	~CScriptArray();
	void Serialize (CArchive & ar);
	void Read (CFile & file);
	void Write (CFile & file);

	UCHAR m_nBkColor;
	int m_nCurrEntry;
	int m_nMX;
	int m_nMY;
	BOOL m_bSelection;
	CString m_strTitle;
	CString m_strName;

private:
	int m_nSize;
	int m_nMax;
	CScriptEntry *m_arrEntries;

	//CExtraData* m_pExtraData;
	//int m_nExtraDataAlloc;

};

/////////////////////////////////////////////////////////////////////////////

#endif