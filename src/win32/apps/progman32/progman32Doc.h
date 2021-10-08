// progman32Doc.h : interface of the CProgman32Doc class
//
/////////////////////////////////////////////////////////////////////////////

#include "iconarray.h"

class CProgman32Doc : public CDocument
{
protected: // create from serialization only
	CProgman32Doc();
	DECLARE_DYNCREATE(CProgman32Doc)

// Attributes
public:
	void Delete();
	void GetRect(RECT & rect);
	void SetRect(RECT & rect);
	void Forget();
	CIconArray & GetIconArray();
	BOOL ProcessAction(CHILD_INFO & info);
	void Load();
	void Save();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgman32Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgman32Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    CIconArray m_arrIcons;
    RECT m_rect;
    int m_nState;

	//{{AFX_MSG(CProgman32Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
