// EditEx.cpp : implementation file
//

#include "stdafx.h"
#include "EditEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define TEXT_COLOR RGB(0,0,255)
#define TEXT_COLOR RGB(0,0,0)

/////////////////////////////////////////////////////////////////////////////
// CEditEx

CEditEx::CEditEx()
{
    strcpy(m_szFaceName, _T("Courier New"));
    m_nFontSize = 200;
    m_nId =0;
    m_nUpdateMsg=0;
    m_color = RGB(0,0,0);
}

CEditEx::~CEditEx()
{
}


BEGIN_MESSAGE_MAP(CEditEx, CRichEditCtrl)
	//{{AFX_MSG_MAP(CEditEx)
	ON_WM_GETDLGCODE()
	ON_WM_CHAR()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditEx message handlers

void CEditEx::Initialize()
{
    //OutputDebugString("Initialize\r\n");

	PARAFORMAT pf;
	pf.cbSize = sizeof(PARAFORMAT);
	pf.dwMask = PFM_TABSTOPS ;
	pf.cTabCount = MAX_TAB_STOPS;
	for( int itab = 0 ; itab < pf.cTabCount  ; itab++ )
		pf.rgxTabs[itab] = (itab + 1) * 1440/5 ;

	SetParaFormat( pf );

	CHARFORMAT cfDefault;
	cfDefault.cbSize = sizeof(cfDefault);
	cfDefault.dwEffects = CFE_PROTECTED; 
	cfDefault.dwMask = CFM_BOLD | CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_PROTECTED | CFM_COLOR;
	cfDefault.yHeight = m_nFontSize ;
	cfDefault.bCharSet = 0xEE; 
	cfDefault.crTextColor = m_color;
	strcpy(cfDefault.szFaceName, m_szFaceName); 

	SetDefaultCharFormat(cfDefault);
	
	SetEventMask(ENM_CHANGE | ENM_SELCHANGE | ENM_PROTECTED | ENM_UPDATE | ENM_KEYEVENTS | ENM_MOUSEEVENTS | ENM_SCROLL);
}


UINT CEditEx::OnGetDlgCode() 
{
	// TODO: Add your message handler code here and/or call default
    CRichEditCtrl::OnGetDlgCode();	
	return DLGC_WANTALLKEYS | DLGC_WANTARROWS | DLGC_WANTCHARS | DLGC_WANTMESSAGE | DLGC_WANTTAB;        
}


void CEditEx::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CEditEx::FixContent(int nStart, int nEnd)
{
	//if (nStart >= nEnd)
	//	return;

	SetSel(nStart, nEnd);

    //COLORREF clr = TEXT_COLOR;

	CHARFORMAT cfm;
	cfm.cbSize = sizeof(cfm);
    GetSelectionCharFormat(cfm);
	
	if ((cfm.dwMask & CFM_COLOR)  && cfm.crTextColor == m_color &&     
       (cfm.dwEffects & (CFE_BOLD |CFE_ITALIC|CFM_STRIKEOUT|CFE_UNDERLINE))== 0 &&
       (cfm.yHeight == m_nFontSize) && 
       !strcmp(cfm.szFaceName, m_szFaceName)
        )
		return;

	cfm.dwEffects = 0;
	cfm.crTextColor = m_color;
	cfm.dwMask = CFM_BOLD | 
        CFM_ITALIC |
        CFM_STRIKEOUT |
        CFM_UNDERLINE |
        CFM_FACE | 
        CFM_SIZE | 
        CFM_COLOR;
	cfm.yHeight = m_nFontSize ;
	strcpy(cfm.szFaceName, m_szFaceName); 

	SetSelectionCharFormat(cfm);
    
}

void CEditEx::OnChange() 
{
	// TODO: Add your control notification handler code here

    static bBusy = FALSE;   

    if (!bBusy && this->GetTextLength())
    {
        bBusy = TRUE;

	    CHARRANGE crOldSel;
	    GetSel(crOldSel);
	    LockWindowUpdate();
	    HideSelection(TRUE, FALSE);

        FixContent(0, -1);

    	SetSel(crOldSel);
        HideSelection(FALSE, FALSE);
	    UnlockWindowUpdate();
	    SetSel(crOldSel);

        bBusy = FALSE;
    }   

    if (m_nUpdateMsg)
    {                                        
        GetParent()->SendMessage(m_nUpdateMsg, m_nId, 0); 
    }
}

void CEditEx::SetFont(char *szFaceName, int nFontSize)
{
    strcpy(m_szFaceName, szFaceName);
    m_nFontSize = nFontSize;
}

void CEditEx::OnUpdate() 
{
	// TODO: Add your control notification handler code here
    //GetParent()->SendMessage(WM_USER + 0x98, m_nId, 0); 
	
}

void CEditEx::SetId(int nId)
{
    m_nId = nId;
}

int CEditEx::GetId()
{
    return m_nId;
}

void CEditEx::SetUpdateMsg(int nMsg)
{
    m_nUpdateMsg = nMsg;
}

void CEditEx::SetColor(COLORREF color)
{
    m_color = color;
}
