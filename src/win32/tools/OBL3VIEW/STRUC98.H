

// STRUCT.H

#ifndef _STRUCT_H
#define _STRUCT_H
#include <windows.h>

#define begin_struct typedef struct {
#define end_struct(_struct) } _struct;  
#define uchar unsigned char
#define uint unsigned int

// ***   STRUCTURES  ***

begin_struct
    HICON hIcon;
    char szText[1024];
end_struct(USER_ICONTEXT);


typedef struct  
{
 DWORD last_x;
 DWORD last_y;
 DWORD x;
 DWORD y;
 DWORD button;
 BYTE  bColor;
} USER_MOUSE;

typedef struct
{
   unsigned char red;
   unsigned char green;
   unsigned char blue;
} USER_WINPAL;

begin_struct
    uchar blue;
    uchar green;
    uchar red;
end_struct(USER_24bpp);

begin_struct
    uchar blue;
    uchar green;
    uchar red;
    uchar reserved;
end_struct(USER_32bpp);


begin_struct 
    int x;
    int y;
    BYTE bOldColor;
end_struct(USER_DOT);

#endif

