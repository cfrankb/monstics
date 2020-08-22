// ClrBox.cpp : implementation file
//

// In accordance with Statics System V4.0 specifications, this class generates
// a color box that is uses to allow the user to click on it; when clicked
// it will show a 256colors palette (a CColorListBox object)

#include "stdafx.h"
#include "ClrBox.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClrBox

CClrBox::CClrBox()
{
}

CClrBox::~CClrBox()
{
}


BEGIN_MESSAGE_MAP(CClrBox, CWnd)
	//{{AFX_MSG_MAP(CClrBox)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_GETMINMAXINFO()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_MBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


#define LISTBOX_LEN 8*17
#define LISTBOX_HEI 8*14

/////////////////////////////////////////////////////////////////////////////
// CClrBox message handlers

int CClrBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//atic CColorListBox wndColorListBox ;

	CRect rectThis;
	GetWindowRect(rectThis);

	CString strWndClass = AfxRegisterWndClass (
        CS_DBLCLKS | CS_OWNDC,                  // Class style
        AfxGetApp()->LoadStandardCursor (IDC_ARROW),   // Class cursor
		NULL,//(HBRUSH) (COLOR_3DFACE ),               // Class background brush
        NULL            // Class icon
        );

    if ( m_wndColorListBox. 
            CreateEx (0	, 
            strWndClass, 
            "",
			WS_DLGFRAME | 
			WS_POPUP	,
            rectThis.left, rectThis.bottom, LISTBOX_LEN, LISTBOX_HEI,
            this->m_hWnd, NULL) ==0 );

	// TODO: Add your specialized creation code here
	m_wndColorListBox.m_pwndParent = (CWnd*) this;
	m_wndColorListBox.ShowWindow (SW_HIDE);
	m_bListBox = FALSE;

	m_nTimer = SetTimer (220990, 10, NULL);

	return 0;
}

void CClrBox::OnPaint() 
{
	// TODO: Add your message handler code here
	
	CRect rectView;

    GetClientRect(rectView);
    CSize rectSize = rectView.Size();

	// insure blitter alignment
	if (rectSize.cx %4) 
		rectSize.cx= rectSize.cx + (4-rectSize.cx %4);

	if (rectSize.cy %4) 
		rectSize.cy= rectSize.cy + (4-rectSize.cy %4);

	ClientToScreen (&rectView); // x & y
 
    // If the user has changed the display resolution our
    // surfaces could be lost.

	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

	if ( pMainFrame->m_lpDDSPrimary == NULL)
	{
		CPaintDC dc (this);
		return;
	}

    if ( FAILED( pMainFrame->m_lpDDSPrimary->IsLost() ) )
	{
        if ( !pMainFrame->RestoreAll() ) 
		{
			pMainFrame->Fail( "DDraw: Couldn't restore surfaces.\n" );
            return ;
        }
    }

	// Code snippet 100% by Frank B.

	DDSURFACEDESC ddsurfdesc;
	ddsurfdesc.dwSize = sizeof(DDSURFACEDESC);
	ddsurfdesc.dwFlags = DDSD_ALL;

	if (pMainFrame->m_lpDDSBack2->
		Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)	{
		OutputDebugString("DDraw: Lock failed!\n");
		pMainFrame->ReleaseObjects();
		PostQuitMessage(0);
		return; 
	}

	char *pDest = (char*)ddsurfdesc.lpSurface; 

	pMainFrame->FillSurface (pMainFrame->m_nPenColor, 
	   pDest, rectSize.cx, rectSize.cy, ddsurfdesc.lPitch);

	if (pMainFrame->m_lpDDSBack2->
		Unlock(NULL))	{
		OutputDebugString("DDraw: Unlock failed!\n");
		pMainFrame->ReleaseObjects();
		PostQuitMessage(0);
		return ;
	}

	// Using the GDI's TextOut to Blt the numbers onto 
	// the DDraw backbuffer.

    // But first let's get a DC for the surface.

    HDC  hdcSurf  = NULL;
    
	if ( FAILED( pMainFrame->m_lpDDSBack2->GetDC( &hdcSurf ) ) )	{
        Fail( "Couldn't get a DC.\n");
        return ;
    }

	int nOldTextColor = ::SetTextColor (hdcSurf, 0xffffff);
	if ((pMainFrame->m_nPenColor == 0x1e) || 
		(pMainFrame->m_nPenColor == 0x1f) ||
		(pMainFrame->m_nPenColor == 0x3c) ||
		(pMainFrame->m_nPenColor == 0x54) ||
		(pMainFrame->m_nPenColor == 0x6c) ||
		(pMainFrame->m_nPenColor == 0xff) ||
		(pMainFrame->m_nPenColor == 0x2f) )
			::SetTextColor (hdcSurf, 0x0);

	int nOldBkMode = ::SetBkMode (hdcSurf, TRANSPARENT);

	CString strText;
	strText.Format ("0x%x %d", pMainFrame->m_nPenColor, pMainFrame->m_nPenColor);
	::TextOut (hdcSurf, rectSize.cx /2, 0, strText, strText.GetLength() ); 

	// Release DC -- important
    if (hdcSurf)
        pMainFrame->m_lpDDSBack2->ReleaseDC( hdcSurf );

   // Quickest way to get the destination RECT size and 
   // position.
   CRect rectDest; 
   GetClientRect(rectDest);

    // We have associate the clipper with this window
    if ( FAILED( pMainFrame->m_lpDDClipper->SetHWnd( 0, this->m_hWnd ) ) )	{
         //
		OutputDebugString(  "Couldn't set the hwnd to ColorBox.\n" );
		 return;
    }


   // Blt from the second surface unto the display surface
   // and fill our little view.
   if ( FAILED( pMainFrame->m_lpDDSPrimary->Blt( &rectView, 
	   pMainFrame->m_lpDDSBack2, &rectDest,
                    DDBLT_WAIT, NULL ) ) )	{
#ifdef _DEBUG
	   OutputDebugString("Couldn't blt! [clrbox] \n");
#endif
		PostMessage(WM_PAINT);
		return ;
    }

    //  Now we'll reassocite the clipper with the MainFrame
    if ( FAILED( pMainFrame->m_lpDDClipper->SetHWnd( 0, pMainFrame->m_hWnd ) ) )	{
         Fail(  "Couldn't reset the hwnd. [clrbox] \n" );
		 return;
    }

	CPaintDC dc(this); // device context for painting
}

void CClrBox::OnClose() 
{
}

void CClrBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

	CWnd::OnMouseMove(nFlags, point);
}

void CClrBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

	if (m_bListBox==FALSE)
	{
		CRect rectThis;
		GetWindowRect(rectThis);
		m_wndColorListBox.MoveWindow 
			(rectThis.left+1, rectThis.bottom+1, LISTBOX_LEN,
			LISTBOX_HEI, FALSE);

		m_wndColorListBox.ShowWindow(SW_SHOW);
		m_bListBox = TRUE;
	}
	else
	{
		m_wndColorListBox.ShowWindow(SW_HIDE);
		m_bListBox = FALSE;
	}


	CWnd::OnLButtonDown(nFlags, point);
}

void CClrBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

    ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_KEYDOWN, nChar, nFlags);   
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);

}


BOOL CClrBox::Fail (char *szMsg)
{
    OutputDebugString( szMsg );
    //AfxGetMainWnd()-> DestroyWindow();
    return FALSE;
}


void CClrBox::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnGetMinMaxInfo(lpMMI);
}

void CClrBox::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if (m_nTimer!=0)
	{
		if (m_bListBox==TRUE)
		{
			CRect rectThis;
			GetWindowRect(rectThis);
			
			//m_wndColorListBox.MoveWindow 
			//	(rectThis.left+1, rectThis.bottom+1, LISTBOX_LEN,
			//	LISTBOX_HEI, FALSE);

			CPoint point;
			GetCursorPos (&point);

			if ((point.x < rectThis.left) ||
				(point.x  > rectThis.right) ||
				(point.y< rectThis.top) ||
				(point.y> rectThis.bottom + LISTBOX_HEI))
			{

				m_wndColorListBox.ShowWindow(SW_HIDE);
				m_bListBox= FALSE;
			}
			
		}
	}

	CWnd::OnTimer(nIDEvent);
}

void CClrBox::OnDestroy() 
{
	if (m_nTimer!=0)
		KillTimer(m_nTimer);
	
	CWnd::OnDestroy();
	// TODO: Add your message handler code here
}

void CClrBox::OnMButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bListBox==FALSE)
	{
		CRect rectThis;
		GetWindowRect(rectThis);
		m_wndColorListBox.MoveWindow 
			(rectThis.left+1, rectThis.bottom+1, LISTBOX_LEN,
			LISTBOX_HEI, FALSE);

		m_wndColorListBox.ShowWindow(SW_SHOW);
		m_bListBox = TRUE;
	}
	else
	{
		m_wndColorListBox.ShowWindow(SW_HIDE);
		m_bListBox = FALSE;
	}
	
	CWnd::OnMButtonDblClk(nFlags, point);
}

BOOL CClrBox::Repaint()
{
	Invalidate();
	m_wndColorListBox.Invalidate();
	return TRUE;
}
