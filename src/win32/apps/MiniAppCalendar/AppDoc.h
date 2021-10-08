// AppDoc.h : interface of the CAppDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _APPDOC_H
#define _APPDOC_H

#include "StaticEx.h"
#include "AlarmNode.h"
#include "editex.h"

class CAppDoc : public CDocument
{
protected: // create from serialization only
	CAppDoc();
	DECLARE_DYNCREATE(CAppDoc)

	void StoreMonth();
	void RestoreMonth();
	void CleanUp();

// Attributes
public:
	BOOL IsUpdated();
	void TrierAlarms();
    BOOL m_nCritical;
	void DeleteLeftOvers();
	BOOL m_bNoModify;
	int FindNote(int, int);
	CObArray m_arrayNotes;
    CObArray m_arrayAlarms;

	CTime m_CurTime;
	CStaticEx m_arrayStatic[42];
	CStaticEx m_arrayDaysWeek[7];
	//CRichEditCtrl m_arrayEdit[42];
	CEditEx m_arrayEdit[42];  

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAppDoc)
	afx_msg void OnFileSendMail();
	afx_msg void OnUpdateFileSendMail(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
