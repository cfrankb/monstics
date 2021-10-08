// WndTable.h : header file
//

#ifndef _CWNDTABLE_H
#define _CWNDTABLE_H

#include "table.h"
#include "sqlmother.h"

/////////////////////////////////////////////////////////////////////////////
// CWndTable window

class CWndTable : public CWnd
{
// Construction
public:
	void DoContextMenu(int nId, CPoint & point);
	void FillTable(CTable & table, int i);
	CWndTable(CSQLMother *pMother);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndTable)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWndTable();

private:
	CListBox m_ctrList;
	CTable *m_pTable;
	CSQLMother *m_pMother;
	int m_nTableId;

	// Generated message map functions
protected:
	//{{AFX_MSG(CWndTable)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
