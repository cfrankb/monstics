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

#include <afxdisp.h>
#include <afxcview.h>

#define WM_PREPARE_NEW_CHILD (WM_USER+100)
#define WM_ADD_PROGRAM       (WM_USER+101)
//#define WM_FILL_CHILD        (WM_USER+102)
#define WM_RESTORE_RECT      (WM_USER+103)
#define WM_SAVE_RECT         (WM_USER+104)

#define ACTION_CREATE       0
#define ACTION_LOAD         1
#define ACTION_SAVE         2
#define ACTION_DESTROY      3
#define ACTION_SET_INFO     4
#define ACTION_GET_INFO     5

typedef struct
{
    char m_szTitle[32];
    char m_szPath[_MAX_PATH];
    BOOL m_bModified;
    BOOL m_nAction;
} CHILD_INFO;

