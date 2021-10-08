// mysql_buddyView.h : interface of the CMysql_buddyView class
//
/////////////////////////////////////////////////////////////////////////////

#include "afxcview.h"

class CMysql_buddyView : public CListView
{
protected: // create from serialization only
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	CMysql_buddyView();
	DECLARE_DYNCREATE(CMysql_buddyView)

// Attributes
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMysql_buddyDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysql_buddyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL DestroyWindow();
	protected:
	virtual void OnActivateView(BOOL bActivate, CListView* pActivateView, CListView* pDeactiveView);
	virtual void OnUpdate(CListView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMysql_buddyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMysql_buddyView)
	afx_msg void OnDestroy();
	afx_msg void OnMysqladminToFront();
	afx_msg void OnUpdateMysqladminToFront(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mysql_buddyView.cpp
inline CMysql_buddyDoc* CMysql_buddyView::GetDocument()
   { return (CMysql_buddyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
