// AlarmsListDialog.cpp : implementation file
//

#include "stdafx.h"
#include "app.h"
#include "AlarmsListDialog.h"
#include "ClockDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmsListDialog dialog


CAlarmsListDialog::CAlarmsListDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmsListDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmsListDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAlarmsListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmsListDialog)
	DDX_Control(pDX, IDC_BDELETE, m_bDelete);
	DDX_Control(pDX, IDC_BNEW, m_bNew);
	DDX_Control(pDX, IDC_LBALARMS, m_lbAlarms);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmsListDialog, CDialog)
	//{{AFX_MSG_MAP(CAlarmsListDialog)
	ON_LBN_DBLCLK(IDC_LBALARMS, OnDblclkLbalarms)
	ON_LBN_SELCHANGE(IDC_LBALARMS, OnSelchangeLbalarms)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	ON_BN_CLICKED(IDC_BNEW, OnBnew)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmsListDialog message handlers

BOOL CAlarmsListDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    CAlarmNode *l_pAlarmNode;

    int l_nIndex;
    int l_nCpt;
    CString l_strText;

    for (l_nCpt=0; l_nCpt< m_pDoc->m_arrayAlarms.GetSize(); 
        l_nCpt++)
    {
        l_pAlarmNode = (CAlarmNode*) 
            m_pDoc->m_arrayAlarms[l_nCpt];

        l_strText = MakeTimeString( l_pAlarmNode ->m_timeRing) ;

        l_nIndex = m_lbAlarms.AddString(l_strText.GetBuffer(128));
        m_lbAlarms.SetItemDataPtr(l_nIndex, (void*) l_pAlarmNode);


    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAlarmsListDialog::OnDblclkLbalarms() 
{
	// TODO: Add your control notification handler code here
    CTime l_RefTime;

    int l_nIndex = m_lbAlarms.GetCurSel();
    CAlarmNode *l_pAlarmNode;                
    l_pAlarmNode = (CAlarmNode *) m_lbAlarms.GetItemDataPtr(l_nIndex);
    //    m_lbAlarms.SetItemData(l_nIndex, l_nCpt);

    l_RefTime = l_pAlarmNode->m_timeRing;

    CClockDialog dialog;

    dialog.m_pDoc = m_pDoc;
    dialog.m_pView = m_pView;

    dialog.m_nYear = l_RefTime.GetYear();
    dialog.m_nMonth = l_RefTime.GetMonth();
    dialog.m_nDay = l_RefTime.GetDay();

    dialog.m_nHour = l_RefTime.GetHour();
    dialog.m_nMin =  5*(l_RefTime.GetMinute()/5);

    dialog.m_strCaption = "Modifier alarme existante...";
    dialog.m_strInfo  = l_pAlarmNode->m_strInfo;
    dialog.m_strSound = l_pAlarmNode->m_strSound ;

    int nStatus = dialog.DoModal();
    if (nStatus==IDOK)
    {

        l_pAlarmNode->m_timeRing = 
            CTime::CTime(dialog.m_nYear,
                         dialog.m_nMonth,
                         dialog.m_nDay,
                         dialog.m_nHour,
                         dialog.m_nMin,
                         0);

        l_pAlarmNode->m_strInfo = dialog.m_strInfo;
        l_pAlarmNode->m_strSound = dialog.m_strSound;

        // Change item's text
        CString l_strText;
        l_strText = MakeTimeString( l_pAlarmNode ->m_timeRing) ;

         m_lbAlarms.DeleteString(l_nIndex );
         m_lbAlarms.InsertString(l_nIndex,l_strText.GetBuffer(128));
         m_lbAlarms.SetItemDataPtr(l_nIndex, (void*) l_pAlarmNode);

         m_lbAlarms.SetCurSel(l_nIndex );

    }

	
}

void CAlarmsListDialog::OnSelchangeLbalarms() 
{
	// TODO: Add your control notification handler code here

    if (m_lbAlarms.GetCurSel()!=LB_ERR)    
        m_bDelete.EnableWindow(TRUE);
    else
        m_bDelete.EnableWindow(FALSE) ;

}

void CAlarmsListDialog::OnBdelete() 
{
	// TODO: Add your control notification handler code here

    if (m_lbAlarms.GetCurSel()!=LB_ERR)
    {
        int l_nIndex = m_lbAlarms.GetCurSel();
        CAlarmNode *l_pAlarmNode;                
        l_pAlarmNode = (CAlarmNode *) m_lbAlarms.GetItemDataPtr(l_nIndex);
        l_pAlarmNode->m_nDeleted=TRUE;
        m_lbAlarms.DeleteString(l_nIndex);

        m_pDoc->SetModifiedFlag( TRUE );

        if (m_lbAlarms.GetCurSel()!=LB_ERR)    
            m_bDelete.EnableWindow(TRUE);
        else
            m_bDelete.EnableWindow(FALSE) ;    
    }
}

void CAlarmsListDialog::OnBnew() 
{
	// TODO: Add your control notification handler code here

    CAlarmNode *l_pAlarmNode = m_pView->NewClock();

    if (l_pAlarmNode==NULL) return;
     
     CString l_strText;
     l_strText = MakeTimeString( l_pAlarmNode ->m_timeRing) ;

     int l_nIndex = m_lbAlarms.AddString(l_strText.GetBuffer(128));
     m_lbAlarms.SetItemDataPtr(l_nIndex, (void*) l_pAlarmNode);

     m_lbAlarms.SetCurSel(l_nIndex );

     if (m_lbAlarms.GetCurSel()!=LB_ERR)            
         m_bDelete.EnableWindow(TRUE);
     else
         m_bDelete.EnableWindow(FALSE) ;    

}

void CAlarmsListDialog::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CAlarmsListDialog::OnDestroy() 
{
    RemoveDeletedAlarmNodes();
	CDialog::OnDestroy();
}

void CAlarmsListDialog::OnClose() 
{
	// TODO: Add your message handler code here
   
	
	CDialog::OnClose();
}

CString CAlarmsListDialog::MakeTimeString(CTime & l_time)
{

        CString l_strText;
        l_strText = l_time.
            Format("%A, %d %b %Y @ %H:%M");

        return l_strText;
}


void CAlarmsListDialog::RemoveDeletedAlarmNodes()
{
    m_pDoc->m_nCritical=TRUE;

    CAlarmNode *l_pAlarmNode ;
    int l_nCpt;
    for (l_nCpt=0; l_nCpt<(m_pDoc->m_arrayAlarms.GetSize());
         l_nCpt++)
    {
    
        l_pAlarmNode = (CAlarmNode *)
            m_pDoc->m_arrayAlarms[l_nCpt];
        if (l_pAlarmNode->m_nDeleted)
        {
            delete l_pAlarmNode;
            m_pDoc->m_arrayAlarms.RemoveAt(l_nCpt);
            l_nCpt--;
        }

    }

    m_pDoc->m_nCritical=FALSE;


}
