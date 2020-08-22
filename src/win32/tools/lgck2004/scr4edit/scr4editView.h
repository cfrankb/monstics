// scr4editView.h : interface of the CScr4editView class
//
/////////////////////////////////////////////////////////////////////////////

class CScr4editView : public CView
{
protected: // create from serialization only
	void OnContextMenu(CWnd*, CPoint point);
	CScr4editView();
	DECLARE_DYNCREATE(CScr4editView)

// Attributes
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void PutDot (void *pDest, int nColor);
	void Draw8bpp (int nRows, int nCols, int ld, int ls, DWORD s, DWORD d, BYTE nTriggerKey);
	void Draw16bpp (int nRows, int nCols, int ld, int ls, DWORD s, DWORD d, BYTE nTriggerKey);
	void Draw24bpp (int nRows, int nCols, int ld, int ls, DWORD s, DWORD d, BYTE nTriggerKey);
	void Draw32bpp (int nRows, int nCols, int ld, int ls, DWORD s, DWORD d, BYTE nTriggerKey);
	BOOL FillSurface(UCHAR nColor);
	CScr4editDoc* GetDocument();

// Operations
public:
	void DrawScript (CScriptArray *pSA, int nMX, int nMY, void *pDest, int nLen, int nHei, int nPitch);
	void DrawRect (CPoint & point, CSize & size, int nLen, int nHei, UCHAR nColor, char *pDest, int nPitch);
	void OutputOBL3 (CSS3Frame * pFrame, int x, int y, int maxX, int maxY, BOOL bClear, UCHAR *pDest, int nPitch );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScr4editView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScr4editView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_nTimer;
	BOOL m_bDragDrop;

// Generated message map functions
protected:
	//{{AFX_MSG(CScr4editView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBringtofront();
	afx_msg void OnUpdateBringtofront(CCmdUI* pCmdUI);
	afx_msg void OnSendtoback();
	afx_msg void OnUpdateSendtoback(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSounds();
	afx_msg void OnUpdateSounds(CCmdUI* pCmdUI);
	afx_msg void OnPoints();
	afx_msg void OnUpdatePoints(CCmdUI* pCmdUI);
	afx_msg void OnUserdefs();
	afx_msg void OnUpdateUserdefs(CCmdUI* pCmdUI);
	afx_msg void OnEditlocal();
	afx_msg void OnUpdateEditlocal(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTagsactions();
	afx_msg void OnUpdateTagsactions(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in scr4editView.cpp
inline CScr4editDoc* CScr4editView::GetDocument()
   { return (CScr4editDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
