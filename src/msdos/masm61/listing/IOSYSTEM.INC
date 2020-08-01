
; * * * * * * * * * * * * * * * * * *
; I/O SYSTEM V1.0
; (C) 1994-95 FRANCOIS BLANCHETTE
; * * * * * * * * * * * * * * * * * *

;-------------------------------------------------------------------------

JcError MACRO
Local	NoError

	jnc NoError
	SetSeg <DS>, DATA
        mov bx, offset ErrorHandler
        jmp word ptr [bx]
NoError:
        ENDM

;------------------------------------------------------------------------

HCreat MACRO Name, IdCode
Local	Ok
	pushall

        SetSeg <DS>,DATA
        mov dx, Name
        mov ah, 3ch
        mov cx, 0
        int 21h
        jnc Ok
        popall
        jcError

Ok:
        SetSeg <DS>,DATA
        mov IdCode, ax

        popall

        ENDM

;------------------------------------------------------------------------

HOpenForRead MACRO Name, IdCode
Local	Ok

	pushall

        SetSeg <DS>, DATA
        mov dx, Name
        mov ah, 3dh
        mov al,0
	int 21h
        jnc Ok
        popall
        jcError


Ok:
        SetSeg <DS>,DATA
        mov IdCode, ax
        popall

        ENDM

;-----------------------------------------------------------------------

HSetHandler MACRO Handler
	push ds
	SetSeg <DS>, DATA
        mov word ptr ErrorHandler, Handler
        pop ds

        ENDM

;-----------------------------------------------------------------------

HClose	MACRO IdCode
Local	Ok

	pushall

        SetSeg <DS>,DATA
	mov ah, 3eh
        mov bx, IdCode
        int 21h
        jnc Ok
   	popall
        jcError
Ok:
        popall

        ENDM

;-----------------------------------------------------------------------

HWrite MACRO SSEG, SI_, CX_, IdCode
Local	Ok

	pushall

        SetSeg <DS>,DATA
        mov bx,IdCode
	mov ah,40h
        mov dx, SI_
        mov cx, CX_
        SetSeg <DS>, SSEG
        int 21h
        jnc Ok
        popall
        jcError
Ok:
        popall

        ENDM

;------------------------------------------------------------------------

HReadFile MACRO DSEG, DI_, CX_, IdCode
Local	Ok

	pushall

        SetSeg <DS>,DATA
        mov bx,IdCode
        mov ah,3fh
        mov dx, DI_
        mov cx, CX_
        SetSeg <DS>, DSEG
        int 21h
        jnc Ok
        popall
        jcError
Ok:
        popall

        ENDM

;-----------------------------------------------------------------------

HLoadIms 	MACRO Name
Local		DoItAgain, LastSeg, LoadData

		pushall

                SetSeg <DS>,DATA
                push FileId

                ;EraseMem LIBRAIRY, offset ImsDefs, 32768
                ;EraseMem LIBRAIRY, offset ImsNames, 8192

                sub sp,12
                mov bp,sp
                add bp,2

		HOpenForRead Name, FileId
                HReadFile STACK, <bp>, 4, FileId

                sub word ptr [bp+2],4
                HReadFile LIBRAIRY, offset ImsDefs, word ptr [bp+2], FileId

                mov cx,word ptr [bp]
                mov dx, FONT

DoItAgain:      cmp cx,1024
                jb LastSeg

                mov ax,65535
                sub cx,1024
                jmp LoadData

LastSeg:	mov ax,cx
		shl ax,6
                mov cx,0

LoadData:       mov word ptr [bp+4], dx
                mov word ptr [bp+6], ax

                add dx,65536/16

                HReadFile word ptr [bp+4],0, word ptr [bp+6], FileId

                cmp cx,0
                jne DoItAgain

                HReadFile STACK, <bp>, 2, FileId
                HReadFile LIBRAIRY, offset ImsNames, word ptr [bp], FileId

                HClose FileId

                add sp,12

                pop FileId
                popall

		ENDM

;-------------------------------------------------------------------------
HLoadNew 	Macro Filename, DSEG, DI_, CX_

		pushall
                setseg <DS>,DATA
                mov dx,Filename
                setseg <ES>,DSEG
                mov bx,DI_
                mov cx,CX_
		call LoadNew
                popall

                ENDM

;-------------------------------------------------------------------------

HLoadOld 	Macro Filename, DSEG, DI_, CX_

		pushall
                setseg <DS>,DATA
                mov dx,Filename
                setseg <ES>,DSEG
                mov bx,DI_
                mov cx,CX_
		call LoadOld
                popall

                ENDM


;------------------------------------------------------------------------


