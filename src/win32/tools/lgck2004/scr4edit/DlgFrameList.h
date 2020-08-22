#include "scr4editdoc.h"

// DlgFrameList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFrameList dialog

class CDlgFrameList : public CDialog
{
// Construction
public:
	void UpdateBEdit();
	CDlgFrameList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFrameList)
	enum { IDD = IDD_FRAMELIST };
	int		m_nFrameSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFrameList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CScr4editDoc *m_pDoc;
	
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFrameList)
	virtual BOOL OnInitDialog();
	afx_msg void OnBadd();
	afx_msg void OnBedit();
	afx_msg void OnBupdateall();
	afx_msg void OnDblclkList();
	afx_msg void OnSelchangeList();
	afx_msg void OnBdelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
