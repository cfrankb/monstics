// IconDlg.h : header file
//

#ifndef _ICONDLG_H
#define _ICONDLG_H

#include "iconlistbox.h"

/////////////////////////////////////////////////////////////////////////////
// CIconDlg dialog

class CIconDlg : public CDialog
{
// Construction
public:
	void SetPath(CString & strPath);
	int GetIndex();
	CString & GetPath();
	HICON GetIcon();
	CIconDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIconDlg)
	enum { IDD = IDD_ICONBOX };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillListBox(CString strFilename);
	void UpdateButtons();

	HICON m_hIcon;
	CString m_strPath;
	int m_nIndex;
	CIconListBox m_ctlIconBox;

	// Generated message map functions
	//{{AFX_MSG(CIconDlg)
	afx_msg void OnOpenup();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkList();
	afx_msg void OnSelchangeListx();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif