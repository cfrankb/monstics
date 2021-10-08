// ReptelView.cpp : implementation of the CReptelView class
//

#include "stdafx.h"
#include "resource.h"
//#include "MiniApp Reptel.h"

#include "ReptelDoc.h"
#include "ReptelView.h"
#include "EntryDlg.h"

#include "Entry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReptelView

IMPLEMENT_DYNCREATE(CReptelView, CListView)

BEGIN_MESSAGE_MAP(CReptelView, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CReptelView)
	ON_WM_CREATE()
	ON_COMMAND(ID_AFFICHAGE_DETAIL, OnAffichageDetail)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_DETAIL, OnUpdateAffichageDetail)
	ON_COMMAND(ID_AFFICHAGE_GRANDESICONES, OnAffichageGrandesicones)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_GRANDESICONES, OnUpdateAffichageGrandesicones)
	ON_COMMAND(ID_AFFICHAGE_LISTES, OnAffichageListes)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_LISTES, OnUpdateAffichageListes)
	ON_COMMAND(ID_AFFICHAGE_PETITESICONES, OnAffichagePetitesicones)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_PETITESICONES, OnUpdateAffichagePetitesicones)
	ON_COMMAND(ID_EDIT_PROPS, OnEditProps)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PROPS, OnUpdateEditProps)
	ON_COMMAND(ID_EDITION_INSERER, OnEditionInserer)
	ON_UPDATE_COMMAND_UI(ID_EDITION_INSERER, OnUpdateEditionInserer)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReptelView construction/destruction

CReptelView::CReptelView()
{
	// TODO: add construction code here
}

CReptelView::~CReptelView()
{
}

BOOL CReptelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CReptelView drawing

void CReptelView::OnDraw(CDC* pDC)
{
	CReptelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CReptelView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CReptelView printing

BOOL CReptelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReptelView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CReptelView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CReptelView diagnostics

#ifdef _DEBUG
void CReptelView::AssertValid() const
{
	CListView::AssertValid();
}

void CReptelView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CReptelDoc* CReptelView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReptelDoc)));
	return (CReptelDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReptelView message handlers

int CReptelView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
    
    GetDocument()->m_arrEntry.SetSize(0,10);
    GetDocument()->m_nEntry=0;  
    
    int nColumns;

	HICON hIcon;
	LV_COLUMN lvC;      		// list view column structure

    char *szColumns [] =
    { "Nom", "Téléphone", "Adresse", "Autre information", NULL  };

	// The listview control already created
	//this->GetListCtrl();       

	// create the large icon image list.
	GetDocument()->m_ImageLarge.Create(32,
		32,
		TRUE,			// list does include masks
		0,              // Default size is zero
		1 );			// list will be growing


	// Load the default icon and add it to the image lists.
		hIcon = ::LoadIcon (AfxGetResourceHandle(),
            MAKEINTRESOURCE(IDI_ICON0));
		GetDocument()->m_ImageLarge.Add(hIcon);
	
	// Be sure that all of large icons were added.
	if (GetDocument()->m_ImageLarge.GetImageCount() < 1)
		return NULL;

	// Associate the image lists with the list view control.
	this->GetListCtrl().SetImageList(
        &(GetDocument()->m_ImageLarge), LVSIL_SMALL);
    this->GetListCtrl().SetImageList(
        &(GetDocument()->m_ImageLarge), LVSIL_NORMAL);

	// Now initialize the columns you will need.
	// Initialize the LV_COLUMN structure.
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align column
	lvC.cx = 75;            // width of column in pixels

	// Add the columns.
	for (nColumns = 0; szColumns[nColumns]; nColumns++)
	{
		lvC.iSubItem = nColumns;
		lvC.pszText = szColumns[nColumns];
		
		if (this->GetListCtrl().InsertColumn(nColumns, &lvC) == -1)
			return NULL;
	}


    CWnd *l_WndTest = this;
    CWnd *l_WndList = this->GetListCtrl().GetParent();

    // Set reportview by default

	DWORD dwStyle;

	dwStyle = GetWindowLong(this->GetListCtrl().m_hWnd,
        GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_REPORT)
		SetWindowLong(this->GetListCtrl().m_hWnd, 
        GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);

    CWinApp* pApp = AfxGetApp();

    GetListCtrl().SetColumnWidth(0, pApp->GetProfileInt  ("ListView", "Col0", 75));
    GetListCtrl().SetColumnWidth(1, pApp->GetProfileInt  ("ListView", "Col1", 75));
    GetListCtrl().SetColumnWidth(2, pApp->GetProfileInt  ("ListView", "Col2", 75));
    GetListCtrl().SetColumnWidth(3, pApp->GetProfileInt  ("ListView", "Col3", 75));


	return 0;
}

void CReptelView::OnAffichageDetail() 
{
	// TODO: Add your command handler code here
	DWORD dwStyle;
	
	dwStyle = GetWindowLong(this->GetListCtrl().m_hWnd, 
        GWL_STYLE);
    BOOL bIsDetail =(dwStyle & LVS_TYPEMASK) 
        == LVS_REPORT;

	if (!bIsDetail)
		SetWindowLong(this->GetListCtrl().m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);

    ArrangeListView(0);
}

void CReptelView::OnUpdateAffichageDetail(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	DWORD dwStyle;

	dwStyle = GetWindowLong(this->GetListCtrl().m_hWnd, 
        GWL_STYLE);
		
    BOOL bIsDetail =(dwStyle & LVS_TYPEMASK) 
        == LVS_REPORT;

    pCmdUI->SetRadio((bIsDetail)
        ? 1 : 0);	
	
}


void CReptelView::OnAffichageGrandesicones() 
{
	// TODO: Add your command handler code here
	DWORD dwStyle;
	
	dwStyle = GetWindowLong(this->GetListCtrl().m_hWnd, 
        GWL_STYLE);
    BOOL bIsIcon =(dwStyle & LVS_TYPEMASK) 
        == LVS_ICON;

	if (!bIsIcon)
		SetWindowLong(this->GetListCtrl().m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_ICON);
    ArrangeListView(0);
	
}

void CReptelView::OnUpdateAffichageGrandesicones(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	DWORD dwStyle;

	dwStyle = GetWindowLong(this->GetListCtrl().m_hWnd, 
        GWL_STYLE);
		
    BOOL bIsIcon =(dwStyle & LVS_TYPEMASK) 
        == LVS_ICON;

    pCmdUI->SetRadio((bIsIcon)
        ? 1 : 0);	
	
}

void CReptelView::OnAffichageListes() 
{
	// TODO: Add your command handler code here
	DWORD dwStyle;
	
	dwStyle = GetWindowLong(this->GetListCtrl().m_hWnd, GWL_STYLE);
    BOOL bIsList =(dwStyle & LVS_TYPEMASK) 
        == LVS_LIST;

	if (!bIsList)
		SetWindowLong(this->GetListCtrl().m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_LIST);
	
    ArrangeListView(0);
}

void CReptelView::OnUpdateAffichageListes(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	DWORD dwStyle;

	dwStyle = GetWindowLong(this->GetListCtrl().m_hWnd, 
        GWL_STYLE);
		
    BOOL bIsList =(dwStyle & LVS_TYPEMASK) 
        == LVS_LIST;

    pCmdUI->SetRadio((bIsList)
        ? 1 : 0);	
	
}


// Handles ListView SmallIcons
void CReptelView::OnAffichagePetitesicones() 
{
	// TODO: Add your command handler code here
	DWORD dwStyle;
	
	dwStyle = GetWindowLong(this->GetListCtrl().m_hWnd, GWL_STYLE);
    BOOL bIsSmallIcon =(dwStyle & LVS_TYPEMASK) 
        == LVS_SMALLICON;

	if (!bIsSmallIcon)
		SetWindowLong(this->GetListCtrl().m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_SMALLICON);
    ArrangeListView(0);
}

void CReptelView::OnUpdateAffichagePetitesicones(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	DWORD dwStyle;

	dwStyle = GetWindowLong(this->GetListCtrl().m_hWnd, 
        GWL_STYLE);
		
    BOOL bIsSmallIcon =(dwStyle & LVS_TYPEMASK) 
        == LVS_SMALLICON;

    pCmdUI->SetRadio((bIsSmallIcon)
        ? 1 : 0);	
}

void CReptelView::OnEditProps() 
{
	// TODO: Add your command handler code here
    CEntryDlg l_Dlg;

    int l_nImage;
    int l_nIndex = GetSelItemIndex();

    LV_ITEM l_lvItem;
    l_lvItem.mask = LVIF_IMAGE;
    l_lvItem.iItem = l_nIndex;
    l_lvItem.iSubItem = 0;

    this->GetListCtrl().GetItem(&l_lvItem); 

    l_nImage = l_lvItem.iImage;

    GetItem(&l_nImage, 
        &l_Dlg.m_szName,                          
        &l_Dlg.m_szTel,
        &l_Dlg.m_szAddr,
        &l_Dlg.m_szInfo,
        l_nIndex) ;

    l_Dlg.m_nImage = l_nImage;
    l_Dlg.m_hIcon = this->GetListCtrl().GetImageList(LVSIL_NORMAL)
        ->ExtractIcon( l_nImage );        
    HICON l_hIcon = l_Dlg.m_hIcon;

    int iStatus= l_Dlg.DoModal();

    if (iStatus==IDOK)
    {
        if (l_hIcon != l_Dlg.m_hIcon)
        {
            l_hIcon = l_Dlg.m_hIcon ;
            if (l_nImage==0)
            {
            
                l_nImage = (this->GetListCtrl()                
                    .GetImageList(LVSIL_NORMAL)            
                        -> Add(l_hIcon));
                l_nImage = (this->GetListCtrl()
                    .GetImageList(LVSIL_SMALL)
                        -> Add(l_hIcon));

            }
            else
            {
                (this->GetListCtrl()                
                    .GetImageList(LVSIL_NORMAL)            
                        -> Replace(l_nImage,l_hIcon));
                (this->GetListCtrl()
                    .GetImageList(LVSIL_SMALL)
                        -> Replace(l_nImage,l_hIcon));
            }
        }

        SaveItem(l_nImage,  
            l_Dlg.m_szName,                          
            l_Dlg.m_szTel,
            l_Dlg.m_szAddr,
            l_Dlg.m_szInfo,
            l_nIndex) ;
    }
    
}

void CReptelView::OnUpdateEditProps(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
        if (GetSelItemIndex()<0)  
           pCmdUI->Enable( FALSE);
        else 
            pCmdUI->Enable(TRUE);

}


void CReptelView::OnEditionInserer() 
{
	// TODO: Add your command handler code here
    CEntryDlg l_Dlg;

    int l_nImage =0;

    l_Dlg.m_nImage = l_nImage;
    l_Dlg.m_hIcon = this->GetListCtrl().GetImageList(LVSIL_NORMAL)
        ->ExtractIcon( l_nImage );        
    HICON l_hIcon = l_Dlg.m_hIcon;

    int iStatus= l_Dlg.DoModal();
    if (iStatus == IDOK)
    {
        if (l_hIcon != l_Dlg.m_hIcon)
        {
            l_hIcon = l_Dlg.m_hIcon ;
            l_nImage = (this->GetListCtrl().GetImageList(LVSIL_NORMAL)
            -> Add(l_hIcon));
            l_nImage = (this->GetListCtrl().GetImageList(LVSIL_SMALL)
            -> Add(l_hIcon));
        }
           
        AddItem(l_nImage, 
               l_Dlg.m_szName ,
               l_Dlg.m_szTel,
               l_Dlg.m_szAddr,
               l_Dlg.m_szInfo);
    }


    this->GetListCtrl().EnsureVisible( this->GetListCtrl().GetItemCount()-1 
        , FALSE );

}

void CReptelView::OnUpdateEditionInserer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CReptelView::DoDataExchange(CDataExchange* pDX) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListView::DoDataExchange(pDX);
}

void CReptelView::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This function was added by the Pop-up Menu component

	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_REPTEL_VIEW));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}

BOOL CReptelView::PreTranslateMessage(MSG* pMsg)
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


void CReptelView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

    unsigned int l_nflags = LVHT_ONITEM;

    int l_nIndex = this->GetListCtrl().
        HitTest(point, &l_nflags);

    if (l_nIndex>=0)
    {
        if (GetSelItemIndex()>=0)
            OnEditProps();
    }
    else
    {
        OnEditionInserer();
    }


	CListView::OnLButtonDblClk(nFlags, point);
}

int CReptelView::GetSelItemIndex()
{

    int l_nItems = this->GetListCtrl().GetItemCount();
    if (l_nItems==0) return -1;

    LV_ITEM l_lvItem;
    char l_szText[256];

    l_lvItem.mask = LVIF_STATE;
    l_lvItem.iSubItem = 0;
    l_lvItem.pszText = l_szText;
    l_lvItem.cchTextMax =1;
    l_lvItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;

    int l_nSelItemIndex =-1;

    for (int l_nIndex=0; l_nIndex < l_nItems; l_nIndex++)
    {
    
        l_lvItem.iItem = l_nIndex;
        if (this->GetListCtrl().GetItem(&l_lvItem)==FALSE)
            return -1;

        if (l_lvItem.state)
            if (l_nSelItemIndex!=-1) return -2;
            else l_nSelItemIndex = l_nIndex;

    }

    return l_nSelItemIndex;


}


void CReptelView::OnEditDelete() 
{
	// TODO: Add your command handler code here
    int l_nIndex;
    CReptelDoc* l_pDoc = GetDocument();
    
    while (Get1stSelected()!=-1)  
    {

        l_nIndex = Get1stSelected();
        //((CEntry*) l_pDoc->m_arrEntry[l_nIndex])->m_nDeleted = TRUE;
        CEntry* l_pEntry = 
            (CEntry*) this->GetListCtrl().GetItemData(l_nIndex) ;       
        l_pEntry->m_nDeleted = TRUE;

        GetListCtrl(). DeleteItem( l_nIndex );


    } 
	
}

void CReptelView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
        if (GetSelItemIndex()==-1)  
           pCmdUI->Enable( FALSE);
        else 
            pCmdUI->Enable(TRUE);
	
}


void CReptelView::SyncItemArray(int p_nIndex)
{

    int l_nImage;
    CString l_strName;
    CString l_strPhone;
    CString l_strAddr;
    CString l_strNote;

    CEntry* l_pEntry = 
        (CEntry*) this->GetListCtrl().GetItemData(p_nIndex) ;       

    if (l_pEntry==NULL) return;

    GetItem(&l_nImage, 
        &l_strName,
        &l_strPhone,
        &l_strAddr,
        &l_strNote,
        p_nIndex);

    l_pEntry->m_nImage =  l_nImage;
    l_pEntry->m_strAddr =  l_strAddr;
    l_pEntry->m_strInfo =  l_strNote;
    l_pEntry->m_strName =  l_strName;
    l_pEntry->m_strTel =  l_strPhone;

}


BOOL CReptelView::AddItem(int p_nImage,
                        CString p_StrName, 
                        CString p_StrPhone, 
                        CString p_StrAddr,  
                        CString p_StrNote)
{
    // TODO: Keep-up the good work.

    // CListCtrl

    CEntry* l_pEntry = new CEntry(GetDocument()->m_nEntry);

    GetDocument()->m_arrEntry.
        Add(l_pEntry);
  
	LV_ITEM lvI;        		// list view item structure
    
    lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	lvI.state = 0;      
	lvI.stateMask = 0;  

    lvI.iItem = this->GetListCtrl().GetItemCount() ;

	lvI.iSubItem = 0;

	lvI.pszText = p_StrName.GetBuffer(256);
	lvI.cchTextMax = 256;
	lvI.iImage = p_nImage;
	lvI.lParam = (unsigned int) l_pEntry;//GetDocument()->m_nEntry; 
    
    GetDocument()->m_nEntry= GetDocument()->m_nEntry++;

    int l_nIndex = this->GetListCtrl().InsertItem(&lvI);
    if (l_nIndex == -1)
		return FALSE;

	this->GetListCtrl().SetItemText( l_nIndex,
			1, p_StrPhone.GetBuffer(256));

	this->GetListCtrl().SetItemText( l_nIndex,
			2, p_StrAddr.GetBuffer(256));

	this->GetListCtrl().SetItemText( l_nIndex,
			3, p_StrNote.GetBuffer(4096));


    SyncItemArray(l_nIndex);

    return TRUE;
}



BOOL CReptelView::GetItem(int *p_pnImage, 
                          CString *p_pStrName,
                          CString *p_pStrPhone, 
                          CString *p_pStrAddr,
                          CString *p_pStrNote,
                          int p_nIndex)
{
    // TODO: Work things out

	LV_ITEM lvI;        		// list view item structure
    
    lvI.mask =  LVIF_IMAGE ;
    lvI.iSubItem =0;
	lvI.iItem = p_nIndex;
    this->GetListCtrl().GetItem( &lvI);

	*p_pStrName = this->GetListCtrl().GetItemText( p_nIndex,0);
	*p_pStrPhone = this->GetListCtrl().GetItemText( p_nIndex,1);
	*p_pStrAddr = this->GetListCtrl().GetItemText( p_nIndex,2);
	*p_pStrNote = this->GetListCtrl().GetItemText( p_nIndex,3);
    *p_pnImage =  lvI.iImage;
    return TRUE;

}

BOOL CReptelView::SaveItem(int p_nImage, 
                          CString p_StrName,
                          CString p_StrPhone, 
                          CString p_StrAddr,
                          CString p_StrNote,
                          int p_nIndex)
{
    // TODO: Get Gabrielle to keep her mind

	LV_ITEM lvI;        		// list view item structure
    
    lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvI.state = 0;      
	lvI.stateMask = 0;  

    lvI.iItem = p_nIndex ;
	lvI.iSubItem = 0;  
    lvI.iImage = p_nImage;
    
    lvI.pszText = p_StrName.GetBuffer(256);
	lvI.cchTextMax = 256;

    if (this->GetListCtrl().SetItem(&lvI)==FALSE) return FALSE;

    this->GetListCtrl().SetItemText( p_nIndex, 1, p_StrPhone.GetBuffer(256) );
    this->GetListCtrl().SetItemText( p_nIndex, 2, p_StrAddr.GetBuffer(256) );
    this->GetListCtrl().SetItemText( p_nIndex, 3, p_StrNote.GetBuffer(4096) );

    SyncItemArray(p_nIndex);

    return TRUE;



}

void CReptelView::ArrangeListView(int p_nHow)
{

    this->GetListCtrl().
        Arrange(LVA_ALIGNLEFT |LVA_ALIGNTOP|LVA_SNAPTOGRID);
    

}

void CReptelView::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);	
    ArrangeListView(0);
	
}


void CReptelView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}


int CReptelView::Get1stSelected()
{
    int l_nItems = this->GetListCtrl().GetItemCount();
    if (l_nItems==0) return -1;

    LV_ITEM l_lvItem;
    char l_szText[256];

    l_lvItem.mask = LVIF_STATE;
    l_lvItem.iSubItem = 0;
    l_lvItem.pszText = l_szText;
    l_lvItem.cchTextMax =1;
    l_lvItem.stateMask = LVIS_SELECTED ;
    
    for (int l_nIndex=0; l_nIndex < l_nItems; l_nIndex++)
    {
    
        l_lvItem.iItem = l_nIndex;
        if (this->GetListCtrl().GetItem(&l_lvItem)==FALSE)
            return -1;

        if (l_lvItem.state)
            return l_nIndex;

    }

    return -1;


}

void CReptelView::OnDestroy() 
{

	// TODO: Add your message handler code here   
	DWORD dwStyle;
	
	dwStyle = GetWindowLong(this->GetListCtrl().m_hWnd, 
        GWL_STYLE);
    BOOL bIsDetail =(dwStyle & LVS_TYPEMASK) 
        == LVS_REPORT;

	if (!bIsDetail)
		SetWindowLong(this->GetListCtrl().m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);


    CWinApp* pApp = AfxGetApp();

    pApp ->WriteProfileInt("ListView", "Col0", GetListCtrl().GetColumnWidth(0 ));
    pApp ->WriteProfileInt("ListView", "Col1", GetListCtrl().GetColumnWidth(1 ));
    pApp ->WriteProfileInt("ListView", "Col2", GetListCtrl().GetColumnWidth(2 ));
    pApp ->WriteProfileInt("ListView", "Col3", GetListCtrl().GetColumnWidth(3 ));

	CListView::OnDestroy();

}

