// GameFile3.cpp : implementation file
//

#include "stdafx.h"
#include "GameFile3.h"
#include "file.h"
#include "paldata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZEOF_SCR (sizeof (CScriptArray * ))
#define GAMEDBVER 0x0002

extern CPalData g_pal;

/////////////////////////////////////////////////////////////////////////////
// CGameFile3

CGameFile3::CGameFile3()
{
	Init ();
}

CGameFile3::~CGameFile3()
{
	Forget();
}

/////////////////////////////////////////////////////////////////////////////
// Retrieving from / sending to archive

void CGameFile3::Serialize (CArchive & ar)
{

	int n;
	int nVersion;

	if (ar.IsStoring())	{  
	// STORING
		
		nVersion = GAMEDBVER;
		ar.Write("GAM3", 4);
		ar.Write(&nVersion,4);

		m_arrOBL3.Serialize(ar, nVersion);
		m_arrClasses.Serialize(ar);
		m_arrProto.Serialize(ar);

		ar << m_nScripts;

		for (n=0; n<m_nScripts; n++)	{
			m_arrScripts[n]->Serialize(ar);
		}

		m_arrSoundData.Serialize(ar);
		m_arrPoints.Serialize(ar);
		m_arrUserDefs.Serialize(ar);
		m_arrActions.Serialize(ar);

		ar << m_strName;
		ar << m_strInformation;

		m_arrExtra.Serialize(ar);
		g_pal.Serialize(ar);

	}
	else	{
	// LOADING
		Forget(); // kill previous instance
		int x;

		char szText[] = "xxxx";
		ar.Read(szText, 4);
		if ( CString(szText) == "GAM3")	{

			ar.Read(&nVersion, 4);
			m_arrOBL3.Serialize(ar, nVersion);
			m_arrClasses.Serialize(ar);
			m_arrProto.Serialize(ar);
	
			ar >> x;

			for (n=0; n<x; n++)	{
				CScriptArray *pScript = new CScriptArray;
				pScript->Serialize(ar);
				AddScript (pScript);
			}

			m_arrSoundData.Serialize(ar);
			m_arrPoints.Serialize(ar);
			m_arrUserDefs.Serialize(ar);
			m_arrActions.Serialize(ar);
	
			ar >> m_strName;
			ar >> m_strInformation;

			m_arrExtra.Serialize(ar);

			switch (nVersion)
			{
				case 0x0001:
				break;

				case 0x0002:
					g_pal.Serialize(ar);
				break;
			}

		}
		else {; // ERROR incompatible format
		}
	}
}

void CGameFile3::Read (CFile & file)
{
	int x;
	int n;
	int nVersion;
	Forget();

	char szText[] = "yyyy";
	file.Read(szText, 4);
	if ( CString(szText) == "GAM3")	{

		file.Read(&nVersion, 4);
		m_arrOBL3.Read(file, nVersion);
		m_arrClasses.Read(file);
		m_arrProto.Read(file);
	
		file.Read (&x, sizeof(x));

		for (n=0; n<x; n++)	{
			CScriptArray *pScript = new CScriptArray;
			pScript->Read(file);
			AddScript (pScript);
		}

		m_arrSoundData.Read(file);
		m_arrPoints.Read(file);
		m_arrUserDefs.Read(file);
		m_arrActions.Read(file);

		file >> m_strName;
		file >> m_strInformation;

		m_arrExtra.Read(file);

		switch (nVersion)
		{
			case 0x0001:
			break;

			case 0x0002:
				g_pal.Read(file);
			break;
		}
	}

	else {; // ERROR incompatible format
	}
}

/////////////////////////////////////////////////////////////////////////////
// Initialization and destruction

void CGameFile3::Init()
{
	m_strName = "";
	m_strInformation ="";
	m_nScripts =0;
	m_arrScripts = NULL;
	m_nCurrScript =0;

	// Add the default class 
	m_arrClasses.Add ( new CStrVal (0, "Background"));

	// Add the default frames set
	CSS3Frame *pFrame = new CSS3Frame (8,8);
	COBL3Filter *pFilter = new COBL3Filter;
	pFilter->SetName (CString("(blank)"));
	pFilter->Add (pFrame);
	m_arrOBL3.Add (pFilter);

	// Add the default Proto-object
	m_arrProto.Add ( CProto (CString("(blank)")));

	m_arrSoundData.Add ( CTagEntry("(no sound)"));
	m_arrPoints.Add ( CTagEntry("(no points)"));
	m_arrUserDefs.Add ( CTagEntry("(null)"));
	m_arrActions.Add ( CTagEntry("(none)"));

	m_arrExtra.Init();
}

void CGameFile3::Forget ()
{
	m_arrOBL3.Forget();
	m_arrProto.Forget();
	m_arrClasses.Forget();

	m_arrPoints.Forget();
	m_arrSoundData.Forget();
	m_arrUserDefs.Forget();
	m_arrActions.Forget();

	m_arrExtra.Forget();

	if (m_nScripts)
	{
		while (m_nScripts) {
			delete m_arrScripts[0];
			RemoveScript (0);
		}
		free (m_arrScripts);
	}

	m_nCurrScript =0;
}

/////////////////////////////////////////////////////////////////////////////
// Scripts

void CGameFile3::RemoveScript (int n)
{
	int i;
	for (i = n; i < m_nScripts-1;  i++)	{
		m_arrScripts[i] = m_arrScripts[i+1];
	}
	m_nScripts--;
}

void CGameFile3::AddScript (CScriptArray *pScriptArray)
{
	CScriptArray **t = (CScriptArray **) 
		malloc (SIZEOF_SCR * (m_nScripts +1));

	if (m_nScripts!=0) {
		memcpy (t, m_arrScripts, SIZEOF_SCR * m_nScripts );
	}

	t[m_nScripts] = pScriptArray;

	if (m_nScripts!=0)
		free (m_arrScripts);

	m_arrScripts = t;

	m_nScripts++;
}

void CGameFile3::InsertScript (int n, CScriptArray *pSA)
{
	AddScript (NULL);

	int i;
	for (i=m_nScripts-1; i > n ; i--)	{
			m_arrScripts [i] = m_arrScripts [i-1];
	}

	m_arrScripts[n] = pSA;
}

void CGameFile3::DrawScript (CScriptArray *pSA, int nMX, int nMY, void *pDest, int nLen, int nHei, int nPitch)
{
	DWORD s;
	DWORD d;
	int nCols, nRows;
	int ld, ls;

	int i;

	int _Ox;
	int _Oy;
	int _x;
	int _y;

	CScriptArray & script = * pSA;
	int nEntries = pSA->GetSize(); 
	register CSS3Frame *pFrame;

	for (i=0; i<nEntries; i++)
	{
		CScriptEntry & entry = script[i] ; 
		COBL3Filter & filter = * m_arrOBL3 [entry.m_nFrameSet];
		pFrame = filter[entry.m_nFrameNo];

		_x = entry.m_nX - nMX;
		_y = entry.m_nY - nMY;

#ifdef _EDITOR_
		if (
#else
		if ((entry.m_nTriggerKey & TRIGGER_HIDDEN) ||
#endif
			 (_x + pFrame->m_nLen <= 0) ||
			 (_x >= nLen) || 
			(_y + pFrame->m_nHei <= 0) || 
			(_y >= nHei) ) {}
		else {

			if (_x<0) {
				_Ox = -_x;
				_x =0;
				nCols = pFrame->m_nLen - _Ox;
			}
			else {
				_Ox = 0;
				nCols = min (pFrame->m_nLen,
					nLen - _x);
			}

			if (_y<0) {
				_Oy = -_y;
				_y =0;
				nRows = pFrame->m_nHei - _Oy;
			}
			else {
				_Oy = 0;
				nRows = min (pFrame->m_nHei,
					nHei - _y);
			}

			ld = -nCols + nPitch;
			ls = -nCols + pFrame->m_nLen;

			s = (DWORD) pFrame->m_pBitmap + _Ox 
					+ _Oy  * pFrame->m_nLen;
			d = (DWORD) pDest + _x + _y * nPitch;

		_asm {

			mov esi,s
			mov edi,d

			mov edx, nRows
loop2:		mov ecx, nCols
loop1:		mov eax, [esi]
			or eax, eax
			je zero1

			mov ebx, [edi]
			//cmp eax,ebx 
			//je zero1

			or ax,ax
			je zero2
			//cmp ax,bx
			//je zero2

			or al,al
			je zero3
			mov bl,al
zero3:
			or ah,ah
			je zero4
			mov bh,ah
zero4:
  		    mov [edi], bx

zero2:
			shr eax,16
			shr ebx,16
		
			inc edi
			inc edi

			or ax,ax
			je zero2b
			//cmp ax,bx
			//je zero2b

			or al,al
			je zero3b

			mov bl,al
zero3b:
			or ah,ah
			je zero4b

			mov bh,ah
zero4b:
			mov [edi], bx
zero2b:

			dec edi
			dec edi

zero1:
			inc edi
			inc edi
			inc edi
			inc edi

			inc esi
			inc esi
			inc esi
			inc esi

			dec ecx
			dec ecx
			dec ecx
			dec ecx
			or ecx,ecx
			jne loop1
			
			add edi, ld
			add esi, ls

			dec edx
			or edx,edx
			jne loop2

			}
		}
	}
}

CScriptArray * CGameFile3::operator [] (int n) 
{
	return m_arrScripts[n];
}

int CGameFile3::WhoIs (CScriptArray & script, int x, int y)
{
	int nTarget = -1;

	int n;
	for (n=0; n<script.GetSize(); n++)
	{
		CScriptEntry &entry = script[n];
		COBL3Filter & filter = * m_arrOBL3[entry.m_nFrameSet];
		CSS3Frame * pFrame = filter[entry.m_nFrameNo];
		if ((entry.m_nX<= x) && (entry.m_nY<= y) &&
			(entry.m_nX+ pFrame->m_nLen) > x &&
			(entry.m_nY+ pFrame->m_nHei) > y )
				nTarget = n;
	}
	return nTarget;
}

int CGameFile3::GetSize()
{
	return m_nScripts;
}

/////////////////////////////////////////////////////////////////////////////
// Object sets & proto

BOOL CGameFile3::UpdateOBL3 (CString &strError)
{
	int n;
	strError = "";
	for (n=0; n<m_arrOBL3.GetSize(); n++)
	{
		COBL3Filter & filter = * m_arrOBL3[n];
		if (CString(filter.m_szFilename)!="")
		{
			COBL3Filter * pFilter = new COBL3Filter;
			if (pFilter->Extract 
				(filter.m_szFilename)==TRUE)
			{
				// sucess
				pFilter->SetName (CString(filter.m_szName));
				pFilter->SetFilename (CString(filter.m_szFilename));
				delete m_arrOBL3[n];
				m_arrOBL3.SetAt (n, pFilter);
			}
			else
			{
				// failure
				CString str;
				str.Format ("*** [%d] %s -> %c%s%c\r\n\r\n",
					n+1, m_arrOBL3[n]->m_szName,
					34, m_arrOBL3[n]->m_szFilename,
					34);
				strError = strError + str;
				delete pFilter;					
			}
		}
	}
	return (strError=="");
}

BOOL CGameFile3::Extract (CString & strFilename)
{
	CFile file;
	CFileException e;

	if (!file.Open(strFilename, CFile::modeRead
		| CFile::typeBinary, &e ))
	{
#ifdef _DEBUG
		afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
	return FALSE;
	}		

	Read(file);
	file.Close();
	return TRUE;
}

void CGameFile3::KillFrameSet (int nFrameSet)
{

	if ((nFrameSet <= 0) ||
		(nFrameSet >= m_arrOBL3.GetSize()))
		return;

	int i;
	for (i=0; i<GetSize(); i++)
	{
		m_arrScripts[i]->KillFrameSet (nFrameSet);
	}

	m_arrProto.KillFrameSet (nFrameSet);
	m_arrOBL3.RemoveAt(nFrameSet);
}

void CGameFile3::KillProto (int nProto)
{
	if ((nProto <= 0) ||
		(nProto >= m_arrProto.GetSize()))
		return;

	int i;
	for (i=0; i<GetSize(); i++)
	{
		m_arrScripts[i]->KillProto (nProto);
	}

	m_arrProto.KillProto (nProto);
}


BOOL CGameFile3::IsValid(CString & strFilename)
{
    CFile file;
    if (file.Open(strFilename, CFile::modeRead | CFile::typeBinary))
    {
    	char szText[] = "yyyy";
    	file.Read(szText, 4);
        file.Close();            
	    return CString(szText) == "GAM3";
    }
    else
    {
        return FALSE;
    }
}
