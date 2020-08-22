// paldata.h : header file
//

#ifndef _PALDATA_H
#define _PALDATA_H

#include "draw.h"
#include "ddraw.h"

#define PAL_MSDOS	 0
#define PAL_PSP		 1

/////////////////////////////////////////////////////////////////////////////
// CPalData window

class CPalData 
{
// Construction
public:
	USER_WINPAL * GetWinPal();
	char* GetName();
	void SetName(char *szName);
	BOOL Reload();
	BOOL Export(CFile & file, int nMode);
	BOOL Import(CFile & file);
	int GetGamma();
	static UINT GetRGBValue (COLORREF rgb, LPDIRECTDRAWSURFACE lpDDS);
	BOOL CreateRefsPal(int nBpp, LPDIRECTDRAWSURFACE lpDDS);
	void ResetPal();
	BOOL Fail(char *sz);

	BOOL CreatePalette(CClientDC *dc, LPDIRECTDRAW p_lpDD, LPDIRECTDRAWPALETTE * p_lpDDPal);
	void SetGamma(int nGammaLevel);
	void DecGamma();
	void IncGamma();
	void Forget();
	void Init();
	BYTE GammaCorrection(BYTE nColor);
	void Write (CFile & file);
	void Read(CFile & file);
	void Serialize(CArchive & ar);
	CPalData();

// Attributes
public:

// Operations
public:

// Implementation
public:
	~CPalData();

protected:
	int m_nGammaLevel;
	USER_WINPAL m_pal[256];
	char m_szName[_MAX_PATH];
};

/////////////////////////////////////////////////////////////////////////////
#endif