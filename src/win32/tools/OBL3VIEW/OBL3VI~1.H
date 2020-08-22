
#include "obl3filter.h"



// OBL3VIEWDoc.h : interface of the COBL3VIEWDoc class
//
/////////////////////////////////////////////////////////////////////////////

class COBL3VIEWDoc : public CDocument
{
protected: // create from serialization only
	COBL3VIEWDoc();
	DECLARE_DYNCREATE(COBL3VIEWDoc)

// Attributes
public:
	void LoadFile(CString p_strFilename);
	void CleanUp();
	COBL3Filter m_obl3Filter;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COBL3VIEWDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COBL3VIEWDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COBL3VIEWDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
