// OBL3VIEWDoc.cpp : implementation of the COBL3VIEWDoc class
//

#include "stdafx.h"
#include "OBL3VIEW.h"

#include "OBL3VIEWDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWDoc

IMPLEMENT_DYNCREATE(COBL3VIEWDoc, CDocument)

BEGIN_MESSAGE_MAP(COBL3VIEWDoc, CDocument)
	//{{AFX_MSG_MAP(COBL3VIEWDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWDoc construction/destruction

COBL3VIEWDoc::COBL3VIEWDoc()
{
	// TODO: add one-time construction code here

}

COBL3VIEWDoc::~COBL3VIEWDoc()
{
        CleanUp();
}

BOOL COBL3VIEWDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
    CleanUp();

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWDoc serialization

void COBL3VIEWDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
        ar. Write("OBL4",4);
        ar << (UINT) 8;
        ar << m_obl3Filter.m_arrFrames.GetSize();
        int x;
        for (x=0; x<m_obl3Filter.m_arrFrames.GetSize(); x++)
        {
            CSS3Frame *l_pFrame = (CSS3Frame*) m_obl3Filter.m_arrFrames[x];
            ar << l_pFrame->m_nLen;
            ar << l_pFrame->m_nHei;
            
        }

	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWDoc diagnostics

#ifdef _DEBUG
void COBL3VIEWDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COBL3VIEWDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COBL3VIEWDoc commands

void COBL3VIEWDoc::OnFileOpen() 
{

    CString l_strFilesFilter =
        "All supported formats|*.obl;*.ima;*.mcx|"\
        "Static Images (*.ima;*.mcx)|*.ima;*.mcx|"\
        "OBL3/OBL4 Format|*.obl|"\
        "|";

	// TODO: Add your command handler code here
    CFileDialog l_Dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    l_Dlg.m_ofn.lpstrTitle = "Open"; 
    
    int iStatus = l_Dlg.DoModal(); 

    if (iStatus==IDOK)
    {
        CleanUp();
        DeleteContents();
        CString l_szText =  l_Dlg.GetPathName();
        UpdateAllViews(NULL) ;

        LoadFile(l_Dlg.GetPathName());

    }	


}

BOOL COBL3VIEWDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

    CleanUp();
    DeleteContents();
    LoadFile(lpszPathName);
    UpdateAllViews(NULL) ;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}

void COBL3VIEWDoc::CleanUp()
{

    while (m_obl3Filter.m_arrFrames.GetSize())
    {
        delete m_obl3Filter.m_arrFrames[0];
        m_obl3Filter.m_arrFrames.RemoveAt(0);
    }
}

void COBL3VIEWDoc::LoadFile(CString p_strFilename)
{
    
        int iStatus = m_obl3Filter.Extract(p_strFilename);
        if (iStatus!=TRUE)
        {
            AfxMessageBox("SSV3 ERROR:\nCannot read or understand this file");
            SetPathName( "(Unknown.obl)", FALSE);
        }
        else
        {
            CDocument::OnOpenDocument(p_strFilename);
            SetTitle( p_strFilename );
            UpdateAllViews( NULL, 0, NULL);
            SetPathName( p_strFilename, TRUE );
        }

}

void COBL3VIEWDoc::OnFileSave() 
{
	// TODO: Add your command handler code here
	
}

void COBL3VIEWDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable(FALSE);
	
}

void COBL3VIEWDoc::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	
}

void COBL3VIEWDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable(FALSE);
	
}
