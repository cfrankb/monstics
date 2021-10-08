// DlgConfig.h : header file
//

#ifndef _DLGCONFIG_H
#define _DLGCONFIG_H

#include "serverarr.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgConfig dialog

class CDlgConfig : public CDialog
{
// Construction
public:
	void UpdateButtons();
	BOOL Save();
	BOOL Load();
	CDlgConfig(CServerArr *p, CDocument *pDoc);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgConfig)
	enum { IDD = IDD_CONFIG };
	int		m_nConfig;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateForm();

	CDocument *m_pDoc;
	CServerArr *m_pServerArr;
	int m_nCurrent;

	// Generated message map functions
	//{{AFX_MSG(CDlgConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseupCbconfig();
	afx_msg void OnSelchangeCbconfig();
	afx_msg void OnBdelete();
	afx_msg void OnBduplicate();
	afx_msg void OnBnew();
	afx_msg void OnBreset();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
