
#ifndef _OBL3FILTER_H
#define _OBL3FILTER_H

#include "Format97.h"
#include "ss3frame.h"

// OBL3Filter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COBL3Filter document

class COBL3Filter : public CObject
{
protected:
	DECLARE_DYNCREATE(COBL3Filter)

// Attributes
public:
	char * Ima2Bitmap(char *ImaData, int len, int hei);
	int Add (CSS3Frame *p_pFrame);
	int Extract (CString l_strFilename);
	CObArray m_arrFrames;
  	COBL3Filter();           // protected constructor used by dynamic creation

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COBL3Filter)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COBL3Filter();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COBL3Filter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

#endif
