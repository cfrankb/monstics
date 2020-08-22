// file.cpp : implementation file
//

#include "stdafx.h"
#include "file.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFile & operator >> (CFile & file, int & n)
{
	file.Read (&n, 4);
	return file;
}

CFile & operator << (CFile & file, int n)
{
	file.Write (&n, 4);
	return file;
}

CFile & operator >> (CFile & file, CString & str)
{

	int x=0;
	file.Read (&x, 1);
	if (x==0xff) {
		file.Read (&x, 2);
	}
	
	if (x!=0)
	{
		char *sz = (char*)malloc (x+1);
		ZeroMemory (sz,x+1);
		file.Read (sz, x);
		str = CString(sz);
		free (sz);
	}
	else {
		str = "";
	}

	return file;
}

CFile & operator << (CFile & file, CString & str)
{

	int x = str.GetLength();
	if (x<=0xfe) {
		file.Write (&x, 1);
	}
	else {
		int t=0xff;
		file.Write (&t, 1);
		file.Write (&x, 2);
	}

	if (x!=0)
		file.Write(str.GetBuffer(1), x);
	

	return file;
}

