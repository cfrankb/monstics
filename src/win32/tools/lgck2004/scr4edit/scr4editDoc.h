#ifndef _SCR4EDITDOC_H
#define _SCR4EDITDOC_H

// scr4editDoc.h : interface of the CScr4editDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "obl3array.h"
#include "gamefile3.h"
#include <io.h>

class CScr4editDoc : public CDocument
{
protected: // create from serialization only
	CScr4editDoc();
	DECLARE_DYNCREATE(CScr4editDoc)

// Attributes
public:
	CView * GetFirstView();

// Operations
public:
	void RepaintAllViews();
	void UpdateTitle ();
	void WriteString (const char *szText, CFile & file);
	BOOL WizardAddObject (_finddata_t & data, int nClass=0);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScr4editDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScr4editDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CGameFile3 m_game3;

	CTagArray m_arrSort;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CScr4editDoc)
	afx_msg void OnInsertframes();
	afx_msg void OnUpdateInsertframes(CCmdUI* pCmdUI);
	afx_msg void OnObjectsInsertobject();
	afx_msg void OnUpdateObjectsInsertobject(CCmdUI* pCmdUI);
	afx_msg void OnClassedit();
	afx_msg void OnUpdateClassedit(CCmdUI* pCmdUI);
	afx_msg void OnProtoeditor();
	afx_msg void OnUpdateProtoeditor(CCmdUI* pCmdUI);
	afx_msg void OnInsertlevel();
	afx_msg void OnUpdateInsertlevel(CCmdUI* pCmdUI);
	afx_msg void OnInsertobject();
	afx_msg void OnUpdateInsertobject(CCmdUI* pCmdUI);
	afx_msg void OnNextlevel();
	afx_msg void OnUpdateNextlevel(CCmdUI* pCmdUI);
	afx_msg void OnPreviouslevel();
	afx_msg void OnUpdatePreviouslevel(CCmdUI* pCmdUI);
	afx_msg void OnDown();
	afx_msg void OnUpdateDown(CCmdUI* pCmdUI);
	afx_msg void OnUp();
	afx_msg void OnUpdateUp(CCmdUI* pCmdUI);
	afx_msg void OnRight();
	afx_msg void OnUpdateRight(CCmdUI* pCmdUI);
	afx_msg void OnLeft();
	afx_msg void OnUpdateLeft(CCmdUI* pCmdUI);
	afx_msg void OnDeleteobject();
	afx_msg void OnUpdateDeleteobject(CCmdUI* pCmdUI);
	afx_msg void OnDuplicateobject();
	afx_msg void OnUpdateDuplicateobject(CCmdUI* pCmdUI);
	afx_msg void OnLevelproperties();
	afx_msg void OnUpdateLevelproperties(CCmdUI* pCmdUI);
	afx_msg void OnAddnewlevel();
	afx_msg void OnUpdateAddnewlevel(CCmdUI* pCmdUI);
	afx_msg void OnInsertlevelafter();
	afx_msg void OnUpdateInsertlevelafter(CCmdUI* pCmdUI);
	afx_msg void OnDeletelevel();
	afx_msg void OnUpdateDeletelevel(CCmdUI* pCmdUI);
	afx_msg void OnRemoveall();
	afx_msg void OnUpdateRemoveall(CCmdUI* pCmdUI);
	afx_msg void OnDecbkcolor();
	afx_msg void OnUpdateDecbkcolor(CCmdUI* pCmdUI);
	afx_msg void OnIncbkcolor();
	afx_msg void OnUpdateIncbkcolor(CCmdUI* pCmdUI);
	afx_msg void OnDefaultbkcolor();
	afx_msg void OnUpdateDefaultbkcolor(CCmdUI* pCmdUI);
	afx_msg void OnInformation();
	afx_msg void OnUpdateInformation(CCmdUI* pCmdUI);
	afx_msg void OnExportDeclarations();
	afx_msg void OnUpdateExportDeclarations(CCmdUI* pCmdUI);
	afx_msg void OnExportDiagnostic();
	afx_msg void OnUpdateExportDiagnostic(CCmdUI* pCmdUI);
	afx_msg void OnPlus();
	afx_msg void OnUpdatePlus(CCmdUI* pCmdUI);
	afx_msg void OnMinus();
	afx_msg void OnUpdateMinus(CCmdUI* pCmdUI);
	afx_msg void OnExportClass();
	afx_msg void OnUpdateExportClass(CCmdUI* pCmdUI);
	afx_msg void OnImportClass();
	afx_msg void OnUpdateImportClass(CCmdUI* pCmdUI);
	afx_msg void OnFrameedit();
	afx_msg void OnUpdateFrameedit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateframes();
	afx_msg void OnUpdateUpdateframes(CCmdUI* pCmdUI);
	afx_msg void OnObjectswizard();
	afx_msg void OnUpdateObjectswizard(CCmdUI* pCmdUI);
	afx_msg void OnMovelevel();
	afx_msg void OnUpdateMovelevel(CCmdUI* pCmdUI);
	afx_msg void OnDuplicatelevel();
	afx_msg void OnUpdateDuplicatelevel(CCmdUI* pCmdUI);
	afx_msg void OnFileSendMail();
	afx_msg void OnUpdateFileSendMail(CCmdUI* pCmdUI);
	afx_msg void OnHome();
	afx_msg void OnUpdateHome(CCmdUI* pCmdUI);
	afx_msg void OnTest123();
	afx_msg void OnEditsortdata();
	afx_msg void OnUpdateEditsortdata(CCmdUI* pCmdUI);
	afx_msg void OnLoadsortdata();
	afx_msg void OnUpdateLoadsortdata(CCmdUI* pCmdUI);
	afx_msg void OnSavesortdata();
	afx_msg void OnUpdateSavesortdata(CCmdUI* pCmdUI);
	afx_msg void OnClearSortData();
	afx_msg void OnUpdateClearSortData(CCmdUI* pCmdUI);
	afx_msg void OnEditsyspaths();
	afx_msg void OnUpdateEditsyspaths(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
