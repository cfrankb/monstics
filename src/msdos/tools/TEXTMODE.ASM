;----------------------------------------------------------------
;       THE VLAMITS
;       by Francois Blanchette
;----------------------------------------------------------------

; NOTE: REQUIERS 94REP
INCLUDE C:\MASM61\LISTING\SSFSM95.INC
INCLUDE C:\MASM61\LISTING\IOSYSTEM.INC

; Enables all externals definitions...
UseRepV2	; 94REPV2.ASM
;UseSTATV2	; 94STATV2.ASM

;----------------------------------------------------------------
ASSUME CS:CODE,DS:DATA,SS:STACK
STACK     SEGMENT STACK
	  DB 400H DUP  (0)
STACK     ENDS
;----------------------------------------------------------------

;----------------------------------------------------------------
DATA      SEGMENT PUBLIC 'DATA'

	db "TextMode (C) 1995: FRANCOIS BLANCHETTE"

DATA   ENDS
;----------------------------------------------------------------

;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
VLAMITS  PROC NEAR
;----------------------------------------------------------------
.386


		mov ah,0fh
                int 10h
                cmp al,	3
                je ByeBye

		mov ah,0
                mov al,3
                int 10h

ByeBye:		leaveprogram 0

; -----------------------FIN DU PROGRAMME-----------------------
VLAMITS    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END     VLAMITS                           ; Point d'entree
;---------------------------------------------------------------
