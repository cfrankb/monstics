// DlgOptions.cpp : implementation file
//

#include "stdafx.h"
#include "vlamits3.h"
#include "DlgOptions.h"
#include "mainfrm.h"
#include "game.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static HWND g_hWnd;

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions dialog


CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptions)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgOptions)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICES, OnSelchangeComboDevices)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions message handlers

BOOL CDlgOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

    g_hWnd= this->m_hWnd;
	CMainFrame* pMainFrame = (CMainFrame*)  AfxGetMainWnd();

    // Enumerate devices to populate drop-down list.
    pMainFrame->m_game.m_lpdi->EnumDevices( 0,  // All types.
                       DIEnumDevicesProc,
                       NULL, 
                       DIEDFL_ATTACHEDONLY );


    // Initialize the list selection.
       SendDlgItemMessage( IDC_COMBO_DEVICES, 
                          CB_SETCURSEL, 0, 0 );

    // Pretend Windows did it so we can respond by saving 
    // the current GUID and updating the list of buttons
       PostMessage( WM_COMMAND,
                    MAKELONG( IDC_COMBO_DEVICES, LBN_SELCHANGE ),
                    NULL );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CALLBACK CDlgOptions::DIEnumDevicesProc( LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef )
{
    int i;
    GUID *pguid;

	// Accept keyboards & joysticks only
	if (((lpddi->dwDevType & 255) !=DIDEVTYPE_MOUSE) && 
		((lpddi->dwDevType & 255) !=DIDEVTYPE_DEVICE))	{
		i = ::SendDlgItemMessage(g_hWnd, IDC_COMBO_DEVICES, 
                       CB_ADDSTRING, 0, 
                       ( LPARAM )( lpddi->tszProductName ) );
		pguid = new GUID( lpddi->guidInstance );
		::SendDlgItemMessage(g_hWnd, IDC_COMBO_DEVICES, 
                        CB_SETITEMDATA, i, ( DWORD )pguid );
	}
  
    return DIENUM_CONTINUE;   
} // DIEnumDevicesProc

void CDlgOptions::OnDestroy() 
{
	CDialog::OnDestroy();

	CComboBox * pCombo = 
		(CComboBox*) GetDlgItem( IDC_COMBO_DEVICES);

	int i;
	int n = pCombo->GetCount();
	for (i=0; i<n; i++)
	{
		delete (GUID*) pCombo->GetItemData (i);
	}

	// TODO: Add your message handler code here
	
}

void CDlgOptions::OnSelchangeComboDevices() 
{
	// TODO: Add your control notification handler code here
}

void CDlgOptions::OnOK() 
{
	// TODO: Add extra validation here

	CComboBox * pCombo = 
		(CComboBox*) GetDlgItem( IDC_COMBO_DEVICES);

	int nIndex = pCombo->GetCurSel();

	if (nIndex!=-1)
		m_pGuid = new GUID 
			( * (GUID*) pCombo->GetItemData (nIndex));
	else 
		m_pGuid = NULL;

	CDialog::OnOK();
}

void CDlgOptions::OnMove(int x, int y) 
{
	CMainFrame* pMainFrame = (CMainFrame*)  AfxGetMainWnd();
	CGame & game = pMainFrame->m_game;

	game.BltScreen();

	while (game.m_bDrawing);

	CDialog::OnMove(x, y);
	Invalidate();
	
	// TODO: Add your message handler code here
}
