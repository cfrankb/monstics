// DlgFrameList.cpp : implementation file
//

#include "stdafx.h"
#include "scr4edit.h"
#include "DlgFrameList.h"
#include "dlgframeedit.h"
#include "dlgMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFrameList dialog


CDlgFrameList::CDlgFrameList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFrameList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFrameList)
	m_nFrameSet = -1;
	//}}AFX_DATA_INIT
}


void CDlgFrameList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFrameList)
	DDX_LBIndex(pDX, IDC_LIST, m_nFrameSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFrameList, CDialog)
	//{{AFX_MSG_MAP(CDlgFrameList)
	ON_BN_CLICKED(IDC_BADD, OnBadd)
	ON_BN_CLICKED(IDC_BEDIT, OnBedit)
	ON_BN_CLICKED(IDC_BUPDATEALL, OnBupdateall)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_BDELETE, OnBdelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFrameList message handlers

BOOL CDlgFrameList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CListBox *pListBox = (CListBox*) GetDlgItem (IDC_LIST);
	CGameFile3 & game = m_pDoc->m_game3;

	int n;
	for (n=0; n< game.m_arrOBL3.GetSize(); n++)
	{
		pListBox->AddString (game.m_arrOBL3[n]->m_szName);
	}

	UpdateBEdit();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgFrameList::OnBadd() 
{
	// TODO: Add your control notification handler code here

	CListBox *pListBox = (CListBox*) GetDlgItem (IDC_LIST);
	CGameFile3 & game = m_pDoc->m_game3;

	CDlgFrameEdit dlg ;
	if (dlg.DoModal()==IDOK)
	{
		pListBox->AddString (dlg.m_strName);

		COBL3Filter *pFilter = new COBL3Filter;
		if (pFilter->Extract (dlg.m_strFilename)==0)
		{
			CSS3Frame *pFrame = new CSS3Frame (8,8);
			pFilter->Add (pFrame);
			CString str;
			str.Format ("Couldn't extract from %c%s%c \n" \
				"creating stub object !"
				, 34, dlg.m_strFilename,34);
			AfxMessageBox (str, MB_OK | 
				MB_ICONEXCLAMATION);
		}

		pFilter->SetName(dlg.m_strName);
		pFilter->SetFilename(dlg.m_strFilename);
		game.m_arrOBL3. Add (pFilter);
		int n = pListBox->GetCount();
		pListBox-> SetCurSel (n);

		m_pDoc->SetModifiedFlag(TRUE);

	}
}

void CDlgFrameList::OnBedit() 
{
	// TODO: Add your control notification handler code here
	CListBox *pListBox = (CListBox*) GetDlgItem (IDC_LIST);
	CGameFile3 & game = m_pDoc->m_game3;

	int n = pListBox->GetCurSel ();
	if ((n!= LB_ERR) && (n!=0))
	{
		CDlgFrameEdit dlg ;
		COBL3Filter *pFilter = game.m_arrOBL3[n];
		dlg.m_strName = pFilter->m_szName;
		dlg.m_strFilename = pFilter->m_szFilename;

		if ((dlg.DoModal()==IDOK) && 
			((CString(pFilter->m_szName) != dlg.m_strName) ||
			(CString(pFilter->m_szFilename) != dlg.m_strFilename)))
		{
			pListBox-> DeleteString(n);

			if (dlg.m_strFilename != 
				CString(pFilter->m_szFilename))
			{
				pFilter = new COBL3Filter;
				if (pFilter->Extract (dlg.m_strFilename))
				{
					delete game.m_arrOBL3[n];
					game.m_arrOBL3.SetAt(n, pFilter);
				}
				else {
					CString str;
			
					if (dlg.m_strFilename!="") 
					{
						str.Format ("Couldn't extract from %c%s%c \n" \
							"your request was ignored !"
							, 34, dlg.m_strFilename,34);

						AfxMessageBox (str, MB_OK | 
							MB_ICONEXCLAMATION);
						delete pFilter;
						pFilter = game.m_arrOBL3[n];
					}
					else
					{
						delete game.m_arrOBL3[n];
						pFilter->Add (new CSS3Frame (8,8));
						game.m_arrOBL3.SetAt(n, pFilter);

						str.Format ("Replacing current frame set " \
							"by a stub as requested !"
							, 34, dlg.m_strFilename,34);

						AfxMessageBox (str, MB_OK | 
							MB_ICONINFORMATION);


					}
				}
			}
			
			pFilter->SetName (dlg.m_strName);
			pFilter->SetFilename(dlg.m_strFilename);
			pListBox-> InsertString(n, dlg.m_strName);	
			pListBox-> SetCurSel (n);
		}

		m_pDoc->SetModifiedFlag(TRUE);

	}
}

void CDlgFrameList::OnBupdateall() 
{
	// TODO: Add your control notification handler code here
	CString strError;
	if (m_pDoc->m_game3.UpdateOBL3(strError)!=TRUE)
	{
		CString str = CString ("") +
			"The fallowing frame set(s) couldn't be updated:\r\n\r\n" +
			strError;

		CDlgMessageBox dlg;
		dlg.SetCaption ("Update frame sets errors");
		dlg.m_strText = str;
		dlg.DoModal ();
	}

	//SetModifiedFlag (TRUE);
	m_pDoc->RepaintAllViews();	
}

void CDlgFrameList::OnDblclkList() 
{
	// TODO: Add your control notification handler code here
	OnBedit() ;
}

void CDlgFrameList::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here
	UpdateBEdit();
}

void CDlgFrameList::UpdateBEdit()
{
	CListBox *pListBox = (CListBox*) GetDlgItem (IDC_LIST);
	CGameFile3 & game = m_pDoc->m_game3;

	int n = pListBox->GetCurSel ();

	CWnd *pWnd = GetDlgItem (IDC_BEDIT);
	if ((n!= LB_ERR) && (n!=0)) {
		pWnd->EnableWindow(TRUE);
	}
	else {
		pWnd->EnableWindow(FALSE);
	}
}

void CDlgFrameList::OnBdelete() 
{
	// TODO: Add your control notification handler code here
	CListBox *pListBox = (CListBox*) GetDlgItem (IDC_LIST);
	CGameFile3 & game = m_pDoc->m_game3;

	int n = pListBox->GetCurSel ();
	if ((n!= LB_ERR) && (n!=0))
	{
		game.KillFrameSet(n);
		pListBox->DeleteString(n);
		m_pDoc->SetModifiedFlag(TRUE);
	}
}

