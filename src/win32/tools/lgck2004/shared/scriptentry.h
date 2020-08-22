#ifndef _SCRIPTENTRY_H
#define _SCRIPTENTRY_H

#include "proto.h"
#include "extradata.h"

// ScriptEntry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScriptEntry 

class CScriptEntry 
{
// Construction
public:
	void Write (CFile & file);
	CScriptEntry (CProto & proto);
	CScriptEntry (CScriptEntry & entry);
	CScriptEntry (int x, int y);
	CScriptEntry();

// Attributes
public:

// Operations
public:
	void MoveTo (CScriptEntry &entry);
	void MoveTo (int x, int y);
	void MoveBy (int byX, int byY);
	CScriptEntry & operator = (CScriptEntry &src);

// Implementation
public:
	~CScriptEntry();
	void Serialize (CArchive & ar);
	void Read (CFile & file);

	union	{
		DWORD m_nBidon;
		WORD m_wU[2];
		BYTE m_bU[4];
	};

	short m_nX;
	short m_nY;
	WORD m_nFrameSet;
	WORD m_nFrameNo;
	BYTE m_nSubClass; // Unused
	BYTE m_nTriggerKey;
	short m_nProto;
	CExtraData *m_pExtraData;

};

/////////////////////////////////////////////////////////////////////////////

#endif