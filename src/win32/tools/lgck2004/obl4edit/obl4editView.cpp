// obl4editView.cpp : implementation of the CObl4editView class
//

#include "stdafx.h"
#include "obl4edit.h"
#include "obl3filter.h"

#include "obl4editDoc.h"
#include "obl4editView.h"
#include "DlgImageSize.h"
#include "DlgPasteBmp.h"
#include "mainfrm.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define C1 (0x40)
#define C2 (0x30)
#define LEFT_BUTTON 1
#define RIGHT_BUTTON 2
#define PREVIEW_LEN (16*16)
#define PREVIEW_HEI (16*16)	   

extern WORD			g_pal16[];
extern USER_24bpp	g_pal24[];
extern UINT			g_pal32[];

/////////////////////////////////////////////////////////////////////////////
// CObl4editView

IMPLEMENT_DYNCREATE(CObl4editView, CView)

BEGIN_MESSAGE_MAP(CObl4editView, CView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CObl4editView)
	ON_UPDATE_COMMAND_UI(IDM_CIRCLE, OnUpdateCircle)
	ON_UPDATE_COMMAND_UI(IDM_FLOOD, OnUpdateFlood)
	ON_UPDATE_COMMAND_UI(IDM_LINES, OnUpdateLines)
	ON_UPDATE_COMMAND_UI(IDM_LINESARC, OnUpdateLinesarc)
	ON_COMMAND(IDM_MAP, OnMap)
	ON_UPDATE_COMMAND_UI(IDM_PEN, OnUpdatePen)
	ON_UPDATE_COMMAND_UI(IDM_RECT, OnUpdateRect)
	ON_UPDATE_COMMAND_UI(IDM_MAP, OnUpdateMap)
	ON_COMMAND(IDM_CIRCLE, OnCircle)
	ON_COMMAND(IDM_FLOOD, OnFlood)
	ON_COMMAND(IDM_LINES, OnLines)
	ON_COMMAND(IDM_LINESARC, OnLinesarc)
	ON_COMMAND(IDM_PEN, OnPen)
	ON_COMMAND(IDM_RECT, OnRect)
	ON_COMMAND(IDM_W1, OnW1)
	ON_UPDATE_COMMAND_UI(IDM_W1, OnUpdateW1)
	ON_COMMAND(IDM_W2, OnW2)	
	ON_UPDATE_COMMAND_UI(IDM_W2, OnUpdateW2)
	ON_COMMAND(IDM_W3, OnW3)	
	ON_UPDATE_COMMAND_UI(IDM_W3, OnUpdateW3)
	ON_COMMAND(IDM_W4, OnW4)
	ON_UPDATE_COMMAND_UI(IDM_W4, OnUpdateW4)
	ON_COMMAND(IDM_W5, OnW5)
	ON_UPDATE_COMMAND_UI(IDM_W5, OnUpdateW5)
	ON_COMMAND(IDM_W6, OnW6)
	ON_UPDATE_COMMAND_UI(IDM_W6, OnUpdateW6)
	ON_COMMAND(IDM_W7, OnW7)
	ON_UPDATE_COMMAND_UI(IDM_W7, OnUpdateW7)
	ON_COMMAND(IDM_W8, OnW8)
	ON_UPDATE_COMMAND_UI(IDM_W8, OnUpdateW8)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_COMMAND(IDM_NEXT, OnNext)
	ON_UPDATE_COMMAND_UI(IDM_NEXT, OnUpdateNext)
	ON_COMMAND(IDM_BACK, OnBack)
	ON_UPDATE_COMMAND_UI(IDM_BACK, OnUpdateBack)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_FLIPHORZ, OnFliphorz)
	ON_UPDATE_COMMAND_UI(IDM_FLIPHORZ, OnUpdateFliphorz)
	ON_COMMAND(IDM_FLIPVERT, OnFlipvert)
	ON_UPDATE_COMMAND_UI(IDM_FLIPVERT, OnUpdateFlipvert)
	ON_COMMAND(IDM_SHIFTUP, OnShiftup)
	ON_UPDATE_COMMAND_UI(IDM_SHIFTUP, OnUpdateShiftup)
	ON_COMMAND(IDM_SHIFTDN, OnShiftdn)
	ON_UPDATE_COMMAND_UI(IDM_SHIFTDN, OnUpdateShiftdn)
	ON_COMMAND(IDM_SHIFTRG, OnShiftrg)
	ON_UPDATE_COMMAND_UI(IDM_SHIFTRG, OnUpdateShiftrg)
	ON_COMMAND(IDM_SHIFTLF, OnShiftlf)
	ON_UPDATE_COMMAND_UI(IDM_SHIFTLF, OnUpdateShiftlf)
	ON_COMMAND(IDM_CLEAR, OnClear)
	ON_UPDATE_COMMAND_UI(IDM_CLEAR, OnUpdateClear)
	ON_WM_RBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_SETCURSOR()
	ON_COMMAND(IDM_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(IDM_UNDO, OnUpdateUndo)
	ON_COMMAND(IDM_REDO, OnRedo)
	ON_UPDATE_COMMAND_UI(IDM_REDO, OnUpdateRedo)
	ON_COMMAND(IDM_EDITMODE, OnEditmode)
	ON_UPDATE_COMMAND_UI(IDM_EDITMODE, OnUpdateEditmode)
	ON_COMMAND(IDM_ROTATION90, OnRotation90)
	ON_UPDATE_COMMAND_UI(IDM_ROTATION90, OnUpdateRotation90)
	ON_COMMAND(IDM_INSERT, OnInsert)
	ON_UPDATE_COMMAND_UI(IDM_INSERT, OnUpdateInsert)
	ON_COMMAND(IDM_DELETE, OnDelete)
	ON_UPDATE_COMMAND_UI(IDM_DELETE, OnUpdateDelete)
	ON_COMMAND(IDM_EDITZOOM, OnEditzoom)
	ON_UPDATE_COMMAND_UI(IDM_EDITZOOM, OnUpdateEditzoom)
	ON_COMMAND(IDM_TAPESTRY, OnTapestry)
	ON_UPDATE_COMMAND_UI(IDM_TAPESTRY, OnUpdateTapestry)
	ON_COMMAND(IDM_ZOOMZOOM, OnZoomzoom)
	ON_UPDATE_COMMAND_UI(IDM_ZOOMZOOM, OnUpdateZoomzoom)
	ON_WM_KILLFOCUS()
	ON_COMMAND(IDM_FRAMECOUNTER, OnFramecounter)
	ON_UPDATE_COMMAND_UI(IDM_FRAMECOUNTER, OnUpdateFramecounter)
	ON_COMMAND(IDM_COLORSELECT, OnColorselect)
	ON_UPDATE_COMMAND_UI(IDM_COLORSELECT, OnUpdateColorselect)
	ON_COMMAND(IDM_SHOWPREVIEW, OnShowpreview)
	ON_UPDATE_COMMAND_UI(IDM_SHOWPREVIEW, OnUpdateShowpreview)
	ON_COMMAND(IDM_SELECT, OnSelect)
	ON_UPDATE_COMMAND_UI(IDM_SELECT, OnUpdateSelect)
	ON_WM_SHOWWINDOW()
	ON_WM_MOVE()
	ON_COMMAND(IDM_DUPLICATE, OnDuplicate)
	ON_UPDATE_COMMAND_UI(IDM_DUPLICATE, OnUpdateDuplicate)
	ON_COMMAND(IDM_ENLARGE, OnEnlarge)
	ON_UPDATE_COMMAND_UI(IDM_ENLARGE, OnUpdateEnlarge)
	ON_COMMAND(IDM_RESIZE, OnResize)
	ON_UPDATE_COMMAND_UI(IDM_RESIZE, OnUpdateResize)
	ON_COMMAND(IDM_COPY, OnCopy)
	ON_UPDATE_COMMAND_UI(IDM_COPY, OnUpdateCopy)
	ON_COMMAND(IDM_PASTE, OnPaste)
	ON_UPDATE_COMMAND_UI(IDM_PASTE, OnUpdatePaste)
	ON_COMMAND(IDM_CUT, OnCut)
	ON_UPDATE_COMMAND_UI(IDM_CUT, OnUpdateCut)
	ON_COMMAND(IDM_RAINBOW, OnRainbow)
	ON_UPDATE_COMMAND_UI(IDM_RAINBOW, OnUpdateRainbow)
	ON_COMMAND(IDM_INVERT, OnInvert)
	ON_UPDATE_COMMAND_UI(IDM_INVERT, OnUpdateInvert)
	ON_COMMAND(IDM_SPREADHORZ, OnSpreadhorz)
	ON_UPDATE_COMMAND_UI(IDM_SPREADHORZ, OnUpdateSpreadhorz)
	ON_COMMAND(IDM_SPREADVERT, OnSpreadvert)
	ON_UPDATE_COMMAND_UI(IDM_SPREADVERT, OnUpdateSpreadvert)
	ON_COMMAND(IDM_RAINBOW_EXCLUDE, OnRainbowExclude)
	ON_UPDATE_COMMAND_UI(IDM_RAINBOW_EXCLUDE, OnUpdateRainbowExclude)
	ON_COMMAND(IDM_SHRINK, OnShrink)
	ON_UPDATE_COMMAND_UI(IDM_SHRINK, OnUpdateShrink)
	ON_COMMAND(IDM_ISOMETRICGRID, OnIsometricgrid)
	ON_UPDATE_COMMAND_UI(IDM_ISOMETRICGRID, OnUpdateIsometricgrid)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObl4editView construction/destruction

CObl4editView::CObl4editView()
{
	// TODO: add construction code here
	m_nMX =0;
	m_nMY =0;
	m_bLockMouse = FALSE;
	m_bSelectionActive = FALSE;
	m_bToolHandled = FALSE;

	CWinApp *pApp = AfxGetApp();
    m_hIArrow = LoadCursor(NULL, IDC_ARROW);
    m_hIPen   = LoadCursor(pApp->m_hInstance, MAKEINTRESOURCE(IDC_PEN));
    m_hIFlood = LoadCursor(pApp->m_hInstance, MAKEINTRESOURCE(IDC_FLOOD));
    m_hICross = LoadCursor(NULL, IDC_CROSS);
	m_hIColorSelect = LoadCursor(pApp->m_hInstance, MAKEINTRESOURCE(IDC_COLORSELECT));

	m_bZoomed = pApp->GetProfileInt ("data", "m_bZoomed", TRUE);
	m_bEdit = pApp->GetProfileInt("data", "m_bEdit", TRUE);
	m_bShowPreview = pApp->GetProfileInt("data", "m_bShowPreview", TRUE);

	//m_bIsometric = FALSE;
}

CObl4editView::~CObl4editView()
{
	CWinApp *pApp = AfxGetApp();
	CMainFrame * pMainWnd = (CMainFrame *) AfxGetMainWnd();

	if (pMainWnd->m_bSaveSettings) {
		pApp->WriteProfileInt ("data", "m_bZoomed", m_bZoomed);
		pApp->WriteProfileInt("data", "m_bEdit", m_bEdit);
		pApp->WriteProfileInt("data", "m_bShowPreview", m_bShowPreview);
	}
}

BOOL CObl4editView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CObl4editView drawing

void CObl4editView::OnDraw(CDC* pDC)
{
	CObl4editDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CObl4editView printing

BOOL CObl4editView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CObl4editView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CObl4editView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CObl4editView diagnostics

#ifdef _DEBUG
void CObl4editView::AssertValid() const
{
	CView::AssertValid();
}

void CObl4editView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CObl4editDoc* CObl4editView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CObl4editDoc)));
	return (CObl4editDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CObl4editView message handlers

void CObl4editView::OnUpdateCircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nTool == IDM_CIRCLE);
}

void CObl4editView::OnUpdateFlood(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nTool == IDM_FLOOD);
	
}

void CObl4editView::OnUpdateLines(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nTool == IDM_LINES);
	
}

void CObl4editView::OnUpdateLinesarc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nTool == IDM_LINESARC);
	
}


void CObl4editView::OnUpdatePen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nTool == IDM_PEN);
	
}

void CObl4editView::OnUpdateRect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nTool == IDM_RECT);
	
}


void CObl4editView::OnUpdateMap(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nTool == IDM_MAP);
	
}


void CObl4editView::OnMap() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nTool = IDM_MAP;	
	
}

void CObl4editView::OnCircle() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nTool = IDM_CIRCLE;	
	
}

void CObl4editView::OnFlood() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nTool = IDM_FLOOD;	
	
}

void CObl4editView::OnLines() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nTool = IDM_LINES;	
	
}

void CObl4editView::OnLinesarc() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nTool = IDM_LINESARC;	
	
}

void CObl4editView::OnPen() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nTool = IDM_PEN;	
	
}

void CObl4editView::OnRect() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nTool = IDM_RECT;	
	
}

// Command Handlers for PenSizes 1 through 8
void CObl4editView::OnW1() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nPenSize = IDM_W1;	
	
}

void CObl4editView::OnUpdateW1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nPenSize == IDM_W1);
	
}

void CObl4editView::OnW2() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nPenSize = IDM_W2;	
	
}

void CObl4editView::OnUpdateW2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nPenSize == IDM_W2);
	
}

void CObl4editView::OnW3() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nPenSize = IDM_W3;	
	
}

void CObl4editView::OnUpdateW3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nPenSize == IDM_W3);
	
}

void CObl4editView::OnW4() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nPenSize = IDM_W4;	
	
}

void CObl4editView::OnUpdateW4(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nPenSize == IDM_W4);
}


void CObl4editView::OnW5() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nPenSize = IDM_W5;	
	
}

void CObl4editView::OnUpdateW5(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nPenSize == IDM_W5);
	
}

void CObl4editView::OnW6() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nPenSize = IDM_W6;	
	
}

void CObl4editView::OnUpdateW6(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nPenSize == IDM_W6);
	
}

void CObl4editView::OnW7() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nPenSize = IDM_W7;	
	
}

void CObl4editView::OnUpdateW7(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nPenSize == IDM_W7);
	
}

void CObl4editView::OnW8() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pMainFrame->m_nPenSize = IDM_W8;	
	
}

void CObl4editView::OnUpdateW8(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	pCmdUI-> SetRadio( pMainFrame->m_nPenSize == IDM_W8);
	
}

void CObl4editView::OnPaint() 
{
	CMainFrame *pMainFrame =  (CMainFrame *) AfxGetMainWnd();
	
	static bCritical = FALSE;
	m_wndPreview.Invalidate();

	if (bCritical) {
		CPaintDC dc(this);
		return;
	}
	bCritical=TRUE;
	if (m_bEdit) {
		DrawGrild();}
	else {
		TapestryMode();
	}

	bCritical=FALSE;
	CPaintDC dc(this);

	CObl4editDoc *pDoc = GetDocument();
	pDoc->UpdateTitle();

	return;
	
	// Do not call CView::OnPaint() for painting messages
}

BOOL CObl4editView::DrawGrild()
{
	CRect rectView;
	CObl4editDoc *pDoc = GetDocument();

    GetClientRect(rectView);
    CSize rectSize = rectView.Size();

	ClientToScreen (&rectView); // x & y

	if ((rectSize.cx < 4) || (rectSize.cy < 4))
		return TRUE; // No drawing surface ?

	if (m_bZoomed) {

		if (rectSize.cx %8) 
			rectSize.cx = rectSize.cx + (8 - rectSize.cx %8);

		if (rectSize.cy %8) 
			rectSize.cy = rectSize.cy + (8 - rectSize.cy %8);
	}

	int nRows = rectSize.cy/8;
	int nCols = rectSize.cx/8;

    // If the user has changed the display resolution our
    // surfaces could be lost.

	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

    if ( pMainFrame->m_lpDDSPrimary== NULL 
		|| FAILED( pMainFrame->m_lpDDSPrimary->IsLost() ) )
	{
        if ( !pMainFrame->RestoreAll() ) 
		{
            return pMainFrame->Fail( "DDraw: Couldn't restore surfaces.\n" );
        }
    }

	// Code snippet 100% by Frank B.
	int nSize = pDoc->m_oblData.GetSize()==0;
	if (pDoc->m_oblData.GetSize()==0)
	{
		pMainFrame->FillSurface(pMainFrame->m_lpDDSBack, 0xff);		

	}
	else
	{
		int nCurrFrame =  pDoc->m_oblData.m_nCurrFrame;	;
		CSS3Frame *pFrame =NULL;
		pFrame = pDoc->m_oblData[nCurrFrame] ;
      
		if ((min (pFrame->m_nLen, nCols) ==0) &&
		  (min (pFrame->m_nHei, nRows) ==0) )		{
#ifdef _DEBUG
			OutputDebugString("Warning: Cannot draw current frame - either invalid or no screen estate\n");
#endif
			pMainFrame->FillSurface(pMainFrame->m_lpDDSBack, 0xff);		
			
		}
		else {	

			DDSURFACEDESC ddsurfdesc;
			ddsurfdesc.dwSize = sizeof(DDSURFACEDESC);
			ddsurfdesc.dwFlags = DDSD_ALL;
			
			if (pMainFrame->m_lpDDSBack == NULL || pMainFrame->m_lpDDSBack->
				Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)
			{
				OutputDebugString("DDraw: Lock failed!\n");
				pMainFrame->ReleaseObjects();
				return FALSE;
			}

			char *pDest = (char*)ddsurfdesc.lpSurface; 

			if (m_bZoomed) {
				DrawImageZoomed ( pFrame,  pDest,  nCols, 
					nRows, ddsurfdesc.lPitch);
			}
			else {
				pMainFrame->OutputOBL3 (pFrame, m_nMX, m_nMY, rectSize.cx, rectSize.cy, TRUE, (UCHAR*) pDest, ddsurfdesc.lPitch);
		
			}

			if (pMainFrame->m_lpDDSBack->
				Unlock(NULL))
			{
				OutputDebugString("DDraw: Unlock failed!\n");
				pMainFrame->ReleaseObjects();
				return FALSE;
			}	
		}
	}	

	// Quickest way to get the destination RECT size and 
	// position.
	CRect rectDest; 
	GetClientRect(rectDest);

	if (pMainFrame->m_lpDDSPrimary==NULL)
 		return FALSE;

	// Blt from the second surface unto the display surface
	// and fill our little view.
	if ( FAILED( pMainFrame->m_lpDDSPrimary->Blt( &rectView, 
	   pMainFrame->m_lpDDSBack, &rectDest,
                    DDBLT_WAIT, NULL ) ) )
  
	{

		OutputDebugString("From obl4editview [drawgrild] -- Couldn't blt!\n");
		PostMessage(WM_PAINT);
		return FALSE;
    }
   	  
	return TRUE;
}

void CObl4editView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

	CObl4editDoc *pDoc = GetDocument();
	int nPenColor = pMainFrame->m_nPenColor;

	if (pDoc->m_oblData.GetSize()) {
		int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
		ToolsHandler (nFlags, 
			point, 
			nPenColor, 
			pMainFrame->m_nTool,
			LEFT_BUTTON);
	}

	CView::OnLButtonDown(nFlags, point);
}

void CObl4editView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

	CObl4editDoc *pDoc = GetDocument();
	int nPenColor = pMainFrame->m_nPenColor;

	ReleaseTool (nFlags, point, nPenColor,  pMainFrame->m_nTool);

	CView::OnLButtonUp(nFlags, point);
}


void CObl4editView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

	CObl4editDoc *pDoc = GetDocument();
	int nPenColor;
	if ( (nFlags & MK_LBUTTON) == MK_LBUTTON) {

		nPenColor = pMainFrame->m_nPenColor;
		ToolsHandler (nFlags, point, nPenColor,  pMainFrame->m_nTool, 
			LEFT_BUTTON);

	}
	else 
	{
		if ( (nFlags & MK_RBUTTON) == MK_RBUTTON){
			nPenColor = 0;
			ToolsHandler (nFlags, point, nPenColor,  pMainFrame->m_nTool, 
			RIGHT_BUTTON);

		}
		else
			{ CView::OnMouseMove(nFlags, point); return;}
	}


	CView::OnMouseMove(nFlags, point);
}

void CObl4editView::OnSize(UINT nType, int cx, int cy) 
{
	// TODO: Add your message handler code here

	// Adjust SB
	AdjustSB(cx, cy);	

	// Try to create the Preview Window
	static bPreviewCreated = FALSE;

	if (bPreviewCreated==FALSE) {
		CreatePreviewWindow();
		bPreviewCreated=TRUE;
	}
	
	CView::OnSize(nType, cx, cy);
}

void CObl4editView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	CView::OnVScroll(nSBCode, nPos, pScrollBar);

	CRect rectView;
    GetClientRect(rectView);
    CSize rectSize = rectView.Size();

	CObl4editDoc *pDoc = GetDocument();
	int nFrame = pDoc->m_oblData.m_nCurrFrame;

	if (pDoc->m_oblData.GetSize()==0) return;

	CSS3Frame *pFrame = pDoc->m_oblData[nFrame];   

	int nPixelHei;
	int nLineUpHei;
	if (m_bZoomed) { 
		nPixelHei= 8;
		nLineUpHei =1;
	} 
	else {
		nPixelHei =1;  
		nLineUpHei =4;
	}

	int _m_nMY; 

    switch (nSBCode) {

    case SB_LINEUP:
        _m_nMY = m_nMY -(min (nLineUpHei, m_nMY));
        break;

    case SB_PAGEUP:
        _m_nMY = m_nMY -(min (rectSize.cy/nPixelHei, m_nMY));
        break;

    case SB_THUMBPOSITION:
        _m_nMY = (int) nPos ;
        break;

    case SB_PAGEDOWN:
        _m_nMY = m_nMY 
			+ min (rectSize.cy/nPixelHei, pFrame->m_nHei - m_nMY);
        break;

    case SB_LINEDOWN:
		_m_nMY = min(m_nMY + nLineUpHei, pFrame->m_nHei);
			//(1, pFrame->m_nLen - m_nMY);
		
        break;

    default: // Ignore other scroll bar messages
        return;
    }

	if ((_m_nMY != m_nMY) && (_m_nMY >=0))
	{
		m_nMY = _m_nMY;
	    SetScrollPos (SB_VERT, m_nMY, TRUE);
		Invalidate();
	}

}

void CObl4editView::AdjustSB( int cx, int cy)
{
    SCROLLINFO si[2];

	int nPixelHei;
	int nLineUpHei;
	if (m_bZoomed) { 
		nPixelHei= 8;
		nLineUpHei =1;
	} 
	else {
		nPixelHei =1;  
		nLineUpHei =4;
	}


	CObl4editDoc *pDoc = GetDocument();
	if (!m_bEdit || pDoc->m_oblData.GetSize()==0) // Can't scroll without an image
	{
	    si[0].fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	    si[0].nMin = 0;
	    si[0].nMax = 0;
	    si[0].nPos = 0;
	    si[0].nPage = 0;

	    si[1].fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	    si[1].nMin = 0;
	    si[1].nMax = 0;
	    si[1].nPos = 0;
	    si[1].nPage = 0;
		
	}
	else
	{
		int nFrame = pDoc->m_oblData.m_nCurrFrame;
		CSS3Frame *pFrame = pDoc->m_oblData[nFrame];

		if ( (cy/nPixelHei)>m_nMY) 
			m_nMY = 0;

		if ( (cx/nPixelHei)>m_nMX) 
			m_nMX = 0;


	    si[0].fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	    si[0].nMin = 0;
	    si[0].nMax = pFrame->m_nLen;
		si[0].nPos = m_nMX;
		si[0].nPage = cx/nPixelHei;

	    si[1].fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	    si[1].nMin = 0;
	    si[1].nMax = pFrame->m_nHei;
		si[1].nPos = m_nMY;
		si[1].nPage = cy/nPixelHei;
	}

    SetScrollInfo (SB_HORZ, &si[0], TRUE);
    SetScrollInfo (SB_VERT, &si[1], TRUE);
}

int CObl4editView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CObl4editView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CView::OnEraseBkgnd(pDC);
}



void CObl4editView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rectView;
    GetClientRect(rectView);
    CSize rectSize = rectView.Size();
	
	AdjustSB(rectSize.cx, rectSize.cy);
}

void CObl4editView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}

BOOL CObl4editView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString strWndClass = AfxRegisterWndClass (
        CS_DBLCLKS | CS_OWNDC,                  // Class style
        NULL,//AfxGetApp()->LoadStandardCursor (IDC_ARROW),   // Class cursor
        NULL,//(HBRUSH) (COLOR_3DFACE ),               // Class background brush
        NULL            // Class icon
        );


	return CWnd::Create(strWndClass, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CObl4editView::DrawImageZoomed ( CSS3Frame *pFrame, char *pDest, int nCols, int nRows, int nPitch)
{
	int x;
	int y;
	int l = nPitch;

	CMainFrame * pMainFrame = (CMainFrame *)AfxGetMainWnd();

	pMainFrame->FillSurface (0xff, pDest,  nCols*8, nRows*8,  nPitch);

	for (y=0; y< min(nRows, pFrame->m_nHei - m_nMY)
		; y++)
	{
		char *s= pFrame->m_pBitmap + m_nMX+
						+ (m_nMY+y)*pFrame->m_nLen;

		char *d= pDest + 	( y*8*nPitch);

		for (x=0; x< min(nCols, pFrame->m_nLen - m_nMX)
			; x++)
		{

			DrawSqr (m_nMX + x,m_nMY +y, s,d, l, pMainFrame->m_nBpp);

			d=d+pMainFrame->m_nBpp;
			s++;
		}
	}
}


void CObl4editView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnHScroll(nSBCode, nPos, pScrollBar);

	CRect rectView;
    GetClientRect(rectView);
    CSize rectSize = rectView.Size();

	CObl4editDoc *pDoc = GetDocument();
	int nFrame = pDoc->m_oblData.m_nCurrFrame;

	if (pDoc->m_oblData.GetSize()==0) return;

	CSS3Frame *pFrame = pDoc->m_oblData[nFrame];   

	int _m_nMX; 

	int nPixelHei;
	int nLineUpHei;
	if (m_bZoomed) { 
		nPixelHei= 8;
		nLineUpHei =1;
	} 
	else {
		nPixelHei =1;  
		nLineUpHei =4;
	}


    switch (nSBCode) {

    case SB_LINEUP:
        _m_nMX = m_nMX -(min (nLineUpHei, m_nMX));
        break;

    case SB_PAGEUP:
        _m_nMX = m_nMX -(min (rectSize.cy/nPixelHei, m_nMX));
        break;

    case SB_THUMBPOSITION:
        _m_nMX = (int) nPos ;
        break;

    case SB_PAGEDOWN:
        _m_nMX = m_nMX 
			+ min (rectSize.cy/nPixelHei, pFrame->m_nLen - m_nMX);
        break;

    case SB_LINEDOWN:
		_m_nMX = min(m_nMX +nLineUpHei, pFrame->m_nLen);
		
        break;

    default: // Ignore other scroll bar messages
        return;
    }

	if ((_m_nMX != m_nMX) && (_m_nMX >=0))
	{
		m_nMX = _m_nMX;
	    SetScrollPos (SB_HORZ, m_nMX, TRUE);
		Invalidate();
	}
}

void CObl4editView::OnNext() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	pDoc->m_oblData.m_nCurrFrame++;
	Invalidate();
	
	CRect rectView;
    GetClientRect(rectView);
    CSize rectSize = rectView.Size();
	
	AdjustSB(rectSize.cx, rectSize.cy);
	
}

void CObl4editView::OnUpdateNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if  (pDoc->m_oblData.GetSize()==0)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		if ( pDoc->m_oblData.m_nCurrFrame +1 >=
			 pDoc->m_oblData.GetSize() )
		{
			pCmdUI->Enable(FALSE);
		}
	}
	
}

void CObl4editView::OnBack() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	pDoc->m_oblData.m_nCurrFrame--;
	Invalidate();
		

	CRect rectView;
    GetClientRect(rectView);
    CSize rectSize = rectView.Size();
	
	AdjustSB(rectSize.cx, rectSize.cy);

}

void CObl4editView::OnUpdateBack(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if  (pDoc->m_oblData.GetSize()==0)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		if ( pDoc->m_oblData.m_nCurrFrame ==0 )
		{
			pCmdUI->Enable(FALSE);
		}
	}
}

void CObl4editView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CObl4editDoc *pDoc = GetDocument();
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();

	int nPenColor = 0;

	if (pDoc->m_oblData.GetSize()) {
		int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
		pDoc->m_oblData[nCurrFrame]->Dirty();// Enable Undo 

		ToolsHandler (nFlags, 
			point, 
			nPenColor, 
			pMainFrame->m_nTool,
			RIGHT_BUTTON);
	}
	
	CView::OnRButtonDown(nFlags, point);
}

void CObl4editView::OnFliphorz() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;

	pDoc->m_oblData[nCurrFrame]->Dirty();

	pDoc->m_oblData[nCurrFrame]->FlipHorz();
	SetModified();

	Invalidate();	
}

void CObl4editView::OnUpdateFliphorz(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if  (pDoc->m_oblData.GetSize()==0)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
	
}


void CObl4editView::OnFlipvert() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;

	pDoc->m_oblData[nCurrFrame]->Dirty();

	pDoc->m_oblData[nCurrFrame]->FlipVert();
	SetModified();

	Invalidate();	
}

void CObl4editView::OnUpdateFlipvert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if  (pDoc->m_oblData.GetSize()==0)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}


}

void CObl4editView::OnShiftup() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;

	pDoc->m_oblData[nCurrFrame]->Dirty();

	pDoc->m_oblData[nCurrFrame]->ShiftUP();
	SetModified();

	Invalidate();	
		

	
}

void CObl4editView::OnUpdateShiftup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if  (pDoc->m_oblData.GetSize()==0)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
	
}

void CObl4editView::OnShiftdn() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;

	pDoc->m_oblData[nCurrFrame]->Dirty();

	pDoc->m_oblData[nCurrFrame]->ShiftDown();
	SetModified();

	Invalidate();	
}

void CObl4editView::OnUpdateShiftdn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if  (pDoc->m_oblData.GetSize()==0)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CObl4editView::OnShiftrg() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;

	pDoc->m_oblData[nCurrFrame]->Dirty();

	pDoc->m_oblData[nCurrFrame]->ShiftRight();
	SetModified();

	Invalidate();	
}

void CObl4editView::OnUpdateShiftrg(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if  (pDoc->m_oblData.GetSize()==0)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CObl4editView::OnShiftlf() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;

	pDoc->m_oblData[nCurrFrame]->Dirty();

	pDoc->m_oblData[nCurrFrame]->ShiftLeft();
	SetModified();

	Invalidate();			
		

	
}

void CObl4editView::OnUpdateShiftlf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();
	if  (pDoc->m_oblData.GetSize()==0)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
	
}

void CObl4editView::OnClear() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;

	pDoc->m_oblData[nCurrFrame]->Dirty();
	pDoc->m_oblData[nCurrFrame]->Erase();
	SetModified();

	Invalidate();	
	
}

void CObl4editView::OnUpdateClear(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if  (pDoc->m_oblData.GetSize()==0)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
	
}

void CObl4editView::ToolsHandler (UINT nFlags, CPoint point, UCHAR nPenColor,  int nTool, int nButton)
{
	CMainFrame *pMainFrame = (CMainFrame *) AfxGetMainWnd();
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	UCHAR nOldColor;
	int x,y;

	if (pDoc->m_oblData.GetSize()==0 || m_bEdit==FALSE)
		return;

	int nPixelHei;
	int nLineUpHei;

	if (m_bZoomed) { 
		nPixelHei= 8;
		nLineUpHei =1;
	} 
	else {
		nPixelHei =1;  
		nLineUpHei =4;
	}

	x= m_nMX + point.x/nPixelHei;
	y= m_nMY + point.y/nPixelHei;

	if (nTool!=IDM_SELECT) {
		m_bSelectionActive = FALSE;
	}

	if ( (nTool!=IDM_SELECT) && (x== m_dotLast.m_nX) && (y== m_dotLast.m_nY))	{	
			return; // same dot - no processing
	}

	m_dotLast.m_nX = x;
	m_dotLast.m_nY = y;
	m_dotLast.m_nColor = nPenColor;

	UCHAR nColor;

#ifdef _DEBUG
	//OutputDebugString ("ToolsHandler()\n");
#endif

	switch(nTool)
	{
	case IDM_PEN:
		if ((x>=pDoc->m_oblData[nCurrFrame]->m_nLen) ||
			(y>=pDoc->m_oblData[nCurrFrame]->m_nHei))
			return;

		SetModified();

		if (m_arrDots.GetSize()!=0)		{
			nColor = m_dotOrigin.m_nColor;
			m_dotOrigin =  m_arrDots[m_arrDots.GetSize()-1];
			m_dotOrigin.m_nColor = nColor;

			m_arrDots.Forget();

			LineTab (m_dotOrigin, CDot(x,y), 0, m_arrDots);
			DrawDots(m_dotOrigin.m_nColor, TRUE, TRUE);
		}
		else {
			m_dotOrigin.m_nX =x;
			m_dotOrigin.m_nY =y;
			m_dotOrigin.m_nColor = nPenColor;

			if (!m_bToolHandled) {
				m_bToolHandled = TRUE;
				pDoc->m_oblData[nCurrFrame]->Dirty();// Enable Undo 
			}

			DrawGrild();
			LineTab (m_dotOrigin, m_dotOrigin, 0, m_arrDots);
			DrawDots(nPenColor, TRUE, TRUE);
		}

		if (m_bLockMouse==FALSE ) {
			CaptureMouse();
			m_bLockMouse=TRUE;
		}

		break; // IDM_PEN

	case IDM_FLOOD:
		if ((x>=pDoc->m_oblData[nCurrFrame]->m_nLen) ||
			(y>=pDoc->m_oblData[nCurrFrame]->m_nHei))
			return;

		if (!m_bToolHandled) {
				m_bToolHandled = TRUE;
				pDoc->m_oblData[nCurrFrame]->Dirty();// Enable Undo 
		}
		
		SetModified();
		
		nOldColor = * pDoc->m_oblData[nCurrFrame]->Point(x,y);

		if (nOldColor != nPenColor)		{
			(pDoc->m_oblData[nCurrFrame])->FloodFill(x,y, nOldColor, nPenColor );
			SetModified();
			Invalidate();	
				

		}

		break;  // IDM_FLOOD

	case IDM_LINES:
		if ((x>=pDoc->m_oblData[nCurrFrame]->m_nLen) ||
			(y>=pDoc->m_oblData[nCurrFrame]->m_nHei))
			return;

		SetModified();

		if (m_arrDots.GetSize()!=0)		{
			DrawDots(0xff, FALSE);
			m_arrDots.Forget();

			LineTab (m_dotOrigin, CDot(x,y), 0, m_arrDots);
			DrawDots(m_dotOrigin.m_nColor, TRUE);
		}

		else		{
			m_dotOrigin.m_nX =x;
			m_dotOrigin.m_nY =y;
			m_dotOrigin.m_nColor = nPenColor;

			if (!m_bToolHandled) {
				m_bToolHandled = TRUE;
				pDoc->m_oblData[nCurrFrame]->Dirty();// Enable Undo 
			}

			DrawGrild();
			LineTab (m_dotOrigin, m_dotOrigin, 0, m_arrDots);
			DrawDots(nPenColor, TRUE);
		}
		
		if (m_bLockMouse==FALSE ) {
			CaptureMouse();
			m_bLockMouse=TRUE;
		}
			
		break; // IDM_LINES

	case IDM_RECT:
		if ((x>=pDoc->m_oblData[nCurrFrame]->m_nLen) ||
			(y>=pDoc->m_oblData[nCurrFrame]->m_nHei))
			return;

		SetModified();

		if (m_arrDots.GetSize()!=0)		{
			DrawDots(0xff, FALSE);
			m_arrDots.Forget();

			LineTab (CDot (m_dotOrigin.m_nX,m_dotOrigin.m_nY), 
					CDot  (x, m_dotOrigin.m_nY),0,m_arrDots);

			LineTab (CDot (m_dotOrigin.m_nX,m_dotOrigin.m_nY), 
					CDot  (m_dotOrigin.m_nX, y),0,m_arrDots);

			LineTab (CDot (x,m_dotOrigin.m_nY), 
					CDot  (x, y),0,m_arrDots);
			
			LineTab (CDot (m_dotOrigin.m_nX,y), 
					CDot  (x, y),0,m_arrDots);

			DrawDots(m_dotOrigin.m_nColor, TRUE);


		}
		else	{
			m_dotOrigin.m_nX =x;
			m_dotOrigin.m_nY =y;
			m_dotOrigin.m_nColor = nPenColor;

			if (!m_bToolHandled) {
				m_bToolHandled = TRUE;
				pDoc->m_oblData[nCurrFrame]->Dirty();// Enable Undo 
			}

			DrawGrild();
			LineTab (m_dotOrigin, m_dotOrigin, 0, m_arrDots);
			DrawDots(nPenColor, TRUE);
		}

		if (m_bLockMouse==FALSE ) {
			CaptureMouse();
			m_bLockMouse=TRUE;
		}

		break; // IDM_RECT


	case IDM_COLORSELECT:
		if ((x>=pDoc->m_oblData[nCurrFrame]->m_nLen) ||
			(y>=pDoc->m_oblData[nCurrFrame]->m_nHei))
			return;

		if (pDoc->m_oblData[nCurrFrame]->Point (x,y)!=NULL)
		{
			if (nButton ==1)
			{
				pMainFrame-> m_nPenColor = 
					* pDoc->m_oblData[nCurrFrame]->Point (x,y);
				pMainFrame-> UpdateColorBox();
				DrawGrild();

			}
			else {
				if (nButton==2)
				{

					SetModified();

					if (!m_bToolHandled) {
						m_bToolHandled = TRUE;
						pDoc->m_oblData[nCurrFrame]->Dirty();// Enable Undo 
					}

					* pDoc->m_oblData[nCurrFrame]->Point (x,y) =
						pMainFrame-> m_nPenColor ;

					LineTab (CDot (x,y), CDot (x, y),0,m_arrDots);
					DrawDots(pMainFrame-> m_nPenColor, TRUE, TRUE);
					m_arrDots.Forget();
					
				}
			}
		}

		break; // IDM_COLORSELECT;

	case IDM_SELECT:
		if ((x>=pDoc->m_oblData[nCurrFrame]->m_nLen) ||
			(y>=pDoc->m_oblData[nCurrFrame]->m_nHei))
			return;
		

		if (!m_bSelectionActive) {
			if (m_arrDots.GetSize()!=0)		{
				m_dotOrigin = m_arrDots[0];
				m_arrDots.Forget();
				m_arrDots.Add ( CDot(m_dotOrigin));
				m_arrDots.Add ( CDot (point.x,point.y));

				TrackRect( CDot (m_dotOrigin),
					CDot (point.x,point.y));

			} // if
			else {
	
				m_arrDots.Add ( CDot (point.x,point.y));
				m_arrDots.Add ( CDot (point.x,point.y));

				TrackRect( CDot (point.x,point.y),
					CDot (point.x+1,point.y+1));

			} // else
		} // if

		else {

			if (m_arrDots.GetSize()!=0)	{

			//	TrackRect( *m_arrDots[0],
			//		*m_arrDots[1]);


			} // if

			else { // internal error 

				
			} // else

		} // else

		break; // IDM_SELECT


	default:
		break;
	}

}


int CObl4editView::LineTab (CDot & Dot1, CDot & Dot2, BYTE color, CDotArray & DotArray)
{

	int Ydiff;
	int Xdiff;          
                     
	int Yunit, Xunit;   
	int Erreur;         
                     
	int Longeur;      
	int i;            

	int XX;
	int YY;

	XX = Dot1.m_nX;	 
	YY = Dot1.m_nY;	 

	Ydiff = Dot2.m_nY - Dot1.m_nY;

    if (Ydiff < 0)   {   
		Ydiff = -Ydiff;
        Yunit = -1;
    }   
    else   {
        Yunit = 1;
    }

  	Xdiff = Dot2.m_nX - Dot1.m_nX;
    
    if (Xdiff < 0)   {
		Xdiff = -Xdiff;
        Xunit = -1;
    }
         
    else   {                
         Xunit = 1;
	}  

    Erreur = 0;     

    if (Xdiff > Ydiff)  {                   
          
		Longeur = Xdiff;// + 1;

		for (i=0; i<=Longeur; i++)	{
			DotArray.Add  (CDot(XX,YY));
			XX = XX + Xunit;
			Erreur = Erreur + Ydiff;    
			if (Erreur > Xdiff)   {
				Erreur = Erreur - Xdiff; 
				YY = YY + Yunit;
		        }             
		}    
	}   
		
	else 	{

		Longeur = Ydiff;// + 1; 

        for (i=0; i<=Longeur; i++)    {
			DotArray.Add  (CDot(XX,YY));
            YY = YY + Yunit;                                          
            Erreur = Erreur + Xdiff;    
            if (Erreur > 0)     {            
                 Erreur = Erreur - Ydiff; 
                 XX = XX + Xunit;                 
              }
          }
      }

      return Longeur;
}
                   

 

void CObl4editView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	
	// TODO: Add your message handler code here and/or call default
	CObl4editDoc *pDoc = GetDocument();
	int nPenColor = 0;

	ReleaseTool (nFlags, point, nPenColor,  pMainFrame->m_nTool);

	CView::OnRButtonUp(nFlags, point);
}

void CObl4editView::ReleaseTool (int nFlags, CPoint point, UCHAR nPenColor, int nTool)
{

	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	int x,y;

	if (pDoc->m_oblData.GetSize()==0 || m_bEdit==FALSE)
		return;

	if (m_bToolHandled)
	{
		m_bToolHandled=FALSE; 
		m_wndPreview.Invalidate();

	}

	int nPixelHei;
	int nLineUpHei;
	if (m_bZoomed) { 
		nPixelHei= 8;
		nLineUpHei =1;
	} 
	else {
		nPixelHei =1;  
		nLineUpHei =4;
	}

	x= m_nMX + point.x/nPixelHei;
	y= m_nMY + point.y/nPixelHei;

	// Forgeting previous dot trackback
	m_dotLast.m_nX = -1;
	m_dotLast.m_nY = -1;

#ifdef _DEBUG
	//OutputDebugString ("ReleaseTool ()\n");
#endif

	switch(nTool)
	{
	case IDM_PEN:
		if (m_arrDots.GetSize()!=0)
		{
			// Copy dots to mem first
			if (nPenColor!=0)	{
				pMainFrame->m_nPenColor = 	
					m_dotOrigin.m_nColor;			
			}

			nPenColor = m_dotOrigin.m_nColor;
			DrawDots(nPenColor, FALSE, TRUE);
			m_arrDots.Forget();

		}	

		m_wndPreview.Invalidate();	
		//DrawGrild();

		break; // IDM_PEN

	case IDM_FLOOD:

		m_wndPreview.Invalidate();
		
		break; // IDM_FLOOD

	case IDM_LINES:
		if (m_arrDots.GetSize()!=0)
		{
			// Copy dots to mem first
			if (nPenColor!=0)	{
				pMainFrame->m_nPenColor = 	
					m_dotOrigin.m_nColor;			
			}

			nPenColor = m_dotOrigin.m_nColor;
			DrawDots(nPenColor, FALSE, TRUE);
			m_arrDots.Forget();
		}
		
		m_wndPreview.Invalidate();	
		//DrawGrild();

		break; //IDM_LINES

	case IDM_RECT:
		if (m_arrDots.GetSize()!=0)
		{
			// Copy dots to mem first
			if (nPenColor!=0)	{
				pMainFrame->m_nPenColor = 	
					m_dotOrigin.m_nColor;			
			}

			nPenColor = m_dotOrigin.m_nColor;
			DrawDots(nPenColor, FALSE, TRUE);
			m_arrDots.Forget();

		}	
		m_wndPreview.Invalidate();			
		//DrawGrild();

		break; // IDM_RECT

	case IDM_SELECT:

		if (m_arrDots.GetSize()!=0)		{

			m_bSelectionActive = TRUE;
			m_arrDots.Forget(); // until we actually code this one

			/*
			m_dotOrigin = *m_arrDots[0];
			m_arrDots.Forget();
			m_arrDots.Add ( new CDot(m_dotOrigin));
			m_arrDots.Add ( new CDot (point.x,point.y));

			TrackRect( CDot (m_dotOrigin),
				CDot (point.x,point.y));*/

		}

		else { // Internal Error

			/*
			m_arrDots.Add ( new CDot (point.x,point.y));
			m_arrDots.Add ( new CDot (point.x,point.y));

			TrackRect( CDot (point.x,point.y),
				CDot (point.x,point.y));*/
		}
		
		break; // IDM_SELECT

	default:
		break;
	}

	if (m_bLockMouse==TRUE ) {
			ClipCursor(FALSE);
			m_bLockMouse=FALSE;
		}

}

void CObl4editView::CaptureMouse()
{

	CRect *rectView = CalcMouseRect();
	if (rectView!=NULL)	{
		ClipCursor(rectView);
		delete rectView;

	}
}



void CObl4editView::RedrawGrild()
{

	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );
	
   // Quickest way to get the destination RECT size and 
   // position.
   CRect rectDest; 
   GetClientRect(rectDest);

   CRect rectView = rectDest;
   ClientToScreen (rectView);

   // Blt from the second surface unto the display surface
   // and fill our little view.
   if ( FAILED( pMainFrame->m_lpDDSPrimary->Blt( &rectView, 
	   pMainFrame->m_lpDDSBack, &rectDest,
                    DDBLT_WAIT, NULL ) ) )
  
	{
#ifdef _DEBUG
	   OutputDebugString("DDraw: Couldn't blt! [Redraw Grild]\n");
#endif
		PostMessage(WM_PAINT);
		return ;
    }
}

void CObl4editView::DrawDots (UINT nColor, BOOL bBlit, BOOL bSave )
{
	
	CObl4editDoc *pDoc = GetDocument();

	int nSize = pDoc->m_oblData.GetSize()==0;

	if (pDoc->m_oblData.GetSize()==0)
	{
#ifdef _DEBUG
		OutputDebugString("Warning: Cannot draw onto an empty frame\n");
#endif
		return ;		
	}

	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	CSS3Frame *pFrame = pDoc->m_oblData[nCurrFrame] ;

	// draw dot to bitmap memory

	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

    if ( FAILED( pMainFrame->m_lpDDSPrimary->IsLost() ) )
	{
        if ( !pMainFrame->RestoreAll() ) 
		{
			pMainFrame->Fail( "DDraw: Couldn't restore surfaces.\n" );
            return ;
        }
    }

	DDSURFACEDESC ddsurfdesc;
	ddsurfdesc.dwSize = sizeof(DDSURFACEDESC);
	ddsurfdesc.dwFlags = DDSD_ALL;

	if (pMainFrame->m_lpDDSBack->
		Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)
	{
		OutputDebugString("DDraw: Lock failed!\n");
		pMainFrame->ReleaseObjects();
		PostQuitMessage(0);
		return ;
	}

	char *pDest = (char*)ddsurfdesc.lpSurface; 

	UCHAR *pDot;
	int l=  ddsurfdesc.lPitch; 

	int nPenSize = pMainFrame->m_nPenSize -IDM_W1 +1;

	int i,j;
	int d,x,y;

	if (m_bZoomed)
		for (d=0; d< m_arrDots.GetSize(); d++)
		{
			for (i=0; i< nPenSize; i++)
			{
				for (j=0; j<nPenSize; j++)
				{

					x=  m_arrDots[d].m_nX+ j;
					y = m_arrDots[d].m_nY+i;
					pDot= (pFrame->Point(x  , y ));

					if (pDot)	{

						if (bSave) 
							*pDot = (UCHAR) nColor;

						if (nColor==0xff) {}
						else {	pDot = (UCHAR*)&nColor;}


						char *d= pDest + (-m_nMX+ x)*pMainFrame->m_nBpp //8
							+ (-m_nMY+y)*8*ddsurfdesc.lPitch;


						DrawSqr ( x, y, (CHAR*) pDot, d, l, pMainFrame->m_nBpp);
					} // if
				} // for j
			} // for i
		} // for d

	else{

		for (d=0; d< m_arrDots.GetSize(); d++)
		{
			x=  m_arrDots[d].m_nX;
			y = m_arrDots[d].m_nY;
			for (i=0; i< nPenSize; i++)
			{
				for (j=0; j<nPenSize; j++)
				{

					pDot= (pFrame->Point(x +j  , y +i));
	
					if (pDot)	{
			
						if (bSave) 
							*pDot = (UCHAR) nColor;

						if (nColor==0xff) {}
						else {	pDot = (UCHAR*)&nColor;}


						switch (pMainFrame->m_nBpp)
						{
					
						case 8:

							* (pDest + (-m_nMX+ x+j)+ 
								(-m_nMY+y+i)*ddsurfdesc.lPitch) =
								* pDot;
						
							break; //8bpp
						case 16:

							* ((short*)((pDest + (-m_nMX+ x+j)*2+ 
								(-m_nMY+y+i)*ddsurfdesc.lPitch))) =
								 g_pal16[*pDot];

							break; //16bpp

						case 24:
							* ((USER_24bpp*)((pDest + (-m_nMX+ x+j)*3+ 
								(-m_nMY+y+i)*ddsurfdesc.lPitch))) =
								 g_pal24[*pDot];
							break; // 24bpp


						case 32:
							* ((int*)((pDest + (-m_nMX+ x+j)*4+ 
								(-m_nMY+y+i)*ddsurfdesc.lPitch))) =
								 g_pal32[*pDot];
							break; //32bpp
						} // switch
					} // if			
				} // for
			} // for
		} // for
	} // else


	if (pMainFrame->m_lpDDSBack->
		Unlock(NULL))
	{
		OutputDebugString("DDraw: Unlock failed!\n");
		pMainFrame->ReleaseObjects();
		PostQuitMessage(0);
		return ;
	}

   // Quickest way to get the destination RECT size and 
   // position.
   CRect rectDest; 
   GetClientRect(rectDest);

   CRect rectView = rectDest;
   ClientToScreen (rectView);


   // Blt from the second surface unto the display surface
   // and fill our little view.
	if (bBlit) {
		if ( FAILED( pMainFrame->m_lpDDSPrimary->Blt( &rectView, 
			pMainFrame->m_lpDDSBack, &rectDest,
                    DDBLT_WAIT, NULL ) ) )
  
		{
#ifdef _DEBUG
			OutputDebugString("DDraw: Couldn't blt! [drawdots] \n");
#endif
			PostMessage(WM_PAINT);
			return ;
		}
	}
	
	
}

void CObl4editView::OnSetFocus(CWnd* pOldWnd) 
{
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();

#ifdef _DEBUG
	OutputDebugString ("OnSetFocus()\n");
#endif

	CView::OnSetFocus(pOldWnd);
	CObl4editDoc *pDoc = GetDocument();

	// TODO: Add your message handler code here
	if (m_bLockMouse==TRUE ) {
		ClipCursor(FALSE);
		m_bLockMouse=FALSE;
	}	

	static BOOL bFirst = TRUE;
	if (bFirst)
	{
		CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
		pMainFrame->NewPalette();
		bFirst = FALSE;
	}
}

BOOL CObl4editView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	CObl4editDoc *pDoc = GetDocument();
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();

	CPoint point;
	
	GetCursorPos (&point);			// where is mouse?

	CRect *rect = CalcMouseRect();	// calc draw-able area

	CRect rectView;
    GetClientRect(rectView);
	ClientToScreen (&rectView);		// calc client area

	if (rect!=NULL)
	{
		if ( (point.x < rectView.left) || (point.y< rectView.top)
			|| (point.x > rectView.right)
			|| (point.y > rectView.bottom))	{	
				::SetCursor (m_hIArrow);
		}
		else
		{

			if ((point.x> rect->right) || (point.y>rect->bottom) ||
				  (m_bEdit==FALSE)  )	{				
				::SetCursor (LoadCursor(NULL, IDC_NO));
			}

			else

			switch( pMainFrame->m_nTool)	{

			case IDM_PEN:
				::SetCursor (m_hIPen);
			break;


			case IDM_FLOOD:
				::SetCursor (m_hIFlood);
			break;

			case IDM_LINES:
			case IDM_SELECT:
			case IDM_RECT:
				::SetCursor (m_hICross);
			break;

			case IDM_COLORSELECT:
				::SetCursor (m_hIColorSelect);
			break;


			default:
				::SetCursor (m_hIArrow);
			break;
			}

		}

		delete rect;
	}
	else {
		::SetCursor (m_hIArrow);
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

CRect * CObl4editView::CalcMouseRect()
{
	CRect rectView;
	CObl4editDoc *pDoc = GetDocument();

    GetClientRect(rectView);
    CSize rectSize = rectView.Size();

	ClientToScreen (&rectView); // x & y

	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (pDoc->m_oblData.GetSize()==0) return NULL;

	if ((m_nMX >= pDoc->m_oblData[nCurrFrame]->m_nLen )
		||(m_nMY >= pDoc->m_oblData[nCurrFrame]->m_nHei ))
		return NULL;

	int nPixelHei;
	int nLineUpHei;
	if (m_bZoomed) { 
		nPixelHei= 8;
		nLineUpHei =1;
	} 
	else {
		nPixelHei =1;  
		nLineUpHei =4;
	}

	int nCols= (rectSize.cx /nPixelHei);
	int nRows = (rectSize.cy/nPixelHei);

	BOOL bEntireClient = TRUE;

	if (m_nMX + nCols >= pDoc->m_oblData[nCurrFrame]->m_nLen)
	{
		nCols = pDoc->m_oblData[nCurrFrame]->m_nLen- m_nMX;
		bEntireClient = FALSE;
	}

	if (m_nMY + nRows >= pDoc->m_oblData[nCurrFrame]->m_nHei)
	{
		nRows = pDoc->m_oblData[nCurrFrame]->m_nHei- m_nMY;
		bEntireClient = FALSE;
	}

	rectView.bottom = rectView.top + nRows*nPixelHei;
	rectView.right = rectView.left + nCols*nPixelHei;

	return new CRect(rectView);
}

void CObl4editView::OnUndo() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (pDoc->m_oblData.GetSize()==0) return ;

	if (pDoc->m_oblData[nCurrFrame]->CanUndo()) {
		pDoc->m_oblData[nCurrFrame]->Undo();
		Invalidate();
		SetModified();			

	}
	
}

void CObl4editView::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (pDoc->m_oblData.GetSize()==0) {
		pCmdUI->Enable(FALSE);
		return ;
	}

	pCmdUI->Enable(pDoc->m_oblData[nCurrFrame]->CanUndo());

}

void CObl4editView::OnRedo() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (pDoc->m_oblData.GetSize()==0) 	return ;
	
	if (pDoc->m_oblData[nCurrFrame]->CanRedo()){
		pDoc->m_oblData[nCurrFrame]->Redo();
		Invalidate();
		SetModified();
			
	}
}

void CObl4editView::OnUpdateRedo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (pDoc->m_oblData.GetSize()==0) 	{
		pCmdUI->Enable(FALSE);
		return ;
	}

	pCmdUI->Enable(pDoc->m_oblData[nCurrFrame]->CanRedo());
	
}

void CObl4editView::TapestryMode()
{
	CRect rectView;
	CObl4editDoc *pDoc = GetDocument();

    GetClientRect(rectView);
    CSize rectSize = rectView.Size();

	CMainFrame *pMainFrame = ((CMainFrame*) AfxGetMainWnd() );

	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (pDoc->m_oblData.GetSize()==0)
	{

		if (rectSize.cx %4) rectSize.cx = rectSize.cx 
			+ (4- rectSize.cx %4);

		if (rectSize.cy %4) rectSize.cy = rectSize.cy 
			+ (4- rectSize.cy %4);

		// No Image - Clear surface 
		pMainFrame->OutputOBL3 (NULL, 0, 0, rectSize.cx, rectSize.cy, TRUE);

		CRect rectSource;
		GetClientRect (rectSource);
		CRect rectDest ;
		GetClientRect (rectDest);
		ClientToScreen (rectDest);

		if ( pMainFrame->m_lpDDSPrimary==NULL ||
			FAILED( pMainFrame->m_lpDDSPrimary->Blt( &rectDest, 
							pMainFrame->m_lpDDSBack, &rectSource,
							DDBLT_WAIT, NULL ) ) )		{

#ifdef _DEBUG
			    OutputDebugString("DDraw: Couldn't blt! [tapestry mode]\n");
#endif
				pMainFrame->RestoreAll();
				PostMessage(WM_PAINT);
				return ;
		}

		return ;
	}
	else
	{
		CSS3Frame *pFrame = pDoc->m_oblData[nCurrFrame];
		pMainFrame->OutputOBL3 (pFrame, 0, 0, rectSize.cx, rectSize.cy, FALSE);
		
		int nCols = rectSize.cx / pFrame->m_nLen ;
		if (rectSize.cx % pFrame->m_nLen) nCols++;
		int nRows = rectSize.cy / pFrame->m_nHei ;
		if (rectSize.cy % pFrame->m_nHei) nRows++;

		int x,y;

		for (y=0; y<nRows; y++)
		{
			for (x=0; x<nCols; x++)
			{
				CRect rectSource (CPoint (0,0),
					CPoint (pFrame->m_nLen , pFrame->m_nHei ));

				CRect rectDest (CPoint (x* pFrame->m_nLen, y*pFrame->m_nHei ),
					rectSource.Size());

				if (rectDest.bottom > rectView.bottom)
					rectDest.bottom = rectView.bottom;

				if (rectDest.right > rectView.right )
					rectDest.right = rectView.right ;

				rectSource = CRect(CPoint (0,0), rectDest.Size());

				ClientToScreen (&rectDest); // x & y

				if ( FAILED( pMainFrame->m_lpDDSPrimary->Blt( &rectDest, 
							pMainFrame->m_lpDDSBack, &rectSource,
							DDBLT_WAIT, NULL ) ) )
  
				{
#ifdef _DEBUG
						OutputDebugString("DDraw: Couldn't blt [tapestry mode]!\n");
#endif
						PostMessage(WM_PAINT);
						return ;
				
				}
			}
		}

	}

}

void CObl4editView::OnRotation90() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (pDoc->m_oblData.GetSize()==0) {
		return ;
	}

	if (pDoc->m_oblData[nCurrFrame]->m_nLen != 
		pDoc->m_oblData[nCurrFrame]->m_nHei) {
			return ;
	}

	pDoc->m_oblData[nCurrFrame]->Dirty();
	pDoc->m_oblData[nCurrFrame]->Rotate90();
	Invalidate();
	SetModified();
}

void CObl4editView::OnUpdateRotation90(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (pDoc->m_oblData.GetSize()==0) {
		pCmdUI->Enable(FALSE);
		return ;
	}

	if (pDoc->m_oblData[nCurrFrame]->m_nLen != 
		pDoc->m_oblData[nCurrFrame]->m_nHei) {
			pCmdUI->Enable(FALSE);
			return ;
	}

	pCmdUI->Enable(TRUE);
}

// Let's do it for all resolutions
void CObl4editView::DrawSqr ( int x, int y, char *s, char *d, int l, int nBpp)
{

	static UCHAR c;
	static CMainFrame * pMainFrame = (CMainFrame *)AfxGetMainWnd();

	static void *p16 = &g_pal16[0];
	static void *p32 = &g_pal32[0];
	static void *p24 = &g_pal24[0];

	static short c16;
	static int c32;
	static USER_24bpp c24;
	static void *pC24 = &c24;

	DWORD nWhite;

	switch (nBpp)
	{
	case 8:

			if ((*s == 0) &&
				(pMainFrame->m_bShowTransparency))
			{
				nWhite = 0x00ff0000;
			}
			else
			{
				nWhite = 0;
			}

					if (((y)%8==7) || ((x)%8==7))
					{
						c = C1;
					}
					else
					{
						c= C2;
					}

					_asm {

						push ecx
						push edx
						push eax
						push ebx
						push edi
						push esi

						mov ecx,4

						mov esi, s
						mov dh, [esi]
						mov dl, c
						shl edx,16
						mov dl, [esi]
						mov dh, dl

						mov ax,dx
						shl eax,16
						mov ax,dx						

						mov edi, d
						mov ebx, l

						// white or no white
						mov esi, eax
						or esi, nWhite

						// 1
						mov [edi], eax
						mov [edi+ecx],edx
						add edi,ebx
						
						// 2
						mov [edi], eax
						mov [edi+ecx],edx
						add edi,ebx
						
						// 3
						mov [edi], eax
						mov [edi+ecx],edx
						add edi,ebx
						
						// 4
						mov [edi], esi
						mov [edi+ecx],edx
						add edi,ebx
						
						// 5
						mov [edi], esi
						mov [edi+ecx],edx
						add edi,ebx
						
						// 6
						mov [edi], eax
						mov [edi+ecx],edx
						add edi,ebx
						
						// 7
						mov [edi], eax
						mov [edi+ecx],edx						
						add edi,ebx

						// 8
						mov al, c
						mov ah,al
						shl eax,16
						mov al,c
						mov ah,al
						mov [edi], eax
						mov [edi+ecx],eax
					
						pop esi
						pop edi
						pop ebx
						pop eax
						pop edx
						pop ecx
					}

		
	break; // 8bpp


	case 16:

			if ((*s == 0) &&
				(pMainFrame->m_bShowTransparency))
			{
				nWhite = 0x0000ffff;
			}
			else
			{
				nWhite = 0;
			}


					if (((y)%8==7) || ((x)%8==7))
						c16 = g_pal16[C1];
					else
						c16= g_pal16[C2];

					if (IsoGrildSQR(x,y))
					{
						c16= g_pal16[60];
					}

					_asm {

						push ecx
						push edx
						push eax
						push ebx
						push edi
						push esi

						mov ecx,4

						mov esi, s
						xor eax,eax
						mov al,[esi]
						shl eax,1 // 2 bits = 2^1
						add eax, p16
						mov dx, c16
						shl edx,16
						mov dx, [eax]

						mov ax,dx
						shl eax,16
						mov ax,dx						

						mov edi, d
						mov ebx, l

						// Transparent color
						// added
						mov esi, eax
						or esi, nWhite						

						mov [edi], eax
						mov [edi+ecx],eax
						mov [edi+ecx*2], eax
						mov [edi+12],edx //1
						add edi,ebx

						mov [edi], eax
						mov [edi+ecx],eax
						mov [edi+ecx*2], eax
						mov [edi+12],edx //2
						add edi,ebx

						mov [edi], eax
						mov [edi+ecx],eax
						mov [edi+ecx*2], eax
						mov [edi+12],edx //3
						add edi,ebx

						mov [edi], eax
						mov [edi+ecx],eax
						mov [edi+ecx*2], esi
						mov [edi+12],edx //4
						add edi,ebx

						mov [edi], eax
						mov [edi+ecx],eax
						mov [edi+ecx*2], esi
						mov [edi+12],edx //5
						add edi,ebx

						mov [edi], eax
						mov [edi+ecx],eax
						mov [edi+ecx*2], eax
						mov [edi+12],edx //6
						add edi,ebx

						mov [edi], eax
						mov [edi+ecx],eax
						mov [edi+ecx*2], eax
						mov [edi+12],edx //7
						add edi,ebx
						
						mov ax, c16
						shl eax,16
						mov ax,c16
						mov [edi], eax
						mov [edi+ecx],eax
						mov [edi+ecx*2], eax
						mov [edi+12],eax
						
						pop esi
						pop edi
						pop ebx
						pop eax
						pop edx
						pop ecx
					}


	
	
	break; //16bpp


	case 24:

		if ((*s == 0) &&
			(pMainFrame->m_bShowTransparency))
		{
			nWhite = 0x0000ffff;
		}
		else
		{
			nWhite = 0;
		}
		
		if (((y)%8==7) || ((x)%8==7))
			c24 = g_pal24[C1];
		else
			c24= g_pal24[C2];

		_asm {

						push ecx
						push edx
						push eax
						push ebx
						push edi
						push esi

						mov ecx,3

						mov esi, s
						xor eax,eax
						mov al,[esi]
						mov edx, eax
						add edx, eax
						add edx, eax
						mov esi, p24
						add esi, edx

						mov al, [esi]
						mov ah, [esi+1]
						mov dl, [esi+2]

						mov esi, pC24
						mov bl, [esi]
						mov bh, [esi+1]
						mov dh, [esi+2]

						mov edi, d
						mov esi, l
						
						// Line1
						// Pixel 1 = +0
						mov [edi], al
						mov [edi+1], ah
						mov [edi+2], dl

						// Pixel 2 = +3
						mov [edi+ecx], al
						mov [edi+1+ecx], ah
						mov [edi+2+ecx], dl

						// Pixel 3 = +6
						mov [edi+ecx*2], al
						mov [edi+1+ecx*2], ah
						mov [edi+2+ecx*2], dl

						// Pixel 4 = +9
						mov [edi+9], al
						mov [edi+1+9], ah
						mov [edi+2+9], dl

						// Pixel 5 = +12
						mov [edi+ecx*4], al
						mov [edi+1+ecx*4], ah
						mov [edi+2+ecx*4], dl

						// Pixel 6 = +15
						mov [edi+15], al
						mov [edi+1+15], ah
						mov [edi+2+15], dl

						// Pixel 7 = +18
						mov [edi+18], al
						mov [edi+1+18], ah
						mov [edi+2+18], dl

						// Pixel 8 = +21
						mov [edi+21], bl
						mov [edi+1+21], bh
						mov [edi+2+21], dh

						// Line2
						// Pixel 1 = +0
						add edi, esi

						mov [edi], al
						mov [edi+1], ah
						mov [edi+2], dl

						// Pixel 2 = +3
						mov [edi+ecx], al
						mov [edi+1+ecx], ah
						mov [edi+2+ecx], dl

						// Pixel 3 = +6
						mov [edi+ecx*2], al
						mov [edi+1+ecx*2], ah
						mov [edi+2+ecx*2], dl

						// Pixel 4 = +9
						mov [edi+9], al
						mov [edi+1+9], ah
						mov [edi+2+9], dl


						// Pixel 5 = +12
						mov [edi+ecx*4], al
						mov [edi+1+ecx*4], ah
						mov [edi+2+ecx*4], dl

						// Pixel 6 = +15
						mov [edi+15], al
						mov [edi+1+15], ah
						mov [edi+2+15], dl

						// Pixel 7 = +18
						mov [edi+18], al
						mov [edi+1+18], ah
						mov [edi+2+18], dl

						// Pixel 8 = +21
						mov [edi+21], bl
						mov [edi+1+21], bh
						mov [edi+2+21], dh


						// Line3
						// Pixel 1 = +0
						add edi, esi

						mov [edi], al
						mov [edi+1], ah
						mov [edi+2], dl

						// Pixel 2 = +3
						mov [edi+ecx], al
						mov [edi+1+ecx], ah
						mov [edi+2+ecx], dl

						// Pixel 3 = +6
						mov [edi+ecx*2], al
						mov [edi+1+ecx*2], ah
						mov [edi+2+ecx*2], dl

						// Pixel 4 = +9
						mov [edi+9], al
						mov [edi+1+9], ah
						mov [edi+2+9], dl


						// Pixel 5 = +12
						mov [edi+ecx*4], al
						mov [edi+1+ecx*4], ah
						mov [edi+2+ecx*4], dl

						// Pixel 6 = +15
						mov [edi+15], al
						mov [edi+1+15], ah
						mov [edi+2+15], dl

						// Pixel 7 = +18
						mov [edi+18], al
						mov [edi+1+18], ah
						mov [edi+2+18], dl

						// Pixel 8 = +21
						mov [edi+21], bl
						mov [edi+1+21], bh
						mov [edi+2+21], dh


						push eax
						mov eax,nWhite
						or eax,eax
						jne White24
						pop eax

						// Line4
						// Pixel 1 = +0
						add edi, esi

						mov [edi], al
						mov [edi+1], ah
						mov [edi+2], dl

						// Pixel 2 = +3
						mov [edi+ecx], al
						mov [edi+1+ecx], ah
						mov [edi+2+ecx], dl

						// Pixel 3 = +6
						mov [edi+ecx*2], al
						mov [edi+1+ecx*2], ah
						mov [edi+2+ecx*2], dl

						// Pixel 4 = +9
						mov [edi+9], al
						mov [edi+1+9], ah
						mov [edi+2+9], dl


						// Pixel 5 = +12
						mov [edi+ecx*4], al
						mov [edi+1+ecx*4], ah
						mov [edi+2+ecx*4], dl

						// Pixel 6 = +15
						mov [edi+15], al
						mov [edi+1+15], ah
						mov [edi+2+15], dl

						// Pixel 7 = +18
						mov [edi+18], al
						mov [edi+1+18], ah
						mov [edi+2+18], dl

						// Pixel 8 = +21
						mov [edi+21], bl
						mov [edi+1+21], bh
						mov [edi+2+21], dh

						
						// Line5
						// Pixel 1 = +0
						add edi, esi

						mov [edi], al
						mov [edi+1], ah
						mov [edi+2], dl

						// Pixel 2 = +3
						mov [edi+ecx], al
						mov [edi+1+ecx], ah
						mov [edi+2+ecx], dl

						// Pixel 3 = +6
						mov [edi+ecx*2], al
						mov [edi+1+ecx*2], ah
						mov [edi+2+ecx*2], dl

						// Pixel 4 = +9
						mov [edi+9], al
						mov [edi+1+9], ah
						mov [edi+2+9], dl


						// Pixel 5 = +12
						mov [edi+ecx*4], al
						mov [edi+1+ecx*4], ah
						mov [edi+2+ecx*4], dl

						// Pixel 6 = +15
						mov [edi+15], al
						mov [edi+1+15], ah
						mov [edi+2+15], dl

						// Pixel 7 = +18
						mov [edi+18], al
						mov [edi+1+18], ah
						mov [edi+2+18], dl

						// Pixel 8 = +21
						mov [edi+21], bl
						mov [edi+1+21], bh
						mov [edi+2+21], dh
						jmp NoWhite24

White24:

						pop eax

						// Line4
						// Pixel 1 = +0
						add edi, esi

						mov [edi], al
						mov [edi+1], ah
						mov [edi+2], dl

						// Pixel 2 = +3
						mov [edi+ecx], al
						mov [edi+1+ecx], ah
						mov [edi+2+ecx], dl

						// Pixel 3 = +6
						mov [edi+ecx*2], al
						mov [edi+1+ecx*2], ah
						mov [edi+2+ecx*2], dl

						// Pixel 4 = +9
						mov [edi+9], 0xff
						mov [edi+1+9], 0xff
						mov [edi+2+9], 0xff

						// Pixel 5 = +12
						mov [edi+ecx*4], al
						mov [edi+1+ecx*4], ah
						mov [edi+2+ecx*4], bh

						// Pixel 6 = +15
						mov [edi+15], al
						mov [edi+1+15], ah
						mov [edi+2+15], dl

						// Pixel 7 = +18
						mov [edi+18], al
						mov [edi+1+18], ah
						mov [edi+2+18], dl

						// Pixel 8 = +21
						mov [edi+21], bl
						mov [edi+1+21], bh
						mov [edi+2+21], dh

						
						// Line5
						// Pixel 1 = +0
						add edi, esi

						mov [edi], al
						mov [edi+1], ah
						mov [edi+2], dl

						// Pixel 2 = +3
						mov [edi+ecx], al
						mov [edi+1+ecx], ah
						mov [edi+2+ecx], dl

						// Pixel 3 = +6
						mov [edi+ecx*2], al
						mov [edi+1+ecx*2], ah
						mov [edi+2+ecx*2], dl

						// Pixel 4 = +9
						mov [edi+9], 0xff
						mov [edi+1+9], 0xff
						mov [edi+2+9], 0xff

						// Pixel 5 = +12
						mov [edi+ecx*4], al
						mov [edi+1+ecx*4], ah
						mov [edi+2+ecx*4], dl

						// Pixel 6 = +15
						mov [edi+15], al
						mov [edi+1+15], ah
						mov [edi+2+15], dl

						// Pixel 7 = +18
						mov [edi+18], al
						mov [edi+1+18], ah
						mov [edi+2+18], dl

						// Pixel 8 = +21
						mov [edi+21], bl
						mov [edi+1+21], bh
						mov [edi+2+21], dh

NoWhite24:

						// Line6
						// Pixel 1 = +0
						add edi, esi

						mov [edi], al
						mov [edi+1], ah
						mov [edi+2], dl

						// Pixel 2 = +3
						mov [edi+ecx], al
						mov [edi+1+ecx], ah
						mov [edi+2+ecx], dl

						// Pixel 3 = +6
						mov [edi+ecx*2], al
						mov [edi+1+ecx*2], ah
						mov [edi+2+ecx*2], dl

						// Pixel 4 = +9
						mov [edi+9], al
						mov [edi+1+9], ah
						mov [edi+2+9], dl


						// Pixel 5 = +12
						mov [edi+ecx*4], al
						mov [edi+1+ecx*4], ah
						mov [edi+2+ecx*4], dl

						// Pixel 6 = +15
						mov [edi+15], al
						mov [edi+1+15], ah
						mov [edi+2+15], dl

						// Pixel 7 = +18
						mov [edi+18], al
						mov [edi+1+18], ah
						mov [edi+2+18], dl

						// Pixel 8 = +21
						mov [edi+21], bl
						mov [edi+1+21], bh
						mov [edi+2+21], dh					

						// Line7
						// Pixel 1 = +0
						add edi, esi

						mov [edi], al
						mov [edi+1], ah
						mov [edi+2], dl

						// Pixel 2 = +3
						mov [edi+ecx], al
						mov [edi+1+ecx], ah
						mov [edi+2+ecx], dl

						// Pixel 3 = +6
						mov [edi+ecx*2], al
						mov [edi+1+ecx*2], ah
						mov [edi+2+ecx*2], dl

						// Pixel 4 = +9
						mov [edi+9], al
						mov [edi+1+9], ah
						mov [edi+2+9], dl


						// Pixel 5 = +12
						mov [edi+ecx*4], al
						mov [edi+1+ecx*4], ah
						mov [edi+2+ecx*4], dl

						// Pixel 6 = +15
						mov [edi+15], al
						mov [edi+1+15], ah
						mov [edi+2+15], dl

						// Pixel 7 = +18
						mov [edi+18], al
						mov [edi+1+18], ah
						mov [edi+2+18], dl

						// Pixel 8 = +21
						mov [edi+21], bl
						mov [edi+1+21], bh
						mov [edi+2+21], dh
						
						// Line8
						// Pixel 1 = +0
						add edi, esi

						mov [edi], bl
						mov [edi+1], bh
						mov [edi+2], dh

						// Pixel 2 = +3
						mov [edi+ecx], bl
						mov [edi+1+ecx], bh
						mov [edi+2+ecx], dh

						// Pixel 3 = +6
						mov [edi+ecx*2], bl
						mov [edi+1+ecx*2], bh
						mov [edi+2+ecx*2], dh

						// Pixel 4 = +9
						mov [edi+9], bl
						mov [edi+1+9], bh
						mov [edi+2+9], dh


						// Pixel 5 = +12
						mov [edi+ecx*4], bl
						mov [edi+1+ecx*4], bh
						mov [edi+2+ecx*4], dh

						// Pixel 6 = +15
						mov [edi+15], bl
						mov [edi+1+15], bh
						mov [edi+2+15], dh

						// Pixel 7 = +18
						mov [edi+18], bl
						mov [edi+1+18], bh
						mov [edi+2+18], dh

						// Pixel 8 = +21
						mov [edi+21], bl
						mov [edi+1+21], bh
						mov [edi+2+21], dh

						
						pop esi
						pop edi
						pop ebx
						pop eax
						pop edx
						pop ecx
					}


	
	
	break; //24bpp

	case 32:

			if ((*s == 0) &&
				(pMainFrame->m_bShowTransparency))
			{
				nWhite = 0x00ffffff;
			}
			else
			{
				nWhite = 0;
			}

					if (((y)%8==7) || ((x)%8==7))
						c32 = g_pal32[C1];
					else
						c32= g_pal32[C2];

					_asm {

						push ecx
						push edx
						push eax
						push ebx
						push edi
						push esi

						mov ecx,4

						mov esi, s
						xor eax,eax
						mov al,[esi]
						shl eax,2 // 4 bits = 2^2
						add eax, p32
						mov edx, c32

						mov eax, [eax]

						mov edi, d
						mov ebx, l

						// Transparent color
						// added
						mov esi, eax
						or esi, nWhite										

						mov [edi], eax
						mov [edi+4],eax
						mov [edi+8], eax
						mov [edi+12],eax 
						mov [edi+16], eax
						mov [edi+20],eax
						mov [edi+24], eax
						mov [edi+28],edx //1
						add edi,ebx

						mov [edi], eax
						mov [edi+4],eax
						mov [edi+8], eax
						mov [edi+12],eax 
						mov [edi+16], eax
						mov [edi+20],eax
						mov [edi+24], eax
						mov [edi+28],edx //2
						add edi,ebx

						mov [edi], eax
						mov [edi+4],eax
						mov [edi+8], eax
						mov [edi+12],eax
						mov [edi+16], eax
						mov [edi+20],eax
						mov [edi+24], eax
						mov [edi+28],edx //3
						add edi,ebx

						mov [edi], eax
						mov [edi+4],eax
						mov [edi+8], eax
						mov [edi+12],esi 
						mov [edi+16], eax
						mov [edi+20],eax
						mov [edi+24], eax
						mov [edi+28],edx //4
						add edi,ebx
						
						mov [edi], eax
						mov [edi+4],eax
						mov [edi+8], eax
						mov [edi+12],esi
						mov [edi+16], eax
						mov [edi+20],eax
						mov [edi+24], eax
						mov [edi+28],edx //5

						add edi,ebx
						mov [edi], eax
						mov [edi+4],eax
						mov [edi+8], eax
						mov [edi+12],eax 
						mov [edi+16], eax
						mov [edi+20],eax
						mov [edi+24], eax
						mov [edi+28],edx //6

						add edi,ebx
						mov [edi], eax
						mov [edi+4],eax
						mov [edi+8], eax
						mov [edi+12],eax 
						mov [edi+16], eax
						mov [edi+20],eax
						mov [edi+24], eax
						mov [edi+28],edx //7
						add edi,ebx

						mov [edi], edx
						mov [edi+4],edx
						mov [edi+8], edx
						mov [edi+12],edx
						mov [edi+16], edx
						mov [edi+20],edx
						mov [edi+24], edx
						mov [edi+28],edx
						
						pop esi
						pop edi
						pop ebx
						pop eax
						pop edx
						pop ecx
					}

	break; // 32bpp
	}

}

void CObl4editView::OnInsert() 
{
	// TODO: Add your command handler code here
	CSS3Frame *pFrame;
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	CRect rect;
	GetClientRect (rect);
	CSize size = rect.Size();
	
	if (pDoc->m_oblData.GetSize()==0) {

		CDlgImageSize dlg;

		dlg.m_nLen = 4;
		dlg.m_nHei = 4;
		dlg.m_bAll = FALSE;

		if (dlg.DoModal()==IDOK)
		{
			pFrame = new CSS3Frame(dlg.m_nLen*8,dlg.m_nHei*8);
			pDoc->m_oblData.Add ( pFrame);
			Invalidate();
				
			SetModified();
			AdjustSB(size.cx, size.cy);
		}

		return;
	}

	pDoc->m_oblData[nCurrFrame];
	pFrame = new CSS3Frame(pDoc->m_oblData[nCurrFrame]->m_nLen,
		pDoc->m_oblData[nCurrFrame]->m_nHei);

	pDoc->m_oblData.InsertAt(nCurrFrame, pFrame);
	Invalidate();
		
	AdjustSB(size.cx, size.cy);
	SetModified();
}

void CObl4editView::OnUpdateInsert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;

	pCmdUI->Enable(TRUE);
	
}



void CObl4editView::OnDelete() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (pDoc->m_oblData.GetSize()==0) {
		return;
	}

	int nStatus = AfxMessageBox ("Deleting an image is an irreveable operation",
		MB_ICONEXCLAMATION | MB_YESNO);

	if (nStatus==IDYES) {
		delete pDoc->m_oblData[nCurrFrame];
		pDoc->m_oblData.RemoveAt(nCurrFrame);

		if ( (nCurrFrame == pDoc->m_oblData.GetSize())
			&& (pDoc->m_oblData.GetSize()!=0) )
			pDoc->m_oblData.m_nCurrFrame--;

		Invalidate();		
		
		CRect rect;
		GetClientRect (rect);
		CSize size = rect.Size();
		AdjustSB(size.cx, size.cy);

		SetModified();

	}

}

void CObl4editView::OnUpdateDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();
	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (pDoc->m_oblData.GetSize()==0) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}
	
}

void CObl4editView::OnEditmode() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_bEdit = TRUE;
	m_bZoomed = FALSE;

	CRect rect;
	GetClientRect (rect);
	CSize size = rect.Size();
	AdjustSB(size.cx, size.cy);
	
	Invalidate();

}

void CObl4editView::OnUpdateEditmode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pCmdUI-> SetRadio(m_bEdit && 
		!m_bZoomed);
}


void CObl4editView::OnEditzoom() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_bEdit = TRUE;
	m_bZoomed = TRUE;

	CRect rect;
	GetClientRect (rect);
	CSize size = rect.Size();	
	AdjustSB(size.cx, size.cy);
	
	Invalidate();
	
	
}

void CObl4editView::OnUpdateEditzoom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pCmdUI-> SetRadio(m_bEdit && 
		m_bZoomed);
	
}

void CObl4editView::OnTapestry() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_bEdit = FALSE;
	m_bZoomed = FALSE;

	CRect rect;
	GetClientRect (rect);
	CSize size = rect.Size();	
	AdjustSB(size.cx, size.cy);
	
	Invalidate();
	
}

void CObl4editView::OnUpdateTapestry(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pCmdUI-> SetRadio(!m_bEdit);
	
}

void CObl4editView::OnZoomzoom() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (m_bEdit ==FALSE)
	{
		m_bEdit=TRUE;
		m_bZoomed = TRUE;
		Invalidate();
		return;
	}

	m_bZoomed  = !m_bZoomed;

	CRect rect;
	GetClientRect (rect);
	CSize size = rect.Size();	
	AdjustSB(size.cx, size.cy);
	
	Invalidate();

}

void CObl4editView::OnUpdateZoomzoom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CObl4editView::OnKillFocus(CWnd* pNewWnd) 
{
	
	// TODO: Add your message handler code here
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();

	CView::OnKillFocus(pNewWnd);
	CObl4editDoc *pDoc = GetDocument();

#ifdef _DEBUG
	OutputDebugString ("OnKillFocus ()\n");
#endif

	ReleaseTool (0, CPoint (0,0), (UCHAR)-1, pMainFrame-> m_nTool);

	// TODO: Add your message handler code here
	if (m_bLockMouse==TRUE ) {
			ClipCursor(FALSE);
			m_bLockMouse=FALSE;
		}	
	
}

void CObl4editView::OnFramecounter() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	pMainFrame->m_bShowFrame = !pMainFrame->m_bShowFrame;
	Invalidate();
}

void CObl4editView::OnUpdateFramecounter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	pCmdUI->SetCheck(pMainFrame->m_bShowFrame);
}

void CObl4editView::OnColorselect() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	pMainFrame->m_nTool = IDM_COLORSELECT;
}

void CObl4editView::OnUpdateColorselect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	pCmdUI->SetRadio(pMainFrame->m_nTool == IDM_COLORSELECT);
}

void CObl4editView::OnShowpreview() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	m_bShowPreview = !m_bShowPreview ;

	if (m_bShowPreview== TRUE)
		m_wndPreview.ShowWindow (SW_SHOW);	
	else
		m_wndPreview.ShowWindow (SW_HIDE);	
}

void CObl4editView::OnUpdateShowpreview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	pCmdUI->SetCheck(m_bShowPreview);
	
}

void CObl4editView::OnSelect() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	pMainFrame->m_nTool = IDM_SELECT;
	
}

void CObl4editView::OnUpdateSelect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	pCmdUI->SetRadio(pMainFrame->m_nTool == IDM_SELECT);
}

void CObl4editView::TrackRect (CDot & dot1, CDot & dot2)
{
	CRectTracker rectTracker
		(CRect(dot1.m_nX,dot1.m_nY,dot1.m_nX,dot1.m_nY), CRectTracker::dottedLine);
	rectTracker.Track (this, dot2.Point(), TRUE, this);
}

void CObl4editView::DrawTrackRect( CDot & dot1, CDot & dot2)
{
	CRectTracker rectTracker
		(CRect(dot1.m_nX,dot1.m_nY,dot2.m_nX,dot2.m_nY), CRectTracker::dottedLine);
	//rectTracker.Track (this, dot2.Point(), TRUE, this);
	CClientDC dc(this);
	rectTracker.Draw( (CDC*) &dc);
}

int CObl4editView::CreatePreviewWindow()
{
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	
	CRect rectClient; 
	GetClientRect (rectClient);
	CSize sizeClient = rectClient.Size();
	
	CString strWndClass = AfxRegisterWndClass (
        CS_DBLCLKS | CS_OWNDC,                  // Class style
        AfxGetApp()->LoadStandardCursor (IDC_ARROW),   // Class cursor
        NULL,//(HBRUSH) (COLOR_3DFACE ),               // Class background brush
        NULL            // Class icon
        );

	CWinApp *pApp = AfxGetApp();
	int nPreviewLen = pApp->GetProfileInt ("Settings", "nPreviewLen", PREVIEW_LEN);
	int nPreviewHei = pApp->GetProfileInt ("Settings", "nPreviewHei", PREVIEW_HEI);

    m_wndPreview.CreateEx (
		WS_EX_TOOLWINDOW, 
			strWndClass, 
            "Preview",
			WS_OVERLAPPEDWINDOW | // Bad style
			WS_BORDER | WS_THICKFRAME ,
            50, 50,
			nPreviewLen, nPreviewHei,
            this->m_hWnd, NULL) ;
	
	if (m_bShowPreview== TRUE)
		m_wndPreview.ShowWindow (SW_SHOW);	
	else
		m_wndPreview.ShowWindow (SW_HIDE);	

	CObl4editDoc *pDoc = GetDocument();

	m_wndPreview.SetDocument(pDoc);
	
	return TRUE;
}

void CObl4editView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CView::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
#ifdef _DEBUG	
	//OutputDebugString ("OnShowWindow()\n");
#endif

}

void CObl4editView::OnMove(int x, int y) 
{
	CView::OnMove(x, y);
	
	// TODO: Add your message handler code here
#ifdef _DEBUG	
	//OutputDebugString ("OnMove()\n");
#endif

}

void CObl4editView::OnDuplicate() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();

	int nCurrFrame = pDoc->m_oblData.m_nCurrFrame;
	if (nCurrFrame+1 == pDoc->m_oblData.GetSize() ) {
		pDoc->m_oblData.
			Add	(new CSS3Frame ( pDoc->m_oblData.Current()));
	}
	else {

		pDoc->m_oblData.
			InsertAt ( nCurrFrame+1, new CSS3Frame ( pDoc->m_oblData.Current()));
	}

	pDoc->m_oblData.m_nCurrFrame ++;
	Invalidate();
	SetModified();
}

void CObl4editView::OnUpdateDuplicate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
}

void CObl4editView::SetModified()
{
	CObl4editDoc *pDoc = GetDocument();
	pDoc->SetModified();
}

void CObl4editView::OnEnlarge() 
{
	// TODO: Add your command handler code here
	CRect rect;
	GetClientRect (rect);
	CSize size = rect.Size();

	CObl4editDoc *pDoc = GetDocument();
	if (pDoc->m_oblData.Current()==NULL) return;
	
	if (AfxMessageBox ("Enlarge 2x - Confirm ?",
		MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		// 99/03/16 addon
		pDoc->m_oblData.Current()->Dirty();
		pDoc->m_oblData.Current()->Enlarge2x();
		Invalidate();
		SetModified();
		AdjustSB(size.cx, size.cy);
	}
}

void CObl4editView::OnUpdateEnlarge(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
	
}

void CObl4editView::OnResize() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	if (pDoc->m_oblData.Current()==NULL) return;
	
	CDlgImageSize dlg;
	if (pDoc->m_oblData.GetSize()>1)
		dlg.UnHideAll();

	dlg.m_nLen = pDoc->m_oblData.Current()->m_nLen /8;
	dlg.m_nHei = pDoc->m_oblData.Current()->m_nHei /8;
	dlg.m_bAll = FALSE;

	if (dlg.DoModal()==IDOK)
	{
		if (dlg.m_bAll==FALSE)
		{
			if ((dlg.m_nLen != (UINT)
				pDoc->m_oblData.Current()->m_nLen /8) ||
				(dlg.m_nHei != (UINT)
				pDoc->m_oblData.Current()->m_nHei /8))
			{
				// 99/03/16 addon
				pDoc->m_oblData.Current()->Dirty();
				pDoc->m_oblData.Current()->Resize(dlg.m_nLen*8,
					dlg.m_nHei*8);

				CRect rect;
				GetClientRect (rect);
				CSize size = rect.Size();
				AdjustSB(size.cx, size.cy);

				Invalidate();
				SetModified();

			}
		}
		else
		{
			int i;
			for (i=0; i<pDoc->m_oblData.GetSize(); i++)
			{

				// 99/03/16 addon
				pDoc->m_oblData[i]->Dirty();
				pDoc->m_oblData[i]->Resize(dlg.m_nLen*8,
				dlg.m_nHei*8);

			}

			CRect rect;
			GetClientRect (rect);
			CSize size = rect.Size();
			AdjustSB(size.cx, size.cy);

			Invalidate();
			SetModified();

		}
	}
}

void CObl4editView::OnUpdateResize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
	
}

void CObl4editView::OnCopy() 
{
	// TODO: Add your command handler code here
	CopyCurrentImageToClipboard();
}

void CObl4editView::OnUpdateCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
}

void CObl4editView::OnPaste() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	CMainFrame* pMainFrame = 
		(CMainFrame*) AfxGetMainWnd();

	UINT CF_OBL4 = pMainFrame->m_nOBL4FormatId;

	// Copy from Clipboard to buffer
    OpenClipboard();					
                    
    HANDLE hMem = GetClipboardData(CF_OBL4);

    if (hMem==NULL) // not OBL4
    {
		HANDLE hMem = GetClipboardData(CF_BITMAP);
		if (hMem==NULL)
		{
			// No supported data in clipboard
			CloseClipboard();
	        return;
		}
		
		CDlgPasteBmp dlg;
		dlg.m_nBpp = pMainFrame->m_nBpp;
		dlg.m_nMethod =0;
		if (dlg.DoModal()==IDOK)
		{

			BeginWaitCursor();

			CSS3Frame * pFrame  = 
				pDoc->BitmapToOBL4( 
					(HBITMAP) hMem, 
					dlg.m_nMethod);

			m_frmCopy = *pFrame;

			CloseClipboard();

			EndWaitCursor();

		}
		else
		{
			// DialogBox cancelled
			CloseClipboard();
			return;
		}
	
    }
	else
	{
		UINT *ptrMem = (UINT*) GlobalLock(hMem);

		int nLen = *ptrMem;
		int nHei = *(ptrMem+1);

		m_frmCopy.Set( nLen, nHei);
		if (m_frmCopy.m_pBitmap==NULL)
		{
			OutputDebugString("Warning: m_frmCopy.m_pBitmap == NULL\nClipboard copy operation halted!\n");
			CloseClipboard();
			return;
		}
	
		memcpy (m_frmCopy.m_pBitmap, ptrMem+2, 
		m_frmCopy.m_nLen * m_frmCopy.m_nHei);
		GlobalUnlock(hMem);

		CloseClipboard(); // Clean up
    }

	BOOL bAllowUndo = TRUE;

	// if no image in frame set then adding one
	if (pDoc->m_oblData.Current()==NULL)
	{
		CSS3Frame *pFrame = new CSS3Frame (&m_frmCopy);
		if (pFrame) 
		{
			pDoc->m_oblData.Add(pFrame);
			pDoc->m_oblData.m_nCurrFrame=0;
		}
		else
		{
			AfxMessageBox ("Internal error\nInsufficient memory",
				MB_OK | MB_ICONSTOP );
			return;
		}

		bAllowUndo = FALSE;
	}

	// Checking for sizing
	if 	((m_frmCopy.m_nLen == pDoc->m_oblData.Current()->m_nLen)
		&& (m_frmCopy.m_nHei == pDoc->m_oblData.Current()->m_nHei) )
	{
		// 99/04/16 addon
		if (bAllowUndo)
			pDoc->m_oblData.Current()->Dirty();
		pDoc->m_oblData.Current()->Replace (&m_frmCopy);
		Invalidate();
		SetModified();

	}
	else
	{
		if (AfxMessageBox ("Not same size - replace anyway?",
			MB_YESNO | MB_ICONQUESTION ) == IDYES) 
		{
			// 99/04/16 addon
			if (bAllowUndo)
				pDoc->m_oblData.Current()->Dirty();
			pDoc->m_oblData.Current()->Replace (&m_frmCopy);
			Invalidate();
			SetModified();

		}
	}

	Invalidate();

}

void CObl4editView::OnUpdatePaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	CMainFrame* pMainFrame = 
		(CMainFrame*) AfxGetMainWnd();

	UINT CF_OBL4 = pMainFrame->m_nOBL4FormatId;

	OpenClipboard();					                   
    HANDLE hMem = GetClipboardData(CF_BITMAP);
	CloseClipboard();
	pCmdUI->Enable (hMem!=NULL);

}

void CObl4editView::OnCut() 
{
	// TODO: Add your command handler code here
	CopyCurrentImageToClipboard();

	CObl4editDoc *pDoc = GetDocument();
	pDoc->m_oblData.Current()->Dirty();
	ZeroMemory (pDoc->m_oblData.Current()->m_pBitmap,
		pDoc->m_oblData.Current()->m_nLen *
		pDoc->m_oblData.Current()->m_nHei );

	Invalidate();
	SetModified();

}

void CObl4editView::OnUpdateCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
	
}

void CObl4editView::OnRainbow() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	if (pDoc->m_oblData.Current()==NULL) return;

	pDoc->m_oblData.Current()->Dirty();
	pDoc->m_oblData.Current()->RainbowEffect();

	Invalidate();
	SetModified();
	
}

void CObl4editView::OnUpdateRainbow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
	
}

void CObl4editView::OnInvert() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	pDoc->m_oblData.Current()->Dirty();
	pDoc->m_oblData.Current()->InverseColor();

	Invalidate();
	SetModified();
}

void CObl4editView::OnUpdateInvert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
}


void CObl4editView::OnSpreadhorz() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	// 99/03/16 addon
	pDoc->m_oblData.Current()->Dirty();
	pDoc->m_oblData.Current()->SpreadHorz();

	CRect rect;
	GetClientRect (rect);
	CSize size = rect.Size();
	AdjustSB(size.cx, size.cy);

	Invalidate();
	SetModified();
	
}

void CObl4editView::OnUpdateSpreadhorz(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
}

void CObl4editView::OnSpreadvert() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	// 99/03/16 addon
	pDoc->m_oblData.Current()->Dirty();
	pDoc->m_oblData.Current()->SpreadVert();

	CRect rect;
	GetClientRect (rect);
	CSize size = rect.Size();
	AdjustSB(size.cx, size.cy);
	
	Invalidate();
	SetModified();

}

void CObl4editView::OnUpdateSpreadvert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
}

void CObl4editView::OnRainbowExclude() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	if (pDoc->m_oblData.Current()==NULL) return;

	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();

	pDoc->m_oblData.Current()->Dirty();
	pDoc->m_oblData.Current()->RainbowEffectExclude(pMainFrame->m_nPenColor);

	Invalidate();
	SetModified();

}

void CObl4editView::OnUpdateRainbowExclude(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
}

void CObl4editView::OnShrink() 
{
	// TODO: Add your command handler code here
	CObl4editDoc *pDoc = GetDocument();
	if (pDoc->m_oblData.Current()==NULL) return;

	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();

	if (AfxMessageBox ("Shrink the image?",
			MB_YESNO | MB_ICONQUESTION ) == IDYES) 		
	{
		// 99/03/16 addon
		pDoc->m_oblData.Current()->Dirty();
		pDoc->m_oblData.Current()->Shrink();
		Invalidate();
		SetModified();
	}
}

void CObl4editView::OnUpdateShrink(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = GetDocument();

	if ( pDoc->m_oblData.Current()==NULL) {
		pCmdUI->Enable (FALSE);
	}
	else {
		pCmdUI->Enable (TRUE);
	}
}

BOOL CObl4editView::CopyCurrentImageToClipboard()
{
	CObl4editDoc *pDoc = GetDocument();
	CSS3Frame & frame = * pDoc->m_oblData.Current();
	m_frmCopy.Replace (&frame); 	

	CMainFrame* pMainFrame = 
		(CMainFrame*) AfxGetMainWnd();

	UINT CF_OBL4 = pMainFrame->m_nOBL4FormatId;

    HDC hdc = ::GetDC(0); 
    
	HBITMAP hbitmap = 
		pMainFrame->MakeBitmap(frame.m_nLen,
		frame.m_nHei, 
		(BYTE*) frame.m_pBitmap , 
		hdc);

    ::ReleaseDC(0, hdc);
                                        
    if (hbitmap)
	{

        OpenClipboard();
        EmptyClipboard();
                        
        // Copying as bitmat
        SetClipboardData (CF_BITMAP, hbitmap);

        // Copying as OBL4 Format
        HANDLE hMem = GlobalAlloc(GHND, 
			frame.m_nLen*frame.m_nHei+16);
        UINT *ptrMem = (UINT*) GlobalLock(hMem);
        memcpy(ptrMem+2, frame.m_pBitmap, 
			frame.m_nLen*frame.m_nHei);

        *ptrMem = frame.m_nLen;
		*(ptrMem+1) = frame.m_nHei;
		GlobalUnlock(hMem);
        SetClipboardData (CF_OBL4, hMem);
		
        CloseClipboard();
	}
	return TRUE;
}

void CObl4editView::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This function was added by the Pop-up Menu component

	BOOL bContextMenu=FALSE;

	CRect *rectDraw = CalcMouseRect();	// calc draw-able area
	CPoint pointScreen = point;

	if (rectDraw!=NULL)
	{
		if ((pointScreen.x> rectDraw->right) || (pointScreen.y>rectDraw->bottom) ||
			  (m_bEdit==FALSE)  )	{				
			bContextMenu=TRUE;

		}
		delete rectDraw;
	}
	else
	{
		bContextMenu = TRUE;;
	}

	if (bContextMenu)
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_OBL4EDIT_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		CWnd* pWndPopupOwner = this;
		while (pWndPopupOwner->GetStyle() & WS_CHILD)
		{
			pWndPopupOwner = pWndPopupOwner->GetParent();
		}

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

BOOL CObl4editView::PreTranslateMessage(MSG* pMsg)
{
	// CG: This block was added by the Pop-up Menu component
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

	}

	return CView::PreTranslateMessage(pMsg);
}

void CObl4editView::OnIsometricgrid() 
{
	// TODO: Add your command handler code here
	CMainFrame * pMainWnd = (CMainFrame *) AfxGetMainWnd();

	pMainWnd->m_bIsometric = ! pMainWnd->m_bIsometric;
	Invalidate();
}

void CObl4editView::OnUpdateIsometricgrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame * pMainWnd = (CMainFrame *) AfxGetMainWnd();

	pCmdUI->SetCheck (pMainWnd->m_bIsometric);
}

BOOL CObl4editView::IsoGrildSQR(int x, int y)
{
	CMainFrame * pMainWnd = (CMainFrame *) AfxGetMainWnd();

	if (pMainWnd->m_bIsometric)
	{
		int xx = x%32;
		int yy= y%16;
		if (yy<8)
			return ((xx== 15-yy*2) ||
				(xx== 15-yy*2-1) ||
				(xx== 16+yy*2) ||
				(xx== 16+yy*2+1));
		else
			return ((xx== (yy%8)*2) ||
				(xx== (yy%8)*2+1) ||
				(xx== 31-(yy%8)*2) ||
				(xx== 31-(yy%8)*2-1));
	}

	return FALSE;
}

LRESULT CObl4editView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
    switch(message)
    {
        case RESET_VIEW_ORG:
            m_nMX =0;
            m_nMY =0;
            Invalidate();
        break;
    } 

	return CView::WindowProc(message, wParam, lParam);
}
