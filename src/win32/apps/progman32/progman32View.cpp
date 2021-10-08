// progman32View.cpp : implementation of the CProgman32View class
//

#include "stdafx.h"
#include "progman32.h"

#include "progman32Doc.h"
#include "progman32View.h"

#include "dlgnewprog.h"
#include "dlgnewthing.h"
#include "dlgprog.h"
#include "helper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgman32View

IMPLEMENT_DYNCREATE(CProgman32View, CListView)

BEGIN_MESSAGE_MAP(CProgman32View, CListView)
	//{{AFX_MSG_MAP(CProgman32View)
	ON_WM_CREATE()
	ON_COMMAND(IDM_TEST, OnTest)
	ON_UPDATE_COMMAND_UI(IDM_TEST, OnUpdateTest)
	ON_WM_DROPFILES()
	ON_WM_CHAR()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(IDM_PROPERTIES, OnProperties)
	ON_UPDATE_COMMAND_UI(IDM_PROPERTIES, OnUpdateProperties)
	ON_COMMAND(IDM_OPEN, OnOpen)
	ON_UPDATE_COMMAND_UI(IDM_OPEN, OnUpdateOpen)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_COMMAND(IDM_DELETE, OnDelete)
	ON_UPDATE_COMMAND_UI(IDM_DELETE, OnUpdateDelete)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRdblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgman32View construction/destruction

CProgman32View::CProgman32View()
{
	// TODO: add construction code here
    m_nSelItem = -1;
}

CProgman32View::~CProgman32View()
{
}

BOOL CProgman32View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

    cs.style |= LVS_SINGLESEL | LVS_AUTOARRANGE;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CProgman32View drawing

void CProgman32View::OnDraw(CDC* pDC)
{
	CProgman32Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CProgman32View diagnostics

#ifdef _DEBUG
void CProgman32View::AssertValid() const
{
	CListView::AssertValid();
}

void CProgman32View::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CProgman32Doc* CProgman32View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProgman32Doc)));
	return (CProgman32Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProgman32View message handlers


int CProgman32View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    // Accept drag and drop files
    ::DragAcceptFiles(m_hWnd, TRUE);

    // display the listview
	CListCtrl & list = GetListCtrl();
    list.ShowWindow(SW_SHOW);
    list.SetBkColor(RGB(128,255, 128));

	// Associate the image lists with the list view control.
    CImageList & imageList = GetDocument()->GetIconArray().GetImageList();
    list.SetImageList(&imageList,  LVSIL_NORMAL);
    
    // give a pointer to this view to the 
    // parent frame
    GetParent()->SendMessage(WM_USER+2, (WPARAM) this);

	return 0;
}

BOOL CProgman32View::ManageItem(ICON_INFO & item, int i, BOOL bSelected, BOOL bInsert)
{
	CListCtrl & list = GetListCtrl();

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
	lvI.pszText = item.m_szTitle; //m_strContent.GetBuffer(1);
	lvI.cchTextMax = 64;
	lvI.iImage = item.m_nIconIndex; //item.m_nId;
	lvI.lParam = 0; //item.m_nId;
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

    return i;
}

void CProgman32View::OnTest() 
{
	// TODO: Add your command handler code here
}

void CProgman32View::OnUpdateTest(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CProgman32View::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default

    UINT nCount = DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);

    AA_ITEM item;
    ICON_INFO *pInfo = (ICON_INFO *) malloc(sizeof(ICON_INFO));
    ICON_INFO & info = *pInfo;

    char *pPath = (char*) malloc(MAX_PATH+1);
	char *pFilename = (char*) malloc(_MAX_FNAME+1);
	char szDrive[_MAX_DRIVE];
	char *pDir= (char*) malloc(_MAX_DIR+1);
	char szExt[_MAX_EXT];

    //CString str;
    //str.Format("OnDropFiles: %d\r\n", nCount);
    //OutputDebugString(str);

    CIconArray & arrIcons = GetDocument()->GetIconArray();

    UINT i=0;
    for (i=0; i<nCount; i++)
    {
        DragQueryFile(hDropInfo, i, pPath, MAX_PATH);    

    	_splitpath(pPath, 
	    	szDrive, 
		    pDir, 
		    pFilename, 
		    szExt);

        int nIcons = 
            (int) ::ExtractIcon (NULL, pPath , (UINT) -1);

        if (nIcons) 
        {
             HICON hIcon = ::ExtractIcon (
                   AfxGetInstanceHandle (),
                   pPath, 0);

             info.m_nIconIndex = arrIcons.Add(hIcon);
        }
        else
        {    
            HICON hIcon = NULL;
            //OutputDebugString(szExt);
            //OutputDebugString("\r\n");

            if (lstrcmpi(szExt, ".exe")==0 
                || lstrcmpi(szExt, ".com")==0
                || lstrcmpi(szExt, ".bat")==0
                || lstrcmpi(szExt, ".pif")==0)
            {
                char szTemp[]="xx";
                FILE *sfile = fopen(pPath, "rb");
                if (sfile)
                {
                    fread(szTemp, 2,1, sfile);
                    fclose(sfile);
                }

                if (memcmp(szTemp, "MZ", 2)==0
                    && lstrcmpi(szExt, ".com")!=0)
                {
                    hIcon = ::LoadIcon(NULL, 
                        MAKEINTRESOURCE(IDI_APPLICATION));
                }
                else
                {
                    if (strstrx(pPath, "command.com"))
                    {
                        hIcon = ::LoadIcon(AfxGetInstanceHandle(), 
                             MAKEINTRESOURCE(IDI_MSDOSICON));                           
                    }
                    else
                    {
                        hIcon = ::LoadIcon(AfxGetInstanceHandle(), 
                             MAKEINTRESOURCE(IDI_MSDOSPROG));                           
                    }
                }
            }
            else
            {
                if (lstrcmpi(szExt, ".dll")==0
                    || lstrcmpi(szExt, ".cpl")==0)
                {
                    hIcon = ::LoadIcon(NULL, 
                        MAKEINTRESOURCE(IDI_WINLOGO));
                }
                else
                {
                    hIcon = ::LoadIcon(AfxGetInstanceHandle(), 
                         MAKEINTRESOURCE(IDI_DATAICON));           
                }
            }
            
            if (hIcon==NULL)
            {
                hIcon = ::LoadIcon(AfxGetInstanceHandle(), 
                     MAKEINTRESOURCE(IDI_DATAICON));           
            }

            info.m_nIconIndex = arrIcons.Add(hIcon);
        }

        CopyString(info.m_szTitle, pFilename, 31);
        strcpy(info.m_szPath, pPath);
        sprintf(info.m_szDir, "%s%s", szDrive, pDir);
        info.m_bMinimize=FALSE;
        info.m_nVirtualKeyCode= 0;
        info.m_nModifiers=0;
        arrIcons.Add(info);
        AddItem(info);
    }

    free(pPath);
    free(pDir);
    free(pFilename);
    free(pInfo);
	
    CHILD_INFO chInfo;
    chInfo.m_nAction = ACTION_SAVE;
    GetDocument()->ProcessAction(chInfo);

	CListView::OnDropFiles(hDropInfo);
}

void CProgman32View::AddItem(ICON_INFO & item)
{
	CListCtrl & list = GetListCtrl();
    ManageItem(item, list.GetItemCount(), TRUE, TRUE);

    m_nSelItem = GetCurSel();
}

void CProgman32View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
    if (nChar==VK_DELETE)
    {
        
    }
            
	CListView::OnChar(nChar, nRepCnt, nFlags);
}

LRESULT CProgman32View::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

    switch(message)
    {
        case WM_PREPARE_NEW_CHILD:
            if (lParam==0x900522)
            {
                ProcessAction(wParam);
                return 0;
            }
        break;

        case WM_ADD_PROGRAM:
            if (lParam==0x900522)
            {
                AddNewProgram();
                return 0;
            }
        break;

        case WM_SAVE_RECT:
            if (lParam==0x900522)
            {
                SetRect(wParam);
            }
        break;

    }

	return CListView::WindowProc(message, wParam, lParam);
}

void CProgman32View::ProcessAction(WPARAM wParam)
{
    CHILD_INFO & info = *((CHILD_INFO*) wParam);
    CProgman32Doc & doc = *((CProgman32Doc*)GetDocument());   

    // Process the action, alter document data
    doc.ProcessAction(info);

    // if the a file was loaded from disk
    if (info.m_nAction==ACTION_LOAD)
    {
    	CListCtrl & list = GetListCtrl();
        CProgman32Doc & doc = * (GetDocument());        
        CIconArray & arrIcons = doc.GetIconArray();

        // Associate the image lists with the list view control.
        CImageList & imageList = GetDocument()->GetIconArray().GetImageList();
        list.SetImageList(&imageList,  LVSIL_NORMAL);

        // Add all the icons to the listview
        int i=0;
        for (i=0; i<arrIcons.GetSize(); i++)
        {
            AddItem(arrIcons[i]);
        }

        // Restore the child window to the size
        // store in the .PRG file
        RECT rect;
        doc.GetRect(rect);
        GetParent()->SendMessage(WM_RESTORE_RECT, (WPARAM)&rect, 0x900522);
        Invalidate();
    }
}

void CProgman32View::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

int CProgman32View::GetCurSel()
{
	CListCtrl & list = GetListCtrl();

    int nItems = list.GetItemCount();
    if (nItems==0) return -1;

    LV_ITEM lvItem;
    char szText[256];

    lvItem.mask = LVIF_STATE;
    lvItem.iSubItem = 0;
    lvItem.pszText = szText;
    lvItem.cchTextMax =1;
    lvItem.stateMask = LVIS_SELECTED; 

    int nSelItemIndex =-1;

    for (int nIndex=0; nIndex < nItems; nIndex++)
    {
        lvItem.iItem = nIndex;
        if (list.GetItem(&lvItem)==FALSE)
        {
            return -1;
        }

        if (lvItem.state)
		{
            if (nSelItemIndex!=-1) 
            {
				return -1;				
            }
			else 
            {
				nSelItemIndex = nIndex;
            }
		}
    }

    return nSelItemIndex;

}

void CProgman32View::OnProperties() 
{
	// TODO: Add your command handler code here
    int i = GetCurSel();
    if (i != -1)
    {
        CProgman32Doc & doc = * (GetDocument());        
        CIconArray & arrIcons = doc.GetIconArray();
        
        ICON_INFO & info = arrIcons[i];

        CDlgProg dlg;
        dlg.m_strDescription = info.m_szTitle;
        dlg.m_strCommandLine = info.m_szPath;
        dlg.m_strDirectory = info.m_szDir;
        dlg.m_bMinimize = info.m_bMinimize;
        dlg.SetIcon(arrIcons.GetIcon(info.m_nIconIndex));

        if (dlg.DoModal()==IDOK)
        {          
            strcpy(info.m_szTitle , dlg.m_strDescription.GetBuffer(1));
            strcpy(info.m_szPath , dlg.m_strCommandLine.GetBuffer(1));
            strcpy(info.m_szDir , dlg.m_strDirectory.GetBuffer(1));
            info.m_bMinimize = dlg.m_bMinimize;

            if (dlg.GetIcon() != arrIcons.GetIcon(info.m_nIconIndex))
            {
                arrIcons.SetIcon(info.m_nIconIndex, dlg.GetIcon());
            }

            ManageItem(info, i, TRUE, FALSE);

            CHILD_INFO info;
            info.m_nAction = ACTION_SAVE;
            GetDocument()->ProcessAction(info);
        }        
    }   
    else
    {
        CDlgNewThing dlg("Propriétés du groupe de programmes");
        dlg.m_strName = GetDocument()->GetTitle();
        if (dlg.DoModal()==IDOK)
        {
            GetDocument()->SetTitle(dlg.m_strName);
            CHILD_INFO info;
            info.m_nAction = ACTION_SAVE;
            GetDocument()->ProcessAction(info);
        }
    }

    Invalidate(TRUE);
}

void CProgman32View::OnUpdateProperties(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CProgman32View::AddNewProgram()
{
    CDlgProg dlg;
    if (dlg.DoModal()==IDOK)
    {
        CProgman32Doc & doc = * (GetDocument());        
        CIconArray & arrIcons = doc.GetIconArray();

        ICON_INFO info;
        strcpy(info.m_szTitle , dlg.m_strDescription.GetBuffer(1));
        strcpy(info.m_szPath , dlg.m_strCommandLine.GetBuffer(1));
        strcpy(info.m_szDir , dlg.m_strDirectory.GetBuffer(1));
        info.m_bMinimize = dlg.m_bMinimize;
        info.m_nIconIndex = arrIcons.Add(dlg.GetIcon());

    	char *pFilename = (char*) malloc(_MAX_FNAME+1);
    	char szDrive[_MAX_DRIVE];
    	char *pDir= (char*) malloc(_MAX_DIR+1);
    	char szExt[_MAX_EXT];   

    	_splitpath(info.m_szPath, 
	    	szDrive, 
		    pDir, 
		    pFilename, 
		    szExt);

        if (info.m_szDir[0]==0)
        {
            sprintf(info.m_szDir, "%s%s", szDrive, pDir);
        }

        if (info.m_szTitle[0]==0)
        {
            CopyString(info.m_szTitle, pFilename, 31);
        }

        free(pDir);
        free(pFilename);
        
        arrIcons.Add(info);
        AddItem(info);
        
        CHILD_INFO chInfo;
        chInfo.m_nAction = ACTION_SAVE;
        GetDocument()->ProcessAction(chInfo);

        Invalidate(TRUE);
    }        
}

void CProgman32View::RunProgram()
{
    int i = GetCurSel();
    if (i!=-1)
    {
        CProgman32Doc & doc = * (GetDocument());        
        CIconArray & arrIcons = doc.GetIconArray();
        
        ICON_INFO & info = arrIcons[i];

        int nCmdShow = SW_SHOWDEFAULT;

        if (info.m_bMinimize)
        {
            nCmdShow = SW_SHOWMINIMIZED;
        }

        if (((UINT)ShellExecute(
            m_hWnd,
            "open",
            info.m_szPath,
            "",
            info.m_szDir,
            nCmdShow))<=32)
        {
            AfxMessageBox("Impossible de trouver le fichiers (un de ses composants). Assurez vous que le chemin d'accès et que le nom soit correct et que toutes les bibliothèques nécessaires sont disponibles.");
        }
    }
}

void CProgman32View::OnOpen() 
{
	// TODO: Add your command handler code here
    RunProgram();	
}

void CProgman32View::OnUpdateOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable(GetCurSel()	!=-1);
}


void CProgman32View::SetRect(WPARAM wParam)
{
    CProgman32Doc & doc = * (GetDocument());        
    doc.SetRect(*((RECT*)wParam));
    doc.Save();
}

void CProgman32View::OnDelete() 
{
	// TODO: Add your command handler code here
    CProgman32Doc & doc = * (GetDocument());        
    CString str;

    if (GetCurSel()!=-1)
    {
        // delete a program icon    
    }
    else
    {
        // delete a group
        str.Format("Êtes vous sûr de vouloir supprimer le group '%s'?",
            doc.GetTitle());
        if (AfxMessageBox(str, MB_YESNO)==IDYES)
        {        
            OutputDebugString("deleting...\r\n");
            doc.Delete();
            GetParent()->SendMessage(WM_CLOSE, 0, 0x900522);
        }
    }
}

void CProgman32View::OnUpdateDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CProgman32View::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    RestoreSelection();
    m_nSelItem = GetCurSel();
    
	*pResult = 0;
}

void CProgman32View::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    RestoreSelection();
    RunProgram();
    m_nSelItem = GetCurSel();

	*pResult = 0;
}

void CProgman32View::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    RestoreSelection();
    m_nSelItem = GetCurSel();
    
	*pResult = 0;
}

void CProgman32View::RestoreSelection()
{
    if (GetCurSel()==-1 && m_nSelItem!=-1)
    {
        CProgman32Doc & doc = * (GetDocument());        
        CIconArray & arr = doc.GetIconArray();
        ManageItem(arr[m_nSelItem], m_nSelItem, TRUE, FALSE);
    }

    //C:\WIN98\SYSTEM\SHELL32.DLL

}

void CProgman32View::OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    RestoreSelection();
    m_nSelItem = GetCurSel();
	
	*pResult = 0;
}
