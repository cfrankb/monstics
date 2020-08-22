// common.h
//

#ifndef _COMMON_H
#define _COMMON_H

#define MAX_STRING 2048

#define WM_USER_SET_STATUS (WM_USER+16)

char *GetArg(char *szSource, char *szArg);
int str2int(char *sz);
char * ReadLine(char * pBuf, char *szLine);

#endif