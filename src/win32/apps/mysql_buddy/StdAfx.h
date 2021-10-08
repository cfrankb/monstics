// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>
#include <afxdisp.h>        // MFC OLE automation classes

#include "mysql.h"
#include "global.h"
#include "file.h"

#define WM_UTABLESORDERCHANGED (WM_USER+2)
#define WM_UTABLENAMECHANGED (WM_USER+3)
#define WM_UTABLEREPOPULATE (WM_USER+4)
#define WM_UTABLETERMINATE (WM_USER+5)

