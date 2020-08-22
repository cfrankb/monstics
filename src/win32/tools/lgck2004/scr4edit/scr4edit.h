// scr4edit.h : main header file for the SCR4EDIT application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef _SCR4EDIT_H
#define _SCR4EDIT_H

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CScr4editApp:
// See scr4edit.cpp for the implementation of this class
//

class CScr4editApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CScr4editApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScr4editApp)
	public:
	virtual BOOL InitInstance();
	virtual void DoWaitCursor(int nCode);
	virtual BOOL InitApplication();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScr4editApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
#endif