// PreviewWnd.cpp : implementation file
//

#include "stdafx.h"
#include "obl4edit.h"
#include "PreviewWnd.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewWnd

CPreviewWnd::CPreviewWnd()
{
	m_pDoc = NULL;
}

CPreviewWnd::~CPreviewWnd()
{
}


BEGIN_MESSAGE_MAP(CPreviewWnd, CWnd)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CPreviewWnd)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_KILLFOCUS()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPreviewWnd message handlers

void CPreviewWnd::OnPaint() 
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

	if (pMainFrame->m_lpDDSPrimary==NULL)
		return;

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
		Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)
	{
		OutputDebugString("DDraw: Lock failed!\n");
		PostMessage (WM_PAINT, 0,0);
		//pMainFrame->ReleaseObjects();
		//PostQuitMessage(0);
		return; 
	}

	char *pDest = (char*)ddsurfdesc.lpSurface; 

	if (m_pDoc !=NULL) {
	
		CSS3Frame *pFrame = m_pDoc->m_oblData.Current();
		if (pFrame) {
			pMainFrame->FillSurface (0xff, pDest, rectSize.cx , rectSize.cy , ddsurfdesc.lPitch);
			pMainFrame->OutputOBL3 ( pFrame, 0, 0, rectSize.cx, rectSize.cy, FALSE, (UCHAR*)pDest, ddsurfdesc.lPitch);
		}
		else { // No Frame to display
			pMainFrame->FillSurface (0xff, pDest, rectSize.cx , rectSize.cy , ddsurfdesc.lPitch);
		}

	}
	
	if (pMainFrame->m_lpDDSBack2->
		Unlock(NULL))
	{
		OutputDebugString("DDraw: Unlock failed!\n");
		PostMessage (WM_PAINT, 0,0);
		//pMainFrame->ReleaseObjects();
		//PostQuitMessage(0);
		return ;
	}

   // Quickest way to get the destination RECT size and 
   // position.
   CRect rectDest; 
   GetClientRect(rectDest);

    // We have associate the clipper with this window
    if ( FAILED( pMainFrame->m_lpDDClipper->SetHWnd( 0, this->m_hWnd ) ) )
	{
         OutputDebugString(  "Couldn't set the hwnd to PreviewWnd.\n" );
		 return;
    }


   // Blt from the second surface unto the display surface
   // and fill our little view.
   if ( FAILED( pMainFrame->m_lpDDSPrimary->Blt( &rectView, 
	   pMainFrame->m_lpDDSBack2, &rectDest,
                    DDBLT_WAIT, NULL ) ) )
  
	{
		OutputDebugString("DDraw: Couldn't blt! [CPreviewWnd]\n");
		PostMessage (WM_PAINT, 0,0);
		return ;
    }

    //  Now we'll reassocite the clipper with the MainFrame
    if ( FAILED( pMainFrame->m_lpDDClipper->SetHWnd( 0, pMainFrame->m_hWnd ) ) )
	{
         Fail(  "Couldn't reset the hwnd.\n" );
		 return;
    }

	CPaintDC dc(this); // device context for painting
	
	// Do not call CView::OnPaint() for painting messages
}

BOOL CPreviewWnd::Fail (char *szMsg)
{
    OutputDebugString( szMsg );
    //AfxGetMainWnd()-> DestroyWindow();
    return FALSE;
}


CPreviewWnd::CPreviewWnd(CObl4editDoc *pDoc)
{
	m_pDoc = pDoc;
}


void CPreviewWnd::SetDocument(CObl4editDoc *pDoc)
{
	m_pDoc = pDoc;
}

void CPreviewWnd::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);
	AfxGetMainWnd() -> PostMessage (WM_COMMAND, IDM_SHOWPREVIEW, 0);

}

void CPreviewWnd::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
		
}

void CPreviewWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here

	CWinApp *pApp = AfxGetApp();
	CMainFrame * pMainWnd = (CMainFrame *) AfxGetMainWnd();

	if (pMainWnd->m_bSaveSettings) {

		CRect rect;
		GetWindowRect(rect);
		CSize size = rect.Size();

		pApp->WriteProfileInt("Settings", "nPreviewLen", size.cx);
		pApp->WriteProfileInt("Settings", "nPreviewHei", size.cy);
	
		pApp->WriteProfileInt("Settings", "nPreviewX", rect.left);
		pApp->WriteProfileInt("Settings", "nPreviewY", rect.top);
	}

}

void CPreviewWnd::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This function was added by the Pop-up Menu component

	/*
	CMenu menu;
	VERIFY(menu.LoadMenu(CG_IDR_POPUP_PREVIEW_WND));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
	*/
}

BOOL CPreviewWnd::PreTranslateMessage(MSG* pMsg)
{
	return CWnd::PreTranslateMessage(pMsg);
}
