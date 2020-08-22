// DlgIntArray.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIntArray dialog

#include "extradata.h"

class CDlgIntArray : public CDialog
{
// Construction
public:
	void FillBox();
	void ResetContent();
	void UpdateButtons();
	CDlgIntArray(char **arrContent, int *arrValue, CWnd* pWnd);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIntArray)
	enum { IDD = IDD_DINTARRAY };
	CEdit	m_ctrName;
	CButton	m_bbInsert;
	CButton	m_bbEdit;
	CButton	m_bbDuplicate;
	CButton	m_bbDelete;
	CButton	m_bbAdd;
	CListBox	m_ctrList;
	CString	m_strName;
	int		m_nIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIntArray)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CExtraData *m_pExtraData;
	char *m_pNameIntArray;
	char *m_pNameIntBox;
	
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIntArray)
	virtual BOOL OnInitDialog();
	afx_msg void OnBadd();
	afx_msg void OnBdelete();
	afx_msg void OnBduplicate();
	afx_msg void OnBedit();
	afx_msg void OnBinsert();
	afx_msg void OnDblclkList();
	afx_msg void OnSelcancelList();
	afx_msg void OnSelchangeList();
	afx_msg void OnBmore();
	afx_msg void OnBpath();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	char **m_arrContent;
	int *m_arrValue;
};
