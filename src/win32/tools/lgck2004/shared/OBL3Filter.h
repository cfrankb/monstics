#ifndef _OBL3FILTER_H
#define _OBL3FILTER_H

#include "ss3frame.h"

// This header file contains structure declarations for many
// obselet, but still supported (read-only) Static System data formats.

#define begin_struct typedef struct {
#define end_struct(_struct) } _struct;  

#define MaxUndo 10		// don't change

// IMA_FORMAT.......................................
typedef struct
{
   char len;
   char hei;
}USER_IMAHEADER;

typedef struct
{
    char Id[4]; // IMC1
    UCHAR len;
    UCHAR hei;
    int SizeData;
} USER_IMC1HEADER;

// MCX_FORMAT........................................
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
char Palette[256][3];		// Palette Couleur
USER_MCX *PtrFirst;
} USER_MCXHEADER;


// USER_OBL3UNDO............................................
typedef struct 
{
    char *PtrUndo[MaxUndo];
    int Bidon[2];
    char *PtrRedo[MaxUndo];
    WORD iNbUndo;
    WORD iNbRedo;
} USER_OBL3UNDO;

// USER_OBL3...............................................
typedef struct 
{
    void *PtrPrev;
    void *PtrNext;  
    char *PtrBits;  // if NULL then we got a problem
    char *PtrMap;   // if NULL = no map   
    USER_OBL3UNDO *PtrUndo;
    char ExtraInfo[4];
} USER_OBL3;

// USER_OBL3HEADER..........................................
typedef struct 
{
    char Id[4];         // "OBL3"
    DWORD LastViewed;
    
    DWORD iNbrImages;
    DWORD iDefaultImage;   
    
    BYTE bClassInfo;    
    BYTE bDisplayInfo;
    BYTE bActAsInfo;
    BYTE bItemProps;

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
} USER_OBL3HEADER;

// OBL3Filter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COBL3Filter 

class COBL3Filter 
{

// Construction
public:
	int GetByteSize();
  	COBL3Filter();   

// Attributes
public:
	CSS3Frame * Current();
	CString & GetName ();
	int GetSize();

// Operations
public:
	int operator ++();
	int operator --();

	//CSS3Frame *& operator[](int);
	CSS3Frame * operator[](int) ;
	int Add (CSS3Frame *p_pFrame);
	int Extract (CString l_strFilename);
    int Extract (CString p_strFilename, CFile & file, BOOL bClose = TRUE);

	void RemoveAt(int n);
	void InsertAt(int n, CSS3Frame *pFrame);
	void SetName (CString & str);
	void SetFilename (CString & str);
	void Forget();
	void RemoveAll ();
	BOOL PackImages ();

private:
	char * Ima2Bitmap(char *ImaData, int len, int hei);

// Implementation
public:
	~COBL3Filter();
	void Serialize(CArchive& ar);   
	void Write (CFile & file);
	void Read (CFile & file);

	char m_szName[_MAX_PATH];
	char m_szFilename[_MAX_PATH];
	int m_nCurrFrame; 

private:
	CSS3Frame **m_arrFrames;
	int m_nMax;
	int m_nSize; 

	BOOL m_bPacked;
	UCHAR *m_pPackedBits;
	CSS3Frame *m_pFrameData;
};
#endif
