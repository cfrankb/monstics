// ProtoArray.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoArray.h"
#include "file.h"
#include "zlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZEOF (sizeof (CProto))
#define GROWBY (16)

#define PROTO_VER 0x2

/////////////////////////////////////////////////////////////////////////////
// CProtoArray

CProtoArray::CProtoArray()
{
	m_nSize=0;
	m_nMax = GROWBY;
	m_arrProto = (CProto*)malloc (SIZEOF * m_nMax);
	ZeroMemory (m_arrProto, SIZEOF * m_nMax);
}

CProtoArray::~CProtoArray()
{
	Forget();
	free (m_arrProto);
}

/////////////////////////////////////////////////////////////////////////////
// CProtoArray message handlers

void CProtoArray::Serialize (CArchive & ar)
{
    int err;
    int nEntrySize;
    int i=0;
    int nVersion = PROTO_VER;
	ULONG nTotalSize;
    ULONG nCompressSize;
    UCHAR * pCompressData;
    int nProtoSize;

	if (ar.IsStoring())	{ 
		// Storing CODE

        /*
		ar << m_nSize;
		ar << (int) sizeof (CProto);
		for (n=0; n<m_nSize; n++)
			m_arrProto[n].Serialize(ar);
        */

        ar << (int) -1;
        ar << (int) nVersion;
        ar << m_nSize;
        ar << (int) sizeof (CProto);

        nTotalSize = m_nSize * sizeof (CProto);
        nCompressSize = nTotalSize + 2048; 
        pCompressData = (UCHAR*) malloc(nCompressSize);

        err = compress(
           (UCHAR *)pCompressData, 
           (ULONG *)& nCompressSize,
           (UCHAR *)m_arrProto,
           (ULONG)nTotalSize);

        ar << (int) nTotalSize;
        ar << (int) nCompressSize;
        ar.Write (pCompressData, nCompressSize);

        free(pCompressData);
	}
	else 
    {
		// Loading CODE
		Forget();
		CProto proto;
		ar >> i;
        if (i!=-1)
        {
		    ar >> nEntrySize;
		    while (i)	
            {
			    proto.Serialize(ar, nEntrySize);
			    Add (proto);
			    i--;
		    }
        }
        else
        {
            ar >> (int) nVersion;
            ar >> m_nSize;
            m_nMax = m_nSize;
            ar >> (int) nProtoSize;

            ar >> nTotalSize;
            ar >> nCompressSize;
            pCompressData = (UCHAR*) malloc(nCompressSize);
            ar.Read (pCompressData, nCompressSize);

            if (m_arrProto)
            {
                free(m_arrProto);
            }

            m_arrProto = (CProto*) malloc(nTotalSize);

            err = uncompress(
               (UCHAR *)m_arrProto, 
               (ULONG *)& nTotalSize,
               (UCHAR *)pCompressData,
               (ULONG)nCompressSize);

            free(pCompressData);           
        }
	}
}

void CProtoArray::Read (CFile & file)
{
    /*
	int n;
	int nSize;

	Forget();
	CProto proto;

	file.Read (&n, sizeof(n));
	file.Read (&nSize, sizeof(nSize));

	while (n)	{
		proto.Read(file, nSize);
		Add (proto);
		n--;
	}
    */

    int err;
    int nEntrySize;
    int i=0;
    int nVersion = PROTO_VER;
	ULONG nTotalSize;
    ULONG nCompressSize;
    UCHAR * pCompressData;
    int nProtoSize;

	Forget();
	CProto proto;
	file.Read (&i, sizeof(i));

    if (i!=-1)
    {
	    file.Read (&nEntrySize, sizeof(nEntrySize));
    	while (i)	{
	    	proto.Read(file, nEntrySize);
		    Add (proto);
		    i--;
	    }
    }
    else
    {
         file >> (int) nVersion;
         file >> m_nSize;
         m_nMax = m_nSize;
         file >> (int) nProtoSize;

         file.Read(&nTotalSize,4);
         file.Read(&nCompressSize,4);
         pCompressData = (UCHAR*) malloc(nCompressSize);
         file.Read (pCompressData, nCompressSize);

         if (m_arrProto)
         {
            free(m_arrProto);
         }

         m_arrProto = (CProto*) malloc(nTotalSize);

         err = uncompress(
            (UCHAR *)m_arrProto, 
            (ULONG *)& nTotalSize,
            (UCHAR *)pCompressData,
            (ULONG)nCompressSize);

        free(pCompressData);           
    }
}


void CProtoArray::Forget()
{
	m_nSize=0;
}

void CProtoArray::Add (CProto & proto)
{
	if (m_nSize==m_nMax)
	{
		m_nMax = m_nMax + GROWBY;
		CProto *t = (CProto*) malloc (SIZEOF * m_nMax);
		ZeroMemory (t, SIZEOF * m_nMax);
		memcpy (t, m_arrProto, SIZEOF * m_nSize);
		free (m_arrProto);
		m_arrProto = t;
	}

	m_arrProto[m_nSize] = proto;
	m_nSize++;

}

void CProtoArray::RemoveAt (int n)
{
	int i;
	for (i=n; i<m_nSize-1;	i++)
	{
		m_arrProto[i] = m_arrProto[i+1];
	}
	m_nSize--;
}

CProto protoTmp;

CProto & CProtoArray::operator [] (int n)
{
	if ((n<0) || (n>=m_nSize))
		return protoTmp;
	else
		return m_arrProto[n];
}

int CProtoArray::GetSize()
{
	return m_nSize;
}

int CProtoArray::GetProtoIndex (const CString & str)
{
	int i;
	for (i=0; i<m_nSize; i++)
	{
		if (CString(m_arrProto[i].m_szName).
			CompareNoCase(str)==0)
			return i;
	}
	return -1;
}

void CProtoArray::KillFrameSet (int nFrameSet)
{
	int i;
	for (i=0; i<GetSize(); i++)
	{
		if (m_arrProto[i].m_nFrameSet == nFrameSet)
		{
			m_arrProto[i].m_nFrameSet=0;
			m_arrProto[i].m_nFrameNo=0;
		}

		if (m_arrProto[i].m_nFrameSet > nFrameSet)
		{
			m_arrProto[i].m_nFrameSet--;
		}
	}
}

void CProtoArray::KillProto (int nProto)
{
	int i;
	for (i=0; i<GetSize(); i++)
	{
		if (m_arrProto[i].m_nChProto == nProto)
		{
			m_arrProto[i].m_nChProto=0;

		}

		if (m_arrProto[i].m_nChProto > nProto)
		{
			m_arrProto[i].m_nChProto--;
		}
	}
	RemoveAt (nProto);
}

CProto & CProtoArray::GetProto(CScriptEntry & entry)
{
	if (entry.m_nProto<0 || entry.m_nProto>m_nSize)
	{
		return protoTmp;
	}
	else
	{
		return m_arrProto[entry.m_nProto];
	}
}
