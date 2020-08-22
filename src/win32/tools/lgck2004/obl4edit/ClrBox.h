// ClrBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClrBox window
#ifndef _CCLRBOX
#define _CCLRBOX

#include "stdafx.h"
#include <ddraw.h>
#include "colorlistbox.h"

class CClrBox : public CWnd
{
// Construction
public:
	BOOL Repaint();
	CClrBox();

private:
	BOOL Fail (char *szMsg);
	BOOL m_bListBox;
	int m_nTimer;

	CColorListBox m_wndColorListBox;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClrBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClrBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CClrBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) ;
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
