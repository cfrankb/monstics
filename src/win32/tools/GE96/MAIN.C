/*-------------- ----------------------------------------------
   HELLOWIN.C -- Displays "Hello, Windows 95!" in client area
                 (c) Charles Petzold, 1996

        	  Modified to become

	FRANK.C  -- a nice test of how the world doesn't work right.

              Then it became

    MAIN.C and many other small C source code files.

  ------------------------------------------------------------*/

// *** INCLUDED FILES ***
#include "include.h"
#include "resource.h"
#include "common.h"

// ***   CONSTANTES   ***
#include "const.h"

#define AppIcon		IDI_LITTLE_GIRL
#define AppTitle	"Graphics Editor 96 Beta"
#define AppAccl		M2INT(ACC1)
#define AppMenu		IDR_MENU1
#define AppWinLen	32*8+64
#define AppWinHei	32*8+64
#define AppWinTopX	100
#define AppWinTopY	100
#define AppWinShow  SW_SHOWMAXIMIZED	// iCmdShow for default
#define AppWinStyle WS_OVERLAPPEDWINDOW
#define AppStyle    CS_HREDRAW | CS_VREDRAW 
//#define AppStyle    CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS

#define AppTimer1	1
#define AppTimer2	0
#define AppTimer1ID	1
#define AppTimer2ID	2


// ***  GLOBAL VARS  ***
HWND			hAppWnd;				// HWND instance for the mother window
HWND			hwnd;
HWND            hchildwnd;				// HWND for child window
HWND            htoolbarwnd;
HWND            hgrildwnd;

HINSTANCE		hAppInstance;			// Application instance

int				HasChanged	= FALSE;
char			Filename[256]="";
char			Titlename[512]="";

TEXTMETRIC		tm ;					// Font info obj    
MOUSE			mouse;

char            MCXFORMATNAME[] = "Static Image MCX3 Format";
static HANDLE   hMem;
static int      MCXFormatId;

char AppName[] =	"Graphics Editor 96 Beta";
const char SansTitre[] = "(sans titre)";
const char ColorsPaletteName[] = "Palette de couleurs";


#define CF_MCX3 MCXFormatId
#define uchar   unsigned char 

// Palette related variables
FILE					*FilePal;

extern char				MSDOS_PAL[];
extern USER_WINPAL		PalColors[256];			// The user colors palette
extern USER_WINPAL		DefColors[256];
extern HPALETTE			hpal;

extern  char   PenColor ;

extern int				SysPalIndex[];
extern COLORREF			MonoColors[]; 
extern COLORREF			OldColors[];

extern char BitPalColor[];

// EDIT GRILD
USER_MCXHEADER mcx_header;
USER_MCX       *current_mcx;
USER_MCXHEADER mcx_header2;

char     BitGrild[32*32*8*8];
char     BitImage[32*32];


// *** FUNCTIONS ***
void NewFile();
BOOL InitAppPal() ;
BOOL Save(char *TempFilename);
BOOL SaveAs(char *TempFilename);
LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void DoCaptionL(HWND hwnd);
int ValidateFilename(char *, char *);
char *Int2Str(int);
HWND RegisterAndCreateAppColorPal(HWND);	

// START OF GRILDCLAS.C

// *** INCLUDED FILES ***
#include "resource.h"
#include "include.h"
#include "const.h"
#include "mcx.h"
#include "WinEasy.h"

extern HPALETTE hpal;
	 
// EDIT GRILD
extern HWND hAppInstance;

extern	USER_MCXHEADER mcx_header;
extern	USER_MCX       *current_mcx;
extern	USER_MCXHEADER mcx_header2;
extern  HWND hwnd;
extern  HWND hAppWnd;
extern  HWND hgrildwnd;	

extern	char     BitGrild[32*32*8*8];
extern  MOUSE	 mouse;

extern  USER_WINPAL		PalColors[256];		// The user colors palette
extern  USER_WINPAL		DefColors[256];
extern  HPALETTE		hpal;

extern  char PenColor;
extern  int HasChanged;
extern  char BitPalColor[];

void RemplirGrild(uchar BitGrild[], uchar ImageData[32][32]);
LRESULT CALLBACK EditGrildWndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void InitBitGrild(uchar BitGrild[]);


void InitEditor(char BitGrild[], char BitImage[])
{
		InitBitGrild(BitGrild);        	
}

void InitBitGrild(uchar BitGrild[])
{
    int x,y,z;
	for (y=0; y<32; y++)
	{
		for (x=0 ; x<32; x++)
	    {    
			for (z=0; z<8; z++)
	        {
			   BitGrild[y*32*8*8+x*8+z+7*32*8] = 148;
			   BitGrild[(y*32*8*8)+(x*8)+7+(z*32*8)] = 148;
			}
	    }
	}
}


//**********************************************************
//
//
//
//**********************************************************

void NewFile()
{
				// Initializing mcx_header
				HasChanged = FALSE;
				memcpy (mcx_header.Id, "GE96",4);
				mcx_header.Class= 0;
				strcpy (mcx_header.Name, "");
				mcx_header.NbrImages = 1;
				mcx_header.LastViewed = 1;
				memcpy (mcx_header.Palette, PalColors, 256*3);
				mcx_header.PtrFirst = malloc (sizeof(USER_MCX));
				*mcx_header.PtrFirst->Name = 0;
				mcx_header.PtrFirst->PtrPrev = NULL;
				mcx_header.PtrFirst->PtrNext = NULL;			   
				current_mcx =  mcx_header.PtrFirst;

				ClearMCX(current_mcx);
			
  				RemplirGrild(BitGrild, current_mcx->ImageData);
                if (hgrildwnd)
                    InvalidateRect(hgrildwnd,NULL,TRUE);				

}

//***********************************************************
//
//HWND RegisterAndCreateAppColorPal(HINSTANCE hInstance)
//
//***********************************************************

#define EditGrildName "Grille d'édition"

HWND RegisterAndCreateEditGrild(HINSTANCE hInstance)

{
	WNDCLASS wc;
    ATOM atom;
    // *****************  Class for the ChildWindow ************************
	wc.style = CS_BYTEALIGNWINDOW 
		       ;
//	wc.style = CS_BYTEALIGNWINDOW |
//		       CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;

    
    wc.lpfnWndProc = EditGrildWndProc; 
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 4;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon (hInstance, M2INT(IDI_ICON8)) ;
	wc.hCursor = LoadCursor(hInstance, M2INT(IDC_PEN96));
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "EditGrild" ; 

	atom = RegisterClass(&wc);

    return (CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE,
		"EditGrild",
		EditGrildName,
		WS_POPUP | WS_CAPTION | WS_CLIPCHILDREN | WS_MINIMIZEBOX
         | WS_CLIPSIBLINGS,
		150, 200, 32*8+128, 32*8+64,
		hwnd,
		(HMENU)NULL,
		hInstance,
		0L));
}


//	wsprintf (text, "%s - [%s]",



void PeinturerFenetre(HDC hdc, char BitGrild[])
{

			char text[512];

			int x,y;

	        HBITMAP hbitmap;
			if (hpal)
			{
				SelectPalette(hdc, hpal, FALSE);
				RealizePalette(hdc);
			}
													     

           hbitmap = MakeBitmap(32*8,32*8, BitGrild, hdc);
		   //hbitmap = CreateBitmap(32*8, 32*8, 1, 8, BitGrild);

		   if (hbitmap)
           { PutBitmap( hdc, 
		                hbitmap,
		                00,
		                00)  ;
		  
			   DeleteObject(hbitmap);
		   }

           hbitmap = MakeBitmap(32,32, (char *)current_mcx->ImageData, hdc);
		   //hbitmap = CreateBitmap(32, 32, 1, 8, current_mcx->ImageData);
		   if (hbitmap)
           { PutBitmap( hdc, 
		                hbitmap,
		                32*8+8,
		                8)  ; }
		  


			if (hbitmap)
			{
			for (y=0; y<3; y++)
			   for (x=0;x<3;x++)
					PutBitmap( hdc, 
		                hbitmap,
		                x*32+32*8+8,
		                y*32+16+32)  ;

			DeleteObject(hbitmap);
			}
			

			
           hbitmap = MakeBitmap(32,32, BitPalColor, hdc); 
		   //hbitmap = CreateBitmap(32, 32, 1, 8, BitPalColor);
		   if (hbitmap)
           { PutBitmap( hdc, 
		                hbitmap,
		                32*9+16,
		                8)  ;
		   



			   DeleteObject(hbitmap);
		   }


					strcpy(text,Int2Str(mcx_header.LastViewed));
					strcat(text, " de ");
					strcat(text,Int2Str(mcx_header.NbrImages));
					strcat(text, " images");


				    PutText(hdc,  
					       text, 
					         8*32+8+8,
							 8*16+32+32, 
							 ANSI_VAR_FONT);						       
}      	    




void RemplirGrild(uchar BitGrild[], uchar ImageData[32][32])
{
	
	int x;
	int y;
	int x2;
	int y2;

	for (y=0; y<32; y++)
	{
	  for (x=0; x<32; x++)
	  {
		  if (ImageData[y][x])
		  {
		    for (y2=0; y2<7; y2++)
		    {
			  for (x2=0; x2<7; x2++)
			  {
				  BitGrild[(y*8*32*8)+ 
					       (y2 * 8*32)+ 
						   (x *8)+x2] =

				  (ImageData[y][x]);
			  }
		    }
		  }
		  else
		    for (y2=0; y2<7; y2++)
		    {
			  for (x2=0; x2<7; x2++)
			  {
				  if (x2>=4&& x2<=5 && y2>=4 && y2<=5)
				  BitGrild[(y*8*32*8)+ 
					       (y2 * 8*32)+ 
						   (x *8)+x2] =148;
				  else
				  BitGrild[(y*8*32*8)+ 
					       (y2 * 8*32)+ 
						   (x *8)+x2] =

				  (ImageData[y][x]);
			  }
		    }


	  }
	}


}





void DrawOnGrild(char color, HWND hwnd)
{
	    if ((mouse.y/8<32) && (mouse.x/8<32))
			{	current_mcx->ImageData[mouse.y/8]
                [mouse.x/8]	 = color ;
										
						
		       RemplirGrild(BitGrild, current_mcx->ImageData);
               InvalidateRect (hwnd, NULL, FALSE) ;

					
				if (!HasChanged){	HasChanged=TRUE;
					       DoCaptionL (hAppWnd);}

		}

}


//**********************************************************************************
//
// ChildWndProc : This is the message handler to the Child PopUp Window
//                The Color Palette Window Proc handler
//
//*********************************************************************************
LRESULT CALLBACK EditGrildWndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{        
PAINTSTRUCT ps ;
    HDC         hdc ;
	//static char bitPalette[16*16*16*14];
	BOOL fAppActive;

	int cpt;
	static HWND hwndButton[2];
	static action  = action_draw;

struct 
{
	   int x;
	   int y;
	   int len;
	   int hei;
	   char *text ;
}
static buttons [] =
{
8*32+8, 8*16+32, 32,16,"<<",
8*32+8+32+32, 8*16+32, 32,16,">>"
} ;
	

		switch (iMsg)
		{
        case WM_CLOSE :
            SendMessage(hAppWnd, iMsg,wParam, lParam);
        return 0 ;



		case WM_COMMAND:

			switch( LOWORD(wParam) )
			{
			
			case 0:
				SendMessage(hAppWnd, WM_COMMAND, ID_IMAGE_PRECEDENTE, 0L);

  			break;

			case 1:
				SendMessage(hAppWnd, WM_COMMAND, ID_IMAGE_SUIVANTE, 0L);
			break;

			}

			
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
					InitEditor(BitGrild, NULL);
	
					mouse.last_x= (DWORD)-1;
					mouse.last_y= (DWORD)-1;
					mouse.x=(DWORD)-1;
					mouse.y=(DWORD)-1;

					NewFile();
                    
					for (cpt=0; cpt<2	; cpt++)
						hwndButton[cpt] = 
						CreateWindow ("button",
									  buttons[cpt].text,
									  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
									  buttons[cpt].x, buttons[cpt].y,
									  buttons[cpt].len,
									  buttons[cpt].hei, hwnd, (HMENU) cpt,
									  hAppInstance, NULL);



				}
				return 0 ;

		case WM_LBUTTONDOWN:
               if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
               {
                   
                	mouse.last_x= mouse.x;
					mouse.last_y= mouse.y;
		            mouse.button = wParam;
                    mouse.x = LOWORD (lParam) ;
                    mouse.y = HIWORD (lParam) ;
		

					if (mouse.button==MK_LBUTTON)
						DrawOnGrild(PenColor, hwnd);

					if (mouse.button==MK_RBUTTON)
						DrawOnGrild(0,hwnd);




			}                    

			
			return 0;

		case WM_MOUSEMOVE:
               if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
               {
                   
                	mouse.last_x= mouse.x;
					mouse.last_y= mouse.y;
		            mouse.button = wParam;
                    mouse.x = LOWORD (lParam) ;
                    mouse.y = HIWORD (lParam) ;
		

					if (mouse.button==MK_LBUTTON)
						DrawOnGrild(PenColor, hwnd);

					if (mouse.button==MK_RBUTTON)
						DrawOnGrild(0, hwnd);
			}                    
               return 0 ;


				case WM_PAINT :
			  		hdc = BeginPaint(hwnd,&ps);
					PeinturerFenetre(hdc, BitGrild);
       				EndPaint(hwnd,&ps);
				return 0L;

 
	
		}
         return DefWindowProc (hwnd, iMsg, wParam, lParam) ;

	}        

// END OF GRILDCLASS.C






//***********************************************************
//
// CreateAppPal()
//
//
//***********************************************************

 int extern MSDOS_PAL16[256];

  BOOL CreateAppPal();

 //***********************************************************
 //
 // HWND RegisterAndCreateMotherWindow(HINSTANCE hInstance)
 //
//***********************************************************

 HWND RegisterAndCreateMotherWindow(HINSTANCE hInstance)
 {
     WNDCLASS  wndclass	;
     ATOM atom;

     // Class for Mother MiniApp's Window
	 
     wndclass.style         = AppStyle;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (hInstance, M2INT(AppIcon)) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (GRAY_BRUSH) ;
     wndclass.lpszMenuName  = M2INT(AppMenu);
     wndclass.lpszClassName = AppName;

     atom = RegisterClass (&wndclass);

     MCXFormatId = RegisterClipboardFormat(MCXFORMATNAME);

	 hwnd = CreateWindowEx ( WS_EX_ACCEPTFILES | WS_EX_APPWINDOW | WS_EX_CONTROLPARENT,
		                  M2INT(atom),       // window class name
						  AppTitle,			 // window caption
			              AppWinStyle ,       // window style
			              AppWinTopX,		 // initial x position
			              AppWinTopY,		 // initial y position
                          AppWinLen,		 // initial x size
                          AppWinHei,		 // initial y size
                          NULL,              // parent window handle
                          NULL,              // window menu handle
                          hInstance,         // program instance handle
		                  NULL) ;		     // creation parameters
	return (hwnd);
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

	 int Status;
	 if (CreateAppPal()==FALSE)
	//	 return( FALSE);
     ;

	 if (strlen(szCmdLine)!=0) 
	 {	 strcpy(Filename,szCmdLine);
		 Status =ValidateFilename(Filename, "GE96");
	     if (Status!=TRUE)
			 strcpy(Filename,"");	 
		 
	 }	 
	 hAppWnd= RegisterAndCreateMotherWindow( hInstance);
	 if (!hAppWnd)
		 error("ERREUR FATALE", "Création de la fenetre mère a échouée");
	 
	 
	 hgrildwnd = RegisterAndCreateEditGrild(hInstance);
	 if (!hgrildwnd)
		 error("ERREUR FATALE", "Création d'une fenetre fille a échouée");


     if ((strlen(Filename) && 
		   LoadMCX(Filename, &mcx_header)==TRUE))
     {
		   current_mcx = mcx_header.PtrFirst;
		   mcx_header.LastViewed =1;
		   RemplirGrild(BitGrild, current_mcx->ImageData);
               		//	 	  HasChanged=TRUE;
			        //     	  DoCaptionL (hwnd);
                   InvalidateRect (hgrildwnd, NULL, FALSE) ;
     };			  			   

	 
	 hAppInstance= hInstance;

     hchildwnd = RegisterAndCreateAppColorPal(hAppWnd);	
	 if (!hchildwnd)
		 error("ERREUR FATALE", "Création d'une fenetre fille a échouée");
     //htoolbarwnd = RegisterAndCreateToolbarWindow(hInstance);
	 //if (!htoolbarwnd)
	//	 error("ERREUR FATALE", "Création d'une fenetre fille a échouée");


	 //InitTimers(hwnd);

		 

     ShowWindow (hwnd, iCmdShow) ;
//     UpdateWindow (hwnd) ;

     ShowWindow (hchildwnd, SW_RESTORE) ;
//     UpdateWindow (hchildwnd) ;

    // ShowWindow (htoolbarwnd, SW_RESTORE) ;
    // UpdateWindow (htoolbarwnd) ;

     ShowWindow (hgrildwnd, SW_RESTORE) ;
 //    UpdateWindow (hgrildwnd) ;
	 
 	 hAccel = LoadAccelerators(hInstance, M2INT(ACC1));
				 
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
           // if (AppIdle())
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








// *************************************************************
//
// DoCaptionL
// 
// *************************************************************

void DoCaptionL(HWND hwnd)
{
	strcpy(Titlename, AppTitle);
	strcat(Titlename, " - ");
	if (strlen(Filename)==0)
	   strcat(Titlename, SansTitre);
	else
	   strcat(Titlename, Filename);

	if (HasChanged) strcat(Titlename, "*");
        SetWindowText (hwnd, Titlename) ;
}






int canclose()
{
    int iStatus;
	if (HasChanged==FALSE) return(TRUE);

    
    iStatus = 
       WarningDialog(hAppWnd,
        "Les modifications n'ayant pas été sauvegarder, elles seront perdues.",   
        "Souhaitez-vous sauvegarder avant de quitter ?");
    
    if (iStatus==IDNO)
		return(TRUE);
	else
	    return(FALSE);
}


BOOL QuitProgram()
{
	char TempFilename [1024];
	int answer;
	strcpy(TempFilename, Filename);
	if (HasChanged==FALSE) return(TRUE);
	answer=  WarningDialog(hAppWnd,
        "Les modifications n'ayant pas été sauvegarder, elles seront perdues.",   
        "Souhaitez-vous sauvegarder avant de quitter ?");

	if (answer==IDNO)
		 return(TRUE);
    else
		if (answer == IDOK)
 			if (strlen(Filename)==0)
				return(SaveAs(TempFilename));
			else
				return(Save(TempFilename));		
	   else
	       return(FALSE);


}




// *************************************************************
//
// AskAboutSave
// This function will ask you about saving your dam  
// file before OPEN or NEW.
//
// *************************************************************

int AskAboutSave()
{	

    return WarningDialog(hAppWnd, "Les modifications n'ayant pas été sauvegarder, elles seront perdues.",
        "Souhaitez-vous sauvegarder avant de continuer ?");

}

//
//
//

BOOL Save(char *TempFilename)
{
	 if (SaveMCX(Filename, &mcx_header)==TRUE)
	 {
			 HasChanged = FALSE;
			 DoCaptionL(hwnd);
			 return(TRUE);
	 }
	 else
	 {	 strcpy(Filename, TempFilename);
		     MessageBox(hwnd, "La sauvegarde a échouée", 
				              "Erreur d'écriture",
							  MB_OK | MB_ICONSTOP);
			 return(FALSE);
	 }
}

BOOL SaveAs(char *TempFilename)
{
     
	 strcpy(TempFilename, Filename);
	 if (PopFileSaveDlg(hwnd, Filename, Titlename))
	 {
		return(Save(TempFilename));
	 }
	 else
		 return(FALSE);

}




void Load(char *x)
{
    char TempFilename [1024];	   
	int Status;

	strcpy(TempFilename, Filename);
 	if (PopFileOpenDlg 
				(hAppWnd, 
				Filename, 
				Titlename))
	{
		Status = LoadMCX(Filename, &mcx_header2);
		switch (Status)
		{
			
		case TRUE:
				 FreeMCX(&mcx_header);
				 mcx_header = mcx_header2;
				 HasChanged= FALSE;
				 DoCaptionL(hwnd);
				 current_mcx =  mcx_header.PtrFirst;
				 mcx_header . LastViewed =1;
  				 RemplirGrild(BitGrild, current_mcx->ImageData);
                 InvalidateRect (hgrildwnd, NULL, FALSE) ;
				 
			     break;

			case err_fileopen: 
				MessageBox(hwnd, "Incapable de lire le fichier.", "Erreur de lecture", 
		 		       MB_OK | MB_ICONSTOP);
					   strcpy(Filename,TempFilename);
				break;

			case err_memory: 
				MessageBox(hwnd, "Mémoire insuffisante.", "Erreur de mémoire", 
					     MB_OK | MB_ICONSTOP);
						strcpy(Filename,TempFilename);
				break;

			case err_format:
				MessageBox(hwnd, "Format incompatible.", "Erreur de fichier", 
					     MB_OK | MB_ICONSTOP);
						strcpy(Filename,TempFilename);
				break;

			default:
				MessageBox(hwnd, "Fournir les circonstances entourant cette erreur.", "Erreur interne", 
					     MB_OK | MB_ICONSTOP);
						strcpy(Filename,TempFilename);
				break;				
			
		}

			
	}
}



		
	





void DoNewFile()
{	
	strcpy(Filename, "");
	FreeMCX(&mcx_header);
	NewFile();
	DoCaptionL(hwnd);
}



//
//
//
//

void Rotation90()
{
      char temp[32][32];
	  int x,y;
	  memcpy(temp, current_mcx->ImageData, 32*32);

	  for (y=0; y<32;y++)
	  {
		for (x=0; x<32; x++)
		{

			temp[31-y][x]= current_mcx->ImageData[x][y];

		}
	  
	  }

	memcpy (current_mcx->ImageData,temp,32*32);

	HasChanged= TRUE;
	DoCaptionL(hwnd);
    RemplirGrild(BitGrild, current_mcx->ImageData);
    InvalidateRect (hgrildwnd, NULL, FALSE) ;


}



void FlipUpDown()
{
	char temp[32];
	int cpt;
	for (cpt =0; cpt<16; cpt++)
	{
        memcpy(temp, &current_mcx->ImageData[cpt][0],32);
        memcpy(&current_mcx->ImageData[cpt][0], 
			   &current_mcx->ImageData[31-cpt][0],32);
        memcpy(&current_mcx->ImageData[31-cpt][0], temp,32);	
	}

	HasChanged= TRUE;
	DoCaptionL(hwnd);
    RemplirGrild(BitGrild, current_mcx->ImageData);
    InvalidateRect (hgrildwnd, NULL, FALSE) ;

}




void FlipLeftRight()
{

	uchar temp;
	int x;
	int y;
	for (y =0; y<32; y++)
	{
		for (x=0; x<16; x++)
	    {

		  temp = current_mcx->ImageData[y][x];
          current_mcx->ImageData[y][x] = 
			   current_mcx->ImageData[y][31-x];
          current_mcx->ImageData[y][31-x] = temp;

		}
	}
	
	HasChanged= TRUE;
	DoCaptionL(hwnd);
    RemplirGrild(BitGrild, current_mcx->ImageData);
    InvalidateRect (hgrildwnd, NULL, FALSE) ;

}



void ShiftRg()
{
	int x; int y;
	uchar temp;

	for (y=0; y<32;y++)
	{
	  temp = current_mcx->ImageData[y][31];
	  for (x=30; x>=0; x--)
		  current_mcx->ImageData[y][x+1]
		     = current_mcx->ImageData[y][x];

	  current_mcx->ImageData[y][0] = temp;
	}
	    
	HasChanged= TRUE;
	DoCaptionL(hwnd);
    RemplirGrild(BitGrild, current_mcx->ImageData);
    InvalidateRect (hgrildwnd, NULL, FALSE) ;

}



void ShiftLf()
{
	int x; int y;
	uchar temp;

	for (y=0; y<32;y++)
	{
	  temp = current_mcx->ImageData[y][0];
	  for (x=1; x<32; x++)
		  current_mcx->ImageData[y][x-1]
		     = current_mcx->ImageData[y][x];

	  current_mcx->ImageData[y][31] = temp;
	}
	    
	HasChanged= TRUE;
	DoCaptionL(hwnd);
    RemplirGrild(BitGrild, current_mcx->ImageData);
    InvalidateRect (hgrildwnd, NULL, FALSE) ;
}



void ShiftUp()
{
	char *Ptr;
	char *PtrID;
	Ptr = malloc(32*32);				// Temp buffer
	PtrID =  &current_mcx->ImageData[0][0];		// ImageData 
	memcpy(Ptr, PtrID+32, 32*31);
	memcpy(Ptr+32*31, PtrID, 32);
	memcpy(PtrID, Ptr, 32*32);

	HasChanged= TRUE;
	DoCaptionL(hwnd);
    RemplirGrild(BitGrild, current_mcx->ImageData);
    InvalidateRect (hgrildwnd, NULL, FALSE) ;
	free(Ptr);
	

}

void ShiftDn()
{
	char *Ptr;
	char *PtrID;
	Ptr = malloc(32*32);				// Temp buffer
	PtrID =  &current_mcx->ImageData[0][0];		// ImageData 
	memcpy(Ptr+32, PtrID, 32*31);
    memcpy(Ptr, PtrID+32*31,32);
	memcpy(PtrID, Ptr, 32*32);

	HasChanged= TRUE;
	DoCaptionL(hwnd);
    RemplirGrild(BitGrild, current_mcx->ImageData);
    InvalidateRect (hgrildwnd, NULL, FALSE) ;
	free(Ptr);
}


                
// ***********************************************************
// 
// Handles all the important messages comming from MS-WINDOWS to
// the Mother Windoez of MiniApps
// 
// ***********************************************************

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
    {
    HDC         hdc ;
     
	HMENU hmenu;
    HBITMAP hbitmap;

    
	BOOL fAppActive;
	BOOL f;
    PAINTSTRUCT ps ;
	USER_MCX *PtrMCX;
    USER_MCX *PtrPrev;
	int Answer;
    static char szFilter[] = "Statics Images Files (*.MCX)\0*.mcx\0\0"  \
                              "All Files (*.*)\0*.*\0\0" ;

    static int ImageNavigationDesactive = FALSE;
    static char TempFilename[1024];

    char *ptrMem;

    switch (iMsg)
		{
		case WM_COMMAND:

				switch (LOWORD(wParam))
				{    

				case ID_EDITION_COPIER:

                    hdc = GetDC(0);
                    hbitmap = MakeBitmap(32,32, (uchar *)current_mcx->ImageData, hdc);
           		    //hbitmap = CreateBitmap(32, 32, 1, 8, current_mcx->ImageData);
                    ReleaseDC(0, hdc);
                                        
                    if (hbitmap)
                    {
                        OpenClipboard(hwnd);
                        EmptyClipboard();
                        
                        // Copying as bitmat
                        SetClipboardData (CF_BITMAP, hbitmap);

                        // Copying as MCX Format
                        hMem = GlobalAlloc(GHND, 32*32+2);
                        ptrMem = GlobalLock(hMem);
                        memcpy(ptrMem, current_mcx->ImageData, 32*32);
                        GlobalUnlock(hMem);
                        SetClipboardData (CF_MCX3, hMem);
                        
                        CloseClipboard();
                    }


					memcpy(BitImage, current_mcx->ImageData, 32*32);
					break;

				case ID_EDITION_COLLER:

                    OpenClipboard(hwnd);					
                    
                    hMem = GetClipboardData(CF_MCX3);

                    if (hMem==NULL) 
                    {
                        CloseClipboard();
                        break;
                    }

                    ptrMem = GlobalLock(hMem);
                    memcpy( current_mcx->ImageData, ptrMem, 32*32);
                    GlobalUnlock(hMem);
                    CloseClipboard();
                                        
                    // Old way....
                    //memcpy( current_mcx->ImageData,BitImage, 32*32);
					HasChanged= TRUE;
					DoCaptionL(hwnd);
				    RemplirGrild(BitGrild, current_mcx->ImageData);
				    InvalidateRect (hgrildwnd, NULL, FALSE) ;
                    
					break;

				case ID_EDITION_COUPER:
                    hdc = GetDC(0);
                    hbitmap = MakeBitmap(32,32, (uchar *)current_mcx->ImageData, hdc);
                    ReleaseDC(0, hdc);
                    //hbitmap = CreateBitmap(32, 32, 1, 8, current_mcx->ImageData);
 
                    if (hbitmap)
                    {
                        OpenClipboard(hwnd);
                        EmptyClipboard();
                        
                        // Copying as bitmap
                        SetClipboardData (CF_BITMAP, hbitmap);

                        // Copying as MCX Format
                        hMem = GlobalAlloc(GHND, 32*32+2);
                        ptrMem = GlobalLock(hMem);
                        memcpy(ptrMem, current_mcx->ImageData, 32*32);
                        GlobalUnlock(hMem);
                        SetClipboardData (CF_MCX3, hMem);                                         

                        CloseClipboard();
                    }

					memcpy(BitImage, current_mcx->ImageData, 32*32);
					ClearMCX(current_mcx);
					HasChanged= TRUE;
					DoCaptionL(hwnd);
					RemplirGrild(BitGrild, current_mcx->ImageData);
				    InvalidateRect (hgrildwnd, NULL, FALSE) ;
					break;

				case ID_OPTION_ROTATION90:
					Rotation90();
				break;


				case ID_OPTION_FLIPVERTICAL:
					FlipUpDown();					
				break;

				case ID_OPTION_FLIPHORIZONTAL:
					FlipLeftRight();					
				break;


				case KEY_UP:
					ShiftUp();					
				break;

				case KEY_DN:
					ShiftDn();
				break;

				case KEY_LF:
					ShiftLf();
				break;

				case KEY_RG:
					ShiftRg();
				break;
				
				case ID_FICHIER_NOUVEAU:

				if (HasChanged==TRUE) 
					{
						Answer = AskAboutSave();
						if (Answer== IDOK)		
						{
							strcpy(TempFilename, Filename);
							if (strlen(Filename)==0)
								SaveAs(TempFilename);
							else
								Save(TempFilename);
							DoNewFile();							
						}
						else
						{
							if (Answer ==IDNO)
							  DoNewFile();							
							
						}
					}
					else
					{
						DoNewFile();							
					
					}
						
				  break;


				 case ID_FICHIER_OUVRIR:
	 				if (HasChanged==TRUE) 
					{
							Answer = AskAboutSave();
						if (Answer== IDOK)		
						{
							strcpy(TempFilename, Filename);
							if (strlen(Filename)==0)
								SaveAs(TempFilename);
							else
								Save(TempFilename);
							Load(TempFilename);							
						}
						else
						{
							if (Answer ==IDNO)
							  Load(TempFilename);							
							
						}
					}
					else
					{
						Load(TempFilename);							
					
					}
					break;

				  case ID_FICHIER_ENREGISTRER  :
					  strcpy(TempFilename, Filename);
					  if (strlen(Filename)==0)
					     SaveAs(TempFilename);
					  else
					     Save(TempFilename);

				  break;

				  case ID_FICHIER_ENREGISTRERSOUS:
					  strcpy(TempFilename, Filename);
	 			      SaveAs(TempFilename);
					  break;

				  //case KEY_ESC:
			      case ID_FICHIER_QUITTER:
					  if (QuitProgram())			        
				         PostQuitMessage(0);
				  break;

			
				  case ID_AIDE_PROPOSDE:
					  AboutDialogBox();	
				  break;
			    

				case ID_IMAGE_EFFACER:
			    //case KEY_C:
					if (MessageBox(hwnd, "Est-vous sure?", "Effacer l'image!", 
					MB_SYSTEMMODAL |MB_ICONQUESTION | MB_YESNO)==IDYES) 
					{
        			ClearMCX(current_mcx);			
  					RemplirGrild(BitGrild, current_mcx->ImageData);
                    InvalidateRect (hgrildwnd, NULL, FALSE) ;
					HasChanged=TRUE;
					DoCaptionL (hwnd);
				   
					}
				break;


				case ID_IMAGE_SUPPRIMER:
					if (MessageBox(hwnd, "Est-vous sur?", "Supprimer l'image!", 
					MB_SYSTEMMODAL |MB_ICONQUESTION | MB_YESNO)==IDYES) 

					  if (current_mcx->PtrPrev == NULL)
					  {
					      if (mcx_header.NbrImages!=1)
						  {
							  mcx_header.PtrFirst = 
								  current_mcx->PtrNext;
							  free(current_mcx);
							  current_mcx = mcx_header.PtrFirst;
							  current_mcx ->PtrPrev =NULL;
							  mcx_header.NbrImages --;
  					          RemplirGrild(BitGrild, current_mcx->ImageData);
               			 	  HasChanged=TRUE;
			             	  DoCaptionL (hwnd);
                              InvalidateRect (hgrildwnd, NULL, FALSE) ;

						  }
						  else
							MessageBox(hwnd, "Le fichier doit avoir au moins une image.", "AVERTISSEMENT", 
							MB_SYSTEMMODAL |MB_ICONSTOP | MB_OK);

					      
					  }
					  else
					  {

							  PtrMCX = current_mcx->PtrNext;
							  if (PtrMCX!=NULL) 
								  PtrMCX->PtrPrev = 
								  current_mcx ->PtrPrev;

						      PtrMCX = current_mcx ->PtrPrev;
							  PtrMCX->PtrNext=current_mcx->PtrNext;

							  free(current_mcx);

							  if (PtrMCX->PtrNext!=NULL)
							    current_mcx = PtrMCX->PtrNext;
							  else
							  {
								  current_mcx = PtrMCX;
								  mcx_header.LastViewed --;
							  }

							  mcx_header.NbrImages --;
  					          RemplirGrild(BitGrild, current_mcx->ImageData);
               			 	  HasChanged=TRUE;
			             	  DoCaptionL (hwnd);
                              InvalidateRect (hgrildwnd, NULL, FALSE) ;
					  }

				break;


				case ID_IMAGE_PRECEDENTE:
				//case KEY_B:
				  if (!ImageNavigationDesactive)
					if (current_mcx->PtrPrev!=NULL)
					{
					     mcx_header.LastViewed --;
						 current_mcx = current_mcx->PtrPrev;
  					     RemplirGrild(BitGrild, current_mcx->ImageData);
                         InvalidateRect (hgrildwnd, NULL, FALSE) ;
					}
					else;
					//MessageBox(hwnd, "Première image", "INFORMATION", 
					//MB_ICONEXCLAMATION | MB_OK);

				break;


				case ID_IMAGE_SUIVANTE:
				//case KEY_N:
				  if (!ImageNavigationDesactive)
					if (current_mcx->PtrNext!=NULL)
					{
					     mcx_header.LastViewed ++;
						 current_mcx = current_mcx->PtrNext;
  					     RemplirGrild(BitGrild, current_mcx->ImageData);
                         InvalidateRect (hgrildwnd, NULL, FALSE) ;
					}
					else
					{ 
					ImageNavigationDesactive = TRUE;
					 if (MessageBox(hwnd, "Ajouter une nouvelle image?", "INFORMATION", 
					  MB_SYSTEMMODAL | MB_ICONEXCLAMATION | MB_YESNO)==IDYES)
					 {

					     mcx_header.NbrImages ++;
					     mcx_header.LastViewed ++;
						 
						current_mcx->PtrNext = malloc (sizeof(USER_MCX));
						PtrMCX = current_mcx->PtrNext;
				
						*PtrMCX -> Name = 0;
						PtrMCX->PtrPrev = current_mcx;
						PtrMCX->PtrNext = NULL;			   
						current_mcx =  current_mcx->PtrNext;

						ClearMCX(current_mcx);
			
		  				RemplirGrild(BitGrild, current_mcx->ImageData);
		                InvalidateRect(hgrildwnd,NULL,FALSE);				
						HasChanged = TRUE;
						DoCaptionL(hwnd);
					 
					  }
					 ImageNavigationDesactive = FALSE; 
					}
				break;


				case ID_IMAGE_INSERER:
					if (current_mcx->PtrPrev !=NULL)
					{
						PtrMCX =malloc (sizeof(USER_MCX));
						PtrMCX->PtrNext = current_mcx;
						PtrMCX->PtrPrev = current_mcx->PtrPrev;
						//mcx_header->PtrFirst = PtrMCX;  																

                        PtrPrev = current_mcx ->PtrPrev;
                        current_mcx ->PtrPrev = PtrMCX;

						//(PtrMCX->PtrPrev)->PtrNext = PtrMCX;
						current_mcx = PtrPrev;
						current_mcx->PtrNext = PtrMCX;

						current_mcx = PtrMCX;
						ClearMCX(current_mcx);
					    mcx_header.NbrImages ++;

		  				RemplirGrild(BitGrild, current_mcx->ImageData);
		                InvalidateRect(hgrildwnd,NULL,FALSE);				
						HasChanged = TRUE;
						DoCaptionL(hwnd);


					}
					else
					{
						PtrMCX =malloc (sizeof(USER_MCX));
						PtrMCX->PtrNext = current_mcx;
						PtrMCX->PtrPrev = NULL;
						current_mcx->PtrPrev = PtrMCX;
						current_mcx = PtrMCX;
						ClearMCX(current_mcx);
						mcx_header.PtrFirst = PtrMCX;  																

					    mcx_header.NbrImages ++;

		  				RemplirGrild(BitGrild, current_mcx->ImageData);
		                InvalidateRect(hgrildwnd,NULL,FALSE);				
						HasChanged = TRUE;
						DoCaptionL(hwnd);
					}



				break;




				}
		   			  

		case WM_QUERYNEWPALETTE:
	      hdc = GetDC(hwnd);

	      if (hpal)
			SelectPalette(hdc, hpal, FALSE);

          f = RealizePalette(hdc);
          ReleaseDC(hwnd,hdc);

          if (f)
              InvalidateRect(hwnd,NULL,TRUE);

          return f;
		

		case WM_ACTIVATEAPP:

           fAppActive = (BOOL)wParam;               
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
		
		
	
		// Event occuring when the WINDOWS is created
			  case WM_CREATE :
               hdc = GetDC (hwnd) ;
               PopFileInitialize (hwnd, szFilter) ;			   			   
        	   

			   DoCaptionL(hwnd);			   			   
               ReleaseDC (hwnd, hdc) ;				                			  			 			   
			  return 0 ;

		// Gestion des événement claviers
			case WM_CHAR :
            return 0 ;  

        // Initialisation du menu avant son affichage
			case WM_INITMENU:
			  hmenu =  (HMENU) wParam;
			  //MenuCheckMark (hmenu, ID_OPTION_AUTOMAPPING, TRUE);

              OpenClipboard(hwnd);					
                   
              hMem = GetClipboardData(CF_MCX3);

              if (hMem==NULL) 
              {

                    EnableMenuItem(hmenu, ID_EDITION_COLLER, MF_BYCOMMAND | MF_DISABLED| MF_GRAYED);                  
    
              }
              else
              {
                    EnableMenuItem(hmenu, ID_EDITION_COLLER, MF_BYCOMMAND | MF_ENABLED);
              }


              CloseClipboard();



			// example of checking & unchecking
			return 0;

			case WM_MENUSELECT:
			// example of a menu selection	
			return 0;


		// Gestion à l'aide des touches virtuelles
		case WM_KEYDOWN:
		break;


        // Event occuring when the WINDOWS is resized 
		case WM_SIZE:
             //CZlen = LOWORD (lParam) ;
             //CZhei = HIWORD (lParam) ;
        return 0 ;

		// Event occuring when the mouse moves

		  // Event occuring when the WINDOWS is in need of repainting		
		case WM_PAINT :
			hdc = BeginPaint(hwnd,&ps);
			//PeinturerFenetre(hdc, BitGrild);
			EndPaint(hwnd,&ps);
		return 0L;


		  // Timer's events
		case WM_TIMER:
				hdc = GetDC (hwnd) ;
                ReleaseDC (hwnd, hdc) ;	                  			   
		return 0 ;
				

        case WM_CLOSE :
			  //if (canclose()==TRUE)
			if (QuitProgram())
			  {  DestroyWindow (hwnd);
			  }
        return 0 ;
	
        case WM_QUERYENDSESSION :
        return 0 ;

		  // Event occuring when closing the main WINDOWS
        case WM_DESTROY :
			//  if (canclose()==TRUE)
			   PostQuitMessage(0);
       return 0 ;

		  // I don't know what it does exactly.
	    case WM_SETFOCUS :
            //   SetFocus (hListBox) ;
        return 0 ;


		}

     return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
     }






