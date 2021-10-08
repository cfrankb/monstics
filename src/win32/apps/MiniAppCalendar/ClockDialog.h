#ifndef _CLOCKDIALOG_H
#define _CLOCKDIALOG_H

#include "AppDoc.h"
#include "AppView.h"

// ClockDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClockDialog dialog

class CClockDialog : public CDialog
{
// Construction
public:
	void FixDayCombo();
	void FillDayCombo(int l_nMonth, int l_nYear);
    CAppDoc * m_pDoc;
	CAppView * m_pView;
	CString m_strCaption;
	CClockDialog(CWnd* pParent = NULL);   // standard constructor

    int m_nYear;
    int m_nMonth;
    int m_nDay;

    int m_nHour;
    int m_nMin;

// Dialog Data
	//{{AFX_DATA(CClockDialog)
	enum { IDD = IDD_ALARME };
	CEdit	m_eSound;
	CButton	m_bSound;
	CEdit	m_eInfo;
	CComboBox	m_cbYear;
	CComboBox	m_cbMonth;
	CComboBox	m_cbMin;
	CComboBox	m_cbHour;
	CComboBox	m_cbDay;
	CString	m_strInfo;
	CString	m_strSound;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClockDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClockDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCmonth();
	afx_msg void OnSelchangeCyear();
	virtual void OnOK();
	afx_msg void OnBsound();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
