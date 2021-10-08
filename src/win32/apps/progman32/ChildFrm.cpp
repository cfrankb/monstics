// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "progman32.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_DROPFILES()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
    m_pChildView = NULL;	
    ZeroMemory(&m_rect, sizeof(m_rect));
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
    OutputDebugString("CChildFrame DropFiles \r\n");
	CMDIChildWnd::OnDropFiles(hDropInfo);

    if (m_pChildView)
    {
        m_pChildView->SendMessage(WM_DROPFILES, (WPARAM) hDropInfo);
    }
}

LRESULT CChildFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

    switch (message)
    {
        case WM_PREPARE_NEW_CHILD:
        case WM_ADD_PROGRAM:
            if (m_pChildView && lParam==0x900522)
            {
                m_pChildView-> SendMessage(message, wParam, 0x900522);
            }
        break;

        case WM_RESTORE_RECT:
            m_rect = *((RECT*) wParam);
            MoveWindow(m_rect);
        break;

        case WM_SAVE_RECT:
            m_pChildView->SendMessage(message, (WPARAM) &m_rect, 0x900522);
        break;

        case WM_USER +2:
            m_pChildView = (CView*) wParam;
        break;

        case WM_CLOSE:
            if (lParam!=0x900522)
            {
                return ShowWindow(SW_SHOWMINIMIZED);    
            }
        break;
    }

	return CMDIChildWnd::WindowProc(message, wParam, lParam);
}

void CChildFrame::OnMove(int x, int y) 
{
	CMDIChildWnd::OnMove(x, y);
	
	// TODO: Add your message handler code here
    SaveRect("OnMove");    

}

void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIChildWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

    switch (nType)
    {
        case SIZE_MAXIMIZED:
        break;

        case SIZE_MINIMIZED:
        break;

        case SIZE_RESTORED:
        case SIZE_MAXHIDE:
        case SIZE_MAXSHOW:
            SaveRect("OnSize");
        break;
    }
}

void CChildFrame::SaveRect(char *sz)
{
    CString str;
	this->GetWindowRect(&m_rect);
	CWnd *pParent = GetParent();
    pParent->ScreenToClient(&m_rect);
    //str.Format("[%s] rect.left=%d rect.top=%d\r\n", 
    //     sz, rectThis.left, rectThis.top);
}

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	
	// TODO: Add your message handler code here
    ::DragAcceptFiles(m_hWnd, FALSE);  	
}
