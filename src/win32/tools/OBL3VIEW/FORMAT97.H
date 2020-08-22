
//
// Format97.h
//

// This header file contain structure declarations for many
// obselet, but still supported Static System data formats.

#ifndef _FORMAT97_H
#define _FORMAT97_H

#define begin_struct typedef struct {
#define end_struct(_struct) } _struct;  
#define uchar unsigned char
#define uint unsigned int
//#include "struc.h"
//#include "user_err.h"

#define MaxUndo 10

// IMA_FORMAT
begin_struct
   char len;
   char hei;
end_struct(USER_IMAHEADER);

begin_struct
    char Id[4]; // IMC1
    char len;
    char hei;
    int SizeData;
end_struct(USER_IMC1HEADER);

// MCX_FORMAT
typedef struct
{
void* PtrPrev;
void* PtrNext;
char  Name [30];			// Nom long de l'image 
short Class;
char ImageData[32][32];
} USER_MCX;

typedef struct 
{
char Id[4];					// "GE96"
short Class;				// 0
char Name[256];				// Nom long du fichier
int  NbrImages;				// Nombre d'images dans le fichier
int  LastViewed;            // Dernière images visualisée
char Palette[256][3];	// Palette Couleur
USER_MCX *PtrFirst;
} USER_MCXHEADER;


// USER_OBL3UNDO............................................
begin_struct
    char *PtrUndo[MaxUndo];
    int Bidon[2];
    char *PtrRedo[MaxUndo];
    WORD iNbUndo;
    WORD iNbRedo;
end_struct(USER_OBL3UNDO);

// USER_OBL3...............................................
begin_struct
    void *PtrPrev;
    void *PtrNext;  
    char *PtrBits;  // if NULL then we got a problem
    char *PtrMap;   // if NULL = no map   
    USER_OBL3UNDO *PtrUndo;
    char ExtraInfo[4];
end_struct(USER_OBL3);

// USER_OBL3HEADER..........................................
begin_struct
    char Id[4];         // "OBL3"
    DWORD LastViewed;
    
    DWORD iNbrImages;// For IDD_GENERALINFO
    DWORD iDefaultImage;   
    
    BYTE bClassInfo;    
    BYTE bDisplayInfo;
    BYTE bActAsInfo;
    BYTE bItemProps;// Solid 1,Deadly 2,KillPlayer 4,KillByLava 8
                    // KillByWater 16,Gravity 32,Jump 64,Swim 128
    WORD wU1;
    WORD wU2;
    WORD wRebirthTime;
    WORD wMaxJump;
    
    WORD wFireRate;
    WORD wLifeForce;   
    WORD wLives;
    WORD wOxygen;
    
    WORD wSpeed;
    WORD wFallSpeed;    
    WORD wAniSpeed;
    WORD wTimeOut;
    
    WORD wDomages;
    WORD wFiller;
    DWORD iLen;
    DWORD iHei;

    BYTE  bU1;
    BYTE  bU2;
    BYTE  bU3;
    BYTE  bCompilerOptions;

    USER_OBL3 *PtrFirst;
    char szFilename[256];    
    char szName[256];
    char szCopyrights[1024];
end_struct(USER_OBL3HEADER);

// USER_OBL3HEADERLITE......................................
begin_struct
    char Id[4];         // "OBL3"
    DWORD LastViewed;
    
    DWORD iNbrImages;// For IDD_GENERALINFO
    DWORD iDefaultImage;   
    
    BYTE bClassInfo;    
    BYTE bDisplayInfo;
    BYTE bActAsInfo;
    BYTE bItemProps;// Solid 1,Deadly 2,KillPlayer 4,KillByLava 8
                    // KillByWater 16,Gravity 32,Jump 64,Swim 128
    WORD wU1;
    WORD wU2;
    WORD wRebirthTime;
    WORD wMaxJump;
    
    WORD wFireRate;
    WORD wLifeForce;   
    WORD wLives;
    WORD wOxygen;
    
    WORD wSpeed;
    WORD wFallSpeed;    
    WORD wAniSpeed;
    WORD wTimeOut;
    
    WORD wDomages;
    WORD wFiller;
    DWORD iLen;
    DWORD iHei;

    BYTE  bU1;
    BYTE  bU2;
    BYTE  bU3;
    BYTE  bCompilerOptions;

    USER_OBL3 *PtrFirst;
    char szFilename[256];    
    char szName[64];
end_struct(USER_OBL3HEADERLITE);

#endif
