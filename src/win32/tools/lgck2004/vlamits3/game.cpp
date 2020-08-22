// Game.cpp : implementation file
//

#include "stdafx.h"
#include <io.h>
#include <stdio.h>
#include <process.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <conio.h>
#include <time.h>  
#include <direct.h>
#include "vlamits3.h"
#include "Game.h"
#include "draw.h"
#include "dlgoptions.h"
#include "dlgselectepisode.h"
#include "dlgwait.h"
#include "PalData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPalData g_pal;

// Directives
#define _NOCLIPPER TRUE
#define _REAL_COLORS

// Constants
#define BUFFERSIZE (16)
#define BUTTONDOWN(b) ((b & 0x80)!=0)

#define JOYMAX 1000
#define JOYMIN -1000
#define JOYDEAD 3000
#define JOYSAT  2000

#define BACKBUFFERS 1
#define JUMPLEN 20

#define LGCK_VERSION "LGCK_4.0"
#define GAME_SIGNATURE "VLA3a"

/*
USER_WINPAL MSDOS_PAL[256] = {
	0 , 0 , 0 , 0 , 0 , 42 , 0 , 42 , 
	0 , 0 , 42 , 42 , 42 , 0 , 0 , 42 , 
	0 , 42 , 42 , 21 , 0 , 42 , 42 , 42 , 
	21 , 21 , 21 , 21 , 21 , 63 , 21 , 63 , 
	21 , 21 , 63 , 63 , 63 , 21 , 21 , 63 , 
	21 , 63 , 63 , 63 , 21 , 63 , 63 , 63 , 
	0 , 0 , 0 , 5 , 5 , 5 , 8 , 8 , 
	8 , 11 , 11 , 11 , 14 , 14 , 14 , 17 , 
	17 , 17 , 20 , 20 , 20 , 24 , 24 , 24 , 
	28 , 28 , 28 , 32 , 32 , 32 , 36 , 36 , 
	36 , 40 , 40 , 40 , 45 , 45 , 45 , 50 , 
	50 , 50 , 56 , 56 , 56 , 63 , 63 , 63 , 
	0 , 0 , 63 , 16 , 0 , 63 , 31 , 0 , 
	63 , 47 , 0 , 63 , 63 , 0 , 63 , 63 , 
	0 , 47 , 63 , 0 , 31 , 63 , 0 , 16 , 
	63 , 0 , 0 , 63 , 16 , 0 , 63 , 31 , 
	0 , 63 , 47 , 0 , 63 , 63 , 0 , 47 , 
	63 , 0 , 31 , 63 , 0 , 16 , 63 , 0 , 
	0 , 63 , 0 , 0 , 63 , 16 , 0 , 63 , 
	31 , 0 , 63 , 47 , 0 , 63 , 63 , 0 , 
	47 , 63 , 0 , 31 , 63 , 0 , 16 , 63 , 
	31 , 31 , 63 , 39 , 31 , 63 , 47 , 31 , 
	63 , 55 , 31 , 63 , 63 , 31 , 63 , 63 , 
	31 , 55 , 63 , 31 , 47 , 63 , 31 , 39 , 
	63 , 31 , 31 , 63 , 39 , 31 , 63 , 47 , 
	31 , 63 , 55 , 31 , 63 , 63 , 31 , 55 , 
	63 , 31 , 47 , 63 , 31 , 39 , 63 , 31 , 
	31 , 63 , 31 , 31 , 63 , 39 , 31 , 63 , 
	47 , 31 , 63 , 55 , 31 , 63 , 63 , 31 , 
	55 , 63 , 31 , 47 , 63 , 31 , 39 , 63 , 
	45 , 45 , 63 , 49 , 45 , 63 , 54 , 45 , 
	63 , 58 , 45 , 63 , 63 , 45 , 63 , 63 , 
	45 , 58 , 63 , 45 , 54 , 63 , 45 , 49 , 
	63 , 45 , 45 , 63 , 49 , 45 , 63 , 54 , 
	45 , 63 , 58 , 45 , 63 , 63 , 45 , 58 , 
	63 , 45 , 54 , 63 , 45 , 49 , 63 , 45 , 
	45 , 63 , 45 , 45 , 63 , 49 , 45 , 63 , 
	54 , 45 , 63 , 58 , 45 , 63 , 63 , 45 , 
	58 , 63 , 45 , 54 , 63 , 45 , 49 , 63 , 
	0 , 0 , 28 , 7 , 0 , 28 , 14 , 0 , 
	28 , 21 , 0 , 28 , 28 , 0 , 28 , 28 , 
	0 , 21 , 28 , 0 , 14 , 28 , 0 , 7 , 
	28 , 0 , 0 , 28 , 7 , 0 , 28 , 14 , 
	0 , 28 , 21 , 0 , 28 , 28 , 0 , 21 , 
	28 , 0 , 14 , 28 , 0 , 7 , 28 , 0 , 
	0 , 28 , 0 , 0 , 28 , 7 , 0 , 28 , 
	14 , 0 , 28 , 21 , 0 , 28 , 28 , 0 , 
	21 , 28 , 0 , 14 , 28 , 0 , 7 , 28 , 
	14 , 14 , 28 , 17 , 14 , 28 , 21 , 14 , 
	28 , 24 , 14 , 28 , 28 , 14 , 28 , 28 , 
	14 , 24 , 28 , 14 , 21 , 28 , 14 , 17 , 
	28 , 14 , 14 , 28 , 17 , 14 , 28 , 21 , 
	14 , 28 , 24 , 14 , 28 , 28 , 14 , 24 , 
	28 , 14 , 21 , 28 , 14 , 17 , 28 , 14 , 
	14 , 28 , 14 , 14 , 28 , 17 , 14 , 28 , 
	21 , 14 , 28 , 24 , 14 , 28 , 28 , 14 , 
	24 , 28 , 14 , 21 , 28 , 14 , 17 , 28 , 
	20 , 20 , 28 , 22 , 20 , 28 , 24 , 20 , 
	28 , 26 , 20 , 28 , 28 , 20 , 28 , 28 , 
	20 , 26 , 28 , 20 , 24 , 28 , 20 , 22 , 
	28 , 20 , 20 , 28 , 22 , 20 , 28 , 24 , 
	20 , 28 , 26 , 20 , 28 , 28 , 20 , 26 , 
	28 , 20 , 24 , 28 , 20 , 22 , 28 , 20 , 
	20 , 28 , 20 , 20 , 28 , 22 , 20 , 28 , 
	24 , 20 , 28 , 26 , 20 , 28 , 28 , 20 , 
	26 , 28 , 20 , 24 , 28 , 20 , 22 , 28 , 
	0 , 0 , 16 , 4 , 0 , 16 , 8 , 0 , 
	16 , 12 , 0 , 16 , 16 , 0 , 16 , 16 , 
	0 , 12 , 16 , 0 , 8 , 16 , 0 , 4 , 
	16 , 0 , 0 , 16 , 4 , 0 , 16 , 8 , 
	0 , 16 , 12 , 0 , 16 , 16 , 0 , 12 , 
	16 , 0 , 8 , 16 , 0 , 4 , 16 , 0 , 
	0 , 16 , 0 , 0 , 16 , 4 , 0 , 16 , 
	8 , 0 , 16 , 12 , 0 , 16 , 16 , 0 , 
	12 , 16 , 0 , 8 , 16 , 0 , 4 , 16 , 
	8 , 8 , 16 , 10 , 8 , 16 , 12 , 8 , 
	16 , 14 , 8 , 16 , 16 , 8 , 16 , 16 , 
	8 , 14 , 16 , 8 , 12 , 16 , 8 , 10 , 
	16 , 8 , 8 , 16 , 10 , 8 , 16 , 12 , 
	8 , 16 , 14 , 8 , 16 , 16 , 8 , 14 , 
	16 , 8 , 12 , 16 , 8 , 10 , 16 , 8 , 
	8 , 16 , 8 , 8 , 16 , 10 , 8 , 16 , 
	12 , 8 , 16 , 14 , 8 , 16 , 16 , 8 , 
	14 , 16 , 8 , 12 , 16 , 8 , 10 , 16 , 
	11 , 11 , 16 , 12 , 11 , 16 , 13 , 11 , 
	16 , 15 , 11 , 16 , 16 , 11 , 16 , 16 , 
	11 , 15 , 16 , 11 , 13 , 16 , 11 , 12 , 
	16 , 11 , 11 , 16 , 12 , 11 , 16 , 13 , 
	11 , 16 , 15 , 11 , 16 , 16 , 11 , 15 , 
	16 , 11 , 13 , 16 , 11 , 12 , 16 , 11 , 
	11 , 16 , 11 , 11 , 16 , 12 , 11 , 16 , 
	13 , 11 , 16 , 15 , 11 , 16 , 16 , 11 , 
	15 , 16 , 11 , 13 , 16 , 11 , 12 , 16 , 
	};
*/

int g_arrPoints[]=
{
	0,
	10,
	25,
	50,
	100,
	200,
	300,
	400,
	500,
	1000,
	2000,
	5000,
	10000
};

#ifdef _DEBUG
	static CFile g_fileDebug;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGame

CGame::CGame()
{
	OutputDebugString("CGame::CGame()\n");

	// DirectDraw Objects
	m_lpDD=NULL;				// DirectDraw object
	m_lpDDSPrimary=NULL;		// DirectDraw primary surface
	m_lpDDPal=NULL;				// DirectDraw Palette
	m_lpDDSBack=NULL;			// DirectDraw backbuffer surface
	m_lpDDClipper=NULL;			// DirectDraw clipper.

	// DirectSound Objects
	m_lpDS=NULL;				// DirectSound object
	//m_lpDSB=NULL;				// DirectSound buffer;

	// DirectInput Objects
	m_lpdi=NULL;				// DirectInput 
	m_lpdid2=NULL;				// DirectInput device

	m_lpdid2Mouse = NULL;

	// Map & scroll
	m_pMap = NULL;
	m_pScrollBK = NULL;

	// BOOL
	m_bGameOver = TRUE;
	m_bPause = FALSE;
	m_bActive = TRUE;
	m_bPlayingMusic = FALSE;
	m_bCritical = TRUE;
	m_bDrawing = FALSE;

	m_bPrimary = TRUE; 

	// Game General Init
	m_nCurrScript =0;
    g_pal.SetGamma(AfxGetApp()->GetProfileInt("data", "gamma", 3));

#ifdef _DEBUG
	g_fileDebug.Open("game_debug.out",
		CFile::modeCreate | CFile::modeWrite |
			CFile::typeBinary );
#endif
}

CGame::~CGame()
{
	OutputDebugString("CGame::~CGame()\n");
#ifdef _DEBUG
	g_fileDebug.Close();
#endif
  
   AfxGetApp()->WriteProfileInt("data", "gamma", g_pal.GetGamma());
}

void CGame::Destroy()
{
	OutputDebugString("CGame::Destroy()\n");
	m_arrSounds.Forget();

	ReleaseDDraw  ();
	ReleaseDSound ();
	ReleaseDInput ();
	//ReleaseDMusic ();

	if (m_pMap!=NULL) {
		free (m_pMap);
		m_pMap = NULL;
	}

	if (m_pScrollBK!=NULL) {
		free (m_pScrollBK);
		m_pScrollBK = NULL;
	}

	m_music.Destroy();
	m_music2.Destroy();

    // Close down COM
    CoUninitialize();
}

/////////////////////////////////////////////////////////////////////////////
// Helper Functions

/*
BOOL CGame::CreatePalette(CClientDC *dc, LPDIRECTDRAW p_lpDD, LPDIRECTDRAWPALETTE * p_lpDDPal  )
{
    static PALETTEENTRY ape[256];

	UCHAR i,j;
    j=0x00;
    for ( i=0x10 ;
         i< (0xf0); i++, j++) 
         {

#ifdef _REAL_COLORS
			if (MSDOS_PAL[j].red)
			{
				ape[i].peRed = GammaCorrection(MSDOS_PAL[j].red);
					//0x82 | (MSDOS_PAL[j].red*2) ;
			}
			else
			{
				ape[i].peRed=0;
			}

			if (MSDOS_PAL[j].green)
			{
				ape[i].peGreen = GammaCorrection(MSDOS_PAL[j].green);
					//0x82 | (MSDOS_PAL[j].green*2) ;
			}
			else
			{
				ape[i].peGreen=0;
			}

            if (MSDOS_PAL[j].blue)
			{
				ape[i].peBlue = GammaCorrection(MSDOS_PAL[j].blue);
					//0*0x82 | (MSDOS_PAL[j].blue*2) ;
			}
			else
			{
				ape[i].peBlue=0;
			}

			ape[i].peFlags = PC_NOCOLLAPSE;//PC_RESERVED;						

			//OutputDebugString("Using Real Colors...\n");
#else			 
            ape[i].peRed = MSDOS_PAL[j].red*4;
            ape[i].peGreen = MSDOS_PAL[j].green*4;
            ape[i].peBlue = MSDOS_PAL[j].blue*4;
			ape[i].peFlags = PC_NOCOLLAPSE;//PC_RESERVED;           
#endif
		 }

	if (GetSystemPaletteEntries(dc->m_hDC, 0, 0x0f, &ape[0])==0)
    {   
        return Fail("FATAL: GetSystemPaletteEntries() failed.\n");   }

    if (GetSystemPaletteEntries(dc->m_hDC, 0xf0,0xff, &ape[0xf0])==0)
    {   
        return Fail("FATAL: GetSystemPaletteEntries() failed.\n");   }

	// Free up 32 entries so Windoz will leave us alone!
	for (i=0x00; i<0x10; i++)
	{
		ape[i].peFlags = 0;
		ape[0xff-i].peFlags = 0;
	}

    if ( FAILED( p_lpDD->CreatePalette( DDPCAPS_ALLOW256 | DDPCAPS_8BIT 	,		 
                    ape,  p_lpDDPal , NULL ) ) )	{   
		return Fail(  "Couldn't create palette.\n" ); 
	}
    return TRUE;
}
*/

BOOL CGame::Fail (char *szText)
{

#ifndef _DEBUG
	AfxMessageBox (szText, MB_OK);
#else
	OutputDebugString( szText );
#endif

    return FALSE;
}

/////////////////////////////////////////////////////////////
// DirectDraw

void CGame::ReleaseDDraw ()
{
	m_bCritical = TRUE;

    if ( m_lpDD != NULL )
    {
        if ( m_lpDDSPrimary != NULL )
        {
            m_lpDDSPrimary->Release();
            m_lpDDSPrimary = NULL;
        }

#ifdef _DEBUG
		if ( m_lpDDSBack != NULL )
        {
            m_lpDDSBack->Release();
            m_lpDDSBack = NULL;
        }
#endif

        m_lpDD->Release();
        m_lpDD = NULL;
    }
}


void CGame::InitDDraw(CWnd *pWnd)
{
   // Create the DirectDraw object -- we just need an IDirectDraw
    // interface so we won't bother to query an IDirectDraw2
    if ( FAILED( DirectDrawCreate( NULL, &m_lpDD, NULL ) ) )
	{
		 Fail( "Fatal: Couldn't create DirectDraw object.\n" );
		 return;
	}

#ifdef _DEBUG
    if FAILED( m_lpDD->SetCooperativeLevel( pWnd->m_hWnd,
                        DDSCL_NORMAL ) )
	{
		Fail( "Fatal: Debug DDraw -- Couldn't set cooperative level.\n" );
		return ;
	}
#else
	// Get exclusive mode
	if FAILED( m_lpDD->SetCooperativeLevel( pWnd->m_hWnd,
                        DDSCL_NORMAL |
						DDSCL_EXCLUSIVE | 
						DDSCL_FULLSCREEN | 
						DDSCL_ALLOWMODEX ) )
	{
		Fail( "Fatal: Release DDraw -- Couldn't set cooperative level.\n" );
		return ;
	}

    // Set the display mode. An palettized mode is required for the
	// working phase of the project
	if ( FAILED( m_lpDD->SetDisplayMode( SCREENLEN, SCREENHEI, 8 ) ) )
	{
		Fail( "Fatal: Couldn't set display mode.\n" );
		return ;
	}
#endif 

    DDSURFACEDESC   ddsd;
	ZeroMemory (&ddsd, sizeof (DDSURFACEDESC));

#ifdef _DEBUG
	// Create the primary surface
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE ;
    
	if ( FAILED( m_lpDD->CreateSurface( &ddsd, &m_lpDDSPrimary, NULL ) ) )
	{
		Fail( "Fatal: Couldn't create primary surface.\n" );
		return ;
	}
#else
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | 
                            DDSCAPS_FLIP | 
                            DDSCAPS_COMPLEX |
							//DDSCAPS_SYSTEMMEMORY;
                            //DDSCAPS_VIDEOMEMORY ;
							0;

    ddsd.dwBackBufferCount = BACKBUFFERS;
	if ( FAILED( m_lpDD->CreateSurface( &ddsd, &m_lpDDSPrimary, NULL ) ) )
	{
		Fail( "Fatal: Couldn't create primary surface. [exclusive mode]\n" );
		return ;
	}
#endif

	// Check pixel format 
    DDPIXELFORMAT       ddpf;       // Surface format structure.

    // Check the surface format.
    ddpf.dwSize = sizeof( ddpf );
    if ( FAILED( m_lpDDSPrimary->GetPixelFormat( &ddpf ) ) )
	{
        Fail( "Fatal: Couldn't get pixel format.\n" );
		return;
    }

	// Requires a 256 colors display mode to run - if video card
	// won't provide then screw it.

	if (ddpf.dwRGBBitCount !=8) {
		Fail ("Fatal: Cannot operated with anything else but 256 colors!\n");
		return ;
	}

    if ( ddpf.dwFlags & DDPF_PALETTEINDEXED8 ) 
    {
        // We are palettized, so create a palette and attach it to
        // the primary surface.

		CClientDC dc( (CFrameWnd*) pWnd);

		/*
		if (CreatePalette(&dc, 
						  m_lpDD,
						  &m_lpDDPal  )==FALSE)
		{
			Fail( "Fatal: Couldn't create the palette\n");
			return;
		}
		*/

		if (g_pal.CreatePalette(&dc, 
						  m_lpDD,
						  &m_lpDDPal)==FALSE)
		{
			Fail( "Fatal: Couldn't create the palette\n");
			return ;
		}

        if ( FAILED( m_lpDDSPrimary->SetPalette( m_lpDDPal ) ) )
		{
            Fail( "Fatal: Couldnt' get and/or set the palette.\n" );
			return;
        }
    }	

#ifndef _NOCLIPPER
    // Create a clipper and attach it to the primary surface.
    if ( FAILED( m_lpDD->CreateClipper( 0, &m_lpDDClipper, NULL ) ) )
	{
        Fail( "Fatal: Couldn't create the clipper.\n" );
		return ;
    }

    // Associate our clipper with our hwnd so it will be updated
    // by Windows.
    if ( FAILED( m_lpDDClipper->SetHWnd( 0, pWnd->m_hWnd ) ) )
	{
        Fail(  "Fatal: Couldn't set the hwnd.\n" );
		return ;
    }

    // Associate our clipper with the primary surface, so Blt 
    // will use it. If this step is skipped by defining NOCLIPPER, you
    // can observe the effects of rendering without clipping. Other
    // windows partially obscuring Inawin's will be overwritten.

    if ( FAILED( m_lpDDSPrimary->SetClipper( m_lpDDClipper ) ) )
	{
        Fail(  "Fatal: Couldn't set the clipper.\n" );
		return ;
    }
#endif

#ifdef _DEBUG
	// Retrieve information concerning primary surface,
	// into the DDSURFACEDESC structure.
    ZeroMemory(&ddsd, sizeof(ddsd));

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_ALL;
	if (FAILED (m_lpDDSPrimary->GetSurfaceDesc(&ddsd) ))
	{
		Fail(  "Fatal: Couldn't grab the surface description.\n" );
		return;
    }
	
	// Use the information to clone another surface identical
	// to the previous.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

    if (m_lpDD->CreateSurface(&ddsd, &m_lpDDSBack, NULL) != DD_OK)
	{
        Fail(  "Fatal: Couldn't clone the primary surface.\n" );
		return;
    }
#else

    // Get a pointer to the back buffer.
    DDSCAPS             ddscaps;    // Surface capabilities structure.
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    if ( FAILED( m_lpDDSPrimary->GetAttachedSurface( &ddscaps, 
		                                           &m_lpDDSBack ) ) )
	{
        Fail("Couldn't find the back buffer.\n" );
		return;
    }

#endif

	OutputDebugString("Info - DirectDraw objects constructed succesfully!\n");
}

BOOL CGame::RestoreDDraw (CWnd *pWnd)
{
    HRESULT ddrval;

    // Try restoring the primary first
    ddrval = m_lpDDSPrimary->Restore();
    if ( ddrval == DDERR_WRONGMODE ) 
	{
        // The restore failed because the display mode was
        // changed. Destroy everything then re-create it.
        OutputDebugString( "Display mode changed!\n" );
        ReleaseDDraw();
        InitDDraw( (CWnd*)pWnd );
		return TRUE;
    }
    else
	{
		if ( FAILED( ddrval ) )
		{
        // We failed for some other reason.
			OutputDebugString( "Random restore failure.\n" );
			return FALSE;
		}
		else
		{
        // We're OK. Restore everything else.
			if ( FAILED( m_lpDDSBack->Restore() ) ) 
				return FALSE;
		}
	}

    return TRUE;
}


////////////////////////////////////////////////////////////
// DirectSound

BOOL CGame::InitDSound (CWnd *pWnd, GUID *pguid)
{
    // Create DirectSound.
    if ( FAILED( DirectSoundCreate( NULL, &m_lpDS, NULL ) ) )
	{		OutputDebugString ("DSound: DirectSoundCreate failed\n");
        return FALSE;
	}

#ifdef _DEBUG
    // Set cooperative level.
    if ( FAILED(  m_lpDS->SetCooperativeLevel( pWnd->m_hWnd, DSSCL_NORMAL ) ) )
	{
		OutputDebugString ("DSound: SetCooperativeLevel failed\n");
        return FALSE;
	}
#else
    //if ( FAILED( m_lpDS->SetCooperativeLevel( pWnd->m_hWnd, DSSCL_PRIORITY ) ) ) {
    if ( FAILED( m_lpDS->SetCooperativeLevel( pWnd->m_hWnd, DSSCL_NORMAL ) ) ) {
		OutputDebugString ("DSound: SetCooperativeLevel failed\n");
        return FALSE;
	}
#endif

    return TRUE;

}

void CGame::ReleaseDSound ()
{
    if ( m_lpDS!=NULL )  {
		m_lpDS->Release();  // This releases buffers as well.
		m_lpDS = NULL;
	}

}

///////////////////////////////////////////////////////////
// DirectInput

BOOL CGame::InitDInput (CWnd *pWnd)
{
    HRESULT     hr;

    // Create DirectInput object.
	CWinApp * pApp = AfxGetApp();

    hr = DirectInputCreate( pApp->m_hInstance, 
		                    DIRECTINPUT_VERSION, 
							&m_lpdi, NULL );
    if ( FAILED( hr ) )
    {
		Fail ("Failed to initialize DirectInput.\n");
        return FALSE;
    }

    return TRUE;    
}  


void CGame::ReleaseDInput ()
{
    if ( m_lpdid2 != NULL ) 
    {
		m_lpdid2->Unacquire();
        m_lpdid2->Release();
        m_lpdid2 = NULL;
    }

	if ( m_lpdid2Mouse != NULL ) 
    {
		m_lpdid2Mouse->Unacquire();
        m_lpdid2Mouse->Release();
        m_lpdid2Mouse = NULL;
    }

    if ( m_lpdi != NULL )
    { 
        m_lpdi->Release();
        m_lpdi = NULL;
    }
}


LPDIRECTINPUTDEVICE2 CGame::CreateIDevice2( LPDIRECTINPUT lpdi, GUID* pguid )
{
    HRESULT hr, hr2;
  
    LPDIRECTINPUTDEVICE  lpdid1;  // Temporary.
    LPDIRECTINPUTDEVICE2 lpdid2;  // The keeper.

    hr = lpdi->CreateDevice( *pguid, &lpdid1, NULL );
 
    if ( SUCCEEDED( hr ) )
    { 
        hr2 = lpdid1->QueryInterface( IID_IDirectInputDevice2, 
                                      ( void ** )&lpdid2 ); 
        lpdid1->Release();
    } 
    else
    {
        OutputDebugString( 
			"Could not create IDirectInputDevice device" );
        return NULL;
    } 

    if ( FAILED( hr2 ) )
    {
        OutputDebugString( 
			"Could not create IDirectInputDevice2 device" );
        return NULL;
    } 

    return lpdid2;
}  

BOOL CGame::InitIDevice(LPDIRECTINPUTDEVICE2 & lpdid2, GUID* pguid, CWnd *pWnd )
{
    HRESULT hr;
    DIDEVICEINSTANCE    diDeviceInstance;
	enum DeviceKind { keyboard, mouse, joystick } CurrentDevice;

    // Release device if it already exists.
    if ( lpdid2 ) 
    {
		lpdid2->Unacquire();
        lpdid2->Release();
    }

    // Create game device and get IDirectInputDevice2 interface.
    lpdid2 = CreateIDevice2( m_lpdi, pguid );
    if ( !lpdid2 ) return FALSE;

    // Find out what type it is and set data format accordingly.

    diDeviceInstance.dwSize = sizeof( DIDEVICEINSTANCE );
    lpdid2->GetDeviceInfo( &diDeviceInstance );

    switch ( GET_DIDEVICE_TYPE( diDeviceInstance.dwDevType ) )
    {
        case DIDEVTYPE_KEYBOARD:
            hr = lpdid2->SetDataFormat( &c_dfDIKeyboard );
            CurrentDevice = keyboard;
            break;
        case DIDEVTYPE_MOUSE:
            hr = lpdid2->SetDataFormat( &c_dfDIMouse );
            CurrentDevice = mouse; 
            break;
        case DIDEVTYPE_JOYSTICK:
            hr = lpdid2->SetDataFormat( &c_dfDIJoystick );
            CurrentDevice = joystick;
            break;
        default: return FALSE;  // Unrecognized type.
    }
    if ( FAILED( hr ) ) return FALSE;

    // Set cooperative level. 
    DWORD cl, cl1;
    if ( CurrentDevice == keyboard ) 
    {
		cl = DISCL_NONEXCLUSIVE;
	}
    else 
	{
		cl = DISCL_EXCLUSIVE;
	}

// Set foreground level for release version, but use background level
// for debugging so we don't keep losing the device when switching to 
// a debug window. Note the mouse can't have exclusive background level.

    cl1 = DISCL_FOREGROUND;
#ifdef _DEBUG
    cl1 = DISCL_BACKGROUND;
    if ( CurrentDevice == mouse ) cl = DISCL_NONEXCLUSIVE;
#endif

    if ( FAILED( lpdid2->SetCooperativeLevel( 
		pWnd->m_hWnd, cl | cl1 ) ) )
    {
        OutputDebugString( "Bad: Failed to set game device cooperative level.\n" );
        lpdid2 = NULL;
        return FALSE;
    }

    // Set up the data buffer.

    DIPROPDWORD dipdw =
    {
        // The header.
        {
            sizeof( DIPROPDWORD ),      // diph.dwSize
            sizeof( DIPROPHEADER ),     // diph.dwHeaderSize
            0,                          // diph.dwObj
            DIPH_DEVICE,                // diph.dwHow
        },
        // Number of elements in data buffer.
        BUFFERSIZE,              // dwData
    };

    lpdid2->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );

    if ( CurrentDevice == joystick )
    { 
        if ( !InitJoystick(lpdid2) ) 
			return FALSE;  
    }

    // In case you were wondering, this is not a good time to acquire the 
    // device. For one thing, we can't acquire in foreground mode here 
    // because the options dialog may be open. We'll acquire it when the
    // main window is activated.

#ifdef _DEBUG
	OutputDebugString ("InitIDevive succesful\n");
#endif

    return TRUE;
} 


BOOL CGame::InitJoystick( LPDIRECTINPUTDEVICE2 lpdid2 )
{
    // Set range. 
    // Note: range, deadzone, and saturation are being set for the
    // entire device. This could have unwanted effects on
    // sliders, dials, etc.

    DIPROPRANGE diprg; 
 
    diprg.diph.dwSize       = sizeof( diprg ); 
    diprg.diph.dwHeaderSize = sizeof( diprg.diph ); 
    diprg.diph.dwObj        = 0; 
    diprg.diph.dwHow        = DIPH_DEVICE; 
    diprg.lMin              = JOYMIN; 
    diprg.lMax              = JOYMAX; 
 
    if ( FAILED( lpdid2->SetProperty( DIPROP_RANGE, &diprg.diph ) ) )
        return FALSE; 

    // Set deadzone.
    DIPROPDWORD dipdw;

    dipdw.diph.dwSize       = sizeof( dipdw ); 
    dipdw.diph.dwHeaderSize = sizeof( dipdw.diph ); 
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = JOYDEAD;

    if ( FAILED( lpdid2->SetProperty( DIPROP_DEADZONE, &dipdw.diph ) ) )
        return FALSE;

    // Set saturation.
    dipdw.dwData            = JOYSAT;
    if ( FAILED( lpdid2->SetProperty( DIPROP_SATURATION, &dipdw.diph ) ) )
        return FALSE;  

    return TRUE;
} 


BOOL CGame::PollDevice( LPDIRECTINPUTDEVICE2 lpdid2, UINT & nState)
{
    static DIJOYSTATE   dijs;
    static char         keys[256]; 
     
    HRESULT				hr;
    DIDEVICEOBJECTDATA	rgdod[BUFFERSIZE];
    DWORD				dwItems; 
    DIDEVICEINSTANCE	diDeviceInstance;
	UINT				nCurrentDevice;

    if ( !m_lpdid2 ) return FALSE;

	lpdid2->Poll();  // May be unnecessary but never hurts.

	dwItems = BUFFERSIZE;
	hr = lpdid2->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), 
                 rgdod,         // Where to put data?
                 &dwItems,      // How many items?
                 0 );           // Flags.

	while ((hr == DIERR_INPUTLOST) &&
		  SUCCEEDED (lpdid2->Acquire()) )
	{
		lpdid2->Poll();  // May be unnecessary but never hurts.

		dwItems = BUFFERSIZE;
		hr = lpdid2->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), 
			         rgdod,         // Where to put data?
				     &dwItems,      // How many items?
					0 );           // Flags.
	}
	

    // We can't get the device. Quit.
    if ( hr == DIERR_NOTACQUIRED )
    {
        OutputDebugString( "Bad: Device not acquired!\n" );
        return FALSE;
    }

    // Find out what type it is and set data format accordingly.

    diDeviceInstance.dwSize = sizeof( DIDEVICEINSTANCE );
    lpdid2->GetDeviceInfo( &diDeviceInstance );

    nCurrentDevice = GET_DIDEVICE_TYPE( diDeviceInstance.dwDevType );

	switch ( nCurrentDevice )
    {
        case DIDEVTYPE_KEYBOARD:
            hr = m_lpdid2->GetDeviceState( sizeof( keys ), keys );  
            break;

        case DIDEVTYPE_JOYSTICK:
            hr = m_lpdid2->GetDeviceState( sizeof( DIJOYSTATE ), &dijs ); 
            break;
    }

	while (( hr == DIERR_INPUTLOST ) && 
				SUCCEEDED (lpdid2->Acquire()) ) 
	{
	    switch ( nCurrentDevice )
		{
	        case DIDEVTYPE_KEYBOARD:
				hr = m_lpdid2->GetDeviceState( sizeof( keys ), keys );  
				break;

	        case DIDEVTYPE_JOYSTICK:
				hr = m_lpdid2->GetDeviceState( sizeof( DIJOYSTATE ), &dijs ); 
				break;
	    }
	}
	
    if ( hr == DIERR_NOTACQUIRED )
    {
        OutputDebugString( "Bad: Device not acquired!\n" );
        return FALSE;
    }

    // We got immediate input, let's act on it.  
    if ( SUCCEEDED( hr ) )
    {
        switch ( nCurrentDevice )
        {
	        case DIDEVTYPE_KEYBOARD:

				nState = BUTTONDOWN (keys[DIK_UP]) * JOY_UP
					| BUTTONDOWN (keys[DIK_DOWN]) * JOY_DOWN
					| BUTTONDOWN (keys[DIK_LEFT]) * JOY_LEFT
					| BUTTONDOWN (keys[DIK_RIGHT]) * JOY_RIGHT
					| BUTTONDOWN (keys[DIK_LSHIFT]) * JOY_JUMP
					| BUTTONDOWN (keys[DIK_SPACE]) * JOY_FIRE ;
			break;

	        case DIDEVTYPE_JOYSTICK:
				nState=0;
			    if ( dijs.lX < 0 ) 
					nState = nState | JOY_LEFT;
                if ( dijs.lX > 0 ) 
					nState = nState | JOY_RIGHT;
                if ( dijs.lY < 0 ) 
					nState = nState | JOY_UP;
                if ( dijs.lY > 0 ) 
					nState = nState | JOY_DOWN;

				nState = nState 
					| BUTTONDOWN (dijs.rgbButtons[0]) * JOY_JUMP
					| BUTTONDOWN (dijs.rgbButtons[1]) * JOY_FIRE
					| BUTTONDOWN (dijs.rgbButtons[2]) * JOY_ZKEY;
	
           break;

        } // switch

        return TRUE;  // Got data.
    }
    else              // FAILED( hr )
        return FALSE;
} 


//////////////////////////////////////////////////////////////////
// CScriptArray

void CGame::SplitScript (CScriptArray &sS, CScriptArray &sBK, CScriptArray & sFW)
{
	int n;
	CProtoArray & arrProto = m_arrProto;
	for (n=0; n<sS.GetSize(); n++)
	{
		CScriptEntry & entry = sS [n];

		if (entry.m_nY < BUFFERHEI
			&& entry.m_nY >= 0
			&& entry.m_nX < BUFFERLEN
			&& entry.m_nX >= 0)
		{
			if (arrProto[entry.m_nProto].m_nClass <0x10)
			{
				sBK. Add (entry);
			}
			else
			{
				InitEntry (entry);
				sFW. Add (entry);
			}
		}
	}

	CScriptEntry t_entry;
	sFW.InsertAt (0, t_entry);
}


BOOL CGame::MapScript (CScriptArray &s, UCHAR * &pMap, int nLen, int nHei, BOOL bBK)
{
	// IMPORTANT: don't forget to null everything first

	CGameFile3 & game = * this;
	if (pMap==NULL)
		return FALSE;

	COBL3Array & arrOBL3 = game.m_arrOBL3;
	CProtoArray & arrProto = game.m_arrProto;
	CSS3Frame *pFrame;

	int n;
	int x;
	int y;
	int i;
	UINT nData;
	UINT *pBits;

	for (n=0; n<s.GetSize(); n++)
	{
		CScriptEntry & entry = s [n];
		pFrame = arrOBL3.GetFrame(entry);
		for (y=0; (y<pFrame->m_nHei/8) &&
				(y*8+ entry.m_nY < nHei); y++)
		{	
			for (x=0; (x<pFrame->m_nLen/8) &&
					(x*8+ entry.m_nX < nLen); x++)
			{
				if (bBK) { // Background script maping
					pBits = (UINT*) pFrame->Point(x*8,y*8);
					
					nData=0;
					for (i=0; i<8; i++)
						nData = nData + (*(pBits+ i*pFrame->m_nLen/4)
							+ *(pBits+ i*pFrame->m_nLen/4 +1)!=0);
							
					if (nData>=4 && arrProto[entry.m_nProto].m_nClass!=0)
						* (pMap + (entry.m_nY/8+y)*nLen + 
							x*8 + entry.m_nX)
								= arrProto[entry.m_nProto]
									.m_nClass;

				}
				else
				{  // Forwardground script maping
					if (arrProto[entry.m_nProto].m_nClass!=0 )
						MapSprite (n, FALSE);
				}				
			}			
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGame message handlers

BOOL CGame::Init (CWnd *pWnd)
{
	OutputDebugString("CGame::Init()\n");

    // Initialize COM
    if (FAILED(CoInitialize(NULL)))
	{
		OutputDebugString("CoInitialize failed\n");
		return FALSE;
	}
	
	// Initializing Direct X components
	InitDDraw (pWnd);
	FillSurface(0x10);

	InitDSound(pWnd);
	InitDInput(pWnd);
	//InitDMusic(pWnd);

    // Set up the keyboard as the default input device -- in case the
    // user cancels out of the dialog.
	if (InitIDevice( m_lpdid2, (GUID *)&GUID_SysKeyboard, (CWnd*)pWnd ))	{
			m_lpdid2->Acquire();
	}

#ifndef _DEBUG
	// Acquire the system mouse in full screen mode to insure the mouse
	// that it will not be visible when we don't want it to be.
    if (InitIDevice( m_lpdid2Mouse, (GUID *)&GUID_SysMouse, (CWnd*)pWnd )) {
		m_lpdid2Mouse->Acquire();
	}
#endif

	//m_music.SetPath("e:\\toolkit\\musics");
	//m_music.Create(m_lpDS, "buffy[1].mid");
	//m_music2.Create(m_lpDS, "rush.mid");
	//m_music2.Play();
	//InitEpisode (CString("..\\scr4edit\\vla3demo.scr"));

    CStringArray arrEpisodes;
    CDlgWait dlgWait;
    CDlgSelectEpisode dlg;
    int nCount = MakeEpisodeList(dlg.m_arrEpisodes);
    if (nCount)
    {
        if (nCount==1)
        {
            dlgWait.Create(IDD_WAIT, AfxGetMainWnd());
            InitEpisode(dlg.m_arrEpisodes[0]);
        }
        else
        {
            if (dlg.DoModal()==IDOK)
            {
                //InitEpisode (CString("e:\\mydocs\\1.scr"));
                dlgWait.Create(IDD_WAIT, AfxGetMainWnd());
                InitEpisode(dlg.m_arrEpisodes[dlg.m_nEpisode]);
            }
            else
            {
                PostQuitMessage(0);
                return FALSE;
            }
        }
    }
    else
    {
        CString str;
        GetEpisodeFilename(str);
        if (str!="")
        {
            InitEpisode(str);        
        }
        else
        {
            AfxMessageBox("No data file found");
            PostQuitMessage(0);
            return FALSE;
        }
    }

    InitSounds();
	InitLevel (0);    
    InitGamma();

	m_nScore = 0;
	m_nLives = 5;
	m_nLifeForce = 100;

	return TRUE;
}

BOOL CGame::InitLevel (CScriptArray &s)
{

	BOOL bStatus = FALSE;
	m_bCritical = TRUE;

	// Split the background from the sprites
	m_sBK.Forget();
	m_sFW.Forget();
	SplitScript (s, m_sBK, m_sFW);

	if (PrepareLevel(s))
	{
		m_nLevelIntroStatus = 0;
		m_bPlayLevelIntro = TRUE;

		m_bCritical = FALSE;
		m_bGameOver = FALSE;

		bStatus = TRUE;
		OutputDebugString("InitLevel good\n");
	}
	else
	{
		bStatus = FALSE;
		OutputDebugString("InitLevel failed\n");	
	}

	return bStatus;
}

void CGame::MoveBy (int x, int y)
{
	m_nMX = m_nMX + x;
	m_nMY = m_nMY + y;
}

void CGame::MoveTo (int x, int y)
{
	m_nMX = x;
	m_nMY = y;
}

BOOL CGame::DrawToBuffer ( int nLen, int nHei, int nMaxX, int nMaxY, DDSURFACEDESC & ddsurfdesc)
{
	
	DWORD d;
	DWORD s;

	int nPitch = ddsurfdesc.lPitch;
	d = 0*nPitch 	+ (DWORD) ddsurfdesc.lpSurface;
	s = m_nMX + nMaxX * (m_nMY) 
			+ (DWORD) m_pScrollBK;

	int nRows = min (nHei, nMaxY - m_nMY);
	int nCols = min (nLen, nMaxX - m_nMX);

	if (nCols>0)
	{
		_asm {

			mov esi, s
			mov edi, d

			mov edx, nRows
			or edx, edx
			je _out

_loop2:
			mov ecx, nCols
			xor ebx,ebx

_loop:
			mov eax, [esi+ebx]
			mov [edi+ebx], eax
			inc ebx
			inc ebx
			inc ebx
			inc ebx
			cmp ecx,ebx
			jne _loop

			add edi, nPitch
			add esi, nMaxX

			dec edx
			or edx,edx
			jne _loop2
_out:
			}
	}

	// draw the sprites
	DrawScript (&m_sFW, m_nMX, m_nMY, 
		ddsurfdesc.lpSurface, SCREENLEN, SCREENHEI, nPitch);

	return TRUE;
}

void CGame::FillSurface (UCHAR nColor, UCHAR *pDest, int nLen, int nHei, int nPitch)
{
	if (!pDest || !nPitch || !(nLen * nHei))
		return;

	int nFillSize = nLen/4;
	int nAdd = nPitch - (nLen - (nLen %4));
	int nRows = nHei;

			_asm {
				push eax
				push ebx
				push ecx
				push edx
				push edi
				push esi
				
				mov ebx, nRows

				mov edi, pDest
				mov al, nColor
				mov ah,al
				shl eax,16
				mov al,nColor
				mov ah,al

				mov esi, nFillSize
				mov edx, nAdd
_loop2:
				mov ecx, esi

_loop:
				mov [edi], eax  
				inc edi
				inc edi
				inc edi
				inc edi
				dec ecx
				or ecx,ecx
				jne _loop

				add edi, edx

				dec ebx
				or ebx,ebx
				jne _loop2

				pop esi
				pop edi
				pop edx
				pop ecx
				pop ebx
				pop eax
			}
}

void CGame::Animate(UINT nTicks)
{
	int nEntries = 	m_sFW.GetSize();
	int i;

	for (i=0; i<nEntries; i++)
	{
		CScriptEntry & entry = m_sFW[i];
		CProto & proto = m_arrProto[entry.m_nProto];

	  if (nTicks%(proto.m_nAniSpeed+1)==0)
		if (proto.m_bAnimate)
		{
			if ( proto.m_nClass == CLASS_PLATFORM_UP_DOWN
				|| proto.m_nClass == CLASS_PLATFORM_LEFT_RIGHT
				|| ((proto.m_nClass>=0x10)
				&& (proto.m_nClass<=0x1e)))
			{
				COBL3Filter &filter = 
					* m_arrOBL3[entry.m_nFrameSet];

				if (filter.GetSize()!=0)
				{
					if (entry.m_nFrameNo == 
						filter.GetSize()-1)
					{
						if (proto.m_nClass!=
							CLASS_ANIMATE_ONCE)
							  entry.m_nFrameNo =0;
						else
						{
							KillSprite(entry);
						}
					}
					else
					{
						entry.m_nFrameNo++;
					}
				}
			}
			else {
				if (proto.m_nClass>0x1f) 
				{
					COBL3Filter &filter = 
						* m_arrOBL3[entry.m_nFrameSet];
					if (filter.GetSize()>=2)
					{
						if (XOR (entry.m_nFrameNo,1)
							< filter.GetSize())
							entry.m_nFrameNo = 
							XOR (entry.m_nFrameNo,1);
					}
				}
			}
		}
	}
}

inline int CGame::XOR (int a, int b)
{

	int r;
	_asm {
		push eax
		mov eax, a
		xor eax, b
		mov r, eax
		pop eax
	}

	return r;
}

void CGame::OutputOBL3 (CSS3Frame * pFrame, int x, int y, int maxX, int maxY, BOOL bClear, UCHAR *pDest, int nPitch, BYTE nColor )
{
 
	if (pFrame!=NULL && pDest!=NULL && nPitch!=0)	
	{
		UCHAR *d;
		UCHAR *s;

		int yy;
		int nCols = min (x + pFrame->m_nLen, maxX) - x;
		int nRows = min (y + pFrame->m_nHei, maxY) - y;
	
		//if (nCols>0 && nRows>0 && x>=0 && y>=0)
		//if (nCols>0 && nRows>0 && x>=0)
		if (nCols>0 && x>=0)
		//for (yy=0; yy<nRows; yy++)
		for (yy=0; yy < pFrame->m_nHei; yy++)
		{
		  if ( (y + yy >= 0) && (y + yy < maxY))
		  {
			s = pFrame->Point(0 ,yy);
			d = (UCHAR*) pDest + (y+yy) * nPitch + x;

			if (bClear)
			{

				_asm {
					push eax
					push ecx
					push edx
					push edi
					push esi
					
					mov ecx, nCols
					mov esi, s
					mov edi, d
					mov edx,4

_loop:				cmp ecx,edx
					jb _Out
					mov eax, [esi]
					mov [edi], eax

					add edi,edx
					add esi,edx

					sub ecx, edx
					or ecx,ecx
					jne _loop

_Out:				pop esi
					pop edi
					pop edx
					pop ecx
					pop eax
				
					}
			}

			else
			{
				_asm
				{		
					push eax
					push ecx
					push edx
					push edi
					push esi
					
					mov ecx, nCols
					mov esi, s
					mov edi, d
					mov edx, 4

					mov bl, nColor

_loop_:				cmp ecx,edx
					jb _Out_
					mov eax, [esi]
					or eax,eax
					je zero

					or ax,ax
					je zero1

					or al,al
					je zero2			
					add al, bl
					mov [edi], al

zero2:				or ah,ah
					je zero3
					add ah,bl
					mov [edi+1], ah

zero3:				
zero1:				shr eax,16

					inc esi
					inc esi
					inc edi
					inc edi

					or ax,ax
					je zero1a

					or al,al
					je zero2a			
					add al,bl
					mov [edi],al

zero2a:				or ah,ah
					je zero3a
					add ah, bl
					mov [edi+1],ah

zero3a:
zero1a:				dec esi
					dec esi
					dec edi
					dec edi

zero:
					add edi,edx
					add esi,edx

					sub ecx, edx
					or ecx,ecx
					jne _loop_

_Out_:				pop esi
					pop edi
					pop edx
					pop ecx
					pop eax				
				}
			}
		  }
		}
	}
}

BOOL CGame::ManagePlayer (int nTicks)
{
	UINT nJoyState=0;
	int nAim = -1;
	static UINT nIdleTime = 0;
	if (nIdleTime==0)
		nIdleTime = nTicks;

	if (m_nPlayerEntry==-1) 
		return FALSE;

	CScriptEntry & player = m_sFW[m_nPlayerEntry];
	int nFlags = CheckPlayerHit (player);
	CScriptEntry _player = player;

	// Play Sound when appropriate
	int nWalkSound = SND_WALK;
	if ((nFlags & FLAG_METAL) == FLAG_METAL)
		nWalkSound = SND_METAL;
	if ((nFlags & FLAG_NOSOUND) == FLAG_NOSOUND)
		nWalkSound = -1;

	if (nTicks%12==0 && nWalkSound==SND_WALK)
			nWalkSound = SND_WALK2;

	// Check if player is falling
	int bFall = (CanFall (_player) &&
		!GetState(player, STATE_JUMP) );
	if (!GetState(player, STATE_FALL) && bFall)
		m_arrSounds["FALL"]->Play();
	else
		if (GetState(player, STATE_FALL) && !bFall)
			m_arrSounds["POUFLIGHT"]->Play();

	SetState (player, STATE_FALL, bFall);

	if (nFlags & FLAG_DEATH)
		SetState(player, STATE_DEAD, nFlags & FLAG_DEATH);

	// Control Player movements
	if (player.STATE_FLAG & STATE_DEAD)
	{
		if (nTicks%6==0 && (
			(player.m_nFrameNo %20)<19))
		{
			player.m_nFrameNo++;
		}

		if ((player.m_nFrameNo % 20) < 16) 
		{
			player.m_nFrameNo = player.m_nFrameNo 
			- (player.m_nFrameNo % 20) + 16;
			m_arrSounds["OUCH"]->Play();

			UnMapSprite(m_nPlayerEntry);
			player.m_nProto = (short)-1;
		}
	}
	else
	{
		if (!bFall && nTicks%2==0) {
			if (!GetState(player, STATE_JUMP)
				&& !(nFlags & FLAG_TELEPORT))
			{
				nAim = ManagePlayerMovements(player, nJoyState, nTicks, nWalkSound);
			}
		}
	}

	// Manage Player Jumping
	if (GetState(player, STATE_JUMP))
	{
		ManagePlayerJump (player);
	}

	// Manage TimeOut - how long after hit
	ManagePlyTimerOutCounter (player, nJoyState);

	// Make the player fall
	if ((nTicks%2==0) && (bFall))
	{
		if ((player.m_nY< BUFFERHEI-32) && CanWalk(_player, DOWN, FALSE))
		{
			UnMapSprite(m_nPlayerEntry);
			player.m_nY = player.m_nY + 8;	
			MapSprite(m_nPlayerEntry);
			AutoCenter(player, DOWN);
		}
	}

	// Animate the player object
	if (nTicks%4==0 && nAim!=-1 && nJoyState!=0) 
	{
		if ((player.m_nFrameNo %4) <=1) {
			player.m_nFrameNo = 
				player.m_nFrameNo - 
					(player.m_nFrameNo %20) +2 + nAim*4; 
		}
		else {
			player.m_nFrameNo = 
				player.m_nFrameNo - 
					(player.m_nFrameNo %20) +1 + nAim*4; 
		}
	}

	static bAlternate = FALSE;
	if ((nTicks %8)==0)
	{
		bAlternate = XOR(bAlternate,1);
	}

	if (! (player.STATE_FLAG & STATE_DEAD))
	{
		if (nJoyState!=0  )
		{
			nIdleTime = nTicks;	
		}
		else
		{
			if(( nTicks - nIdleTime) > 5) 
			{
				nIdleTime = nTicks;
				player.m_nFrameNo = 
				player.m_nFrameNo - 
				player.m_nFrameNo %4; 
			}
		}

		if (bAlternate && GetState(player, STATE_HIT)
			&& (nTicks%8<4))
		{
			player.m_nFrameNo = 
				player.m_nFrameNo | 3;
		}
		else
		{
			if (nJoyState!=0 && (player.m_nFrameNo & 3))
				player.m_nFrameNo = 
					player.m_nFrameNo -
						(player.m_nFrameNo & 2) +1;
		}
	}

	// autocenter
	// When off-screen
	if (player.m_nX < m_nMX)
	{
			AutoCenter(player, LEFT);
			AutoCenter(player, LEFT);
	}

	if (player.m_nX > m_nMX+ SCREENLEN)
	{
			AutoCenter(player, RIGHT);
			AutoCenter(player, RIGHT);
	}

	if (player.m_nY < m_nMY)
	{
			AutoCenter(player, UP);
			AutoCenter(player, UP);
	}

	if (player.m_nY > m_nMY + SCREENHEI)
	{
			AutoCenter(player, DOWN);
			AutoCenter(player, DOWN);
	}

	// Re-center while on screen
	if (nTicks%2==0) {
		if (!GetState(player, STATE_JUMP))
		{
			AutoCenter(player, UP);
			AutoCenter(player, DOWN);
		}

		AutoCenter(player, LEFT);
		AutoCenter(player, RIGHT);
	}

	// Manage Player firing 
	ManagePlayerFiring (player, nTicks, nJoyState);

	return TRUE;
}

BOOL CGame::CanWalk (CScriptEntry & entry, int nAim, BOOL bActor)
{
	UCHAR *pMap = GetMapEntry (entry);
	CSS3Frame & frame = * m_arrOBL3.GetFrame (entry);

	BOOL bIsPlayer = entry.m_nProto == TYPE_PLAYERS;

	int nBaseY;
	switch (nAim)
	{
		case UP:
			pMap = pMap - BUFFERLEN;
			if (entry.m_nY==0 && !bIsPlayer) 
				return FALSE;
	
			nBaseY = entry.m_nY - 1;
		break;

		case DOWN:
			pMap = pMap + BUFFERLEN * frame.m_nHei/8;
			if (entry.m_nY>= BUFFERHEI-frame.m_nHei)
				return FALSE;

			nBaseY = entry.m_nY + (frame.m_nHei/8);
		break;

		case LEFT:
			pMap = pMap -8;
			if (entry.m_nX==0)
				return FALSE;

			nBaseY = entry.m_nY;
		break;

		case RIGHT:
			pMap = pMap+ frame.m_nLen;
			if (entry.m_nX>= BUFFERLEN-frame.m_nLen)
				return FALSE;

			nBaseY = entry.m_nY;		
		break;

		default:
			return FALSE;
		break;
	}

	int x;
	int y;
	if (nAim==UP || nAim==DOWN)
	{
		if (nBaseY>=0)
		for (x=0; x<frame.m_nLen/8; x++)
		{
			USER_MapEntry *pMapEntry = 
				(USER_MapEntry*) (pMap + x*8);

			if (( pMapEntry->m_nBkClass == CLASS_SOLID_BACKGROUND)
				|| (pMapEntry->m_nFwClass == CLASS_SOLID_ANIMATED )
			//	|| (pMapEntry->m_nFwClass == CLASS_TELEPORT_PAD )
				|| (pMapEntry->m_nFwClass == CLASS_TELEPORT_DESTINATION )
				|| (( pMapEntry->m_nBkClass == CLASS_STOP) && bActor))
					return FALSE;

			if ((pMapEntry->m_nAcClass >=CLASS_GENERIC_COS))
				return FALSE;

			if ((nAim==DOWN) && 
				(pMapEntry->m_nBkClass ==CLASS_SOLID__AIM_DOWN_ONLY_))
				return FALSE;
		}
	}
	else
	{
		for (y=0; y<frame.m_nHei/8; y++)
		{
			if ((nBaseY+y)>=0)
			{
				USER_MapEntry *pMapEntry = 
					(USER_MapEntry*) (pMap +y*BUFFERLEN);

				if (( pMapEntry->m_nBkClass == CLASS_SOLID_BACKGROUND)
					|| (pMapEntry->m_nFwClass == CLASS_SOLID_ANIMATED )
				//	|| (pMapEntry->m_nFwClass == CLASS_TELEPORT_PAD )
					|| (pMapEntry->m_nFwClass == CLASS_TELEPORT_DESTINATION )
					|| (( pMapEntry->m_nBkClass == CLASS_STOP) && bActor))
						return FALSE;

				if ((pMapEntry->m_nAcClass >=CLASS_GENERIC_COS))
					return FALSE;
			}
		}
	}

	return TRUE;	
}

BOOL CGame::CanFall (CScriptEntry & entry)
{
	UCHAR *pMap = GetMapEntry (entry);
	CSS3Frame & frame = * m_arrOBL3.GetFrame (entry);

	if (!CanWalk (entry, DOWN, FALSE)) 
		return FALSE;

	if (entry.m_nY<0)
		return TRUE;

	int x,y;
	int i=0;
	int ii=0;
	for (y=0; y<frame.m_nHei/8; y++) {
		for (x=0; x<frame.m_nLen/8; x++) {
			if (*(pMap+x*8) && *(pMap+x*8)<0xa) 
				//return FALSE;
				i++;
		}
		pMap = pMap + BUFFERLEN;
	}

	for (x=0; x<frame.m_nLen/8; x++)
	{
		if (*(pMap+x*8) && *(pMap+x*8)<0xa) 
			ii++;
	}

	int nEntrySize = (frame.m_nHei / 8) * 
		(frame.m_nLen / 8) ;

	return (i<nEntrySize) && (ii<frame.m_nLen/8);
	// return TRUE;
}


BOOL CGame::MapSprite (int nEntry, BOOL bSmart)
{
	CGameFile3 & game = * this;
	COBL3Array & arrOBL3 = game.m_arrOBL3;
	CProtoArray & arrProto = game.m_arrProto;
	CSS3Frame *pFrame;

	int x;
	int y;

	CScriptEntry entry = m_sFW[nEntry];
	int nClass = arrProto[entry.m_nProto].m_nClass;

	if (entry.m_nY<0)
		return FALSE;

	UCHAR *pData = GetMapEntry (entry);

	if (nClass!=0 && 
		(entry.m_nTriggerKey & TRIGGER_HIDDEN)==0) 
	{
		pFrame = arrOBL3.GetFrame(entry);
		for (y=0; (y<pFrame->m_nHei/8) &&
				(y*8+ entry.m_nY < BUFFERHEI); y++)
		{	
			USER_MapEntry *pMapEntry = 
				(USER_MapEntry*) pData;
			pData = pData + BUFFERLEN;

			if (entry.m_nY + y >= 0)
			for (x=0; (x<pFrame->m_nLen/8) &&
					(x*8+ entry.m_nX < BUFFERLEN); x++)
			{
				if (nClass== CLASS_PLAYER_OBJECT)
					pMapEntry->m_bPlayer = TRUE;						
				else
				if (nClass < CLASS_GENERIC_COS) 
				{	
					pMapEntry->m_nFwClass = 
						arrProto[entry.m_nProto].m_nClass;

					pMapEntry->m_nFwEntry = nEntry;
				}
				else
				{
					pMapEntry->m_nAcClass = 
						arrProto[entry.m_nProto].m_nClass;

					pMapEntry->m_nAcEntry = nEntry;
				}

				pMapEntry ++;
			}					
		}
	}
	return TRUE;
}

BOOL CGame::UnMapSprite (int nEntry)
{
	CGameFile3 & game = * this;
	COBL3Array & arrOBL3 = game.m_arrOBL3;
	CProtoArray & arrProto = game.m_arrProto;
	CSS3Frame *pFrame;

	int x;
	int y;

	CScriptEntry & entry = m_sFW[nEntry];
	UCHAR *pData = GetMapEntry (entry);
	int nClass = arrProto[entry.m_nProto].m_nClass;

	if (nClass!=0) {
		pFrame = arrOBL3.GetFrame(entry);
		for (y=0; (y<pFrame->m_nHei/8) &&
				(y*8+ entry.m_nY < BUFFERHEI); y++)
		{	
			USER_MapEntry *pMapEntry = 
				(USER_MapEntry*) pData;
			pData = pData + BUFFERLEN;

			if (entry.m_nY + y >= 0)
			for (x=0; (x<pFrame->m_nLen/8) &&
					(x*8+ entry.m_nX < BUFFERLEN); x++)
			{
				if (pMapEntry->m_bPlayer && 
					nClass == CLASS_PLAYER_OBJECT)
						pMapEntry->m_bPlayer = FALSE;

				if (pMapEntry->m_nFwEntry == nEntry)
				{
					pMapEntry->m_nFwClass =0;
					pMapEntry->m_nFwEntry = 0;
				}

				if (pMapEntry->m_nAcEntry == nEntry)
				{
					pMapEntry->m_nAcClass =0;
					pMapEntry->m_nAcEntry = 0;
				}
				pMapEntry++;
			}					
		}
	}
	return TRUE;

}

int CGame::CheckPlayerHit (CScriptEntry & player)
{
	CGameFile3 & game = * this;
	COBL3Array & arrOBL3 = game.m_arrOBL3;
	CProtoArray & arrProto = game.m_arrProto;
	CSS3Frame *pFrame;

	int x;
	int y;
	int nFlags=0;

	if (player.m_nY<0)
		return 0;

	UCHAR *pData = GetMapEntry (player.m_nX, player.m_nY);
			
	pFrame = arrOBL3.GetFrame(player);
	for (y=0; (y<pFrame->m_nHei/8) &&
				(y*8+ player.m_nY < BUFFERHEI); y++)
	{	
		USER_MapEntry *pMapEntry = 
			(USER_MapEntry*) pData;

		pData = pData + BUFFERLEN;

		if (player.m_nY + y >= 0)
		for (x=0; (x<pFrame->m_nLen/8) &&
					(x*8+ player.m_nX < BUFFERLEN); x++)
		{
			CScriptEntry & object = 
				 m_sFW[pMapEntry->m_nFwEntry] ;

			int nTriggerKey = 
				object.m_nTriggerKey & TRIGGER_KEYS;

			CProto & proto = arrProto[object.m_nProto];

			switch (pMapEntry->m_nBkClass)
			{
				case CLASS_WATER:
					nFlags = nFlags | FLAG_NOSOUND | FLAG_WATER;
				break;

				case CLASS_METAL_LADDERS:
					nFlags = nFlags | FLAG_METAL;
				break;

				case CLASS_IMMEDIATE_DEADLY:
					nFlags = nFlags | FLAG_DEATH;
				break;
			}

			switch (pMapEntry->m_nFwClass)
			{
				case CLASS_PICKUP_TRIGGERS:
					UnMapSprite(pMapEntry->m_nFwEntry);

					if (nTriggerKey)
					{
						CastTrigger(object);
					}

					KillSprite(object);

				break;

				case CLASS_TELEPORT_PAD:
					
					if (nTriggerKey)
					{
						int i;
						for (i=0; i<m_sFW.GetSize(); i++)
						{
							CScriptEntry & temp = m_sFW[i];
							if (temp.m_nTriggerKey == nTriggerKey)
							{
								CProto & proto = m_arrProto[temp.m_nProto];
								if (proto.m_nClass == CLASS_TELEPORT_DESTINATION)
								{
									m_arrSounds["TELEPORT"]->Play();

									UnMapSprite(m_nPlayerEntry);
									player.MoveTo(temp.m_nX+8, temp.m_nY-32);
									MapSprite(m_nPlayerEntry, FALSE);

									nFlags = nFlags | FLAG_TELEPORT;
									
									return nFlags;
								}
							}
						}
					}

					break;

				default:
				break;
			}
			pMapEntry ++;
		}					
	}
	return nFlags;
}

UCHAR * CGame::GetMapEntry (int x, int y)
{
	return (UCHAR *) m_pMap + (y/8)* BUFFERLEN + x;
}

UCHAR * CGame::GetMapEntry (CScriptEntry & entry)
{
	return (UCHAR *) m_pMap + (entry.m_nY/8)* BUFFERLEN 
		+ entry.m_nX;
}

BOOL CGame::PlayerZKey()
{
	if (m_nPlayerEntry==-1) 
		return FALSE;

	CScriptEntry & player = m_sFW[m_nPlayerEntry];
	CScriptEntry _player = m_sFW[m_nPlayerEntry];

	CGameFile3 & game = * this;

	COBL3Array & arrOBL3 = game.m_arrOBL3;
	CProtoArray & arrProto = game.m_arrProto;
	CSS3Frame *pFrame;

	int x;
	int y;

	if (player.m_nY<0)
		return FALSE;

	UCHAR *pData = GetMapEntry (_player);
			
	pFrame = arrOBL3.GetFrame(_player);
	for (y=0; (y<pFrame->m_nHei/8) &&
				(y*8+ player.m_nY < BUFFERHEI); y++)
	{	
		USER_MapEntry *pMapEntry = 
			(USER_MapEntry*) pData;

		pData = pData + BUFFERLEN;

		if (player.m_nY + y >= 0)
		for (x=0; (x<pFrame->m_nLen/8) &&
					(x*8+ player.m_nX < BUFFERLEN); x++)
		{
			CScriptEntry & object = 
				 m_sFW[pMapEntry->m_nFwEntry] ;

			switch (pMapEntry->m_nFwClass)
			{
				case CLASS_Z_KEY_SWITCH:
					player.m_nFrameNo = 
					player.m_nFrameNo - 
					player.m_nFrameNo %20; 

					object.m_nFrameNo = 
						XOR (object.m_nFrameNo,1);
					m_arrSounds["CLICK"]->Play();
				
					CastTrigger (object);

					return TRUE;
				break;

				default:
				break;
			}
			pMapEntry ++;
		}					
	}
	return TRUE;
}

void CGame::AutoCenter (CScriptEntry & player, UINT nAim)
{
	switch (nAim)
	{
		case UP:
			if ((player.m_nY - m_nMY) < SCREENHEI/2)
			{
				if (m_nMY !=0)
					m_nMY = m_nMY -4;
			}
		break;

		case DOWN:
			if ((player.m_nY - m_nMY) > SCREENHEI/2)
			{
				if (m_nMY + SCREENHEI < BUFFERHEI)
				m_nMY = m_nMY +4;
			}
		break;

		case LEFT:
			if ((player.m_nX - m_nMX) < SCREENLEN/2)
			{
				if (m_nMX !=0)
					m_nMX = m_nMX -4;
			}
		break;

		case RIGHT:
			if ((player.m_nX - m_nMX) > SCREENLEN/2)
			{
				if (m_nMX + SCREENLEN < BUFFERLEN)
					m_nMX = m_nMX +4;

			}
		break;
	}
}

void CGame::ManageObjects (int nTicks)
{
	static int arrAims [4][6] = {
		LEFT,  LEAP_LEFT,  UP,   RIGHT, LEAP_RIGHT, DOWN,
		RIGHT, LEAP_RIGHT, DOWN, LEFT,  LEAP_LEFT,  UP,
		DOWN,  LEFT, LEAP_LEFT,   UP, RIGHT, LEAP_RIGHT,
		UP, RIGHT, LEAP_RIGHT, DOWN, LEFT, LEAP_LEFT
	};

	static int arrComplex[4][6] = {
		LEFT, LEAP_LEFT, UP, UP, DOWN, DOWN,
		RIGHT, LEAP_RIGHT,UP, UP, DOWN, DOWN,
		UP, UP,  RIGHT, LEAP_RIGHT, LEFT, LEAP_LEFT,
		DOWN, DOWN,  RIGHT, LEAP_RIGHT, LEFT, LEAP_LEFT,
	};

	int n;
	int bCanWalk;
	int x,y;
	int u;
	int i;

	//char szTemp[128];

	CScriptEntry & player = m_sFW[m_nPlayerEntry];

	for (n=0; n<m_sFW.GetSize(); n++)
	{
		CScriptEntry & entry = m_sFW[n];

		switch (entry.m_nProto)
		{
			case TYPE_POINTS:
				if (nTicks%8==0)
				{
					if (entry.m_nY!=0 && 
						IsVisible(entry))	
					{
						entry.m_nY = entry.m_nY -8;
					}
					else
					{
						entry.m_nProto =0;
						entry.m_nFrameNo =0;
						entry.m_nFrameSet =0;
					}
				}		
			break;
		}

		CProto & proto = m_arrProto[entry.m_nProto];
		COBL3Filter & filter = * m_arrOBL3[entry.m_nFrameSet];
		int nAim = entry.AIM_FLAG;
		int nAimT;

		if ((entry.m_nTriggerKey & TRIGGER_HIDDEN) ==0)
		switch (proto.m_nClass)
		{
			case CLASS_GENERIC_COS___COMPLEX:

				x = -1;
				y = 0;
				if (IsPlayerAlign(entry, player, UP | DOWN))
				{			
					x = (player.m_nX > entry.m_nX);
					y = 2 + (player.m_nY > entry.m_nY) * 2;		
				}  // UP | DOWN

				if ( (x == -1) && IsPlayerAlign(entry, player, LEFT | RIGHT))
				{
					x = (player.m_nY > entry.m_nY) + 2;
					y = 2 + (player.m_nX > entry.m_nX) * 2;
				} // LEFT | RIGHT 

				// Manage AI
				if (x != -1)
				{
					u = -1;

					for (i=0;(i<2) && (u==-1); i++)
					{
						if (TestAim(entry, arrComplex[x][i]))
						{
							u = i;
						}
					}

					if (u != -1)
					{
						x = arrComplex[x][u];
					}
					else
					{			
						for (i=0;(i<2) && (u==-1); i++)
						{
							if (TestAim(entry, arrComplex[x][y+i]))
							{
								u = y + i;
							}
						}

						if (u != -1)
						{
							x = arrComplex[x][u+i];
						}
						else
						{
							x = -1;
						}
					}
				}

				if (CanFall (entry))
				{
					if (nTicks%1==0) {
						UnMapSprite(n);
						entry.MoveBy(0,8);
						MapSprite(n);
						break;
					}
				}		
				else
				{
					if (x != -1 && ((!proto.m_nMoveSpeed) 
							|| (nTicks % proto.m_nMoveSpeed)==0))
					{			
						if (IsPlayerThere(entry, entry.AIM_FLAG)
							&& !GetState(player, STATE_HIT))
						{
							SetState(player, STATE_HIT, TRUE);
							player.TIMEOUT_DELAY = CONST_TIMEOUT;
						}

						UnMapSprite(n);

						entry.AIM_FLAG = x & 3;

						if (filter.GetSize() ==4)
						{
							if (entry.AIM_FLAG==LEFT)
							{
								entry.m_nFrameNo =
									entry.m_nFrameNo & 1;
							}

							if (entry.AIM_FLAG==RIGHT)
							{
								entry.m_nFrameNo =
									(entry.m_nFrameNo & 1) +2;
							}
						}

						if (TestAim(entry, x))
						{
							MoveSprite(entry, x);
						}

						MapSprite(n);
						break;
					}		
					else
					{
						UnMapSprite(n);
						if (TestAim(entry, entry.AIM_FLAG))
						{
							if ((proto.m_nMoveSpeed==0) 
								|| (nTicks % (proto.m_nMoveSpeed) ==0))
							{

								MoveSprite(entry, entry.AIM_FLAG);
		
								if (IsPlayerThere(entry, entry.AIM_FLAG)
									&& !GetState(player, STATE_HIT))
								{
									SetState(player, STATE_HIT, TRUE);
									player.TIMEOUT_DELAY = CONST_TIMEOUT;
								}
							
							}
							MapSprite(n);

							break;
						}
						MapSprite(n);
					}
				}
				
				nAim = entry.AIM_FLAG;

			case CLASS_GENERIC_COS :
				UnMapSprite(n);						
				if (filter.GetSize() ==4)
				{
					if (nAim==LEFT)
					{
						entry.m_nFrameNo =
							entry.m_nFrameNo & 1;
					}

					if (nAim==RIGHT)
					{
						entry.m_nFrameNo =
							(entry.m_nFrameNo & 1) +2;
					}
				}

				bCanWalk = FALSE;
				if (CanFall (entry) )
				{
					if( nTicks % 1 ==0) {
						entry.MoveBy(0,8);
					}
				}		
				else
				if ((proto.m_nMoveSpeed==0) 
					|| (nTicks % (proto.m_nMoveSpeed) ==0))
				{
				
					bCanWalk = FALSE;
					for (x=0; x<6 && !bCanWalk; x++)
					{
						nAimT = arrAims[nAim][x];
						if (nAimT>DOWN && nAimT!=nAim)
						{
							bCanWalk = 
								TestAimEx (entry, nAimT , 2);
						}
						else
						{
							bCanWalk = 
								TestAim (entry, nAimT);
						}
					}						

					x --;
					if (bCanWalk) {
						nAim= arrAims[nAim][x];
						MoveSprite(entry, nAim);

						if (IsPlayerThere(entry, nAim & RIGHT)
							&& !GetState(player, STATE_HIT))
						{
							SetState(player, STATE_HIT, TRUE);
							player.TIMEOUT_DELAY = CONST_TIMEOUT;
						}

						entry.AIM_FLAG = nAim & RIGHT;
					} // if bCanWalk
				} // if nTicks

				MapSprite(n);
				
			break; // CLASS_GENERIC_COS

			case CLASS_DRONE_LEFT_RIGHT:
				UnMapSprite(n);
				if (nAim==UP || nAim==DOWN)
				{
					nAim = nAim + LEFT;
				}

				if (filter.GetSize() ==4)
				{
					if (nAim==LEFT)
					{
						entry.m_nFrameNo =
							entry.m_nFrameNo & 1;
					}

					if (nAim==RIGHT)
					{
						entry.m_nFrameNo =
							(entry.m_nFrameNo & 1) +2;
					}
				}

			case CLASS_DRONE_UP_DOWN:
				UnMapSprite(n);
				if (CanFall (entry) )
				{
					if( nTicks % 1 ==0)
					{
						entry.MoveBy(0,8);
					}
				}
				else
				if ((proto.m_nMoveSpeed==0) 
					|| (nTicks % (proto.m_nMoveSpeed) ==0))
				{
					
					if (TestAim (entry, nAim))
					{
						if (IsPlayerThere(entry, nAim & RIGHT)
							&& !GetState(player, STATE_HIT))
						{
							SetState(player, STATE_HIT, TRUE);
							player.TIMEOUT_DELAY = CONST_TIMEOUT;
						}

						MoveSprite(entry, nAim);
						entry.AIM_FLAG = nAim;

					}
					else
					{
						nAim = XOR (nAim,1);
						entry.AIM_FLAG = nAim;				
					}
				}

				MapSprite(n);

			break; // CLASS_DRONE_UP_DOWN && LEFT_RIGHT

			case CLASS_WACKER_LEFT_RIGHT:
			case CLASS_PLATFORM_LEFT_RIGHT:
				UnMapSprite(n);

				if (proto.m_nClass< CLASS_PLATFORM_UP_DOWN &&
				       filter.GetSize() ==4)
				{
					if (nAim==LEFT)
					{
						entry.m_nFrameNo =
							entry.m_nFrameNo & 1;
					}

					if (nAim==RIGHT)
					{
						entry.m_nFrameNo =
							(entry.m_nFrameNo & 1) +2;
					}
				}	
				
				if (nAim==UP || nAim==DOWN)
				{
					nAim = nAim + LEFT;
				}

				if ((proto.m_nMoveSpeed==0) 
					|| (nTicks % (proto.m_nMoveSpeed) ==0))
				{
					if (CanWalk (entry, nAim, TRUE))
					{

						if (IsPlayerThere (entry, UP) && 
							proto.m_nClass != CLASS_WACKER_LEFT_RIGHT)
						{							
							if (CanWalk	(player, nAim, FALSE))
							{
								UnMapSprite(m_nPlayerEntry);
								MoveSprite (player, nAim);
								MapSprite(m_nPlayerEntry);
								AutoCenter(player, nAim);
								AutoCenter(player, nAim);
							}
							else
							{
								SetState (player, STATE_DEAD, TRUE);
							}
						}

						if (IsPlayerThere (entry, nAim))
						{							
							if (CanWalk	(player, nAim, FALSE))
							{
								UnMapSprite(m_nPlayerEntry);
								MoveSprite (player, nAim);
								MapSprite(m_nPlayerEntry);
								AutoCenter(player, nAim);
								AutoCenter(player, nAim);
							}
							else
							{
								SetState (player, STATE_DEAD, TRUE);
							}
						}

						MoveSprite(entry,nAim);
						entry.AIM_FLAG = nAim;
					}
					else
					{
						nAim = XOR (nAim,1);
						entry.AIM_FLAG = nAim;				
					}
				}

				MapSprite(n);

			break; // CLASS_WACKER_LEFT_RIGHT && CLASS_PLATFORM_LEFT_RIGHT

			case CLASS_WACKER_UP_DOWN:
			case CLASS_PLATFORM_UP_DOWN:
				UnMapSprite(n);

				if ((proto.m_nMoveSpeed==0) 
					|| (nTicks % (proto.m_nMoveSpeed) ==0))
				{
					
					if (CanWalk (entry, nAim, TRUE))
					{
						if (IsPlayerThere (entry, nAim))
						{							
							if (CanWalk	(player, nAim, FALSE))
							{
								UnMapSprite(m_nPlayerEntry);
								MoveSprite (player, nAim);
								MapSprite(m_nPlayerEntry);
								AutoCenter(player, nAim);
								AutoCenter(player, nAim);
							}
							else
							{
								SetState (player, STATE_DEAD, TRUE);
							}
						}

						if ((nAim==DOWN) && 
							(IsPlayerThere (entry,UP)))
						{
								UnMapSprite(m_nPlayerEntry);
								MoveSprite (player, nAim);
								MapSprite(m_nPlayerEntry);
								AutoCenter(player, nAim);
								AutoCenter(player, nAim);
						}
						
						MoveSprite(entry,nAim);
						entry.AIM_FLAG = nAim;

					}
					else
					{
						nAim = XOR (nAim,1);
						entry.AIM_FLAG = nAim;				
					}
				}

				MapSprite(n);

				break; // CLASS_PLATFORM_LEFT_RIGHT

				case CLASS_PLAYER_BULLET:
				if ((proto.m_nMoveSpeed==0) 
					|| (nTicks % (proto.m_nMoveSpeed) ==0))
				{
					if (CanWalk (entry, entry.AIM_FLAG))
					{
						UnMapSprite(n);
						MoveSprite (entry, entry.AIM_FLAG);
						MapSprite(n);
					}
					else
					{
						UnMapSprite(n);
						KillSprite (entry);
					}
				}
				break; // CLASS_PLAYER_BULLET

				case CLASS_CREATURE_BULLET:
				if ((proto.m_nMoveSpeed==0) 
					|| (nTicks % (proto.m_nMoveSpeed) ==0))
				{
					if (IsPlayerThere(entry, entry.AIM_FLAG))
					{
						if(!GetState(player, STATE_HIT))
						{
							SetState(player, STATE_HIT, TRUE);
							player.TIMEOUT_DELAY = CONST_TIMEOUT;
						}
						
						UnMapSprite(n);
						MoveSprite (entry, entry.AIM_FLAG);
						KillSprite(entry);
						break;
					}

					if (CanWalk (entry, entry.AIM_FLAG))
					{
						UnMapSprite(n);
						MoveSprite (entry, entry.AIM_FLAG);
						MapSprite(n);
					}
					else
					{
						UnMapSprite(n);
						KillSprite (entry);
					}
				}
				break; // CLASS_CREATURE_BULLET

				case CLASS_VAMPIRE_PLANT_SOLID:

					for (nAim=0; nAim<4; nAim++)
					{
						if (IsPlayerThere(entry, nAim)
							&& !GetState(player, STATE_HIT))
						{
							SetState(player, STATE_HIT, TRUE);
							player.TIMEOUT_DELAY = CONST_TIMEOUT;
							break;
						}
					}
					
				break; // CLASS_VAMPIRE_PLANT_SOLID:

		} // switch proto.nClass
	} // for n
}

BOOL CGame::SelectDevice (CWnd *pWnd)
{
	CDlgOptions dlg;
	CGame & game = *this;
	if (dlg.DoModal()==IDOK)
	{
		if (dlg.m_pGuid!=NULL )
		{
			if (game.m_lpdid2!=NULL) {
				game.m_lpdid2->Unacquire();
				game.m_lpdid2->Release();
				game.m_lpdid2=NULL;
			}

    		if (game.InitIDevice( game.m_lpdid2, (GUID *)dlg.m_pGuid, (CWnd*)pWnd))
				game.m_lpdid2->Acquire();
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGame::CenterOnPlayer (CScriptEntry & player)
{

	MoveTo (0,0);

	if (player.m_nX > SCREENLEN /2)
	{
		MoveBy( min (BUFFERLEN - SCREENLEN,
			player.m_nX - SCREENLEN /2), 0);
	}

	if (player.m_nY > SCREENHEI /2)
	{
		MoveBy(0, min (player.m_nY- SCREENHEI /2,
			BUFFERHEI - SCREENHEI));
	}

	return TRUE;
}

BOOL CGame::TestAim (CScriptEntry & entry, int nAim)
{
	CScriptEntry _entry = entry;
	switch (nAim)
	{
		case UP:
			_entry.MoveBy (0,-8);
			break;
		case DOWN:
			_entry.MoveBy (0,8);
			break;
		case LEFT:
			_entry.MoveBy (-8,0);
			break;
		case RIGHT:
			_entry.MoveBy (8,0);
			break;
		
		case LEAP_LEFT:
			if (CanWalk(entry, DOWN))
				return FALSE;

			_entry.MoveBy (0, -8);
			if (!CanWalk (entry, UP, TRUE) ||
				!CanWalk (_entry, LEFT, TRUE))
				return FALSE;
			_entry.MoveBy (-8,0);
			return !CanFall (_entry);

		case LEAP_RIGHT:
			if (CanWalk(entry, DOWN))
				return FALSE;

			_entry.MoveBy (0, -8);
			if (!CanWalk (entry, UP, TRUE) ||
				!CanWalk (_entry, RIGHT, TRUE))
				return FALSE;
			_entry.MoveBy (8,0);
			return !CanFall (_entry);

		default:
			return FALSE;
	}
	if (nAim>=LEFT)
		return (CanWalk (entry, nAim, TRUE) &&
			(!CanFallHigh (_entry)));
	else
		return (CanWalk (entry, nAim, TRUE) &&
			(!CanFall (_entry)));

}

void CGame::HideSystemClass (CScriptArray & script, BOOL bHide)
{
	int n;
	for (n=0; n<script.GetSize(); n++)
	{
		CScriptEntry & entry = script[n];
		CProto & proto = m_arrProto[entry.m_nProto];
		int nIndex = m_arrClasses.
			GetIndexFor (proto.m_nClass);

		if (nIndex!=-1 && m_arrClasses[nIndex]->m_bSystem)
		{
			if (bHide)
			{
				entry.m_nFrameNo = entry.m_nFrameNo | 0x8000;
			}
			else
			{
				entry.m_nFrameNo = entry.m_nFrameNo & 0x7fff;
			}
		}
	}
}

BOOL CGame::CanFallHigh (CScriptEntry & entry)
{
	CScriptEntry _entry = entry;
	if (!CanFall(entry))
		return FALSE;

	_entry.MoveBy (0,8);
	return CanFall(_entry);
}


BOOL CGame::IsPlayerThere (CScriptEntry & entry, int nAim)
{
	UCHAR *pMap = GetMapEntry (entry.m_nX, entry.m_nY);

	CSS3Frame & frame = * m_arrOBL3.GetFrame (entry);

	switch (nAim)
	{
		case UP:
			pMap = pMap - BUFFERLEN;
			if (entry.m_nY==0)
				return FALSE;
		break;

		case DOWN:
			pMap = pMap + BUFFERLEN * frame.m_nHei/8;
			if (entry.m_nY>= BUFFERHEI-frame.m_nHei)
				return FALSE;
		break;

		case LEFT:
			pMap = pMap -8;
			if (entry.m_nX==0)
				return FALSE;
		break;

		case RIGHT:
			pMap = pMap+ frame.m_nLen;
			if (entry.m_nX>= BUFFERLEN-frame.m_nLen)
				return FALSE;
		break;

		default:
			return FALSE;
		break;
	}

	int x;
	int y;
	if (nAim==UP || nAim==DOWN)
	{
		for (x=0; x<frame.m_nLen/8; x++)
		{
			USER_MapEntry *pMapEntry = 
				(USER_MapEntry*) (pMap + x*8);

			if (pMapEntry->m_bPlayer)
				return TRUE;
		}
	}
	else
	{
		for (y=0; y<frame.m_nHei/8; y++)
		{
			USER_MapEntry *pMapEntry = 
				(USER_MapEntry*) (pMap +y*BUFFERLEN);

			if (pMapEntry->m_bPlayer)
				return TRUE;
		}
	}
	return FALSE;
}

void CGame::MoveSprite (CScriptEntry & entry, int nAim)
{
	switch (nAim)
	{
		case UP:
			entry.MoveBy (0,-8);
		break;

		case DOWN:
			entry.MoveBy (0,8);
		break;

		case LEAP_LEFT:
			entry.MoveBy (0,-8);
		case LEFT:
			entry.MoveBy (-8,0);
		break;

		case LEAP_RIGHT:
			entry.MoveBy (0,-8);
		case RIGHT:
			entry.MoveBy (8,0);
		break;

		default:
		break;

	} // switch (nAim)
}

void CGame::SetState (CScriptEntry & entry, int nState, BOOL bOn)
{
	if (bOn)
	{
		entry.STATE_FLAG = entry.STATE_FLAG | nState;
	}
	else
	{
		entry.STATE_FLAG = entry.STATE_FLAG - (entry.STATE_FLAG & nState);
	}
}

BOOL CGame::GetState (CScriptEntry & entry, int nState)
{
	return ((entry.STATE_FLAG & nState)!=0);
}

void CGame::ManagePlyTimerOutCounter (CScriptEntry & player, UINT nJoyState)
{
	// Check hit - Dec TimeOutDelay
	if (!GetState(player, STATE_BEGINNING))
	{
		if (player.TIMEOUT_DELAY==0)
			SetState(player, STATE_HIT, FALSE);
		else
			player.TIMEOUT_DELAY--;
	}

	if (nJoyState && GetState(player, STATE_BEGINNING))
	{
		SetState(player, 
			STATE_HIT | STATE_BEGINNING, FALSE);
	}
}

int CGame::ManagePlayerMovements (CScriptEntry & player, UINT & nJoyState, int nTicks, int nWalkSound)
{
	int nAim = -1;
	CScriptEntry _player = player;

	if (PollDevice(m_lpdid2, nJoyState))
	{

		if ((nJoyState & JOY_JUMP) &&
			CanWalk(player, UP))
		{
			int _nJoyState = XOR(nJoyState, JOY_JUMP);
			if (_nJoyState & JOY_FIRE)
				_nJoyState = XOR (_nJoyState, JOY_FIRE);
			
			switch (_nJoyState)
			{

				case JOY_UP:
					if (CanWalk(player, UP))
					{
						player.AIM_FLAG = UP;
						SetState (player, STATE_JUMP, TRUE);
						player.JUMP_STATUS = 0;					
						m_arrSounds["JUMP"]->Play();				
		
						return -1;
					}
				break;

				case JOY_DOWN:
					player.AIM_FLAG = DOWN;
				break;

				case JOY_LEFT | JOY_DOWN:
					if (CanWalk(player, LEFT))
					{
						player.AIM_FLAG = LEFT_DOWN;
						SetState (player, STATE_JUMP, TRUE);
						player.JUMP_STATUS = 0;
						m_arrSounds["JUMP"]->Play();

						player.m_nFrameNo = 
						player.m_nFrameNo - 
							(player.m_nFrameNo %20)  
							//(player.m_nFrameNo&3)
							+ LEFT*4 +2; 						

						return LEFT;
					}
				break; // LEFT + DOWN

				
				case JOY_LEFT | JOY_UP:
					player.AIM_FLAG = LEFT_UP;
					SetState (player, STATE_JUMP, TRUE);
					player.JUMP_STATUS = 0;
					m_arrSounds["JUMP"]->Play();

					player.m_nFrameNo = 
					player.m_nFrameNo - 
						(player.m_nFrameNo %20)  
						//(player.m_nFrameNo&3)
						+ LEFT*4 +2; 						

					return LEFT;
				break; // LEFT + UP

				case JOY_LEFT:
					if (CanWalk(player, LEFT))
					{
						player.AIM_FLAG = LEFT;
						SetState (player, STATE_JUMP, TRUE);
						player.JUMP_STATUS = 0;
						m_arrSounds["JUMP"]->Play();

					player.m_nFrameNo = 
					player.m_nFrameNo - 
						(player.m_nFrameNo %20)  
						//(player.m_nFrameNo&3)
						+ LEFT*4 +2; 				

						return LEFT;
					}
				break; // LEFT

				case JOY_RIGHT | JOY_DOWN:
					if (CanWalk(player, RIGHT))
					{
						player.AIM_FLAG = RIGHT_DOWN;
						SetState (player, STATE_JUMP, TRUE);
						player.JUMP_STATUS = 0;
						m_arrSounds["JUMP"]->Play();

						player.m_nFrameNo = 
						player.m_nFrameNo - 
							(player.m_nFrameNo %20)  
							//(player.m_nFrameNo&3)
							+ RIGHT*4 +2; 						

					return RIGHT;
					}

				break; // RIGHT + DOWN

				case JOY_RIGHT | JOY_UP:
					player.AIM_FLAG = RIGHT_UP;
					SetState (player, STATE_JUMP, TRUE);
					player.JUMP_STATUS = 0;
					m_arrSounds["JUMP"]->Play();

					player.m_nFrameNo = 
					player.m_nFrameNo - 
						(player.m_nFrameNo %20)  
						//(player.m_nFrameNo&3)
						+ RIGHT*4 +2; 						

					return RIGHT;
				break; // RIGHT + UP

				case JOY_RIGHT:
					if (CanWalk(player, RIGHT))
					{
						player.AIM_FLAG = RIGHT;
						SetState (player, STATE_JUMP, TRUE);
						player.JUMP_STATUS = 0;
						m_arrSounds["JUMP"]->Play();

						player.m_nFrameNo = 
						player.m_nFrameNo - 
							(player.m_nFrameNo %20)  
							//(player.m_nFrameNo&3)
							+ RIGHT*4 +2; 
						
						return RIGHT;
					}
				break; // RIGHT 

			}
		}

		// Resume normal moving thing

		int nNewAim = -1;

		if (nJoyState & JOY_DOWN ||
			nJoyState & JOY_UP)
		{
			nNewAim = UP;
		}

		if (nJoyState & JOY_LEFT)
		{
			nNewAim = LEFT;
		}

		if (nJoyState & JOY_RIGHT)
		{
			nNewAim = RIGHT;
		}

		if ((nNewAim != -1)
			&& player.AIM_FLAG != nNewAim)
		{
			//OutputDebugString("NewAim\n");
			player.AIM_FLAG = nNewAim;
			return nNewAim;
		}

		char *szSound ="";

		switch(nWalkSound)
		{
			case SND_WALK:
				szSound="WALK";
			break;

			case SND_WALK2:
				szSound="WALK2";
			break;

			case SND_METAL:
				szSound="METAL";
			break;

			default:
				nWalkSound = -1;
			break;
		}

		if (nJoyState & JOY_DOWN)
		{
			if (CanWalk(_player, DOWN, FALSE)) {
				UnMapSprite(m_nPlayerEntry);
				player.MoveBy(0,8);
				MapSprite(m_nPlayerEntry);

				AutoCenter(player, DOWN);

				if (nTicks%WALK_DELAY ==0 && nWalkSound!=-1) 
					m_arrSounds[szSound]->Play();
			}

			nAim = UP;
		}

		if ((nJoyState & JOY_LEFT) &&
			 (player.m_nX !=0))
		{		
			if (CanWalk(_player, LEFT, FALSE)) {
				UnMapSprite(m_nPlayerEntry);
				player.m_nX = player.m_nX - 8;
				_player.m_nX = _player.m_nX - 8;
				MapSprite(m_nPlayerEntry);
				
				AutoCenter(player, LEFT);

				if (nTicks%WALK_DELAY ==0 && nWalkSound!=-1) 
					m_arrSounds[szSound]->Play();
			}
			else
			{
				CScriptEntry t_player = _player;
				t_player.MoveBy (0,-8);
				if (player.m_nY !=0 &&
					CanWalk(_player, UP, FALSE) &&
					CanWalk(t_player, LEFT, FALSE))
				{
					UnMapSprite(m_nPlayerEntry);
					player.MoveBy(-8,-8);
					_player.MoveBy(-8,-8);
					MapSprite(m_nPlayerEntry);
	
					m_arrSounds["SHORTJUMP"]->Play();

					AutoCenter(player, LEFT);
					AutoCenter(player, UP);
				}
			}

			nAim = LEFT;
		}

		if (nJoyState & JOY_RIGHT)
		{
			if (CanWalk(_player, RIGHT, FALSE)) {
				UnMapSprite(m_nPlayerEntry);
				player.m_nX = player.m_nX + 8;
				_player.m_nX = player.m_nX + 8;
				MapSprite(m_nPlayerEntry);

				AutoCenter(player, RIGHT);

				if (nTicks%WALK_DELAY ==0 && nWalkSound!=-1) 
					m_arrSounds[szSound]->Play();
			}
			else
			{
				CScriptEntry t_player = _player;
				t_player.MoveBy (0,-8);
				AutoCenter(player, RIGHT);
				if (player.m_nY !=0 &&
					CanWalk(_player, UP, FALSE) &&
					CanWalk(t_player, RIGHT, FALSE))
				{
					UnMapSprite(m_nPlayerEntry);
					player.MoveBy(8, -8);
					_player.MoveBy(8, -8);
					MapSprite(m_nPlayerEntry);
					m_arrSounds["SHORTJUMP"]->Play();

					AutoCenter(player, RIGHT);
					AutoCenter(player, UP);
				}
			}

			nAim = RIGHT;
		}

		if (nJoyState & JOY_UP)
		{
			CScriptEntry t_player = _player;
			t_player.MoveBy (0,-8);

			if (CanWalk(_player, UP, FALSE) &&
				!CanFall(t_player)) 
			{
				AutoCenter(player, UP);
				UnMapSprite(m_nPlayerEntry);
				player.m_nY = player.m_nY - 8;
				MapSprite(m_nPlayerEntry);
				nAim = UP;
				if (nTicks%WALK_DELAY ==0 && nWalkSound!=-1) 
					m_arrSounds[szSound]->Play();
			}
		}

		if ((nJoyState & JOY_ZKEY) && (nTicks%6==0))
			PlayerZKey ();			
	}

	return nAim;
}

void CGame::ManagePlayerJump (CScriptEntry & player)
{
	char arrAimNames[9][16]={
		"JUMP_UP",
		"JUMP_DOWN",
		"JUMP_LEFT",
		"JUMP_RIGHT",
		"JUMP_UP_LEFT",
		"JUMP_UP_RIGHT",
		"JUMP_DOWN_LEFT",
		"JUMP_DOWN_RIGHT",
		NULL
	};

	if (player.AIM_FLAG > 7)
	{
		SetState(player, STATE_JUMP, FALSE);
		OutputDebugString("Internal error- jump sequence\n");
		return;
	}

	char *pAim = arrAimNames[player.AIM_FLAG];
	CExtraData & data = m_arrExtra[pAim];

	int i = player.JUMP_STATUS ;
	if (i >= data.GetSize())
	{
		SetState(player, STATE_JUMP, FALSE);
		return;
	}

	while (data[i]==-1)
	{
		i++;
		if (i >= data.GetSize())
		{
			SetState(player, STATE_JUMP, FALSE);
			return;
		}
	}

	int nAim = data[i];

	BOOL bCanWalk;

	/*
	if (nAim > UP ||
		(( nAim == UP) && (player.AIM_FLAG ==UP)))
	{
		bCanWalk = CanWalk (player, nAim);
	}
	else
	{
		bCanWalk = TRUE;
	}
	*/

	bCanWalk = CanWalk (player, nAim);

	switch (nAim)
	{
		case UP:
			if (player.m_nY>=0)
			{
				bCanWalk = bCanWalk;
			}
			else
			{
				bCanWalk = TRUE;
			}		
			// 24-DEC-00
			//bCanWalk;//(player.m_nY>0) && bCanWalk;
			// 07-DEC-00
		break;

		case DOWN:
			bCanWalk = (player.m_nY + 32< BUFFERHEI) 
				&& bCanWalk;
		break;

		case LEFT:
			bCanWalk = (player.m_nX > 0) 
				&& bCanWalk;
		break;

		case RIGHT:
			bCanWalk = (player.m_nX + 32 < BUFFERLEN) 
				&& bCanWalk;
		break;

		case PAUSE:
			bCanWalk = TRUE;
		break;

		default:
			bCanWalk=FALSE;
		break;
	}

	if (bCanWalk) {

		if (nAim!=-2)
		{
			UnMapSprite (m_nPlayerEntry);
			MoveSprite (player, nAim);
			MapSprite (m_nPlayerEntry);
		}

		i++;
		player.JUMP_STATUS = i;
		if (i >= data.GetSize())
		{
			SetState(player, STATE_JUMP, FALSE);
		}
	}
	else 
	{
		SetState(player, STATE_JUMP, FALSE);
	}
}

BOOL CGame::DrawScreen ()
{
	if (m_bDrawing) return FALSE;
	m_bDrawing = TRUE;

#ifdef _DEBUG

	if (!DrawScreenHelper(m_lpDDSPrimary))
		return FALSE;

#else

	if (!DrawScreenHelper(m_lpDDSBack))
		return FALSE;

	if ( m_lpDDSPrimary-> 
		GetFlipStatus (DDGFS_CANFLIP) == DD_OK)
	{
	    if (FAILED( m_lpDDSPrimary->Flip( NULL, DDFLIP_DONOTWAIT  ) ) )
		{
			OutputDebugString ("Couldn't perform flip.\n" );
			m_bDrawing = FALSE;
	        return FALSE;
		}

		m_bPrimary = !m_bPrimary;
    }
	else
	{
		return FALSE;
	}
	
#endif

	m_bDrawing = FALSE;
	return TRUE;
}

BOOL CGame::AddSprite (CScriptEntry & entry)
{
	int nSize = m_sFW.GetSize();
	int n; 
	BOOL bFound = FALSE;

	for (n=0; n<nSize && !bFound; n++)
		bFound = m_sFW[n].m_nProto ==0;

	if (bFound)
	{
		m_sFW[n-1] = entry;
	}
	else
	{
		m_sFW.Add (entry);
	}
	return TRUE;
}

BOOL CGame::InitLevel (int n)
{
	m_nCurrScript = n;
	return InitLevel (* m_arrScripts[n]);
}

BOOL CGame::ManagePlayerFiring (CScriptEntry & player, int nTicks, int nJoyState)
{
	// Manage Player Firing
	if (nJoyState & JOY_FIRE)
	{
		SetState(player, STATE_FIRING, TRUE);
	}
	else
	{
		SetState(player, STATE_FIRING, FALSE);
	}

	if (GetState(player, STATE_FIRING))
	{
		if (nTicks %5 ==0)
		{
			CScriptEntry bullet = player;
			CProto & proto = m_arrProto[TYPE_BULLET_LITTLE_STAR__PLY_];
			bullet.m_nProto = TYPE_BULLET_LITTLE_STAR__PLY_;
			bullet.m_nFrameSet = proto.m_nFrameSet;
			bullet.m_nFrameNo =0;
			bullet.AIM_FLAG = (UCHAR) 0xff;
			
			switch (nJoyState & (JOY_UP|JOY_DOWN|JOY_LEFT|JOY_RIGHT) )
			{
				case JOY_UP:
					if (bullet.m_nY!=0)
						bullet.MoveBy (8, - 8);
					bullet.AIM_FLAG = UP;
				break;

				case JOY_DOWN:
					if (bullet.m_nY+32 < BUFFERHEI)
						bullet.MoveBy(8, 32);
					bullet.AIM_FLAG = DOWN;
				break;

				case JOY_UP | JOY_LEFT:
				case JOY_DOWN | JOY_LEFT:
				case JOY_LEFT:
					if (bullet.m_nX !=0)
						bullet.MoveBy(-8, 8);
					bullet.AIM_FLAG = LEFT;
				break;


				case JOY_UP | JOY_RIGHT:
				case JOY_DOWN|JOY_RIGHT:
				case JOY_RIGHT:
					if (bullet.m_nX+32< BUFFERLEN)
						bullet.MoveBy(8,8);
					bullet.AIM_FLAG = RIGHT;
				break;
			}

			if (bullet.AIM_FLAG !=(UCHAR) 0xff)
				AddSprite (bullet);
		}
	}

	return TRUE;
}

void CGame::KillSprite (CScriptEntry & sprite)
{
	CProto & proto = m_arrProto [sprite.m_nProto];
	CProto & newproto =  m_arrProto[proto.m_nChProto];

	if ((m_nProtoPoints!=-1) && (proto.m_nPoints>0))
	{		
		CScriptEntry newSprite;
		newSprite.m_nFrameNo = proto.m_nPoints;
		newSprite.m_nFrameSet =
			m_arrProto[m_nProtoPoints].m_nFrameSet;
		newSprite.m_nProto =m_nProtoPoints;
		newSprite.MoveTo(sprite);

		AddToScore(g_arrPoints[proto.m_nPoints]);
		AddSprite(newSprite);
	}

	sprite.m_nProto = proto.m_nChProto;
	sprite.m_nFrameNo = newproto.m_nFrameNo;
	sprite.m_nFrameSet = newproto.m_nFrameSet;

	int nChSound = proto.m_nChSound;
	if (nChSound)
	{
		m_arrSounds[nChSound]->Play();
	}
}

BOOL CGame::InitSounds ()
{
	int x;
	m_arrSounds.Forget();
	for (x=0; x<m_arrSoundData.GetSize(); x++)
	{
		CSnd *pSnd = new CSnd();
		pSnd->Create(m_lpDS, m_arrSoundData[x].m_szDescription);
		pSnd->CreateClones(m_arrSoundData[x].m_nValue);
		pSnd->SetName(m_arrSoundData[x].GetName());
		m_arrSounds.Add (pSnd);
	}
	return TRUE;
}

BOOL CGame::PackGraphics()
{
	return m_arrOBL3.PackImages();
}

BOOL CGame::InitEpisode (CString strFilename)
{
	// Allocate Memory
	if (m_pScrollBK==NULL) 
	{
		m_pScrollBK = (UCHAR *) malloc (BUFFERLEN * BUFFERHEI);
	}
	
	if (m_pMap==NULL)
	{
		m_pMap = (UCHAR *) malloc (BUFFERLEN * BUFFERHEI / 8);
	}

	// Load game ressources in memory
	Forget();
	if (!Extract (strFilename))
	{
		OutputDebugString("Cannot extract episode\n");
		return FALSE;
	}

	// Find SIGNS.OBL #
	m_nProtoSigns = m_arrProto.GetProtoIndex("signs");
	if (m_nProtoSigns==-1)
	{
		OutputDebugString("No ''signs'' frameset in database\n");
		return FALSE;
	}
	
	CProto & proto = m_arrProto[m_nProtoSigns];
	COBL3Filter & filterS = * m_arrOBL3 [proto.m_nFrameSet];
	int n = filterS.GetSize();

	int i;
	for (i=0; i<n; i++)
	{
		CSS3Frame * pFrame =  new CSS3Frame (filterS [i]);
		pFrame->Shrink();
		filterS.Add (pFrame);
	}

	//PackGraphics();
	return TRUE;
}

void CGame::CastTrigger (CScriptEntry & triggerGen)
{
	int i;
	int nKey = triggerGen.m_nTriggerKey & TRIGGER_KEYS;
	if (nKey==0) return;

	for (i=0; i<m_sFW.GetSize(); i++)
	{
		CScriptEntry & entry = m_sFW[i];
		CProto & proto =  m_arrProto [entry.m_nProto];

		if (!proto.m_nTriggerType &&
			(entry.m_nTriggerKey & TRIGGER_KEYS) == nKey)
		{
			UnMapSprite (i);
			entry.m_nTriggerKey = 
				XOR (entry.m_nTriggerKey, TRIGGER_HIDDEN);
			MapSprite (i);
		}		
	}
}

int CGame::SignToFrameNo (char nSign, BOOL bSmall)
{
	const char szSigns[] = " abcdefghijklmnopqrstuvwxyz!0123456789$'";
	UINT i;
	for (i=0; i<strlen(szSigns); i++)
	{
		if (nSign == szSigns[i])
		{
			
			return i + strlen(szSigns)*bSmall;
		}
	}
	return 0;
}

void CGame::InitEntry (CScriptEntry & entry)
{
	CProto & proto = m_arrProto[entry.m_nProto];

	entry.AIM_FLAG = proto.m_nDefaultAim;
	entry.STATE_FLAG =0;
	entry.HIT_POINTS = proto.m_nHitPoints;
	entry.TIMEOUT_DELAY =0;
}

void CGame::ManageAuto (int nTicks)
{
	int i;
	CScriptArray & script = m_sFW;
	int nRateFactor;

	for (i=0; i<script.GetSize(); i++)
	{
		CScriptEntry & entry = script[i];
		CProto & proto = m_arrProto[entry.m_nProto];
		CSS3Frame *pFrame = 
			m_arrOBL3.GetFrame(entry);

		int nTicksT = nTicks + i * 20 + (i % 20);

		// AutoFire
		if (IsVisible(entry))
		{
			nRateFactor = proto.m_nAutoBulletTime *20 ;
			if ((proto.m_nAutoBullet!=0) &&
				(nRateFactor &&
					(nTicksT % nRateFactor)==0))
			{

				CProto bulletProto = m_arrProto[proto.m_nAutoBullet];
				CScriptEntry bullet(bulletProto);
				bullet.m_nProto = proto.m_nAutoBullet;
				bullet.AIM_FLAG = entry.AIM_FLAG;
				bullet.m_nX = entry.m_nX;
				bullet.m_nY = entry.m_nY;

				switch (bullet.AIM_FLAG)
				{
					case UP:
					case LEFT:
						if (CanWalk(bullet, bullet.AIM_FLAG))
						{	
							MoveSprite (bullet, bullet.AIM_FLAG);
							MoveSprite (bullet, bullet.AIM_FLAG);
						}
					break;

					case RIGHT:
						bullet.m_nX = bullet.m_nX +
							pFrame->m_nLen +8;
					break;

					case DOWN:
						bullet.m_nY = bullet.m_nY +
							pFrame->m_nHei +8;
					break;

				}					
					AddSprite(bullet);
			}		

			// ChangeTo
			nRateFactor = proto.m_nAutoProtoTime *20 ;
			if 	(nRateFactor &&
					(nTicksT % nRateFactor)==0)
			{
					CProto newProto = m_arrProto[proto.m_nAutoProto];

					UnMapSprite(i);
					entry.m_nFrameSet = newProto.m_nFrameSet;
					entry.m_nFrameNo = newProto.m_nFrameNo;
					entry.m_nProto = proto.m_nAutoProto;
					MapSprite(i);				
			}

			// AutoSound
			nRateFactor = proto.m_nAutoSoundTime *20 ;
			if 	(nRateFactor &&
					(nTicksT % nRateFactor)==0)
			{
				int nSound = proto.m_nAutoSound;
				if (nSound)
				{
					m_arrSounds[nSound]->Play();
				}		
			}	

		} // if IsVisible

		// AutoTrigger
		if (proto.m_bAutoTrigger)
		{
			nRateFactor = proto.m_nAutoTriggerTime *20 ;
			if 	(nRateFactor &&
				(nTicksT % nRateFactor)==0)
			{
				CastTrigger(entry);						
			}			
		}
	}
}

BOOL CGame::IsVisible (CScriptEntry & entry)
{
	CProto & proto = m_arrProto[entry.m_nProto];
	COBL3Filter & filter = *m_arrOBL3[entry.m_nFrameSet];
	CSS3Frame * pFrame = filter[entry.m_nFrameNo];

	int _x = entry.m_nX - m_nMX;
	int _y = entry.m_nY - m_nMY;
	int nLen = SCREENLEN;
	int nHei = SCREENHEI;

	if ((entry.m_nTriggerKey & TRIGGER_HIDDEN) ||
		 (_x + pFrame->m_nLen <= 0) ||
		 (_x >= nLen) || 
			(_y + pFrame->m_nHei <= 0) || 
			(_y >= nHei) )
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CGame::DrawScore (DDSURFACEDESC & ddsurfdesc)
{
	int nPitch = ddsurfdesc.lPitch;
	UCHAR *pDest = (UCHAR*) (0*nPitch + (DWORD) ddsurfdesc.lpSurface);

	int nZeroFrame = SignToFrameNo('0', TRUE); 
	int nTemp = m_nScore;
	int i;

	int nFrameSet = m_arrProto[m_nProtoSigns].m_nFrameSet;
	COBL3Filter & filter = *m_arrOBL3[nFrameSet];

	int y;

	switch(m_nShowStatus)
	{
		case 1:
			y = - 32 + m_nStatusCount;
		break;

		case 2:
			y = 0;
		break;

		case 3:
			y = 0 - m_nStatusCount;
		break;

		default:
		return FALSE;
	}

	for (i=7; i>=0; i--)
	{
		int nSign = (nTemp % 10) + nZeroFrame;

		CSS3Frame *pFrame = filter[nSign];

		OutputOBL3(pFrame,
			i * pFrame->m_nLen, y, 
			SCREENLEN, SCREENHEI, 
			FALSE,
			pDest,
			nPitch,
			0x5);

		nTemp = nTemp / 10;
	}
  
	return TRUE;

}

void CGame::AddToScore(int nPoints)
{
	m_nScore = m_nScore + nPoints;

	ShowScore(TRUE);
}

void CGame::PlotText(DDSURFACEDESC & ddsurfdesc, char *szText, int x, int y, BYTE nColor, BOOL bSmall)
{
	int nPitch = ddsurfdesc.lPitch;
	UCHAR *pDest = (UCHAR*) (0*nPitch + (DWORD) ddsurfdesc.lpSurface);

	int nFrameSet = m_arrProto[m_nProtoSigns].m_nFrameSet;
	COBL3Filter & filter = *m_arrOBL3[nFrameSet];

	if (x == -1)	{
		int nSign = SignToFrameNo(*szText, bSmall); 
		CSS3Frame *pFrame = filter[nSign];
		
		x = (SCREENLEN - 
			(pFrame->m_nLen*strlen(szText)))/2;
	}

	if (y == -1)	{
		int nSign = SignToFrameNo(*szText, bSmall); 
		CSS3Frame *pFrame = filter[nSign];
		
		y = (SCREENHEI - pFrame->m_nHei)/2;
	}

	int i;
	for (i=0; i<(int)strlen(szText); i++)	{
		int nSign = SignToFrameNo(szText[i], bSmall); 
		CSS3Frame *pFrame = filter[nSign];

		OutputOBL3(pFrame,
			x, y, 
			SCREENLEN, SCREENHEI, 
			FALSE,
			pDest,
			nPitch,
			nColor);

		x = x + pFrame->m_nLen;
	}
}

void CGame::ShowScore (BOOL bShow)
{
	if (bShow)
	{
		switch(m_nShowStatus)
		{
			case 0:
				m_nShowStatus = 1;
				m_nStatusCount = 0;
			break;

			case 2:
				m_nStatusCount = 0;
			break;

			case 3:
				m_nShowStatus = 1;
				m_nStatusCount = 32 - m_nStatusCount;
			break;
		}
	}
	else
	{
		switch(m_nShowStatus)
		{
			case 1:
				m_nStatusCount = 3;
				m_nStatusCount = 32 - m_nStatusCount;
			break;

			case 2:
				m_nShowStatus = 3;
			break;
		}
	}
}

void CGame::PlayLevelIntro(DDSURFACEDESC & ddsurfdesc)
{
	int nPitch = ddsurfdesc.lPitch;
	UCHAR *pDest = (UCHAR*) (0*nPitch + (DWORD) ddsurfdesc.lpSurface);
	FillSurface (0x10, pDest, SCREENLEN, SCREENHEI, nPitch);

	int nTotalHei = 32+16+16;
	int y = (SCREENHEI - nTotalHei)/2;

	int n = m_nCurrScript * 5;

	char szTemp[128];
	wsprintf(szTemp, "level %.2d", m_nCurrScript+1);
	PlotText(ddsurfdesc, szTemp, -1, y, (BYTE)32+n, FALSE);

	CScriptArray & script = * m_arrScripts[m_nCurrScript];
	strcpy(szTemp, script.m_strName.GetBuffer(1));
	int i=0;
	while (szTemp[i])
	{
		if ((szTemp[i]>='A') && (szTemp[i]<='Z'))
			szTemp[i] = szTemp[i] - 'A' + 'a';
				i++;
	}
	PlotText(ddsurfdesc, szTemp , -1, y+32+16, (BYTE)25+n, TRUE);
}

void CGame::ApplyGamma()
{
	CClientDC dc(AfxGetMainWnd());

	g_pal.IncGamma();

	if (g_pal.CreatePalette(&dc, 
			  m_lpDD,
			  &m_lpDDPal  )==FALSE)
	{
		Fail( "Fatal: Couldn't create the palette\n");
		return ;
	}

	/*
	if (CreatePalette(&dc, 
			  m_lpDD,
			  &m_lpDDPal  )==FALSE)
	{
		Fail( "Fatal: Couldn't create the palette\n");
		return;
	}
	*/

    if ( FAILED( m_lpDDSPrimary->SetPalette( m_lpDDPal ) ) )
	{
		Fail( "Fatal: Couldnt' get and/or set the palette.\n" );
		return;
	}
}

BOOL CGame::Save(char *szName)
{
	int nTemp;

	int *arrVars[]=
	{
		&m_nMX,
		&m_nMY,
		&nTemp,
		&m_nLifeForce,
		&m_nLives,
		&m_nPlayerEntry,
		&m_nProtoPlayer,
		&m_nProtoPoints,
		&m_nProtoPlayer,
		&m_nScore,
		&m_nShowStatus,
		&m_nStatusCount,
		&m_nProtoPlayer,

		&m_nCurrScript,
		&m_bGameOver ,
		NULL
	};
	
	CFile file;
	BOOL bStatus = FALSE;

	if (file.Open(szName, CFile::modeCreate  |
		CFile::modeWrite |
		CFile::typeBinary))

	{
		file.Write(LGCK_VERSION, 8);
		CString strSig = CString(GAME_SIGNATURE);
		file << strSig;
		
		int i;
		for (i=0; arrVars[i]; i++)
		{
			file.Write (arrVars[i], 4);
		}

		int nSizeL = BUFFERLEN;
		int nSizeH = BUFFERHEI;
		file.Write (&nSizeL, 4);
		file.Write (&nSizeH, 4);

		m_sBK.Write(file);
		m_sFW.Write(file);

		file.Close();	

		bStatus = TRUE;
	}

	return bStatus;
}

BOOL CGame::Load(char *szName)
{
	int nTemp;

	int *arrVars[]=
	{
		&m_nMX,
		&m_nMY,
		&nTemp,
		&m_nLifeForce,
		&m_nLives,
		&m_nPlayerEntry,
		&m_nProtoPlayer,
		&m_nProtoPoints,
		&m_nProtoPlayer,
		&m_nScore,
		&m_nShowStatus,
		&m_nStatusCount,
		&m_nProtoPlayer,

		&m_nCurrScript,
		&m_bGameOver ,
		NULL
	};
	
	CFile file;
	BOOL bStatus = FALSE;

	char szSig[]="12345678";
	char szTemp[128];

	if (file.Open(szName, CFile::modeRead  |
		CFile::typeBinary))
	{
		file.Read(szSig, 8);

		if (strcmp(szSig, LGCK_VERSION)!=0)
		{
			wsprintf(szTemp, "WARNING: Wrong version of LGCK (%c%s%c)\n",
				34,szSig,34);
			OutputDebugString(szTemp);
			
			file.Close();
			return FALSE;
		}

		CString strGame;
		file >> strGame ;

		if (strGame != GAME_SIGNATURE)
		{
			OutputDebugString("WARNING: Wrong Game signature\n");
		
			file.Close();
			return FALSE;
		}

		m_bCritical = TRUE;

		int i;
		for (i=0; arrVars[i]; i++)
		{
			file.Read (arrVars[i], 4);
		}

		int nSizeL;
		int nSizeH;
		file.Read(&nSizeL, 4);
		file.Read(&nSizeH, 4);

		m_sBK.Forget();
		m_sFW.Forget();

		m_sBK.Read(file);
		m_sFW.Read(file);

		file.Close();	

		// UnHide system-class objects
		HideSystemClass (m_sBK, FALSE);
		HideSystemClass (m_sFW, FALSE);

		PrepareLevel(*m_arrScripts[m_nCurrScript]);

		bStatus = TRUE;

		m_bPause = FALSE;
		m_bActive = TRUE;

		m_nShowStatus = 1;
		m_nStatusCount = 0;

		m_bCritical = FALSE;
	}
	else
	{
		OutputDebugString("Can't open savegame\n");
	}

	return bStatus;
}

BOOL CGame::PrepareLevel (CScriptArray &s)
{
	// Map the game area 
	// both background and forewardground objects
	ZeroMemory (m_pMap, BUFFERLEN * BUFFERHEI / 8);

	if (!MapScript (m_sBK, m_pMap, BUFFERLEN, BUFFERHEI, TRUE)) 
	{
		OutputDebugString ("MapScript malloc failed!\n");
		return FALSE;
	}

	if (!MapScript (m_sFW, m_pMap, BUFFERLEN, BUFFERHEI, FALSE)) 
	{
		OutputDebugString ("MapScript malloc failed!\n");
		return FALSE;
	}

	// Find the player object
	m_nProtoPlayer = m_arrProto.GetProtoIndex("players");
	if (m_nProtoPlayer!=-1) {
		m_nPlayerEntry = m_sFW.FindProto(m_nProtoPlayer);
	}
	else {
		m_nPlayerEntry = -1;
		OutputDebugString("Bad: Missing player object!\n");
		return FALSE;
	}

	// Find SIGNS.OBL #
	m_nProtoSigns = m_arrProto.GetProtoIndex("signs");

	// Find POINTS.OBL #
	m_nProtoPoints = m_arrProto.GetProtoIndex("points");

	// Hide system-class objects
	HideSystemClass (m_sBK, TRUE);
	HideSystemClass (m_sFW, TRUE);
	
	// Draw the entire game area
	if (m_pScrollBK!=NULL)
	{
	    FillSurface (s.m_nBkColor, m_pScrollBK, 
			BUFFERLEN, BUFFERHEI, BUFFERLEN);
		DrawScript (&m_sBK, 0,0, m_pScrollBK, 
			BUFFERLEN, BUFFERHEI, BUFFERLEN);
	}
	else
	{
		OutputDebugString ("error: m_pScrollBK malloc failed!\n");
		return FALSE;
	}

	// Init PlayerObject
	if (m_nPlayerEntry!=-1) {

		CScriptEntry & player = 
			m_sFW [m_nPlayerEntry];

		CenterOnPlayer (player);
		SetState(player, STATE_HIT | STATE_BEGINNING, TRUE);
		player.HIT_POINTS = 5;
		player.TIMEOUT_DELAY = 0;
	}

	m_nShowStatus = 0;
	m_nStatusCount = 0;

	return TRUE;
}

BOOL CGame::BltScreen()
{
	if (!DrawScreenHelper(m_lpDDSBack))
	{
		return FALSE;
	}

	m_lpDDSPrimary->BltFast(
        0, 0,			// Upper left xy of destination
        m_lpDDSBack,	// Source surface
        NULL,			// Source rectangle = entire surface
        DDBLTFAST_WAIT);

	return TRUE;
}

BOOL CGame::DrawScreenHelper(LPDIRECTDRAWSURFACE lpDDS)
{
	// Check if display surface is lost
    if ( FAILED( lpDDS->IsLost() ) )
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
	if (lpDDS->Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)	{
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
		PlotText(ddsurfdesc, "press [f4]", -1, -1, (BYTE) -10, FALSE);
	}

	// unlock surface
	if (lpDDS->Unlock(NULL))	{
		OutputDebugString("DDraw: Unlock failed!\n");
		m_bDrawing= FALSE;
		return FALSE;
	} 

	return TRUE;
}

BOOL CGame::IsPlayerAlign(CScriptEntry & entry, CScriptEntry & player, int nAim)
{
	CSS3Frame & frmEntry = *(m_arrOBL3.GetFrame (entry));
	CSS3Frame & frmPlayer = *(m_arrOBL3.GetFrame (player));

	switch (nAim)
	{
		case UP | DOWN:
			return 
				( (player.m_nY<= entry.m_nY) && ( (player.m_nY + frmPlayer.m_nHei) <= (entry.m_nY + frmEntry.m_nHei) ) ) ||
				( (player.m_nY>= entry.m_nY) && ( (player.m_nY + frmPlayer.m_nHei) >= (entry.m_nY + frmEntry.m_nHei) ) ) ||
				(player.m_nY == entry.m_nY);
		break;

		case LEFT | RIGHT :
			return 
				( (player.m_nX<= entry.m_nX) && ( (player.m_nX + frmPlayer.m_nLen) <= (entry.m_nX + frmEntry.m_nLen) ) ) ||
				( (player.m_nX>= entry.m_nX) && ( (player.m_nX + frmPlayer.m_nLen) >= (entry.m_nX + frmEntry.m_nLen) ) ) ||
				(player.m_nX == entry.m_nX);
		break;

		default:
			return FALSE;
		break;
	}
}

void CGame::HurtPlayer(CScriptEntry & player, CScriptEntry & actor)
{
	CProto & proto = m_arrProto.GetProto(actor);

	if (!GetState(player, STATE_HIT))
	{
		SetState(player, STATE_HIT, TRUE);
		player.TIMEOUT_DELAY = CONST_TIMEOUT;
	}
}

BOOL CGame::FillSurface(UCHAR nColor)
{
	// Erase the background
	DDBLTFX     ddbltfx;
	ddbltfx.dwSize = sizeof( ddbltfx );
	ddbltfx.dwFillColor = nColor; 

	ddbltfx.dwFillColor = nColor; 
	if ( !m_lpDDSPrimary || FAILED( m_lpDDSPrimary->Blt( NULL, 
			NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx ) ) )	
	{	
		OutputDebugString("DDraw: ColorFill failed\n");
		return FALSE;
	}
	return TRUE;
}

void CGame::Debug(char *sz)
{
#ifdef _DEBUG
	g_fileDebug.Write(sz, strlen(sz));
#endif
}

BOOL CGame::TestAimEx (CScriptEntry & entry, int nAim, int nTimes)
{
	CScriptEntry temp = entry;

	for (int i=0; i<nTimes; i++)
	{
		if (!TestAim(temp, nAim))
			return FALSE;

		MoveSprite(temp, nAim);
		nAim = nAim & 3;
	}

	return TRUE;
}

int CGame::MakeEpisodeList(CStringArray & arr)
{
	//_splitpath(szFileFilter, 
	//	szDrive, 
	//	szDir, 
	//	szFilename, 
	//	szExt);

	struct _finddata_t data;
	int handle;

	handle = _findfirst( "*.scr", &data);
	if (handle!=-1)
	{
        if (CGameFile3::IsValid(CString(data.name)))
        {
            arr.Add(data.name);
        }

		while (_findnext (handle, &data)!=-1)
		{
            if (CGameFile3::IsValid(CString(data.name)))
            {
                arr.Add(data.name);
            }
		} // while
    }

    return arr.GetSize();   
}

void CGame::InitGamma()
{
	CClientDC dc(AfxGetMainWnd());

	//g_pal.IncGamma();

	if (g_pal.CreatePalette(&dc, 
			  m_lpDD,
			  &m_lpDDPal  )==FALSE)
	{
		Fail( "Fatal: Couldn't create the palette\n");
		return ;
	}

    if ( FAILED( m_lpDDSPrimary->SetPalette( m_lpDDPal ) ) )
	{
		Fail( "Fatal: Couldnt' get and/or set the palette.\n" );
		return;
	}
}

int CGame::GetGamma()
{
    return g_pal.GetGamma();
}

void CGame::SetGamma(int i)
{
}

BOOL CGame::GetEpisodeFilename(CString & str)
{
    while (TRUE)
    {
	    CString strFilesFilter =
            "LGCK scripts (*.scr)|*.scr|"\
            "|";

        CFileDialog dlg( TRUE, ".scr", "", 
                OFN_HIDEREADONLY , 
                strFilesFilter,  AfxGetMainWnd() ) ;

        dlg.m_ofn.lpstrTitle = "Select Episode";
    
        if (dlg.DoModal()==IDOK)
        {    
            if (CGameFile3::IsValid(CString(dlg.GetPathName())))
            {
                str = dlg.GetPathName();
                return TRUE;
            }
            else
            {
                AfxMessageBox("This is not a valid episode file");
            }
        }	        
        else
        {
            str = "";
            return FALSE; 
        }
    }
}
