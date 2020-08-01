;----------------------------------------------------------------
;       Pipes Linker for Tubeler
;       by Francois Blanchette
;----------------------------------------------------------------

; NOTE: USE 94REP.ASM

PUBLIC CONVENSIONS
PUBLIC PATH

EXTERN CLS:PROC
EXTERN VIDEOSWITCH:PROC
EXTERN LOADOLD:PROC
EXTERN LOADNEW:PROC
EXTERN GETAX:PROC
EXTERN MAKEPATH:PROC
EXTERN QUIT:PROC
EXTERN NOT_FOUND:PROC
EXTERN MELO_PAINT:PROC

EXTERN FILENAME:WORD
EXTERN OLD_VIDEO_MODE:WORD
EXTERN EXT:PROC

;----------------------------------------------------------------
ASSUME CS:CODE,DS:DATA,SS:STACK
STACK     SEGMENT STACK
	  DB 400H DUP  (0)
STACK     ENDS
;----------------------------------------------------------------

;----------------------------------------------------------------
DATA      SEGMENT PUBLIC 'DATA'
COPYRIGHT      db "PIPES LINKER (C) 1994: FRANCOIS BLANCHETTE"
PATH           db 0
GIVENAME       db "Requiered .MXK file on command line.$"
PSP 	       db 256 DUP (0)
MXKBUFF	       db 1024 DUP (0)
MXKEXTENSION   db ".mxk",0
Tubeler	       db 32768 DUP (0)
_TBL	       db ".tbl",0,"$"
align 2
TubCode	       dw 0
TubPointers    dw offset Tubeler
MxkPointers    dw offset MXKBuff
DATA   ENDS
;----------------------------------------------------------------

;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
VLAMITS  PROC NEAR
;----------------------------------------------------------------
.386

		mov bl,es:[80h]
		cmp bl,0
		je GIVE_CM_LINE

		mov cl,bl
		mov ch,0
		inc cx

		mov dx,DATA
		mov ds,dx

		mov si,80h
		mov di,offset PSP

XTRSN:		mov al,es:[si]
		mov [di],al

		inc si
		inc di
		loop XTRSN

		mov di,offset PSP
		add di,bx
		inc di

		mov si,offset MXKEXTENSION
                push di
		call EXT			; Add extension to filename

		mov dx,DATA
		mov ds,dx
		mov es,dx
		mov dx,offset PSP+2
		mov bx,offset MXKBUFF
		mov cx,1024
		call LOADNEW
		jmp PREPARE

GIVE_CM_LINE:   mov dx,DATA
		mov ds,dx
		mov dx,offset GIVENAME
		mov ah,9
		int 21h
		mov ah,4ch
		int 21h

		;--------------------------------------------------
		;--------------------------------------------------

PREPARE:


		; Add an _TBL extensions to filename
                call Convensions
		pop di
                mov si,offset _TBL
                call EXT

		; Open acces to target file
                mov dx,offset PSP+2
		mov cx,0
                mov ah,3ch
                int 21h
                jc Not_Found
                mov bp,ax

		; Read a source filename
ReadTBL:        call Convensions
		mov si,offset MxkPointers
		mov al,[si]
                cmp al,255
                je CloseFile

                mov dx,DATA
                mov ds,dx
                mov es,dx
                mov dx,word ptr MxkPointers
                mov bx,word ptr TubPointers
                mov cx,100
                call LoadNew

		call Convensions
                mov bx,bp
                mov dx,word ptr TubPointers
                mov cx,100
                mov ah,40h
                int 21h
                jc Not_Found

                call Convensions
                mov ax,word ptr TubPointers
                add ax,100
                mov word ptr TubPointers,ax

		mov si,word ptr MxkPointers
LookForNul:     mov al,[si]
                inc si
                cmp al,0
                je FoundNul
                jmp LookForNul

FoundNul:	mov word ptr MxkPointers,si
           	jmp ReadTBL

CloseFile:	mov bx,bp
		mov ah,3eh
                int 21h
                jc Not_Found
		jmp QUIT

CONVENSIONS PROC NEAR
		push dx
		mov dx,DATA
		mov ds,dx
		pop dx
		ret
CONVENSIONS ENDP

; -----------------------FIN DU PROGRAMME-----------------------
VLAMITS    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END     VLAMITS                           ; Point d'entree
;---------------------------------------------------------------
