// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MiniApp Reptel.h"
#include "Entry.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	InitCommonControls();
    m_wndToolBar.SetWindowText("Barre d'outils");
    LoadBarState ("BarSettings");

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



int CALLBACK CMainFrame::ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int iResult;


    CEntry *l_pEntry1 = (CEntry *) lParam1;
    CEntry *l_pEntry2 = (CEntry *) lParam2;

    int l_nColumn = abs( (int) lParamSort);
    BOOL l_bOrder = ((int) lParamSort)<0;



    switch( l_nColumn)
	{
		case 0:     // sort by Name               
            iResult  = l_pEntry1->m_strName >
                       l_pEntry2->m_strName;
            break;

			case 1:     // sort by Phone
                iResult  = l_pEntry1->m_strTel >
                           l_pEntry2->m_strTel;
                break;

			case 2:     // sort by Addr
                iResult  = l_pEntry1->m_strAddr >
                           l_pEntry2->m_strAddr;
				break;

			case 3:     // sort by Note
                iResult  = l_pEntry1->m_strInfo >
                           l_pEntry2->m_strInfo;
				break;

			default: // sort by Nothing
				iResult = 0;
				break;

		}

    if (l_bOrder) 
    {    
        if (iResult==0)
            iResult=1;
            else
            iResult=0;
    }

	return(iResult);

}

LRESULT CMainFrame::NotifyHandler(UINT message, WPARAM wParam, LPARAM lParam)
{
	LV_DISPINFO *pLvdi = (LV_DISPINFO *)lParam;
	NM_LISTVIEW *pNm = (NM_LISTVIEW *)lParam;

    static BOOL l_bSens[4];
    int l_nColumn ;
	switch(pLvdi->hdr.code)
	{

        case LVN_BEGINLABELEDIT:
            {
            //CEdit *pEdit;

            // Get the handle to the edit control.
            //pEdit = m_ListCtl.GetEditControl();
            // Limit the amount of text that teh user can enter.
            //pEdit->LimitText(20);
            }
            break;

        case LVN_ENDLABELEDIT:
            // If label editing wasn't cancelled and the 
            // text buffer is non-NULL...
            //if ((pLvdi->item.iItem != -1) && (pLvdi->item.pszText != NULL))
                // save the new label information.
	    	//	lstrcpy(pHouse->szAddress, pLvdi->item.pszText);
            break;          

		case LVN_COLUMNCLICK:
			// The user clicked on one of the column headings - sort by
			// this column.

            l_nColumn = pNm->iSubItem;
            l_bSens[l_nColumn] = 1 - l_bSens[l_nColumn];
            if (l_bSens==FALSE) ((CListView*)GetActiveView())->GetListCtrl().SortItems( ListViewCompareProc,
								(LPARAM)(pNm->iSubItem));
            else
                ((CListView*)GetActiveView())->GetListCtrl().SortItems( ListViewCompareProc,
								(LPARAM)-(pNm->iSubItem));

			break;

		default:
			break;
	}
	return 0L;


}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_NOTIFY)
		NotifyHandler(message, wParam, lParam);
	
	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
    SaveBarState ("BarSettings");
	
	CFrameWnd::OnClose();
}

