// ScriptEntry.cpp : implementation file
//

#include "stdafx.h"
#include "ScriptEntry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptEntry

CScriptEntry::CScriptEntry()
{
	ZeroMemory (this, sizeof (CScriptEntry));
}

CScriptEntry::~CScriptEntry()
{
	if (m_pExtraData)
	{
		free(m_pExtraData);
		m_pExtraData = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScriptEntry message handlers

CScriptEntry & CScriptEntry::operator = (CScriptEntry &src)
{
	memcpy (this, &src, sizeof (CScriptEntry));
	// TODO: PUT POINTERS TO NULL
	m_pExtraData = NULL;

	return *this;
}

void CScriptEntry::Serialize (CArchive & ar)
{
	if (ar.IsStoring()) { 
		// Storing code
		ar. Write (this, sizeof (CScriptEntry));

		if (m_pExtraData)
		{
			m_pExtraData->Serialize(ar);
		}
	}
	else {
		// Loading code
		ar. Read (this, sizeof (CScriptEntry));

		// TODO: PUT POINTERS TO NULL
		if (m_pExtraData)
		{
			CExtraData *m_pExtraData = 
				(CExtraData *) malloc (sizeof(CExtraData));

			m_pExtraData->Serialize(ar);
		}
	} 
}

void CScriptEntry::MoveBy (int byX, int byY)
{
	m_nX = m_nX + byX;
	m_nY = m_nY + byY;
}

CScriptEntry::CScriptEntry (int x, int y)
{
	ZeroMemory (this, sizeof (CScriptEntry));
	m_nX = x;
	m_nY = y;
}

void CScriptEntry::MoveTo (int x, int y)
{
	m_nX = x;
	m_nY = y;
}

void CScriptEntry::MoveTo (CScriptEntry &entry)
{
	m_nX = entry.m_nX;
	m_nY = entry.m_nY;
}

void CScriptEntry::Read (CFile & file)
{
	file. Read (this, sizeof (CScriptEntry));
	if (m_pExtraData)
	{
		CExtraData *m_pExtraData = 
			(CExtraData *) malloc (sizeof(CExtraData));
		m_pExtraData->Read(file);
	}
}

CScriptEntry::CScriptEntry (CScriptEntry & entry)
{
	*this = entry;
}

CScriptEntry::CScriptEntry (CProto & proto)
{
	ZeroMemory (this, sizeof (CScriptEntry));
	m_nFrameSet = proto.m_nFrameSet;
	m_nFrameNo = proto.m_nFrameNo;
}

void CScriptEntry::Write (CFile & file)
{
	file. Write (this, sizeof (CScriptEntry));
	if (m_pExtraData)
	{
		m_pExtraData->Write(file);
	}
}
