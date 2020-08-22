// ScriptArray.cpp : implementation file
//

#include "stdafx.h"
#include "ScriptArray.h"
#include "file.h"
#include "zlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZEOF (sizeof (CScriptEntry))
#define GROWBY 32

#define SCRIPT_VER 0x00000002

//#define EXTRADATABUFFER (16*1024)
//#define EXTRADATASIZE	sizeof(CExtraData)
//#define EXTRADATAMAX	(EXTRADATABUFFER/EXTRADATASIZE)	

/////////////////////////////////////////////////////////////////////////////
// CScriptArray

CScriptArray::CScriptArray()
{
	m_nBkColor = 0x0;
	
	m_nMax = GROWBY;
	m_arrEntries = (CScriptEntry *) malloc (SIZEOF * m_nMax);
	ZeroMemory (m_arrEntries, SIZEOF * m_nMax);
	m_nSize =0;

	m_strName = "";
	m_strTitle = "";

	m_nCurrEntry =0;
	m_nMX =0;
	m_nMY =0;
	m_bSelection = FALSE;

	//m_pExtraData = (CExtraData *) malloc(EXTRADATABUFFER);
	//ZeroMemory(m_pExtraData, EXTRADATABUFFER);
	//m_pExtraData=NULL;
	//m_nExtraDataAlloc = 0;
}

CScriptArray::~CScriptArray()
{
	Forget();
	m_nMax =0;
	free (m_arrEntries);

	/*
	if (m_pExtraData!=NULL)
	{
		free(m_pExtraData);
		m_pExtraData = NULL;
		m_nExtraDataAlloc = 0;
	}
	*/
}

void CScriptArray::Serialize (CArchive & ar)
{
//    char szTemp[1024];

    int nSize;
    int nEntrySize;
    ULONG nTotalSize;
    ULONG nCompressSize;
    UCHAR *pCompressData;
    
    int nVer = SCRIPT_VER;
    int nMarker = -1;
	int i;
    int err;

	if (ar.IsStoring()) 
    { 
		// Storing code

        /*
        // old code

        ar << m_nSize;
		ar << m_strName;
		ar << m_strTitle;
		ar << m_nBkColor;

		ar << (int) sizeof (CScriptEntry);

		for (n=0; n<m_nSize; n++)
			m_arrEntries[n].Serialize(ar);

        */

        ar << (int) nMarker ;   // marker compressed version 
        ar << (int) (nVer);     // script version 

        ar << m_nSize;
		ar << m_strName;
		ar << m_strTitle;
		ar << m_nBkColor;
		ar << (int) sizeof (CScriptEntry);

        nTotalSize = m_nSize * sizeof (CScriptEntry);
        nCompressSize = nTotalSize + 2048; 
        pCompressData = (UCHAR*) malloc(nCompressSize);

        err = compress(
           (UCHAR *)pCompressData, 
           (ULONG *)& nCompressSize,
           (UCHAR *)m_arrEntries,
           (ULONG)nTotalSize);

        ar << nTotalSize;       
        ar << (int) nCompressSize;
        ar.Write(pCompressData, nCompressSize);

        free(pCompressData);
	}
	else 
    {
		// Loading code
		Forget ();
        ar >> nSize;            // # of entries
        if (nSize != -1)        
        {
		    ar >> m_strName;
		    ar >> m_strTitle;
		    ar >> m_nBkColor;
		    ar >> nEntrySize ;

		    CScriptEntry entry;
		    for (i=0; i<nSize; i++) 
            {
    			entry.Serialize(ar);
	    		Add (entry);
		    }
        }
        else                    
        {
            ar >> nVer;         // script version (new)
            ar >> m_nSize;      // # of entries
            m_nMax = m_nSize;
		    ar >> m_strName;
		    ar >> m_strTitle;
		    ar >> m_nBkColor;
		    ar >> nEntrySize ;

            ar >> nTotalSize;   // new
            ar >> nCompressSize;// new

            /*
            wsprintf(szTemp, "****\nEntrySize(%d) * Number(%d) = %d \n", nEntrySize, m_nSize,  nEntrySize * m_nSize);
            OutputDebugString(szTemp);
            
            wsprintf(szTemp, "Total size: %d\n", nTotalSize);
            OutputDebugString(szTemp);
            */
            
            UCHAR *pCompressData = (UCHAR*) malloc(nCompressSize);
            if (m_arrEntries)
            {
                free(m_arrEntries);
            }

            m_arrEntries = (CScriptEntry*) malloc(nTotalSize);
            ar.Read(pCompressData, nCompressSize);
            err = uncompress((UCHAR*)m_arrEntries,
                            &nTotalSize,
                            pCompressData,
                            nCompressSize);

            free(pCompressData);
        }
	}
}

void CScriptArray::Read (CFile & file)
{
    OutputDebugString("Reading script start\n");
//    char szTemp[1024];

    int nVer = SCRIPT_VER;
    int nMarker = -1;
	int nSize; // nEntries
    int nEntrySize;
	int i;
    int err;
    ULONG nTotalSize = NULL;
    ULONG nCompressSize = NULL;
    UCHAR *pCompressData = NULL;

	Forget ();

	file.Read (&nSize, sizeof (nSize));
    if (nSize != -1)
    {
    	file >> m_strName;
	    file >> m_strTitle;
	    file.Read (&m_nBkColor, sizeof (m_nBkColor));
	    file.Read (&nEntrySize, sizeof(nSize));

	    CScriptEntry entry;
	    for (i=0; i<nSize; i++) 
        {
		    entry.Read(file);
		    Add (entry);
	    }
    } 
    else
    {
    	file.Read (&nVer, sizeof (nVer));
    	file.Read (&m_nSize, sizeof (nSize));
        m_nMax = m_nSize;
    	file >> m_strName;
	    file >> m_strTitle;
	    file.Read (&m_nBkColor, sizeof (m_nBkColor));
	    file.Read (&nEntrySize, sizeof(nEntrySize));
        file.Read (&nTotalSize, 4);
        file.Read (&nCompressSize,4);
                    
        UCHAR *pCompressData = (UCHAR*) malloc(nCompressSize);
        if (m_arrEntries)
        {
            free(m_arrEntries);
        }

        m_arrEntries = (CScriptEntry*) malloc(nTotalSize);
        file.Read(pCompressData, nCompressSize);
        err = uncompress((UCHAR*)m_arrEntries,
                          &nTotalSize,
                          pCompressData,
                          nCompressSize);

        free(pCompressData);    
    }

    OutputDebugString("Reading script complete\n");
}

void CScriptArray::Write (CFile & file)
{
    /*
	int n;

	file.Write (&m_nSize, sizeof (m_nSize));
	file << m_strName;
	file << m_strTitle;
	file.Write (&m_nBkColor, sizeof (m_nBkColor));

	int nSize = sizeof(CScriptEntry);
	file.Write(&nSize, 4);

	for (n=0; n<m_nSize; n++) {
		m_arrEntries[n].Write(file);
	}
    */
     
    int nVer = SCRIPT_VER;
    int nMarker = -1;
    int err;
    ULONG nTotalSize = NULL;
    ULONG nCompressSize = NULL;
    UCHAR *pCompressData = NULL;

    file.Write( &nMarker, 4) ;      // marker compressed version 
    file.Write( &nVer,4);           // script version 

    file.Write(&m_nSize,4);
	file << m_strName;
	file << m_strTitle;
	file.Write(&m_nBkColor,sizeof(m_nBkColor));
	file << (int) sizeof (CScriptEntry);

    nTotalSize = m_nSize * sizeof (CScriptEntry);
    nCompressSize = nTotalSize + 2048; 
    pCompressData = (UCHAR*) malloc(nCompressSize);

    err = compress(
        (UCHAR *)pCompressData, 
        (ULONG *)& nCompressSize,
        (UCHAR *)m_arrEntries,
        (ULONG)nTotalSize);

    file << (int) nTotalSize;       
    file << (int) nCompressSize;
    file.Write(pCompressData, nCompressSize);

    free(pCompressData);
}

/////////////////////////////////////////////////////////////////////////////
// CScriptArray message handlers

void CScriptArray::Forget()
{
	m_nCurrEntry=0;
	m_nMX =0;
	m_nMY =0;
	m_bSelection = FALSE;

    /*
	while (m_nSize)	{
		RemoveAt (0);
	}
    */
    m_nSize =0;
    ZeroMemory(m_arrEntries, SIZEOF);

	//ZeroMemory(m_pExtraData, EXTRADATABUFFER);
	//m_nExtraDataAlloc = 0;
}

void CScriptArray::RemoveAt(int n)
{
	ZeroMemory (&m_arrEntries[n], SIZEOF);
	
	int i;
	for (i=n; i< m_nSize-1; i++)	{	
		m_arrEntries[i] = m_arrEntries[i+1];
	}
	m_nSize--;
}

int CScriptArray::Add (CScriptEntry &entry)
{
	if (m_nSize==m_nMax) 
    {
		m_nMax = m_nMax + GROWBY; 
		CScriptEntry *t = 
			(CScriptEntry *) malloc (m_nMax * SIZEOF);

		ZeroMemory (t, m_nMax * SIZEOF);
		
		memcpy (t, m_arrEntries, m_nSize * SIZEOF);
		free (m_arrEntries);
		m_arrEntries = t;
	}

    m_arrEntries[m_nSize] = entry;
	m_nSize++;
	return m_nSize-1;
}

CScriptEntry & CScriptArray::operator [] (int n) 
{
	return (CScriptEntry &) m_arrEntries[n];
}

int CScriptArray::GetSize() 
{
	return m_nSize;
}

void CScriptArray::InsertAt (int n, CScriptEntry &entry)
{
	CScriptEntry entryTemp;
	Add (entryTemp);

	int i;
	for (i=m_nSize-1; i>n; i--)
	{
		m_arrEntries [i] = m_arrEntries [i-1];
	}
	m_arrEntries[n] = entry;
}

void CScriptArray::MoveBy (int nByX, int nByY)
{
	m_nMX = m_nMX + nByX;
	m_nMY = m_nMY + nByY;
}

int CScriptArray::FindProto (int nProto, int nStartAt)
{
	int i=nStartAt;
	for (; i<m_nSize; i++)
	{
		if (m_arrEntries[i].m_nProto == nProto)
			return i;
	}
	return -1;
}

void CScriptArray::KillFrameSet (int nFrameSet)
{

	m_bSelection = FALSE;

	int i;
	for (i=0; i<GetSize(); i++)
	{
		CScriptEntry & entry = m_arrEntries[i];
		if (entry.m_nFrameSet == nFrameSet)
		{
			RemoveAt(i);
			i--;
		}
		else
		if (entry.m_nFrameSet > nFrameSet)
		{
			entry.m_nFrameSet--;
		}

	}
}

void CScriptArray::KillProto(int nProto)
{
	m_bSelection = FALSE;

	int i;
	for (i=0; i<GetSize(); i++)
	{
		CScriptEntry & entry = m_arrEntries[i];
		if (entry.m_nProto == nProto)
		{
			RemoveAt(i);
			i--;
		}
		else
		if (entry.m_nProto > nProto)
		{
			entry.m_nProto--;
		}
	}
}

#define CopyVar(_var_) _var_ = source. _var_
CScriptArray & CScriptArray::operator = (CScriptArray & source)
{
	if (m_arrEntries)
		free (m_arrEntries);

	CopyVar(m_nBkColor);
	CopyVar(m_nMX);
	CopyVar(m_nMY);
	CopyVar(m_strName);
	CopyVar(m_strTitle);
	
	m_bSelection = FALSE;
	m_nCurrEntry=0;

	m_nSize = source.GetSize();
	m_nMax = m_nSize;

	m_arrEntries = (CScriptEntry*) malloc (m_nMax * SIZEOF);
	memcpy (m_arrEntries, source.m_arrEntries, m_nMax * SIZEOF);
	
	return *this;
}

CExtraData * CScriptArray::AllocExtraData(int nEntryTarget)
{
	/*
	m_arrEntries[nEntryTarget].m_pExtraData =  &m_pExtraData[m_nExtraDataAlloc];
	ZeroMemory(&m_pExtraData[m_nExtraDataAlloc], sizeof(CExtraData));
	m_pExtraData[m_nExtraDataAlloc].m_bOwner = TRUE ;

	m_nExtraDataAlloc++;
	return m_arrEntries[nEntryTarget].m_pExtraData;
	*/
	return NULL;
}
	

