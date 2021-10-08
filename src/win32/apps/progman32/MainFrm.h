// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAINFRM_H
#define _MAINFRM_H

#include "autoarr.h"

typedef struct 
{
    RECT rect;
    CAutoArr m_arrGroups;
} SETTINGS;

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
    SETTINGS    m_settings;

	void CreateGroups();
	void SaveSettings();
	void LoadSettings();
	BOOL GetGroupName(CString & str);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCreateNew();
	afx_msg void OnUpdateCreateNew(CCmdUI* pCmdUI);
	afx_msg void OnWindowsCascade();
	afx_msg void OnUpdateWindowsCascade(CCmdUI* pCmdUI);
	afx_msg void OnWindowsMosaic();
	afx_msg void OnUpdateWindowsMosaic(CCmdUI* pCmdUI);
	afx_msg void OnWindowsReorganizeicons();
	afx_msg void OnUpdateWindowsReorganizeicons(CCmdUI* pCmdUI);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnOptionReorganizeAutomatic();
	afx_msg void OnUpdateOptionReorganizeAutomatic(CCmdUI* pCmdUI);
	afx_msg void OnRun();
	afx_msg void OnUpdateRun(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
