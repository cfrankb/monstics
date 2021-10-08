#ifndef _ALARMSLISTDIALOG_H
#define _ALARMSLISTDIALOG_H

#include "AppView.h"

// AlarmsListDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmsListDialog dialog

class CAlarmsListDialog : public CDialog
{
// Construction
public:
	void RemoveDeletedAlarmNodes();
	CString MakeTimeString(CTime & l_time);
    CAppView *m_pView;
    CAppDoc *m_pDoc;
	CAlarmsListDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmsListDialog)
	enum { IDD = IDD_ALARMSLIST };
	CButton	m_bDelete;
	CButton	m_bNew;
	CListBox	m_lbAlarms;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmsListDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmsListDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkLbalarms();
	afx_msg void OnSelchangeLbalarms();
	afx_msg void OnBdelete();
	afx_msg void OnBnew();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
