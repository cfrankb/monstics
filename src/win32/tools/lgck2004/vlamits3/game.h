// Game.h header file
//

#ifndef _GAME_H
#define _GAME_H

#include <mmsystem.h>
#include <dinput.h>
#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>
#include <dmusicc.h>
#include <dmusici.h>
#include <winnls.h>

#include "GameFile3.h"
#include "sndarray.h"
#include "file.h"
#include "music.h"

// *** GAME AREA

#define SCREENLEN		(320*2)
#define SCREENHEI		(240*2)
//#define SCREENLEN		(1024)
//#define SCREENHEI		(768)

#define BUFFERLEN		(0xb00)
#define BUFFERHEI		(0x600)

#define WALK_DELAY		6
#define FIRE_DELAY		20
#define CONST_TIMEOUT	240

// *** AIMS

#define UP				0
#define DOWN			1
#define LEFT			2
#define RIGHT			3
#define LEAP_LEFT		0x12
#define LEAP_RIGHT		0x13
#define JUMP_UP			0x20
#define JUMP_DOWN		0x21
#define JUMP_LEFT		0x22
#define JUMP_RIGHT		0x23

#define LEFT_UP			4
#define RIGHT_UP		5
#define LEFT_DOWN		6
#define RIGHT_DOWN		7
#define PAUSE			-2
#define SEPARATOR		-1
#define HERE			255

// *** JOY STATUS

#define JOY_UP			1
#define JOY_DOWN		2
#define JOY_LEFT		4
#define JOY_RIGHT		8
#define JOY_JUMP		16
#define JOY_FIRE		32
#define JOY_ZKEY		64

// *** POINTS

#define PTS_NONE		0
#define PTS_10			1
#define PTS_25			2
#define PTS_50			3
#define PTS_100			4
#define PTS_200			5
#define PTS_300			6
#define PTS_400			7
#define PTS_500			8
#define PTS_1000		9
#define PTS_2000		10
#define PTS_5000		11
#define PTS_10000		12

// *** SOUNDS

#define SND_NO_SOUND	0
#define SND_CLICK		1
#define SND_SHORTJUMP	2
#define SND_WALK		3
#define SND_FALL		4
#define SND_POUFLIGHT	5
#define SND_JUMP		6
#define SND_METAL		7
#define SND_WALK2		8
#define SND_OUCH		9
#define SND_TELEPORT	10

// *** FLAGS

#define FLAG_NONE		0x0
#define FLAG_METAL		0x1
#define FLAG_NOSOUND	0x2
#define FLAG_WATER		0x4
#define FLAG_DEATH		0x8
#define FLAG_HIT		0x10
#define FLAG_TELEPORT   0x20

// *** STATES

#define STATE_NONE		0x0
#define STATE_FALL		0x1
#define STATE_DEAD		0x2
#define STATE_HIT		0x4
#define STATE_JUMP		0x8
#define STATE_BEGINNING 0x10
#define STATE_FIRING	0x20
// MORE STATES 0x40 0x80

// *** CONSTANTS

#define AIM_FLAG		m_bU[0]
#define STATE_FLAG		m_bU[1]
#define HIT_POINTS		m_bU[2]
#define TIMEOUT_DELAY	m_bU[3]
#define JUMP_STATUS		m_nSubClass

#include "..\scr4edit\vlamits3.txt"

#ifndef MULTI_TO_WIDE
#define MULTI_TO_WIDE( x,y )  MultiByteToWideChar( CP_ACP, \
        MB_PRECOMPOSED, y, -1, x, _MAX_PATH );
#endif

/////////////////////////////////////////////////////////////////////////////
// CGame 

class CGame : public CGameFile3
{
// Construction
public:
	BOOL GetEpisodeFilename(CString & str);
	void SetGamma(int i);
	int GetGamma();
	void InitGamma();
	int MakeEpisodeList(CStringArray & arr);
	BOOL TestAimEx (CScriptEntry & entry, int nAim, int nTimes);
	void Debug(char *sz);
	void HurtPlayer(CScriptEntry & player, CScriptEntry & actor);
	BOOL DrawScreenHelper(LPDIRECTDRAWSURFACE lpDDS);
	BOOL BltScreen();
	BOOL PrepareLevel (CScriptArray &s);
	void ApplyGamma();
	//BYTE GammaCorrection(BYTE nColor);
	void PlayLevelIntro(DDSURFACEDESC & ddsurfdesc);
	void ShowScore (BOOL bShow);
	void PlotText(DDSURFACEDESC & ddsurfdesc, char *szText, int x, int y, BYTE nColor, BOOL bSmall);
	void AddToScore(int nPoints);
	BOOL DrawScore (DDSURFACEDESC & ddsurfdesc);
	BOOL IsVisible (CScriptEntry & entry);
	void ManageAuto (int nTicks);
	void InitEntry (CScriptEntry & entry);
	int SignToFrameNo (char nSign, BOOL bSmall);
	void CastTrigger (CScriptEntry & triggerGen);
	BOOL InitEpisode (CString strFilename);
	BOOL PackGraphics();
	BOOL InitSounds ();
	void Destroy();
	CGame();

// Attributes
public:

// Operations
public:
	// CScriptArray
	void HideSystemClass (CScriptArray & script, BOOL bHide);
	void SplitScript (CScriptArray &sS, CScriptArray &sBK, CScriptArray & sFW);
	BOOL MapScript (CScriptArray &s, UCHAR * &pMap, int nLen, int nHei, BOOL bBK=TRUE);
    void FillSurface (UCHAR nColor, UCHAR *pDest, int nLen, int nHei, int nPitch);
	void OutputOBL3 (CSS3Frame * pFrame, int x, int y, int maxX, int maxY, BOOL bClear, UCHAR *pDest, int nPitch, BYTE nColor );

	BOOL DrawToBuffer ( int nLen, int nHei, int nMaxX, int nMaxY, DDSURFACEDESC & ddsurfdesc);
	void MoveTo (int x, int y);
	void MoveBy (int x, int y);
	BOOL InitLevel (CScriptArray &s);
	BOOL InitLevel (int n);
	void Animate(UINT nTicks);

	BOOL DrawScreen ();
	BOOL AddSprite (CScriptEntry & entry);
	BOOL FillSurface(UCHAR nColor);

	// Game play functions	
	BOOL Init (CWnd *pWnd);
	BOOL Load(char *szName);
	BOOL Save(char *szName);

	BOOL UnMapSprite (int nEntry);
	BOOL MapSprite (int nEntry, BOOL bSmart=FALSE);
	UCHAR * GetMapEntry (CScriptEntry & entry);
	UCHAR * GetMapEntry (int x, int y);

	BOOL GetState (CScriptEntry & entry, int nState);
	void SetState (CScriptEntry & entry, int nState, BOOL bOn);
	void MoveSprite (CScriptEntry & entry, int nAim);
	void KillSprite (CScriptEntry & sprite);

	BOOL CanFall (CScriptEntry & entry);
	BOOL CanWalk (CScriptEntry & entry, int nAim, BOOL bActor=FALSE);
	BOOL TestAim (CScriptEntry & entry, int nAim);
	BOOL IsPlayerThere (CScriptEntry & entry, int nAim);
	BOOL CanFallHigh (CScriptEntry & entry);
	BOOL IsPlayerAlign(CScriptEntry & entry, CScriptEntry & player, int nAim);

	void ManageObjects (int nTicks);
	
	// Player specific functions
	BOOL ManagePlayer (int nTicks);
	void ManagePlayerJump (CScriptEntry & player);
	int ManagePlayerMovements (CScriptEntry & player, UINT & nJoyState, int nTicks, int nWalkSound);
	void ManagePlyTimerOutCounter (CScriptEntry & player, UINT nJoyState);
	int CheckPlayerHit (CScriptEntry & player);
	BOOL ManagePlayerFiring (CScriptEntry & player, int nTicks, int nJoyState);

	void AutoCenter (CScriptEntry & player, UINT nAim);
	BOOL CenterOnPlayer (CScriptEntry & player);
	BOOL PlayerZKey();

	// Helper Functions
	BOOL Fail (char *szText);
	int XOR (int a, int b);

	// DDraw
	void ReleaseDDraw ();
	void InitDDraw(CWnd *pWnd);
	BOOL RestoreDDraw (CWnd *pWnd);
	BOOL CreatePalette(CClientDC *dc, LPDIRECTDRAW p_lpDD, LPDIRECTDRAWPALETTE * p_lpDDPal  );

	// DSound
	BOOL InitDSound (CWnd *pWnd, GUID *pguid=NULL);
	void ReleaseDSound ();

	// DMusic
	/*
	BOOL InitDMusic(CWnd *pWnd);
	void ReleaseDMusic();
	BOOL LoadMIDI(char *szFilename);
	*/

	// DInput
	BOOL InitDInput (CWnd *pWnd);
	void ReleaseDInput ();
	LPDIRECTINPUTDEVICE2 CreateIDevice2( LPDIRECTINPUT lpdi, GUID* pguid );
	BOOL InitIDevice(LPDIRECTINPUTDEVICE2 & lpdid2, GUID* pguid, CWnd *pWnd );
	BOOL InitJoystick( LPDIRECTINPUTDEVICE2 lpdid2 );
	BOOL PollDevice( LPDIRECTINPUTDEVICE2 lpdid2, UINT & nState );
	BOOL SelectDevice (CWnd *pWnd);

// Implementation
public:
	~CGame();

	// Game variables
	CSndArray m_arrSounds;
	CMusic m_music;
	CMusic m_music2;

	CScriptArray m_sFW;
	CScriptArray m_sBK;

	UCHAR * m_pMap ;
	UCHAR * m_pScrollBK;

	int m_nMX ;
	int m_nMY ;
	int m_nProtoPoints;		// What's the proto for "points"
	int m_nProtoSigns;		// What's the proto for "signs"
	int m_nProtoPlayer;		// What's the proto for "players"
	int m_nPlayerEntry;		// Entry that is player object

	BOOL m_bGameOver ;
	BOOL m_bPause ;
	BOOL m_bActive ;
	BOOL m_bPlayingMusic ;
	BOOL m_bCritical;
	BOOL m_bDrawing;
	BOOL m_bPrimary;

	int m_nScore;
	int m_nLifeForce;
	int m_nLives;

	int m_nShowStatus;
	int m_nStatusCount;

	int m_bPlayLevelIntro;
	int m_nLevelIntroStatus;

	//int m_nGammaLevel;

	// DirectDraw Objects
	LPDIRECTDRAW            m_lpDD;				// DirectDraw object
	LPDIRECTDRAWSURFACE     m_lpDDSPrimary;		// DirectDraw primary surface
	LPDIRECTDRAWPALETTE		m_lpDDPal;			// DirectDraw Palette
	LPDIRECTDRAWSURFACE		m_lpDDSBack;		// DirectDraw backbuffer surface
	LPDIRECTDRAWCLIPPER     m_lpDDClipper;		// DirectDraw clipper.

	// DirectSound Objects
	LPDIRECTSOUND			m_lpDS;				// DirectSound object

	// DirectMusic Objects
	/*
	IDirectMusicLoader*      m_lpDMLoader;      // DirectMusicLoader
	IDirectMusicPerformance* m_lpDMPerformance; // DirectMusicPerformance
	IDirectMusicSegment*     m_lpDMSegment;     // DirectMusicSegment
	IDirectMusicSegmentState* m_lpDMSegState;	// DirectMusicSegment State
	*/

	// DirectInput Objects
	LPDIRECTINPUT			m_lpdi;				// DirectInput 
	LPDIRECTINPUTDEVICE2	m_lpdid2;			// DirectInput device
	LPDIRECTINPUTDEVICE2	m_lpdid2Mouse;		// SystemMouse

};

/////////////////////////////////////////////////////////////////////////////

#endif