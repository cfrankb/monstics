/*-------------------------------------------------------------

  OBL3EDIT is part of the Static System V3.0 for Windows 95
           and NT 4.0.

  (c) 1997 Francois Blanchette, all rights reserved.


  HELLOWIN.C -- Displays "Hello, Windows 95!" in client area
                 and other samplers (c) Charles Petzold, 1996

                 UI samplers (c) Nancy Winnick Cluts, 1995

                 Samples code from Microsoft WIN32 SDK

   MAIN.C        Additional code (c) François Blanchette, 1997 
  
  ------------------------------------------------------------*/

// *** INCLUDED FILES ***
#include "include.h"
#include "menu.h"
#include "const.h"
#include "gadgets.h"
#include "Common.h"
#include "resource.h"
#include "dialog.h"
#include "WinFb.h"
#include "struc.h"
#include "Pal.h"
#include "WinEasy.h"
#include "obl3.h"
#include "draw.h"
#include "popfile.h"
#include "import.h"
#include "user_err.h"
#include "comcthlp.h"
#include "psObl.h"

// *** COMPILER DIRECTIVES ***

#pragma warning( disable : 4244 ) 

// ***  GLOBAL VARS  ***

HWND			hAppWnd,hwnd;			// HWND instance for the mother window
HINSTANCE		hAppInstance;			// Application instance
FILE *tfile;

// OBL3 vars............................................
USER_OBL3HEADER sHeader;
USER_OBL3   *psObl3;
int    iMx;
int    iMy;
int    iMaxMx;
int    iMaxMy;

// Yuck! don't crash my program..........................
int         bCritical = FALSE;
extern uchar PenColor;                  // PenColor
extern HWND hchildwnd;                  // Color palette
extern USER_OBL3HEADER sgOBL3;
HWND        hWndStatus;

// Grild Info Vars.......................................
DWORD  GRILD_LEN  = 64;
DWORD  GRILD_HEI=(48+16);
DWORD  GRILD_X =0;
DWORD  GRILD_Y =(32-4);
int    GRILD_SQR =8;
int    GRILD_FSQR =1;


// ***   CONSTANTES   ***

char        AppTitle []        = "OBL3EDIT beta";
const char  SansTitre [] = "(sans titre)";
const char  ColorsPaletteName[]
                        = "Palette de couleurs";
#define  _ReleaseDrag ReleaseDrag\
                      (bHasMouseZoned, &bDrag,  pDots,  pBackBits,\
                      &bFirst, &sLastDot);

#define TOOLS_BUTTON 7
//#define DEBUG_FB

// Resources icones
#define IDI_SMILEY      M2INT(IDI_ICON01)
#define IDI_WARNING2    M2INT(IDI_ICON03)
#define IDI_BLINDMAN    M2INT(IDI_ICON04)
#define IDI_RAINBOW     M2INT(IDI_ICON06)
#define IDI_TREE        M2INT(IDI_ICON07)
#define IDI_DEVIL       M2INT(IDI_ICON08)
#define IDI_YAN         M2INT(IDI_ICON10)
#define IDI_OBL3        M2INT(IDI_ICON12)
#define IDI_JOSIANE     M2INT(IDI_ICON13)
#define IDI_CUTE1       M2INT(IDI_ICON14)
#define IDI_NANCY       M2INT(IDI_ICON15)
#define IDI_ANNIE       M2INT(IDI_ICON16)
#define IDI_DOMINIQUE   M2INT(IDI_ICON17)
#define IDI_GHOST       M2INT(IDI_ICON18)
#define IDI_MONSTER     M2INT(IDI_ICON19)
#define IDI_JJEAN       M2INT(IDI_ICON20)
#define IDI_NATHALIE    M2INT(IDI_ICON21)
#define IDI_INFO        M2INT(IDI_ICON22)
#define IDI_JJEAN93     M2INT(IDI_ICON23)
#define IDI_GE96        M2INT(IDI_ICON24)
#define IDI_JLANGLOIS   M2INT(IDI_ICON25)
#define IDI_LGCK        M2INT(IDI_ICON26)
#define IDI_SOPHIE      M2INT(IDI_ICON27)
#define IDI_CUTE2       M2INT(IDI_ICON28)

// Liste de descriptions pour MenuSelect
USER_MENUHELP sMenuHelp[] =
{
    SC_SIZE,        "Change la taille de la fenêtre."            ,
    SC_MOVE,        "Déplace la fenêtre."                          ,
    SC_MINIMIZE,    "Réduit la fenêtre en icon."                   ,
    SC_MAXIMIZE,    "Agrandi la fenêtre à la largeur de l'écran."   ,
    SC_NEXTWINDOW,  "Active la prochaine fenêtre."                 ,
    SC_PREVWINDOW,  "Active la fenêtre précédente."             ,
    SC_CLOSE,       "Ferme la fenêtre."                        ,
    SC_VSCROLL,     "Vertical scroll?"                          ,
    SC_HSCROLL,     "Horizontal scroll?"                        ,
    SC_MOUSEMENU,   "A menu for mice."                          ,
    SC_KEYMENU,     "A menu for keys (I guess)."                ,
    SC_ARRANGE,     "Arrange something."                        ,
    SC_RESTORE,     "Restaure la fenêtre à sa taille normale."  ,
    SC_TASKLIST,    "Put up the task list dialog."              ,
    SC_SCREENSAVE,  "Save the screen!  Run for your life!"      ,
    SC_HOTKEY,      "Boy, is this key hot!" ,                    
    
    IDM_NEW     ,   "Crée un nouveau fichier",
    IDM_OPEN    ,   "Permet l'ouverture d'un fichier existant",
    IDM_SAVE    ,   "Sauvegarde le document courant",
    IDM_SAVEAS  ,   "Sauvegarde sous un autre nom",
    IDM_IMPORT  ,   "Importe des données à partir d'un autre fichier.",
    IDM_EXPORT  ,   "Exporte vers un autre fichier.",
    IDM_EXIT    ,   "Quitte l'application",
    IDM_CLEAR   ,   "Efface l'image courante",
    IDM_CUT     ,   "Coupe la sélection et place la sur le presse papier",
    IDM_COPY    ,   "Copie la sélection dans le presse papier",
    IDM_PASTE   ,   "Copie le contenu du presse papier",
    IDM_COPYSET ,   "Copie la série dans le presse papier",
    IDM_PASTESET,   "Recopie une série à partir du presse papier",
    IDM_INSERT  ,   "Insère une nouvelle image",
    IDM_REMOVE  ,   "Supprime l'image courante",            
    IDM_ABOUT   ,   "Affiche l'information sur l'application",
    IDM_UNDO    ,   "Annuler la dernière modification",
    IDM_REDO    ,   "Refaire la dernière modification",

    IDM_HASTOOLBAR, "Affiche/Masque la barre d'outils.",
    IDM_HASSTATUSBAR,"Affiche/Masque la barre d'état.",
    IDM_HASTOOLBOX, "Affiche/Masque la boîte à outils.",
    IDM_HASPALETTE, "Affiche/Masque la palette de couleurs.",
    IDM_HASPREVIEW, "Affiche/Masque l'apercu",
    IDM_EDITMODE,   "Affiche/Masque la grille d'édition.",

    IDM_BACK,       "Procède à l'image précédente.",
    IDM_NEXT,       "Procède à l'image suivante.",
    IDM_FLIPHORZ,   "Inverse horizontalement toutes les pixels de l'image.",
    IDM_FLIPVERT,   "Inverse verticalement toutes les pixels de l'image.",
    IDM_INVERT,     "Inverse la couleurs des pixels.",
    IDM_BIGGER,     "Agrandi l'image selon un facteur désigné.",
    IDM_PROPS,      "Affiche la feuille de propriétés.",
    IDM_REDIM,      "Redimensionne l'image",
    IDM_ROTATION90, "Effectue une rotation de 90' sur l'image.",

    IDM_PEN,        "Sert à dessiner",
    IDM_FLOOD,      "Sert de remplisseur automatique.",
    IDM_LINES,      "Sert à tracer des lignes",
    IDM_LINESARC,   "Sert à tracer des lignes en arches",
    IDM_CIRCLE,     "Sert à tracer des cercles",

    IDM_W1,         "Le crayon d'épaisseur 1",
    IDM_W2,         "Le crayon d'épaisseur 2",
    IDM_W3,         "Le crayon d'épaisseur 3",
    IDM_W4,         "Le crayon d'épaisseur 4",
    IDM_W5,         "Le crayon d'épaisseur 5",
    IDM_W6,         "Le crayon d'épaisseur 6",
    IDM_W7,         "Le crayon d'épaisseur 7",
    IDM_W8,         "Le crayon d'épaisseur 8",

    IDM_LARGEICON,  "Affiche les éléments en utilisant des grandes icônes.",
    IDM_SMALLICON,  "Affiche des éléments en utilisant des petites icônes.",
    IDM_LISTVIEW,   "Affiche des éléments dans une liste.",
    IDM_REPORTVIEW, "Affiche les informations de chaque élément dans une fenêtre.",

    0,NULL
};

// Liste de textes pour les tooltips
USER_MENUHELP sToolTips[] =
{
    IDM_NEW   , "Nouveau",
    IDM_OPEN  , "Ouvrir",
    IDM_SAVE  , "Sauvegarder",
    IDM_COPY  , "Copier",
    IDM_PASTE , "Coller",
    IDM_DELETE, "Supprimer",
    IDM_ABOUT , "À propos de..",
    IDM_CUT   , "Couper",
    IDM_PROPS , "Propriétés",
    IDM_LARGEICON, "Grandes Icônes",
    IDM_SMALLICON, "Petites Icônes",
    IDM_LISTVIEW, "Liste",
    IDM_REPORTVIEW, "Détails",

    IDM_PEN, "Crayon",
    IDM_FLOOD, "Remplissage",
    IDM_LINES, "Lignes",
    IDM_LINESARC, "Lignes archées",
    IDM_CIRCLE, "Cercles",
    IDM_RECT, "Rectangles",
    IDM_MAP, "Mapping manuel",

    501       , "Abc Hi Hi Hi",
    502       , "1121 Ho Ho Ho",
    503       , "!text Bla Bla Bla",
    504       , "Josiane Non Non Non",
    0         , NULL
};


// Structure d'une Statusbar 
USER_STATBAR sStatbar[] = 
{
        {0, "Ready.",300},
        {SBT_POPOUT, "2This text pops out.",480},
        {SBT_OWNERDRAW, "",490},
        0,0     
};

// Structure de la toolbar
TBBUTTON tbButtons[] = {
    { 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ STD_FILENEW, IDM_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ STD_FILEOPEN, IDM_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ STD_FILESAVE, IDM_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	
    { STD_CUT, IDM_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ STD_COPY, IDM_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ STD_PASTE, IDM_PASTE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},	
	{ STD_DELETE, IDM_DELETE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    
    { STD_PROPERTIES, IDM_PROPS, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    //12
    { 0, IDM_PEN, TBSTATE_ENABLED | TBSTATE_PRESSED | TBSTATE_CHECKED, 0L, 0L, 0},	
    { 1, IDM_FLOOD, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},	
    { 2, IDM_LINES,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 3, IDM_LINESARC,TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},   
    { 4, IDM_CIRCLE,TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},   
    { 5, IDM_RECT,TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},   
    { 6, IDM_MAP,TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},   


};


// Structure d'une PropretySheet Window
USER_PROPWIN PropWin[] = 
{
    M2INT(IDD_GENERALINFO),
    "Informations générales", 
    Page1Proc ,
    NULL ,

    M2INT(IDD_ITEMPROP),
    "Propriétés de l'item", 
    Page2Proc , 
    NULL ,

    M2INT(IDD_IMGPROPS),
    "Attributs des images", 
    Page3Proc ,
    NULL, 

    0,0,0,0
};


// ***  PROTOTYPES  ***
LRESULT CALLBACK WndProc (HWND , UINT , WPARAM , LPARAM );
HWND RegisterAndCreateAppColorPal(HINSTANCE hInstance);
HBITMAP MakeBitmap(int len, int hei, unsigned char *bits, HDC hdc);
HWND RegisterAndCreateEditGrild(HINSTANCE hInstance);
extern USER_PROPWIN PropWin [];
int XOR(int src1, int src2);
HWND CreatePreviewWindow(HINSTANCE ,HWND );
void Draw2(DWORD , DWORD , BYTE , USER_OBL3 * ,int , int , int , HWND , int );
BOOL CALLBACK ImageSizeDialogProc(HWND,	UINT, WPARAM , LPARAM );
BOOL CALLBACK ImageBiggerDialogProc( HWND ,	UINT, WPARAM, LPARAM);
int DrawImageNoZoom(int, int, USER_OBL3 *, USER_OBL3HEADER , HDC );
USER_OBL3UNDO *AddUndo(USER_OBL3UNDO *, char *);
void Draw(DWORD, DWORD ,  BYTE , USER_OBL3 * , int , int , int , HWND , int );
int LoadAny(USER_OBL3HEADER *, char *);


BOOL InCharArray(char *ptArray, int iSizeArray, char bSearch)
{
    int iCpt;

    if (iSizeArray==0) return FALSE;
    for (iCpt=0; 
        (iCpt<iSizeArray) && *(ptArray+iCpt)!= bSearch;
        iCpt++);

    return *(ptArray+iCpt)== bSearch;
}



void  MakeRainbow(HWND hwnd, USER_OBL3 *xxxx)
{

    int iRainColor = 0;
    char itColors[256];
    DWORD iCpt;
    DWORD iCpt2;
    char cTemp;
    InfoDialog(hwnd, "IDM_RAINBOW: Option disfonctionnelle.");
return;

    for (iCpt=0; iCpt<(16*sHeader.iLen *
                       sHeader.iHei); iCpt++)
    {
        cTemp = *(psObl3->PtrBits+iCpt);

        if (cTemp>16)
            if (InCharArray(itColors, iRainColor, cTemp)==FALSE)
            {
                itColors[iRainColor] = cTemp;
                iRainColor++;
            }
    }
    
    if (iRainColor<2) 
    {
        InfoDialog(hwnd, "L'effet ne peut requière un minimun de deux couleurs.");
        return;
    }


    for (iCpt=0; iCpt<iRainColor; iCpt++)
    {
        for (iCpt2=0; 
                iCpt2<(sHeader.iLen * sHeader.iHei);
                iCpt2++)
        {
        
           cTemp = *(psObl3->PtrBits+iCpt2);

        }
    }



    ;

}



//
//
//

void StatusMessageOneOf(USER_OBL3HEADER sHeader,
                  HWND hStatus)
{

    char ch[256];

    sprintf(ch, "%d de %d", sHeader.LastViewed+1, 
                            sHeader.iNbrImages);

    Status_SetText(hStatus, 1, SBT_POPOUT, ch);
    
}


//
//
//
void SetMaxMxMy()
{           if ((sHeader.iLen*OBL3FNT)>32)
                iMaxMx = (sHeader.iLen*OBL3FNT)-32;
            else
                iMaxMx = 0;

            if ((sHeader.iHei*OBL3FNT)>32)
                iMaxMy = (sHeader.iHei*OBL3FNT)-32;
            else
                iMaxMy =0;

            SetScrollRange(hAppWnd, SB_VERT, 0, iMaxMy, TRUE);
            SetScrollRange(hAppWnd, SB_HORZ, 0, iMaxMx, TRUE);
}


//
//
//

void LockCursor(BOOL *pHasMouseZoned,
                HWND hwnd)
{
    RECT sRect;        

    if (*pHasMouseZoned!=TRUE)
    {
         *pHasMouseZoned = TRUE;

          GetWindowRect(
                hwnd,
                &sRect);
  
           sRect.left = sRect.left +4;
           sRect.right = sRect.right -4;
           sRect.top = sRect.top + GRILD_Y +32+16-5;
           sRect.bottom = sRect.bottom -12*2;
                
           ClipCursor(&sRect);
           
    }

}



//
//
//
int DrawImageNoZoom(int iMx,
                     int iMy,
                     USER_OBL3 *psObl3,
                     USER_OBL3HEADER sHeader,
                     HDC hdc                     
                    )
{
        int x;
        int y;

        HBITMAP hbitmap;

        int iLen, isLen;
        int iHei, isHei;
        char *lpBits;
        char *pBits = psObl3->PtrBits;

        isLen = GRILD_LEN *8;
        isHei = GRILD_HEI *8;
        iLen = sHeader.iLen * OBL3FNT;
        iHei = sHeader.iHei * OBL3FNT;

        lpBits = malloc(isLen*isHei);
        if (lpBits==NULL) return FALSE;

        fillmem( (void*)lpBits,(BYTE) 0x97, isLen*isHei);

        for (y=0; (y+iMy)<iHei; y++)
        {
            for (x=0; (x+iMx)<iLen; x++)
            {
                *(lpBits + y*isLen + x) =
                   *(pBits+x+iMx+ (y+iMy)*iLen);                  
            }
        }
                
        hbitmap = MakeBitmap(GRILD_LEN*8, GRILD_HEI*8,
                             lpBits, hdc);

	    if (hbitmap)
	    { 
	    	PutBitmap( hdc, 
               hbitmap,
               GRILD_X,
               GRILD_Y)  ;
          	   DeleteObject(hbitmap);
	    }

        free(lpBits);

        return TRUE;
}


//
//
//



void DEBUG_FBUndo(USER_OBL3UNDO *psUndo)
{

#ifdef DEBUG_FB
    int x;
    fprintf(tfile, "%d %d\n",  
        psUndo->iNbUndo,
        psUndo->iNbRedo);
    for (x=0; x<MaxUndo; x++)
    {
    
           fprintf(tfile, "%x        %x\n", 
                psUndo->PtrUndo[x],
                psUndo->PtrRedo[x]);

    
    }

    fputs("\n****************************************\n", tfile);

#endif
}


//
//
//

USER_OBL3UNDO *AddUndo(USER_OBL3UNDO *psUndo,
                 char *pBits)
{

    int x;
    char *pUndoData;

    if (psUndo==NULL)
    {
        psUndo = malloc (sizeof(USER_OBL3UNDO));
        fillmem ((void*)psUndo, 0, sizeof(USER_OBL3UNDO));
    }

    pUndoData = malloc(sHeader.iLen * sHeader.iHei *
                       OBL3FNT* OBL3FNT);

    memcpy(pUndoData, pBits, sHeader.iLen * sHeader.iHei *
                       OBL3FNT* OBL3FNT);



    // Libère le dernier Undo
    if (psUndo->PtrUndo[MaxUndo-1])
        free (psUndo->PtrUndo[MaxUndo-1]);

    for (x=0; x<MaxUndo-1;  x++)
    {
        psUndo->PtrUndo[MaxUndo-x-1] = 
            psUndo->PtrUndo[MaxUndo-x-2] ;
    }
    
    psUndo->iNbUndo++;
    if  (psUndo->iNbUndo>MaxUndo) 
        psUndo->iNbUndo = MaxUndo;

    psUndo->PtrUndo[0] = pUndoData;

#ifdef DEBUG_FB
    fputs("AddUndo\n",tfile);
    DEBUG_FBUndo(psUndo);
#endif

    return psUndo;


}

//
//
//
USER_OBL3UNDO *DelUndo(USER_OBL3UNDO *psUndo,
                 char *pBits)
{
    int x;

    if (psUndo==NULL)
    {
        psUndo = malloc (sizeof(USER_OBL3UNDO));
        fillmem ((void*)psUndo, 0, sizeof(USER_OBL3UNDO));
    }

    if (psUndo->iNbUndo>0)
    {
       
        // Libère dernier Redo
        if (psUndo->PtrRedo[MaxUndo-1]!=NULL)
        {
#ifdef DEBUG_FB
            fprintf(tfile,"Free: psUndo->PtrRedo[MaxUndo-1] = %x\n",
                psUndo->PtrRedo[MaxUndo-1]);
#endif
            free(psUndo->PtrRedo[MaxUndo-1]);
        }

        // Insert a blank in Redo List
        for (x=0; x<MaxUndo-1;  x++)
        {
            psUndo->PtrRedo[MaxUndo-x-1] = 
                psUndo->PtrRedo[MaxUndo-x-2] ;
        }

        // Fill Blank in Redo List
        psUndo->PtrRedo[0] =
                 malloc(sHeader.iLen * sHeader.iHei *
                        OBL3FNT* OBL3FNT);

        memcpy(psUndo->PtrRedo[0], pBits, sHeader.iLen * sHeader.iHei *
                       OBL3FNT* OBL3FNT);

        // Make the actual undo
        memcpy(pBits, psUndo->PtrUndo[0], sHeader.iLen * sHeader.iHei *
                       OBL3FNT* OBL3FNT);


        // Remove First item in Undo List
        for (x=0; x<MaxUndo-1;  x++)
        {
            psUndo->PtrUndo[x] = 
                psUndo->PtrUndo[x+1] ;
        }        

        psUndo->PtrUndo[psUndo->iNbUndo -1]    
           = NULL;
   
    }

    psUndo->iNbRedo++;
    if  (psUndo->iNbRedo>MaxUndo) 
        psUndo->iNbRedo = MaxUndo;

    if  (psUndo->iNbUndo>0) 
        psUndo->iNbUndo --;

#ifdef DEBUG_FB
    fputs("DelUndo\n",tfile);
    DEBUG_FBUndo(psUndo);
#endif

    return psUndo;

}

//
//
//
USER_OBL3UNDO *DelRedo(USER_OBL3UNDO *psUndo,
                 char *pBits)
{
    int x;

    if (psUndo==NULL)
    {
        psUndo = malloc (sizeof(USER_OBL3UNDO));
        fillmem ((void*)psUndo, 0, sizeof(USER_OBL3UNDO));
    }

    if (psUndo->iNbRedo>0)
    {


        AddUndo(psUndo, pBits);
        
        memcpy(pBits, psUndo->PtrRedo[0],sHeader.iLen * sHeader.iHei *
                       OBL3FNT* OBL3FNT);

        for (x=0; x<MaxUndo-1;  x++)
        {

            psUndo->PtrRedo[x] = 
                psUndo->PtrRedo[x+1] ;
            
        }        

        psUndo->PtrRedo[psUndo->iNbRedo -1]    
            = NULL;
       

    }

    if  (psUndo->iNbRedo>0) 
        psUndo->iNbRedo --;

#ifdef DEBUG_FB
    fputs("DelRedo\n",tfile);
    DEBUG_FBUndo(psUndo);
#endif


    return psUndo;

}








//
//
//

void ImageChanged(BOOL *pHasChanged, 
                  HWND hwnd,
                  char *Filename)
{
      if (*pHasChanged == FALSE)
      {
            *pHasChanged=TRUE;
            DoCaption(hwnd, 
                      AppTitle, 
                      Filename, 
                      TRUE);
                  
      }
}

//
//
//

void ReleaseDrag(
            BOOL bHasMouseZoned,
            BOOL *bDrag,
            USER_DOT *pDots,
            char *pBackBits,
            BOOL *bFirst,
            USER_DOT *pLastDot
            )
{

            if (bHasMouseZoned)
            {
                ClipCursor(NULL);
                bHasMouseZoned = FALSE;
            }
            
            if (*bDrag)
            {
                *bDrag = FALSE;
                if (pDots)
                {
                    free(pDots);
                    pDots=NULL;    
                }

                if (pBackBits)
                {
                    free(pBackBits);
                    pBackBits=NULL;
                }
                *bFirst = TRUE;
            }

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
// HWND CreateToolbar(HWND hwnd, TBBUTTON tbButtons[]);
//
HWND CreateToolbar(HWND hwnd, TBBUTTON tbButtons[])
{
        HWND hWndToolbar;
        TBADDBITMAP tb;
        int index, stdidx;
        
		// Create the toolbar control.
            
            hWndToolbar = CreateToolbarEx(hwnd,
                WS_CHILD | WS_BORDER | WS_VISIBLE | 
                TBSTYLE_TOOLTIPS, ID_TOOLBAR, 32,
                (HINSTANCE)HINST_COMMCTRL, 
                IDB_STD_SMALL_COLOR, (LPCTBBUTTON)tbButtons,
                12,16, 16, 16, 16, sizeof(TBBUTTON));

			if (hWndToolbar == NULL )
			{
				MessageBox (NULL, "Tool not created!", NULL, MB_OK );
				//break;
                return NULL;
			}

        // Add the system-defined view bitmaps.
            tb.hInst = hAppInstance;//HINST_COMMCTRL;
            tb.nID = IDB_TOOLBOX;
            stdidx = SendMessage(hWndToolbar, TB_ADDBITMAP, 12, (LPARAM)&tb);

/*          tb.hInst = HINST_COMMCTRL;
            tb.nID = IDB_VIEW_SMALL_COLOR;
            stdidx = SendMessage(hWndToolbar, TB_ADDBITMAP, 12, (LPARAM)&tb);
*/            

        // Update the indices to the bitmaps.
            for (index = 0; index < TOOLS_BUTTON; index++)
                tbButtons[12+index].iBitmap += stdidx;
 
         // Add the view buttons.
            SendMessage(hWndToolbar, TB_ADDBUTTONS, 
                TOOLS_BUTTON, (LONG) &tbButtons[12]);         
  
        return hWndToolbar;
}



//
// HWND InitApp(HINSTANCE hInstance)
//
HWND InitApp(HINSTANCE hInstance)
{
    USER_WINDOW sMainWnd;
    uint cx,cy;

    //LPCSTR hRTFLib;

    // Register the ToolbarClass
    //RegisterToolboxClass();

    // Load the rich edit DLL
    //hRTFLib = LoadLibrary("RICHED32.DLL");
    //if (hRTFLib ==NULL) 
    //    error ("FATAL","Cannot load RICHED32.DLL");

    cx  = GetSystemMetrics (SM_CXSCREEN)  ;
    cy  = GetSystemMetrics (SM_CYSCREEN)  ;

    // Create Mother Windoz for the application
    sMainWnd.iClassStyle= CS_HREDRAW | CS_VREDRAW | 
                          CS_OWNDC | CS_DBLCLKS;

    sMainWnd.iClassProc = WndProc;
    sMainWnd.hIcon      = LoadIcon(hInstance, "ABC");
    sMainWnd.hCursor    = NULL;

    sMainWnd.hBrush     = NULL;//(HBRUSH) GetStockObject(WHITE_BRUSH);
    sMainWnd.cMenuName  = (M2INT(IDR_MENU1));
    sMainWnd.cClassName = "MiniApp OBL3EDIT";
        
    sMainWnd.iWndExStyle= 0;
    sMainWnd.cWndTitle  = "";
    sMainWnd.iWndStyle  = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN
                          |  WS_VSCROLL | WS_HSCROLL;
    sMainWnd.iWndLen    = 640/2;			    
    sMainWnd.iWndHei    = 320;
    sMainWnd.iWndX      = (cx-sMainWnd.iWndLen)/2;
    sMainWnd.iWndY      = (cy-sMainWnd.iWndHei)/2;

    hAppWnd = (void*) RegisterAndCreateWindow
                        (hInstance, sMainWnd);

    ShowWindow(hAppWnd,SW_RESTORE) ;
    //ShowWindow (hAppWnd, iCmdShow) ;
    UpdateWindow (hAppWnd) ;

    SetMaxMxMy();
    InvalidateRect(hAppWnd, NULL, FALSE);
    
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
     
     int iStatus;

     char szMsg[1024];
     char *pDot;


     //InitCommonControls ();
	 hAppInstance= hInstance;     

   
     if  (strlen(szCmdLine)!=0)
     {
        strcpy(&sHeader.szFilename[0] , szCmdLine);

        iStatus = LoadAny(&sHeader,
                           sHeader.szFilename);

        strcpy(&sHeader.szFilename[0] , szCmdLine);

        if (iStatus!=TRUE)
        {

            pDot = LastOf(sHeader.szFilename, '\\');
            if (pDot!=NULL) strcpy(sHeader.szFilename, pDot+1);       
            
            wsprintf(szMsg, "La lecture du fichier %c%s%c a été " \
                "impossible car ", 34, sHeader.szFilename,
                34);


            switch (iStatus)
            { 
            case err_format:
                strcat(szMsg, "le format est incorrect.\n\nVous assurez que le fichier est dans un format supporté.");
                break;

            case err_filename:
                strcat(szMsg, "le nom du fichier est incorrect.\n\nAssurez-vous que le nom du fichier est valide.");
                break;

            case err_fileopen:
                strcat(szMsg, "l'ouverture fichier a échouée.\n\nAssurez-vous que le fichier existe.");
                break;

            default:
                strcat(szMsg, "une erreur inconnue s'est produite.");
                break;

            }
        
            InfoDialog(0, szMsg);
            strcpy(sHeader.szFilename , "");
            
        }
        else
        {
            pDot = LastOf(sHeader.szFilename, '.');
            if (pDot!=NULL) strcpy(pDot, ".obl");       
        }
     

     }

	 if (CreateAppPal()==FALSE)
        return( FALSE);


     InitApp(hInstance);

      
	 if (!hAppWnd)
		 error("ERREUR FATALE", "Création de la fenetre mère a échouée");
               
     UpdateWindow (hwnd) ;
 	 hAccel = LoadAccelerators(hInstance, M2INT(ACC1));
     
    for (;;)
    {
  
        if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

          if (!TranslateAccelerator (hAppWnd, hAccel, &msg))
               {
               TranslateMessage (&msg) ;
               DispatchMessage (&msg) ;
               }
          else
          {
            WaitMessage();
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




BYTE GetGrildColor(DWORD x, DWORD y)
{
    if (  ((x%16)==15) || ((y%16)==15) )
        return (BYTE) 0x34;

    if ( ((x%8)==7) || ((y%8)==7))
        return (BYTE) 0x65;
    else
        return (BYTE) 0x97;
}



void DrawHairySqr(void *pDest, 
                  UCHAR bColor, 
                  UCHAR bGrildColor,
                  int iAdd)
{


            __asm 
            {
                push eax
                push ebx
                push edx
                push edi               

                mov edi, pDest
                mov al, bColor
                mov ah,al
                mov bx,ax
                shl eax,16
                mov ax,bx
                mov bh,bGrildColor
                shl ebx,16
                mov bx,ax
                mov edx, iAdd

                mov [edi],eax       //1
                mov [edi+4],ebx
                add edi, edx

                mov [edi],eax       //2
                mov [edi+4],ebx
                add edi, edx

                or al,al
                jne PixNotZZ

                mov bx,0x3030

PixNotZZ:

                mov [edi],eax       //3
                mov [edi+4],ebx
                add edi, edx

                mov [edi],eax       //4
                mov [edi+4],ebx
                add edi, edx

                mov bx,ax

                mov [edi],eax       //5
                mov [edi+4],ebx
                add edi, edx

                mov [edi],eax       //6
                mov [edi+4],ebx
                add edi, edx

                mov [edi],eax       //7
                mov [edi+4],ebx
                add edi, edx

                mov al,bGrildColor
                mov ah,al
                shl eax,16
                mov al,bGrildColor
                mov ah,al
                mov [edi],eax       
                mov [edi+4],eax      //8

                pop edi
                pop edx
                pop ebx
                pop eax

            }

}

int DrawGrild(USER_OBL3 *psObl3, 
               DWORD iImaLen,
               DWORD iImaHei,
               DWORD iMx,
               DWORD iMy,
               HDC hdc)


{

    char *pBits;
    char *pOblBits;
    DWORD x;
    DWORD y;
    HBITMAP hbitmap;

    BYTE bColor;
    void * pDest;
    DWORD iAdd;
    BYTE bGrildColor;

    pOblBits = psObl3->PtrBits;      

    pBits = malloc(GRILD_LEN * GRILD_HEI * 8 * 8);
    if (pBits==NULL) return FALSE;

    for (y=0; (y<GRILD_HEI) ; y++)
    {
        for (x=0; (x<GRILD_LEN) ; x++)
        {

            if ( ((iMy+y)<iImaHei) &&
                 ((iMx+x)<iImaLen))
            {
                 bColor = *(pOblBits+(iMy+y)*iImaLen+x+iMx);
                 bGrildColor = GetGrildColor(iMx+x, iMy+y);
            }
            else 
            {
                 bColor = 0x97;
                 bGrildColor =0x97;
            }

            pDest = pBits +
                        (y*8)*GRILD_LEN*8 +
                        (x*8);

            iAdd = GRILD_LEN *8;

            DrawHairySqr(
                pDest, 
                bColor, 
                bGrildColor, 
                iAdd);
            

        }
    }

    hbitmap = MakeBitmap(GRILD_LEN *8, GRILD_HEI *8, pBits, hdc);

	if (hbitmap)
	{ 
	    	PutBitmap( hdc, 
               hbitmap,
               GRILD_X,
               GRILD_Y)  ;
          	   DeleteObject(hbitmap);
	}

    free(pBits);
    
    return TRUE;


}


//
//
//



void Draw(DWORD x, 
          DWORD y, 
          BYTE bColor, 
          USER_OBL3 *psObl3 ,
          int iLen,
          int iMx,
          int iMy,
          HWND hPreview,
          int iPenSize)
{


    int xx;
    int yy;
    static RECT sRect;

    char *pOblBits = psObl3->PtrBits;

    for (yy=0;(yy<iPenSize) && (yy+y+iMy<(sHeader.iHei*OBL3FNT))
        ; yy++)
    {
        for (xx=0; (xx<iPenSize) 
              && (xx+x+iMx<(sHeader.iLen*OBL3FNT))
            ; xx++)
        {
            if (bColor!=0xff)
            *(pOblBits + x + iMx + xx +
                (iMy + y +yy)*iLen) = bColor;
        }
    }

    sRect.left = x * GRILD_SQR + GRILD_X;
    sRect.right = sRect.left + (GRILD_SQR+1)*iPenSize;
    sRect.top = y * GRILD_SQR + GRILD_Y;
    sRect.bottom = sRect.top + (GRILD_SQR+1)*iPenSize;
  

    InvalidateRect(
        hAppWnd,	
        &sRect,	
        FALSE);

     InvalidateRect(hPreview, NULL, FALSE);


}


//
//
//

void Rect2Dz(RECT sRect,
             DWORD *pDx,
             DWORD *pDy,
             DWORD *pL,
             DWORD *pH)
{



    *pH = (sRect.bottom - sRect.top)/8;    
    if ((sRect.bottom - sRect.top)& 7 )
        *pH = *pH +1;

    *pL = (sRect.right - sRect.left)/8 ;
     if ((sRect.right - sRect.left)& 7 )
         *pL = *pL +1;
          
    *pDx = (sRect.left - GRILD_X)/8;
    *pDy = (sRect.top - GRILD_Y)/8;



}

//
//
//



int DrawOneSquare(
              USER_OBL3 *psObl3, 
               DWORD iImaLen,
               DWORD iImaHei,
               DWORD iMx,
               DWORD iMy,
               HDC hdc,
               RECT sRect)
{
          
    static DWORD iDx;
    static DWORD iDy;
    static DWORD iL;
    static DWORD iH;

    static DWORD x;
    static DWORD y;

    BYTE *pBits;
    BYTE *pOblBits;
    BYTE bColor;
    BYTE bGrildColor;

    HBITMAP hbitmap;

    DWORD iAdd;
    void *pDest;
    
    pOblBits = psObl3->PtrBits;

    Rect2Dz(sRect, &iDx, &iDy, &iL, &iH);

    if  ( ((iMx+iDx)>=iImaLen) ||
          ((iMy+iDy)>=iImaHei) )
          return FALSE;

    bColor = *(pOblBits + iMx + iDx
               + (iDy +iMy)* iImaLen);

    bGrildColor = GetGrildColor(iMx+iDx, iMy+iDy);

    pBits = malloc( 64  );
    fillmem(pBits, (BYTE) 0x97, 64);
    if (pBits==NULL) return FALSE;

     pDest = pBits; 
     iAdd =8;


     DrawHairySqr(
         pDest, 
         bColor, 
         bGrildColor, 
         iAdd);
         
            

    hbitmap = MakeBitmap(8,8 , pBits, hdc);

	if (hbitmap)
	{ 
	    	PutBitmap( hdc, 
               hbitmap,
               sRect.left,
               sRect.top)  ;
          	   DeleteObject(hbitmap);
	}

    free(pBits);
    return TRUE;

}


//
//
//

void UmbaScroll(HWND hwnd, 
                int iDx,
                int iDy,
                RECT *psRect)
{

    static RECT lsRect;
    ScrollWindowEx(
             hwnd,
             iDx,
             iDy,
             psRect,
             psRect,
             NULL,
             &lsRect,
             SW_INVALIDATE);

             UpdateWindow(hwnd);

}


//
//
//

int DrawRowCol(USER_OBL3 *psObl3, 
               DWORD iImaLen,
               DWORD iImaHei,
               DWORD iMx,
               DWORD iMy,
               HDC hdc,
               RECT sRect)
{

    char *pBits;
    char *pOblBits;
    DWORD x;
    DWORD y;
    HBITMAP hbitmap;    

    static DWORD iDx;
    static DWORD iDy;
    static DWORD iL;
    static DWORD iH;

    BYTE bColor;
    BYTE bGrildColor;

    void *pDest;
    DWORD iAdd;

    pOblBits = psObl3->PtrBits;

    Rect2Dz(sRect, &iDx, &iDy, &iL, &iH);
    iL++;
    iH++;
    if (iDx) {iDx--; iL++;}
    if (iDy) {iDy--; iH++;}

    if  ( ((iMx+iDx)>=iImaLen) ||
          ((iMy+iDy)>=iImaHei) )
    {
        pBits = malloc(iH * iL * 8 * 8);
        if (pBits==NULL) return FALSE;

        fillmem(pBits, (BYTE) 0x97, iL * iH * 8 * 8);

        hbitmap = MakeBitmap(iL *8, iH  *8, pBits, hdc);

	    if (hbitmap)
	    { 
	    	PutBitmap( hdc, 
               hbitmap,
               GRILD_X+iDx*8,
               GRILD_Y+iDy*8)  ;
          	   DeleteObject(hbitmap);
	    }

        free(pBits);   
        return FALSE;

    }

    bColor = *(pOblBits + iMx + iDx
               + (iDy +iMy)* iImaLen);

    pBits = malloc(iH * iL * 8 * 8);
    if (pBits==NULL) return FALSE;

    for (y=0; (y<iH) ; y++)
    {
        for (x=0; (x<iL); x++)
        {

            if ( ((iMy+y+iDy)<iImaHei) &&
                 ((iMx+x+iDx)<iImaLen))
            {
                bColor = *(pOblBits+(iMy+y+iDy)*
                       iImaLen+x+iMx+iDx);
                bGrildColor = 
                     GetGrildColor(iDx+x+iMx, iDy+y+iMy);
            }
            else 
            {
                 bColor = 0x97;
                 bGrildColor = bColor;
            }

            pDest = pBits +
                        (y)*8*iL*8 +
                        (x)*8;

            iAdd = iL*8;

             DrawHairySqr(
                pDest, 
                bColor, 
                bGrildColor, 
                iAdd);
         
        }
    }

    hbitmap = MakeBitmap(iL *8, iH  *8, pBits, hdc);

	if (hbitmap)
	{ 
	    	PutBitmap( hdc, 
               hbitmap,
               GRILD_X+iDx*8,
               GRILD_Y+iDy*8)  ;
          	   DeleteObject(hbitmap);
	}

    free(pBits);  
    return TRUE;
}


void FillScRect(HWND hwnd, RECT *pRect)
{
      GetWindowRect(hwnd, pRect);
      pRect->bottom = pRect->bottom-
                          pRect->top 
                          -10;
      pRect->top = GRILD_Y;

      pRect->right = pRect->right - pRect->left;
      pRect->left =0    ;
}

int SaveAsOBL3File(char *Filename,
                 char *Title,
                 USER_OBL3HEADER *psHeader,
                 HWND hwnd)
{
        static char szFilter_OBL[] = "Statics Objects (*.OBL)\0*.obl\0\0"  ;
        char lcFilename[1024];
        char lcTitle[1024];
        int iStatus;

        PopFileInitialize (hwnd, szFilter_OBL) ;			   			   
        strcpy(lcFilename, Filename);
            
        iStatus = PopFileSaveDlg 
                      (hwnd, 
                      lcFilename, 
                      lcTitle);

         if (iStatus)
         {
             iStatus = SaveOBL3(psHeader, lcFilename); 
             if (iStatus==TRUE)
             {
                 strcpy(Filename, lcFilename);
                 strcpy(Title, lcTitle);

              }
          }

         return iStatus;
}


int SaveOBL3File(char *Filename,
                 char *Title,
                 USER_OBL3HEADER *psHeader,
                 HWND hwnd)
{

        if (strlen(Filename))
        {
            return SaveOBL3(psHeader, Filename);            
        }
        else
        {
            return SaveAsOBL3File
                   (Filename, 
                    Title,
                    psHeader,
                    hwnd);
        }
}


int LoadAny(USER_OBL3HEADER *pHeader, 
            char *szFilename)
{
    char *pDot;

     pDot = LastOf(szFilename, '.');

     if ((pDot) == NULL) 
        return err_filename;

     if (_stricmp(pDot, ".obl")==0)
     {
         return LoadOBL3(pHeader, szFilename);
     }

     if (_stricmp(pDot, ".mcx")==0)
     {
         SendMessage (hWndStatus, SB_SETTEXT, 0, 
                      (LPARAM)(LPSTR)"Patience - Conversion en cours.");
         UpdateWindow(hAppWnd);
       return Import_MCX2OBL 
              (szFilename, 
               pHeader);
 
     }

     if (_stricmp(pDot, ".ima")==0)
     {
         SendMessage (hWndStatus, SB_SETTEXT, 0, 
                      (LPARAM)(LPSTR)"Patience - Conversion en cours.");
         UpdateWindow(hAppWnd);

       return Import_IMA2OBL (
                    szFilename,
                    pHeader);
 
     }

    return err_filename;
}

int LoadOBL3File(char *Filename,
                 char *Title,
                 USER_OBL3HEADER *psHeader,
                 USER_OBL3 **ppsFirst,
                 HWND hwnd
                 )
{

        static char szFilter_OBL[] = 
          "Tous les formats supportés\0*.obl;*.ima;*.mcx\0" \
          "Static Objects (*.OBL)\0*.obl\0Static Images (*.IMA, *.MCX)\0*.ima;*.mcx\0" ;
        char lcFilename[1024];
        char lcTitle[1024];
        char *pDot;

        USER_OBL3HEADER *lpsHeader;

        int iStatus;

        PopFileInitialize (hwnd, szFilter_OBL) ;			   			   
        strcpy(lcFilename, Filename);

        iStatus =PopFileOpenDlg 
    			        (hwnd, 
        			    lcFilename, 
			            lcTitle);
        
         if ( iStatus)
         {
             

             lpsHeader = malloc(sizeof(USER_OBL3HEADER));
             //iStatus = LoadOBL3(lpsHeader, lcFilename);
             iStatus = LoadAny(lpsHeader, lcFilename);

             pDot = LastOf(lcFilename, '.');
             strcpy(pDot, ".obl");

             switch (iStatus)
             {

             case TRUE:
                    FreeOBL3(psHeader);
                    memcpy(psHeader, lpsHeader, 
                           sizeof(USER_OBL3HEADER));

                    psHeader->LastViewed=0;
                    *ppsFirst = psHeader->PtrFirst;
                    strcpy(Filename, lcFilename);
                    strcpy(Title, lcTitle);

             break;

             default:
             break;                  

             }
         }
         else
         {
              SendMessage (hWndStatus, SB_SETTEXT, 0, 
                         (LPARAM)(LPSTR)"Ready.");
                return FALSE;
         }

        SendMessage (hWndStatus, SB_SETTEXT, 0, 
                    (LPARAM)(LPSTR)"Ready.");
        free(lpsHeader);
        return iStatus;
}

int FlipHorz(char *pBits, int iLen, int iHei)
{
    char *pTemp;
    int y;
    int x;
    pTemp = malloc(iLen);
    if (pTemp==NULL) return FALSE;
    
    for (y=0; y<iHei; y++)
    {
        ddmemcpy(pTemp, pBits+y*iLen, iLen);
        for (x=0; x<iLen; x++)
        {
            *(pBits+y*iLen+x)  =
                *(pTemp+iLen-1-x);
        }

    }
    free(pTemp);
    return TRUE;
}


int FlipVert(char *pBits, int iLen, int iHei)
{
    char *pTemp;
    int y;

    pTemp = malloc(iLen);
    if (pTemp==NULL) return FALSE;

    for (y=0;y<iHei/2; y++)
    {
        ddmemcpy(pTemp, pBits+y*iLen, iLen);
        ddmemcpy(pBits+y*iLen,
               pBits+(iHei-1-y)*iLen, iLen);
        ddmemcpy(pBits+(iHei-1-y)*iLen,
               pTemp, iLen);
    }

    free(pTemp);
    return TRUE;

}


int Invert(char *pBits, int iLen, int iHei)
{
    int cpt;
    for (cpt=0; cpt<iLen*iHei; cpt++, pBits++)
        *pBits = (BYTE) XOR(*pBits, 0xf0);
    return TRUE;
}




void GotoNext(USER_OBL3HEADER *pHeader,
              USER_OBL3 **ppObl)
{
    USER_OBL3 *pObl;
    pObl = *ppObl;

    if (pObl->PtrNext==NULL)
    {

        pObl->PtrNext = MakeOBL3(pHeader->iLen, 
                                 pHeader->iHei,
                                 pObl,
                                 NULL);

        *ppObl = pObl->PtrNext;
        pHeader->iNbrImages ++;
        pHeader->LastViewed++;
    }
    else
    {

        *ppObl = pObl->PtrNext;
        pHeader->LastViewed++;
    }
}


void GotoBack(USER_OBL3HEADER *pHeader,
              USER_OBL3 **ppObl)
{
    USER_OBL3 *pObl;
    pObl = *ppObl;

    if (pObl->PtrPrev==NULL)
    {

        pObl->PtrPrev = MakeOBL3(pHeader->iLen, 
                                 pHeader->iHei,
                                 NULL,
                                 pObl);

        *ppObl = pObl->PtrPrev;
        pHeader->iNbrImages ++;
        
    }
    else
    {

        *ppObl = pObl->PtrPrev;
        pHeader->LastViewed--;
    }
}


void MouseDraw(
               HWND hwnd,
               WPARAM wParam,
               LPARAM lParam,
               int *pHasChanged,
               USER_OBL3HEADER sHeader,
               USER_OBL3 *psObl3,
               int iMx,
               int iMy,
               char *Filename,
               BOOL *pHasMouseZoned, 
               HWND hPreview,
               int iPenSize,
               UINT iMsg
               )
{
      static MOUSE mouse = {(DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1, 
                            (DWORD) -1,
                            (BYTE)  -1};

      BYTE bTheColor;

      if (wParam & MK_LBUTTON || 
                   wParam & MK_RBUTTON)
      {

            if ((LOWORD (lParam)<GRILD_X ) ||
                 (HIWORD (lParam)<GRILD_Y))
            return;

            LockCursor(pHasMouseZoned, hwnd);

            mouse.x = (LOWORD (lParam) - GRILD_X) /GRILD_SQR;
            mouse.y = (HIWORD (lParam) - GRILD_Y)/GRILD_SQR;		

		    mouse.button = wParam;

            switch (mouse.button)
            {
            case MK_LBUTTON:
                bTheColor = (BYTE) PenColor;
            break;

            case MK_RBUTTON:
                bTheColor = (BYTE) 0;
            break;

            default:
                bTheColor = (BYTE) -1;
            break;

            }

            if( (mouse.last_x == mouse.x) &&
                (mouse.last_y == mouse.y) &&
                (bTheColor == mouse.bColor))
            return;

            mouse.bColor = bTheColor;
            mouse.last_x= mouse.x;
        	mouse.last_y= mouse.y;

            if ((mouse.x >= (DWORD) GRILD_LEN *GRILD_FSQR) ||
                (mouse.y >= (DWORD) GRILD_HEI *GRILD_FSQR) ||
                (mouse.x+iMx >= sHeader.iLen*OBL3FNT) ||
                (mouse.y+iMy >= sHeader.iHei*OBL3FNT))
            return;
                                        
		    if (mouse.button==MK_LBUTTON)
            {
                if (*pHasChanged == FALSE)
                {
                      *pHasChanged=TRUE;
                          DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);
                  }

                    if ((iMsg==WM_LBUTTONDOWN) ||
                        (iMsg==WM_RBUTTONDOWN))
                    psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);
                    
                   Draw(mouse.x , 
                       mouse.y , 
                       PenColor, 
                       psObl3,
                       sHeader.iLen*OBL3FNT,
                       iMx,
                       iMy,
                       hPreview,
                       iPenSize);
              }

	    	  if (mouse.button==MK_RBUTTON)
              {
                    if (*pHasChanged == FALSE)
                    {
                         *pHasChanged=TRUE;
                         DoCaption(hwnd, 
                             AppTitle, 
                             Filename, 
                             TRUE);

                     }

                    if ((iMsg==WM_LBUTTONDOWN) ||
                        (iMsg==WM_RBUTTONDOWN))
                      psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);

                     Draw(mouse.x , 
                          mouse.y , 
                          0, 
                          psObl3,
                          sHeader.iLen*OBL3FNT,
                          iMx,
                          iMy,
                          hPreview,
                          iPenSize
                          );
                }
      }                    


}



// Assume 4 bytes aligned lines
char *MakeTiledBitmap(char *pSrcBits, 
                      int iSrcLen,
                      int iSrcHei,
                      int iDestLen,
                      int iDestHei)
{

    char * pDestBits;
    static int iHeiLeft;
    static int iLenLeft;
    static int x;
    static int y;
    static int yy;

    pDestBits = malloc(iDestLen * iDestHei);
    if (pDestBits==NULL) return NULL;
   
    y=0;
    for (iHeiLeft = iDestHei;iHeiLeft;)
    {

      x=0;
      for (iLenLeft = iDestLen; iLenLeft;)
      {

          for (yy=0; yy < min(iSrcHei,iHeiLeft); 
                   yy++)
          {

                ddmemcpy(pDestBits+(yy+y)*iDestLen+x,
                       pSrcBits+yy*iSrcLen,
                       min(iSrcLen, iLenLeft));
          }
         
          iLenLeft = iLenLeft - min(iSrcLen, iLenLeft);
          x=x+iSrcLen;
      }

      iHeiLeft = iHeiLeft - min(iSrcHei, iHeiLeft);
      y = y +yy;
    }

    return pDestBits;
}


int PeinturerFenetre(HWND hwnd,
                      USER_OBL3HEADER sHeader,
                      USER_OBL3 *psObl3,
                      int iMx,
                      int iMy,
                      BOOL bCritical,
                      BOOL bbHasEdit,
                      BOOL bHasZoom
                      )
{
    PAINTSTRUCT ps ;
    HDC hdc;
    char *pBits;
    HBITMAP hbitmap;

    if (bCritical) 
    {
         hdc = BeginPaint(hwnd,&ps);
    	 EndPaint(hwnd,&ps);
         return 0;
     }

     hdc = BeginPaint(hwnd,&ps);

     if (bbHasEdit!=TRUE)
     {
        pBits = MakeTiledBitmap(
                      psObl3->PtrBits, 
                      sHeader.iLen*OBL3FNT,
                      sHeader.iHei*OBL3FNT,
                      GRILD_LEN*8,
                      GRILD_HEI*8);

        hbitmap = MakeBitmap
                     (GRILD_LEN*8, 
                      GRILD_HEI*8, pBits, hdc);

    	if (hbitmap)
	    { 
	    	PutBitmap( hdc, 
               hbitmap,
               GRILD_X,
               GRILD_Y)  ;
          	   DeleteObject(hbitmap);
	    }

        free(pBits);
     	EndPaint(hwnd,&ps);
        return 0;
     
     }


     if (bHasZoom!=TRUE)
     {
         DrawImageNoZoom(iMx,
                     iMy,
                     psObl3,
                     sHeader,
                     hdc);
    	 EndPaint(hwnd,&ps);
         return 0;

     }

     if (((ps.rcPaint.bottom - ps.rcPaint.top) == 9) &&
          ((ps.rcPaint.right - ps.rcPaint.left) == 9))
     {

          DrawOneSquare(
          psObl3, 
          sHeader.iLen*OBL3FNT   ,
          sHeader.iHei*OBL3FNT    ,
          iMx,
          iMy,
          hdc,
          ps.rcPaint) ;

       }
       else
       {
            if (ps.rcPaint.right |
                ps.rcPaint.left|
                ps.rcPaint.top |
                ps.rcPaint.bottom)
            {
                DrawRowCol(
                   psObl3,                       
                   sHeader.iLen*OBL3FNT,
                   sHeader.iHei*OBL3FNT,
                   iMx,
                   iMy,
                   hdc,
                   ps.rcPaint) ;
                   
             }
             else
             {
                DrawGrild(psObl3, 
                        sHeader.iLen*OBL3FNT,
                        sHeader.iHei*OBL3FNT,
                        iMx,
                        iMy,
                        hdc);
              }
                
       }

            
	EndPaint(hwnd,&ps);
    return 0;
    
}



int ShiftUp(char *pBits, int iLen, int iHei)
{  
    char *pTemp;
    pTemp = malloc(iLen);
    if (pTemp==NULL) return FALSE;

    ddmemcpy(pTemp, pBits, iLen);
    ddmemcpy(pBits, pBits+iLen, (iHei-1)*iLen);
    ddmemcpy(pBits + (iHei-1)*iLen, pTemp, iLen);
    free(pTemp);
}

int ShiftDn(char *pBits, int iLen, int iHei)
{

    char *pTemp;
    int y;

    pTemp = malloc(iLen);
    if (pTemp==NULL) return FALSE;

    for (y= iHei ; y; y--)
    {
        if (y==iHei)
            ddmemcpy(pTemp,pBits + (iHei-1)*iLen,  iLen);
        else
            ddmemcpy(pBits + y*iLen, pBits + (y-1)*iLen, iLen);
    }
   
    ddmemcpy(pBits, pTemp, iLen);
    free(pTemp);
}

int ShiftLf(char *pBits, int iLen, int iHei)
{
    char bByte;
    int y;

    for (y=0; y<iHei; y++)
    {
        bByte = *(pBits + y*iLen);
        memcpy(pBits + y*iLen, pBits+1 + y*iLen, iLen-1);
        *(pBits+ iLen-1 + y*iLen) = bByte;

    }

    return TRUE;
}


int ShiftRg(char *pBits, int iLen, int iHei)
{
    char bByte;
    int y;
    char *pTemp;

    pTemp =  malloc(iLen);
    if (pTemp==NULL) return FALSE;

    for (y=0; y<iHei; y++)
    {
        bByte = *(pBits + y*iLen + iLen-1);
        ddmemcpy(pTemp, pBits+ y*iLen, iLen);
        memcpy(pBits+1+ y*iLen, pTemp, iLen-1);
        *(pBits+ y*iLen) = bByte;

    }
    free(pTemp);
    return TRUE;
}


int Rotation90(char *pBits, int iLen, int iHei)
{
    int x;
    int y;
    char *pTemp;

    pTemp = malloc (iLen *iHei);
    if (pTemp==NULL) return FALSE;
    memcpy(pTemp, pBits, iLen* iHei);

    for (y=0; y<iHei; y++)
    {
        for (x=0; x<iLen; x++)
        {
           *(pBits + iLen-1-y + x *iLen) =
               *(pTemp + y *iLen +x);
        }

    }

    free(pTemp);
    return TRUE;
}


// Floodfill is recursived...........
void MyFloodFill(BYTE *pBits,
          int iLen,
          int iHei,
          int x,
          int y,
          BYTE bOldColor,
          BYTE bNewColor)
{

    int ex=x;
    int MinX;
    int MaxX;

    for (; (x>=0) &&
           (*(pBits+(y*iLen) + x) ==bOldColor); x--)
    {
        *(pBits+(y*iLen) + x) =bNewColor;
        
    }

    MinX=x; if (MinX==-1) MinX=0;

    for (x=ex+1; (x<iLen) &&
           (*(pBits+(y*iLen) + x) ==bOldColor); x++)
    {
        *(pBits+(y*iLen) + x) =bNewColor;
        
    }

    MaxX=x; if (MaxX) MaxX--;

    // Let's hope for the best........

if (x>MinX)
    for (x=ex; (x>MinX) ; x--)
    {
        
        if ((y-1)>=0)
        {
            if (*(pBits+(y-1)*iLen + x) == bOldColor)
               MyFloodFill(pBits, iLen, iHei, x, y-1,
                          bOldColor,bNewColor);
        }

        if ((y+1)<=(iHei-1))
        {
            if (*(pBits+(y+1)*iLen + x) == bOldColor)
               MyFloodFill(pBits, iLen, iHei, x, y+1,
                            bOldColor,bNewColor);
        }


    }

if (x<MaxX)    
    for (x=ex; (x<MaxX) ; x++)
    {
        
        if ((y-1)>=0)
        {
            if (*(pBits+(y-1)*iLen + x) == bOldColor)
               MyFloodFill(pBits, iLen, iHei, x, y-1,
                        bOldColor,bNewColor);
        }

        if ((y+1)<=(iHei-1))
        {
            if (*(pBits+(y+1)*iLen + x) == bOldColor)
               MyFloodFill(pBits, iLen, iHei, x, y+1,
                        bOldColor,bNewColor);
        }


    }


}

int Flood( int iDx , 
            int iDy , 
            BYTE bOldColor,
            BYTE bNewColor, 
            USER_OBL3 *psObl3,
            USER_OBL3HEADER sHeader,
            int iMx,
            int iMy,
            HWND hPreview, 
            HWND hwnd)
{

          MyFloodFill(psObl3->PtrBits,
            (short) sHeader.iLen * OBL3FNT,
            (short) sHeader.iHei * OBL3FNT,
            iDx+iMx,
            iDy+iMy,
            bOldColor,
            bNewColor);

        InvalidateRect(
            hAppWnd,	
            NULL,	
            FALSE);

        InvalidateRect(hPreview, NULL, FALSE);
        return 0;
}


void MouseFlood(HWND hwnd,
               WPARAM wParam,
               LPARAM lParam,
               BOOL *pHasChanged,
               char *Filename,
               HWND hPreview,
               USER_OBL3HEADER sHeader,
               USER_OBL3 *psObl3)
{
      static MOUSE mouse = {(DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1, 
                            (DWORD) -1,
                            (BYTE)  -1};

      BYTE bTheColor;
      BYTE bOldColor;

      if (wParam & MK_LBUTTON || 
                   wParam & MK_RBUTTON)
      {

            if ((LOWORD (lParam)<GRILD_X) ||
                 (HIWORD (lParam)<GRILD_Y))
            return;

            mouse.x = (LOWORD (lParam) - GRILD_X) /GRILD_SQR;
            mouse.y = (HIWORD (lParam) - GRILD_Y)/GRILD_SQR;		

     	    mouse.button = wParam;

            switch (mouse.button)
            {
            case MK_LBUTTON:
                bTheColor = (BYTE) PenColor;
            break;

            case MK_RBUTTON:
                bTheColor = (BYTE) 0;
            break;

            default:
                bTheColor = (BYTE) -1;
            break;

            }

            if ((mouse.x >= (DWORD) GRILD_LEN *GRILD_FSQR) ||
                (mouse.y >= (DWORD) GRILD_HEI *GRILD_FSQR) ||
                (mouse.x+iMx >= sHeader.iLen*OBL3FNT) ||
                (mouse.y+iMy >= sHeader.iHei*OBL3FNT))
            return;
                     
            bOldColor = *(psObl3->PtrBits + 
                          iMx + mouse.x + 
                          ((iMy +mouse.y)*
                             (sHeader.iLen*OBL3FNT))
                            );

            if (bTheColor==bOldColor) return;

		    if (mouse.button==MK_LBUTTON)
            {
                if (*pHasChanged == FALSE)
                {
                      *pHasChanged=TRUE;
                          DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);
                  }
                    psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);


                   Flood(mouse.x , 
                       mouse.y , 
                       bOldColor,
                       PenColor, 
                       psObl3,
                       sHeader,
                       iMx,
                       iMy,
                       hPreview,
                       hwnd);
              }

	    	  if (mouse.button==MK_RBUTTON)
              {
                    if (*pHasChanged == FALSE)
                    {
                         *pHasChanged=TRUE;
                         DoCaption(hwnd, 
                             AppTitle, 
                             Filename, 
                             TRUE);

                     }

                    psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);


                     Flood(mouse.x , 
                          mouse.y , 
                          bOldColor,
                          0, 
                          psObl3,
                          sHeader,
                          iMx,
                          iMy,
                          hPreview, 
                          hwnd);
                }



      }
}


                 
                   
int LineTab(int X1,
            int X2, 
            int Y1, 
            int Y2, 
            BYTE color,
            USER_DOT **ppDots)
{
 int Ydiff;
 int Xdiff;          
                     
 int Yunit, Xunit;   
 int Erreur;         
                     
 int Longeur;      
 int i;            

 int XX;
 int YY;

 USER_DOT *pDots;


      XX = X1;
      YY = Y1;

      Ydiff = Y2 - Y1;
      if (Ydiff < 0)  
      {   
         Ydiff = -Ydiff;
         Yunit = -1;
      }   
      else
      {
         Yunit = 1;
      }

      Xdiff = X2 - X1;    
    
      if (Xdiff < 0) 
         
      {
         Xdiff = -Xdiff;
         Xunit = -1;
      }
         
      else
      {                
         Xunit = 1;
      }  

      Erreur = 0;     

      if (Xdiff > Ydiff)  
      {                   
          
          Longeur = Xdiff + 1;
          *ppDots = malloc(sizeof(USER_DOT)*(Longeur+2));
          pDots = *ppDots;

          for (i=0; i<=Longeur; i++)
          {
         
              pDots->x = XX;
              pDots->y = YY;
              pDots++;
              XX = XX + Xunit;
              Erreur = Erreur + Ydiff;    
              if (Erreur > Xdiff) 
                 
              {
                 Erreur = Erreur - Xdiff; 
                 YY = YY + Yunit;
              }
                
          }    
      }   
       else 
      {

          Longeur = Ydiff + 1; 
          *ppDots = malloc(sizeof(USER_DOT)*(Longeur+2));
          pDots = *ppDots;

          for (i=0; i<=Longeur; i++)
          {
              pDots->x = XX;
              pDots->y = YY;
              pDots++;
              YY = YY + Yunit;
                                          
              Erreur = Erreur + Xdiff;    
              if (Erreur > 0)     
              {
                 
                 Erreur = Erreur - Ydiff; 
                 XX = XX + Xunit;
                 
              }
              
          }
          
      }
      return Longeur;
}
                   

 


void DrawDots(USER_OBL3 *pObl3,
              USER_OBL3HEADER sHeader,
              USER_DOT *pDots,
              int NbDots,
              int iPenSize,
              int iMx,
              int iMy,
              BYTE bColor,
              HWND hPreview)
{
        int cpt;

        for (cpt=0; cpt<NbDots; cpt++)
        {
            Draw2 ( ((pDots+cpt)->x) - iMx,
                   ((pDots+cpt)->y) - iMy,
                   bColor,
                   pObl3,
                   sHeader.iLen*OBL3FNT,
                   iMx,
                   iMy,
                   hPreview,
                   iPenSize);
        }

    InvalidateRect(
        hAppWnd,	
        NULL,	
        FALSE);

     InvalidateRect(hPreview, NULL, FALSE);

}
        

void MouseLineDrag(
               HWND hwnd,
               WPARAM wParam,
               LPARAM lParam,
               int *pHasChanged,
               USER_OBL3HEADER sHeader,
               USER_OBL3 *psObl3,
               int iMx,
               int iMy,
               char *Filename,
               BOOL *pHasMouseZoned, 
               HWND hPreview,
               int iPenSize,
               BOOL *pDrag,
               USER_DOT **ppDots,
               int *pNbDots,
               char *pBackBits,
               BOOL bClear

                   )

{
      static MOUSE mouse = {(DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1, 
                            (DWORD) -1,
                            (BYTE)  -1};
      BYTE bTheColor;
      USER_DOT pFirstDot;

      if (wParam & MK_LBUTTON || 
                   wParam & MK_RBUTTON)
      {

            if ((LOWORD (lParam)<GRILD_X) ||
                 (HIWORD (lParam)<GRILD_Y))
            return;


            *pDrag = TRUE;

            mouse.x = (LOWORD (lParam) - GRILD_X) /GRILD_SQR;
            mouse.y = (HIWORD (lParam) - GRILD_Y)/GRILD_SQR;		

		    mouse.button = wParam;

            switch (mouse.button)
            {
            case MK_LBUTTON:
                bTheColor = (BYTE) PenColor;
            break;

            case MK_RBUTTON:
                bTheColor = (BYTE) 0;
            break;

            default:
                bTheColor = (BYTE) -1;
            break;
            }

            if( (mouse.last_x == mouse.x) &&
                (mouse.last_y == mouse.y) &&
                (bTheColor == mouse.bColor))
            return;

            mouse.bColor = bTheColor;
            mouse.last_x= mouse.x;
        	mouse.last_y= mouse.y;

            if ((mouse.x >= (DWORD) GRILD_LEN *GRILD_FSQR) ||
                (mouse.y >= (DWORD) GRILD_HEI *GRILD_FSQR) ||
                (mouse.x+iMx >= sHeader.iLen*OBL3FNT) ||
                (mouse.y+iMy >= sHeader.iHei*OBL3FNT))
            return;

            if (bTheColor!=-1)
            {

               if (bClear)
               {

                   if (pBackBits!=NULL)
                      ddmemcpy( (void*)psObl3->PtrBits, 
                          (void*)pBackBits,
                          sHeader.iLen*OBL3FNT *
                          sHeader.iHei*OBL3FNT);                        

                   if (*ppDots)
                     DrawDots(
                       psObl3,
                       sHeader,
                       *ppDots,
                       *pNbDots,
                       iPenSize,
                       iMx,
                       iMy,
                       0xff, 
                       hPreview
                        );
               }

                 
                if (*ppDots!=NULL)
                {
                    pFirstDot = **ppDots;
                    free(*ppDots);

                    *pNbDots =
                        LineTab(pFirstDot.x,
                            mouse.x+iMx,
                            pFirstDot.y,
                            mouse.y+iMy, 
                            0,
                            ppDots);


                    DrawDots(
                       psObl3,
                       sHeader,
                       *ppDots,
                       *pNbDots,
                       iPenSize,
                       iMx,
                       iMy,
                       bTheColor, 
                       hPreview
                        );
               }
               else
               {
                   *pDrag = FALSE;
               }
            }
      }                    

}                  


//
//
//

void MouseInitDrag(

               HWND hwnd,
               WPARAM wParam,
               LPARAM lParam,
               int *pHasChanged,
               USER_OBL3HEADER sHeader,
               USER_OBL3 *psObl3,
               int iMx,
               int iMy,
               char *Filename,
               BOOL *pHasMouseZoned, 
               HWND hPreview,
               int iPenSize,
               BOOL *pDrag,
               USER_DOT **ppDots,
               int *pNbDots,
               char **ppBackBits,
               int iToolId
                
               )
{
      static MOUSE mouse = {(DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1, 
                            (DWORD) -1,
                            (BYTE)  -1};

      BYTE bTheColor;
      USER_DOT pFirstDot;

      if (*pDrag==TRUE) return;

      if (wParam & MK_LBUTTON || 
                   wParam & MK_RBUTTON)
      {

            if ((LOWORD (lParam)<GRILD_X) ||
                 (HIWORD (lParam)<GRILD_Y))
            return;

            LockCursor(pHasMouseZoned, hwnd);

    
            mouse.x = (LOWORD (lParam) - GRILD_X) /GRILD_SQR;
            mouse.y = (HIWORD (lParam) - GRILD_Y)/GRILD_SQR;		

		    mouse.button = wParam;

            switch (mouse.button)
            {
            case MK_LBUTTON:
                bTheColor = (BYTE) PenColor;
            break;

            case MK_RBUTTON:
                bTheColor = (BYTE) 0;
            break;

            default:
                bTheColor = (BYTE) -1;
            break;
            }

            if( (mouse.last_x == mouse.x) &&
                (mouse.last_y == mouse.y) &&
                (bTheColor == mouse.bColor))
            return;

            mouse.bColor = bTheColor;
            mouse.last_x= mouse.x;
        	mouse.last_y= mouse.y;

            if ((mouse.x >= (DWORD) GRILD_LEN *GRILD_FSQR) ||
                (mouse.y >= (DWORD) GRILD_HEI *GRILD_FSQR) ||
                (mouse.x+iMx >= sHeader.iLen*OBL3FNT) ||
                (mouse.y+iMy >= sHeader.iHei*OBL3FNT))
            return;

            if (bTheColor!=-1)
            {

                *pDrag = TRUE;

                psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);


                  ImageChanged(pHasChanged, 
                               hwnd,
                               Filename) ;

                pFirstDot.x = (mouse.x+iMx);
                pFirstDot.y = (mouse.y+iMy);

               *pNbDots =1;
               *ppDots = malloc(sizeof(USER_DOT));
               **ppDots = pFirstDot;

               if (iToolId!=IDM_CIRCLE)               
                    DrawDots(
                       psObl3,
                       sHeader,
                       *ppDots,
                       *pNbDots,
                       iPenSize,
                       iMx,
                       iMy,
                       bTheColor, 
                       hPreview
                        );

                    *ppBackBits = malloc(
                        sHeader.iLen * OBL3FNT *
                        sHeader.iHei * OBL3FNT);
                    ddmemcpy(*ppBackBits,psObl3->PtrBits,
                        sHeader.iLen * OBL3FNT *
                        sHeader.iHei * OBL3FNT);


            }
      }                    
}



void Draw2(DWORD x, 
          DWORD y, 
          BYTE bColor, 
          USER_OBL3 *psObl3 ,
          int iLen,
          int iMx,
          int iMy,
          HWND hPreview,
          int iPenSize)
{


    int xx;
    int yy;
    static RECT sRect;

    char *pOblBits = psObl3->PtrBits;

    for (yy=0;(yy<iPenSize) && (yy+y+iMy<(sHeader.iHei*OBL3FNT))
        && (yy+y+iMy>=0); yy++)
    {
        for (xx=0; (xx<iPenSize) 
              && (xx+x+iMx<(sHeader.iLen*OBL3FNT)) &&
              (xx+x+iMx>=0) ; xx++)
        {
            if (bColor!=0xff)
            *(pOblBits + x + iMx + xx +
                (iMy + y +yy)*iLen) = bColor;
        }
    }

}

//
//
//

int DrawCircle( double x0,
                double y0,
                double R,
                USER_OBL3 *psObl3,
                int iPenSize,
                int iMx,
                int iMy,
                BYTE bTheColor,
                HWND hPreview )
{
 
  USER_DOT sDot;
  double x, y;
  double temp;

  x = (-1) * R; 
  temp = R * R;
  //Repeat
  //Until (x >= 0.0);
  do
  {
    y = sqrt(temp - (x * x));
    sDot.x = (x0 + (x));
    sDot.y = (y0 - (y)); //4.th quadrant

    Draw2(sDot.x -iMx,
         sDot.y -iMy, 
         bTheColor, 
         psObl3, 
         sHeader.iLen * OBL3FNT,
         iMx,
         iMy,
         hPreview,
         iPenSize);

    sDot.x = (x0 - (x));
    sDot.y = (y0 - (y)); // 1.st quadrant

    Draw2(sDot.x -iMx,
         sDot.y -iMy, 
         bTheColor, 
         psObl3, 
         sHeader.iLen * OBL3FNT,
         iMx,
         iMy,
         hPreview,
         iPenSize);

    sDot.x = (x0 + (x));
    sDot.y = (y0 + (y)); // 3.rd quadrant

    Draw2(sDot.x -iMx,
         sDot.y -iMy, 
         bTheColor, 
         psObl3, 
         sHeader.iLen * OBL3FNT,
         iMx,
         iMy,
         hPreview,
         iPenSize);

    sDot.x = (x0 - (x));
    sDot.y = (y0 + (y)); // 2.nd quadrant 

    Draw2(sDot.x -iMx,
         sDot.y -iMy, 
         bTheColor, 
         psObl3, 
         sHeader.iLen * OBL3FNT,
         iMx,
         iMy,
         hPreview,
         iPenSize);

    x = x + 0.1; 
  }
  while (x <= 0);

    InvalidateRect(
        hAppWnd,	
        NULL,	
        FALSE);

     InvalidateRect(hPreview, NULL, FALSE);

  return TRUE;

}


//
//
//

void MouseCircleDrag(
               HWND hwnd,
               WPARAM wParam,
               LPARAM lParam,
               int *pHasChanged,
               USER_OBL3HEADER sHeader,
               USER_OBL3 *psObl3,
               int iMx,
               int iMy,
               char *Filename,
               BOOL *pHasMouseZoned, 
               HWND hPreview,
               int iPenSize,
               BOOL *pDrag,
               USER_DOT **ppDots,
               int *pNbDots,
               char *pBackBits,
               BOOL bClear, 
               BOOL bFirst

                   )

{
      static MOUSE mouse = {(DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1, 
                            (DWORD) -1,
                            (BYTE)  -1};
      //RECT sRect;
      BYTE bTheColor;
      USER_DOT pFirstDot;

      static USER_DOT sMidDot;
      static int iNbDotsT;
      USER_DOT *pDotsT;


      if (bFirst) iNbDotsT =0;

      if (wParam & MK_LBUTTON || 
                   wParam & MK_RBUTTON)
      {

            if ((LOWORD (lParam)<GRILD_X) ||
                 (HIWORD (lParam)<GRILD_Y))
            return;


            *pDrag = TRUE;

            mouse.x = (LOWORD (lParam) - GRILD_X) /GRILD_SQR;
            mouse.y = (HIWORD (lParam) - GRILD_Y)/GRILD_SQR;		

		    mouse.button = wParam;

            switch (mouse.button)
            {
            case MK_LBUTTON:
                bTheColor = (BYTE) PenColor;
            break;

            case MK_RBUTTON:
                bTheColor = (BYTE) 0;
            break;

            default:
                bTheColor = (BYTE) -1;
            break;
            }

            if( (mouse.last_x == mouse.x) &&
                (mouse.last_y == mouse.y) &&
                (bTheColor == mouse.bColor))
            return;

            mouse.bColor = bTheColor;
            mouse.last_x= mouse.x;
        	mouse.last_y= mouse.y;

            if ((mouse.x >= (DWORD) GRILD_LEN *GRILD_FSQR) ||
                (mouse.y >= (DWORD) GRILD_HEI *GRILD_FSQR) ||
                (mouse.x+iMx >= sHeader.iLen*OBL3FNT) ||
                (mouse.y+iMy >= sHeader.iHei*OBL3FNT))
            return;

            if (bTheColor!=-1)
            {

               if (bClear)
               {

                   if (pBackBits!=NULL)
                      ddmemcpy( (void*)psObl3->PtrBits, 
                          (void*)pBackBits,
                          sHeader.iLen*OBL3FNT *
                          sHeader.iHei*OBL3FNT);                        

                   if (*ppDots!=NULL) 
                   {

                     if (iNbDotsT)
                        DrawCircle(sMidDot.x,
                               sMidDot.y,
                               iNbDotsT/2,
                               psObl3,
                               iPenSize,
                               iMx,
                               iMy,
                               0xff,
                               hPreview);
                   }

               }

                 
                if (*ppDots!=NULL)
                {
                    pFirstDot = **ppDots;

                    iNbDotsT = LineTab(pFirstDot.x,
                            mouse.x+iMx,
                            pFirstDot.y,
                            mouse.y+iMy, 
                            0,
                            &pDotsT);

                    sMidDot = *(pDotsT+iNbDotsT/2);

                    DrawCircle(sMidDot.x,
                               sMidDot.y,
                               iNbDotsT/2,
                               psObl3,
                               iPenSize,
                               iMx,
                               iMy,
                               bTheColor,
                               hPreview);

                    free(pDotsT);

               }
               else
               {
                   *pDrag = FALSE;
                   iNbDotsT = 0;
               }
            }
      }                    

}                  



int DrawRect (  USER_OBL3 *psObl3,
                int iPenSize,
                int x1,
                int x2,
                int y1,
                int y2,                                
                int iMx,
                int iMy,
                BYTE bColor,
                HWND hPreview)
{

    int MinX;
    int MinY;
    int MaxX;
    int MaxY;

    USER_DOT *pDots;
    int iNbDots;

    MinX= min(x1,x2);
    MinY= min(y1,y2);
    MaxX = max(x1,x2);
    MaxY = max(y1,y2);

    iNbDots= 
        LineTab
           (MinX,// x1
            MaxX,// x2 
            MinY,// y1 
            MinY,// y2 
            0,
            &pDots);

    DrawDots(
             psObl3,
             sHeader,
             pDots,
             iNbDots,
             iPenSize,
             iMx,
             iMy,
             bColor, 
             hPreview);


    iNbDots= 
    LineTab(MinX,// x1
            MaxX,// x2 
            MaxY,// y1 
            MaxY,// y2 
            0,
            &pDots);


    DrawDots(
             psObl3,
             sHeader,
             pDots,
             iNbDots,
             iPenSize,
             iMx,
             iMy,
             bColor, 
             hPreview);


    iNbDots= 
    LineTab(MinX,// x1
            MinX,// x2 
            MinY,// y1 
            MaxY,// y2 
            0,
            &pDots);

    DrawDots(
             psObl3,
             sHeader,
             pDots,
             iNbDots,
             iPenSize,
             iMx,
             iMy,
             bColor, 
             hPreview);


    iNbDots= 
    LineTab(MaxX,// x1
            MaxX,// x2 
            MaxY,// y1 
            MinY,// y2 
            0,
            &pDots);


    DrawDots(
             psObl3,
             sHeader,
             pDots,
             iNbDots,
             iPenSize,
             iMx,
             iMy,
             bColor, 
             hPreview);


    return TRUE;
}




//
//
//

void MouseRectDrag(
               HWND hwnd,
               WPARAM wParam,
               LPARAM lParam,
               int *pHasChanged,
               USER_OBL3HEADER sHeader,
               USER_OBL3 *psObl3,
               int iMx,
               int iMy,
               char *Filename,
               BOOL *pHasMouseZoned, 
               HWND hPreview,
               int iPenSize,
               BOOL *pDrag,
               USER_DOT **ppDots,
               int *pNbDots,
               char *pBackBits,
               BOOL bClear, 
               BOOL bFirst

                   )

{
      static MOUSE mouse = {(DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1,
                            (DWORD) -1, 
                            (DWORD) -1,
                            (BYTE)  -1};
      //RECT sRect;
      BYTE bTheColor;

      static USER_DOT lsDot;

      if (bFirst) lsDot = **ppDots;

      if (wParam & MK_LBUTTON || 
                   wParam & MK_RBUTTON)
      {

            if ((LOWORD (lParam)<GRILD_X) ||
                 (HIWORD (lParam)<GRILD_Y))
            return;


            *pDrag = TRUE;

            mouse.x = (LOWORD (lParam) - GRILD_X) /GRILD_SQR;
            mouse.y = (HIWORD (lParam) - GRILD_Y)/GRILD_SQR;		

		    mouse.button = wParam;

            switch (mouse.button)
            {
            case MK_LBUTTON:
                bTheColor = (BYTE) PenColor;
            break;

            case MK_RBUTTON:
                bTheColor = (BYTE) 0;
            break;

            default:
                bTheColor = (BYTE) -1;
            break;
            }

            if( (mouse.last_x == mouse.x) &&
                (mouse.last_y == mouse.y) &&
                (bTheColor == mouse.bColor))
            return;

            mouse.bColor = bTheColor;
            mouse.last_x= mouse.x;
        	mouse.last_y= mouse.y;

            if ((mouse.x >= (DWORD) GRILD_LEN *GRILD_FSQR) ||
                (mouse.y >= (DWORD) GRILD_HEI *GRILD_FSQR) ||
                (mouse.x+iMx >= sHeader.iLen*OBL3FNT) ||
                (mouse.y+iMy >= sHeader.iHei*OBL3FNT))
            return;

            if (bTheColor!=-1)
            {

               if (bClear)
               {

                   if (pBackBits!=NULL)
                      ddmemcpy( (void*)psObl3->PtrBits, 
                          (void*)pBackBits,
                          sHeader.iLen*OBL3FNT *
                          sHeader.iHei*OBL3FNT);                        

                   if (*ppDots!=NULL) 
                   {

                      DrawRect (  
                             psObl3,
                            iPenSize,
                            (**ppDots).x,
                            lsDot.x,
                            (**ppDots).y,
                            lsDot.y,                                
                            iMx,
                            iMy,
                            0xff,
                            hPreview);
                   }

               }

                 
                if (*ppDots!=NULL)
                {

                    lsDot.x = mouse.x+iMx;
                    lsDot.y = mouse.y+iMy;

                      DrawRect (  
                             psObl3,
                            iPenSize,
                            (**ppDots).x,
                            lsDot.x,
                            (**ppDots).y,
                            lsDot.y,                                
                            iMx,
                            iMy,
                            bTheColor,
                            hPreview);

               }
               else
               {
                   *pDrag = FALSE;
               }
            }
      }                    

}                  


//
//
//



void DeleteCurrentImage(
                        )
{

    USER_OBL3 *pBack;
    USER_OBL3 *pNext;

    if (sHeader.iNbrImages==1)
    {
        MessageBox(hwnd, "Le fichier doit contenir au moins une image.",
                   "AVERTISSEMENT", MB_SYSTEMMODAL |
                       MB_ICONSTOP | MB_OK);
        return;
    }

    if (psObl3->PtrPrev==NULL)
    {
#ifdef DEBUG_FB

        fprintf(tfile, "Before Del 1st \n");
        fprintf(tfile, "    PtrFirst = %x\n", sHeader.PtrFirst);
        fprintf(tfile, "    psObl3   = %x\n", psObl3);
        fprintf(tfile, "    pPrev    = %x\n", psObl3->PtrPrev);
        fprintf(tfile, "    pNext    = %x\n\n", psObl3->PtrNext);
#endif

        pNext = psObl3->PtrNext; // next
        pNext->PtrPrev = NULL;   // prev
        sHeader.PtrFirst = psObl3->PtrNext;
        sHeader.iNbrImages --;
        Free1xObl3(psObl3);
        psObl3 = pNext;
        sHeader.PtrFirst = pNext;

#ifdef DEBUG_FB

        fprintf(tfile, "After Del 1st \n");
        fprintf(tfile, "    PtrFirst = %x\n", sHeader.PtrFirst);
        fprintf(tfile, "    psObl3   = %x\n", psObl3);
        fprintf(tfile, "    pPrev    = %x\n", psObl3->PtrPrev);
        fprintf(tfile, "    pNext    = %x\n\n", psObl3->PtrNext);

#endif
    }
    else
    {

        pBack= psObl3->PtrPrev;
        pNext = psObl3->PtrNext;
        if (pNext!=NULL) 
        {

            pBack->PtrNext = psObl3->PtrNext;
            pNext->PtrPrev = pBack;
            sHeader.iNbrImages --;
            Free1xObl3(psObl3);
            psObl3 = pNext;

        }
        else
        {

            pBack->PtrNext = NULL;
            sHeader.iNbrImages --;
            Free1xObl3(psObl3);
            psObl3 = pBack;

        }

        


    }

}




#define hPalette        hchildwnd

// ***********************************************************
// 
// Handles all the important messages comming from MS-WINDOWS to
// the Mother Windoez of MiniApps
// 
// ***********************************************************

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
    {
    HDC         hdc ;
    
	static  MOUSE mouse;
    static  char Temp[512];

    // Handles to windoz and resources ....................
    static  HWND hWndToolbar;
    static  HWND hWndTT;
    static  HWND hPreview   ;
    
	HMENU   hmenu;
    HMENU   hMenuTrackPopup;

	// Tooltips vars .......................................
    LPTOOLTIPTEXT lpToolTipText;
    static idx; 
    static int aWidths [4]; 
    RECT RectMother;

    // Propreties Sheets....................................
    static bPropInUse;

    static int cpt;
    static BOOL HasChanged = FALSE;  

    MINMAXINFO sMinMaxInfo;

    static int Status;

    static RECT rcScroll;
    static RECT rcClip;
    static RECT rcInvalid;

    static char Filename[1024];
    static char Title[1024];
    int iStatus;

    USER_OBL3 *lpOBL;
    char *lpBits;

    // Gizmo stuff...........................................
    static bHasEdit         = TRUE;
    static bHasMouseZoned   = FALSE;
    static HasPalette = 1;
    static HasPreview = 1;
    static HasZoom =1;

    static iToolId = IDM_PEN;
    static iPenSize =1;

    static bDrag = FALSE;
    static USER_DOT *pDots = NULL;
    static int iNbDots;
    static char *pBackBits;

    static BOOL bFirst = TRUE;
    static USER_DOT sLastDot = {-1,-1};

    // Undo/Redo vars..........................................
    USER_OBL3UNDO *psUndo;

    // Cursors handles..........................................
    static HCURSOR hIArrow;
    static HCURSOR hIPen;
    static HCURSOR hIFlood;
    static HCURSOR hICross;

    // Cut & Past (for now)
    static USER_NEOIMA lsPasteData;

    // Drag & drop vars............................................
    HANDLE  hFilesInfo;
    WORD    wIndex;
    char    szFileName [FILE_NAME_LENGTH];
    static POINT lspointDrop;
    int iFilesDropped;

    // Handling the .INI file.....................................
    static char szWindowsDir [1024];
    static char szCurrentDir [1024];

    switch (iMsg)
		{

        // ***** MSG WM_DROPFILES:
        case WM_DROPFILES:
            hFilesInfo = (HANDLE) wParam;

            // Retrieve the window coordinates of the mouse
            // pointer when the drop was made
            DragQueryPoint ((HANDLE) wParam, 
                             (LPPOINT) &lspointDrop);

            // Get the total number of files dropped
            iFilesDropped = DragQueryFile (hFilesInfo,
                            (UINT)-1,
                                NULL,
                                   0);

            // Retrieve each file name and add to the list box
            for (wIndex=0; wIndex < iFilesDropped; wIndex++)
            {
                DragQueryFile (hFilesInfo,
                               wIndex,
                               (LPSTR) szFileName,
                               FILE_NAME_LENGTH);

          /*      SendMessage (hListBox,
                             LB_ADDSTRING,
                             0,
                             (LONG) (LPSTR) szFileName);*/
            } // for 

            DragFinish (hFilesInfo);
        break;


        case WM_KEYUP:
            InvalidateRect(hwnd, NULL, FALSE);
             break;

        case WM_KEYDOWN:

            // Next
            if (wParam==0x4e)
            {

                if (psObl3->PtrNext!=NULL)
                {
                    GotoNext(&sHeader, &psObl3);
                }
                else
                {
    			    if (MessageBox(hwnd, 
                        "Est-vous sur?", 
                        "Ajouter une image!", 
        			    MB_SYSTEMMODAL |MB_ICONQUESTION | MB_YESNO)==IDYES) 
                    {
                    GotoNext(&sHeader, &psObl3);                
                    }
            
    
                }

                InvalidateRect(hwnd, NULL, FALSE);
                InvalidateRect(hPreview, NULL, FALSE);

                StatusMessageOneOf(sHeader,
                              hWndStatus);
                

            }

            // Back
            if (wParam==0x42)
            {
                _ReleaseDrag;

                if (psObl3->PtrPrev!=NULL)
                    GotoBack(&sHeader, &psObl3);
                InvalidateRect(hwnd, NULL, FALSE);
                InvalidateRect(hPreview, NULL, FALSE);

                StatusMessageOneOf(sHeader,
                              hWndStatus);

            }

            break;

        case WM_GETMINMAXINFO:
            memcpy(&sMinMaxInfo, (void *)lParam, sizeof(MINMAXINFO));

            sMinMaxInfo.ptMinTrackSize.x = 420;  // 
            sMinMaxInfo.ptMinTrackSize.y = 420;  // 
   
            memcpy((void *)lParam, &sMinMaxInfo, sizeof(MINMAXINFO));

        return 0; // WM_GETMINMAXINFO ************************

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
            _ReleaseDrag;
        break;

		case WM_MOUSEMOVE:

            mouse.x = (LOWORD (lParam) - GRILD_X) /GRILD_SQR;
            mouse.y = (HIWORD (lParam) - GRILD_Y) /GRILD_SQR;		

            if ((mouse.x+iMx>= (sHeader.iLen*OBL3FNT)) ||
                (mouse.y+iMy>= (sHeader.iHei*OBL3FNT)) ||
                (bHasEdit==FALSE)
                )
            {
                    SetCursor(LoadCursor(NULL, IDC_NO));                               
                    return 0;
            }      

            else
            {
                switch (iToolId)
                {
                case IDM_PEN:
                    SetCursor(hIPen);
                break;

                case IDM_FLOOD:
                    SetCursor(hIFlood);
                break;

                case IDM_RECT:
                case IDM_CIRCLE:
                case IDM_LINESARC:
                case IDM_LINES:
                    SetCursor(hICross);
                break;

                default:
                    SetCursor(hIArrow);
                break;
                }
            }

            switch(wParam)
            {

                case MK_LBUTTON:
                case MK_RBUTTON:
                break;

                default:
                   _ReleaseDrag;

                    return 0;
                break;
            }

            if (bDrag) // Drag Mode
            
                switch (iToolId)
                { //a

                case IDM_LINES:
                    MouseLineDrag(
                        hwnd,
                        wParam,
                        lParam,
                        &HasChanged,
                        sHeader,
                        psObl3,
                        iMx,
                        iMy,
                        Filename,
                        &bHasMouseZoned,
                        hPreview,
                        iPenSize,
                        &bDrag,
                        &pDots,
                        &iNbDots,
                        pBackBits,
                        TRUE);
                    break;

                case IDM_LINESARC:
                    MouseLineDrag(
                        hwnd,
                        wParam,
                        lParam,
                        &HasChanged,
                        sHeader,
                        psObl3,
                        iMx,
                        iMy,
                        Filename,
                        &bHasMouseZoned,
                        hPreview,
                        iPenSize,
                        &bDrag,
                        &pDots,
                        &iNbDots,
                        pBackBits,
                        FALSE);
                    break;


                case IDM_CIRCLE:
                    MouseCircleDrag(
                        hwnd,
                        wParam,
                        lParam,
                        &HasChanged,
                        sHeader,
                        psObl3,
                        iMx,
                        iMy,
                        Filename,
                        &bHasMouseZoned,
                        hPreview,
                        iPenSize,
                        &bDrag,
                        &pDots,
                        &iNbDots,
                        pBackBits,
                        TRUE,
                        bFirst);

                        bFirst = FALSE;
                    break;

                case IDM_RECT:
                    MouseRectDrag(
                        hwnd,
                        wParam,
                        lParam,
                        &HasChanged,
                        sHeader,
                        psObl3,
                        iMx,
                        iMy,
                        Filename,
                        &bHasMouseZoned,
                        hPreview,
                        iPenSize,
                        &bDrag,
                        &pDots,
                        &iNbDots,
                        pBackBits,
                        TRUE,
                        bFirst);

                        bFirst = FALSE;
                    break;

                }    // a

            else
                
                switch (iToolId)
                { // b
                case IDM_PEN:
                    MouseDraw(
                    hwnd,
                    wParam,
                    lParam,
                    &HasChanged,
                    sHeader,
                    psObl3,
                    iMx,
                    iMy,
                    Filename,
                    &bHasMouseZoned, 
                    hPreview,
                    iPenSize,
                    iMsg
                    );
                    break;

                case IDM_FLOOD:
                     MouseFlood( 
                        hwnd,
                        wParam,
                        lParam,
                        &HasChanged,
                        Filename,
                        hPreview,
                        sHeader,
                        psObl3 );
                     break;

                    } //b                         
                return 0;

        case WM_RBUTTONDOWN:
		case WM_LBUTTONDOWN:

            mouse.x = (LOWORD (lParam) - GRILD_X) /GRILD_SQR;
            mouse.y = (HIWORD (lParam) - GRILD_Y) /GRILD_SQR;		

            if ((mouse.x+iMx>= (sHeader.iLen*OBL3FNT)) ||
                (mouse.y+iMy>= (sHeader.iHei*OBL3FNT)) ||
                (bHasEdit==FALSE)
                )
            {
                    SetCursor(LoadCursor(NULL, IDC_NO));                               
                    return 0;
            }      

            switch(wParam)
            {

                case MK_LBUTTON:
                case MK_RBUTTON:
                break;

                default:
                    _ReleaseDrag;
                    return 0;
                break;
            }

            if (bDrag)
                return 0;

            if (bHasEdit)
            {
                switch (iToolId)
                {
                case IDM_PEN:
                    MouseDraw(
                    hwnd,
                    wParam,
                    lParam,
                    &HasChanged,
                    sHeader,
                    psObl3,
                    iMx,
                    iMy,
                    Filename,
                    &bHasMouseZoned, 
                    hPreview,
                    iPenSize,
                    iMsg
                    );
                    break;

                case IDM_FLOOD:
                     MouseFlood( 
                        hwnd,
                        wParam,
                        lParam,
                        &HasChanged,                
                        Filename,
                        hPreview,
                        sHeader,
                        psObl3 );
                     break;

                case IDM_RECT:
                case IDM_LINESARC:
                case IDM_LINES:
                case IDM_CIRCLE:
                    MouseInitDrag(hwnd,
                        wParam,
                        lParam,
                        &HasChanged,
                        sHeader,
                        psObl3,
                        iMx,
                        iMy,
                        Filename,
                        &bHasMouseZoned,
                        hPreview,
                        iPenSize,
                        &bDrag,
                        &pDots,
                        &iNbDots,
                        &pBackBits,
                        iToolId);                           
                    break;

                }
            }
        break; // WM_LBUTTONDOWN ******************************


	    case WM_COMMAND:
        switch (LOWORD(wParam))
	    {    

        case KEY_PLUS:
            if (PenColor<(256-16))
                PenColor++;
            break;

        case KEY_MINUS:
            if (PenColor>16)
                PenColor--;
            break;

        case KEY_UP:
            if ((iMy) && (bHasEdit))

            {
                iMy--;
                FillScRect(hwnd, &rcScroll);
                UmbaScroll(hwnd, 0,+GRILD_SQR, &rcScroll);
                _ReleaseDrag;

               if ((iMy )!= GetScrollPos (hwnd, SB_VERT))
               {    SetScrollPos (hwnd, SB_VERT, iMy, TRUE) ;
			   }


            }
        return 0;

        case KEY_DOWN:
            if ((iMy<(iMaxMy))
                 && (bHasEdit))
            {
                iMy++;
                FillScRect(hwnd, &rcScroll);
                UmbaScroll(hwnd, 0,-GRILD_SQR, &rcScroll);
                _ReleaseDrag;

               if ((iMy )!= GetScrollPos (hwnd, SB_VERT))
               {    SetScrollPos (hwnd, SB_VERT, iMy, TRUE) ;
			   }

            }
            return 0;

        case KEY_LEFT:
            if ((iMx) && (bHasEdit))
            {
                iMx--;
                FillScRect(hwnd, &rcScroll);
                UmbaScroll(hwnd, +GRILD_SQR,0, &rcScroll);
                _ReleaseDrag;

               if ((iMx )!= GetScrollPos (hwnd, SB_HORZ))
               {    SetScrollPos (hwnd, SB_HORZ, iMx, TRUE) ;
			   }

            }
            return 0;

        case KEY_RIGHT:
            if ((iMx<(iMaxMx))
                && (bHasEdit))
            {
                iMx++;
                FillScRect(hwnd, &rcScroll);
                UmbaScroll(hwnd, -GRILD_SQR,0, &rcScroll);
                _ReleaseDrag;

               if ((iMx )!= GetScrollPos (hwnd, SB_HORZ))
               {    SetScrollPos (hwnd, SB_HORZ, iMx, TRUE) ;
			   }


            }
            return 0;

        case IDM_HASPALETTE:
            hmenu = GetMenu(hwnd);
            HasPalette = XOR(HasPalette, 1);
            Menu_CheckItem(hmenu, 
                           IDM_HASPALETTE,
                           HasPalette);
            ShowWindow(hPalette, 
                      (HasPalette) ? SW_SHOW : SW_HIDE) ;
        break;

        case IDM_HASPREVIEW:
            hmenu = GetMenu(hwnd);
            HasPreview = XOR(HasPreview, 1);
            Menu_CheckItem(hmenu, 
                           IDM_HASPREVIEW,
                           HasPreview);
            ShowWindow(hPreview, 
                      (HasPreview) ? SW_SHOW : SW_HIDE) ;
        break; // IDM_HASPREVIEW ------------------------------

        case IDM_HASZOOM:
            hmenu = GetMenu(hwnd);
            HasZoom = XOR(HasZoom, 1);
            Menu_CheckItem(hmenu, 
                           IDM_HASZOOM,
                           HasZoom);        
            _ReleaseDrag;

            iMx=0;
            iMy=0;
            if (HasZoom)
            {
                GRILD_FSQR=1;
                GRILD_SQR =8;
            }
            else
            {
                GRILD_FSQR=8;
                GRILD_SQR =1 ;
            }

            InvalidateRect(hwnd,NULL,FALSE);

        break; // IDM_HASZOOM ---------------------------------

		case IDM_EXIT:
            SendMessage(hwnd, WM_CLOSE, 0,0);
		break; // IDM_EXIT ------------------------------------

			
		case IDM_ABOUT:
			  AboutDialogBox();	
		break; // IDM_ABOUT -----------------------------------

        case IDM_REDIM:
            sgOBL3=sHeader;               

            _ReleaseDrag;

	        if  (DialogBox(hAppInstance, 
        		        M2INT(IDD_IMAGESIZE), 
		                hwnd, 
             		    ImageSizeDialogProc) == IDOK)
            {

                if ((sHeader.iLen != sgOBL3.iLen) ||
                   (sHeader.iHei != sgOBL3.iHei))
                {

                    bCritical = TRUE;



                    DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);

                    HasChanged= TRUE;

                    lpOBL = sgOBL3.PtrFirst;
                    for (;lpOBL; lpOBL = lpOBL->PtrNext)
                    {
                        lpBits = 
                            ResizeImage( 
                                 lpOBL->PtrBits,
                                 sHeader.iLen * OBL3FNT,
                                 sHeader.iHei * OBL3FNT,
                                 sgOBL3.iLen * OBL3FNT,
                                 sgOBL3.iHei * OBL3FNT);
                        free(lpOBL->PtrBits);
                        lpOBL->PtrBits = lpBits;

                        if (lpOBL->PtrMap) 
                        {
                            free(lpOBL->PtrMap);
                            lpOBL->PtrMap = NULL;
                        }

                        if (lpOBL->PtrUndo!=NULL) 
                        {
                            FlushOBL3Undo(lpOBL->PtrUndo);   
                            lpOBL->PtrUndo = NULL;
                        }


                    }

                    sHeader = sgOBL3;
                    bCritical = FALSE;
                }

                sHeader = sgOBL3;
                bPropInUse= FALSE;

                SetMaxMxMy();

                InvalidateRect(hwnd, NULL, FALSE);
                InvalidateRect(hPreview, NULL, TRUE);

            }


            break; // IDM_REDIM -------------------------------

        case IDM_PROPS:       
            _ReleaseDrag; 

            SetFocus(hWndToolbar);
            if (bPropInUse==FALSE)
            {
                bPropInUse = TRUE;
                sgOBL3=sHeader;               
                CreatePropertySheet( hAppWnd, 
                        PropWin, 
                        "Propriétés");

                if ((sHeader.iLen != sgOBL3.iLen) ||
                   (sHeader.iHei != sgOBL3.iHei))
                {

                    bCritical = TRUE;

                    DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);

                    HasChanged= TRUE;

                    lpOBL = sgOBL3.PtrFirst;
                    for (;lpOBL; lpOBL = lpOBL->PtrNext)
                    {
                        lpBits = 
                            ResizeImage( 
                                 lpOBL->PtrBits,
                                 sHeader.iLen * OBL3FNT,
                                 sHeader.iHei * OBL3FNT,
                                 sgOBL3.iLen * OBL3FNT,
                                 sgOBL3.iHei * OBL3FNT);
                        free(lpOBL->PtrBits);
                        lpOBL->PtrBits = lpBits;

                        if (lpOBL->PtrMap) 
                        {
                            free(lpOBL->PtrMap);
                            lpOBL->PtrMap = NULL;
                        }

                        if (lpOBL->PtrUndo!=NULL) 
                        {
                            FlushOBL3Undo(lpOBL->PtrUndo);   
                            lpOBL->PtrUndo = NULL;
                        }


                    }



                    sHeader = sgOBL3;
                    bCritical = FALSE;
                    SetMaxMxMy();
                }

              if (memcmp(&sHeader, 
                    &sgOBL3, sizeof(USER_OBL3HEADER))!=0)
              {
                        DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);

                        HasChanged= TRUE;
               };


                sHeader = sgOBL3;
                bPropInUse= FALSE;
                InvalidateRect(hwnd, NULL, FALSE);
                InvalidateRect(hPreview, NULL, TRUE);

            }
            return 0;
        break; // IDM_PROPS -----------------------------------

        case IDM_NEW:
            _ReleaseDrag;

            if (HasChanged)
            {
         	    iStatus = WarningDialog(hAppWnd,
                       "Les modifications n'ayant pas été sauvegarder, elles seront perdues.",   
                       "Souhaitez-vous sauvegarder avant continuer ?");
                switch(iStatus)
                {
                case IDOK:// Save & New

                    iStatus = SaveOBL3File(Filename,
                         Title,
                         &sHeader,
                         hwnd);

                    if (iStatus!=TRUE)
                    {
                        bCritical = FALSE;
                        InvalidateRect(hwnd, NULL, FALSE);
                        InvalidateRect(hPreview, NULL, FALSE);
                        return 0;
                    }

                    DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          FALSE);

                    HasChanged = FALSE;
                break;

                case IDNO:// New Only
                break;

                case IDCANCEL: // Don't bother
                    bCritical = FALSE;
                    InvalidateRect(hwnd, NULL, FALSE);
                    InvalidateRect(hPreview, NULL, FALSE);
                    return 0;
                break;
                }

            }

            // Clear the images ........
            bCritical = TRUE;

            iMx =0;
            iMy =0;

            FreeOBL3(&sHeader);          
            NewOBL3(&sHeader,sHeader.iLen,sHeader.iHei);
            psObl3 = sHeader.PtrFirst;
            
            bCritical = FALSE;    

            // House keeping,........
            strcpy(Filename, "");
            
            DoCaption(hwnd, 
                       AppTitle, 
                       Filename, 
                       FALSE);

            HasChanged = FALSE;

            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, TRUE);

            // Dim the new image..........................

            StatusMessageOneOf(sHeader,
                              hWndStatus);
                
        break; // IDM_NEW -------------------------------------
        
        case IDM_OPEN:
            _ReleaseDrag;

            if (HasChanged)
            {
         	    iStatus = WarningDialog(hAppWnd,
                       "Les modifications n'ayant pas été sauvegarder, elles seront perdues.",   
                       "Souhaitez-vous sauvegarder avant continuer ?");
                switch(iStatus)
                {
                case IDOK:// Save & Load

                    bCritical = TRUE;

                    iStatus = SaveOBL3File(Filename,
                         Title,
                         &sHeader,
                         hwnd);

                    if (iStatus!=TRUE)
                    {
                        bCritical = FALSE;
                        InvalidateRect(hwnd, NULL, FALSE);
                        InvalidateRect(hPreview, NULL, TRUE);
                        return 0;
                    }

                    DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          FALSE);

                    HasChanged = FALSE;

                    SetMaxMxMy();

    
                break;

                case IDNO:// Load Only
                break;

                case IDCANCEL: // Don't bother
                    bCritical = FALSE;
                    InvalidateRect(hwnd, NULL, FALSE);
                    InvalidateRect(hPreview, NULL, TRUE);
                    return 0;
                break;

                }

             }


            bCritical = TRUE;
            iStatus = LoadOBL3File(Filename,
                          Title,
                          &sHeader,
                          &psObl3,
                          hwnd);
            bCritical = FALSE;    

             if (iStatus == TRUE)
             {
                DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          FALSE);

                HasChanged = FALSE;

                iMx =0;
                iMy =0;

                InvalidateRect(hwnd, NULL, FALSE);
                InvalidateRect(hPreview, NULL, TRUE);

             }


             else
             {
                 if (iStatus!=0)
                    InfoDialog(hwnd, 
                           "La lecture du fichier a échouée.\n\n");

                InvalidateRect(hwnd, NULL, FALSE);
                InvalidateRect(hPreview, NULL, TRUE);

             }
 
            StatusMessageOneOf(sHeader,
                              hWndStatus);
              

        break; // IDM_OPEN ------------------------------------

        case IDM_SAVE:
            _ReleaseDrag;

            iStatus = SaveOBL3File(Filename,
                         Title,
                         &sHeader,
                         hwnd);
            
            if (iStatus==TRUE)
            {
                DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          FALSE);

                HasChanged= FALSE;

            }
            else
            {
                if (iStatus!=0)
                   InfoDialog(hwnd, "La sauvegarde du fichier a échouée.");

            }

            return 0;
        break; // IDM_SAVE -----------------------------------

        case IDM_SAVEAS:
            _ReleaseDrag;

            iStatus = SaveAsOBL3File(Filename,
                         Title,
                         &sHeader,
                         hwnd);
            
            if (iStatus==TRUE)
            {
                DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          FALSE);

                HasChanged= FALSE;
     
            }
            else
            {
                if (iStatus!=0)
                   InfoDialog(hwnd, "La sauvegarde du fichier a échouée.");
            }

        break; // IDM_SAVEAS ---------------------------------

        case IDM_IMPORT:
            InfoDialog(hwnd, "IDM_IMPORT - Cette option n'est pas disponible.");
        break; // IDM_IMPORT ---------------------------------

        case IDM_EXPORT:
            InfoDialog(hwnd, "IDM_EXPORT - Cette option n'est pas disponible.");
        break; // IDM_EXPORT ---------------------------------

        case IDM_UNDO:
            psUndo = psObl3->PtrUndo;
            if (psUndo)
            {
                if (psUndo->iNbUndo>0)
                {
                    DelUndo(psUndo, psObl3->PtrBits);             
                }
            }

            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);

        break; // IDM_UNDO ------------------------------------

        case IDM_REDO:
            psUndo = psObl3->PtrUndo;
            if (psUndo)
            {
                if (psUndo->iNbRedo>0)
                {
                    DelRedo(psUndo, psObl3->PtrBits);             
                }
            }

            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);
        break; // IDM_REDO -----------------------------------

        case IDM_CUT:
        break; // IDM_CUT ------------------------------------

        case IDM_COPY:

            lsPasteData.iLen = sHeader.iLen * OBL3FNT;
            lsPasteData.iHei = sHeader.iHei * OBL3FNT;
            if (lsPasteData.pBits!=NULL)
                free(lsPasteData.pBits);

            lsPasteData.pBits = malloc( sHeader.iLen * OBL3FNT *
                                        sHeader.iHei * OBL3FNT);

            memcpy(lsPasteData.pBits, 
                   psObl3->PtrBits, 
                   sHeader.iLen * OBL3FNT *
                       sHeader.iHei * OBL3FNT);

        break; // IDM_COPY -----------------------------------

        case IDM_PASTE:
            if (( (sHeader.iLen*OBL3FNT) != ((DWORD)(lsPasteData.iLen) ) ||
                ( (sHeader.iHei*OBL3FNT) != ((DWORD) lsPasteData.iHei) )))
            {
                InfoDialog(hwnd, "Cannot paste. Source not same " \
                    "size as target.");

            }
            else
            {

                psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);

                memcpy(psObl3->PtrBits, 
                   lsPasteData.pBits, 
                   sHeader.iLen * OBL3FNT *
                       sHeader.iHei * OBL3FNT);

                 if (HasChanged == FALSE)
                 {
                    DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);
                    HasChanged = TRUE;               
                }

                InvalidateRect(hwnd, NULL, FALSE);
                InvalidateRect(hPreview, NULL, FALSE);                

            }


        break; // IDM_PASTE ----------------------------------

        case IDM_CLEAR:


                psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);

                fillmem(psObl3->PtrBits, 
                   (BYTE)0, 
                   sHeader.iLen * OBL3FNT *
                       sHeader.iHei * OBL3FNT);


                 if (HasChanged == FALSE)
                 {
                    DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);

                    HasChanged = TRUE;
               
                }

                InvalidateRect(hwnd, NULL, FALSE);
                InvalidateRect(hPreview, NULL, FALSE);                



        break; // IDM_CLEAR ----------------------------------

        case IDM_RAINBOW:
            MakeRainbow(hwnd, psObl3);
        break;


        case IDM_COPYSET:
            InfoDialog(hwnd, "IDM_COPYSET: Option non-implantée dans cette version.");
        break; 

        case IDM_PASTESET:
            InfoDialog(hwnd, "IDM_PASTESET: Option non-implantée dans cette version.");
        break;

        case IDM_INSERT:
            InfoDialog(hwnd, "IDM_INSERT: Option non-implantée dans cette version.");

        break;

        case IDM_DELETE:

            bCritical = TRUE;
			if (MessageBox(hwnd, "Cette opération est irrévocable.\n\n Est-vous sur?", "Supprimer l'image!", 
        			MB_SYSTEMMODAL |MB_ICONQUESTION | MB_YESNO)==IDYES) 
            {          
                 if (HasChanged == FALSE)
                 {
                    DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);
                    HasChanged = TRUE;               
                }
                DeleteCurrentImage();            
            }
            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);
            bCritical = FALSE;
            StatusMessageOneOf(sHeader,
                              hWndStatus);


        break; // IDM_DELETE --------------------------------

        case IDM_BACK:
            _ReleaseDrag;

            if (psObl3->PtrPrev!=NULL)
                GotoBack(&sHeader, &psObl3);
            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);

            StatusMessageOneOf(sHeader,
                              hWndStatus);
 
        break; // IDM_BACK ---------------------------------

        case IDM_NEXT:
            _ReleaseDrag;

            if (psObl3->PtrNext!=NULL)
            {
                GotoNext(&sHeader, &psObl3);
            }
            else
            {
    			if (MessageBox(hwnd, 
                    "Est-vous sur?", 
                    "Ajouter une image!", 
        			MB_SYSTEMMODAL |MB_ICONQUESTION | MB_YESNO)==IDYES) 
                {
                    GotoNext(&sHeader, &psObl3);                
                }
            
            }

            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);

            StatusMessageOneOf(sHeader,
                              hWndStatus);
 
        break; // IDM_NEXT ---------------------------------
            
        case IDM_FLIPHORZ:
            _ReleaseDrag;
           if (HasChanged==FALSE)
                {
                    DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);

                    HasChanged= TRUE;
                }

            psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);


            FlipHorz(psObl3->PtrBits, 
                     sHeader.iLen * OBL3FNT, 
                     sHeader.iHei* OBL3FNT);
            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);

        break; // IDM_FLIPHORZ: ------------------------------

        case IDM_FLIPVERT:
            _ReleaseDrag;
            if (HasChanged==FALSE)
                {
                    DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);

                    HasChanged= TRUE;
                }

            psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);

            FlipVert(psObl3->PtrBits, 
                     sHeader.iLen * OBL3FNT, 
                     sHeader.iHei* OBL3FNT);
            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);
        break;  // IDM_FLIPVERT ------------------------------

        case IDM_ROTATION90:
            _ReleaseDrag;

            if (sHeader.iLen ==
                sHeader.iHei)
            {
                if (HasChanged==FALSE)
                {
                    DoCaption(hwnd, 
                          AppTitle, 
                          Filename, 
                          TRUE);

                    HasChanged= TRUE;
                }

                psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);

                Rotation90(psObl3->PtrBits, 
                     sHeader.iLen * OBL3FNT, 
                     sHeader.iHei* OBL3FNT);

                InvalidateRect(hwnd, NULL, FALSE);
                InvalidateRect(hPreview, NULL, FALSE);

            }
            else
            {
                 InfoDialog(hwnd, 
                 "Vous ne pouvez pas effectuer de rotation sur une image qui est rectangulaire.\n\nRedimensionner là.");
            }


        break;

        case IDM_INVERT:
            _ReleaseDrag;

                psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);

                Invert(psObl3->PtrBits, 
                     sHeader.iLen * OBL3FNT, 
                     sHeader.iHei* OBL3FNT);

                InvalidateRect(hwnd, NULL, FALSE);
                InvalidateRect(hPreview, NULL, FALSE);
        break;  // IDM_INVERT --------------------------------

        case IDM_BIGGER:
            _ReleaseDrag;

	        if  (DialogBox(hAppInstance, 
        		        M2INT(IDD_BIGGER), 
		                hwnd, 
             		    ImageBiggerDialogProc) == IDOK)           
            {
            }

        break; // IDM_BIGGER --------------------------------

        case IDM_EDITMODE:
            _ReleaseDrag;

            if (bHasEdit ==TRUE)
            {
                bHasEdit = FALSE;
                InvalidateRect(hwnd, NULL, FALSE);
                
                Menu_CheckItem(GetMenu(hwnd),
                               IDM_EDITMODE,
                               FALSE);
            }
            else
            {
                bHasEdit = TRUE;
                InvalidateRect(hwnd, NULL, FALSE);
    
                Menu_CheckItem(GetMenu(hwnd),
                               IDM_EDITMODE,
                               TRUE);            
            }


        break;  // IDM_EDITMODE -------------------------------

        case IDM_SHIFTUP:

            _ReleaseDrag;

            psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);

            ShiftUp(psObl3->PtrBits, 
                     sHeader.iLen * OBL3FNT, 
                     sHeader.iHei* OBL3FNT);
            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);
          
            if (HasChanged==FALSE)
            {  
                DoCaption(hwnd,AppTitle,Filename,TRUE); 
                HasChanged = TRUE;
            }
            
            break; // IDM_SHIFTUP -------------------------------

        case IDM_SHIFTDN:
            _ReleaseDrag;

            psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);

            ShiftDn(psObl3->PtrBits, 
                     sHeader.iLen * OBL3FNT, 
                     sHeader.iHei* OBL3FNT);
            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);

            if (HasChanged==FALSE)
            {  
                DoCaption(hwnd,AppTitle,Filename,TRUE); 
                HasChanged = TRUE;
            }

        break; // IDM_SHIFTDN -------------------------------

        case IDM_SHIFTLF:
            _ReleaseDrag;

            psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);

            ShiftLf(psObl3->PtrBits, 
                     sHeader.iLen * OBL3FNT, 
                     sHeader.iHei* OBL3FNT);
            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);


            if (HasChanged==FALSE)
            {  
                DoCaption(hwnd,AppTitle,Filename,TRUE); 
                HasChanged = TRUE;
            }

        break; // IDM_SHIFTLF -------------------------------

        case IDM_SHIFTRG:
            _ReleaseDrag;

            psObl3->PtrUndo = AddUndo(
                           psObl3->PtrUndo,
                           psObl3->PtrBits);

            ShiftRg(psObl3->PtrBits, 
                     sHeader.iLen * OBL3FNT, 
                     sHeader.iHei* OBL3FNT);
            InvalidateRect(hwnd, NULL, FALSE);
            InvalidateRect(hPreview, NULL, FALSE);


            if (HasChanged==FALSE)
            {  
                DoCaption(hwnd,AppTitle,Filename,TRUE); 
                HasChanged = TRUE;
            }

        break; // IDM_SHIFTRG -------------------------------


        // More tools......................................
       
        case IDM_MAP:
        case IDM_RECT:
        case IDM_PEN:
        case IDM_FLOOD:
        case IDM_LINES:
        case IDM_LINESARC:
        case IDM_CIRCLE:

            _ReleaseDrag;

            ToolBar_SetState(hWndToolbar, iToolId, TBSTATE_ENABLED); 
  
            Menu_CheckItem(GetMenu(hwnd), 
                           iToolId,
                           FALSE);           

            iToolId = LOWORD(wParam);

            ToolBar_SetState(hWndToolbar, iToolId,
                 TBSTATE_ENABLED | TBSTATE_PRESSED 
                     | TBSTATE_CHECKED); 

            Menu_CheckItem(GetMenu(hwnd), 
                           iToolId,
                           TRUE);           
            
        break;


        case IDM_W1:
        case IDM_W2:
        case IDM_W3:
        case IDM_W4:
        case IDM_W5:
        case IDM_W6:
        case IDM_W7:
        case IDM_W8:

            Menu_CheckItem(GetMenu(hwnd), 
                           IDM_W1 + iPenSize -1,
                           FALSE);           

            iPenSize =  LOWORD(wParam) - IDM_W1 +1;

            Menu_CheckItem(GetMenu(hwnd), 
                           IDM_W1 + iPenSize -1,
                           TRUE);           

        break; // IDM_Wx--------------------------------------

        default : 
        break ; // ELSE --------------------------------------  
        }
		  
        break; // WM_COMMAND ********************************

		case WM_QUERYNEWPALETTE:
            return msg_QueryNewPalette( hwnd, hpal);
        break; // WM_QUERYNEWPALETTE ************************

		case WM_ACTIVATEAPP:

            if ((wParam==FALSE) && (bHasMouseZoned))
            {
                bHasMouseZoned = FALSE;
                ClipCursor(NULL);
            }

           msg_ActivateApp( hwnd,  hpal,  wParam) ;
        break; // WM_ACTIVATEAPP ****************************

		case WM_CREATE :

            GetWindowsDirectory(szWindowsDir, 1020);
            if (*(szWindowsDir+strlen(szWindowsDir)-1)!='\\')
            {
                strcat(szWindowsDir, "\\");
            }


            GetCurrentDirectory(1020, szCurrentDir);
  
            if (strlen(sHeader.szFilename)==0)
            {
                DoCaption(hwnd, AppTitle,"", FALSE);			   			   

                NewOBL3(&sHeader,4,4);
                psObl3 = sHeader.PtrFirst;   
            }
            else
            {

                DoCaption(hwnd, AppTitle,sHeader.szFilename, FALSE);			   			   
                psObl3 = sHeader.PtrFirst;   
                strcpy(Filename, sHeader.szFilename);
                strcpy(sHeader.szFilename, "");

            }

            hAppWnd = hwnd;
            hWndStatus = CreateStatusBar(hwnd, 
                              sStatbar);
            hWndToolbar = CreateToolbar(hwnd, 
                              (TBBUTTON *) &tbButtons);
           
            srand( (unsigned)time( NULL ) );
  
            GetWindowRect(hwnd, &RectMother);
            aWidths[0]=RectMother.right- RectMother.left;
            
            // Create Color Palette..........................
            hPalette = RegisterAndCreateAppColorPal(hwnd);	
	        if (!hPalette)
 		        error("ERREUR FATALE", 
                      "Création de la palette de couleurs a échouée");
            ShowWindow (hPalette, SW_RESTORE) ;           
#ifdef DEBUG_FB
            tfile = fopen("DEBUG_FB.txt", "w");
#endif            
            GRILD_HEI = ( RectMother.right    
                             -GRILD_Y)/8 -2 ;
            GRILD_LEN = ( RectMother.bottom 
                             -10 -GRILD_X)/8;

            hPreview = CreatePreviewWindow(
                                hAppInstance,
                                 hwnd);

            ShowWindow (hPreview, SW_RESTORE) ; 
            
            // Load Cursors Resources.............................           
            hIArrow = LoadCursor(NULL, IDC_ARROW);
            hIPen   = LoadCursor(hAppInstance, M2INT(IDC_PEN));
            hIFlood = LoadCursor(hAppInstance, M2INT(IDC_FLOOD));
            hICross = LoadCursor(NULL, IDC_CROSS);

            SetMaxMxMy();

            StatusMessageOneOf(sHeader,
                              hWndStatus);
            

        return 0 ; // WM_CREATE ******************************

		case WM_CHAR :
        return 0 ;   // WM_CHAR ******************************

        //
		case WM_INITMENU:
    	  hmenu =  (HMENU) wParam;

          psUndo = psObl3->PtrUndo ;
          if (psUndo)
          {
              if (psUndo->iNbUndo>0)
                  Menu_EnableItem(hmenu, IDM_UNDO, TRUE) ;
              else
                  Menu_EnableItem(hmenu, IDM_UNDO, FALSE) ;

              if (psUndo->iNbRedo>0)
                  Menu_EnableItem(hmenu, IDM_REDO, TRUE) ;
              else
                  Menu_EnableItem(hmenu, IDM_REDO, FALSE) ;

          }
          else
          {
                  Menu_EnableItem(hmenu, IDM_UNDO, FALSE) ;
                  Menu_EnableItem(hmenu, IDM_REDO, FALSE) ;
          }

		return 0; // WM_INITMENU *****************************

        //
		case WM_MENUSELECT:
             AppMenuHelp(wParam, 
                         lParam, 
                         sMenuHelp,
                         hWndStatus);
		return 0; // WM_MENUSELECT  *************************

      case WM_SIZE:
        // Resize status bar to fit along bottom of the client area.
           MoveWindow (hWndStatus, 
                    0, 
                    HIWORD(lParam) - 10, 
                        LOWORD(lParam),
                    HIWORD(lParam), 
                    TRUE);

            // Tell the toolbar to resize itself to fill the top of the window.
            SendMessage(hWndToolbar, TB_AUTOSIZE, 0L, 0L);

            GRILD_HEI = (HIWORD(lParam) - 10-GRILD_Y)/8;
            if ((HIWORD(lParam) - 10-GRILD_Y)%8)
                GRILD_HEI ++;

            GRILD_LEN = (LOWORD(lParam) -  0-GRILD_X)/8;
            if ((LOWORD(lParam) - GRILD_X)%8)
                GRILD_LEN ++;

            SetMaxMxMy();

        break; // WM_SIZE ************************************

		  // Event occuring when the WINDOWS is in need of repainting		
		case WM_PAINT :            
            
              return PeinturerFenetre(
                      hwnd,
                      sHeader,
                      psObl3,
                      iMx,
                      iMy,
                      bCritical,
                      bHasEdit,
                      HasZoom);

		return 0L; // WM_PAINT ********************************

        case WM_CONTEXTMENU:
            return 0;
	   		// The right mouse button has been clicked.
			if ((HWND)wParam == hwnd)
			{
			    // Get the context menu from the resource file.
   				hmenu = LoadMenu(hAppInstance, M2INT(IDR_MENU2));
   				if (!hmenu)
       				break;;

   				// Get the first item in the menu for TrackPopupMenu(). 
   				hMenuTrackPopup = GetSubMenu(hmenu, 0);

   				// Draw and track the "floating" menu. 
   				TrackPopupMenu(hMenuTrackPopup, 
   					TPM_LEFTALIGN | TPM_RIGHTBUTTON,
       				LOWORD(lParam), HIWORD(lParam), 
       				0, hwnd, NULL);

			    // Destroy the menu
   				DestroyMenu(hmenu);
			}
		break; // WM_CONTEXTMENU *****************************

		case WM_TIMER:
				hdc = GetDC (hwnd) ;
                ReleaseDC (hwnd, hdc) ;	                  			   
		return 0 ; // WM_TIMER *******************************
				
        case WM_CLOSE :
              if (HasChanged) 
              {
                 Status = WarningDialog(hwnd,
                    "Les modifications n'ayant pas été sauvegarder, elles seront perdues.",   
                     "Souhaitez-vous sauvegarder avant de quitter ?");

                 switch (Status)
                 {
                 case IDOK:     // Save & Quit
                    iStatus = SaveOBL3File(Filename,
                                 Title,
                                 &sHeader,
                                hwnd);

                    if (iStatus!=TRUE)
                    {
                        InvalidateRect(hwnd, NULL, FALSE);
                        InvalidateRect(hPreview, NULL, TRUE);
      
                        return 0;
                    }
                    break;

                 case IDNO:     // Quit
                     break;

                 case IDCANCEL: // Forget it
                     return 0;
                    break;

                 }

              }
              DestroyWindow (hwnd);
			  
        return 0 ; // WM_CLOSE *******************************
	
        //
        case WM_QUERYENDSESSION :
        return 0 ; // WM_QUERYENDSESSION *********************

  	    // Event occuring when closing 
        // the main WINDOWS
        case WM_DESTROY :
#ifdef DEBUG_FB
               fclose(tfile);
#endif
               FreeOBL3(&sHeader);
               DeleteObject(hIArrow);
               DeleteObject(hICross);
               DeleteObject(hIPen);
               DeleteObject(hIFlood);
 		 	   PostQuitMessage(0);
        return 0 ; // WM_DESTROY        **********************

	    case WM_SETFOCUS :

            if (bHasMouseZoned)
            {
                bHasMouseZoned = FALSE;
                ClipCursor(NULL);
            }

        return 0 ; // WM_SETFOCUS ***************************

        
        case WM_VSCROLL :
                    switch (LOWORD (wParam))
                    {
                    case SB_LINEUP :
						 if (iMy)
						   iMy -= 1 ;
                         break ;

                    case SB_LINEDOWN :
						 if (iMy<iMaxMy)
                           iMy += 1 ;
                         break ;

                    case SB_PAGEUP :
						 if ((iMy-10)>=0)
						    iMy -= 10 ;
						 else iMy=0;
                         break ;

                    case SB_PAGEDOWN :
						 if ((iMy+10)<iMaxMy)						
                             iMy += 10;
						 else iMy=iMaxMy;
                         break ;

                    case SB_THUMBPOSITION :
                            iMy = HIWORD (wParam) ;
                         break ;

                    default :
                         return 0;
                         break ;
                    }
               
				
               if ((iMy )!= GetScrollPos (hwnd, SB_VERT))
               {    SetScrollPos (hwnd, SB_VERT, iMy, TRUE) ;
                    InvalidateRect (hwnd, NULL, FALSE) ;
			   }

        break; // WM_VSCROLL ********************************


        case WM_HSCROLL :
                    switch (LOWORD (wParam))
                    {
                    case SB_LINEUP :
						 if (iMx)
						   iMx -= 1 ;
                         break ;

                    case SB_LINEDOWN :
						 if (iMx<iMaxMx)
                           iMx += 1 ;
                         break ;

                    case SB_PAGEUP :
						 if ((iMx-10)>=0)
						    iMx -= 10 ;
						 else iMx=0;
                         break ;

                    case SB_PAGEDOWN :
						 if ((iMx+10)<iMaxMx)						
                             iMx += 10;
						 else iMx=iMaxMx;
                         break ;

                    case SB_THUMBPOSITION :
                            iMx = HIWORD (wParam) ;
                         break ;

                    default :
                         return 0;
                         break ;
                    }
               
				
               if ((iMx )!= GetScrollPos (hwnd, SB_HORZ))
               {    SetScrollPos (hwnd, SB_HORZ, iMx, TRUE) ;
                    InvalidateRect (hwnd, NULL, FALSE) ;
			   }
        break; // WM_HSCROLL ********************************

	    case WM_KILLFOCUS :

            _ReleaseDrag;           

        return 0 ; // WM_SETFOCUS ***************************

        case WM_LBUTTONDBLCLK:
            _ReleaseDrag;

            break; // WM_LBUTTONDBLCLK **********************
	  
		case WM_NOTIFY:
            switch (((LPNMHDR) lParam)->code) 
            {
                case TTN_NEEDTEXT:    
                    // Display the ToolTip text.
			        lpToolTipText = (LPTOOLTIPTEXT)lParam;

                    lpToolTipText->lpszText =
                        GetString(sToolTips,
                                  lpToolTipText->hdr.idFrom);
			        break;

                case TBN_QUERYDELETE:
                    break;

                case TBN_GETBUTTONINFO:
                    break;

                case TBN_QUERYINSERT:
                    break;

                case TBN_CUSTHELP:
                    break;

                case TBN_TOOLBARCHANGE:
                    SendMessage(hWndToolbar, TB_AUTOSIZE, 0L, 0L);
                    break;

                default:
                    return FALSE;
                    break;
            } // WM_NOTIFY **********************************

        } // EndCase 

     return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
     }
