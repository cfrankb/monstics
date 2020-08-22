// DlgImageSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImageSize dialog

class CDlgImageSize : public CDialog
{
// Construction
public:
	BOOL m_bShowAll;
	void UnHideAll ();
	CDlgImageSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgImageSize)
	enum { IDD = IDD_IMAGESIZE };
	CButton	m_buttonOk;
	CButton	m_buttonCancel;
	CSpinButtonCtrl	m_spinLen;
	CSpinButtonCtrl	m_spinHei;
	UINT	m_nLen;
	UINT	m_nHei;
	BOOL	m_bAll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImageSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgImageSize)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
