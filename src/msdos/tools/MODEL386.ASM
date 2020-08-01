;**********************************************************************
; PMODE MODULE
;**********************************************************************
; NAME       :
; DESCRIPTION:
;
;**********************************************************************
;
; PMODE v2.1232 raw, DPMI, VCPI, & XMS compliant protected mode header.
; By Tran (a.k.a. Thomas Pytel) of Renaissance
;
; STATIC3.ASM written by Francois Blanchette to run under PMODE
; Portion borrowed from EXAMPLE.ASM, written by Tran.
;
; 386.INC written by Francois Blanchette
; Portion borrowed from FILE.INC & PMODE.INC, written by Tran.
;
; 96REPV3.ASM written by Francois Blanchette
; Portion borrowed from FILE.INC & PMODE.INC, written by Tran.
;
; PMODE.OBJ compiled from PMODE.ASM, written by Tran.
;
; SEE PMODE.DOC ABOUT USING PMODE.
;
; CODE COMPILED USING MASM 6.1. (Sorry TASM lovers).
;
;***********************************************************************
.386p

;;; INCLUDE FILES
include \masm61\listing\386.inc

;;; PUBLIC procedure
public  _main
public  _leave

externdef hexcode:byte
externdef stringW:byte
externdef Ima2Bytes:byte
externdef FileFound: byte
externdef nbFiles:WORD

;####################################################################
copyrights segment para public use16
		   db "PMODE v2.1232 raw, DPMI, VCPI, & XMS compliant protected mode header. "
		   db "By Tran (a.k.a. Thomas Pytel) of Renaissance"
copyrights ends
;####################################################################

;----------------------------------------------------------------------
;####################################################################
code16  segment para public use16
	assume cs:code16, ds:code16
;####################################################################
rmirq0:                                 ; real mode IRQ0 handler
	push ax
	push ds

	mov ax,0b800h
	mov ds,ax
;	xor word ptr ds:[(4*160)+(38h*2)+(BasePos/256*160)],0fdbh
	pop ds
	mov al,20h
	out 20h,al
	pop ax
	iret
code16  ends
;####################################################################


;####################################################################
code32  segment para public use32
	assume cs:code32, ds:code32
;####################################################################

ormirq0         dd      ?               ; old real mode IRQ handler seg:off
opmirq0         dd      ?               ; old protected mode IRQ handler off

SystemType      db      "System type         :  $"
mainstr1        db      "Low memory free     :  0x$"
mainstr2        db      "Extended memory free:  0x$"

systypestrtbl   dd      sysstr0,sysstr1,sysstr2,sysstr3
sysstr0         db      'raw',0,"$"
sysstr1         db      'XMS',0,"$"
sysstr2         db      'VCPI',0,"$"
sysstr3         db      'DPMI',0,"$"
return          db      13,10,"$"
keystr          db      'Press any key to go on...',0

;#########################################################################
;;  F. BLANCHETTE ADD-ON
;#########################################################################

Tran1              db "PMODE v2.1232 raw, DPMI, VCPI, & XMS compliant protected mode header.",13,10,"$",0
Tran2              db "By Tran (a.k.a. Thomas Pytel) of Renaissance",13,10,"$",0
ERR_LOW_MEM        db "FATAL: Insuficient base memory to run program.",0
ERR_HI_MEM         db "FATAL: Insuficient XMS memory to run program.",0
ERR_VESA_INIT      db "FATAL: VESA driver intialisation failed.$"
ERR_XVESA_INFO     db "FATAL: No VESA information available.$"
ERR_XVESA_MODEINFO db "FATAL: No VESA mode information available.$"
ERR_XCORR_MODE     db "FATAL: No VESA mode to satisfy demand.$"
TXT_FatalReadErr   db "FATAL: File read error occured.$"
ERR_VESA_RES101    db "FATAL: VESA MODE 0x101 is not 640x480x256.$"

TXT_NEED           db "You need 0x$"
__TXT_BYTES_LOW    db " bytes of free base memory to run this program.$"
__TXT_BYTES_XMS    db " bytes of free XMS to run this program.$"

MinLowMem          dd 256*1024		; Requiered based Memory (in K)
MinXMSMem          dd 1*1024*1024	; Requiered XMS (in K)
oldmode            dw 0			; Old Video mode
FileBuf 	   db 4096 DUP (0)	; File Transfer Buffer

;-----------------------------------------------------------------------
;
; TRAN's handy work. I don't know what it does exactly but I'm keeping
; it there just in case it serves any purpose.
;
pmirq0:                                 ; protected mode IRQ0 handler
	push ds
	mov ds,cs:_selzero
;	xor word ptr ds:[0b8000h+(2*160)+(38h*2)+(BasePos/256*160)],0fdbh
	pop ds
	jmp cs:opmirq0                  ; chain to old IRQ0 redirector

int0d: iret

;----------------------------------------------------------------------
;
; PMODE jumps to _main to turn over control to your program. That is
; where your program begins.
;
_main:

	sti
	mov eax,gs:[8*4]                ; save real mode IRQ0 vector
	mov ormirq0,eax
	xor bl,bl                       ; get protected mode IRQ0 redirector
	call _getirqvect
	mov opmirq0,edx

	call SeparateArgs


;#####################################################################
include \masm61\listing\_main.inc
include \masm61\listing\_com386.inc
;#####################################################################

;
; RETURN TO REAL MODE
;
_leave:
	mov eax,ormirq0                 ; restore old real mode IRQ0 vector
	mov gs:[8*4],eax
	jmp _exit

;########################################################################
 module_start PROC NEAR
;########################################################################

		call InitFileSys
		call useMOUSEICO
		call InitSVGA
		call InitMouse

_Remove:
		;; Restore your old video mode and leave
		mov bx, word ptr OldMode
		ss_setvesamode bx
		jmp _leave

;####################################################################
  module_start ENDP
;####################################################################

 include \masm61\listing\graph.inc

;####################################################################
code32  ends            ; fin du module
	end             ; fin du fichier...
;####################################################################

