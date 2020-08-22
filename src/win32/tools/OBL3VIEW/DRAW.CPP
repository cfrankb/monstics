// Draw.cpp : implementation file
//

#include "stdafx.h"
#include "struc98.h"
#include "Draw.h"

CDraw g_Draw;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDraw

CDraw::CDraw()
{
}

CDraw::~CDraw()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDraw message handlers

void CDraw::PutBitmap(HDC hdc, 
				HBITMAP hBitmap,
				int xStart,
				int yStart)
{

	BITMAP	bm;
	HDC		hdcMem;
	POINT   ptSize, ptOrg;
    HBITMAP hOldBitmap;

	hdcMem = CreateCompatibleDC(hdc);

    hOldBitmap = (HBITMAP) SelectObject (hdcMem, hBitmap);
	SetMapMode(hdcMem, GetMapMode(hdc));

	GetObject(hBitmap, sizeof (BITMAP), (LPVOID) &bm);

	ptSize.x= bm.bmWidth;
	ptSize.y= bm.bmHeight;

	ptOrg.x= 0;
	ptOrg.y= 0;

	BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y,
		   hdcMem, ptOrg.x, ptOrg.y, SRCCOPY);

	SelectObject (hdcMem, hOldBitmap);

	DeleteDC(hdcMem);
}


HBITMAP CDraw::MakeBitmap(int len, int hei, 
                          unsigned char *bits, HDC hdc)
{

    int lplanes;
    int lbpp;

    short       *ptrIData;
    int         *ptrData32;
    USER_24bpp  *ptrData24;
    char        *ptr;
    char        *ptrABC;
    int         cpt;
    int         *ptrPal;

    unsigned char color;

    HBITMAP hbitmap=NULL;

    if ((len==0) || (hei==0))
        return NULL;

    lplanes = GetDeviceCaps(hdc, PLANES);
    lbpp = GetDeviceCaps(hdc, BITSPIXEL);
     
    switch (lbpp)
    {

        case 8:
            hbitmap =  CreateBitmap(len,hei,lplanes,lbpp, bits);
            return hbitmap;
        break;

        case 16:
            ptrIData =  (short *)malloc(len*hei*2);    
            ptr = (char *) ptrIData;

            ptrPal = &MSDOS_PAL16[0];

            cpt = len*hei/4;
            __asm
            {

                push eax
                push ebx            
                push ecx
                push edx
                push edi
                push esi
               
                mov ecx, cpt
                mov esi, bits
                mov edi, ptrIData
                mov ebx, ptrPal

again:

                xor eax,eax
                //mov al, [esi]
                mov edx, [esi]
//                              
                or edx,edx
                jne NotBlack

                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi

                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi
                
                inc esi
                inc esi
                inc esi
                inc esi
                jmp LoopNext

NotBlack:

                mov al,dl
                or al,al 
                je EqualZero                             

                sub al,16                
               
                shl eax,2        

                mov ax, [ebx+eax]
EqualZero:
                mov [edi], ax
                inc edi
                inc edi

//
                xor eax,eax
                mov al,dh
                or al,al 
                je EqualZero2

                sub al,16                
               
                shl eax,2        

                mov ax, [ebx+eax]
EqualZero2:
                mov [edi], ax
                inc edi
                inc edi



//
                sub eax,eax    
                shr edx,16
                mov al,dl
                or al,al 
                je EqualZero3

                sub al,16                
               
                shl eax,2        

                mov ax, [ebx+eax]
EqualZero3:
                mov [edi], ax
                inc edi
                inc edi

//

                sub eax,eax
                mov al,dh
                or al,al 
                je EqualZero4                             

                sub al,16                
               
                shl eax,2        

                mov ax, [ebx+eax]
EqualZero4:
                mov [edi], ax
                inc edi
                inc edi

                inc esi
                inc esi
                inc esi
                inc esi


LoopNext:
                dec ecx
                or ecx,ecx
                jne again


                pop esi
                pop edi
                pop edx
                pop ecx
                pop ebx
                pop eax
            }

            hbitmap =  CreateBitmap(len,hei,lplanes,lbpp,ptr);
            free(ptr);

            return hbitmap;
        break;

        case 24:

            ptrData24 = (USER_24bpp*) malloc(len*hei*lbpp/8);    
            ptr = (char *)ptrData24;
            for (cpt = len*hei; cpt; cpt--)
            {

                color=0;
                if ((*bits <16) && (*bits!=0)) color = 134    ;
                else color = (*bits) -16;

                ptrABC = (char *) &MSDOS_PAL24[color];
                __asm 
                {
                    push ax
                    push esi
                    push edi

                    mov edi, ptrData24
                    mov esi, ptrABC
                    mov al, [esi]
                    mov [edi],al

                    mov al, [esi+1]
                    mov [edi+1],al

                    mov al, [esi+2]
                    mov [edi+2],al

                    pop edi
                    pop esi
                    pop ax
                }

                ptrData24++;
                bits++;
             }

            hbitmap =  CreateBitmap(len,hei,lplanes,lbpp,ptr);
            free(ptr);
            return hbitmap;
        break;

       case 32:

            ptrData32 = (int*) malloc(len*hei*lbpp/8);    
            ptr = (char *) ptrData32;

            ptrPal = (int*)&MSDOS_PAL32[0];

            cpt = len*hei/4;

            __asm 
            {         
            
                push eax
                push ebx            
                push ecx
                push edx
                push edi
                push esi
               
                mov ecx, cpt
                mov esi, bits
                mov edi, ptrData32
                mov ebx, ptrPal


again32:
                mov edx, [esi]

                or edx,edx
                jne NotNULL32

             
                mov eax,edx
                mov [edi],eax
                inc edi
                inc edi
                inc edi
                inc edi
                mov [edi],eax
                inc edi
                inc edi
                inc edi
                inc edi
                mov [edi],eax
                inc edi
                inc edi
                inc edi
                inc edi
                mov [edi],eax
                inc edi
                inc edi
                inc edi
                inc edi

                inc esi
                inc esi
                inc esi
                inc esi
                
                jmp LoopNext32  



NotNULL32:

//              1st byte .......................
                xor eax,eax
                mov al,dl
                or al,al 
                je EqualZ32

                sub al,16                
               
                shl eax,2        

                mov eax, [ebx+eax]
EqualZ32:
                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi


//              2nd byte ........................
                xor eax,eax
                mov al,dh
                or al,al 
                je EqualZ32ii

                sub al,16                
               
                shl eax,2        

                mov eax, [ebx+eax]
EqualZ32ii:
                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi

//              3rd byte ........................
                shr edx,16
                xor eax,eax
                mov al,dl
                or al,al 
                je EqualZ32iii

                sub al,16                
               
                shl eax,2        

                mov eax, [ebx+eax]
EqualZ32iii:
                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi

//              4th byte ........................
                xor eax,eax
                mov al,dh
                or al,al 
                je EqualZ32iv

                sub al,16                
               
                shl eax,2        

                mov eax, [ebx+eax]
EqualZ32iv:
                mov [edi], eax
                inc edi
                inc edi
                inc edi
                inc edi

//              inc source reg. ...................

                inc esi
                inc esi
                inc esi
                inc esi


LoopNext32:
                dec ecx
                or ecx,ecx
                jne again32
             

                pop esi
                pop edi
                pop edx
                pop ecx
                pop ebx
                pop eax
            }


            hbitmap =  CreateBitmap(len,hei,lplanes,lbpp,ptr);
            free(ptr);
            return hbitmap;
        break;

    }
   

    return NULL;
}



BOOL CDraw::CreatePalette(CClientDC *dc)
{

static  USER_WINPAL MSDOS_PAL[256] = {
	0 , 0 , 0 , 0 , 0 , 42 , 0 , 42 , 
	0 , 0 , 42 , 42 , 42 , 0 , 0 , 42 , 
	0 , 42 , 42 , 21 , 0 , 42 , 42 , 42 , 
	21 , 21 , 21 , 21 , 21 , 63 , 21 , 63 , 
	21 , 21 , 63 , 63 , 63 , 21 , 21 , 63 , 
	21 , 63 , 63 , 63 , 21 , 63 , 63 , 63 , 
	0 , 0 , 0 , 5 , 5 , 5 , 8 , 8 , 
	8 , 11 , 11 , 11 , 14 , 14 , 14 , 17 , 
	17 , 17 , 20 , 20 , 20 , 24 , 24 , 24 , 
	28 , 28 , 28 , 32 , 32 , 32 , 36 , 36 , 
	36 , 40 , 40 , 40 , 45 , 45 , 45 , 50 , 
	50 , 50 , 56 , 56 , 56 , 63 , 63 , 63 , 
	0 , 0 , 63 , 16 , 0 , 63 , 31 , 0 , 
	63 , 47 , 0 , 63 , 63 , 0 , 63 , 63 , 
	0 , 47 , 63 , 0 , 31 , 63 , 0 , 16 , 
	63 , 0 , 0 , 63 , 16 , 0 , 63 , 31 , 
	0 , 63 , 47 , 0 , 63 , 63 , 0 , 47 , 
	63 , 0 , 31 , 63 , 0 , 16 , 63 , 0 , 
	0 , 63 , 0 , 0 , 63 , 16 , 0 , 63 , 
	31 , 0 , 63 , 47 , 0 , 63 , 63 , 0 , 
	47 , 63 , 0 , 31 , 63 , 0 , 16 , 63 , 
	31 , 31 , 63 , 39 , 31 , 63 , 47 , 31 , 
	63 , 55 , 31 , 63 , 63 , 31 , 63 , 63 , 
	31 , 55 , 63 , 31 , 47 , 63 , 31 , 39 , 
	63 , 31 , 31 , 63 , 39 , 31 , 63 , 47 , 
	31 , 63 , 55 , 31 , 63 , 63 , 31 , 55 , 
	63 , 31 , 47 , 63 , 31 , 39 , 63 , 31 , 
	31 , 63 , 31 , 31 , 63 , 39 , 31 , 63 , 
	47 , 31 , 63 , 55 , 31 , 63 , 63 , 31 , 
	55 , 63 , 31 , 47 , 63 , 31 , 39 , 63 , 
	45 , 45 , 63 , 49 , 45 , 63 , 54 , 45 , 
	63 , 58 , 45 , 63 , 63 , 45 , 63 , 63 , 
	45 , 58 , 63 , 45 , 54 , 63 , 45 , 49 , 
	63 , 45 , 45 , 63 , 49 , 45 , 63 , 54 , 
	45 , 63 , 58 , 45 , 63 , 63 , 45 , 58 , 
	63 , 45 , 54 , 63 , 45 , 49 , 63 , 45 , 
	45 , 63 , 45 , 45 , 63 , 49 , 45 , 63 , 
	54 , 45 , 63 , 58 , 45 , 63 , 63 , 45 , 
	58 , 63 , 45 , 54 , 63 , 45 , 49 , 63 , 
	0 , 0 , 28 , 7 , 0 , 28 , 14 , 0 , 
	28 , 21 , 0 , 28 , 28 , 0 , 28 , 28 , 
	0 , 21 , 28 , 0 , 14 , 28 , 0 , 7 , 
	28 , 0 , 0 , 28 , 7 , 0 , 28 , 14 , 
	0 , 28 , 21 , 0 , 28 , 28 , 0 , 21 , 
	28 , 0 , 14 , 28 , 0 , 7 , 28 , 0 , 
	0 , 28 , 0 , 0 , 28 , 7 , 0 , 28 , 
	14 , 0 , 28 , 21 , 0 , 28 , 28 , 0 , 
	21 , 28 , 0 , 14 , 28 , 0 , 7 , 28 , 
	14 , 14 , 28 , 17 , 14 , 28 , 21 , 14 , 
	28 , 24 , 14 , 28 , 28 , 14 , 28 , 28 , 
	14 , 24 , 28 , 14 , 21 , 28 , 14 , 17 , 
	28 , 14 , 14 , 28 , 17 , 14 , 28 , 21 , 
	14 , 28 , 24 , 14 , 28 , 28 , 14 , 24 , 
	28 , 14 , 21 , 28 , 14 , 17 , 28 , 14 , 
	14 , 28 , 14 , 14 , 28 , 17 , 14 , 28 , 
	21 , 14 , 28 , 24 , 14 , 28 , 28 , 14 , 
	24 , 28 , 14 , 21 , 28 , 14 , 17 , 28 , 
	20 , 20 , 28 , 22 , 20 , 28 , 24 , 20 , 
	28 , 26 , 20 , 28 , 28 , 20 , 28 , 28 , 
	20 , 26 , 28 , 20 , 24 , 28 , 20 , 22 , 
	28 , 20 , 20 , 28 , 22 , 20 , 28 , 24 , 
	20 , 28 , 26 , 20 , 28 , 28 , 20 , 26 , 
	28 , 20 , 24 , 28 , 20 , 22 , 28 , 20 , 
	20 , 28 , 20 , 20 , 28 , 22 , 20 , 28 , 
	24 , 20 , 28 , 26 , 20 , 28 , 28 , 20 , 
	26 , 28 , 20 , 24 , 28 , 20 , 22 , 28 , 
	0 , 0 , 16 , 4 , 0 , 16 , 8 , 0 , 
	16 , 12 , 0 , 16 , 16 , 0 , 16 , 16 , 
	0 , 12 , 16 , 0 , 8 , 16 , 0 , 4 , 
	16 , 0 , 0 , 16 , 4 , 0 , 16 , 8 , 
	0 , 16 , 12 , 0 , 16 , 16 , 0 , 12 , 
	16 , 0 , 8 , 16 , 0 , 4 , 16 , 0 , 
	0 , 16 , 0 , 0 , 16 , 4 , 0 , 16 , 
	8 , 0 , 16 , 12 , 0 , 16 , 16 , 0 , 
	12 , 16 , 0 , 8 , 16 , 0 , 4 , 16 , 
	8 , 8 , 16 , 10 , 8 , 16 , 12 , 8 , 
	16 , 14 , 8 , 16 , 16 , 8 , 16 , 16 , 
	8 , 14 , 16 , 8 , 12 , 16 , 8 , 10 , 
	16 , 8 , 8 , 16 , 10 , 8 , 16 , 12 , 
	8 , 16 , 14 , 8 , 16 , 16 , 8 , 14 , 
	16 , 8 , 12 , 16 , 8 , 10 , 16 , 8 , 
	8 , 16 , 8 , 8 , 16 , 10 , 8 , 16 , 
	12 , 8 , 16 , 14 , 8 , 16 , 16 , 8 , 
	14 , 16 , 8 , 12 , 16 , 8 , 10 , 16 , 
	11 , 11 , 16 , 12 , 11 , 16 , 13 , 11 , 
	16 , 15 , 11 , 16 , 16 , 11 , 16 , 16 , 
	11 , 15 , 16 , 11 , 13 , 16 , 11 , 12 , 
	16 , 11 , 11 , 16 , 12 , 11 , 16 , 13 , 
	11 , 16 , 15 , 11 , 16 , 16 , 11 , 15 , 
	16 , 11 , 13 , 16 , 11 , 12 , 16 , 11 , 
	11 , 16 , 11 , 11 , 16 , 12 , 11 , 16 , 
	13 , 11 , 16 , 15 , 11 , 16 , 16 , 11 , 
	15 , 16 , 11 , 13 , 16 , 11 , 12 , 16 , 
	};

    int cpt;
		
    int icolor;
    int red;
    int blue;
    int green;

	for (cpt=0; cpt<256; cpt++)
	{
               
           red= (MSDOS_PAL[cpt].red) /2;                                              
           green= (MSDOS_PAL[cpt].green) /2 ;                        
           blue= (MSDOS_PAL[cpt].blue) /2;          
                
           icolor =  (1*  blue)      
                   + (1*64*green )    
                   + (1*0x800* red)    ;
                                   
            MSDOS_PAL16[cpt] = icolor;             
            MSDOS_PAL24[cpt].red = MSDOS_PAL[cpt].red*4;
            MSDOS_PAL24[cpt].blue = MSDOS_PAL[cpt].blue*4;
            MSDOS_PAL24[cpt].green = MSDOS_PAL[cpt].green*4;

            MSDOS_PAL32[cpt].red = MSDOS_PAL[cpt].red*4;
            MSDOS_PAL32[cpt].blue = MSDOS_PAL[cpt].blue*4;
            MSDOS_PAL32[cpt].green = MSDOS_PAL[cpt].green*4;
            MSDOS_PAL32[cpt].reserved = 0;
                  
    }
    


    HDC hDC = ::GetDC(0);
    ::SetSystemPaletteUse(hDC,SYSPAL_STATIC);

    int nReserved = dc->GetDeviceCaps (NUMRESERVED);
    
    if ((dc->GetDeviceCaps (RASTERCAPS) & RC_PALETTE) == 0) 
        return FALSE;

    struct {
        LOGPALETTE lp;
        PALETTEENTRY ape[256];
    } pal;

    LOGPALETTE* pLP = (LOGPALETTE*) &pal;
    pLP->palVersion = 0x300;
    pLP->palNumEntries = 256;

    uchar j=0xf0+ (nReserved/2);
    for (int i=0 ;
         i< (256); i++, j++) 
         {

            pLP->palPalEntry[i].peRed = MSDOS_PAL[j].red*4;
            pLP->palPalEntry[i].peGreen = MSDOS_PAL[j].green*4;
            pLP->palPalEntry[i].peBlue = MSDOS_PAL[j].blue*4;
            pLP->palPalEntry[i].peFlags = PC_RESERVED;
        }

    SetSystemPaletteUse(dc->m_hDC,SYSPAL_STATIC);
    m_palette.CreatePalette (pLP);

    return TRUE;
}



