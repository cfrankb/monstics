// IconWnd.cpp : implementation file
//

#include "stdafx.h"
#include "progman32.h"
#include "IconWnd.h"
#include "dlgnewprog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIconWnd

CIconWnd::CIconWnd()
{
}

CIconWnd::~CIconWnd()
{
}


BEGIN_MESSAGE_MAP(CIconWnd, CWnd)
	//{{AFX_MSG_MAP(CIconWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_SETFOCUS()
	ON_WM_DROPFILES()
	ON_COMMAND(IDM_CREATE_NEW, OnCreateNew)
	ON_UPDATE_COMMAND_UI(IDM_CREATE_NEW, OnUpdateCreateNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#ifndef LVM_SETEXTENDEDLISTVIEWSTYLE
#define LVM_SETEXTENDEDLISTVIEWSTYLE (LVM_FIRST + 54)
#define LVS_EX_GRIDLINES        0x00000001
#define LVS_EX_CHECKBOXES       0x00000004
#define LVS_EX_TRACKSELECT      0x00000008
#define LVS_EX_HEADERDRAGDROP   0x00000010
#define LVS_EX_FULLROWSELECT    0x00000020 // applies to report mode only
#endif

/////////////////////////////////////////////////////////////////////////////
// CIconWnd message handlers

BOOL CIconWnd::CreateList()
{
    // add some cool effects

    m_listview.SendMessage(
            LVM_SETEXTENDEDLISTVIEWSTYLE,
            0,
            LVS_EX_FULLROWSELECT | 
            LVS_EX_GRIDLINES               
            );

    m_listview.ShowWindow(SW_SHOW);
	CListCtrl & list = m_listview.GetListCtrl();

	CRect rect;
	GetClientRect(&rect);
   
    if (list.Create(
        LVS_AUTOARRANGE | LVS_ICON | LVS_SINGLESEL, 
        rect,
        this,
        1))
    {

        list.ShowWindow(SW_SHOW);
        list.SetBkColor(RGB(128,255, 128));

        int i;

	    HICON hIcon;
	    LV_COLUMN lvC;      		// list view column structure

        char *arrHeaders [] =
        { "show", 
	      NULL  };

        int arrWidth[] =
        {
            100,
            64,
            0
        };

        int arrAlignment[]=
        {
            LVCFMT_LEFT,
            LVCFMT_LEFT,
            0
        };

	    // Create the small icon image list.
	    m_imageList.Create(
		    32,
		    32,
		    TRUE,			// list does include masks
		    0,              // Default size is zero
		    1 );			// list will be growing


	    // Load the default icon and add it to the image lists.
	    hIcon = ::LoadIcon (AfxGetResourceHandle(),
               MAKEINTRESOURCE(IDI_ICON1));
	    m_imageList.Add(hIcon);
	    
	    // Be sure that all of large icons were added.
	    if (m_imageList.GetImageCount() < 1)
		    return FALSE;

	    // Associate the image lists with the list view control.
        list.SetImageList(&m_imageList,  LVSIL_NORMAL);

	    // Now initialize the columns you will need.
	    // Initialize the LV_COLUMN structure.
	    lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	    //lvC.cx = 124;            // width of column in pixels
   
	    // Add the columns.
	    for (i = 0; arrHeaders[i]; i++)
	    {
		    lvC.iSubItem = i;
		    lvC.pszText = arrHeaders[i];
            lvC.cx = arrWidth[i];
    	    lvC.fmt = arrAlignment[i];  // left-align column
		    
		    if (list.InsertColumn(i, &lvC) == -1)
			    return FALSE;;
	    }   

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int CIconWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

    DragAcceptFiles(TRUE);

    if (CreateList())
    {
        OutputDebugString("Listview created\r\n");        
    }

    Invalidate();

	return 0;
}

void CIconWnd::AddItem(AA_ITEM & item)
{
    ManageItem(item, m_arrItems.GetSize(), TRUE, TRUE);
    m_arrItems.Add(item);
}

int CIconWnd::ManageItem(AA_ITEM & item, int i, BOOL bSelected, BOOL bInsert)
{
	CListCtrl & list = m_listview.GetListCtrl();

	LV_ITEM lvI;        		// list view item structure
   
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	if (bSelected)
    {
		lvI.state = LVIS_FOCUSED | LVIS_SELECTED ;      
    }
	else
    {
		lvI.state = 0;
    }

    lvI.stateMask = LVIS_FOCUSED | LVIS_SELECTED ;      
	lvI.iSubItem = 0;
	lvI.pszText = item.m_strContent.GetBuffer(1);
	lvI.cchTextMax = 64;
	lvI.iImage = 0;
	lvI.lParam = item.m_nId;
	lvI.iItem = i; 

    // insert an item
    if (bInsert)
    {
	    i = list.InsertItem(&lvI);
    }
    // update an item
    else
    {
        list.SetItem(&lvI);
    }

  	if (i != -1)
    {	
	   //list.SetItemText( i, 1, item.m_strContent);
       //list.SetItemText( i, 2, item.m_szText2);
       //list.SetItemText( i, 3, item.m_szText3);
       //list.SetItemText( i, 4, item.m_szText4);
    }
    else
    {
        OutputDebugString("index is -1\r\n");
    }

    return i;

}

void CIconWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
    CRect rect;
	GetWindowRect(&rect);

    /*
	if (m_pTable)
	{
		m_pTable->SetWndSize(1+rect.right-rect.left,
			1+rect.bottom-rect.top);
	}
    */

	GetClientRect(&rect);
	m_listview.MoveWindow(0,0, 1+rect.right, 1+rect.bottom);
	
}

void CIconWnd::OnMove(int x, int y) 
{
	CWnd::OnMove(x, y);
	
	// TODO: Add your message handler code here

	CRect rectThis;
	this->GetWindowRect(&rectThis);

	CWnd *pParent = GetParent();
	CRect rectParent;
	pParent->GetWindowRect(&rectParent);

	int nX = rectThis.left - rectParent.left;
	int nY = rectThis.top - rectParent.top;

    /*
	if (m_pTable)
	{
		m_pTable->SetWndXY(nX,nY);
	} 
    */

}

void CIconWnd::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
    SetActiveWindow();
}

void CIconWnd::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default

    UINT nCount = DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);

    AA_ITEM item;

    char *pPath = (char*) malloc(MAX_PATH+1);
	char *pFilename = (char*) malloc(_MAX_FNAME+1);
	char szDrive[_MAX_DRIVE];
	char *pDir= (char*) malloc(_MAX_DIR+1);
	char szExt[_MAX_EXT];

    CString str;
    str.Format("OnDropFiles: %d\r\n", nCount);
    OutputDebugString(str);

    UINT i=0;
    for (i=0; i<nCount; i++)
    {
        DragQueryFile(hDropInfo, i, pPath, MAX_PATH);    

    	_splitpath(pPath, 
	    	szDrive, 
		    pDir, 
		    pFilename, 
		    szExt);

        item.m_strContent = pFilename;
        AddItem(item);
    }

    free(pPath);
    free(pDir);
    free(pFilename);

	CWnd::OnDropFiles(hDropInfo);
}

void CIconWnd::OnCreateNew() 
{
	// TODO: Add your command handler code here
    CDlgNewProg dlg;
    dlg.DoModal();
}

void CIconWnd::OnUpdateCreateNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
