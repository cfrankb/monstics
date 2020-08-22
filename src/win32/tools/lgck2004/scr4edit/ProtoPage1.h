// ProtoPage1.h : header file
//

#ifndef __PROTOPAGE1_H__
#define __PROTOPAGE1_H__

#include "scr4editdoc.h"

/////////////////////////////////////////////////////////////////////////////
// CProtoPage1 dialog

class CProtoPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProtoPage1)

// Construction
public:
	void Fill_FrameNoCombo(int nFrameSet);
	CProtoPage1();
	~CProtoPage1();

// Dialog Data
	//{{AFX_DATA(CProtoPage1)
	enum { IDD = IDD_PROTOPAGE1 };
	BOOL	m_bAnimate;
	int		m_nClass;
	int		m_nFrameSet;
	int		m_nObjectKey;
	int		m_nTrigger;
	CString	m_strName;
	int		m_nFrameNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProtoPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProtoPage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCframeset();
	afx_msg void OnChangeEname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CScr4editDoc *m_pDoc;

};

#endif // __PROTOPAGE1_H__
