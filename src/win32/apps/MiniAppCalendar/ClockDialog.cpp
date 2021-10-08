// ClockDialog.cpp : implementation file
//

#include "stdafx.h"
#include "app.h"
#include "ClockDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClockDialog dialog


CClockDialog::CClockDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CClockDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClockDialog)
	m_strInfo = _T("");
	m_strSound = _T("");
	//}}AFX_DATA_INIT

    m_strCaption = "Alarme";
}


void CClockDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClockDialog)
	DDX_Control(pDX, IDC_ESOUND, m_eSound);
	DDX_Control(pDX, IDC_BSOUND, m_bSound);
	DDX_Control(pDX, IDC_EINFO, m_eInfo);
	DDX_Control(pDX, IDC_CYEAR, m_cbYear);
	DDX_Control(pDX, IDC_CMONTH, m_cbMonth);
	DDX_Control(pDX, IDC_CMIN, m_cbMin);
	DDX_Control(pDX, IDC_CHOUR, m_cbHour);
	DDX_Control(pDX, IDC_CDAY, m_cbDay);
	DDX_Text(pDX, IDC_EINFO, m_strInfo);
	DDX_Text(pDX, IDC_ESOUND, m_strSound);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClockDialog, CDialog)
	//{{AFX_MSG_MAP(CClockDialog)
	ON_CBN_SELCHANGE(IDC_CMONTH, OnSelchangeCmonth)
	ON_CBN_SELCHANGE(IDC_CYEAR, OnSelchangeCyear)
	ON_BN_CLICKED(IDC_BSOUND, OnBsound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClockDialog message handlers

BOOL CClockDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    char *pBuffer = this->m_strCaption.GetBuffer(256); 
    this->SetWindowText(pBuffer);


    CTime l_TodayTime = CTime::GetCurrentTime();
    CTime l_RefTime;

    if (l_TodayTime < m_pDoc->m_CurTime)
        l_RefTime = m_pDoc->m_CurTime;
    else
        l_RefTime = l_TodayTime;

    int l_nCpt;
    int l_nIndex;
    char l_szText[16];

    // Fill Year combo
   
    for (l_nCpt=1996; (l_nCpt<2001) || (l_nCpt<l_RefTime.GetYear());
        l_nCpt++)
    {
  
        //CComboBox
        wsprintf(l_szText, "%d", l_nCpt);
        l_nIndex = m_cbYear. AddString( l_szText );
        m_cbYear. SetItemData(l_nIndex, (UINT) l_nCpt);
        
        if (l_nIndex==0)
            m_cbYear.SetCurSel(0);

        if (m_nYear == l_nCpt)
            m_cbYear.SetCurSel( l_nIndex );
    }



    m_cbMonth.SetCurSel( m_nMonth-1 );

    FillDayCombo(m_nMonth, m_nYear);
    m_cbDay.SetCurSel( m_nDay-1 );

    m_cbHour.SetCurSel( m_nHour );
    m_cbMin.SetCurSel( m_nMin/5 );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CClockDialog::FillDayCombo(int l_nMonth, int l_nYear)
{
    int l_nCpt;
    char l_szText[16];
    int l_nIndex;

    for (l_nCpt =1; 
        l_nCpt <= m_pView->GetMonthSize(l_nMonth, l_nYear);
        l_nCpt++)
    {
        wsprintf(l_szText, "%-2d", l_nCpt);
        l_nIndex = m_cbDay. AddString( l_szText );
        m_cbDay. SetItemData(l_nIndex, (UINT) l_nCpt);    
    }

}

void CClockDialog::OnSelchangeCmonth() 
{
	// TODO: Add your control notification handler code here
    FixDayCombo();
}

void CClockDialog::FixDayCombo()
{
    int l_nDay = m_cbDay.GetCurSel()+1;
    int l_nMonth = m_cbMonth.GetCurSel()+1;
    int l_nYear= m_cbYear.GetItemData (m_cbYear.GetCurSel());   

    char l_szText[16];
    int l_nIndex;

    if (l_nDay> (m_pView->GetMonthSize(l_nMonth, l_nYear)))
         l_nDay=(m_pView->GetMonthSize(l_nMonth, l_nYear));

    while ((m_cbDay.GetCount()) >
            (m_pView->GetMonthSize(l_nMonth, l_nYear)))
    {
        m_cbDay.DeleteString( m_cbDay.GetCount()-1);
    }

    while ((m_cbDay.GetCount()) <
            (m_pView->GetMonthSize(l_nMonth, l_nYear)))
    {
        wsprintf(l_szText, "%-2d", m_cbDay.GetCount()+1);
        l_nIndex = m_cbDay. AddString( l_szText );
        m_cbDay. SetItemData(l_nIndex, (UINT) l_nIndex +1);    
    }

    m_cbDay.SetCurSel( l_nDay-1 );

}

void CClockDialog::OnSelchangeCyear() 
{
	// TODO: Add your control notification handler code here
    if (( m_cbMonth.GetCurSel()+1)==2)
        FixDayCombo();
}

void CClockDialog::OnOK() 
{
	// TODO: Add extra validation here
    m_nDay = m_cbDay.GetCurSel()+1;
    m_nMonth = m_cbMonth.GetCurSel()+1;
    m_nYear= m_cbYear.GetItemData (m_cbYear.GetCurSel());   

    m_nHour = m_cbHour.GetCurSel();
    m_nMin = m_cbMin.GetCurSel()*5; 
        
    m_pDoc->SetModifiedFlag( TRUE );

	CDialog::OnOK();
}

void CClockDialog::OnBsound() 
{
	// TODO: Add your control notification handler code here
    char BASED_CODE szFilter[] = 
        "Sons WINDOWS (*.wav)|*.wav|"\
        "Musique MIDI (*.mid)|*.mid|" \
        "Tous formats supportés|*.wav;*.mid||";


    CFileDialog l_Dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
            szFilter,  this ) ;

    l_Dlg.m_ofn.lpstrTitle = "Changement de son..."; 
    
    int iStatus = l_Dlg.DoModal(); 

    if (iStatus==IDOK)
    {
        CString l_strPath = l_Dlg.GetPathName();
        m_eSound.SetWindowText(l_strPath);
    
    }
}
