// DlgSplitExport.h : header file
//

#include "Obl4editDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitExport dialog

class CDlgSplitExport : public CDialog
{
// Construction
public:
	CObl4editDoc * m_pDoc;
	CDlgSplitExport(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSplitExport)
	enum { IDD = IDD_SPLITDLG };
	int		m_nFrom;
	int		m_nSize;
	int		m_nTo;
	int		m_bSplit;
	CString	m_strFilename;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSplitExport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSplitExport)
	virtual BOOL OnInitDialog();
	afx_msg void OnRsplit();
	afx_msg void OnRextract();
	afx_msg void OnCloseupCfrom();
	afx_msg void OnCloseupCto();
	afx_msg void OnBrowse();
	afx_msg void OnChangeEfilename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
