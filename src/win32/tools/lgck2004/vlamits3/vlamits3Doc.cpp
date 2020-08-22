// vlamits3Doc.cpp : implementation of the CVlamits3Doc class
//

#include "stdafx.h"
#include "vlamits3.h"

#include "vlamits3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVlamits3Doc

IMPLEMENT_DYNCREATE(CVlamits3Doc, CDocument)

BEGIN_MESSAGE_MAP(CVlamits3Doc, CDocument)
	//{{AFX_MSG_MAP(CVlamits3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVlamits3Doc construction/destruction

CVlamits3Doc::CVlamits3Doc()
{
	// TODO: add one-time construction code here

}

CVlamits3Doc::~CVlamits3Doc()
{
}

BOOL CVlamits3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVlamits3Doc serialization

void CVlamits3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVlamits3Doc diagnostics

#ifdef _DEBUG
void CVlamits3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVlamits3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVlamits3Doc commands
