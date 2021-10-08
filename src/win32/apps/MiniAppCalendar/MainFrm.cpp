// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Resource.h"

#include "App.h"
#include "MainFrm.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CSdiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_TIMECHANGE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
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
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    EnableDocking(CBRS_ALIGN_ANY);

    if ((CreateToolBar()==TRUE) &&
        (CreateStatusBar()==TRUE))
    {}
    else 
        return -1;
    
    LoadBarState ("BarSettings");

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);

    m_wndToolBar.SetWindowText("Barre d'outils");

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


BOOL CMainFrame::CreateToolBar()
{
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
	DockControlBar(&m_wndToolBar);

    return TRUE;

}

BOOL CMainFrame::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
    return TRUE;


}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

    SaveWindowState();
    SaveBarState ("BarSettings");
    
	CFrameWnd::OnClose();
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnTimeChange() 
{
	CFrameWnd::OnTimeChange();
	
	// TODO: Add your message handler code here
	
}

BOOL CMainFrame::RestoreWindowState ()
{
    CString section = "MainWindow";

    //m_bFullWindow = myApp.GetProfileInt (version, "FullWindow", 0);
    //SetTitleBarState ();

    //m_bStayOnTop = myApp.GetProfileInt (version, "StayOnTop", 0);
   // SetTopMostState ();

    WINDOWPLACEMENT wp;
    wp.length = sizeof (WINDOWPLACEMENT);
    GetWindowPlacement (&wp);

    if (((wp.flags =
            theApp.GetProfileInt (section, "flags", -1)) != -1) &&
        ((wp.showCmd =
            theApp.GetProfileInt (section, "showCmd", -1)) != -1) &&
        ((wp.rcNormalPosition.left =
            theApp.GetProfileInt (section, "x1", -1)) != -1) &&
        ((wp.rcNormalPosition.top =
            theApp.GetProfileInt (section, "y1", -1)) != -1) &&
        ((wp.rcNormalPosition.right =
            theApp.GetProfileInt (section, "x2", -1)) != -1) &&
        ((wp.rcNormalPosition.bottom =
            theApp.GetProfileInt (section, "y2", -1)) != -1)) {

        wp.rcNormalPosition.left = min (wp.rcNormalPosition.left,
            ::GetSystemMetrics (SM_CXSCREEN) -
            ::GetSystemMetrics (SM_CXICON));
        wp.rcNormalPosition.top = min (wp.rcNormalPosition.top,
            ::GetSystemMetrics (SM_CYSCREEN) -
            ::GetSystemMetrics (SM_CYICON));

        SetWindowPlacement (&wp);
        return TRUE;
    }
    return FALSE;

}

void CMainFrame::SaveWindowState()
{
    CString section = "MainWindow";

    //theApp.WriteProfileInt (version, "FullWindow", m_bFullWindow);
    //theApp.WriteProfileInt (version, "StayOnTop", m_bStayOnTop);

    WINDOWPLACEMENT wp;
    wp.length = sizeof (WINDOWPLACEMENT);
    GetWindowPlacement (&wp);

    theApp.WriteProfileInt (section, "flags", wp.flags);
    theApp.WriteProfileInt (section, "showCmd", wp.showCmd);
    theApp.WriteProfileInt (section, "x1", wp.rcNormalPosition.left);
    theApp.WriteProfileInt (section, "y1", wp.rcNormalPosition.top);
    theApp.WriteProfileInt (section, "x2", wp.rcNormalPosition.right);
    theApp.WriteProfileInt (section, "y2", wp.rcNormalPosition.bottom);

}
