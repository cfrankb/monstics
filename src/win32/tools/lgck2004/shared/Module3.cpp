// Module3.cpp : implementation file
//

#include "common.h"
#include "stdafx.h"
#include "Module3.h"
#include "f:\toolkit\win32\lc4\const.h"

int GenOpCode(UCHAR *pCode, 
			   unsigned nAddr,
			   char *szGen, 
			   BOOL bVerbose);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ARGTYPE_STRING	0x80000000
#define ARGTYPE_VAR		0x40000000
#define ARGTYPE_CONST	0x00000000
#define ARGTYPE_MASK	0xf0000000

#define CMDTYPE_IF		0x81000000
#define CMDTYPE_WHILE	0x41000000
#define CMDTYPE_IFX		0x90000000
#define CMDTYPE_ELSE	0x20000000
#define CMDTYPE_ENDIF	0x20000000
#define CMDTYPE_WHILEX	0x50000000
#define CMDTYPE_WEND	0x20000000
#define CMDTYPE_SWITCH  0x20000000
#define CMDTYPE_CASE	0x20000000
#define CMDTYPE_BREAK	0x22000000
#define CMDTYPE_DEFAULT	0x20000000
#define CMDTYPE_SEND    0x20000000
#define CMDTYPE_MASK	0xf0000000
#define CMDTYPE_MASKX	0x10000000

#define GROWBY 10
#define SIZEOF sizeof(CLgckArr)
#define PTR CLgckArr*
#define MAX_STRING 2048

typedef struct 
{
	int m_nVal;
	char m_szText[16];
} VALCODE;

typedef struct
{
	char m_szText[16];
	int m_nLevelMod;
	int m_nCmdType;
} VALCODE2;

typedef struct
{
	int m_nOp;
	int m_nOp2;
	char m_szOp[16];
	char m_szEn[4];
	int m_nOpType;
} VALCODE3;

static VALCODE2 g_arrCmdTypes[]=
{
	"ifx",		 1,	CMDTYPE_IFX,
	"else",		 0,	CMDTYPE_ELSE,
	"endif",	-1, CMDTYPE_ENDIF,
	"whilex",	 1,	CMDTYPE_WHILEX,
	"wend",		-1, CMDTYPE_WEND,
	"switch",	 1,	CMDTYPE_SWITCH,
	"end",		-1, CMDTYPE_SEND,
	"if",		 1, CMDTYPE_IF,
	"while",	 1,	CMDTYPE_WHILE,
	"case",		 0, CMDTYPE_CASE,
	"break",	 0, CMDTYPE_BREAK,
	"default",	 0, CMDTYPE_DEFAULT,
	NULL,		 0,	0,
};

static VALCODE g_arrConstX[]=
{
	0,			"up",
	1,			"down",
	2,			"left",
	3,			"right",
	4,			"left_up",
	5,			"right_up",
	6,			"left_down",
	7,			"right_down",
	0x12,		"leap_left", 
	0x13,		"leap_right",
	0x20,		"jump_up", 
	0x21,		"jump_down",
	0x22,		"jump_left",
	0x23,		"jump_right",
	255,		"here",
	0,			"false",
	1,			"true",
	NULL, NULL
};

static char *g_arrInst[]=
{
	"rem|",
	"die|",
	"play|$",
	"music|$",
	"level|*",
	"nextlevel|",
	"endlevel|",
	"changeto|$",
	"move|%",
	"moveby|%=",
	"trigger|=",
	"create|$",
	"destroy|$",
	"debug|*",
	"message|*",
	"gameover|",
	"aim|%",
	"exit|",
	"return|=",
	"call|$",
	"save|$",
	"load|$",
	"restart|",
	"episode|$",
	"ifx|",
	"else|",	
	"endif|",
	"label|%",
	"goto|%",
	"whilex|",
	"wend|",
	"inc|%",
	"dec|%",
	"add|%=",
	"sub|%=",
	"set|%=",
	"xor|%=",
	"mod|%%",
	"div|%%",
	"isplayerthere|%",
	"canwalk|%",
	"testaim|%",
	"valid|%",
	"switch|=",
	"case|=",
	"end|",
	"if|==",
	"while|==",
	"break|",
	"default|",
	"ismyclass|$",
	"ismytype|$",
	"unmap_sprite|",
	"map_sprite|",
	"killplayer|",
	"idiv|%%",
	"storereg|%",
	"loadreg|=",
	"or|%=",
	"and|%=",
	NULL
};

static int GetIndexFor(VALCODE *arr, char *szText)
{
	int i =0;
	BOOL bFound = FALSE;

	while (*arr[i].m_szText && !bFound)
	{
		bFound = (strcmp(arr[i].m_szText, szText)==0);
		if (!bFound)
		{
			i++;
		}
	}
	
	if (bFound)
	{
		return i;
	}
	else
	{
		return -1;
	}
}

static int GetIndexFor(VALCODE2 *arr, char *szText)
{
	int i =0;
	BOOL bFound = FALSE;

	while (*arr[i].m_szText && !bFound)
	{
		bFound = (strcmp(arr[i].m_szText, szText)==0);
		if (!bFound)
		{
			i++;
		}
	}
	
	if (bFound)
	{
		return i;
	}
	else
	{
		return -1;
	}
}

static int GetIndexFor(char **arr, char *szText)
{
	int i =0;
	BOOL bFound = FALSE;

	while (arr[i] && !bFound)
	{
		bFound = (strcmp(arr[i], szText)==0);
		if (!bFound)
		{
			i++;
		}
	}
	
	if (bFound)
	{
		return i;
	}
	else
	{
		return -1;
	}
}

static int GetIndexFor(VALCODE3 *arr, char *szOp, char *szEn)
{
	int i =0;
	BOOL bFound = FALSE;

	while (*arr[i].m_szOp && !bFound)
	{
		bFound = (strcmp(arr[i].m_szOp, szOp) == 0)
			&& (strcmp(arr[i].m_szEn, szEn) == 0);
		if (!bFound)
		{
			i++;
		}
	}
	
	if (bFound)
	{
		return i;
	}
	else
	{
		return -1;
	}
}

/*

static char *GetArg(char *szSource, char *szArg)
{
	while (*szSource==' ')
	{
		szSource++;
	}
	
	BOOL bString = (*szSource=='$');
	BOOL bDone = !*szSource;

	while (!bDone)		
	{
		*szArg = *szSource;

		if (bString)
		{
			bDone = !*szSource;
		}
		else
		{
			bDone = !(*szSource) || (*szSource==' ');
		}

		if (!bDone)
		{
			szArg++;	
			szSource++;
		}
	}

	*szArg = 0;

	return szSource;
}

static str2int(char *sz)
{
	BOOL bHex=FALSE;

	BOOL bNeg = FALSE;
	int i = 0;
	int n = 0;

	switch (sz[i])
	{
		case '-':
			bNeg = TRUE;
		case '+':
			i++;
		break;
	}

	if (sz[i]=='0' && sz[i+1]=='x')
	{
		i=i+2;
		bHex=TRUE;
	}

	if (!bHex)
	{
		while (sz[i] && sz[i]>='0' && sz[i]<='9')
		{
			n = n * 10 + sz[i] - '0';
			i++;
		}
	}
	else
	{
		while (sz[i] && ((sz[i]>='0' && sz[i]<='9') ||
			(sz[i]>='a' && sz[i]<='f')))
		{
			if (sz[i]<='9')
			{
				n = n * 16+ sz[i] - '0';
			}
			else
			{
				n = n * 16+ sz[i] - 'a' + 10;
			}

			i++;
		}
	}

	if (bNeg)
		n = - n;

	return n;
}

static char * ReadLine(char * pBuf, char *szLine)
{
	int n=0;
	char *pOrg = pBuf;

	while ( (*pBuf!=0x0d) && (*pBuf!=0x0a) && (*pBuf) )
	{
		n++;
		pBuf++;
	}

	if (n>MAX_STRING)
	{
		char szTemp[64];
		wsprintf(szTemp, "Warning: string length is n=%d -- too large\n", n);
		OutputDebugString(szTemp);
		n=MAX_STRING;
	}
	
	if (*pBuf==0x0d)
		pBuf++;

	if (*pBuf==0x0a)
		pBuf++;

	memcpy(szLine, pOrg, n);
	*(szLine+n)=0;

	return pBuf;
}

  */

static int ExtendSign(int n)
{
	if (n & 0x8000)
		return n | 0xffff0000;
	else
		return n;
}

/////////////////////////////////////////////////////////////////////////////
// CModule3

CModule3::CModule3()
{
	Init();
}

CModule3::~CModule3()
{
	Forget();
}	

/////////////////////////////////////////////////////////////////////////////
// CModule3 message handlers

void CModule3::Forget()
{
	OutputDebugString("--> CModule3::Forget()\n");

	m_arrStrings.Forget();
	m_arrVars.Forget();

	if (m_pData)
	{
		for (int i=0; i<m_nSize; i++)
		{
			m_pData[i].Forget();
		}

		free(m_pData);
		m_pData = 0;
	}

	m_nMax =0;
	m_nSize =0;

	// close fileT

	m_fileT.Close();
}

void CModule3::Init()
{
	OutputDebugString("--> CModule3::Init()\n");
	char *p;
	int i;
	if (strstr(g_arrInst[0], "|"))
	{
		i = 0;
		while (g_arrInst[i])
		{
			p = strstr(g_arrInst[i], "|");
			if (p)
			{
				*p =0;
			}
			i++;
		}
	}

	i = 0;
	while (*g_arrConstX[i].m_szText)
	{
		CTagEntry entry(g_arrConstX[i].m_szText, g_arrConstX[i].m_nVal);
		m_arrVars.Add(entry);
		i++;
	}

	m_nMax = GROWBY;
	m_nSize = 0;
	m_pData = (PTR) malloc(SIZEOF * m_nMax);
	ZeroMemory(m_pData, SIZEOF * m_nMax);

	// prepare output file
	//CFile m_fileT;
	if (!m_fileT.Open("debug.out", CFile::modeCreate |
		CFile::modeWrite |
		CFile::typeBinary)) 
	{
		OutputDebugString("CModule3::ProcessText -- cannot create debug.out\n");
		//return FALSE;
	}
}

int CModule3::eval(char *sz)
{
	int n;
	
	switch(*sz)
	{
		case '%':	// Variables
			_strlwr(sz);
			sz++;
			n = m_arrVars.GetIndexFor(sz);
			if (n!=-1) 
			{
				return n & 0xffff | ARGTYPE_VAR;
			}
			else
			{
				return m_arrVars.Add(sz) | ARGTYPE_VAR;
			}
		break;

		case '$': // strings
			sz++;
			n = m_arrStrings.GetIndexFor(sz);
			if (n!=-1) 	
			{	
				return (n & 0xffff)| ARGTYPE_STRING;
			}
			else
			{
				return m_arrStrings.Add(sz) | ARGTYPE_STRING;
			}
		break;

		default:	// Constants
			return str2int(sz) & 0xffff;
		break;
	}
	return 0;
}

char* CModule3::ProcessString(char *sz, int &nLevel)
{
	char *szT = sz;

	CLgckCmd cmd;
	cmd.m_nLevel = nLevel;

	static char szArgs[4][_MAX_PATH];
	szArgs[0][0]=0;
	szArgs[1][0]=0;
	szArgs[2][0]=0;
	szArgs[3][0]=0;

	int x;
	int i;
	int n = 0;

	int nLevelMod = 0;
	int nCmdType = 0;

	for (i=0; i<4 && *szT; i++)
	{
		szT = GetArg(szT, szArgs[i]);
		if (!n)		
		{
			_strlwr(szArgs[i]);
			x = GetIndexFor(g_arrCmdTypes, szArgs[i]);
			if (x != -1)
			{
				nLevelMod = g_arrCmdTypes[x].m_nLevelMod;
				nCmdType = g_arrCmdTypes[x].m_nCmdType;
			}

			if (nCmdType == CMDTYPE_IF)
			{
				GetArg(szT, szArgs[1]);
				x = GetIndexFor(g_arrInst, szArgs[1]);
				if (x!=-1)
				{
					nCmdType = CMDTYPE_IFX;
				}
			}

			if (nCmdType == CMDTYPE_WHILE)
			{
				GetArg(szT, szArgs[1]);
				x = GetIndexFor(g_arrInst, szArgs[1]);
				if (x!=-1)
				{
					nCmdType = CMDTYPE_WHILEX;
				}
			}

			if (nCmdType & CMDTYPE_MASKX)
			{
				i++;
				szT = GetArg(szT, szArgs[i]);
				_strlwr(szArgs[i]);
				cmd.m_arrArgs[n] = 
					GetIndexFor(g_arrInst, szArgs[i]) 
					| nCmdType;
			}
			else
			{
				cmd.m_arrArgs[n] = 
					GetIndexFor(g_arrInst, szArgs[i]) 
					| nCmdType;
			}
		
			if (cmd.m_arrArgs[0]==0)
			{
				break;
			}

			n++;		
		}
		else
		{
			cmd.m_arrArgs[n] = eval(szArgs[i]);
			n++;
		}
	}

	// Set how many args
	if (nCmdType & CMDTYPE_MASKX)
	{
		cmd.m_nArgs = i -1;
	}
	else
	{
		cmd.m_nArgs = i;
	}

	if (szArgs[0][0]=='%' && strlen(szArgs[0])>1)
	{
		cmd.m_arrArgs[0] = GetIndexFor(g_arrInst, "set");
		cmd.m_arrArgs[1] = eval(szArgs[0]);
		cmd.m_arrArgs[2] = eval(szArgs[1]);

		cmd.m_nArgs = 3;
	}

	if (szArgs[0][0]==':' && strlen(szArgs[0])>1)
	{	
		cmd.m_arrArgs[0] = GetIndexFor(g_arrInst, "label");
		cmd.m_arrArgs[1] = eval(szArgs[0]+1);

		cmd.m_nArgs = 2;
	}

	int a =1;
	a++;

	nLevel = nLevel + nLevelMod;
	if (nLevelMod>=0)
	{
		cmd.m_nLevel = nLevel;
	}

	if (cmd.m_arrArgs[0]==-1)
	{
		char *p = (char*)malloc(40+strlen(sz));
		wsprintf(p,"Syntax error in %c%s%c",
			34, sz,34);
		return p;
	}
	else
	{
		if (cmd.m_arrArgs[0])
		{
		
			char *p= CheckCmd(cmd);
			if (p)
			{
				char *pp = (char*)malloc(strlen(p)+strlen(sz)+5);
				wsprintf(pp,"%s %c%s%c",
					p, 34, sz,34);

				free(p);
				return pp;
			}

			Add(cmd);
		}
	}

	return NULL;
}

int CModule3::Add(CLgckCmd & cmd)
{
	if (m_nSize==0)
	{
		m_nSize=1;
		if (!m_pData)
		{
			m_nMax = GROWBY;
			m_pData = (PTR) malloc(m_nMax*SIZEOF);
		}
		m_pData[0].Init();
	}

	m_pData[m_nSize-1].Add(cmd);

	return m_nSize-1;	
}

void CModule3::Clean(char *sz)
{
	BOOL bPre = TRUE;
	int n = 0;
	int i = 0;

	i = 0;
	while (sz[i])
	{
		switch(sz[i])
		{
			case 9:
				sz[i]=32;
			break;

			case '#':
			case ';':
			case '/':
				sz[i]=0;
			break;
		}
		i++;
	}

	i = 0;
	while (sz[i])
	{	
		bPre = bPre && sz[i]==32;
		sz[n]= sz[i];

		if (!bPre)
		{
			n++;
		}

		i++;
	}
	sz[n]=0;

	i = strlen(sz)-1;
	while (i && sz[i]==32)
	{
		sz[i]=0;
		i --;
	}
}

void CModule3::Write (CFile &file)
{
	// storing

	file.Write ("CMD3", 4);
	file.Write (&m_nSize, 4);

	int i;
	for (i=0; i<m_nSize; i++)
	{
		m_pData[i].Write(file);
	}

	m_arrVars.Write(file);
	m_arrStrings.Write(file);
}

void CModule3::Read(CFile &file)
{
	char szSig[5];
	szSig[4] = 0;

	file.Read(szSig, 4);

	if (strcmp(szSig, "CMD3")==0)
	{
		Forget();
		int nSize;
		file.Read(&nSize,4);
		for (int i=0; i<nSize; i++)
		{
			NewArray("");
			m_pData[i].Read(file);
		}

		m_arrVars.Forget();
		m_arrStrings.Forget();

		m_arrVars.Read(file);
		m_arrStrings.Read(file);
	}
}

char * CModule3::CheckCmd(CLgckCmd & cmd)
{
	char *pError;

	if (cmd.m_arrArgs[0]==0)
	{
		return NULL;
	}

	if (cmd.m_arrArgs[0]==-1)
	{
		pError = (char*)malloc(32);
		strcpy(pError, "Syntax error in ");
		return pError;
	}

	int i = cmd.m_arrArgs[0] & 0xffff;

	char *p = g_arrInst[i] + strlen(g_arrInst[i]) + 1;

	int n = (int)strlen(p) +1;

	if (cmd.m_nArgs < n )
	{
		pError = (char*)malloc(64);
		wsprintf(pError, "Not enough args for");
		return pError;
	}

	if (cmd.m_nArgs > n)
	{
		pError = (char*)malloc(64);
		wsprintf(pError, "Too many args for");
		return pError;
	}

	for (n=1; n<4 && *p; n++)
	{
		switch(*p)
		{
			case '%':
				if ( (cmd.m_arrArgs[n] & ARGTYPE_MASK) != ARGTYPE_VAR)
				{
					pError = (char*)malloc(64);
					wsprintf(pError, "Wrong argument %d(%%) in", n);
					return pError;
				}
			break;

			case '=':
				if ( (cmd.m_arrArgs[n] & ARGTYPE_MASK) == ARGTYPE_STRING)
				{
					pError = (char*)malloc(64);
					wsprintf(pError, "Wrong argument %d(=) in", n);
					return pError;
				}
			break;

			case '$':
				if ( (cmd.m_arrArgs[n] & ARGTYPE_MASK) != ARGTYPE_STRING)
				{
					pError = (char*)malloc(64);
					wsprintf(pError, "Wrong argument %d($) in", n);
					return pError;
				}
			break;

			case '*':
			break;

		}

		p++;
	}

	return NULL;
}

void CModule3::Verbose(CLgckCmd & cmd, int nLine, char *szCmd)
{
	char szTemp[32];
	*szCmd=0;

	if (m_nSize==0)
		return;

	int i;
	int n = cmd.m_arrArgs[0] & 0xffff;

	wsprintf(szTemp, "%-.4d ", nLine);
	strcat(szCmd, szTemp);

	if ((cmd.m_arrArgs[0] & CMDTYPE_MASK) &&	
		(cmd.m_arrArgs[0] & 0xffff)!= CMD_BREAK)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}

	for (; i<cmd.m_nLevel; i++)
	{
		strcat(szCmd,"    ");
	}

	char *pInst = g_arrInst[n];
	char *pPre="";

	if ((cmd.m_arrArgs[0] & CMDTYPE_MASK) == CMDTYPE_WHILEX)
	{
		pPre = "whilex ";
	}

	if ((cmd.m_arrArgs[0] & CMDTYPE_MASK)== CMDTYPE_IFX)
	{
		pPre = "ifx ";
	}

	wsprintf(szTemp, "%s%s", pPre, pInst);
	strcat(szCmd, szTemp);

	for (i=1; i<cmd.m_nArgs; i++)
	{
		n = cmd.m_arrArgs[i];
		switch( n & ARGTYPE_MASK)
		{
			case ARGTYPE_STRING:
				strcat(szCmd, " $");
				strcat(szCmd,m_arrStrings[n & 0xffff].GetName());
			break;

			case ARGTYPE_VAR:
				strcat(szCmd, " %");
				strcat(szCmd,m_arrVars[n & 0xffff].GetName());
			break;

			case 0:
				wsprintf(szTemp, " %d (0x%x)", n, n);
				strcat(szCmd,szTemp);
			break;

			default:
				strcat(szCmd, " (invalid)");
			break;
		}
	}

	strcat(szCmd, "\r\n");
}

void CModule3::SetVar(char *sz, int nValue)
{
	if (sz && *sz)
	{
		_strlwr(sz);
		int n = m_arrVars.GetIndexFor(sz);
		if (n!=-1) 
		{
			m_arrVars[n].m_nValue = nValue;
		}
		else
		{
			m_arrVars.Add(sz, nValue);
		}
	}
	else
	{
		OutputDebugString("CModule3::SetVar -- NULL or empty string\n");
	}
}

int CModule3::GetVar(char *sz)
{
	if (sz && *sz)
	{
		_strlwr(sz);
		int n = m_arrVars.GetIndexFor(sz);
		if (n!=-1) 
		{
			return m_arrVars[n].m_nValue;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		OutputDebugString("CModule3::GetVar -- NULL or empty string\n");
		return 0;
	}
}

static CLgckArr g_arr;

CLgckArr & CModule3::operator[](int n)
{
	if (n<0 || n>=m_nSize)
	{
		OutputDebugString("CModule3::operator[] -- out of bound\n");
		return g_arr;
	}
	else
	{
		return m_pData[n];
	}
}

CLgckArr & CModule3::operator[] (char *sz)
{
	BOOL bFound = FALSE;
	for (int i=0; i<m_nSize && !bFound; i++)
	{
		bFound = ! _stricmp(sz, m_pData[i].GetName());
		if (bFound)
			break;
	}

	if (bFound)
		return m_pData[i];
	else
		return g_arr;
}

int CModule3::ProcessFile(char *szFile)
{
	CFile fileS;
	if (fileS.Open(szFile, CFile::modeRead |
		CFile::typeBinary))
	{
		int nLen = fileS.GetLength();
		char *p = (char*)malloc(nLen+1);
		*(p+nLen)=0;
		fileS.Read(p, nLen);
		fileS.Close();

		char *pp = p;
		int nErrors = ProcessText(p);
		free(pp);
		return nErrors;
	}
	return -1;
}

int CModule3::ProcessText(char *p)
{
	char szTemp[MAX_STRING];
	char szTemp2[MAX_STRING];
	char szError[MAX_STRING];
	int nLevel=0;
	int nErrors=0;
	if (p)
	{	
		p = ReadLine(p, szTemp); 
		int n =1;
		while (*p || *szTemp)
		{
			Clean(szTemp);
			GetArg(szTemp, szTemp2);

			if (_stricmp(szTemp2, "function")!=0)
			{

				char *pError = ProcessString(szTemp, nLevel);
				if (pError)
				{
					wsprintf(szError, "%s line %d\r\n", pError, n);
					m_fileT.Write(szError, strlen(szError));
					free(pError);
					nErrors++;
				}
			}
			else
			{
				if (nLevel)
				{
					wsprintf(szError, "Unclosed imbrication level in function %c%s%c\r\n",
						34,m_pData[m_nSize-1].GetName(),34);
					m_fileT.Write(szError, strlen(szError));
					nErrors++;
				}

				char *pError = ProcessString("return %true", nLevel);
				if (pError)
				{
					wsprintf(szError, "%s line %d\r\n", pError, n);
					m_fileT.Write(szError, strlen(szError));
					free(pError);
					nErrors++;
				}

				char *t = GetArg(szTemp, szTemp2);
				Clean(t);
				NewArray(t);
				nLevel=0;
			}

			p = ReadLine(p, szTemp);
			n++;
		}

		char *pError = ProcessString("return %true", nLevel);
		if (pError)
		{
			wsprintf(szError, "%s line %d\r\n", pError, n);
			m_fileT.Write(szError, strlen(szError));
			free(pError);
			nErrors++;
		}

		if (nLevel)
		{
			wsprintf(szError, "Unclosed imbrication level\r\n");
			m_fileT.Write(szError, strlen(szError));
		}

		for (int i=0; i<m_nSize; i++)
		{
			Verbose(m_pData[i], m_fileT);
		}

		//fileT.Close();
		return nErrors;
	}
	else
	{
		OutputDebugString("CModule3::ProcessText-- NULL\n");
		return -1;
	}
}

void CModule3::Verbose(CLgckArr & arr, CFile & file)
{
	char szTemp[MAX_STRING];

	wsprintf(szTemp, ";\r\n;function %s\r\n;\r\n\r\n",
		arr.GetName());

	file.Write(szTemp, strlen(szTemp));

	for (int i=0; i<arr.GetSize(); i++)
	{
		Verbose(arr[i], i, szTemp);
		file.Write(szTemp, strlen(szTemp));
	}


	wsprintf(szTemp, "\r\n\r\n");
	file.Write(szTemp, strlen(szTemp));
}


void CModule3::NewArray(char *sz)
{
	if (m_nSize==m_nMax)
	{
		m_nMax = m_nMax + GROWBY;
		PTR p = (PTR) malloc(m_nMax*SIZEOF);
		memcpy(p, m_pData, m_nSize*SIZEOF);
		free(m_pData);
		m_pData =p;
	}

	m_pData[m_nSize].Init();
	m_pData[m_nSize].SetName(sz);
	m_nSize++;
}

BOOL CModule3::Run(int n, BOOL bFresh)
{
	if (n<0 || n>=m_nSize)
	{
		OutputDebugString("CModule3::Run // Out of bound index error\n");
		return 0;
	}

	//static BOOL bRunning;
	m_bRunning = bFresh;

	CLgckArr & arrCmd = m_pData[n];

	BOOL bIsVar= FALSE;
	BOOL bIsIf= FALSE;
	BOOL bIsSwitch= FALSE;
	BOOL bIsWhile=FALSE;

	BOOL bDone = FALSE;
	int nCmd =0;
	int nLevel = 0; 

	int nSize = arrCmd.GetSize();
	int i;
	int nVar1;
	int nVar2;

	int a;
	int b;

	int nResult;
	int *arr;
	char *p;

	int nLStackSize =0;
	int arrLStack[200];

	char szTemp[MAX_STRING];
	
	while (!bDone && m_bRunning)
	{	
		CLgckCmd & cmd = arrCmd[nCmd];
		arr = cmd.m_arrArgs;

		_asm
		{
			mov esi, arr
			mov eax, [esi]
			and eax, CMDTYPE_MASKX 
			or eax,eax
			jne _isIf
			mov eax, [esi]
			and eax, 0xffff
			cmp eax, CMD_IF
			je _isIf
			cmp eax, CMD_WHILE
			je _isIf
			xor eax,eax
_isIf:		mov bIsIf, eax

			mov eax, [esi]
			and eax, 0xffff
			cmp eax, CMD_SWITCH
			je _isSwitch
			xor eax,eax
_isSwitch:	mov bIsSwitch, eax

			mov eax, [esi]
			and eax, 0xffff
			cmp eax, CMD_WHILE
			je _isWhile
			and eax, CMDTYPE_MASK
			cmp eax, CMDTYPE_WHILEX
			je _isWhile
			xor eax,eax
_isWhile:	mov bIsWhile, eax

			mov eax, [esi+4]
			and eax, ARGTYPE_VAR
			mov bIsVar, eax

			mov eax, [esi+4]
			mov nVar1, eax
			and eax, 0xffff
			mov i, eax

			mov eax, [esi+8]
			mov nVar2, eax							
		}

		if(cmd.m_nLevel>nLevel)
		{
			if (bIsWhile)
			{
				arrLStack[nLStackSize] = nCmd |	CMDTYPE_MASK;
			}
			else
			{
				arrLStack[nLStackSize] = nCmd & 0xffff;
			}

			nLStackSize++;
			if (nLStackSize>=200)
			{
				OutputDebugString("CModule3::Run() // Stack overflow error\n");
				return 0;
			}
		}
		
		nLevel = cmd.m_nLevel;	
		nResult = 0;

		switch(arr[0] & 0xffff)
		{
			case CMD_CALL:
				p = m_arrStrings[i].GetName();
				i = WhoIs(p);
				if (i>=0 && i<m_nSize)
				{
					nResult = Run(i, TRUE);
				}
				else
				{
					OutputDebugString("CModule::Run cannot resolve 'Call to ...'\n");
					nResult = 0;
				}
			break;

			case CMD_GOTO:
				nCmd =0;
				while ( (nCmd < nSize) && 
					(arrCmd[nCmd].m_arrArgs[0] & 0xffff) 
					!= CMD_LABEL )
				{
					nCmd++;
				}

				nCmd--;

				if (nCmd>=m_nSize)
					return nResult;

			break;
			
			case CMD_RETURN:
				return GetVar(nVar1);
			break;

			case CMD_EXIT:
				m_bRunning=  FALSE;				
			break;

			case CMD_BREAK:
				while (nCmd<nSize && arrCmd[nCmd].m_nLevel!=0)
				{
					nCmd++;
				}
				nCmd--;
			break;

			case CMD_ELSE:
				while (nCmd<nSize && arrCmd[nCmd].m_nLevel>=nLevel)
				{
					nCmd++;
				}
				nCmd--;
			break;

			case CMD_IF:
					nResult = (GetVar(nVar1) == GetVar(nVar2));
			break;

			case CMD_XOR:
				if (bIsVar) 
				{

					a = m_arrVars[i].m_nValue;
					b = GetVar(nVar2);

					_asm
					{
						mov eax, a
						xor eax, b
						mov a, eax
					}

					nResult = m_arrVars[i].m_nValue = a;
				}
			break;		

			case CMD_MOD:
				if (bIsVar)
				{
					a = GetVar(nVar2);
					if (a)
					{
						nResult = 
							m_arrVars[i].m_nValue =
								m_arrVars[i].m_nValue % a;
					}
				}
			break;		

			case CMD_DIV:
				if (bIsVar)
				{
					a = GetVar(nVar2);
					if (a)
					{
						nResult = 
							m_arrVars[i].m_nValue =
								m_arrVars[i].m_nValue / a;
					}
				}
			break;		
			
			case CMD_SET:
				if (bIsVar)
				{
					nResult = 
						m_arrVars[i].m_nValue
							= GetVar(nVar2);
			}
			break;

			case CMD_ADD:
				if (bIsVar)
				{
					nResult = 
						m_arrVars[i].m_nValue
							+= GetVar(nVar2);
				}
			break;

			case CMD_SUB:
				if (bIsVar)
				{
					nResult = 
						m_arrVars[i].m_nValue
							-= GetVar(nVar2);
				}
			break;

			case CMD_INC:
				if (bIsVar)
				{
					nResult = m_arrVars[i].m_nValue++;
				}
			break;

			case CMD_DEC:
				if (bIsVar)
				{
					nResult = m_arrVars[i].m_nValue--;
				}
			break;

			case CMD_DEBUG:
				if (arr[1] & ARGTYPE_STRING)
				{
					OutputDebugString(
						m_arrStrings[i].m_szName);
					OutputDebugString("\r\n");
				}
				else
				{
					wsprintf(szTemp, "DEC:%d HEX:0x%x\r\n",
						GetVar(nVar1),GetVar(nVar1));
					OutputDebugString(szTemp);
				}
			break;

			case CMD_VALID:
				nResult = GetVar(nVar1);
			break;

			default:
			break;
		}

		if (bIsIf && !nResult)
		{
			nCmd = FindElse(arrCmd, nCmd, nSize);
					
		}
		else
		{
			nCmd++;
		}

		_asm
		{
			mov eax, nCmd
			cmp eax, nSize
			jae _label1
			mov bDone,0
			jmp _label2
_label1:	
			mov bDone,1
_label2:
		}

		if ( (arr[0] & 0xffff) != CMD_GOTO &&
			(bDone || arrCmd[nCmd].m_nLevel<nLevel) && 
			nLStackSize)
		{
			if (arrLStack[nLStackSize-1] & CMDTYPE_MASK)
			{
				nCmd = arrLStack[nLStackSize-1] & 0xffff;
				bDone = FALSE;
				nLStackSize--;
			}
		}
	}
	return nResult;
}

void CModule3::MakeHeader(char *szFile)
{
	if (!szFile || !*szFile)
	{
		OutputDebugString("CModule3::MakeHeader filename is null\n");
		return;
	}

	CFile file;
	BOOL bStatus = file.Open(szFile, 
		CFile::modeCreate|
		CFile::modeWrite|
		CFile::typeBinary);

	char szCmd[128];
	char szTemp[128];

	if (!bStatus)
		return;

	int i = 0;
	while (g_arrInst[i])
	{
		strcpy(szTemp, g_arrInst[i]);
		_strupr(szTemp);
		wsprintf(szCmd,"#define CMD_%.16s %d\r\n",
				szTemp, i);
		file.Write(szCmd, strlen(szCmd));
		i++;
	}

	file.Close();
}

BOOL CModule3::OutputVars(char *szFile)
{
	if (!szFile || !*szFile)
	{
		OutputDebugString("CModule3::OutputVars filename is null\n");
		return FALSE;
	}

	CFile file;

	BOOL bStatus = file.Open(szFile, 
		CFile::modeCreate|
		CFile::modeWrite|
		CFile::typeBinary);

	char szTemp[2048];

	if (!bStatus)
	{
		OutputDebugString("CModule3::Opening file failed\n");
		return FALSE;
	}

	int i = 0;
	while (i<m_arrVars.GetSize())
	{
		wsprintf(szTemp,"%4d %.16s %d\r\n",
				i, 
				m_arrVars[i].m_szName, 
				m_arrVars[i].m_nValue);
		file.Write(szTemp, strlen(szTemp));
		i++;
	}

	file.Close();
	return TRUE;
}

int CModule3::GetVar(int nVar)
{
	if (nVar & ARGTYPE_VAR)
	{
		_asm 
		{
			mov eax, nVar
			and eax, 0xffff
			mov nVar, eax
		}
		return m_arrVars[nVar].m_nValue;
	}
	else
	{
		_asm 
		{
			mov eax, nVar
			and eax, 0xffff
			mov nVar, eax
		}
		return nVar;
	}
}

int CModule3::FindElse(CLgckArr & arr, int i, int nSize)
{
	int nLevel = arr[i].m_nLevel;
	BOOL bFound = FALSE;

	while (i<nSize && !bFound && arr[i].m_nLevel>=nLevel)
	{
		CLgckCmd & cmd = arr[i];
		bFound = ((cmd.m_arrArgs[0] & 0xffff)==CMD_ELSE)
			&& (cmd.m_nLevel == nLevel);

		i++;
	}

	return i;
}

int CModule3::WhoIs(char *sz)
{
	if (!sz && !*sz)
	{
		OutputDebugString("CModule3::WhoIs received NULL\n");
		return -1;
	}

	int i;

	for (i=0; i<m_nSize; i++)
	{
		if (stricmp(m_pData[i].GetName(), sz)==0)
		{
			return i;
		}
	}

	return -1;
}

int CModule3::Run(char *sz)
{
	int i = WhoIs(sz); 
	if (i == -1)
	{
		OutputDebugString("CModule3::Run(char*) function not found\n");
		return 0;
	}
	else
	{
		return Run(i, TRUE);
	}

}

void CModule3::CompileToAsm()
{
	int i;
	int n;
	
	int nOffset =0;
	int nSize =0;

	char szTemp[256];

	for (i=0; i<m_nSize; i++)
	{
		CLgckArr & arr = m_pData[i];
		for (n=0; n<arr.GetSize(); n++)
		{
			arr[n].m_nOffset = nSize;
			nSize = nSize + 
				ComputeEncode(arr[n], szTemp, n+1);	
		}
	}
}

int CModule3::GetHex(char nChar)
{
	int nTemp =0;

	if ( (nChar>='0') && (nChar<='9'))
	{
		nTemp = nTemp + nChar - '0';
	}

	if ( (nChar>='a') && (nChar<='f'))
	{
		nTemp = nTemp + nChar - 'a' + 10;
	}

	if ( (nChar>='A') && (nChar<='Z'))
	{
		nTemp = nTemp + nChar - 'A' +10;
	}

	return nTemp;
}

#define IsVar(n) if (n & VARTYPE_VAR)

int CModule3::ComputeEncode(CLgckCmd & cmd, char *pBuf, int nLine)
{
	int nSize = 0;
	int nTemp = 0;

	char szTemp[128];
	Verbose(cmd, nLine, szTemp);
	m_fileT.Write(szTemp, strlen(szTemp));

	switch(cmd.m_arrArgs[0] & 0xffff)
	{
		case CMD_ADD:
			switch(cmd.m_arrArgs[2] & CMDTYPE_MASK)
			{
				case ARGTYPE_VAR:
					 nSize = nSize +
						 MiniAsm("mov eax, [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);

					 nSize = nSize +
						 MiniAsm("add eax, [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[2], nTemp);

					 
					 nSize = nSize +
						 MiniAsm("mov [0000], eax", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);
				break;

				case ARGTYPE_CONST:
					 nSize = nSize +
						 MiniAsm("mov eax, [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);

					 nSize = nSize +
						 MiniAsm("add eax, 0000", 
							pBuf + nSize,
							cmd.m_arrArgs[2], nTemp);
				 
					 nSize = nSize +
						 MiniAsm("mov [0000], eax", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);
				break;
			}
		break; // CMD_ADD

		case CMD_DEC:
			 nSize = nSize +
				 MiniAsm("mov eax, [0000]", 
					pBuf + nSize,
					cmd.m_arrArgs[1], nTemp);

			 nTemp = 0xffff;
			 nSize = nSize +
				 MiniAsm("add eax, 0000", 
					pBuf + nSize,
					nTemp, nTemp);
		 
			 nSize = nSize +
				 MiniAsm("mov [0000], eax", 
					pBuf + nSize,
					cmd.m_arrArgs[1], nTemp);
		break; // CMD_DEC

		case CMD_DIV:
			switch(cmd.m_arrArgs[2] & CMDTYPE_MASK)
			{
				case ARGTYPE_VAR:
					 nSize = nSize +
						 MiniAsm("xor edx, edx", 
							pBuf + nSize,
							nTemp, nTemp);

					 nSize = nSize +
						 MiniAsm("mov eax, [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);

					 nSize = nSize +
						 MiniAsm("div [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[2], nTemp);

					 nSize = nSize +
						 MiniAsm("mov [0000], eax", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);			 
				break;
			}
		break;

		case CMD_INC:
			 nSize = nSize +
				 MiniAsm("mov eax, [0000]", 
					pBuf + nSize,
					cmd.m_arrArgs[1], nTemp);

			 nTemp = 1;
			 nSize = nSize +
				 MiniAsm("add eax, 0000", 
					pBuf + nSize,
					nTemp, nTemp);
		 
			 nSize = nSize +
				 MiniAsm("mov [0000], eax", 
					pBuf + nSize,
					cmd.m_arrArgs[1], nTemp);
		break; // CMD_INC


		case CMD_MOD:
			switch(cmd.m_arrArgs[2] & CMDTYPE_MASK)
			{
				case ARGTYPE_VAR:
					 nSize = nSize +
						 MiniAsm("xor edx, edx", 
							pBuf + nSize,
							nTemp, nTemp);

					 nSize = nSize +
						 MiniAsm("mov eax, [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);

					 nSize = nSize +
						 MiniAsm("div [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[2], nTemp);

					 nSize = nSize +
						 MiniAsm("mov edx, eax", 
							pBuf + nSize,
							nTemp, nTemp);

					 nSize = nSize +
						 MiniAsm("mov [0000], edx", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);			 
				break;
			}
		break;

		case CMD_RETURN:
			switch(cmd.m_arrArgs[1] & CMDTYPE_MASK)
			{
				case ARGTYPE_VAR:
					 nSize = nSize +
						 MiniAsm("mov eax, [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);
					 nSize = nSize +
						 MiniAsm("ret", 
							pBuf + nSize,
							nTemp, nTemp);
				break;

				case ARGTYPE_CONST:
					 nSize = nSize +
						 MiniAsm("mov eax, 0000", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);

					 nSize = nSize +
						 MiniAsm("ret", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);

				break;
			}
		break; // CMD_RETURN
	
		case CMD_SET:
			switch(cmd.m_arrArgs[2] & CMDTYPE_MASK)
			{
				case ARGTYPE_VAR:
					 nSize = nSize +
						 MiniAsm("mov eax, [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[2], nTemp);

					 nSize = nSize +
						 MiniAsm("mov [0000], eax", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);
			 
				break;

				case ARGTYPE_CONST:
					 nSize = nSize +
						 MiniAsm("mov eax, 0000", 
							pBuf + nSize,
							cmd.m_arrArgs[2], nTemp);

					 nSize = nSize +
						 MiniAsm("mov [0000], eax", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);
				break;
			}
		break; // CMD_SET

		case CMD_XOR:
			switch(cmd.m_arrArgs[2] & CMDTYPE_MASK)
			{
				case ARGTYPE_VAR:
					 nSize = nSize +
						 MiniAsm("mov eax, [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);

					 nSize = nSize +
						 MiniAsm("xor eax, [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[2], nTemp);

					 
					 nSize = nSize +
						 MiniAsm("mov [0000], eax", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);
				break;

				case ARGTYPE_CONST:
					 nSize = nSize +
						 MiniAsm("mov eax, [0000]", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);

					 nSize = nSize +
						 MiniAsm("xor eax, 0000", 
							pBuf + nSize,
							cmd.m_arrArgs[2], nTemp);
				 
					 nSize = nSize +
						 MiniAsm("mov [0000], eax", 
							pBuf + nSize,
							cmd.m_arrArgs[1], nTemp);
				break;
			}
		break; // CMD_XOR

	}
	return nSize;
}

VALCODE g_arrOp[]= // & 0x38
{
	0x0, "eax",
	0x8, "ecx",
	0x10,"edx",
	0x18,"ebx",
	0x20,"esp",
	0x28,"ebp",
	0x30,"esi",
	0x38,"edi",
	NULL, NULL
};

VALCODE g_arrMem[]= // & 0x7
{
	0x0, "[eax]",
	0x1, "[ecx]",
	0x2, "[edx]",
	0x3, "[ebx]",
	0x4, "[--][--]",
	0x5, "[0000]",
	0x6, "[esi]",
	0x7, "[edi]",
	NULL, NULL
};

#define ASM_MEM_OP		0
#define ASM_MEM_IMM		1	
#define ASM_OP_MEM		2
#define ASM_OP_IMM		3
#define ASM_NOTHING		4
#define ASM_SEQ			5
#define ASM_MEM_IMM_SEQ 6
#define ASM_OP_IMM_SEQ	7
#define ASM_MEM_SEQ		8
#define ASM_OP_OP_SEQ	9

VALCODE3 g_arrAsm[]=
{
	0x31, 0xc0, "xor", "ee", ASM_OP_OP_SEQ,		// xor eax, eax
	0x8b, 0xc0, "mov", "ee", ASM_OP_OP_SEQ,		// mov eax, eax
	
	0x89, 0, "mov", "[e",	ASM_MEM_OP,			// mov [eax], eax
	0x8b, 0, "mov", "e[",	ASM_OP_MEM,			// mov eax, [eax]
	0xb8, 0, "mov", "e0",	ASM_OP_IMM,			// mov eax, 0000
	0xc7, 0, "mov", "[0",	ASM_MEM_IMM,		// mov [eax], 0000
	0xc3, 0, "ret", "",		ASM_NOTHING,		// ret
	0x58, 0, "pop", "e",	ASM_SEQ,			// pop eax
	0x68, 0, "push","e",	ASM_SEQ,			// push eax

	0x35, 0,	"xor", "e0", ASM_OP_IMM,		// xor eax,	  0000
	0x81, 0x00, "add", "[0", ASM_MEM_IMM_SEQ,	// add [eax], 0000
	0x81, 0x08, "or",  "[0", ASM_MEM_IMM_SEQ,	// or [eax],  0000
	0x81, 0x10, "adc", "[0", ASM_MEM_IMM_SEQ,	// adc [eax], 0000
	0x81, 0x18, "sbb", "[0", ASM_MEM_IMM_SEQ,	// sbb [eax], 0000
	0x81, 0x20, "and", "[0", ASM_MEM_IMM_SEQ,	// and [eax], 0000
	0x81, 0x28, "sub", "[0", ASM_MEM_IMM_SEQ,	// sub [eax], 0000
	0x81, 0x30, "xor", "[0", ASM_MEM_IMM_SEQ,	// xor [eax], 0000
	0x81, 0x38, "cmp", "[0", ASM_MEM_IMM_SEQ,	// cmp [eax], 0000

	0x81, 0xc0, "add", "e0", ASM_OP_IMM_SEQ,	// add eax, 0000
	0x81, 0xc8, "or", "e0",	 ASM_OP_IMM_SEQ,	// or eax,  0000
	0x81, 0xd0, "adc", "e0", ASM_OP_IMM_SEQ,	// adc eax, 0000
	0x81, 0xd8, "sbb", "e0", ASM_OP_IMM_SEQ,	// sbb eax, 0000
	0x81, 0xe0, "and", "e0", ASM_OP_IMM_SEQ,	// and eax, 0000
	0x81, 0xe8, "sub", "e0", ASM_OP_IMM_SEQ,	// sub eax, 0000
	0x81, 0xf0, "xor", "e0", ASM_OP_IMM_SEQ,	// xor eax, 0000
	0x81, 0xf8, "cmp", "e0", ASM_OP_IMM_SEQ,	// cmp eax, 0000

	0x03, 0, "add", "e[",	ASM_OP_MEM,			// add eax, [eax]

	0xf7, 0x00, "test", "[0", ASM_MEM_IMM_SEQ,	// test [eax], 0000
	0xf7, 0x10, "not", "[", ASM_MEM_SEQ,		// not [eax]
	0xf7, 0x18, "neg", "[", ASM_MEM_SEQ,		// neg [eax]
	0xf7, 0x20, "mul", "[", ASM_MEM_SEQ,		// mul [eax]
	0xf7, 0x28, "imul", "[", ASM_MEM_SEQ,		// imul [eax]
	0xf7, 0x30, "div", "[", ASM_MEM_SEQ,		// div [eax]
	0xf7, 0x38, "idiv", "[", ASM_MEM_SEQ,		// idiv [eax]

	NULL, NULL, NULL, NULL, NULL
};

int CModule3::MiniAsm(char *szSource, char *pDest, int & nValue, int & nValue2)
{
	int nSize = 0;

	char *t = pDest;

	char* p = szSource;
	while (*p)
	{
		if (*p == ',')
			*p = 32;
		p++;
	};

	p = szSource;

	char arrArgs[3][10];
	arrArgs[0][0] =0;
	arrArgs[1][0] =0;
	arrArgs[2][0] =0;

	for (int i=0; i< 3; i++)
	{
		p = GetArg(p, arrArgs[i]);
	}

	char szEnc[3];
	szEnc[0] = arrArgs[1][0];
	szEnc[1] = arrArgs[2][0];
	szEnc[2] = 0;

	int n = GetIndexFor(g_arrAsm, 
		arrArgs[0], 
		szEnc); 

	if (n==-1)
	{
		char szTemp[128];
		wsprintf(szTemp, "CModule3::MiniAsm wrong ASM '%s' + '%s' not handled\n",
			arrArgs[0], szEnc);
		OutputDebugString(szTemp);
		return 0;
	}

	int i1;
	int i2;

	int nExtra = GetReal32(nValue);
	int nExtra2 = GetReal32(nValue);

	switch(g_arrAsm[n].m_nOpType)
	{
		case ASM_MEM_OP:
			i1 = GetIndexFor(g_arrMem, arrArgs[1]);
			i2 = GetIndexFor(g_arrOp, arrArgs[2]);

			pDest[0] = g_arrAsm[n].m_nOp;
			pDest[1] = (char) (i1+i2);
			nSize=2;

			if (i1 == 5)
			{
				memcpy(pDest+2, &nExtra, 4);
				nSize=nSize+4;
			}	
		break; // ASM_MEM_OP

		case ASM_MEM_IMM:
			i1 = GetIndexFor(g_arrMem, arrArgs[1]);							   
			//i2 = GetIndexFor(g_arrOp, arrArgs[2]);

			pDest[0] = g_arrAsm[n].m_nOp;
			pDest[1] = (char) (i1);
			nSize = 2;
				   
			memcpy(pDest+2, &nExtra, 4);
			nSize = nSize + 4;
		break; // ASM_MEM_IMM

		case ASM_OP_MEM:
			i1 = GetIndexFor(g_arrOp, arrArgs[1]);
			i2 = GetIndexFor(g_arrMem, arrArgs[2]);

			pDest[0] = g_arrAsm[n].m_nOp;
			pDest[1] = (char) (i1+i2);
			nSize=2;
			if (i2 == 5)
			{	memcpy(pDest+2, &nExtra, 4);
				nSize=nSize+4;
			}
		break; // ASM_OP_MEM

		case ASM_OP_IMM:
			i1 = GetIndexFor(g_arrOp, arrArgs[1]);
			//i2 = GetIndexFor(g_arrOp, arrArgs[2]);

			pDest[0] = g_arrAsm[n].m_nOp + i1;
			//pDest[1] = (char) (i1);
			nSize = 1;

			memcpy(pDest+1, &nExtra, 4);
			nSize = nSize + 4;
		break; // ASM_OP_IMM

		case ASM_NOTHING:
			pDest[0] = g_arrAsm[n].m_nOp ;
			nSize = 1;
		break; // ASM_NOTHING

		case ASM_SEQ:
			i1 = GetIndexFor(g_arrOp, arrArgs[1]);
			pDest[0] = g_arrAsm[n].m_nOp +i1;
			nSize = 1;

			memcpy(pDest+1, &nExtra, 4);
			nSize = nSize + 4;
		break; // ASM_SEQ

		case ASM_MEM_IMM_SEQ:
			i1 = GetIndexFor(g_arrMem, arrArgs[1]);
			pDest[0] = g_arrAsm[n].m_nOp;
			pDest[1] = g_arrAsm[n].m_nOp2 +i1;
			nSize=2;

			if (i1==5)
			{
				memcpy(pDest+nSize, &nExtra, 4);
				nSize=nSize+4;
				memcpy(pDest+nSize, &nExtra2, 4);
				nSize=nSize+4;
			}
			else
			{
				memcpy(pDest+nSize, &nExtra, 4);
				nSize=nSize+4;
			}
		break; // ASM_MEM_IMM_SEQ

		case ASM_OP_IMM_SEQ:
			i1 = GetIndexFor(g_arrOp, arrArgs[1]);
			pDest[0] = g_arrAsm[n].m_nOp;
			pDest[1] = g_arrAsm[n].m_nOp2 +i1;
			nSize=2;

			memcpy(pDest+nSize, &nExtra, 4);
			nSize = nSize + 4;
		break; // ASM_OP_IMM_SEQ

		case ASM_MEM_SEQ:
			i1 = GetIndexFor(g_arrMem, arrArgs[1]);
			pDest[0] = g_arrAsm[n].m_nOp;
			pDest[1] = g_arrAsm[n].m_nOp2 +i1;
			nSize=2;

			if (i1==5)
			{
				memcpy(pDest+nSize, &nExtra, 4);
				nSize = nSize + 4;
			}
		break;	// ASM_MEM_SEQ

		case ASM_OP_OP_SEQ:
			i1 = GetIndexFor(g_arrOp, arrArgs[1]);
			i2 = GetIndexFor(g_arrOp, arrArgs[2]);

			pDest[0] = g_arrAsm[n].m_nOp;
			pDest[1] = g_arrAsm[n].m_nOp2 +i2+i1*8;
			nSize=2;
		break;

		default:
			OutputDebugString("CModule3::MiniAsm illegal ASM type\n");
		return 0; // default
	}

	char szTemp[128]="--> ";

	GenOpCode((BYTE*)t, (unsigned)t, szTemp+4, FALSE);
	strcat(szTemp, "\r\n");
	m_fileT.Write(szTemp, strlen(szTemp));

	return nSize;
}

int CModule3::GetReal32(int n)
{
	int nArgType = n & ARGTYPE_MASK;

	n = n  & 0xffff;

	switch(nArgType)
	{
		case ARGTYPE_VAR:
			return (int)(&m_arrVars[n].m_nValue);
		break;

		case ARGTYPE_STRING:
			return (int)(m_arrStrings[n].m_szName);
		break;

		case ARGTYPE_CONST:
			if (n & 0x8000)
			{
				return n | 0xffff0000;
			}
			else
			{
				return n ;
			}
		break;

		// unhandled types
		default:
			OutputDebugString("CModule3::GetReal32(n) n is not a valid expression\n");
			return 0;
	}
}
