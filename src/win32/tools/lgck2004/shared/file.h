// file.h : header file
//

#include "stdafx.h"

CFile & operator >> (CFile & file, CString & str);
CFile & operator << (CFile & file, CString & str);

CFile & operator >> (CFile & file, int & n);
CFile & operator << (CFile & file, int n);
