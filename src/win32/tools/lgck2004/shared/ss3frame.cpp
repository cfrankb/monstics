// SS3Frame.cpp : implementation file
//

#include "stdafx.h"
#include "SS3Frame.h"
#include "zlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSV3Frame

CSS3Frame::CSS3Frame()
{
	Init();
}

CSS3Frame::~CSS3Frame()
{

	Forget();
}


/////////////////////////////////////////////////////////////////////////////
// CSS3Frame message handlers

void CSS3Frame::Serialize(CArchive& ar, int nMode)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here

        ar << m_nLen;
        ar << m_nHei;
        ar << m_bMapped;

        if (m_bMapped)
        {
            ar.Write(m_pMap, m_nLen* m_nHei /IMG2MAP_RATIO);   
        }

        if ((m_nLen>0) && (m_nHei>0))
        {
            ULONG nDestLen = m_nLen* m_nHei + 1024;
            UCHAR *pDest = (UCHAR*)malloc(nDestLen);

            int err = compress(
                (UCHAR *)pDest, 
                (ULONG *)& nDestLen,
                (UCHAR *)m_pBitmap,
                (ULONG)m_nLen* m_nHei);
            
            //ar.Write(m_pBitmap, m_nLen* m_nHei );
            ar << nDestLen;
            ar.Write(pDest, nDestLen);
            free(pDest);
        }
        else
        {
            ar << (int) 0;        
        }          
    }
	else
	{
		// TODO: add loading code here

		if (!m_bPacked) {
			if (m_pBitmap) free (m_pBitmap);
		}

		if (m_pMap) free (m_pMap);

		m_pBitmap = NULL;
		m_pMap = NULL;

        ar >> m_nLen;
        ar >> m_nHei;
        ar >> m_bMapped;

        if (m_bMapped)
        {
            m_pMap = (char*) malloc (m_nLen*m_nHei/IMG2MAP_RATIO);
            ar.Read(m_pMap, m_nLen* m_nHei /IMG2MAP_RATIO);   
        }

        if ((m_nLen>0) && (m_nHei>0))
        {
            if (nMode!=MODE_ZLIB_ALPHA)
            {
                m_pBitmap = (char*) malloc (m_nLen*m_nHei) ;
                ar.Read(m_pBitmap, m_nLen* m_nHei);
            }
            else
            {
                ULONG nSrcLen;
                ar >> nSrcLen;
                UCHAR *pSrc = (UCHAR*)malloc(nSrcLen);
                ar.Read(pSrc, nSrcLen);

                ULONG nDestLen = m_nLen* m_nHei;
                m_pBitmap = (char*) malloc (m_nLen*m_nHei) ;

                int err = uncompress(
                    (UCHAR *)m_pBitmap, 
                    (ULONG *)& nDestLen,
                    (UCHAR *)pSrc,
                    (ULONG)nSrcLen);
            
                free(pSrc);            
            }
        }
        else
        {
            ar << (int) 0;
        }   
    }
}

CSS3Frame::CSS3Frame(int p_nLen, int p_nHei, char *pBitmap)
{
    Init();
    m_nLen = p_nLen;
    m_nHei = p_nHei;

    if (pBitmap ==NULL) {
        m_pBitmap = (char*)malloc (m_nLen * m_nHei)  ;
		ZeroMemory(m_pBitmap, m_nLen * m_nHei);
	}
    else {
        m_pBitmap = pBitmap;
	}
}


CSS3Frame::CSS3Frame(CSS3Frame* src, BOOL bClear)
{

 	if (src==this) return;

	Init();

    m_nHei = src->m_nHei;
    m_nLen = src->m_nLen;

    m_bMapped = src->m_bMapped;

	if (src->m_pBitmap!=NULL) 
	{
		m_pBitmap = (char*) malloc( src-> m_nLen* src->m_nHei);
		if (bClear==FALSE)
			memcpy( m_pBitmap, src->m_pBitmap, src-> m_nLen* src->m_nHei);
		else
			ZeroMemory(m_pBitmap, src-> m_nLen* src->m_nHei);
	}
	else 
    {
		m_pBitmap= (char*) NULL;
    }

	if (src->m_pMap!=NULL) 
	{
		m_pMap = (char*) malloc( src-> m_nLen* src->m_nHei/IMG2MAP_RATIO);
		if (bClear==FALSE)
			memcpy( m_pMap, src->m_pMap, src-> m_nLen* src->m_nHei/IMG2MAP_RATIO);
		else
			ZeroMemory(m_pMap, src-> m_nLen* src->m_nHei/IMG2MAP_RATIO);

	}
	else 
    {
		m_pMap= (char*) NULL;	
    }
}

void CSS3Frame::Init()
{
    m_pBitmap = NULL;
    m_pMap = NULL;

    m_nHei =0;
    m_nLen =0;

    m_bMapped =FALSE;

	// Packing if set to false by default
	m_bPacked = FALSE;

}

void CSS3Frame::Replace (CSS3Frame *src)
{
 	if (src==this) return;

    m_nHei = src->m_nHei;
    m_nLen = src->m_nLen;

    m_bMapped = src->m_bMapped;

	if (!m_bPacked)
	{
		if (m_pBitmap!=NULL) 
			free(m_pBitmap);
	}

	if (m_pMap!=NULL) 
		free (m_pMap);

	m_bPacked = FALSE;

	if (src->m_pBitmap!=NULL) {
		m_pBitmap = (char*) malloc( src-> m_nLen* src->m_nHei);
		memcpy( m_pBitmap, src->m_pBitmap, src-> m_nLen* src->m_nHei);
	}
	else 
		m_pBitmap= (char*) NULL;

	if (src->m_pMap!=NULL) {
		m_pMap = (char*) malloc( src-> m_nLen* src->m_nHei/IMG2MAP_RATIO);
		memcpy( m_pMap, src->m_pMap, src-> m_nLen* src->m_nHei/IMG2MAP_RATIO);
	}
	else 
		m_pMap= (char*) NULL;	
}

BOOL CSS3Frame::IsValid()
{
	return ((m_nLen!=0) && (m_nHei!=0) && (m_pBitmap!=NULL));
}

BOOL CSS3Frame::Dirty()
{
	CSS3Frame *pFrame = new CSS3Frame(this, FALSE);
	m_arrUndo.InsertAt(0,
		(CObject*) pFrame, 1);
	if (m_arrUndo.GetSize()>=MAX_UNDO)	{
		delete m_arrUndo[m_arrUndo.GetSize()-1];
		m_arrUndo.RemoveAt(m_arrUndo.GetSize()-1);
	}
	
	return TRUE;
}

BOOL CSS3Frame::Undo()
{

	if (CanUndo()==FALSE) 
		return FALSE;

// T -> R
	CSS3Frame *pFrame = new CSS3Frame(this, FALSE);
	m_arrRedo.InsertAt(0,
		(CObject*) pFrame, 1);

	if (m_arrRedo.GetSize()>=MAX_UNDO)	{
		delete m_arrRedo[m_arrRedo.GetSize()-1];
		m_arrRedo.RemoveAt(m_arrRedo.GetSize()-1);
	}


// U -> T
	// 99/03/16 addon
	this->Set(((CSS3Frame*)m_arrUndo[0])->m_nLen, 
		((CSS3Frame*)m_arrUndo[0])->m_nHei);

	this->NewImage( ((CSS3Frame*)m_arrUndo[0])->m_pBitmap);

	delete m_arrUndo[0];
	m_arrUndo.RemoveAt(0);

	return TRUE;
}


BOOL CSS3Frame::Redo()
{
	if (CanRedo()==FALSE) 
		return FALSE;

// T -> U
	CSS3Frame *pFrame = new CSS3Frame(this, FALSE);
	m_arrUndo.InsertAt(0,
		(CObject*) pFrame, 1);
	if (m_arrUndo.GetSize()>=MAX_UNDO)	{
		delete m_arrUndo[m_arrUndo.GetSize()-1];
		m_arrUndo.RemoveAt(m_arrUndo.GetSize()-1);
	}


// R -> T
	// 99/03/16 addon
	this->Set(((CSS3Frame*)m_arrRedo[0])->m_nLen, 
		((CSS3Frame*)m_arrRedo[0])->m_nHei);
	this->NewImage( ((CSS3Frame*)m_arrRedo[0])->m_pBitmap);

	delete m_arrRedo[0];
	m_arrRedo.RemoveAt(0);

	return TRUE;
}

BOOL CSS3Frame::CanUndo()
{
	return m_arrUndo.GetSize() >0 ;
}

BOOL CSS3Frame::CanRedo ()
{
	return m_arrRedo.GetSize() >0 ;
}

void CSS3Frame::Forget()
{
	if (!m_bPacked) {
		if (m_pBitmap!=NULL) free(m_pBitmap);
	}

	if (m_pMap!=NULL) free (m_pMap);

	m_nLen= 0;
	m_nHei =0;

	while (m_arrRedo.GetSize())	{
		delete m_arrRedo[0];
		m_arrRedo.RemoveAt(0);
	}

	while (m_arrUndo.GetSize())	{
		delete m_arrUndo[0];
		m_arrUndo.RemoveAt(0);
	}
}

void CSS3Frame::NewImage(char *pImage)
{

    if (IsValid())
		memcpy(m_pBitmap, pImage, m_nHei * m_nLen);
}


UCHAR * CSS3Frame::Point (int x, int y)
{

	if (!IsValid())
		return NULL;
	else
		if ((x>=m_nLen) || (y>=m_nHei) )
			return NULL;
		else
			return (UCHAR*) m_pBitmap + x + y * m_nLen;
}

void CSS3Frame::FlipHorz()
{
	CSS3Frame frmTemp (m_nLen, m_nHei);
	
	int x,y;
	for (y=0; y<m_nHei; y++)	{
		for (x=0; x<m_nLen; x++)	{
			* frmTemp.Point (m_nLen-x-1, y) =
			  *	Point (x, y);
		}
	}

	NewImage(frmTemp.m_pBitmap);
}

void CSS3Frame::FlipVert()
{

	CSS3Frame frmTemp (m_nLen, m_nHei);
	
	int x,y;
	for (y=0; y<m_nHei; y++)	{
		for (x=0; x<m_nLen; x++)		{
			* frmTemp.Point (x, m_nHei-y-1) =
			  *	Point (x, y);
		}
	}

	NewImage(frmTemp.m_pBitmap);
}


void CSS3Frame::ShiftUP()
{

	CSS3Frame frmTemp (m_nLen, m_nHei);
	
	int x,y;
	for (y=0; y<m_nHei-1; y++)	{
		for (x=0; x<m_nLen; x++)		{
			* frmTemp.Point (x, y) =
			  *	Point (x, y+1);
		}
	}

	for (x=0; x<m_nLen; x++)
		* frmTemp.Point (x, m_nHei-1) =
			  *	Point (x, 0);

	NewImage(frmTemp.m_pBitmap);
}


void CSS3Frame::ShiftDown()
{
	CSS3Frame frmTemp (m_nLen, m_nHei);
	
	int x,y;
	for (y=0; y<m_nHei-1; y++)	{
		for (x=0; x<m_nLen; x++)		{
			* frmTemp.Point (x, y+1) =
			  *	Point (x, y);
		}
	}

	for (x=0; x<m_nLen; x++)
		* frmTemp.Point (x, 0) =
			  *	Point (x, m_nHei-1);

	NewImage(frmTemp.m_pBitmap);
}


void CSS3Frame::ShiftLeft()
{
	CSS3Frame frmTemp (m_nLen, m_nHei);
	
	int x,y;
	for (y=0; y<m_nHei; y++)	{
		for (x=0; x<m_nLen-1; x++)		{
			* frmTemp.Point (x, y) =
			  *	Point (x+1, y);
		}
	}

	for (y=0; y<m_nHei; y++)
		* frmTemp.Point (m_nLen-1, y) =
			  *	Point (0, y);

	NewImage(frmTemp.m_pBitmap);
}

void CSS3Frame::ShiftRight()
{
	CSS3Frame frmTemp (m_nLen, m_nHei);
	
	int x,y;
	for (y=0; y<m_nHei; y++)	{
		for (x=0; x<m_nLen-1; x++)		{
			* frmTemp.Point (x+1, y) =
			  *	Point (x, y);
		}
	}

	for (y=0; y<m_nHei; y++)
		* frmTemp.Point (0, y) =
			  *	Point (m_nLen-1, y);

	NewImage(frmTemp.m_pBitmap);
}

void CSS3Frame::Erase()
{
	if (IsValid())
		::ZeroMemory (m_pBitmap, m_nLen * m_nHei);
}

void CSS3Frame::FloodFill (int x, int y, UCHAR bOldColor, UCHAR bNewColor  )
{

	int ex=x;
	if (Point (x,y)==NULL) return;
    for (; (x>=0) && *Point(x,y)
            ==bOldColor; x--)
    {
        *Point(x,y) =bNewColor;
		if ((y>0) && (*Point (x,y-1) ==bOldColor))
			FloodFill (x,y-1, bOldColor, bNewColor);
		
		if ((y<m_nHei-1) && (*Point (x,y+1) ==bOldColor))
			FloodFill (x,y+1, bOldColor, bNewColor);      
    }

	x=ex +1;
	if (Point (x,y)==NULL) return;
    for (; (x<m_nLen) && *Point(x,y)
            ==bOldColor; x++)
    {
        *Point(x,y) =bNewColor;
		if ((y>0) && (*Point (x,y-1) ==bOldColor))
			FloodFill (x,y-1, bOldColor, bNewColor);
		
		if ((y<m_nHei-1) && (*Point (x,y+1) ==bOldColor))
			FloodFill (x,y+1, bOldColor, bNewColor);
        
    }	
}

void CSS3Frame::Rotate90()
{
	CSS3Frame frmTemp (m_nLen, m_nHei);
	
	int x,y;

	if ((m_nLen!=m_nHei) || (IsValid()==FALSE)) return;

	for (y=0; y<m_nHei; y++)
	{
		for (x=0; x<m_nLen; x++)
		{
			* frmTemp.Point (m_nLen-y-1, x) =
			  *	Point (x, y);
		}
	}

	NewImage(frmTemp.m_pBitmap);
}

void CSS3Frame::Resize (int nLen, int nHei)
{
	CSS3Frame frmTemp (nLen, nHei);

	int x,y;
	for (y=0; y < min (nHei, m_nHei); y++)
	{
		for ( x=0 ; x< min (nLen, m_nLen); x++)
		{
			* frmTemp.Point (x,y) =
			  *	Point (x, y);		
		}
	}

	delete m_pBitmap;
	m_nLen = nLen;
	m_nHei = nHei;
	m_pBitmap = (CHAR *)malloc (nLen*nHei);

	NewImage(frmTemp.m_pBitmap);

}



void CSS3Frame::Enlarge2x()
{

	CSS3Frame frmTemp (m_nLen*2, m_nHei*2);

	int x,y;
	for (y=0; y < m_nHei;y++)
	{
		for ( x=0 ; x< m_nLen; x++)
		{
			* frmTemp.Point (x*2,y*2) =
			  *	Point (x, y);		

			* frmTemp.Point (x*2+1,y*2) =
			  *	Point (x, y);		

			* frmTemp.Point (x*2,y*2+1) =
			  *	Point (x, y);		

			* frmTemp.Point (x*2+1,y*2+1) =
			  *	Point (x, y);		
		}
	}

	delete m_pBitmap;
	m_nLen = m_nLen*2;
	m_nHei = m_nHei*2;
	m_pBitmap = (CHAR *)malloc (m_nLen*m_nHei);
	NewImage(frmTemp.m_pBitmap);

}

void CSS3Frame::InverseColor ()
{
	int x,y;

	for (y=0; y < m_nHei;y++)	{
		for ( x=0 ; x< m_nLen; x++)		{
			* Point (x, y)=
			~( * Point (x, y) -0x10) + 0x10;		
		}
	}
}


void CSS3Frame::RainbowEffect ()
{
	int x,y;

	for (y=0; y < m_nHei;y++)	{
		for ( x=0 ; x< m_nLen; x++)		{
			if (* Point (x, y) ) 
				 (* Point (x, y)) ++;
		}
	}
}

void CSS3Frame::RainbowEffectExclude (UCHAR nColor)
{
	int x,y;

	for (y=0; y < m_nHei;y++)	{
		for ( x=0 ; x< m_nLen; x++)		{
			if (* Point (x, y) !=0 &&
				* Point (x, y) !=nColor) 
				 (* Point (x, y)) ++;
		}
	}
}

CSS3Frame & CSS3Frame::operator = (CSS3Frame &src)
{
	Replace (&src);
	return *this;
}

void CSS3Frame::Write (CFile & file)
{
	file.Write(&m_nLen,4);
	file.Write(&m_nHei,4);
    file.Write(&m_bMapped,4);

    if (m_bMapped)
    {
		file.Write(m_pMap, m_nLen* m_nHei /IMG2MAP_RATIO);   
    }

    if ((m_nLen>0) && (m_nHei>0))
    {
        //file.Write(m_pBitmap, m_nLen* m_nHei);
        ULONG nDestLen = m_nLen* m_nHei + 1024;
        UCHAR *pDest = (UCHAR*)malloc(nDestLen);

        int err = compress(
           (UCHAR *)pDest, 
           (ULONG *)& nDestLen,
           (UCHAR *)m_pBitmap,
           (ULONG)m_nLen* m_nHei);
            
        file.Write(&nDestLen,4);
        file.Write(pDest, nDestLen);
        free(pDest);
    }
    else
    {
        int nTemp = 0;
        file.Write(&nTemp, 4);
    }
}

void CSS3Frame::Read (CFile & file, int nMode)
{
	if (!m_bPacked)
	{
		if (m_pBitmap) free (m_pBitmap);
	}

	m_bPacked=FALSE;
	if (m_pMap) free (m_pMap);

	m_pBitmap = NULL;
	m_pMap = NULL;

	file.Read (&m_nLen, sizeof (m_nLen));
	file.Read (&m_nHei, sizeof (m_nHei));
	file.Read (&m_bMapped, sizeof (m_bMapped));

    if (m_bMapped)
    {
		m_pMap = (char*) malloc (m_nLen*m_nHei/IMG2MAP_RATIO);
        file.Read(m_pMap, m_nLen* m_nHei /IMG2MAP_RATIO);   
    }

    if ((m_nLen>0) && (m_nHei>0))
    {
        if (nMode!= MODE_ZLIB_ALPHA)
        {
            m_pBitmap = (char*) malloc (m_nLen*m_nHei) ;
            file.Read(m_pBitmap, m_nLen* m_nHei );
        }
        else
        {
            ULONG nSrcLen;
            file.Read(&nSrcLen, 4);
            UCHAR *pSrc = (UCHAR*)malloc(nSrcLen);
            file.Read(pSrc, nSrcLen);

            ULONG nDestLen = m_nLen* m_nHei;
            m_pBitmap = (char*) malloc (m_nLen*m_nHei) ;

            int err = uncompress(
                (UCHAR *)m_pBitmap, 
                (ULONG *)& nDestLen,
                (UCHAR *)pSrc,
                (ULONG)nSrcLen);
            
            free(pSrc);            
        }
    }
}

void CSS3Frame::SpreadHorz ()
{
	CSS3Frame frmTemp (m_nLen*2, m_nHei);

	int x,y;
	for (y=0; y < m_nHei;y++)
	{
		for ( x=0 ; x< m_nLen; x++)
		{
			* frmTemp.Point (x,y) =
				* Point (x,y); 

			* frmTemp.Point (m_nLen+x,y) =
				* Point (x,y); 
		}
	}

	delete m_pBitmap;
	m_nLen = m_nLen*2;
	m_nHei = m_nHei;
	m_pBitmap = (CHAR *)malloc (m_nLen*m_nHei);
	NewImage(frmTemp.m_pBitmap);

}


void CSS3Frame::SpreadVert ()
{
	CSS3Frame frmTemp (m_nLen, m_nHei*2);

	int x,y;
	for (y=0; y < m_nHei;y++)
	{
		for ( x=0 ; x< m_nLen; x++)
		{

			* frmTemp.Point (x,y) =
				* Point (x,y); 

			* frmTemp.Point (x,m_nHei+y) =
				* Point (x,y); 

		}
	}

	delete m_pBitmap;
	m_nLen = m_nLen;
	m_nHei = m_nHei*2;
	m_pBitmap = (CHAR *)malloc (m_nLen*m_nHei);
	NewImage(frmTemp.m_pBitmap);

}

BOOL CSS3Frame::IsPacked ()
{
	return m_bPacked;
}


void CSS3Frame::SetPacked ()
{
	m_bPacked = TRUE;
}

void CSS3Frame::Shrink()
{
	CSS3Frame frmTemp (m_nLen/2, m_nHei/2);

	int x,y;
	for (y=0; y < (m_nHei/2);y++)
	{
		for ( x=0 ; x< (m_nLen/2); x++)
		{
			if (frmTemp.Point(x,y)
				&& Point (x*2,y*2))
					* frmTemp.Point(x,y) =
						* Point (x*2,y*2);
		}
	}

	delete m_pBitmap;
	m_nLen = m_nLen/2;
	m_nHei = m_nHei/2;
	m_pBitmap = (CHAR *)malloc (m_nLen*m_nHei);
	NewImage(frmTemp.m_pBitmap);

}

void CSS3Frame::CopyImage (CSS3Frame * src)
{
	if (!src->IsValid())
		return;
	
	if ((m_nLen != src->m_nLen) ||
		(m_nHei != src->m_nHei))
	{
		if (m_pBitmap && !IsPacked())
			free (m_pBitmap);
		m_pBitmap = (char*)malloc (src->m_nLen * src->m_nHei);
		m_bPacked = FALSE;

		// TODO: Adjust map to new size
		m_bMapped = 0;
		if (m_pMap)
			free (m_pMap);
		m_pMap = NULL;
	}

	m_nLen =  src->m_nLen;
	m_nHei =  src->m_nHei;
	NewImage (src->m_pBitmap);

}

void CSS3Frame::Set (int nLen, int nHei)
{
	if (m_pBitmap!=NULL)
		free (m_pBitmap);

	m_pBitmap = (char*)malloc (nLen * nHei);
	ZeroMemory (m_pBitmap, nLen* nHei);

	if (m_pMap!=NULL)
	{
		free (m_pMap);
		m_pMap = NULL;
	}

	m_nLen = nLen;
	m_nHei = nHei;

}
