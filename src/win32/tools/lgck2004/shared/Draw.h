
#ifndef _DRAW_H
#define _DRAW_H

#include <windows.h>

#define begin_struct typedef struct {
#define end_struct(_struct) } _struct;  

begin_struct 
   unsigned char red;
   unsigned char green;
   unsigned char blue;
end_struct(USER_WINPAL);

begin_struct 
    UCHAR blue;
    UCHAR green;
    UCHAR red;
end_struct(USER_24bpp);

begin_struct
    UCHAR blue;
    UCHAR green;
    UCHAR red;
    UCHAR reserved;
end_struct(USER_32bpp);

begin_struct
	UCHAR m_nBkClass;
	UCHAR m_nFwClass;
	UCHAR m_nAcClass;
	UCHAR m_bPlayer;
	short m_nFwEntry;
	short m_nAcEntry;
end_struct(USER_MapEntry);

#endif