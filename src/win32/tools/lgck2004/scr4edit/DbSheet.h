// DbSheet.h : header file
//

#include "dbpage1.h"
#include "dbpage2.h"
#include "dbpage3.h"
#include "dbpage4.h"

/////////////////////////////////////////////////////////////////////////////
// CDbSheet

class CDbSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CDbSheet)

// Construction
public:
	void Build();
	CDbSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDbSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDbSheet();

	CDbPage1 m_page1;
	CDbPage2 m_page2;
	CDbPage3 m_page3;
	CDbPage4 m_page4;

	// Generated message map functions
protected:
	//{{AFX_MSG(CDbSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
