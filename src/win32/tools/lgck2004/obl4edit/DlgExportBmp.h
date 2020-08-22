// DlgExportBmp.h : header file
//

#include "Obl4editDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgExportBmp dialog

class CDlgExportBmp : public CDialog
{
// Construction
public:
	CObl4editDoc * m_pDoc;
	CDlgExportBmp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgExportBmp)
	enum { IDD = IDD_EXPORTBMP };
	int		m_nFrom;
	int		m_nTo;
	CString	m_strFilename;
	int		m_bAll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExportBmp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgExportBmp)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	afx_msg void OnChangeEfilename();
	afx_msg void OnCloseupCfrom();
	afx_msg void OnCloseupCto();
	afx_msg void OnRall();
	afx_msg void OnRextract();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
