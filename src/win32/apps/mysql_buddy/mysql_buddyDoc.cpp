// mysql_buddyDoc.cpp : implementation of the CMysql_buddyDoc class
//

#include "stdafx.h"
#include "mysql_buddy.h"
#include "mysql_buddyDoc.h"
#include "field.h"
#include "table.h"
#include "SQLMother.h"
#include "wndtable.h"

#include "dlgtable.h"
#include "dlgdatabase.h"
#include "dlgconfig.h"
#include "dlgnewthing.h"
#include "dlgdescription.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyDoc
IMPLEMENT_DYNCREATE(CMysql_buddyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMysql_buddyDoc, CDocument)
	//{{AFX_MSG_MAP(CMysql_buddyDoc)
	ON_COMMAND(IDM_TABLES, OnTables)
	ON_UPDATE_COMMAND_UI(IDM_TABLES, OnUpdateTables)
	ON_COMMAND(IDM_EXPORTSQL, OnExportsql)
	ON_UPDATE_COMMAND_UI(IDM_EXPORTSQL, OnUpdateExportsql)
	ON_COMMAND(IDM_SERVER, OnServer)
	ON_UPDATE_COMMAND_UI(IDM_SERVER, OnUpdateServer)
	ON_COMMAND(IDM_TEST, OnTest)
	ON_UPDATE_COMMAND_UI(IDM_TEST, OnUpdateTest)
	ON_COMMAND(IDM_DATABASE, OnDatabase)
	ON_UPDATE_COMMAND_UI(IDM_DATABASE, OnUpdateDatabase)
	ON_COMMAND(IDM_TABLEDELETE, OnTabledelete)
	ON_UPDATE_COMMAND_UI(IDM_TABLEDELETE, OnUpdateTabledelete)
	ON_COMMAND(IDM_TABLEEDIT, OnTableedit)
	ON_UPDATE_COMMAND_UI(IDM_TABLEEDIT, OnUpdateTableedit)
	ON_COMMAND(IDM_TABLERENAME, OnTablerename)
	ON_UPDATE_COMMAND_UI(IDM_TABLERENAME, OnUpdateTablerename)
	ON_COMMAND(IDM_WRITE_DROP_CODE, OnWriteDropCode)
	ON_UPDATE_COMMAND_UI(IDM_WRITE_DROP_CODE, OnUpdateWriteDropCode)
	ON_COMMAND(IDM_WRITE_TECHDOC, OnWriteTechdoc)
	ON_UPDATE_COMMAND_UI(IDM_WRITE_TECHDOC, OnUpdateWriteTechdoc)
	ON_COMMAND(IDM_SET_TABLE_DESCRIPTION, OnSetTableDescription)
	ON_UPDATE_COMMAND_UI(IDM_SET_TABLE_DESCRIPTION, OnUpdateSetTableDescription)
	ON_COMMAND(IDM_IMPORTSQL, OnImportsql)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
	ON_UPDATE_COMMAND_UI(IDM_IMPORTSQL, OnUpdateImportsql)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyDoc construction/destruction

CMysql_buddyDoc::CMysql_buddyDoc()
{
	// TODO: add one-time construction code here
}

CMysql_buddyDoc::~CMysql_buddyDoc()
{
	m_mother.Forget();
}

BOOL CMysql_buddyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_mother.Forget();
	m_mother.Init();
	m_mother.AddDefault();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyDoc serialization

void CMysql_buddyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		m_mother.Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		m_mother.Serialize(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyDoc diagnostics

#ifdef _DEBUG
void CMysql_buddyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMysql_buddyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMysql_buddyDoc commands

void CMysql_buddyDoc::OnTables() 
{
	// TODO: Add your command handler code here

	CDlgTable dlg(&m_mother, (CDocument*)this);
	if (dlg.DoModal()==IDOK)
	{
	}

	m_mother.SetMainWnd(GetView());
	m_mother.NotifyTables(WM_UTABLEREPOPULATE, 0);
	m_mother.UpdateVisual();
}

void CMysql_buddyDoc::OnUpdateTables(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

BOOL CMysql_buddyDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	m_mother.SetMainWnd(GetView());
	m_mother.CreateVisual();

	return TRUE;
}

BOOL CMysql_buddyDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocument::OnSaveDocument(lpszPathName);
}

void CMysql_buddyDoc::OnExportsql() 
{
	// TODO: Add your command handler code here
    CString strFilesFilter =
        "SQL files |*.sql"\
        "|";

	CFileDialog dlg( FALSE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Export declarations"; 
	dlg.m_ofn.lpstrDefExt = ".sql";
    
    if (dlg.DoModal()==IDOK)  {

		CString strFilename = dlg.GetFileName();
		CFile file;
		if (file.Open(strFilename, 	CFile::modeCreate| CFile::modeWrite
			| CFile::typeBinary ))
		{
			for (int i=0; i< m_mother.GetSize(); i++)
			{
				CString str;				

				m_mother[i]->ProcessSQL(str);
				str=str + "\r\n";
				str = CString("#\r\n# Table structure for table '") 
					+ m_mother[i]->m_szName + "'\r\n#\r\n\r\n" 
					+ str + "\r\n";
				char *p = str.GetBuffer(1);
				file.Write(p, strlen(p));
			}

			file.Close();
		}
	}			
}

void CMysql_buddyDoc::OnUpdateExportsql(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here


}

void CMysql_buddyDoc::OnServer() 
{
	// TODO: Add your command handler code here

	CServerArr & config = m_mother.m_config;

	CDlgConfig dlg(&config, this);
	if (dlg.DoModal()==IDOK)
	{
	}
}

void CMysql_buddyDoc::OnUpdateServer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

CMainFrame * CMysql_buddyDoc::GetFrame()
{
	return (CMainFrame*) (AfxGetMainWnd());
}

void CMysql_buddyDoc::OnTest() 
{
	// TODO: Add your command handler code here
	GetView()->SetFocus();
}

void CMysql_buddyDoc::OnUpdateTest(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMysql_buddyDoc::OnDatabase() 
{
	// TODO: Add your command handler code here

	GetFrame()->SetStatus("Connecting...");

	CDlgDatabase dlg(&m_mother, (CDocument*)this);
	dlg.DoModal();

	m_mother.SetMainWnd(GetView());
	m_mother.NotifyTables(WM_UTABLEREPOPULATE, 0);
	m_mother.UpdateVisual();
}

void CMysql_buddyDoc::OnUpdateDatabase(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

CWnd * CMysql_buddyDoc::GetView()
{
	CView* pView = NULL;

	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		pView  = GetNextView(pos);
		return (CWnd*)(pView);
   }   

   return NULL;
}


void CMysql_buddyDoc::OnTabledelete() 
{
	// TODO: Add your command handler code here
	
	int i = m_mother.GetSelTable();

	if (i!= -1)
	{
		CTable & table = (* m_mother[i]) ;

		char szTemp[256];
		wsprintf(szTemp,"Are you sure you want to delete \"%s\"?",
			table.m_szName);

		if (AfxMessageBox(szTemp, MB_YESNO)==IDYES)
		{
			m_mother.RemoveAt(i);
			m_mother.SetSelTable(-1);
			m_mother.NotifyTables(WM_UTABLESORDERCHANGED, 0);
			SetModifiedFlag(TRUE);
		}
	}
}

void CMysql_buddyDoc::OnUpdateTabledelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMysql_buddyDoc::OnTableedit() 
{
	// TODO: Add your command handler code here

	int i = m_mother.GetSelTable();
	if (i!= -1)
	{
		CDlgTable dlg(&m_mother, (CDocument*)this, i);
		if (dlg.DoModal()==IDOK)
		{
		}

		m_mother.SetMainWnd(GetView());
		m_mother.NotifyTables(WM_UTABLEREPOPULATE, 0);
		m_mother.UpdateVisual();
	}
}

void CMysql_buddyDoc::OnUpdateTableedit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMysql_buddyDoc::OnTablerename() 
{
	// TODO: Add your command handler code here
	int i = m_mother.GetSelTable();
	if (i!= -1)
	{
		CTable & table = (* m_mother[i]) ;
		CDlgNewThing dlg("New name");
		dlg.SetName(table.m_szName);
		if (dlg.DoModal()==IDOK)
		{
			strcpy(table.m_szName, dlg.m_strName.GetBuffer(1));
			m_mother.NotifyTables(WM_UTABLENAMECHANGED, 0);
			SetModifiedFlag(TRUE);
		}
	}
}

void CMysql_buddyDoc::OnUpdateTablerename(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMysql_buddyDoc::OnWriteDropCode() 
{
	// TODO: Add your command handler code here
    CString strFilesFilter =
        "SQL files |*.sql"\
        "|";

	CFileDialog dlg( FALSE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Export DROP TABLES"; 
	dlg.m_ofn.lpstrDefExt = ".sql";
    
    if (dlg.DoModal()==IDOK)  {

		CString strFilename = dlg.GetFileName();
		CFile file;
		if (file.Open(strFilename, 	CFile::modeCreate| CFile::modeWrite
			| CFile::typeBinary ))
		{
			for (int i=0; i< m_mother.GetSize(); i++)
			{
				CString str;				

				str= CString("DROP TABLE ") + m_mother[i]->m_szName + ";\r\n";
				char *p = str.GetBuffer(1);
				file.Write(p, strlen(p));
			}

			file.Close();
		}
	}			
}

void CMysql_buddyDoc::OnUpdateWriteDropCode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMysql_buddyDoc::OnWriteTechdoc() 
{
	// TODO: Add your command handler code here
    CString strFilesFilter =
        "HTML files |*.html;*.htm"\
        "|";

	CFileDialog dlg( FALSE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			| OFN_EXPLORER, 
            strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Export TechDoc"; 
	dlg.m_ofn.lpstrDefExt = ".htm";
    
    if (dlg.DoModal()==IDOK)  {

		CString strFilename = dlg.GetFileName();
		CFile file;        
        if (file.Open(strFilename, 	CFile::modeCreate| CFile::modeWrite
			| CFile::typeBinary ))
		{
            CString str;				

            str = "<html>\r\n" \
                "<head>\r\n" \
                "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=ISO-8859-1\">\r\n" \
                "  <title>Data model</title>\r\n" \
                "  <meta name=\"GENERATOR\" content=\"MySQL Buddy v0.03\">\r\n" \
                "</head>\r\n" \
                "<body>\r\n\r\n";

    		char *p = str.GetBuffer(1);
			file.Write(p, strlen(p));

			for (int i=0; i< m_mother.GetSize(); i++)
			{				
                m_mother[i]->FormatTechDoc(str);

				p = str.GetBuffer(1);
				file.Write(p, strlen(p));
			}

            str = "</body>\r\n</html>";
            p = str.GetBuffer(1);
			file.Write(p, strlen(p));

			file.Close();
		}

	}			
}

void CMysql_buddyDoc::OnUpdateWriteTechdoc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMysql_buddyDoc::DestroyDocument()
{
	m_mother.Forget();
}

void CMysql_buddyDoc::OnSetTableDescription() 
{
	// TODO: Add your command handler code here
	int i = m_mother.GetSelTable();
	if (i!= -1)
	{
        CTable *pTable = m_mother[i];

		CDlgDescription dlg(pTable, GetView());
        dlg.m_strDescription = CString(pTable->m_szInfo);
		if (dlg.DoModal()==IDOK)
		{
            char *p = dlg.m_strDescription.GetBuffer(1);

            if (strcmp(p, pTable->m_szInfo))
            {
                strcpy(pTable->m_szInfo, p); 
                this->SetModifiedFlag(TRUE);
            }
		}

		m_mother.SetMainWnd(GetView());
		//m_mother.NotifyTables(WM_UTABLEREPOPULATE, 0);
		//m_mother.UpdateVisual();
	}
}

void CMysql_buddyDoc::OnUpdateSetTableDescription(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMysql_buddyDoc::OnImportsql() 
{
	// TODO: Add your command handler code here
    CString strFilesFilter =
        "SQL files |*.sql"\
        "|";

	CFileDialog dlg( TRUE,NULL,NULL, 
            OFN_HIDEREADONLY | OFN_EXPLORER, 
            strFilesFilter,  AfxGetMainWnd() ) ;

    dlg.m_ofn.lpstrTitle = "Import SQL tables"; 
	dlg.m_ofn.lpstrDefExt = ".sql";
    
    if (dlg.DoModal()==IDOK)  
    {   
		CString strFilename = dlg.GetFileName();
		CFile file;
		if (file.Open(strFilename, 	 CFile::modeRead
			| CFile::typeBinary ))
		{
            int nSize = file.GetLength();
            char *pOrg = (char*)malloc(nSize+1);
            pOrg[nSize]=0;
            file.Read(pOrg, nSize);
            file.Close();

            char c = 0;
            char *pBuf = pOrg;
            char *pStart = pBuf;
            char *pEnd;
            char *p;

            CTable *pTable = NULL;
            CField *pField = NULL;

            CString str;

            while (*pBuf)
            {
                switch((unsigned)*pBuf)
                {
                    // ignore comments
                    case '#':                
                        while (*pBuf!='\r' && *pBuf!='\n' && *pBuf)
                        {
                            pBuf++;
                        }
                    break;

                    // skip end of line
                    case 13:
                        pBuf++;
                        if (*pBuf==10) { pBuf++;}
                        pStart = pBuf;
                    break;

                    // carriage return
                    case 10:
                        pBuf++;
                        if (*pBuf==13) { pBuf++; }
                        pStart = pBuf;
                    break;

                    // skip tab and space
                    case 9:
                    case 32:
                        pBuf ++;
                    break;

                    // if a line start with a ')'
                    // add this table and
                    // move on to the next table
                    case ')':
                        if (pTable)
                        {
                            m_mother.Add(pTable);
                            pTable = NULL;
                        }
                        else
                        {
                            OutputDebugString("WARNING: End of table found but no table in processing\r\n");
                        }

                        while (*pBuf!='\r' && *pBuf!='\n' && *pBuf)
                        {
                            pBuf++;
                        }
                    break;

                    default:
                        // found a new table
                        if (memicmp(pBuf, "CREATE TABLE", strlen("CREATE_TABLE"))==0)
                        {
                            OutputDebugString("New table\r\n");

                            pBuf += strlen("CREATE TABLE ");
                            pTable= (CTable*)malloc(sizeof(CTable));
                            ZeroMemory(pTable, sizeof(CTable));
                            pTable->SetWndXY(100,100);
                            pTable->SetWndSize(100,100);

                            pStart = pBuf;
                            while (*pBuf && (isalnum(*pBuf) || *pBuf=='_'))
                            {
                                pBuf++;
                            }

                            c = *pBuf;
                            *pBuf =0;
                            strcpy(pTable->m_szName, pStart);
                            *pBuf = c;                            

                            while (*pBuf!='\r' && *pBuf!='\n' && *pBuf)
                            {
                                pBuf++;
                            }
                        }
                        else
                        {
                            if (isalnum(*pBuf) && pTable)
                            {
                                if (memicmp(pBuf, "PRIMARY KEY", strlen("PRIMARY KEY"))==0)
                                {
                                    pStart = strstr(pBuf, "(");
                                    if (pStart)
                                    {
                                        pStart++;

                                        pEnd = strstr(pStart, ")");
                                        if (pEnd)
                                        {
                                            c = *pEnd;
                                            *pEnd =0;

                                            while (*pStart)
                                            {
                                                p = strstr(pStart, ",");
                                                if (p) *p=0;

                                                CField *pField = pTable->FindField(pStart);
                                                if (pField)
                                                {
                                                    pField->m_bPrimary = TRUE;
                                                }
                                                else
                                                {
                                                    str.Format("Couldn't find field '%s' for PRIMARY KEY\r\n", pStart);
                                                    OutputDebugString(str);
                                                }                                            

                                                if (p) 
                                                {
                                                    *p=',';
                                                    pStart = p+1;
                                                }
                                                else
                                                {
                                                    pStart = pEnd;
                                                }
                                            }

                                            *pEnd =c;
                                        }
                                    }

                                }
                                else if (memicmp(pBuf, "KEY", strlen("KEY"))==0)
                                {
                                    pStart = strstr(pBuf, "(");
                                    if (pStart)
                                    {
                                        pStart++;

                                        pEnd = strstr(pStart, ")");
                                        if (pEnd)
                                        {
                                            c = *pEnd;
                                            *pEnd =0;

                                            while (*pStart)
                                            {
                                                p = strstr(pStart, ",");
                                                if (p) *p=0;

                                                CField *pField = pTable->FindField(pStart);
                                                if (pField)
                                                {
                                                    pField->m_bKey = TRUE;
                                                }
                                                else
                                                {
                                                    str.Format("Couldn't find field '%s' for KEY\r\n", pStart);
                                                    OutputDebugString(str);
                                                }

                                                if (p) 
                                                {
                                                    *p=',';
                                                    pStart = p+1;
                                                }
                                                else
                                                {
                                                    pStart = pEnd;
                                                }
                                            }

                                            *pEnd =c;
                                        }  
                                    }
                                }
                                else if (memicmp(pBuf, "UNIQUE KEY", strlen("UNIQUE KEY"))==0)
                                {
                                    // don,t know how to handle this one
                                    // so just skip it
                                    while (*pBuf!='\r' && *pBuf!='\n' && *pBuf)
                                    {
                                        pBuf++;
                                    }                                
                                }                                    
                                else
                                {
                                    if (pTable)
                                    {
                                        pEnd = strstr(pBuf, "\n");
                                        if (!pEnd)
                                        {
                                            pEnd = strstr(pBuf, "\r");
                                            if (!pEnd)
                                            {
                                                pEnd = pBuf + strlen(pBuf);
                                            }
                                        } 

                                        c = *pEnd;
                                        *pEnd =0;

                                        pField = (CField*) malloc(sizeof(CField));
                                        ZeroMemory(pField, sizeof(CField));
                                        pField->Fill(pBuf);
                                        pTable->Add(pField);

                                        *pEnd =c;

                                        pBuf = pEnd;
                                    }
                                }

                                while (*pBuf!='\r' && *pBuf!='\n' && *pBuf)
                                {
                                    pBuf++;
                                }                            
                            }
                        }
                    break;                        
                }                
            }

            free(pOrg);

    		m_mother.SetMainWnd(GetView());
	    	m_mother.NotifyTables(WM_UTABLEREPOPULATE, 0);
		    m_mother.UpdateVisual();
        }
    }
}

void CMysql_buddyDoc::OnUpdateImportsql(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
