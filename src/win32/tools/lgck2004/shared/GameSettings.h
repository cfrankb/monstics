// GameSettings.h : header file
//

#ifndef _GAMESETTINGS_H
#define _GAMESETTINGS_H

/////////////////////////////////////////////////////////////////////////////
// CGameSettings window

class CGameSettings 
{
// Construction
public:
	void Write (CFile & file);
	void Read(CFile & file);
	void Serialize(CArchive & ar);
	void Init();
	void Forget();
	CGameSettings();

// Attributes
public:

// Operations
public:

// Implementation
public:
	~CGameSettings();

	// page 2
	BYTE m_nLives;
	BYTE m_nHP;
	BYTE m_nMaxLives;
	BYTE m_nMaxHP;

	BYTE m_bAtDeathResetHP;
	BYTE m_bAtDeathResetLev;
	WORD m_b000;

	// page 3
	BYTE	m_bAtLevelResetHP;
	BYTE	m_bContinuity;
	BYTE	m_bForceDefObj;
	BYTE	m_bInheritPlrObj;

	BYTE	m_bResizeLevel;
	BYTE	m_b001[3];
	WORD	m_nLevelHei;
	WORD	m_nLevelLen;

	// page 4
	char m_szSigns[_MAX_PATH];
	char m_szSignsChars[_MAX_PATH];
	char m_szPts[_MAX_PATH];

protected:
};

/////////////////////////////////////////////////////////////////////////////
#endif