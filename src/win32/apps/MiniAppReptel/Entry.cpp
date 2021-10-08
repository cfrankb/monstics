// Entry.cpp : implementation file
//

#include "stdafx.h"
#include "MiniApp Reptel.h"
#include "Entry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEntry

CEntry::CEntry()
{     

    m_nDeleted = FALSE;
    m_nImage= 0;
    m_strName = "";
    m_strAddr = "";
    m_strTel = "";
    m_strInfo = "";

}

CEntry::~CEntry()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEntry message handlers

CEntry::CEntry(int p_nEntry)
{
    CEntry();
    m_nEntry = p_nEntry;
}
