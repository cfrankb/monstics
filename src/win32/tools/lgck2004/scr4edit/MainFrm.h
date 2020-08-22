#include <ddraw.h>

// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	void SetStatus(char *szText);
	void InitPal();
	BOOL NewPalette();

// Operations
public:
	BOOL Fail (char *szText);
	BOOL RestoreAll ();
	void ReleaseObjects ();
	BOOL InitDDraw();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	LPDIRECTDRAW            m_lpDD;           // DirectDraw object
	LPDIRECTDRAWSURFACE     m_lpDDSPrimary;   // DirectDraw primary surface
	LPDIRECTDRAWPALETTE		m_lpDDPal;		  // DirectDraw Palette
	LPDIRECTDRAWSURFACE		m_lpDDSBack;	  // DirectDraw backbuffer surface
	LPDIRECTDRAWCLIPPER     m_lpDDClipper;    // DirectDraw clipper.

protected:  // control bar embedded members
    char sz1[1024];
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
    char sz2[1024];

	BOOL m_bSaveSettings;
	BOOL m_bAutoUpdateData;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnGammacorrection();
	afx_msg void OnUpdateGammacorrection(CCmdUI* pCmdUI);
	afx_msg void OnExportpal();
	afx_msg void OnUpdateExportpal(CCmdUI* pCmdUI);
	afx_msg void OnSavesettings();
	afx_msg void OnUpdateSavesettings(CCmdUI* pCmdUI);
	afx_msg void OnAutoUpdatedata();
	afx_msg void OnUpdateAutoUpdatedata(CCmdUI* pCmdUI);
	afx_msg void OnImportpal();
	afx_msg void OnUpdateImportpal(CCmdUI* pCmdUI);
	afx_msg void OnResetpal();
	afx_msg void OnUpdateResetpal(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
