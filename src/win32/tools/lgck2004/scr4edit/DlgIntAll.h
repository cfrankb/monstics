// DlgIntAll.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIntAll dialog

#include "ExtraArray.h"

class CDlgIntAll : public CDialog
{
// Construction
public:
	void FillBox();
	void UpdateButtons();
	CDlgIntAll(char **arrContent, int *arrValue, CWnd *pWnd);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIntAll)
	enum { IDD = IDD_DINTALL };
	CButton	m_bbEdit;
	CButton	m_bbDelete;
	CButton	m_bbAdd;
	CListBox	m_ctrList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIntAll)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:
	CExtraArray *m_pArray;

protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgIntAll)
	afx_msg void OnBadd();
	afx_msg void OnBedit();
	afx_msg void OnBdelete();
	afx_msg void OnDblclkList();
	afx_msg void OnSelcancelList();
	afx_msg void OnSelchangeList();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	char *m_pNameIntAll;
	char *m_pNameIntArray;
	char *m_pNameIntBox;

	char **m_arrContent;
	int *m_arrValue;
};
