// OBL3Array.cpp : implementation file
//

#include "stdafx.h"
#include "OBL3Array.h"
#include "file.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GROWBY 16
#define SIZEOF (sizeof (COBL3Filter *))

/////////////////////////////////////////////////////////////////////////////
// COBL3Array

COBL3Array::COBL3Array()
{
	m_nSize =0;
	m_nMax = GROWBY;
	m_arrFilters = (COBL3Filter**) malloc (m_nMax * SIZEOF);
	ZeroMemory (m_arrFilters, m_nMax * SIZEOF);
}

COBL3Array::~COBL3Array()
{
	Forget ();
	free (m_arrFilters);
}


/////////////////////////////////////////////////////////////////////////////
// COBL3Array message handlers

void COBL3Array::Serialize (CArchive & ar, int nGameDBVer)
{
    char szTemp[1024];
    int i;
	int nSize;

    int nTotalSize;
    int nCompressSize;

    CWnd *pWnd = AfxGetMainWnd();

	if (ar.IsStoring())	{  
		// STORING DATA
		ar. Write ("ARR4", 4);
		ar << m_nSize;

		for (i=0; i<m_nSize ; i++) 	
        {
            if (pWnd)
            {
                wsprintf(szTemp, "Packing graphics: %d of %d (%d %%) done", 
                    i,
                    m_nSize,
                    100 * i / m_nSize);
                pWnd->SendMessage(WM_USER_SET_STATUS, (UINT) szTemp, 0);
            }

			m_arrFilters[i]->Serialize(ar);
			ar << CString(m_arrFilters[i]->m_szName);
			ar << CString(m_arrFilters[i]->m_szFilename);
		}

	}
	else {
		// LOADING DATA
		char szText[5] = "xxxx";

		ar. Read (szText, 4);
		if ( CString (szText) != "ARR4") {
			// ERROR - incorrect format
			return;
		}

		Forget();
		ar >> nSize;

        if (nSize!=-1)
        {
		    CString strName;
		    CString strFilename;

    		for (i=0; i<nSize; i++)	
            {
                if (pWnd && nSize)
                {
                    wsprintf(szTemp, "Unpacking graphics: %d of %d (%d %%) done", 
                        i,
                        nSize,
                        100 * i / nSize );
                    pWnd->SendMessage(WM_USER_SET_STATUS, (UINT) szTemp, 0);
                }

			    COBL3Filter *pFilter = new COBL3Filter;		
			    pFilter->Serialize(ar);
			    ar >> strName;      //pFilter->m_szName;
			    ar >> strFilename;  //pFilter->m_szFilename;
			    pFilter->SetName(strName);
			    pFilter->SetFilename(strFilename);
			    Add (pFilter);
		    }
        }
        else
        {
            ar >> nSize;
            ar >> nTotalSize;
            ar >> nCompressSize;        

            for (i=0; i<nSize; i++)
            {
                
            
            }
        }
	}

    if (pWnd)
    {
        pWnd->SendMessage(WM_USER_SET_STATUS, (UINT) "", 0);
    }
}

void COBL3Array::Read (CFile & file, int nGameDBVer)
{
	int i;
	int n;

	char szText[5] = "xxxx";

	file.Read (szText, 4);

	if ( CString (szText) != "ARR4") {
		// ERROR - incorrect format
		return;
	}

	Forget();
	file.Read (&n, 4);

	CString strName;
	CString strFilename;

	for (i=0; i<n; i++)	{
		COBL3Filter *pFilter = new COBL3Filter;		
		pFilter->Read(file);

		file >> strName; 
		file >> strFilename; 
		pFilter->SetName(strName);
		pFilter->SetFilename(strFilename);
		Add (pFilter);
	}
}

void COBL3Array::Forget()
{
	while ( GetSize() )	{
		delete m_arrFilters [0];
		RemoveAt (0);
	}
}

int COBL3Array::GetSize()
{
	return m_nSize;
}

void COBL3Array::RemoveAt(int n)
{
	int i;
	for (i=n; i< m_nSize-1; i++)  {	
		m_arrFilters[i] = m_arrFilters[i+1];
	}

	m_nSize--;
	m_arrFilters[m_nSize] = NULL;
}

void COBL3Array::Add(COBL3Filter *pFilter)
{
	if (m_nSize==m_nMax) {
		m_nMax = m_nMax + GROWBY; 
		COBL3Filter **t = 
			(COBL3Filter **) malloc (m_nMax * SIZEOF);

		ZeroMemory (t, m_nMax * SIZEOF);
		
		memcpy (t, m_arrFilters, m_nSize * SIZEOF);
		free (m_arrFilters);
		m_arrFilters = t;
	}

    m_arrFilters[m_nSize] = pFilter;
	m_nSize++;
}

COBL3Filter * COBL3Array::operator [] (int n)
{
	return m_arrFilters[n];
}

CSS3Frame * COBL3Array::GetFrame (int y, int x)
{
	COBL3Filter & filter = * m_arrFilters[y];
	return filter [x];
}

CSS3Frame * COBL3Array::GetFrame (CScriptEntry &entry)
{
	COBL3Filter & filter = * m_arrFilters[entry.m_nFrameSet];
	return filter [entry.m_nFrameNo];
}

void COBL3Array::SetAt (int n, COBL3Filter * pFilter)
{
	m_arrFilters [n] = pFilter;
}

int COBL3Array::GetFilePathIndex (const CString & str)
{
	int i;
	for (i=0; i<m_nSize; i++)
	{
		if (CString(m_arrFilters[i]->m_szFilename).
			CompareNoCase(str)==0)
			return i;
	}
	 
	return -1;
}

int COBL3Array::GetNameIndex (const CString & str)
{
	int i;
	for (i=0; i<m_nSize; i++)
	{
		if (CString(m_arrFilters[i]->m_szName).
			CompareNoCase(str)==0)
			return i;
	}
	 
	return -1;
}

BOOL COBL3Array::PackImages ()
{
	int i;
	for (i=0; i< GetSize(); i++)
	{
		COBL3Filter & filter = * m_arrFilters[i];
		filter.PackImages();
	}

	OutputDebugString ("OBL3Array Packed\n");
	return TRUE;

}

COBL3Filter * COBL3Array::operator [] (char *sz)
{
	int i;
	for (i=0; i< GetSize(); i++)
	{
		if (stricmp(m_arrFilters[i]->m_szName, sz)==0)
		{
			return m_arrFilters[i];
		}
	}

	return NULL;
}

int COBL3Array::GetIndexFor (char *sz)
{
	return GetNameIndex(CString(sz));
}


