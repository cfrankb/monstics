// shared.cpp
//

#include "stdafx.h"
#include "shared.h"

int DoProtoProps(CProto & proto, CScr4editDoc *pDoc)
{

	CProtoSheet propSheet;
	CStrValArray & arrClasses = 
		pDoc->m_game3.m_arrClasses;

	// Page 1
	propSheet.m_Page1.m_pDoc = pDoc;
	propSheet.m_Page1.m_nFrameNo = proto.m_nFrameNo;
	propSheet.m_Page1.m_nClass = arrClasses.GetIndexFor (proto.m_nClass);

	propSheet.m_Page1.m_nFrameSet = proto.m_nFrameSet;
	propSheet.m_Page1.m_nTrigger= proto.m_nTriggerType; 
	propSheet.m_Page1.m_nObjectKey= proto.m_nObjectKey;
	propSheet.m_Page1.m_bAnimate = proto.m_bAnimate;
	propSheet.m_Page1.m_strName = proto.m_szName;

	// Page 2
	propSheet.m_Page2.m_pDoc = pDoc;
	propSheet.m_Page2.m_nMoveSpeed = proto.m_nMoveSpeed;
	propSheet.m_Page2.m_nAniSpeed = proto.m_nAniSpeed;
	propSheet.m_Page2.m_nDefaultAim = proto.m_nDefaultAim;

	propSheet.m_Page2.m_nUserTag = proto.m_nUserTag ;

	//propSheet.m_Page2. m_bIgnoreStops = proto. m_bIgnoreStops;
	propSheet.m_Page2. m_nDamages = proto. m_nDamages;
	propSheet.m_Page2. m_nHitPoints= proto. m_nHitPoints;
	propSheet.m_Page2. m_nPowerLevel= proto.m_nPowerLevel ;

	// Page 3
	propSheet.m_Page3.m_pDoc = pDoc;
	propSheet.m_Page3.m_nPoints = proto.m_nPoints;
	propSheet.m_Page3.m_nChProto= proto.m_nChProto;
	propSheet.m_Page3.m_nChSound = proto.m_nChSound;

	propSheet.m_Page3. m_nRbDelay = proto. m_nRbDelay;
	propSheet.m_Page3. m_nRebirths= proto. m_nRebirths;

	// Page 4
	propSheet.m_Page4.m_pDoc = pDoc;
	propSheet.m_Page4.m_nAutoProto = proto.m_nAutoProto;
	propSheet.m_Page4.m_nAutoBullet = proto.m_nAutoBullet;
	propSheet.m_Page4.m_nAutoSound = proto.m_nAutoSound;
	propSheet.m_Page4.m_bAutoTrigger = proto.m_bAutoTrigger;

	propSheet.m_Page4.m_nAutoProtoTime = proto.m_nAutoProtoTime;
	propSheet.m_Page4.m_nAutoBulletTime = proto.m_nAutoBulletTime;
	propSheet.m_Page4.m_nAutoSoundTime = proto.m_nAutoSoundTime;
	propSheet.m_Page4.m_nAutoTriggerTime = proto.m_nAutoTriggerTime;

	if (propSheet.DoModal()==IDOK)
	{
		CProtoArray & arrProto = pDoc->m_game3.m_arrProto;

		// Page 1
		proto.m_nClass = arrClasses[propSheet.m_Page1.m_nClass]->m_nVal;	

		char sz[128];
		wsprintf(sz,"OUT: Class %d\n", proto.m_nClass);
		OutputDebugString(sz);
		
		proto.m_nFrameNo= propSheet.m_Page1.m_nFrameNo;
		proto.m_nFrameSet = propSheet.m_Page1.m_nFrameSet;
		proto.m_nTriggerType = propSheet.m_Page1.m_nTrigger;
		proto.m_nObjectKey = propSheet.m_Page1.m_nObjectKey;
		proto.m_bAnimate = propSheet.m_Page1.m_bAnimate;
		strcpy (proto.m_szName, 
			propSheet.m_Page1.m_strName.GetBuffer(32));

		// Page 2
		proto.m_nMoveSpeed = propSheet.m_Page2.m_nMoveSpeed ;
		proto.m_nAniSpeed = propSheet.m_Page2.m_nAniSpeed ;
		proto.m_nDefaultAim = propSheet.m_Page2.m_nDefaultAim;

		proto.m_nUserTag = propSheet.m_Page2.m_nUserTag  ;

		//proto.m_bIgnoreStops = propSheet.m_Page2. m_bIgnoreStops;
		proto.m_nDamages = propSheet.m_Page2. m_nDamages;
		proto.m_nHitPoints= propSheet.m_Page2. m_nHitPoints;
		proto.m_nPowerLevel= propSheet.m_Page2. m_nPowerLevel ;

		// Page 3
		proto.m_nPoints = propSheet.m_Page3.m_nPoints;
		proto.m_nChProto = propSheet.m_Page3.m_nChProto;
		proto.m_nChSound = propSheet.m_Page3.m_nChSound ;

		proto.m_nRbDelay = propSheet.m_Page3.  m_nRbDelay;
		proto.m_nRebirths= propSheet.m_Page3.m_nRebirths;
		
		// Page 4
		proto.m_nAutoProto = propSheet.m_Page4.m_nAutoProto ;
		proto.m_nAutoBullet = propSheet.m_Page4.m_nAutoBullet;
		proto.m_nAutoSound = propSheet.m_Page4.m_nAutoSound ;
		proto.m_bAutoTrigger = propSheet.m_Page4.m_bAutoTrigger ;

		proto.m_nAutoProtoTime = propSheet.m_Page4.m_nAutoProtoTime ;
		proto.m_nAutoBulletTime = propSheet.m_Page4.m_nAutoBulletTime ;
		proto.m_nAutoSoundTime = propSheet.m_Page4.m_nAutoSoundTime  ;
		proto.m_nAutoTriggerTime = propSheet.m_Page4.m_nAutoTriggerTime ;

		return IDOK;
	}
	return IDCANCEL;
}