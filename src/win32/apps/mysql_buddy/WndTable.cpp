// WndTable.cpp : implementation file
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "WndTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CFont g_font;

/////////////////////////////////////////////////////////////////////////////
// CWndTable

CWndTable::CWndTable(CSQLMother *pMother)
{
	m_pTable = NULL;

	static b =  TRUE;
	if (b)
	{
		CClientDC dc (AfxGetMainWnd());
		int nHeight = 15;
		int iStatus = g_font.CreateFont (nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0,
			DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH , "Arial");
		b= FALSE;
	}

	m_pMother = pMother;
	m_nTableId = -1;
}

CWndTable::~CWndTable()
{
}

BEGIN_MESSAGE_MAP(CWndTable, CWnd)
	//{{AFX_MSG_MAP(CWndTable)
	ON_WM_CREATE()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_SHOWWINDOW()
	ON_WM_NCHITTEST()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
	ON_WM_NCRBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndTable message handlers

int CWndTable::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	CRect rect;
	GetClientRect(&rect);

	if (m_ctrList.Create(
		WS_VSCROLL |
		LBS_NOTIFY	| LBS_USETABSTOPS | LBS_WANTKEYBOARDINPUT,
		rect,
		this,
		1))
	{
		//OutputDebugString("Listbox created\n");
	}

	m_ctrList.ShowWindow(SW_SHOW);
	ShowWindow(SW_SHOWNOACTIVATE);
	return 0;
}

LRESULT CWndTable::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	switch (message)
	{
		case WM_UTABLESORDERCHANGED:
			m_nTableId = wParam;
		break;

		case WM_UTABLENAMECHANGED:
			SetWindowText(m_pTable->m_szName);
			m_nTableId = wParam;
		break;

		case WM_UTABLEREPOPULATE:
			FillTable(*m_pTable, wParam);
		break;

        case WM_UTABLETERMINATE:
            m_ctrList.SendMessage(WM_DESTROY);
            //PostMessage(WM_DESTROY);
        break;
	}

	return CWnd::DefWindowProc(message, wParam, lParam);
}

void CWndTable::OnMove(int x, int y) 
{
	CWnd::OnMove(x, y);
	// TODO: Add your message handler code here

	if (m_pMother && m_pTable)
	{
		CRect rectThis;
		this->GetWindowRect(&rectThis);

		CWnd *pParent = GetParent();
		CRect rectParent;
		pParent->GetWindowRect(&rectParent);

		int nX = rectThis.left - rectParent.left;
		int nY = rectThis.top - rectParent.top;
			
		if (m_pTable)
		{
			m_pTable->SetWndXY(nX,nY);
		}
	}

	SetWindowText(m_pTable->m_szName);
	Invalidate();
}

void CWndTable::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
 	// TODO: Add your message handler code here	

	CRect rect;
	GetWindowRect(&rect);

	if (m_pTable)
	{
		m_pTable->SetWndSize(1+rect.right-rect.left,
			1+rect.bottom-rect.top);
	}

	GetClientRect(&rect);
	m_ctrList.MoveWindow(0,0, 1+rect.right, 1+rect.bottom);
}

void CWndTable::FillTable(CTable & table, int i)
{
	SetWindowText(table.m_szName);

	m_ctrList.ResetContent();
	m_ctrList.SetFont(&g_font);
	for (int n=0; n<table.GetSize(); n++)
	{
		m_ctrList.AddString(table[n]->m_szName);	
	}

	Invalidate();
	m_pTable = &table;
	m_nTableId = i;
}

void CWndTable::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here

	GetParent()->SetFocus();
}

void CWndTable::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
}

UINT CWndTable::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	return CWnd::OnNcHitTest(point);
}

void CWndTable::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnNcMouseMove(nHitTest, point);
}

void CWndTable::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OutputDebugString("CWndTable::OnNcLButtonDblClk()\n");
	if (m_pMother)
	{
		m_pMother->SetSelTable(m_nTableId);
		AfxGetMainWnd()->PostMessage(IDM_TABLEEDIT, 0,0) ;
	}
	//CWnd::OnNcLButtonDblClk(nHitTest, point);
}

void CWndTable::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	OutputDebugString("CWndTable::OnContextMenu()\n");

	if (m_pMother)
	{
		m_pMother->SetSelTable(m_nTableId);
		DoContextMenu(IDR_TABLE, point);
	}
}

void CWndTable::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnRButtonDown(nFlags, point);
}

void CWndTable::DoContextMenu(int nId, CPoint &point)
{
	CMenu menu;
	VERIFY(menu.LoadMenu(nId));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		AfxGetMainWnd()/*pWndPopupOwner*/);
	
}

void CWndTable::OnNcRButtonDown(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OutputDebugString("CWndTable::OnNcRButtonDown()\n");
	
	CWnd::OnNcRButtonDown(nHitTest, point);

	if (m_pMother)
	{
		m_pMother->SetSelTable(m_nTableId);
		DoContextMenu(IDR_TABLE, point);
	}
}

