// DlgExportPal.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgExportPal dialog

class CDlgExportPal : public CDialog
{
// Construction
public:
	void UpdateButtons();
	CDlgExportPal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgExportPal)
	enum { IDD = IDD_EXPORTPAL };
	CButton	m_ctrFormat;
	CEdit	m_ctrName;
	CButton	m_ctrOK;
	CString	m_strName;
	int		m_nFormat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExportPal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgExportPal)
	afx_msg void OnBbrowse();
	afx_msg void OnChangeEname();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
