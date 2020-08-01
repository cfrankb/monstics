;**********************************************************************
; RUNTIME LIBRAIRY FOR PMODE
;**********************************************************************
; NAME       : 96REPV3.ASM
; DESCRIPTION: Runtime librairy for PMODE programs. Code in this module
;              only works under PMODE.   Code will crash in real mode.
;
;**********************************************************************
;
; CODE WRITTEN           : F.Blanchette
; EXTERNAL DEFS & MACROS : Tran (a.k.a. Thomas Pytel) of Renaissance
;                          (Tran -> author of PMODE)
;
;***********************************************************************
.386p

ss_ecrirecar    MACRO _car_
		invoke _ss_ecrirecar, _car_,0
		ENDM

ecrirecar       MACRO _car_
		invoke _ss_ecrirecar, _car_, 0
		ENDM


ss_printw       MACRO _val_
		invoke _ss_printw, _val_
		ENDM


printw          MACRO _val_
		invoke _ss_printw, _val_
		ENDM




printcr         MACRO
		ecrirecar 13
		ecrirecar 10
		ENDM

printa          MACRO _dword_
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


printd          MACRO _dword_
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



extrn   v86r_eax:dword, v86r_ebx:dword, v86r_ecx:dword, v86r_edx:dword
extrn   v86r_esi:dword, v86r_edi:dword, v86r_ebp:dword
extrn   v86r_ah:byte, v86r_al:byte, v86r_bh:byte, v86r_bl:byte
extrn   v86r_ch:byte, v86r_cl:byte, v86r_dh:byte, v86r_dl:byte
extrn   v86r_ax:word, v86r_bx:word, v86r_cx:word, v86r_dx:word
extrn   v86r_si:word, v86r_di:word, v86r_bp:word
extrn   v86r_ds:word, v86r_es:word, v86r_fs:word, v86r_gs:word
extrn   _selcode:word, _seldata:word, _selzero:word, _lomembase:dword
extrn   _lomemtop:dword, _himembase:dword, _himemtop:dword, _pspa:dword
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
; MY EASY LIFE MACROS
;

@ds2gs macro __offset
   (__offset + CODE32*16)
endm

@gs2ds macro __offset
   (__offset - CODE32*16)
endm

;
; PUBLIC DECLARATIONS
;

;; Bios based routines (INTs)
public _ss_setrangex
public _ss_setrangey
public _ss_initmouse_bs
public _ss_showmouse_bs
public _ss_hidemouse_bs

;; Public variables
public mouse_obj
public mode_info_obj
public vesa_info_obj
public hexcode
public stringW

;#####################################################
;.model flat
code32  segment para public use32
	assume cs:code32, ds:code32, gs:nothing
;#####################################################
;
; TYPES AND STRUCTURES
;

@t_0            TYPEDEF         FAR PTR BYTE
@t_1            TYPEDEF         FAR PTR WORD
@tag_0          STRUCT 2t
VESASignature           BYTE            4t DUP (?)
VESAVersion             WORD            ?
OEMStringPtr            @t_0            ?
Capabilities            WORD            4t DUP (?)
VideoModePtr            @t_1            ?
@tag_0          ENDS

VGAINFOBLOCK            TYPEDEF         @tag_0

@tag_1          STRUCT 2t
ModeAttributes          WORD            ?
WinAAttributes          BYTE            ?
WinBAttributes          BYTE            ?
WinGranularity          WORD            ?
WinSize         WORD            ?
WinASegment             WORD            ?
WinBSegment             WORD            ?
WinFuncPtr              DWORD           ?
BytesPerScanLine                WORD            ?
XResolution             WORD            ?
YResolution             WORD            ?
XCharSize               BYTE            ?
YCharSize               BYTE            ?
NumberOfPlanes          BYTE            ?
BitsPerPixel            BYTE            ?
NumberOfBanks           BYTE            ?
MemoryModel             BYTE            ?
BankSize                BYTE            ?
@tag_1          ENDS

MODEINFOBLOCK           TYPEDEF         @tag_1

@tag_2          STRUCT 2t
boutons         WORD            ?
x               WORD            ?
y               WORD            ?
oldx            WORD            ?
oldy            WORD            ?
mouse           BYTE            16t DUP (16t DUP (?))
temp            BYTE            16t DUP (16t DUP (?))
@tag_2          ENDS

MOUSE           TYPEDEF         @tag_2


;
; SYSTEM DATA
;

mouse_obj     MOUSE <>
	      db 512 DUP(0)
vesa_info_obj VGAINFOBLOCK <>
	      db 512 DUP(0)
mode_info_obj MODEINFOBLOCK <>
	      db 512 DUP(0)

hexcode         db "0123456789ABCDEF"
stringW         db "0","0","0","0","$"


MousePtr     EQU MOUSE PTR         mouse_obj
VesaInfoPtr  EQU VGAINFOBLOCK PTR  vesa_info_obj
ModeInfoPtr  EQU MODEINFOBLOCK PTR mode_info_obj



;-----------------------------------------------------------------
;
; MACRO FACILITIES
; Save a few lines of code
;
; Movx move a source into a destination.
; Movb move a byte into a byte
;

movx            MACRO S_, D_
		push s_
		pop d_
		ENDM

movb            MACRO s_,d_
		push ax
		mov al, s_
		mov d_,al
		pop ax
		ENDM



pushall MACRO
		push eax  ;6
		push ebx  ;5
		push ecx  ;4
		push edx  ;3
		push edi  ;2
		push esi  ;1
		;push ebp
	ENDM

popall MACRO
		;pop ebp
		pop esi ;1
		pop edi ;2
		pop edx ;3
		pop ecx ;4
		pop ebx ;5
		pop eax ;6
	ENDM



;----------------------------------------------------------------
; ss_setvga [mode]
; change le mode video courant.
;
; IN
;   [mode] numéro du mode
;
; OUT
;   rien
;
; NOTE: NE FONCTIONNE QU'AVEC LES MODES VGA.
;
;----------------------------------------------------------------
ss_setvga       MACRO _mode
		invoke _ss_setvga, _mode
		ENDM

_ss_setvga      PROTO NEAR PASCAL  _mode:byte
_ss_setvga      PROC NEAR PASCAL, _mode:byte

		push ax
		mov al,10h              ; int 10h
		mov v86r_ah,0           ; ah = set VGA MODE
		mov ah,_mode
		mov byte ptr v86r_al,ah ; al = mode
		int 33h
		pop ax
		ret

_ss_setvga      ENDP


;----------------------------------------------------------------
; print [offset]
; affiche une chaine specifique finissant par "$" à l'écran.
;
; IN
;
;
; OUT
;   rien
;
;----------------------------------------------------------------
print           MACRO _offset_
		invoke _print, _offset_
		ENDM

_print          PROTO NEAR PASCAL  _offset:dword
_print          PROC NEAR PASCAL, _offset:dword


		push eax
		push ebx
		xor eax,eax
		mov ax, code32
		shl eax,4

		mov ebx, _offset
		add eax,ebx
		mov ebx,eax

		and ebx,15
		shr eax,4

		mov v86r_ds, ax
		mov v86r_dx,bx
		mov v86r_ah,9

;                mov v86r_ds,code32                     ; ds = segment
;                mov v86r_ah,9                          ; ah = fonction 9:
							;      afficher

;                mov eax, _offset
;                mov word ptr v86r_dx, ax               ; dx= offset


		mov al,21h                              ; int 21h
		int 33h

		pop ebx
		pop eax

		ret

_print endp


;
;       Set the mouse x range (min, max)
;

ss_setrangex    MACRO _min, _max
		invoke _ss_setrangey, _min, _max
		ENDM

_ss_setrangex   PROTO NEAR PASCAL  _min: word, _max:word
_ss_setrangex   PROC NEAR PASCAL,  _min: word, _max:word

		push ax
		mov word ptr v86r_ax, 7
		mov byte ptr v86r_al, 7
		mov byte ptr v86r_ah, 0
		mov ax, _min
		mov word ptr v86r_cx, ax
		mov ax, _max
		mov word ptr v86r_dx, ax
		mov al,033h
		int 33h
		pop ax
		ret

_ss_setrangex   ENDP

;-----------------------------------------------------------

;
;       Set the mouse y range (min, max)
;

ss_setrangey    MACRO _min, _max
		invoke _ss_setrangey, _min, _max
		ENDM

_ss_setrangey   PROTO NEAR PASCAL  _min: word, _max:word
_ss_setrangey   PROC NEAR PASCAL,  _min: word, _max:word

		push ax
		mov word ptr v86r_ax, 8
		mov byte ptr v86r_al, 8
		mov byte ptr v86r_ah, 0
		mov ax, _min
		mov word ptr v86r_cx, ax
		mov ax, _max
		mov word ptr v86r_dx, ax
		mov al,033h
		int 33h
		pop ax
		ret

_ss_setrangey   ENDP

;-----------------------------------------------------------

;
;       initialize mouse throught BIOS
;


ss_initmouse_bs MACRO
		invoke _ss_initmouse_bs
		ENDM

_ss_initmouse_bs   PROTO NEAR PASCAL
_ss_initmouse_bs   PROC NEAR PASCAL

		push ax
		mov word ptr v86r_ax, 0
		mov byte ptr v86r_al, 0
		mov byte ptr v86r_ah, 0
		mov al,033h
		int 33h
		pop ax

		ret

_ss_initmouse_bs        ENDP

;-----------------------------------------------------------

;
;       show mouse w/ BIOS
;


ss_showmouse_bs MACRO
		invoke _ss_showmouse_bs
		ENDM

_ss_showmouse_bs   PROTO NEAR PASCAL
_ss_showmouse_bs   PROC NEAR PASCAL

		push ax
		mov word ptr v86r_ax, 1
		mov byte ptr v86r_al, 1
		mov byte ptr v86r_ah, 0
		mov al,033h
		int 33h
		pop ax

		ret

_ss_showmouse_bs        ENDP

;-----------------------------------------------------------

;
;       hide mouse w/ BIOS
;


ss_hidemouse_bs MACRO
		invoke _ss_hidemouse_bs
		ENDM

_ss_hidemouse_bs   PROTO NEAR PASCAL
_ss_hidemouse_bs   PROC NEAR PASCAL

		push ax
		mov word ptr v86r_ax, 2
		mov byte ptr v86r_al, 2
		mov byte ptr v86r_ah, 0
		mov al,033h
		int 33h
		pop ax

		ret

_ss_hidemouse_bs        ENDP


;--------------------------------------------------------------

;
; InitMouse for incorporated VESA support
;

ss_initmouse  MACRO _MOUSE_
	      invoke _ss_initmouse, _mouse
	      ENDM


_ss_initmouse  PROTO NEAR PASCAL          :DWORD
_ss_initmouse  PROC NEAR PASCAL ,  _mouse_:DWORD
		push esi

		mov v86r_ax, 0  ; mov ax, 0
		mov al,33h      ; int 33h
		int 33h

		mov esi, _mouse_

		mov word ptr [esi+offset MOUSE.x], -1
		mov word ptr[esi+offset MOUSE.y], -1
		mov word ptr[esi+offset MOUSE.oldx], -1
		mov word ptr[esi+offset MOUSE.oldy], -1

		pop esi
		ret

_ss_initmouse ENDP

;--------------------------------------------------------------

;
; ReadMouse for incorporated VESA support
;

ss_readmouse  MACRO _MOUSE_
	      invoke _ss_readmouse, _mouse
	      ENDM


_ss_readmouse  PROTO NEAR PASCAL          :DWORD
_ss_readmouse  PROC NEAR PASCAL ,  _mouse_:DWORD

	pushall
	push edi

	mov v86r_ax, 3  ; mov ax, 3
	mov al,33h      ; int 33h
	int 33h

	mov edi, _mouse_
	mov ax, [edi+offset Mouse.x]
	mov [edi+offset Mouse.oldx],ax
	mov ax, [edi+offset Mouse.y]
	mov [edi+offset Mouse.oldy],ax

	mov ax, v86r_cx
	mov [edi+ offset MOUSE.x], ax
	mov ax, v86r_dx
	mov [edi+ offset MOUSE.y], ax
	mov ax, v86r_bx
	mov [edi+ offset MOUSE.boutons], ax

	pop edi
	popall
	ret

_ss_readmouse endp



;------------------------------------------------------------
; ----------------------------------------------------------
; VESA FUNCTIONS -- BIOS SERVICES or DRIVERS BASED SERVICES
; ---------------------------------------------------------
;--------------------------------------------------------------
;
; set vesa mode
;
; AX= Valeur retournee
;


ss_setvesamode MACRO _MODE_
	       invoke _ss_setvesamode, _MODE_
	       ENDM


_ss_setvesamode PROTO NEAR PASCAL          :WORD
_ss_setvesamode PROC NEAR PASCAL ,  _MODE_:WORD

		mov v86r_ah, 4fh
		mov v86r_al,2
		mov ax, _mode_
		mov v86r_bx, ax
		mov al,10h
		int 35h

		mov ax, v86r_ax
		ret
_ss_setvesamode ENDP

;--------------------------------------------------------------

;
; get svga mode
;
; return AX= error code
;        BX= mode

ss_getvesamode MACRO
	       invoke _ss_getvesamode
	       ENDM


_ss_getvesamode PROTO NEAR PASCAL
_ss_getvesamode PROC NEAR PASCAL

		mov v86r_ah, 4fh
		mov v86r_al,3
		;mov v86r_bx,_mode_
		mov al,10h
		int 33h
		mov ax, v86r_ax
		mov bx, v86r_bx
		ret
_ss_getvesamode ENDP

;--------------------------------------------------------------

;
; get information about a VESA mode.
;
; AL = 4fh supported
; AH = 0 Successful / AX=1 ERROR, FAILED ou MERDE
;
; Le programmeur SMART (i.e. intelligent) vérifie si AX=4fh point final.
;
;


ss_getvesamodeinfo MACRO _buffer_, _mode_
	       invoke _ss_getvesamodeinfo, _buffer_, _mode_
	       ENDM

_ss_getvesamodeinfo PROTO NEAR PASCAL :dWORD, :dWORD
_ss_getvesamodeinfo PROC NEAR PASCAL, _buffer_:dword, _mode_:dword

;INT 10 - VESA SuperVGA BIOS - GET SuperVGA MODE INFORMATION
;        AX = 4F01h
;        CX = SuperVGA video mode
;        ES:DI -> 256-byte buffer mode information (see below)
;Return: AL = 4Fh function supported
;        AH = status
;             00h successful
;             01h failed



		mov v86r_es, code32     ; es:di = buffer
		mov eax, _buffer_
		mov v86r_di, ax
		mov eax, _mode_
		mov v86r_cx, ax         ; cx=mode
		mov v86r_al, 1
		mov v86r_ah, 4fh        ; ah = 4f
					; getvesamodeinfo

		mov al, 10h             ; int 10h
		int 33h

		mov ax, v86r_ax
		ret

_ss_getvesamodeinfo ENDP

;--------------------------------------------------------------

;
; get information about VESA compatibility of your video card
;
; AL = 4fh supported
; AH = 0 Successful / AH=1 ERROR, FAILED ou MERDE
;
; Le programmeur SMART (i.e. intelligent) vérifie si AX=4fh point final.
;
;
;INT 10 - VESA SuperVGA BIOS - GET SuperVGA INFORMATION
;        AX = 4F00h
;        ES:DI -> 256-byte buffer for SuperVGA information (see below)
;Return: AL = 4Fh function supported
;        AH = status
;             00h successful
;             01h failed


ss_getvesainfo MACRO _buffer_
	       invoke _ss_getvesainfo, _buffer_
	       ENDM

_ss_getvesainfo PROTO NEAR PASCAL :dWORD
_ss_getvesainfo PROC NEAR PASCAL, _buffer_: dword

		mov v86r_es, code32     ; es:di = buffer
		mov eax, _buffer_
		mov v86r_di, ax
		mov v86r_ax, 4f00h      ; ax = 0x4f00
					; getvesamodeinfo

		mov al, 10h             ; int 10h
		int 33h

		mov ax, v86r_ax
		ret
_ss_getvesainfo ENDP



;--------------------------------------------------------------

;
; setfastwindow to be used with SVGA/VESA compabitible
;     cards
;
; NOTE: I'm not sur if SETFASTWINDOW is fast with an INT call.
;
; no return code
;

ss_setfastwindow MACRO _win_, _pos_, _winptr_
	       invoke _ss_setfastwindow, _win_, _pos_, _winptr_
	       ENDM

_ss_setfastwindow PROTO NEAR PASCAL :BYTE, :WORD, :DWORD
_ss_setfastwindow PROC NEAR PASCAL win:BYTE, pos:WORD, winptr:DWORD
	push es
	pusha

	mov v86r_bh,0           ;mov bh,0
	mov al,win
	mov v86r_bl, al         ;mov bl, win
	mov ax, pos
	mov v86r_dx, ax         ;mov dx, pos

	mov ecx, winptr         ; CX:DX SEG:OFF
	mov dx, cx              ; DX = OFF
	shr ecx,16              ; CX= SEG


	int 32h                 ; call a far real mode proc

	;call winptr
	popa
	pop es
	ret
_ss_setfastwindow ENDP



;--------------------------------------------------------------------

;
; getax: read keyboard
;
; AX = key
;


ss_getax MACRO
	invoke _ss_getax
	ENDM


_ss_getax PROTO NEAR PASCAL
_ss_getax PROC NEAR PASCAL
			push bx
			push dx
			push ds
			mov ax,0
			;mov dx,0x40
			;mov ds,dx
			;mov dx,word ptr ds:[0x1c]
			;mov bx,word ptr ds:[0x1a]

			mov dx, word ptr gs:[41ch]
			mov bx, word ptr gs:[41ah]

			cmp dx,bx
			jz GETOUT
			;mov ax,[bx]
			mov ax,gs:[bx+400h]
			;mov ds:[0x1a],dx
			mov gs:[41ah],dx

GETOUT:
			pop ds
			pop dx
			pop bx
			ret
_ss_getax ENDP

;--------------------------------------------------------------
;
; Ecrire un caractère
; IN
; car = caractère, color = couleur
; OUT
; No return

ss_ecrirecar    MACRO _car_
		invoke _ss_ecrirecar, _car_,0
		ENDM

_ss_ecrirecar PROTO NEAR PASCAL :BYTE, :BYTE
_ss_ecrirecar PROC NEAR PASCAL, _car_:BYTE, _color_:BYTE

		pushall
		push ax
		mov al, _car_
		mov v86r_al, al         ; mov al,Car
		;mov al, _color_
		mov v86r_bl,7           ; mov bl,color
		mov v86r_ah, 0eh        ; mov ah, 0eh
		mov al,10h              ; int 10h
		int 33h
		pop ax
		popall
		ret

_ss_ecrirecar ENDP

;--------------------------------------------------------------
;
; GotoXy
; IN
; X,Y
; OUT
; No return

ss_gotoXY MACRO _x_,_y_
	invoque _ss_gotoxy, _x_,_y_
ENDM

_ss_gotoxy PROTO NEAR PASCAL :BYTE, :BYTE
_ss_gotoxy PROC NEAR PASCAL, _x_:BYTE, _y_:BYTE

		push ax
		mov v86r_bh,0   ; mov bh,0
		mov al, _x_
		mov v86r_dl, al ; mov dl,x
		mov al,_y_
		mov v86r_dh, al ; mov dh,y
		mov v86r_ah,2
		mov al,10h
		int 33h
		pop ax
		ret

_ss_gotoxy ENDP


;-------------------------------------------------------
; ss_blowvideo
;
;    fill VGA/SVGA video memory window w/ a color
;

ss_blowvideo MACRO _color_
	invoke  _ss_blowvideo, _color_
	ENDM

_ss_blowvideo PROTO NEAR PASCAL :DWORD
_ss_blowvideo PROC NEAR PASCAL, _color_:DWORD

		push cx
		push eax
		push esi

		mov eax, _color_
		 mov esi, 0a000h *16
		 mov cx, 65536/4
x:              mov gs:[esi],eax
		 add esi,4
		 loop x

		 pop esi
		 pop eax
		 pop cx
		 ret

_ss_blowvideo ENDP

;-------------------------------------------------------------------------

;------------------------------------------------------------------------
; ss_printw
; IN _val_ is WORD
; OUT rien


ss_printw       MACRO _val_
		invoke _ss_printw, _val_
		ENDM

_ss_printw      PROTO NEAR PASCAL _val_:WORD
_ss_printw      PROC NEAR PASCAL, _val_:WORD
		pushall
		mov edi, offset stringW+3
		mov dx, _val_

		mov cx,4
putdigit:       mov bx, dx
		and ebx,15
		mov al, byte ptr [offset hexcode+ebx]
		mov byte ptr [edi],al

		dec edi
		shr dx,4
		loop putdigit

		invoke _print, offset stringW
		popall
		ret


_ss_printw      ENDP



;-------------------------------------------------------------------
;
; Écrire une chaine finissant par zéro
;  IN Offset
;

printc MACRO _offset_
		invoke _ss_printc, _offset_
	  ENDM


ss_printc MACRO _offset_
		invoke _ss_printc, _offset_
	  ENDM

_ss_printc PROTO NEAR PASCAL :DWORD
_ss_printc PROC NEAR PASCAL, _offset_:DWORD

	   push esi
	   push ax

	   mov esi, _offset_
	   mov al, [esi]
	   .while al!=0 && al!="$"
		ss_ecrirecar <al>
		inc esi
		mov al, [esi]
	   .endw

	   pop ax
	   pop esi
	   ret

_ss_printc ENDP


;--------------------------------------------------------------------
;
; Printb        Ecrit un byte
;


_ss_printb      PROTO NEAR PASCAL _val_:WORD
_ss_printb      PROC NEAR PASCAL, _val_:WORD
		pusha
		mov edi, offset stringW+3
		mov dx, _val_

		mov cx,2
putdigit:       mov bx, dx
		and ebx,15
		mov al, byte ptr [offset hexcode+ebx]
		mov byte ptr [edi],al

		dec edi
		shr dx,4
		loop putdigit

		;invoke _print, offset stringW
		printc offset stringW+2
		popa
		ret


_ss_printb      ENDP

;---------------------------------------------------------------------
;
; ss_drawmouse _MOUSE_, _MODEINFOBLOCK_
;
; draw the mouse on SVGA/VESA screen without the BIOS
;

     ss_drawmouse MACRO _MOUSE_, _MODEINFOBLOCK_
	invoke _ss_drawmouse, _MOUSE_, _MODEINFOBLOCK_
	ENDM

_ss_drawmouse PROTO NEAR PASCAL _MOUSE_:DWORD, _ModeInfoBlock_:DWORD
_ss_drawmouse PROC NEAR PASCAL, _MOUSE_:DWORD, _ModeInfoBlock_:DWORD
local           BaseX: WORD
local           Res: WORD
		pushall

		mov ebx,  offset Mode_Info_Obj
		mov esi,  offset Mouse_obj
		mov cx, [esi+offset MOUSE.Y]

		xor eax,eax
		xor edx,edx
		mov dx, [ebx+offset MODEINFOBLOCK.xResolution]
		mov word ptr Res,dx

		.if cx!=0
DM1:            add eax, edx
		loop DM1
		.endif

		mov dx, [esi+offset MOUSE.X]
		mov word ptr BaseX, dx
		add eax,edx

		; eax = AbsMousePos
		; esi = _MOUSE_
		; ebx = _MODEINFOBLOCK_

		xor ecx,ecx
		mov cx, [ebx+offset MODEINFOBLOCK.WinGranularity]
		shl ecx, 10

		mov edx,0
		.while eax > ecx
		    sub eax,ecx
		    inc edx
		.endw

		; eax = offset from windows
		; edx = window pos in granulity units

;                mov ecx, [ebx+offset MODEINFOBLOCK.WinFuncPtr]
		; ecx = WinFuncPtr

		;s_setfastwindow 0, <dx>, <ecx>
		ss_setfastwindow 0, <dx>, mode_info_obj.WinFuncPtr
		;ss_setfastwindow 0, 0, mode_info_obj.WinFuncPtr

		add eax, 0a000h * 10h
		mov ebx,eax
		;mov ebx, 0a0000h

	      ; popall
	      ; ret

		mov edx, esi
		add edx, offset MOUSE.temp
		add esi, offset MOUSE.mouse




		mov cl, 16
x2:             mov ch, 16

		mov di,word ptr BaseX

x:
		mov al, gs:[ebx]
		  mov [edx], al
		  mov al,[esi]
		  .if (al!=0) && (di < Res)
		  mov gs:[ebx],al
		  .endif

		inc ebx
		inc esi
		inc edx
		inc di

		dec ch
		cmp ch,0
		jne x

		xor eax,eax
		mov ax, mode_info_obj.XResolution
		add ebx, eax
		sub ebx,16

		dec cl
		cmp cl,0
		jne x2

		mov ax, mouse_obj.x
		mov mouse_obj.oldx, ax

		mov ax, mouse_obj.y
		mov mouse_obj.oldy, ax
		popall

		ret
_ss_drawmouse ENDP

;---------------------------------------------------------------------
;
; ss_undrawmouse _MOUSE_, _MODEINFOBLOCK_
;
; undraw the mouse from SVGA/VESA screen without the BIOS
;

     ss_undrawmouse MACRO _MOUSE_, _MODEINFOBLOCK_
	invoke _ss_undrawmouse, _MOUSE_, _MODEINFOBLOCK_
	ENDM

_ss_undrawmouse PROTO NEAR PASCAL _MOUSE_:DWORD, _ModeInfoBlock_:DWORD
_ss_undrawmouse PROC NEAR PASCAL, _MOUSE_:DWORD, _ModeInfoBlock_:DWORD

		pushall

		mov ebx,  offset Mode_Info_Obj
		mov esi,  offset Mouse_obj
		mov cx, [esi+offset MOUSE.oldY]

		xor eax,eax
		xor edx,edx
		mov dx, [ebx+offset MODEINFOBLOCK.xResolution]

		.if cx!=0
DM1:            add eax, edx
		loop DM1
		.endif

		mov dx, [esi+offset MOUSE.oldX]
		add eax,edx

		; eax = AbsMousePos
		; esi = _MOUSE_
		; ebx = _MODEINFOBLOCK_

		xor ecx,ecx
		mov cx, [ebx+offset MODEINFOBLOCK.WinGranularity]
		shl ecx, 10

		mov edx,0
		.while eax > ecx
		    sub eax,ecx
		    inc edx
		.endw

		; eax = offset from windows
		; edx = window pos in granulity units

;                mov ecx, [ebx+offset MODEINFOBLOCK.WinFuncPtr]
		; ecx = WinFuncPtr

		;s_setfastwindow 0, <dx>, <ecx>
		ss_setfastwindow 0, <dx>, mode_info_obj.WinFuncPtr
		;ss_setfastwindow 0, 0, mode_info_obj.WinFuncPtr

		add eax, 0a000h * 10h
		mov ebx,eax
		;mov ebx, 0a0000h


	      ; popall
	      ; ret

		mov edx, esi
		add edx, offset MOUSE.temp
		add esi, offset MOUSE.mouse

		mov cl, 16
x2:             mov ch, 16
x:
		;mov al, gs:[ebx]
		;  mov [edx], al
		;  mov al,[esi]
		;  mov gs:[ebx],al

		mov al, [edx]
		mov gs:[ebx],al

		inc ebx
		inc esi
		inc edx

		dec ch
		cmp ch,0
		jne x

		xor eax,eax
		mov ax, mode_info_obj.XResolution
		add ebx, eax
		sub ebx,16

		dec cl
		cmp cl,0
		jne x2

		popall

		ret
_ss_undrawmouse ENDP

;------------------------------------------------------------------------
;
; ss_findvesamode _xres, _yres, _colors
;
; Trouve le 1er mode VESA qui correspond à la demande.
; IN _xres, _yres, _colors
;
; NOTE: _colors est le nbr de bits/pixel (bpp)
; exemple: 4 bits = 16 couleurs
;          8 bits = 256 couleurs (limite de ma carte vidéo 8bpp)
;          16 bits= 32K couleurs
;          24 bits= 16M couleurs
;
; aucune validation des données d'entrée (comme toutes les autres fonctions
; que j'ai écrit)
;
; OUT ax=mode
;     ax=-1 si aucun
;     ax=-2 aucun support VESA detecte
;
;

ss_findvesamode MACRO _xres, _yres, _bpp
	invoke _ss_findvesamode, _xres, _yres, _bpp
ENDM

_ss_findvesamode PROTO NEAR PASCAL :WORD, :WORD, :BYTE
_ss_findvesamode PROC NEAR PASCAL, _xres:WORD, _yres:WORD, _bpp:BYTE

	push bx
	push cx
	push di
	push si

	;; Get informations about your SVGA/VESA adapter.
	   ss_getvesainfo offset vesa_info_obj ; Get info
	   .if v86r_ax!=4fh                    ; about your VESA
	    mov ax,-2
	    jmp _bye
	   .endif

	;; Get information from the VESA modes list


	mov ebx, offset vesa_info_obj
	printa ebx
	printcr
	add ebx, offset VGAINFOBLOCK.VideoModePtr

	mov ax, [ebx+2]
	shl eax,16
	mov ax, [ebx]
	printa ebx
	printcr
	printa eax
	printcr
	xor ebx,ebx
	mov bx, ax
	shr eax,16
	shl eax,4
	add ebx,eax

	mov ax, gs:[ebx]        ; obtient le 1er mode vesa
	.while ax!=-1           ; est-ce fin de liste?

	    ;; Get informations about video mode 0x101
	       ss_getvesamodeinfo (offset mode_info_obj) , ax
	       .if v86r_ax!=4fh                           ; Get information
		mov ax,-2
		jmp _bye
	       .endif

	       mov si, mode_info_obj.XResolution
	       mov di, mode_info_obj.YResolution
	       mov cl, mode_info_obj.BitsPerPixel

	       .if (si==_xres) && (di==_yres) && (cl==_bpp)
		  jmp trouve
	       .endif

	      add ebx,2
	      mov ax, gs:[ebx]

	.endw

trouve:
_bye:
	pop si
	pop di
	pop cx
	pop bx

	ret
_ss_findvesamode ENDP

;--------------------------------------------------------------------------
;
;ss_copymem _dest_, _source_ (32bits offset of 0)
;
; Ever used a C compiler? If you don't understand, leave and find
; yourself another carer. Yannick Bertrand just left TECH INFO
; for literrature. Fallow his example.
;
ss_copymem MACRO _dest_, _source_, _len_
	_ss_copymem _dest_, _source_ , _len_
ENDM

_ss_copymem PROTO NEAR pASCAL :DWORD, :DWORD, :DWORD
_ss_copymem PROC NEAR pASCAL, _dest_ :DWORD, _source_:DWORD, _len_:DWORD

	pushall

	mov ecx, _len_
	mov edx, ecx
	and edx, 3
	mov eax, esi
	and eax, 3
	mov ebx,edi
	and ebx, 3

	.if edx==0 && eax==0 && ebx==0
	    ;; You are a smart boy, even offset are good...
	    ;; even target size is good.
	    ;; Keep up the good work. - Victor
	    mov ebx,0
	    shr ecx, 2
C32:        mov eax, gs:[esi+ebx]
	    mov gs:[edi+ebx],eax
	    add ebx,4
	    dec ecx
	    or ecx,ecx
	    jne C32
	.else
	    ;; You are a foul. You expect your code to be fast on a
	    ;; none align data. Align your data or write customized
	    ;; copy routines.
	    mov esi, _source_
	    mov edi, _dest_
	    mov ebx,0
C8:         mov al, gs:[esi+ebx]
	    mov gs:[edi+ebx],al
	    ;add ebx,4
	    inc ebx
	    dec ecx
	    or ecx,ecx
	    jne C8
	.endif

	popall
	ret

_ss_copymem ENDP


;°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
; Open file
; In:
;   EDX -> ASCIIZ filename
; Out:
;   CF=1 - Error opening file
;   CF=0 - File opened succesfully
;     V86R_BX - file handle
;
; Tran provided OpenFile, but I had rather use my own. But it still uses
; the same arguments as the procedure provided by Tran.
;
; mov ax,3d02
; function 3dh -> is open file
;           2  -> read/write mode
;
; Tran? Do you know that opening a read-only file in read/write mode causes
; anoying errors? I bet you did, but you didn't care.
;
; INT 21 FUNCTION 3D Ouverture d'un fichier
; DS:DX pointe le nom du fichier,AL contient:
; 0 Ouverture en lecteur seul
; 1 Ouverture en écriture seulement
; 2 Ouverture en lecture et écriture
; Dans le cas d'une erreur, CF est posé et dans le cas contraire AX contient le numéro d'entré du fichier.
;
;°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°

_openfile PROTO NEAR PASCAL

_openfile PROC NEAR PASCAL

		push eax
		push edx
		add edx, _code32a
		mov eax,edx
		and dx,15
		shr eax, 4
		mov v86r_dx, dx
		mov v86r_ds, ax
		mov al,21h
		mov v86r_ah,3dh
		mov v86r_al,0           ; opening as read-only
		int 33h
		mov ax, v86r_ax
		mov v86r_bx,ax
		pop edx
		pop eax
		ret
_openfile ENDP


code32 ends
end






