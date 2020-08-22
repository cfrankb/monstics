// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "scr4edit.h"

#include "MainFrm.h"
#include "paldata.h"
#include "dlgexportpal.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "draw.h"
#include "Splash.h"

CPalData g_pal;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_ACTIVATEAPP()
	ON_COMMAND(IDM_GAMMACORRECTION, OnGammacorrection)
	ON_UPDATE_COMMAND_UI(IDM_GAMMACORRECTION, OnUpdateGammacorrection)
	ON_COMMAND(IDM_EXPORTPAL, OnExportpal)
	ON_UPDATE_COMMAND_UI(IDM_EXPORTPAL, OnUpdateExportpal)
	ON_COMMAND(IDM_SAVESETTINGS, OnSavesettings)
	ON_UPDATE_COMMAND_UI(IDM_SAVESETTINGS, OnUpdateSavesettings)
	ON_COMMAND(IDM_AUTO_UPDATEDATA, OnAutoUpdatedata)
	ON_UPDATE_COMMAND_UI(IDM_AUTO_UPDATEDATA, OnUpdateAutoUpdatedata)
	ON_COMMAND(IDM_IMPORTPAL, OnImportpal)
	ON_UPDATE_COMMAND_UI(IDM_IMPORTPAL, OnUpdateImportpal)
	ON_COMMAND(IDM_RESETPAL, OnResetpal)
	ON_UPDATE_COMMAND_UI(IDM_RESETPAL, OnUpdateResetpal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

	// Initialize DirectDraw Objects
	m_lpDD=NULL;        
	m_lpDDSPrimary=NULL;
	m_lpDDPal = NULL;
	m_lpDDSBack = NULL;	
	m_lpDDClipper = NULL;

	CWinApp * pApp = AfxGetApp(); 

	// Load general settings
	m_bSaveSettings = pApp->GetProfileInt("settings", "SaveSettings", TRUE);
	int nGamma = pApp->GetProfileInt("settings", "GammaLevelHiRes", 5);
	m_bAutoUpdateData = pApp->GetProfileInt("settings", "AutoUpdateData", FALSE);

	// Reset to the default palette & apply gamma settings
	g_pal.ResetPal();
	g_pal.SetGamma(nGamma);

	OutputDebugString("CMainFrame() Init completed\n");
}

CMainFrame::~CMainFrame()
{
	CWinApp * pApp = AfxGetApp(); 

	pApp->WriteProfileInt("settings", "SaveSettings", m_bSaveSettings);

	if (m_bSaveSettings)
	{
		pApp->WriteProfileInt("settings", "GammaLevelHiRes", g_pal.GetGamma());
		pApp->WriteProfileInt("settings", "AutoUpdateData", m_bAutoUpdateData);
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    OutputDebugString("CMainFrame::OnCreate\n");

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    {
        TRACE0("Failed in CFrameWnd::OnCreate()\n");
		return -1;
    }
    

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    
    // TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);


    EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

    LoadBarState ("BarSettings");

    

	InitDDraw();

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


BOOL CMainFrame::InitDDraw()
{

#ifdef _DEBUG
	OutputDebugString("InitDDraw\n");
#endif

   // Create the DirectDraw object -- we just need an IDirectDraw
    // interface so we won't bother to query an IDirectDraw2
    if ( FAILED( DirectDrawCreate( NULL, &m_lpDD, NULL ) ) )
	{
		 return Fail( "Fatal: Couldn't create DirectDraw object.\n" );
	}


    if FAILED( m_lpDD->SetCooperativeLevel( this->m_hWnd,
                        DDSCL_NORMAL ) )
	{
		return Fail( "Fatal: Couldn't set cooperative level.\n" );
	}

	// Create the primary surface
    DDSURFACEDESC   ddsd;
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    
	if ( FAILED( m_lpDD->CreateSurface( &ddsd, &m_lpDDSPrimary, NULL ) ) )
	{
		return Fail( "Fatal: Couldn't create primary surface.\n" );
	}

	// Check pixel format 
    DDPIXELFORMAT       ddpf;       // Surface format structure.

    // Check the surface format.
    ddpf.dwSize = sizeof( ddpf );
    if ( FAILED( m_lpDDSPrimary->GetPixelFormat( &ddpf ) ) )
	{
        return Fail( "Fatal: Couldn't get pixel format.\n" );
    }

	// Requires either 256, 64K, or 16M colors display mode to run - if video card
	// won't provide then screw it.

	switch (ddpf.dwRGBBitCount)
	{
		case 8:
		case 16:
		case 24:
		case 32:
		break;

		default:
			Fail ("Fatal: Cannot operated at this video mode.\nTry either 256, 32k, 64k or 16M colors!\n");
		break;

	}

	// Create a clipper and attach it to the primary surface.
    if ( FAILED( m_lpDD->CreateClipper( 0, &m_lpDDClipper, NULL ) ) )
	{
        return Fail( "Couldn't create the clipper.\n" );
    }

    // Associate our clipper with our hwnd so it will be updated
    // by Windows.
    if ( FAILED( m_lpDDClipper->SetHWnd( 0, this->m_hWnd ) ) )
	{
        return Fail(  "Couldn't set the hwnd.\n" );
    }

    // Associate our clipper with the primary surface, so Blt 
    // will use it. If this step is skipped by defining NOCLIPPER, you
    // can observe the effects of rendering without clipping. Other
    // windows partially obscuring Inawin's will be overwritten.

    if ( FAILED( m_lpDDSPrimary->SetClipper( m_lpDDClipper ) ) )
	{
        return Fail(  "Couldn't set the clipper.\n" );
    }

	// Retrieve information concerning primary surface,
	// into the DDSURFACEDESC structure.
    ZeroMemory(&ddsd, sizeof(ddsd));

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_ALL;
	if (FAILED (m_lpDDSPrimary->GetSurfaceDesc(&ddsd) ))
	{
		return Fail(  "Fatal: Couldn't grab the surface description.\n" );
    }
	
	// Use the information to clone another surface identical
	// to the previous.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

    if (m_lpDD->CreateSurface(&ddsd, &m_lpDDSBack, NULL) != DD_OK)
	{
        return Fail(  "Fatal: Couldn't create surface 2.\n" );
    }

    if ( ddpf.dwFlags & DDPF_PALETTEINDEXED8 ) 
    {
        // We are palettized, so create a palette and attach it to
        // the primary surface.

		CClientDC dc(this);

		if (g_pal.CreatePalette(&dc, 
						  m_lpDD,
						  &m_lpDDPal  )==FALSE)
		{
			return Fail( "Fatal: Couldn't create the palette\n");
		}

        if ( FAILED( m_lpDDSPrimary->SetPalette( m_lpDDPal ) ) )
		{
            return Fail( "Fatal: Couldnt' get and/or set the palette.\n" );
        }
    }	
	else
	{
		// Create additional Colors Tables
		// for 16bpp, 24bpp and 32 bpp if applicable

		int nBpp = ddpf.dwRGBBitCount;
		g_pal.CreateRefsPal(nBpp, m_lpDDSBack);
	}

#ifdef _DEBUG
	OutputDebugString("Info - DirectDraw objects constructed succesfully!\n");
#endif

	return TRUE;
}

void CMainFrame::ReleaseObjects ()
{
    if ( m_lpDD != NULL )
    {
        if ( m_lpDDSPrimary != NULL )
        {
            m_lpDDSPrimary->Release();
            m_lpDDSPrimary = NULL;
        }

		if ( m_lpDDSBack != NULL )
        {
            m_lpDDSBack->Release();
            m_lpDDSBack = NULL;
        }

        m_lpDD->Release();
        m_lpDD = NULL;
    }
}

BOOL CMainFrame::Fail (char *szText)
{
	OutputDebugString( szText );
    return FALSE;
}

void CMainFrame::OnDestroy() 
{
    ReleaseObjects();

	m_wndToolBar.DestroyWindow();
    m_wndStatusBar.DestroyWindow();
    SaveBarState ("BarSettings");
	CFrameWnd::OnDestroy();
	// TODO: Add your message handler code here	
}

BOOL CMainFrame::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default
    // We didn't cause it, so we have lost the palette.
#ifdef _DEBUG
    OutputDebugString( "Palette lost.\n" );
#endif

    // Realize our palette.
    if (m_lpDDPal)
	{
		m_lpDDSPrimary->SetPalette( m_lpDDPal ); 
	}
		
	return CFrameWnd::OnQueryNewPalette();
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
    // We didn't cause it, so we have lost the palette.
#ifdef _DEBUG
    OutputDebugString( "Palette lost.\n" );
#endif

    // Realize our palette.
    if (m_lpDDPal)
	{
		OutputDebugString("1\n");
	    m_lpDDSPrimary->SetPalette( m_lpDDPal ); 
		OutputDebugString("2\n");
	}

	CFrameWnd::OnPaletteChanged(pFocusWnd);
	
	// TODO: Add your message handler code here
}

BOOL CMainFrame::RestoreAll ()
{
    HRESULT ddrval;


	if (m_lpDDSPrimary==NULL)
	{
		OutputDebugString("Primary surface gone??!\n");
		//ReleaseObjects();
		InitDDraw();
		return FALSE;
	}

    // Try restoring the primary first
    ddrval = m_lpDDSPrimary->Restore();
    if ( ddrval == DDERR_WRONGMODE ) 
	{
        // The restore failed because the display mode was
        // changed. Destroy everything then re-create it.
        OutputDebugString( "Display mode changed!\n" );
        ReleaseObjects();
        InitDDraw( );
		return TRUE;
    }
    else if ( FAILED( ddrval ) )
    {
        // We failed for some other reason.
        OutputDebugString( "Random restore failure.\n" );
        return FALSE;
    }
    else
    {
        // We're OK. Restore everything else.
        if ( FAILED( m_lpDDSBack->Restore() ) ) return FALSE;
    }
    return TRUE;
}

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CFrameWnd::OnActivateApp(bActive, hTask);
	
	// TODO: Add your message handler code here
#ifdef _DEBUG
    OutputDebugString( "Palette lost.\n" );
#endif

    // Realize our palette.
    if (bActive && m_lpDDSPrimary && (m_lpDDPal!=NULL))
		m_lpDDSPrimary->SetPalette( m_lpDDPal ); 
}

void CMainFrame::OnGammacorrection() 
{
	// TODO: Add your command handler code here
	g_pal.IncGamma();
	NewPalette();
}

void CMainFrame::OnUpdateGammacorrection(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnExportpal() 
{
	CDlgExportPal dlg;
	dlg.m_nFormat = PAL_MSDOS;
	if (dlg.DoModal()==IDOK)
	{
		CFile file;
		if (file.Open(dlg.m_strName, CFile::modeCreate 
			| CFile::modeWrite | CFile::typeBinary, NULL ))
		{
			g_pal.Export(file, dlg.m_nFormat);
			file.Close();
		}		
		else
		{
			AfxMessageBox("Cannot create palette");
		}
	}
}

void CMainFrame::OnUpdateExportpal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnSavesettings() 
{
	// TODO: Add your command handler code here
	m_bSaveSettings = ! m_bSaveSettings;
}

void CMainFrame::OnUpdateSavesettings(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bSaveSettings);
}

void CMainFrame::OnAutoUpdatedata() 
{
	// TODO: Add your command handler code here
	m_bAutoUpdateData = ! m_bAutoUpdateData;
}

void CMainFrame::OnUpdateAutoUpdatedata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bAutoUpdateData);	
}

void CMainFrame::OnImportpal() 
{
	// TODO: Add your command handler code here
	    CString l_strFilesFilter =
		    "Color palette |*.pal"\
			"|";

	CFileDialog dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY //| OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Import color palette"; 
	dlg.m_ofn.lpstrDefExt = ".pal";
    
    if (dlg.DoModal()==IDOK)  {

		CString strFilename = dlg.GetPathName();
		CFile file;

		if (file.Open(strFilename, CFile::modeRead | CFile::typeBinary, NULL ))
		{
			if (g_pal.Import(file))
			{
				NewPalette();
				g_pal.SetName(strFilename.GetBuffer(1));
			}
			else
			{
				AfxMessageBox("Unsupported format");
			}

			file.Close();
		}		

		else
		{
			AfxMessageBox("Cannot open palette file");
		}
	}
}

void CMainFrame::OnUpdateImportpal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnResetpal() 
{
	// TODO: Add your command handler code here
	if (AfxMessageBox("Reset the default colors?",
				MB_YESNO)==IDYES)
	{
		g_pal.ResetPal();
		NewPalette();
		Invalidate();
	}
}

void CMainFrame::OnUpdateResetpal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

BOOL CMainFrame::NewPalette()
{
	 if (!m_lpDDSPrimary || !m_lpDDSBack)
	 {
		 return FALSE;
	 }

	// Retrieve information concerning primary surface,
	// into the DDSURFACEDESC structure.
    DDPIXELFORMAT       ddpf;       // Surface format structure.

    ddpf.dwSize = sizeof( ddpf );
    if ( FAILED( m_lpDDSPrimary->GetPixelFormat( &ddpf ) ) )
	{
        Fail( "Fatal: Couldn't get pixel format.\n" );
    }
   
    if ( ddpf.dwFlags & DDPF_PALETTEINDEXED8 ) 
    {
        // We are palettized, so create a palette and attach it to
        // the primary surface.

		CClientDC dc(this);

		if (g_pal.CreatePalette(&dc, 
						  m_lpDD,
						  &m_lpDDPal  )==FALSE)
		{
			Fail( "Fatal: Couldn't create the palette\n");
		}

        if ( FAILED( m_lpDDSPrimary->SetPalette( m_lpDDPal ) ) )
		{
            Fail( "Fatal: Couldnt' get and/or set the palette.\n" );
        }
    }	
	else
	{
		// Create additional Colors Tables
		// for 16bpp, 24bpp and 32 bpp if applicable

		int nBpp = ddpf.dwRGBBitCount;
		g_pal.CreateRefsPal(nBpp, m_lpDDSBack);
	}
	
	Invalidate();
	return TRUE;
}

void CMainFrame::InitPal()
{
	g_pal.ResetPal();
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	char *pText;

	switch (message)
	{
		case WM_USER_SET_STATUS:		
			pText = (char*) (wParam);
			SetStatus(pText);
		break;
	}   

	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::SetStatus(char *szText)
{
    m_wndStatusBar.SetPaneText ( 0, szText );
}
