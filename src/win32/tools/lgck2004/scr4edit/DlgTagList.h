// DlgTagList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTagList dialog

#include "tagArray.h"

class CDlgTagList : public CDialog
{
// Construction
public:
	void SetTitle (const CString & string);
	CTagArray *m_pArray;
	char **m_ppChoices;
	char **m_ppContent;
	CDlgTagList(UINT nChildIDD=IDD_TAGEDIT, char **ppChoices=NULL, char **ppContent=NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTagList)
	enum { IDD = IDD_TAGLIST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTagList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CString m_strName;
	UINT m_nChildIDD;

	void UpdateButtons ();
	
	// Generated message map functions
	//{{AFX_MSG(CDlgTagList)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList();
	afx_msg void OnSelchangeList();
	afx_msg void OnBadd();
	afx_msg void OnBedit();
	afx_msg void OnBdelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
