// scr4editDoc.cpp : implementation of the CScr4editDoc class
//

#include "stdafx.h"
#include "scr4edit.h"
#include "scr4editDoc.h"
#include "dlgclasslist.h"
#include "DlgNameDesc.h"
#include "dlgframelist.h"
#include "dlgmessagebox.h"
#include "dlgobjswiz.h"
#include "sortarray.h"
#include "mainfrm.h"
#include "dlgeditlocal.h"
#include "DlgMoveLevel.h"
#include "DlgObjectsList.h"
#include "DlgTagList.h"
#include "DlgIntArray.h"
#include "DlgIntAll.h"
#include "ExtraArray.h"
#include "dbsheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct 
{
	int m_nVal;
	char m_szText[16];
} VALCODE;

CString operator + (const CString & str1, int n)
{
	char sz[8];
	wsprintf(sz,"%d", n);
	return CString(str1 + sz);
}

/////////////////////////////////////////////////////////////////////////////
// CScr4editDoc

IMPLEMENT_DYNCREATE(CScr4editDoc, CDocument)

BEGIN_MESSAGE_MAP(CScr4editDoc, CDocument)
	//{{AFX_MSG_MAP(CScr4editDoc)
	ON_COMMAND(IDM_INSERTFRAMES, OnInsertframes)
	ON_UPDATE_COMMAND_UI(IDM_INSERTFRAMES, OnUpdateInsertframes)
	ON_COMMAND(IDM_CLASSEDIT, OnClassedit)
	ON_UPDATE_COMMAND_UI(IDM_CLASSEDIT, OnUpdateClassedit)
	ON_COMMAND(IDM_PROTOEDITOR, OnProtoeditor)
	ON_UPDATE_COMMAND_UI(IDM_PROTOEDITOR, OnUpdateProtoeditor)
	ON_COMMAND(IDM_INSERTLEVEL, OnInsertlevel)
	ON_UPDATE_COMMAND_UI(IDM_INSERTLEVEL, OnUpdateInsertlevel)
	ON_COMMAND(IDM_INSERTOBJECT, OnInsertobject)
	ON_UPDATE_COMMAND_UI(IDM_INSERTOBJECT, OnUpdateInsertobject)
	ON_COMMAND(IDM_NEXTLEVEL, OnNextlevel)
	ON_UPDATE_COMMAND_UI(IDM_NEXTLEVEL, OnUpdateNextlevel)
	ON_COMMAND(IDM_PREVIOUSLEVEL, OnPreviouslevel)
	ON_UPDATE_COMMAND_UI(IDM_PREVIOUSLEVEL, OnUpdatePreviouslevel)
	ON_COMMAND(IDM_DOWN, OnDown)
	ON_UPDATE_COMMAND_UI(IDM_DOWN, OnUpdateDown)
	ON_COMMAND(IDM_UP, OnUp)
	ON_UPDATE_COMMAND_UI(IDM_UP, OnUpdateUp)
	ON_COMMAND(IDM_RIGHT, OnRight)
	ON_UPDATE_COMMAND_UI(IDM_RIGHT, OnUpdateRight)
	ON_COMMAND(IDM_LEFT, OnLeft)
	ON_UPDATE_COMMAND_UI(IDM_LEFT, OnUpdateLeft)
	ON_COMMAND(IDM_DELETEOBJECT, OnDeleteobject)
	ON_UPDATE_COMMAND_UI(IDM_DELETEOBJECT, OnUpdateDeleteobject)
	ON_COMMAND(IDM_DUPLICATEOBJECT, OnDuplicateobject)
	ON_UPDATE_COMMAND_UI(IDM_DUPLICATEOBJECT, OnUpdateDuplicateobject)
	ON_COMMAND(IDM_LEVELPROPERTIES, OnLevelproperties)
	ON_UPDATE_COMMAND_UI(IDM_LEVELPROPERTIES, OnUpdateLevelproperties)
	ON_COMMAND(IDM_ADDNEWLEVEL, OnAddnewlevel)
	ON_UPDATE_COMMAND_UI(IDM_ADDNEWLEVEL, OnUpdateAddnewlevel)
	ON_COMMAND(IDM_INSERTLEVELAFTER, OnInsertlevelafter)
	ON_UPDATE_COMMAND_UI(IDM_INSERTLEVELAFTER, OnUpdateInsertlevelafter)
	ON_COMMAND(IDM_DELETELEVEL, OnDeletelevel)
	ON_UPDATE_COMMAND_UI(IDM_DELETELEVEL, OnUpdateDeletelevel)
	ON_COMMAND(IDM_REMOVEALL, OnRemoveall)
	ON_UPDATE_COMMAND_UI(IDM_REMOVEALL, OnUpdateRemoveall)
	ON_COMMAND(IDM_DECBKCOLOR, OnDecbkcolor)
	ON_UPDATE_COMMAND_UI(IDM_DECBKCOLOR, OnUpdateDecbkcolor)
	ON_COMMAND(IDM_INCBKCOLOR, OnIncbkcolor)
	ON_UPDATE_COMMAND_UI(IDM_INCBKCOLOR, OnUpdateIncbkcolor)
	ON_COMMAND(IDM_DEFAULTBKCOLOR, OnDefaultbkcolor)
	ON_UPDATE_COMMAND_UI(IDM_DEFAULTBKCOLOR, OnUpdateDefaultbkcolor)
	ON_COMMAND(IDM_INFORMATION, OnInformation)
	ON_UPDATE_COMMAND_UI(IDM_INFORMATION, OnUpdateInformation)
	ON_COMMAND(IDM_EXPORT_DECLARATIONS, OnExportDeclarations)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_DECLARATIONS, OnUpdateExportDeclarations)
	ON_COMMAND(IDM_EXPORT_DIAGNOSTIC, OnExportDiagnostic)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_DIAGNOSTIC, OnUpdateExportDiagnostic)
	ON_COMMAND(IDM_PLUS, OnPlus)
	ON_UPDATE_COMMAND_UI(IDM_PLUS, OnUpdatePlus)
	ON_COMMAND(IDM_MINUS, OnMinus)
	ON_UPDATE_COMMAND_UI(IDM_MINUS, OnUpdateMinus)
	ON_COMMAND(IDM_EXPORT_CLASS, OnExportClass)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_CLASS, OnUpdateExportClass)
	ON_COMMAND(IDM_IMPORT_CLASS, OnImportClass)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_CLASS, OnUpdateImportClass)
	ON_COMMAND(IDM_FRAMEEDIT, OnFrameedit)
	ON_UPDATE_COMMAND_UI(IDM_FRAMEEDIT, OnUpdateFrameedit)
	ON_COMMAND(IDM_UPDATEFRAMES, OnUpdateframes)
	ON_UPDATE_COMMAND_UI(IDM_UPDATEFRAMES, OnUpdateUpdateframes)
	ON_COMMAND(IDM_OBJECTSWIZARD, OnObjectswizard)
	ON_UPDATE_COMMAND_UI(IDM_OBJECTSWIZARD, OnUpdateObjectswizard)
	ON_COMMAND(IDM_MOVELEVEL, OnMovelevel)
	ON_UPDATE_COMMAND_UI(IDM_MOVELEVEL, OnUpdateMovelevel)
	ON_COMMAND(IDM_DUPLICATELEVEL, OnDuplicatelevel)
	ON_UPDATE_COMMAND_UI(IDM_DUPLICATELEVEL, OnUpdateDuplicatelevel)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
	ON_COMMAND(IDM_HOME, OnHome)
	ON_UPDATE_COMMAND_UI(IDM_HOME, OnUpdateHome)
	ON_COMMAND(IDM_TEST123, OnTest123)
	ON_COMMAND(IDM_EDITSORTDATA, OnEditsortdata)
	ON_UPDATE_COMMAND_UI(IDM_EDITSORTDATA, OnUpdateEditsortdata)
	ON_COMMAND(IDM_LOADSORTDATA, OnLoadsortdata)
	ON_UPDATE_COMMAND_UI(IDM_LOADSORTDATA, OnUpdateLoadsortdata)
	ON_COMMAND(IDM_SAVESORTDATA, OnSavesortdata)
	ON_UPDATE_COMMAND_UI(IDM_SAVESORTDATA, OnUpdateSavesortdata)
	ON_COMMAND(IDM_CLEAR_SORT_DATA, OnClearSortData)
	ON_UPDATE_COMMAND_UI(IDM_CLEAR_SORT_DATA, OnUpdateClearSortData)
	ON_COMMAND(IDM_EDITSYSPATHS, OnEditsyspaths)
	ON_UPDATE_COMMAND_UI(IDM_EDITSYSPATHS, OnUpdateEditsyspaths)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScr4editDoc construction/destruction

CScr4editDoc::CScr4editDoc()
{
	// TODO: add one-time construction code here

	CWinApp * pApp = AfxGetApp(); 
    OutputDebugString("CScr4editDoc::CScr4editDoc()\r\n");
}

CScr4editDoc::~CScr4editDoc()
{
	CWinApp * pApp = AfxGetApp(); 
}

BOOL CScr4editDoc::OnNewDocument()
{
	OutputDebugString("OnNewDocument enter()\n");

    if (!CDocument::OnNewDocument())
		return FALSE;

	static BOOL bFirst = TRUE;

	if (!bFirst)
	{
		CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd(); 

		if (pMainFrame)
		{
			pMainFrame->InitPal();
			pMainFrame->NewPalette();
		}
	}

	bFirst = FALSE;

	m_game3.Forget();
	m_game3.Init();
	RepaintAllViews();

	OutputDebugString("OnNewDocument exit()\n");

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CScr4editDoc serialization

void CScr4editDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		m_game3.Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		m_game3.Serialize(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScr4editDoc diagnostics

#ifdef _DEBUG
void CScr4editDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScr4editDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScr4editDoc commands

void CScr4editDoc::OnInsertframes() 
{
	// TODO: Add your command handler code here
    CString l_strFilesFilter =
        "All supported formats|*.obl;*.ima;*.mcx|"\
        "Static Images (*.ima;*.mcx)|*.ima;*.mcx|"\
        "OBL3/OBL4 Format|*.obl|"\
        "|";

	CFileDialog l_Dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER | OFN_ALLOWMULTISELECT, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    l_Dlg.m_ofn.lpstrTitle = "Insert frame set"; 
    
    if (l_Dlg.DoModal()==IDOK)  {

		POSITION pos;
		pos = l_Dlg.GetStartPosition ();
		
		int n;

		while (pos!=NULL)	{
			CString strTheFile = 
				l_Dlg.GetNextPathName (pos);
			COBL3Filter *pOBL3 =new COBL3Filter;
			pOBL3 ->Extract (strTheFile);
			pOBL3 ->SetFilename (strTheFile);

			if (strTheFile.ReverseFind ('\\')!=-1)
			{
				n= strTheFile.ReverseFind ('\\');
				pOBL3 ->SetName ( CString 
					(strTheFile.GetBuffer (1) +1+n));				
			}
				
			m_game3.m_arrOBL3.Add (pOBL3);
		}
    }		
		
}

void CScr4editDoc::OnUpdateInsertframes(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}


void CScr4editDoc::OnClassedit() 
{
	// TODO: Add your command handler code here
	CDlgClassList dlg;
	dlg.m_pDoc = this;

	dlg.DoModal();
}

void CScr4editDoc::OnUpdateClassedit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CScr4editDoc::OnProtoeditor() 
{
	// TODO: Add your command handler code here
	CDlgObjectsList dlg;
	dlg.m_pDoc = this;
	dlg.m_strOK = "&OK";

	dlg.DoModal();

	RepaintAllViews(); 
}


void CScr4editDoc::OnUpdateProtoeditor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CScr4editDoc::OnInsertlevel() 
{
	// TODO: Add your command handler code here
	if (m_game3.m_nScripts!=0)
	{
		CDlgNameDesc dlg;

		if (dlg.DoModal()==IDOK)
		{
			CScriptArray *pScript = new CScriptArray;
			pScript->m_strName = dlg.m_strName;
			pScript->m_strTitle = dlg.m_strTitle;
			m_game3.InsertScript (m_game3.m_nCurrScript, pScript);
			SetModifiedFlag (TRUE);
			RepaintAllViews();
		}
	}
}

void CScr4editDoc::OnUpdateInsertlevel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.m_nScripts!=0);
}

void CScr4editDoc::OnInsertobject() 
{
	// TODO: Add your command handler code here
	if (m_game3.m_nScripts !=0)
	{
		CDlgObjectsList dlg;
		dlg.m_strOK = "&Select";
		dlg.m_pDoc = this;

		if ((dlg.DoModal ()==IDOK) && 
			(dlg.m_nObject!=0))		{

			CScriptArray & script = 
				* m_game3 [m_game3.m_nCurrScript];

			// New entry properties....
			CScriptEntry entry 
				(script.m_nMX, script.m_nMY);

			entry.m_nFrameSet = 
				m_game3.m_arrProto[dlg.m_nObject].m_nFrameSet;

			entry.m_nFrameNo = 
				m_game3.m_arrProto[dlg.m_nObject].m_nFrameNo;

			if (entry.m_nFrameNo<0) entry.m_nFrameNo =0;

			entry.m_nProto = dlg.m_nObject;
			entry.m_nTriggerKey = 0; // Place system default here

			// Add entry to script
			script. m_nCurrEntry = script. Add (entry);
			script. m_bSelection = TRUE;

			SetModifiedFlag (TRUE);
		}	
	}
	RepaintAllViews();
}

void CScr4editDoc::OnUpdateInsertobject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable (m_game3.m_nScripts !=0);
}

void CScr4editDoc::OnNextlevel() 
{
	// TODO: Add your command handler code here
	if (m_game3.m_nCurrScript < m_game3.m_nScripts) {
		m_game3.m_nCurrScript ++;
		RepaintAllViews();
	}
}

void CScr4editDoc::OnUpdateNextlevel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.m_nCurrScript < m_game3.m_nScripts-1);
}


void CScr4editDoc::OnPreviouslevel() 
{
	// TODO: Add your command handler code here
	if (m_game3.m_nCurrScript !=0) {
		m_game3.m_nCurrScript --;
		RepaintAllViews();
	}
}

void CScr4editDoc::OnUpdatePreviouslevel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.m_nCurrScript !=0);
}

void CScr4editDoc::RepaintAllViews()
{
	UpdateAllViews(NULL);
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		pView->Invalidate();
	}   
}


void CScr4editDoc::OnDown() 
{
	// TODO: Add your command handler code here
	CGameFile3 & game = m_game3; 
	CScr4editDoc *pDoc = this;

	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)
		&& game[game.m_nCurrScript]->m_bSelection)	{
		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry & entry =  script[script.m_nCurrEntry];
		COBL3Filter & filter = * game.m_arrOBL3[entry.m_nFrameSet];	

		CSS3Frame *pFrame = filter[entry.m_nFrameNo];
		CRect rect;
		CView *pView = GetFirstView();
		pView->GetClientRect (rect);
		CSize size = rect.Size();

		if ((entry.m_nY + pFrame->m_nHei - script.m_nMY) 
			< (size.cy -MOVESTEP))
		{
			entry.MoveBy(0,MOVESTEP);
		}
		else
		{
			script.m_nMY = script.m_nMY +MOVESTEP;
			entry.MoveBy(0,MOVESTEP);
		}
		
		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}
	else {
		if ((game.m_nScripts !=0) &&
			(game[game.m_nCurrScript]->GetSize()!=0))
		{
			CScriptArray & script = * game[game.m_nCurrScript];
			script.m_nMY = script.m_nMY + MOVESTEP;	
			script.m_bSelection = FALSE;
			RepaintAllViews();
		}
	}
}

void CScr4editDoc::OnUpdateDown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CScr4editDoc::OnUp() 
{
	// TODO: Add your command handler code here
	CGameFile3 & game = m_game3; 
	CScr4editDoc *pDoc = this;

	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)
		&& game[game.m_nCurrScript]->m_bSelection)	{
		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry & entry =  script[script.m_nCurrEntry];
		COBL3Filter & filter = * game.m_arrOBL3[entry.m_nFrameSet];	

		if (entry.m_nY - script.m_nMY !=0)		{
			entry.MoveBy(0,-MOVESTEP);
		}
		else {		 
			if (script.m_nMY !=0)		{
				script.m_nMY = script.m_nMY -MOVESTEP;
				entry.MoveBy(0,-MOVESTEP);
			}
		}
		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}
	else {
		if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0))	{
			CScriptArray & script = * game[game.m_nCurrScript];
			if (script.m_nMY !=0) {
				script.m_nMY = script.m_nMY - MOVESTEP;	
				script.m_bSelection = FALSE;
				RepaintAllViews();
			}
		}
	}
}

void CScr4editDoc::OnUpdateUp(CCmdUI* pCmdUI) 
{
}

void CScr4editDoc::OnRight() 
{
	// TODO: Add your command handler code here
	CGameFile3 & game = m_game3; 
	CScr4editDoc *pDoc = this;

	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)
		&& game[game.m_nCurrScript]->m_bSelection)	{
		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry & entry =  script[script.m_nCurrEntry];
		COBL3Filter & filter = * game.m_arrOBL3[entry.m_nFrameSet];	

		CSS3Frame *pFrame = filter[entry.m_nFrameNo];
		CRect rect;
		CView *pView = GetFirstView();
		pView->GetClientRect (rect);
		CSize size = rect.Size();

		if ((entry.m_nX + pFrame->m_nLen - script.m_nMX) 
			< (size.cx -MOVESTEP))	{
			entry.MoveBy(MOVESTEP,0);
		}
		else	{
			script.m_nMX = script.m_nMX +MOVESTEP;
			entry.MoveBy(MOVESTEP,0);
		}

		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}
	else {
		if ((game.m_nScripts !=0) &&
			(game[game.m_nCurrScript]->GetSize()!=0))	{
			CScriptArray & script = * game[game.m_nCurrScript];
			script.m_nMX = script.m_nMX + MOVESTEP;	
			script.m_bSelection = FALSE;
			RepaintAllViews();
		}
	}
}

void CScr4editDoc::OnUpdateRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGameFile3 & game = m_game3; 
	pCmdUI->Enable ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0));
}

void CScr4editDoc::OnLeft() 
{
	// TODO: Add your command handler code here
	CGameFile3 & game = m_game3; 
	CScr4editDoc *pDoc = this;

	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)		
		&& game[game.m_nCurrScript]->m_bSelection)	{
		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry & entry =  script[script.m_nCurrEntry];
		COBL3Filter & filter = * game.m_arrOBL3[entry.m_nFrameSet];	

		if (entry.m_nX - script.m_nMX !=0)	{
			entry.MoveBy(-MOVESTEP,0);
		}
		else {		 
			if (script.m_nMX !=0)	{
				script.m_nMX = script.m_nMX -MOVESTEP;
				entry.MoveBy(-MOVESTEP,0);
			}
		}
			
		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}
	else
	{
		CGameFile3 & game = pDoc->m_game3; 

		if ((game.m_nScripts !=0) &&
			(game[game.m_nCurrScript]->GetSize()!=0))
		{
			CScriptArray & script = * game[game.m_nCurrScript];
			if (script.m_nMX) {
				script.m_nMX = script.m_nMX - MOVESTEP;	
				script.m_bSelection = FALSE;
				RepaintAllViews();
			}
		}
	}
}

void CScr4editDoc::OnUpdateLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CScr4editDoc::OnDeleteobject() 
{
	// TODO: Add your command handler code here
	CGameFile3 & game = m_game3; 
	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)		
		&& game[game.m_nCurrScript]->m_bSelection)	{

		CScriptArray & script = * game[game.m_nCurrScript];
		script.m_bSelection = FALSE;
		script.RemoveAt (script.m_nCurrEntry);
		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}	
}

void CScr4editDoc::OnUpdateDeleteobject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGameFile3 & game = m_game3; 
	pCmdUI->Enable ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)		
		&& game[game.m_nCurrScript]->m_bSelection);
}

void CScr4editDoc::OnDuplicateobject() 
{
	// TODO: Add your command handler code here
	CGameFile3 & game = m_game3; 
	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)		
		&& game[game.m_nCurrScript]->m_bSelection)	{

		CScriptArray & script = * game[game.m_nCurrScript];
		script.m_bSelection = TRUE;
		CScriptEntry entry = script[script.m_nCurrEntry];
		entry.MoveBy(MOVESTEP,MOVESTEP);
		//script.MoveBy(MOVESTEP,MOVESTEP);
		script.m_nCurrEntry = script.Add (entry);
		
		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}	
	
}

void CScr4editDoc::OnUpdateDuplicateobject(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGameFile3 & game = m_game3; 
	pCmdUI->Enable ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)		
		&& game[game.m_nCurrScript]->m_bSelection);	
}

CView * CScr4editDoc::GetFirstView()
{
	UpdateAllViews(NULL);
	POSITION pos = GetFirstViewPosition();
	if (pos!=NULL) 
		return GetNextView(pos);
	else 
		return NULL;
}

void CScr4editDoc::OnLevelproperties() 
{
	// TODO: Add your command handler code here
	CGameFile3 & game = m_game3; 
	if (game.m_nScripts !=0)	{
		CDlgNameDesc dlg;
		dlg.SetCaption ("Modify existing level");
		dlg.m_strName = game[game.m_nCurrScript]->m_strName;
		dlg.m_strTitle = game[game.m_nCurrScript]->m_strTitle;

		CScriptArray *pScript = game[game.m_nCurrScript];

		if ((dlg.DoModal()==IDOK) && 
			((pScript->m_strName != dlg.m_strName) || 
			(pScript->m_strTitle != dlg.m_strTitle))) {
			
			pScript->m_strName = dlg.m_strName;
			pScript->m_strTitle = dlg.m_strTitle;

			SetModifiedFlag (TRUE);
			RepaintAllViews();
		}
	}
}

void CScr4editDoc::OnUpdateLevelproperties(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CGameFile3 & game = m_game3; 
	pCmdUI->Enable (game.m_nScripts !=0);
}

void CScr4editDoc::OnAddnewlevel() 
{
	// TODO: Add your command handler code here
	CDlgNameDesc dlg;

	if (dlg.DoModal()==IDOK)	{
		CScriptArray *pScript = new CScriptArray;
		pScript->m_strName = dlg.m_strName;
		pScript->m_strTitle = dlg.m_strTitle;
		m_game3.AddScript (pScript);
		m_game3.m_nCurrScript = m_game3.m_nScripts -1;

		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}
}

void CScr4editDoc::OnUpdateAddnewlevel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CScr4editDoc::UpdateTitle ()
{
	CWinApp *pApp = AfxGetApp();
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd(); 

	CScr4editDoc *pDoc = this;
	char szTemp [1024];

	if (pDoc->IsModified() )	{
		wsprintf (szTemp, "%s* - %s ",
			pDoc ->GetTitle(),
			pApp->m_pszAppName);
	}
	else	{
		wsprintf (szTemp, "%s - %s ",
			pDoc ->GetTitle(),
			pApp->m_pszAppName);
	}
	
	char szTitle [2048];

	if (m_game3.GetSize()!=0)	{
		CScriptArray & script = * m_game3[m_game3.m_nCurrScript];
		wsprintf (szTitle, "%s[%d/%d] %c%s%c BK = %x; MX = %x; MY = %x", szTemp, 
				min ( m_game3. m_nCurrScript+1,m_game3.GetSize()),
				m_game3.GetSize(), 	34, script.m_strName.GetBuffer(1) , 34,
				script.m_nBkColor, script.m_nMX, script.m_nMY);
	}
	else	{
		wsprintf (szTitle, "%s[no script loaded]", szTemp);
	}

	CString str = szTitle;
	CString strOld;
	
	pMainFrame->GetWindowText(strOld);
	if (strOld != str)
		pMainFrame->SetWindowText(str);	
}

BOOL CScr4editDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	int nStatus = CDocument::OnSaveDocument(lpszPathName);
	UpdateTitle();
	
	return nStatus;
}

void CScr4editDoc::OnInsertlevelafter() 
{
	// TODO: Add your command handler code here
	if (m_game3.m_nScripts!=0)
	{
		CDlgNameDesc dlg;

		if (dlg.DoModal()==IDOK)
		{
			CScriptArray *pScript = new CScriptArray;
			pScript->m_strName = dlg.m_strName;
			pScript->m_strTitle = dlg.m_strTitle;

			if (m_game3.m_nCurrScript+1 < m_game3.m_nScripts) 
				m_game3.InsertScript (m_game3.m_nCurrScript+1, pScript);
			else
				m_game3.AddScript (pScript);

			m_game3.m_nCurrScript++;

			SetModifiedFlag (TRUE);
			RepaintAllViews();
		}
	}	
}

void CScr4editDoc::OnUpdateInsertlevelafter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.m_nScripts!=0);	
}

void CScr4editDoc::OnDeletelevel() 
{
	// TODO: Add your command handler code here
	if (m_game3.m_nScripts!=0)
	{
		if ( AfxMessageBox ("Delete current level ?\nConfirm ?",
			 MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
		{
			delete m_game3[m_game3.m_nCurrScript];
			m_game3.RemoveScript (m_game3.m_nCurrScript);
		
			if ((m_game3.m_nCurrScript == m_game3.m_nScripts)
				&& (m_game3.m_nCurrScript!=0))
					m_game3.m_nCurrScript --;

			SetModifiedFlag (TRUE);
			RepaintAllViews();
		}
	}
}

void CScr4editDoc::OnUpdateDeletelevel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.m_nScripts!=0);	
	
}

void CScr4editDoc::OnRemoveall() 
{
	// TODO: Add your command handler code here
	if (m_game3.m_nScripts!=0)
	{
		if ( AfxMessageBox ("Clear current level ?\nConfirm ?",
			 MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
		{
			m_game3 [m_game3.m_nCurrScript] ->Forget();
			SetModifiedFlag (TRUE);
			RepaintAllViews();
		}
	}
}

void CScr4editDoc::OnUpdateRemoveall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.m_nScripts!=0);		
}

void CScr4editDoc::OnDecbkcolor() 
{
	// TODO: Add your command handler code here
	if (m_game3.m_nScripts!=0)
	{
		CScriptArray & script = * m_game3[m_game3.m_nCurrScript];
		script.m_nBkColor --;

		if (script.m_nBkColor < 0x10 || 
			script.m_nBkColor >= 0xf0)
			script.m_nBkColor = 0xef;

		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}
}

void CScr4editDoc::OnUpdateDecbkcolor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.m_nScripts !=0);
}

void CScr4editDoc::OnIncbkcolor() 
{
	// TODO: Add your command handler code here
	if (m_game3.m_nScripts!=0)
	{
		CScriptArray & script = * m_game3[m_game3.m_nCurrScript];
		script.m_nBkColor ++;

		if (script.m_nBkColor < 0x10 || 
			script.m_nBkColor >= 0xf0)
			script.m_nBkColor = 0x10;

		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}
}

void CScr4editDoc::OnUpdateIncbkcolor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.m_nScripts !=0);
	
}

void CScr4editDoc::OnDefaultbkcolor() 
{
	// TODO: Add your command handler code here
	if (m_game3.m_nScripts!=0)
	{
		CScriptArray & script = * m_game3[m_game3.m_nCurrScript];
		script.m_nBkColor =0;

		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}
}

void CScr4editDoc::OnUpdateDefaultbkcolor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.m_nScripts !=0);
}

void CScr4editDoc::OnInformation() 
{
	// TODO: Add your command handler code here
	/*
	CDlgNameDesc dlg;
	dlg.SetCaption ("Edit database information");
	dlg.m_strName = m_game3.m_strName ;
	dlg.m_strTitle = m_game3.m_strInformation ;

	if ((dlg.DoModal()==IDOK) && ((m_game3.m_strName != dlg.m_strName) ||
			m_game3.m_strInformation != dlg.m_strTitle) )	{
		m_game3.m_strName = dlg.m_strName;
		m_game3.m_strInformation = dlg.m_strTitle;
		SetModifiedFlag (TRUE);
		RepaintAllViews();
	}
	*/

	CDbSheet sheet("Game database");

	// Page 1
	sheet.m_page1.m_strName = m_game3.m_strName;
	sheet.m_page1.m_strTitle = m_game3.m_strInformation;

	// Page 2
	sheet.m_page2.m_nHP = 
		m_game3.m_settings.m_nHP;
	sheet.m_page2.m_nLives = 
		m_game3.m_settings.m_nLives;
	sheet.m_page2.m_nMaxHP = 
		m_game3.m_settings.m_nMaxHP;
	sheet.m_page2.m_nMaxLives = 
		m_game3.m_settings.m_nMaxLives;
	
	sheet.m_page2.m_bAtDeathResetHP = 
		m_game3.m_settings.m_bAtDeathResetHP;
	sheet.m_page2.m_bAtDeathResetLev = 
		m_game3.m_settings.m_bAtDeathResetLev;

	// Page 3

	sheet.m_page3.m_bAtLevelResetHP = 
		m_game3.m_settings.m_bAtLevelResetHP;

	sheet.m_page3.m_bContinuity = 
		m_game3.m_settings.m_bContinuity;

	sheet.m_page3.m_bForceDefObj = 
		m_game3.m_settings.m_bForceDefObj;

	sheet.m_page3.m_bInheritPlrObj = 
		m_game3.m_settings.m_bInheritPlrObj;

	sheet.m_page3.m_bResizeLevel = 
		m_game3.m_settings.m_bResizeLevel;

	if (sheet.m_page3.m_bResizeLevel)
	{
		sheet.m_page3.m_nLevelLen = 
			m_game3.m_settings.m_nLevelLen;

		sheet.m_page3.m_nLevelHei = 
			m_game3.m_settings.m_nLevelHei;
	}
	else
	{
		sheet.m_page3.m_nLevelLen = 
			640;

		sheet.m_page3.m_nLevelHei = 
			480;
	}

	if (sheet.DoModal()==IDOK)
	{
		// Page 1
		m_game3.m_strName = sheet.m_page1.m_strName;
		m_game3.m_strInformation = sheet.m_page1.m_strTitle;

		// Page 2
		m_game3.m_settings.m_nHP = sheet.m_page2.m_nHP ;
		m_game3.m_settings.m_nLives = sheet.m_page2.m_nLives ;
		m_game3.m_settings.m_nMaxHP = sheet.m_page2.m_nMaxHP ;
		m_game3.m_settings.m_nMaxLives = sheet.m_page2.m_nMaxLives;

		m_game3.m_settings.m_bAtDeathResetHP = sheet.m_page2.m_bAtDeathResetHP ;
		m_game3.m_settings.m_bAtDeathResetLev = sheet.m_page2.m_bAtDeathResetLev ;

		// Page 3

		m_game3.m_settings.m_bAtLevelResetHP = 
			sheet.m_page3.m_bAtLevelResetHP ;
		
		m_game3.m_settings.m_bContinuity = 
			sheet.m_page3.m_bContinuity ;

		m_game3.m_settings.m_bForceDefObj =
			sheet.m_page3.m_bForceDefObj ; 

		m_game3.m_settings.m_bInheritPlrObj =
			sheet.m_page3.m_bInheritPlrObj ;

		m_game3.m_settings.m_bResizeLevel =
			sheet.m_page3.m_bResizeLevel ;
		
		if (sheet.m_page3.m_bResizeLevel)
		{
			m_game3.m_settings.m_nLevelLen = 
				sheet.m_page3.m_nLevelLen ; 

			m_game3.m_settings.m_nLevelHei = 
				sheet.m_page3.m_nLevelHei ; 
		}
	}
}

void CScr4editDoc::OnUpdateInformation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CScr4editDoc::OnExportDeclarations() 
{
	// TODO: Add your command handler code here
    CString l_strFilesFilter =
        "Text files |*.txt"\
        "|";

	CFileDialog dlg( FALSE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Export declarations"; 
	dlg.m_ofn.lpstrDefExt = ".txt";
    
    if (dlg.DoModal()==IDOK)  {

		CString strFilename = dlg.GetFileName();

		CFile file;
		CFileException e;

		if (!file.Open(strFilename, CFile::modeCreate 
			| CFile::modeWrite | CFile::typeBinary, &e ))
		{
#ifdef _DEBUG
			afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
		return ;
		}		

		CString str;
		CProtoArray & arrProto = m_game3.m_arrProto;
		CStrValArray & arrClasses = m_game3.m_arrClasses;

		str = CString ("") +
			"// Constants declarations for C/C++\r\n" +
			"// ====================================\r\n\r\n"+
			"// *** OBJECT TYPES\r\n\r\n" ;

		WriteString (str, file);

		int n;
		for (n=0; n<m_game3.m_arrProto.GetSize(); n++)
		{

			CString strName = CString ("") + arrProto[n].m_szName + "\r\n" ;
			strName.TrimRight();
			strName.TrimLeft();
			strName.MakeUpper();

			int i;
			for (i=0; i<strName.GetLength();i++)
			{
				if ((strName[i] >= 'A'
					&& strName[i] <= 'Z') ||
					(strName[i] >= '0'
					&& strName[i] <= '9') )
				{}
				else
					strName.SetAt (i, '_');
			}

			str.Format("#define TYPE_%-40s %d \r\n", strName, n);

			WriteString (str, file);
		}

		str = "\r\n// *** OBJECT CLASSES\r\n\r\n" ;
		WriteString (str, file);

		for (n=0; n<arrClasses.GetSize(); n++)
		{
			CString strName = arrClasses[n]->m_strLabel;
			strName.TrimRight();
			strName.TrimLeft();
			strName.MakeUpper();

			int i;
			for (i=0; i<strName.GetLength();i++)
			{
				if ((strName[i] >= 'A'
					&& strName[i] <= 'Z') ||
					(strName[i] >= '0'
					&& strName[i] <= '9') )
				{}
				else
					strName.SetAt (i, '_');
			}

			str. Format ("#define CLASS_%-40s0x%x\r\n",
				strName,
				arrClasses[n]->m_nVal);
				
			WriteString (str, file);
		}


		file.Close();
	}
}

void CScr4editDoc::OnUpdateExportDeclarations(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editDoc::OnExportDiagnostic() 
{
	// TODO: Add your command handler code here
    CString l_strFilesFilter =
        "Text files |*.txt"\
        "|";

	CFileDialog dlg( FALSE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Diagnostic report"; 
	dlg.m_ofn.lpstrDefExt = ".txt";
    
    if (dlg.DoModal()==IDOK)  {

		CString strFilename = dlg.GetFileName();

		CFile file;
		CFileException e;

		if (!file.Open(strFilename, CFile::modeCreate 
			| CFile::modeWrite | CFile::typeBinary, &e ))
		{
#ifdef _DEBUG
			afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
		return ;
		}		
		
		CString str;

		CProtoArray & arrProto = m_game3.m_arrProto;
		CStrValArray & arrClasses = m_game3.m_arrClasses;
		COBL3Array & arrOBL3 = m_game3.m_arrOBL3;

		CTime time = CTime::GetCurrentTime();
		str = CString("Script Editor 4.0\r\nDiagnostic report - ") +
			time.GetMonth() + "/" 
			+ time.GetDay() + "/" 
			+time.GetYear() + "\r\n\r\n" ;

		WriteString(str,file);

		str = CString("")+ "STATISTICS"+"\r\n" 
		 + "============================" + "\r\n"
		 + CString("\r\nScripts     : ") + m_game3.GetSize()
		 + CString("\r\nFrames sets : ") + m_game3.m_arrOBL3.GetSize()
		 + CString("\r\nObject types: ") + m_game3.m_arrProto.GetSize()
		 + CString("\r\nClasses     : ") + m_game3.m_arrClasses.GetSize();

		WriteString (str, file);


		str = CString("\r\n\r\nEntries per script................\r\n");
		WriteString (str, file);

		int n;
		int nSize = m_game3.GetSize();
		for  (n=0; n<nSize; n++)
		{
			CScriptArray & script = * m_game3[n];
			str.Format ("# %4d - %-40s %4d\r\n",
				n+1, script.m_strName, script.GetSize());
			WriteString (str, file);
			
		}
		
		OutputDebugString ("OUT\n");


		 str = CString("\r\n\r\nOBL3/OBL4 FRAME SET\r\n")
		 + "============================" + "\r\n\r\n";
		WriteString (str, file);

		for (n=0; n<m_game3.m_arrOBL3.GetSize(); n++)
		{
			str = CString("Frame set #    : ") + (n+1) + CString("\r\n") 
				+ CString("Name           : ") + m_game3.m_arrOBL3[n]->m_szName + CString("\r\n") 
				+ CString("Source filename: ")  
				+ m_game3.m_arrOBL3[n]->m_szFilename + CString("\r\n") 
				+ CString("Base Frame #   : ") 
				+ m_game3.m_arrOBL3[n]->GetSize() + "\r\n" 
				+ CString("Total frames   : ") + m_game3.m_arrOBL3[n]->GetSize() + "\r\n" 
				+ CString("\r\n\r\n") ;
				WriteString (str, file);
		}

		str = CString("\r\nOBJECTS TYPES\r\n")
		 + "============================" + "\r\n\r\n";
		WriteString (str, file);

		for (n=0; n<m_game3.m_arrProto.GetSize(); n++)
		{
			char sz[16];
			if (arrProto[n].m_nObjectKey)
				wsprintf(sz, "0x%x", arrProto[n].m_nObjectKey);
			else strcpy(sz, "(no key)");

			str = CString("")
				+ "Type #          : " + (n+1)+ "\r\n" 
				+ "Name            : " + arrProto[n].m_szName + "\r\n" 
				+ "Class           : " 
				+ arrClasses.StringFor (arrProto[n].m_nClass) + "\r\n" 
				+ "Frame set #     : "  
				+ ((int)arrProto[n].m_nFrameSet +1) 
				+ " ["  
				+ arrOBL3[arrProto[n].m_nFrameSet]->m_szName 
				+ "] ~" + ((int) arrProto[n].m_nFrameNo +1) + "\r\n"
				+ "TriggerKey      : " +sz +
				(arrProto[n].m_nTriggerType==0 ? " - [RECIPIANT]" : " - [GENERATOR]") + "\r\n"
			    + "MoveSpeed       : " + (int) arrProto[n].m_nMoveSpeed + "\r\n"
				+ "AniSpeed        : " + (int) arrProto[n].m_nAniSpeed
				+ "\r\n\r\n";

			WriteString (str, file);
		}

		str = CString("\r\nOBJECT CLASSES\r\n")
		 + "============================" + "\r\n\r\n";
		WriteString (str, file);

		for (n=0; n<arrClasses.GetSize(); n++)
		{
			char sz[12];
		
			if (	arrClasses[n]->m_nVal <0x10)
				wsprintf(sz, "0x0%x", arrClasses[n]->m_nVal );
			else
				wsprintf(sz, "0x%x", arrClasses[n]->m_nVal );

			str = CString ("") +
				sz + " " + arrClasses[n]->m_strLabel + 
				(arrClasses[n]->m_bSystem==FALSE ? "" : " [SYSTEM]") +
				"\r\n\r\n";

			WriteString (str, file);
		}


		str = CString("\r\nSCRIPTS ARRAYS\r\n")
		 + "============================" + "\r\n";
		WriteString (str, file);

		for (n=0; n<m_game3.m_nScripts; n++)
		{
			CScriptArray & script = * m_game3[n];

			char sz[16];
			wsprintf(sz, "0x%x", script.m_nBkColor);
			
			str = CString ("\r\n") +
				"\r\n ----------------------------------------" +
				"\r\n Script #      : " + (n+1) + 
				"\r\n Name          : " + script.m_strName+
				"\r\n Title         : " + script.m_strTitle+
				"\r\n Member entries: " + script.GetSize() +
				"\r\n BkColor       : " + sz +
				"\r\n ----------------------------------------" +
				"\r\n";

			WriteString (str, file);

			int i;
			for (i=0; i<script.GetSize(); i++)
			{
				CScriptEntry & entry = script[i];
				if (entry.m_nTriggerKey)
					wsprintf(sz, "0x%x", entry.m_nTriggerKey);
				else strcpy(sz, "(no key)");
				str = CString ("") +
					"\r\n Entry #       : " + (i+1) + 
					"\r\n FrameSet      : " + (int) (entry.m_nFrameSet+ 1) + 
						" [" + m_game3.m_arrOBL3[entry.m_nFrameSet]->m_szName + "]" +
					"\r\n FrameNo       : " + (int) (entry.m_nFrameNo+1) +
					"\r\n Object #      : " + (int) (entry.m_nProto +1) +
					    " [" + arrProto[entry.m_nProto].m_szName +"]" +
					"\r\n Class    : "	+ arrClasses.StringFor (arrProto[entry.m_nProto].m_nClass) +
					"\r\n Sub. Class    : "	+ (int) (entry.m_nSubClass) +
					"\r\n Trigger Key   : " + sz +
					"\r\n X position    : " + (int) entry.m_nX +
					"\r\n Y position    : " + (int) entry.m_nY +
					"\r\n Unused        : " + (int) entry.m_nBidon +
					"\r\n ExtraData ptr : " + (int) entry.m_pExtraData +
					"\r\n" +
					"\r\n";
				WriteString (str, file);
			}
		}
		file.Close();
	}
}

void CScr4editDoc::OnUpdateExportDiagnostic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editDoc::WriteString (const char *szText,   CFile & file)
{
	file.Write (szText, strlen (szText));
}


void CScr4editDoc::OnPlus() 
{
	// TODO: Add your command handler code here
	CGameFile3 & game = m_game3; 
	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)		
		&& game[game.m_nCurrScript]->m_bSelection)	{

		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry & entry = script[script.m_nCurrEntry];
		COBL3Array & arrOBL3 = game.m_arrOBL3;
		COBL3Filter & filter = * arrOBL3 [entry.m_nFrameSet];

		if (entry.m_nFrameNo < filter.GetSize()-1)
		{
			entry.m_nFrameNo++;
			SetModifiedFlag (TRUE);
			RepaintAllViews();
		}
	}
		
}

void CScr4editDoc::OnUpdatePlus(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editDoc::OnMinus() 
{
	// TODO: Add your command handler code here
	CGameFile3 & game = m_game3; 
	if ((game.m_nScripts !=0) &&
		(game[game.m_nCurrScript]->GetSize()!=0)		
		&& game[game.m_nCurrScript]->m_bSelection)	{

		CScriptArray & script = * game[game.m_nCurrScript];
		CScriptEntry & entry = script[script.m_nCurrEntry];
		COBL3Array & arrOBL3 = game.m_arrOBL3;
		COBL3Filter & filter = * arrOBL3 [entry.m_nFrameSet];

		if (entry.m_nFrameNo >0)
		{
			entry.m_nFrameNo--;
			SetModifiedFlag (TRUE);
			RepaintAllViews();
		}
	}
		
	
}

void CScr4editDoc::OnUpdateMinus(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editDoc::SetTitle(LPCTSTR lpszTitle) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (m_strPathName != "") {
		CDocument::SetTitle(lpszTitle);
		UpdateTitle	();
	}
	else {
		CDocument::SetTitle(lpszTitle);
	}
}

void CScr4editDoc::ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::ReportSaveLoadException(lpszPathName, e, bSaving, nIDPDefault);
}

void CScr4editDoc::OnExportClass() 
{
	// TODO: Add your command handler code here
    CString l_strFilesFilter =
        "Data files |*.dat"\
        "|";

	CFileDialog dlg( FALSE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Export class information"; 
	dlg.m_ofn.lpstrDefExt = ".dat";
    
    if (dlg.DoModal()==IDOK)  {

		CString strFilename = dlg.GetFileName();

		CFile file;
		CFileException e;

		if (!file.Open(strFilename, CFile::modeCreate 
			| CFile::modeWrite | CFile::typeBinary, &e ))
		{
#ifdef _DEBUG
			afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
		return ;
		}		

		m_game3.m_arrClasses.Write(file, TRUE);
		file.Close();
	}
}

void CScr4editDoc::OnUpdateExportClass(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}



void CScr4editDoc::OnImportClass() 
{
	// TODO: Add your command handler code here
    CString l_strFilesFilter =
        "Data files |*.dat"\
        "|";

	CFileDialog dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Import class information"; 
	dlg.m_ofn.lpstrDefExt = ".dat";
    
    if (dlg.DoModal()==IDOK)  {

		CString strFilename = dlg.GetFileName();

		CFile file;
		CFileException e;

		if (!file.Open(strFilename, CFile::modeRead 
			| CFile::typeBinary, &e ))
		{
#ifdef _DEBUG
			afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
		return ;
		}		

		m_game3.m_arrClasses.Read(file, TRUE);
		file.Close();
	}
	
}

void CScr4editDoc::OnUpdateImportClass(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CScr4editDoc::OnFrameedit() 
{
	// TODO: Add your command handler code here
	CDlgFrameList dlg;
	dlg. m_pDoc = this;

	dlg.DoModal();
	RepaintAllViews();

}

void CScr4editDoc::OnUpdateFrameedit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editDoc::OnUpdateframes() 
{
	// TODO: Add your command handler code here
	CString strError;
	if (m_game3.UpdateOBL3(strError)!=TRUE)
	{
		CString str = CString ("") +
			"The following frame set(s) couldn't be updated:\r\n\r\n" +
			strError;

		CDlgMessageBox dlg;
		dlg.SetCaption ("Update frame sets errors");
		dlg.m_strText = str;
		dlg.DoModal ();
	}

	RepaintAllViews();
}

void CScr4editDoc::OnUpdateUpdateframes(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

BOOL CScr4editDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	return TRUE;
}



void CScr4editDoc::OnObjectswizard() 
{
	// TODO: Add your command handler code here
	CGameFile3 & game = m_game3;
	CProtoArray & arrProto = m_game3.m_arrProto;
	CStrValArray & arrClasses = m_game3.m_arrClasses;

	CDlgObjsWiz dlg;
	dlg.m_pDoc = this;
	dlg.m_nClass =0;
	if (dlg.DoModal()==IDOK)
	{
		
		CSortArray arrayFiles;
		_finddata_t data;
		int handle;
		
		handle = _findfirst( dlg.m_strFilename.GetBuffer(1),
			&data);

		if (handle!=-1)
		{
			arrayFiles.Add(data.name);

			while (_findnext (handle, &data)!=-1)
			{
				arrayFiles.Add(data.name);
			} // while

			_findclose( handle );

		} // if

		int n;
		for (n=0; n<arrayFiles.GetSize(); n++)
		{
			memcpy (data.name, arrayFiles[n]->GetBuffer(1),
				arrayFiles[n]->GetLength()+1);
			if (WizardAddObject (data, dlg.m_nClass))
				SetModifiedFlag(TRUE);
		}

	}
}


void CScr4editDoc::OnUpdateObjectswizard(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

BOOL CScr4editDoc::WizardAddObject (_finddata_t & data, int nClass)
{
	char szFilePath[_MAX_PATH];

	CGameFile3 & game = m_game3;
	CProtoArray & arrProto = m_game3.m_arrProto;
	CStrValArray & arrClasses = 
		m_game3.m_arrClasses;
	
	COBL3Filter *pFilter = new COBL3Filter;
	if ( _fullpath(szFilePath, data.name, _MAX_PATH)
			&& (game.m_arrOBL3.GetFilePathIndex(szFilePath)==-1 )
			&&	(pFilter->Extract (szFilePath)!=FALSE)
			&&  (pFilter->GetSize()!=0)	)
	{
		CProto proto;
		proto.m_nClass = arrClasses[nClass]->m_nVal;	
		proto.m_nFrameNo= 0;
		proto.m_nFrameSet = game.m_arrOBL3.GetSize();
		proto.m_nTriggerType = 0;
		proto.m_nObjectKey = 0;
		proto.m_bAnimate = FALSE;
		ZeroMemory(proto.m_szName, 32);
		memcpy (proto.m_szName, data.name, 31);
		char *pDot = strrchr (proto.m_szName, '.');
		if (pDot && (_stricmp (pDot, ".obl")==0 ||
			strlen(pDot)<4)) 
				*pDot=0;

		arrProto.Add (proto);		
		
		pFilter->SetName ( CString(data.name));
		pFilter->SetFilename ( CString(szFilePath));
		game.m_arrOBL3. Add (pFilter);	

		return TRUE;
	}

	else  
	{
		delete pFilter;
		return FALSE;
	}
}


void CScr4editDoc::OnMovelevel() 
{
	// TODO: Add your command handler code here
	CDlgMoveLevel dlg;
	dlg.m_pDoc = this;
	if (dlg.DoModal()==IDOK)
	{

		int nCurrLevel = m_game3.m_nCurrScript;
		int nTarget = dlg.m_nTarget;
		if (nTarget!= nCurrLevel)
		{
			CScriptArray *pScript = m_game3[nCurrLevel];
			m_game3.RemoveScript(nCurrLevel);
			if (nTarget>nCurrLevel)
				nTarget--;

			if (dlg.m_nInsertMode==0) {
				m_game3.InsertScript(nTarget, pScript);
				m_game3.m_nCurrScript = nTarget;
			}
			else {
				m_game3.InsertScript(nTarget+1, pScript);
				m_game3.m_nCurrScript = nTarget+1;
			}

			SetModifiedFlag(TRUE);
		}
	}

	RepaintAllViews();
}

void CScr4editDoc::OnUpdateMovelevel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.GetSize()!=0);
}

void CScr4editDoc::OnDuplicatelevel() 
{
	// TODO: Add your command handler code here
	CScriptArray *pNewScript = new CScriptArray();
	* pNewScript = *m_game3[m_game3.m_nCurrScript];

	m_game3.InsertScript(m_game3.m_nCurrScript+1, pNewScript);
	//m_game3.m_nCurrScript = m_game3.GetSize()-1;
	RepaintAllViews();

}

void CScr4editDoc::OnUpdateDuplicatelevel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_game3.GetSize()!=0);
	
}

void CScr4editDoc::OnFileSendMail() 
{
	// TODO: Add your command handler code here
	CDocument::OnFileSendMail() ;
}

void CScr4editDoc::OnUpdateFileSendMail(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editDoc::OnHome() 
{
	// TODO: Add your command handler code here
	CScr4editDoc *pDoc = this;
	CGameFile3 & game = pDoc->m_game3; 

	if (game.GetSize()!=0)
	{
	
		CScriptArray & script = * game[game.m_nCurrScript];

		script.m_nMX=0;
		script.m_nMY=0;
		script.m_bSelection = FALSE;
		RepaintAllViews();	
	}
	
}

void CScr4editDoc::OnUpdateHome(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editDoc::OnEditsortdata() 
{
	// TODO: Add your command handler code here
	int nSize = m_game3.m_arrProto.GetSize();
	char **ppChoices = (char**) malloc(4 * nSize + 4);

	for (int i=0; i<nSize; i++)
	{
		ppChoices[i] = m_game3.m_arrProto[i].GetName();
	}

	ppChoices[nSize]=0;

	char *ppContent[]=
	{
		"SEND_TO_BACK",
		"SEND_TO_FRONT",
		"DELETE",
		NULL
	};

	CDlgTagList dlg(IDD_TAGEDIT2, ppChoices, ppContent);
	//dlg.m_pDoc = this;
	dlg.SetTitle("Filter options");
	dlg.m_pArray = &m_arrSort;
	dlg.DoModal();	

	free(ppChoices);
}

void CScr4editDoc::OnUpdateEditsortdata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editDoc::OnLoadsortdata() 
{
	// TODO: Add your command handler code here
    CString l_strFilesFilter =
        "Custom filters |*.fil"\
        "|";

	CFileDialog dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY //| OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Open custom filter"; 
	dlg.m_ofn.lpstrDefExt = ".fil";
    
    if (dlg.DoModal()==IDOK)  {

		CString strFilename = dlg.GetFileName();
		CFile file;
		CFileException e;

		if (file.Open(strFilename, CFile::modeRead 
			| CFile::typeBinary, &e ))
		{
			char szSig[]="1234";
			file.Read(szSig,4);

			if (strcmp(szSig, "FIL3")==0)
			{
				m_arrSort.Forget();
				m_arrSort.Read(file);
			}
			else
			{
				AfxMessageBox("Wrong format");
			}
	
			file.Close();
		}
		else
		{
			AfxMessageBox("Cannot open file");
		}
	}	
}

void CScr4editDoc::OnUpdateLoadsortdata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CScr4editDoc::OnSavesortdata() 
{
	// TODO: Add your command handler code here
    CString l_strFilesFilter =
        "Custom filters |*.fil"\
        "|";

	CFileDialog dlg( FALSE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Save custom filter"; 
	dlg.m_ofn.lpstrDefExt = ".fil";
    
    if (dlg.DoModal()==IDOK)  {

		CString strFilename = dlg.GetFileName();
		CFile file;
		CFileException e;

		if (file.Open(strFilename, CFile::modeWrite
			| CFile::modeCreate
			| CFile::typeBinary, &e ))
		{
			file.Write("FIL3",4);
			m_arrSort.Write(file);
			file.Close();			
		}
		else
		{
			AfxMessageBox("Cannot create file");
		}
	}
}

void CScr4editDoc::OnUpdateSavesortdata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CScr4editDoc::OnClearSortData() 
{
	// TODO: Add your command handler code here
	if (AfxMessageBox("Clear setting?\nAre you sure?",
		MB_YESNO)==IDYES)
	{
		m_arrSort.Forget();
	}
}

void CScr4editDoc::OnUpdateClearSortData(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CScr4editDoc::OnTest123() 
{
	// TODO: Add your command handler code here
	/*CDlgObjectsList dlg;
	dlg.m_pDoc = this;
	dlg.m_strOK = "&OK";

	dlg.DoModal();	
	*/

	char *ppContent[]=
	{
		"UP",
		"DOWN",
		"LEFT",
		"RIGHT",
		NULL
	}; 

	int pValue[]=
	{
		0,
		1,
		2,
		3,
		-1
	};

  	CFile file;

	CExtraData data;
	CDlgIntArray dlg(ppContent, pValue, NULL);
	dlg.m_pExtraData = &data;
	//dlg.DoModal();

	CExtraArray arr;

	if (file.Open("test.dat",  CFile::modeRead | 
		CFile::typeBinary))
	{
		arr.Read(file);  	
		file.Close();
	}

	CDlgIntAll dlg2(ppContent, pValue, NULL);
	dlg2.m_pArray = &arr;
	dlg2.DoModal();

	if (file.Open("test.dat", CFile::modeCreate 
		| CFile::modeWrite |  CFile::typeBinary))
	{
		arr.Write(file);  	
		file.Close();
	}
}

void CScr4editDoc::OnEditsyspaths() 
{
	// TODO: Add your command handler code here

	char *ppContent[]=
	{
		"UP",
		"DOWN",
		"LEFT",
		"RIGHT",
		NULL
	}; 

	int pValue[]=
	{
		0,
		1,
		2,
		3,
		NULL
	};

	CDlgIntAll dlg(ppContent, pValue, NULL);
	dlg.m_pArray = &m_game3.m_arrExtra; //&arr;
	dlg.DoModal();
}

void CScr4editDoc::OnUpdateEditsyspaths(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

