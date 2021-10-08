// AppDoc.cpp : implementation of the CAppDoc class
//

#include "resource.h"
#include "stdafx.h"
#include "StaticEx.h"
#include "AppDoc.h"
#include "AppView.h"
#include "App.h"

#include "note.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppDoc

IMPLEMENT_DYNCREATE(CAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CAppDoc, CDocument)
	//{{AFX_MSG_MAP(CAppDoc)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppDoc construction/destruction

CAppDoc::CAppDoc()
{
	// TODO: add one-time construction code here
    m_nCritical= FALSE;
    m_bNoModify = FALSE;
    m_arrayNotes.SetSize(0,10);
    m_arrayAlarms.SetSize(0,10);

}

CAppDoc::~CAppDoc()
{

    DeleteLeftOvers();

}

BOOL CAppDoc::OnNewDocument()
{

    StoreMonth();
    
    if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

    DeleteLeftOvers();
    RestoreMonth();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAppDoc serialization

void CAppDoc::Serialize(CArchive& ar)
{      

    int iSize;
    int x,y;

    while (m_nCritical); // Wait for critical section to
                         // complete.

    m_nCritical = TRUE;  // Entering another critical section

    CNote *l_pNote;

    CString szPCA ("MiniApp Calendar v1.0");
    CString szTMP ("");
    
    iSize = m_arrayNotes.GetSize();

	if (ar.IsStoring())
	{
		// TODO: add storing code here
        // Compact document before commiting
        
        CleanUp();
        iSize = m_arrayNotes.GetSize();

        ar << szPCA;
        ar << iSize;
        for (y=0; y<iSize; y++)
        {
            l_pNote = (CNote*) m_arrayNotes[y];

            ar << l_pNote->m_iYear;
            ar << l_pNote->m_iMonth;

            ar << l_pNote->m_strMemo;

            for (x=0; x<42; x++)
            {

                ar << l_pNote->m_strNotes[x];            

            }      
        }

        // Save alarms data..............................

        ar << (UINT) m_arrayAlarms.GetSize();
        iSize = m_arrayAlarms.GetSize();

        for (y=0;y<iSize; y++)
        {

            CAlarmNode *l_pAlarm = (CAlarmNode*) m_arrayAlarms[y];
            ar << l_pAlarm->m_timeRing;

            ar << l_pAlarm->m_strInfo;
            ar << l_pAlarm->m_strSound;
        }
	}
	else
	{
		// TODO: add loading code here

        ar >> szTMP;            
        if (szTMP != szPCA)
        {
            AfxThrowArchiveException(CArchiveException::badIndex); 
            return;
        }

        DeleteLeftOvers();
        ar >> iSize;
        m_arrayNotes.SetSize(0, 10);

        for (y=0; y<iSize; y++)
        {

            m_arrayNotes.Add(new CNote);
            
            l_pNote = (CNote*) m_arrayNotes[y];
            ar >> l_pNote->m_iYear;
            ar >> l_pNote->m_iMonth;
            ar >> l_pNote->m_strMemo;
            
            for (x=0; x<42; x++)
            {

                ar >> l_pNote->m_strNotes[x];            

            }
        
        }
    
        // Load alarms data............................
        ar >>  iSize;

        for (y=0;y<iSize; y++)
        {

            CAlarmNode *l_pAlarm = new CAlarmNode;
            m_arrayAlarms.Add ( (CObject*)l_pAlarm);
                //(CAlarmNode*) m_arrayAlarms[y];
            ar >> l_pAlarm->m_timeRing;

            ar >> l_pAlarm->m_strInfo;
            ar >> l_pAlarm->m_strSound;
        }
    }

    m_nCritical = FALSE;  // Leaving critical section

}

/////////////////////////////////////////////////////////////////////////////
// CAppDoc diagnostics

#ifdef _DEBUG
void CAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAppDoc commands

BOOL CAppDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    StoreMonth();
    
    if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

    RestoreMonth();

	return TRUE;
}

BOOL CAppDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class

    StoreMonth();    

	return CDocument::OnSaveDocument(lpszPathName);
}


void CAppDoc::RestoreMonth()
{

    m_bNoModify = TRUE;

    CNote l_note;
	CAppDoc* pDoc = this;
    CNote* l_pNote;

    int iYear;
    int iMonth;
    int iCpt;

    int iIndex;

    iYear = m_CurTime.GetYear();
    iMonth = m_CurTime.GetMonth();

    iIndex = FindNote(iYear, iMonth);
    if (iIndex==-1)
    {
        for (iCpt=0; iCpt<42; iCpt++)
        {
            m_arrayEdit[iCpt].
                SetWindowText("");
        }
        return;
    }

    l_pNote= (CNote*) pDoc->m_arrayNotes[iIndex];

    for (iCpt=0; iCpt<42; iCpt++)
    {
        m_arrayEdit[iCpt].
            SetWindowText(l_pNote->m_strNotes[iCpt]);
    }

    m_bNoModify = FALSE;

}

void CAppDoc::StoreMonth()
{

	m_bNoModify = TRUE;
    
    CAppDoc* pDoc = this;
    CNote* l_pNote;

    int iYear;
    int iMonth;
    int iCpt;

    int iIndex;

    iYear = m_CurTime.GetYear();
    iMonth = m_CurTime.GetMonth();

    iIndex = FindNote(iYear, iMonth);
    if (iIndex==-1)
    {
        l_pNote = new CNote;
        l_pNote->m_iMonth =  iMonth;
        l_pNote->m_iYear  =  iYear;
        iIndex = (pDoc->m_arrayNotes).Add (l_pNote);         
    }

    //
    l_pNote= (CNote*) pDoc->m_arrayNotes[iIndex];

    // Recopying the data from the memory
    // back to the controls.
    for (iCpt=0; iCpt<42; iCpt++)
    {
        m_arrayEdit[iCpt].
            GetWindowText(l_pNote->m_strNotes[iCpt]);
    }

    m_bNoModify = FALSE;
}

int CAppDoc::FindNote(int iYear, int iMonth)
{

	CAppDoc* pDoc = this;
    CNote* pNote;

    int iSize = (pDoc->m_arrayNotes).GetSize();
    int iCpt;

    for (iCpt=0; iCpt<iSize; iCpt++)
    {
                      
        pNote= (CNote*) pDoc->m_arrayNotes[iCpt];
        if ((pNote->m_iYear==iYear) &&
            (pNote->m_iMonth==iMonth))
         
            return iCpt;
    }
    return -1;   
}

void CAppDoc::CleanUp()
{
    int iSize= m_arrayNotes.GetSize();
    CNote* pNotes;
    BOOL bDelete ;

    for (int y=0; y<iSize; y++)
    {
        if (iSize<=1) return;

        pNotes = (CNote*)(m_arrayNotes[y]);
        bDelete = TRUE;
        for (int x=0; x<42; x++)
        {
            if ((pNotes->m_strNotes[x]).GetLength()!=0)
                bDelete=FALSE;
        }
        if ((bDelete) && (pNotes->m_strMemo==""))
        {
            m_arrayNotes.RemoveAt(y);
            delete pNotes;
            y-- ;
            iSize--;
        }
    }
}

void CAppDoc::DeleteLeftOvers()
{
    for (;m_arrayNotes.GetSize();)
    {
         delete m_arrayNotes[0];
         m_arrayNotes.RemoveAt(0);    
    }

    m_nCritical=TRUE;

    while (m_arrayAlarms.GetSize())
    {
         delete m_arrayAlarms[0];
         m_arrayAlarms.RemoveAt(0);    
    }

    m_nCritical=FALSE;


}

void CAppDoc::TrierAlarms()
{

    CObArray l_arrayAlarms;
    CAlarmNode *l_pAlarm;
    int l_nCpt;
    int l_nCpt2;

    l_arrayAlarms.SetSize(0,10);

    for (l_nCpt=0; l_nCpt<m_arrayAlarms.GetSize(); l_nCpt++)
    {

        l_pAlarm = (CAlarmNode*) m_arrayAlarms[l_nCpt];
        for (l_nCpt2=0; (l_nCpt2<l_arrayAlarms.GetSize())
                      && (((CAlarmNode*)(l_arrayAlarms[l_nCpt2]))->m_timeRing
                       <= l_pAlarm->m_timeRing);  
            l_nCpt2++)
            {
                int a=0;
                a=a +1;

            }

        l_arrayAlarms.InsertAt(l_nCpt2, (CObject*)l_pAlarm, 1);

    }

    // This a critical section // so don't interrupt...
    m_nCritical = TRUE;

    while (m_arrayAlarms.GetSize())
         m_arrayAlarms.RemoveAt(0);    

    for (l_nCpt=0; l_nCpt< l_arrayAlarms.GetSize(); l_nCpt++)
    {
        m_arrayAlarms.Add( (CObject*)l_arrayAlarms[l_nCpt] );        
    }

    m_nCritical = FALSE;

}

void CAppDoc::SetTitle(LPCTSTR lpszTitle) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::SetTitle(lpszTitle);
}

void CAppDoc::OnFileSendMail() 
{
	// TODO: Add your command handler code here
	CDocument::OnFileSendMail();	
}

void CAppDoc::OnUpdateFileSendMail(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

BOOL CAppDoc::IsUpdated()
{
    return m_bNoModify;
}
