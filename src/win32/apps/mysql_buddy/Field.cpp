// Field.cpp : implementation file
//

#include "stdafx.h"
//#include "mysql_buddy.h"
#include "Field.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// UNIQUE requestid (requestid)
//  KEY msg_id (msg_id),
// auto_increment

TYPEINFO g_arrTypeHash[]=
{
	2, "double", (int) FIELD_TYPE_DECIMAL, 
	1, "tinyint", (int) FIELD_TYPE_TINY,
	1, "short", (int)FIELD_TYPE_SHORT,  //???
	1, "int", (int)FIELD_TYPE_LONG,
	2, "double", (int)FIELD_TYPE_FLOAT,  
	2, "double", (int)FIELD_TYPE_DOUBLE,
	0, "null", (int)FIELD_TYPE_NULL,   
	0, "timestamp", (int)FIELD_TYPE_TIMESTAMP, // ???
	1, "bigint", (int)FIELD_TYPE_LONGLONG,
	1, "mediumint", (int)FIELD_TYPE_INT24, // int24
	0, "date", (int)FIELD_TYPE_DATE,   
	0, "time", (int)FIELD_TYPE_TIME,
	0, "datetime", (int)FIELD_TYPE_DATETIME, 
	0, "year", (int)FIELD_TYPE_YEAR, // year ???
	0, "newdate", (int)FIELD_TYPE_NEWDATE,  // ???
	0, "enum", (int)FIELD_TYPE_ENUM /*=247*/,  
	0, "set", (int)FIELD_TYPE_SET /*=248*/, // ???
	0, "tinytext", (int)FIELD_TYPE_TINY_BLOB /*=249*/,
	0, "mediumtext", (int)FIELD_TYPE_MEDIUM_BLOB /*=250*/,
	0, "bigtext", (int)FIELD_TYPE_LONG_BLOB /*=251*/,
	0, "text", (int)FIELD_TYPE_BLOB /*=252*/,
	1, "varchar", (int)FIELD_TYPE_VAR_STRING /*=253*/,
	1, "string", (int)FIELD_TYPE_STRING /*=254*/,
	0, NULL, -1
};

char *g_arrTypes[]=
{
	"int",
	"tinyint", 
	"mediumint",
	"bigint",
	"varchar",
	"char",
	"text", // no size
	"tinytext", // no size
	"date", // no size (0000-00-00)
	"datetime", // 	'0000-00-00 00:00:00'
	"enum", // special
	"double", // (x,y)
	"time",
	"mediumtext",
	"bigtext",
	"timestamp",
	"year",
	//"newdate",
	//"short",
	"set",
	"null",
	"boolean",
	NULL
};

char *g_arrTypeAlias[]=
{
    "longtext", "bigtext",
    "decimal", "double",
    "smallint", "tinyint",
    "blob", "text",
    NULL, NULL
};

/////////////////////////////////////////////////////////////////////////////
// CField

CField::CField()
{
	Init();
}

CField::~CField()
{
}

/////////////////////////////////////////////////////////////////////////////
// CField message handlers

void CField::Init()
{
	/*
	m_szName[0] = 0;
	m_bPrimary  = FALSE;
	m_bNotNull  = FALSE;
	m_nType = 0;
	m_nSize = 0;
	m_pNext = NULL;
	*/

	ZeroMemory(this, sizeof(CField));
}

typedef struct 
{
	 char m_szName[MAX_FI_NAME];
	 char m_szDefault[MAX_FI_DEFAULT];
	 char m_szArg[MAX_FI_ARG];
	 int m_nType;
	 int m_nSize;

	 BOOL m_bPrimary;
	 BOOL m_bNotNull;
	 BOOL m_bAuto;
	 BOOL m_bKey;
	 BOOL m_bUnique;
	 BOOL m_bUnsigned;

	 CField *m_pNext;

} FIELD_INFO;

void CField::Serialize(CArchive & ar, int nVer)
{
    int nInfoSize;

	if (ar.IsLoading()) // loading
	{
        switch(nVer)
        {
            case 0:
            case 1:
            case 2:
        		ar.Read(this, sizeof(FIELD_INFO));		
            break;

            case 3:
        		ar.Read(this, sizeof(FIELD_INFO));		
                ar.Read(&nInfoSize, 4);
                ar.Read(m_szInfo, nInfoSize);
                m_szInfo[nInfoSize]=0;
            break;
        }

		m_pNext = NULL;
	}
	else // saving
	{
		ar.Write(this, sizeof(FIELD_INFO));
        nInfoSize = strlen(m_szInfo);
        ar.Write(&nInfoSize, 4);
        ar.Write(m_szInfo, nInfoSize);
	}
}

void CField::Forget()
{
	Init();
}

void CField::FormatField(char *szTemp)
{
	CField *p = this;

	char *pTypeName = "";
	if (p->m_nType !=-1)
	{
		pTypeName = g_arrTypes[p->m_nType];
	}

	if (p->m_szArg[0])
	{	

		wsprintf(szTemp,
			"%s %s(%s)", p->m_szName, pTypeName, p->m_szArg);
	}
	else
	{
		wsprintf(szTemp,
			"%s %s", p->m_szName, pTypeName);
	}

	if (p->m_bUnsigned)
	{
		strcat(szTemp, " UNSIGNED");
	}

	if (p->m_bNotNull)
	{
		strcat(szTemp, " NOT NULL");
	}

	if (p->m_bAuto)
	{
		strcat(szTemp, " auto_increment");
	}
}

void CField::Init(MYSQL_FIELD *pField)
{
/*

name
table
def ???
type
length
max_length
flags (1) NOT NULL

*/
	Init();

	strcpy(m_szName, pField->name);

	int nHash =-1;

	for (int i=0; g_arrTypeHash[i].m_szName[0]; i++)
	{
		if ( ((int)pField->type) == g_arrTypeHash[i].m_nType)
		{
			nHash = i;
			break;
		}
	}

	int nArgs;

	if (nHash!=-1)
	{
		nArgs = g_arrTypeHash[nHash].m_nArgs;
		m_nType = FindType(g_arrTypeHash[nHash].m_szName);
	}
	else
	{
		nArgs = 0;
		m_nType = -1;
		OutputDebugString("Unknown type\n");
	}

	switch (nArgs)
	{
		case 0:			
		break;
		
		case 1:
			wsprintf(m_szArg, "%d", pField->length);
		break;

		case 2:
			wsprintf(m_szArg, "%d,%d", pField->length, 
				pField->decimals);
		break;
	}

	m_bNotNull = (pField->flags & NOT_NULL_FLAG);
	m_bPrimary = (pField->flags & PRI_KEY_FLAG);
	m_bAuto = (pField->flags & AUTO_INCREMENT_FLAG);
	m_bKey = (pField->flags & PART_KEY_FLAG);
}

int CField::FindType(char *sz)
{
	int i;
	for (i=0; g_arrTypes[i]; i++)
	{
		if (stricmp(sz,  g_arrTypes[i])==0)
		{
			return i;
		}
	}

	char szTemp[256];
	wsprintf(szTemp,"Type %s is unknown\n", sz);
	OutputDebugString(szTemp);
	return -1;
}

void CField::FormatTechDoc(CString & str)
{
    char szTemp[64];

	CField *p = this;

	char *pTypeName = "";
	if (p->m_nType !=-1)
	{
		pTypeName = g_arrTypes[p->m_nType];
	}

	if (p->m_szArg[0])
	{	

		wsprintf(szTemp,
			"%s(%s)", pTypeName, p->m_szArg);
	}
	else
	{
		wsprintf(szTemp,
			"%s", pTypeName);
	}

    char *szPrefix="";

    if (m_bKey)
    {
        szPrefix="-";
    }

    if (m_bPrimary)
    {
        szPrefix="*";
    }

    str.Format("<tr>\r\n" \
        "  <td valign=TOP width=212>%s%s</td>\r\n" \
            "  <td valign=TOP width=212>%s</td>\r\n" \
            "  <td valign=TOP width=212>%s</td>\r\n" \
            "</tr>\r\n",
        szPrefix, p->m_szName, szTemp, p->m_szInfo); 
}

void CField::Fill(char *sz)
{
    CString str;

    while (*sz==9 || *sz==32)
    {
        sz++;
    }

    // find the name
    char *pStart = sz;
    while (*sz && (isalnum(*sz) || *sz=='_'))
    {
        sz++;
    }

    char c= *sz;
    *sz=0;
    strcpy(m_szName, pStart);
    *sz=c;

    // find the type
    sz++;
    pStart = sz;

    while (*sz && (isalnum(*sz) || *sz=='_'))
    {
        sz++;
    }

    c= *sz;
    *sz=0;
    /*
    for (i=0; g_arrTypes[i] && !bFound; i++)
    {
        if (strcmpi (g_arrTypes[i], pStart)==0)
        {
            bFound = TRUE;
            m_nType= i;
        }
    }
    */
    m_nType = FindType(pStart);

    int i;
    BOOL bFound = FALSE;
    if (m_nType==-1)
    {
        for (i=0; g_arrTypeAlias[i] && !bFound; i+=2)
        {
            if (strcmpi (g_arrTypeAlias[i], pStart)==0)
            {
                bFound = TRUE;
                m_nType = FindType(g_arrTypeAlias[i+1]);
            }
        }
    }

    if (m_nType==-1)
    {
        str.Format("REALLY unknown type '%s'\r\n", pStart);
        OutputDebugString(str);
        m_nType=0;
    }
    
    *sz=c;

    m_szArg[0]=0;
    if (c == '(')
    {
        sz++;
        pStart = sz;

        char *pEnd = strstr(sz, ")");
        if (pEnd)
        {
            c = *pEnd;
            *pEnd = 0;
            strcpy(m_szArg, pStart);
            *pEnd = c;
        }
    }

    m_bAuto = strstr(sz, "auto_increment") != NULL;
    m_bNotNull = strstr (sz, "NOT NULL") != NULL;
    m_bUnsigned = strstr (sz, "unsigned") != NULL;

    m_szDefault[0]=0;
    m_szInfo[0]=0;
    // unique to be implemented
    m_bUnique=FALSE;
    m_bPrimary=FALSE;
    m_bKey=FALSE;


}
