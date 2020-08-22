// OBL3VIEWView.h : interface of the COBL3VIEWView class
//
/////////////////////////////////////////////////////////////////////////////

class COBL3VIEWView : public CView
{
protected: // create from serialization only
	COBL3VIEWView();
	DECLARE_DYNCREATE(COBL3VIEWView)

// Attributes
public:
	COBL3VIEWDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COBL3VIEWView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COBL3VIEWView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COBL3VIEWView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OBL3VIEWView.cpp
inline COBL3VIEWDoc* COBL3VIEWView::GetDocument()
   { return (COBL3VIEWDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
