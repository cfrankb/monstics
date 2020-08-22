#include "strvalarray.h"
#include "scr4editdoc.h"

// DlgClassList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgClassList dialog

class CDlgClassList : public CDialog
{
// Construction
public:
	CDlgClassList(CWnd* pParent = NULL);   // standard constructor

// Attributes
	CScr4editDoc *m_pDoc;

// Operation
	void FillListBox();
	void UpdateBEdit ();
	void UpdateBDelete();

// Dialog Data
	//{{AFX_DATA(CDlgClassList)
	enum { IDD = IDD_CLASSLIST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgClassList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgClassList)
	afx_msg void OnBclose();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList();
	afx_msg void OnBadd();
	afx_msg void OnBdelete();
	afx_msg void OnBedit();
	afx_msg void OnDblclkList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
