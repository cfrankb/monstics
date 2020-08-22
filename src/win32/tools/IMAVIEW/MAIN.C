/*-------------- ----------------------------------------------

  HELLOWIN.C -- Displays "Hello, Windows 95!" in client area
                 (c) Charles Petzold, 1996

        	  Modified to become

	MAIN.C  -- a nice test of how the world doesn't work right.

  ------------------------------------------------------------*/

// *** INCLUDED FILES ***
#include "include.h"
#include "ims.h"
#include "menu.h"
#include "const.h"
#include "include.h"
#include "Common.h"
#include "draw.h"
#include "resource.h"
#include "dialog.h"
#include "include.h"
#include "menu.h"
#include "ima3.h"
#include "struc.h"
#include "user_err.h"
#include "popfile.h"

// ***   CONSTANTES   ***

const char SansTitre[] = "(Sans Titre)";
char AppTitle[] = "Imaview pour Windows";

// ***  GLOBAL VARS  ***

HWND			hAppWnd;				// HWND instance for the mother window
HWND			hwnd;					// HWND instance for the mother window
HINSTANCE		hAppInstance;			// Application instance
TEXTMETRIC		tm ;					// Font info obj    

char PenColor =0;                       // Pencil color
HWND hchildwnd;                         // ????
HWND hgrildwnd;                         // My color grild
BOOL HasChanged;
USER_MOUSE mouse;                       // Mouse structure
HWND  extern hDocWnd;

USER_STDIMA stdima;
char        *bitdata;
int         Zoom=1;

extern int Zoom;
extern USER_STDIMA stdima;
extern char        *bitdata;
extern int         Zoom;

// Prototypes
char *Ima2Bitmap(USER_STDIMA sStdIma, char *ImaData);
int LoadIma(const char *filename, USER_STDIMA *sStdIma, char **ppImaData);
int LoadIma(const char *, USER_STDIMA *, char **);
char *Ima2Bitmap(USER_STDIMA sStdIma, char *ImaData);
HBITMAP MakeBitmap(int len, int hei, unsigned char *bits, HDC hdc);
char *StretchBitmap(USER_STDIMA sStdIma, char *ImaData, uint Factor);
LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
HWND RegisterAndCreateWindow(HINSTANCE hInstance, USER_WINDOW sUserWindow);


void ChangeZoom(HWND hwnd, HMENU hmenu)
{

    switch(Zoom)
    {
    case 1:
        Menu_CheckItem(hmenu, IDM_1x, FALSE);
        break;

    case 2:
        Menu_CheckItem(hmenu, IDM_2x, FALSE);
        break;

    case 4:
        Menu_CheckItem(hmenu, IDM_4x, FALSE);
        break;


    }

}


//
//
//
int Load(HWND hwnd)
{

    static char szFilter_IMA[] = "Statics Images (*.IMA)\0*.ima\0\0"  ;   
	static char Filename[1024];
	static char Titlename[1024];

    char **ppIma;
    USER_STDIMA stdima2;
    int Code;

	        PopFileInitialize (hwnd, szFilter_IMA) ;
            if ((PopFileOpenDlg 
			    (hAppWnd, 
			    Filename, 
			    Titlename) 	)==0)          
                return FALSE;

            ppIma = malloc(4);
            Code = LoadIma(Filename, &stdima2,  ppIma);

            if (Code==TRUE)
            {


                    stdima.len = stdima2.len;
                    stdima.hei = stdima2.hei;
                    
                    free (bitdata);

                    bitdata = Ima2Bitmap(stdima, *ppIma);
                    free(*ppIma);

                    //Zoom=1;
                    InvalidateRect(hwnd, NULL, TRUE);
                    DoCaption(hwnd, AppTitle, Filename, FALSE);

                    
                    UpdateWindow(hwnd);
                  

              }

            else

			  switch ( Code)
			  {
			    case err_fileopen:
	 	          MessageBox(hwnd, "La lecture du fichier a échouée", 
				              "Erreur de lecture",
							  MB_OK | MB_ICONSTOP);
				break;

			    case err_format:
	 	          MessageBox(hwnd, "Format incompatible", 
				              "Erreur de fichier",
							  MB_OK | MB_ICONSTOP);
			    break;

			  }
    
    if (ppIma)
        free(ppIma);


    return FALSE;
};

//
//
//


long msg_Command(HWND hwnd, 
                 UINT iMsg, 
                 WPARAM wParam, 
                 LPARAM lParam 
                 )
{ 
    
    static PropInUse;
    HMENU hmenu;


    switch (LOWORD(wParam))
	{    
  
    case IDM_1x:
        hmenu = GetMenu(hwnd);
        ChangeZoom(hwnd, hmenu);
        Menu_CheckItem(hmenu, IDM_1x, TRUE);
        
        Zoom=1;
        InvalidateRect(hwnd, NULL, TRUE);
        UpdateWindow(hwnd);
        break;

    case IDM_2x:
        hmenu = GetMenu(hwnd);
        ChangeZoom(hwnd, hmenu);
        Menu_CheckItem(hmenu, IDM_2x, TRUE);

        Zoom=2;
        InvalidateRect(hwnd, NULL, TRUE);
        UpdateWindow(hwnd);
        break;

    case IDM_4x:
        hmenu = GetMenu(hwnd);
        ChangeZoom(hwnd, hmenu);
        Menu_CheckItem(hmenu, IDM_4x, TRUE);

        Zoom=4;
        InvalidateRect(hwnd, NULL, TRUE);
        UpdateWindow(hwnd);
        break;

    case IDM_8x:

        
        //Zoom=8;
        //InvalidateRect(hwnd, NULL, TRUE);
        //UpdateWindow(hwnd);
        break;

        // Accelerator keys.....
	    case KEY_UP:
            WarningDialog(hwnd, "KEY_UP", "");
		break;


		case KEY_DN:
            WarningDialog(hwnd, "KEY_DN", "");
		break;

		case KEY_LF:
            WarningDialog(hwnd, "KEY_LF", "");
		break;

		case KEY_RG:
            WarningDialog(hwnd, "KEY_RG", "");
		break;

			
		// FICHIER / QUITTER
		case IDM_QUIT:
            if (canclose()==TRUE)
                  PostQuitMessage(0);
		break;
			
		case IDM_ABOUT:
			  AboutDialogBox();	
		break;   

        case IDM_NEW:
            WarningDialog(hwnd, "IDM_NEW", "");
        break;
        
        case IDM_OPEN:
            //WarningDialog(hwnd, "IDM_OPEN", "");
            Load(hwnd);
        break;

        case IDM_SAVE:
        break;

        case IDM_CUT:
        break;

        case IDM_COPY:
        break;

        case IDM_PASTE:
        break;

        case IDM_PRINT:
			MessageBox (NULL, "Not implemented in this sample.", "Command", MB_OK );
		break;

		case IDM_EXIT:
			PostQuitMessage(0);
		break;

		default:
			return (DefWindowProc(hwnd, iMsg, wParam, lParam));

	}  			  
    return 0;
}




/************************************************************/
int canclose()
{
    int Status;
    
    if (HasChanged==FALSE) return(TRUE);

     Status = WarningDialog(hwnd,
        "Les modifications n'ayant pas été sauvegarder, elles seront perdues.",   
        "Souhaitez-vous sauvegarder avant de quitter ?");

    if (Status ==IDNO) return TRUE;
   	else
    {
        if (Status==IDOK)
        {
        //   return (Save()==TRUE);
        
        }

        else
	        return(FALSE);
    }
}


//

//
// HWND InitApp(HINSTANCE hInstance)
//
HWND InitApp(HINSTANCE hInstance)
{
    USER_WINDOW sMainWnd;
    uint cx,cy;

    LPCSTR hRTFLib;

    // Register the ToolbarClass
    //RegisterToolboxClass();

    // Load the rich edit DLL
    hRTFLib = LoadLibrary("RICHED32.DLL");
    if (hRTFLib ==NULL) 
        error ("FATAL","Cannot load RICHED32.DLL");

    cx  = GetSystemMetrics (SM_CXSCREEN)  ;
    cy  = GetSystemMetrics (SM_CYSCREEN)  ;

    // Create Mother Windoz for Application
    sMainWnd.iClassStyle= CS_HREDRAW | CS_VREDRAW | 
                          CS_OWNDC | CS_DBLCLKS;

    sMainWnd.iClassProc = WndProc;
    sMainWnd.hIcon      = LoadIcon(hInstance, "ABC");
    sMainWnd.hCursor    = LoadCursor(NULL, IDC_ARROW);
    sMainWnd.hBrush     = (HBRUSH) GetStockObject(GRAY_BRUSH);
    sMainWnd.cMenuName  = (M2INT(IDR_MENU1));
    sMainWnd.cClassName = "MiniApp";
        
    sMainWnd.iWndExStyle= 0;
    sMainWnd.cWndTitle  = AppTitle ;
    sMainWnd.iWndStyle  = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    sMainWnd.iWndLen    = 640;			    
    sMainWnd.iWndHei    = 480;
    sMainWnd.iWndX      = (cx-sMainWnd.iWndLen)/2;
    sMainWnd.iWndY      = (cy-sMainWnd.iWndHei)/2;

    hAppWnd = (void*) RegisterAndCreateWindow
                        (hInstance, sMainWnd);

    //InitTimers(hAppWnd);

    return hAppWnd;

}






// ******************************************************
//
// int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
//                    PSTR szCmdLine, int iCmdShow)
//
// Create a main windows and register it's class stuff.
//
// ******************************************************
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
     {
     
     MSG					msg		;
     static		HACCEL		hAccel ;
   
     
 
     char **ppImaData;
     
     int code;

     static char filename[1024];
                                  
     ppImaData = malloc(4);
     if (strlen(szCmdLine))
     {

        code = (LoadIma(szCmdLine,&stdima, ppImaData)) ;
        if (code)
        {

            if (code==TRUE) 
            {

                bitdata = Ima2Bitmap(stdima, *ppImaData)  ;
                strcpy(filename, szCmdLine);
                 
            }

            if (code==err_fileopen) 
            {
                
                InfoDialog(NULL, "Erreur fatale\nFileOpen");
                
                error("Erreur fatale", "FileOpen");

            }

            if (code==err_format)
            {
                InfoDialog(NULL, "Erreur fatale\nLe format du fichier n'est pas une image à base FNT");
                error("Erreur fatale", "Format");
            }

            
        }
     }

    


     hAppInstance= hInstance;


	 if (CreateAppPal()==FALSE)
       return( FALSE);
     
   

	 //hAppWnd= RegisterAndCreateMotherWindow(hInstance);
    hAppWnd = InitApp(hInstance);
     
	 if (!hAppWnd)
		 error("ERREUR FATALE", "Création de la fenetre mère a échouée");

     ShowWindow (hAppWnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     hAccel = LoadAccelerators(hInstance, M2INT(ACC1));
     DoCaption(hwnd, AppTitle, filename, FALSE);

    for (;;)
    {
        if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

         if (!TranslateAccelerator (hwnd, hAccel, &msg))
               {
               TranslateMessage (&msg) ;
               DispatchMessage (&msg) ;
               }
        }
        else
        {
                WaitMessage();
        }
    }

    		
     

    AppExit();
    return msg.wParam;
}


// ********************************************************
//
// Initialize all the program's timers
// void InitTimers(HWND hwnd);
//
// PURPOSE: Initialise the application's timers.
//
// ********************************************************
void InitTimers(HWND hwnd)
{
	if (AppTimer1!=0)
	  SetTimer (hwnd, AppTimer1ID, AppTimer1, NULL);
    if (AppTimer2!=0)
	  SetTimer (hwnd, AppTimer2ID, AppTimer2, NULL);
}



//
//
//

void PeinturerFenetre(HDC hdc)
{

    HBITMAP hbitmap;
    char *Bigbit;
    uint len;
    uint hei;

    len = stdima.len*8;
    hei = stdima.hei*8;

   
    

    if (Zoom!=1)
    {
        Bigbit = StretchBitmap(stdima, bitdata, Zoom);
        hbitmap = MakeBitmap(stdima.len*8*Zoom, stdima.hei*8*Zoom, Bigbit, hdc);
    }
    else
    {
        hbitmap = MakeBitmap(len,hei , bitdata, hdc);
        //error("aa","bb");
    }

    if (hbitmap)
    {
        PutBitmap(hdc, hbitmap,0,0);
        DeleteObject(hbitmap);
    }

    if ((Zoom!=1) && (Bigbit!=NULL))
        free(Bigbit);


}


//
//
//
int AskAboutSave()
{

    return WarningDialog(hwnd,
        "Les modifications n'ayant pas été sauvegarder, elles seront perdues.",   
        "Souhaitez-vous sauvegarder avant de quitter ?");

}



//
//
//


// ***********************************************************
// 
// Handles all the important messages comming from MS-WINDOWS to
// the Mother Windoez of MiniApps
// 
// ***********************************************************

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
    {
    HDC         hdc ;
     

    PAINTSTRUCT ps ;
    
 
	static MOUSE mouse;
    static char Temp[512];


 	HMENU hMenu, hMenuTrackPopup;

    switch (iMsg)
		{

        // Msg WM_COMMAND ************************************
		case WM_COMMAND:
           return  msg_Command( hwnd,  iMsg,  wParam,  lParam);
        break;

        // Msg WM_QUERYNEWPALETTE ****************************
		case WM_QUERYNEWPALETTE:
            return msg_QueryNewPalette( hwnd, hpal);
        break;

        // Msg WM_ACTIVATEAPP ********************************
		case WM_ACTIVATEAPP:
           msg_ActivateApp( hwnd,  hpal,  wParam) ;
        break;  		
	
		// Event occuring when the WINDOWS is created *********
		case WM_CREATE :
            hdc = GetDC (hwnd) ;
            //PopFileInitialize (hwnd, szFilter) ;			   			   
			//DoCaption(hwnd, AppTitle,"", FALSE);			   			   
     
            srand( (unsigned)time( NULL ) );

            ReleaseDC (hwnd, hdc) ;				                			  			 			   
                                 
            return 0 ;

	    // Gestion des événement claviers *******************
		case WM_CHAR :
        return 0 ;  

        //
		case WM_INITMENU:
    	  //hMenu =  (HMENU) wParam;

          //Menu_EnableItem(hMenu, IDM_OPEN, FALSE) ;

		return 0;

        //
		case WM_MENUSELECT:
		return 0;

        //
        case WM_MOUSEMOVE:
        break;
       
      //
      case WM_SIZE:

       break;

		  // Event occuring when the WINDOWS is in need of repainting		
		case WM_PAINT :
			hdc = BeginPaint(hwnd,&ps);

		    PeinturerFenetre(hdc);

			EndPaint(hwnd,&ps);
		return 0L;


        //
        case WM_CONTEXTMENU:
        return 0;

		  // Timer's events
		case WM_TIMER:
				hdc = GetDC (hwnd) ;
                ReleaseDC (hwnd, hdc) ;	                  			   
		return 0 ;
				
        //
        case WM_CLOSE :
			  if (canclose()==TRUE)
			  {  DestroyWindow (hwnd);
			  }
        return 0 ;
	
        //
        case WM_QUERYENDSESSION :
        return 0 ;

		  // Event occuring when closing the main WINDOWS ******
        case WM_DESTROY :
			   PostQuitMessage(0);
        return 0 ;

		  // I don't know what it does exactly. *************
	    case WM_SETFOCUS :
        return 0 ;
        

        // ****************************************************
        case WM_LBUTTONDBLCLK:
            // Double-click on the toolbar -- display the customization dialog.
            //SendMessage(hWndToolbar, TB_CUSTOMIZE, 0L , 0L );
            break;
	  
        // ****************************************************
    } 

     return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
}



