// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "obl4edit.h"

#include "MainFrm.h"
#include "draw.h"
#include "Splash.h"
#include "PalData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPalData g_pal;

extern WORD			g_pal16[];
extern USER_24bpp	g_pal24[];
extern UINT			g_pal32[];

extern g_nBpp;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_SIZE()
	ON_COMMAND(IDM_HASPALETTE, OnHaspalette)
	ON_UPDATE_COMMAND_UI(IDM_HASPALETTE, OnUpdateHaspalette)
	ON_WM_SYSCOLORCHANGE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOVE()
	ON_COMMAND(IDM_PLUS, OnPlus)
	ON_UPDATE_COMMAND_UI(IDM_PLUS, OnUpdatePlus)
	ON_COMMAND(IDM_MINUS, OnMinus)
	ON_UPDATE_COMMAND_UI(IDM_MINUS, OnUpdateMinus)
	ON_COMMAND(IDM_SAVESETTINGS, OnSavesettings)
	ON_UPDATE_COMMAND_UI(IDM_SAVESETTINGS, OnUpdateSavesettings)
	ON_WM_ACTIVATEAPP()
	ON_COMMAND(IDM_SHOWTRANSPARENCY, OnShowtransparency)
	ON_UPDATE_COMMAND_UI(IDM_SHOWTRANSPARENCY, OnUpdateShowtransparency)
	ON_COMMAND(IDM_ADJUSTGAMMA, OnAdjustgamma)
	ON_UPDATE_COMMAND_UI(IDM_ADJUSTGAMMA, OnUpdateAdjustgamma)
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
	CWinApp * pApp = AfxGetApp(); 
	
	m_lpDD = NULL;
	m_lpDDClipper =NULL;
	m_lpDDSBack = NULL;
	m_lpDDSBack2 = NULL;
	m_lpDDSPrimary = NULL;
	m_lpDDPalette = NULL;	

	m_bSaveSettings = pApp->GetProfileInt("Settings", "m_bSaveSettings", TRUE);

	m_nPenColor = pApp->GetProfileInt("Settings", "m_nPenColor", 0x11);
	m_nTool = pApp->GetProfileInt("Settings", "m_nTool", IDM_PEN);
	m_nPenSize= pApp->GetProfileInt("Settings", "m_nPenSize", IDM_W1);
	m_bShowFrame = pApp->GetProfileInt("Settings", "m_bShowFrame", TRUE);
	m_bShowTransparency = pApp->GetProfileInt("Settings", "m_bShowTransparency", TRUE);
	m_bIsometric = pApp->GetProfileInt("Settings", "m_bIsometric", FALSE);

	int nGamma = pApp->GetProfileInt("Settings", "m_nGamma", 4);

	g_pal.ResetPal();
	g_pal.SetGamma(nGamma);
}

CMainFrame::~CMainFrame()
{
	ReleaseObjects(); // Destroy DDraw Objects

	CWinApp * pApp = AfxGetApp( ); 
	pApp->WriteProfileInt("Settings", "m_bSaveSettings", m_bSaveSettings);

	if (m_bSaveSettings) {
		pApp->WriteProfileInt("Settings", "m_nPenColor", m_nPenColor);
		pApp->WriteProfileInt("Settings", "m_nTool", m_nTool);
		pApp->WriteProfileInt("Settings", "m_nPenSize", m_nPenSize);
		pApp->WriteProfileInt("Settings", "m_bShowFrame", m_bShowFrame);
		pApp->WriteProfileInt("Settings", "m_bShowTransparency", m_bShowTransparency);
		pApp->WriteProfileInt("Settings", "m_bIsometric", m_bIsometric);
		pApp->WriteProfileInt("Settings", "m_nGamma", g_pal.GetGamma());
	}
}	

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetWindowText ("Standard");

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM );
	EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndToolBar);

	InitDDraw( this->m_hWnd );

	CString strWndClass = AfxRegisterWndClass (
        CS_DBLCLKS | CS_OWNDC,                  // Class style
        AfxGetApp()->LoadStandardCursor (IDC_ARROW),   // Class cursor
        NULL,//(HBRUSH) (COLOR_3DFACE ),               // Class background brush
        NULL            // Class icon
        );

    if ( m_wndColorBox. 
            CreateEx (
			WS_EX_TOOLWINDOW, 
            strWndClass, 
            "Palette de couleur",
			WS_DLGFRAME |
            WS_VISIBLE |
			WS_CHILD,
            72, 0, 8*17, 24,
            m_wndToolBar.m_hWnd, NULL) ==0 )
	
		m_wndColorBox.ShowWindow (SW_SHOW);

    LoadBarState ("BarSettings");

	// Register the OBL4 Format for the clipboard
	char szOBL4FORMATNAME[] = "OBL4 Format";
    m_nOBL4FormatId = 
		RegisterClipboardFormat(szOBL4FORMATNAME);

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

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	if (m_bSaveSettings) {
		SaveBarState ("BarSettings");
	}

	CFrameWnd::OnClose();
}

BOOL CMainFrame::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default

    // We didn't cause it, so we have lost the palette.
#ifdef _DEBUG
    OutputDebugString( "Palette lost.\n" );
#endif

    // Realize our palette.
	if (m_lpDDPalette)
		m_lpDDSPrimary->SetPalette( m_lpDDPalette );
	
	return CFrameWnd::OnQueryNewPalette();
	
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CFrameWnd::OnPaletteChanged(pFocusWnd);
	
    // We didn't cause it, so we have lost the palette.
#ifdef _DEBUG
    OutputDebugString( "Palette lost.\n" );
#endif

    // Realize our palette.
	if (m_lpDDPalette)
		m_lpDDSPrimary->SetPalette( m_lpDDPalette );

}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::ReleaseObjects()
{
    if ( m_lpDD != NULL )
    {
        // Our clipper destroys itself automatically
        // when we release the primary surface.
        if ( m_lpDDSPrimary != NULL ) 
		{
            m_lpDDSPrimary->Release();
            m_lpDDSPrimary = NULL;
        }

		// Releasing our backbone surface, by 
		// kindness of heart.
        if ( m_lpDDSBack != NULL ) 
		{
            m_lpDDSBack->Release();
            m_lpDDSBack = NULL;
		}


		// Releasing our backbone surface, by 
		// kindness of heart.
        if ( m_lpDDSBack2 != NULL ) 
		{
            m_lpDDSBack2->Release();
            m_lpDDSBack2 = NULL;
        }
		
        // Releasing the primary first insures that
        // the palette will destroy itself.
        if ( m_lpDDPalette != NULL ) 
		{
            m_lpDDPalette->Release();
            m_lpDDPalette = NULL;
        }

        m_lpDD->Release();
        m_lpDD = NULL;
    }

	OutputDebugString ("DDraw: ReleaseObjects() succesful\n");
}

BOOL CMainFrame::InitDDraw( HWND hwnd )
{
    DDSURFACEDESC       ddsd;       // Surface description structure.

    // Create the DirectDraw object.
    if ( FAILED( DirectDrawCreate( NULL, &m_lpDD, NULL ) ) )
	{
        return Fail(  "Couldn't create DirectDraw object.\n" );
    }

    // Set normal cooperative level.
    if ( FAILED( m_lpDD->SetCooperativeLevel( hwnd, DDSCL_NORMAL ) ) )
	{
        return Fail(  "Couldn't set cooperative level.\n" );
    }

    // Create the primary surface.
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
  
    if ( FAILED( m_lpDD->CreateSurface( &ddsd, &m_lpDDSPrimary, NULL ) ) )
	{
        return Fail(  "Couldn't create primary surface.\n" );
    }

    // Create a clipper and attach it to the primary surface.
    if ( FAILED( m_lpDD->CreateClipper( 0, &m_lpDDClipper, NULL ) ) )
	{
        return Fail( "Couldn't create the clipper.\n" );
    }

    // Associate our clipper with our hwnd so it will be updated
    // by Windows.
    if ( FAILED( m_lpDDClipper->SetHWnd( 0, hwnd ) ) )
	{
        return Fail(  "Couldn't set the hwnd.\n" );
    }

    // Associate our clipper with the primary surface, so Blt 
    // will use it. If this step is skipped by defining NOCLIPPER, you
    // can observe the effects of rendering without clipping. Other
    // windows partially obscuring Inawin's will be overwritten.
    #ifndef NOCLIPPER

    if ( FAILED( m_lpDDSPrimary->SetClipper( m_lpDDClipper ) ) )
	{
        return Fail(  "Couldn't set the clipper.\n" );
    }

    #endif
    
    m_lpDDClipper->Release();

	// Retrieve information concerning primary surface,
	// into the DDSURFACEDESC structure.
    ZeroMemory(&ddsd, sizeof(ddsd));

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_ALL;
	if (FAILED (m_lpDDSPrimary->GetSurfaceDesc(&ddsd) ))
	{
		return Fail(  "Couldn't get pixel format.\n" );
    }
	
	// Use the information to clone another surface identical
	// to the previous.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

    if (m_lpDD->CreateSurface(&ddsd, &m_lpDDSBack, NULL) != DD_OK)
	{
		OutputDebugString("Insufficient VRAM - using SYSMEMORY instead!\n");
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY ;
        if (m_lpDD->CreateSurface(&ddsd, &m_lpDDSBack, NULL) != DD_OK)
			return Fail(  "Couldn't create surface 'back'.\n" );
    }

	// Use the information to clone another surface identical
	// to the previous two - the primary and the backbuffer.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY ;

    if (m_lpDD->CreateSurface(&ddsd, &m_lpDDSBack2, NULL) != DD_OK)
	{
        return Fail(  "Couldn't create surface 'back2'.\n" );
    }

    // Check the surface format.
    DDPIXELFORMAT       ddpf;       // Surface format structure.
    ddpf.dwSize = sizeof( ddpf );
    if ( FAILED( m_lpDDSPrimary->GetPixelFormat( &ddpf ) ) )
	{
        return Fail( "Couldn't get pixel format.\n" );
    }

	if (ddpf.dwRGBBitCount <8)
		return Fail ("Cannot operated with less than 256 colors!");

	m_nBpp = ddpf.dwRGBBitCount ;

	// Check for palettized modes
    if ( ddpf.dwFlags & DDPF_PALETTEINDEXED8 ) 
    {
        // We are palettized, so create a palette and attach it to
        // the primary surface.

		CClientDC dc(this);

		if (g_pal.CreatePalette(&dc, 
						  m_lpDD,
						  &m_lpDDPalette  )==FALSE)
		{
			return Fail( "DDraw: Couldn't create the palette\n");
		}

        if ( FAILED( m_lpDDSPrimary->SetPalette( m_lpDDPalette ) ) )
		{
            return Fail( "DDraw: Couldnt' get and/or set the palette.\n" );
        }
    }	
	else
	{
		g_pal.CreateRefsPal(m_nBpp, m_lpDDSBack2);
	}

	// Retrieve information concerning primary surface,
	// into the DDSURFACEDESC structure.
    ZeroMemory(&ddsd, sizeof(ddsd));

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_ALL;
	if (FAILED (m_lpDDSPrimary->GetSurfaceDesc(&ddsd) ))
	{
		return Fail(  "DDraw: Couldn't surface description.\n" );
    }
	
	OutputDebugString("Info: DirectDraw objects constructed succesfully!\n");

    return TRUE;
}

BOOL CMainFrame::Fail (char *szMsg)
{
    ReleaseObjects();

#ifdef _DEBUG
    OutputDebugString( szMsg );
#endif 

    return FALSE;
}

BOOL CMainFrame::RestoreAll ()
{
    HRESULT ddrval;

	OutputDebugString ("RestoreAll()\n");

    // Try restoring the primary first
    ddrval = m_lpDDSPrimary->Restore();
    if ( ddrval == DDERR_WRONGMODE ) 
	{
        // The restore failed because the display mode was
        // changed. Destroy everything then re-create it.
        OutputDebugString( "Display mode changed!\n" );
        ReleaseObjects();
        return InitDDraw( this->m_hWnd );
    }
    else 
		if ( FAILED( ddrval ) )
		{
			// We failed for some other reason.
			OutputDebugString( "Random restore failure.\n" );
			return FALSE;
		}
		else
		{
			// We're OK. Restore everything else.
			//OutputDebugString( "No DDraw Error!\n" );
			//ReleaseObjects();
			//return InitDDraw( this->m_hWnd );
			if ( FAILED( m_lpDDSBack->Restore() ) ) 
				return FALSE;
		}
    return TRUE;
}



void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	if ((nType == SIZE_RESTORED) || (nType == SIZE_MAXIMIZED))
	{
	
	}

}


void CMainFrame::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFrameWnd::CalcWindowRect(lpClientRect, nAdjustType);
}


void CMainFrame::OnHaspalette() 
{
}

void CMainFrame::OnUpdateHaspalette(CCmdUI* pCmdUI) 
{
}


void CMainFrame::OnSysColorChange() 
{
	// TODO: Add your message handler code here
	CFrameWnd::OnSysColorChange();
	OutputDebugString ("OnSysColorChange()\n");
}

void CMainFrame::RecalcLayout(BOOL bNotify) 
{
	// TODO: Add your specialized code here and/or call the base class
	CFrameWnd::RecalcLayout(bNotify);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnMove(int x, int y) 
{
	CFrameWnd::OnMove(x, y);
	
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnPlus() 
{
	// TODO: Add your command handler code here

	m_nPenColor = m_nPenColor ++;
	if (m_nPenColor>=0xf0)
	{
		m_nPenColor=0x10;
	}

	m_wndColorBox.Invalidate();

}

void CMainFrame::OnUpdatePlus(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnMinus() 
{
	// TODO: Add your command handler code here
	m_nPenColor = m_nPenColor --;
	if (m_nPenColor<=0x0f)
	{
		m_nPenColor=0xef;
	}

	m_wndColorBox.Invalidate();
	
}

void CMainFrame::OnUpdateMinus(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::UpdateColorBox()
{
	m_wndColorBox.Repaint();
	//m_wndColorBox.m_wndColorListBox.Invalidate();
}

void CMainFrame::FillSurface (UCHAR nColor, char *pDest, int nLen, int nHei, int nPitch)
{
	if ((nLen * nHei)==0)
		return;

	int nFillSize;
	int nRows = nHei;
	void *pSource;

	//CMainFrame * pMainFrame = (CMainFrame *)AfxGetMainWnd();

	switch(m_nBpp)
	{
		case 8:
			nFillSize = nLen/4;

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

				mov edx,4
_loop2:
				mov ecx, nFillSize
				xor esi,esi

_loop:
				mov [edi+esi], eax  
				add esi,edx
				dec ecx
				or ecx,ecx
				jne _loop

				add edi, nPitch

				dec ebx
				or ebx,ebx
				jne _loop2

				pop esi
				pop edi
				pop edx
				pop ecx
				pop ebx
				pop eax

			
			} // 8 Bpp
		break;

		case 16:
			nFillSize = nLen/2;
			pSource = (void *) &(g_pal16[nColor]);

			_asm {
				push eax
				push ebx
				push ecx
				push edx
				push edi
				push esi
				
				mov ebx, nRows

				mov edi, pDest
				mov esi, pSource
				mov ax, [esi]
				shl eax,16
				mov ax, [esi]


				mov edx,4
_loop2_16:
				mov ecx, nFillSize
				xor esi,esi

_loop_16:
				mov [edi+esi], eax  
				add esi,edx
				dec ecx
				or ecx,ecx
				jne _loop_16

				add edi, nPitch

				dec ebx
				or ebx,ebx
				jne _loop2_16

				pop esi
				pop edi
				pop edx
				pop ecx
				pop ebx
				pop eax


			
			} // 16 Bpp
	break;


		case 24:
			nFillSize = nLen;
			pSource = (void *) &( g_pal24[nColor]);

			_asm {
				push eax
				push ebx
				push ecx
				push edx
				push edi
				push esi
				
				mov ebx, nRows

				mov edi, pDest
				mov esi, pSource
				mov al, [esi]
				mov ah, [esi+1]
				mov dl, [esi+2]

_loop2_24:
				mov ecx, nFillSize
				xor esi,esi

_loop_24:
				mov [edi+esi], al
				mov [edi+esi+1], ah
				mov [edi+esi+2], dl
				inc esi
				inc esi
				inc esi
				dec ecx
				or ecx,ecx
				jne _loop_24

				add edi, nPitch

				dec ebx
				or ebx,ebx
				jne _loop2_24

				pop esi
				pop edi
				pop edx
				pop ecx
				pop ebx
				pop eax


			
			} // 24 Bpp
		break;


		case 32:
			nFillSize = nLen;
			pSource = (void *) &( g_pal32[nColor]);

			_asm {
				push eax
				push ebx
				push ecx
				push edx
				push edi
				push esi
				
				mov ebx, nRows

				mov edi, pDest
				mov esi, pSource
				mov eax, [esi]

				mov edx,4
_loop2_32:
				mov ecx, nFillSize
				xor esi,esi

_loop_32:
				mov [edi+esi], eax  
				add esi,edx
				dec ecx
				or ecx,ecx
				jne _loop_32

				add edi, nPitch

				dec ebx
				or ebx,ebx
				jne _loop2_32

				pop esi
				pop edi
				pop edx
				pop ecx
				pop ebx
				pop eax


			
			} // 32 Bpp
		break;
	}
}


void CMainFrame::OutputOBL3 (CSS3Frame * pFrame, int _mx, int _my, int maxX, int maxY, BOOL bClear, UCHAR *pDest, int nPitch )
{
	//CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

	static void *p16 = &g_pal16[0];
	static void *p32 = &g_pal32[0];
	static void *p24 = &g_pal24[0];

	static short c16;
	static int c32;

	if (m_lpDDSPrimary==NULL)
		return;

    if (m_lpDDSPrimary==NULL || 
		FAILED( m_lpDDSPrimary->IsLost() ) )	{
        if ( !RestoreAll() ) 		{
			Fail( "DDraw: Couldn't restore surfaces.\n" );
            return ;
        }
    }

	// Lock surface
	
	DDSURFACEDESC ddsurfdesc;
	ddsurfdesc.dwSize = sizeof(DDSURFACEDESC);
	ddsurfdesc.dwFlags = DDSD_ALL;

	if (pDest==NULL) {
		if (m_lpDDSBack==NULL || m_lpDDSBack->
			Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)	{
			OutputDebugString("DDraw: Lock failed!\n");
			ReleaseObjects();
			//PostQuitMessage(0);
			return ;
		}
	}
	else {
		ddsurfdesc.lpSurface = pDest; // DO NOT LOCK BY
		ddsurfdesc.lPitch = nPitch;   // USE OUTSIDE PTR IF PROVIDED
	}
	 
	if (pFrame!=NULL)	{
		if ((_mx < pFrame->m_nLen) || (_my< pFrame->m_nHei)) {

			if (bClear)
				FillSurface (0xff, (CHAR*)ddsurfdesc.lpSurface,  
					maxX, maxY,  ddsurfdesc.lPitch );

			UCHAR *s;
			int l=  ddsurfdesc.lPitch; 
			UCHAR *d;

			int y;
			int nCols = min (pFrame->m_nLen - _mx, maxX);
			int nRows = min (pFrame->m_nHei - _my, maxY);
			int nCols3 = nCols/3;

			for (y=0; y<nRows; y++)
			{

				s= pFrame->Point(_mx ,_my +y);
				d = (UCHAR*) ddsurfdesc.lpSurface+y*l;

				switch (m_nBpp)
				{

				case 8:

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

				break; // 8bpp

				case 16:
					_asm{

					push eax
					push ecx
					push edx
					push edi
					push esi
					
					mov ecx, nCols
					mov esi, s
					mov edi, d
					mov edx, 2

					mov ebx, p16

					shr ecx,1
					shl ecx,1

					cmp ecx,edx
					jb _Out16

_loop16:					
					xor eax,eax
					mov al,[esi]
					add eax,eax // 16bits = 2 bytes
					mov ax, [eax+ebx]
					mov [edi], ax
					inc edi
					inc edi
					inc esi

					xor eax,eax
					mov al,[esi]
					add eax,eax // 16bits = 2 bytes
					mov ax, [eax+ebx]
					mov [edi], ax					
					inc edi
					inc edi
					inc esi

					dec ecx
					dec ecx
					or ecx,ecx
					jne _loop16

_Out16:				pop esi
					pop edi
					pop edx
					pop ecx
					pop eax
				
					}
					
				break; // 16bpp

				case 24:
					_asm {
					push eax
					push ecx
					push edx
					push edi			
					push esi
					
					mov ecx, nCols
					mov esi, s
					mov edi, d

					mov ebx, p24

_loop24:			
					// pixel 1
					xor eax,eax
					mov al,[esi]
					mov edx,eax
					add eax,eax // 24bits = 3 bytes
					add eax,edx
					mov dl, [eax+ebx]
					mov [edi], dl					
					mov dl, [eax+ebx+1]
					mov [edi+1], dl					
					mov dl, [eax+ebx+2]
					mov [edi+2], dl					

					inc edi
					inc edi
					inc edi
					inc esi
		
					dec ecx
					or ecx,ecx
					jne _loop24

					pop esi
					pop edi
					pop edx
					pop ecx
					pop eax

					}
				break;

				case 32:
					_asm {

					push eax
					push ecx
					push edx
					push edi
					push esi
					
					mov ecx, nCols
					mov esi, s
					mov edi, d
	
					mov ebx, p32

_loop32:					
					xor eax,eax
					mov al,[esi]
					add eax,eax // 32bits = 4 bytes
					add eax,eax // 
					mov eax, [eax+ebx]
					mov [edi], eax
					inc edi
					inc edi
					inc edi
					inc edi
					inc esi

					dec ecx
					or ecx,ecx
					jne _loop32

					pop esi
					pop edi
					pop edx
					pop ecx
					pop eax
				
					}

				break; // 32bpp

				}

			}
		}
	}
	else {
		if (bClear)
			FillSurface (0xff, (CHAR*)ddsurfdesc.lpSurface,  
				maxX, maxY,  ddsurfdesc.lPitch );
	}

	// Unlock surface
	if (pDest == NULL) {
		if (m_lpDDSBack==NULL || m_lpDDSBack->
			Unlock(NULL))	{
			OutputDebugString("DDraw: Unlock failed!\n");
			ReleaseObjects();
			return ;
		}
	}

}


void CMainFrame::OnSavesettings() 
{
	// TODO: Add your command handler code here
	m_bSaveSettings = !m_bSaveSettings;	
}

void CMainFrame::OnUpdateSavesettings(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck (m_bSaveSettings);
}

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CFrameWnd::OnActivateApp(bActive, hTask);
	
	// TODO: Add your message handler code here
	if (bActive && m_lpDDPalette)
		m_lpDDSPrimary->SetPalette( m_lpDDPalette );

	Invalidate();
	
}

void CMainFrame::OnShowtransparency() 
{
	// TODO: Add your command handler code here
	m_bShowTransparency	 = !m_bShowTransparency;
	Invalidate();
}

void CMainFrame::OnUpdateShowtransparency(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck (m_bShowTransparency);
	
}

BOOL CMainFrame::FillSurface (LPDIRECTDRAWSURFACE lpDDS, UCHAR nColor)
{

	UINT nRGBColor =0 ;

	switch (m_nBpp)
	{
		case 8:
			nRGBColor = nColor;
		break;

		case 16:
			nRGBColor = g_pal16[nColor];		    	              
		break;

		case 24:
			memcpy (&nRGBColor, &g_pal24[nColor], 3);
		break;

		case 32:
			nRGBColor = g_pal32[nColor];
		break;
	}

    // Erase the background
    DDBLTFX     ddbltfx;
	ddbltfx.dwSize = sizeof( ddbltfx );
	ddbltfx.dwFillColor = nRGBColor;
    
	if ( FAILED( lpDDS->Blt( NULL, 
			NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx ) ) )	
	{	
		OutputDebugString("DDraw: ColorFill failed\n");
		return FALSE;
	}

	return TRUE;
}

HBITMAP CMainFrame::MakeBitmap(int len, int hei, unsigned char *bits, HDC hdc)
{

    int			lplanes;
    int			lbpp;
    int         cpt;

    WORD		*ptrIData;
    UINT        *ptrData32;
    USER_24bpp  *ptrData24;
    UCHAR       *ptr;
    UCHAR       *ptrABC;
    UINT		*ptrPal;
	BYTE		color;

    HBITMAP		hbitmap=NULL;

    if ((len==0) || (hei==0))
        return NULL;

    lplanes = GetDeviceCaps(hdc, PLANES);
    lbpp = GetDeviceCaps(hdc, BITSPIXEL);
     
    switch (lbpp)
    {
        case 8:
            hbitmap =  CreateBitmap(len,hei,lplanes,lbpp, bits);
            return hbitmap;
        break;

        case 16:
            ptrIData = (WORD*) malloc(len*hei*2);    
            ptr = (UCHAR *) ptrIData;

            ptrPal = (unsigned int *) &g_pal16[0];

            cpt = len*hei/4;
            __asm
            {

                push eax
                push ebx            
                push ecx
                push edx
                push edi
                push esi
               
                mov ecx, cpt
                mov esi, bits
                mov edi, ptrIData
                mov ebx, ptrPal

again:

                xor eax,eax
                mov edx, [esi]

                or edx,edx
                jne NotBlack

                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi

                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi
                
                inc esi
                inc esi
                inc esi
                inc esi
                jmp LoopNext

NotBlack:

// 1st Pixel
                mov al,dl
                or al,al 
                je EqualZero                             

                shl eax,1        
                mov ax, [ebx+eax]

EqualZero:
                mov [edi], ax
                inc edi
                inc edi
	
// 2nd Pixel
                xor eax,eax
                mov al,dh
                or al,al 
                je EqualZero2

                shl eax,1
                mov ax, [ebx+eax]
EqualZero2:
                mov [edi], ax
                inc edi
                inc edi

// 3rd Pxiel
                sub eax,eax    
                shr edx,16
                mov al,dl
                or al,al 
                je EqualZero3

                shl eax,1        
                mov ax, [ebx+eax]
EqualZero3:
                mov [edi], ax
                inc edi
                inc edi

// 4th Pixel

                sub eax,eax
                mov al,dh
                or al,al 
                je EqualZero4                             

                shl eax,1        
                mov ax, [ebx+eax]
EqualZero4:
                mov [edi], ax
                inc edi
                inc edi

                inc esi
                inc esi
                inc esi
                inc esi

LoopNext:
                dec ecx
                or ecx,ecx
                jne again

                pop esi
                pop edi
                pop edx
                pop ecx
                pop ebx
                pop eax
            }

            hbitmap =  CreateBitmap(len,hei,lplanes,lbpp,ptr);
            free(ptr);

            return hbitmap;
        break;

        case 24:
            ptrData24 =  (USER_24bpp*)
					malloc(len*hei*lbpp/8);    
            ptr = (BYTE *)ptrData24;
            for (cpt = len*hei; cpt; cpt--)
            {

				color = *bits; // APR-16-99

                ptrABC = (BYTE *) &g_pal24[color];
                __asm 
                {
                    push ax
                    push esi
                    push edi

                    mov edi, ptrData24
                    mov esi, ptrABC
                    mov al, [esi]
                    mov [edi],al

                    mov al, [esi+1]
                    mov [edi+1],al

                    mov al, [esi+2]
                    mov [edi+2],al

                    pop edi
                    pop esi
                    pop ax
                }



                ptrData24++;
                bits++;
             }

            hbitmap =  CreateBitmap(len,hei,lplanes,lbpp,ptr);
            free(ptr);
            return hbitmap;
        break;

       case 32:

            ptrData32 =  (UINT*)malloc(len*hei*lbpp/8);    
            ptr = (UCHAR *) ptrData32;

            ptrPal = (UINT*)&g_pal32[0];

            cpt = len*hei/4;

            __asm 
            {         
            
                push eax
                push ebx            
                push ecx
                push edx
                push edi
                push esi
               
                mov ecx, cpt
                mov esi, bits
                mov edi, ptrData32
                mov ebx, ptrPal


again32:
                mov edx, [esi]

                or edx,edx
                jne NotNULL32

             
                mov eax,edx
                mov [edi],eax
                inc edi
                inc edi
                inc edi
                inc edi
                mov [edi],eax
                inc edi
                inc edi
                inc edi
                inc edi
                mov [edi],eax
                inc edi
                inc edi
                inc edi
                inc edi
                mov [edi],eax
                inc edi
                inc edi
                inc edi
                inc edi

                inc esi
                inc esi
                inc esi
                inc esi
                
                jmp LoopNext32  

NotNULL32:

//              1st byte .......................
                xor eax,eax
                mov al,dl
                or al,al 
                je EqualZ32

                shl eax,2        

                mov eax, [ebx+eax]
EqualZ32:
                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi


//              2nd byte ........................
                xor eax,eax
                mov al,dh
                or al,al 
                je EqualZ32ii

                shl eax,2        

                mov eax, [ebx+eax]
EqualZ32ii:
                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi

//              3rd byte ........................
                shr edx,16
                xor eax,eax
                mov al,dl
                or al,al 
                je EqualZ32iii

                shl eax,2        

                mov eax, [ebx+eax]
EqualZ32iii:
                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi

//              4th byte ........................
                xor eax,eax
                mov al,dh
                or al,al 
                je EqualZ32iv

                shl eax,2        

                mov eax, [ebx+eax]
EqualZ32iv:
                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi

//              inc source reg. ...................

                inc esi
                inc esi
                inc esi
                inc esi

LoopNext32:
                dec ecx
                or ecx,ecx
                jne again32
             

                pop esi
                pop edi
                pop edx
                pop ecx
                pop ebx
                pop eax
            }

            hbitmap =  CreateBitmap(len,hei,lplanes,lbpp,ptr);
            free(ptr);
            return hbitmap;
        break;
    }
   
    return NULL;
}

BOOL CMainFrame::NewPalette()
{
	//ReleaseObjects();
	//InitDDraw(AfxGetMainWnd()->m_hWnd);

	if (!m_lpDDSPrimary)
		return FALSE;

    // Check the surface format.
    DDPIXELFORMAT       ddpf;       // Surface format structure.
    ddpf.dwSize = sizeof( ddpf );
    if ( FAILED( m_lpDDSPrimary->GetPixelFormat( &ddpf ) ) )
	{
        return Fail( "Couldn't get pixel format.\n" );
    }

	if (ddpf.dwRGBBitCount <8)
		return Fail ("Cannot operated with less than 256 colors!");

	m_nBpp = ddpf.dwRGBBitCount ;

	// Check for palettized modes
    if ( ddpf.dwFlags & DDPF_PALETTEINDEXED8 ) 
    {
        // We are palettized, so create a palette and attach it to
        // the primary surface.

		CClientDC dc(this);

		if (g_pal.CreatePalette(&dc, 
						  m_lpDD,
						  &m_lpDDPalette  )==FALSE)
		{
			return Fail( "DDraw: Couldn't create the palette\n");
		}

        if ( FAILED( m_lpDDSPrimary->SetPalette( m_lpDDPalette ) ) )
		{
            return Fail( "DDraw: Couldnt' get and/or set the palette.\n" );
        }
    }	
	else
	{
		g_pal.CreateRefsPal(m_nBpp, m_lpDDSBack2);
	}

	Invalidate();
	UpdateColorBox();
	return TRUE;
}

void CMainFrame::OnAdjustgamma() 
{
	// TODO: Add your command handler code here
	g_pal.IncGamma();	
	NewPalette();
}

void CMainFrame::OnUpdateAdjustgamma(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}
