// vlamits3View.cpp : implementation of the CVlamits3View class
//

#include "stdafx.h"
#include "vlamits3.h"

#include "vlamits3Doc.h"
#include "vlamits3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVlamits3View

IMPLEMENT_DYNCREATE(CVlamits3View, CView)

BEGIN_MESSAGE_MAP(CVlamits3View, CView)
	//{{AFX_MSG_MAP(CVlamits3View)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVlamits3View construction/destruction

CVlamits3View::CVlamits3View()
{
	// TODO: add construction code here

}

CVlamits3View::~CVlamits3View()
{
}

BOOL CVlamits3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVlamits3View drawing

void CVlamits3View::OnDraw(CDC* pDC)
{
	CVlamits3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CVlamits3View diagnostics

#ifdef _DEBUG
void CVlamits3View::AssertValid() const
{
	CView::AssertValid();
}

void CVlamits3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVlamits3Doc* CVlamits3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVlamits3Doc)));
	return (CVlamits3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVlamits3View message handlers

BOOL CVlamits3View::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString strWndClass = AfxRegisterWndClass (
        0,//CS_DBLCLKS ,                  // Class style
        NULL, //AfxGetApp()->LoadStandardCursor (IDC_ARROW),   // Class cursor
        NULL,//(HBRUSH)COLOR_INFOTEXT,//(HBRUSH) (COLOR_3DFACE ),               // Class background brush
        NULL            // Class icon
        );
	
	return CWnd::Create(strWndClass, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CVlamits3View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(NULL);
	return CView::OnSetCursor(pWnd, nHitTest, message);
}
