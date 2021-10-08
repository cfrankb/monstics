// mysql_buddy.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "mysql_buddy.h"

#include "MainFrm.h"
#include "mysql_buddyDoc.h"
#include "mysql_buddyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyApp

BEGIN_MESSAGE_MAP(CMysql_buddyApp, CWinApp)
	//{{AFX_MSG_MAP(CMysql_buddyApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyApp construction

CMysql_buddyApp::CMysql_buddyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMysql_buddyApp object

CMysql_buddyApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyApp initialization

BOOL CMysql_buddyApp::InitInstance()
{

	WSADATA WsaData;

	if (!AfxSocketInit(&WsaData))
	{
		AfxMessageBox("AfxSocketInit() failed");
		return FALSE;
	}

	if (SOCKET_ERROR == WSAStartup (0x0101, &WsaData))
	{
		AfxMessageBox("WSAStartup Failed\n");
		return FALSE;
	}	

	/*
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox("AfxOleInit() failed");
		return FALSE;
	}
	*/

	AfxEnableControlContainer();
 
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey("MiniApp Package");
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMysql_buddyDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMysql_buddyView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// CG: This block was added by the MAPI component
	{
		// TODO: Add a menu item for sending mail:
		//   1. In ResourceView, open your application's menu resource
		//   2. Select the File submenu
		//   3. Double-click on the blank item at the bottom of the submenu
		//   4. Assign the new item an ID: ID_FILE_SEND_MAIL
		//   5. Assign the item a Caption: Sen&d...

		// TODO: Delete this entire block of code.
		// The code below is only for temporary use, until the above
		// instructions have been carried out. This code will not work
		// correctly if your application has multiple menus or is an
		// MDI application and starts up maximized.

		CMenu* pMenu = NULL;
		CMenu* pFileMenu = NULL;
		if ((m_pMainWnd != NULL) &&
			((pMenu = m_pMainWnd->GetMenu()) != NULL) &&
			((pFileMenu = pMenu->GetSubMenu(0)) != NULL))
		{
			// Locate the "Sen&d..." menu item
			for (int i = 0, nLength = pFileMenu->GetMenuItemCount();
				i<nLength; i++)
			{
				CString strSend;
				pFileMenu->GetMenuString(i, strSend, MF_BYPOSITION);
				if (strSend == _T("Sen&d...")) break;
			}

			if (i == nLength)
			{
				// Didn't find "Sen&d..." menu item, so add one.
				pFileMenu->InsertMenu(nLength-1, MF_BYPOSITION);
				pFileMenu->InsertMenu(nLength-1, MF_BYPOSITION,
					ID_FILE_SEND_MAIL, _T("Sen&d..."));
			}
		}
	}


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMysql_buddyApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyApp commands
