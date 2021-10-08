// ReptelView.h : interface of the CReptelView class
//
/////////////////////////////////////////////////////////////////////////////

class CReptelView : public CListView
{
protected: // create from serialization only
	int GetSelItemIndex();
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	CReptelView();
	DECLARE_DYNCREATE(CReptelView)

    // Handling Item manipulations
    BOOL AddItem(int p_nImage, CString p_szName, CString p_szPhone,  CString p_szAddr,  CString p_szNote);
	BOOL GetItem(int *p_pnImage, CString *p_pStrName, CString *p_pStrPhone, CString *p_pStrAddr, CString *p_pStrNote, int p_nIndex);
    BOOL SaveItem(int p_nImage, CString p_StrName, CString p_StrPhone, CString p_StrAddr, CString p_pStrNote, int p_nIndex);

// Attributes
public:
	int Get1stSelected();
	CReptelDoc * m_pDoc;
	void ArrangeListView(int p_nHow);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CReptelDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReptelView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReptelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReptelView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAffichageDetail();
	afx_msg void OnUpdateAffichageDetail(CCmdUI* pCmdUI);
	afx_msg void OnAffichageGrandesicones();
	afx_msg void OnUpdateAffichageGrandesicones(CCmdUI* pCmdUI);
	afx_msg void OnAffichageListes();
	afx_msg void OnUpdateAffichageListes(CCmdUI* pCmdUI);
	afx_msg void OnAffichagePetitesicones();
	afx_msg void OnUpdateAffichagePetitesicones(CCmdUI* pCmdUI);
	afx_msg void OnEditProps();
	afx_msg void OnUpdateEditProps(CCmdUI* pCmdUI);
	afx_msg void OnEditionInserer();
	afx_msg void OnUpdateEditionInserer(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SyncItemArray(int p_nIndex);
};

#ifndef _DEBUG  // debug version in ReptelView.cpp
inline CReptelDoc* CReptelView::GetDocument()
   { return (CReptelDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
