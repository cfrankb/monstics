// ProtoPage3.h : header file
//

#ifndef __PROTOPAGE3_H__
#define __PROTOPAGE3_H__

#include "scr4editdoc.h"

/////////////////////////////////////////////////////////////////////////////
// CProtoPage3 dialog

class CProtoPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CProtoPage3)

// Construction
public:
	CProtoPage3();
	~CProtoPage3();

// Dialog Data
	//{{AFX_DATA(CProtoPage3)
	enum { IDD = IDD_PROTOPAGE3 };
	int		m_nChProto;
	int		m_nChSound;
	int		m_nPoints;
	int		m_nRbDelay;
	int		m_nRebirths;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProtoPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProtoPage3)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CScr4editDoc *m_pDoc;


};

#endif
