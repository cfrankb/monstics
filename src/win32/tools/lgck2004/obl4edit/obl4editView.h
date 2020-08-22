/////////////////////////////////////////////////////////////////////////////
// CObl4editView 

#include "previewwnd.h"
#include "dotarray.h"
#include <ddraw.h>

class CObl4editView : public CView
{
protected: // create from serialization only
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	CObl4editView();
	DECLARE_DYNCREATE(CObl4editView)

// Attributes
public:
	inline BOOL IsoGrildSQR(int x, int y);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL CopyCurrentImageToClipboard();
	void SetModified();
	int CreatePreviewWindow();
	void DrawTrackRect( CDot & dot1, CDot & dot2);
	void TrackRect (CDot & dot1, CDot & dot2);
	inline void DrawSqr ( int x, int y, char *s, char *d, int l, int nBpp);
	void TapestryMode();
	void RedrawGrild();
	CRect * CalcMouseRect();
	void DrawDots (UINT nColor, BOOL bBlit, BOOL bSave=FALSE);
	void CaptureMouse();
	void ReleaseTool (int nFlags, CPoint point, UCHAR nPenColor, int nTool);
	int LineTab (CDot & Dot1, CDot & Dot2, BYTE color, CDotArray & DotArray);
	void ToolsHandler (UINT nFlags, CPoint point, UCHAR nPenColor,  int n_tool, int nButton = 0);
	void DrawImageZoomed ( CSS3Frame *pFrame, char *pDest, int nCols, int nRows, int nPitch);
	void AdjustSB( int cx, int cy);
	CObl4editDoc* GetDocument();
	int DrawGrild();

	int m_nMY;
	int m_nMX;
	BOOL m_bEdit;
	BOOL m_bZoomed;
	BOOL m_bShowPreview;

	BOOL m_bLockMouse;
	BOOL m_bSelectionActive;
	BOOL m_bToolHandled;

private:
	CDotArray m_arrDots;
	CDot m_dotLast;
	CDot m_dotOrigin;
	
	HCURSOR m_hIArrow;
    HCURSOR m_hIPen;
    HCURSOR m_hIFlood;
    HCURSOR m_hICross;
    HCURSOR m_hIColorSelect;

	CSS3Frame m_frmCopy;
	CPreviewWnd m_wndPreview;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObl4editView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CObl4editView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CObl4editView)
	afx_msg void OnUpdateCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFlood(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLines(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLinesarc(CCmdUI* pCmdUI);
	afx_msg void OnMap();
	afx_msg void OnUpdatePen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMap(CCmdUI* pCmdUI);
	afx_msg void OnCircle();
	afx_msg void OnFlood();
	afx_msg void OnLines();
	afx_msg void OnLinesarc();
	afx_msg void OnPen();
	afx_msg void OnRect();
	afx_msg void OnW1();
	afx_msg void OnUpdateW1(CCmdUI* pCmdUI);
	afx_msg void OnW2();
	afx_msg void OnUpdateW2(CCmdUI* pCmdUI);
	afx_msg void OnW3();
	afx_msg void OnUpdateW3(CCmdUI* pCmdUI);
	afx_msg void OnW4();
	afx_msg void OnUpdateW4(CCmdUI* pCmdUI);
	afx_msg void OnW5();
	afx_msg void OnUpdateW5(CCmdUI* pCmdUI);
	afx_msg void OnW6();
	afx_msg void OnUpdateW6(CCmdUI* pCmdUI);
	afx_msg void OnW7();
	afx_msg void OnUpdateW7(CCmdUI* pCmdUI);
	afx_msg void OnW8();
	afx_msg void OnUpdateW8(CCmdUI* pCmdUI);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNext();
	afx_msg void OnUpdateNext(CCmdUI* pCmdUI);
	afx_msg void OnBack();
	afx_msg void OnUpdateBack(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFliphorz();
	afx_msg void OnUpdateFliphorz(CCmdUI* pCmdUI);
	afx_msg void OnFlipvert();
	afx_msg void OnUpdateFlipvert(CCmdUI* pCmdUI);
	afx_msg void OnShiftup();
	afx_msg void OnUpdateShiftup(CCmdUI* pCmdUI);
	afx_msg void OnShiftdn();
	afx_msg void OnUpdateShiftdn(CCmdUI* pCmdUI);
	afx_msg void OnShiftrg();
	afx_msg void OnUpdateShiftrg(CCmdUI* pCmdUI);
	afx_msg void OnShiftlf();
	afx_msg void OnUpdateShiftlf(CCmdUI* pCmdUI);
	afx_msg void OnClear();
	afx_msg void OnUpdateClear(CCmdUI* pCmdUI);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnUndo();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnRedo();
	afx_msg void OnUpdateRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditmode();
	afx_msg void OnUpdateEditmode(CCmdUI* pCmdUI);
	afx_msg void OnRotation90();
	afx_msg void OnUpdateRotation90(CCmdUI* pCmdUI);
	afx_msg void OnInsert();
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
	afx_msg void OnDelete();
	afx_msg void OnUpdateDelete(CCmdUI* pCmdUI);
	afx_msg void OnEditzoom();
	afx_msg void OnUpdateEditzoom(CCmdUI* pCmdUI);
	afx_msg void OnTapestry();
	afx_msg void OnUpdateTapestry(CCmdUI* pCmdUI);
	afx_msg void OnZoomzoom();
	afx_msg void OnUpdateZoomzoom(CCmdUI* pCmdUI);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnFramecounter();
	afx_msg void OnUpdateFramecounter(CCmdUI* pCmdUI);
	afx_msg void OnColorselect();
	afx_msg void OnUpdateColorselect(CCmdUI* pCmdUI);
	afx_msg void OnShowpreview();
	afx_msg void OnUpdateShowpreview(CCmdUI* pCmdUI);
	afx_msg void OnSelect();
	afx_msg void OnUpdateSelect(CCmdUI* pCmdUI);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnDuplicate();
	afx_msg void OnUpdateDuplicate(CCmdUI* pCmdUI);
	afx_msg void OnEnlarge();
	afx_msg void OnUpdateEnlarge(CCmdUI* pCmdUI);
	afx_msg void OnResize();
	afx_msg void OnUpdateResize(CCmdUI* pCmdUI);
	afx_msg void OnCopy();
	afx_msg void OnUpdateCopy(CCmdUI* pCmdUI);
	afx_msg void OnPaste();
	afx_msg void OnUpdatePaste(CCmdUI* pCmdUI);
	afx_msg void OnCut();
	afx_msg void OnUpdateCut(CCmdUI* pCmdUI);
	afx_msg void OnRainbow();
	afx_msg void OnUpdateRainbow(CCmdUI* pCmdUI);
	afx_msg void OnInvert();
	afx_msg void OnUpdateInvert(CCmdUI* pCmdUI);
	afx_msg void OnSpreadhorz();
	afx_msg void OnUpdateSpreadhorz(CCmdUI* pCmdUI);
	afx_msg void OnSpreadvert();
	afx_msg void OnUpdateSpreadvert(CCmdUI* pCmdUI);
	afx_msg void OnRainbowExclude();
	afx_msg void OnUpdateRainbowExclude(CCmdUI* pCmdUI);
	afx_msg void OnShrink();
	afx_msg void OnUpdateShrink(CCmdUI* pCmdUI);
	afx_msg void OnIsometricgrid();
	afx_msg void OnUpdateIsometricgrid(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in obl4editView.cpp
inline CObl4editDoc* CObl4editView::GetDocument()
   { return (CObl4editDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
