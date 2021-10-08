// ReptelDoc.cpp : implementation of the CReptelDoc class
//

#include "stdafx.h"
#include "resource.h"
//#include "MiniApp Reptel.h"
#include "ReptelDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReptelDoc

IMPLEMENT_DYNCREATE(CReptelDoc, CDocument)

BEGIN_MESSAGE_MAP(CReptelDoc, CDocument)
	//{{AFX_MSG_MAP(CReptelDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#include "Entry.h"

/////////////////////////////////////////////////////////////////////////////
// CReptelDoc construction/destruction

CReptelDoc::CReptelDoc()
{
	// TODO: add one-time construction code here

}

CReptelDoc::~CReptelDoc()
{
    if (m_arrEntry.GetSize())
    {
        while (m_arrEntry.GetSize())
        {
                delete m_arrEntry[0];
                m_arrEntry.RemoveAt(0);
        }
    }
}



BOOL CReptelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


    if (m_arrEntry.GetSize())
    {
        while (m_arrEntry.GetSize())
        {
            delete m_arrEntry[0];
            m_arrEntry.RemoveAt(0);
                     
        }
    }

    m_arrEntry.SetSize(0,10);
    m_nEntry=0;  

    CListView *l_pListView = GetView();
    CListCtrl &l_rListCtrl = l_pListView->GetListCtrl();

    l_rListCtrl.DeleteAllItems();
    CImageList *l_pOldImageList = l_rListCtrl.GetImageList(LVSIL_NORMAL);

    for (int x=0; x<l_pOldImageList->GetImageCount(); x++)
            l_pOldImageList->Remove(0);

	HICON hIcon = ::LoadIcon (AfxGetResourceHandle(),
            MAKEINTRESOURCE(IDI_ICON0));
	m_ImageLarge.Add(hIcon);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CReptelDoc serialization

void CReptelDoc::Serialize(CArchive& ar)
{
    CString l_strSig = "MiniApp Reptel v1.0" ;
    CString l_temp;

    int l_nRealEntry =0;
    int l_nImages;
    int x;



	if (ar.IsStoring())
	{
		// TODO: add storing code here

        CListCtrl &l_rListCtrl = GetView()->GetListCtrl();
        CImageList *l_pImageList = 
            l_rListCtrl.GetImageList(LVSIL_NORMAL);

        ar << l_strSig;
        for (x=0; x<m_nEntry; x++)
            if (((CEntry*)(m_arrEntry[x])) ->m_nDeleted==FALSE)
                l_nRealEntry++;
        
        ar << l_nRealEntry;

        ar << (int) l_pImageList->GetImageCount();

        CEntry* l_pEntry;

        for (x=0; x<m_nEntry; x++)
        {
            l_pEntry = (CEntry*)(m_arrEntry[x]);

            if ( (l_pEntry->m_nDeleted)==FALSE)
            {
                ar << l_pEntry->m_nEntry   ;
                ar << l_pEntry->m_nImage   ;
                ar << l_pEntry->m_strAddr  ;
                ar << l_pEntry->m_strInfo  ;
                ar << l_pEntry->m_strName  ;
                ar << l_pEntry->m_strTel   ;
            }
        }


        m_ImageLarge.Write(&ar);


	}
	else
	{
		// TODO: add loading code here

        ar >> l_temp;

        if (l_temp!=l_strSig)
        {
            AfxThrowArchiveException(CArchiveException::badIndex); 
            return;
        }

        ar >> m_nEntry;
        ar >> l_nImages;


        if (m_arrEntry.GetSize())
        {
            while (m_arrEntry.GetSize())
            {
                delete m_arrEntry[0];
                m_arrEntry.RemoveAt(0);
            }
        }

        m_arrEntry.SetSize(0,10);
        CEntry* l_pEntry;

        for (x=0; x<m_nEntry; x++)
        {
            m_arrEntry.Add(new CEntry);
            l_pEntry = (CEntry*)(m_arrEntry[x]);
            
            ar >> l_pEntry->m_nEntry  ;
            ar >> l_pEntry->m_nImage  ;
            ar >> l_pEntry->m_strAddr  ;
            ar >> l_pEntry->m_strInfo ;
            ar >> l_pEntry->m_strName  ;
            ar >> l_pEntry->m_strTel  ;
        }
    
        CListView *l_pListView = GetView();
        CListCtrl &l_rListCtrl = l_pListView->GetListCtrl();

        l_rListCtrl.DeleteAllItems();
        
        CImageList l_sNewImageList;
        //l_sNewImageList. m_hImageList;

	    int iStatus = l_sNewImageList.Create(32,
		32,
		TRUE,			// list does include masks
		l_nImages,      // l_nImages,
		0 );			// list will grow

		HICON hIcon = ::LoadIcon (AfxGetResourceHandle(),
            MAKEINTRESOURCE(IDI_ICON0));

        for (x=0; x<l_nImages; x++)
			l_sNewImageList.Add(hIcon);

        l_sNewImageList.Read(&ar);

        HIMAGELIST l_hNewImageList = l_sNewImageList.Detach();

        CImageList *l_pOldImageList = l_rListCtrl.GetImageList(LVSIL_NORMAL);
        //HIMAGELIST l_hOldImageList =l_pOldImageList->Detach();
        //DeleteObject(l_hOldImageList);
        l_pOldImageList->Attach(l_hNewImageList);

        l_pOldImageList = l_rListCtrl.GetImageList(LVSIL_SMALL);
        l_pOldImageList->Attach(l_hNewImageList);

        l_rListCtrl.SetImageList(l_pOldImageList, LVSIL_NORMAL);
        l_rListCtrl.SetImageList(l_pOldImageList, LVSIL_SMALL);

        for ( x=0; x<m_nEntry ; x++)
        {
            l_pEntry = (CEntry*)(m_arrEntry[x]);

        	LV_ITEM lvI;        		// list view item structure
    
            lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	        lvI.state = 0;      
	        lvI.stateMask = 0;  

            lvI.iItem = l_rListCtrl.GetItemCount() ;

	        lvI.iSubItem = 0;

	        lvI.pszText = l_pEntry->m_strName.GetBuffer(256);
	        lvI.cchTextMax = 256;
	        lvI.iImage = l_pEntry->m_nImage;
	        lvI.lParam = (unsigned int) l_pEntry; 

            l_rListCtrl.InsertItem(&lvI);

	        l_rListCtrl.SetItemText( x,
			    1,                   
                l_pEntry->m_strTel.GetBuffer(256));

        	l_rListCtrl.SetItemText( x,
		    	2,
                l_pEntry->m_strAddr.GetBuffer(256));

	        l_rListCtrl.SetItemText( x,
			    3,
                l_pEntry->m_strInfo.GetBuffer(4096));

        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CReptelDoc diagnostics

#ifdef _DEBUG
void CReptelDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CReptelDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReptelDoc commands


BOOL CReptelDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}

BOOL CReptelDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocument::OnSaveDocument(lpszPathName);
}

CListView *CReptelDoc::GetView()
{

   POSITION l_pos = GetFirstViewPosition();
   if (l_pos != NULL)
   {
       CView* l_pView = GetNextView(l_pos);
       return (CListView*)l_pView;
   }   
    return NULL;
}
