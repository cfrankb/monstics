// DlgDatabase.h : header file
//

#ifndef _DLGDATABASE_H
#define _DLGDATABASE_H

#include "SQLMother.h"
#include "TextArray.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDatabase dialog

class CDlgDatabase : public CDialog
{
// Construction
public:
	CDlgDatabase(CSQLMother *p, CDocument *pDoc);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDatabase)
	enum { IDD = IDD_DATABASE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDatabase)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:	
	~CDlgDatabase();

protected:

	CSQLMother *m_pMother;
	CTextArray m_arrMySQLDB;
	CTextArray m_arrMySQLTables;
	CDocument *m_pDoc;

	void UpdateButtons();
	int GetCurrLocalTableId();
	char * GetCurrMySQLTable();
	char* GetCurrMySQLDB();
	CTable * GetCurrLocalTable();
	BOOL FillListLocal();
	BOOL OnChangeMySQLDB();
	BOOL FillListMySQL();
	BOOL FillComboMySQL();
	void SetStatus(char *szText);

	// Generated message map functions
	//{{AFX_MSG(CDlgDatabase)
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseupCblocal();
	afx_msg void OnSelchangeCblocal();
	afx_msg void OnCloseupCbmysql();
	afx_msg void OnSelchangeCbmysql();
	afx_msg void OnBdropmysqldb();
	afx_msg void OnBdroptablelocal();
	afx_msg void OnBdroptablemysql();
	afx_msg void OnBnewmysqldb();
	afx_msg void OnBtomysql();
	afx_msg void OnSelchangeLlocal();
	afx_msg void OnSelchangeLmysql();
	afx_msg void OnBshowsql();
	afx_msg void OnDblclkLlocal();
	afx_msg void OnBrename();
	afx_msg void OnDblclkLmysql();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
