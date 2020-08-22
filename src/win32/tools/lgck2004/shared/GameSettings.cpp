// GameSettings.cpp : implementation file
//

#include "stdafx.h"
#include "GameSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZEOF sizeof(CGameSettings)

/////////////////////////////////////////////////////////////////////////////
// CGameSettings

CGameSettings::CGameSettings()
{
	Init();
}

CGameSettings::~CGameSettings()
{
	Forget();
}

/////////////////////////////////////////////////////////////////////////////
// CGameSettings message handlers

void CGameSettings::Forget()
{

}

void CGameSettings::Init()
{
	ZeroMemory(this, SIZEOF);
}

void CGameSettings::Serialize(CArchive & ar)
{
	int nSize;
	if (ar.IsLoading()) // loading
	{
		ar >> nSize;
		ar.Read(this, nSize);
	}
	else // saving
	{
		nSize = SIZEOF;
		ar << nSize;
		ar.Write(this, nSize);
	}
}

void CGameSettings::Read(CFile & file)
{
	int nSize;
	file.Read(&nSize, 4);
	file.Read(this, nSize);
}

void CGameSettings::Write (CFile & file)
{
	int nSize = SIZEOF;
	file.Write(&nSize, 4);
	file.Write(this, nSize);
}
