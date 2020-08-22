// paldata.cpp : implementation file
//

#include "stdafx.h"
#include "paldata.h"
#include "common.h"
#include "file.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_GAMMA 5

WORD		g_pal16[256];
USER_24bpp	g_pal24[256];
UINT		g_pal32[256];

int g_nBpp = 0;

static USER_WINPAL g_defaultpal[256] = {
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

/////////////////////////////////////////////////////////////////////////////
// CPalData

CPalData::CPalData()
{
	Init();
}

CPalData::~CPalData()
{
	Forget();
}

/////////////////////////////////////////////////////////////////////////////
// CPalData message handlers

void CPalData::Serialize(CArchive & ar)
{
	if (ar.IsLoading()) // loading
	{
		ar.Read(m_pal, sizeof(m_pal));
		CString str;
		ar >> CString(str);
		strcpy(m_szName, str.GetBuffer(1));
	}
	else	// saving
	{
		ar.Write(m_pal, sizeof(m_pal));
		ar << CString(m_szName);
	}
}

void CPalData::Read(CFile & file)
{
	file.Read(m_pal, sizeof(m_pal));

	CString str;
	file >> CString(str);
	strcpy(m_szName, str.GetBuffer(1));
}

void CPalData::Write (CFile & file)
{
	file.Write(m_pal, sizeof(m_pal));
	file << CString(m_szName);
}

BYTE CPalData::GammaCorrection(BYTE nColor)
{
	switch (m_nGammaLevel)
	{
		case 0:
		break;

		case 1:
			nColor = nColor *2;
		break;

		case 2:
			nColor = nColor *2 | 0x40;
		break;

		case 3:
			nColor = nColor *4;
		break;

		case 4:
			nColor = nColor *4 | 0x40;
		break;

		case 5:
			nColor = nColor *2 | 0x80;
		break;
	}
	return nColor | 1;
}

void CPalData::Init()
{
	m_nGammaLevel =0;
	g_nBpp =0;
	*m_szName=0;
}

void CPalData::Forget()
{
	m_nGammaLevel =0;	
	g_nBpp =0;
	*m_szName=0;
}

void CPalData::IncGamma()
{
	if (m_nGammaLevel==MAX_GAMMA)
    {
		m_nGammaLevel =0;
    }
	else
    {
		m_nGammaLevel ++;
    }
}

void CPalData::DecGamma()
{
	if (m_nGammaLevel==0)
    {
		m_nGammaLevel =MAX_GAMMA;
    }
	else
    {
		m_nGammaLevel --;
    }
}

void CPalData::SetGamma(int nGammaLevel)
{
	if (nGammaLevel>=0 
		&& nGammaLevel<=MAX_GAMMA)
    {
		m_nGammaLevel = nGammaLevel;
    }
	else
    {
		m_nGammaLevel = 0;
    }
}

BOOL CPalData::CreatePalette(CClientDC *dc, LPDIRECTDRAW p_lpDD, LPDIRECTDRAWPALETTE * p_lpDDPal)
{
    PALETTEENTRY ape[256];

	UCHAR i,j;
    j=0x00;
    for ( i=0x10 ; i< (0xf0); i++, j++) 
    {
		if (m_pal[j].red)
			ape[i].peRed = GammaCorrection(m_pal[j].red);
		else
			ape[i].peRed=0;

		if (m_pal[j].green)
			ape[i].peGreen = GammaCorrection(m_pal[j].green);
		else
			ape[i].peGreen=0;

		if (m_pal[j].blue)
			ape[i].peBlue = GammaCorrection(m_pal[j].blue);
		else
			ape[i].peBlue=0;

		ape[i].peFlags = PC_NOCOLLAPSE;				
	}

    if (GetSystemPaletteEntries(dc->m_hDC, 0, 0x0f, &ape[0])==0)
    {   
        return Fail("FATAL: GetSystemPaletteEntries() failed.\n");   }

    if (GetSystemPaletteEntries(dc->m_hDC, 0xf0,0xff, &ape[0xf0])==0)
    {   
        return Fail("FATAL: GetSystemPaletteEntries() failed.\n");   }

	// Free up 32 entries so Windoz will leave us alone!
	for (i=0x00; i<0x10; i++)
	{
		ape[i].peFlags = 0;
		ape[0xff-i].peFlags = 0;
	}

    if ( FAILED( p_lpDD->CreatePalette( DDPCAPS_ALLOW256 | DDPCAPS_8BIT 	,		 
                    ape,  p_lpDDPal , NULL ) ) )	{   
		return Fail(  "Couldn't create palette.\n" ); }

	g_nBpp = 8;

    return TRUE;
}

BOOL CPalData::Fail(char *sz)
{
	OutputDebugString(sz);
	return FALSE;
}

void CPalData::ResetPal()
{
	for (int i=0; i<256; i++)
	{
		m_pal[i] = g_defaultpal[i];
	}

	strcpy(m_szName, "(default)");
}

BOOL CPalData::CreateRefsPal(int nBpp, LPDIRECTDRAWSURFACE lpDDS)
{
	UINT blue;
	UINT green;
	UINT red;
	UINT icolor;

	UCHAR i,j;
    j=0x00;
    for ( i=0x10; i< (0xf0); i++, j++) 
    {
		if (m_pal[j].red)
			red = GammaCorrection(m_pal[j].red) ;
		else
			red =0;

		if (m_pal[j].green)
			green = GammaCorrection(m_pal[j].green) ;
		else
			green=0;

        if (m_pal[j].blue)
			blue = GammaCorrection(m_pal[j].blue) ;
		else
			blue=0;

		COLORREF rgb = RGB(red, green, blue);
		
		switch (nBpp)
		{
			case 16:
				g_pal16[i] = 
					(WORD) GetRGBValue (rgb, lpDDS);		    	              
			break;

			case 24:
				icolor = GetRGBValue (rgb, lpDDS);
				memcpy (&g_pal24[i], &icolor, 3);
			break;

			case 32:
				g_pal32[i] = GetRGBValue (rgb, lpDDS);
			break;
		}
	}

	// Fill-in color 0 and 255
	UINT nBlackRGB = 0;
	UINT nWhiteRGB = 0xffffffff;

	switch (nBpp)
	{
		case 16:
			g_pal16[0] =0;
			g_pal16[255] = (WORD)0xffff;
		break;

		case 24:
			memcpy (&g_pal24[0], &nBlackRGB, 3);
			memcpy (&g_pal24[255], &nWhiteRGB, 3);
		break;

		case 32:
			g_pal32[0] =0;
			g_pal32[255]= 0xffffff;
		break;
	}

	g_nBpp = nBpp;
	return TRUE;
}

UINT CPalData::GetRGBValue (COLORREF rgb, LPDIRECTDRAWSURFACE lpDDS)
{
		HDC hdc;
	    DDSURFACEDESC ddsd;
		HRESULT hres;
		UINT nColor=0;

		//  use GDI SetPixel to color match for us
		if (lpDDS->GetDC(&hdc) == DD_OK)
		{
			SetPixel(hdc, 0, 0, rgb);               // set our value
			lpDDS->ReleaseDC(hdc);
		}

		// now lock the surface so we can read back the converted color
		ddsd.dwSize = sizeof(ddsd);
		while ((hres = lpDDS->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
		;

		if (hres == DD_OK)
		{
			nColor  = *(UINT *)ddsd.lpSurface;                     // get DWORD
			lpDDS->Unlock(NULL);
		} 

		return nColor;
}

int CPalData::GetGamma()
{
	return m_nGammaLevel;
}

BOOL CPalData::Import(CFile & file)
{
	BOOL bValid= FALSE;
	
	int nLen = file.GetLength();
	char *p = (char *)malloc(nLen+1); 
	char *pBuf = p;
	file.Read(p, nLen);

	if (memcmp(p, "JASC-PAL", 8)==0) // PAL_JASC
	{
		*(p+nLen)=0;

		char szSig[] = "JASC-PAL";
		char szVer[] = "0100";

		char szTemp[MAX_STRING];
		char szArg[32];

		pBuf = ReadLine(pBuf, szTemp);
		bValid = (strcmp(szTemp, szSig)==0);
		if (bValid)
		{
			pBuf = ReadLine(pBuf, szTemp);
			bValid = (strcmp(szTemp, szVer)==0);
			if (bValid)
			{
				int nSize;
				pBuf = ReadLine(pBuf, szTemp);
				nSize = str2int(szTemp);
				bValid = (nSize>0) && (nSize<=256);
				if (bValid)
				{
					ZeroMemory(&m_pal, sizeof(m_pal));

					for (int i=0; i<nSize; i++)
					{
						pBuf = ReadLine(pBuf, szTemp);
						char *t= szTemp;
						t = GetArg(t, szArg);
						m_pal[i].red = str2int(szArg) / 4;

						t = GetArg(t, szArg);
						m_pal[i].green = str2int(szArg) / 4;

						t = GetArg(t, szArg);
						m_pal[i].blue = str2int(szArg) / 4;
					}
				}
			}
		}		
	}
	else
	{
		if (nLen == sizeof(m_pal))	 // PAL_MSDOS
		{
			memcpy(&m_pal, p, sizeof(m_pal));
			bValid = TRUE;
		}
		else
		{
		}
	}

	free(p);
	return bValid;
}

BOOL CPalData::Export(CFile & file, int nMode)
{
	if (nMode==PAL_MSDOS)
	{
		file.Write(m_pal, sizeof(m_pal));
	}
	else
	{
		char szSig[] =  "JASC-PAL\r\n";
		char szVer[] =  "0100\r\n";
		char szSize[] =  "256\r\n" ;

		file.Write(szSig, strlen(szSig));
		file.Write(szVer, strlen(szVer));
		file.Write(szSize, strlen(szSize));

		char szTemp[100];

		for (int i=0; i<256; i++)
		{
			wsprintf(szTemp, "%d %d %d\r\n",
				m_pal[i].red * 4,
				m_pal[i].green * 4,
				m_pal[i].blue * 4);

			file.Write(szTemp, strlen(szTemp));
		}
	}
	return TRUE;
}

BOOL CPalData::Reload()
{
	BOOL bStatus = FALSE;

	CFile file;
	if (stricmp(m_szName, "(default)")==0)
	{
		ResetPal();		
		bStatus = TRUE;
	}
	else
	{
		if (file.Open(m_szName, 
			CFile::modeRead | CFile::typeBinary))
		{
			bStatus = Import(file);
			file.Close();
		}
	}
	return bStatus;
}

void CPalData::SetName(char *szName)
{
	if (szName)
	{
		strcpy(m_szName, szName);
	}
}

char* CPalData::GetName()
{
	return m_szName;
}

USER_WINPAL * CPalData::GetWinPal()
{
	return &m_pal[0];
}
