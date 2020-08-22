// Proto.h : header file
//

#ifndef _PROTO_H
#define _PROTO_H

/////////////////////////////////////////////////////////////////////////////
// CProto 

class CProto
{
// Construction
public:
	char* GetName();
	CProto (CString &str);
	CProto (CProto & proto);
	CProto();

// Attributes
public:

// Operations
public:
	CProto & operator = (CProto & proto);

// Implementation
public:
	void Read (CFile & file, int nSize=0);
	void Serialize (CArchive & ar, int nSize=0);
	~CProto();

	UCHAR m_nClass;
	UCHAR m_nObjectKey;
	UCHAR m_nTriggerType;
	UCHAR m_bAnimate;

	char  m_szName[32];

	short m_nFrameSet;
	short m_nFrameNo;
	
	UCHAR m_nMoveSpeed;
	UCHAR m_nAniSpeed;	
	UCHAR m_nDefaultAim;
	UCHAR m_nPoints; 

	short m_nSound;// unused
	UCHAR m_nUserTag;
	UCHAR m_nSFreq; // unused

	short m_nChProto;
	short m_nChSound;

	UCHAR m_bIgnoreStops;
	UCHAR m_nDamages;
	UCHAR m_nHitPoints;
	UCHAR m_nPowerLevel;

	UCHAR m_nRbDelay;
	UCHAR m_nRebirths;

	short m_nAutoProto;
	short m_nAutoBullet;
	short m_nAutoSound;
	UCHAR m_bAutoTrigger;
	UCHAR m_bExtra;

	UCHAR m_nAutoProtoTime;
	UCHAR m_nAutoBulletTime;
	UCHAR m_nAutoSoundTime;
	UCHAR m_nAutoTriggerTime;

};

/////////////////////////////////////////////////////////////////////////////
#endif