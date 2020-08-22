// ProtoPage2.h : header file
//

#ifndef __PROTOPAGE2_H__
#define __PROTOPAGE2_H__

#include "scr4editdoc.h"

/////////////////////////////////////////////////////////////////////////////
// CProtoPage2 dialog

class CProtoPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProtoPage2)

// Construction
public:
	CProtoPage2();
	~CProtoPage2();

// Dialog Data
	//{{AFX_DATA(CProtoPage2)
	enum { IDD = IDD_PROTOPAGE2 };
	int		m_nDefaultAim;
	int		m_nAniSpeed;
	int		m_nMoveSpeed;
	int		m_nDamages;
	int		m_nHitPoints;
	int		m_nUserTag;
	int		m_nPowerLevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProtoPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProtoPage2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CScr4editDoc *m_pDoc;

};

#endif
