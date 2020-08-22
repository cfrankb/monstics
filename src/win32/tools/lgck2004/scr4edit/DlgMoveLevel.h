#include "scr4editdoc.h"
// DlgMoveLevel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMoveLevel dialog

class CDlgMoveLevel : public CDialog
{
// Construction
public:
	CDlgMoveLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMoveLevel)
	enum { IDD = IDD_MOVELEVEL };
	int		m_nInsertMode;
	int		m_nTarget;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMoveLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMoveLevel)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListlevels();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CScr4editDoc *m_pDoc;

};
