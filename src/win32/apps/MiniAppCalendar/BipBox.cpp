#ifndef _BIPBOX_H
#define _BIPBOX_H

// BipBox.cpp : implementation file
//

#include "stdafx.h"
#include "app.h"
#include "BipBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBipBox dialog


CBipBox::CBipBox(CWnd* pParent /*=NULL*/)
	: CDialog(CBipBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBipBox)
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
}


void CBipBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBipBox)
	DDX_Text(pDX, IDC_EINFO, m_strInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBipBox, CDialog)
	//{{AFX_MSG_MAP(CBipBox)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBipBox message handlers

#endif