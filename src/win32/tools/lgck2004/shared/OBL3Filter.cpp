// OBL3Filter.cpp : implementation file
//

#include "stdafx.h"
#include "OBL3Filter.h"
#include "ss3frame.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COBL3Filter

#define OBL_VERSION 0x400
#define GROWBY 16
#define SIZEOF (sizeof(CSS3Frame *))

COBL3Filter::COBL3Filter()
{
	m_arrFrames = (CSS3Frame**) malloc (GROWBY * SIZEOF);
	ZeroMemory (m_arrFrames, GROWBY * SIZEOF );
	m_szName[0] = 0;
	m_szFilename[0] = 0;

	m_nCurrFrame = 0;
	m_nMax = GROWBY;
	m_nSize = 0;

	// By default the frame filter is not packed
	m_bPacked = FALSE;
	m_pPackedBits = NULL;
	m_pFrameData = NULL;
}

COBL3Filter::~COBL3Filter()
{
	Forget();
	m_nMax =0;
	free (m_arrFrames);
}

/////////////////////////////////////////////////////////////////////////////
// COBL3Filter serialization

void COBL3Filter::Serialize(CArchive& ar)
{
    char szTemp[1024];
    CWnd *pWnd = AfxGetMainWnd();
    int i;

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar.Write( "OBL4",4);
		ar<< (int) GetSize();
		ar << (int) MODE_ZLIB_ALPHA; 

		for (i=0; i<GetSize(); i++)
		{
			m_arrFrames[i]->Serialize(ar, MODE_ZLIB_ALPHA) ;

            if (pWnd && (m_nSize>16))
            {
                wsprintf(szTemp, "Packing frames: %d of %d (%d %%) done", 
                    i,
                    m_nSize,
                    100 * i / m_nSize);
                pWnd->SendMessage(WM_USER_SET_STATUS, (UINT) szTemp, 0);
            }        
        }
	}
	else
	{
		// TODO: add loading code here
		char szVersion[5] = "xxxx";
		int nObjects; 

		ar.Read(szVersion,4) ;	

		if (strcmp(szVersion, "OBL4")!=0)
		{ // de-serialize older objects

			Forget();
			ar.Flush();
			CFile *pFile = ar.GetFile();
			
			CString strFilename;
			strFilename = pFile->GetFilePath();

			if (Extract (strFilename, *pFile, FALSE) !=TRUE)
			{
				// Error Occured!
			}; 
		}
		else
		{ 
            // reading OBL4 format

			int nMode;
			ar >> nObjects;
			ar >> nMode;
	
			Forget();
			CSS3Frame frmTemp;

			for (i=0; i<nObjects; i++)
			{			

                if (pWnd && (m_nSize>16))
                {
                    wsprintf(szTemp, "Unpacking frames: %d of %d (%d %%) done", 
                        i,
                        m_nSize,
                        100 * i / m_nSize);
                    pWnd->SendMessage(WM_USER_SET_STATUS, (UINT) szTemp, 0);
                }

				frmTemp.Serialize(ar, nMode);
				Add (new CSS3Frame);
				((CSS3Frame*) m_arrFrames[i] )->Replace(&frmTemp);
			} // for n
		} // else	
	}
}

void COBL3Filter::Write (CFile & file)
{
    int nMode = MODE_ZLIB_ALPHA;

	file.Write( "OBL4",4);
	file.Write( &m_nSize, 4);
	file.Write( &nMode, 4);

	int n;
	for (n=0; n<GetSize(); n++)
	{
		m_arrFrames[n]->Write(file) ;
	}
}

void COBL3Filter::Read (CFile & file)
{
    // if the data is compressed
    // nMode will be equal to MODE_ZLIB_ALPHA

	int nTotalSize=0;
	char szVersion[5] = "xxxx";

	file.Read(szVersion,4) ;	

	int nObjects; 
	int nMode;
	file.Read (&nObjects, sizeof (nObjects));
	file.Read (&nMode, sizeof (nMode));
	
	Forget();
	CSS3Frame frmTemp;

	int n;
	for (n=0; n<nObjects; n++)
	{			
		frmTemp.Read(file, nMode);
		Add (new CSS3Frame);
		((CSS3Frame*) m_arrFrames[n] )->Replace(&frmTemp);
	} // for n
}

/////////////////////////////////////////////////////////////////////////////
// COBL3Filter commands

int COBL3Filter::Extract (CString p_strFilename)
{

    CFile file;
    CFileException e;

    if (!file.Open(p_strFilename, CFile::modeRead | CFile::typeBinary, &e ))
    {
#ifdef _DEBUG
		afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
		return NULL;
    }

	return Extract(p_strFilename, file);

}

int COBL3Filter::Add (CSS3Frame *p_pFrame)
{

	if (m_nSize!= m_nMax)	{
		m_arrFrames[m_nSize] = p_pFrame;
		m_nSize++;
	}
	else
	{
		m_nMax = m_nMax + GROWBY;
		CSS3Frame **t = (CSS3Frame **) 
			malloc (sizeof (CSS3Frame*) * m_nMax );

		ZeroMemory (t, sizeof (CSS3Frame*) * m_nMax );
		
		memcpy (t, m_arrFrames, m_nSize * sizeof (CSS3Frame*) );
		t[m_nSize] = p_pFrame;
		m_nSize++;

		delete m_arrFrames;
		m_arrFrames = t;
	}
    
	return TRUE;
}

char * COBL3Filter::Ima2Bitmap(char *ImaData, int len, int hei)
{
    
    int x;
    int y;
    int x2;
    int y2;

    char *dest;
   
    if (ImaData ==NULL) return NULL;

    dest = (char *) malloc (len*hei*64);
    if (dest==NULL) return NULL; 

    for (y=0; y<hei; y++)    
    {
        for (x=0; x<len; x++)
        {
            for (y2=0; y2<8; y2++)         
            {
                for (x2=0; x2<8; x2++)
                {
					if (*(ImaData+(x+y*len)*64+x2+y2*8))
						*(dest + x*8+x2+(y*8+y2)*len*8) = 16+
							*(ImaData+(x+y*len)*64+x2+y2*8);
					else
						*(dest + x*8+x2+(y*8+y2)*len*8) = 0;
                }
            }
        }
    }

    return dest;
}

CSS3Frame t_frame(8,8);

CSS3Frame * COBL3Filter::operator[](int n) 
{
	if (n & 0x8000)
    {
		n = 0;
    }

	if (n < m_nSize && n>=0)
	{
		return m_arrFrames[n];
	}
	else
	{
		return &t_frame;
	}
}

void COBL3Filter::Forget()
{
	if (m_bPacked)
	{
		m_bPacked= FALSE;
		free (m_pPackedBits);
		m_pPackedBits=NULL;

		if (m_pFrameData)
		{
			int i;
			for (i=0; i<m_nSize; i++)
			{
				m_pFrameData[i].Forget();
			}

			//OutputDebugString("m_pFrameData() deleted\n");
			free (m_pFrameData);
			m_pFrameData=NULL;
		}
		else
		{
			while (GetSize()!=0)
			{
				delete m_arrFrames[0];
				RemoveAt(0);    
			};
		}

	}
	else
	{
		while (GetSize()!=0)
		{
			delete m_arrFrames[0];
			RemoveAt(0);    
		};

	}

	m_nCurrFrame =0;
	m_nSize =0;
}

int COBL3Filter::GetSize() inline
{
	return m_nSize;
}

int COBL3Filter::operator ++()
{
	this->Add(new CSS3Frame);
	return this->GetSize()-1;
}

int COBL3Filter::operator --()
{
	if (this->GetSize()==0) return 0;
	delete m_arrFrames[this->GetSize()];
	RemoveAt(this->GetSize()-1);
	return this->GetSize()-1;
}

int COBL3Filter::Extract (CString p_strFilename, CFile & file, BOOL bClose)
{
    file.Seek( CFile::begin , 0 );
	
	char l_szId[5]; 
    ::ZeroMemory(l_szId,5);
    int l_nCpt;

    file.Read(l_szId,4);
    CString l_strId = l_szId;

    if (l_strId=="OBL4")
    {
        file.Seek( CFile::begin , 0 );
        Read(file);

        /*
        CSS3Frame *l_pData;
		int nImages;
		int nCurrFrame;
		int nBidon;
		file.Read (&nBidon, 4);
		file.Read (&nImages, 4);
		file.Read (&nCurrFrame, 4);

        for (l_nCpt=0; l_nCpt<(INT)nImages; l_nCpt++)
		{
            l_pData = new CSS3Frame;

			file.Read (&l_pData->m_nLen, 4);
			file.Read (&l_pData->m_nHei, 4);
			file.Read (&l_pData->m_nMapped, 4);
			
	        if (l_pData->m_nMapped) {

				l_pData->m_pMap = (char*)
					malloc ( l_pData->m_nLen* l_pData->m_nHei /IMG2MAP_RATIO);  

				file.Read (l_pData->m_pMap, 
					l_pData->m_nLen* l_pData->m_nHei /IMG2MAP_RATIO);

			}

			if ((l_pData->m_nLen>0) || (l_pData->m_nHei>0)) {

				l_pData->m_pBitmap = (char *)
					malloc(l_pData->m_nLen *l_pData->m_nHei);

				file.Read (l_pData->m_pBitmap, 
					l_pData->m_nLen* l_pData->m_nHei );
			
			}

            this->Add(l_pData);		
		}
        */

        if (bClose)
			file.Close();

        return TRUE;
	}


    if (l_strId=="OBL3")
    {
        file.Seek( CFile::begin , 0 );
        USER_OBL3HEADER l_oblHead;
        file.Read(&l_oblHead, sizeof(USER_OBL3HEADER));

        CSS3Frame *l_pData;

        for (l_nCpt=0; l_nCpt<(INT)l_oblHead.iNbrImages; l_nCpt++)
        {
            l_pData = new CSS3Frame;
            l_pData->m_nLen = l_oblHead.iLen *16;
            l_pData->m_nHei = l_oblHead.iHei *16;
            l_pData->m_pBitmap = (char *)malloc(l_oblHead.iLen *16 *l_oblHead.iHei *16);

            USER_OBL3 l_obl;
            file.Read(&l_obl, sizeof(USER_OBL3));
            file.Read(l_pData->m_pBitmap, l_oblHead.iLen *16 *l_oblHead.iHei *16);

            this->Add(l_pData);

        }
        if (bClose)
			file.Close();

        return TRUE;
 
    }

   if (l_strId=="GE96")
   {
        file.Seek( CFile::begin , 0 );
        USER_MCXHEADER l_mcxHead;
        file.Read(&l_mcxHead, sizeof(USER_MCXHEADER));
       
        for (l_nCpt=0; l_nCpt<(INT)l_mcxHead.NbrImages; l_nCpt++)
        {
        
            CSS3Frame *l_pData = new CSS3Frame;
            l_pData->m_nLen = 32;
            l_pData->m_nHei = 32;
            l_pData->m_pBitmap = (char *)malloc(32*32);

            USER_MCX l_mcx;
            file.Read(&l_mcx, sizeof(USER_MCX));
            memcpy(l_pData->m_pBitmap, &l_mcx.ImageData[0][0], 32*32);

            this->Add(l_pData);

        }
        if (bClose)
	        file.Close();

        return TRUE;
 
   }


   if (l_strId=="IMC1")
   {
        USER_IMC1HEADER l_imc1Head;

        file.Seek( CFile::begin , 0 );
        file.Read(&l_imc1Head, 6);
        file.Read(&l_imc1Head.SizeData, 4);

        UCHAR *l_pIMC1 = (UCHAR *)malloc (l_imc1Head.SizeData);
        file.Read(l_pIMC1, l_imc1Head.SizeData);

        UCHAR *l_pIMA = (UCHAR *) malloc (l_imc1Head.len * l_imc1Head.hei * 64 +1);

        if (bClose)
	        file.Close();

        int loop;
        int cpt;
        UCHAR car;
        UCHAR *ptr = l_pIMA;
        UCHAR *ptrIMC1 = l_pIMC1;

        int safetycpt =0;

		for (cpt=0; (cpt< (l_imc1Head.SizeData-1))
			&& (safetycpt< (l_imc1Head.len * l_imc1Head.hei * 64));)
        {

            if (*ptrIMC1==0xff)
            {
                
                car = *(ptrIMC1+1);
                for (loop = (*(ptrIMC1+2) + *(ptrIMC1+3) *256);
                            (loop !=0 )                                 
                                ; loop--, ptr++)
                    *ptr = car;

                safetycpt = safetycpt + (*(ptrIMC1+2) + *(ptrIMC1+3) *256);
                ptrIMC1 = ptrIMC1+4;
                cpt = cpt+4;

            }

            else
            {
                *ptr = *ptrIMC1;                                
                ptr ++;
                ptrIMC1 ++;
                cpt++;

                safetycpt ++;

            }

        }

        CSS3Frame *l_pData = new CSS3Frame;
        l_pData->m_nLen = l_imc1Head.len*8 ;
        l_pData->m_nHei = l_imc1Head.hei*8 ;
        l_pData->m_pBitmap = 
			Ima2Bitmap( (char*)l_pIMA, l_imc1Head.len, l_imc1Head.hei);

        free (l_pIMC1);
        free (l_pIMA);

        this->Add(l_pData);

        return TRUE;    
 
   }

   p_strFilename.MakeLower( );
   if (p_strFilename.Find(".ima")!=-1)
   {

       USER_IMAHEADER l_imaHead;
       file.Seek( CFile::begin , 0 );
       file.Read( &l_imaHead, 2);
        
       char * l_pIMA = (char *) malloc(l_imaHead.len * l_imaHead.hei * 64);
       file.Read(l_pIMA, l_imaHead.len * l_imaHead.hei * 64);
  
       CSS3Frame *l_pData = new CSS3Frame;
       l_pData->m_nLen = l_imaHead.len*8  ;
       l_pData->m_nHei = l_imaHead.hei*8  ;
       l_pData->m_pBitmap = Ima2Bitmap(l_pIMA, l_imaHead.len, l_imaHead.hei);

       if (bClose)
	       file.Close();
             
       free (l_pIMA);

       this->Add(l_pData);
       return TRUE;
    
   }
    
   
#ifdef _DEBUG
	afxDump << "Cannot recognize the file format \n";
#endif

    if (bClose)
	    file.Close();
    
    return 0;
}

void COBL3Filter::InsertAt(int n, CSS3Frame *pFrame) {
	int i;

	if (n== m_nSize)
	{
		Add (pFrame);
	}
	else
	{
		if (m_nSize== m_nMax)		{
			Add (NULL); 
		}
		else {
			m_nSize++;
		}

		for (i=m_nSize -1; i > n ; i--)
		{
			m_arrFrames [i] = m_arrFrames [i-1];
		}

		m_arrFrames [n]= pFrame;
	}
	
	return ;
}

void COBL3Filter::RemoveAt(int n) {
	int i;

	if (n == m_nSize-1)	{
		m_nSize--;
	}
	else
	{
		for (i=n; i<m_nSize-1; i++)
		{
			m_arrFrames[i] = m_arrFrames[i+1];
		}
		
		m_nSize--;
	}

	m_arrFrames[m_nSize] = NULL; 

	return ;
}

CSS3Frame * COBL3Filter::Current()
{
	if (GetSize()==0) return NULL;
	return (CSS3Frame * ) m_arrFrames[m_nCurrFrame];
}

CString & COBL3Filter::GetName ()
{
	return CString(m_szName);
}


void COBL3Filter::SetName (CString & str)
{
	 strcpy(m_szName, str.GetBuffer(1));
}

void COBL3Filter::SetFilename (CString & str)
{
	 strcpy(m_szFilename, str.GetBuffer(1));
}

void COBL3Filter::RemoveAll ()
{
	int n;
	for (n=0; n<m_nSize; n++)
	{
		m_arrFrames[n] = NULL;
	}

	m_nSize=0;
}	

BOOL COBL3Filter::PackImages ()
{

	int nRelIndex=0;
	int nTotalSize =0;
	int nUsedMem =0;
	int i;

	if (m_pPackedBits!=NULL) {
		free (m_pPackedBits);
		m_pPackedBits=NULL;
	}
	
	m_bPacked = TRUE;

	for (i=0; i<m_nSize; i++)
	{
		CSS3Frame & frame = * m_arrFrames [i];
		nTotalSize = 
			nTotalSize + frame.m_nLen * frame.m_nHei;

		if ((frame.m_nLen * frame.m_nHei) %4096)
		{
			nUsedMem = nUsedMem 
				+ frame.m_nLen * frame.m_nHei -
				((frame.m_nLen * frame.m_nHei) %4096)
				+ 4096;
		}
		else
		{
			nUsedMem = nUsedMem 
				+ frame.m_nLen * frame.m_nHei;
		}

	}

	m_pPackedBits = (UCHAR*) malloc (nTotalSize);
	m_pFrameData = (CSS3Frame*)malloc (m_nSize* sizeof(CSS3Frame));
	ZeroMemory(m_pFrameData, m_nSize* sizeof(CSS3Frame));

	for (i=0; i<m_nSize; i++)
	{
		memcpy (m_pPackedBits + nRelIndex, 
			m_arrFrames[i]->m_pBitmap,
				m_arrFrames[i]->m_nLen * 
					m_arrFrames[i]->m_nHei);

		if (!m_arrFrames[i]->IsPacked())
		{
			CSS3Frame *pOld = m_arrFrames[i];
			m_pFrameData[i].m_nLen = 
				m_arrFrames[i]->m_nLen ;
			m_pFrameData[i].m_nHei = 
				m_arrFrames[i]->m_nHei ;
			m_pFrameData[i].m_pMap =
				NULL ;

			m_arrFrames[i] = &m_pFrameData[i];

			free (pOld->m_pBitmap);
			pOld->m_pBitmap=NULL;
			delete pOld;
		}

		m_arrFrames[i]->SetPacked();
		m_arrFrames[i]->m_pBitmap = 
			(char*)m_pPackedBits + nRelIndex;
		
		nRelIndex = nRelIndex 
				+ m_arrFrames[i]->m_nLen 
					* m_arrFrames[i]->m_nHei;
	}

	return TRUE;
}

int COBL3Filter::GetByteSize()
{
    int i;
    int nTotalSize=0;
	for (i=0; i<m_nSize; i++)
	{
		CSS3Frame & frame = * m_arrFrames [i];
		nTotalSize = 
			nTotalSize + frame.m_nLen * frame.m_nHei;
    }

    return nTotalSize;
}
