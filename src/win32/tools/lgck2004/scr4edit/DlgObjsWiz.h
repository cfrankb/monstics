// DlgObjsWiz.h : header file
//

#include "scr4editdoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgObjsWiz dialog

class CDlgObjsWiz : public CDialog
{
// Construction
public:
	void UpdateBCreate();
	void FillCombo();
	CDlgObjsWiz(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgObjsWiz)
	enum { IDD = IDD_OBJSWIZ };
	CString	m_strFilename;
	int		m_nClass;
	//}}AFX_DATA

	CScr4editDoc *m_pDoc;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgObjsWiz)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgObjsWiz)
	virtual BOOL OnInitDialog();
	afx_msg void OnBbrowse();
	afx_msg void OnBnew();
	afx_msg void OnChangeEfilename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
