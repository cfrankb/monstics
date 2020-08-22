// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "vlamits3.h"
#include "MainFrm.h"
#include "midi.h"
#include "game.h"
#include "Splash.h"

#include "dlgoptions.h"
#include "dlgErrorBox.h"
#include "dlgload.h"
#include "dlgsave.h"
#include "dlgtext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_BIP, OnBip)
	ON_UPDATE_COMMAND_UI(IDM_BIP, OnUpdateBip)
	ON_COMMAND(IDM_START, OnStart)
	ON_UPDATE_COMMAND_UI(IDM_START, OnUpdateStart)
	ON_COMMAND(IDM_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(IDM_STOP, OnUpdateStop)
	ON_COMMAND(IDM_OPTIONS, OnOptions)
	ON_UPDATE_COMMAND_UI(IDM_OPTIONS, OnUpdateOptions)
	ON_WM_ACTIVATEAPP()
	ON_WM_PAINT()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_COMMAND(IDM_PAUSE, OnPause)
	ON_UPDATE_COMMAND_UI(IDM_PAUSE, OnUpdatePause)
	ON_WM_CLOSE()
	ON_COMMAND(IDM_ZKEY, OnZkey)
	ON_UPDATE_COMMAND_UI(IDM_ZKEY, OnUpdateZkey)
	ON_WM_ACTIVATE()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(IDM_RESTART, OnRestart)
	ON_UPDATE_COMMAND_UI(IDM_RESTART, OnUpdateRestart)
	ON_COMMAND(IDM_NEXT, OnNext)
	ON_UPDATE_COMMAND_UI(IDM_NEXT, OnUpdateNext)
	ON_COMMAND(IDM_GAMMA, OnGamma)
	ON_UPDATE_COMMAND_UI(IDM_GAMMA, OnUpdateGamma)
	ON_COMMAND(IDM_SAVE, OnSave)
	ON_UPDATE_COMMAND_UI(IDM_SAVE, OnUpdateSave)
	ON_COMMAND(IDM_LOAD, OnLoad)
	ON_UPDATE_COMMAND_UI(IDM_LOAD, OnUpdateLoad)
	ON_COMMAND(IDM_HELP, OnHelp)
	ON_UPDATE_COMMAND_UI(IDM_HELP, OnUpdateHelp)
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
	m_nTimer =0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//m_nTimer = SetTimer (902209, 1, NULL);
	//m_game.Init( (CWnd*) this);

	// CG: The following line was added by the Splash Screen component.
	//CSplashWnd::ShowSplashScreen(this);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

#ifndef _DEBUG 
	cs.style =  WS_POPUP | WS_MAXIMIZE | WS_VISIBLE; 
	cs.hMenu = NULL;
	cs.x =0;
	cs.y =0;
	cs.cx = SCREENLEN;
	cs.cy = SCREENHEI;
	cs.dwExStyle = WS_EX_TOPMOST;
#else
	cs.style =   WS_MAXIMIZE | WS_VISIBLE; 
	cs.hMenu = NULL;
	cs.x =0;
	cs.y =0;
	cs.dwExStyle = 0;
#endif

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

void CMainFrame::OnHelp() 
{
	// TODO: Add your command handler code here
    if (m_game.m_bCritical)
    {
        return;
    }

	PrepareForMessageBox();

    char szText[]=
    {
        "General help\r\n\r\n"
        "[F1] HELP\r\n" \
        "[F2] SAVE\r\n" \
        "[F3] LOAD\r\n" \
        "[F4] OPTIONS\r\n" \
        "[F5] RESTART\r\n" \
        "[F6] NEXT LEVEL\r\n" \
        "[F9] CHANGE VLAMIT\r\n" \
        "[F11] GAMMA CORRECTION\r\n" \
        "[P] PAUSE\r\n" \
        "[Z] ACTION KEY (e.g. pull switches)\r\n" \
        "[ESC] QUIT\r\n" \
    };

	CDlgText dlg;
    dlg.SetData("Help", szText, "&Close");
	dlg.DoModal();

	AcquireMouse();

}

void CMainFrame::OnUpdateHelp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnSave() 
{
    /*
	if (m_game.m_bCritical)
    	if (!m_game.Save("vlamits3.sav"))
	    {
		    ErrorBox("Saving game failed!");
	    }

		return;

	// TODO: Add your command handler code here
    */

    char szTemp[1024];

	if (m_game.m_bCritical)
		return;

	PrepareForMessageBox();

	CDlgSave dlg;
	if (dlg.DoModal()==IDOK)
	{       
        wsprintf(szTemp, "%s.sav", 
            dlg.m_strName.GetBuffer(1));

    	if (!m_game.Save(szTemp))
	    {
		    ErrorBox("Saving game failed!");
	    }
	}

	AcquireMouse();
	
}

void CMainFrame::OnUpdateSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnLoad() 
{
    char szTemp[1024];
    
    if (m_game.m_bCritical)
		return;

	PrepareForMessageBox();

    /*
	// TODO: Add your command handler code here
	if (!m_game.Load("vlamits3.sav"))
	{
		ErrorBox("Loading game failed!");
	}
    */

    CDlgLoad dlg;
	if (dlg.DoModal()==IDOK)
	{   
        /*
        wsprintf(szTemp, "%s.sav", 
            dlg.m_strName.GetBuffer(1));
            */

        wsprintf(szTemp, "Loading %s\n", dlg.m_strName.GetBuffer(1));
        OutputDebugString(szTemp);

    	if (!m_game.Load(dlg.m_strName.GetBuffer(1)))
	    {
		    ErrorBox("Loading game failed!");
	    }
    }

	AcquireMouse();
}

void CMainFrame::OnUpdateLoad(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnBip() 
{
	// TODO: Add your command handler code here
	if (m_game.m_nPlayerEntry!=-1)
	{
		CScriptEntry & player =
			m_game.m_sFW[m_game.m_nPlayerEntry];

		COBL3Filter & filter = *
			m_game.m_arrOBL3[player.m_nFrameSet];

		if (player.m_nFrameNo +20< 	filter.GetSize())
			player.m_nFrameNo  =
				player.m_nFrameNo +20;
		else
			player.m_nFrameNo =
				player.m_nFrameNo %20;
	}
}

void CMainFrame::OnUpdateBip(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnStart() 
{
	// TODO: Add your command handler code here
	/*
	m_game.m_bPlayingMusic = !m_game.m_bPlayingMusic;
	int bStatus = PlayMidi (this->m_hWnd, "c:\\!projet\\musics\\6.mid");
	if (bStatus!=TRUE)
	{
		OutputDebugString("PlayMidi() Failed!\n");
	}
	*/

	m_game.m_music.Play();
}

void CMainFrame::OnUpdateStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->Enable (!m_game.m_bPlayingMusic);	
}

void CMainFrame::OnStop() 
{
	// TODO: Add your command handler code here
	//m_game.m_bPlayingMusic = !m_game.m_bPlayingMusic;
	//StopMidi (this->m_hWnd);

	m_game.m_music.Stop();
}

void CMainFrame::OnUpdateStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->Enable (m_game.m_bPlayingMusic);	
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch (message)
	{
		case MM_MCINOTIFY:
			if (m_game.m_bPlayingMusic) {
				//ReplayMidi (this->m_hWnd);
			}

		break;

		default:
		break;
	}

	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnOptions() 
{
	// TODO: Add your command handler code here
	PrepareForMessageBox();

	CDlgOptions dlg;
	if (dlg.DoModal()==IDOK)
	{
		if (dlg.m_pGuid!=NULL )
		{
			if (m_game.m_lpdid2!=NULL) {
				m_game.m_lpdid2->Unacquire();
				m_game.m_lpdid2->Release();
				m_game.m_lpdid2=NULL;
			}

    		if (m_game.InitIDevice( m_game.m_lpdid2, (GUID *)dlg.m_pGuid, (CWnd*)this ))
			{
				m_game.m_lpdid2->Acquire();
			}
		}
	}

	AcquireMouse();
}

void CMainFrame::OnUpdateOptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnDestroy() 
{
	// TODO: Add your message handler code here

	CFrameWnd::OnDestroy();
}

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) 
{

#ifndef _DEBUG
	SetFocus();
    //UpdateWindow();
#endif	

	CFrameWnd::OnActivateApp(bActive, hTask);
	
	// TODO: Add your message handler code here

	m_game.m_bActive = bActive;
	if (m_game.m_bActive!=TRUE)
	{
		m_game.m_bPause = TRUE;
	}

	if (bActive) {
    // We didn't cause it, so we have lost the palette.
#ifdef _DEBUG
		OutputDebugString( "Palette lost.\n" );
#endif
	    // Realize our palette.
		if (m_game.m_lpDDPal) {
			m_game.m_lpDDSPrimary->SetPalette( m_game.m_lpDDPal ); 
		}
	}
}

void CMainFrame::OnPaint() 
{
	// TODO: Add your message handler code here
	CPaintDC dc(this); // device context for painting
	
	// Do not call CFrameWnd::OnPaint() for painting messages
}


void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CFrameWnd::OnPaletteChanged(pFocusWnd);
    // We didn't cause it, so we have lost the palette.
#ifdef _DEBUG
    OutputDebugString( "Palette lost.\n" );
#endif

    // Realize our palette.
    if (m_game.m_lpDDPal && !m_game.m_bCritical)
		m_game.m_lpDDSPrimary->SetPalette( m_game.m_lpDDPal ); 
	
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
    if (m_game.m_lpDDPal && !m_game.m_bCritical)
		m_game.m_lpDDSPrimary->SetPalette( m_game.m_lpDDPal ); 
	
	return CFrameWnd::OnQueryNewPalette();
}


void CMainFrame::OnPause() 
{
	// TODO: Add your command handler code here
	//m_game.m_bPause = !m_game.m_bPause ;

	PrepareForMessageBox();

    /*
	// TODO: Add your command handler code here
	if (!m_game.Load("vlamits3.sav"))
	{
		ErrorBox("Loading game failed!");
	}
    */

    ErrorBox("Game paused");

	AcquireMouse();

}

void CMainFrame::OnUpdatePause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_game.m_bCritical = TRUE;
	if (m_nTimer)
	{
		KillTimer (m_nTimer);
	}

	m_game.Destroy();
	CFrameWnd::OnClose();
}

BOOL CMainFrame::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString strWndClass = AfxRegisterWndClass (
        0,//CS_DBLCLKS ,                  // Class style
        NULL, //AfxGetApp()->LoadStandardCursor (IDC_ARROW),   // Class cursor
        0,//(HBRUSH)COLOR_INFOTEXT,//(HBRUSH) (COLOR_3DFACE ),               // Class background brush
        NULL            // Class icon
        );
	
	return CWnd::Create(strWndClass, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CMainFrame::UpdateGamePlay(BOOL bReset)
{
	static UINT nNextTick =0;
	static UINT nTickCount =0;

	if (bReset) {
		nTickCount =0;
		nNextTick=0;
		return FALSE;
	}

	UINT nTime =timeGetTime ();
	
	if ((nNextTick!=0) && (nTime<nNextTick) ){
		return FALSE;
	}

	UINT nNextTickT = nNextTick;
	nNextTick = nTime + 1000/60;

	if (m_game.m_bPlayLevelIntro) 
	{
		if (nTickCount%1 == 0)
		{
			unsigned nState;
			m_game.PollDevice( m_game.m_lpdid2, nState)	;

			m_game.m_nLevelIntroStatus ++;
			if (m_game.m_nLevelIntroStatus>60*2 || nState)
			{
				m_game.m_nLevelIntroStatus = 0;
				m_game.m_bPlayLevelIntro=FALSE;
				m_game.m_nShowStatus = 1;
				m_game.m_nStatusCount = 0;
			}
		}

		m_game.DrawScreen ();
		nTickCount++;
		return TRUE;
	}

	m_game.Animate(nTickCount); 
	m_game.ManagePlayer (nTickCount);
	m_game.ManageObjects (nTickCount);
	m_game.ManageAuto (nTickCount);

	if (nTickCount%2==0 && m_game.m_nShowStatus)
	{
		switch(m_game.m_nShowStatus)
		{
			case 1:
				m_game.m_nStatusCount ++;
				if (m_game.m_nStatusCount == 32)
				{
					m_game.m_nShowStatus = 2;
					m_game.m_nStatusCount = 0;
				}
			break;					  

			case 2:
				m_game.m_nStatusCount ++;
				if (m_game.m_nStatusCount == 256)
				{
					m_game.m_nShowStatus = 3;
					m_game.m_nStatusCount = 0;
				}
			break;

			case 3:
				m_game.m_nStatusCount ++;
				if (m_game.m_nStatusCount == 32)
				{
					m_game.m_nShowStatus = 0;
					m_game.m_nStatusCount = 0;
				}
			break;
		}
	}

	// compensate for lost frames
	if ((nNextTickT + 1000/60)>=nTime)
	{
		if (nTickCount%1==0)
		{
			m_game.DrawScreen ();
		}
	}

	nTickCount++;

	return TRUE;

}

void CMainFrame::OnZkey() 
{
	// TODO: Add your command handler code here
	if (!m_game.m_bPause && !m_game.m_bGameOver &&
		!m_game.m_bCritical) 
	{
			m_game.PlayerZKey();
	}
}

void CMainFrame::OnUpdateZkey(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);

	SetFocus();
    //UpdateWindow();
	
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnRestart() 
{
	// TODO: Add your command handler code here
	m_game.InitLevel (0);
	
}

void CMainFrame::OnUpdateRestart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
    
#ifndef _DEBUG
	SetFocus();
    UpdateWindow();
#endif 
	
	CFrameWnd::ActivateFrame(nCmdShow);
	m_game.Init( (CWnd*) this);
} 

void CMainFrame::OnNext() 
{
	// TODO: Add your command handler code here
	if (m_game.m_nCurrScript+1 < m_game.GetSize() )
	{
		m_game.m_nCurrScript	++;
	}
	else
	{
		m_game.m_nCurrScript=0;
	}
	m_game.InitLevel (m_game.m_nCurrScript);
}

void CMainFrame::OnUpdateNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnGamma() 
{
	// TODO: Add your command handler code here
	/*
	m_game.m_nGammaLevel ++;
	if (m_game.m_nGammaLevel>5)
		m_game.m_nGammaLevel = 0;

#ifdef _DEBUG
	char szTemp[128];
	wsprintf(szTemp,"Gamma correction level %d\n", m_game.m_nGammaLevel);
	OutputDebugString(szTemp);
#endif

	*/
	m_game.ApplyGamma();
}

void CMainFrame::OnUpdateGamma(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::PrepareForMessageBox()
{
#ifndef _DEBUG
	while (m_game.m_bDrawing);
	while (m_game.m_lpDDSPrimary-> GetFlipStatus (DDGFS_CANFLIP) != DD_OK);

	if (!m_game.m_bPrimary)
	{
		OutputDebugString("NOT PRIMARY\n");
		m_game.m_lpDDSPrimary->Flip(NULL, DDFLIP_WAIT);		
		m_game.m_bPrimary = !m_game.m_bPrimary;
	}
	else
	{
		OutputDebugString("PRIMARY\n");
	}

	while (m_game.m_lpDDSPrimary-> GetFlipStatus (DDGFS_CANFLIP) != DD_OK);
#endif
}

void CMainFrame::AcquireMouse()
{
#ifndef _DEBUG
	// Acquire the system mouse in full screen mode to insure the mouse
	// that it will not be visible when we don't want it to be.
    if (m_game.InitIDevice( m_game.m_lpdid2Mouse, (GUID *)&GUID_SysMouse, (CWnd*)this ))
		m_game.m_lpdid2Mouse->Acquire();
#endif
}

void CMainFrame::ErrorBox(char *sz)
{
	PrepareForMessageBox();
	CDlgErrorBox dlg;
	dlg.m_strText = sz;
	dlg.DoModal();
	AcquireMouse();
}

