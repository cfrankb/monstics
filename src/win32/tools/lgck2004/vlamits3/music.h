// Music.h : header file
//

#ifndef _MUSIC_H
#define _MUSIC_H

#include <dmusicc.h>
#include <dmusici.h>
#include <winnls.h>

#ifndef MULTI_TO_WIDE
#define MULTI_TO_WIDE( x,y )  MultiByteToWideChar( CP_ACP, \
        MB_PRECOMPOSED, y, -1, x, _MAX_PATH );
#endif

/////////////////////////////////////////////////////////////////////////////
// CMusic 

class CMusic 
{
// Construction
public:
	BOOL HasPath();
	BOOL SetPath(char *szPath, BOOL bRelative=FALSE);
	IDirectMusicLoader * GetLoader();
	CMusic();
	BOOL Create (LPDIRECTSOUND lpDS, char *sz, int nType=-1);

// Attributes
public:
	BOOL IsValid();
	char * GetName();

// Operations
public:
	void SetName(char *szName);
	BOOL Play ();
	void Stop();

protected:
	BOOL LoadMIDI(char *szFilename);

// Implementation
public:
	~CMusic();
	void Destroy();

protected:
	// DirectMusic Objects
	//static IDirectMusicLoader*      m_lpDMLoader;      // DirectMusicLoader
	IDirectMusicPerformance* m_lpDMPerformance; // DirectMusicPerformance
	IDirectMusicSegment*     m_lpDMSegment;     // DirectMusicSegment
	IDirectMusicSegmentState* m_lpDMSegState;	// DirectMusicSegment State

	// DirectSound
	LPDIRECTSOUND m_lpDS;

	//static int m_nMusicCount;
	char m_szName[_MAX_PATH];
	BOOL m_bValid;
};

#endif

/////////////////////////////////////////////////////////////////////////////
