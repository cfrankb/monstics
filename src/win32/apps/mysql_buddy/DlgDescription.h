// DlgDescription.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDescription dialog

#include "sqlmother.h"

class CDlgDescription : public CDialog
{
// Construction
public:
	CDlgDescription(CTable *pTable, CWnd* pParent); 

// Dialog Data
	//{{AFX_DATA(CDlgDescription)
	enum { IDD = IDD_DESCRIPTION };
	CString	m_strDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDescription)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CTable * m_pTable;

	// Generated message map functions
	//{{AFX_MSG(CDlgDescription)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
