// mysql_buddyDoc.h : interface of the CMysql_buddyDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "SQLMother.h"
#include "table.h"
#include "mainfrm.h"

class CMysql_buddyDoc : public CDocument
{
protected: // create from serialization only
	CMysql_buddyDoc();
	DECLARE_DYNCREATE(CMysql_buddyDoc)

// Attributes
public:
	void DestroyDocument();
	CWnd * GetView();
	CMainFrame * GetFrame();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysql_buddyDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMysql_buddyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	//CTable m_table;
	CSQLMother m_mother;

// Generated message map functions
protected:
	//{{AFX_MSG(CMysql_buddyDoc)
	afx_msg void OnTables();
	afx_msg void OnUpdateTables(CCmdUI* pCmdUI);
	afx_msg void OnExportsql();
	afx_msg void OnUpdateExportsql(CCmdUI* pCmdUI);
	afx_msg void OnServer();
	afx_msg void OnUpdateServer(CCmdUI* pCmdUI);
	afx_msg void OnTest();
	afx_msg void OnUpdateTest(CCmdUI* pCmdUI);
	afx_msg void OnDatabase();
	afx_msg void OnUpdateDatabase(CCmdUI* pCmdUI);
	afx_msg void OnTabledelete();
	afx_msg void OnUpdateTabledelete(CCmdUI* pCmdUI);
	afx_msg void OnTableedit();
	afx_msg void OnUpdateTableedit(CCmdUI* pCmdUI);
	afx_msg void OnTablerename();
	afx_msg void OnUpdateTablerename(CCmdUI* pCmdUI);
	afx_msg void OnWriteDropCode();
	afx_msg void OnUpdateWriteDropCode(CCmdUI* pCmdUI);
	afx_msg void OnWriteTechdoc();
	afx_msg void OnUpdateWriteTechdoc(CCmdUI* pCmdUI);
	afx_msg void OnSetTableDescription();
	afx_msg void OnUpdateSetTableDescription(CCmdUI* pCmdUI);
	afx_msg void OnImportsql();
	afx_msg void OnUpdateImportsql(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
