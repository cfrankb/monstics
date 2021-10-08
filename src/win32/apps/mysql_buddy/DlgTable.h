// DlgTable.h : header file
//

#ifndef _CDLGTABLE_H
#define _CDLGTABLE_H

#include "Table.h"
#include "DlgField.h"
#include "SQLMother.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTable dialog

class CDlgTable : public CDialog
{
// Construction
public:
	CDlgTable(CSQLMother *p, CDocument *pDoc, int i=0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTable)
	enum { IDD = IDD_TABLE };
	CComboBox	m_ctrCBTable;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnChangeTable();
	void OnNewTable();
	void FillComboTables();
	CTable * GetCurrTable();
	void FillBox(CTable * pTable);
	void FormatField(CField *p, char *szTemp);
	void UpdateButtons();
	void SaveField(CField *pField, CDlgField & dlg);

	CSQLMother *m_pMother;
	CDocument *m_pDoc;
	int m_nDefault;

	// Generated message map functions
	//{{AFX_MSG(CDlgTable)
	afx_msg void OnBadd();
	afx_msg void OnBdelete();
	afx_msg void OnBedit();
	afx_msg void OnSelchangeListbox();
	afx_msg void OnDblclkListbox();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEname();
	afx_msg void OnBsql();
	afx_msg void OnBnew();
	afx_msg void OnCloseupCbswitch();
	afx_msg void OnSelchangeCbswitch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif