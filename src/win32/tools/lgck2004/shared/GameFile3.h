#ifndef GAMEFILE3_H
#define GAMEFILE3_H

#include "obl3array.h"
#include "scriptarray.h"
#include "protoarray.h"
#include "strvalarray.h"
#include "tagArray.h"
#include "extraarray.h"
#include "gamesettings.h"

// *** TRIGGERS

#define TRIGGER_KEYS	0x0f
#define TRIGGER_EXTRA2  0x10
#define TRIGGER_EXTRA1  0x20
#define TRIGGER_FROZEN  0x40
#define TRIGGER_HIDDEN	0x80

#define MOVESTEP 8

// GameFile3.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CGameFile3 

class CGameFile3 
{
// Construction
public:
	static BOOL IsValid(CString & strFilename);
	CGameFile3();

// Attributes
public:
	int GetSize();

// Operations
public:
	CScriptArray * operator [] (int n);
	void Forget ();
	void DrawScript (CScriptArray *pSA, int nMX, int nMY, void *pDest, int nLen, int nHei,  int nPitch);
	void InsertScript (int n, CScriptArray *pSA);
	void AddScript (CScriptArray *pScriptArray);
	void RemoveScript (int n);
	void Init();
	int WhoIs (CScriptArray & script, int x, int y);
	BOOL UpdateOBL3 (CString &strError);
	void KillProto (int nProto);
	void KillFrameSet (int nFrameSet);

// Implementation
public:
	~CGameFile3();
	BOOL Extract (CString & strFilename);
	void Serialize (CArchive & ar);
	void Read (CFile & file);


	int m_nScripts;
	int m_nCurrScript;

	CString			m_strName;
	CString			m_strInformation;

	COBL3Array		m_arrOBL3;
	CProtoArray		m_arrProto;
	CScriptArray	**m_arrScripts;
	CStrValArray	m_arrClasses;

	CTagArray		m_arrSoundData;
	CTagArray		m_arrPoints;
	CTagArray		m_arrUserDefs;
	CTagArray		m_arrActions;

	CExtraArray		m_arrExtra;

	CGameSettings	m_settings;
};

/////////////////////////////////////////////////////////////////////////////

#endif