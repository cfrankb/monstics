;----------------------------------------------------------------
;       MCG TO IMA CONVERTER
;       by Francois Blanchette
;----------------------------------------------------------------

include c:\Masm61\listing\SSFSM95.INC
include c:\MASM61\LISTING\IOSYSTEM.INC

; Enables all externals definitions...
UseRepV2		; 94REPV2.ASM
;UseSSFSLB	; 94SSFSLB.ASM
;UseSTATLB	; 94STATLB.ASM

;----------------------------------------------------------------
ASSUME CS:CODE,DS:DATA,SS:STACK
STACK     SEGMENT STACK
	  DB 400H DUP  (0)
STACK     ENDS
;----------------------------------------------------------------

;----------------------------------------------------------------
DATA      SEGMENT PUBLIC 'DATA'
COPYRIGHT      db "MCG TO IMA CONVERTOR (C) 1995: FRANCOIS BLANCHETTE"
GIVENAME       db "Please specify the name of the source .MCG file to",13,10
		db "be converted.",13,10,13,10
                db "Example:",13,10
                db "MCG2IMA SONIA.MCG",13,10,13,10,"$"

_IMA		db ".IMA",0,"$"

PSP 	       db 256 DUP (0)
Junk		db 7 DUP (0)

align 4
SFileHandle	dw 0
TFileHandle	dw 0
DotPtr		dw offset PSP+2
		db 2,2
NeoFile		db 256 DUP (0)
Buffer		db 256 DUP (0)

DATA   ENDS
;----------------------------------------------------------------

SFile		EQU word ptr SFileHandle
TFile		EQU word ptr TFileHandle

;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
VLAMITS  PROC NEAR
;----------------------------------------------------------------
.386

		set ds,DATA

		mov bl,es:[80h]
		cmp bl,0
		je GIVE_CM_LINE

		mov cl,bl
		mov ch,0
		inc cx

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

                mov byte ptr [di],0
                jmp DoTheJob

GIVE_CM_LINE:   Print offset GiveName
		LeaveProgram 1

;---------------------------------------------------------------

DoTheJob:       set ds,DATA

		HOpenForRead offset PSP+2, SFile
		HReadFile DATA,offset Junk, 7, SFile
                HReadFile DATA, offset Buffer, 256, SFile
                HClose SFile

		SkipChar DATA,word ptr DotPtr, "."

                mov si,offset _IMA
                mov di,word ptr DotPtr
                dec di
                call EXT

		Print offset PSP+2

                mov si,offset Buffer
                mov di,offset NeoFile

                mov ex,2
A3:             mov dx,2
		push si

A2:             mov cx,8
                push si

A1:             mov eax,[si]
                mov [di],eax
                mov eax,[si+4]
                mov [di+4],eax

		add di,8
                add si,16

		loop A1

		pop si
                add si,8
                mov cx,dx
                dec dx
                loop A2

		pop si
                add si,128
                mov cx,ex
                dec ex
                loop A3

                HCreat offset PSP+2, TFile
                HWrite DATA, offset NeoFile-2, 258, TFile
                HClose TFile

		LeaveProgram 0

; -----------------------FIN DU PROGRAMME-----------------------
VLAMITS    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END     VLAMITS                           ; Point d'entree
;---------------------------------------------------------------
