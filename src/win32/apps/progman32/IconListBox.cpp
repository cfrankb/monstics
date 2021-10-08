
// IconListBox.cpp : implementation file
//

#include "stdafx.h"
#include "IconListBox.h"

typedef struct {
    HICON hIcon;
    char szText[1024];
} USER_ICONTEXT;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CIconListBox

CIconListBox::CIconListBox()
{
}

CIconListBox::~CIconListBox()
{
}


BEGIN_MESSAGE_MAP(CIconListBox, CListBox)
	//{{AFX_MSG_MAP(CIconListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIconListBox message handlers

BOOL CIconListBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class

    if (!CListBox::PreCreateWindow (cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~(LBS_OWNERDRAWVARIABLE | LBS_SORT);
    cs.style |= LBS_OWNERDRAWFIXED;

    return CListBox::PreCreateWindow(cs);
}

void CIconListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item

    lpMeasureItemStruct->itemHeight = 36;
    lpMeasureItemStruct->itemWidth = 40 ;   
}

void CIconListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
    CDC dc;

    USER_ICONTEXT *l_psIconText;

    if (lpDrawItemStruct->itemID==-1) return;

    dc.Attach (lpDrawItemStruct->hDC);
    CRect rect = lpDrawItemStruct->rcItem;
    int nIndex = lpDrawItemStruct->itemID;

    CBrush* pBrush = new CBrush;
    pBrush->CreateSolidBrush (::GetSysColor ((lpDrawItemStruct->itemState &
        ODS_SELECTED) ? COLOR_HIGHLIGHT : COLOR_WINDOW));
    dc.FillRect (rect, pBrush);
    delete pBrush;

    if (lpDrawItemStruct->itemState & ODS_FOCUS)
        dc.DrawFocusRect (rect);

    GetItemData (nIndex);

    l_psIconText = (USER_ICONTEXT*) GetItemData (nIndex);

    if (nIndex != (UINT) -1)
       dc.DrawIcon (rect.left + 4, rect.top + 2,
            l_psIconText->hIcon);

    if (strlen(l_psIconText->szText))
    {
        dc.SelectObject(::GetStockObject(DEFAULT_GUI_FONT));
    
        dc.SetBkMode( TRANSPARENT );
        dc.SetTextColor(lpDrawItemStruct->itemState &
            ODS_SELECTED ? 0xffffffff : COLOR_WINDOWTEXT);

        dc.ExtTextOut( rect.left + 50,rect.top+ 10,
            ETO_CLIPPED, NULL,
            l_psIconText->szText, strlen(l_psIconText->szText),
            NULL);
    }

    dc.Detach ();
}

int CIconListBox::AddIcon (HICON hIcon, char *szString )
{
    USER_ICONTEXT *l_psIconText = (USER_ICONTEXT *)
        malloc(sizeof(USER_ICONTEXT));

    int nIndex = AddString (szString);

    l_psIconText->hIcon = hIcon;

    if (szString!=NULL)
        strcpy(l_psIconText->szText, szString);
    else
        strcpy(l_psIconText->szText, "");

    if ((nIndex != LB_ERR) && (nIndex != LB_ERRSPACE))
        SetItemData (nIndex, (DWORD) l_psIconText);

    return nIndex;
}

void CIconListBox::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct) 
{
	// TODO: Add your specialized code here and/or call the base class 
    USER_ICONTEXT *l_psIconText;
    l_psIconText = 
        (USER_ICONTEXT*) GetItemData (lpDeleteItemStruct->itemID);
    free(l_psIconText);    

    // default class handler
    CListBox::DeleteItem(lpDeleteItemStruct);
}
