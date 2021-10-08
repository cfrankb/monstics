// AlarmNode.cpp : implementation file
//

#include "stdafx.h"
#include "app.h"
#include "AlarmNode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmNode

CAlarmNode::CAlarmNode()
{
    m_strInfo="";
    m_strSound="";
    m_nDeleted = FALSE;
    m_timeRing= CTime::GetCurrentTime( );

}

CAlarmNode::~CAlarmNode()
{
}


//BEGIN_MESSAGE_MAP(CAlarmNode, CObject)
	//{{AFX_MSG_MAP(CAlarmNode)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAlarmNode message handlers
