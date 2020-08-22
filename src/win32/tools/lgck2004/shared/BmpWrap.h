// BmpWrap.h : header file
//

#define begin_struct typedef struct {
#define end_struct(_struct) } _struct;  

// BM was read separatly
begin_struct
	UINT m_nTotalSize;// 3a 00 00 00
	UINT m_nZero;     // 00 00 00 00 ???
	UINT m_nDiff;     // 36 00 00 00 TotalSize - ImageSize
	UINT m_n28;       // 28 00 00 00 ???

	UINT m_nLen;      // 80 00 00 00
	UINT m_nHei;      // 80 00 00 00
	WORD m_nPlanes;   // 01 00 
	WORD m_nBitCount; // 18 00
	UINT m_nCompress; // 00 00 00 00 

	UINT m_nImageSize;// c0 00 00 00 
	UINT m_nXPix;     // 00 00 00 00 X pix/m
	UINT m_nYPix;     // 00 00 00 00 Y pix/m
	UINT m_nClrUsed;  // 00 00 00 00 ClrUsed

	UINT m_nClrImpt;  // 00 00 00 00 ClrImportant
end_struct (USER_BMPHEADER);

begin_struct
	UCHAR m_uBlue;
	UCHAR m_uGreen;
	UCHAR m_uRed;
end_struct (USER_BMP_RGB)

begin_struct
	UCHAR m_uByte [3];
end_struct (USER_3BYTES);

#ifndef _BMPWRAP_H
#define _BMPWRAP_H

/////////////////////////////////////////////////////////////////////////////
// CBmpWrap

class CBmpWrap 
{
// Construction
public:
	CBmpWrap (int nLen, int nHei);
	CBmpWrap();

// Attributes
public:
	int GetHei ();
	int GetLen ();
	int GetPitch ();
	BOOL IsValid ();
	USER_3BYTES * Point (int x, int y);

// Operations
public:
	void Forget ();
	BOOL Split (CString strFilename, int nCols, int nRows);
	void FlipUpDown ();
	void Size (int nLen, int nHei);

// Implementation
public:
	 ~CBmpWrap();
	BOOL Write (CString strFilename);
	BOOL Read (CString strFilename);

protected:
	UCHAR * m_pBits;
	USER_BMPHEADER m_bmpHeader;
	int m_nLen;
	int m_nHei;
	int m_nPitch;

};

/////////////////////////////////////////////////////////////////////////////

#endif