// common.cpp
//

#include "stdafx.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *GetArg(char *szSource, char *szArg)
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

int str2int(char *sz)
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

char * ReadLine(char * pBuf, char *szLine)
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
