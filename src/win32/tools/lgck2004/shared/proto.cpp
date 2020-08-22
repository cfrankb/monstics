// Proto.cpp : implementation file
//

#include "stdafx.h"
#include "Proto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProto

CProto::CProto()
{
	ZeroMemory (this, sizeof(CProto));
}

CProto::~CProto()
{
}


/////////////////////////////////////////////////////////////////////////////
// CProto message handlers

CProto & CProto::operator = (CProto & proto)
{
	memcpy (this, &proto, sizeof (CProto));
	return *this;
}

CProto::CProto (CProto & proto)
{
	memcpy (this, &proto, sizeof (CProto));
}

CProto::CProto (CString & str)
{
	ZeroMemory (this, sizeof(CProto));
	strcpy (m_szName, str.GetBuffer (32));
}

void CProto::Serialize (CArchive & ar, int nSize)
{
	if (nSize==0)
		nSize = sizeof (CProto);
	
	if (ar.IsStoring())	{ 
		// Storing CODE
		ar.Write(this, nSize);

	}
	else {
		// Loading CODE
		ar.Read(this, nSize);	
	}
}

void CProto::Read (CFile & file, int nSize)
{
	if (nSize==0)
		nSize = sizeof (CProto);

	file.Read(this, nSize);
}

char* CProto::GetName()
{
	return m_szName;
}
