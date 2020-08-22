// vlamits3View.h : interface of the CVlamits3View class
//
/////////////////////////////////////////////////////////////////////////////

class CVlamits3View : public CView
{
protected: // create from serialization only
	CVlamits3View();
	DECLARE_DYNCREATE(CVlamits3View)

// Attributes
public:
	CVlamits3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVlamits3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVlamits3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVlamits3View)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in vlamits3View.cpp
inline CVlamits3Doc* CVlamits3View::GetDocument()
   { return (CVlamits3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
