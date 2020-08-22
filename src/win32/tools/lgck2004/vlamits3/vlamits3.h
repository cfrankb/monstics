// vlamits3.h : main header file for the VLAMITS3 application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVlamits3App:
// See vlamits3.cpp for the implementation of this class
//

class CVlamits3App : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL UpdateScreen();
	int m_nFrameTime;
	CVlamits3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVlamits3App)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVlamits3App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
