// SS3Frame.cpp : implementation file
//        

#include "stdafx.h"
#include "SS3Frame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSV3Frame

CSS3Frame::CSS3Frame()
{
    m_nDeleted = FALSE;
    m_arrUndo.SetSize(0,10);
    m_arrRedo.SetSize(0,10);

    m_pBitmap = NULL;
    m_pMap = NULL;

    m_nHei =0;
    m_nLen =0;

    m_nMapped =FALSE;
    m_nMapEnabled =FALSE;


}

CSS3Frame::~CSS3Frame()
{
    if (m_pBitmap!=NULL) free (m_pBitmap);
    if (m_pMap!=NULL) free (m_pMap);

}


//BEGIN_MESSAGE_MAP(CSS3Frame, CObject)
	//{{AFX_MSG_MAP(CSSV3Frame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSS3Frame message handlers

void CSS3Frame::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
        //CArchive

        ar << m_nDeleted;
        ar << m_nLen;
        ar << m_nHei;
        ar << m_nMapEnabled;
        ar << m_nMapped;

        if (m_nMapped)
        {
            ar.Write(m_pMap, m_nLen* m_nHei /8);   
        }

        if (m_nLen | m_nHei)
            ar.Write(m_pBitmap, m_nLen* m_nHei );
           
    }
	else
	{
		// TODO: add loading code here

        ar >> m_nDeleted;
        ar >> m_nLen;
        ar >> m_nHei;
        ar >> m_nMapEnabled;
        ar >> m_nMapped;

        if (m_nMapped)
        {
            m_pMap = (char*) malloc (m_nLen*m_nHei/8);
            ar.Read(m_pMap, m_nLen* m_nHei /8);   

        }

        if (m_nLen | m_nHei)
        {
            m_pBitmap = (char*) malloc (m_nLen*m_nHei) ;
            ar.Read(m_pBitmap, m_nLen* m_nHei );
        }
    
    }

}
