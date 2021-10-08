// AppView.cpp : implementation of the CAppView class
//


#include "resource.h"
#include "stdafx.h"
#include "StaticEx.h"
#include "AppDoc.h"
#include "AppView.h"
#include "App.h"

#include "note.h"
#include "resource.h"

#include "MemoDialog.h"
#include "ClockDialog.h"
#include "AlarmsListDialog.h"

#include "bipbox.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppView

IMPLEMENT_DYNCREATE(CAppView, CView)

BEGIN_MESSAGE_MAP(CAppView, CView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CAppView)
	ON_WM_CREATE()
	ON_COMMAND(ID_MOIS_BACK, OnMoisBack)
	ON_COMMAND(ID_MOIS_NEXT, OnMoisNext)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_MOIS_MEMO, OnMoisMemo)
	ON_UPDATE_COMMAND_UI(ID_MOIS_MEMO, OnUpdateMoisMemo)
	ON_COMMAND(ID_MOIS_CLOCK, OnMoisClock)
	ON_UPDATE_COMMAND_UI(ID_MOIS_CLOCK, OnUpdateMoisClock)
	ON_COMMAND(ID_EDIT_NEWCLOCK, OnEditNewclock)
	ON_UPDATE_COMMAND_UI(ID_EDIT_NEWCLOCK, OnUpdateEditNewclock)
	ON_COMMAND(ID_MOIS_CURRENT, OnMoisCurrent)
	ON_UPDATE_COMMAND_UI(ID_MOIS_CURRENT, OnUpdateMoisCurrent)
	ON_COMMAND(ID_VIEW_ALARMSLIST, OnViewAlarmslist)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALARMSLIST, OnUpdateViewAlarmslist)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
    
    ON_CONTROL_RANGE( EN_CHANGE, 0,41, OnEditChanged)
    
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppView construction/destruction

CAppView::CAppView()
{
	// TODO: add construction code here
    m_bBusy = FALSE;
}

CAppView::~CAppView()
{
}

BOOL CAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAppView drawing

void CAppView::OnDraw(CDC* pDC)
{
	CAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CAppView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: calculate the total size of this view
}

/////////////////////////////////////////////////////////////////////////////
// CAppView printing

BOOL CAppView::OnPreparePrinting(CPrintInfo* pInfo)
{   
    // default preparation
    CAppDoc* pDoc = GetDocument();
    pDoc->StoreMonth();
    
    return DoPreparePrinting(pInfo);
}

void CAppView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing

    m_iLen = ((pDC->GetDeviceCaps (HORZRES) ) );
    m_iHei = ((pDC->GetDeviceCaps (VERTRES) ) );

}
          
void CAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAppView diagnostics

#ifdef _DEBUG
void CAppView::AssertValid() const
{
	CView::AssertValid();
}

void CAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAppDoc* CAppView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAppDoc)));
	return (CAppDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAppView message handlers

#define EDITSIZE 90
#define EDITSPACE 8

int CAppView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

    m_bBusy = TRUE;

    CString str;
    int x,y;

    CAppDoc* l_pDoc = GetDocument();

    char *szDays[]=
    {
        "Dim",
        "Lun",
        "Mar",
        "Mer",
        "Jeu",
        "Ven",
        "Sam"
    };

    for (y=0; y<6; y++)
    {       
        for (x=0; x<7; x++)
        {
            CEditEx & edit = l_pDoc->m_arrayEdit[y*7+x];

            CRect rect = CRect(8+ x*EDITSIZE, 50+y*EDITSIZE, 
                (x+1)*EDITSIZE+8, -16+50+(y+1)*EDITSIZE);

            if (!edit.Create(
                ES_MULTILINE|  ES_WANTRETURN | WM_PARENTNOTIFY|
//                ES_AUTOVSCROLL | ES_AUTOHSCROLL |
                ES_LEFT |
                WS_CHILD  | WS_TABSTOP | WS_BORDER |
//                WS_VSCROLL | WS_HSCROLL  |
                WS_CLIPCHILDREN,
                rect,
                this,
                0 //y * 7 + x
                ))
            {
                str.Format("Creating CEditEx control failed\r\n");            
                OutputDebugString(str);
            }

            edit.SetUpdateMsg(WM_USER + 0x98);
            edit.SetId(y * 7 + x);
            edit.SetFont("Arial", 150);
            //edit.SetColor(RGB(0,0,255));
            edit.Initialize();

            l_pDoc->m_arrayStatic[y*7+x].Create
                ("", WS_CHILD,
                CRect(8+ x*EDITSIZE, -16+50+y*EDITSIZE, 
                -16+50+(x)*EDITSIZE+40, 
                50+y*EDITSIZE),
                this, y*7+x  ); 

            l_pDoc->m_arrayStatic[y*7+x].
                SetColor(0xff0000, RGB(255, 255, 0));
        }
    }

    for (x=0; x<7; x++)
    {              
        l_pDoc->m_arrayDaysWeek[x].Create                
            (szDays[x], WS_CHILD| WS_VISIBLE,
            CRect(8+ x*EDITSIZE, 4, 
            -16+50+(x)*EDITSIZE+40, 
            -16+50),
            this, x );     

        l_pDoc->m_arrayDaysWeek[x].SetWindowText(szDays[x]);
    }

    m_bBusy = FALSE;
 
    GotoToday();

    m_nTimer = SetTimer(0x1, 6000, NULL);

	return 0;
}

int CAppView::UpdateToMonth(int iMonth, int iYear)
{
    CAppDoc* m_pDoc = GetDocument();

    int iDay;
    int iBase;
    char szText[50];    
    int x;
    
    CTime _time(iYear, iMonth, 1,0,0,0);
    iDay = _time.GetDay();
    iBase = _time.GetDayOfWeek() -1;

    int iSizeMonth = GetMonthSize(iMonth, iYear);

    for (x=0;x<42;x++)
    {        
        // Hide them...
        if ( (x<iBase) || (x>=(iBase+iSizeMonth)) )      
        {

            if (m_pDoc->m_arrayEdit[x].
                IsWindowVisible())
            {
                m_pDoc->m_arrayStatic[x].ShowWindow(SW_HIDE);
                m_pDoc->m_arrayEdit[x].ShowWindow(SW_HIDE);
            }

        }
        else // Show them
        {

            if (m_pDoc->m_arrayEdit[x].
                IsWindowVisible()==FALSE)
            {
                m_pDoc->m_arrayStatic[x].ShowWindow(SW_SHOW);
                m_pDoc->m_arrayEdit[x].ShowWindow(SW_SHOW);
            }

            wsprintf(szText, "%d", -iBase+x+1);
            m_pDoc->m_arrayStatic[x].SetWindowText(szText);
        }
    }

    SendMessage(WM_PAINT,0,0);
    this->Invalidate(FALSE);
    
    return TRUE;
}

void CAppView::OnMoisBack() 
{
	// TODO: Add your command handler code here

    CAppDoc* m_pDoc = GetDocument();

    m_pDoc->StoreMonth();

    int iYear;
    int iMonth;

    iYear = m_pDoc->m_CurTime.GetYear();
    iMonth = m_pDoc->m_CurTime.GetMonth();

    if (iMonth==1)
    {
        iMonth=12;
        iYear--;
        m_pDoc->m_CurTime = CTime(iYear, iMonth, 1, 0,0,0);
    }
    else
    {
        iMonth--;
        m_pDoc->m_CurTime = CTime(iYear, iMonth, 1, 0,0,0);
    }

    UpdateToMonth(iMonth, iYear);

    m_pDoc->RestoreMonth();
}

void CAppView::OnMoisNext() 
{
	// TODO: Add your command handler code here
    CAppDoc* m_pDoc = GetDocument();

    m_pDoc->StoreMonth();

    int iYear;
    int iMonth;

    iYear = m_pDoc->m_CurTime.GetYear();
    iMonth = m_pDoc->m_CurTime.GetMonth();

    if (iMonth==12)
    {
        iMonth=1;
        iYear++;
        m_pDoc->m_CurTime = CTime(iYear, iMonth, 1, 0,0,0);
    }
    else
    {
        iMonth++;
        m_pDoc->m_CurTime = CTime(iYear, iMonth, 1, 0,0,0);
    }

    UpdateToMonth(iMonth, iYear);

    m_pDoc->RestoreMonth();
    
}

int CAppView::GetMonthSize(int iMonth, int iYear)
{
    int iSizeMonths[]=
    {
        31,28,31,30,31,30,
        31,31,30,31,30,31
    };

    if (!(iYear%4))
	{
        iSizeMonths[1]=29;
	}

    return iSizeMonths[iMonth-1];

}

void CAppView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting     
    
    CAppDoc* m_pDoc = GetDocument();

    char szText[50];
    int iYear;
    int iMonth;

    iYear = m_pDoc->m_CurTime.GetYear();
    iMonth = m_pDoc->m_CurTime.GetMonth();

    int iStatus;
    CFont font;

    CRect rectView;

    GetClientRect(rectView);
    CSize rectSize = rectView.Size();

    int nHeight = rectSize.cx/22;
    if (nHeight<13) nHeight=13;

    iStatus = font.CreateFont (nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH , "Arial");

    dc.SetTextColor(COLOR_WINDOWTEXT);
    dc.SetBkColor(0xffffffff);

    CFont *l_pOldFont = (CFont*) dc.SelectObject(font);

    CString strMonthName = GetMonthName(iMonth);

    wsprintf(szText, "%s %i             ", strMonthName, iYear);

    iStatus= dc.ExtTextOut(8 , 4,
        ETO_CLIPPED, NULL,
        szText, strlen(szText),
        NULL);


	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
}


void CAppView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
    ResizeControls	();
}


void CAppView::ResizeControls()
{
    //left right top bottom

    CRect rectView;
    CAppDoc * m_pDoc = GetDocument();

    GetClientRect(rectView);
    CSize rectSize = rectView.Size();

    int constTopMargin = rectSize.cx/8;
    if (constTopMargin<60) constTopMargin=60;
    if (constTopMargin>80) constTopMargin=80;

    int iBoxHei= -10+( rectSize.cy-constTopMargin) /6;
    int iBoxLen= +(rectSize.cx-8)/7;

    char szText[10];

    for (int y=0; y<6; y++)
    {
        for (int x=0; x<7; x++)
        {
            m_pDoc->m_arrayEdit[y*7+x].
                SetWindowPos(
                    NULL, 
                    8+(iBoxLen)*x,                     
                    constTopMargin+(8+iBoxHei)*y, 
                    iBoxLen, 
                    iBoxHei, 
                    SWP_NOZORDER 
                    );

            wsprintf(szText, "%d", y*7+x);

            m_pDoc->m_arrayStatic[y*7+x].
                SetWindowPos(
                    NULL, 
                    -2+8+(iBoxLen)*x,                     
                    -14+constTopMargin+(8+iBoxHei)*y, 
                    32,                    
                    14, 
                    SWP_NOZORDER 
                    );
        }
    }

    //
    for (int x=0; x<7; x++)
    {
        m_pDoc->m_arrayDaysWeek[x].                                
            SetWindowPos(                    
                NULL, 
                8+(iBoxLen)*x,                     
                -12+constTopMargin-20, 
                32,                    
                14, 
                SWP_NOZORDER 
                );
    }

}

void CAppView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CWnd *pWnd = GetFocus();    
    if (CanDoEdit ()) 
        ((CRichEditCtrl*)pWnd ) ->Copy();
}

void CAppView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable(	CanDoEdit());
	
}

void CAppView::OnEditCut() 
{
	// TODO: Add your command handler code here
	CWnd *pWnd = GetFocus();    
    if (CanDoEdit ()) 
        ((CRichEditCtrl*)pWnd ) ->Cut();
}

void CAppView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable(	CanDoEdit());
	
}

void CAppView::OnEditPaste() 
{
	// TODO: Add your command handler code here
    
	CWnd *pWnd = GetFocus();    
    if (CanDoEdit ()) 
        ((CRichEditCtrl*)pWnd ) ->Paste();
	
}

void CAppView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

    pCmdUI->Enable(	CanDoEdit());
    
}

BOOL CAppView::CanDoEdit ()
{
	CWnd *pWnd = GetFocus();
    CAppDoc *pDoc = GetDocument();
    
    int iCpt;
    int bIsEdit= FALSE;

    if (pWnd==NULL) return FALSE;

    for (iCpt=0; iCpt<42; iCpt++)
        if (pWnd->m_hWnd == pDoc->m_arrayEdit[iCpt].m_hWnd)
            bIsEdit=TRUE;

    return bIsEdit;
}

void CAppView::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This function was added by the Pop-up Menu component

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_APP_VIEW));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}

BOOL CAppView::PreTranslateMessage(MSG* pMsg)
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

	return CView::PreTranslateMessage(pMsg);
}

void CAppView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	CWnd *pWnd = GetFocus();    
    if (CanDoEdit () &&
        ((CRichEditCtrl*)pWnd)->CanUndo() ) 
    {
        ((CRichEditCtrl*)pWnd ) ->Undo();
    }
	
}

void CAppView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if (CanDoEdit())
    {
	    CWnd *pWnd = GetFocus();    
        pCmdUI->Enable(((CRichEditCtrl*)pWnd)->CanUndo());
        
    }    
    else pCmdUI->Enable(FALSE);
	
}

BOOL CAppView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CView::OnNotify(wParam, lParam, pResult);
}




void CAppView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
}


void CAppView::OnEditChanged(UINT nID)
{

    if ( GetDocument()->m_bNoModify)
    {}
    else
    {
        GetDocument()-> SetModifiedFlag( TRUE );      
    } 
}

void CAppView::PrintMonth(CDC *pDC, int iMonth, int iYear)
{

    char *szDays[] = {"Dimanche", "Lundi", "Mardi", "Mercredi",
                      "Jeudi", "Vendredi",
                     "Samedi"};


    CAppDoc * pDoc = GetDocument();

    CString strMonthName = GetMonthName(iMonth);

    CFont font;
    char szText [50];
    
    int nRows =7;

    int nHdFntSize = m_iHei/(nRows*3);
    int nHdHei = nHdFntSize +10*4;

    int nSqrLen = m_iLen / nRows;
    int nSqrHei =(m_iHei - nHdHei ) / nRows;
    int nFntSize;

    if (m_iLen < m_iHei)
        nFntSize = nSqrHei/9;
    else
        nFntSize = nSqrLen/9;


    font.CreateFont (nHdFntSize, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH , "Arial");
    pDC->SelectObject(&font);

    pDC->SetBkMode(TRANSPARENT);

    wsprintf(szText, "%s %i", 
        strMonthName.GetBuffer(49), iYear);

    ::ExtTextOut(pDC->m_hDC,0 , 8,
        ETO_CLIPPED, NULL,
        szText, strlen(szText),
        NULL);

    CTime _time(iYear, iMonth, 1, 0,0,0,0);
    int iBase = _time.GetDayOfWeek() -1;
    int iSizeMonth = GetMonthSize(iMonth, iYear);

    CFont font2;
    font2.CreateFont (nFntSize, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH , "Arial");
    pDC->SelectObject(&font2);

    int iNote = pDoc->FindNote(iYear, iMonth);

    for (int x=0; x<7; x++)
    {
                
        ::ExtTextOut(pDC->m_hDC,
               4+x*nSqrLen,
               nHdHei-(nFntSize)-2,            
               ETO_CLIPPED, NULL,
               szDays[x], strlen(szDays[x]),
               NULL);

    }

    int z=0;
    for (int y=0; y<7; y++)
    {
        for (int x=0; x<7; x++, z++)
        {

            if ( (z<iBase) || (z>=(iBase+iSizeMonth)) )      
            {}
            else
            {
                pDC->Rectangle(CRect(x*nSqrLen,
                             nHdHei+y*nSqrHei, 
                             (x+1)*nSqrLen,
                             nHdHei+(y+1)*nSqrHei)
                             );

                wsprintf(szText, "%i", 
                    z-iBase+1);
            
                ::ExtTextOut(pDC->m_hDC,
                    4+x*nSqrLen,
                    nHdHei+y*(nSqrHei),            
                    ETO_CLIPPED, NULL,
                    szText, strlen(szText),
                    NULL);

                if (iNote==-1)
                {}
                else

            
            pDC->DrawText
            (((CNote*)(pDoc->m_arrayNotes[iNote]))->
                      m_strNotes[y*7+x], 
                    CRect(4+x*nSqrLen,
                          nHdHei+y*nSqrHei+ nFntSize,            
                          -2+(x+1)*nSqrLen-2,
                          nHdHei+(y+1)*nSqrHei-2),            
                          DT_WORDBREAK);
                    
            }

        }
    
    }
               
}

CString CAppView::GetMonthName(int iMonth)
{
    char *szMonths[]=
    {
        "Janvier",
        "Février",
        "Mars",
        "Avril",
        "Mai",        
        "Juin",
        
        "Juillet",
        "Août",
        "Septembre",
        "Octobre",
        "Novembre",
        "Décembre"            
    };

    return CString(szMonths[iMonth-1]);
}

void CAppView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class

    CAppDoc *pDoc = GetDocument();

    PrintMonth(pDC, pDoc->m_CurTime.GetMonth(), 
        pDoc->m_CurTime.GetYear()); 

	CView::OnPrint(pDC, pInfo);
}


void CAppView::OnProperties()
{
	// TODO: The property sheet attached to your project
	// via this function is not hooked up to any message
	// handler.  In order to actually use the property sheet,
	// you will need to associate this function with a control
	// in your project such as a menu item or tool bar button.

}

BOOL CAppView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CView::OnCommand(wParam, lParam);
}


void CAppView::OnMoisMemo() 
{
	// TODO: Add your command handler code here

    CMemoDialog dialog;
    CAppDoc * pDoc = GetDocument();

    CNote *l_pNote;

    int iYear = pDoc->m_CurTime.GetYear();
    int iMonth = pDoc->m_CurTime.GetMonth();

    int iIndex = pDoc->FindNote(iYear, iMonth);
    if (iIndex==-1)
    {
        l_pNote = new CNote;
        l_pNote->m_iMonth =  iMonth;
        l_pNote->m_iYear  =  iYear;
        iIndex = (pDoc->m_arrayNotes).Add (l_pNote);         

    }
    else 
        l_pNote = (CNote *)pDoc->m_arrayNotes[iIndex];

    dialog.m_strCaption.Format("Mémo du mois de %s %d",
        GetMonthName(pDoc->m_CurTime.GetMonth()), 
        pDoc->m_CurTime.GetYear());
    
    dialog.m_strMemo = l_pNote->m_strMemo;
    if (dialog.DoModal()==IDOK)
    {
        if (l_pNote->m_strMemo!= dialog.m_strMemo)
            GetDocument()-> SetModifiedFlag( TRUE );      
        l_pNote->m_strMemo= dialog.m_strMemo;
    };

}

void CAppView::OnUpdateMoisMemo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CAppView::OnMoisClock() 
{
	// TODO: Add your command handler code here
}

void CAppView::OnUpdateMoisClock(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CAppView::OnEditNewclock() 
{
    NewClock();	
}

void CAppView::OnUpdateEditNewclock(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CAppView::GotoToday()
{
    int iMonth;
    int iYear;

    CAppDoc *l_pDoc = GetDocument();
    l_pDoc->m_CurTime = CTime::GetCurrentTime();

    iYear = l_pDoc->m_CurTime.GetYear();
    iMonth = l_pDoc->m_CurTime.GetMonth();

    UpdateToMonth(iMonth, iYear);
    l_pDoc->RestoreMonth();
}

void CAppView::OnMoisCurrent() 
{
	// TODO: Add your command handler code here
    CAppDoc *l_pDoc = GetDocument();
    l_pDoc->StoreMonth();

    if ((l_pDoc->m_CurTime.GetYear()!=CTime::GetCurrentTime().GetYear())
        | (l_pDoc->m_CurTime.GetMonth()!=CTime::GetCurrentTime().GetMonth()))
        GotoToday();
	
}

void CAppView::OnUpdateMoisCurrent(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CAppView::OnViewAlarmslist() 
{
	// TODO: Add your command handler code here

    CAppDoc *l_pDoc = GetDocument();

    l_pDoc->TrierAlarms();

    if ( (l_pDoc->m_arrayAlarms.GetSize()) && 
           
            ((((CAlarmNode*)(l_pDoc->m_arrayAlarms[0]))->m_timeRing < 
            CTime::GetCurrentTime())) )
    {
        
        int iStatus =  AfxMessageBox( "Certaines alarmes ont expirées.\nVoulez-vous les supprimer?", 
                        MB_YESNO);

        if (iStatus == IDYES)
        {
            l_pDoc->m_nCritical = TRUE;
            while ((l_pDoc->m_arrayAlarms.GetSize()) && 
                   ((((CAlarmNode*)(l_pDoc->m_arrayAlarms[0]))->m_timeRing < 
                    CTime::GetCurrentTime())))
            {
            
                delete l_pDoc->m_arrayAlarms[0];
                l_pDoc->m_arrayAlarms.RemoveAt(0);  
                l_pDoc->SetModifiedFlag( TRUE )  ;
            }

            l_pDoc->m_nCritical = FALSE;
        }
    
    }
    
    
    CAlarmsListDialog dialog;

    dialog.m_pView = this;
    dialog.m_pDoc = this->GetDocument();

    dialog.DoModal();    

    GetDocument()->TrierAlarms();

}

void CAppView::OnUpdateViewAlarmslist(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

CAlarmNode * CAppView::NewClock()
{
	// TODO: Add your command handler code here
    CClockDialog dialog;
    CAppDoc * pDoc = GetDocument();

    CNote *l_pNote;

    int iYear = pDoc->m_CurTime.GetYear();
    int iMonth = pDoc->m_CurTime.GetMonth();

    int iIndex = pDoc->FindNote(iYear, iMonth);
    if (iIndex==-1)
    {
        l_pNote = new CNote;
        l_pNote->m_iMonth =  iMonth;
        l_pNote->m_iYear  =  iYear;
        iIndex = (pDoc->m_arrayNotes).Add (l_pNote);         
    }
    else 
        l_pNote = (CNote *)pDoc->m_arrayNotes[iIndex];

    dialog.m_strCaption = "Nouvelle alarme...";
    dialog.m_pView = this;
    dialog.m_pDoc = GetDocument();

    CTime l_TodayTime = CTime::GetCurrentTime();
    CTime l_RefTime;

    if (l_TodayTime < pDoc->m_CurTime)
        l_RefTime =   pDoc->m_CurTime;
    else
        l_RefTime = l_TodayTime;

    dialog.m_nYear = l_RefTime.GetYear();
    dialog.m_nMonth = l_RefTime.GetMonth();
    dialog.m_nDay = l_RefTime.GetDay();

    dialog.m_nHour = l_RefTime.GetHour();
    dialog.m_nMin =  5*(l_RefTime.GetMinute()/5);

    int nStatus = dialog.DoModal();
    if (nStatus==IDOK)
    {

        CAlarmNode *l_pAlarmNode = new CAlarmNode;
        l_pAlarmNode->m_timeRing = 
            CTime::CTime(dialog.m_nYear,
                         dialog.m_nMonth,
                         dialog.m_nDay,
                         dialog.m_nHour,
                         dialog.m_nMin,
                         0);

        l_pAlarmNode->m_strInfo = dialog.m_strInfo;
        l_pAlarmNode->m_strSound = dialog.m_strSound;

        pDoc->m_arrayAlarms.Add( (CObject*)l_pAlarmNode);
        return l_pAlarmNode;
    }
    else
        return NULL;


}



void CAppView::OnDestroy() 
{
	CView::OnDestroy();
    KillTimer(m_nTimer);
	
	// TODO: Add your message handler code here
	
}

void CAppView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

    static CTime l_PrevTime (1980, 1,1,0,0,0);
    static l_bCritical = FALSE;

    CAppDoc *l_pDoc = GetDocument();

    // Critical section / disable no exec.
    if  ( (l_bCritical == TRUE)  ||
          (l_pDoc->m_nCritical==TRUE)  )
    {
        CView::OnTimer(nIDEvent);    
        return  ;
    }

    l_bCritical = TRUE;

    CTime l_CurTime;  
    l_CurTime = CTime::GetCurrentTime();

    l_CurTime = CTime::CTime
        (l_CurTime.GetYear(),
         l_CurTime.GetMonth(),
         l_CurTime.GetDay(),
         l_CurTime.GetHour(),
         l_CurTime.GetMinute(),
             0);

    CAlarmNode *l_pAlarmNode;
    int l_nCpt;

    if (l_CurTime!=l_PrevTime)
    {

        l_PrevTime = l_CurTime;

        for (l_nCpt=0; l_nCpt< l_pDoc-> m_arrayAlarms.GetSize(); l_nCpt++)
        {
            l_pAlarmNode = (CAlarmNode *)l_pDoc->m_arrayAlarms[l_nCpt] ;

            if ( (l_pAlarmNode->m_nDeleted==FALSE) &&
                (l_CurTime== l_pAlarmNode->m_timeRing) )
            {
                CBipBox dialog;
                
                dialog.m_strInfo = l_pAlarmNode->m_strInfo;

                CString l_strSound = l_pAlarmNode->m_strSound;
                l_strSound.MakeLower( );

                if(l_strSound.Find(".mid")==-1)
                {
                    PlaySound(l_pAlarmNode->m_strSound, NULL, 
                        SND_ASYNC | SND_FILENAME | SND_NOWAIT); 
                    dialog.DoModal();
                }
                else
                {
                    PlayMidi(l_pAlarmNode->m_strSound.GetBuffer(512));
                    dialog.DoModal();
                    StopMidi();
                }


                break;
            }
        
        }
        
    
    }

    l_bCritical = FALSE;

	CView::OnTimer(nIDEvent);
}


BOOL CAppView::PlayMidi(char *szFilename)
{
    char buf[1024];

    sprintf(buf, "open %s type sequencer alias MUSIC", szFilename);
    
    if (mciSendString("close all", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    if (mciSendString(buf, NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    if (mciSendString("play MUSIC from 0", NULL, 0, this->m_hWnd) != 0)
    {
	return(FALSE);
    }
    
    // Yahoo!
    return TRUE;
}



BOOL CAppView::StopMidi()
{
    if (mciSendString("close all", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }	

    // Yahoo!
    return TRUE;
}

LRESULT CAppView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

    switch(message)
    {
        case WM_USER+0x98:
            if (!m_bBusy && !GetDocument()->IsUpdated())
            {
                GetDocument()-> SetModifiedFlag( TRUE );      
                CString str;
                str.Format("modified %d\r\n", wParam);
                OutputDebugString(str);
            }
        break;
    }

	return CView::WindowProc(message, wParam, lParam);
}
