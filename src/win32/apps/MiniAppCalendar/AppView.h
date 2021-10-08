
#ifndef _APPVIEW_H
#define _APPVIEW_H
#include "AppDoc.h"

// AppView.h : interface of the CAppView class
//
/////////////////////////////////////////////////////////////////////////////

class CAppView : public CView
{

private:
	void PrintMonth(CDC *pDC, int iMonth, int iYear);
	int m_iHei;
	int m_iLen;
	void OnEditChanged(UINT nID);
	void ResizeControls();
	void GotoToday();
	int m_nTimer;
    BOOL m_bBusy;

protected: // create from serialization only
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	BOOL CanDoEdit ();
	CAppView();
	DECLARE_DYNCREATE(CAppView)

    int GetMonthSize(int iMonth, int);
	int UpdateToMonth(int iMonth, int iYear);

	virtual BOOL PreTranslateMessage(MSG* pMsg);


// Attributes
public:
	BOOL StopMidi();
	BOOL PlayMidi(char *szFilename);
    CAlarmNode * NewClock();
	void OnProperties();
	CString GetMonthName(int iMonth);

    CAppDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAppView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMoisBack();
	afx_msg void OnMoisNext();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnMoisMemo();
	afx_msg void OnUpdateMoisMemo(CCmdUI* pCmdUI);
	afx_msg void OnMoisClock();
	afx_msg void OnUpdateMoisClock(CCmdUI* pCmdUI);
	afx_msg void OnEditNewclock();
	afx_msg void OnUpdateEditNewclock(CCmdUI* pCmdUI);
	afx_msg void OnMoisCurrent();
	afx_msg void OnUpdateMoisCurrent(CCmdUI* pCmdUI);
	afx_msg void OnViewAlarmslist();
	afx_msg void OnUpdateViewAlarmslist(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AppView.cpp
inline CAppDoc* CAppView::GetDocument()
   { return (CAppDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
#endif
