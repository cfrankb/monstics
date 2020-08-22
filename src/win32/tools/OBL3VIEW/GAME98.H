
//
// Game98.h
//
// Static Systen V3.x defined constants & structures
// (c) 1998 Francois Blanchette


#include "struc98.h"

#ifndef _GAME98_H
#define _GAME98_H

#define CAA_STAND   0
#define CAA_KILLED  1
#define CAA_HURT    2
#define CAA_REBIRTH 3
#define CAA_UP      4
#define CAA_DOWN    5
#define CAA_LEFT    6
#define CAA_RIGHT   7
#define CAA_JUMPUP  8
#define CAA_FALL    9
#define CAA_JUMPLF  0xa
#define CAA_JUMPRG  0xb
#define CAA_UNUSED  0xc

#define DAA_NOTHING 0x0
#define DAA_STAND   0x1
#define DAA_KILLED  0x2
#define DAA_HURT    0x4
#define DAA_REBIRTH 0x8
#define DAA_UP      0x10
#define DAA_DOWN    0x20
#define DAA_LEFT    0x40
#define DAA_RIGHT   0x80
#define DAA_JUMPUP  0x100
#define DAA_FALL    0x200
#define DAA_JUMPLF  0x400
#define DAA_JUMPRG  0x800
#define DAA_UNUSED  0x1000

#define SPA_NOTHING 0x0
#define SPA_MOVEUP  0x1
#define SPA_MOVEDN  0x2
#define SPA_MOVELF  0x4
#define SPA_MOVERG  0x8
#define SPA_FIRE    0x10
#define SPA_JUMPSIDE 0x20
#define SPA_JUMPUP  0x40
#define SPA_FALL    0x80

#define CEV_WHENTOUCHED     0x0
#define CEV_WHENZPRESSED    0x1
#define CEV_WHENTRIGGERCALL 0x2
#define CEV_WHENHURT        0x3
#define CEV_WHENKILLED      0x4
#define CEV_WHENREBORN      0x5
#define CEV_WHENUSED        0x6
#define CEV_WHENTIMER       0x7
#define CEV_WHENREACHINGPLAYER 0x8

#define DEV_WHENTOUCHED     0x1
#define DEV_WHENZPRESSED    0x2
#define DEV_WHENTRIGGERCALL 0x4
#define DEV_WHENHURT        0x8
#define DEV_WHENKILLED      0x10
#define DEV_WHENREBORN      0x20
#define DEV_WHENUSED        0x40
#define DEV_WHENTIMER       0x80
#define DEV_WHENREACHINGPLAYER 0x100

#define ILI_DOOR            0
#define ILI_NOTE            1
#define ILI_DIAMOND         2
#define ILI_CLOSED_FOLDER   3
#define ILI_OPEN_FOLDER     4

#define ILI_TREE            5
#define ILI_MUSICNOTE       6
#define ILI_SOUND           7
#define ILI_SYSTEM          8

#define ILI_CREATURE        9
#define ILI_PLAYER          10
#define ILI_BULLET          11
#define ILI_PLATFORM        12

#define ILI_DUMMY           13
#define ILI_DRONE           14
#define ILI_COS10           15
#define ILI_COMPUTER        16

begin_struct
    UINT    m_nValue;
    char * m_szText;
end_struct(USER_TEXTINFO)

begin_struct
    CString m_strName;
    UINT    m_nAniSpeed;
    UINT    m_nMoveSpeed;
    CUIntArray m_arrFrames;
end_struct(USER_ANISEQ);

extern USER_TEXTINFO ObjClasses[];
extern USER_TEXTINFO ObjAttribs[];
extern USER_TEXTINFO FireRate[];
extern USER_TEXTINFO FireAim[];

int GetTabItemVal(USER_TEXTINFO p_tab[], char *p_szItem);
char *GetTabItemText(USER_TEXTINFO p_tab[], UINT p_nVal);

#endif