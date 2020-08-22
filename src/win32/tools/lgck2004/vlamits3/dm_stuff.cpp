/*
	// Check if primary display surface is lost
    if ( FAILED( m_lpDDSPrimary->IsLost() ) )
	{
        if ( !RestoreDDraw((CWnd*)this) ) 
		{
            OutputDebugString( "DDraw: Couldn't restore surfaces.\n" );
			m_bDrawing= FALSE;
			return FALSE;
        }
    }

	DDSURFACEDESC ddsurfdesc;
	ZeroMemory (&ddsurfdesc, sizeof(DDSURFACEDESC));
	ddsurfdesc.dwSize = sizeof(DDSURFACEDESC);

	// Lock surface
	if (m_lpDDSPrimary->Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)	{
			OutputDebugString("DDraw: Lock failed!\n");
			m_bDrawing= FALSE;
			return FALSE;
	} 

	if (!m_bPlayLevelIntro)
	{
		DrawToBuffer (SCREENLEN, SCREENHEI, 
			BUFFERLEN, BUFFERHEI, ddsurfdesc);
	}
	else
	{
		PlayLevelIntro(ddsurfdesc);
	}

	DrawScore(ddsurfdesc);

	if (m_bPause)
	{
		PlotText(ddsurfdesc, "pause", -1, -1, (BYTE) -10, FALSE);
	}

	// unlock surface
	if (m_lpDDSPrimary->Unlock(NULL))	{
		OutputDebugString("DDraw: Unlock failed!\n");
		m_bDrawing= FALSE;
		return FALSE;
	} 
	*/

/*
    if ( FAILED( m_lpDDSPrimary->IsLost() ) )
	{
        if ( !RestoreDDraw((CWnd*)this) ) 
		{
            OutputDebugString( "DDraw: Couldn't restore surfaces.\n" );
			m_bDrawing= FALSE;
			return FALSE;
        }
    }
	DDSURFACEDESC ddsurfdesc;
	ZeroMemory (&ddsurfdesc, sizeof(DDSURFACEDESC));
	ddsurfdesc.dwSize = sizeof(DDSURFACEDESC);

	// Lock surface
	if (m_lpDDSBack->Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)	{
		OutputDebugString("DDraw: Lock failed!\n");
		m_bDrawing= FALSE;
		return FALSE;
	} 

	if (!m_bPlayLevelIntro)
	{
		DrawToBuffer (SCREENLEN, SCREENHEI, 
			BUFFERLEN, BUFFERHEI, ddsurfdesc);
	}
	else
	{
		PlayLevelIntro(ddsurfdesc);
	}

	DrawScore(ddsurfdesc);

	if (m_bPause)
	{
		PlotText(ddsurfdesc, "pause", -1, -1, (BYTE)-10, FALSE);
	}

	// unlock surface
	if (m_lpDDSBack->Unlock(NULL))	{
		OutputDebugString("DDraw: Unlock failed!\n");
		m_bDrawing= FALSE;
		return FALSE;
	}	*/




//////////////////////////////////////////////////////////////////
// DirectMusic

/*

BOOL CGame::InitDMusic(CWnd *pWnd)
{

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

    // Create loader object
	if (FAILED (CoCreateInstance( CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC, 
                      IID_IDirectMusicLoader, (void**)&m_lpDMLoader )))
	{
		OutputDebugString("FATAL: Cannot Create DirectMusicLoader Object\n");
		return FALSE;	
	}

	// Load MIDI file
	if (!LoadMIDI("5.mid"))
	{
		OutputDebugString("FATAL: Cannot load MIDI file\n");
		return FALSE;
	}

	// Play Segment
    if (FAILED(m_lpDMPerformance->PlaySegment(m_lpDMSegment, 0, 0, &m_lpDMSegState)))
	{
		OutputDebugString("FATAL: Play segment failed\n");
		return FALSE;	
	}

	//_getcwd
	return TRUE;
}

void CGame::ReleaseDMusic()
{
   
	// Cleanup all interfaces

	if (m_lpDMLoader)
	{
		m_lpDMLoader->Release(); 
		m_lpDMLoader=NULL;
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

BOOL CGame::LoadMIDI(char *szFilename)
{
	char szPath[_MAX_PATH] = "e:\\toolkit\\musics";
	WCHAR wszPath[_MAX_PATH];

	MULTI_TO_WIDE(wszPath, szPath);

    if (FAILED(m_lpDMLoader->SetSearchDirectory(GUID_DirectMusicAllTypes,
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

    if (FAILED(m_lpDMLoader->GetObject(&ObjDesc,
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

  */