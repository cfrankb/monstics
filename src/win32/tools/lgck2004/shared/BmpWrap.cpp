// BmpWrap.cpp : implementation file
//

#include "stdafx.h"
#include "BmpWrap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpWrap

CBmpWrap::CBmpWrap()
{
	m_pBits=NULL;
	Forget();
}

CBmpWrap::~CBmpWrap()
{
	Forget();
}


/////////////////////////////////////////////////////////////////////////////
// CBmpWrap message handlers

BOOL CBmpWrap::Read (CString strFilename)
{
	// Can only read pure RGB files

    CFile file;
    CFileException e;

	UCHAR szSig[] = ".." ; // BM

    if (!file.Open(strFilename, 
		CFile::modeRead | CFile::typeBinary, &e ))
    {
#ifdef _DEBUG
		OutputDebugString ("Error: Cannot read file\n");
#endif
		return NULL;
    }
	
	file.Read (szSig, 2);
	if (CString (szSig)!="BM")
	{
		file.Close();
		OutputDebugString ("Error: Not a valid BMP\n");
		return FALSE;
	}
	file.Read (&m_bmpHeader, sizeof (m_bmpHeader));
	
	if (m_bmpHeader.m_nBitCount!=24)
	{
		Forget();
		file.Close();
		OutputDebugString ("Error: Not 24bpp\n");
		return FALSE;
	}

	m_pBits = (UCHAR*)malloc (m_bmpHeader.m_nImageSize);
	file.Read (m_pBits, m_bmpHeader.m_nImageSize);

	m_nLen = m_bmpHeader.m_nLen;
	m_nHei = m_bmpHeader.m_nHei;
	m_nPitch = m_nLen * 3;

	if (m_nPitch %4)
		m_nPitch = m_nPitch - (m_nPitch %4) +4;


	if (m_nHei<0) {
		m_nHei = - m_nHei;
		FlipUpDown ();
	}

	file.Close();
	
	return TRUE;
}

BOOL CBmpWrap::Write (CString strFilename)
{
    CFile file;
    CFileException e;

	UCHAR szSig[] = "BM" ; // BM

	if (!file.Open(strFilename, CFile::modeWrite|
		CFile::modeCreate 
		| CFile::typeBinary, &e ))
	{
#ifdef _DEBUG
		afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
		return FALSE;
	}

	file.Write (szSig, 2);
	file.Write (&m_bmpHeader, sizeof (m_bmpHeader));
	
	if (m_pBits)
		file.Write (m_pBits, m_bmpHeader.m_nImageSize);

	file.Close();

	return TRUE;
}

void CBmpWrap::Forget ()
{
	if (m_pBits) 
		free (m_pBits);

	m_pBits = NULL;

	ZeroMemory (&m_bmpHeader, sizeof (USER_BMPHEADER));
	m_nLen=0;
	m_nHei=0;
	m_nPitch=0;
}

int CBmpWrap::GetPitch ()
{
	return m_nPitch;
}


BOOL CBmpWrap::Split (CString strFilename, int nCols, int nRows)
{

	BOOL bError = FALSE;

	int nLen = m_nLen / nCols;
	int nHei = m_nHei / nRows;
	CString str;

	CBmpWrap wrap (nLen, nHei);

	int x,y;
	int xx,yy;
	for (y=0; y<nRows; y++)
	{
		for (x=0; x<nCols; x++)
		{
			for (yy=0; yy<nHei; yy++)
			{
				for (xx=0; xx<nLen; xx++)
				{
					if (Point(xx,yy) && Point (x*nLen+xx, y*nHei+yy))
						* wrap.Point(xx,yy) =
							* Point (x*nLen+xx, y*nHei+yy);
				}
			}

			str.Format("%s%c%c.bmp", strFilename, 'a'+nRows-y-1, 'a'+x);
			bError = bError || (wrap.Write (str) ==0) ;
		}
	}


	return !bError;
}

int CBmpWrap::GetLen ()
{
	return m_nLen;
}

int CBmpWrap::GetHei ()
{
	return m_nHei;
}

void CBmpWrap::Size (int nLen, int nHei)
{
	m_pBits = NULL;
	Forget();

	m_nLen = nLen;
	m_nHei = nHei;
	m_nPitch = m_nLen * 3;

	if (m_nPitch %4)
		m_nPitch = m_nPitch - (m_nPitch %4) +4;

	m_bmpHeader.m_nTotalSize = 54+ m_nPitch * m_nHei;
	m_bmpHeader.m_nDiff = 54;
	m_bmpHeader.m_n28   = 40;

	m_bmpHeader.m_nLen = nLen;
	m_bmpHeader.m_nHei = nHei;
	m_bmpHeader.m_nPlanes = 1; // always 1
	m_bmpHeader.m_nBitCount = 24;

	m_bmpHeader.m_nImageSize = m_nPitch* m_nHei;

	m_pBits = (UCHAR*) malloc (m_nPitch* m_nHei);
	ZeroMemory (m_pBits, m_nPitch* m_nHei);
}

CBmpWrap::CBmpWrap (int nLen, int nHei)
{
	Size (nLen, nHei);
}


USER_3BYTES * CBmpWrap::Point (int x, int y)
{
	if (!IsValid () 
		|| (x<0) 
		|| (x>= m_nLen) 
		|| (y<0) 
		|| (y>= m_nHei))
			return NULL;		

	return (USER_3BYTES *) (m_pBits + x*3 + y*m_nPitch);
}

BOOL CBmpWrap::IsValid ()
{
	if ((m_nPitch ==0) ||
		(m_pBits==NULL))
		return FALSE;
	else
		return TRUE;
}

void CBmpWrap::FlipUpDown ()
{
	int y;
	char *pBits = (char*) malloc (m_nHei* m_nPitch);
	if (!pBits)
	{
		OutputDebugString("FlipUpDown() failed - insufficient memory\n");
		return;
	}

	if (!IsValid())
	{
		OutputDebugString("CBmpWrap Object - not valid i.e. flip aborted\n");
		return;
	}

	for (y=0; y<m_nHei; y++)
	{
		memcpy (pBits+y*m_nPitch, 
				m_pBits+ (m_nHei-1-y)*m_nPitch,
					m_nPitch);
	}

	memcpy (m_pBits, pBits, m_nHei*m_nPitch);
	free(pBits);

	OutputDebugString ("FlipUpDown done!\n");
}

