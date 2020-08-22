// ProtoSheet.h : header file
//
// This class defines custom modal property sheet 
// CProtoSheet.
 
#ifndef __ProtoSheet_H__
#define __ProtoSheet_H__

#include "ProtoPage1.h"
#include "ProtoPage2.h"
#include "ProtoPage3.h"
#include "ProtoPage4.h"
#include "ProtoPage5.h"

/////////////////////////////////////////////////////////////////////////////
// CProtoSheet

class CProtoSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CProtoSheet)

// Construction
public:
	CProtoSheet(CWnd* pParentWnd = NULL);

// Attributes
public:
	CProtoPage1 m_Page1;
	CProtoPage2 m_Page2;
	CProtoPage3 m_Page3;
	CProtoPage4 m_Page4;
	CProtoPage5 m_Page5;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtoSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProtoSheet();

// Generated message map functions
protected:
	//{{AFX_MSG(CProtoSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __ProtoSheet_H__