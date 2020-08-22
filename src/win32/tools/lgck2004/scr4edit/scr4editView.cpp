// scr4editView.cpp : implementation of the CScr4editView class
//

#include "stdafx.h"
#include "scr4edit.h"

#include "scr4editDoc.h"
#include "scr4editView.h"
#include "DlgTagList.h"
#include "dlgeditlocal.h"
#include "shared.h"

#include "mainfrm.h"
#include "draw.h"
#include "resource.h"
#include "paldata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int			g_nBpp;
extern WORD			g_pal16[];
extern USER_24bpp	g_pal24[];
extern UINT			g_pal32[];

extern CPalData		g_pal;

/////////////////////////////////////////////////////////////////////////////
// CScr4editView

IMPLEMENT_DYNCREATE(CScr4editView, CView)

BEGIN_MESSAGE_MAP(CScr4editView, CView)
	//{{AFX_MSG_MAP(CScr4editView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_BRINGTOFRONT, OnBringtofront)
	ON_UPDATE_COMMAND_UI(IDM_BRINGTOFRONT, OnUpdateBringtofront)
	ON_COMMAND(IDM_SENDTOBACK, OnSendtoback)
	ON_UPDATE_COMMAND_UI(IDM_SENDTOBACK, OnUpdateSendtoback)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_SOUNDS, OnSounds)
	ON_UPDATE_COMMAND_UI(IDM_SOUNDS, OnUpdateSounds)
	ON_COMMAND(IDM_POINTS, OnPoints)
	ON_UPDATE_COMMAND_UI(IDM_POINTS, OnUpdatePoints)
	ON_COMMAND(IDM_USERDEFS, OnUserdefs)
	ON_UPDATE_COMMAND_UI(IDM_USERDEFS, OnUpdateUserdefs)
	ON_COMMAND(IDM_EDITLOCAL, OnEditlocal)
	ON_UPDATE_COMMAND_UI(IDM_EDITLOCAL, OnUpdateEditlocal)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(IDM_TAGSACTIONS, OnTagsactions)
	ON_UPDATE_COMMAND_UI(IDM_TAGSACTIONS, OnUpdateTagsactions)
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScr4editView construction/destruction

CScr4editView::CScr4editView()
{
	// TODO: add construction code here
	OutputDebugString("CScr4editView::CScr4editView()\n");

    m_nTimer = 0;
	m_bDragDrop = FALSE;
}

CScr4editView::~CScr4editView()
{
}

BOOL CScr4editView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CScr4editView drawing

void CScr4editView::OnDraw(CDC* pDC)
{
	CScr4editDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CScr4editView printing

BOOL CScr4editView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CScr4editView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CScr4editView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CScr4editView diagnostics

#ifdef _DEBUG
void CScr4editView::AssertValid() const
{
	CView::AssertValid();
}

void CScr4editView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CScr4editDoc* CScr4editView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScr4editDoc)));
	return (CScr4editDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScr4editView message handlers

BOOL CScr4editView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	OutputDebugString("CScr4editView::OnCreate() enter\n");
    
    // TODO: Add your specialized code here and/or call the base class
	CString strWndClass = AfxRegisterWndClass (
        CS_DBLCLKS | CS_OWNDC,                  // Class style
        AfxGetApp()->LoadStandardCursor (IDC_ARROW),   // Class cursor
        NULL,//(HBRUSH) (COLOR_3DFACE ),               // Class background brush
        NULL            // Class icon
        );

	OutputDebugString("CScr4editView::OnCreate() exit\n");
    
	return CWnd::Create(strWndClass, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CScr4editView::OnPaint() 
{
	// TODO: Add your message handler code here

	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd());

	BOOL bLocked = FALSE;

	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	pDoc->UpdateTitle();

   // Quickest way to get the destination RECT size and 
   // position.
	CRect rectSrc; 
	GetClientRect (rectSrc);
	rectSrc.right = rectSrc.right + (4 - rectSrc.right %4);
	CSize sizeSrc = rectSrc.Size();

	CRect rectDest = rectSrc;
	ClientToScreen (rectDest);

	DDSURFACEDESC ddsurfdesc;
	ZeroMemory (&ddsurfdesc, sizeof(DDSURFACEDESC));
	ddsurfdesc.dwSize = sizeof(DDSURFACEDESC);
	ddsurfdesc.dwFlags = DDSD_ALL;

	if (sizeSrc.cx < 4 || sizeSrc.cy <4 ) {
		CPaintDC dc(this);
		return;
	}

	// Check if primary display surface is lost
    if ( pMainFrame->m_lpDDSPrimary==0 
		|| FAILED( pMainFrame->m_lpDDSPrimary->IsLost() ) )
	{
        if ( !pMainFrame->RestoreAll() ) 
		{
            pMainFrame->Fail( "DDraw: Couldn't restore surfaces.\n" );
			//pMainFrame->ReleaseObjects();
			return;
        }
    }

	// Draw the screen if a screen there is
	if (game.m_nScripts !=0)
	{
		// Draw custom BkColod and the entire script onto the screen
		CScriptArray & script = * game[game.m_nCurrScript];

		FillSurface (script.m_nBkColor);

		// Lock surface
		if (pMainFrame->m_lpDDSBack->
			Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)	{
			OutputDebugString("DDraw: Lock failed!\n");
			//pMainFrame->ReleaseObjects();
			Invalidate();
			return ;
		}

		bLocked = TRUE;
		DrawScript (&script, script.m_nMX, script.m_nMY, ddsurfdesc.lpSurface, sizeSrc.cx, sizeSrc.cy, ddsurfdesc.lPitch);
	}
	else
	{
		// Fill surface with a nice a white shadow
		FillSurface(0xff);
	}

	// Draw the selection rect if applicable
	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0) &&
		(game[game.m_nCurrScript]->m_bSelection))	{

		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry & entry = script[script.m_nCurrEntry];
		COBL3Filter & filter = 
			* game.m_arrOBL3 [entry.m_nFrameSet];
		CSS3Frame * pFrame = filter [entry.m_nFrameNo];

		if ((entry.m_nX - script.m_nMX>=0) &&
			(entry.m_nY - script.m_nMY>=0) &&
			(entry.m_nX - script.m_nMX<sizeSrc.cx) &&
			(entry.m_nY - script.m_nMY<sizeSrc.cy)) 
		{
	
			DrawRect ( CPoint (entry.m_nX - script.m_nMX,
							entry.m_nY - script.m_nMY),
					CSize (pFrame->m_nLen, pFrame->m_nHei),
					sizeSrc.cx, sizeSrc.cy,
					0x1e, (char*) ddsurfdesc.lpSurface,
					ddsurfdesc.lPitch);
		}
	}

	// unlock surface
	if (bLocked && pMainFrame->m_lpDDSBack->Unlock(NULL))	{
		OutputDebugString("DDraw: Unlock failed!\n");
		//pMainFrame->ReleaseObjects();
		bLocked = FALSE;
		return ;
	}

	// Gather the original coordonates again - when
	// blitting we'll forget about alignment considerations
	// (i.e. performance is not an issue)
	GetClientRect (rectSrc);
	rectDest = rectSrc;
	ClientToScreen (rectDest);

	// Blt from the second surface unto the display surface
	// and fill our little view.
	if ( FAILED( pMainFrame->m_lpDDSPrimary->Blt( &rectDest, 
	   pMainFrame->m_lpDDSBack, &rectSrc,
                    DDBLT_WAIT, NULL ) ) )	{	
#ifdef _DEBUG
		OutputDebugString("DDraw: Couldn't blt!\n");
#endif
		PostMessage(WM_PAINT);
		return ;
    }	

	CPaintDC dc(this); // device context for painting

	// Do not call CView::OnPaint() for painting messages
}

void CScr4editView::OutputOBL3 (CSS3Frame * pFrame, int x, int y, int maxX, int maxY, BOOL bClear, UCHAR *pDest, int nPitch )
{

	BOOL bUnlock = !pDest;

	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

    if ( FAILED( pMainFrame->m_lpDDSPrimary->IsLost() ) )	{
        if ( !pMainFrame->RestoreAll() ) 		{
			pMainFrame->Fail( "DDraw: Couldn't restore surfaces.\n" );
            return ;
        }
    }

	// Lock surface
	
	DDSURFACEDESC ddsurfdesc;
	ddsurfdesc.dwSize = sizeof(DDSURFACEDESC);
	ddsurfdesc.dwFlags = DDSD_ALL;

	if (pDest==NULL) {
		if (pMainFrame->m_lpDDSBack->
			Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)	{
			OutputDebugString("DDraw: Lock failed!\n");
			//pMainFrame->ReleaseObjects();
			//PostQuitMessage(0);
			return ;
		}
	}
	else {
		ddsurfdesc.lpSurface = pDest; // DO NOT LOCK BY
		ddsurfdesc.lPitch = nPitch;   // USE OUTSIDE PTR IF PROVIDED
	}
	 
	if (pFrame!=NULL)	
	{
		UINT s = (UINT)pFrame->Point(0,0);
		UINT d = (UINT)ddsurfdesc.lpSurface;

		int nPitch=  ddsurfdesc.lPitch; 

		int nCols = min (x + pFrame->m_nLen, maxX) -x;
		int nRows = min (y + pFrame->m_nHei, maxY) -y;

		int ld = -nCols + nPitch;
		int ls = -nCols + pFrame->m_nLen;	

		BYTE nTriggerKey = (bClear & 1) * TRIGGER_HIDDEN;

		if (nCols>0 && nRows>0 && x>=0 && y>=0)
		{
			switch (g_nBpp)
			{
				case 8:
					Draw8bpp (nRows, nCols, ld, ls, s, d, nTriggerKey);
				break;
	
				case 16:
					Draw16bpp (nRows, nCols, nPitch, pFrame->m_nLen, s, d, nTriggerKey);
				break;

				case 24:
					Draw24bpp (nRows, nCols, nPitch, pFrame->m_nLen, s, d, nTriggerKey);
				break;

				case 32:
					Draw32bpp (nRows, nCols, nPitch, pFrame->m_nLen, s, d, nTriggerKey);
				break;		
			}
		}
	}

	// Unlock surface
	if ((pDest == NULL) && bUnlock) {
		if (pMainFrame->m_lpDDSBack->
			Unlock(NULL))	{
			OutputDebugString("DDraw: Unlock failed!\n");
			//pMainFrame->ReleaseObjects();
			//PostQuitMessage(0);
			return ;
		}
	}  
}

void CScr4editView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

/*
	if (nFlags == MK_LBUTTON)
	{
		CScr4editDoc *pDoc = GetDocument();
		CGameFile3 & game = pDoc->m_game3; 

		if ((game.m_nScripts !=0) &&
			(game[game.m_nCurrScript]->GetSize()!=0))
		{
			CScriptArray & script = * game[game.m_nCurrScript];
			int nTarget = 
				game.WhoIs (script, script.m_nMX + point.x, script.m_nMY + point.y);

			if (nTarget !=-1)	{
				if (script[nTarget].m_nX < script.m_nMX)
					script.m_nMX = script[nTarget].m_nX;

				if (script[nTarget].m_nY < script.m_nMY)
					script.m_nMY = script[nTarget].m_nY;

				script.m_nCurrEntry = nTarget;
				script.m_bSelection = TRUE;

				Invalidate();
			}
			else {
				script.m_bSelection = FALSE;
				Invalidate();
			}
		}
	}
*/
	CView::OnLButtonDown(nFlags, point);
}

void CScr4editView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnMouseMove(nFlags, point);
}

//WM_RBUTTONDOWN

void CScr4editView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
/*	if (nFlags == MK_RBUTTON)
	{
		CScr4editDoc *pDoc = GetDocument();
		CGameFile3 & game = pDoc->m_game3; 

		if ((game.m_nScripts !=0) &&
			(game[game.m_nCurrScript]->GetSize()!=0))
		{
			CScriptArray & script = * game[game.m_nCurrScript];
			int nTarget = 
				game.WhoIs (script, script.m_nMX + point.x, script.m_nMY + point.y);

			if (nTarget !=-1)			{
				script.m_nCurrEntry = nTarget;
				script.RemoveAt(nTarget);
				script.m_bSelection = FALSE;
				pDoc->SetModifiedFlag (TRUE);
				Invalidate();
			}
			else {
				script.m_bSelection = FALSE;
				Invalidate();
			}
		}
	}
*/	
	CView::OnRButtonDown(nFlags, point);
}

void CScr4editView::OnBringtofront() 
{
	// TODO: Add your command handler code here
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	if ( (game.m_nScripts !=0) &&
			(game[game.m_nCurrScript]->GetSize()!=0) &&
			(game[game.m_nCurrScript]->m_bSelection))
	{
		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry entry = script[script.m_nCurrEntry];
		script.m_bSelection = FALSE;

		script.Add (entry);
		script.RemoveAt (script.m_nCurrEntry);
		script.m_nCurrEntry = script.GetSize()-1;
		
		script.m_bSelection = TRUE;

		//TODO: Check the following line
		ZeroMemory (&entry, sizeof (CScriptEntry));
		pDoc->SetModifiedFlag (TRUE);
		Invalidate();
	}
}

void CScr4editView::OnUpdateBringtofront(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	pCmdUI->Enable ( (game.m_nScripts !=0) &&
			(game[game.m_nCurrScript]->GetSize()!=0) &&
			(game[game.m_nCurrScript]->m_bSelection));
}

void CScr4editView::OnSendtoback() 
{
	// TODO: Add your command handler code here
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	if ( (game.m_nScripts !=0) &&
			(game[game.m_nCurrScript]->GetSize()!=0) &&
			(game[game.m_nCurrScript]->m_bSelection))
	{
		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry entry = script[script.m_nCurrEntry];
		script.m_bSelection = FALSE;

		script.InsertAt (0, entry);
		script.RemoveAt (script.m_nCurrEntry+1);
		script.m_nCurrEntry = 0;
		
		script.m_bSelection = TRUE;

		// TODO: Check the fallowing line later
		ZeroMemory (&entry, sizeof (CScriptEntry));
		pDoc->SetModifiedFlag (TRUE);
		Invalidate();
	}
}

void CScr4editView::OnUpdateSendtoback(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	pCmdUI->Enable ( (game.m_nScripts !=0) &&
			(game[game.m_nCurrScript]->GetSize()!=0) &&
			(game[game.m_nCurrScript]->m_bSelection));
}

void CScr4editView::DrawRect (CPoint & point, CSize & size, int nLen, int nHei, UCHAR nColor,  char *pDest, int nPitch)
{

	UCHAR * d;
	int nCols, nRows;
	int ld;

	int _Ox;
	int _Oy;
	int _x;
	int _y;

	_x = (int)point.x ;
	_y = (int)point.y;

	int nPixLen = g_nBpp /8;

	if ( (_x + (int) size.cx <= 0) ||
			 (_x >= nLen) || 
			(_y + (int) size.cy <= 0) || 
			(_y >= nHei) ) {}
	else {

		if (_x<0) {
			_Ox = -_x;
			_x =0;
			nCols = (int) size.cx - _Ox;
		}
		else {
			_Ox = 0;
			nCols = min ( (int)size.cx,	nLen - _x);
		}

		if (_y<0) {
			_Oy = -_y;
			_y =0;
			nRows = (int) size.cy - _Oy;
		}
		else {
			_Oy = 0;
			nRows = min ( (int) size.cy, nHei - _y);
		}

		ld = -nCols + nPitch;
		d = (UCHAR *) pDest + _x*nPixLen + _y * nPitch;

	}

	int i;

	if ( nCols<0 || nRows<0 || 
		nCols> (int) size.cx || nRows > (int) size.cy) 
		return;

	for (i=0; i<nCols; i++)	{
		if (_y == (int) point.y)
			PutDot(d+i*nPixLen,nColor);

		if ((_y+ nRows) == ((int)point.y + (int) size.cy))
			PutDot(d+ nRows * nPitch +i*nPixLen, nColor);
	}

	for (i=0; i<nRows; i++)	{
		if (_x == (int) point.x)
			PutDot(d +i*nPitch, nColor);

		if ((_x + nCols) == ( (int) point.x + (int) size.cx))
			PutDot(d+ nCols*nPixLen + i*nPitch, nColor);
	}
}

void CScr4editView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	//OutputDebugString("Tic tac\n");

	// Autoscroll with mousemove

	POINT pointCursor;
	if (GetCursorPos(&pointCursor) 
		&& m_bDragDrop 
		&& game.m_nScripts!=0 
		&& (game[game.m_nCurrScript]->GetSize()!=0))
	{
		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry & entry = script[script.m_nCurrEntry];

		int nStepSize;
		if (script.m_bSelection)
		{
			nStepSize=MOVESTEP;
		}
		else
		{
			nStepSize=4*MOVESTEP;
		}

		CRect rectView;
		GetClientRect(&rectView);
		ClientToScreen (&rectView);

		if (pointCursor.x== rectView.left)
		{
			if (script.m_nMX>=nStepSize)
			{

				script.m_nMX = script.m_nMX - nStepSize;
				
				if (script.m_bSelection)
					entry.MoveBy(-nStepSize,0);
				
				Invalidate();
			}
			else
			{
				script.m_nMX = 0;

				if (script.m_bSelection)		
					entry.m_nX =0;

				Invalidate();
			}
		}

		if (pointCursor.x== rectView.right-1)
		{
			if (script.m_nMX<8*256)
			{
				script.m_nMX = script.m_nMX + nStepSize;

				if (script.m_bSelection)
					entry.MoveBy(+nStepSize,0);

				Invalidate();
			}
		}

		if (pointCursor.y== rectView.top)
		{
			if (script.m_nMY>=nStepSize)
			{
				script.m_nMY = script.m_nMY - nStepSize;

				if (script.m_bSelection)
					entry.MoveBy(0,-nStepSize);

				Invalidate();
			}
			else
			{
				script.m_nMY =0;

				if (script.m_bSelection)
					entry.m_nY =0;

				Invalidate();
			}
		}

		if (pointCursor.y== rectView.bottom-1)
		{
			if (script.m_nMY<8*256)
			{
				if (script.m_bSelection)
					entry.MoveBy(0,+nStepSize);

				script.m_nMY = script.m_nMY + nStepSize;

				Invalidate();
			}
		}
	}
  
	// Draw Rectangle arround target...................

	static UCHAR nColor = 0;
	int nPixLen = g_nBpp/8;

	CView::OnTimer(nIDEvent);

	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );
	if (GetFocus ()!= (CWnd*) pMainFrame 
		&& GetFocus () != (CWnd*) this )
		return;

   // Quickest way to get the destination RECT size and 
   // position.
	CRect rectSrc; 
	GetClientRect (rectSrc);
	CSize sizeSrc = rectSrc.Size();

	ClientToScreen (rectSrc);

	DDSURFACEDESC ddsurfdesc;
	ZeroMemory (&ddsurfdesc, sizeof(DDSURFACEDESC));
	ddsurfdesc.dwSize = sizeof(DDSURFACEDESC);
	ddsurfdesc.dwFlags = DDSD_ALL;

	if (sizeSrc.cx < 4 || sizeSrc.cy <4 ) {
		return;
	}

	if ((game.m_nScripts ==0) ||
		(game[game.m_nCurrScript]->GetSize()==0) ||
		(game[game.m_nCurrScript]->m_bSelection==FALSE))	
		return;

	// Is surface lost ???
    if ( FAILED( pMainFrame->m_lpDDSPrimary->IsLost() ) )
	{
        if ( !pMainFrame->RestoreAll() ) 
		{
            pMainFrame->Fail( "DDraw: Couldn't restore surfaces.\n" );
			//pMainFrame->ReleaseObjects();
			//PostQuitMessage(0);
			return;
        }
    }

	// Lock surface
	if (pMainFrame->m_lpDDSPrimary->
			Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)	{
			OutputDebugString("DDraw: Lock failed!\n");
			//pMainFrame->ReleaseObjects();
			//PostQuitMessage(0);
			return ;
	}

	// Draw the selection rect if applicable

	CScriptArray & script = * game[game.m_nCurrScript];
	CScriptEntry & entry = script[script.m_nCurrEntry];
	COBL3Filter & filter = 
		* game.m_arrOBL3 [entry.m_nFrameSet];
	CSS3Frame * pFrame = filter [entry.m_nFrameNo];

	nColor ++;
	if ((entry.m_nX - script.m_nMX>=0) &&
		(entry.m_nY - script.m_nMY>=0) &&
		(entry.m_nX - script.m_nMX<sizeSrc.cx) &&
			(entry.m_nY - script.m_nMY<sizeSrc.cy)) 
	{

		DrawRect ( CPoint (entry.m_nX - script.m_nMX,
						entry.m_nY - script.m_nMY),
				CSize (pFrame->m_nLen, pFrame->m_nHei),
				sizeSrc.cx, sizeSrc.cy,
				(nColor & 0x7) + 0x18, 
				(char*) ddsurfdesc.lpSurface + rectSrc.left*nPixLen +
				rectSrc.top * ddsurfdesc.lPitch,
				ddsurfdesc.lPitch);
	}

	// unlock surface
	if (pMainFrame->m_lpDDSPrimary->Unlock(NULL))	{
		OutputDebugString("DDraw: Unlock failed!\n");
		//pMainFrame->ReleaseObjects();
		//PostQuitMessage(0);
		return ;
	}
}

int CScr4editView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_nTimer = SetTimer (0x092290, 50/2, NULL);		

	if (m_nTimer==0)
	{
		OutputDebugString("Warning: NoTimer\n");
	}
	else
	{
		OutputDebugString("Timer set\n");
	}

	return 0;
}

void CScr4editView::OnDestroy() 
{
	CView::OnDestroy();
	if (m_nTimer)
	{
		KillTimer (m_nTimer);
	}
	
	// TODO: Add your message handler code here
}

void CScr4editView::OnSounds() 
{
	// TODO: Add your command handler code here
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	CDlgTagList dlg;
	dlg.m_pArray = & game.m_arrSoundData;
	dlg.SetTitle ("Sound tags list");
	dlg.DoModal();
}

void CScr4editView::OnUpdateSounds(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editView::OnPoints() 
{
	// TODO: Add your command handler code here
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	CDlgTagList dlg;
	dlg.m_pArray = & game.m_arrPoints;
	dlg.SetTitle ("Point tags list");
	dlg.DoModal();
}

void CScr4editView::OnUpdatePoints(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editView::OnUserdefs() 
{
	// TODO: Add your command handler code here
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	CDlgTagList dlg;
	dlg.m_pArray = & game.m_arrUserDefs;
	dlg.SetTitle ("User defined constants list");
	dlg.DoModal();
}

void CScr4editView::OnUpdateUserdefs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

#define IsTrue(_exp) ((_exp)!=0)

void CScr4editView::OnEditlocal() 
{
	// TODO: Add your command handler code here
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 
	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)		
		&& game[game.m_nCurrScript]->m_bSelection)	{

		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry & entry = script[script.m_nCurrEntry];

		CDlgEditLocal dlg;
		dlg.m_nSubClass = entry.m_nSubClass;
		dlg.m_nTriggerKey = entry.m_nTriggerKey & 15;

		dlg.m_bC80 = IsTrue(entry.m_nTriggerKey & 0x80);
		dlg.m_bC40 = IsTrue(entry.m_nTriggerKey & 0x40);
		dlg.m_bC20 = IsTrue(entry.m_nTriggerKey & 0x20);
		dlg.m_bC10 = IsTrue(entry.m_nTriggerKey & 0x10);

		CProto & proto = game.m_arrProto[entry.m_nProto];
		dlg.m_strClass = game.m_arrClasses.StringFor(proto.m_nClass);
		dlg.m_strObject = proto.m_szName;
		dlg.m_pDoc = GetDocument();
		dlg.m_nProto = entry.m_nProto;
		dlg.m_pEntry = &entry;

		if (dlg.DoModal()==IDOK)
		{
			int nNewTriggerKey = dlg.m_nTriggerKey +
				dlg.m_bC80 * 0x80 +
				dlg.m_bC40 * 0x40 +
				dlg.m_bC20 * 0x20 +
				dlg.m_bC10 * 0x10 ;

			int nNewSubClass = dlg.m_nSubClass;

			if (( nNewTriggerKey != entry.m_nTriggerKey)
				|| nNewSubClass!= entry.m_nSubClass)
			{
				entry.m_nSubClass = nNewSubClass;
				entry.m_nTriggerKey = nNewTriggerKey;

				pDoc->SetModifiedFlag (TRUE);
			}

			Invalidate();
		}
	}		
}

void CScr4editView::OnUpdateEditlocal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 
	pCmdUI->Enable ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)		
		&& game[game.m_nCurrScript]->m_bSelection);
}

void CScr4editView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OnEditlocal();	
	CView::OnLButtonDblClk(nFlags, point);
}

void CScr4editView::OnTagsactions() 
{
	// TODO: Add your command handler code here
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	CDlgTagList dlg;
	dlg.m_pArray = & game.m_arrActions;
	dlg.SetTitle ("Action tags list");
	dlg.DoModal();
	
}

void CScr4editView::OnUpdateTagsactions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

BOOL CScr4editView::FillSurface(UCHAR nColor)
{
	CMainFrame *pMainFrame = 
		((CMainFrame*) AfxGetMainWnd() );

	// Erase the background
	DDBLTFX     ddbltfx;
	ddbltfx.dwSize = sizeof( ddbltfx );
	ddbltfx.dwFillColor = nColor; 

	switch (g_nBpp)
	{
		case 8:
			ddbltfx.dwFillColor = nColor; 
		break;

		case 16:
			ddbltfx.dwFillColor = g_pal16[nColor]; 
		break;

		case 24:
			memcpy(&ddbltfx.dwFillColor,
				&g_pal24[nColor],3); 
		break;

		case 32:
			ddbltfx.dwFillColor = g_pal32[nColor]; 
		break;
	}

	if ( !pMainFrame->m_lpDDSBack || FAILED( pMainFrame->m_lpDDSBack->Blt( NULL, 
			NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx ) ) )	
	{	
		OutputDebugString("DDraw: ColorFill failed\n");
		return FALSE;
	}
	
	return TRUE;
}

void CScr4editView::DrawScript (CScriptArray *pSA, int nMX, int nMY, void *pDest, int nLen, int nHei, int nPitch)
{
	DWORD s;
	DWORD d;
	int nCols, nRows;
	int ld, ls;

	int i;

	int _Ox;
	int _Oy;
	int _x;
	int _y;

	CScriptArray & script = * pSA;
	int nEntries = pSA->GetSize(); 
	CSS3Frame *pFrame;
	CGameFile3 & game = GetDocument()->m_game3;
	int nPixLen = g_nBpp/8;

	for (i=0; i<nEntries; i++)
	{
		CScriptEntry & entry = script[i] ; 
		COBL3Filter & filter = * game.m_arrOBL3 [entry.m_nFrameSet];
		pFrame = filter[entry.m_nFrameNo];

		_x = entry.m_nX - nMX;
		_y = entry.m_nY - nMY;

		if ( (_x + pFrame->m_nLen <= 0) ||
			 (_x >= nLen) || 
			(_y + pFrame->m_nHei <= 0) || 
			(_y >= nHei) ) {}
		else {

			if (_x<0) {
				_Ox = -_x;
				_x =0;
				nCols = pFrame->m_nLen - _Ox;
			}
			else {
				_Ox = 0;
				nCols = min (pFrame->m_nLen,
					nLen - _x);
			}

			if (_y<0) {
				_Oy = -_y;
				_y =0;
				nRows = pFrame->m_nHei - _Oy;
			}
			else {
				_Oy = 0;
				nRows = min (pFrame->m_nHei,
					nHei - _y);
			}

			ld = -nCols + nPitch;
			ls = -nCols + pFrame->m_nLen;

			s = (DWORD) pFrame->m_pBitmap + _Ox 
					+ _Oy  * pFrame->m_nLen;
			d = (DWORD) pDest + _x*nPixLen + _y * nPitch;

			switch (g_nBpp)
			{
				case 8:
					Draw8bpp (nRows, nCols, ld, ls, s, d, entry.m_nTriggerKey);
				break;
	
				case 16:
					Draw16bpp (nRows, nCols, nPitch, pFrame->m_nLen, s, d, entry.m_nTriggerKey);
				break;

				case 24:
					Draw24bpp (nRows, nCols, nPitch, pFrame->m_nLen, s, d, entry.m_nTriggerKey);
				break;

				case 32:
					Draw32bpp (nRows, nCols, nPitch, pFrame->m_nLen, s, d, entry.m_nTriggerKey);
				break;
			
			}
		}
	}
}

void CScr4editView::Draw8bpp (int nRows, int nCols, int ld, int ls, DWORD s, DWORD d, BYTE nTriggerKey)
{
	BYTE bHidden = ((nTriggerKey & TRIGGER_HIDDEN) != 0);

		_asm {
			mov esi,s
			mov edi,d

			mov bl, bHidden
			xor bh,bh

			mov edx, nRows
loop2:		mov ecx, nCols
loop1:		mov eax, [esi]
			or eax, eax
			je zero1

			// byte 0-1

			or bl,bl
			je NotHidden

			or bh,bh
			jne zero2

NotHidden:
			or ax,ax
			je zero2

			or al,al
			je zero3

			or ah,ah
			je zero4

			mov [edi], ax
			jmp zero2

zero3:		or ah,ah
			je zero2
			mov [edi+1],ah
			jmp zero2

zero4:		mov [edi],al

zero2:
			inc edi
			inc edi
			shr eax,16

			// byte 2-3
			
			or bl,bl
			je NotHidden2

			or bh,bh
			je zero2a

NotHidden2:

			or ax,ax
			je zero2a

			or al,al
			je zero3a

			or ah,ah
			je zero4a

			mov [edi], ax
			jmp zero2a

zero3a:		or ah,ah
			je zero2a
			mov [edi+1],ah
			jmp zero2a

zero4a:		mov [edi],al

zero2a:
			dec edi
			dec edi

zero1:
			inc edi
			inc edi
			inc edi
			inc edi

			inc esi
			inc esi
			inc esi
			inc esi

			dec ecx
			dec ecx
			dec ecx
			dec ecx

			or ecx,ecx
			jne loop1
			
			add edi, ld
			add esi, ls

			xor bh,bl
			
			dec edx
			or edx,edx
			jne loop2

			} // asm 8bpp
}

void CScr4editView::Draw16bpp (int nRows, int nCols, int ld, int ls, DWORD s, DWORD d, BYTE nTriggerKey)
{
	UINT nBase = (UINT) g_pal16;
	BYTE bHidden = ((nTriggerKey & TRIGGER_HIDDEN) != 0);

	int y;
	int x;

	if (!nRows || !nCols)
		return;

	_asm
	{
		mov ecx, nBase
		
		mov dl,bHidden
		xor dh,dh
		
		mov eax, nRows
		mov y, eax

		mov esi, s
		mov edi, d

loop2:
		mov eax, nCols
		shr eax,2
		mov x, eax

loop1:
		mov eax, [esi]
		or eax,eax
		je zero

		// doing pixel 0 & 1
		or ax, ax
		je zero1

		or dl,dl
		je nothidden1

		or dh,dh
		je zero1

nothidden1:

		or al, al
		je zero2

		// pixel 0
		xor ebx,ebx
		mov bl, al
		mov bx, word ptr [ebx*2+ecx]

		cmp al,ah
		jne notsame1

		mov ax,bx
		shl ebx, 16
		mov bx, ax
		mov [edi], ebx
		jmp zero1


notsame1:
		mov [edi], bx

zero2:
		or ah, ah
		je zero1

		// pixel 1
		xor ebx,ebx
		mov bl, ah
		mov bx, word ptr [ebx*2+ecx]
		mov [edi+2], bx

zero1:
		shr eax, 16
		
		// doing pixel 2 & 3	
		or ax, ax
		je zero

		or dl,dl
		je nothidden2

		or dh,dh
		jne zero
nothidden2:
		
		or al, al
		je zero3

		// pixel 2
		xor ebx,ebx
		mov bl, al
		mov bx, word ptr [ebx*2+ecx]
		cmp al,ah
		jne notsame2

		mov ax,bx
		shl ebx, 16
		mov bx, ax
		mov [edi+4], ebx
		jmp zero

notsame2:
		mov [edi+4], bx

zero3:
		or ah, ah
		je zero

		// pixel 3
		xor ebx,ebx
		mov bl, ah
		mov bx, word ptr [ebx*2+ecx]
		mov [edi+6], bx

zero:
		mov eax, 4
		add esi, eax
		add eax, eax
		add edi, eax

		dec x
		cmp x, 0
		jne loop1

		mov edi,d
		add edi,ld
		mov d, edi

		mov esi,s
		add esi,ls
		mov s, esi

		xor dh,dl

		dec y
		cmp y,0
		jne loop2
	}

/*
  // the original C++ version
  // versus the new optimized version above
  // no speed difference noticed

	UCHAR *ptrS	= (UCHAR*) s;
	WORD *ptrD = (WORD*) d;

	int x;
	int y;

	if (nTriggerKey & TRIGGER_HIDDEN)
	{
		for (y=0; y<nRows; y++)
		{
			for (x=0; x<nCols;x++)
			{
				if (*ptrS)
				{
					if (y%2)
					{
						if ((x%4)<2)
						{
							*ptrD = g_pal16[*ptrS];
						}
						else
						{
						}
					}
					else
					{
						if ((x%4)<2)
						{
						}
						else
						{
							*ptrD = g_pal16[*ptrS];
						}
					}
				}

				ptrD++;
				ptrS++;
			}

			d = d + ld;
			s = s + ls;

			ptrS = (UCHAR*) s;
			ptrD = (WORD*) d;
		}
	}
	else
	{
		for (y=0; y<nRows; y++)
		{
			for (x=0; x<nCols;x=x+4)
			{
				if (*ptrS)
				{
					*ptrD = g_pal16[*ptrS];
				}

				ptrD++;
				ptrS++;

				if (*ptrS)
				{
					*ptrD = g_pal16[*ptrS];
				}

				ptrD++;
				ptrS++;

				if (*ptrS)
				{
					*ptrD = g_pal16[*ptrS];
				}

				ptrD++;
				ptrS++;

				if (*ptrS)
				{
					*ptrD = g_pal16[*ptrS];
				}

				ptrD++;
				ptrS++;
				
			}

			d = d + ld;
			s = s + ls;

			ptrS = (UCHAR*) s;
			ptrD = (WORD*) d;
		}
	}
	*/
}

void CScr4editView::Draw24bpp (int nRows, int nCols, int ld, int ls, DWORD s, DWORD d, BYTE nTriggerKey)
{
	UCHAR *ptrS	= (UCHAR*) s;
	USER_24bpp *ptrD = (USER_24bpp*) d;

	int x;
	int y;

	if (nTriggerKey & TRIGGER_HIDDEN)
	{
		for (y=0; y<nRows; y++)
		{
			for (x=0; x<nCols;x++)
			{
				if (*ptrS)
				{
					if (y%2)
					{
						if ((x%4)<2)
						{
							*ptrD = g_pal24[*ptrS];
						}
						else
						{
						}
					}
					else
					{
						if ((x%4)<2)
						{
						}
						else
						{
							*ptrD = g_pal24[*ptrS];
						}
					}
				}

				ptrD++;
				ptrS++;
			}

			d = d + ld;
			s = s + ls;

			ptrS = (UCHAR*) s;
			ptrD = (USER_24bpp*) d;
		}
	}
	else
	{
		for (y=0; y<nRows; y++)
		{
			for (x=0; x<nCols;x++)
			{
				if (*ptrS)
				{
					*ptrD = g_pal24[*ptrS];
				}

				ptrD++;
				ptrS++;
			}

			d = d + ld;
			s = s + ls;

			ptrS = (UCHAR*) s;
			ptrD = (USER_24bpp*) d;
		}
	}
}

void CScr4editView::Draw32bpp (int nRows, int nCols, int ld, int ls, DWORD s, DWORD d, BYTE nTriggerKey)
{
	UCHAR *ptrS	= (UCHAR*) s;
	UINT *ptrD = (UINT*) d;

	int x;
	int y;

	if (nTriggerKey & TRIGGER_HIDDEN)
	{
		for (y=0; y<nRows; y++)
		{
			for (x=0; x<nCols;x++)
			{
				if (*ptrS)
				{
					if (y%2)
					{
						if ((x%4)<2)
						{
							*ptrD = g_pal32[*ptrS];
						}
						else
						{
						}
					}
					else
					{
						if ((x%4)<2)
						{
						}
						else
						{
							*ptrD = g_pal32[*ptrS];
						}
					}
				}

				ptrD++;
				ptrS++;
			}

			d = d + ld;
			s = s + ls;

			ptrS = (UCHAR*) s;
			ptrD = (UINT*) d;
		}
	}
	else
	{
		for (y=0; y<nRows; y++)
		{
			for (x=0; x<nCols;x++)
			{
				if (*ptrS)
				{
					*ptrD = g_pal32[*ptrS];
				}

				ptrD++;
				ptrS++;
			}

			d = d + ld;
			s = s + ls;

			ptrS = (UCHAR*) s;
			ptrD = (UINT*) d;
		}
	}
}

void CScr4editView::PutDot (void *pDest, int nColor)
{
	/*
	union 
	{
		UCHAR *p8;
		WORD *p16;
		USER_24bpp *p24;
		UINT *p32;
	};
	*/

	UCHAR *p8 = (UCHAR *) pDest;
	WORD * p16 = (WORD *) pDest;
	USER_24bpp * p24 = (USER_24bpp *) pDest;
	UINT * p32 = (UINT *) pDest;

	switch (g_nBpp)
	{
		case 8:
			*p8 = nColor;
		break;

		case 16:
			*p16 = g_pal16[nColor];
		break;

		case 24:
			*p24 = g_pal24[nColor];
		break;
	
		case 32:
			*p32 = g_pal32[nColor];
		break;
	}
}

void CScr4editView::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This function was added by the Pop-up Menu component
	BOOL bItemPopUp = FALSE;

	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 
	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0))
	{
		CScriptArray & script = * game[game.m_nCurrScript];
		bItemPopUp = script.m_bSelection ;
	}
			
	CMenu menu;
	
	if (bItemPopUp)
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_SCR4EDIT_VIEW));
	else
		VERIFY(menu.LoadMenu(IDR_SCRIPT_POPUP));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, pWndPopupOwner);
}

BOOL CScr4editView::PreTranslateMessage(MSG* pMsg)
{
	// CG: This block was added by the Pop-up Menu component
	CScr4editDoc *pDoc = GetDocument();
	CGameFile3 & game = pDoc->m_game3; 

	CPoint point;
	point.x = LOWORD(pMsg->lParam);  // horizontal position of cursor 
	point.y = HIWORD(pMsg->lParam);  // vertical 

	if ( ( (pMsg->message == WM_RBUTTONDOWN) ||
		  (pMsg->message == WM_LBUTTONDOWN) ) &&
		(game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0))
	{
		CScriptArray & script = * game[game.m_nCurrScript];
		int nTarget = 
				game.WhoIs (script, script.m_nMX + point.x, script.m_nMY + point.y);

		if (nTarget !=-1)			{
			script.m_nCurrEntry = nTarget;
			script.m_bSelection = TRUE;
			Invalidate();
		}
		else {
			script.m_bSelection = FALSE;
			Invalidate();
		}
	}
	
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		m_bDragDrop = TRUE;

		CRect rectView;
		GetClientRect(&rectView);
		ClientToScreen (&rectView);

		ClipCursor(&rectView);
	}

	if ((pMsg->message == WM_LBUTTONUP ) ||
		(pMsg->message == WM_RBUTTONDOWN ))
	{
		m_bDragDrop = FALSE;
		
		ClipCursor(NULL);

		GetDocument()->SetModifiedFlag (TRUE);
	}

	if ( (m_bDragDrop) &&
		(pMsg->message == WM_MOUSEMOVE) &&
		(game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0))
	{

		CScriptArray & script = * game[game.m_nCurrScript];

		if (script.m_bSelection)
		{
			CScriptEntry & entry = script[script.m_nCurrEntry];
			entry.m_nX = point.x - (point.x % 8) + script.m_nMX;
			entry.m_nY = point.y - (point.y % 8) + script.m_nMY;
			Invalidate();
		}
	}

	// Shift+F10: show pop-up menu.
	if ((((pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN) && // If we hit a key and
			(pMsg->wParam == VK_F10) && (GetKeyState(VK_SHIFT) & ~1)) != 0) ||	// it's Shift+F10 OR
			(pMsg->message == WM_CONTEXTMENU))									// Natural keyboard key
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		CPoint point = rect.TopLeft();
		point.Offset(5, 5);
		OnContextMenu(NULL, point);

		return TRUE;
	}

	return CView::PreTranslateMessage(pMsg);
}


void CScr4editView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	// TODO: Add your message handler code here

	OutputDebugString("CScr4editView::OnSetFocus\n");

	static BOOL bFirst = TRUE;

	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

    // Realize our palette.
    if (bFirst && pMainFrame->m_lpDDSPrimary)
	{
		pMainFrame->NewPalette();
		pMainFrame->m_lpDDSPrimary->SetPalette( 
			pMainFrame->m_lpDDPal ); 


		bFirst = FALSE;
	}
}
