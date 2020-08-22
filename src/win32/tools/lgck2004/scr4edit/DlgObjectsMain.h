// DlgObjectsMain.h : header file
//

#include "Scr4editDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgObjectsMain dialog

class CDlgObjectsMain : public CDialog
{
// Construction
public:
	int DoProps(CProto & proto);
	void UpdateEDIT();
	CString m_strOK;
	CDlgObjectsMain(CWnd* pParent = NULL);   // standard constructor

// Operations
public:
	void FillListBox();

// Dialog Data
	//{{AFX_DATA(CDlgObjectsMain)
	enum { IDD = IDD_OBJECTS };
	int		m_nObject;
	//}}AFX_DATA

	CScr4editDoc *m_pDoc;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgObjectsMain)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgObjectsMain)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnDuplicate();
	afx_msg void OnEdit();
	afx_msg void OnDblclkList();
	afx_msg void OnClose();
	afx_msg void OnSelchangeList();
	afx_msg void OnBdelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
