// Snd.h : header file
//
#ifndef _SND_H
#define _SND_H

#include <mmsystem.h>
#include <dsound.h>

/////////////////////////////////////////////////////////////////////////////
// CSnd 

class CSnd 
{
// Construction
public:
	CSnd();

// Attributes
public:
	BOOL IsUnique();
	BOOL IsValid ();
	int GetSize();
	char * GetName();

// Operations
public:
	void SetName(char *szName);
	BOOL Create (IDirectSound *pDS, char *sz);
	BOOL CreateClones (int n);
	BOOL Play (DWORD dwPlayFlags=0);
	BOOL Stop ();
	void RemoveAt (int n);
	int Add (LPDIRECTSOUNDBUFFER pDSB);
	void Destroy();

private:
	BOOL RestoreSoundBuffer(IDirectSoundBuffer *pDSB, LPCTSTR lpName);
	BOOL FillSoundBuffer(IDirectSoundBuffer *pDSB, BYTE *pbWaveData, DWORD cbWaveSize);
	BOOL ParseWaveResource(void *pvRes, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData,DWORD *pcbWaveSize);
	BOOL GetWaveResource (HMODULE hModule, LPCTSTR lpName, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pcbWaveSize);
	LPDIRECTSOUNDBUFFER LoadSound (IDirectSound *pDS, char *sz);
	LPDIRECTSOUNDBUFFER LoadSoundResource (IDirectSound *pDS, char *sz);
	LPDIRECTSOUNDBUFFER LoadSoundFile (IDirectSound *pDS, char *sz);
	LPDIRECTSOUNDBUFFER GetFreeBuffer ();

// Implementation
public:
	~CSnd();

protected:
	// for handling clones
	IDirectSound * m_pDS;
	BYTE * m_pData;
	int m_nDataSize;

	// managing the object
	BOOL m_bResource;
	BOOL m_bValid;
	char m_szName[_MAX_PATH];
	int m_nSize;
	int m_nMax;
	LPDIRECTSOUNDBUFFER * m_arrBuffers;
};

/////////////////////////////////////////////////////////////////////////////

#endif