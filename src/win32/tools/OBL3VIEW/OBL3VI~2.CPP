// OBL3VIEWView.cpp : implementation of the COBL3VIEWView class
//

#include "stdafx.h"
#include "OBL3VIEW.h"

#include "OBL3VIEWDoc.h"
#include "OBL3VIEWView.h"

#include "draw.h"

/////////////////////////////////////////////////////////////////////////////
// External vars

extern CDraw g_Draw;



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWView

IMPLEMENT_DYNCREATE(COBL3VIEWView, CView)

BEGIN_MESSAGE_MAP(COBL3VIEWView, CView)
	//{{AFX_MSG_MAP(COBL3VIEWView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWView construction/destruction

COBL3VIEWView::COBL3VIEWView()
{
	// TODO: add construction code here

}

COBL3VIEWView::~COBL3VIEWView()
{
}

BOOL COBL3VIEWView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWView drawing

void COBL3VIEWView::OnDraw(CDC* pDC)
{
	COBL3VIEWDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWView printing

BOOL COBL3VIEWView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COBL3VIEWView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COBL3VIEWView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWView diagnostics

#ifdef _DEBUG
void COBL3VIEWView::AssertValid() const
{
	CView::AssertValid();
}

void COBL3VIEWView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COBL3VIEWDoc* COBL3VIEWView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COBL3VIEWDoc)));
	return (COBL3VIEWDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWView message handlers

void COBL3VIEWView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

    
    COBL3VIEWDoc *pDoc = GetDocument();
    if (pDoc->m_obl3Filter.m_arrFrames.GetSize()==0)
        return;

//void GetClientRect( LPRECT lpRect ) const;

    CRect l_rectClient;
    GetClientRect(l_rectClient);

    CSS3Frame *pFrame = (CSS3Frame *) (pDoc->m_obl3Filter.m_arrFrames[0]);   

    int l_nHorz = l_rectClient.Width()/pFrame->m_nLen; 
            
    if ((l_nHorz==0) &&(l_rectClient.Width()%pFrame->m_nLen)) l_nHorz++;

    int l_nVert = l_rectClient.Height()/pFrame->m_nHei;  
            
    if ((l_nVert==0) && (l_rectClient.Height()%pFrame->m_nHei)) l_nVert++;

    int x;
    int y;  
    int l_nCpt =0;

    for (y=0; y< l_nVert; y++)
    {
        for (x=0;x<l_nHorz; x++)
        {
            if (l_nCpt>= pDoc->m_obl3Filter.m_arrFrames.GetSize())
                return;
            pFrame = (CSS3Frame *) 
                (pDoc->m_obl3Filter.m_arrFrames[l_nCpt]);                           
        
            HBITMAP hBitmap = g_Draw.MakeBitmap(pFrame->m_nLen ,pFrame->m_nHei, 
                (UCHAR*)pFrame->m_pBitmap, dc.m_hDC);
            g_Draw.PutBitmap(dc.m_hDC, hBitmap,x*pFrame->m_nLen ,
                                               y*pFrame->m_nHei);
            if (hBitmap) DeleteObject(hBitmap);

            l_nCpt++;
        }    
    } 

	// Do not call CView::OnPaint() for painting messages
}
