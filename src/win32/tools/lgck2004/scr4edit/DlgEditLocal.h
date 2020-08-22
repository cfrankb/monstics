// DlgEditLocal.h : header file
//

#ifndef _DLGEDITLOCAL_H
#define	_DLGEDITLOCAL_H

#include "Scr4editdoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEditLocal dialog

class CDlgEditLocal : public CDialog
{
// Construction
public:
	CDlgEditLocal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEditLocal)
	enum { IDD = IDD_EDITLOCAL };
	int		m_nSubClass;
	int		m_nTriggerKey;
	CString	m_strClass;
	CString	m_strObject;
	BOOL	m_bC10;
	BOOL	m_bC20;
	BOOL	m_bC40;
	BOOL	m_bC80;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditLocal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:
	CScriptEntry *m_pEntry;
	CScr4editDoc *m_pDoc;
	int m_nProto;

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEditLocal)
	virtual BOOL OnInitDialog();
	afx_msg void OnBproto();
	afx_msg void OnBmore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
