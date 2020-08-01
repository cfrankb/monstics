; ****************************************************************
;
; 	ASSEMBLY MODULES RUNTIME LIBRAIRY: 95STRING.ASM
;
; 		COPYRIGHT 1995 FRANCOIS BLANCHETTE
;
; ****************************************************************

ASSUME SS:STACK, DS:DATA

TITLE RUNTIME_LIBRAIRY_95STRING

INCLUDE \MASM61\LISTING\SSFSM95.INC
INCLUDE \MASM61\LISTING\IOSYSTEM.INC

USEREPV2	; 94REPV2.ASM
;USESTATV2	; 94STATV2.ASM
;USESTATV2_1	; 95STV2_1.ASM
;USEVGAHI	; 95VGAHI.ASM
USESTRINGS	; 95STRING.ASM

STACK     SEGMENT STACK
STACK     ENDS

DATA SEGMENT 'DATA' PUBLIC
COPYRIGHT	DB "95STRING RUNTIME LIBRAIRY "
		DB "(C) 1995 FRANCOIS BLANCHETTE."
DATA ENDS

;------------------------------------------------------------------------
CODE SEGMENT 'CODE' PUBLIC
.386
;------------------------------------------------------------------------
_STRCMP		PROC NEAR PASCAL, DSEG:WORD, DOFF:WORD, SSEG:WORD, SOFF:WORD
		PUSH ES
                PUSH DI
                PUSH FS
                PUSH SI

                SET ES,DSEG
                SET FS,SSEG
                MOV DI,DOFF
                MOV SI,SOFF

                XOR AL,AL
NX:             IFEDO BYTE PTR ES:[DI],0, BYE
                IFEDO BYTE PTR FS:[SI],0, BYE

		MOV AL, ES:[DI]
                SUB AL, FS:[SI]
                INC DI
                INC SI
                IFZDO AL,NX

BYE:            POP SI
                POP FS
                POP DI
                POP ES
		RET
_STRCMP		ENDP

;------------------------------------------------------------------
_STRCMPI	PROC NEAR PASCAL, DSEG:WORD, DOFF:WORD, SSEG:WORD, SOFF:WORD, SIZE_:WORD
                PUSH CX
		PUSH ES
                PUSH DI
                PUSH FS
                PUSH SI

                SET ES,DSEG
                SET FS,SSEG
                MOV DI,DOFF
                MOV SI,SOFF
                MOV CX,SIZE_

NX:             ;IFEDO BYTE PTR ES:[DI],0, BYE
                ;IFEDO BYTE PTR FS:[SI],0, BYE

		MOV AL, ES:[DI]
                SUB AL, FS:[SI]
                INC DI
                INC SI
                IFNDO AL,0, BYE
                LOOP NX

BYE:
                POP SI
                POP FS
                POP DI
                POP ES
                POP CX
		RET
_STRCMPI	ENDP

;------------------------------------------------------------------

_STRLEN   	PROC NEAR PASCAL, DSEG:WORD, SOURCE:WORD
                PUSH ES
                PUSH SI
                MOV SI, SOURCE
		SET ES,DSEG
                XOR AX,AX
NX:		CMP BYTE PTR ES:[SI],0
                JE BYE
                INC SI
                INC AX
		JMP NX
BYE:
		POP SI
		POP ES
                RET
_STRLEN		ENDP

;------------------------------------------------------------------
_REPLACECHAR 	PROC NEAR PASCAL, DSEG:WORD,DI_:WORD,CX_:WORD,SCAR:BYTE,DCAR:BYTE
		PUSHALL
		MOV DX,DSEG
                MOV ES,DX
                MOV SI,DI_
                MOV CX,CX_
                MOV BL,SCAR
                MOV BH,DCAR

CC:             MOV AL,ES:[SI]
                CMP AL,BL
                JNE NCMATCH
                MOV ES:[SI],BH
NCMATCH:	INC SI
		LOOP CC
		POPALL
                RET
_REPLACECHAR	ENDP
;------------------------------------------------------------------

CODE ENDS
END
