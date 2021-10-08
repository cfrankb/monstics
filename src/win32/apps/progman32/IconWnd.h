// IconWnd.h : header file
//

#ifndef _ICONWND_H
#define _ICONWND_H

#include "autoarr.h"

/////////////////////////////////////////////////////////////////////////////
// CIconWnd window

class CIconWnd : public CWnd
{
// Construction
public:
	int ManageItem(AA_ITEM & item, int i, BOOL bSelected, BOOL bInsert);
	void AddItem(AA_ITEM & item);
	CIconWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIconWnd();

	// Generated message map functions
protected:
	BOOL CreateList();

    CListView m_listview;
    CImageList m_imageList;
    CAutoArr m_arrItems;

	//{{AFX_MSG(CIconWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnCreateNew();
	afx_msg void OnUpdateCreateNew(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
