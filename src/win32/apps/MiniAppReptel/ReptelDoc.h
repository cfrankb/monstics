// ReptelDoc.h : interface of the CReptelDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CReptelDoc : public CDocument
{
protected: // create from serialization only
	CReptelDoc();
	DECLARE_DYNCREATE(CReptelDoc)

// Attributes
public:
	int m_nEntry;
	CObArray m_arrEntry;
	CImageList m_ImageLarge;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReptelDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReptelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReptelDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CListView *GetView();
};

/////////////////////////////////////////////////////////////////////////////
