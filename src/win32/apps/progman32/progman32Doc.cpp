// progman32Doc.cpp : implementation of the CProgman32Doc class
//

#include "stdafx.h"
#include "progman32.h"

#include "progman32Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FORMAT_HEADER   "PM32"
#define VERSION         0x0

/////////////////////////////////////////////////////////////////////////////
// CProgman32Doc

IMPLEMENT_DYNCREATE(CProgman32Doc, CDocument)

BEGIN_MESSAGE_MAP(CProgman32Doc, CDocument)
	//{{AFX_MSG_MAP(CProgman32Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgman32Doc construction/destruction

CProgman32Doc::CProgman32Doc()
{
	// TODO: add one-time construction code here
    m_nState =0;
    ZeroMemory(&m_rect, sizeof(m_rect));
}

CProgman32Doc::~CProgman32Doc()
{
}

BOOL CProgman32Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CProgman32Doc serialization

void CProgman32Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CProgman32Doc diagnostics

#ifdef _DEBUG
void CProgman32Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProgman32Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProgman32Doc commands

void CProgman32Doc::Save()
{
    CFile file;
    if (file.Open(GetPathName(), CFile::modeCreate | CFile::modeWrite))
    {
        CArchive ar(&file, CArchive::store, 512, NULL);
        char *szFormatHeader = FORMAT_HEADER;
        ar.Write(szFormatHeader,4);
        
        int nVersion= VERSION;
        ar.Write(&nVersion, 4);
        ar <<  GetTitle();
        ar.Write(&m_rect, sizeof(m_rect));
        ar.Write(&m_nState,4);
        m_arrIcons.Serialize(ar);      
    }  
    else
    {
    }
}

void CProgman32Doc::Load()
{
    CFile file;
    if (file.Open(GetPathName(), CFile::modeRead ))
    {
        CArchive ar(&file, CArchive::load, 512, NULL);

        Forget();
        char szTemp[]="xyzw";
        ar.Read(szTemp,4);

        if (memcmp(szTemp, FORMAT_HEADER,4)==0)
        {
            int nVersion=0;
            ar.Read(&nVersion, 4);
            CString strTitle;
            ar >>  strTitle;
            SetTitle(strTitle);
            ar.Read(&m_rect, sizeof(m_rect));
            ar.Read(&m_nState,4);
            m_arrIcons.Serialize(ar);      
        }
        else
        {
            AfxThrowArchiveException(CArchiveException::badIndex);       
        }
    }  
    else
    {
    
    }
}

BOOL CProgman32Doc::ProcessAction(CHILD_INFO & info)
{
    switch (info.m_nAction)
    {
        case ACTION_CREATE:
            SetPathName(info.m_szPath);
            SetTitle(info.m_szTitle);
            Save();
        break;

        case ACTION_LOAD:
            SetPathName(info.m_szPath);
            Load();
        break;

        case ACTION_SAVE:
            Save();
        break;

        case ACTION_SET_INFO:
            SetPathName(info.m_szPath);
            SetTitle(info.m_szTitle);
        break;

        case ACTION_GET_INFO:
            strcpy(info.m_szPath, GetPathName());
            strcpy(info.m_szTitle, GetTitle());
        break;
    }

    return TRUE;
}

CIconArray & CProgman32Doc::GetIconArray()
{
    return m_arrIcons;
}

void CProgman32Doc::Forget()
{
    m_arrIcons.Forget();
}

void CProgman32Doc::SetRect(RECT & rect)
{
    m_rect = rect;
}

void CProgman32Doc::GetRect(RECT & rect)
{
    rect = m_rect;
}

void CProgman32Doc::Delete()
{
    OutputDebugString(GetPathName() + "\r\n");

    TRY
    {   
        CFile::Remove(GetPathName());
    }
    CATCH (CFileException, e);
    {
        OutputDebugString("File " + GetPathName() + "cannot be removed!\r\n");    
    }
    END_CATCH         
}
