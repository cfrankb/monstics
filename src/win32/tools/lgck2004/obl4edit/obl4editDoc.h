#ifndef _OBL4EDITDOC_H
#define _OBL4EDITDOC_H

#include "obl3filter.h"
#include "ddraw.h"

// obl4editDoc.h : interface of the CObl4editDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CObl4editDoc : public CDocument
{
protected: // create from serialization only
	CObl4editDoc();
	DECLARE_DYNCREATE(CObl4editDoc)

// Attributes
public:
	void ResetViewPort();
	CWnd * GetView();
	BOOL AddSet(char *szFilename, int & nCurrImage);
	CSS3Frame * BitmapToOBL4(HBITMAP hbm, int nMethod);
	BOOL ImportGM (COBL3Filter & filter, CString & Filename);
	HRESULT CopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
	BOOL ImportBitmap (COBL3Filter & filter, CString & strFilename, int nMethod);
	void UpdateTitle ();
	void SetModified();
	COBL3Filter m_oblData;

private:
	void RepaintAllViews();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObl4editDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CObl4editDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CObl4editDoc)
	afx_msg void OnSplitFrameset();
	afx_msg void OnUpdateSplitFrameset(CCmdUI* pCmdUI);
	afx_msg void OnImportwindowbitmap();
	afx_msg void OnUpdateImportwindowbitmap(CCmdUI* pCmdUI);
	afx_msg void OnImportgamemaker();
	afx_msg void OnUpdateImportgamemaker(CCmdUI* pCmdUI);
	afx_msg void OnSavepalette();
	afx_msg void OnUpdateSavepalette(CCmdUI* pCmdUI);
	afx_msg void OnLoadpalette();
	afx_msg void OnUpdateLoadpalette(CCmdUI* pCmdUI);
	afx_msg void OnExportbmp();
	afx_msg void OnUpdateExportbmp(CCmdUI* pCmdUI);
	afx_msg void OnFileSendMail();
	afx_msg void OnUpdateFileSendMail(CCmdUI* pCmdUI);
	afx_msg void OnImportobl();
	afx_msg void OnUpdateImportobl(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define RESET_VIEW_ORG (WM_USER + 1)
 
#endif
