// OBL3Filter.cpp : implementation file
//

#include "stdafx.h"
#include "OBL3Filter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COBL3Filter

IMPLEMENT_DYNCREATE(COBL3Filter, CObject)

COBL3Filter::COBL3Filter()
{
    m_arrFrames.SetSize(0,10);
}


COBL3Filter::~COBL3Filter()
{
}


//BEGIN_MESSAGE_MAP(COBL3Filter, CObject)
	//{{AFX_MSG_MAP(COBL3Filter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBL3Filter diagnostics

#ifdef _DEBUG
void COBL3Filter::AssertValid() const
{
	CObject::AssertValid();
}

void COBL3Filter::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COBL3Filter serialization

void COBL3Filter::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
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

    char l_szId[5]; 
    ::ZeroMemory(l_szId,5);
    int l_nCpt;

    file.Read(l_szId,4);
    CString l_strId = l_szId;

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
        file.Close();

        return TRUE;
 
   }


   if (l_strId=="IMC1")
   {

#ifdef _DEBUG
       afxDump << "Loading an IMC1 file\n";
#endif
        USER_IMC1HEADER l_imc1Head;

        file.Seek( CFile::begin , 0 );
        file.Read(&l_imc1Head, 6);
        file.Read(&l_imc1Head.SizeData, 4);

        UCHAR *l_pIMC1 = (UCHAR *)malloc (l_imc1Head.SizeData);
        file.Read(l_pIMC1, l_imc1Head.SizeData);

        UCHAR *l_pIMA = (UCHAR *) malloc (1+l_imc1Head.len * l_imc1Head.hei * 64);
        ::ZeroMemory(l_pIMA,l_imc1Head.len * l_imc1Head.hei * 64);

        file.Close();

        int loop;
        int cpt;
        UCHAR car;
        UCHAR *ptr = l_pIMA;
        UCHAR *ptrIMC1 = l_pIMC1;

        int safetycpt =0;

        for (cpt=0; (cpt< (l_imc1Head.SizeData-1)) ;)
        {

            if (safetycpt>= (l_imc1Head.len * l_imc1Head.hei * 64))
            {    
#ifdef _DEBUG
       afxDump << "Zing...\n";
#endif
            break;
            }

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
        l_pData->m_pBitmap = (CHAR*)
            Ima2Bitmap((CHAR*)l_pIMA, l_imc1Head.len, l_imc1Head.hei);

        free (l_pIMC1);
        free (l_pIMA);

        this->Add(l_pData);

#ifdef _DEBUG
        afxDump << safetycpt << " !=" << (l_imc1Head.len * l_imc1Head.hei * 64);
        afxDump << "IMC1 file loaded succesfully\n";
#endif
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

       file.Close();
             
       free (l_pIMA);

       this->Add(l_pData);
       return TRUE;
    
   }
    
   
#ifdef _DEBUG
	afxDump << "Cannot recognize the file format \n";
#endif

    file.Close();
    
    return 0;


}

int COBL3Filter::Add (CSS3Frame *p_pFrame)
{
    return m_arrFrames.Add( (CObject*)p_pFrame);

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
                    *(dest + x*8+x2+(y*8+y2)*len*8) = 16+
                        *(ImaData+(x+y*len)*64+x2+y2*8);
                    
                }
            }

        }
    }
    


    return dest;

}

