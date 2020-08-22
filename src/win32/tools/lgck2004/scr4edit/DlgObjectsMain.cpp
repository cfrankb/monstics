// DlgObjectsMain.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgObjectsMain.h"
#include "ProtoSheet.h"
#include "shared.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgObjectsMain dialog


CDlgObjectsMain::CDlgObjectsMain(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgObjectsMain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgObjectsMain)
	m_nObject = -1;
	//}}AFX_DATA_INIT

	m_strOK = "Select";
}


void CDlgObjectsMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgObjectsMain)
	DDX_LBIndex(pDX, IDC_LIST, m_nObject);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgObjectsMain, CDialog)
	//{{AFX_MSG_MAP(CDlgObjectsMain)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DUPLICATE, OnDuplicate)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgObjectsMain message handlers

BOOL CDlgObjectsMain::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;
	FillListBox();
	UpdateEDIT();

	CButton * pOK = (CButton *) GetDlgItem (IDOK);
	pOK ->SetWindowText (m_strOK);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgObjectsMain::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;
	CProto proto;
	strcpy(proto.m_szName, "(no name)");

	if (DoProps(proto)==IDOK)
	{
		arrProto.Add (proto);		

		int i;
		CListBox *pListBox = (CListBox *)
			GetDlgItem (IDC_LIST);
		i = pListBox->AddString (proto.m_szName);
		pListBox->SetItemData (i, arrProto.GetSize()-1);
		pListBox->SetCurSel (i);

		m_pDoc->SetModifiedFlag(TRUE);	
	}
	
}

void CDlgObjectsMain::OnDelete() 
{
	// TODO: Add your control notification handler code here
}

void CDlgObjectsMain::OnDuplicate() 
{
	// TODO: Add your control notification handler code here

	CListBox *pListBox = (CListBox *)
		GetDlgItem (IDC_LIST);

	if ((pListBox ->GetCurSel () != LB_ERR) &&
		(pListBox ->GetCurSel () != 0))
	{
		int i = pListBox ->GetCurSel ();
		int n = pListBox ->GetItemData (i);
		CProtoArray & arrProto = 
			m_pDoc->m_game3.m_arrProto;

		CProto & proto = arrProto[n];
		arrProto.Add (proto);		

		i = pListBox->AddString (proto.m_szName);
		pListBox->SetItemData (i, arrProto.GetSize()-1);
		pListBox->SetCurSel (i);
	}
	
}

void CDlgObjectsMain::OnEdit() 
{
	// TODO: Add your control notification handler code here

	CListBox *pListBox = (CListBox *)
		GetDlgItem (IDC_LIST);

	if ((pListBox ->GetCurSel () != LB_ERR) &&
		(pListBox ->GetCurSel () != 0))
	{

		int i = pListBox ->GetCurSel ();
		int n = pListBox ->GetItemData (i);

		CProtoArray & arrProto = 
			m_pDoc->m_game3.m_arrProto;

		CProto & proto = arrProto[i];
		
		if (DoProps(proto)==IDOK)
		{
			pListBox->DeleteString (i);
		    i = pListBox->InsertString (i, proto.m_szName);
		    pListBox->SetItemData (i, n);
			pListBox->SetCurSel (i);

			m_pDoc->SetModifiedFlag(TRUE);
		}
	}
}

void CDlgObjectsMain::FillListBox()
{
	CListBox *pListBox = (CListBox *)
		GetDlgItem (IDC_LIST);

	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;

	int n;
	int i;

	for (n=0; n< arrProto.GetSize(); n++)
	{
		i = pListBox->AddString (arrProto[n].m_szName);
		pListBox->SetItemData (i, n);
	}

	pListBox ->SetCurSel (0);

}

void CDlgObjectsMain::OnDblclkList() 
{
	// TODO: Add your control notification handler code here
	OnEdit();
}

void CDlgObjectsMain::OnClose() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE,0,0);
}

void CDlgObjectsMain::UpdateEDIT()
{
	CListBox *pListBox = (CListBox *)
		GetDlgItem (IDC_LIST);

	if ((pListBox ->GetCurSel () != LB_ERR) &&
		(pListBox ->GetCurSel () != 0))	{
		CWnd *pWnd = GetDlgItem (IDC_EDIT);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem (IDC_DUPLICATE);
		pWnd->EnableWindow(TRUE);
	}
	else	{
		CWnd *pWnd = GetDlgItem (IDC_EDIT);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem (IDC_DUPLICATE);
		pWnd->EnableWindow(FALSE);
	}
}

void CDlgObjectsMain::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here
	UpdateEDIT();
}


int CDlgObjectsMain::DoProps(CProto & proto)
{

	//int DoProtoProps(CProto & proto, CScr4editDoc *pDoc)

	return DoProtoProps(proto, m_pDoc);

	/*
	CProtoSheet propSheet;
	CStrValArray & arrClasses = 
		m_pDoc->m_game3.m_arrClasses;

	// Page 1
	propSheet.m_Page1.m_pDoc = m_pDoc;
	propSheet.m_Page1.m_nFrameNo = proto.m_nFrameNo;
	propSheet.m_Page1.m_nClass = arrClasses.GetIndexFor (proto.m_nClass);
		//proto.m_nClass;
	propSheet.m_Page1.m_nFrameSet = proto.m_nFrameSet;
	propSheet.m_Page1.m_nTrigger= proto.m_nTriggerType; 
	propSheet.m_Page1.m_nObjectKey= proto.m_nObjectKey;
	propSheet.m_Page1.m_bAnimate = proto.m_bAnimate;
	propSheet.m_Page1.m_strName = proto.m_szName;

	// Page 2
	propSheet.m_Page2.m_pDoc = m_pDoc;
	propSheet.m_Page2.m_nMoveSpeed = proto.m_nMoveSpeed;
	propSheet.m_Page2.m_nAniSpeed = proto.m_nAniSpeed;
	propSheet.m_Page2.m_nDefaultAim = proto.m_nDefaultAim;

	propSheet.m_Page2.m_nUserTag = proto.m_nUserTag ;

	//propSheet.m_Page2. m_bIgnoreStops = proto. m_bIgnoreStops;
	propSheet.m_Page2. m_nDamages = proto. m_nDamages;
	propSheet.m_Page2. m_nHitPoints= proto. m_nHitPoints;
	propSheet.m_Page2. m_nPowerLevel= proto.m_nPowerLevel ;

	// Page 3
	propSheet.m_Page3.m_pDoc = m_pDoc;
	propSheet.m_Page3.m_nPoints = proto.m_nPoints;
	propSheet.m_Page3.m_nChProto= proto.m_nChProto;
	propSheet.m_Page3.m_nChSound = proto.m_nChSound;

	propSheet.m_Page3. m_nRbDelay = proto. m_nRbDelay;
	propSheet.m_Page3. m_nRebirths= proto. m_nRebirths;

	// Page 4
	propSheet.m_Page4.m_pDoc = m_pDoc;
	propSheet.m_Page4.m_nAutoProto = proto.m_nAutoProto;
	propSheet.m_Page4.m_nAutoBullet = proto.m_nAutoBullet;
	propSheet.m_Page4.m_nAutoSound = proto.m_nAutoSound;
	propSheet.m_Page4.m_bAutoTrigger = proto.m_bAutoTrigger;

	propSheet.m_Page4.m_nAutoProtoTime = proto.m_nAutoProtoTime;
	propSheet.m_Page4.m_nAutoBulletTime = proto.m_nAutoBulletTime;
	propSheet.m_Page4.m_nAutoSoundTime = proto.m_nAutoSoundTime;
	propSheet.m_Page4.m_nAutoTriggerTime = proto.m_nAutoTriggerTime;

	if (propSheet.DoModal()==IDOK)
	{
		CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;

		// Page 1
		proto.m_nClass = arrClasses[propSheet.m_Page1.m_nClass]->m_nVal;	

		char sz[128];
		wsprintf(sz,"OUT: Class %d\n", proto.m_nClass);
		OutputDebugString(sz);
		
		proto.m_nFrameNo= propSheet.m_Page1.m_nFrameNo;
		proto.m_nFrameSet = propSheet.m_Page1.m_nFrameSet;
		proto.m_nTriggerType = propSheet.m_Page1.m_nTrigger;
		proto.m_nObjectKey = propSheet.m_Page1.m_nObjectKey;
		proto.m_bAnimate = propSheet.m_Page1.m_bAnimate;
		strcpy (proto.m_szName, 
			propSheet.m_Page1.m_strName.GetBuffer(32));

		// Page 2
		proto.m_nMoveSpeed = propSheet.m_Page2.m_nMoveSpeed ;
		proto.m_nAniSpeed = propSheet.m_Page2.m_nAniSpeed ;
		proto.m_nDefaultAim = propSheet.m_Page2.m_nDefaultAim;

		proto.m_nUserTag = propSheet.m_Page2.m_nUserTag  ;

		//proto.m_bIgnoreStops = propSheet.m_Page2. m_bIgnoreStops;
		proto.m_nDamages = propSheet.m_Page2. m_nDamages;
		proto.m_nHitPoints= propSheet.m_Page2. m_nHitPoints;
		proto.m_nPowerLevel= propSheet.m_Page2. m_nPowerLevel ;


		// Page 3
		proto.m_nPoints = propSheet.m_Page3.m_nPoints;
		proto.m_nChProto = propSheet.m_Page3.m_nChProto;
		proto.m_nChSound = propSheet.m_Page3.m_nChSound ;

		proto.m_nRbDelay = propSheet.m_Page3.  m_nRbDelay;
		proto.m_nRebirths= propSheet.m_Page3.m_nRebirths;
		
		// Page 4
		proto.m_nAutoProto = propSheet.m_Page4.m_nAutoProto ;
		proto.m_nAutoBullet = propSheet.m_Page4.m_nAutoBullet;
		proto.m_nAutoSound = propSheet.m_Page4.m_nAutoSound ;
		proto.m_bAutoTrigger = propSheet.m_Page4.m_bAutoTrigger ;

		proto.m_nAutoProtoTime = propSheet.m_Page4.m_nAutoProtoTime ;
		proto.m_nAutoBulletTime = propSheet.m_Page4.m_nAutoBulletTime ;
		proto.m_nAutoSoundTime = propSheet.m_Page4.m_nAutoSoundTime  ;
		proto.m_nAutoTriggerTime = propSheet.m_Page4.m_nAutoTriggerTime ;

		return IDOK;
	}
	return IDCANCEL;
	*/

}

void CDlgObjectsMain::OnBdelete() 
{
	// TODO: Add your control notification handler code here
	CListBox *pListBox = (CListBox *)
		GetDlgItem (IDC_LIST);

	if ((pListBox ->GetCurSel () != LB_ERR) &&
		(pListBox ->GetCurSel () != 0))
	{
		OutputDebugString ("Killing a proto\n");
		int i = pListBox ->GetCurSel ();
		m_pDoc->m_game3.KillProto(i);		
		pListBox->DeleteString (i);
	}
	
}
