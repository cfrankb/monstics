; ****************************************************************
;
; 	Assembly modules runtime librairy: 95SSV20C.ASM
;
; 		Copyright 1995 FRANCOIS BLANCHETTE
;
; ****************************************************************

include \masm61\listing\ssfsm95.inc

.model large, c

EXTERNDEF DrawScript: PROC
EXTERNDEF ss_maplevel:PROC
EXTERNDEF ss_copyseg: PROC
EXTERNDEF ss_drawima: PROC
EXTERNDEF ss_fillseg: PROC
EXTERNDEF ss_eraseseg: PROC
EXTERNDEF ss_drawsomescreen:PROC
EXTERNDEF ss_erasescreen:PROC

STATV2_TEXT SEGMENT 'CODE' PUBLIC
.386

ScrTask			EQU		0
ScrClass		EQU		1
ScrU1			EQU		2
ScrU2			EQU		3
ScrIma			EQU		4
ScrX			EQU		6
ScrY			EQU		7
ImaPtr			EQU		0
ImaLen			EQU		2
ImaHei			EQU		4
StoTask			EQU		0
StoClass		EQU		1
StoIma			EQU		2
size_ImsTable		EQU		32768t
size_Font		EQU		65535t
size_ImaNames		EQU		8192t
size_ScrTable		EQU		32768t
size_FowTable		EQU		2048t
class_antigravity	EQU		0000000d0h
class_obstacle		EQU		0000000e0h

db "STATICS SYSTEM V2.0 FOR C COMPILERS (C) 1995 FRANCOIS BLANCHETTE.",0

;-------------------------------------------------------------------
@proto_0		TYPEDEF		PROTO FAR C ScrTable:FAR PTR BYTE, ImsTable:FAR PTR BYTE, Font:PTR FAR PTR BYTE, mx:word, my:word, screen:SWORD, :word, hei:word, bckcolor:WORD, ScrSize:WORD
DrawScript		PROTO		@proto_0

@proto_1		TYPEDEF		PROTO FAR C :FAR PTR BYTE, :FAR PTR BYTE, :FAR PTR BYTE, :WORD
ss_maplevel		PROTO		@proto_1

@proto_2		TYPEDEF		PROTO FAR C :WORD, :WORD
ss_copyseg		PROTO		@proto_2

;-------------------------------------------------------------------
; The procedure ERASESCREEN was originally used in the STATLB.ASM module
; that service the STATICS V1 system. But, I choose to include it here
; so it could service the new programs as well.

align 2
ERASESEQ	dw 0,1,6,2,5,3,7,4

ss_erasescreen PROC FAR C

		pushall

		mov dx,0a000h
		mov gs,dx
		mov al,0
		mov si,0
		mov bx,0

		mov dx,2
MANIACLAPX_:	mov cx,65536

DODRAWSCREEN_:  mov di,si
		add di,cs:[bx+offset ERASESEQ]
		inc bx
		inc bx
		cmp bx,10 +4
		jne XNULBXAT_
		mov bx,0
XNULBXAT_:

		mov al,0
		mov gs:[di],al
		add si,5+7

		push cx
		mov cx,64/4
WAITFORCORRINE_:loop WAITFORCORRINE_
		pop cx
		loop DODRAWSCREEN_

		mov cx,dx
		dec dx
		loop MANIACLAPX_

                popall
		ret
ss_erasescreen ENDP

		;-----------------------

;-------------------------------------------------------------------
; The procedure DRAWSOMESCREEN was originally used in the STATLB.ASM module
; that service the STATICS V1 system. But, I choose to include it here
; so it could service the new programs as well.

ss_drawsomescreen PROC FAR C, SSEG:WORD

                pushall

		mov dx,0a000h
		mov gs,dx
		mov dx,SSEG
		mov es,dx
		mov al,0
		mov si,0
		mov bx,0


		mov dx,2
MANIACLAPX:	mov cx,65536

DODRAWSCREEN:  	mov di,si
		add di,cs:[bx+offset ERASESEQ]
		inc bx
		inc bx
		cmp bx,10 +4
		jne XNULBXAT
		mov bx,0
XNULBXAT:

		mov al,es:[di]
		mov gs:[di],al
		add si,5+7

		push cx
		mov cx,64/4
WAITFORCORRINE: loop WAITFORCORRINE
		pop cx
		loop DODRAWSCREEN

		mov cx,dx
		dec dx
		loop MANIACLAPX
                popall
		ret

ss_drawsomescreen ENDP


;-------------------------------------------------------------------
ss_fillseg PROC FAR C, DSEG:WORD, COLOR:WORD
                pushall
		set es, DSEG
                mov ax, Color
                shl eax,16
                mov ax, Color
                mov cx, 65536 /4
                xor di,di
X0001:          mov es:[di],eax
                add di,4
                loop X0001
		popall
                ret
ss_fillseg ENDP

;-------------------------------------------------------------------
ss_eraseseg PROC FAR C, DSEG:WORD
                pushall
		set es, DSEG
                xor eax,eax
                mov cx, 65536 /4
                xor di,di
X0001:          mov es:[di],eax
                add di,4
                loop X0001
		popall
		ret
ss_eraseseg ENDP

;-------------------------------------------------------------------
ss_drawima PROC  FAR C, ImsTable:FAR PTR BYTE, Font:PTR FAR PTR BYTE, ImaNo:WORD, Screen:WORD, X_:WORD, Y_:WORD, Transparence: WORD
Local		Len: WORD
Local		Hei: WORD
Local 	        x: WORD
Local		y: WORD
		pushall


                set gs,Screen
                mov di, X_
                shl di, 3
                mov ax, Y_
                mov ah,0ah
                mul ah
                shl ax,8
                add di,ax

                les bx, ImsTable
		mov cx, ImaNo
                jcxz ImaZ

                mov dx,bx
NxIma:		mov bx, es:[bx]
                add bx,dx
                loop NxIma
ImaZ:

                movw Len, es:[bx+ImaLen]
                movw Hei, es:[bx+ImaHei]
                add bx,6

		movw y, Hei
X011:           movw x, Len
		push di
X010:
	        lfs si, Font
                mov ax, es:[bx]
                shr ax, 10		; FONT / 1024
                shl ax, 2		; FONT * 4
                add si,ax
                lfs si, dword ptr fs:[si]

                mov ax, es:[bx]
                and ax,1023
                shl ax, 6		; FONT * 64
		add si,ax

                push di

                .if Transparence == -1
                mov dx,8
X0002:          mov cx,8
X0001:          mov al,fs:[si]
                or al,al
                je PixZ
                mov gs:[di],al
PixZ:           inc si
                inc di
                loop X0001

                add di,140h-8
                mov cx,dx
                dec dx
                loop X0002

                .else
                     .if Transparence == 0
                     	mov cx,8
X0003:                  mov eax, fs:[si]
                        mov gs:[di],eax
                        mov eax, fs:[si+4]
                        mov gs:[di+4],eax
                        add di,140h
                        add si,8
                        loop X0003

                     .else

                     	mov dx, 8
X0005:                  mov cx, 4
X0004:                  mov ax, fs:[si]
                        .if al==0
                            movb gs:[di], byte ptr Transparence
                        .else
                            mov gs:[di],al
                        .endif

                        .if ah==0
                            movb gs:[di+1],byte ptr Transparence+1
                        .else
                             mov gs:[di+1],ah
                        .endif

                        add di,2
                        add si,2
                        loop X0004
                        add di,140h-8
                        mov cx,dx
                        dec dx
                        loop X0005

                     .endif
                .endif

                pop di
                add di,8
		add bx,2
                mov cx,x
                dec x
                eloop X010

                pop di
                add di,0a00h
                mov cx,y
                dec y
                eloop X011

		popall
		ret
ss_drawima ENDP

;-------------------------------------------------------------------
ss_copyseg PROC FAR C, dseg:WORD, sseg:WORD
		pushall
		set ds,sseg
		set es,dseg
		mov cx, 65536/4
		xor si,si
X0001:		mov eax, [si]
		mov es:[si],eax
		add si,4
		loop X0001
		popall
		ret
ss_copyseg ENDP

;-------------------------------------------------------------------
ss_maplevel PROC FAR C, Map:FAR PTR BYTE, ScrTable:FAR PTR BYTE, ImsTable:FAR PTR BYTE, ScrSize:WORD
Local		ObjClass:  BYTE
Local		Len 	: WORD
Local 		Hei	: WORD
		pushall

     		 lds di, Map
		 mov cx,32768/4
                 xor eax,eax
X0001:           mov [di],eax
                 add di,4
                 loop X0001

                 lds si, ScrTable

                 .while byte ptr [si+ScrTask]!=-1 && ScrSize !=0

                      movb ObjClass, [si+ScrClass]

                      lgs di, Map
                      mov al,[si+ScrX]
                      mov ah,[si+ScrY]
                      add di,ax

                 mov cx, [si+ScrIma]

                 les bx, ImsTable

                 mov dx, bx		; compensateur pour addr non fixe
                 .while cx!=0
                 	dec cx
                        mov bx, es:[bx]
                        add bx,dx
		 .endw

		movw Hei, es:[bx+ImaHei]
                movw Len, es:[bx+ImaLen]

                mov dx, Hei
X0003:          mov cx, Len
X0002:
                mov al, ObjClass
                .if al> gs:[di]
                	mov gs:[di],al
                .endif

                inc di
                loop X0002

                sub di, Len
                add di,256
                mov cx,dx
                dec dx
                loop X0003

                add si,8
                sub ScrSize,8

                .endw

                popall
                ret

ss_maplevel	ENDP
;-------------------------------------------------------------------

DrawScript PROC FAR C, ScrTable:FAR PTR BYTE, ImsTable:FAR PTR BYTE, Font:PTR FAR PTR BYTE, mx:word, my:word, screen:SWORD, len:word, hei:word, bckcolor:WORD, ScrSize:WORD
Local		PixLen: WORD
Local		PixHei: WORD
Local 		PixX: word
Local		PixY: word
Local		LPix: word
Local		HPix: word

		pushall
		set gs,Screen
		mov ax, BckColor
                .if ax!=-1
	                shl eax,16
	                mov ax,BckColor
			mov cx,65536/4
			xor di,di
_X:
			mov gs:[di],eax
        	        add di,4
			loop _X
        	.endif

		lds si,ScrTable

		.while (byte ptr [si+ScrTask]!=-1) && (ScrSize !=0)

                    sub ScrSize,8
	  	    mov cx, [si + ScrIma]

                	mov PixX,0
                	mov PixY,0

                    movb byte ptr PixX, byte ptr [si+ScrX]
                    movb byte ptr PixY, byte ptr [si+ScrY]

		    push ds
		    push si

   		    les si, ImsTable
		    jcxz _ImaZ

		    mov dx,si			; Compensateur
NxIma:
		    mov si, es:[si+ImaPtr]
                    add si,dx
                    loop NxIma
_ImaZ:

		    set PixHei, es:[si+ImaHei]
		    set PixLen, es:[si+ImaLen]

                    mov cx,mx

                    ; OX + OL > MX
		    mov ax, PixX
                    add ax, PixLen
                    cmp ax, cx
                    jbe NotOnScreen

                    ; OX < MX + SL
                    sub ax, PixLen
		    add cx, Len
                    cmp ax, cx
                    jae NotOnScreen

                    mov cx,my

                    ; OY + OH > MY
                    mov ax, PixY
                    add ax, PixHei
                    cmp ax,cx
                    jbe NotOnScreen

                    ; OY < MY + SH
                    sub ax, PixHei
                    add cx, Hei
                    cmp ax,cx
                    jae NotOnScreen

                    ; Get relative position for
                    ; PixX & PixY
                    mov ax, PixX
                    sub ax, mx
                    mov PixX,ax

                    mov ax, PixY
                    sub ax, my
                    mov PixY,ax

		    add si,6

                    set LPix, PixLen
                    set HPix, PixHei

L4:
                     mov ax, PixY
                    .if ax < Hei
L3:
                         mov ax, PixX
                    	.if ax < Len

	                    mov ax, es:[si]
	                    lds bx, Font                ; Ptr FONT[0]
	                    shr ax, 10  		;
                            shl ax, 2
			    add bx,ax                   ; Ptr FONT[x]

	                    lds bx, dword ptr ds:[bx]	; Ptr *FONT[x]

	                    mov ax, es:[si]		; An FNT block
	                    and ax,1023
	                    shl ax,6
	                    add bx,ax			; Ptr *FONT[x]+64*Fnt&1023

			    mov ax, PixY
	                    mov ah, 0ah
	                    mul ah
	                    shl ax,8

	                    mov di, PixX
	                    shl di,3
	                    add di,ax



			;********************************

         		    mov cx,8
L1:
			   ;======LOWER AX======
                            mov eax, [bx]
                            mov edx, [bx+4]

                            or eax,eax
                            je DX_

                            or ax,ax
                            je SHR_AX
			    or al,al
                            je _AH
                            or ah,ah
                            je _AL

                            mov gs:[di],ax
                            jmp SHR_AX

_AL:                        mov gs:[di],al
			    jmp SHR_AX

_AH:                        or ah,ah
                            je SHR_AX
			    mov gs:[di+1],ah

                            ;==== UPPER AX =====
SHR_AX:			    shr eax,16

                            or ax,ax
                            je DX_
			    or al,al
                            je _AH2
                            or ah,ah
                            je _AL2

                            mov gs:[di+2],ax
                            jmp DX_

_AL2:                       mov gs:[di+2],al
			    jmp DX_

_AH2:                       or ah,ah
                            je DX_
			    mov gs:[di+3],ah

			    ;==== LOWER DX =====
DX_:
                            or edx,edx
                            je PixZ

			    or dx,dx
                            je SHR_DX
			    or dl,dl
                            je _DH
                            or dh,dh
                            je _DL

                            mov gs:[di+4],dx
                            jmp SHR_DX

_DL:                        mov gs:[di+4],dl
			    jmp SHR_DX

_DH:                        or dh,dh
                            je SHR_DX
			    mov gs:[di+5],dh

			    ;======== UPPER DX =======

SHR_DX:                     shr edx,16
                            or dx,dx
                            je PixZ
			    or dl,dl
                            je _DH2
                            or dh,dh
                            je _DL2

                            mov gs:[di+6],dx
                            jmp PixZ

_DL2:                       mov gs:[di+6],dl
			    jmp PixZ

_DH2:                       or dh,dh
                            je PixZ
			    mov gs:[di+7],dh

PixZ:			    add bx,8
			    add di,140h
	                    eloop L1


			;********************************


                    	.endif

			    inc si
                            inc si
                            inc PixX
                            dec LPix
                            cmp LPix,0
                            jne L3

                .else
                	add si, PixLen
                	add si, PixLen
                        addw PixX, PixLen

		.endif
                            mov ax, PixX
                            sub ax, PixLen
                            mov PixX,ax
                            inc PixY
                            set LPix, PixLen
                            dec HPix
                            cmp HPix,0
                            jne L4

NotOnScreen:	    pop si
		    pop ds
                    add si,8
		.endw
		popall
		ret
DrawScript ENDP

;-------------------------------------------------------------------

STATV2_TEXT     ENDS

; ****************************************************************
;
; 	Assembly modules runtime librairy: 95COLORC.ASM
;
; 		Copyright 1995 FRANCOIS BLANCHETTE
;
; ****************************************************************

EXTERNDEF ss_fillregisters: PROC
EXTERNDEF ss_getregisters: PROC
EXTERNDEF ss_setcolor: PROC

COLOR_TEXT SEGMENT 'CODE' PUBLIC
.386
;----------------------------------------------------
ss_fillregisters PROC FAR C, C_Registers:FAR PTR

	        pushall
		mov ah,10h
	        mov al,12h
	        mov bx,0
	        mov cx,256
		lds dx, C_Registers
		int 10h
	        popall
	        ret
ss_fillregisters ENDP

;------------------------------------------------------------------------

ss_getregisters PROC FAR C, C_Registers: FAR PTR
	        pushall
		mov ah,10h
	        mov al,17h
	        mov bx,0
	        mov cx,256
                les dx, C_Registers
		int 10h
	        popall
        	ret
ss_getregisters ENDP

;-------------------------------------------------------------------------
ss_setcolor	PROC FAR C, ColorReg:WORD, Red:BYTE, Green:BYTE, Blue:BYTE
		pushall
                mov ah,10h
                mov al,10h
                mov bx,ColorReg
                mov ch,Green
                mov cl,Blue
                mov dh,Red
                int 10h
                popall
                ret
ss_setcolor       ENDP

;-----------------------------------------------------
COLOR_TEXT ENDS
END