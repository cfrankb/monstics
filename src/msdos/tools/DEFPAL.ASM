;----------------------------------------------------------------
;       DEFAULT.PAL
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
DefPal		db "Default.pal",0
C_registers	db 3*256 DUP (0)

align 2
TfileCode	 dw 0

DATA   ENDS
;----------------------------------------------------------------

TFile		EQU word ptr TFileCode



;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
VLAMITS  PROC NEAR
;----------------------------------------------------------------
.386


                call VideoSwitch
		call GetRegisters

		HCreat offset DefPal,TFile
                HWrite DATA,offset C_Registers, 3*256,TFile
                HClose TFile

		leaveprogram 0


GetRegisters PROC NEAR
	        pushall
		mov ah,10h
	        mov al,17h
	        mov bx,0
	        mov cx,256
	        set es,DATA
	        mov dx,offset C_Registers
		int 10h
	        popall
        	ret
GetRegisters ENDP

; -----------------------FIN DU PROGRAMME-----------------------
VLAMITS    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END     VLAMITS                           ; Point d'entree
;---------------------------------------------------------------
