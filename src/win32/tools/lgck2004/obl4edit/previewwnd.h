// PreviewWnd.h : header file
//
#include "mainfrm.h"
#include "obl4editdoc.h"

/////////////////////////////////////////////////////////////////////////////
// CPreviewWnd window

class CPreviewWnd : public CWnd

{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetDocument(CObl4editDoc *pDoc);
	CPreviewWnd(CObl4editDoc *pDoc);
	BOOL Fail (char *szMsg);
	CPreviewWnd();

private:
	CObl4editDoc* m_pDoc;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPreviewWnd();

	// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CPreviewWnd)
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
