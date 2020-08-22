
//
// Preview.c
//

#include "include.h"
#include "struc.h"
#include "pal.h"
#include "WinEasy.h"
#include "resource.h"
#include "const.h"
#include "WinFb.h"
#include "obl3.h"
#include "draw.h"

extern HPALETTE hpal;
// OBL3 vars............................................
extern USER_OBL3HEADER sHeader;
extern USER_OBL3   *psObl3;
extern DWORD       iMx;
extern DWORD       iMy;
extern HWND hAppWnd;

// Yuck! don't crash my program..........................
extern int         bCritical;


LRESULT CALLBACK PreviewWndProc 
        (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);


HWND CreatePreviewWindow(HINSTANCE hInstance,
                         HWND hwnd)
{
    USER_WINDOW sUserWnd;
    uint cx,cy;
    ATOM atom;

    WNDCLASS wndclass;

    cx  = GetSystemMetrics (SM_CXSCREEN)  ;
    cy  = GetSystemMetrics (SM_CYSCREEN)  ;

    // Create a Windoz for the application
    sUserWnd.iClassStyle= CS_HREDRAW | CS_VREDRAW | 
                             CS_OWNDC | CS_DBLCLKS;
    sUserWnd.iClassProc = PreviewWndProc;
    sUserWnd.hIcon      = LoadIcon(hInstance, M2INT(IDI_ICON01));
    sUserWnd.hCursor    = LoadCursor(NULL,M2INT(IDC_ARROW));
    sUserWnd.hBrush     = (HBRUSH) GetStockObject(WHITE_BRUSH);
    sUserWnd.cMenuName  = NULL;
    sUserWnd.cClassName = "Preview";
        
    sUserWnd.iWndExStyle= 0;
    sUserWnd.cWndTitle  = "Preview";
    sUserWnd.iWndStyle  = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN
                          ;
    sUserWnd.iWndLen    = 640/4;			    
    sUserWnd.iWndHei    = 320/2;
    sUserWnd.iWndX      = (cx-sUserWnd.iWndLen);
    sUserWnd.iWndY      = (cy-sUserWnd.iWndHei);

    wndclass.style         = sUserWnd.iClassStyle;
    wndclass.lpfnWndProc   = sUserWnd.iClassProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = hInstance ;
    wndclass.hIcon         = sUserWnd.hIcon ;//LoadIcon (hInstance, "ABC") ;
    wndclass.hCursor       = sUserWnd.hCursor; //LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = sUserWnd.hBrush; //(HBRUSH) GetStockObject (GRAY_BRUSH) ;
    wndclass.lpszMenuName  = sUserWnd.cMenuName;//M2INT(AppMenu);
    wndclass.lpszClassName = sUserWnd.cClassName;//AppName;

    atom = RegisterClass (&wndclass);
    
    hwnd =  CreateWindowEx( 
				WS_EX_TOOLWINDOW | 
                 WS_EX_WINDOWEDGE,      /* no extended styles        */ 
			    M2INT(atom),            /* window class              */ 
				sUserWnd.cWndTitle,  /* text for window title bar */ 
			    sUserWnd.iWndStyle,  /* window styles             */ 
				 
				sUserWnd.iWndX,	    /* default horizontal position */ 
			    sUserWnd.iWndY,		/* default vertical position   */ 
				sUserWnd.iWndLen,	/* default width               */ 
			    sUserWnd.iWndHei,	/* default height              */ 
				(HWND) hwnd,			/* no parent for overlapped windows  */ 
			    (HMENU) NULL,			/* window class menu                 */ 
				hInstance,				/* instance owning this window       */ 
                (LPVOID) NULL           /* pointer not needed                */ 
                  );


    return hwnd;


}





//**********************************************************************************
//
// PreviewWndProc: This is the message handler to the Child PopUp Window
//                 The Preview Window Proc handler
//
//*********************************************************************************
LRESULT CALLBACK PreviewWndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{        
PAINTSTRUCT ps ;
    HDC         hdc ;
	BOOL fAppActive;
    HBITMAP hbitmap;
    RECT sRect;
    int iLen;
    int iHei;

		switch (iMsg)
		{

        case WM_KEYDOWN:
            SendMessage(hAppWnd, WM_KEYDOWN, wParam, lParam);

        return 0;

        case WM_CLOSE :
            SendMessage(hAppWnd, WM_COMMAND,
                IDM_HASPREVIEW, 0);
        return 0 ;
		
		case WM_LBUTTONDBLCLK:
        return TRUE;

		case WM_LBUTTONDOWN:
        break;

        case WM_RBUTTONDOWN:
        break;

        case WM_ACTIVATEAPP:

            fAppActive = (BOOL)wParam;

        //*** Remap the system colors and deal with the palette
               
           //AppActivate(fAppActive);
           AppActivate(FALSE);
           if (hpal)
           {
            hdc = GetDC(hwnd);

            UnrealizeObject(hpal);
            SelectPalette(hdc, hpal, FALSE);
            RealizePalette(hdc);
            ReleaseDC(hwnd, hdc);
           }
        
           break;
	
		        case WM_CREATE :

				if (hpal)
				{
         		
					hdc = GetDC(hwnd);

					UnrealizeObject(hpal);
					SelectPalette(hdc, hpal, FALSE);
					RealizePalette(hdc);				
					
					ReleaseDC(hwnd, hdc);
 			        //FillbitPalette(bitPalette);

				}

				return 0 ;



				case WM_PAINT :

                    if (bCritical)
                    {
                        hdc = BeginPaint(hwnd,&ps);
           				EndPaint(hwnd,&ps);
                        return 0;
                    }

                    GetClientRect(hwnd, &sRect);

                    iLen = max(sRect.right - sRect.left,0);
                    iHei = max(sRect.bottom - sRect.top,0);

                    hdc = BeginPaint(hwnd,&ps);
                    hbitmap = MakeBitmap(
                                sHeader.iLen *OBL3FNT, 
                                sHeader.iHei *OBL3FNT, 
                                psObl3->PtrBits, 
                                hdc);

	                if (hbitmap)
            	    { 
	    	            PutBitmap( hdc, 
                           hbitmap,
                           (iLen-sHeader.iLen *OBL3FNT)/2,
                           (iHei-sHeader.iHei *OBL3FNT) /2) ;
   	                    DeleteObject(hbitmap);
            	    }

					//PaintPaletteChildWindowWithRect( hdc);
                    //PaintPaletteWithBitmap(hdc, bitPalette);
       				EndPaint(hwnd,&ps);
 			    return 0L;
	
		}
         return DefWindowProc (hwnd, iMsg, wParam, lParam) ;

	}        


