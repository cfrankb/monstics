// DlgMySQLTable.h : header file
//

#ifndef _CDLGMYSQLTABLE_H
#define _CDLGMYSQLTABLE_H

#include "textarray.h"
#include "sqlmother.h"
#include "table.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMySQLTable dialog

class CDlgMySQLTable : public CDialog
{
// Construction
public:
	int GetCurTableId();
	int GetCurFieldId();
	char * GetCurField();
	CDlgMySQLTable(CSQLMother *pMother, CWnd *pParent, char *szDB, char *szTable);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMySQLTable)
	enum { IDD = IDD_MYSQLTABLE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMySQLTable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetStatus(char *sz);

	CSQLMother *m_pMother;
	char m_szTable[128];
	char m_szDB[128];

	CTextArray m_arrTables;
	CTextArray m_arrFields;
	CTable m_table;

	BOOL FillList();
	BOOL FillCombo();
	void UpdateButtons();

	// Generated message map functions
	//{{AFX_MSG(CDlgMySQLTable)
	afx_msg void OnSelchangeCbswitch();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListbox();
	afx_msg void OnDblclkListbox();
	afx_msg void OnBadd();
	afx_msg void OnBdelete();
	afx_msg void OnBedit();
	afx_msg void OnBnew();
	afx_msg void OnBsql();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif