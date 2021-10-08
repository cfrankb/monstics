// mysql_buddyView.cpp : implementation of the CMysql_buddyView class
//

#include "stdafx.h"
#include "mysql_buddy.h"

#include "mysql_buddyDoc.h"
#include "mysql_buddyView.h"
#include "wndtable.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyView

IMPLEMENT_DYNCREATE(CMysql_buddyView, CListView)

BEGIN_MESSAGE_MAP(CMysql_buddyView, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CMysql_buddyView)
	ON_WM_DESTROY()
	ON_COMMAND(IDM_MYSQLADMIN_TO_FRONT, OnMysqladminToFront)
	ON_UPDATE_COMMAND_UI(IDM_MYSQLADMIN_TO_FRONT, OnUpdateMysqladminToFront)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyView construction/destruction

CMysql_buddyView::CMysql_buddyView()
{
	// TODO: add construction code here

}

CMysql_buddyView::~CMysql_buddyView()
{
}

BOOL CMysql_buddyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

    cs.style |= WS_HSCROLL | WS_VSCROLL ;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyView drawing

void CMysql_buddyView::OnDraw(CDC* pDC)
{
	CMysql_buddyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyView diagnostics

#ifdef _DEBUG
void CMysql_buddyView::AssertValid() const
{
	CListView::AssertValid();
}

void CMysql_buddyView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMysql_buddyDoc* CMysql_buddyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMysql_buddyDoc)));
	return (CMysql_buddyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyView message handlers

BOOL CMysql_buddyView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	static CREATESTRUCT cs;

	

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CMysql_buddyView::OnActivateView(BOOL bActivate, CListView* pActivateView, CListView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	CListView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CMysql_buddyView::OnUpdate(CListView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	OutputDebugString("OnUpdate()\n");	
	
}

void CMysql_buddyView::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This function was added by the Pop-up Menu component

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_VIEW));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}

BOOL CMysql_buddyView::PreTranslateMessage(MSG* pMsg)
{
	// CG: This block was added by the Pop-up Menu component
	{
		// Shift+F10: show pop-up menu.
		if ((((pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN) && // If we hit a key and
			(pMsg->wParam == VK_F10) && (GetKeyState(VK_SHIFT) & ~1)) != 0) ||	// it's Shift+F10 OR
			(pMsg->message == WM_CONTEXTMENU))									// Natural keyboard key
		{
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			CPoint point = rect.TopLeft();
			point.Offset(5, 5);
			OnContextMenu(NULL, point);

			return TRUE;
		}
	}

	return CListView::PreTranslateMessage(pMsg);
}

BOOL CMysql_buddyView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
    OutputDebugString("CMysql_buddyView::DestroyWindow()\n");
	return CListView::DestroyWindow();
}

void CMysql_buddyView::OnDestroy() 
{
    OutputDebugString("CMysql_buddyView::Destroy()\n");
    GetDocument()->DestroyDocument();
	CListView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CMysql_buddyView::OnMysqladminToFront() 
{
	// TODO: Add your command handler code here
	HWND hWnd = FindWindowEx(NULL, NULL,  NULL, "WinMySQLAdmin 1.3");
    ::ShowWindow(hWnd, SW_MAXIMIZE | SW_SHOW);
    ::SetFocus(hWnd);
}

void CMysql_buddyView::OnUpdateMysqladminToFront(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	HWND hWnd = FindWindowEx(NULL, NULL,  NULL, "WinMySQLAdmin 1.3");
    pCmdUI->Enable((BOOL)hWnd);   
    //GetWindowThreadProcessId
}
