// timerDlg.cpp : implementation file
//

#include "stdafx.h"
#include <mmsystem.h>
#include "timer.h"
#include "timerDlg.h"
#include "dlgSetTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_EVENT 0x900522

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg dialog

CTimerDlg::CTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_bRunning = FALSE;
    m_bOnTop = FALSE;
    m_hAccel = NULL;

}

void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialog)
	//{{AFX_MSG_MAP(CTimerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg message handlers

BOOL CTimerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

    CMenu * pMenu = GetMenu();

    m_hAccel = LoadAccelerators (
        AfxGetResourceHandle(),
        MAKEINTRESOURCE( IDR_ACCEL ));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimerDlg::OnPaint() 
{
    CString strText;
    CString str = "0:00:00";

    if (m_bRunning)
    {
        CTime now = CTime::GetCurrentTime();
        if (now < m_timeEnd)
        {
            CTimeSpan len = m_timeEnd - now;

            str.Format("%d:%2.2d:%2.2d",
                len.GetHours(),
                len.GetMinutes(),
                len.GetSeconds());
        }
        else
        {
            PlaySound();
            m_bRunning = FALSE;
        }
    }

    CPaintDC dc(this); // device context for painting
    
    if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

        SetWindowText(str);

	}
	else
	{
        GetWindowText (strText);

        if (strText != "timer")
        {
            SetWindowText("timer");
        }
        
        CFont font;

        CRect rectView;

        GetClientRect(rectView);
        CSize rectSize = rectView.Size();

        int nHeight = 100;

        BOOL iStatus = font.CreateFont (nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0,
            DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH , "Arial");

        dc.SetTextColor(COLOR_WINDOWTEXT);
        dc.SetBkColor(0xffffffff);
        dc.SetBkMode(TRANSPARENT);

        CFont *pOldFont = (CFont*) dc.SelectObject(font);

        iStatus= dc.ExtTextOut(8 , 4,
            ETO_CLIPPED, NULL,
            str, str.GetLength(),
            NULL);
               
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTimerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
    if (m_bRunning)
    {
        Invalidate();
    }

    CString str = "0:00:00";

    if (m_bRunning)
    {
        CTime now = CTime::GetCurrentTime();
        if (now < m_timeEnd)
        {
            CTimeSpan len = m_timeEnd - now;

            str.Format("%d:%2.2d:%2.2d",
                len.GetHours(),
                len.GetMinutes(),
                len.GetSeconds());
        }
        else
        {
            PlaySound();
            m_bRunning = FALSE;
        }
    }

    if (IsIconic())
    {
        SetWindowText(str);
    }


	CDialog::OnTimer(nIDEvent);
}

BOOL CTimerDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

    CDlgSetTimer dlg;

    switch (wParam & 0xffff)
    {
    case IDM_START_TIMER:
        if (dlg.DoModal()==IDOK)
        {
            CTimeSpan len = CTimeSpan(
                0, 
                dlg.m_nHours,
                dlg.m_nMinutes,
                dlg.m_nSeconds);

            m_timeStart = CTime::GetCurrentTime();
            m_timeEnd = m_timeStart + len;
            m_bRunning = TRUE;

            Invalidate();

        }                
    break;

    case IDM_STOP_TIMER:
        m_bRunning = FALSE;
        Invalidate();
    break;

    case IDM_ALWAYS_TOP:

        if (m_bOnTop)
        {
            SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, 
                SWP_NOMOVE | SWP_NOSIZE);

        }
        else
        {
            SetWindowPos(&wndTopMost, 0, 0, 0, 0, 
                SWP_NOMOVE | SWP_NOSIZE);
            
        }

        m_bOnTop = !m_bOnTop;

        int nValue = MF_BYCOMMAND;
        if (m_bOnTop)
        {
            nValue |= MF_CHECKED;
        }
        else
        {
            nValue |= MF_UNCHECKED;
        }

        GetMenu()->CheckMenuItem(wParam, nValue);
    
    break;

    }

	return CDialog::OnCommand(wParam, lParam);
}

BOOL CTimerDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

    OutputDebugString("destroy\n");

    KillTimer(TIMER_EVENT);

    if (m_hAccel)
    {
        DestroyAcceleratorTable(m_hAccel);
        m_hAccel = NULL;
    }

	return CDialog::DestroyWindow();
}

int CTimerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
    OutputDebugString("create\n");

    int nTimer = SetTimer(TIMER_EVENT, 1000, NULL);

    if (!nTimer)
    {
        return -1;
    }
	
	return 0;
}       

void CTimerDlg::PlaySound()
{    
    ::PlaySound("C:\\Win98\\Media\\Chimes.wav", NULL, 
        SND_ASYNC | SND_FILENAME | SND_NOWAIT);  
}

void CTimerDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

LRESULT CTimerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CTimerDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

    if (TranslateAccelerator(
        this->m_hWnd,
        m_hAccel,
        pMsg))
    {
#ifdef _DEBUG
        OutputDebugString("translated\n");
#endif
    }


    return CDialog::PreTranslateMessage(pMsg);
}
