;----------------------------------------------------------------
;       THE VLAMITS
;       by Francois Blanchette
;----------------------------------------------------------------

; NOTE: REQUIERS 94REPV2
INCLUDE C:\MASM61\LISTING\SSFSM95.INC
INCLUDE C:\MASM61\LISTING\IOSYSTEM.INC

; Enables all externals definitions...
UseRepV2	; 94REPV2.ASM
;UseSTATV2	; 94STATV2.ASM

;-----------------------------------------------------------------------
HexFrameExtender MACRO Value, Frame
Local		ALNotABC, ALNotABC_

                pushall

                set <ds>,DATA

                mov di, Frame


                mov al,Value
                and al,15
                add al,30h

                cmp al,3ah
                jb ALNotABC
                sub al,3ah
                add al,65
ALNotABC:	mov [di+1], al


		mov al,Value
                shr al,4
                and al,15
                add al,30h

                cmp al,3ah
                jb ALNotABC_
                sub al,3ah
                add al,65
ALNotABC_:	mov [di],al

                popall
                ENDM

;------------------------------------------------------------
printx	MACRO Value_
	HexFrameExtender Value_, offset Frame_
	print offset Frame_
	ENDM

;------------------------------------------------------------

Pause 	Macro
	local X

        pushall
	mov ah,9
        set ds,DATA
        set dx,offset PauseTxt
        int 21h

X:       call getax
        cmp ax,0
        je X

	popall
	ENDM

;----------------------------------------------------------------
ASSUME CS:CODE,DS:DATA,SS:STACK
STACK     SEGMENT STACK
	  DB 400H DUP  (0)
STACK     ENDS
;----------------------------------------------------------------

;----------------------------------------------------------------
DATA      SEGMENT PUBLIC 'DATA'
Copyright	db "Hex2Text",13,10
		db "(C) 1995: FRANCOIS BLANCHETTE.",13,10,13,10,"$"
Retour		db 13,10,"$"
DBTxt		db "		DB $"
Space		db ",$"
HTxt		db "0x$"
align 2
Frame_		dw 0,"$"

Buffer		db 16 DUP (0)
SFileName	db 64 DUP (0)
align 2
HSFile		dw 0
PspPtr		dw 81h

		   ;0123456789012345
Junk		db "To my lost self!"
ErrTxt		db "Syntaxe: HEX2TEXT <filename>",13,10,"$"

DATA   ENDS
;----------------------------------------------------------------
SFile		EQU word ptr HSFile
;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
VLAMITS  PROC NEAR
;----------------------------------------------------------------
.386

                HSetHandler offset LocalErrorHandler

		set ds,DATA
		print offset Copyright


                set ds,DATA
                read <es>,word ptr PSPPtr,DATA,offset SFileName

                HOpenForRead offset SFileName, SFile
X1:             Copymem DATA, offset Buffer, DATA, offset Junk,16
                HReadfile DATA, offset Buffer, 16, SFile
                CmpStrings DATA, offset Buffer, DATA, offset Junk,16
                jnerr Bye

Ok:
                mov cx,16
                mov si,offset Buffer

                print offset DBTxt
X:

                print offset HTxt
		printx byte ptr [si]
                inc si
                cmp cx,1
                je Z
                print offset Space
Z:              eloop X

                print offset Retour
                mov cx,dx
                dec dx
		jmp X1
Bye:
		leaveprogram 0

LocalErrorHandler:

		print offset ErrTxt
                leaveprogram -1



; -----------------------FIN DU PROGRAMME-----------------------
VLAMITS    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END     VLAMITS                           ; Point d'entree
;---------------------------------------------------------------
