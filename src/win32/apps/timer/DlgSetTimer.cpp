// DlgSetTimer.cpp : implementation file
//

#include "stdafx.h"
#include "timer.h"
#include "DlgSetTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetTimer dialog


CDlgSetTimer::CDlgSetTimer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetTimer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetTimer)
	m_nSeconds = 0;
	m_nMinutes = 0;
	m_nHours = 0;
	//}}AFX_DATA_INIT
}


void CDlgSetTimer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetTimer)
	DDX_Text(pDX, IDC_ESEC, m_nSeconds);
	DDX_Text(pDX, IDC_EMIN, m_nMinutes);
	DDX_Text(pDX, IDC_EHOUR, m_nHours);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetTimer, CDialog)
	//{{AFX_MSG_MAP(CDlgSetTimer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SHOUR, OnDeltaposShour)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SMIN, OnDeltaposSmin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SSEC, OnDeltaposSsec)
	ON_EN_CHANGE(IDC_EHOUR, OnChangeEhour)
	ON_EN_UPDATE(IDC_EHOUR, OnUpdateEhour)
	ON_EN_CHANGE(IDC_EMIN, OnChangeEmin)
	ON_EN_UPDATE(IDC_EMIN, OnUpdateEmin)
	ON_EN_CHANGE(IDC_ESEC, OnChangeEsec)
	ON_EN_UPDATE(IDC_ESEC, OnUpdateEsec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetTimer message handlers

void CDlgSetTimer::OnDeltaposShour(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
    // prevent wrapping beyond 9
    if (pNMUpDown->iPos==9 &&
        pNMUpDown->iDelta>=0)
    {
    	*pResult = TRUE;
        pNMUpDown->iPos = 9;    
    }
    else
    {
	    *pResult = FALSE;    
    }

}

void CDlgSetTimer::OnDeltaposSmin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
    // prevent wrapping beyond 60
    if (pNMUpDown->iPos>=59 &&
        pNMUpDown->iDelta>=0)
    {
    	*pResult = TRUE;
        pNMUpDown->iPos = 59;
    
    }
    else
    {
	    *pResult = FALSE;    
    }
}

void CDlgSetTimer::OnDeltaposSsec(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
    /*
    CString str;
    str.Format("pos: %d; delta: %d\n", 
        pNMUpDown->iPos,
        pNMUpDown->iDelta);

    OutputDebugString(str);
    */

    // prevent wrapping beyond 60
    if (pNMUpDown->iPos>=59 &&
        pNMUpDown->iDelta>=0)
    {
    	*pResult = TRUE;
        pNMUpDown->iPos = 59;
    
    }
    else
    {
	    *pResult = FALSE;    
    }
}

void CDlgSetTimer::OnChangeEhour() 
{
	// TODO: Add your control notification handler code here

    CString str;

    CEdit * p = (CEdit*) GetDlgItem(IDC_EHOUR);

    if (p)
    {
        p->GetWindowText(str);

        if (str2int(str)>9)
        {
            p->SetWindowText("9");
        }
    }

}

void CDlgSetTimer::OnUpdateEhour() 
{
	// TODO: Add your control notification handler code here

    CString str;

    CEdit * p = (CEdit*) GetDlgItem(IDC_EHOUR);

    if (p)
    {
        p->GetWindowText(str);

        if (str2int(str)>9)
        {
            p->SetWindowText("9");
        }
    }

    
}

int CDlgSetTimer::str2int(CString & str)
{
    int i = 0;
    int v = 0;

    while (i < str.GetLength() && isdigit(str[i]))
    {
        v = v * 10 + str[i] - '0';
        i++;
    }

    return v;

}

void CDlgSetTimer::OnChangeEmin() 
{
	// TODO: Add your control notification handler code here
    CString str;

    CEdit * p = (CEdit*) GetDlgItem(IDC_EMIN);

    if (p)
    {
        p->GetWindowText(str);

        if (str2int(str)>59)
        {
            p->SetWindowText("59");
        }
    }

	
}

void CDlgSetTimer::OnUpdateEmin() 
{
	// TODO: Add your control notification handler code here
    CString str;

    CEdit * p = (CEdit*) GetDlgItem(IDC_EMIN);

    if (p)
    {
        p->GetWindowText(str);

        if (str2int(str)>59)
        {
            p->SetWindowText("59");
        }
    }

	
}

void CDlgSetTimer::OnChangeEsec() 
{
	// TODO: Add your control notification handler code here
    CString str;

    CEdit * p = (CEdit*) GetDlgItem(IDC_ESEC);

    if (p)
    {
        p->GetWindowText(str);

        if (str2int(str)>59)
        {
            p->SetWindowText("59");
        }
    }

	
}

void CDlgSetTimer::OnUpdateEsec() 
{
	// TODO: Add your control notification handler code here
    CString str;

    CEdit * p = (CEdit*) GetDlgItem(IDC_ESEC);

    if (p)
    {
        p->GetWindowText(str);

        if (str2int(str)>59)
        {
            p->SetWindowText("59");
        }
    }

	
}
