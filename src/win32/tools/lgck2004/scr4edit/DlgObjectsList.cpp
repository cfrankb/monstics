// DlgObjectsList.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgObjectsList.h"
#include "protosheet.h"
#include "shared.h"
#include <afxcview.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgObjectsList dialog


CDlgObjectsList::CDlgObjectsList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgObjectsList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgObjectsList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_strOK = "Select";
	m_nObject =0 ;
}


void CDlgObjectsList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgObjectsList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	int i = GetSelItemIndex();

	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (!pListView)
		return ;

	CListCtrl & list = pListView->GetListCtrl();
	
	if (i != -1)
	{
		m_nObject = list.GetItemData(i);
	}
	else
	{
		m_nObject = 0;
	}
}

BEGIN_MESSAGE_MAP(CDlgObjectsList, CDialog)
	//{{AFX_MSG_MAP(CDlgObjectsList)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_DUPLICATE, OnDuplicate)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTOBJECTS, OnDblclkListobjects)
	ON_NOTIFY(NM_CLICK, IDC_LISTOBJECTS, OnClickListobjects)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTOBJECTS, OnColumnclickListobjects)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgObjectsList message handlers

void CDlgObjectsList::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;
	CProto proto;
	strcpy(proto.m_szName, "(no name)");

	int i = GetSelItemIndex();

	if (DoProps(proto)==IDOK)
	{
		int n= arrProto.GetSize();

		if (!strcmp(proto.m_szName, "(blank)"))
		{
			char szTemp[128];
			wsprintf(szTemp, "%s~%d", 
				proto.m_szName, 	
				n);	
			szTemp[31] = 0;
			strcpy(proto.m_szName, szTemp);
		}

		arrProto.Add (proto);		

		if (i != -1)
			SetItemState(i, FALSE);

		AddListItem(n, -1);

		m_pDoc->SetModifiedFlag(TRUE);	
	}

	UpdateButtons();

	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (pListView)
		pListView->SetFocus();

}

void CDlgObjectsList::OnBdelete() 
{
	// TODO: Add your control notification handler code here

	int i = GetSelItemIndex();
	BOOL bValid = ValidateItem(i);

	if (bValid)
	{

		CListView *pListView = (CListView *)
			GetDlgItem (IDC_LISTOBJECTS);

		if (!pListView)
			return ;

		CListCtrl & list = pListView->GetListCtrl();

		CProtoArray & arrProto = 
			m_pDoc->m_game3.m_arrProto;

		int nProto = list.GetItemData(i);	
		CProto & proto = arrProto[nProto];

		char szMessage[128];
		wsprintf(szMessage, "Confirm deleting %c%s%c?",
			34, proto.m_szName, 34);

		if( AfxMessageBox(szMessage, 
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{

			m_pDoc->m_game3.KillProto(nProto);		

			list.DeleteItem(i);			

			if (i>= arrProto.GetSize())
				i--;

			SetItemState(i, TRUE);		

			m_pDoc->SetModifiedFlag(TRUE);
		}
	}

	UpdateButtons();

	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (pListView)
		pListView->SetFocus();

}

void CDlgObjectsList::OnClose() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE,0,0);	
}

void CDlgObjectsList::OnDuplicate() 
{
	// TODO: Add your control notification handler code here

	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (!pListView)
		return ;
	
	int i = GetSelItemIndex();
	BOOL bValid = ValidateItem(i);

	if (bValid)
	{
		CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;
		CListCtrl & list = pListView->GetListCtrl();

		int nProtoSrc = list.GetItemData(i);
		
		CProto proto = arrProto[nProtoSrc];
		int n = arrProto.GetSize();
	
		for (int x=0; x<(int)strlen(proto.m_szName); x++)
			if (proto.m_szName[x]=='~')
				proto.m_szName[x]=0;

		if (strlen(proto.m_szName)>26)
			proto.m_szName[26]=0;

		char szTemp[128];
		wsprintf(szTemp, "%s~%d", 
			proto.m_szName, 	
			n);	
		szTemp[31]=0;
		strcpy(proto.m_szName, szTemp);

		arrProto.Add (proto);		

		if (i != -1)
			SetItemState(i, FALSE);

		AddListItem(n, -1);
		m_pDoc->SetModifiedFlag(TRUE);	
	}
	
	UpdateButtons();	
}

void CDlgObjectsList::OnEdit() 
{
	// TODO: Add your control notification handler code here
	int i = GetSelItemIndex();
	BOOL bValid = ValidateItem(i);

	if (bValid)
	{
		CListView *pListView = (CListView *)
			GetDlgItem (IDC_LISTOBJECTS);

		CProtoArray & arrProto = 
			m_pDoc->m_game3.m_arrProto;

		if (!pListView)
			return ;
		
		CListCtrl & list = pListView->GetListCtrl();
		int nProto = list.GetItemData(i);	
		CProto & proto = arrProto[nProto];

		if (DoProps(proto)==IDOK)
		{
			list.DeleteItem(i);			

			if (!strcmp(proto.m_szName, "(blank)"))
			{
				char szTemp[128];
				wsprintf(szTemp, "%s~%d", 
					proto.m_szName, 	
					nProto);	
				szTemp[31] = 0;
				strcpy(proto.m_szName, szTemp);
			}	
			
			i = AddListItem(nProto, i);
			m_pDoc->SetModifiedFlag(TRUE);
		}
	}

	UpdateButtons();

	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (pListView)
	{
		pListView->SetFocus();
	}
}

void CDlgObjectsList::OnDblclkListobjects(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnEdit();
	*pResult = 0;
}

BOOL CDlgObjectsList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	FillBox();
	UpdateButtons();

	CButton * pOK = (CButton *) GetDlgItem (IDOK);
	pOK ->SetWindowText (m_strOK);

	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (pListView)
		pListView->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgObjectsList::FillBox()
{
	// Check if listview is valid
	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (!pListView)
		return;

	CListCtrl & list = pListView->GetListCtrl();

    int nColumns;

	HICON hIcon;
	LV_COLUMN lvC;      		// list view column structure

    char *szColumns [] =
    { "object name", 
	  "class name", 
	  NULL  };

	// Create the small icon image list.
	m_ImageList.Create(
		16,
		16,
		TRUE,			// list does include masks
		0,              // Default size is zero
		1 );			// list will be growing


	// Load the default icon and add it to the image lists.
	hIcon = ::LoadIcon (AfxGetResourceHandle(),
           MAKEINTRESOURCE(IDR_SCR4TYPE));
	m_ImageList.Add(hIcon);
	
	// Be sure that all of large icons were added.
	if (m_ImageList.GetImageCount() < 1)
		return ;

	// Associate the image lists with the list view control.
    list.SetImageList(&m_ImageList,  LVSIL_SMALL);

	// Now initialize the columns you will need.
	// Initialize the LV_COLUMN structure.
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align column
	lvC.cx = 124;            // width of column in pixels

	// Add the columns.
	for (nColumns = 0; szColumns[nColumns]; nColumns++)
	{
		lvC.iSubItem = nColumns;
		lvC.pszText = szColumns[nColumns];
		
		if (list.InsertColumn(nColumns, &lvC) == -1)
			return ;
	}

    CWnd *l_WndList = list.GetParent();

    // Set reportview by default

	DWORD dwStyle;

	dwStyle = GetWindowLong(list.m_hWnd,
        GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_REPORT)
		SetWindowLong(list.m_hWnd, 
        GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);

	// Fill ListView

	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;
	CStrValArray & arrClass = m_pDoc->m_game3.m_arrClasses;

	int n;
	int i;

	for (n=0; n< arrProto.GetSize(); n++)
	{	
		CProto & proto = arrProto[n];

		i = AddListItem(n, FALSE);
	}
	
	SetItemState(0, TRUE);

}

int CDlgObjectsList::GetSelItemIndex()
{
	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (!pListView)
		return -1;

	CListCtrl & list = pListView->GetListCtrl();

    int l_nItems = list.GetItemCount();
    if (l_nItems==0) return -1;

    LV_ITEM l_lvItem;
    char l_szText[256];

    l_lvItem.mask = LVIF_STATE;
    l_lvItem.iSubItem = 0;
    l_lvItem.pszText = l_szText;
    l_lvItem.cchTextMax =1;
    l_lvItem.stateMask = LVIS_SELECTED ;//| LVIS_FOCUSED;

    int l_nSelItemIndex =-1;

    for (int l_nIndex=0; l_nIndex < l_nItems; l_nIndex++)
    {
    
        l_lvItem.iItem = l_nIndex;
        if (list.GetItem(&l_lvItem)==FALSE)
            return -1;

        if (l_lvItem.state)
		{
            if (l_nSelItemIndex!=-1) 
				return -1;				
			else 
				l_nSelItemIndex = l_nIndex;
		}

    }

    return l_nSelItemIndex;
}

void CDlgObjectsList::UpdateButtons()
{
	int i = GetSelItemIndex();
	BOOL bValid = ValidateItem(i);

	if (bValid)
	{
		CWnd *pWnd = GetDlgItem (IDC_EDIT);
		pWnd->EnableWindow(TRUE);

		pWnd = GetDlgItem (IDC_DUPLICATE);
		pWnd->EnableWindow(TRUE);

		pWnd = GetDlgItem (IDC_BDELETE);
		pWnd->EnableWindow(TRUE);
	}
	else	
	{
		CWnd *pWnd = GetDlgItem (IDC_EDIT);
		pWnd->EnableWindow(FALSE);

		pWnd = GetDlgItem (IDC_DUPLICATE);
		pWnd->EnableWindow(FALSE);

		pWnd = GetDlgItem (IDC_BDELETE);
		pWnd->EnableWindow(FALSE);
	}
}

void CDlgObjectsList::OnClickListobjects(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	UpdateButtons();
}

int CDlgObjectsList::DoProps(CProto & proto)
{
	return DoProtoProps(proto, m_pDoc);
}

int CDlgObjectsList::AddListItem(int nProto, BOOL bSelected)
{

	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (!pListView)
		return -1;

	pListView->SetFocus();

	CListCtrl & list = pListView->GetListCtrl();
	CStrValArray & arrClass = m_pDoc->m_game3.m_arrClasses;
	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;

	CProto & proto = arrProto[nProto];

	int i;

	LV_ITEM lvI;        		// list view item structure
   
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	if (bSelected)
		lvI.state = LVIS_FOCUSED | LVIS_SELECTED ;      
	else
		lvI.state = 0;

	lvI.stateMask = LVIS_FOCUSED | LVIS_SELECTED ;      ;  

	lvI.iSubItem = 0;

	lvI.pszText = proto.m_szName;
	lvI.cchTextMax = 64;
	lvI.iImage = 0;
	lvI.lParam = nProto;

	lvI.iItem = list.GetItemCount() ;
	i = list.InsertItem(&lvI);

	if (i!=-1)
	{	
		char *pText = arrClass.StringFor(proto.m_nClass).GetBuffer(256);
		list.SetItemText( i, 1, pText);
	}

	return i;
}

BOOL CDlgObjectsList::ValidateItem(int i)
{
	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (!pListView)
		return FALSE;

	CListCtrl & list = pListView->GetListCtrl();
	CProtoArray & arrProto = m_pDoc->m_game3.m_arrProto;

	BOOL bValid = FALSE;

	if (i != -1)
	{
		int nProto = list.GetItemData(i);
		CProto & proto = arrProto[nProto];
		bValid = strcmp(proto.m_szName, "(blank)");
	}
	
	return bValid;
}

void CDlgObjectsList::SetItemState(int nItem, BOOL bSelected)
{
	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (!pListView)
		return ;

	CListCtrl & list = pListView->GetListCtrl();

	int nState;

	if (bSelected)
		nState =LVIS_FOCUSED | LVIS_SELECTED ;      
	else
		nState= 0;

	list.SetItemState(nItem, nState, 
		LVIS_FOCUSED | LVIS_SELECTED );

	UpdateButtons();
}

BOOL CDlgObjectsList::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_NOTIFY)
		NotifyHandler(pMsg->message, 
			pMsg->wParam, 
			pMsg->lParam);


	return CDialog::PreTranslateMessage(pMsg);
}

static CScr4editDoc * pDoc;

LRESULT CDlgObjectsList::NotifyHandler(UINT message, WPARAM wParam, LPARAM lParam)
{
	CListView *pListView = (CListView *)
		GetDlgItem (IDC_LISTOBJECTS);

	if (!pListView)
		return FALSE;

	pDoc = m_pDoc;

	CListCtrl & list = pListView->GetListCtrl();
		
	LV_DISPINFO *pLvdi = (LV_DISPINFO *)lParam;
	NM_LISTVIEW *pNm = (NM_LISTVIEW *)lParam;

    static BOOL l_bSens[4];
    int l_nColumn ;
	switch(pLvdi->hdr.code)
	{

		case LVN_COLUMNCLICK:
			// The user clicked on one of the column headings - sort by
			// this column.

            l_nColumn = pNm->iSubItem;
            l_bSens[l_nColumn] = 1 - l_bSens[l_nColumn];
            if (l_bSens==FALSE) 
				list.SortItems( ListViewCompareProc,
						(LPARAM)(pNm->iSubItem));
            else
                list.SortItems( ListViewCompareProc,
							(LPARAM)-(pNm->iSubItem));
			break;

		default:
			break;
	}
	return 0L;

}

int CALLBACK CDlgObjectsList::ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int iResult;

	CProtoArray & arrProto  = pDoc->m_game3.m_arrProto;
	CStrValArray & arrClass = pDoc->m_game3.m_arrClasses;

    CProto &proto1 = arrProto[lParam1];
    CProto &proto2 = arrProto[lParam2];

    int nColumn = abs( (int) lParamSort);

    switch(nColumn)
	{
		case 0:     // sort by Name               
		case 1:
            iResult  = strcmp(proto1.m_szName,
						proto2.m_szName);
        break;

		default: // sort by Nothing
			iResult = 0;
		break;

		}

    if (((int)lParamSort)<0) 
    {    
        if (iResult==0)
            iResult=1;
            else
            iResult=0;
    }

	return(iResult);
}



void CDlgObjectsList::OnColumnclickListobjects(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
