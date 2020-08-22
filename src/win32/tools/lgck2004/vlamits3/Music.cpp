// Music.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMusic

static IDirectMusicLoader * g_lpDMLoader = NULL;
static int g_nMusicCount = 0;
static BOOL g_bHasPath = FALSE;
static char g_szPath[_MAX_PATH]="";

CMusic::CMusic()
{
	// DirectMusic Objects
	//m_lpDMLoader         = NULL;
	m_lpDMPerformance    = NULL;
	m_lpDMSegment        = NULL;
	m_lpDMSegState		 = NULL;

	// DirectSound
	m_lpDS = NULL;

	// Our objects
	m_bValid = FALSE;
	*m_szName = 0;
}

CMusic::~CMusic()
{
	if (m_bValid)
	{
		char szTemp[128] ;
		wsprintf(szTemp,"CMusic: 'NOT GOOD' i.e. Forgot to destroy %c%s%c??!\n",
			34,m_szName,34);
		OutputDebugString(szTemp);
	}
	//Destroy();
}

/////////////////////////////////////////////////////////////////////////////
// CMusic message handlers

BOOL CMusic::Create (LPDIRECTSOUND lpDS, char *sz, int nType)
{
	if (m_bValid)
	{
		Destroy();
	}

	OutputDebugString("TESTING CMusic.Create()\n");

	CWnd *pWnd = (CWnd*) AfxGetMainWnd();

    // Create performance object
    if (FAILED(CoCreateInstance( CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC, 
                      IID_IDirectMusicPerformance, (void**)&m_lpDMPerformance )))
	{

		OutputDebugString("FATAL: Cannot Create DirectMusicPerformance Object\n");
		return FALSE;
	}
			
	// Initialize DirectMusicPerformance
	if (FAILED(m_lpDMPerformance->Init( 
			NULL,				// IDirectMusic**,
			m_lpDS,				// LPDIRECTSOUND 
			pWnd->m_hWnd ))) 	// HWND
	{
		OutputDebugString("FATAL: Cannot Init DirectMusicPerformance Object\n");
		return FALSE;
	}

	// Initialize default port 
	if (FAILED(m_lpDMPerformance->AddPort(NULL)))
	{
		OutputDebugString("FATAL: Cannot Add default port to DirectMusicPerformance Object\n");
		return FALSE;
	}	

	if (!g_lpDMLoader)
	{
		// Create loader object
		if (FAILED (CoCreateInstance( CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC, 
                      IID_IDirectMusicLoader, (void**)&g_lpDMLoader )))
		{
			OutputDebugString("FATAL: Cannot Create DirectMusicLoader Object\n");
			return FALSE;	
		}
	}

	// Load MIDI file
	if (!LoadMIDI(sz))
	{
		OutputDebugString("FATAL: Cannot load MIDI file\n");
		return FALSE;
	}

	m_bValid = TRUE;

	char szTemp[128];
	wsprintf(szTemp, "Info -- CMusic for %c%s%c created\n",
		34, sz,34);
	OutputDebugString(szTemp);

	g_nMusicCount++;

	return TRUE;
}

void CMusic::Destroy()
{
	if (m_bValid && g_nMusicCount)
	{
		g_nMusicCount--;
	}

	m_bValid = FALSE;
	*m_szName = 0;

	if (g_lpDMLoader && !g_nMusicCount)
	{
		g_lpDMLoader->Release(); 
		g_lpDMLoader=NULL;
	}

	if (m_lpDMSegment)
	{
		// Unload instruments – this will cause silence.
		// CloseDown unloads all instruments, so this call is also not 
		// strictly necessary.

		if (m_lpDMPerformance)
		{
			m_lpDMSegment->SetParam(GUID_Unload, 
				(unsigned int)-1, 0, 0, (void*)m_lpDMPerformance);
		}

	    m_lpDMSegment->Release();
		m_lpDMSegment = NULL;
	}

	if (m_lpDMSegState)
	{
	    m_lpDMSegState->Release();
		m_lpDMSegState = NULL;
	}

	if (m_lpDMPerformance)
	{
		// If there is any music playing, stop it. This is 
		// not really necessary, because the music will stop when
		// the instruments are unloaded or the performance is
		// closed down.

	    m_lpDMPerformance->Stop( NULL, NULL, 0, 0 );
		
		m_lpDMPerformance->CloseDown();
		m_lpDMPerformance->Release();
		m_lpDMPerformance = NULL;
	}
}

BOOL CMusic::IsValid()
{
	return m_bValid;
}

char * CMusic::GetName()
{
	return m_szName;
}

void CMusic::SetName(char *szName)
{
	if (szName)
	{
		strcpy(m_szName, szName);
	}
}

BOOL CMusic::LoadMIDI(char *szFilename)
{
	// Set path

	//char szPath[_MAX_PATH] = "e:\\toolkit\\musics";
	WCHAR wszPath[_MAX_PATH];
	MULTI_TO_WIDE(wszPath, g_szPath);

    if (FAILED(g_lpDMLoader->SetSearchDirectory(GUID_DirectMusicAllTypes,
        wszPath, FALSE)))
	{
		OutputDebugString("BAD: Cannot set DirectMusicLoader' search directory\n");
		return FALSE;
	}  

	// Prepare to load file

	WCHAR wszFilename[_MAX_PATH];
	MULTI_TO_WIDE(wszFilename, szFilename);

	DMUS_OBJECTDESC ObjDesc;

    ObjDesc.guidClass = CLSID_DirectMusicSegment;
    ObjDesc.dwSize = sizeof(DMUS_OBJECTDESC);
    wcscpy( ObjDesc.wszFileName, wszFilename );
    ObjDesc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;

    if (FAILED(g_lpDMLoader->GetObject(&ObjDesc,
		IID_IDirectMusicSegment2, (void**) &m_lpDMSegment)))
	{
		OutputDebugString("BAD: Failed to open MIDI file\n");
		return FALSE;
	}

	// Set format to "standardMIDI"
	if (FAILED(m_lpDMSegment->SetParam(GUID_StandardMIDIFile,
            (unsigned long)-1, 0, 0, (void*)m_lpDMPerformance)))
	{
		OutputDebugString("BAD: Cannot Set Format to 'StandardMIDIFile'\n");
		return FALSE;
	}

	// Download segment
	if (FAILED(m_lpDMSegment->SetParam(GUID_Download, 
		(unsigned long)-1, 0, 0, (void*)m_lpDMPerformance)))
	{
		OutputDebugString("BAD: Couldn't download segment\n");
		return FALSE;
	}

	return TRUE;
}

BOOL CMusic::Play ()
{
	if (m_bValid)
	{
		Stop();

		if (m_lpDMSegState)
		{
			m_lpDMSegState ->Release();
			m_lpDMSegState = NULL;
		}

		// Play Segment
		if (FAILED(m_lpDMPerformance->PlaySegment(m_lpDMSegment, 0, 0, &m_lpDMSegState)))
		{
			OutputDebugString("BAD: Play segment failed\n");
			return FALSE;	
		}
	}
	else
	{
		OutputDebugString("BAD: Cannot play from an invalid CMusic object\n");
	}

	return m_bValid;
}


void CMusic::Stop()
{
	if (m_lpDMPerformance)
	{
	    m_lpDMPerformance->Stop( NULL, NULL, 0, 0 );
	}
}

IDirectMusicLoader * CMusic::GetLoader()
{
	return g_lpDMLoader;
}

BOOL CMusic::SetPath(char *szPath, BOOL bRelative)
{
	if (szPath)
	{
		strcpy(g_szPath, szPath);
		g_bHasPath = TRUE;
	}

	return szPath!=NULL;
}

BOOL CMusic::HasPath()
{
	return g_bHasPath;
}
