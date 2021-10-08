// Note.cpp : implementation file
//

#include "stdafx.h"
#include "app.h"
#include "Note.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNote

CNote::CNote()
{
   for (int x=0;x<42; x++)
    {
        m_strNotes[x]="";
    }

   m_strMemo = "";

}

CNote::~CNote()
{
}




/////////////////////////////////////////////////////////////////////////////
// CNote message handlers
