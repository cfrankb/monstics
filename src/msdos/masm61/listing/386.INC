;**********************************************************************
; INCLUDED FILE
;**********************************************************************
; NAME       : 386.INC
; DESCRIPTION: PMODE 386 DESCRIPTION FILE
;
;**********************************************************************
;
; PMODE v2.1232 raw, DPMI, VCPI, & XMS compliant protected mode header.
; By Tran (a.k.a. Thomas Pytel) of Renaissance
;
; This file must be included in all PMODE modules.
;
; NOTE: Prototypes in this file may not match actual prototypes.
;       Warning: use of this code is at your own risk.
;       Fatal: Please don't try stupid things, because it usualy crash.
;
;       32bits offsets are offsets of CODE32
;           (where only the 16bit portion is taken in account in functions
;		calling MS-DOS services)
;
; 96REPV3 RUNTIME LIBRAIRY was designed by Francois Blanchette
; Code became obselet and was never tested.
;
; By using this code you assume any consequences resulting from the use
; of this code. If you use PMODE, mention Tran (a.k.a. Thomas Pytel).
; If DOS no longer exists, delete this program. - H96
;
; MACROS comes from PMODE.INC & FILE.INC remove if duplication conflicts.
;
; Debugging macros may still contain bugs.
;
;************************************************************************

;; constantes for CT-VOICE.DRV
const_getver  		EQU 0
const_setport 		EQU 1
const_setint    	EQU 2
const_initctv 		EQU 3
const_setspeaker 	EQU 4
const_setstatusaddr	EQU 5
const_readsample	EQU 6
const_deadstop		EQU 8
const_removedrv		EQU 9

;; IMPORTANT KEYBOARD SCAN CODES
;; Low value scan code
;; ===================
KEY_TAB		EQU 9
KEY_RETURN	EQU 13
KEY_ESC		EQU 27
KEY_SPACE	EQU 32

;; High value scan code
;; ====================
KEY_F1		EQU 59
KEY_F2		EQU 60
KEY_F3		EQU 61
KEY_F4		EQU 62
KEY_F5		EQU 63
KEY_F6		EQU 64
KEY_F7		EQU 65
KEY_F8		EQU 66
KEY_F9		EQU 67
KEY_F10		EQU 68
KEY_F11		EQU 57h
KEY_F12		EQU 58h

KEY_UP		EQU 72
KEY_DN          EQU 80
KEY_LF		EQU 75
KEY_RG          EQU 77

KEY_PgUp       	EQU 73
KEY_PgDn	EQU 81
KEY_END		EQU 79
KEY_HOME	EQU 71
KEY_Ins		EQU 82
KEY_DEL		EQU 83

KEY_LCTRL	EQU 1dh
KEY_RCTRL	EQU 10h
KEY_LALT	EQU 38h
KEY_RALT        EQU ?
KEY_LSHIFT	EQU 2ah
KEY_RSHIFT	EQU 36h
KEY_CAPS	EQU 3ah
KEY_NUM_LOCK	EQU 45h
KEY_BACKSPACE	EQU 0eh

;; Search paterns
;;===============
FindFirst	EQU 4eh
FindNext	EQU 4fh

;; File attributs
;;===============
ReadOnly	EQU 1 ; 2^0
Hidden		EQU 2 ; 2^1
System		EQU 4 ; 2^2
VolumeLabel	EQU 8 ; 2^3
Directory	EQU 16; 2^4
Archived	EQU 32; 2^5


;; ORDRE DES SEGMENTS
copyrights segment para public use16
copyrights ends
code16  segment para public use16
code16  ends
code32  segment para public use32
code32  ends
ctvoice segment para public use16
ctvoice ends
codeend segment para stack use32 'stack'
codeend ends


;; FILE.INC
extrn   _filebufloc:dword, _filebuflen:word

extrn   _openfile:near, _closefile:near, _lseekfile:near, _readfile:near
extrn   _writefile:near, _createfile:near, _filesize:near, _filecopy:near
extrn   _deletefile:near, _findfile:near


;; PMODE.INC
extrn   v86r_eax:dword, v86r_ebx:dword, v86r_ecx:dword, v86r_edx:dword
extrn   v86r_esi:dword, v86r_edi:dword, v86r_ebp:dword
extrn   v86r_ah:byte, v86r_al:byte, v86r_bh:byte, v86r_bl:byte
extrn   v86r_ch:byte, v86r_cl:byte, v86r_dh:byte, v86r_dl:byte
extrn   v86r_ax:word, v86r_bx:word, v86r_cx:word, v86r_dx:word
extrn   v86r_si:word, v86r_di:word, v86r_bp:word
extrn	v86r_ds:word, v86r_es:word, v86r_fs:word, v86r_gs:word
extrn	_selcode:word, _seldata:word, _selzero:word, _lomembase:dword
extrn	_lomemtop:dword, _himembase:dword, _himemtop:dword, _pspa:dword
extrn   _code16a:dword, _code32a:dword, _getirqvect:dword, _setirqvect:dword
extrn   _sysbyte0:byte, _irqmode:word

extrn   _getmem:near, _getlomem:near, _gethimem:near, _lomemsize:near
extrn   _himemsize:near, _ret:near, _exit:near, _getirqmask:near
extrn   _setirqmask:near

; Convert physical pointer to realative pointer
@rlp    macro reg, ptr
        mov &reg,&ptr
        sub &reg,_code32a
endm

; Convert realative pointer to physical pointer
@php    macro reg, ptr
        mov &reg,&ptr
	add &reg,_code32a
endm

; Output a byte to DX
@outb           macro   val
        mov al,&val
        out dx,al
endm

; Output a word to DX
@outw           macro   val
        mov ax,&val
        out dx,ax
endm

; Get interrupt flag status
@gif    macro
        mov ax,902h
        int 31h
endm

; Get interrupt flag status and clear
@gifc   macro
        mov ax,900h
        int 31h
endm

; Get interrupt flag status and set
@gifs   macro
        mov ax,901h
        int 31h
endm

; Get interrupt flag status and set to AL (0=clear, 1=set)
@gifal  macro
        mov ah,9
        int 31h
endm


;
; TYPES AND STRUCTURES
;

@t_0		TYPEDEF		FAR PTR BYTE
@t_1		TYPEDEF		FAR PTR WORD
@tag_0		STRUCT 2t
VESASignature		BYTE		4t DUP (?)
VESAVersion		WORD		?
OEMStringPtr		@t_0		?
Capabilities		WORD		4t DUP (?)
VideoModePtr		@t_1		?
@tag_0		ENDS
VGAINFOBLOCK		TYPEDEF		@tag_0

@tag_1		STRUCT 2t
ModeAttributes		WORD		?
WinAAttributes		BYTE		?
WinBAttributes		BYTE		?
WinGranularity		WORD		?
WinSize			WORD		?
WinASegment		WORD		?
WinBSegment		WORD		?
WinFuncPtr		DWORD		?
BytesPerScanLine	WORD		?
XResolution		WORD		?
YResolution		WORD		?
XCharSize		BYTE		?
YCharSize		BYTE		?
NumberOfPlanes		BYTE		?
BitsPerPixel		BYTE		?
NumberOfBanks		BYTE		?
MemoryModel		BYTE		?
BankSize		BYTE		?
@tag_1		ENDS
MODEINFOBLOCK		TYPEDEF		@tag_1

@tag_2		STRUCT 2t
boutons			WORD		?
x			WORD		?
y			WORD		?
oldx			WORD		?
oldy			WORD		?
mouse			BYTE		16t DUP (16t DUP (?))
temp			BYTE		16t DUP (16t DUP (?))
@tag_2		ENDS
MOUSE		TYPEDEF		@tag_2

;; PROTOTYPES (actualy they're ASM procedures)
;; Bios services
_ss_setrangex       PROTO NEAR PASCAL  	  :word, :word
_ss_setrangey       PROTO NEAR PASCAL     :word, :word
_ss_initmouse_bs    PROTO NEAR PASCAL
_ss_showmouse_bs    PROTO NEAR PASCAL
_ss_hidemouse_bs    PROTO NEAR PASCAL
_ss_setvga          PROTO NEAR PASCAL     :byte

;; Statics System services
_ss_setvesamode     PROTO NEAR PASCAL    :dWORD
_ss_getvesamode     PROTO NEAR PASCAL
_ss_getvesamodeinfo PROTO NEAR PASCAL 	 :dWORD, :dWORD
_ss_getvesainfo     PROTO NEAR PASCAL 	 :dWORD
_ss_setfastwindow   PROTO NEAR PASCAL    :BYTE, :WORD, :DWORD
_ss_blowvideo       PROTO NEAR PASCAL    :DWORD
_ss_initmouse	    PROTO NEAR PASCAL    :DWORD
_ss_readmouse	    PROTO NEAR PASCAL    :DWORD
_ss_drawmouse 	    PROTO NEAR PASCAL    :DWORD, :DWORD
_ss_undrawmouse     PROTO NEAR PASCAL    :DWORD, :DWORD

;; Debugging procedures
_ss_ecrirecar 	    PROTO NEAR PASCAL 	 :BYTE, :BYTE
_ss_gotoxy	    PROTO NEAR PASCAL 	 :BYTE, :BYTE
_ss_getax 	    PROTO NEAR PASCAL
_ss_printw 	    PROTO NEAR PASCAL 	 :WORD
_print     	    PROTO NEAR PASCAL    :dword
_ss_printc          PROTO NEAR PASCAL    :DWORD
_ss_printb          PROTO NEAR PASCAL    :DWORD

;; C like functions/procedures
_ss_copymem 	    PROTO NEAR PASCAL :DWORD, :DWORD, :DWORD
_ss_getax 	    PROTO NEAR PASCAL

;; CT-VOICE.DRV services
_ctv_removedrv 	    PROTO NEAR PASCAL
_ctv_deadstop 	    PROTO NEAR PASCAL
_ctv_readsample	    PROTO NEAR PASCAL _seg_:WORD, _offset_:DWORD
_ctv_setstatusaddr  PROTO NEAR PASCAL _seg_:WORD, _offset_:DWORD
_ctv_setspeaker     PROTO NEAR PASCAL _mode_:BYTE
_ctv_setint         PROTO NEAR PASCAL _int_:WORD
_ctv_setport        PROTO NEAR PASCAL _Port_:WORD
_ctv_initctv        PROTO NEAR PASCAL
_ctv_getver         PROTO NEAR PASCAL

;; EXTERNAL OBJECTS
EXTERNDEF mouse_obj           	: MOUSE
EXTERNDEF mode_info_obj       	: MODEINFOBLOCK
EXTERNDEF vesa_info_obj		: VGAINFOBLOCK

;; MOUSE MACROS
ss_setrangex  	MACRO _min, _max
		invoke _ss_setrangey, _min, _max
		ENDM

ss_setrangey  	MACRO _min, _max
		invoke _ss_setrangey, _min, _max
		ENDM

ss_initmouse_bs MACRO
		invoke _ss_initmouse_bs
		ENDM

ss_showmouse_bs MACRO
		invoke _ss_showmouse_bs
		ENDM

ss_hidemouse_bs MACRO
		invoke _ss_hidemouse_bs
		ENDM

ss_initmouse  	MACRO _MOUSE_
	      	invoke _ss_initmouse, _mouse_
	      	ENDM

ss_readmouse  	MACRO _MOUSE_
	      	invoke _ss_readmouse, _mouse_
	      	ENDM

;; VESA MODE MACROS
ss_setvesamode 	MACRO _MODE_
	       	invoke _ss_setvesamode, _MODE_
	       	ENDM

ss_getvesamode 	MACRO
	       	invoke _ss_getvesamode
	       	ENDM

ss_getvesamodeinfo MACRO _buffer_, _mode_
	       	invoke _ss_getvesamodeinfo, _buffer_, _mode_
	       	ENDM


ss_getvesainfo 	MACRO _buffer_
	       	invoke _ss_getvesainfo, _buffer_
	       	ENDM


ss_setfastwindow MACRO _win_, _pos_, _winptr_
	       	invoke _ss_setfastwindow, _win_, _pos_, _winptr_
	       	ENDM

;;  Général purpose macros
ss_getax 	MACRO
		invoke _ss_getax
		ENDM

getax MACRO
		invoke _ss_getax
		ENDM

getchar MACRO
		invoke _ss_getax
		ENDM


ss_ecrirecar 	MACRO _car_
		invoke _ss_ecrirecar, _car_,0
		ENDM

ecrirecar 	MACRO _car_
		invoke _ss_ecrirecar, _car_, 0
		ENDM

putchar		MACRO _car_
		invoke _ss_ecrirecar, _car_, 0
		ENDM


ss_gotoXY 	MACRO _x_,_y_
		invoke _ss_gotoxy, _x_,_y_
		ENDM

gotoXY 		MACRO _x_,_y_
		invoke _ss_gotoxy, _x_,_y_
		ENDM

ss_printw 	MACRO _val_
		invoke _ss_printw, _val_
		ENDM


printw      	MACRO _val_
		invoke _ss_printw, _val_
		ENDM


ss_printw      	MACRO _val_
		invoke _ss_printw, _val_
		ENDM


ss_blowvideo MACRO _color_
		invoke  _ss_blowvideo, _color_
		ENDM


ss_setvga  	MACRO _mode
		invoke _ss_setvga, _mode
		ENDM


setvga  	MACRO _mode
		invoke _ss_setvga, _mode
		ENDM

;; Savetime MACROS

movx		MACRO d_, s_
		push s_
                pop d_
		ENDM

movb		MACRO d_,s_
                push ax
                mov al, s_
                mov d_,al
                pop ax
		ENDM


;; DEBUGGING MACROS (may contain bugs or crash inexplicably)

print      	MACRO _offset
		invoke _print, _offset
		ENDM

ss_print      	MACRO _offset
		invoke _print, _offset
		ENDM


ss_printc 	MACRO _offset_
		invoke _ss_printc, _offset_
	  	ENDM

printc 		MACRO _offset_
		invoke _ss_printc, _offset_
	  	ENDM

printcr		MACRO
                ecrirecar 13
                ecrirecar 10
		ENDM

printa		MACRO _dword_
                push eax
                mov eax, _dword_
                push ax
                shr eax,16
		printw <ax>
                ecrirecar ":"
                pop ax
                printw <ax>
                pop eax
                ENDM


printd		MACRO _dword_
                push eax
                mov eax, _dword_
                push ax
                shr eax,16
		printw <ax>
                ;ecrirecar ":"
                pop ax
                printw <ax>
                pop eax
                ENDM

ss_printb 	MACRO _offset_
		invoke _ss_printb, _offset_
	  	ENDM

printb 		MACRO _offset_
		invoke _ss_printb, _offset_
	  	ENDM


;; SoundBlaster -- CT-VOICE.DRV MACROS

ctv_getver  	MACRO
           	call _ctv_getver
	   	ENDM

ctv_initctv	MACRO
           	call _ctv_initctv
	   	ENDM

ctv_setport 	MACRO _Port_
           	invoke _ctv_setport, _Port_
 		ENDM

ctv_setint	MACRO _int_
           	invoke _ctv_setint, _int_
 		ENDM

ctv_setspeaker 	MACRO _int_
           	invoke _ctv_setspeaker, _mode_
 		ENDM

ctv_setstatusaddr MACRO _seg_, _offset_
                 invoke _ctv_setstatusaddr, _seg_, _offset_
		 ENDM

ctv_readsample 	MACRO _seg_, _offset_
		invoke _ctv_setstatusaddr, _seg_, _offset_
		ENDM

ctv_deadstop 	MACRO
		call _ctv_deadstop
		ENDM

ctv_removedrv 	MACRO
		call _ctv_removedrv
		ENDM

;---------------------------------------------------------------------
;
; These functions (ss_drawmouse & ss_undrawmouse) are still under
; developpement. Macro arguments passed will be ignored.
;
; Functions use global vars "mouse_obj" & "mode_info_obj" ONLY.
; Developpement is expected to be never completed.
;

ss_drawmouse 	MACRO _MOUSE_, _MODEINFOBLOCK_
		invoke _ss_drawmouse, 0,0
		ENDM

ss_undrawmouse 	MACRO _MOUSE_, _MODEINFOBLOCK_
		invoke _ss_undrawmouse, 0,0
		ENDM


ss_copymem 	MACRO _dest_, _source_, _len_
		invoke _ss_copymem, _dest_, _source_ , _len_
		ENDM

;-----------------------------------------------------------------


pushall 	macro
		push eax
		push ebx
		push ecx
		push edx
		push edi
		push esi
		endm

popall 		macro
		pop esi
		pop edi
		pop edx
		pop ecx
		pop ebx
		pop eax
		endm

NUL 		MACRO _D_
		xor _D_,_D_
		ENDM


;----------------------------------------------------------------------
;**********************************************************************
; INCLUDED FILE
;**********************************************************************
; NAME       : 386.INC
; DESCRIPTION: PMODE 386 DESCRIPTION FILE
;
;**********************************************************************
;
; ADD ON MACROS AND PROTOTYPES WERE ADDED. THEY WILL BE INCLUDED
; USING TRIGGER CONSTANTE FOR COMPATIBILITY NEEDS ONLY.
; THESE MACROS ARE USED BY 96EXTRA.ASM
;
;***********************************************************************
ifdef extra
OutText 	MACRO _X_, _Y_, _TEXT_, _TCOLOR_, _BCOLOR_
	     	invoke _OutText, _X_, _Y_, _TEXT_, _TCOLOR_, _BCOLOR_
		ENDM

DrawSqrt 	MACRO _x_, _y_, _len_, _hei_, _color_
		invoke _DrawSqrt, _X_,_Y_, _LEN_,_HEI_,_COLOR_
		ENDM

StrCmp		MACRO _S_, _D_
                invoke _strcmp, _S_, _D_
		ENDM


DebugBreak MACRO _text_
                invoke _debugbreak, _text_
		ENDM

_DebugBreak 	PROTO NEAR PASCAL :DWORD
_OutText 	PROTO NEAR PASCAL :WORD, :WORD, :DWORD, :BYTE, :BYTE
_DrawSqrt 	PROTO NEAR PASCAL :WORD,:WORD,:WORD, :WORD,:BYTE
ss_findfirst 	PROTO NEAR PASCAL
ss_findnext  	PROTO NEAR PASCAL
GetPspAdrr 	PROTO NEAR PASCAL
_StrCmp		PROTO NEAR PASCAL :DWORD, :DWORD
_drawTextWindow PROTO NEAR PASCAL :WORD, :WORD, :DWORD,:BYTE, :BYTE
_strcat		PROTO NEAR PASCAL :DWORD, :DWORD
_strlen		PROTO NEAR PASCAL :DWORD
_strcpy		PROTO NEAR pASCAL :DWORD, :DWORD
Mousie		PROTO NEAR PASCAL

GetDta 		PROTO NEAR PASCAL
ShowScreen 	PROTO NEAR PASCAL
GetCurrentDrive PROTO NEAR PASCAL
MakeCurrentPath PROTO NEAR PASCAL
changedir 	PROTO NEAR PASCAL
getch 		PROTO NEAR PASCAL
InitFileSys2 	PROTO NEAR PASCAL
SetWGranDD      PROTO NEAR PASCAL
ShowScreen2     PROTO NEAR PASCAL

Delay 		PROTO NEAR PASCAL
ChkMem 		PROTO NEAR PASCAL

LoadIma 	PROTO NEAR PASCAL
ClearBuffer 	PROTO NEAR PASCAL
_Find1stOf 	PROTO NEAR PASCAL :BYTE, :DWORD
_Findlastof 	PROTO NEAR PASCAL :BYTE, :DWORD

SeparateArgs 	PROto NEAR PASCAL
UseMOUSEICO 	PROto NEAR PASCAL
InitFileSys 	PROto NEAR PASCAL
InitSVGA 	PROto NEAR pASCAL
InitMouse 	PROto NEAR PASCAL
SeePMODE 	PROTO NEAR PASCAL


EXTERNDEF 	_leave      : 	PROC
EXTERNDEF 	MinLowMem   : 	DWORD
EXTERNDEF 	MinXmsMem   : 	DWORD
EXTERNDEF 	DtaPtr      :	DWORD
EXTERNDEF 	Ascii_table : 	BYTE
EXTERNDEF 	Ascii_data  : 	BYTE
EXTERNDEF 	oldmode     : 	WORD
EXTERNDEF 	MOUSE_ICO   : 	BYTE
EXTERNDEF 	module_start:	PROC
EXTERNDEF 	NbFiles     : 	WORD
EXTERNDEF 	ImaHeader   :	WORD

EXTERNDEF 	WGranDD	    : 	DWORD
EXTERNDEF 	CurrentPath : 	BYTE


endif
;------------------------------------------------------------------

