// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _MAINFRAME_H
#define _MAINFRAME_H

#include "ss3frame.h"
#include "clrbox.h"
#include <ddraw.h>
#include "draw.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CSplitterWnd m_wndSplitter;
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	BOOL NewPalette();
	HBITMAP MakeBitmap(int len, int hei, unsigned char *bits, HDC hdc);
	BOOL FillSurface (LPDIRECTDRAWSURFACE lpDDS, UCHAR nColor);

	int m_nBpp;									

	BYTE m_nPenColor;
	int m_nPenSize;
	int m_nTool;

	int m_yyy[32];

	BOOL m_bIsometric;
	BOOL m_bShowTransparency;
	BOOL m_bShowFrame;
	BOOL m_bSaveSettings;

	UINT m_nOBL4FormatId;

	LPDIRECTDRAW            m_lpDD;             // DirectDraw object.
	LPDIRECTDRAWSURFACE     m_lpDDSPrimary;     // DirectDraw primary.
	LPDIRECTDRAWSURFACE     m_lpDDSBack;		// DirectDraw surface
	LPDIRECTDRAWSURFACE     m_lpDDSBack2;		// DirectDraw surface
	LPDIRECTDRAWPALETTE     m_lpDDPalette;      // DirectDraw palette.
	LPDIRECTDRAWCLIPPER     m_lpDDClipper;      // DirectDraw clipper.

	void OutputOBL3 (CSS3Frame * pFrame, int _mx, int _my, int maxX, int maxY, BOOL bClear, UCHAR *pDest = NULL, int nPitch = 0 );
	void FillSurface (UCHAR nColor, char *pDest, int nLen, int nHei, int nPitch);
	void UpdateColorBox();
	
	BOOL InitDDraw( HWND hwnd );
	BOOL RestoreAll ();
	BOOL Fail (char *szMsg);
	void ReleaseObjects();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CClrBox		m_wndColorBox;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHaspalette();
	afx_msg void OnUpdateHaspalette(CCmdUI* pCmdUI);
	afx_msg void OnSysColorChange();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPlus();
	afx_msg void OnUpdatePlus(CCmdUI* pCmdUI);
	afx_msg void OnMinus();
	afx_msg void OnUpdateMinus(CCmdUI* pCmdUI);
	afx_msg void OnSavesettings();
	afx_msg void OnUpdateSavesettings(CCmdUI* pCmdUI);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnShowtransparency();
	afx_msg void OnUpdateShowtransparency(CCmdUI* pCmdUI);
	afx_msg void OnAdjustgamma();
	afx_msg void OnUpdateAdjustgamma(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
