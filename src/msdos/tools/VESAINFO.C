/*
	PROGRAMME: VESAINFO.C
	AUTEUR   : FRANCOIS BLANCHETTE
	BUT      : AFFICHER DES INFORMATIONS CONCERNANT VOTRE CARTE
			   VESA/SVGA.

*/
#include <user\friendly.h>
#include <stdlib.h>

void showcopyright()
{
	puts("\nVESAINFO v1.0 (01/01/96)\n (c) 1996 Francois Blanchette, all rights reserved.");
	puts("\nFREEWARE may be distributed if not modified in any way.");
}
typedef struct
{
   unsigned char al;
   unsigned char ah;
} STATUS;

#define SAVE asm{push di; push es}
#define RESTORE asm{pop es; pop di}

/*6.1 int information
----------------------

Every function returns int information in the AX register.  The format
of the int word is as follows:

	AL == 4Fh: Function is supported
	AL != 4Fh: Function is not supported
	AH == 00h: Function call successful
	AH == 01h: Function call failed

Software should treat a nonzero value in the AH register as a general
failure condition.  In later versions of the VESA BIOS Extension new
error codes might be defined.

6.2 Function 00h - Return Super VGA Information
-----------------------------------------------

The purpose of this function is to provide information to the calling
program about the general capabilities of the Super VGA environment.  The
function fills an information block structure at the address specified by
the caller.  The information block size is 256 bytes.

	Entry:	AH = 4Fh: Super VGA support
		AL = 00h: Return Super VGA Information
		ES:DI   : Pointer to buffer

	Exit:	AX	:int

The information block has the following structure:

VgaInfoBlock	struc
 VESASignature	db 'VESA'	;4 signature bytes
 VESAVersion	dw ?		;VESA version number
 OEMStringPtr	dd ?		;Pointer to OEM string
 Capabilities	db 4 dup (?)	;capabilities of the video environment
 VideoModePtr	dd ?		;pointer to supported Super VGA modes
VgaInfoBlock	ends

The VESASignature field contains the characters 'VESA' if this is a valid block.

The VESAVersion field specifies which VESA standard the Super VGA BIOS
conforms to.  The higher byte would specify the major version number.
The lower byte specify the minor version number.  The initial VESA
version number is 1.0.  Applications written to use the features of the
specific version of the VESA BIOS Extension, is guaranteed to work in
later versions.  The VESA BIOS Extension will be fully upwards compatible.

The OEMStringPtr is a far pointer to a null terminated OEM-defined
string.  The string may be used to identify the video chip, video board,
memory configuration, etc., to hardware specific display drivers.  There
are no restrictions on the format of the string.

The Capabilities field describes what general features are supported in
the video environment.  The bits are defined as follows:

	D0-D31 = Reserved (=0)

The VideoModePtr points to a list of supported Super VGA (VESA-defined
as well as OEM-specific) mode numbers.  Each mode number occupies one
word (16 bits).  The list of mode numbers is terminated by a -1 (FFFFh).
Please refer to chapter 2 for a description of VESA mode numbers.  The
pointer could point into either ROM or RAM, depending on the specific
implementation.  Either the list would be a static string stored in ROM,
or the list would be generated at run-time in the information block (see
above) in RAM. */


/*	Entry:	AH = 4Fh: Super VGA support
		AL = 00h: Return Super VGA Information
		ES:DI   : Pointer to buffer

	Exit:	AX	:int

The information block has the following structure:

VgaInfoBlock	struc
 VESASignature	db 'VESA'	;4 signature bytes
 VESAVersion	dw ?		;VESA version number
 OEMStringPtr	dd ?		;Pointer to OEM string
 Capabilities	db 4 dup (?)	;capabilities of the video environment
 VideoModePtr	dd ?		;pointer to supported Super VGA modes
VgaInfoBlock	ends*/

typedef struct
{
	unsigned char VESASignature[4];
	unsigned int VESAVersion;
	unsigned char far*OEMStringPtr;
	unsigned int Capabilities[4];
	unsigned int far* VideoModePtr;
} VGAINFOBLOCK;

int ss_returnsvgainfo(VGAINFOBLOCK  *buffer)
{
	int retour;
	SAVE;
	asm { les di, buffer
		  mov al,0
		  mov ah,0x4f
		  int 0x10
		  mov &retour, ax
		}
	RESTORE;
	return(retour);
}

/*6.3 Function 01h - Return Super VGA Mode Information
----------------------------------------------------

This function returns information about a specific Super VGA video mode.
The function fills a mode information block structure at the address
specified by the caller.  The mode information block is maximum 256 bytes.

Some information provided by this function is implicitly defined by the
VESA mode number.  However, some Super VGA implementations might support
other video modes than those defined by VESA.  To provide access to these
modes, this function also returns various other information about the mode.

	Entry:	AH = 4Fh: Super VGA support
		AL = 01h: Return Super VGA Mode Information
		CX =	: Super VGA video mode
		ES:DI   : Pointer to buffer

	Exit:	AX	:int

The mode information block has the following structure:

ModeInfoBlock	struc
 ;mandatory information
 ModeAttributes		dw ?		;mode attributes
 WinAAttributes		db ?		;Window A attributes
 WinBAttributes		db ?		;Window B attributes
 WinGranularity		dw ?		;window granularity
 WinSize		dw ?		;window size
 WinASegment		dw ?		;Window A start segment
 WinBSegment		dw ?		;Window B start segment
 WinFuncPtr		dd ?		;pointer to window function
 BytesPerScanLine	dw ?		;bytes per scan line

 ;extended information
 ;optional information
 XResolution		dw ?		;horizontal resolution
 YResolution		dw ?		;vertical resolution
 XCharSize		db ?		;character cell width
 YCharSize		db ?		;character cell height
 NumberOfPlanes		db ?		;number of memory planes
 BitsPerPixel		db ?		;bits per pixel
 NumberOfBanks		db ?		;number of banks
 MemoryModel		db ?		;memory model type
 BankSize		db ?		;bank size in K
ModeInfoBlock	ends

The Mode Attributes field describes certain important characteristics of
the video mode.  Bit D0 specifies whether this mode can be initialized in
the present video configuration.  This bit can be used to block access to
a video mode if it requires a certain monitor type, and that this monitor
is presently not connected.  Bit D1 specifies whether extended mode
information is available.  Video modes defined by VESA will have certain
known characteristics, like resolution, number of planes, pixel format,
etc.  Doe to the severe space constraint for ROM-based implementations of
the VESA BIOS Extension, this information need not be given for
VESA-defined video modes.  Bit D2 indicates whether the BIOS has support
for output functions like TTY output, scroll, pixel output, etc. in this
mode (it is recommended, but not mandatory, that the BIOS have support
for all output functions.)

The field is defined as follows:

	D0 = Mode supported in hardware
		0=Mode not supported in hardware
		1=Mode supported in hardware
	D1 = Extended information available
		0=Extended mode information not available
		1=Extended mode information available
	D2 = Output functions supported by BIOS
		0=Output functions not supported by BIOS
		1=Output functions supported by BIOS
	D3 = Monochrome/color mode (see note below)
		0=Monochrome mode
		1=Color mode
	D4 = Mode type
		0=Text mode
		1=Graphics mode
	D5-D15 = Reserved (=0)

Note:  Monochrome modes have their CRTC address at 3B4h.  Color modes
have their CRTC address at 3D4h.  Monochrome modes have attributes in
which only bit 3 (video) and bit 4 (intensity) of the attribute
controller output are significant.  Therefore, monochrome text modes have
attributes of off, video, high intensity, blink, etc.  Monochrome
graphics modes are two plane graphics modes and have attributes of off,
video , high intensity, and blink.  Extended two color modes that have
their CRTC address at 3D4h, are color modes with one bit per pixel and
one plane.  The standard VGA modes, 06h and 11h would be classified as
color modes, while the standard VGA modes 07h and 0Fh would be classified
as monochrome modes.

The BytesPerScanLine field specifies how many bytes each logical scanline
consists of.  The logical scanline could be equal to or larger than the
displayed scanline.

The WinAAttributes and WinBAttributes  describe the characteristics of
the CPU windowing scheme such as whether the windows exist and are
read/writable, as follows:

	D0 = Window supported
		0=Window is not supported
		1=Window is supported
	D1 = Window readable
		0=Window is not readable
		1=Window is readable
	D2 = Window writable
		0=Window is not writable
		1=Window is writable
	D3-D7 = Reserved (=0)

WinGranularity specifies the smallest boundary, in KB, on which the
window can be placed in the video memory.

WinSize specifies the size of the window in KB.

WinASegment and WinBSegment address specify the segment addresses where
the windows are located in the CPU address space.

WinFuncPtr specifies the address of the CPU vide memory windowing
function.  The windowing function can be invoked either through VESA BIOS
Function 05h, or by calling the function directly.  A direct call will
provide faster access to the hardware paging registers the using INT 10h,
and is intended to be used by high performance applications.

The XResolution and YResolution specify the width and height of the video
mode.  In graphics modes, this resolution is in unites of pixels,  In
text modes this resolution is in unites of characters.  Note that text
mode resolutions, in units of pixels, can be obtained by multiplying
XResolution and YResolution by the cell width and height, if the extended
information is present.

The XCharSize and YCharSize specify the size of the character cell in
pixels.

The NumberOfPlanes field specifies the number of bits that define the
color of one pixel.  16-color and 256-color graphics modes would specify
4 and 8 respectively.  Nonstandard memory organizations can be specified
using this field and the NumberOfPlanes field.  For example, 1 16-color
packed pixel mode would be described as having 1 plane and 4 bits per
pixel.

The MemoryModel field specifies the general type of memory organization
used in this mode.  The following models have been defined:

	00h = Text mode
	01h = CGA graphics
	02h = Hercules graphics
	03h = 4-plane planar
	04h = Packed pixel
	05h = Non-chain 4, 256 color
	06h-0Fh = Reserved, to be defined by VESA
	10h-FFh = To be defined by OEM

NumberOfBanks defines the number of banks in which the scan lines are
grouped.  The remainder from dividing the scan line number by the number
of banks is the bank that contains the scan line and the quotient is the
scan line number within the bank.  For example, CGA graphics modes have
two banks and Hercules graphics mode has four banks.  For modes that
don't have scanline banks (such s VGA modes 0Dh-13h), this field should
be set to 1.

The BankSize field specifies the size of a bank (group of scan lines) in
units of 1K.  For CGA and Hercules graphics modes this is 8, as each bank
is 8192 bytes in length.  For modes that don't have scanline banks (such
as VGA modes 0Dh-13h), this field should be set to 0.

	Entry:	AH = 4Fh: Super VGA support
		AL = 01h: Return Super VGA Mode Information
		CX =	: Super VGA video mode
		ES:DI   : Pointer to buffer

	Exit:	AX	:int
*/

typedef struct
{
 //;mandatory information
unsigned  int ModeAttributes;		// dw ?		;mode attributes
unsigned  char WinAAttributes;		//db ?		;Window A attributes
unsigned  char WinBAttributes;		//db ?		;Window B attributes
unsigned int WinGranularity;		//dw ?		;window granularity
unsigned  int WinSize;	   //	dw ?		;window size
unsigned  int WinASegment;		//dw ?		;Window A start segment
unsigned  int WinBSegment;	   //	dw ?		;Window B start segment
unsigned  char far *WinFuncPtr;		//dd ?		;pointer to window function
unsigned  int BytesPerScanLine;	//dw ?		;bytes per scan line

 //;extended information
 //;optional information
 int XResolution;	   //	dw ?		;horizontal resolution
 int YResolution;	//	dw ?		;vertical resolution
 char XCharSize;	   //	db ?		;character cell width
 char YCharSize;		//db ?		;character cell height
 char NumberOfPlanes;  //		db ?		;number of memory planes
 char BitsPerPixel;	  //	db ?		;bits per pixel
 char NumberOfBanks ;   //		db ?		;number of banks
 char MemoryModel;	   //	db ?		;memory model type
 char BankSize;	   //	db ?		;bank size in K

} MODEINFOBLOCK;

int ss_returnsvgamodeinfo(MODEINFOBLOCK *buffer, int mode)
{
	int retour;
	SAVE;
	asm { mov al,01
		  mov cx,mode
		  mov ah,0x4f
		   les di, buffer
		   int 0x10
		   mov &retour,ax
		  }
	RESTORE;
	return(retour);
}

/*6.4 Function 02h - Set Super VGA Video Mode
-------------------------------------------

This function initializes a Super VGA video mode.  The BX register
contains the Super VGA mode to set.  The format of VESA mode numbers is
described in chapter 2.  If the mode cannot be set, the BIOS should leave
the video environment unchanged and return a failure error code.

	Entry:	AH = 4Fh: Super VGA support
		AL = 02h: Set Super VGA Video Mode
		BX =	: Video mode
			D0-D14 = Video mode
			D15 = Clear memory flag
				0=Clear video memory
				1=Don't clear video memory

	Exit:	AX	:int*/


int ss_setsvgamode(int mode)
{
	int retour;
	asm { mov ah,0x4f
		  mov al,2
		  mov bx,mode
		  int 0x10

		  mov &retour, ax
		}
		return(retour);
}



/*6.5 Function 03h - Return Super VGA Video Mode
----------------------------------------------

This function returns the current video mode in BX.  The format of VESA
video mode numbers is described in chapter 2 of this document.

	Entry:	AH = 4Fh: Super VGA support
		AL = 03h: Return current video mode

	Exit:	AX	:int
		BX =	:Current video mode

Note: In a standard VGA BIOS, function 0Fh (Read current video state)
returns the current video mode in the AL register.  In D7 of AL, it also
returns the int of the memory clear bit (D7 at 40:87).  This bit is
set if the mode was set without clearing memory.  In this Super VGA
function, the memory clear bit will not be returned in BX since the
purpose of the function is to return the video mode only.  If an
application wants to obtain the memory clear bit, it should call VGA BIOS
function 0Fh.*/

int ss_getsvgamode(int *mode)
{
	int retour;
	int MODE;

	asm { mov ah,0x4f
		  mov al,3
		  int 0x10

		  mov &retour, ax
		  mov &MODE,bx
		}

		*mode= MODE;
		return(retour);
}
/*
6.7 - CPU Window Memory Window Control
--------------------------------------

This function sets or gets the position of the specific window in the
video memory.  The function allows direct access to the hardware paging
registers.  To use this function properly, the software should use VESA
BIOS Function 01h (Return Super VGA mode information) to determine the
size, location and granularity of the windows.

	Entry:	AH = 4Fh: Super VGA support
		AL = 05h: Super VGA Video Memory Window Control
		BH = Sub-function
			00=Select Super VGA Video Memory Window
			01=Return Super VGA Video Memory Window
		BL = Window A/B (0/1)
		DX = Window position in video memory (in window
			 granularity units)

	Exit:	AX	:int
		DX = Window position in video memory (in window
			 granularity units)

Note: This function is also directly accessible through a far call from
the application.  The address os the BIOS function may be obtained by
using the VESA BIOS Function 01h, Return Super VGA Mode Information.  A
field in the ModeInfoBlock contains the address of this function.  Note
that this function may be different among video modes in a particular
BIOS implementation so the function pointer should be obtained after each
set mode.

In the far call version, no int information is returned to the
application.  Also, in the far call version, the AX and DX registers will
be destroyed.  Therefore if AX and/or DX must be preserved, the
application must do so prior to making the far call.

The application must load the input arguments in BH, BL, and DX (for set
window) but does not need to load either AH or AL in order to use the far
call version of this function.
*/

int ss_setsvgawindow(char win, int pos)
{
	int retour;
	asm {
			mov ah, 0x4f
			mov al,5
			mov bh,0
			mov bl, win
			mov dx, pos;
			int 0x10
			mov &retour, ax
		}
	return(retour);
}


int ss_getsvgawindow(char win, int *pos)
{
	int POS;
	int retour;
	asm {
			mov ah, 0x4f
			mov al,5
			mov bh,1
			mov bl, win
			int 0x10
			mov &retour, ax
			mov &POS, dx
		}
			*pos = POS;

	return(retour);
}




void error(const char *text, char no)
{
	puts(text);
	exit(no);
}

void main()
{
	VGAINFOBLOCK *vgainfoblock;
	MODEINFOBLOCK *modeinfoblock;

	vgainfoblock= (VGAINFOBLOCK*) farmalloc(sizeof(VGAINFOBLOCK)+256);
	if (vgainfoblock==NULL) error("Memoire insuffisante", 21);

	modeinfoblock= (MODEINFOBLOCK*) farmalloc(sizeof(MODEINFOBLOCK));
	if (modeinfoblock==NULL) error("Memoire insuffisante", 21);

	showcopyright();
	if (ss_returnsvgainfo(vgainfoblock)!=0x4f) error("No VESA support detected.", 10);

	puts("");
	printf("VESA version %d.%d (%s)\n", vgainfoblock->VESAVersion /256,
								vgainfoblock->VESAVersion %256,
								vgainfoblock->OEMStringPtr);


	puts("");


	ss_returnsvgamodeinfo(modeinfoblock, 0x101);
	printf("INFORMATION ABOUT: mode 0x101\n");
	printf("Attributes:              %d\n",modeinfoblock->ModeAttributes);
	printf("WinA	          	 %d\nWinB     	     		%d\n", modeinfoblock->WinAAttributes,
											modeinfoblock->WinBAttributes);


	printf("Win Granulity (in kb): %d\n", modeinfoblock->WinGranularity);
	printf("Win Size             : %d\n", modeinfoblock->WinSize);
	printf("WinA Segment          : 0x%x\n", modeinfoblock->WinASegment);
	printf("WinB Segment          : 0x%x\n", modeinfoblock->WinBSegment);
	printf("Win function ptr      : %p\n", modeinfoblock->WinFuncPtr);
	printf("Byte per lines        : 0x%x\n", modeinfoblock->BytesPerScanLine);
	puts("");

	printf("XResolution  	      : 0x%x\n", modeinfoblock->XResolution);
	printf("YResolution  	      : 0x%x\n", modeinfoblock->YResolution);
	printf("XCharSize             : 0x%x\n", modeinfoblock->XCharSize);
	printf("YCharSize             : 0x%x\n", modeinfoblock->YCharSize);
	printf("Nb planes  	          : 0x%x\n", modeinfoblock->NumberOfPlanes);
	printf("BitsPerPixel          : 0x%x\n", modeinfoblock->BitsPerPixel);
	printf("Nb of banks           : 0x%x\n", modeinfoblock->NumberOfBanks);
	printf("MemoryModel  	          : 0x%x\n", modeinfoblock->MemoryModel);
	printf("BankSize 	          : 0x%x\n", modeinfoblock->BankSize);








}
