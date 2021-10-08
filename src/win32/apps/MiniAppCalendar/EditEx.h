// EditEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditEx window

class CEditEx : public CRichEditCtrl
{
// Construction
public:
	CEditEx();

// Attributes
public:
	int GetId();
	void SetId(int nId);
	void SetFont(char *szFaceName, int nFontSize);
	void SetColor(COLORREF color);
	void SetUpdateMsg(int nMsg);

// Operations
public:
	void Initialize();
	void FixContent(int nStart, int nEnd);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditEx();

	// Generated message map functions
protected:

    char m_szFaceName[32];
    int m_nFontSize;
    int m_nId;
    int m_nUpdateMsg;
    COLORREF m_color;

	//{{AFX_MSG(CEditEx)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChange();
	afx_msg void OnUpdate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
