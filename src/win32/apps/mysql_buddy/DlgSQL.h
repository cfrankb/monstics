// DlgSQL.h : header file
//

#ifndef _CDLGSQL_H
#define _CDLGSQL_H

#include "table.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSQL dialog

class CDlgSQL : public CDialog
{
// Construction
public:
	CDlgSQL(CTable *pTable);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSQL)
	enum { IDD = IDD_SQL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSQL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CString m_strSQL;

	// Generated message map functions
	//{{AFX_MSG(CDlgSQL)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif