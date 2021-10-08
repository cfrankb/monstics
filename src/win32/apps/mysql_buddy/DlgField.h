// DlgField.h : header file
//

#ifndef _CDLG_FIELD_H
#define _CDLG_FIELD_H

#include "field.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgField dialog

class CDlgField : public CDialog
{
// Construction
public:
	CDlgField(CField *p);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgField)
	enum { IDD = IDD_FIELD };
	CString	m_strName;
	int		m_nType;
	BOOL	m_bNotNull;
	BOOL	m_bPrimary;
	BOOL	m_bKey;
	BOOL	m_bAuto;
	CString	m_strDefault;
	CString	m_strArg;
	BOOL	m_bUnique;
	BOOL	m_bUnsigned;
	CString	m_strInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgField)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CField *m_pField;

	// Generated message map functions
	//{{AFX_MSG(CDlgField)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
