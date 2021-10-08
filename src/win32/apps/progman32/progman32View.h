// progman32View.h : interface of the CProgman32View class
//
/////////////////////////////////////////////////////////////////////////////

class CProgman32View : public CListView
{
protected: // create from serialization only
	CProgman32View();
	DECLARE_DYNCREATE(CProgman32View)

// Attributes
public:
	CProgman32Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgman32View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgman32View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	void SetRect(WPARAM wParam);
	void RunProgram();
	void AddNewProgram();
	int GetCurSel();
	void ProcessAction(WPARAM wParam);
	void AddItem(ICON_INFO & item);
	BOOL ManageItem(ICON_INFO & item, int i, BOOL bSelected, BOOL bInsert);
	void RestoreSelection();

    int m_nSelItem;

// Generated message map functions
protected:
	//{{AFX_MSG(CProgman32View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTest();
	afx_msg void OnUpdateTest(CCmdUI* pCmdUI);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnProperties();
	afx_msg void OnUpdateProperties(CCmdUI* pCmdUI);
	afx_msg void OnOpen();
	afx_msg void OnUpdateOpen(CCmdUI* pCmdUI);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnUpdateDelete(CCmdUI* pCmdUI);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in progman32View.cpp
inline CProgman32Doc* CProgman32View::GetDocument()
   { return (CProgman32Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
