
#ifndef _DRAW_H
#define _DRAW_H

#include "Struc98.h"

// Draw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDraw window

class CDraw : public CObject
{
// Construction
private:
  	int        MSDOS_PAL16[256];
  	USER_24bpp MSDOS_PAL24[256];
  	USER_32bpp MSDOS_PAL32[256];

public:
	BOOL CreatePalette(CClientDC *dc);
	CPalette m_palette;
	HBITMAP MakeBitmap(int len, int hei, unsigned char *bits, HDC hdc);
	void PutBitmap(HDC, HBITMAP, int, int);
	CDraw();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDraw)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDraw();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDraw)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif