// ColorListBox.cpp : implementation file
//

// This class displays the new color palette, for Statics System V4.0
// applications. The 256-Colors selector of previous version is now
// replaced with one, that fully support DDRAW.


#include "stdafx.h"
#include "obl4edit.h"
#include "ColorListBox.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern WORD		g_pal16[256];
extern USER_24bpp	g_pal24[256];
extern UINT		g_pal32[256];

/////////////////////////////////////////////////////////////////////////////
// CColorListBox

CColorListBox::CColorListBox()
{
}

CColorListBox::~CColorListBox()
{
}


BEGIN_MESSAGE_MAP(CColorListBox, CWnd)
	//{{AFX_MSG_MAP(CColorListBox)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorListBox message handlers

BOOL CColorListBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWnd::PreCreateWindow(cs);
}


BOOL CColorListBox::Fail (char *szMsg)
{
    OutputDebugString( szMsg );
    return FALSE;
}

void CColorListBox::OnPaint() 
{
	// TODO: Add your message handler code here
	
	int x,y,xx,yy;
	char c;
	short c16;
	USER_24bpp c24;
	int c32;

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

	if (pMainFrame->m_lpDDSBack2->
		Lock(NULL, &ddsurfdesc, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)
	{
		OutputDebugString("DDraw: Lock failed!\n");
		pMainFrame->ReleaseObjects();
		PostQuitMessage(0);
		return; 
	}

	char *pDest = (char*)ddsurfdesc.lpSurface; 

	switch (pMainFrame->m_nBpp)
	{
	case 8:

	for (y=0; y<15; y++)
	{
		for (x=0; x<16; x++)
		{
			for (yy=0; yy<16; yy++)
			{
				for (xx=0; xx<16; xx++)
				{
					if ((xx%8 == 7) || (yy %8==7))
						c =0;
					else
						c = x+16*y+16;

					*(pDest + x*8 +xx + (y*8+yy)* ddsurfdesc.lPitch) =
						c;

				}

			}
		}
	}
	break; // 8 bpp

	case 16:

	for (y=0; y<15; y++)
	{
		for (x=0; x<16; x++)
		{
			for (yy=0; yy<16; yy++)
			{
				for (xx=0; xx<16; xx++)
				{
					if ((xx%8 == 7) || (yy %8==7))
						c16 =0;
					else
						c16 = g_pal16[x+16*y+16];

					* ((short*)(pDest + (x*8 +xx)*2 + (y*8+yy)* ddsurfdesc.lPitch) )
						=	c16;

				}

			}
		}
	}
	break; // 16 bpp

	case 24:

	for (y=0; y<15; y++)
	{
		for (x=0; x<16; x++)
		{
			for (yy=0; yy<16; yy++)
			{
				for (xx=0; xx<16; xx++)
				{
					if ((xx%8 == 7) || (yy %8==7))
						c24 = g_pal24[0];
					else
						c24 = g_pal24[x+16*y+16];

					* ((USER_24bpp*)(pDest + (x*8 +xx)*3 + (y*8+yy)* ddsurfdesc.lPitch) )
						=	c24;

				}

			}
		}
	}
	break; // 24 bpp


	case 32:

	for (y=0; y<15; y++)
	{
		for (x=0; x<16; x++)
		{
			for (yy=0; yy<16; yy++)
			{
				for (xx=0; xx<16; xx++)
				{
					if ((xx%8 == 7) || (yy %8==7))
						c32 =0;
					else
						c32 = g_pal32[x+16*y+16];

					*((int*)(pDest + (x*8 +xx)*4 + (y*8+yy)* ddsurfdesc.lPitch)) =
						c32;

				}

			}
		}
	}
	break; // 32 bpp


	}


	if (pMainFrame->m_lpDDSBack2->
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

    // We have associate the clipper with this window
    if ( FAILED( pMainFrame->m_lpDDClipper->SetHWnd( 0, this->m_hWnd ) ) )
	{
         OutputDebugString(  "Couldn't set the hwnd to ColorListBox.\n" );
		 return;
    }


   // Blt from the second surface unto the display surface
   // and fill our little view.
   if ( FAILED( pMainFrame->m_lpDDSPrimary->Blt( &rectView, 
	   pMainFrame->m_lpDDSBack2, &rectDest,
                    DDBLT_WAIT, NULL ) ) )
  
	{
#ifdef _DEBUG
	   OutputDebugString("DDraw: Couldn't blt! [CColorListBox]\n");
#endif
		PostMessage(WM_PAINT);
		return ;
    }

    //  Now we'll reassocite the clipper with the MainFrame
    if ( FAILED( pMainFrame->m_lpDDClipper->SetHWnd( 0, pMainFrame->m_hWnd ) ) )
	{
         Fail(  "Couldn't reset the hwnd.\n" );
		 return;
    }


	CPaintDC dc(this); // device context for painting
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CColorListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int nColor;
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

    if (nFlags & MK_LBUTTON)              
    {				
        if ((point.y/8 <14) && (point.x/8<16))					
        {				
				nColor = (char) (                                     
                (point.y /8)*16 			       
                + (point.x/8) +16);					

           if (pMainFrame->m_nPenColor!=nColor)
		   {
				pMainFrame->m_nPenColor=nColor;
				m_pwndParent->Invalidate();
				
		   }
        }			   
    }
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CColorListBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int nColor;
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

    if (nFlags & MK_LBUTTON)              
    {				
        if ((point.y/8 <14) && (point.x/8<16))					
        {				
				nColor = (char) (                                     
                (point.y / 8) *16			       
                + (point.x/8) +16);					

           if (pMainFrame->m_nPenColor!=nColor)
		   {
				pMainFrame->m_nPenColor=nColor;
				m_pwndParent->Invalidate();
				
		   }
        }			   
    }
	
	CWnd::OnMouseMove(nFlags, point);
}

void CColorListBox::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
}
