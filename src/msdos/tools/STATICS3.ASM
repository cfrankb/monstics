;**********************************************************************
; PMODE MODULE
;**********************************************************************
; NAME       : STATICS3.ASM
; DESCRIPTION: Statics Editor V3.0's main module
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
; SEE PMODE.DOC ABOUT USING PMODE. Code can be distributed and modified
; and used under one restriction: If it ever serves YOU, mention the
; authors (Tran for PMODE, Francois Blanchette for STATICS3). Give
; some credits.
;
; CODE COMPILED USING MASM 6.1. (Sorry TASM lovers).
;
; IMPROVING THE STATICS EDITOR V3.0
; =================================
;
; If you solve the 64k problem with code32. (i.e. I had problems with
; program when code32 exceded 64k. That is quite weird because as I
; understand it the segment is suppose to be 4GB wide) I suppose it
; might just be problem of compatibility between TASM/MASM, or just
; a segment attribut gismo.
;
; In any case, if you improve this program you MUST:
; * Include all sources codes along with your distribution.
; * Keep the credit section of this program as it is, but you can
;   add your name at the end.
; * The fallowing programs are included in this distribution
;   (they are expected to continue to be)
;
;   PMODE.ASM PMODE.OBJ PMODE.DOC STUFF.DOC PMODE.INC FILE.INC
;   STATICS3.ASM STATICS3.OBJ _MAIN.INC 386.INC
;   96REPV3.ASM 96REPV3.OBJ RUN96.LIB
;
; * You may distribute your versions of these programs, as long
;   as the original credits sections contains the original
;   names of the authors who originally worked on their respective
;   programs.
;
; * Don't expect anyone to procecute or anything, but that is a matter
;   of honnor.
;
; * Specials thanks to Tran (a.k.a Thomas Pythel) who developped PMODE
;   and made 32-bits protected mode programming available to everyone.
; * Send me a copy the new source files so I can get a look at what
;   the new STATICS3.
;
;   FRANCOIS BLANCHETTE
;   3825 BAZIN
;   BROSSARD, QC
;   CANADA
;   J4Z-2J3
;   (514) 462-2755
;
; * Please don't use TASM. I don't have TASM and I can't afford to buy
;   a new assembler as of now.
;
; * Feel free to correct bugs, if you find any.
;
; * Keep up with a disclaimer saying that:" WE are not responsible
;   for any lost of data, bugs, crashs, lost of money or hardware problems
;   resulting from the use of this program. The user is assuming
;   all responsability  resulting from the use of this software.
;   By using the software the user is stating that he understand the
;   terms of the aggrement and FULLY comply with it. "
;
; * FREEWARE MAY NOT BE SOLD FOR PROFIT.
;
;
;**********************************************************************

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

Copy4dd       PROTO NEAR PASCAL :DWORD, :DWORD
Exchange      PROTO NEAR PASCAL :DWORD, :DWORD
TrierFichiers PROTO NEAR PASCAL

; MEMORY MAP STRUCTURE
;_himembase			Screen buffer
;_himembase + 256k		Image buffer
;_himembase + 512k		Directories
;_himembase + 256*3k		Clipboard

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
	xor word ptr ds:[(4*160)+(38h*2)+(BasePos/256*160)],0fdbh
	pop ds
	mov al,20h
	out 20h,al
	pop ax
	iret
code16  ends
;####################################################################
;.model Flat


;####################################################################
code32  segment para public use32
	assume cs:code32, ds:code32, gs:nothing
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
BasePos         EQU 4*256       ;; do not remove

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
TXT_OBLEDIT        db "             STATICS EDITOR V3.0: (c) 1996 Francois Blanchette         ",0

QuietPMODE	   dw 0

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
 	call ControlArgs


;#####################################################################
include \masm61\listing\_main.inc
;#####################################################################

;
; RETURN TO REAL MODE
;
_leave:
	mov eax,ormirq0                 ; restore old real mode IRQ0 vector
	mov gs:[8*4],eax
	jmp _exit


;----------------------------------------------------------------------<
_draw_win PROTO NEAR PASCAL :WORD, :WORD, :WORD, :WORD, :BYTE
_draw_win PROC  NEAR PASCAL, _topx_ :WORD, _topy_:WORD, _len_:WORD, _hei_:WORD, _color_:BYTE
;----------------------------------------------------------------------<

		pushall

                mov ax, _topy_				; y*resolution
                mul Mode_Info_obj. XResolution

                shl edx,16				; edx= 256*dx
                mov dx,ax				; edx= 256*dx +ax

                xor eax,eax
                mov ax, _topx_				; eax = x

                add eax,edx				; eax = x + y*res
                add eax, _himembase
                mov edi,eax				; edi =eax


                mov dx, _hei_
DW00013:
		mov al, _color_
		mov cx, _len_


DW00012:        mov ds:[edi],al
		inc edi
                loop DW00012

                xor eax,eax
                mov ax, Mode_info_obj.XResolution
                sub ax, _len_
                add edi, eax

                mov cx,dx
                dec dx
                loop DW00013

                popall
		ret

_draw_win ENDP


;--------------------------------------------------------------------
OutText MACRO _X_, _Y_, _TEXT_, _TCOLOR_, _BCOLOR_
     invoke _OutText, _X_, _Y_, _TEXT_, _TCOLOR_, _BCOLOR_
ENDM
;---------------------------------------------------------------------

;--------------------------------------------------------------------
_OutText PROTO NEAR PASCAL :WORD, :WORD, :DWORD, :BYTE, :BYTE
_OutText PROC NEAR PASCAL, _X_:WORD, _Y_:WORD, _TEXT_:DWORD, _TCOLOR_:BYTE, _BCOLOR_:BYTE
;--------------------------------------------------------------------

Local 		TempDest: DWORD

		pushall
                xor eax,eax
                mov ax, _Y_
                mul mode_info_obj. XResolution

                shl edx, 16
                mov dx,ax  			; edx = y * Xres

                xor eax,eax
                mov ax, _X_
                add edx, eax			; edx= y*res+ x

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
                ;xor edx,edx
                mov eax,edx			; eax=edx
                xor edx,edx
 		div WGranDD			; eax /4 on my VideoCard

                pushall
                ss_setfastWindow 0, <ax>, mode_info_obj. WinFuncPtr
                popall

                mov ebx,edx			; remainder of "div WGranDD"
                mov edi,ebx
                add edi, 0a0000h		; abs adresse on screen
		mov tempdest, edi

           	mov esi, _TEXT_
                mov al,[esi]
                .while al!=0 && al!="$"
;                  ecrirecar <al>

		  ;-----------------------------------------
  			mov ebx, offset ascii_table
	                mov ah, [ebx]
			.while al!=[ebx] && ah!=0
	   		   inc ebx
	                   mov ah, [ebx]
        	        .endw

	                sub ebx, offset ascii_table
	                shl ebx, 6
	                add ebx, offset ascii_data
                        add ebx,64
	                ;ret
                  ;call LookInTable	; get ebx for obj
		  ;----------------------------------------
                  mov edi, tempdest
                  add tempdest,8

                  ;gotoxy 0,8
                  ;printd <edi>
    ;
     ;              cmp al," "
      ;             je __TADUM
		  mov dx, 8
XX0002:
                    mov cx, 8
XX0001:
                     mov al,[ebx]
                     or al,al
                     je black
		     cmp al,15
                     je White
                     mov byte ptr gs:[edi],al
                     jmp XBlack

White:
                     mov al, _Tcolor_
                     mov byte ptr gs:[edi], al
                     jmp XBlack
Black:
                     mov al, _Bcolor_
		     mov byte ptr gs:[edi], al
XBlack:

                    inc ebx
		    inc edi
                  loop XX0001

                  xor eax,eax
                  mov ax, mode_info_obj.XResolution
                  add edi, eax
                  sub edi,8

                  mov cx,dx
                  dec dx
                loop XX0002

__TADUM:

                  inc esi
                  mov al,[esi]
                .endw

	        popall
	        ret


_OutText ENDP
;-------------------------------------------------------------------
OutTextb MACRO _X_, _Y_, _TEXT_, _TCOLOR_, _BCOLOR_
     invoke _OutTextb, _X_, _Y_, _TEXT_, _TCOLOR_, _BCOLOR_
ENDM
;---------------------------------------------------------------------

;--------------------------------------------------------------------
_OutTextb PROTO NEAR PASCAL :WORD, :WORD, :DWORD, :BYTE, :BYTE
_OutTextb PROC NEAR PASCAL, _X_:WORD, _Y_:WORD, _TEXT_:DWORD, _TCOLOR_:BYTE, _BCOLOR_:BYTE
;--------------------------------------------------------------------
Local 		TempDest: DWORD

		pushall
                xor eax,eax
                mov ax, _Y_
                mul mode_info_obj. XResolution

                shl edx, 16
                mov dx,ax  			; edx = y * Xres

                xor eax,eax
                mov ax, _X_
                add edx, eax			; edx= y*res+ x

                ;mov eax,edx			; eax=edx
                ;shr eax,2			; eax /4
                ;shr eax, 10                     ; eax/1024/4


                ;mov ebx,edx
                ;shl eax,12
                ;sub ebx,eax

                ;mov edi,ebx
                ;add edi, 0a0000h		; abs adresse on screen
                mov edi,edx
                add edi,_himembase
		mov tempdest, edi

           	mov esi, _TEXT_
                mov al,[esi]
                .while al!=0 && al!="$"
;                  ecrirecar <al>

		  ;-----------------------------------------
  			mov ebx, offset ascii_table
	                mov ah, [ebx]
			.while al!=[ebx] && ah!=0
	   		   inc ebx
	                   mov ah, [ebx]
        	        .endw

	                sub ebx, offset ascii_table
	                shl ebx, 6
	                add ebx, offset ascii_data
                        add ebx,64
	                ;ret
                  ;call LookInTable	; get ebx for obj
		  ;----------------------------------------
                  mov edi, tempdest
                  add tempdest,8

                  ;gotoxy 0,8
                  ;printd <edi>
    ;
     ;              cmp al," "
      ;             je __TADUM
		  mov dx, 8
XX0002:
                    mov cx, 8
XX0001:
                     mov al,[ebx]
                     or al,al
                     je black
		     cmp al,15
                     je White
                     mov byte ptr gs:[edi],al
                     jmp XBlack

White:
                     mov al, _Tcolor_
                     mov byte ptr gs:[edi], al
                     jmp XBlack
Black:
                     mov al, _Bcolor_
		     mov byte ptr gs:[edi], al
XBlack:

                    inc ebx
		    inc edi
                  loop XX0001

                  xor eax,eax
                  mov ax, mode_info_obj.XResolution
                  add edi, eax
                  sub edi,8

                  mov cx,dx
                  dec dx
                loop XX0002


                  inc esi
                  mov al,[esi]
                .endw

	        popall
	        ret


_OutTextb ENDP



;--------------------------------------------------------------------
OutCar MACRO _X_, _Y_, _CAR_, _TCOLOR_, _BCOLOR_
     invoke _OutCar, _X_, _Y_, _CAR_, _TCOLOR_, _BCOLOR_
ENDM

_OutCar PROTO NEAR PASCAL :WORD, :WORD, :BYTE, :BYTE, :BYTE
_OutCar PROC NEAR PASCAL, _X_:WORD, _Y_:WORD, _CAR_:BYTE, _TCOLOR_:BYTE, _BCOLOR_:BYTE
;--------------------------------------------------------------------

Local 		TempDest: DWORD

		pushall
                xor eax,eax
                mov ax, _Y_
                mul mode_info_obj. XResolution

                shl edx, 16
                mov dx,ax  			; edx = y * Xres

                xor eax,eax
                mov ax, _X_
                add edx, eax			; edx= y*res+ x

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
                mov eax,edx			; eax=edx
                xor edx,edx
                div WGranDD
                ;shr eax,2			; eax /4
                ;shr eax, 10                     ; eax/1024/4

                pushall
                ss_setfastWindow 0, <ax>, mode_info_obj. WinFuncPtr
                popall

                mov ebx,edx			; edx = remain "div WGranDD"
                ;shl eax,12
                ;sub ebx,eax

                mov edi,ebx
                add edi, 0a0000h		; abs adresse on screen
		mov tempdest, edi

;           	mov esi, _TEXT_
;                mov al,[esi]
		mov al,_car_
;                .while al!=0 && al!="$"
;                  ecrirecar <al>

		  ;-----------------------------------------
  			mov ebx, offset ascii_table
	                mov ah, [ebx]
			.while al!=[ebx] && ah!=0
	   		   inc ebx
	                   mov ah, [ebx]
        	        .endw

	                sub ebx, offset ascii_table
	                shl ebx, 6
	                add ebx, offset ascii_data
                        add ebx,64
	                ;ret
                  ;call LookInTable	; get ebx for obj
		  ;----------------------------------------
                  mov edi, tempdest
                  add tempdest,8

                  ;gotoxy 0,8
                  ;printd <edi>
    ;
     ;              cmp al," "
      ;             je __TADUM
		  mov dx, 8
XX0002:
                    mov cx, 8
XX0001:
                     mov al,[ebx]
                     or al,al
                     je black
White:
                     mov al, _Tcolor_
                     mov byte ptr gs:[edi], al
                     jmp XBlack
Black:
                     mov al, _Bcolor_
		     mov byte ptr gs:[edi], al
XBlack:

                    inc ebx
		    inc edi
                  loop XX0001

                  xor eax,eax
                  mov ax, mode_info_obj.XResolution
                  add edi, eax
                  sub edi,8

                  mov cx,dx
                  dec dx
                loop XX0002

__TADUM:

                  inc esi
;                  mov al,[esi]
;                .endw

	        popall
	        ret
_OutCar ENDP

;---------------------------------------------------------------------
OutWord MACRO _X_, _Y_, _VAL_, _TCOLOR_, _BCOLOR_
     invoke _OutWORD, _X_, _Y_, _VAL_, _TCOLOR_, _BCOLOR_
ENDM

_OutWord PROTO NEAR PASCAL :WORD, :WORD, :WORD, :BYTE, :BYTE
_OutWord PROC NEAR PASCAL, _X_:WORD, _Y_:WORD, _VAL_:WORD, _TCOLOR_:BYTE, _BCOLOR_:BYTE
;---------------------------------------------------------------------

		pushall
                mov edi, offset stringW+3
		mov dx, _val_

		mov cx,4
putdigit:	mov bx, dx
		and ebx,15
                mov al, byte ptr [offset hexcode+ebx]
                mov byte ptr [edi],al

                dec edi
                shr dx,4
                loop putdigit

                ;invoke _print, offset stringW
                OutText _x_, _y_, offset StringW, _TCOLOR_, _BCOLOR_
                popall
		ret


_OutWord ENDP

;---------------------------------------------------------------------
OutdWord MACRO _X_, _Y_, _VAL_, _TCOLOR_, _BCOLOR_
     invoke _Outdword, _X_, _Y_, _VAL_, _TCOLOR_, _BCOLOR_
ENDM

_OutdWord PROTO NEAR PASCAL :WORD, :WORD, :DWORD, :BYTE, :BYTE
_OutdWord PROC NEAR PASCAL, _X_:WORD, _Y_:WORD, _VAL_:dWORD, _TCOLOR_:BYTE, _BCOLOR_:BYTE
;---------------------------------------------------------------------

                push eax
                mov eax, _val_
                push ax
                shr eax,16
                Outword _x_, _y_, <ax>, _TCOLOR_, _BCOLOR_

                pop ax
                Outword _x_+2, _y_, <ax>, _TCOLOR_, _BCOLOR_
                pop eax
 		ret

_OutdWord	ENDP

;---------------------------------------------------------------------
DrawSqrt MACRO _x_, _y_, _len_, _hei_, _color_
	invoke _DrawSqrt, _X_,_Y_, _LEN_,_HEI_,_COLOR_
ENDM

_DrawSqrt PROTO NEAR PASCAL :WORD,:WORD,:WORD, :WORD,:BYTE
_DrawSqrt PROC  NEAR PASCAL _X_:WORD,_Y_:WORD, _LEN_:WORD,_HEI_:WORD,_COLOR_:BYTE
;-----------------------------------------------------------------------

		pushall
                xor eax,eax
                mov ax, _Y_
                mul mode_info_obj. XResolution

                shl edx, 16
                mov dx,ax  			; edx = y * Xres

                xor eax,eax
                mov ax, _X_
                add edx, eax			; edx= y*res+ x

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
                mov eax,edx			; eax=edx
                xor edx,edx
                ;shr eax,2			; eax /4
                ;shr eax, 10                     ; eax/1024/4
                div WGranDD

                pushall
                ss_setfastWindow 0, <ax>, mode_info_obj. WinFuncPtr
                popall

                mov ebx,edx
                ;shl eax,12
                ;sub ebx,eax

                mov edi,ebx
                add edi, 0a0000h		; abs adresse on screen
		;mov tempdest, edi

;                pushall
 ;               printd <edi>
  ;              popall


                mov al, _color_
                xor ebx,ebx
                mov bx, mode_info_obj. XResolution
                sub bx, _len_

                mov dx,_hei_
DD0002:         mov cx,_len_

DD0001:
                mov gs:[edi],al
                inc edi
                loop DD0001

                add edi, ebx
                mov cx,dx
                dec dx
                loop DD0002
		popall
                ret
_DrawSqrt	ENDP

;-----------------------------------------------------------------------
drawpix 	MACRO _X_, _Y_,_COLOR_
		invoke _drawpix,   _X_, _Y_,_COLOR_
ENDM

_drawpix	PROTO NEAR PASCAL :WORD,:WORD,:BYTE
_drawpix	PROC NEAR PASCAL, _X_:WORD,_Y_:WORD,_COLOR_:BYTE
		pushall
                xor eax,eax
                mov ax, _Y_
                mul mode_info_obj. XResolution

                shl edx, 16
                mov dx,ax  			; edx = y * Xres

                xor eax,eax
                mov ax, _X_
                add edx, eax			; edx= y*res+ x

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
                mov eax,edx			; eax=edx
                xor edx,edx
                div WGranDD
                ;shr eax,2			; eax /4
                ;shr eax, 10                     ; eax/1024/4

                pushall
                ss_setfastWindow 0, <ax>, mode_info_obj. WinFuncPtr
                popall

                mov ebx,edx			; remain of "Div WGranDD"
                ;shl eax,12
                ;sub ebx,eax

                mov edi,ebx
                add edi, 0a0000h		; abs adresse on screen
		;mov tempdest, edi

                mov al, _color_
                mov gs:[edi],al

                popall
                ret
_drawpix	ENDP

;---------------------------------------------------------------------------------------

AskQuestion PROTO NEAR PASCAL :DWORD, :DWORD, :BYTE, :BYTE
AskQuestion PROC NEAR PASCAL _TEXT_:DWORD, _CHOICE_:DWORD, _FCOLOR_:BYTE, _BCOLOR_:BYTE

                ss_undrawmouse 0,0
		outtext 0,0, _TEXT_, _FCOLOR_, _BCOLOR_
                ss_drawmouse 0,0
                ss_getax
                mov ah,0
                .while ah==0

                     inc Timer
                     .if word ptr Timer >=5
			mov word ptr Timer,0
                        inc word ptr ParamColor
                        .if word ptr ParamColor>=15
                           mov ParamColor,1
                        .endif
                        call DrawParams
                     .endif

                     pushall
		     ss_readmouse offset mouse_obj
		     mov ax, mouse_obj.x
	             mov bx, mouse_obj.y
                     mov cx, mouse_obj.boutons

               	     .if ax!=mouse_obj.oldx || bx!=mouse_obj.oldy
                       ; call InfoZone
	   	       ss_undrawmouse 0,0
	               ss_drawmouse 0,0
                     .endif
                     popall


                     call MAJ
                     mov esi, _CHOICE_
                     mov ah, [esi]
                     .while ah!=0 && al!=ah
                        inc esi
                        mov ah,  [esi]
                     .endw

                     sub esi, _CHOICE_

                    .if ah==0
                    ss_getax
                    mov ah,0
                    .endif
                .endw

                push esi
                pushall
                ss_undrawmouse 0,0
                call ClearTopLine
                ss_drawmouse 0,0
		;call ZoneInfo
                popall
                pop eax
                ret

AskQuestion ENDP

;------------------------------------------------------------------------

ClearTopLine PROC NEAR PASCAL
;-----------
			pushall
    		      ss_setfastwindow 0, 0*65536/4096, mode_info_obj.WinFuncPtr
                      mov esi, _himembase
                      mov edi, 0a0000h
                      mov cx, 640*8/4
                      mov eax, app_color
CTL000:
                      ;mov eax, [esi]
                      mov gs:[edi],eax
                      ;add esi,4
                      add edi,4
                      loop CTL000
                      ;call InfoZone
                      popall
		      ret

ClearTopLine		ENDP

;-------------------------------------------------------------------------

MAJ PROC NEAR PASCAL
;--
		.if al>="a" && al<="z"
                       	sub al,"a"
                        add al,"A"
                .endif

		ret

MAJ		ENDP
;------------------------------------------------------------------------

DrawParams PROC NEAR PASCAL
;---------
              	pushall

		;; [Get position of ImageZone]
		mov ax, ImageTopY
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax			; edx = y* Xres

                xor eax,eax
                mov ax, ImageTopX
                add edx,eax			; edx = y* XRes + x
                mov edi,edx

                ;; Adding offset from VX & VY
                xor eax,eax
		mov ax, VX
                shl ax, 3
                add edi, eax

                mov ax, VY
                shl ax,3
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax
		add edi, edx

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
		;; Setup multiportion Window
                mov ebx,edi
                ;shr ebx, 10 +2
                xor edx,edx
                mov eax, ebx			; abs addr in VideoWin
		div WGranDD
                mov ebx, eax

    		ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                ;and edi, 4096-1
                mov edi,edx			; copy remain in2 edx
                add edi, 0a0000h

                ;; DrawTopPortion
                mov ax, ParamColor
                mov ah, al
                push ax
                shl eax,16
                pop ax

                mov gs:[edi], eax
                mov gs:[edi+4],eax

                mov gs:[edi+640],al
                mov gs:[edi+640*2],al
                mov gs:[edi+640*3],al

                add edi, ImageLastFNToffset

		;; DrawBottomPortion
                mov gs:[edi + 7+640*4],al
                mov gs:[edi + 7+640*5],al
                mov gs:[edi + 7+640*6],al

                mov gs:[edi  +640*7], eax
                mov gs:[edi+4+640*7],eax

                popall
                ret
DrawParams ENDP

;-------------------------------------------------------------------------
;_OutText PROTO NEAR PASCAL :WORD, :WORD, :DWORD, :BYTE, :BYTE
_drawTextWindow PROTO NEAR PASCAL :WORD, :WORD, :DWORD,:BYTE, :BYTE
_drawTextWindow PROC NEAR PASCAL,_X_:WORD,_Y_:WORD,_WinINFo_:DWORD,_TCOLOR_:BYTE,_BCOLOR_:BYTE
		pushall
                mov bx, _y_
                mov esi, _WinInfo_
                .while dword ptr [esi]!=-1 && dword ptr [esi]!=0
			mov eax, dword ptr [esi]
			OutText _x_, <bx>, <eax>, _TCOLOR_, _BCOLOR_
                        add bx,8
                	add esi,4
                .endw
                popall
		ret
_drawTextWindow ENDP


;--------------------------------------------------------------------
;
; GetDta
;
;

GetDta PROC NEAR PASCAL
		pushall

                mov al, 21h
                mov v86r_ah,2fh
                int 33h

                xor eax,eax
                mov ax, v86r_es
                shl eax,4

                xor ebx,ebx
                mov bx, v86r_bx
                add eax,ebx
                mov DtaPtr, eax

	        popall
	        ret
GetDta ENDP

;---------------------------------------------------------------------
; SS_FINDFIRST
;
; IN
; cx= attribut, EDX = azt name
; OUT
; if carry = failed then ax = error code.


ss_findfirst PROC NEAR PASCAL

;		pushall
;                print <edx>
;                printd DtaPtr
;                popall
                clc
                push edx

                xor eax,eax
                mov ax, Code32
                shl eax, 4
                add eax, edx

                mov edx,eax
                and eax, 15
                shr edx,4

		mov v86r_ah, 4eh	; ah = findfirst
		mov v86r_cx, cx		; cx= cx

                mov v86r_ds, dx
                mov v86r_dx, ax
                mov al, 21h
                int 33h
                mov ax, v86r_ax
                pop edx
                ret

ss_findfirst ENDP

ss_findnext  PROC NEAR PASCAL

		clc
                push edx
                ;mov eax, edx
                ;and eax, 15
                ;shr edx,4

		mov v86r_ah, 4fh	; ah = findfirst
		;mov v86r_cx, cx		; cx= cx

                ;mov v86r_ds, dx
                ;mov v86r_dx, ax
                mov al, 21h
                int 33h
                mov ax, v86r_ax
                pop edx
                ret

ss_findnext  ENDP

;---------------------------------------------------------------------
; Dodir: Read the content of the current directory.
;
; SYNTAXE:  invoke DoDir, [DDptrFileType$]
;
; Structure of an entry
Image_Type EQU 0		; 1 byte image type descriptor
				;  0 unknown
                                ;  1 Ima 1.0
                                ;  3 Ima 3.0
                                ; -1 End of data

Image_Name EQU 1		; 13 bytes name of file
Image_desc EQU 15               ; 16 bytes description

align 4
DestName	dd 0
ImageAbsSize EQU ((400-16)/8)*64*64
DtaPtr		dd offset Dta

FilenameOffset EQU 1eh

Testing		db "Testing",13,10,"$"
TXT_FindNext	db "FindNext",13,10,"$"

Dta		db 1eh DUP (0)
           	db 0,0
                db (4096/2) DUP (0)

ALL_FILES	db "*.*",0
NULL_FILES	db 0
		;  0  123456789012345
DriveString	db 3,"A:            ",0
		db 16 DUP (0)
;-------------------------------------------------------------------------
DoDir PROTO NEAR PASCAL :DWORD
DoDir PROC NEAR PASCAL _FILETYPE_:DWORD

		pushall

                call GetDta			; Get the location of
                				; the DTA (disk transfer
                                                ; area)

                mov eax, offset Dta
                xor ebx,ebx
                mov bx, Code32
                shl ebx, 4
                add eax,ebx
                mov ebx,eax

                shr eax, 4
                mov ebx, offset Dta
                and ebx, 15

                mov v86r_ds, ax
                mov v86r_dx, bx
                mov v86r_ah, 1ah		; Set a new DTA (disk
                mov al, 21h			; transfer area) larger
                int 33h				; so we won't have problems

                ; Ajust the destination name
                mov edi, _himembase
                add edi, 512*1024
                mov DestName, edi

                ;; Add 4 drives to list
                mov byte ptr DriveString+1, "A"
                mov dx, 4
                xor ebx,ebx
DD0002:
                mov esi, offset DriveString
                mov cx, 32

DD0001:
                mov al, [esi]
                mov byte ptr [edi+ebx], AL
                inc esi
                inc ebx
                loop DD0001

                inc byte ptr DriveString+1
		dec dx
                or dx,dx
                jne DD0002

		add DestName, 32*4

                ;;---------------------------------
                ;; FindFirst DIR
		mov cx, Directory;Archived
                mov edx, offset ALL_FILES
		call ss_findfirst
                jc NoMoreDirs;

                mov edx, offset Dta
	mov al,[edx+15h]
        and al,Directory
	.if al==Directory && al!=al


                add edx, 1eh ;+1
                mov edi, DestName
                add DestName, 32
                mov byte ptr [edi],2		; TypeDef DIR

                mov cx, 16
                mov ebx,1
GND00:
                mov byte ptr [edi+ebx], 32
                inc ebx
                loop GND00

                mov byte ptr [edi+15],0

                mov al, [edx]
                .while al!=0
                  .if al!=0
                     mov [edi+1], al
                  .else
                     mov byte ptr [edi+1],32
                  .endif
                  mov byte ptr [edi+16], al

                  inc edi
                  inc edx
                  mov al, [edx]
                .endw

                mov byte ptr [edi+16],0

	.endif

GND02:
                ;; FindNext DIR
		call ss_findnext
                jc NoMoreDirs

                mov edx, offset Dta;Ptr
	mov al,[edx+15h]
        and al,Directory
	.if al==Directory


                add edx, 1eh ;+1

                mov edi, DestName
                add DestName, 32
                mov byte ptr [edi],2		; TypeDef DIR

                mov cx, 16
                mov ebx,1
GND01:
                mov byte ptr [edi+ebx], 32
                inc ebx
                loop GND01

		mov byte ptr [edi+15],0


                mov al, [edx]
                .while al!=0
                  .if al!=0
                     mov [edi+1], al
                  .else
                     mov byte ptr [edi+1],32
                  .endif
                  mov byte ptr [edi+16], al

                  inc edi
                  inc edx
                  mov al, [edx]
                .endw
                mov byte ptr [edi+16],0

	.endif
;                sub edi,13
     		jmp GND02

                ;; Ok! We've finished searching for Directories

NoMoreDirs:
                ;; FindFirst File...
		mov cx, 0;Archived
                mov edx, offset ALL_IMA
		call ss_findfirst
                jc NoMoreFiles

                mov edx, offset Dta
                add edx, 1eh ;+1
                mov edi, DestName
                add DestName, 32
                mov byte ptr [edi],1		; TYPEDEF FILE

                mov cx, 16
                mov ebx,1
GN100:
                mov byte ptr [edi+ebx], 32
                inc ebx
                loop GN100

                mov byte ptr [edi+15],0

                mov al, [edx]
                .while al!=0
                  .if al!=0
                     mov [edi+1], al
                  .else
                     mov byte ptr [edi+1],32
                  .endif
                  mov byte ptr [edi+16], al

                  inc edi
                  inc edx
                  mov al, [edx]
                .endw
                mov byte ptr [edi+16],0

GN002:
                ;; FindNext File
		call ss_findnext
                jc NoMoreFiles


                mov edx, offset Dta;Ptr
                add edx, 1eh ;+1

                mov edi, DestName
                add DestName, 32
                mov byte ptr [edi],1		; TYPEDEF FILE

                mov cx, 16
                mov ebx,1
GN101:
                mov byte ptr [edi+ebx], 32
                inc ebx
                loop GN101

		mov byte ptr [edi+15],0


                mov al, [edx]
                .while al!=0
                  .if al!=0
                     mov [edi+1], al
                  .else
                     mov byte ptr [edi+1],32
                  .endif
                  mov byte ptr [edi+16], al

                  inc edi
                  inc edx
                  mov al, [edx]
                .endw
                mov byte ptr [edi+16],0
;                sub edi,13
     		jmp GN002

NoMoreFiles:

		mov edi, DestName
		mov byte ptr [edi], -1

                sub edi, _himembase
                sub edi,512*1024
                mov eax,edi
                shr eax, 5
                mov [NbFiles],ax

                mov eax, DtaPtr
                shr eax,4
                mov ebx, DtaPtr
                and ebx,15
                mov v86r_ds, ax
                mov v86r_dx, bx
                mov v86r_ah, 1ah
                mov al, 21h
                int 33h

                call TrierFichiers

                popall
                ret

DoDir		ENDP

;-----------------------------------------------------------------------


Mousie		     PROC NEAR PASCAL
                     pushall
		     ss_readmouse offset mouse_obj
		     mov ax, mouse_obj.x
	             mov bx, mouse_obj.y
                     mov cx, mouse_obj.boutons

               	     .if ax!=mouse_obj.oldx || bx!=mouse_obj.oldy
                       ; call InfoZone
	   	       ss_undrawmouse 0,0
	               ss_drawmouse 0,0
                     .endif
                     popall
		     ret

Mousie		     ENDP
;-----------------------------------------------------------------------


DebugBreak MACRO _text_
                invoke _debugbreak, _text_
		ENDM

_DebugBreak PROTO NEAR PASCAL :DWORD
_DebugBreak PROC NEAR PASCAl, _text_:DWORD
                push ax
                pushall
		print _text_
                popall
                ss_getax
                .while al!=32
                  ss_getax
                .endw
                pop ax
		ret
_DebugBreak ENDP


;-----------------------------------------------------------------------

GetPspAdrr PROC NEAR PASCAL
;---------
; Execute a DOS function call from PMODE. Then return the result
; in ESI.
; IN: none
; OUT: ESI is the PSP address , offset of CODE32

                mov esi, _pspa
                ret


GetPspAdrr	ENDP

;--------------------------------------------------------------------

align 4
Args_data  db 256 DUP (0)		; Data information for each args
Args_table dd 16 DUP (0)                ; Table (array) of args.
PSP_Copy   db 256 DUP (0)		; Copy of the PSP table
NbArgs     dw 0				; Number of Args on command line

SeparateArgs PROC NEAR PASCAL
;-----------
; Fill-in the args_table. Call GetPspAddr. Must be called before
; any disk access or PSP lost. Args_table provide a facility
; similar to those you find in C compiler. Neat. yeah! It also
; copy the PSP to a secure area for further reference.

		pushall

                mov NbArgs,0
                ; Getting PSP addr into ESI
		call GetPspAdrr

                ; copy the PSP to a secure location.
                xor ebx,ebx
                mov edi, offset PSP_Copy
                mov cx, 256
                .while cx!=0
		  mov al, gs:[esi+ebx]
                  mov byte ptr [edi+ebx], al
                  inc ebx
                  dec cx
                .endw
		;debugbreak offset TEXT5

                mov esi,edi
                add esi,80h
                xor dx,dx
                mov dl, [esi]
                inc esi
                mov edi, offset Args_data
                mov ebx, offset args_table
		;debugbreak offset TEXT8

                .while dl!=0
		;debugbreak offset TEXT7

                  mov al, [esi]
                  .while al==32 && dl!=0
                     inc		 esi
                     dec dl
                     mov al,[esi]
                  .endw

                  .if dl!=0
                    inc NbArgs
                    mov [ebx], edi
                    add ebx,4
    		    ;debugbreak offset TEXT6
                  .endif

                  .if al!=32 && dl!=0
                     .if al>="a" && al <="z"
                       add al,"A"
                       sub al,"a"
                     .endif
                     mov [edi],al
                     inc edi
                     inc esi
                     mov al, [esi]
                     dec dl
                  .endif

                  .while al!=32 && al!=0 && al!="/" && dl!=0
                     .if al>="a" && al <="z"
                       add al,"A"
                       sub al,"a"
                     .endif
                    mov [edi],al
                    inc edi
                    inc esi
                    mov al, [esi]
                    dec dl
                  .endw

                   mov byte ptr [edi],0
                   inc edi
                   mov byte ptr [edi],"$"
                   inc edi

                .endw


                ;print Args_table
                ;printcr

                ;print Args_table+4
                ;printcr

                ;print Args_table+8
                ;printcr

                ;print Args_table+12
                ;printcr

                ;print Args_table+16
                ;printcr

                ;debugbreak offset TEXT9

                popall
		ret
SeparateArgs  ENDP

;-------------------------------------------------------------------
;
; PMODE ASM version of STRCMP
; Be sure that string is terminated by a '/0'.
;

StrCmp		MACRO _S_, _D_
                invoke _strcmp, _S_, _D_
		ENDM

_StrCmp		PROC NEAR PASCAL, _S_:DWORD, _D_:DWORD

                push esi
                push edi
		mov esi, _S_
                mov edi, _D_

                xor al,al
                .while byte ptr [esi]!=0 && byte ptr [edi]!=0 && al==0
                   inc edi
                   inc esi
                   mov al, [esi]
                   sub al, [edi]
                .endw

                mov al, [esi]
                sub al, [edi]

                pop edi
                pop esi
                ret

_StrCmp 	ENDP

;####################################################################
;
; Trier fichier (en ordre alphabétique) Et c'est en temps, non?
;
;####################################################################
align 4
tempnom		dd 4 DUP (0)
TamponPtr	dd 0
FileListPtr	dd 0
LoFilePtr	dd 0
HiFilePtr	dd 0
LoDirPtr	dd 0
HiDirPtr	dd 0
FileCpt		dw 0

TrierFichiers PROC NEAR PASCAL


		pushall
		mov esi, _himembase
                add esi, 512*1024
		add esi, 32*4

		mov edi, _lomembase

		mov ax, NbFiles
                sub ax,4
                mov FileCpt,ax

                mov LoDirPtr, esi
		.while ax!=0 && byte ptr [esi]!=-1 && byte ptr [esi]!=IMAGE_FNT
                    add esi,32
                    dec ax
                .endw

                mov HiDirPtr,esi
                cmp esi, LoDirPtr
                je NoDir2Sort

                mov ecx, LoDirPtr
                mov edx, HiDirPtr
                call SortFiles



NoDir2Sort:

                mov LoFilePtr, esi
		.while ax!=0 && byte ptr [esi]!=-1
                    add esi,32
                    dec ax
                .endw

                mov HiFilePtr,esi
                cmp esi, LoFilePtr
                je NoFile2Sort

                mov ecx, LoFilePtr
                mov edx, HiFilePtr
                call SortFiles
NoFile2Sort:


		popall
		ret
TrierFichiers	ENDP

;--------------------------------------------------------------------
SortFiles:
;========
		pushall
                mov esi,ecx
                .while esi!=edx
                  mov ebx,esi
                  add ebx,32
                  .while ebx!=edx
                    strcmp <esi>, <ebx>
                    ; S-D
                    ; IF S>D +
                    ; IF S<D -
                    .if ax<=80h
                      invoke exchange, esi, ebx
                    .endif
                    add ebx,32
                  .endw
                  add esi,32
                .endw

                popall
                ret


;--------------------------------------------------------------------
Copy4dd PROTO NEAR PASCAL :DWORD, :DWORD
Copy4dd PROC  NEAR PASCAL, _D_:DWORD, _S_:DWORD
		pushall

                mov esi, _S_
                mov edi, _D_

                mov cx,8
                .while cx!=0
                  mov eax, [esi]
                  mov [edi],eax
                  add esi,4
                  add edi,4
                  dec cx
                .endw

                popall
		ret
Copy4dd ENDP
;------------------------------------------------------------------

Exchange PROTO NEAR PASCAL :DWORD, :DWORD
Exchange PROC  NEAR PASCAL, _1_:DWORD, _2_:DWORD
		pushall
		invoke copy4dd, offset tempnom, _1_
                invoke copy4dd, _1_, _2_
                invoke copy4dd, _2_, offset tempnom
                popall
                ret

Exchange ENDP


;-----------------------------------------------------------------------

;Args_table
ControlArgs PROC NEAR PASCAL
                pushall
		mov ebx, offset Args_table
                mov esi,[ebx]
                mov ax,1
                .while esi!=0

                   ;StrCmp <esi>, offset QuietArg1
                   .if al==0
                     mov QuietPMODE,1
                   .endif

                   ;StrCmp <esi>, offset QuietArg2
                   .if al==0
                     mov QuietPMODE,1
                   .endif
                   add ebx,4
                   mov esi,[ebx]
                .endw
                popall
                ret

ControlArgs ENDP


;#######################################################################
; NEW MODULE STARTS HERE...
;#######################################################################
;;
;;  CONSTANTES
;;

app_color          EQU 01040104h

;; Definition des zones de l'interface
grildtopx          EQU 8			; grille d'édition
grildtopy  	   EQU 8
grildlen   	   EQU (512-8-8-8 -6*8  +8)
grildhei   	   EQU (256-16+8)

imagetopx          EQU GrildTopX + grildlen +8	; Image portion shown
imagetopy  	   EQU 8
imagelen   	   EQU 640-8- ImageTopX
imagehei   	   EQU 16*8

paltopx    	   EQU 8			; pallette de couleur
paltopy    	   EQU 256+8
pallen	   	   EQU 640-16
palhei 	   	   EQU 400-8-paltopy

;; Zone de l'interface en plein écran
ImageFTopX 	   EQU (640-(64*8))/2
ImageFTopY         EQU 8
ImageFHei          EQU 400-8
ImageFLen          EQU 64*8

;; Emplacements mémoires
SCREEN             EQU 0
IMAGE      	   EQU SCREEN + 256*1024

;; Définitions de l'interface
Zone_grild 	   EQU 1
Zone_image 	   EQU 2
Zone_pal   	   EQU 3
Zone_none  	   EQU 0

;; ColorBox
ColorBoxX  	   EQU imagetopx+ imagelen/4
ColorBoxY          EQU imagetopy+ imagehei+16
ColorBoxLen        EQU imagelen/2
ColorBoxHei        EQU 16

;; Layouts
NormalLayout	   EQU 0
AllZoneLayout	   EQU 1

;; Image handling
ImageLastFNToffset EQU (GrildLen /8) -8 + ((GrildHei /8)-7) *640
ImageFLsFNTOffset  EQU ImageLen-8 + (ImageHei-8)*640

;;
;; VARIABLES
;;

align 4
MinLowMem          dd 256*1024		; Requiered based Memory (in K)
MinXMSMem          dd 1*1024*1024	; Requiered XMS (in K)
oldmode            dw 0			; Old Video mode
;FileBuf 	   db 4096 DUP (0)	; File Transfer Buffer
Zone	   	   db 0			; Current Zone
Color	   	   db 0			; Current dropDown Color

align 4
WGranDD		   dd 0
ImageBuffer	   dd 0			; Memory location of ImageBuffer
LDX	   	   dw -1		; Last Mouse TouchDown position
LDY	   	   dw -1                ; Last Mouse TouchDown position

MX		   dw 0			; X Top of image from mem
MY		   dw 0			; Y Top of image from mem
VX		   dw 0			; X Top of visual grild
VY		   dw 0			; Y Top of visual grild
Timer		   dw 0			; Internal timer
ParamColor	   dw 1			; ParamColor

ALL_IMA		   db "*.IMA",0,"$"
ALL_FNT		   db "*.FNT",0,"$"
_IMA		   db ".IMA",0
_FNT		   db ".FNT",0
FileFound	   db 13+1 DUP (0)

align 2
Ima2Bytes	   db 0,0

;########################################################################
 module_start PROC NEAR
;########################################################################

		call InitFileSys
		call useMOUSEICO
		call InitSVGA
                call SetWGranDD
		call CleanScreen
                call DrawAllWins
                call DrawPalColors
                call FillWithJunk
                call RedrawGrild
                call RedrawImage
		call ShowScreen

                call DrawColorBox
                call WriteCopyrights
		call InitMouse

		ss_readmouse offset mouse_obj
                call InfoZone
		ss_drawmouse offset 0,0
		ss_getax
		 .while al==al
		     call DealWithKeys
		     ss_readmouse offset mouse_obj

		     mov ax, mouse_obj.x
		     mov bx, mouse_obj.y
                     mov cx, mouse_obj.boutons

                     mov si,ax
                     shr si,3
                     mov di,bx
                     shr di,3

                     inc Timer
                     .if word ptr Timer >=5
			mov word ptr Timer,0
                        inc word ptr ParamColor
                        .if word ptr ParamColor>=15
                           mov ParamColor,1
                        .endif
                        call DrawParams
                     .endif


                     .if cx==1 && (LDX!= si || LDY!=di)
  			 call InfoZone
                         call gereBouton1
                         mov ldx,si
                         mov ldy,di
		     .endif

;		     mov ax, mouse_obj.x
;		     mov bx, mouse_obj.y
;                     mov cx, mouse_obj.boutons


                     .if ax!=mouse_obj.oldx || bx!=mouse_obj.oldy
                          call InfoZone
			  ss_undrawmouse 0,0
		          ss_drawmouse 0,0
                     .endif
		     ss_getax
		.endw

_Remove:
		;; Restore your old video mode and leave
		mov bx, word ptr OldMode
		ss_setvesamode bx
		jmp _leave


;##############################################################
; Routines related to module_start
;##############################################################

SetWGranDD:     push eax
		xor eax,eax
		mov ax, Mode_info_obj.WinGranularity
                shl eax,10
                mov WGranDD, eax
                pop eax
                ret


;--------------------------------------------------------------------

TXT_WantToQuit	db "Are you sure you want to quit? (Y/N)?                                           ",0

WantToQuit:
;---------
                pushall
		outtext 0, 0, offset TXT_WantToQuit, 15, 4
WantToQuit00:
		ss_getax
		.if al>="a" && al<="z"
                   add al, "A"
                   sub al ,"a"
                .endif

                .if al=="Y" || al=="O"
                   jmp _Remove
                .else
                   .if al=="N" || al==27
    		      ss_setfastwindow 0, 0*65536/4096, mode_info_obj.WinFuncPtr
                      mov esi, _himembase
                      mov edi, 0a0000h
                      mov cx, 640*8/4
                      mov eax, app_color
WTQ000:
                      ;mov eax, [esi]
                      mov gs:[edi],eax
                      ;add esi,4
                      add edi,4
                      loop WTQ000
                      call InfoZone
                      popall
                      ret
                   .endif
                .endif

                     inc Timer
                     .if word ptr Timer >=5
			mov word ptr Timer,0
                        inc word ptr ParamColor
                        .if word ptr ParamColor>=15
                           mov ParamColor,1
                        .endif
                        call DrawParams
                     .endif

		ss_readmouse offset mouse_obj
	        mov ax, mouse_obj.x
	        mov bx, mouse_obj.y
                mov cx, mouse_obj.boutons

               .if ax!=mouse_obj.oldx || bx!=mouse_obj.oldy
                 ; call InfoZone
	   	  ss_undrawmouse 0,0
	          ss_drawmouse 0,0
                .endif


                jmp WantToQuit00


;-----------------------------------------------------------------------
WriteCopyrights:
;--------------

		outtext  8*4,400-8, offset TXT_OBLEDIT, 15,0;color
;                outtextb 8*4,400-8, offset TXT_OBLEDIT, 15,0;color
                ret

;-----------------------------------------------------------------------
;
;AskQuestion PROC NEAR PASCAL _TEXT_:DWORD, _CHOICE_:DWORD, _FCOLOR_:BYTE, _BCOLOR_:BYTE;;
; invoke AskQuestion , _TEXT_, _CHOICE_, _FCOLOR_, _BCOLOR_

;
TXT_WANTOSAVE	      db "Do you want to save the work grild? (Y/N)?",0
CHC_WANTOSAVE	      db "YN",27,0
TXT_WANTOLOAD	      db "Do you want to load a work grild? (Y/N)?",0
CHC_WANTOLOAD	      db "YN",27,0
TXT_WANTOCLEAR	      db "Do you want to clear the work grild? (Y/N)?",0
CHC_WANTOCLEAR	      db "YN",27,0

DealWithKeys:
                     .if al==27
                        call WantToQuit
                     .endif

                     .if al=="8" || ah==KEY_UP; && word ptr MY!=0	; move UP
                     	call MoveUp
                     .endif

                     .if al=="2" || ah==KEY_DN;&&  word ptr MY<40	; move DN
                     	call MoveDn
                     .endif

                     .if al=="4" || ah==KEY_LF;&&  word ptr MX!=0	; move LEFT
                     	call MoveLf
                     .endif

                     .if al=="6" || ah==KEY_RG;&&  word ptr MX<50	; move RIGHT
                     	call MoveRg
                     .endif

                     .if al=="S" || al=="s"
                        pushall
                        invoke AskQuestion , offset TXT_WANTOSAVE, offset CHC_WANTOSAVE, 15, 2
                        .if al==0
                     	call SaveXnt
                        .endif
                        popall
                     .endif

                     .if al=="L" || al=="l"
                     	pushall
                        invoke AskQuestion , offset TXT_WANTOLOAD, offset CHC_WANTOLOAD, 15, 2
                        .if al==0
                           call LoadXnt
                           popall
                	   call RedrawGrild
                	   call RedrawImage
                	   call ShowScreen2
			   call DrawColorBox
		           ss_drawmouse 0,0
                        .else
                           popall
                        .endif

                     .endif

                     .if al=="C" || al=="c"
                        pushall
                        invoke AskQuestion , offset TXT_WANTOCLEAR, offset CHC_WANTOCLEAR, 15, 2
                        .if al==0
                     	  call FillWithJunk
                          popall
                	  call RedrawGrild
                	  call RedrawImage
                	  call ShowScreen2
			  call DrawColorBox
		          ss_drawmouse 0,0
                        .else
                          popall
                        .endif
                     .endif

                     .if ah==KEY_F1 ; al=="h" || al=="H"
                        call GeneralHelpSys
                     .endif


                     .if ah==KEY_F3
                     	call GereImaDir
                     .endif

                     .if ah==KEY_F4
                        call MakeSelection
                     .endif

                     .if ah==KEY_F5
                        call FullScreenView
                     .endif

                     .if ah==KEY_F6 ||  ah==KEY_F7 ||  ah==KEY_F8
                        call gereChangeDir
                     .endif

                     .if ah==KEY_F10
                       call SpecialOptions
                     .endif

                     .if al==" "
                         mov color,0
                         ss_undrawmouse
                         call DrawColorBox
                         ss_drawmouse
                     .endif

                     ret

;----------------------------------------------------------------------

MoveUp:
;-----
                .if VY!=0
   		  dec  word ptr VY
                  call RedrawGrild
                  call RedrawImage
                  .if Mouse_obj.Y >= PalTopY
                      ss_undrawmouse 0,0
                  .endif
                  ;ss_undrawmouse 0,0
                  call ShowScreen2
		  call DrawColorBox
                     call Drawparams
                  ss_drawmouse 0,0

                .else
                   .if MY!=0
   		     dec  word ptr MY
                     call RedrawGrild
                     call RedrawImage
                     .if Mouse_obj.Y >= PalTopY
                        ss_undrawmouse 0,0
                     .endif
                     ;ss_undrawmouse 0,0
                     call ShowScreen2
		     call DrawColorBox
                     call Drawparams
                     ss_drawmouse 0,0

                   .endif
                .endif

                ret
;-----------------------------------------------------------------------


MoveDn:
;-----
                mov dx, ImageHei
                shr dx,3
                sub dx,4

                .if word ptr VY!= dx ;((ImageHei/8) -4)
		     pushall
                     inc  word ptr VY
                     call RedrawGrild
                     call RedrawImage
                     .if Mouse_obj.Y >= PalTopY
                        ss_undrawmouse 0,0
                     .endif
                     ;ss_undrawmouse 0,0
                     call ShowScreen2
		     call DrawColorBox
                     call Drawparams
		     ss_drawmouse 0,0
                     popall
		.else
                   .if MY!=48 - Imagehei/8 ; Original Value was 40
		     pushall
                     inc  word ptr MY
                     call RedrawGrild
                     call RedrawImage
                     .if Mouse_obj.Y >= PalTopY
                        ss_undrawmouse 0,0
                     .endif
                     ;ss_undrawmouse 0,0
                     call ShowScreen2
		     call DrawColorBox
                     call Drawparams
                     ss_drawmouse 0,0
                     popall
                   .endif
                .endif
		ret

;-----------------------------------------------------------------------

MoveLf:
;-----

                .if VX!=0
	       	   dec  word ptr VX
                   call RedrawGrild
                   call RedrawImage
                   .if Mouse_obj.Y >= PalTopY
                      ss_undrawmouse 0,0
                   .endif
                   ;ss_undrawmouse 0,0
                   call ShowScreen2
		   call DrawColorBox
                     call Drawparams
		   ss_drawmouse 0,0
                .else
                   .if MX!=0
		      dec  word ptr MX
                      call RedrawGrild
                      call RedrawImage
                      .if Mouse_obj.Y >= PalTopY
                         ss_undrawmouse 0,0
                      .endif
                      ;ss_undrawmouse 0,0
                      call ShowScreen2
		      call DrawColorBox
                     call Drawparams
		      ss_drawmouse 0,0
                   .endif
                .endif
		ret

;-----------------------------------------------------------------------

MoveRg:
;-----

                mov dx, ImageLen
                shr dx,3
                sub dx,7
                .if VX!= dx ; ((ImageLen/8) -7)
		   inc  word ptr VX
                   call RedrawGrild
                   call RedrawImage
                   .if Mouse_obj.Y >= PalTopY
                      ss_undrawmouse 0,0
                   .endif
;                   ss_undrawmouse 0,0
                   call ShowScreen2
		   call DrawColorBox
                     call Drawparams
		   ss_drawmouse 0,0
                .else
                   .if MX!= (64 - (ImageLen/8)); Original Value was 50
		      inc  word ptr MX
                      call RedrawGrild
                      call RedrawImage
                      .if Mouse_obj.Y >= PalTopY
                         ss_undrawmouse 0,0
                      .endif
                      call ShowScreen2
		      call DrawColorBox
                     call Drawparams
		      ss_drawmouse 0,0
                   .endif
                .endif


		ret

;----------------------------------------------------------------------

TestXNT	db "TEST.XNT",0
ERR_SAVETESTXNT db "WARNING: Unable to creat test.xnt         ",0

SaveXNT:
;------

    		mov edx, offset TestXNT
                call _createfile	; V86r_bx = handle
                jc ErrSaveXNT

		mov edx, _himembase
                add edx, 256*1024
                mov ecx, 256*1024
                call _writefile
                jc ErrSaveXNT

                call _closefile
                jc ErrSaveXNT
;                         call RedrawGrild
;;                	 call RedrawImage
;                     	 call ShowScreen

                ret

ErrSaveXnt:

		outtext 0,0, offset ERR_SAVETESTXNT, 0, 14
                ret

;----------------------------------------------------------------------
ERR_LOADTESTXNT db "WARNING: Unable to load test.xnt             ",0
LoadXNT:
;------
    		mov edx, offset TestXNT
                call _openfile; V86r_bx = handle
                jc ErrLoadXNT

		mov edx, _himembase
                add edx, 256*1024
                mov ecx, 256*1024
                call _readfile
                jc ErrLoadXNT

                call _closefile
                jc ErrLoadXNT


		ret

ErrLoadXnt:

		outtext 0,0, offset ERR_LOADTESTXNT, 0, 14
                ret


;----------------------------------------------------------------------
FatalReadErr:
;-----------
  		print offset TXT_FatalReadErr
		jmp _leave

;----------------------------------------------------------------------

UseMOUSEICO:
;----------

	;pushall
	mov cx, 256


	mov esi, offset MOUSE_ICO
	;add esi, eax
	mov edi, offset MOUSE_OBJ.MOUSE
	;add edi, eax

X00013:
	mov al, ds:[esi]
	mov ds:[edi], al
	inc esi
	inc edi
	loop X00013
	;popall
	ret

;----------------------------------------------------------------------

InitFileSys:
;----------
	    	;; Define transfer buffer
                push eax
                mov eax, _lomembase
		mov dword ptr _filebufloc, eax;offset FileBuf
		mov word ptr _filebuflen, 65535; 4096
                pop eax
		ret

;----------------------------------------------------------------------

LoadMouseMCG:
;-----------

		;; Load "MOUSE.MCG"
		mov edx, offset MOUSE_MCG
		call _openfile
		jc FatalReadErr
		; v86r_bx = file handle

		mov eax,7
		mov bl, 0
		call _lseekfile
		jc FatalReadErr

		mov edx, offset Mouse_Obj.Mouse
		mov ecx,256
		call _readfile
		jc FatalReadErr

		call _closefile
		;; fin Load "MOUSE.MCG"
		ret

;----------------------------------------------------------------------
InitSVGA:
;-------
		;; Get informations about your SVGA/VESA adapter.
		ss_getvesainfo offset vesa_info_obj ; Get info
		.if v86r_ax!=4fh                    ; about your VESA
		   print offset ERR_XVESA_INFO      ; adapter
		   jmp _leave
		.endif

		;; Get informations about video mode 0x101
		ss_getvesamodeinfo (offset mode_info_obj) , 101h
		.if v86r_ax!=4fh                           ; Get information
		   print offset ERR_XVESA_MODEINFO    ; about mode 101h
		   jmp _leave
		.endif

		;; Get your current SVGA/VESA mode
		ss_getvesamode          ; get current vesa mode
		mov oldmode,bx
		.if v86r_ax!=4fh                ; réussi?
		   print offset ERR_VESA_INIT
		   jmp _leave
		.endif

		mov cx, mode_info_obj.Xresolution
		mov dx, mode_info_obj.YResolution
		mov al, Mode_info_obj.bitsperpixel
		.if cx!=640 || dx!=480 || al!=8
		   print offset ERR_VESA_RES101
		   jmp _leave
		.endif


		;; Set SVGA/VESA video mode to 0x101
		ss_setvesamode 100H; set vesa mode to 0x101
		.if v86r_ax!=4fh                ; réussi?
		   print offset ERR_VESA_INIT
		   jmp _leave
		.endif

		ret

;----------------------------------------------------------------------

RunTest:
;------
		;; Test setfastwindow & blowvideo
		ss_setfastwindow 0, 0*65536/4096, mode_info_obj.WinFuncPtr
		ss_blowvideo 01010101h

		ss_setfastwindow 0, 1*65536/4096, mode_info_obj.WinFuncPtr
		ss_blowvideo 02020202h

		ss_setfastwindow 0, 2*65536/4096, mode_info_obj.WinFuncPtr
		ss_blowvideo 03030303h

		ss_setfastwindow 0, 3*65536/4096, mode_info_obj.WinFuncPtr
		ss_blowvideo 04040404h

		ss_setfastwindow 0, 4*65536/4096, mode_info_obj.WinFuncPtr
		ss_blowvideo 05050505h

		printa dword ptr mode_info_obj.WinFuncPtr
		printcr
		ret

;----------------------------------------------------------------------

InitMouse:
;--------
		; Initialise la souris et redefinie les
		; limites de l'espace de travail
		ss_initmouse offset mouse_obj
		ss_setrangex 0, mode_info_obj.XResolution
		ss_setrangey 0, mode_info_obj.YResolution
		ret

;----------------------------------------------------------------------

CleanScreen:
;----------
                pushall
		xor eax,eax
		mov edi,_himembase
		mov ecx, 256*1024/4

XX00012:
                mov eax, app_color
		mov ds:[edi], eax
		add edi,4

		dec ecx
		or ecx,ecx
		jne XX00012

		xor ecx,ecx
                popall
		ret

;----------------------------------------------------------------------

ShowScreen:
;---------
		mov edi, 0a0000h
		mov esi,_himembase
		ss_setfastwindow 0, 0, mode_info_obj.WinFuncPtr

		cld
		mov edx, 0
		mov bx,5
XX00014:
		mov cx, 65536/4

		mov edi,0a0000h
XX00013:

		mov eax, ds:[esi]
		mov gs:[edi],eax
		add edi,4
		add esi,4
		loop XX00013

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
                push edx	      	; Protect EDX
                mov eax, 65536
                xor edx,edx
                div WGranDD
                pop edx			; Restore EDX
		add edx, eax		; was  65536/4096
  		ss_setfastwindow 0, <dx>, mode_info_obj.WinFuncPtr

		dec bx
		or bx,bx
		jne XX00014
		ret


;----------------------------------------------------------------------

draw_win MACRO _topx_ , _topy_, _len_, _hei_, _color_
	invoke _draw_win, _topx_ , _topy_, _len_, _hei_, _color_
ENDM

DrawAllWins:
;----------
                pushall
                call DrawEditGrild
        	;draw_win grildtopx, grildtopy,grildlen, grildhei, 0
                draw_win imagetopx, imagetopy, imagelen, imagehei, 0
                draw_win PalTopx, PalTopy, PalLen, PalHei, 0
                popall
                ret

;----------------------------------------------------------------------

_CaseX		dw 0
_CaseY		dw 0

DrawEditGrild:
;-------------
		pushall

                mov word ptr _CaseX,-1
                mov word ptr _CaseY,-1

		mov ax, GrildTopY
                mul  word ptr Mode_Info_Obj.XResolution

                shl edx,16
                mov dx,ax        		;edx= y*Xres

                mov eax, GrildTopX		; eax =x
		add edx, eax			; edx = x+ y*XRes
		add edx, _himembase		; edx = edx + videoseg
                mov edi,edx

                xor eax,eax
		mov ax, Mode_info_obj.XResolution
                mov ebx, 21000000h

                mov dx, GrildHei/8

XXG0003:
                  inc _casey
                  .if (word ptr _casey>=8)
                        mov word ptr _casey,0
                  .endif
                  mov word ptr _CaseX,-1
                  push edi
                  mov cx, GrildLen/8

XXG0002:
                    inc _caseX
                    .if (word ptr _caseX>=8)
                        mov word ptr _casex,0
                    .endif

                    push edi
    		    mov si,7

XXG0001:
                      mov dword ptr ds:[edi], 0
                      .if word ptr _casex>=6 || word ptr _casey==7
                        mov dword ptr ds:[edi+4], 0f000000h
                      .else
                        mov dword ptr ds:[edi+4], ebx
                      .endif
                      add edi, eax

                    or si,si
                    dec si
                    jne XXG0001

                     .if word ptr _casex==7 || word ptr _casey>=6
                        mov dword ptr ds:[edi],   0f0f0f0fh
                        mov dword ptr ds:[edi+4], 0f0f0f0fh
                     .else
                       mov dword ptr ds:[edi],   21212121h
                       mov dword ptr ds:[edi+4], 21212121h
                     .endif

                  pop edi
                  add edi,8
		  loop XXG0002_
                  jmp  XXG0002__
XXG0002_:	  jmp  XXG0002
XXG0002__:

                pop edi
                shl eax, 3
                add edi, eax
                shr eax, 3
                mov cx,dx
                dec dx
                or cx,cx
                jne XXG0003
                ;eloop XXG0003

                popall
        	ret

;---------------------------------------------------------------------

align 2
TileX		DW 0
TileY   	DW 0
TileColor 	DB 0

DrawPalColors:
;------------
		pushall

                mov TileColor,0

                mov ax, PalTopX
       		mov TileX, ax

                mov ax, PalTopY
                mov TileY, ax

                add TileX,4
                add TileY,4

                mov dx, 4  +2
XXX0013:
                mov cx, (640-16) / (16+4);16
XXX0012:        draw_win TileX, TileY, 16,16, TileColor
                inc TileColor
                add TileX, 16+4
                loop XXX0012

                mov ax, PalTopX
       		mov TileX, ax

                add TileX,4
                add TileY,16+4
                mov cx,dx
                dec dx
                loop XXX0013

		popall
                ret

;-------------------------------------------------------------------------
InfoZone:
;-------
                pushall
		mov ax, Mouse_obj. X
                mov bx, Mouse_obj. Y

		.if ax>=grildtopx && ax<grildtopx+grildlen && bx>=grildtopy && bx<grildtopy+grildhei+8
		      ;	outtext 0,0, offset TXT_grildzone, 15,1
           		mov zone, zone_grild
                .else
			.if ax>=imagetopx && ax<imagetopx+imagelen && bx>=imagetopy && bx<imagetopy+imagehei
			     ;	outtext 0,0, offset TXT_imagezone, 15,2
                                mov zone, zone_image

                        .else
	                        .if ax>=paltopx && ax<paltopx+pallen && bx>=paltopy && bx<=paltopy+palhei
				    ;	outtext 0,0, offset TXT_palette,15, 3
                                        mov zone, zone_pal
                                .else
				     ;	outtext 0,0, offset TXT_nothing,15, 4
                                        mov zone, zone_none
                                .endif
			.endif

		.endif
                popall
		ret
;---------------------------------------------------------------------

GereBouton1:
;----------
		cmp zone, zone_grild
                je DrawOnGrild

                cmp zone, zone_pal
                je GetColor
		ret

;----------------------------------------------------------------------
; Draw a little square on the drawing grild
;----------------------------------------------------------------------

DropAtX 	DW 0
DropAtY		DW 0

DrawOnGrild:
;----------

                xor eax,eax
		mov ax, Mouse_obj. X
                xor ebx,ebx
                mov bx, Mouse_obj. Y

                .if eax > 640 || ebx > 400
                  jmp DOG00
                .endif

		ss_undrawmouse 0,0

                shr eax,3
                shl eax,3
                shr ebx,3
                shl ebx,3

		drawsqrt <ax>, <bx>, 7,7, color ; draw on screen
;        	draw_win <ax>, <bx>, 7,7, color ; draw in buffer

                xor eax,eax
		mov ax, Mouse_obj. X
                xor ebx,ebx
                mov bx, Mouse_obj. Y

		sub eax, GrildTopX
		sub ebx, GrildTopY

                shr eax,3
		shr ebx,3

                mov DropAtX, ax
                mov DropAtY, bx

                add ax, ImageTopX
                mov cx, VX	;
                shl cx, 3       ;
                add ax, cx      ;

                add bx, ImageTopY
                mov cx, VY      ;
                shl cx,3        ;
                add bx,cx       ;
                drawpix <ax>, <bx>, color

                ;; Empêche de redessiner.
                mov ax, Mouse_obj.X
                mov Mouse_obj.Oldx,ax

                mov ax, Mouse_obj.Y
                mov Mouse_obj.Oldy, ax
		ss_drawmouse 0,0

                ; Update memory buffer

                xor eax,eax
                mov ax, DropAtY
                shr ax, 3
                add ax, MY
                add ax, VY
                shl eax, 6+6		; 64*64 (Y x ligne de FNT)

                xor ebx,ebx
                mov bx, DropAtX
                shr bx, 3
                add bx, MX
                add bx, VX
                shl ebx, 6		; 64 (  X x FNT)

                xor ecx,ecx
                mov cx, DropAtY
                ;shr ecx,3
                and cx,7
                shl ecx,3

                xor edx,edx
                mov dx, DropAtX
                ;shr edx,3
                and dx,7

                mov edi, eax
                add edi, ebx
                add edi, ecx
                add edi, edx
                add edi, _himembase
                add edi, 256*1024
                mov al,color
		mov [edi], al

DOG00:
		ret

;----------------------------------------------------------------------


;                xor eax,eax
 ;               mov ax, _Y_
                mul mode_info_obj. XResolution

                shl edx, 16
                mov dx,ax  			; edx = y * Xres

                xor eax,eax
  ;              mov ax, _X_
                add edx, eax			; edx= y*res+ x
		add edx, _himembase
                mov al,color
                mov [edi], al





;-----------------------------------------------------------------------


GetColor:
;-------
                pushall
                xor eax,eax
		mov ax, Mouse_obj. X
                xor ebx,ebx
                mov bx, Mouse_obj. Y

                sub eax, PalTopX
                sub eax,4
                sub ebx, PalTopY
                sub ebx,4

                xor cx,cx
                .if eax>=640 || ebx>=400
                   jmp GC0001
                .endif

                .while eax>=20
                     inc cx
                     sub eax,20
                .endw

                .while ebx>=20
                    add cx,(640-16)/20
                    sub ebx, 20
                .endw

		ss_undrawmouse 0,0

                mov color,cl
;		outtext 300,0, offset TXT_color, 15,color
		call drawcolorbox
                mov ax, Mouse_obj.X
                mov Mouse_obj.Oldx,ax

                mov ax, Mouse_obj.Y
                mov Mouse_obj.Oldy, ax
		ss_drawmouse 0,0

GC0001:
                popall
         	ret

;--------------------------------------------------------------------

DrawColorBox:
;-----------
                drawsqrt ColorBoxX,ColorBoxY,ColorBoxLen,ColorBoxHei,Color
		ret

;--------------------------------------------------------------------
align 2
NoLine		dw 0
NoFNT		dw 0
LigneFNT	dw 0
CaseFNT		dw 0

RedrawGrild:
;----------
; XIM
;   64x FNT
;   50x FNT
;
		pushall

                ; Get destination TOP adresse in EDI
                mov ax, GrildTopy
                mul word ptr mode_info_obj. xResolution

                shl edx,16
                mov dx,ax			       	; edx = y* Res

                xor eax,eax
                mov ax, GrildTopX			; eax= x

                add edx,eax                             ; edx=  x+y*res
                mov edi,edx				; edi= edx
                add edi, _himemBase
;                add edi, 256*1024

                ; Get source adresse in ESI
                xor eax,eax
                mov ax, MX                              ; TopX of Image
                add ax, VX
                shl eax, 6				; x64 (block size)

                xor ebx,ebx				;
		mov bx, MY                              ; TopY of Image
                add bx, VY
                shl ebx, 6+6				; x64x64

                add eax,ebx
                add eax, _himembase
                mov esi,eax
                add esi, 256*1024

                xor ebx,ebx
                mov bx,mode_info_obj. xResolution

                ;--------------------------------

                mov word ptr NoLine, 4;(GrildHei/8  -1)/8
XRG005:         				   ;1
		push edi
                push esi
                mov word ptr NoFNT, 7; (GrildLen/8)/8

XRG004:
		push edi                           ;2
		mov word ptr LigneFNT, 8

XRG003:         push edi                           ;3
		mov word ptr CaseFNT,8

XRG002:                                            ;4
		mov al, [esi]
                mov ah,al
                push ax
                shl eax,16
                pop ax
                push edi

                mov cx,7		; 8xligne x4points

XRG001:                                            ;5
		mov [edi], eax
                mov [edi+4], ax
                mov [edi+6], al				; 1xpts
                ;add edi,ebx
                add edi,640
		loop XRG001                        ;5

                inc esi
                pop edi                             	; 8xpts
                add edi,8
                dec word ptr CaseFNT
                cmp word ptr CaseFNT,0
                jne XRG002			   ;4

                pop edi					; 1xcase
                add edi,640*8; ebx
                dec word ptr LigneFNT
                cmp word ptr LigneFNT,0
                jne XRG003                         ;3

                pop edi					; 1xligne (x case)
                add edi,64
                dec word ptr NoFNT
                cmp word ptr NoFNT,0
                jne XRG004			   ;2

                pop esi					; xxligne
                pop edi
               ;shl ebx,3
                add edi,  640*8*8		; ebx
               ;shr ebx,3
                add esi,64*64
                dec word ptr NoLine
                cmp word ptr NoLine,0
                jne XRG005                        ;1

		popall
                ret

;---------------------------------------------------------------------

FillWithJunk:
;-----------

		mov edi, _himembase
                add edi,256*1024
                mov esi, 0
 		xor eax,eax
                mov ecx, 256*1024/4
FWJ:
                mov eax,0; [esi]

                mov [edi],eax

                add edi,4
                add esi,4
                ;loop FWJ
                or ecx,ecx
                dec ecx
                jne FWJ

                ret

;---------------------------------------------------------------------

align 2
Line2Draw	dw 0
Sqr2Draw	dw 0
LineInSqr	dw 0

RedrawImage:
;----------

		pushall

                ; Get destination TOP adresse in EDI
                mov ax, ImageTopy
                mul word ptr mode_info_obj. xResolution

                shl edx,16
                mov dx,ax			       	; edx = y* Res

                xor eax,eax
                mov ax, ImageTopX			; eax= x

                add edx,eax                             ; edx=  x+y*res
                mov edi,edx				; edi= edx
                add edi, _himemBase
;                add edi, 256*1024

                ; Get source adresse in ESI
                xor eax,eax
                mov ax, MX                              ; TopX of Image
                ;add ax, VX
                shl eax, 6				; x64 (block size)

                xor ebx,ebx				;
		mov bx, MY                              ; TopY of Image
                ;add bx, VY
                shl ebx, 6+6				; x64x64

                add eax,ebx
                add eax, _himembase
                mov esi,eax
                add esi, 256*1024

                mov word ptr Line2Draw, ImageHei/8
Ri002:
                push edi
                push esi
                mov word ptr Sqr2Draw, ImageLen/8
Ri001:
                push edi
                mov word ptr LineInSqr, 8

Ri000:
		mov eax, [esi]
                mov [edi], eax
		mov eax, [esi+4]
                mov [edi+4], eax

                add esi,8
                add edi,640
                dec LineInSqr
                cmp LineInSqr,0
                jne Ri000

                pop edi
                add edi,8
                dec Sqr2Draw
                cmp Sqr2Draw,0
                jne Ri001

                pop esi
                pop edi
                add edi, 640*8
                add esi, 64*64
                dec Line2Draw
                cmp Line2Draw,0
                jne Ri002

                popall
		ret

;---------------------------------------------------------------------


ShowScreen2:
;---------
		mov edi, 0a0000h
		mov esi,_himembase
		ss_setfastwindow 0, 0, mode_info_obj.WinFuncPtr

		cld
		mov edx, 0
		mov bx,3
XX00214:
		mov cx, 65536/4

		mov edi,0a0000h
XX00213:

		mov eax, ds:[esi]
		mov gs:[edi],eax
		add edi,4
		add esi,4
		loop XX00213

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
                push edx	      	; Protect EDX
                mov eax, 65536
                xor edx,edx
                div WGranDD
                pop edx			; Restore EDX
		add edx, eax		; was  65536/4096
  		ss_setfastwindow 0, <dx>, mode_info_obj.WinFuncPtr

                ;; Was...
		;;add edx, 65536/4096
  		;;ss_setfastwindow 0, <dx>, mode_info_obj.WinFuncPtr

		dec bx
		or bx,bx
		jne XX00214
		ret
;------------------------------------------------------------------

HelpStr001	db "=============== HELP ==================",0
HelpStr002	db "                                1/4    ",0
HelpStr003	db "                                       ",0
HelpStr004	db "   These screens contains an online    ",0
HelpStr005	db "   help to using STATICS V3.           ",0
HelpStr006	db "                                       ",0
HelpStr007	db "   Use the fallowing key to travel:    ",0
HelpStr008	db "                                       ",0
HelpStr009	db "   [B]                  Backtrack      ",0
HelpStr00a	db "                                       ",0
HelpStr00b	db "   [N]                  NextScreen     ",0
HelpStr00c	db "                                       ",0
HelpStr00d	db "   [Q]/[ESC]            Leave help     ",0
HelpStr00e	db "                                       ",0
HelpStr00f	db "                                       ",0
HelpStr010	db "                                       ",0
HelpStr011	db "       STATICS V3 IS SHAREWARE         ",0
HelpStr012	db "                                       ",0
HelpStr013	db "                                       ",0
HelpStr014	db "                                       ",0
HelpStr015	db "               Q>UIT         N>EXT     ",0
HelpStr016	db "                                       ",0
HelpStr017	db "=======================================",0

HelpStr101	db "=============== HELP ==================",0
HelpStr102	db "                                2/4    ",0
HelpStr103	db "                                       ",0
HelpStr104	db "   General guide line on using this    ",0
HelpStr105	db "   software.                           ",0
HelpStr106	db "                                       ",0
HelpStr107	db "   Use the mouse and the left button   ",0
HelpStr108	db "   to draw.                            ",0
HelpStr109	db "                                       ",0
HelpStr10a	db "   Use CURSOR KEYS to move the image   ",0
HelpStr10b	db "   up and down.                        ",0
HelpStr10c	db "                                       ",0
HelpStr10d	db "   Read messages carefully before      ",0
HelpStr10e	db "   proceding.                          ",0
HelpStr10f	db "                                       ",0
HelpStr110	db "   Press F1 to get help.               ",0
HelpStr111	db "                                       ",0
HelpStr112	db "                                       ",0
HelpStr113	db "                                       ",0
HelpStr114	db "                                       ",0
HelpStr115	db "   B>ACK       Q>UIT         N>EXT     ",0
HelpStr116	db "                                       ",0
HelpStr117	db "=======================================",0

HelpStr201	db "=============== HELP ==================",0
HelpStr202	db "                                3/4    ",0
HelpStr203	db "                                       ",0
HelpStr204	db "   Quick keyboard reference            ",0
HelpStr205	db "   ------------------------            ",0
HelpStr206	db "                                       ",0
HelpStr207	db "   F3                  LOAD IMAGE      ",0
HelpStr208	db "   F4                  SELECT ZONE *   ",0
HelpStr209	db "   F5                  FULL SCREEN     ",0
HelpStr20a	db "                                       ",0
HelpStr20b	db "                                       ",0
HelpStr20c	db "   +                   SAVE GRILD      ",0
HelpStr20d	db "   -                   LOAD GRILD      ",0
HelpStr20e	db "                                       ",0
HelpStr20f	db "                                       ",0
HelpStr210	db "  * After selecting a zone you will    ",0
HelpStr211	db "    be give the option to SAVE, DELETE ",0
HelpStr212	db "    CUT or MOVE it.                    ",0
HelpStr213	db "                                       ",0
HelpStr214	db "                                       ",0
HelpStr215	db "   B>ACK       Q>UIT         N>EXT     ",0
HelpStr216	db "                                       ",0
HelpStr217	db "=======================================",0

HelpStr301	db "=============== HELP ==================",0
HelpStr302	db "                                4/4    ",0
HelpStr303	db "                                       ",0
HelpStr304	db "   For more informations consult the   ",0
HelpStr305	db "   READ.ME file provided with this     ",0
HelpStr306	db "   file.                               ",0
HelpStr307	db "                                       ",0
HelpStr308	db "   Or, you can contact me to ask       ",0
HelpStr309	db "   questions,  give comments or        ",0
HelpStr30a	db "   report BUGS.                        ",0
HelpStr30b	db "                                       ",0
HelpStr30c	db "   Francois Blanchette                 ",0
HelpStr30d	db "   3825 Bazin                          ",0
HelpStr30e	db "   Brossard                            ",0
HelpStr30f	db "   Quebec, Canada                      ",0
HelpStr310	db "   J4Z-2J3                             ",0
HelpStr311	db "                                       ",0
HelpStr312	db "   (514) 462-2755                      ",0
HelpStr313	db "                                       ",0
HelpStr314	db "                                       ",0
HelpStr315	db "   B>ACK       Q>UIT                   ",0
HelpStr316	db "                                       ",0
HelpStr317	db "=======================================",0

HelpScrHei	EQU 15
HelpScrLen      EQU 39
HelpScrX	EQU (640 - (39*8))/2
HelpScrY	EQU 16+8+16*3
HelpTColor	EQU 15
HelpBColor	EQU 1
HelpScreens	EQU 4-1

DrawHelpScreen:
;-------------
align 4
HelpDat1	DD offset HelpStr001,offset HelpStr002,offset HelpStr003
                DD offset HelpStr004,offset HelpStr005,offset HelpStr006
                DD offset HelpStr007,offset HelpStr008,offset HelpStr009
                DD offset HelpStr00a,offset HelpStr00b,offset HelpStr00c
                DD offset HelpStr00d
                DD offset HelpStr00e,offset HelpStr00f,offset HelpStr010
                DD offset HelpStr011,offset HelpStr012,offset HelpStr013
                DD offset HelpStr014,offset HelpStr015,offset HelpStr016
                DD offset HelpStr017, -1


HelpDat2	DD offset HelpStr101,offset HelpStr102,offset HelpStr103
                DD offset HelpStr104,offset HelpStr105,offset HelpStr106
                DD offset HelpStr107,offset HelpStr108,offset HelpStr109
                DD offset HelpStr10a,offset HelpStr10b,offset HelpStr10c
                DD offset HelpStr10d
                DD offset HelpStr10e,offset HelpStr10f,offset HelpStr110
                DD offset HelpStr111,offset HelpStr112,offset HelpStr113
                DD offset HelpStr114,offset HelpStr115,offset HelpStr116
                DD offset HelpStr117, -1


HelpDat3	DD offset HelpStr201,offset HelpStr202,offset HelpStr203
                DD offset HelpStr204,offset HelpStr205,offset HelpStr206
                DD offset HelpStr207,offset HelpStr208,offset HelpStr209
                DD offset HelpStr20a,offset HelpStr20b,offset HelpStr20c
                DD offset HelpStr20d
                DD offset HelpStr20e,offset HelpStr20f,offset HelpStr210
                DD offset HelpStr211,offset HelpStr212,offset HelpStr213
                DD offset HelpStr214,offset HelpStr215,offset HelpStr216
                DD offset HelpStr217, -1

HelpDat4	DD offset HelpStr301,offset HelpStr302,offset HelpStr303
                DD offset HelpStr304,offset HelpStr305,offset HelpStr306
                DD offset HelpStr307,offset HelpStr308,offset HelpStr309
                DD offset HelpStr30a,offset HelpStr30b,offset HelpStr30c
                DD offset HelpStr30d
                DD offset HelpStr30e,offset HelpStr30f,offset HelpStr310
                DD offset HelpStr311,offset HelpStr312,offset HelpStr313
                DD offset HelpStr314,offset HelpStr315,offset HelpStr316
                DD offset HelpStr317, -1

;-----------------------------------------------------------------------

DrawHelpScreen1:invoke _drawtextWindow,HelpScrX,HelpScrY+8*0 ,offset HelpDat1,HelpTColor,HelpBColor
;--------------
                ret


DrawHelpScreen2:invoke _drawtextWindow,HelpScrX,HelpScrY+8*0 ,offset HelpDat2,HelpTColor,HelpBColor
;--------------
                ret


DrawHelpScreen3:invoke _drawtextWindow,HelpScrX,HelpScrY+8*0 ,offset HelpDat3,HelpTColor,HelpBColor
;--------------
                ret


DrawHelpScreen4:invoke _drawtextWindow,HelpScrX,HelpScrY+8*0 ,offset HelpDat4,HelpTColor,HelpBColor
;--------------
                ret

;--------------------------------------------------------------------
align 4
CurrentHelpScr	dw 0

GeneralHelpSys:
;-------------
			mov CurrentHelpScr,0

                      	pushall
GHS0001:                ss_undrawmouse 0,0

                        .if CurrentHelpScr==0
                                call DrawHelpScreen1
                        .endif

                        .if CurrentHelpScr==1
                                call DrawHelpScreen2
                        .endif


                        .if CurrentHelpScr==2
                                call DrawHelpScreen3
                        .endif


                        .if CurrentHelpScr==3
                                call DrawHelpScreen4
                        .endif


                        ss_drawmouse 0,0

                        ss_getax
                        call MAJ
                        .while al!="Q" && al!=27 && al!=" " && al!=9 && ah!=KEY_F1

                            .if (al=="B") && CurrentHelpScr!=0
				 dec CurrentHelpScr
                                 jmp GHS0001
                            .endif

                            .if (al=="N") && CurrentHelpScr!=3
				 inc CurrentHelpScr
                                 jmp GHS0001
                            .endif

				ss_readmouse offset mouse_obj
			        mov ax, mouse_obj.x
			        mov bx, mouse_obj.y
		                mov cx, mouse_obj.boutons

		               .if ax!=mouse_obj.oldx || bx!=mouse_obj.oldy
		                 ; call InfoZone
			   	  ss_undrawmouse 0,0
			          ss_drawmouse 0,0
		                .endif

                            ss_getax
                            call MAJ
                        .endw
                        popall

                	call ShowScreen2
                        ss_drawmouse
                        ret
;-------------------------------------------------------------------

TESTX db "TEST$",0

DrawImageFullScreen:
;----------

		pushall

                ; Get destination TOP adresse in EDI
                mov ax, ImageFTopY; 8;ImageTopy
                mul word ptr mode_info_obj. xResolution

                shl edx,16
                mov dx,ax			       	; edx = y* Res

                xor eax,eax
                mov ax,ImageFTopX ;(640-(64*8))/2;ImageTopX	; eax= x

                add edx,eax                             ; edx=  x+y*res
                mov edi,edx				; edi= edx
                add edi, _himemBase
;               add edi, 256*1024

                ; Get source adresse in ESI
                xor eax,eax
                ;;mov ax, MX                              ; TopX of Image
                ;add ax, VX
                shl eax, 6				; x64 (block size)

                xor ebx,ebx				;
		;;mov bx, MY                              ; TopY of Image
                ;add bx, VY
                shl ebx, 6+6				; x64x64

                add eax,ebx
                add eax, _himembase
                mov esi,eax
                add esi, 256*1024

                mov word ptr Line2Draw,(400-16)/8;ImageHei/8
RiX02:
                push edi
                push esi
                mov word ptr Sqr2Draw, 64 ;ImageLen/8
RiX01:
                push edi
                mov word ptr LineInSqr, 8

RiX00:
		mov eax, [esi]
                mov [edi], eax
		mov eax, [esi+4]
                mov [edi+4], eax

                add esi,8
                add edi,640
                dec LineInSqr
                cmp LineInSqr,0
                jne RiX00

                pop edi
                add edi,8
                dec Sqr2Draw
                cmp Sqr2Draw,0
                jne RiX01

                pop esi
                pop edi
                add edi, 640*8
                add esi, 64*64
                dec Line2Draw
                cmp Line2Draw,0
                jne RiX02

;                print offset TESTX

                popall
		ret



;--------------------------------------------------------------------



DrawImageBorderInFS:
;-------------------
              	pushall

		;; [Get position of ImageZone]
		mov ax, ImageFTopY ;ImageTopY
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax			; edx = y* Xres

                xor eax,eax
                mov ax, ImageFTopX  ;ImageTopX
                add edx,eax			; edx = y* XRes + x
                mov edi,edx

                ;; Adding offset from VX & VY
                xor eax,eax
		mov ax, MX;VX
                shl ax, 3
                add edi, eax

                mov ax, MY;VY
                shl ax,3
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax
		add edi, edx

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
		;; Setup multiportion Window
                push edi
                ;mov ebx,edi
                ;shr ebx, 10 +2
                xor edx,edx
                mov eax,edi
                div WGranDD
                mov ebx,eax			; copy dividen in2 ebx

    		ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                ;and edi, 4096-1
                mov edi,edx			; Remain copy in2 EDI
                add edi, 0a0000h

                ;; DrawTopPortion
                mov ax, ParamColor
                mov ah, al
                push ax
                shl eax,16
                pop ax

                mov gs:[edi], eax
                mov gs:[edi+4],eax

                mov gs:[edi+640],al
                mov gs:[edi+640*2],al
                mov gs:[edi+640*3],al

                ;sub edi,0a0000h
                pop edi
                add edi, ImageFLsFNTOffset


                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
		;; Setup multiportion Window
                ;push edi
                ;mov ebx,edi
                ;shr ebx, 10 +2
                xor edx,edx
                push eax			; save EAX
                mov eax,edi
                div WGranDD
                mov ebx,eax			; copy dividen in2 ebx
                pop eax				; restore EAX

    		ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                ;and edi, 4096-1
                mov edi,edx			; Remain copy in2 EDI
                add edi, 0a0000h


		;; DrawBottomPortion
                mov gs:[edi + 7+640*4],al
                mov gs:[edi + 7+640*5],al
                mov gs:[edi + 7+640*6],al

                mov gs:[edi  +640*7], eax
                mov gs:[edi+4+640*7],eax

                popall
                ret



;-------------------------------------------------------------------

UndrawBorderInFS:
;----------------

              	pushall

		;; [Get position of ImageZone]
		mov ax, ImageFTopY ;ImageTopY
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax			; edx = y* Xres

                xor eax,eax
                mov ax, ImageFTopX  ;ImageTopX
                add edx,eax			; edx = y* XRes + x
                mov edi,edx

                ;; Adding offset from VX & VY
                xor eax,eax
		mov ax, MX;VX
                shl ax, 3
                add edi, eax

                mov ax, MY;VY
                shl ax,3
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax
		add edi, edx



                ;**********ORIGINAL CODE*************************
		;; Setup multiportion Window
                ;;mov esi,edi
                ;;push edi
                ;;mov ebx,edi
                ;;shr ebx, 10 +2
    		;;ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                ;;and edi, 4096-1
                ;;add edi, 0a0000h
                ;;add esi, _himembase
		;*************************************************

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
		;; Setup multiportion Window
                mov esi,edi
                push edi
                xor edx,edx
                mov eax,edi
                div WGranDD
                mov ebx,eax			; copy dividen in2 ebx

    		ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                mov edi,edx			; Remain copy in2 EDI
                add edi, 0a0000h
                add esi, _himembase


                ;; DrawTopPortion
;                mov ax, ParamColor
;                mov ah, al
;                push ax
;                shl eax,16
;                pop ax

                mov eax, [esi]
                mov gs:[edi], eax
                mov eax, [esi+4]
                mov gs:[edi+4],eax

                mov al,[esi+640]
                mov gs:[edi+640],al
                mov al,[esi+640*2]
                mov gs:[edi+640*2],al
                mov al,[esi+640*3]
                mov gs:[edi+640*3],al

                ;sub edi,0a0000h
                pop edi
                add edi, ImageFLsFNTOffset
                ; ImageLen + (ImageHei*640) ;(GrildLen /8) -3 + ((GrildHei /8)-3) *640


                ;***********ORIGINAL CODE**************************
		;; Setup multiportion Window
                ;;mov esi,edi
                ;;mov ebx,edi
                ;;shr ebx, 10 +2
    		;;ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                ;;and edi, 4096-1
                ;;add edi, 0a0000h
                ;;add esi, _himembase
                ;**************************************************

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
		;; Setup multiportion Window
                mov esi,edi
                xor edx,edx
                mov eax,edi
                div WGranDD
                mov ebx,eax			; copy dividen in2 ebx

    		ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                mov edi,edx			; Remain copy in2 EDI
                add edi, 0a0000h
                add esi, _himembase




		;; DrawBottomPortion
                mov al,[esi + 7+640*4]
                mov gs:[edi + 7+640*4],al
                mov al,[esi + 7+640*5]
                mov gs:[edi + 7+640*5],al
                mov al,[esi + 7+640*6]
                mov gs:[edi + 7+640*6],al

                mov eax,[esi  +640*7]
                mov gs:[edi  +640*7], eax
                mov eax,[esi+4+640*7]
                mov gs:[edi+4+640*7],eax

                popall
                ret

;--------------------------------------------------------------------
FullScreenView:
;--------------
                ;pushall
		;call CleanScreen
                ;popall

                mov ecx, (256*1024)/4
                mov eax, app_Color
                mov edi, dword ptr _himembase

FSV000:         mov [edi],eax
                add edi,4
                dec ecx
                cmp ecx,0
                jne FSV000

		call DrawImageFullScreen
                call ShowScreen
                call WriteCopyrights

                ss_drawmouse
                ss_getax
                .while ah!=KEY_F5 && al!=27 && al!=32 && al!=9 && al!=13
                     call FSKEYS
                     inc Timer
                     .if word ptr Timer >=5
			mov word ptr Timer,0
                        inc word ptr ParamColor
                        .if word ptr ParamColor>=15
                           mov ParamColor,1
                        .endif
                        ;call DrawParams
	                call DrawImageBorderInFS
                     .endif

                     ss_readmouse offset mouse_obj
                     mov ax, mouse_obj.x
		     mov bx, mouse_obj.y
                     mov cx, mouse_obj.boutons

                     .if ax!=mouse_obj.oldx || bx!=mouse_obj.oldy
                     ;     call InfoZone
			  ss_undrawmouse 0,0
		          ss_drawmouse 0,0
                     .endif

                 ss_getax
                .endw

		call CleanScreen
                call DrawAllWins
                call DrawPalColors
             ;   call FillWithJunk
                call RedrawGrild
                call RedrawImage
		call ShowScreen

                call DrawColorBox
                call WriteCopyrights

                ss_readmouse offset mouse_obj
                ss_drawmouse 0,0
                ret
;--------------------------------------------------------------------

FSKEYS:
;------
		pushall

		.if (al=="8" || ah==key_up) && MY!=0
                        call UndrawBorderInFS
                        dec MY
                        ;call ShowScreen
                .endif

		.if (al=="2" || ah==key_dn) && MY< (ImageFHei/8-ImageHei/8 -1)
                        call UndrawBorderInFS
                        inc MY
                        ;call ShowScreen
                .endif

		.if (al=="4" || ah==key_lf) && MX!=0
                        call UndrawBorderInFS
			dec MX
                        ;call ShowScreen
                .endif

		.if (al=="6" || ah==key_rg) && MX< (ImageFLen/8 - ImageLen/8)
                        call UndrawBorderInFS
       			inc MX
                        ;call ShowScreen
                .endif

                     .if al=="C" || al=="c"
                        pushall
                        invoke AskQuestion , offset TXT_WANTOCLEAR, offset CHC_WANTOCLEAR, 15, 2
                        .if al==0
                     	  call FillWithJunk
                          popall
			  call DrawImageFullScreen
                	  call ShowScreen
                	  call WriteCopyrights

                	  ;call RedrawGrild
                	  ;call RedrawImage
                	  ;call ShowScreen2
			  ;call DrawColorBox
		          ss_drawmouse 0,0
                        .else
                          popall
                        .endif
                     .endif

                     .if ah==KEY_F1 ; al=="h" || al=="H"
                        call GeneralHelpSys
                     .endif

                     .if ah==KEY_F6 ||  ah==KEY_F7 ||  ah==KEY_F8
                        call gereChangeDir
                     .endif


                popall
                ret

;#####################################################################
;	LoadIma DIALOG BOX
;#####################################################################

DialogTopX	EQU (640 - DialogLen )/2
DialogTopY	EQU 16*2
DialogHeiSQR	EQU DialogFHeiSQR +6+2+2
DialogLenSQR    EQU 24+10
DialogHei	EQU DialogHeiSQR *8
DialogLen	EQU DialogLenSQR *8
DialogTColor	EQU 15
DialogBColor    EQU 2

DialogFTopX	EQU (640 - DialogFLen )/2
DialogFTopY	EQU DialogTopY+2*8+2*8
DialogFHeiSQR	EQU 20
DialogFLenSQR	EQU 16
DialogFHei	EQU DialogFHeiSQR *8
DialogFLen	EQU DialogFLenSQR *8
DialogFTColor	EQU 1
DialogFBColor	EQU 15

DialogMETColor	EQU 1
DialogMEBColor	EQU 14

align 2
WhatLine	dw 0
DlgLine		dw 0
ATLine		dw 0

DlgTopLine	dw 0
DlgYLine	dw 0
NbFiles		dw 0

;                   0123456789012345678901234567890
DialogLdImaTop  db "============  LOAD IMAGE  ==============",0
DialogLdImaMid  db "                                        ",0
DialogLdImaBot  db "========================================",0

HelpstrD01	db "=============== HELP ==================",0
Helpstrd02	db "                                       ",0
HelpStrD03	db "                                       ",0
HelpStrD04	db "   Use cursors to move up and down     ",0
HelpStrD05	db "   into the list.                      ",0
HelpStrD06	db "                                       ",0
HelpStrD07	db "   Press SHIFT-A to access drive A     ",0
HelpStrD08	db "      or SHIFT-B to access drive B     ",0
HelpStrD09	db "      or SHIFT-C to access drive C     ",0
HelpStrD0a	db "      etc.                             ",0
HelpStrD0b	db "                                       ",0
HelpStrD0c	db "   Press SPACE or ENTER to make        ",0
HelpStrD0d	db "   selection.                          ",0
HelpStrD0e	db "                                       ",0
HelpStrD0f	db "   Press ESC or TAB to return to       ",0
HelpStrD10	db "   the editor.                         ",0
HelpStrD11	db "                                       ",0
HelpStrD12	db "   Consult READ.ME for more            ",0
HelpStrD13	db "   informations.                       ",0
HelpStrD14	db "                                       ",0
HelpStrD15	db "                                       ",0
HelpStrD16	db "                                       ",0
HelpStrD17	db "=======================================",0

CurrentPath     db 128 DUP (0)
		db -1

align 4
HelpForDialog   DD offset HelpStrD01,offset HelpStrD02,offset HelpStrD03
                DD offset HelpStrD04,offset HelpStrD05,offset HelpStrD06
                DD offset HelpStrD07,offset HelpStrD08,offset HelpStrD09
                DD offset HelpStrD0a,offset HelpStrD0b,offset HelpStrD0c
                DD offset HelpStrD0d
                DD offset HelpStrD0e,offset HelpStrD0f,offset HelpStrD10
                DD offset HelpStrD11,offset HelpStrD12,offset HelpStrD13
                DD offset HelpStrD14,offset HelpStrD15,offset HelpStrD16
                DD offset HelpStrD17, -1

DIR_ERR_DLG1	db "==== ERROR! ====",0
DIR_ERR_DLG2	db "   Unable to    ",0
DIR_ERR_DLG3	db "change directory",0
DIR_ERR_DLG4	db "================",0


DRV_ERR_DLG1	db "==== ERROR! ====",0
DRV_ERR_DLG2	db " Invalid drive. ",0
DRV_ERR_DLG3	db "================",0

align 4
DirERRDLG	dd offset DIR_ERR_DLG1,offset DIR_ERR_DLG2,offset DIR_ERR_DLG3,offset DIR_ERR_DLG4,-1
DrvERRDLG	dd offset DRV_ERR_DLG1,offset DRV_ERR_DLG2,offset DRV_ERR_DLG3,-1

cd_err		db "Error changing directory.",13,10,"$"
cd_docdtxt	db "Doing change dir.",13,10,"$"


;------------------------------------------------------------------------
; Get current drive
; IN:
; OUT: al=drive (0=A, 1=B ...)
;
GetCurrentDrive:

                mov v86r_ah,19h		; mov ah,19h
                mov al,21h              ; int 21h
                int 33h
                mov al, V86r_al		; mov al, al
		ret

;-----------------------------------------------------------------------

GetCurrentDir:
;-------------
                pushall
                xor eax,eax
                mov ax, Code32
                shl eax,4
                add edi,eax

		mov eax, edi
                and eax,15
                shr edi, 4

                mov v86r_ah,47h		; mov ah,47h
                mov v86r_ds, di         ; mov ds,di
                mov v86r_si, ax         ; mov si,ax
                mov v86r_dl,0           ; mov dl,0 	current drive
                mov al,21h		; int 21h
                int 33h

                popall
                ret


;------------------------------------------------------------------------
MCP_ERR		db "GetCurrentPath issued an error",10,13,"$"
RootPath	db "\",0
MakeCurrentPath:
;---------------
                pushall

		call  GetCurrentDrive
                add al, "A"
                ;inc al
                mov CurrentPath, al
                mov byte ptr CurrentPath+1, ":"
                mov byte ptr CurrentPath+2, "\"

                mov edi,offset CurrentPath+3
                call GetCurrentDir
                jnc MCP0001
                ;print offset MCP_ERR

                pushall
                  invoke _drawtextWindow,DialogFTopx, DialogFTopY ,offset DrvERRDLG, 15,4

                  mov v86r_ah, 0eh
                  mov v86r_dl,2
                  mov al,21h
                  int 33h

                  mov esi,offset RootPath
                  call ChangeDir

                  ss_getax
                  .while al!=27 && al!=9 && ah!=KEY_F1 && al!=13 && al!=32 && ah!=KEY_UP && ah!=KEY_DN
                     ss_getax
                  .endw
                  call showScreen2
                  invoke DoDir, offset ALL_IMA
  		  call DrawImaLoadDialogBox
		popall

MCP0001:
                popall
                ret

;------------------------------------------------------------------------
DrawImaLoadDialogBox:
;--------------------
                pushall
                mov DlgTopLine,0
                mov DlgYLine,0+4

                ; DrawLoadImageDialog Top Line
                mov DlgLine, 0
                OutText DialogTopX, DialogTopY, offset DialogLdImaTop,DialogTColor,DialogBColor

                ; DrawLoadImageDialog MidLines
                mov dx, DialogTopY+8
                .while DlgLine != DialogheiSQR-2
                   OutText DialogTopX,<dx>,offset DialogLdImaMid,DialogTColor,DialogBColor
		   add dx,8
                   inc DlgLine
                .endw

                ; DrawLoadImageDialog Bottom line
                OutText DialogTopX,<dx>,offset DialogLdImaBot,DialogTColor,DialogBColor
                mov WhatLine, 20

                ; Print current path onto dialog box
                call MakeCurrentPath
                OutText DialogTopX+8*2, DialogTopY+8*2,offset CurrentPath, DialogTColor, DialogBColor

                ; DrawList of files onto dialog box
                mov dx, DialogFTopY
                mov esi, _himembase
                add esi, 512*1024

                mov byte ptr [esi+15],0
                .while WhatLine!=0 && byte ptr [esi]!=-1
                  OutText DialogFTopX,<dx>,<esi>,DialogFTColor,DialogFBColor
     		  add dx,8
                  add esi,32
                  mov byte ptr [esi+15],0
                  dec WhatLine
                .endw

		; Calculate position in dialogbox of current selected
                ; file. Draw selected file in YELLOW.

                mov dx, DlgYLine
                shl dx, 3
                add dx, DialogFTopY

                xor eax,eax
                mov ax, DlgYLine
                add ax, DlgTopLine
                shl eax, 5
                add eax, _himembase
                add eax, 512*1024
                mov esi,eax
                OutText DialogFTopX,<dx>,<esi>,DialogMETColor,DialogMEBColor
                popall
		ret

;-----------------------------------------------------------------------

align 2
OutGereImaDir	dw 0

GereImaDir:
;---------
                pushall
		invoke DoDir, offset ALL_IMA

                mov OutGereImaDir,0

                ss_undrawmouse 0,0
		call DrawImaLoadDialogBox
                ss_drawmouse 0,0
                ss_getax
                .while al!=27  && ah!=KEY_F3 && al!=9 && OutGereImaDir!=1

                   call Mousie
                   call LoadImaDlgKeys

                   ss_getax
                .endw

                ss_undrawmouse 0,0
                call ShowScreen2
                ss_drawmouse 0,0

                popall
                ret

;------------------------------------------------------------------------

RedrawAllFiles:
;--------------
                pushall
                ; DrawList of files onto dialog box
                mov WhatLine, 20
                mov dx, DialogFTopY
                ;ov esi, _himembase
                ;dd esi, 512*1024

                ;pushall
                ;print offset testing
                ;popall

                xor eax,eax
                ;ov ax, DlgYLine
                mov ax, DlgTopLine
                shl eax, 5
                add eax, _himembase
                add eax, 512*1024
                mov esi,eax

                mov byte ptr [esi+15],0
                .while WhatLine!=0 && byte ptr [esi]!=-1
                  OutText DialogFTopX,<dx>,<esi>,DialogFTColor,DialogFBColor
     		  add dx,8
                  add esi,32
                  mov byte ptr [esi+15],0
                  dec WhatLine
                .endw

                popall
                ret

;-----------------------------------------------------------------------

DrawWhiteLine:
;------------
		; Calculate position in dialogbox of current selected
                ; file. Draw selected file in YELLOW.
                pushall

                mov dx, DlgYLine
                shl dx, 3
                add dx, DialogFTopY

                xor eax,eax
                mov ax, DlgYLine
                add ax, DlgTopLine
                shl eax, 5
                add eax, _himembase
                add eax, 512*1024
                mov esi,eax
                OutText DialogFTopX,<dx>,<esi>,DialogFTColor,DialogFBColor
                popall
                ret

;-----------------------------------------------------------------------



DrawYellowLine:
;-------------
		; Calculate position in dialogbox of current selected
                ; file. Draw selected file in YELLOW.
                pushall

                mov dx, DlgYLine
                shl dx, 3
                add dx, DialogFTopY

                xor eax,eax
                mov ax, DlgYLine
                add ax, DlgTopLine
                shl eax, 5
                add eax, _himembase
                add eax, 512*1024
                mov esi,eax
                OutText DialogFTopX,<dx>,<esi>,DialogMETColor,DialogMEBColor

                popall
                ret

;------------------------------------------------------------------------

;DlgTopLine	dw 0
;DlgYLine	dw 0

LoadImaDlgKeys:
;-------------

		.if al=="8" || ah==KEY_UP
                    .if DlgYLine!=0
			call DrawWhiteLine
                        dec DlgYLine
                        call DrawYellowLine

		    .else
                       .if DlgTopLine!=0
                          ;call DrawWhiteLine
                          dec DlgTopLine
			  call RedrawAllFiles
                          call DrawYellowLine
                       .endif
                    .endif

                .endif

                .if al=="2" || ah==KEY_DN
                    mov bx, DlgYLine
                    add bx, DlgTopLine
                    mov cx, NbFiles
                    dec cx
                    .if DlgYLine<DialogFHeiSQR-1 && bx<cx
			call DrawWhiteLine
                        inc DlgYLine
                        call DrawYellowLine

                    .else

                       .if bx<cx
                          ;call DrawWhiteLine
                          inc DlgTopLine
			  call RedrawAllFiles
                          call DrawYellowLine
                       .endif
                    .endif
                .endif


                .if ah==KEY_F1
                   pushall
                     invoke _drawtextWindow,HelpScrX,HelpScrY+8*0 ,offset HelpForDialog,HelpTColor,HelpBColor
                     ss_getax
                     .while al!=27 && al!=9 && ah!=KEY_F1 && al!=13 && al!=32 && ah!=KEY_UP && ah!=KEY_DN
                        ss_getax
                     .endw
                     call showScreen2
  		     call DrawImaLoadDialogBox
                   popall
                .endif


                ;; Select a new drive
                .if al>="A" && al<="Z" && al==0

                   ; Select Disk
                   sub al,"A"
                   mov v86r_ah,0eh
                   mov v86r_dl, al
                   mov al, 21h
                   int 33h

                   invoke DoDir, offset ALL_IMA
		   call DrawImaLoadDialogBox

                .endif


                ;; Select a file or a directory
                .if al==13 || al==" "
                  pushall
                  mov dx, DlgYLine
                  shl dx, 3
                  add dx, DialogFTopY

                  xor eax,eax
                  mov ax, DlgYLine
                  add ax, DlgTopLine
                  shl eax, 5
                  add eax, _himembase
                  add eax, 512*1024
                  mov esi,eax

                  mov al, [esi]
                  .if al==2		; TYPEDEF DIR
                     add esi,16
                     call changeDir
                     invoke DoDir, offset ALL_IMA
     		     call DrawImaLoadDialogBox
                     popall
                  .endif

                  .if al==1
                     add esi,16
                     call LoadImaIntoBuffer
                     call DrawImaLoadDialogBox
		     call RedrawAllFiles
                     call DrawYellowLine
                     popall
                  .endif

                  .if al==3
                   mov al, [esi+1]
                   sub al,"A"
                   mov v86r_ah,0eh
                   mov v86r_dl, al
                   mov al, 21h
                   int 33h

                   invoke DoDir, offset ALL_IMA
		   call DrawImaLoadDialogBox
                   popall
                  .endif
                .endif


                ret

;--------------------------------------------------------------------
tampon		db 16 DUP (0)

changedir:
;--------
;               pushall
;               print offset cd_docdtxt
;               popall

                mov edx, offset tampon
                .while byte ptr [esi]!=0
                   mov al, [esi]
                   mov [edx],al
                   inc esi
                   inc edx
                .endw

                mov byte ptr [edx],0

                mov esi,offset tampon
                xor eax,eax
                mov ax, Code32
                shl eax,4
                add esi,eax

		mov v86r_ah,3bh
                mov eax, esi
                and eax,15
                shr esi,4
		mov v86r_ds, si
                mov v86r_dx, ax
                mov al, 21h
                int 33h
                jnc CD0001

                pushall
                  invoke _drawtextWindow,DialogFTopx, DialogFTopY ,offset DirErrDlg, 15,4
                  ss_getax
                  .while al!=27 && al!=9 && ah!=KEY_F1 && al!=13 && al!=32 && ah!=KEY_UP && ah!=KEY_DN
                     ss_getax
                  .endw
                  call showScreen2
  		  call DrawImaLoadDialogBox
		popall
CD0001:
		ret

;--------------------------------------------------------------------

ERR_OPENFILE1   db "==== ERROR! ====",0
ERR_OPENFILE2   db " Error opening  ",0
ERR_OPENFILE3   db "     file !     ",0
ERR_OPENFILE4 	db "================",0

TXT_GOODLOAD1   db "==== BRAVO! ====",0
TXT_GOODLOAD2   db "  File loaded   ",0
TXT_GOODLOAD3   db "     a ok!      ",0
TXT_GOODLOAD4 	db "================",0


align 4
ERROPENFILE     DD offset ERR_OPENFILE1, OFFSET ERR_OPENFILE2
                DD offset ERR_OPENFILE3, OFFSET ERR_OPENFILE4, -1

TXTGOODLOAD	dd OFFSET TXT_GOODLOAD1, OFFSET TXT_GOODLOAD2
		DD OFFSET TXT_GOODLOAD3, OFFSET TXT_GOODLOAD4,-1

LocalErrorHandler:
;----------------

                pushall
                  invoke _drawtextWindow,DialogFTopx, DialogFTopY, esi, 15,4
                  ss_getax
                  .while al!=27 && al!=9 && ah!=KEY_F1 && al!=13 && al!=32 && ah!=KEY_UP && ah!=KEY_DN
                     ss_getax
                  .endw
                  call showScreen2
  		  call DrawImaLoadDialogBox
		popall
		ret


;--------------------------------------------------------------------------


;####################################################################
; DragImage from Buffer onto the FULL SCREEN...
;
;####################################################################
DrawImageBorderInFS2:
; Undrawing the upper & lower corner of the image in the video
; memory.
;
;-------------------

              	pushall

		;; [Get position of ImageZone]
		mov ax, ImageFTopY ;ImageTopY
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax			; edx = y* Xres

                xor eax,eax
                mov ax, ImageFTopX  ;ImageTopX
                add edx,eax			; edx = y* XRes + x
                mov edi,edx

                ;; Adding offset from VX & VY
                xor eax,eax
		mov ax, IX;MX;VX
                shl ax, 3
                add edi, eax

                mov ax, IY;MY;VY
                shl ax,3
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax
		add edi, edx

		;**********ORIGINAL CODE  ************************
		;; Setup multiportion Window
                ;;push edi
                ;;mov ebx,edi
                ;;shr ebx, 10 +2
    		;;ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr
                ;;
                ;;and edi, 4096-1
                ;;add edi, 0a0000h
		;****************************************************

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
		;; Setup multiportion Window
                ;mov esi,edi
                push edi
                xor edx,edx
                mov eax,edi
                div WGranDD
                mov ebx,eax			; copy dividen in2 ebx

    		ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                mov edi,edx			; Remain copy in2 EDI
                add edi, 0a0000h
                ;add esi, _himembase


                ;; DrawTopPortion
                mov ax, ParamColor
                mov ah, al
                push ax
                shl eax,16
                pop ax

                mov gs:[edi], eax
                mov gs:[edi+4],eax

                mov gs:[edi+640],al
                mov gs:[edi+640*2],al
                mov gs:[edi+640*3],al

                ;sub edi,0a0000h
                pop edi
                ;add edi, ImageFLsFNTOffset

		;; [Get position of ImageZone]
		mov ax, ImageFTopY ;ImageTopY
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax			; edx = y* Xres

                xor eax,eax
                mov ax, ImageFTopX  ;ImageTopX
                add edx,eax			; edx = y* XRes + x
                mov edi,edx

                ;; Adding offset from VX & VY
                xor eax,eax
		mov ax, IX2;MX;VX
                shl ax, 3
                add edi, eax

                mov ax, IY2;MY;VY
                shl ax,3
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax
		add edi, edx

                ;;************************************************
		;; Setup multiportion Window
                ;;mov ebx,edi
                ;;shr ebx, 10 +2
    		;;ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr
                ;;
                ;;and edi, 4096-1
                ;;add edi, 0a0000h
                ;;*************************************************

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
		;; Setup multiportion Window
                ;mov esi,edi
                ;push edi
                xor edx,edx
                mov eax,edi
                div WGranDD
                mov ebx,eax			; copy dividen in2 ebx

    		ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                mov edi,edx			; Remain copy in2 EDI
                add edi, 0a0000h


                .if SelectPhase==1

		  ;; DrawBottomPortion
                  mov ax, ParamColor
                  mov ah, al
                  push ax
                  shl eax,16
                  pop ax

                  mov gs:[edi + 7+640*4],al
                  mov gs:[edi + 7+640*5],al
                  mov gs:[edi + 7+640*6],al

                  mov gs:[edi  +640*7], eax
                  mov gs:[edi+4+640*7],eax
                .endif

                popall
                ret



;-------------------------------------------------------------------

UndrawBorderInFS2:
;
; Undrawing the upper & lower corner of the image from the video
; memory. Replacing them with data from _himembase where screen
; buffer is located.
;----------------

              	pushall

		;; [Get position of ImageZone]
		mov ax, ImageFTopY ;ImageTopY
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax			; edx = y* Xres

                xor eax,eax
                mov ax, ImageFTopX  ;ImageTopX
                add edx,eax			; edx = y* XRes + x
                mov edi,edx

                ;; Adding offset from VX & VY
                xor eax,eax
		mov ax, IX;MX;VX
                shl ax, 3
                add edi, eax

                mov ax, IY;MY;VY
                shl ax,3
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax
		add edi, edx


                ;;*****************************************************
		;; Setup multiportion Window
                ;;mov esi,edi
                ;;push edi
                ;;mov ebx,edi
                ;;shr ebx, 10 +2
    		;;ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr
                ;;
                ;;and edi, 4096-1
                ;;add edi, 0a0000h
                ;;add esi, _himembase
                ;;
		;***************************************************

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
		;; Setup multiportion Window
                mov esi,edi
                push edi
                xor edx,edx
                mov eax,edi
                div WGranDD
                mov ebx,eax			; copy dividen in2 ebx

    		ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                mov edi,edx			; Remain copy in2 EDI
                add edi, 0a0000h
                add esi, _himembase



                ;; UnDrawTopPortion
;                mov ax, ParamColor
;                mov ah, al
;                push ax
;                shl eax,16
;                pop ax

                mov eax, [esi]
                mov gs:[edi], eax
                mov eax, [esi+4]
                mov gs:[edi+4],eax

                mov al,[esi+640]
                mov gs:[edi+640],al
                mov al,[esi+640*2]
                mov gs:[edi+640*2],al
                mov al,[esi+640*3]
                mov gs:[edi+640*3],al

                ;sub edi,0a0000h
                pop edi
                ;add edi, ImageFLsFNTOffset

		;; [Get position of ImageZone]
		mov ax, ImageFTopY ;ImageTopY
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax			; edx = y* Xres

                xor eax,eax
                mov ax, ImageFTopX  ;ImageTopX
                add edx,eax			; edx = y* XRes + x
                mov edi,edx

                ;; Adding offset from VX & VY
                xor eax,eax
		mov ax, IX2;MX;VX
                shl ax, 3
                add edi, eax

                mov ax, IY2;MY;VY
                shl ax,3
		mul word ptr Mode_info_obj. XResolution
                shl edx,16
                mov dx,ax
		add edi, edx
                ; ImageLen + (ImageHei*640) ;(GrildLen /8) -3 + ((GrildHei /8)-3) *640

                ;;*******************************************************
		;; Setup multiportion Window
                ;;mov esi,edi
                ;;mov ebx,edi
                ;;shr ebx, 10 +2
    		;;ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr
                ;;
                ;;and edi, 4096-1
                ;;add edi, 0a0000h
                ;;add esi, _himembase
                ;;********************************************************

                ; MODIFIED FOR FULL VESA COMPATIBILITY 6/19/96
		;; Setup multiportion Window
                mov esi,edi
                ;push edi
                xor edx,edx
                mov eax,edi
                div WGranDD
                mov ebx,eax			; copy dividen in2 ebx

    		ss_setfastwindow 0, <bx>, mode_info_obj.WinFuncPtr

                mov edi,edx			; Remain copy in2 EDI
                add edi, 0a0000h
                add esi, _himembase



                .if SelectPhase==1
		  ;; UnDrawBottomPortion
                  mov al,[esi + 7+640*4]
                  mov gs:[edi + 7+640*4],al
                  mov al,[esi + 7+640*5]
                  mov gs:[edi + 7+640*5],al
                  mov al,[esi + 7+640*6]
                  mov gs:[edi + 7+640*6],al

                  mov eax,[esi  +640*7]
                  mov gs:[edi  +640*7], eax
                  mov eax,[esi+4+640*7]
                  mov gs:[edi+4+640*7],eax
                .endif

                popall
                ret

;----------------------------------------------------

align 4
ix 	        dw 0
iy	        dw 0
ix2	        dw 0
iy2	        dw 0
Timer2		dw 0
IsDrawn		dw 0
BreakLoopDI	dw 0

DragImageInFullScreen:
;
; Dragging an image from the clipboard located (_himembase + 256*3*1024)
; ?This image was either loaded into memory or copy from image
; buffer located _himembase + 256*1024
;--------------------

                pushall

		mov ix,0
                mov iy,0
                mov Timer2,0
                mov BreakLoopDi,0
                mov SelectPhase,1

                ;; Calculate IX2
                mov ax, ix
                add ax,TImaLen
                mov ix2,ax
                dec ix2

                ;; Calculate IY2
                mov ax, iy
                add ax, TimaHei
                mov iy2,ax
                dec iy2

                mov ecx, (256*1024)/4
                mov eax, app_Color
                mov edi, dword ptr _himembase

                .while ecx!=0
                  mov [edi],eax
                  add edi,4
                  dec ecx
		.endw

		call DrawImageFullScreen
                call ShowScreen
                call WriteCopyrights
		call copyBuf2Tampon
                call DrawIma2Screen

                ss_drawmouse
                ss_getax
                .while ah!=KEY_F5 && al!=27 && al!=9 && BreakLoopDi!=1
                     call DIFSKEYS
                     inc Timer

                     .if word ptr Timer >=5
			mov word ptr Timer,0
                        inc word ptr ParamColor
                        .if word ptr ParamColor>=15
                           inc Timer2
                           .if word ptr Timer2>=1000
                              mov Timer2,0
                           .endif
                           mov ParamColor,1
                        .endif
                        ;call DrawParams
	                call DrawImageBorderInFS2
                     .endif

                     ss_readmouse offset mouse_obj
                     mov ax, mouse_obj.x
		     mov bx, mouse_obj.y
                     mov cx, mouse_obj.boutons

                     .if ax!=mouse_obj.oldx || bx!=mouse_obj.oldy
                     ;     call InfoZone
			  ss_undrawmouse 0,0
		          ss_drawmouse 0,0
                     .endif

                 ss_getax
                .endw

		call CleanScreen
                call DrawAllWins
                call DrawPalColors
                call RedrawGrild
                call RedrawImage
		call ShowScreen

                call DrawColorBox
                call WriteCopyrights

                ss_readmouse offset mouse_obj
                ss_drawmouse 0,0

                popall
                ret

;--------------------------------------------------------------------

DIFSKEYS:
;------
		pushall

		.if (al=="8" || ah==key_up) && IY!=0
                        call UndrawImaFromTampon
                        dec IY
                        dec IY2
		        call DrawIma2Screen
                        ss_drawmouse 0,0
                .endif

		.if (al=="2" || ah==key_dn) && IY2< (ImageFHei/8 -2)
                        call UndrawImaFromTampon
                        inc IY
                        inc IY2
		        call DrawIma2Screen
                        ss_drawmouse 0,0
                .endif

		.if (al=="4" || ah==key_lf) && IX!=0
                        call UndrawImaFromTampon
			dec IX
                        dec IX2
 		        call DrawIma2Screen
                        ss_drawmouse 0,0
                .endif

		.if (al=="6" || ah==key_rg) && IX2< (ImageFLen/8 -1)
                        call UndrawImaFromTampon
       			inc IX
                        inc IX2
		        call DrawIma2Screen
                        ss_drawmouse 0,0
                .endif

                     .if al=="C" || al=="c"
                        pushall
                        invoke AskQuestion , offset TXT_WANTOCLEAR, offset CHC_WANTOCLEAR, 15, 2
                        .if al==0
                     	  call FillWithJunk
                          popall
			  call DrawImageFullScreen
                	  call ShowScreen
                	  call WriteCopyrights
		          ss_drawmouse 0,0
                        .else
                          popall
                        .endif
                     .endif

                     .if ah==KEY_F1 ; al=="h" || al=="H"
                        call GeneralHelpSys
                     .endif

                     .if al==32 || al==13
                         mov breakloopDi,1
                     	call CopyIma2Image
                     .endif

                popall
		ret

;--------------------------------------------------------------------
_0Line	dw 0
_0SqrT	dw 0
_0Sqr	dw 0

CopyIma2Image:
;
; Copying from Clipboard located at _himembase +1024*256*3
; to actual image buffer (buffer) located at _himembase+1024*256
;
;------------
        pushall

        ; Load Destination into EDI
        xor eax,eax
	mov ax, iy
        shl eax, 12			; Sqr*64*64

        xor ebx,ebx
        mov bx, ix
        shl ebx, 6

        add eax,ebx
        mov edi, eax
        add edi, _himembase
        add edi, 1024*256

	; Load source into ESI
        mov esi, _himembase
        add esi, 1024*256*3

  	; Calculate lenght & height
        mov ax, ix2
        sub ax, ix
        inc ax
        mov _0SqrT, ax

        mov ax, iy2
        sub ax, iy
        inc ax
        mov _0Line,ax

        xor ebx,ebx

CI2I00:
        push ebx
	mov ax, _0SqrT
        mov _0Sqr,ax

CI2I01:
       	mov cx,64
CI2I02:
        mov al, [esi]
        or al,al
        je CI2103
        mov [edi+ebx],al
CI2103:
	inc ebx
        inc esi
        loop CI2I02

        dec _0Sqr
        cmp _0Sqr,0
        jne CI2I01

        pop ebx
        add ebx, 64*64
        dec _0Line
        cmp _0Line,0
        jne CI2I00

        popall
        ret

;---------------------------------------------------------------------
copyBuf2Tampon:
;
; Buffer is located at _himembase + 1024*246
; Tampon               _lomembase
;
; Copying 256k from Buffer to Tampon
; Tampon is TEMP storage.
;-------------
                pushall

                mov ecx, 256*1024/4
                mov esi, _himembase
                mov edi, _lomembase
		mov edx,4
                xor ebx,ebx

                .while ecx!=0
                  mov eax, [esi+ebx]
                  mov [edi+ebx],eax
                  add ebx,edx
                  dec ecx
                .endw

                popall
		ret

;-----------------------------------------------------------------------

align 2
LineCpt         dw 0
SqrCpt		dw 0
SqrCptT		dw 0

SqrCptERR	db "FATAL: Unresolved error IL0101$"
LineCptERR	db "FATAL: Unresolved error IL0102$"

drawImaInTampon:
;
; Draw the image from the Tampon located at _lomembase. This means
; that the image stored in the clipboard located at _himembase +
; 256*1024*3 is overwritting the data previously stored in the
; tampon.
; Tampon is used for TEMP storage only.
;
;--------------
                pushall
		mov ax, ImageFTopY
                mov bx, IY
                shl bx, 3
                add ax,bx
                mul mode_info_obj. Xresolution
                shl edx,16
                mov dx,ax		; edx = Y*Res

                xor eax,eax
                xor ebx,ebx
                mov ax, ImageFTopX
                mov bx, IX
                shl ebx,3
                add eax,ebx
                add edx,eax		; edx = x + Y*res
                add edx, _lomembase
                mov edi,edx

                mov esi, _himembase
                add esi, 1024*256*3

                mov ax, IX2
                sub ax, IX
                inc ax
                mov SqrCptT, ax

                mov ax, IY2
                sub ax, IY
                inc ax
                mov LineCpt, ax
                xor ebx,ebx

                ;printw LineCpt
                ;printcr
                .if LineCpt==0
		  print offset LineCptERR
                  jmp QUIT000
                .endif

                ;printw SqrCptT
                ;printcr
                .if SqrCptT==0
		  print offset SqrCptERR
                  jmp QUIT000
                .endif


DIIT001:

                push ebx
                mov ax, word ptr SqrCptT
                mov word ptr SqrCpt, ax

DIIT002:
                push ebx

        	mov dx, 8
                .while dx!=0
                  mov cx, 8
                  .while cx!=0
	            mov al,[esi]
                    .if al==0
                    .else
                      mov [edi+ebx],al
                    .endif
                    inc ebx
                    inc esi
                    dec cx
                    ;print offset CXLOOP
                  .endw
                  dec dx
                  add ebx, 640-8
                   ;print offset DXLOOP
                .endw

       		pop ebx
                add ebx,8
                dec word ptr SqrCpt

                ;print offset SqrCptLOOP
                cmp word ptr SqrCpt,0
                jne DIIT002



                pop ebx
                add ebx,640*8
                dec word ptr LineCpt
                ;print offset LineCptLOOP
                cmp word ptr LineCpt,0
                jne DIIT001


QUIT000:
                popall
                ret
;---------------------------------------------------------------------

UndrawImaFromTampon:
;
; Undraw the image from the Tampon located at _lomembase. This means
; that the image stored at _himembase +256*1024 is overwritting
; the tampon counterpart.
; Tampon is used for TEMP storage only.
;
;------------------
                pushall
		mov ax, ImageFTopY
                mov bx, IY
                shl bx, 3
                add ax,bx
                mul mode_info_obj. Xresolution
                shl edx,16
                mov dx,ax		; edx = Y*Res

                xor eax,eax
                xor ebx,ebx
                mov ax, ImageFTopX
                mov bx, IX
                shl ebx,3
                add eax,ebx
                add edx,eax		; edx = x + Y*res
                add edx, _lomembase
                mov edi,edx

                mov esi, _himembase
		add esi,edi
                sub esi, _lomembase
;               add esi, 1024*256*3

                mov ax, IX2
                sub ax, IX
                inc ax
                mov SqrCptT, ax

                mov ax, IY2
                sub ax, IY
                inc ax
                mov LineCpt, ax
                xor ebx,ebx

                ;printw LineCpt
                ;printcr
                .if LineCpt==0
		  print offset LineCptERR
                  jmp QUIT000
                .endif

                ;printw SqrCptT
                ;printcr
                .if SqrCptT==0
		  print offset SqrCptERR
                  jmp QUIT00U
                .endif


UIIT001:

                push ebx
                mov ax, word ptr SqrCptT
                mov word ptr SqrCpt, ax

UIIT002:
                push ebx

        	mov dx, 8
                .while dx!=0
	          mov eax,[eSi+ebx]
                  mov [eDi+ebx],eax
	          mov eax,[eSi+ebx+4]
                  mov [eDi+ebx+4],eax
                  dec dx
                  add ebx, 640
                .endw

       		pop ebx
                add ebx,8
                dec word ptr SqrCpt

                ;print offset SqrCptLOOP
                cmp word ptr SqrCpt,0
                jne UIIT002

                pop ebx
                add ebx,640*8
                dec word ptr LineCpt
                ;print offset LineCptLOOP
                cmp word ptr LineCpt,0
                jne UIIT001


QUIT00U:
                popall
                ret



;---------------------------------------------------------------------

showTampon2Screen:
;
; Copy from _lomembase a 256k buffer called Tampon to 0a000h by
; 64k chunk. Tampon is used for TEMP storage only.
;
;---------
                pushall
		mov edi, 0a0000h
		mov esi,_lomembase
		ss_setfastwindow 0, 0, mode_info_obj.WinFuncPtr

		cld
		mov edx, 0
		mov bx,5
SIT0014:
		mov cx, 65536/4

		mov edi,0a0000h
SIT0013:

		mov eax, ds:[esi]
		mov gs:[edi],eax
		add edi,4
		add esi,4
		loop SIT0013

                push edx
                xor edx,edx
		mov eax, 65536
                div WGranDD

                pop  edx
		add edx, eax		; was 65536/4096
  		ss_setfastwindow 0, <dx>, mode_info_obj.WinFuncPtr

		dec bx
		or bx,bx
		jne SIT0014
                popall
		ret

;--------------------------------------------------------------------
DrawIma2Screen:
;
; Buffer refers to location identified by _himembase + 256*1024
;  (provided by PMODE)
; Tampon refers to _lomembase
;
; This will call the procedure that will the image into the the
; "TAMPON" and draw it into video memory
;-------------
	        call drawImaInTampon
		call showTampon2Screen
                ret

;---------------------------------------------------------------------

;###################################################################
; Select, Copy , Move Save or Erase.
;###################################################################

align 2
SelectPhase	dw 0

SelectImagePortion:
; This Routine allows to select a portion of the GREAT FULL SCREEN
; image to eventually do something with it
;
; SelectPhase 0 	Only the upper corner showing
;             1		Both lower & upper corner showing
;-----------------
                pushall

		mov ix,0
                mov iy,0
                mov Timer2,0
                mov BreakLoopDi,0
                mov SelectPhase,0

                ;; Calculate IX2
                mov ax, ix
                add ax,TImaLen
                mov ix2,ax
                dec ix2

                ;; Calculate IY2
                mov ax, iy
                add ax, TimaHei
                mov iy2,ax
                dec iy2

                mov ecx, (256*1024)/4
                mov eax, app_Color
                mov edi, dword ptr _himembase

                .while ecx!=0
                  mov [edi],eax
                  add edi,4
                  dec ecx
		.endw

		call DrawImageFullScreen
                call ShowScreen
                call WriteCopyrights
		;call copyBuf2Tampon
                ;call DrawIma2Screen

                ss_drawmouse
                ss_getax
                .while ah!=KEY_F4 && al!=27 && al!=9 && BreakLoopDi!=1
                     call SIPKEYS
                     inc Timer

                     .if word ptr Timer >=5
			mov word ptr Timer,0
                        inc word ptr ParamColor
                        .if word ptr ParamColor>=15
                           mov ParamColor,1
                        .endif
	                call DrawImageBorderInFS2
                     .endif

                     ss_readmouse offset mouse_obj
                     mov ax, mouse_obj.x
		     mov bx, mouse_obj.y
                     mov cx, mouse_obj.boutons

                     .if ax!=mouse_obj.oldx || bx!=mouse_obj.oldy
			  ss_undrawmouse 0,0
		          ss_drawmouse 0,0
                     .endif

                 ss_getax
                .endw

                .if breakloopdi==0
		  call CleanScreen
                  call DrawAllWins
                  call DrawPalColors
                  call RedrawGrild
                  call RedrawImage
		  call ShowScreen

                  call DrawColorBox
                  call WriteCopyrights

	          ss_readmouse offset mouse_obj
                  ss_drawmouse 0,0
                .endif

                popall
                ret
;---------------------------------------------------------------------

SIPKEYS:
;------
		pushall

                mov bx,IY2
		.if (al=="8" || ah==key_up)
                  .if ((IY!=0 && SelectPhase==0) || (bx>IY && SelectPhase==1))
	                call UnDrawBorderInFS2
                        .if SelectPhase==0
                          dec IY
                        .endif
                        dec IY2
                        ss_drawmouse 0,0
                   .endif
                .endif

		.if (al=="2"||ah==key_dn)
                  .if ((IY < (ImageFHei/8 -2) && SelectPhase==0) || (IY2 <(ImageFHei/8 -2) && SelectPhase==1))
	                call UnDrawBorderInFS2
                        .if selectPhase==0
                          inc IY
                        .endif
                        inc IY2
                        ss_drawmouse 0,0
                  .endif
                .endif

                mov bx, IX2
		.if (al=="4" || ah==key_lf)
                  .if ((IX!=0 && SelectPhase==0) || (bx>IX && SelectPhase==1))
	                call UnDrawBorderInFS2
                        .if selectphase==0
			  dec IX
                        .endif
                        dec IX2
                        ss_drawmouse 0,0
                  .endif
                .endif

		.if (al=="6" || ah==key_rg)
                  .if (( IX< (ImageFLen/8 -1) && SelectPhase==0) || (IX2 <(ImageFLen/8-1) && SelectPhase==1))
	                call UnDrawBorderInFS2
                        .if selectphase==0
       		          inc IX
                        .endif
                        inc IX2
                        ss_drawmouse 0,0
                  .endif
                .endif

                     .if al=="C" || al=="c"
                        pushall
                        invoke AskQuestion , offset TXT_WANTOCLEAR, offset CHC_WANTOCLEAR, 15, 2
                        .if al==0
                     	  call FillWithJunk
                          popall
			  call DrawImageFullScreen
                	  call ShowScreen
                	  call WriteCopyrights
		          ss_drawmouse 0,0
                        .else
                          popall
                        .endif
                     .endif

                     .if ah==KEY_F1 ; al=="h" || al=="H"
                        call GeneralHelpSys
                     .endif

                     .if al==32 || al==13
                         .if selectphase==1
                           mov breakloopDi,1
                         .else
                            mov selectphase,1
                            mov ax, ix
                            mov ix2, ax
                            mov ax, iy
                            mov iy2,ax

                         .endif


                     	;call CopyIma2Image
                     .endif

                popall


           	ret
;--------------------------------------------------------------------
SELECT_DIAL01	db "======= IMAGE SELECTED ========",0
SELECT_DIAL02	db "                               ",0
SELECT_DIAL03	db "  M)ove image                  ",0
SELECT_DIAL04	db "  C)opy image                  ",0
SELECT_DIAL05	db "  S)ave image                  ",0
SELECT_DIAL06	db "  E)rase image                 ",0
SELECT_DIAL07	db "                               ",0
SELECT_DIAL08	db "===============================",0

SelectTOPX  	EQU ((80-30)*8)/2
SelectTOPY      EQU 16*4
SelectTcolor    EQU 15
SelectBColor    EQU 1

align 4
SelectDial	dd offset select_dial01, offset select_dial02, offset select_dial03
                dd offset select_dial04, offset select_dial05, offset select_dial06
		dd offset select_dial07, offset select_dial08,-1

;---------------------------------------------------------------------

ShowSelectDialog:
; This dialog box shows you the fallowing option when you selected a
; portion of the image for whatever:
;
; C>opy
; M>ove
; E>rase
; S>ave
;---------------

                  invoke _drawtextWindow,SelectTopx, SelectTopY, offset SelectDial, SelectTcolor, SelectBColor
		ret

;---------------------------------------------------------------------

align 4
LineLenght 	dd 0

CopySelection2Tampon:
;
;  After select an portion of the image, it will be copied to the clipboard
; (so to speak.)
;-------------------

		pushall

		xor eax,eax
		mov ax, iy
                shl eax, 12			; eax = y * 4096

                xor edx,edx
                mov dx, ix
                shl edx, 6			; edx, x*64
                add edx, eax			; edx = x*64 + y*4096
                mov esi, edx
                add esi, _himembase
                add esi, 1024*256; *3

                mov edi, _himembase
                add edi, 1024*256*3

                xor eax,eax
                mov ax, ix2
                sub ax, ix
                inc ax
                shl eax, 6			; lenght per line
                mov lineLenght, eax

                mov ax,iy2
                sub ax, iy
                inc ax				; number of lines
                mov dx, ax


CC2T002:
                push esi
                mov ecx, LineLenght
                shr ecx, 2

CC2T001:
		mov eax, [esi]
                mov [edi],eax
                add esi,4
                add edi,4
                dec ecx
                or ecx,ecx
                jne CC2T001

                pop esi
                add esi,64*64
                dec dx
                or dx,dx
                jne CC2T002

                popall
                ret

;-----------------------------------------------------------------------
EraseSelectionFromBuffer:
;-----------------------
; Call from MakeSelection, this subroutine will erase the selected portion
; of the image( selected by the user). This is used in MOVE, DELETE.
;

		pushall

		xor eax,eax
		mov ax, iy
                shl eax, 12			; eax = y * 4096

                xor edx,edx
                mov dx, ix
                shl edx, 6			; edx, x*64
                add edx, eax			; edx = x*64 + y*4096
                mov esi, edx
                add esi, _himembase
                add esi, 1024*256; *3

                mov edi, _himembase
                add edi, 1024*256*3

                xor eax,eax
                mov ax, ix2
                sub ax, ix
                inc ax
                shl eax, 6			; lenght per line
                mov lineLenght, eax

                mov ax,iy2
                sub ax, iy
                inc ax				; number of lines
                mov dx, ax

;                xor edx,edx

EC2T002:
                push esi
                mov ecx, LineLenght
                shr ecx, 2

EC2T001:
		;ov eax, [esi]
                ;ov [edi],eax
                mov dword ptr [esi],0
                add esi,4
                ;dd edi,4
                dec ecx
                or ecx,ecx
                jne EC2T001

                pop esi
                add esi,64*64
                dec dx
                or dx,dx
                jne EC2T002

                popall
                ret



;---------------------------------------------------------------------

MakeSelection:
;------------
; After selecting a portion of the image, the user will then be asked
; to choose an option.
;
; E> ERASE
; S> Save
; C> Copy
; M> MOVE
;
; This code is handling the selection of an option, reading the keyboard,
; callinf the necessairy code. etc.
		call SelectImagePortion
                .if breakloopDi==1
                   ss_undrawmouse 0,0
                   call ShowSelectDialog
                   call CopySelection2Tampon

                   mov ax, ix2
                   sub ax, ix
                   inc ax
                   mov Timalen,ax

                   mov ax, iy2
                   sub ax, iy
                   inc ax
                   mov Timahei,ax

                   ss_getax
                   .if al>="a" && al <="z"
                      sub al,"a"
                      add al,"A"
                   .endif

                   mov bx,0
                   ss_drawmouse 0,0
                   .while al!=9 && al!=27 && ah!=key_F4 && bx!=1

                      call Mousie
		     .if al=="M"
			call EraseSelectionFromBuffer
			call DragImageInFullScreen
			mov bx,1
                     .endif

                     .if al=="C"
			call DragImageInFullScreen
                        mov bx,1
                     .endif

                     .if al=="S"
                         mov bx,1
                         call RealSaveImaHandler
                         ;call GereSaveImaDir
                     .endif

                     .if al=="E"
			call EraseSelectionFromBuffer
                        mov bx,1
                     .endif

                     ss_getax
                     .if al>="a" && al <="z"
                        sub al,"a"
                        add al,"A"
                     .endif
                   .endw

                .endif

		  call CleanScreen
                  call DrawAllWins
                  call DrawPalColors
                  call RedrawGrild
                  call RedrawImage
		  call ShowScreen

                  call DrawColorBox
                  call WriteCopyrights

	          ss_readmouse offset mouse_obj
                  ss_drawmouse 0,0
                ret

;########################################################################
; This portion is ABOUT change DIRECTORIES.... HA HA HA
;########################################################################
DialogChDirTop  db "=========  CHANGE DIRECTORY...   =======",0
DialogChDirMid  db "                                        ",0
DialogChDirBot  db "========================================",0

;--------------------------------------------------------------------
; Actually it is about changing directories
; but I did'nt wanted to change the name to save developpement time
; because this program is going to HELL. The more I work on it
; the more conveinced I that it will NEVER be used at all.
DrawChDirDlgBox:
;--------------
                pushall
                mov DlgTopLine,0
                mov DlgYLine,0+4

                ; DrawLoadImageDialog Top Line
                mov DlgLine, 0
                OutText DialogTopX, DialogTopY, offset DialogChDirTop,DialogTColor,DialogBColor

                ; DrawLoadImageDialog MidLines
                mov dx, DialogTopY+8
                .while DlgLine != DialogheiSQR-2
                   OutText DialogTopX,<dx>,offset DialogChDirMid,DialogTColor,DialogBColor
		   add dx,8
                   inc DlgLine
                .endw

                ; DrawLoadImageDialog Bottom line
                OutText DialogTopX,<dx>,offset DialogChDirBot,DialogTColor,DialogBColor
                mov WhatLine, 20

                ; Print current path onto dialog box
                call MakeCurrentPath
                OutText DialogTopX+8*2, DialogTopY+8*2,offset CurrentPath, DialogTColor, DialogBColor

                popall
		ret

;------------------------------------------------------------------------
DrawChDirComboBox:
;----------------
; Actually it is about changing directories
; but I did'nt wanted to change the name to save developpement time
; because this program is going to HELL. The more I work on it
; the more conveinced I that it will NEVER be used at all.
                pushall
                ; DrawList of files onto dialog box
                mov WhatLine, 20
                mov dx, DialogFTopY
                ;ov esi, _himembase
                ;dd esi, 512*1024

                ;pushall
                ;print offset testing
                ;popall

                xor eax,eax
                ;ov ax, DlgYLine
                mov ax, DlgTopLine
                shl eax, 5
                add eax, _himembase
                add eax, 512*1024
                mov esi,eax

                mov byte ptr [esi+15],0
                .while WhatLine!=0 && byte ptr [esi]!=-1
                  OutText DialogFTopX,<dx>,<esi>,DialogFTColor,DialogFBColor
     		  add dx,8
                  add esi,32
                  mov byte ptr [esi+15],0
                  dec WhatLine
                .endw

                call DrawYellowLine

                popall
                ret

;---------------------------------------------------------------------
ChDirDlgKeys:
;-----------
; Actually it is about changing directories
; but I did'nt wanted to change the name to save developpement time
; because this program is going to HELL. The more I work on it
; the more conveinced I that it will NEVER be used at all.

               ;pushall

		.if al=="8" || ah==KEY_UP
                    .if DlgYLine!=0
			call DrawWhiteLine
                        dec DlgYLine
                        call DrawYellowLine

		    .else
                       .if DlgTopLine!=0
                          ;call DrawWhiteLine
                          dec DlgTopLine
			  ;call RedrawAllFiles
                          call DrawChDirComboBox
                          call DrawYellowLine
                       .endif
                    .endif

                .endif

                .if al=="2" || ah==KEY_DN
                    mov bx, DlgYLine
                    add bx, DlgTopLine
                    mov cx, NbFiles
                    dec cx
                    .if DlgYLine<DialogFHeiSQR-1 && bx<cx
			call DrawWhiteLine
                        inc DlgYLine
                        call DrawYellowLine

                    .else

                       .if bx<cx
                          ;call DrawWhiteLine
                          inc DlgTopLine
			  ;call RedrawAllFiles
                          call DrawChDirComboBox
                          call DrawYellowLine
                       .endif
                    .endif
                .endif


                .if ah==KEY_F1
                   pushall
                     invoke _drawtextWindow,HelpScrX,HelpScrY+8*0 ,offset HelpForDialog,HelpTColor,HelpBColor
                     ss_getax
                     .while al!=27 && al!=9 && ah!=KEY_F1 && al!=13 && al!=32 && ah!=KEY_UP && ah!=KEY_DN
                        ss_getax
                     .endw
                     call showScreen2
                     call DrawChDirDlgBox
                     call DrawChDirComboBox
  		     ;call DrawImaLoadDialogBox
                   popall
                .endif


                ;; Select a file or a directory
                .if al==13 || al==" "
                  pushall
                  mov dx, DlgYLine
                  shl dx, 3
                  add dx, DialogFTopY

                  xor eax,eax
                  mov ax, DlgYLine
                  add ax, DlgTopLine
                  shl eax, 5
                  add eax, _himembase
                  add eax, 512*1024
                  mov esi,eax

                  mov al, [esi]
                  .if al==2		; TYPEDEF DIR
                     add esi,16
                     call changeDir
                     invoke DoDir, offset ALL_IMA
                     call DrawChDirDlgBox
                     call DrawChDirComboBox
     		     ;call DrawImaLoadDialogBox
                     popall
                  .endif

                  .if al==1
                     add esi,16
                     ;call LoadImaIntoBuffer
                     ;call DrawImaLoadDialogBox
		     ;call RedrawAllFiles
                     ;call DrawYellowLine
                     popall
                  .endif

                  .if al==3
                   mov al, [esi+1]
                   sub al,"A"
                   mov v86r_ah,0eh
                   mov v86r_dl, al
                   mov al, 21h
                   int 33h

                   invoke DoDir, offset ALL_IMA
		   ;call DrawImaLoadDialogBox
                   call DrawChDirDlgBox
                   call DrawChDirComboBox
                   popall
                  .endif


                .endif
                ret

;----------------------------------------------------------------------
align 4
NewImaName	db 32 DUP (0)
NamePtr		dd 0
Blank16		db 16 DUP (" ")
		db 0

GereChangeDir:
;------------
; Actually it is about changing directories
; but I did'nt wanted to change the name to save developpement time
; because this program is going to HELL. The more I work on it
; the more conveinced I that it will NEVER be used at all.
;-------------
                pushall
		invoke DoDir, offset ALL_IMA

                mov DlgYLine,0+4
                add DlgTopLine,0
                mov OutGereImaDir,0
                mov NewImaName,0
                mov NamePtr,0
                ;call CountDirs

                ss_undrawmouse 0,0
                call DrawChDirDlgBox
                call DrawChDirComboBox
                call DrawYellowLine

                ss_drawmouse 0,0

                ss_getax
                .while al!=27 && ah!=KEY_F4 && ah!=KEY_F3 && al!=9 && OutGereImaDir!=1 && ah!=KEY_F6 && ah!=KEY_F7 && ah!=KEY_F8
                   call ChDirDlgKeys
                   call Mousie
                   ss_getax
                .endw

                ss_undrawmouse  0,0
                call ShowScreen2
                ss_drawmouse 0,0

                popall
                ret


;-------------------------------------------------------------------------
GetDriveData:
;-----------
;
; IN
; al = drive number
;      0 current (default or what ever)
;      1 A
;      2 B
;      ...
;
; OUT
; Carry raised means ERROR, v86r_al = ffh
; Otherwise
;      V86R_AL    = Sector per cluster
;      V86R_DS:BX = Segment and offset of media ID byte
;      V86R_CX    = Size of physical sector (bytes)
;      V86R_DX    = Number of cluster of drive
;      al	  = media id byte
;

	push esi
	mov v86r_ah, 1ch		; mov ah, 1ch
	mov v86r_dl, al			; mov dl, al ( desired drive)
        mov al, 21h			; int 21h
        int 33h				; Call PMODE  realmode INT handler

        xor eax,eax
        mov ax, v86r_ds
        shl eax,4			; eax = segment *16
        mov esi,eax                     ; esi = seg*16
        xor eax,eax
        mov ax, v86r_bx                 ; eax=offset
	add edi, eax    		; esi = seg*16 + offset
        mov al, gs:[esi]
	pop esi
        ret

;--------------------------------------------------------------------
;--------------------------------------------------------------------
;####################################################################
; It is about time to save the .IMA to disk...
;####################################################################
; This is important. Yeah! If he can't save, what is it worth?
;--------------------------------------------------------------------

DialogSAVEIMATOP db "========      SAVE IMAGE AS      =======",0
DialogSAVEIMAMID db "                                        ",0
DialogSAVEIMABOT db "========================================",0

SAVEIMA_ERR1	db "==== ERROR! ====",0
SAVEIMA_ERR2	db "   Unable to    ",0
SAVEIMA_ERR3	db "   save file!   ",0
SAVEIMA_ERR4	db "================",0

align 4
SAVEIMA_ERR	dd offset SaveIma_Err1, offset SaveIma_Err2
		dd offset SaveIma_err3, offset SaveIma_Err4
                dd -1

;---------------------------------------------------------------------
DrawREALSaveImaDlgBox:
;--------------------
; This subroutine is call to draw SaveIma dialog box.
; The dialogue box is as above.
;

                pushall
                mov DlgTopLine,0
                mov DlgYLine,0+4

                ; DrawLoadImageDialog Top Line
                mov DlgLine, 0
                OutText DialogTopX, DialogTopY, offset DialogSaveImaTop,DialogTColor,DialogBColor

                ; DrawLoadImageDialog MidLines
                mov dx, DialogTopY+8
                .while DlgLine != 5 ;DialogheiSQR-2
                   OutText DialogTopX,<dx>,offset DialogSaveImaMid,DialogTColor,DialogBColor
		   add dx,8
                   inc DlgLine
                .endw

                ; DrawLoadImageDialog Bottom line
                OutText DialogTopX,<dx>,offset DialogSaveImaBot,DialogTColor,DialogBColor
                mov WhatLine, 5

                ; Print current path onto dialog box
                call MakeCurrentPath
                OutText DialogTopX+8*2, DialogTopY+8*2,offset CurrentPath, DialogTColor, DialogBColor

                popall
		ret

;---------------------------------------------------------------------

align 4
NewImaFilename	db 64 DUP (0)
NewImaPtr	dd 0
CTimer		dw 1

ValidChar	db "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!%&()_+="
		DB "<>#- ",0
LeaveSaveIma	dw 0



;---------------------------------------------------------------------

REALSaveImaHandler:
;-----------------
; This is the SaveImaHandler. It will draw the SaveIma Dialog Box, read
; the keyboard, make-up a filename, ... etc. And ofcourse, will save
; the image once everything is done.

		pushall

                mov NewImaPtr,0
                mov NewImaFileName,0
                  mov ebx, NewImaPtr
                  mov edi, offset NewImaFileName
                  mov byte ptr [edi+ebx],0

		call DrawREALSaveImaDlgBox
		call WriteNewImaNameIntoDialogBox

                mov LeaveSaveIma,0
                ss_getax
                .while al!=9 && al!=27 && ah!=KEY_F4 && LeaveSaveIma!=1

                  mov ebx, NewImaPtr
                  mov edi, offset NewImaFileName
                  mov byte ptr [edi+ebx],0

                  call WriteCursor

                  .if CTimer<= 15
                     inc CTimer
                  .else
                     mov CTimer,1
                  .endif

                  ; Maj "al"
                  .if al>="a" && al<="z"
                     sub al,"a"
                     add al,"A"
                  .endif

                  mov esi, offset ValidChar
                  .while byte ptr [esi]!=0 && NewImaPtr!=32
                    .if al==byte ptr [esi]
                     mov ebx, NewImaPtr
                     mov esi, offset NewImaFilename
                     mov [esi+ebx], al
                     inc NewImaPtr
		     call WriteNewImaNameIntoDialogBox
                     mov bx,0
                     jmp XCarChk0001
                    .endif
                    inc esi
                  .endw

                  .if al==8 && NewImaPtr!=0
                     mov ebx, NewImaPtr
                     mov esi, offset NewImaFilename
                     mov byte ptr [esi+ebx], 0
                     mov CTimer, DialogBColor
                     call WriteCursor
                     dec NewImaPtr
                  .endif


XCarChk0001:
                  .if ah==KEY_F6 || ah==KEY_F7 || ah==KEY_F8 || al=="\"
                     call GereChangeDir
                     call ShowScreen2
	             ;call CleanScreen
                     ;call DrawAllWins
                     ;call DrawPalColors
                     ;call RedrawGrild
                     ;call RedrawImage
		     ;call ShowScreen
                     ;call DrawColorBox
                     call WriteCopyrights
  		     call DrawREALSaveImaDlgBox
		     call WriteNewImaNameIntoDialogBox

                  .endif

                  .if al==13
                     call SaveImaModule
                     mov LeaveSaveIma,bx
                     .if bx==0
			invoke _drawtextWindow,DialogFTopx, DialogFTopY ,offset SaveIma_Err, 15,4
                        ss_getax
                        .while al!=9 && al!=27 && al!=32 && al!=13
                           ss_getax
                        .endw
                        call ShowScreen2
                        call WriteCopyrights
        	        call DrawREALSaveImaDlgBox
		        call WriteNewImaNameIntoDialogBox
                     .endif

                  .endif

                  ss_getax
                .endw

                popall
                ret

;-------------------------------------------------------------------
;-------------------------------------------------------------------

FilenameLine	EQU 3
FilenameCol	EQU 3-1

WriteNewImaNameIntoDialogBox:
;
; Write the name of the new ima on the save ima dialog box. The
; is entered progressivly by the user. In a loop found in
; the routine REALSaveImaHandler
;
                  mov ebx, NewImaPtr
                  mov edi, offset NewImaFileName
                  mov byte ptr [edi+ebx],0
                OutText DialogTopX+FilenameCol*8,DialogTopY+FilenameLine*8,offset NewImaFileName,DialogTColor,DialogBColor
                call WriteCursor
		ret

;------------------------------------------------------------------
WriteCursor:
;
; Write a cursor in the SaveIma Dialog box. At a given offset
; specified by NewImaPtr.
;

                pushall
                mov bx,DialogTopX+FilenameCol*8
                mov eax, NewImaPtr
                shl ax,3
                add bx,ax
                mov cx,DialogTopY+FilenameLine*8
                mov ax, Ctimer
                OutCar <bx>, <cx>, "@",<al>,DialogBColor
                popall
		ret


;###################################################################
; SPECIAL OPTIONS
;###################################################################

;		    123456789012345678901234567890123456789
SpecialDlg1	db "=========   SPECIAL OPTIONS      =======",0
SpecialDlg2	db "                                        ",0
SpecialDlg3	db " E. Enlarge 1st quarter by x2           ",0
SpecialDlg4	db " L. Flip Left/Right the entire image    ",0
SpecialDlg5	db " U. Flip Up/Down the entire image       ",0
SpecialDlg6	db " R. Rotate Image                        ",0
SpecialDlg7	db " S. Shift image /Wrap around            ",0
SpecialDlg8	db "                                        ",0
SpecialDlg9	db "========================================",0

SpcDlgTopX	EQU ((80-40)/2)*8
SpcDlgTopY	EQU 16
SpcDlgTColor    EQU 15
SpcDlgBColor    EQU 1

align 4
SpecialDlg	dd offset SpecialDlg1,offset SpecialDlg2,offset SpecialDlg3
		dd offset SpecialDlg4,offset SpecialDlg5, offset SpecialDlg6
		dd offset SpecialDlg7,offset SpecialDlg8,offset SpecialDlg9
                dd -1

SpecialOptions:
                pushall

                ss_undrawmouse 0,0
		call DrawSpcDlg

                ss_drawmouse 0,0
                ss_getax
                .if al>="a" && al<="z"
                   sub al,"a"
                   add al,"A"
                .endif

                ;ss_undrawmouse 0,0

                xor bx,bx
                .while al!=9 && al!=27 && ah!=KEY_F10 && al!="Q" && bx==0


                   .if al=="E"
		      call CnfDlgBoxHandler
                     .if bx==1
                       call EnlargeImage
                     .else
			call ShowScreen2
        	        call DrawColorBox
			call DrawSpcDlg
                     .endif
                   .endif

                   .if al=="L"
			call FlipLfRg
                   .endif

                   .if al=="U"
                   	call FlipUpDn
                   .endif

                   .if al=="R"
		      call CnfDlgBoxHandler
                     .if bx==1
                   	call RotateImage
                     .else
			call ShowScreen2
        	        call DrawColorBox
			call DrawSpcDlg
                     .endif
                   .endif


                   .if al=="S"
		     call EnteringShiftMode
                     .if bx!=1
                        ss_undrawmouse
			call DrawSpcDlg
                        ss_drawmouse 0,0
                     .endif

                   .endif

                   call Mousie

                   ss_getax
                   .if al>="a" && al<="z"
                     sub al,"a"
                     add al,"A"
                   .endif
                .endw
		call ShowScreen2
                call DrawColorBox
                call RedrawGrild
                call RedrawImage
		call ShowScreen

                call DrawColorBox
                call WriteCopyrights
                ss_drawmouse 0,0

                popall
                ret

;-------------------------------------------------------------------
;		    123456789
DlgCnf1		db "==========================",0
DlgCnf2     	db " What you are about to do ",0
DlgCnf3     	db " cannot be reversed.      ",0
DlgCnf4     	db "                          ",0
DlgCnf5     	db " Do you STILL want to     ",0
DlgCnf6     	db " continue? (Y/N)?         ",0
DlgCnf7     	db "==========================",0


align 4
DlgCnf	        dd offset DlgCnf1, offset DlgCnf2, offset DlgCnf3
		dd offset DlgCnf4, offset DlgCnf5, offset DlgCnf6
		dd offset DlgCnf7, -1

DlgCnfTopX	EQU 8*(80-(offset DlgCnf2- offset DlgCnf1))/2
DlgCnfTopY      EQU 32
CnfTColor	EQU 15
CnfBColor	EQU 4

;--------------------------------------------------------------------
DrawDlgCnf:
                  invoke _drawtextWindow,DlgCnfTopX,DlgCnfTopY,offset DlgCnf,CnfTColor,CnfBColor
		  ret
;--------------------------------------------------------------------

EICol		dw 0
EILine		dw 0
EIFNTLine	dw 0

align 4
EIStruct	dd 16*0 + 0, 16*0 + 4, 16*0 + 64, 16*0 + 64+4
		dd 16*1 + 0, 16*1 + 4, 16*1 + 64, 16*1 + 64+4
		dd 16*2 + 0, 16*2 + 4, 16*2 + 64, 16*2 + 64+4
		dd 16*3 + 0, 16*3 + 4, 16*3 + 64, 16*3 + 64+4

		dd 4096+16*0,4096+16*0+4,4096+16*0+64,4096+16*0+64+4
		dd 4096+16*1,4096+16*1+4,4096+16*1+64,4096+16*1+64+4
		dd 4096+16*2,4096+16*2+4,4096+16*2+64,4096+16*2+64+4
		dd 4096+16*3,4096+16*3+4,4096+16*3+64,4096+16*3+64+4
;---------------------------------------------------------------------

EnlargeImage:
                pushall
		mov EICol,32
                mov EILine, ((400/8) -2)/2

                ; Setup source addr
                mov esi, _himembase
                add esi, 256*1024

                ; Setup Dest addr
                mov edi, _lomembase

EI0003:
                push edi
                push esi
		mov EICol,32


EI0002:
                mov edx, offset EIStruct
		mov EIFNTLine,16

EI0001:
                ; pix 1-2
                mov eax, [esi]
                mov bl,al		; read 1pix
                mov bh,al
                push bx
                mov bl,ah		; read 2pix
                mov bh,ah
                shl ebx,16
                pop bx
		mov ecx, [edx]
                mov [edi+ecx], ebx	; copy 2 (extended as 4)
                mov [edi+ecx+8], ebx	; copy 2 (extended as 4)
                add edx,4

                ; pix 3-4
		shr eax,16
                mov bl,al		; read 1pix
                mov bh,al
                push bx
                mov bl,ah		; read 2pix
                mov bh,ah
                shl ebx,16
                pop bx
                mov ecx, [edx]
                mov [edi+ecx], ebx	; copy 2 (extended as 4)
                mov [edi+ecx+8], ebx	; copy 2 (extended as 4)
		add edx,4

                add esi,4
                dec EIFNTLine
                cmp EIFNTLine,0
                jne EI0001

		add edi, 64*2
                dec EICol
                cmp EICol,0
                jne EI0002

		pop esi
                pop edi
                add esi,4096
                add edi,4096*2
		dec EILine
                cmp EILine,0
                jne EI0003

                call CopyBack2Buffer

                popall
		mov bx,1
		ret

;---------------------------------------------------------------------
CopyBack2Buffer:
		pushall
                mov ecx, 256*1024/4
                mov esi, _lomembase
                mov edi, _himembase
                add edi,256*1024
                xor ebx,ebx

EI000X:
                mov eax, [esi+ebx]
                mov [edi+ebx],eax
                add ebx,4
                dec ecx
                or ecx,ecx
                jne EI000X

                popall
                ret

;--------------------------------------------------------------------
align 2
ImgRow00	dw 0
ImgLine00	dw 0
FNTLine00	dw 0

FlipLfRg:
;=======
;
; This routine will flip the image lf/rg
;
		pushall

                ; Setup source addr
                mov esi, _himembase
                add esi, 256*1024

                ; Setup Dest addr
                mov edi, _lomembase

                mov ImgLine00, (400-16)/8

FLR003:
                mov ImgRow00, 512/8
                mov edx,63*64


FLR002:
                mov FNTLine00,8
FLR001:

                mov eax, [esi]
                mov bl,ah
                mov bh,al
                shl ebx,16
                shr eax,16
                mov bl,ah
                mov bh,al
		mov [edi+edx+4], ebx

                mov eax, [esi+4]
                mov bl,ah
                mov bh,al
                shl ebx,16
                shr eax,16
                mov bl,ah
                mov bh,al
		mov [edi+edx], ebx

                add esi,8
                add edx,8
		dec FNTLine00
                cmp FNTLine00,0
                jne FLR001

		sub edx,128
       		dec ImgRow00
                cmp ImgRow00,0
                jne FLR002

                add edi,4096
                dec ImgLine00
                cmp ImgLine00,0
                jne FLR003

                call CopyBack2Buffer

                popall
                mov bx,1
		ret

;-------------------------------------------------------------------
;ImgRow00	dw 0
;ImgLine00	dw 0
;FNTLine00	dw 0

FlipUpDn:
;=======
;
; This routine will flip the image up/dn
;
		pushall
                ; Setup source addr
                mov esi, _himembase
                add esi, 256*1024

                ; Setup Dest addr
                mov edi, _lomembase
                add edi, ((400-16)/8 -1 ) *4096 +7*8

                mov ImgLine00, (400-16)/8

FUD003:
		push edi
                mov ImgRow00, 512/8

FUD002:
                push edi
                mov cx,8
FUD001:
		mov eax, [esi]
                mov [edi],eax
		mov eax, [esi+4]
                mov [edi+4],eax
                add esi,8
                sub edi,8
                loop FUD001

                pop edi
                add edi,64
                dec ImgRow00
                cmp ImgRow00,0
                jne FUD002

                pop edi
		sub edi,4096
		dec ImgLine00
		cmp ImgLine00,0
                jne FUD003


                call CopyBack2Buffer

                popall
                mov bx,1
                ret

;--------------------------------------------------------------------

align 2
X1		dw 0
Y1              dw 0
X2		dw 0
Y2		dw 0

RotateImage:
;=======
;
; This routine will rotate the image 90' to the left.
;

                pushall
                ; Setup source addr
                mov esi, _himembase
                add esi, 256*1024

                ; Setup Dest addr
                mov edi, _lomembase
                add edi, 47*64 +7
                mov Y1,48

RI004:
		push edi
                push esi
		mov X1,48

RI003:
                push edi
                mov Y2, 8

RI012:
                push edi
                mov X2, 8

RI011:
                mov al,[esi]
                mov [edi],al
                inc esi
                add edi,8
		dec X2
                cmp X2,0
                jne RI011

                pop edi
                dec edi
                dec Y2
                cmp Y2,0
                jne RI012

                pop edi
                add edi,4096
                dec X1
                cmp X1,0
                jne RI003

		pop esi
                pop edi
                add esi,4096
                sub edi,64
                dec Y1
                cmp Y1,0
                jne RI004

                call CopyBack2Buffer

                popall
                mov bx,1
                ret

;--------------------------------------------------------------------

DrawCnfDlgBox:
;============
; CnfDlg (RED Confirmation dialog box) is used by the ROTATE & ENLARGE
; option of the SPECIAL OPTION F10 MENU.
;

                invoke _drawtextWindow,DlgCnfTopX,DlgCnfTopY,offset DlgCnf,CnfTColor,CnfBColor
		ret

;----------------------------------------------------------------------

CnfDlgBoxHandler:
;===============
; This code is responsible for the drawing the Confirmation Dialog Box
; and awaiting the user's response to the question.
;


                ss_undrawmouse 0,0
		call DrawCnfDlgBox
                ss_drawmouse

		ss_getax
                .if al>="a" && al<="z"
                   sub al,"a"
                   add al,"A"
                .endif

                .while al!=9 && al!=27 && al!="Y" && al!="N"
		  call Mousie

                  ss_getax
                  .if al>="a" && al<="z"
                     sub al,"a"
                     add al,"A"
                  .endif
                .endw

                .if al=="Y"
                  mov bx,1
                .else
                  mov bx,0
                .endif

		ret

;--------------------------------------------------------------------
DrawSpcDlg:
;=========
; Draw the SPECIAL OPTION F10 dialog box. BLUE.
;


		invoke _drawtextWindow,SpcDlgTopX,SpcDlgTopY,offset SpecialDlg,SpcDlgTColor,SpcDlgBColor
           	ret
;--------------------------------------------------------------------
;####################################################################
EnteringShiftMode:
;-----------------
; The underling code will handle IMA shifting & Wrap around. This
; option is expected to be painfully slow on OLD 386 & 486 machines.
; Too slow for YOU, then get a fancy new PENTIUM. I heard that prices
; are dropping fast.
;####################################################################

		call DrawAppColor
		call DrawImageFullScreen
                call ShowScreen
                call WriteCopyrights

                ss_drawmouse 0,0
                ss_getax
                mov bx,0
                .while ah!=KEY_F5 && al!=27 && al!=32 && al!=9 && al!=13
		   .if al=="8" || ah==KEY_UP
                      call ShiftUp
      		      call DrawImageFullScreen
                      call ShowScreen
                      ss_drawmouse 0,0
                   .endif

		   .if al=="2" || ah==KEY_DN
                      call ShiftDn
      		      call DrawImageFullScreen
                      call ShowScreen
                      ss_drawmouse 0,0
                   .endif

		   .if al=="4" || ah==KEY_LF
                      call ShiftLf
      		      call DrawImageFullScreen
                      call ShowScreen
                      ss_drawmouse 0,0
                   .endif

		   .if al=="6" || ah==KEY_RG
                      call ShiftRg
      		      call DrawImageFullScreen
                      call ShowScreen
                      ss_drawmouse 0,0
                   .endif

                   ; Shift UP/LF
                   .if al=="7" || ah==KEY_HOME
                      call ShiftUp
                      call ShiftLf
      		      call DrawImageFullScreen
                      call ShowScreen
                      ss_drawmouse 0,0
                   .endif

                   ; Shift UP/RG
                   .if al=="9" || ah==KEY_PgUp
                      call ShiftUp
                      call ShiftRg
      		      call DrawImageFullScreen
                      call ShowScreen
                      ss_drawmouse 0,0
                   .endif

                   ; Shift DN/LF
                   .if al=="1" || ah==KEY_END
                      call ShiftDn
                      call ShiftLf
      		      call DrawImageFullScreen
                      call ShowScreen
                      ss_drawmouse 0,0
                   .endif

                   ; Shift DL/RG
                   .if al=="3" || ah==KEY_PgDn
                      call ShiftDn
                      call ShiftRg
      		      call DrawImageFullScreen
                      call ShowScreen
                      ss_drawmouse 0,0
                   .endif

		 call Mousie
                 ss_getax
                .endw

		call CleanScreen
                call DrawAllWins
                call DrawPalColors
                call RedrawGrild
                call RedrawImage
		call ShowScreen

                call DrawColorBox
                call WriteCopyrights

                ss_readmouse offset mouse_obj
                ss_drawmouse 0,0
                ret


;-----------------------------------------------------------------------
align 4
SLine		dw 0
SFnt		dw 0

ShiftUp:
;=======
; This routine will shift the image up one byte (pixel) at a time
; wrapping it around when applicable.
;
		pushall

                ; Copy the 1st line to tampon
		mov esi, _himembase
                add esi, 256*1024
                mov edi, _lomembase
                xor ebx,ebx
                mov cx, 4096/4

SU001:
                mov eax, [esi+ebx]
                mov [edi+ebx],eax
                add  ebx,4
                loop SU001

                ; Setup & Do the Shift-Up
		mov SLine,(400-16)/8
SU004:
                xor ebx,ebx
		mov SFNT,64
SU003:
                mov cx,7
SU002:
		mov eax,[ebx+esi+0+8]
                mov [ebx+esi],eax
                mov eax, [ebx+esi+8+4]
                mov [ebx+esi+4],eax
                 add ebx,8
                dec cx
                or cx,cx
                jne SU002

		mov eax,[esi+4096]
                mov [ebx+esi],eax
                mov eax, [esi+4096+4]
                mov [ebx+esi+4],eax
                xor ebx,ebx
                add esi,64
                dec SFNT
                cmp SFNT,0
                jne SU003

		;add esi,4096
                dec SLine
                cmp Sline,0
                jne SU004

                ; Copy the final line
                mov cx,64
                mov esi, _himembase
                add esi,1024*256
                add esi, ((400-16)-1)/8 *4096
                add esi,8*7
                mov ebx, _lomembase

SU005:
                mov eax, [ebx]
                mov [esi],eax
                mov eax, [ebx+4]
                mov [esi+4],eax
                add ebx,64
                add esi,64
                dec cx
                or cx,cx
                jne SU005

		popall
                ret

;-------------------------------------------------------------------
;SLine		dw 0
;SFnt		dw 0

ShiftDn:
;======
; This routine will shift the image down one byte (pixel) at a time
; wrapping it around when applicable.
;
                pushall

                ; Copy the last line to tampon
		mov esi, _himembase
                add esi, 256*1024
                add esi, ((400-16)/8 -1)*4096
                mov edi, _lomembase
                xor ebx,ebx

                mov cx, 4096/4
		.while cx!=0
                  mov eax, [esi+ebx]
                  mov [edi+ebx],eax
                  add  ebx,4
                  dec cx
                .endw

                mov edx,esi
                sub edx,4096

                mov Sline, (400-16)/8

SD003:
                mov SFnt,64
                push edx
                push esi

SD002:
                mov ebx, 6*8
                mov cx,7


                mov eax, [esi+7*8]
                mov [esi+4096],eax
                mov eax, [esi+7*8 +4]
                mov [esi+4096+4],eax


SD001:
                mov eax, [esi+ebx]
                mov [esi+ebx+8],eax
                mov eax, [esi+ebx+4]
                mov [esi+ebx+8+4],eax

                sub ebx,8
                dec cx
                or cx,cx
                jne SD001

                mov eax, [edx+7*8]
                mov [esi],eax
                mov eax, [edx+7*8 +4]
                mov [esi+4],eax

                add edx,64
                add esi,64
		dec SFnt
                cmp SFnt,0
                jne SD002

		pop esi
                pop edx
                sub esi,4096
                sub edi,4096
       		dec SLine
                cmp SLine,0
                jne SD003

                mov esi,_lomembase
                mov edi,_himembase
                add edi, 1024*256
                ;add edi, ((400-16)/8 -1)*4096

                mov cx, 64
                .while cx!=0
                  mov eax , [esi+7*8]
                  mov [edi],eax
                  mov eax , [esi+7*8+4]
                  mov [edi+4],eax
                  add edi,64
                  add esi,64
                  dec cx
                .endw


                popall
		ret

;-------------------------------------------------------------------
;SLine		dw 0
;SFnt		dw 0
tempbyte	db 8 DUP (0)
		db 16 DUP (0)

ShiftLf:
;======
; This routine will shift the image LEFT one byte (pixel) at a time
; wrapping it around when applicable.
;

		pushall

                mov esi, _himembase
                add esi, 256*1024

                mov Sline,(400-16)/8
SL002:

                mov ebx, offset tempbyte
                mov cx,8*64
SL001:
		mov eax, [esi]
                mov edx, [esi+4]

                .if ebx< offset tempbyte +8
                  mov [ebx],al
                  inc ebx
                .endif

                shr eax,8
                mov [esi],eax
                mov [esi+3],dl

                shr edx,8
                mov [esi+4],edx
                mov al, [esi+64]
                mov [esi+7],al

		add esi,8
                dec cx
                or cx,cx
                jne SL001


                xor ebx,ebx
                mov cx,8
SL003:
                mov al, byte ptr [tempbyte+ebx]
                mov [esi-64+7+ebx*8],al
                inc ebx
                dec cx
                or cx,cx
                jne SL003

		dec sline
                cmp sline,0
                jne SL002

                popall
		ret

;-------------------------------------------------------------------

ShiftRg:
;======
; This routine will shift the image RIGHT one byte (pixel) at a time
; wrapping it around when applicable.
;
                pushall

                mov esi, _himembase
                add esi, 256*1024
                add esi, 64*63+7*8

                mov Sline,(400-16)/8

SR002:

                mov ebx,offset tempbyte +7
                push esi
                mov cx,8*64

SR001:
                mov eax, [esi]
                shl eax,8
                mov al,[esi-64+7]

                mov edx, [esi+4]
		shl edx,8
                mov dl,[esi+3]

                mov [esi],eax
                mov al, [esi+7]
                mov [esi+4],edx
                .if ebx>= offset tempbyte ; cx<8*64 -8
                  mov [ebx],al
                  dec ebx
                .else
                  mov [esi+64],al
                .endif

                sub esi,8
                dec cx
                or cx,cx
                jne SR001

		xor ebx,ebx
                mov cx,8
SR003:
                mov al, byte ptr [tempbyte+ebx]
                mov [esi+ebx*8+8],al
                inc ebx
                dec cx
                or cx,cx
                jne SR003

                pop esi
                add esi,4096
                dec SLine
                cmp Sline,0
                jne SR002

                popall
		ret

;------------------------------------------------------------------------

DrawAppColor:
;===========
		pushall
                mov ecx, (256*1024)/4
                mov eax, app_Color
                mov edi, dword ptr _himembase

DAC000:         mov [edi],eax
                add edi,4
                dec ecx
                cmp ecx,0
                jne DAC000
                popall
		ret

;########################################################################
;
; The real "SaveImaModule"
;
; Now featuring "primitive" compression to save hard drive space.
; New header. Etc.
;
; IMC FORMAT 1.0 (compressed IMA file)
; - 0-3     HEADER "IMC1"
; - 4-5     LENGHT, HEIGHT in FNT
; - 6...    compressed FNT data
;
; ------------------------------------
;
; Compression format
;
; when FF is found...
;   the next byte is the char (unless FF too)
;   the two fallowing bytes is a word counter for repeat
;
;########################################################################
;
; MEMORY MAP STRUCTURE
;_himembase			Screen buffer
;_himembase + 256k		Image buffer
;_himembase + 512k		Directories
;_himembase + 256*3k		Clipboard
;
;########################################################################


align 4
NILEN		dw 0
NIHEI		dw 0
NewImaHeader	db "IMC1"
NIHEADER	dw 0
HowMany		dw 0
CurChar		db 0
align 4
ImcSize		dd 0


SaveImaModule:
		mov esi, offset _IMA
                mov edi, NewImaPtr
                add edi, offset NewImaFilename
		mov cx, 5

                .while cx!=0
                  mov al, [esi]
                  mov [edi],al
                  dec cx
                  inc esi
                  inc edi
                .endw

                ; calculating the lenght
                mov ax, ix2
                sub ax, ix
                inc ax
                mov NILEN,ax
                mov byte ptr NiHeader, al

                ; calculating the height
                mov ax,iy2
                sub ax, iy
                inc ax
                mov NIHEI,ax
                mov byte ptr NiHeader+1,al

                ; create a new .iMA
                mov edx, offset NewImaFilename		; edx =filename
                call _createfile
                jc ErrSaveIma				; v86r_bx=handle

                ; Write .IMA header to file
                mov edx, offset NewImaHeader		; offset NIHEADER
                mov ecx,6
                call _writefile
                jc ErrSaveIma

                ; Calculating the source addr
                xor eax,eax
                mov ax, iy
                shl eax, 12

		xor ebx,ebx
                mov bx, ix
                shl ebx,6

                add eax,ebx
                mov esi, eax
                add esi, _himembase
                add esi, 1024*256

                ; Calculating the destination address
                mov edi, _himembase
                add edi, 1024*256*3

                ; Lenght of a line of FNT (in the image that is)
                xor eax,eax
                mov ax, NILEN
                shl eax, 6
                mov ecx,eax

                ; copy data to a buffer
                mov dx, NIHEI
                .while dx!=0

                  push ecx
                  push esi
                  shr ecx,2
SIM0010:          mov eax, [esi]
                  mov [edi],eax
                  add edi,4
                  add esi,4
                  dec ecx
                  or ecx,ecx
                  jne SIM0010
                  pop esi
                  pop ecx

                  add esi, 4096
                  dec dx
                .endw


                ;;
                mov esi, _himembase             ; image data was copied                				; to
                add esi, 1024*256*3             ; into the tampon area
                				; locate 768k passed himem
                                                ; (sort of)

                mov edi, _himembase    		; using Screentampon as
                				; buffer for compressed
                                                ; data


                xor dx,dx
                mov ax, NILEN
                mul word ptr NIHEI
                shl edx,16
                mov dx,ax			; edx = NILEN*NIHEI
                shl edx, 6			; edx = NILEN*NIHEI*64

                mov al, [esi]
                mov CurChar,al
                mov HowMany,1

                .if al==0ffh
                  dec al
                  dec CurChar
                .endif

                inc esi

                ;;
                .while edx!=0			; while pas fini
		  mov al, [esi]
                  inc esi
                  .if al==0ffh			; si al=ff alors al=fe
                    dec al
                  .endif

                  .if al== CurChar && HowMany !=0ffffh  ; si le nouveau
                                                        ; caractère est
                                                        ; identique au
                                                        ; précédent
                                                        ; alors augmenter
                                                        ; le compteur.
                    inc HowMany

                  .else					; autrement
                  					; Curchar prend
                                                        ; la valeur du
                                                        ; nouveau caractère
                                                        ; et CurChar est
                                                        ; loader dans
                                                        ; al.

                    mov ah,al
                    mov al, CurChar
                    mov CurChar,ah

                    .if HowMany<=4			; Si la répétition
                    					; est moins que 4x
                                                        ; alors code
                                                        ; de compression
                                                        ; sans importance.

                      mov cx, HowMany
SIM0100:

                      mov [edi],al
                      inc edi
                      dec cx
                      or cx,cx
                      jne SIM0100
                    .else				; Autrement
                    					; ajouter code
                    					; de compression
                                                        ; à la séquence
                      mov byte ptr [edi],0ffh
                      mov [edi+1], al
                      mov al,byte ptr Howmany
                      mov [edi+2], al
                      mov al,byte ptr Howmany+1
                      mov [edi+3], al
                      add edi,4
                    .endif
                    mov HowMany,1
        	  .endif

                  dec edx
                .endw
                ;;



                ;;;;;;;;;;;
                    .if HowMany<=4			; Si la répétition
                    					; est moins que 4x
                                                        ; alors code
                                                        ; de compression
                                                        ; sans importance.

                      mov cx, HowMany
SIM0110:

                      mov [edi],al
                      inc edi
                      dec cx
                      or cx,cx
                      jne SIM0110
                    .else				; Autrement
                    					; ajouter code
                    					; de compression
                                                        ; à la séquence
                      mov byte ptr [edi],0ffh
                      mov [edi+1], al
                      mov al,byte ptr Howmany
                      mov [edi+2], al
                      mov al,byte ptr Howmany+1
                      mov [edi+3], al
                      add edi,4
                    .endif
		;;;;;;;;;



                ; Write size of compressed .IMA to disk
                mov ecx,edi
		sub ecx, _himembase
                mov ImcSize, ecx
                mov edx, offset ImcSize
                mov ecx,4
                call _writefile



                ; Write compressed .ima to disk
                mov edx, _himembase    		; using Screentampon as
                				; buffer for compressed
                                                ; data

                sub edi,edx
                mov ecx,edi
                call _writefile
                jc ErrSaveIma

                call _closefile
                jc ErrSaveIma

                mov bx,1
		jmp XERRSaveIma

ERRSAVEIMATXT	db "Error can't save ima.",13,10,"$"

ErrSaveIma:     mov bx,0
XERRSaveIma:
		ret

;########################################################################
;
; NEW LoadIMAintoBuffer: Great....
;
; The newer LoadIMAin2Buffer to accomodate IMC1 compression. Cheap.
; But terribly ineficient. Zip compressed 2x that much. But IMC1 is
; not too hard to uncompress.
;
;#######################################################################

TImaLen dw 0
TImaHei dw 0

fnametampon	db 64 DUP (0)
FileNameAddr	dd 0

align 4
IMC1SIG		db "IMC1"
FILESIG		db 4 DUP (0)


LoadImaIntoBuffer:
;----------------

		pushall
                mov FilenameAddr , esi

                ; esi is the filename (already loaded)
                mov edi, offset fnametampon
		.while byte ptr [esi]!=0
                   mov al, [esi]
                   mov [edi],al
                   inc edi
                   inc esi
                .endw
                mov byte ptr [edi],0

                ; Opening File on readonly
                mov edx, offset fnametampon
                call _openfile
                jc ErrOpenImaFile


                ; Read the 4st bytes of the .IMA file
                ; into FILESIG

                mov edx, offset FILESIG
                mov ecx, 4
                call _readfile
                jc ErrOpenImaFile

                ; If it is a new .IMA (IMC1 format) then
                ; jump 2 the decompression code.
                mov eax, dword ptr FileSig
                .if eax== dword ptr IMC1Sig

                  jmp LoadIMC1

                .endif

		; This file is an old .IMA
                ; Lseek 2 0 ... na na na >>>!
                mov eax, 0
                mov bl,0
                call _lseekfile

                ; Read ImaHeader into low memory
                mov edx, offset Ima2Bytes	; dest buffer
                mov ecx, 2			; lenght
                call _readfile
                jc ErrOpenImaFile

		mov al, Ima2Bytes
                mov byte ptr TImaLen, al
		mov al, Ima2Bytes +1
                mov byte ptr TImaHei, al

                xor eax,eax
                mov ax, TImaLen
                mul TImaHei             ; eax = Len*hei
                shl eax, 6		; eax = len*hei*64

                mov edx, _himembase
                add edx, 3*256*1024
                mov ecx, eax
                call _readfile
                jc ErrOpenImaFile

CloseLoadIma:
		call _closefile
                jc ErrOpenImaFile

                jmp XErrOpenImaFile

ErrOpenImaFile: mov esi, offset ERROPENFILE
		call LocalErrorHandler
                jmp ErrOpenImaXXX
XErrOpenImaFile:
		call DragImageInFullScreen
ErrOpenImaXXX:
                POPALL
                ret

                ;-------------------------------------------------
		;
		; This code will load a IMC1 file into memory.
		; And, moreover it will uncompressed the dam thing.
		; Great, he said. All I have to hope now is that it
		; doesn't crash. Because if it does then I'll have
                ; to wait for the computer to reboot. If it does
                ; reboot.
                ;
                ; The computer crashed around 12h and only booted back a
                ; 19h.
                ;
                ;---------------------------------------------------


_pressakey	db 13,10,"press a key to continue.",13,10,"$"

align 4
SizeIMC1	dd 0

LoadIMC1:
                ; Read ImaHeader into low memory
                mov edx, offset Ima2Bytes	; dest buffer
                mov ecx, 2			; lenght
                call _readfile
                jc ErrOpenImaFile

		mov al, Ima2Bytes
                mov byte ptr TImaLen, al
		mov al, Ima2Bytes +1
                mov byte ptr TImaHei, al

		; Get size of IMC1
                mov edx, offset SizeImc1
                mov ecx,4
                call _readfile
                jc ErrOpenImaFile

                ;printd SizeImc1
                ;printcr
                ;debugbreak offset _pressakey
                ;jmp CloseLoadIma

                ; Read IMC1 into memory
                mov edx, _himembase
                mov ecx, SizeIMC1
                call _readfile
                jc ErrOpenImaFile

                mov edi, _himembase
                add edi, 3*256*1024
                mov esi, _himembase

                mov edx, 0
                .while edx <= SizeImc1
                   mov al, [esi]
                   .if al==0ffh
		     mov al, [esi+1]
                     mov cl, [esi+2]
                     mov ch, [esi+3]
                     add esi,4

LI0001:
                     mov [edi],al
                     inc edi
                     dec cx
                     or cx,cx
                     jne LI0001

                     add edx,4

                   .else
                     mov [edi],al
                     inc edi
                     inc edx
                     inc esi

                   .endif
                .endw

             	jmp CloseLoadIma

;####################################################################
  module_start ENDP
;####################################################################

 include \masm61\listing\graph.inc

;####################################################################
code32  ends            ; fin du module
	end             ; fin du fichier...
;####################################################################
