// DlgObjectsList.h : header file
//

#ifndef _DLGOBJECTSLIST_H
#define _DLGOBJECTSLIST_H

#include "Scr4editDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgObjectsList dialog

class CDlgObjectsList : public CDialog
{
// Construction
public:
	int static CALLBACK ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	LRESULT NotifyHandler(UINT message, WPARAM wParam, LPARAM lParam);
	void SetItemState(int nItem, BOOL bSelected);
	BOOL ValidateItem(int i);
	int AddListItem(int nProto, BOOL bSelected);
	int DoProps(CProto & proto);
	void UpdateButtons();
	int GetSelItemIndex();
	void FillBox();
	CString m_strOK;
	CDlgObjectsList(CWnd* pParent = NULL);   // standard constructor

	CScr4editDoc *m_pDoc;
	CImageList m_ImageList;
	int m_nObject;

// Dialog Data
	//{{AFX_DATA(CDlgObjectsList)
	enum { IDD = IDD_OBJECTS2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgObjectsList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgObjectsList)
	afx_msg void OnAdd();
	afx_msg void OnBdelete();
	afx_msg void OnClose();
	afx_msg void OnDuplicate();
	afx_msg void OnEdit();
	afx_msg void OnDblclkListobjects(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListobjects(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListobjects(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif