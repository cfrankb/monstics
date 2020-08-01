; ****************************************************************
;
; 	ASSEMBLY MODULES RUNTIME LIBRAIRY: 95VGAHI.ASM
;
; 		COPYRIGHT 1995 FRANCOIS BLANCHETTE
;
; ****************************************************************

ASSUME SS:STACK, DS:DATA, ES:LIBRAIRY

TITLE RUNTIME_LIBRAIRY_95VGAHI

INCLUDE \MASM61\LISTING\SSFSM95.INC
INCLUDE \MASM61\LISTING\IOSYSTEM.INC

USEREPV2	; 94REPV2.ASM
USESTATV2	; 94STATV2.ASM
USESTATV2_1	; 95STV2_1.ASM
USEVGAHI	; 95VGAHI.ASM

STACK     SEGMENT STACK
STACK     ENDS

DATA SEGMENT 'DATA' PUBLIC

COPYRIGHT	DB "95VGAHI RUNTIME LIBRAIRY "
		DB "(C) 1995 FRANCOIS BLANCHETTE."

DATA ENDS

LIBRAIRY SEGMENT PUBLIC 'LIBRAIRY'
;IMSDEFS		DB 32768 DUP (0)
;SCRDEFS		DB 16384 DUP (0)
;SCRTEMP		DB 04096 DUP (0)
;IMSNAMES        	DB 08192 DUP (0)
;STODEFS		DB 04096 DUP (0)
LIBRAIRY ENDS

FONT SEGMENT PUBLIC 'FONT'
FONT ENDS

FONT2 SEGMENT PUBLIC 'FONT2'
FONT2 ENDS

FONT3 SEGMENT PUBLIC 'FONT3'
FONT3 ENDS

FONT4 SEGMENT PUBLIC 'FONT4'
FONT4 ENDS

SCREEN SEGMENT 'SCREEN' PUBLIC
SCREEN ENDS

;------------------------------------------------------------------------
CODE SEGMENT 'CODE' PUBLIC
;------------------------------------------------------------------------
.386

DRAWSCRIPTWITHBIOS PROC

                PUSHALL
		SET ES,LIBRAIRY
                ;MOV SI,OFFSET SCRDEFS
		IFEDO WORD PTR ES:[SI], -1, ENDOFSCR

                ;MOV BP,DX
                ;IFEDO BP,0,ENDOFSCR


CHKNXENTRY:

		CALL GETAX
                IFEDO AL," ", BYE

                MOV DX,WORD PTR MX
                MOV AX,ES:[SI+6]		; AL=OBJX, AH=OBJY


                ; CHANGEMENT 16 MAI 1995
                ;XOR BX,BX
                ;MOV CX,WORD PTR ES:[SI+4]	; CURRENTIMA
                ;JCXZ FOUNDIMAPTR

CHKNXIMA:       ;MOV BX,ES:[BX]
                ;LOOP CHKNXIMA

                FINDIMAPTR


FOUNDIMAPTR:	MOV CL,ES:[BX+2]		; CL=OBJ LENGHT
		MOV CH,ES:[BX+4]		; CH=OBJ HEIGHT

                MOV LX,BX
		MOV BX,DX			; BL= MX; BH=MY

		; OX+OL >= MX
		ADD AL,CL
                CMP AL,BL
                JB ITISOVER

                ; OX <= MX+40
                ADD BL,BYTE PTR SCRLEN
		SUB AL,CL
                CMP AL,BL
                JA ITISOVER

                ; OY+OH >= MY
                ADD AH,CH
                CMP AH,BH
                JB ITISOVER

                ; OY <= MY+40
		ADD BH,BYTE PTR SCRHEI
                SUB AH,CH
                CMP AH,BH
                JA ITISOVER

;*****************************************************************

		PUSH BP
		MOV BX,LX

TROUVEIMAPTR:   SET HX, WORD PTR ES:[BX+4]
		SET LX, WORD PTR ES:[BX+2]

                MOV DX, WORD PTR ES:[SI+6]

                ADD BX, 6

SC2:						; ** BEGIN 2
                MOV CX,LX			; ** BEGIN 1

SC1:

                MOV AX, ES:[BX]			; FONT
                OR AX,AX
                JE BLANKIMA

                PUSH DX

                SUB DL,BYTE PTR MX
                CMP DL,BYTE PTR SCRLEN
                JAE NOTONSCREEN_

                SUB DH,BYTE PTR MY
		CMP DH,BYTE PTR SCRHEI
                JAE NOTONSCREEN_

                PUSH BX

                MOV BP,FONT
ISINSEG_:       CMP AX,1024
                JB INTHISSEG

                SUB AX,1024
		ADD BP,65536/16
                JMP ISINSEG_

INTHISSEG:	SHL AX,6
                MOV BX,AX
                MOV FS,BP



                ;-----------------------------------------------
                ; LE BIOS PREND EN CHARGE L'AFFICHAGE, CE QUI SIGNIFIE
                ; QUE LE BLOC D'INSTRUCTIONS CI-DESSUS N'EST PLUS
                ; NÉCESSAIRE.
                ;MOV AX,DX
             	;XOR DH,DH
                ;SHL DX,3
                ;MOV DI,DX

                ; AJOUTÉ UNE OFFSET ICI!	; 27 AVRIL 1995
                ;ADD DI,WORD PTR DRAWOFFSET

                ;MOV AL,0AH
                ;MUL AH
                ;SHL AX,8
                ;ADD DI,AX
                ;-----------------------------------------------

                PUSH CX

		;------------------------------------------------
                ; THIS INSIDE ZONE WAS MODIFIED ON 02-11-95
                ;------------------------------------------------

                PUSH SI
                MOV SI,BX
                XOR BX,BX

                MOV CL,DL		; CX = X
                XOR CH,CH
                SHL CX,3

                MOV DL,DH
                XOR DH,DH		; DX = Y
                SHL DX,3

NXROW:		PUSH CX
NXPIX:
                XOR BX,BX
                MOV AH,0CH
                MOV AL,FS:[SI]
                OR AL,AL
                JE NULZ
                ;PUSHALL
                INT 10H
                ;POPALL
NULZ:

                ;MOV AH, 0X0C
		  ;MOV AL,COLOR
		  ;MOV BX,0
		  ;MOV CX,X
		  ;MOV DX,Y
		  ;INT 0X10

                INC SI
                INC CX
                MOV BX,CX
                AND BX,7
                CMP BX,0
                JNE NXPIX

      		;AND CX,65535-7
                POP CX
                INC DX
                MOV BX,DX
                AND BX,7
                CMP BX,0
                JNE NXROW

		POP SI

		;--------------------------------------------

                POP CX

		POP BX
NOTONSCREEN_:	POP DX

BLANKIMA:       ADD BX,2
                INC DL
                ELOOP SC1            		; ** END 1

		MOV DL,BYTE PTR ES:[SI+6]
                INC DH
                MOV CX,HX
                DEC HX
                ELOOP SC2                        ; ** END 2

;**********************************************************************

		POP BP

ITISOVER:	ADD SI,8
		IFEDO WORD PTR ES:[SI],-1,ENDOFSCR
                JNE CHKNXENTRY

ENDOFSCR:       ;MOV WORD PTR ES:[DI],-1
BYE:
		POPALL
		RET
DRAWSCRIPTWITHBIOS ENDP


CODE ENDS
END
