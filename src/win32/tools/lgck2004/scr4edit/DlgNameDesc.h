// DlgNameDesc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNameDesc dialog

#include "scr4editdoc.h"

class CDlgNameDesc : public CDialog
{
// Construction
public:
	void SetCaption (const CString & string);
	CDlgNameDesc(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNameDesc)
	enum { IDD = IDD_NAMEDESC };
	CString	m_strName;
	CString	m_strTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNameDesc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CScr4editDoc *m_pDoc;
	
protected:
	CString m_strCaption;

	// Generated message map functions
	//{{AFX_MSG(CDlgNameDesc)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
