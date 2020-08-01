; ****************************************************************
;
; 	ASSEMBLY MODULES RUNTIME LIBRAIRY: 95COLORS.ASM
;
; 		COPYRIGHT 1995 FRANCOIS BLANCHETTE
;
; ****************************************************************

ASSUME SS:STACK, DS:DATA

TITLE RUNTIME_LIBRAIRY_95COLORS

INCLUDE \MASM61\LISTING\SSFSM95.INC
INCLUDE \MASM61\LISTING\IOSYSTEM.INC

USEREPV2	; 94REPV2.ASM
USECOLORS	; 95COLORS.ASM

STACK     SEGMENT STACK
STACK     ENDS
;-----------------------------------------------------------------------

DATA SEGMENT 'DATA' PUBLIC
COPYRIGHT	DB "95COLORS RUNTIME LIBRAIRY "
		DB "(C) 1995 FRANCOIS BLANCHETTE."
C_REGISTERS     DB 256 * 3 DUP (0)
O_REGISTERS	DB 256 * 3 DUP (0)
COLORSUSED	DB 256 DUP (0)
DATA ENDS

;-----------------------------------------------------------------------
CODE SEGMENT 'CODE' PUBLIC
.386
;-----------------------------------------------------------------------

FINDCOLORSUSED PROC

		PUSHALL
                SET DS,DATA
                XOR BH,BH
                XOR SI,SI
                MOV DI,OFFSET COLORSUSED
                MOV AX,1
                MOV BL,GS:[SI]
                CMP BYTE PTR [BX+DI], 0
                JNE ALREADYUSED
                MOV BYTE PTR [BX+DI],AL
                INC AL
ALREADYUSED:
                POPALL
                RET

FINDCOLORSUSED ENDP

;---------------------------------------------------------------------

ENABLEREFRESH PROC
		PUSHALL
                MOV AH,12H
                MOV AL,0
                MOV BL,36H
                INT 10H
                POPALL
		RET
ENABLEREFRESH ENDP

;----------------------------------------------------------------------

DISABLEREFRESH PROC

		PUSHALL
		MOV AH,12H
                MOV AL,1
                MOV BL,36H
                INT 10H

                POPALL
		RET
DISABLEREFRESH ENDP

;------------------------------------------------------------------------

FILLREGISTERS PROC

	        PUSHALL
                CALL DISABLEREFRESH
		MOV AH,10H
	        MOV AL,12H
	        MOV BX,0
	        MOV CX,256
	        SET ES,DATA
	        MOV DX,OFFSET C_REGISTERS
		INT 10H
	        POPALL
                CALL ENABLEREFRESH
	        RET
FILLREGISTERS ENDP

;------------------------------------------------------------------------

GETREGISTERS PROC
	        PUSHALL
		MOV AH,10H
	        MOV AL,17H
	        MOV BX,0
	        MOV CX,256
	        SET ES,DATA
	        MOV DX,OFFSET C_REGISTERS
		INT 10H
	        POPALL
        	RET
GETREGISTERS ENDP

;-------------------------------------------------------------------------
_SETCOLOR	PROC NEAR PASCAL, COLORREG:WORD, RED:BYTE, GREEN:BYTE, BLUE:BYTE
		PUSHALL
                MOV AH,10H
                MOV AL,10H
                MOV BX,COLORREG
                MOV CH,GREEN
                MOV CL,BLUE
                MOV DH,RED
                INT 10H
                POPALL
                RET
_SETCOLOR       ENDP
;-------------------------------------------------------------------------------

CODE ENDS
END

