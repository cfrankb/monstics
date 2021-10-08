// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "progman32.h"

#include "MainFrm.h"
#include "dlggroup.h"
#include "dlgnewprog.h"
#include "dlgnewthing.h"
#include "dlgrun.h"
#include "autoarr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct
{
    char *m_szText;
    long * m_pValue;
} INT_HOLDER;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_CREATE_NEW, OnCreateNew)
	ON_UPDATE_COMMAND_UI(IDM_CREATE_NEW, OnUpdateCreateNew)
	ON_COMMAND(IDM_WINDOWS_CASCADE, OnWindowsCascade)
	ON_UPDATE_COMMAND_UI(IDM_WINDOWS_CASCADE, OnUpdateWindowsCascade)
	ON_COMMAND(IDM_WINDOWS_MOSAIC, OnWindowsMosaic)
	ON_UPDATE_COMMAND_UI(IDM_WINDOWS_MOSAIC, OnUpdateWindowsMosaic)
	ON_COMMAND(IDM_WINDOWS_REORGANIZEICONS, OnWindowsReorganizeicons)
	ON_UPDATE_COMMAND_UI(IDM_WINDOWS_REORGANIZEICONS, OnUpdateWindowsReorganizeicons)
	ON_WM_ACTIVATEAPP()
	ON_COMMAND(IDM_OPTION_REORGANIZE_AUTOMATIC, OnOptionReorganizeAutomatic)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_REORGANIZE_AUTOMATIC, OnUpdateOptionReorganizeAutomatic)
	ON_COMMAND(IDM_RUN, OnRun)
	ON_UPDATE_COMMAND_UI(IDM_RUN, OnUpdateRun)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
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
    srand( (unsigned)time( NULL ) );
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    ShowWindow(SW_HIDE);

    if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

    if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    
	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_ALIGN_RIGHT | CBRS_BORDER_RIGHT| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_RIGHT);
	//DockControlBar(&m_wndToolBar);

    ShowWindow(SW_HIDE);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

    cs.style &= XOR(-1, WS_VISIBLE);
    cs.style |= WS_VSCROLL | WS_HSCROLL;

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnCreateNew() 
{
	// TODO: Add your command handler code here

    CMDIChildWnd *pWnd = MDIGetActive();
    CString strName;

    if (pWnd)
    {        
        CDlgNewProg dlg;
        dlg.m_nSelection=1;
        if (dlg.DoModal()==IDOK)
        {
            if (dlg.m_nSelection==0)
            {
                if (GetGroupName(strName))
                {
                    SendMessage(WM_COMMAND, ID_FILE_NEW);
                    while (MDIGetActive()==pWnd);
                    pWnd = MDIGetActive();

                    CHILD_INFO info;
                    int nValue = rand()+rand()*65536;
                    strcpy(info.m_szTitle, strName.GetBuffer(1));
                    sprintf(info.m_szPath, "%x.prg", nValue);
                    info.m_bModified = TRUE;
                    info.m_nAction= ACTION_CREATE;
                    pWnd->SendMessage(WM_PREPARE_NEW_CHILD, (WPARAM) &info, 0x900522);
                }
            }
            else
            {
                pWnd->SendMessage(WM_ADD_PROGRAM, 0, 0x900522);
            }
        }
    }
    else
    {
        if (GetGroupName(strName))
        {
            SendMessage(WM_COMMAND, ID_FILE_NEW);
            pWnd = MDIGetActive();

            CHILD_INFO info;
            int nValue = rand()+rand()*65536;
            strcpy(info.m_szTitle, strName.GetBuffer(1));
            sprintf(info.m_szPath, "%x.prg", nValue);
            info.m_bModified = TRUE;
            info.m_nAction= ACTION_CREATE;
            pWnd->SendMessage(WM_PREPARE_NEW_CHILD, (WPARAM) &info, 0x900522);
        }
    }
}

void CMainFrame::OnUpdateCreateNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CMDIFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnWindowsCascade() 
{
	// TODO: Add your command handler code here
    MDICascade();	
}

void CMainFrame::OnUpdateWindowsCascade(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnWindowsMosaic() 
{
	// TODO: Add your command handler code here
    MDITile();	
}

void CMainFrame::OnUpdateWindowsMosaic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnWindowsReorganizeicons() 
{
	// TODO: Add your command handler code here
    MDIIconArrange();	
}

void CMainFrame::OnUpdateWindowsReorganizeicons(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnOptionReorganizeAutomatic() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateOptionReorganizeAutomatic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(TRUE);
}

BOOL CMainFrame::GetGroupName(CString & str)
{
    CDlgNewThing dlg("Nouveau group de programmes");
    if (dlg.DoModal()==IDOK)
    {
        str = dlg.m_strName;
        return TRUE;
    }
    else
    {
        return FALSE;    
    }
}

void CMainFrame::OnRun() 
{
	// TODO: Add your command handler code here
    CDlgRun dlg;
    if (dlg.DoModal()==IDOK)
    {
        int nCmdShow = SW_SHOWDEFAULT;

        if (dlg.m_bRunMinimize)
        {
            nCmdShow = SW_SHOWMINIMIZED;
        }

        if (((UINT)ShellExecute(
            m_hWnd,
            "open",
            dlg.m_strCommandLine,
            "",
            "",
            nCmdShow))<=32)
        {
            AfxMessageBox("Impossible de trouver le fichier (un de ses composants). Assurez vous que le chemin d'accès et que le nom soit correct et que toutes les bibliothèques nécessaires sont disponibles.");
        }
    }
	
}

void CMainFrame::OnUpdateRun(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

    SaveSettings();
	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CMDIFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here

    ::DragAcceptFiles(m_hWnd, FALSE);  	

    static BOOL bDone = FALSE;
    if (!bDone)
    {
        SETTINGS settings;
        bDone = TRUE;
        LoadSettings();

        if (m_settings.rect.bottom 
            && m_settings.rect.right)
        {
            OutputDebugString("Move main window\r\n");
            MoveWindow(&m_settings.rect);
        }

        ShowWindow(SW_SHOW);
    }
}

LRESULT CMainFrame::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CMDIFrameWnd::DefWindowProc(message, wParam, lParam);
}

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CMDIFrameWnd::OnActivateApp(bActive, hTask);

    // TODO: Add your message handler code here

    static BOOL bDone = FALSE;
    if (!bDone)
    {
        SETTINGS settings;
        bDone = TRUE;
        CreateGroups();
    }
}

void CMainFrame::LoadSettings()
{
    CString str;

    INT_HOLDER arrSettings[]=
    {
        "left=", &m_settings.rect.left,
        "top=", &m_settings.rect.top,
        "right=", &m_settings.rect.right,
        "bottom=", &m_settings.rect.bottom,
        NULL, NULL
    };

    int i;
    for (i=0; arrSettings[i].m_szText; i++)
    {
        INT_HOLDER & item = arrSettings[i];
        *item.m_pValue = 0;
    }

    char szPath[_MAX_PATH+1];

    GetWindowsDirectory(szPath, MAX_PATH);
    strcat(szPath, "\\progman32.ini");       

    FILE *sfile = fopen(szPath,"rt");
    if (sfile)
    {
        while (fgets(szPath, MAX_PATH, sfile))
        {
            if (memcmp(szPath, "group=", 6)==0)
            {
                AA_ITEM item;
                char *p=strstr(szPath, "\n");
                if (p) 
                {
                    *p=0;
                }

                item.m_strContent = szPath + 6;
                m_settings.m_arrGroups.Add(item);
            }
            else
            {
                int i=0;
                for (i=0; arrSettings[i].m_szText; i++)
                {
                    INT_HOLDER & item = arrSettings[i];

                    if (memcmp(szPath, item.m_szText, strlen(item.m_szText))==0)
                    {
                        *item.m_pValue = 
                            str2int(szPath+strlen(item.m_szText));

                        str.Format("%s%d\r\n", item.m_szText, *item.m_pValue);
                        OutputDebugString(str);
                    }
                }
            }
        }
    }
}

void CMainFrame::SaveSettings()
{
    char szPath[_MAX_PATH+1];

    GetWindowsDirectory(szPath, MAX_PATH);
    strcat(szPath, "\\progman32.ini");
    
    FILE *tfile = fopen(szPath,"wb");
    if (tfile)
    {
        CMDIChildWnd *pWnd = MDIGetActive();
        CHILD_INFO info;
        info.m_nAction = ACTION_GET_INFO;

        CRect rect;
        GetWindowRect(rect);

        fprintf(tfile,"[Settings]\r\n");
        fprintf(tfile,"left=%d\r\n", rect.left);
        fprintf(tfile,"top=%d\r\n", rect.top);
        fprintf(tfile,"right=%d\r\n", rect.right);
        fprintf(tfile,"bottom=%d\r\n\r\n", rect.bottom);
        fprintf(tfile,"[Groups]\r\n");

        CString strGroups;
        CString str;
  
        if (pWnd)
        {        
            pWnd->SendMessage(WM_PREPARE_NEW_CHILD, (WPARAM) &info, 0x900522);
            str.Format("group=%s\r\n", info.m_szPath); 
            strGroups = str + strGroups;
            pWnd->SendMessage(WM_SAVE_RECT, 0, 0x900522);

            CWnd *pOrgWnd = pWnd;
            MDINext();            
           
            while (MDIGetActive()!=pOrgWnd)
            {
                pWnd = MDIGetActive();
                pWnd->SendMessage(WM_PREPARE_NEW_CHILD, (WPARAM) &info, 0x900522);
                str.Format("group=%s\r\n", info.m_szPath); 
                strGroups = str + strGroups;
                pWnd->SendMessage(WM_SAVE_RECT, 0, 0x900522);

                MDINext();            
            }

            fwrite(strGroups, strGroups.GetLength(), 1, tfile);
        }

        fclose(tfile);
    }
}

void CMainFrame::CreateGroups()
{
    int i;
    for (i=0; i < m_settings.m_arrGroups.GetSize(); i++)
    {
        CMDIChildWnd *pWnd = MDIGetActive();
        if (pWnd)
        {
            SendMessage(WM_COMMAND, ID_FILE_NEW);
            while (MDIGetActive()==pWnd);
            pWnd = MDIGetActive();                
        }
        else
        {
            SendMessage(WM_COMMAND, ID_FILE_NEW);
            pWnd = MDIGetActive();
        }

        AA_ITEM item = m_settings.m_arrGroups[i];
        CHILD_INFO info;       
        strcpy(info.m_szPath, item.m_strContent);
        info.m_nAction= ACTION_LOAD;
        pWnd->SendMessage(WM_PREPARE_NEW_CHILD, (WPARAM) &info, 0x900522);          
    }
}
