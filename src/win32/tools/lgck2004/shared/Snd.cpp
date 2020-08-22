// Snd.cpp : implementation file
//

#include "stdafx.h"
#include "Snd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const char c_szWAV[] = "WAVE";

#define GROWBY 16
#define SIZEOF sizeof(LPDIRECTSOUNDBUFFER)

/////////////////////////////////////////////////////////////////////////////
// CSnd

CSnd::CSnd()
{

	m_nSize=0;
	m_nMax =GROWBY;
	m_bResource= TRUE;

	m_arrBuffers = (LPDIRECTSOUNDBUFFER *)
		malloc (SIZEOF * m_nMax);

	ZeroMemory (m_arrBuffers, SIZEOF * m_nMax);
	
	m_szName[0] = 0;
	m_bValid = FALSE;

	m_pData=NULL;
	m_nDataSize = 0;	

	m_pDS = NULL;
}

CSnd::~CSnd()
{
	Destroy();
	free (m_arrBuffers);
}

/////////////////////////////////////////////////////////////////////////////
// CSnd message handlers

LPDIRECTSOUNDBUFFER CSnd::LoadSound (IDirectSound *pDS, char * sz)
{	
	LPDIRECTSOUNDBUFFER pdsb = LoadSoundResource (pDS, sz);
	if (pdsb!=NULL) 
		return pdsb;
	else 
		return LoadSoundFile (pDS, sz);	
}


BOOL CSnd::GetWaveResource (HMODULE hModule, LPCTSTR lpName, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData, DWORD *pcbWaveSize)
{
    HRSRC hResInfo;
    HGLOBAL hResData;
    void *pvRes;

    if (((hResInfo = FindResource(hModule, lpName, c_szWAV)) != NULL) &&
        ((hResData = LoadResource(hModule, hResInfo)) != NULL) &&
        ((pvRes = LockResource(hResData)) != NULL) &&
        ParseWaveResource(pvRes, ppWaveHeader, ppbWaveData, pcbWaveSize))
    {
        return TRUE;
    }

    return FALSE;
}

BOOL CSnd::ParseWaveResource(void *pvRes, WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData,DWORD *pcbWaveSize)
{
    DWORD *pdw;
    DWORD *pdwEnd;
    DWORD dwRiff;
    DWORD dwType;
    DWORD dwLength;

    if (ppWaveHeader)
        *ppWaveHeader = NULL;

    if (ppbWaveData)
        *ppbWaveData = NULL;

    if (pcbWaveSize)
        *pcbWaveSize = 0;

    pdw = (DWORD *)pvRes;
    dwRiff = *pdw++;
    dwLength = *pdw++;
    dwType = *pdw++;

    if (dwRiff != mmioFOURCC('R', 'I', 'F', 'F'))
        goto exit;      // not even RIFF

    if (dwType != mmioFOURCC('W', 'A', 'V', 'E'))
        goto exit;      // not a WAV

    pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);

    while (pdw < pdwEnd)
    {
        dwType = *pdw++;
        dwLength = *pdw++;

        switch (dwType)
        {
        case mmioFOURCC('f', 'm', 't', ' '):
            if (ppWaveHeader && !*ppWaveHeader)
            {
                if (dwLength < sizeof(WAVEFORMAT))
                    goto exit;      // not a WAV

                *ppWaveHeader = (WAVEFORMATEX *)pdw;

                if ((!ppbWaveData || *ppbWaveData) &&
                    (!pcbWaveSize || *pcbWaveSize))
                {
                    return TRUE;
                }
            }
            break;

        case mmioFOURCC('d', 'a', 't', 'a'):
            if ((ppbWaveData && !*ppbWaveData) ||
                (pcbWaveSize && !*pcbWaveSize))
            {
                if (ppbWaveData)
                    *ppbWaveData = (LPBYTE)pdw;

                if (pcbWaveSize)
                    *pcbWaveSize = dwLength;

                if (!ppWaveHeader || *ppWaveHeader)
                    return TRUE;
            }
            break;
        }

        pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
    }

exit:
    return FALSE;

}

BOOL CSnd::FillSoundBuffer(IDirectSoundBuffer *pDSB, BYTE *pbWaveData, DWORD cbWaveSize)
{
    if (pDSB && pbWaveData && cbWaveSize)
    {
        LPVOID pMem1, pMem2;
        DWORD dwSize1, dwSize2;

        if (SUCCEEDED(IDirectSoundBuffer_Lock(pDSB, 0, cbWaveSize,
            &pMem1, &dwSize1, &pMem2, &dwSize2, 0)))
        {
            CopyMemory(pMem1, pbWaveData, dwSize1);

            if ( 0 != dwSize2 )
			{
                CopyMemory(pMem2, pbWaveData+dwSize1, dwSize2);
			}

            IDirectSoundBuffer_Unlock(pDSB, pMem1, dwSize1, pMem2, dwSize2);
            return TRUE;
        }
    }
    return FALSE;

}

BOOL CSnd::RestoreSoundBuffer(IDirectSoundBuffer *pDSB, LPCTSTR lpName)
{

	if (SUCCEEDED(IDirectSoundBuffer_Restore(pDSB)) &&
        FillSoundBuffer(pDSB, m_pData, m_nDataSize))
		return TRUE;
	else
		return FALSE;
}

BOOL CSnd::IsValid ()
{
	return m_bValid;
}


BOOL CSnd::Play (DWORD dwPlayFlags)
{
	if (IsValid() == FALSE) {
		OutputDebugString ("Warning - Cannot play from an invalid CSnd object\n");
		return FALSE; 
	}

	LPDIRECTSOUNDBUFFER pdsbuf = 
		GetFreeBuffer ();

	if (pdsbuf!=NULL) {
		pdsbuf->Stop();
		pdsbuf->SetCurrentPosition(0);
		return pdsbuf->Play (0,0, dwPlayFlags);
	}
	else {
		return FALSE;
	}
}

BOOL CSnd::Stop ()
{
	if (IsValid()) { 
		int i;
		for (i=0; i<m_nSize; i++)
		{
			m_arrBuffers[i]->Stop();
			m_arrBuffers[i]->SetCurrentPosition(0);
		}
		return TRUE;
	}
	else	{
		return FALSE;
	}
}

void CSnd::Destroy()
{
	if ((m_bValid) && (m_nSize!=0)) {
		int i;
		for (i=0; i<m_nSize; i++)
		{
			if (m_arrBuffers[i]== NULL)
			{
				m_arrBuffers[i]->Release;
				m_arrBuffers[i]= NULL;
			}
		}

		m_nSize=0;
	}

	if (m_bResource==FALSE)
	{
		if (m_pData!=NULL)
			free (m_pData);
		m_pData = NULL;
		m_nDataSize = 0;
	}

	*m_szName = 0;
	m_bValid = FALSE;

}

BOOL CSnd::Create (IDirectSound *pDS, char *sz)
{
	if (m_bValid)
	{
		Destroy();
	}
    
	LPWAVEFORMATEX pWaveHeader;
    BYTE *pbData;
    UINT cbData;

	m_pDS = pDS;

	m_bResource = TRUE;

    if (GetWaveResource(NULL, 
		sz, 
		&pWaveHeader, 
		&pbData, 
		(ULONG*) &cbData)) {

		// Store info for clones
        m_pData = pbData;
        m_nDataSize = cbData;

		// Load sound resource
		LPDIRECTSOUNDBUFFER pDSB =  LoadSoundResource (pDS, sz);
		m_bValid = pDSB != NULL;
		strcpy (m_szName, sz);

		Add (pDSB);

		if (pDSB==NULL)
		{
			char szTemp[128];
			wsprintf(szTemp,"CSnd Warning: Cannot find RESOURCE %c%s%c\n",34,sz,34);
			OutputDebugString(szTemp);
		}

		return pDSB != NULL;
	}
	else
	{
		LPDIRECTSOUNDBUFFER pDSB =  LoadSoundFile (pDS, sz);
		m_bValid = pDSB != NULL;
		strcpy (m_szName, sz);

		Add (pDSB);

		char szTemp[128];
		if (pDSB==NULL)
		{
			wsprintf(szTemp,"CSnd Warning: Cannot find FILE %c%s%c\n",34,sz,34);
			OutputDebugString(szTemp);
		}
		
		return pDSB != NULL;
	}
}

int CSnd::Add (LPDIRECTSOUNDBUFFER pDSB)
{
	m_arrBuffers[m_nSize] = pDSB;
	m_nSize++;
	if (m_nSize==m_nMax)
	{
		m_nMax = m_nMax + GROWBY;
		LPDIRECTSOUNDBUFFER * t = 
			(LPDIRECTSOUNDBUFFER *)malloc (m_nMax * SIZEOF);
		memcpy (t, m_arrBuffers, m_nSize * SIZEOF);

		free (m_arrBuffers);
		m_arrBuffers = t;
	}
	return m_nSize;
}

LPDIRECTSOUNDBUFFER CSnd::GetFreeBuffer ()
{
	ULONG dwStatus ;
	int n=0;

	for (n=0; n<m_nSize; n++)
	{
		// Get the sound buffer status
		if FAILED ( m_arrBuffers[n]->GetStatus (& dwStatus) ) 
		{
			OutputDebugString ("DSoundBuffer - GetStatus() failed\n");
			return NULL;
		}

		// if buffer lost the attempt to restore it
		if (dwStatus & DSBSTATUS_BUFFERLOST)
		{
			OutputDebugString ("DSoundBuffer - GetStatus : buffer lost\n");
			if (RestoreSoundBuffer(m_arrBuffers[n], m_szName)
				==FALSE)
			{
				OutputDebugString ("DSoundBuffer - cannot restore buffer\n");
				return NULL;
			}
			else
			{
				// Send the selected to the end of the queue
				Add (m_arrBuffers[n]);
				RemoveAt(n);
				return m_arrBuffers[n];			
			}
		}
		else 
		{ // if already playing ???
			if (dwStatus & (DSBSTATUS_LOOPING | DSBSTATUS_PLAYING)) 
			{
				//OutputDebugString ("DSound - already playing\n");
				//Skip to the next one until we find one that's free
			}
			else
			{
				// Send the selected to the end of the queue
				Add (m_arrBuffers[n]);
				RemoveAt(n);
				return m_arrBuffers[n];
			}
		}
	}

	//OutputDebugString ("DSound - oldest replaced\n");

	// Send the selected to the end of the queue
	Add (m_arrBuffers[0]);
	RemoveAt(0);
	return m_arrBuffers[m_nSize-1];
}

void CSnd::RemoveAt (int n)
{
	int i;
	for (i=n; i<m_nSize-1; i++)
	{
		m_arrBuffers[i] = m_arrBuffers[i+1];
	}

	m_nSize--;
	m_arrBuffers[m_nSize] = NULL;
}

int CSnd::GetSize()
{
	return m_nSize;
}

BOOL CSnd::CreateClones (int n)
{
	LPDIRECTSOUNDBUFFER pdsb;

	if (IsValid()==FALSE)
		return FALSE;

	int i;
    for (i=0; i<n; i++)
    {
		if (FAILED(m_pDS->DuplicateSoundBuffer 
			(m_arrBuffers[0], &pdsb)))
		{
			pdsb = LoadSound(m_pDS, m_szName);
			if (pdsb==NULL) 
				return FALSE;
		}
		Add (pdsb);
	}
	return TRUE;
}

LPDIRECTSOUNDBUFFER CSnd::LoadSoundResource (IDirectSound *pDS, char * sz)
{
    IDirectSoundBuffer *pDSB = NULL;
    DSBUFFERDESC dsBD = {0};
    BYTE *pbWaveData;

	char *lpName = sz;

    if (GetWaveResource(NULL, lpName, &dsBD.lpwfxFormat, &pbWaveData, &dsBD.dwBufferBytes))
    {
        dsBD.dwSize = sizeof(dsBD);
        dsBD.dwFlags = DSBCAPS_STATIC | DSBCAPS_GETCURRENTPOSITION2;

        if (SUCCEEDED(IDirectSound_CreateSoundBuffer(pDS, &dsBD, &pDSB, NULL)))
        {
            if (!FillSoundBuffer(pDSB, pbWaveData, dsBD.dwBufferBytes))
            {
                IDirectSoundBuffer_Release(pDSB);
                pDSB = NULL;
            }
        }
        else
        {
            pDSB = NULL;
        }
    }
    return pDSB;
}


LPDIRECTSOUNDBUFFER CSnd::LoadSoundFile (IDirectSound *pDS, char * sz)
{
    IDirectSoundBuffer *pDSB = NULL;
    DSBUFFERDESC dsBD = {0};
	BYTE *pbWaveData;

	CFile file;
	CFileException e;

	if (!file.Open(sz, CFile::modeRead
		| CFile::typeBinary, &e ))
	{
#ifdef _DEBUG
		afxDump << "File " << sz << " could not be opened " << e.m_cause << "\n";
#endif
		return NULL;
	}		

	CFileStatus status;
	if (file.GetStatus (status) == FALSE) {
		OutputDebugString ("File doesn't exist\n");
		return NULL;
	}

	BYTE *buf =(BYTE*) malloc(status.m_size);
	if (buf==NULL)  {
		OutputDebugString ("Insufficient memory\n");
		return NULL;
	}

	file.Read(buf, status.m_size);
	file.Close();

	if (ParseWaveResource (buf, &dsBD.lpwfxFormat, &pbWaveData, &dsBD.dwBufferBytes))
	{
        dsBD.dwSize = sizeof(dsBD);
        dsBD.dwFlags = DSBCAPS_STATIC | DSBCAPS_GETCURRENTPOSITION2;

        if (SUCCEEDED(IDirectSound_CreateSoundBuffer(pDS, &dsBD, &pDSB, NULL)))
        {
            if (!FillSoundBuffer(pDSB, pbWaveData, dsBD.dwBufferBytes))
            {
                IDirectSoundBuffer_Release(pDSB);
                pDSB = NULL;
            }
			else  {
				m_bResource = FALSE;
			}
        }
        else  {
            pDSB = NULL;
        }
	}

	if (pDSB==NULL) {
		free (buf);
	}
	else {
		m_pData = buf;
		m_nDataSize = status.m_size;
	}

	return pDSB;
}

char * CSnd::GetName()
{
	return m_szName;
}

BOOL CSnd::IsUnique()
{
	return (m_nSize == 1);
}

void CSnd::SetName(char *szName)
{
	if (szName)
	{
		strcpy(m_szName, szName);
	}
}
