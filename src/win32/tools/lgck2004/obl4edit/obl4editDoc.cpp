// obl4editDoc.cpp : implementation of the CObl4editDoc class
//

#include "stdafx.h"
#include "obl4edit.h"
#include "obl4editDoc.h"
#include "Mainfrm.h"
#include "BmpWrap.h"
#include "Draw.h"
#include "DlgImportBmp.h"
#include "DlgExportBmp.h"
#include "DlgImportOBL.h"
#include "DlgSplitExport.h"
#include "SortArray.h"
#include "PalData.h"
#include <io.h>
#include "DlgExportPal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern USER_WINPAL MSDOS_PAL[];
extern CPalData g_pal;

/////////////////////////////////////////////////////////////////////////////
// CObl4editDoc

IMPLEMENT_DYNCREATE(CObl4editDoc, CDocument)

BEGIN_MESSAGE_MAP(CObl4editDoc, CDocument)
	//{{AFX_MSG_MAP(CObl4editDoc)
	ON_COMMAND(IDM_SPLIT_FRAMESET, OnSplitFrameset)
	ON_UPDATE_COMMAND_UI(IDM_SPLIT_FRAMESET, OnUpdateSplitFrameset)
	ON_COMMAND(IDM_IMPORTWINDOWBITMAP, OnImportwindowbitmap)
	ON_UPDATE_COMMAND_UI(IDM_IMPORTWINDOWBITMAP, OnUpdateImportwindowbitmap)
	ON_COMMAND(IDM_IMPORTGAMEMAKER, OnImportgamemaker)
	ON_UPDATE_COMMAND_UI(IDM_IMPORTGAMEMAKER, OnUpdateImportgamemaker)
	ON_COMMAND(IDM_SAVEPALETTE, OnSavepalette)
	ON_UPDATE_COMMAND_UI(IDM_SAVEPALETTE, OnUpdateSavepalette)
	ON_COMMAND(IDM_LOADPALETTE, OnLoadpalette)
	ON_UPDATE_COMMAND_UI(IDM_LOADPALETTE, OnUpdateLoadpalette)
	ON_COMMAND(IDM_EXPORTBMP, OnExportbmp)
	ON_UPDATE_COMMAND_UI(IDM_EXPORTBMP, OnUpdateExportbmp)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
	ON_COMMAND(IDM_IMPORTOBL, OnImportobl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObl4editDoc construction/destruction

CObl4editDoc::CObl4editDoc()
{
	CWinApp *pApp = AfxGetApp();

	// TODO: add one-time construction code here
}

CObl4editDoc::~CObl4editDoc()
{
	CWinApp *pApp = AfxGetApp();
}


BOOL CObl4editDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	//int m_nMY;
	//int m_nMX;

	m_oblData.Forget();
	m_oblData.m_nCurrFrame =0;

    ResetViewPort();

	UpdateAllViews(NULL);
	RepaintAllViews();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CObl4editDoc serialization

void CObl4editDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		m_oblData.Serialize(ar);
		// TODO: add storing code here
	}
	else
	{
		m_oblData.Serialize(ar);
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CObl4editDoc diagnostics

#ifdef _DEBUG
void CObl4editDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CObl4editDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CObl4editDoc commands

BOOL CObl4editDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	m_oblData.m_nCurrFrame =0;

    ResetViewPort();

	UpdateAllViews(NULL);
	RepaintAllViews();
	return TRUE;
}

void CObl4editDoc::RepaintAllViews()
{
   POSITION pos = GetFirstViewPosition();
   while (pos != NULL)
   {
      CView* pView = GetNextView(pos);
      pView->Invalidate();
   }   

}

void CObl4editDoc::SetModified()
{
	CObl4editDoc *pDoc = this;
	CWinApp *pApp = AfxGetApp();
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd(); 

	if (pDoc->IsModified()==FALSE )	{

		pDoc->SetModifiedFlag (TRUE);

		UpdateTitle();	

	}

}

void CObl4editDoc::UpdateTitle ()
{
	CObl4editDoc *pDoc = this;
	CWinApp *pApp = AfxGetApp();
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd(); 

	char szTitle [1024];

	if (pDoc->IsModified() )	{
		wsprintf (szTitle, "%s* - %s [%d / %d]",
			pDoc ->GetTitle(),
			pApp->m_pszAppName,
			min ( m_oblData. m_nCurrFrame+1,m_oblData.GetSize()),
			m_oblData.GetSize()	);
	}
	else
	{
		wsprintf (szTitle, "%s - %s [%d / %d]",
			pDoc ->GetTitle(),
			pApp->m_pszAppName,
			min ( m_oblData. m_nCurrFrame+1,m_oblData.GetSize()),
			m_oblData.GetSize()	);
	}

	CString str = szTitle;

	pMainFrame->SetWindowText(str);

}

BOOL CObl4editDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	int iStatus = CDocument::OnSaveDocument(lpszPathName);
	return iStatus;

}

void CObl4editDoc::OnSplitFrameset() 
{
	// TODO: Add your command handler code here
	if (m_oblData.Current()==NULL)
		return;
	
	CDlgSplitExport dlg;
	dlg.m_pDoc = this;
	if (dlg.DoModal()==IDOK) {
			
		COBL3Filter filter;
		CString str = dlg.m_strFilename;
		int i = str.Find (".obl");
		if (i!=-1)
			str.SetAt(i, 0) ;


		if (dlg.m_bSplit== 0)
		{
			i=0;
			int n=0;
			int x=0;
			while (n<m_oblData.GetSize())
			{

				CString strFilename;
				strFilename.Format
					("%s_split%d.obl", str, i+1);

				for (x=0; x<dlg.m_nSize+1
					&& n<m_oblData.GetSize(); x++, n++) {
					filter.Add (m_oblData[n]);
				}

				CFile file;
				CFileException e;

				if (!file.Open(strFilename, CFile::modeWrite|
					CFile::modeCreate 
					| CFile::typeBinary, &e ))
				{
#ifdef _DEBUG
					afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
					filter.RemoveAll();
					AfxMessageBox ("Write error occured!", MB_ICONEXCLAMATION |
						MB_OK);
					return ;
				}

				filter.Write(file);
				filter.RemoveAll();
				file.Close();

				i++;
			}
		
		}
		else
		{
			CString strFilename = str + "_subset.obl";

			int n;
			for (n=dlg.m_nFrom; n<=dlg.m_nTo; n++)
			{

				filter.Add (m_oblData[n]);
			}

			CFile file;
			CFileException e;

			if (!file.Open(strFilename, CFile::modeWrite|
				CFile::modeCreate 
				| CFile::typeBinary, &e ))
			{
#ifdef _DEBUG
				afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
				filter.RemoveAll();
				AfxMessageBox ("Write error occured!", MB_ICONEXCLAMATION |
						MB_OK);
				return ;
			}

			filter.Write(file);
			filter.RemoveAll();
			file.Close();

		}
	}
}

void CObl4editDoc::OnUpdateSplitFrameset(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = this;
	pCmdUI->Enable (pDoc->m_oblData.Current()!=NULL);
}

void CObl4editDoc::SetTitle(LPCTSTR lpszTitle) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::SetTitle(lpszTitle);
}

void CObl4editDoc::OnImportwindowbitmap() 
{
	// TODO: Add your command handler code here
	CDlgImportBmp dlg;
	CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();
	dlg.m_nBpp = pMainFrame->m_nBpp;
	dlg.m_nMethod = 0;
    
    int iStatus = dlg.DoModal(); 
    if (iStatus==IDOK)
    {
		char sz[26];
		wsprintf(sz, "Method %d %d\n", dlg.m_nMethod, dlg.m_nBpp);
		OutputDebugString (sz);

		if (!ImportBitmap (m_oblData, 
			dlg.m_strFilename, dlg.m_nMethod))
		{
			AfxMessageBox("Import bitmap failed - \neither an incompatible format/missing file \nor an internal error!");
		}
		else
		{
			RepaintAllViews();
			SetModified();
		}
    }			
}

void CObl4editDoc::OnUpdateImportwindowbitmap(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

BOOL CObl4editDoc::ImportBitmap (COBL3Filter & filter, CString & strFilename, int nMethod)
{

    CMainFrame *pMainFrame = (CMainFrame*) AfxGetMainWnd();

	HBITMAP             hbm;

	hbm = (HBITMAP)LoadImage(NULL, strFilename, 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    if (hbm == NULL) {
		OutputDebugString ("IMPORTBITMAP: Cannot load bitmap\n");
		return NULL;
	}

	BeginWaitCursor();
	CSS3Frame *pFrame = BitmapToOBL4 (hbm, nMethod);
	EndWaitCursor();

	if (pFrame) 
		filter.Add(pFrame);
	
    DeleteObject(hbm);

	return (pFrame!=NULL);
}

HRESULT CObl4editDoc::CopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy)
{
    HDC                 hdcImage;
    HDC                 hdc;
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    HRESULT             hr;

    if (hbm == NULL || pdds == NULL)
	return E_FAIL;

    // make sure this surface is restored.
    pdds->Restore();

    //  select bitmap into a memoryDC so we can use it.
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
	OutputDebugString("createcompatible dc failed\n");
    SelectObject(hdcImage, hbm);

    // get size of the bitmap
    GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap
    dx = dx == 0 ? bm.bmWidth  : dx;    // use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;

    // get size of surface.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
		BitBlt (hdc, 0,0,ddsd.dwWidth, ddsd.dwHeight,hdcImage, 0,0,SRCCOPY);
		pdds->ReleaseDC(hdc);
    }

    DeleteDC(hdcImage);

    return hr;
}

void CObl4editDoc::OnImportgamemaker() 
{
	// TODO: Add your command handler code here
    CString l_strFilesFilter =
        "Game Maker 3.0 (*.mbl;*.cbl;*.bbl)|*.mbl;*.cbl;*.bbl|"\
        "Background blocks (*.bbl)|*.bbl|"\
        "Character blocks (*.cbl)|*.cbl|"\
        "Monster blocks (*.mbl)|*.mbl|"\
        "|";

    CFileDialog l_Dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    l_Dlg.m_ofn.lpstrTitle = "Import Block Sets"; 
    
    int iStatus = l_Dlg.DoModal(); 
    if (iStatus==IDOK)
    {
		CString strFilename= l_Dlg.GetPathName();
		if (!ImportGM (m_oblData, strFilename))
		{
			AfxMessageBox("Import failed - \neither an incompatible format/missing file \nor an internal error!");
		}
		else
		{
			RepaintAllViews();
			SetModified();
		}
    }			
}

void CObl4editDoc::OnUpdateImportgamemaker(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

BOOL CObl4editDoc::ImportGM (COBL3Filter & filter, CString & Filename)
{

	CFile file;
	CFileException e;

	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	USER_WINPAL pal[256];
	USER_WINPAL GMpal[256];
	UCHAR arrIndex[256];
				   
	memcpy (pal, g_pal.GetWinPal(), 256*3);
	memcpy (GMpal, g_pal.GetWinPal(), 256*3);

	UINT x;
	UINT y;
	UINT diff;
	UINT _diff;
	UCHAR nColor;

	for (y=0; y<256; y++)
	{
		if (pal[y].red)
			pal[y].red = g_pal.GammaCorrection(pal[y].red);

		if (pal[y].green)
			pal[y].green = g_pal.GammaCorrection(pal[y].green);

		if (pal[y].blue)
			pal[y].blue = g_pal.GammaCorrection(pal[y].blue);
	}

	for (y=0; y<256; y++)
	{
		_diff = 0xffffff;
		nColor =0x10;

		if (GMpal[y].red)
			GMpal[y].red = g_pal.GammaCorrection(GMpal[y].red);

		if (GMpal[y].green)
			GMpal[y].green = g_pal.GammaCorrection(GMpal[y].green);

		if (GMpal[y].blue)
			GMpal[y].blue = g_pal.GammaCorrection(GMpal[y].blue);

		for (x=16; x<=223; x++)
		{
			diff =	(
				(GMpal[y].red - pal[x].red) *
				(GMpal[y].red - pal[x].red) +
					
				(GMpal[y].green - pal[x].green) *
				(GMpal[y].green - pal[x].green) +
					
				(GMpal[y].blue - pal[x].blue) *
				(GMpal[y].blue - pal[x].blue)
				
				);

			if (diff < _diff)
			{
				nColor = x;
				_diff= diff;
			}
		}		

		arrIndex[y] = nColor;
	}
	

	if (!file.Open(Filename, CFile::modeRead
				| CFile::typeBinary, &e ))
	{
		OutputDebugString("IMPORTGM: Cannot read GM blocks set\n");
		return FALSE;
	}

	UINT nLen =	file.GetLength();			
	char temp[420];
	int i;

	for (x=0; (x*420) < nLen; x++)
	{
		file.Read (temp, 420);
		CSS3Frame *pFrame = new CSS3Frame (20,20);

		for (y=0; y<400; y++)
		{
			i = temp[y];
			if (i==0xff)
				temp[y] =0;

			if (i >=0xe0 ) 
				temp[y] = arrIndex[i];
			else
				temp[y] = i + 0x10;

		}

		memcpy (pFrame->m_pBitmap, temp, 400);
		pFrame->Enlarge2x();
		filter.Add (pFrame);
		file.Close;
	}

  	return TRUE;
}

void CObl4editDoc::OnSavepalette() 
{
	// TODO: Add your command handler code here
	CDlgExportPal dlg;
	dlg.m_nFormat = PAL_MSDOS;
	if (dlg.DoModal()==IDOK)
	{
		CFile file;
		if (file.Open(dlg.m_strName, CFile::modeWrite   |
				CFile::modeCreate | CFile::typeBinary, NULL ))
		{
			g_pal.Export(file, dlg.m_nFormat);
			file.Close();
		}
		else
		{
			AfxMessageBox("Cannot create palette");
		}
	}
}

void CObl4editDoc::OnUpdateSavepalette(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CObl4editDoc::OnLoadpalette() 
{
	// TODO: Add your command handler code here

	CString l_strFilesFilter =
        "RGB Palette (*.pal)|*.pal|"\
        "|";

    CFileDialog l_Dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
            l_strFilesFilter,  AfxGetMainWnd() ) ;

    l_Dlg.m_ofn.lpstrTitle = "Loading palette"; 
    
    int iStatus = l_Dlg.DoModal(); 
    if (iStatus!=IDOK)
		return;
    
	CString strFilename= l_Dlg.GetPathName();
	
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();

	CFile file;
	CFileException e;
	if (!file.Open(strFilename, CFile::modeRead   
				| CFile::typeBinary, &e ))
	{
		AfxMessageBox("Cannot load palette!");
		OutputDebugString("LOADPALETTE: Cannot create palette\n");
		return ;
	}

	//file.Read(MSDOS_PAL, 256*3);
	if (!g_pal.Import(file))
	{
		AfxMessageBox("Unsupported format");
	}
	file.Close();

	pMainFrame->NewPalette();

}

void CObl4editDoc::OnUpdateLoadpalette(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CObl4editDoc::OnExportbmp() 
{
	// TODO: Add your command handler code here

	CMainFrame* pMainFrame = 
		(CMainFrame*) AfxGetMainWnd();

	CDlgExportBmp dlg;
	dlg.m_pDoc = this;
	if (dlg.DoModal()!=IDOK)
		return;
	CObl4editDoc *pDoc = this;	

	int x;
	int y;
	UCHAR nColor;

	int nFirst;
	int nLast;

	if (dlg.m_bAll==0) // First Radio Button (ndx=0)
	{
		nFirst = 0;
		nLast = pDoc->m_oblData.GetSize();
	}
	else
	{
		nFirst = dlg.m_nFrom;
		nLast = dlg.m_nTo+1;
	}

	CBmpWrap bmpWrap;

	CString str = dlg.m_strFilename;
	int i = str.Find (".bmp");
	if (i!=-1)
		str.SetAt(i, 0) ;

	CString strFilename;
	UCHAR * pDest;
	UCHAR * pSrc;

	USER_WINPAL *pal = g_pal.GetWinPal();

	for (i=nFirst; i<nLast; i++)
	{
		CSS3Frame & frame = * pDoc->m_oblData[i]; 
		bmpWrap.Size(frame.m_nLen, frame.m_nHei);
		for (y=0; y<frame.m_nHei; y++)
		{
			for (x=0; x<frame.m_nLen; x++)
			{
				nColor = *frame.Point(x,y);
				pDest = (UCHAR *) bmpWrap.Point(x,y);
				pSrc = (UCHAR*) &pal[nColor-0x10];

				// blue green red --> pDest 0,1,2

				*(pDest) = g_pal.GammaCorrection(*(pSrc+2));
				*(pDest+1) = g_pal.GammaCorrection(*(pSrc+1));
				*(pDest+2) = g_pal.GammaCorrection(*(pSrc+0));
			}
		}

		bmpWrap.FlipUpDown();
		strFilename.Format
			("%s_s_%d.bmp", str, i+1);
		bmpWrap.Write(strFilename);		
		bmpWrap.Forget();
	}
}

void CObl4editDoc::OnUpdateExportbmp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CObl4editDoc *pDoc = this;
	pCmdUI->Enable (pDoc->m_oblData.Current()!=NULL);
	
}

void CObl4editDoc::OnFileSendMail() 
{
	// TODO: Add your command handler code here
	CDocument::OnFileSendMail() ;
}

void CObl4editDoc::OnUpdateFileSendMail(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

}

CSS3Frame * CObl4editDoc::BitmapToOBL4(HBITMAP hbm, int nMethod)
{
    CMainFrame * pMainFrame = (CMainFrame*) AfxGetMainWnd();
	LPDIRECTDRAW & pdd = pMainFrame->m_lpDD;

    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    IDirectDrawSurface *pdds;

	COLORREF rgb;
	int i,x,y;
	DWORD diff;
	DWORD _diff;
	UCHAR nColor;

	GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap

    // create a DirectDrawSurface for this bitmap
	int nLen = bm.bmWidth;
	if (nLen%8) 
		nLen = nLen + (8 - bm.bmWidth % 8);

	int nHei = bm.bmHeight;
	if (nHei%8)
		nHei = nHei + (8 -  bm.bmHeight % 8);

	ZeroMemory(&ddsd, sizeof(ddsd));
  
	ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY ;
    ddsd.dwWidth = nLen;
    ddsd.dwHeight = nHei;

	char sz[128];
	wsprintf(sz, "Importing - 0%%");
	pMainFrame->SetWindowText(sz);

    if (pdd->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
	{
		OutputDebugString("IMPORTBITMAP: Cannot Create Surface");
		return NULL;
	}

    CopyBitmap(pdds, hbm, 0, 0, 0, 0);

	CSS3Frame * pFrame = new CSS3Frame (nLen, nHei);
	if (pFrame==NULL) return FALSE;

	HDC hdc;

	// Safety check, GDI color convert only works 
	// in 256-color mode
	if (pMainFrame->m_nBpp!=8 && nMethod==2)
	{
		nMethod =1;
	}

    if ((nMethod!=2) && (pdds->GetDC(&hdc) != DD_OK))
    {
		OutputDebugString("IMPORTBITMAP: GetDC() failed\n");
		return FALSE;
    }
	
	USER_WINPAL * pal = g_pal.GetWinPal();

 if (nMethod!=2)
 {
	BYTE *pColorTable = (BYTE*) malloc(64*64*64);
	memset(pColorTable, -1, 64*64*64);

	for (y=0; y< nHei; y++)
	{
		wsprintf(sz, "Importing - %d%%", 100*y/nHei);
		pMainFrame->SetWindowText(sz);
		for (x=0; x<nLen; x++)
		{
			rgb = GetPixel (hdc, x, y);

			BYTE nRed	= GetRValue(rgb);
			BYTE nGreen = GetGValue(rgb);
			BYTE nBlue	= GetBValue(rgb);

			int nIndex = (nRed / 4) +
				64 * (nGreen / 4) +
				64 * 64 * (nBlue / 4);

			if (pColorTable[nIndex]==0xff)
			{
				_diff = 256*256*3;
				for (i=16; i<=223; i++)
				{
					if (nMethod==0)
					{
						diff =	(nRed - g_pal.GammaCorrection(pal[i-0x10].red)) *
							(nRed - g_pal.GammaCorrection(pal[i-0x10].red)) +
					
							(nGreen - g_pal.GammaCorrection(pal[i-0x10].green)) *
							(nGreen - g_pal.GammaCorrection(pal[i-0x10].green)) +
					
							(nBlue - g_pal.GammaCorrection(pal[i-0x10].blue)) *
							(nBlue - g_pal.GammaCorrection(pal[i-0x10].blue));
					}

					if (nMethod==1)
					{
						diff =	(nRed - 4*pal[i-0x10].red) *
							(nRed - 4*pal[i-0x10].red) +
					
							(nGreen - 4*pal[i-0x10].green) *
							(nGreen - 4*pal[i-0x10].green) +
					
							(nBlue - 4*pal[i-0x10].blue) *
							(nBlue - 4*pal[i-0x10].blue);
					}		

					if (diff <= _diff)
					{
						nColor = i;
						_diff= diff;
					}
				}		

				pColorTable[nIndex] = nColor;
			}
			else
			{
				nColor = pColorTable[nIndex];
			}

			* (pFrame->Point(x,y)) = nColor;
		}
	}

	free(pColorTable);
 
 }
 else // Let the GDI do the work... he he he
	{
		UCHAR arrIndex[256];
		CClientDC dc(pMainFrame);

	    PALETTEENTRY ape[256];

		if (GetSystemPaletteEntries(dc.m_hDC, 0, 0x0f, &ape[0])==0)
		{   
			OutputDebugString("FATAL: GetSystemPaletteEntries() failed.\n");   
			return FALSE;
		}

		if (GetSystemPaletteEntries(dc.m_hDC, 0xf0,0xff, &ape[0xf0])==0)
		{   
			OutputDebugString("FATAL: GetSystemPaletteEntries() failed.\n");   
			return FALSE;
		}

		for (y=0; y<256; y++)
		{
			_diff = 0xffffff;
			nColor =0x10;

			for (i=16; i<=223; i++)
			{
				diff =	
					(ape[y].peRed - pal[i-0x10].red) *
						(ape[y].peRed - pal[i-0x10].red) +
					
					(ape[y].peGreen - pal[i-0x10].green) *
						(ape[y].peGreen - pal[i-0x10].green) +
					
					(ape[y].peBlue - pal[i-0x10].blue) *
						(ape[y].peBlue - pal[i-0x10].blue);
				

				if (diff < _diff)
				{
					nColor = i;
					_diff= diff;
				}
			}

			arrIndex[y] = nColor;	
		}		

		if (pdds == NULL || pdds->
			Lock(NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL) !=DD_OK)
		{
			OutputDebugString("IMPORTBITMAP: Lock failed!\n");
			return FALSE;
		}

		UCHAR *pDest = (UCHAR*) ddsd.lpSurface;
		int nPitch = ddsd.lPitch;

		for (y=0; y<nHei; y++)
		{
			wsprintf(sz, "Importing - %d%%", 100*y/nHei);
			for (x=0; x<nLen; x++)
			{
				nColor = * (pDest+x + y * nPitch);
			
				if ((nColor<0x10) || (nColor>=0xf0))
				{
					nColor = arrIndex[nColor];
				}
				
				* (pFrame->Point(x,y)) = nColor;
			}
		}

		if ((nMethod==2) && (pdds->Unlock(NULL)))
		{
			OutputDebugString("IMPORTBITMAP: Unlock failed!\n");
			return FALSE;
		}	
	}

	if (nMethod!=2)
		pdds->ReleaseDC(hdc);

	pdds->Release();

	return pFrame;
}

void CObl4editDoc::OnImportobl() 
{
	// TODO: Add your command handler code here
	CDlgImportOBL dlg;
	dlg.m_bAppend=0;
	if (dlg.DoModal()==IDOK)
	{
		
		CSortArray arrayFiles;
		_finddata_t data;
		int handle;
		
		handle = _findfirst( dlg.m_strFilename.GetBuffer(1),
			&data);

		if (handle!=-1)
		{
			arrayFiles.Add(data.name);

			while (_findnext (handle, &data)!=-1)
			{
				arrayFiles.Add(data.name);
			} // while

			_findclose( handle );

		} // if

		int n;
		int nCurrImage;
		if (dlg.m_bAppend==0)
			nCurrImage = m_oblData.GetSize();
		else
			nCurrImage = m_oblData.m_nCurrFrame;

		for (n=0; n<arrayFiles.GetSize(); n++)
		{
			memcpy (data.name, arrayFiles[n]->GetBuffer(1),
				arrayFiles[n]->GetLength()+1);

			AddSet(data.name, nCurrImage);		
		}
	}
}

BOOL CObl4editDoc::AddSet(char *szFilename, int & nCurrImage)
{
	COBL3Filter filter;
	filter.Extract(szFilename);

	int i;
	for (i=0; i<filter.GetSize(); i++)
	{
		SetModifiedFlag(TRUE);
		m_oblData.InsertAt(nCurrImage, filter[i]);
		nCurrImage++;
	}

	filter.RemoveAll();
	filter.Forget();

	return TRUE;
}

CWnd * CObl4editDoc::GetView()
{
    POSITION pos = GetFirstViewPosition();
    if (pos != NULL)
    {
        return GetNextView(pos);
    }   
    else
    {
        return NULL;
    }
}

void CObl4editDoc::ResetViewPort()
{
    CWnd * pWnd = GetView();
    if (pWnd)
    {
        pWnd->SendMessage(RESET_VIEW_ORG, 0, 0);
    }
}
