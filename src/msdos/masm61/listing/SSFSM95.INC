;----------------------------------------------------------------------
;----------------------------------------------------------------------
; THIS FILE CONTAINS THE MACROS THAT WILL MAKE ASSEMBLY AS SIMPLE AS IT
; COULD BE, SOMEDAY. -- FRANCOIS BLANCHETTE.
;----------------------------------------------------------------------
;----------------------------------------------------------------------

ADDB		MACRO DEST,SOURCE
		PUSH AX
		MOV AL,SOURCE
                ADD DEST,AL
                POP AX
                ENDM

;-----------------------------------------------------------------

PUSHALL		MACRO
		PUSHA
                PUSH DS
                PUSH ES
                PUSH FS
                PUSH GS
                PUSH BP
                ENDM

;-----------------------------------------------------------------
POPALL		MACRO
                POP BP
		POP GS
		POP FS
                POP ES
                POP DS
                POPA
                ENDM

;---------------------------------------------------------------------

ERASESEG	MACRO SSEG:REQ
LOCAL		SSEG, ES_

		PUSH CX
                PUSH DI
                PUSH DX
                PUSH ES

		MOV DX,SSEG
                MOV ES,DX
                MOV DI,0
                MOV CX,65536/4
                MOV EAX,0

ES_:            MOV ES:[DI],EAX
                ADD DI,4
                LOOP ES_

		POP ES
                POP DX
                POP DI
                POP CX

                ENDM

;----------------------------------------------------------------------

ERASEMEM        MACRO DSEG,DI_,CX_
LOCAL		DSEG,DI_,CX_,EM_

                PUSH CX
                PUSH DI
                PUSH DX
		PUSH ES

		MOV DX,DSEG
                MOV ES,DX
                MOV DI,DI_
                MOV CX,CX_

                MOV AL,0
EM_:            MOV ES:[DI],AL
                INC DI
                LOOP EM_

                POP ES
                POP DX
                POP DI
                POP CX

                ENDM

;------------------------------------------------------------------------
FILLMEM        MACRO DSEG,DI_,CX_,AL_
LOCAL		DSEG,DI_,CX_,EM_,AL_

                PUSH CX
                PUSH DI
                PUSH DX
		PUSH ES

		MOV DX,DSEG
                MOV ES,DX
                MOV DI,DI_
                MOV CX,CX_

                MOV AL,AL_
EM_:            MOV ES:[DI],AL
                INC DI
                LOOP EM_

                POP ES
                POP DX
                POP DI
                POP CX

                ENDM

;-------------------------------------------------------------------------
PRINT		MACRO TEXT:REQ
LOCAL 		TEXT
                PUSHALL
		;MOV DX,DATA
                ;MOV DS,DX
                SET DS,DATA
                MOV DX,TEXT
                MOV AH,9
                INT 21H
                POPALL
                ENDM

;-------------------------------------------------------------------------

INPUT		MACRO BUFFER:REQ, LENGHT:REQ
LOCAL		BUFFER, LENGHT
                PUSHALL
		MOV DX,DATA
                MOV DS,DX
                MOV DI,BUFFER
                MOV AL,LENGHT+1
                MOV BYTE PTR [DI],AL
                MOV AL,0
                MOV BYTE PTR [DI+1],AL
                MOV DX,DI
                MOV AH,0AH
                INT 21H
                POPALL
                ENDM

;--------------------------------------------------------------------------

POKE		MACRO ESEG:REQ, DI_:REQ, AL_:REQ
                PUSH AX
                PUSH DI
		PUSH DX
                PUSH ES

		MOV DX,ESEG
                MOV ES,DX
                MOV DI,DI_
                MOV AL,AL_

                MOV ES:[DI],AL

                POP ES
                POP DX
                POP DI
                POP AX
                ENDM

;-------------------------------------------------------------------------

POKEW		MACRO ESEG:REQ, DI_:REQ, AL_:REQ
                PUSH AX
                PUSH DI
		PUSH DX
                PUSH ES

		MOV DX,ESEG
                MOV ES,DX
                MOV DI,DI_
                MOV AX,AL_

                MOV ES:[DI],AX

                POP ES
                POP DX
                POP DI
                POP AX
                ENDM

;-------------------------------------------------------------------------

CLEARSCREEN	MACRO
                LOCAL CS
                PUSHALL
		MOV DX,0B800H
                MOV ES,DX
                MOV DI,0
                MOV CX,30*80
                MOV AX,0A00H
CS:             MOV ES:[DI],AX
                ADD DI,2
                LOOP CS
                POPALL
                ENDM

;-------------------------------------------------------------------

CLEARSCREENC	MACRO COLOR
                LOCAL CS
                PUSHALL
		MOV DX,0B800H
                MOV ES,DX
                MOV DI,0
                MOV CX,30*80
                MOV AX,COLOR*256
CS:             MOV ES:[DI],AX
                ADD DI,2
                LOOP CS
		POPALL
                ENDM

;-------------------------------------------------------------------------

GOSUB		MACRO LABEL_
		CALL LABEL_
                ENDM

;-------------------------------------------------------------------------

CMPW		MACRO DESTINATION,SOURCE
                PUSH AX
                PUSH BX
		MOV AX,DESTINATION
                MOV BX,SOURCE
                CMP AX,BX
                POP BX
                POP AX
                ENDM

MOVW		MACRO DESTINATION,SOURCE
		PUSH AX
                MOV AX,SOURCE
                MOV DESTINATION,AX
                POP AX
                ENDM

MOVB		MACRO DESTINATION, SOURCE
		PUSH AX
                MOV AL,SOURCE
                MOV DESTINATION,AL
                POP AX
                ENDM


JSE		MACRO DESTINATION
LOCAL		ENDMACRO
		JNE ENDMACRO
                PUSHALL
                CALL DESTINATION
                POPALL

ENDMACRO:
		ENDM

CMPB		MACRO DESTINATION, SOURCE

		PUSH AX
                MOV AL,DESTINATION
                MOV AH,SOURCE
                CMP AL,AH
                POP AX
                ENDM

;-------------------------------------------------------------------------

LEAVEPROGRAM	MACRO PARAM
		MOV AH,4CH
                MOV AL,PARAM
                INT 21H
                ENDM

;-------------------------------------------------------------------------

LOCATE		MACRO XPOS:REQ,YPOS:REQ

                PUSHA
		MOV BH,0
                MOV DL,XPOS
                MOV DH,YPOS
                MOV AH,2
                INT 10H
                POPA
                ENDM

;-------------------------------------------------------------------------

READ		MACRO SSEG,SI_,DSEG,DI_
LOCAL		TRANSFERSTRING, ENDOFSTRING,_TRANSFERSTRING
LOCAL 		COPYITEM, IGNORECOMAS,SPACEIGNORED
LOCAL		ENDOFSTRING_, NOTACOMMENT
LOCAL 		XCOMMENT

		PUSHALL

		;MOV DX,SSEG
                ;MOV ES,DX
                ;MOV DX,DSEG
                ;MOV FS,DX

                SET ES,SSEG
                SET FS,DSEG

                MOV SI,SI_
                MOV DI,DI_

                MOV CX,255

                MOV BX,0

TRANSFERSTRING: MOV AL,ES:[SI]
                INC SI

                CMP AL,0		; NUL CHAR
                JE ENDOFSTRING
                CMP AL,13		; RETURN
                JE ENDOFSTRING_

                CMP BX,1
                JE IGNORECOMAS

                CMP BP,1		; IS COMMENT=TRUE?
                JE IGNORECOMAS		; IF TRUE THEN

                CMP AL,","		; ","
                JE ENDOFSTRING

                CMP AL,";"
		JNE NOTACOMMENT

                CMP DI,DI_		; IS ";" FIRST CHAR OF SEQ?
                JNE ENDOFSTRING		; IF FALSE THEN ENDOFSTRING

                MOV BP,1		; COMMENT=TRUE

NOTACOMMENT:

                CMP DI,DI_
                JE SPACEIGNORED

		CMP AL," "
                JE ENDOFSTRING

SPACEIGNORED:   CMP AL," "
		JE _TRANSFERSTRING

IGNORECOMAS:
                CMP AL,34
		JNE COPYITEM
           	XOR BX,1
                JMP _TRANSFERSTRING

COPYITEM:       MOV FS:[DI],AL
                INC DI
_TRANSFERSTRING:LOOP TRANSFERSTRING

                SETSEG <DS>,DATA
                MOV DX,OFFSET STRINGOVERFLOW
                JMP SENDERRORMESSAGE

ENDOFSTRING_:	INC SI
ENDOFSTRING:
		XOR AL,AL
                CMP BP,1
                JNE XCOMMENT

                MOV AL,0DH
                MOV BYTE PTR FS:[DI+1],0AH
                MOV BYTE PTR FS:[DI+2],0

XCOMMENT:	MOV FS:[DI],AL
                MOV SI_,SI
                POPALL
		ENDM

;----------------------------------------------------------------------

COPYSEG		MACRO DESTINATION:REQ,SOURCE:REQ
LOCAL		DESTINATION,SOURCE,CS

		PUSH CX
		PUSH DI
                PUSH DX
                PUSH ES
                PUSH FS

		MOV DI,0
                MOV DX,SOURCE
                MOV ES,DX
                MOV DX,DESTINATION
                MOV FS,DX
                MOV CX,65536/4

CS:             MOV EAX,ES:[DI]
                MOV FS:[DI],EAX
                ADD DI,4
                LOOP CS

		POP FS
                POP ES
                POP DX
                POP DI
                POP CX
                ENDM

;---------------------------------------------------------------

COPYSEGS	MACRO DESTINATION:REQ,SOURCE:REQ
LOCAL		DESTINATION,SOURCE,CS,CS2

		PUSH CX
		PUSH DI
                PUSH DX
                PUSH ES
                PUSH FS

		MOV DI,0
                MOV DX,SOURCE
                MOV ES,DX
                MOV DX,DESTINATION
                MOV FS,DX
                MOV CX,65536/4

CS:             MOV EAX,ES:[DI]
                CMP EAX,0
                JE CS2
                MOV FS:[DI],EAX
CS2:            ADD DI,4
                LOOP CS

		POP FS
                POP ES
                POP DX
                POP DI
                POP CX
	        ENDM

SECURITYDATA MACRO
SECURITYSTRING	DB "PACKED FILE IS CORRUPT$"
                ENDM

SECURITYPROTOCOL MACRO MONTH,LOWDAY,HIDAY,YEAR
LOCAL SECURITYVIOLATION, OK,FUCKSYSTEM
		PUSHALL

                MOV AH,2AH
                INT 21H

                CMP DL,LOWDAY
                JB SECURITYVIOLATION
                CMP DL,HIDAY
                JA SECURITYVIOLATION
                CMP DH,MONTH
                JNE SECURITYVIOLATION
                CMP CX,YEAR
                JNE SECURITYVIOLATION

                JMP OK

SECURITYVIOLATION:

                MOV DX,DATA
                MOV DS,DX
                MOV DX,OFFSET SECURITYSTRING
                MOV AH,9
                INT 21H

                MOV AL,-1
                MOV AH,4CH
                INT 21H

OK:		POPALL
                ENDM

;-------------------------------------------------------------------

SAVESEG		MACRO DSEG, FILENAME_
		PUSHALL

                ; CREATFILE
                HCREAT FILENAME_, FILEID
                ; WRITETOFILE
                HWRITE DSEG,0,65535,FILEID
                ; CLOSEFILE
                HCLOSE FILEID
                POPALL
                ENDM

;---------------------------------------------------------------------

LOADSEG		MACRO DSEG, FILENAME_
		PUSHALL

                MOV DX,DATA
                MOV DS,DX
                MOV DX,FILENAME_

                MOV BX,DSEG
                MOV ES,DX
                MOV BX,0

                MOV CX,65535
                CALL LOADNEW
                POPALL
                ENDM

;--------------------------------------------------------------------

COPYMEM		MACRO DSEG, DI_, SSEG, SI_,CX_
LOCAL		CM
		PUSHALL
                ;MOV DX,SSEG
                ;MOV ES,DX
                ;MOV DX,DSEG
                ;MOV FS,DX

                SET ES,SSEG
                SET FS,DSEG

                MOV CX, CX_
                MOV SI,SI_
                MOV DI,DI_
CM:             MOV AL,ES:[SI]
                MOV FS:[DI],AL
                INC SI
                INC DI
                LOOP CM

                POPALL
                ENDM

;---------------------------------------------------------------------

WRITEMEM	MACRO DSEG, DI_, SSEG, SI_, CX_
LOCAL		WM

		PUSHALL
                SET ES,SSEG
                SET FS,DSEG
                ;MOV DX,SSEG
                ;MOV ES,DX
                ;MOV DX,DSEG
                ;MOV FS,DX
		MOV CX,CX_
                MOV DI,DI_
                MOV SI,SI_

WM:             MOV AL,ES:[SI]
                MOV FS:[DI],AL
                INC SI
                INC DI
                LOOP WM

                ADDW DI_,CX_
                POPALL
                ENDM

;----------------------------------------------------------------------

ADDW		MACRO DEST, SOURCE
		PUSH AX
                PUSH BX
                MOV AX,DEST
                MOV BX,SOURCE
                ADD AX,BX
                MOV DEST,AX
                POP BX
                POP AX
		ENDM

;-----------------------------------------------------------------------

SKIPCHAR	MACRO SSEG, SI_, CHAR
LOCAL		LFC, FOUNDCHAR

		PUSHALL
                ;MOV DX,SSEG
                ;MOV ES,DX

                SET ES,SSEG

                MOV SI,SI_
LFC:            CMP BYTE PTR ES:[SI],CHAR	; CORRECTION 5 DÉC 94
                JE FOUNDCHAR
                INC SI
                JMP LFC

FOUNDCHAR:      INC SI
		MOV SI_,SI
		POPALL
                ENDM

;----------------------------------------------------------------------

SETSEG		MACRO SSEG, VALUE
                SET SSEG,VALUE
                ENDM

;----------------------------------------------------------------------

CMPD		MACRO DEST, SOURCE
		PUSH EAX
                MOV EAX, SOURCE
                CMP DEST, EAX
                POP EAX
                ENDM

;----------------------------------------------------------------------

MOVD		MACRO DEST, SOURCE
		PUSH EAX
                MOV EAX, SOURCE
                MOV DEST, EAX
                POP EAX
                ENDM

;----------------------------------------------------------------------

JSEM		MACRO LABEL1, LABEL2
LOCAL		NOTEQ
                JNE NOTEQ
		PUSHALL
                CALL LABEL1
                POPALL
                JMP LABEL2
NOTEQ:
                ENDM

;----------------------------------------------------------------------

JSC		MACRO LABEL
LOCAL		NOTCF

		JNC NOTCF

		PUSHALL
                CALL LABEL
                POPALL
NOTCF:
		ENDM

;----------------------------------------------------------------------

JSCM		MACRO LABEL1, LABEL2
LOCAL		NOTCF
                JNC NOTC
		JSC LABEL1
                JMP LABEL2
NOTCF:
                ENDM


;----------------------------------------------------------------------

LOAD		MACRO FILENAME, DSEG, DI_, CX_, MODE
LOCAL		LOADNEW_, LOADOLD_, OUT_

		PUSHALL

                SETSEG <DS>, DATA
                SETSEG <ES>, DSEG
                MOV CX,CX_
                MOV DI,DI_
                MOV DX,FILENAME

		CMPB MODE,1
                JE LOADNEW_

                CALL LOADOLD
                JMP OUT_

LOADNEW_:	CALL LOADNEW


OUT_:		POPALL
		ENDM

;------------------------------------------------------------------------

GRABPSP		MACRO
LOCAL		ERROR, XTRSN, OUT_

                PUSHALL

                SETSEG <DS>, DATA

		MOV BL,ES:[80H]
		CMP BL,0
		JE ERROR

		MOV CL,BL
		MOV CH,0
		INC CX

		MOV DX,DATA
		MOV DS,DX

		MOV SI,80H
		MOV DI,OFFSET PSP

XTRSN:		MOV AL,ES:[SI]
		MOV [DI],AL

		INC SI
		INC DI
		LOOP XTRSN

		POPALL
                MOV AL,0

                JMP OUT_

ERROR:		POPALL
                MOV AL,-1

		ENDM


;-------------------------------------------------------------------------

CREATPSPSTACK	MACRO
PSP             DB 256 DUP (0)
		ENDM

;------------------------------------------------------------------------

CMPSTRINGS	MACRO SSEG, SOURCE, DSEG, DEST, LENGHT
LOCAL		CHK, ERROR, OUT_

		PUSHALL

                SETSEG <ES>, SSEG
                SETSEG <FS>, DSEG

		MOV CX, LENGHT
                MOV SI, SOURCE
                MOV DI, DEST

CHK:            CMPB <ES:[SI]>, <FS:[DI]>
		JNE ERROR
                INC SI
                INC DI
                LOOP CHK

                POPALL
                MOV AL,0
                JMP OUT_

ERROR:          POPALL
                MOV AL,-1

OUT_:
		ENDM

;--------------------------------------------------------------------------

JNERR		MACRO LABEL
		OR AL,AL
       		JE LABEL
                ENDM

;--------------------------------------------------------------------------

TOLOWERCASE	MACRO DSEG, DI_, LENGHT
LOCAL		NOTUP, CHK
		PUSHALL

                SETSEG <ES>, DSEG
                MOV DI,DI_
                MOV CX, LENGHT

CHK:            MOV AL,ES:[DI]
                CMP AL,"A"
                JB NOTUP
                CMP AL,"Z"
                JA NOTUP

                ADD AL, 32
                MOV ES:[DI],AL

NOTUP:          INC DI
		LOOP CHK

                POPALL

		ENDM

;-----------------------------------------------------------------------

NUL		MACRO DEST
		MOV DEST,0
                ENDM

;-----------------------------------------------------------------------

EMULATESTATICSMSQ	MACRO DSEG, LETTERS, TABLE
LOCAL 			NEXTCHAR,TCHAR,LASTCHAR

		PUSHALL

		SETSEG <GS>, 0A000H
                SETSEG <DS>, DSEG

		MOV BP,TABLE
                MOV DI,LETTERS

NEXTCHAR:       PUSH DI

                ; PLACE LE CURSEUR À (0,0)
                MOV BH,0
                MOV DX,0
                MOV AH,2
                INT 10H

                SETSEG <DS>, DATA
                MOV SI,BP
                MOV AL,[SI]
                CMP AL,-1
                JE LASTCHAR
                INC BP

                ; AFFICHE UN CHARACTER
		MOV BL,15
                MOV AH,0EH
                INT 10H

                POP DI
                MOV SI,0

                SETSEG <DS>, DATA
                SETSEG <GS>, 0A000H

                MOV CX,8
TCHAR:          MOV EAX,GS:[SI]
                MOV [DI],EAX
                MOV EAX,GS:[SI+4]
		MOV [DI+4],EAX
                ADD SI,140H
                ADD DI,8
                LOOP TCHAR
                JMP NEXTCHAR
LASTCHAR:

                POP DI
		POPALL

		ENDM

;-----------------------------------------------------------------------

SET		MACRO DEST, SOURCE
		PUSH SOURCE
                POP DEST
                ENDM

;-----------------------------------------------------------------------

IFEDO		MACRO DEST,SOURCE,LABEL
		CMP DEST,SOURCE
                JE LABEL
		ENDM


IFZDO		MACRO DEST, LABEL
		OR DEST,DEST
                JE LABEL
		ENDM

IFNDO		MACRO DEST,SOURCE,LABEL
		CMP DEST,SOURCE
                JNE LABEL
		ENDM

;-----------------------------------------------------------------------

ELOOP		MACRO DEST
LOCAL		PDEST, OUT_

		LOOP PDEST
                JMP OUT_
PDEST:		JMP DEST
OUT_:

		ENDM

;------------------------------------------------------------------------

ECALL		MACRO DEST
LOCAL		EXTENDER, OUT_

		CALL EXTENDER
                JMP OUT_
EXTENDER:       JMP DEST
OUT_:
		ENDM

;-------------------------------------------------------------------------

IFSEDO          MACRO DEST,SOURCE, LABEL
LOCAL		OUT_

		CMP DEST,SOURCE
                JNE OUT_

		JSE LABEL
OUT_:
		ENDM
;------------------------------------------------------------------------

IFINDO		MACRO DEST, S1, S2, LABEL
LOCAL		BYE
		CMP DEST,S1
                JB BYE
                CMP DEST,S2
                JA BYE
                JBE LABEL
BYE:
    		ENDM
;------------------------------------------------------------------------

ACTIFE          MACRO SOURCE, DEST, ACT
LOCAL		BYE
		IFNDO SOURCE, DEST, BYE
                ACT
BYE:
		ENDM

;------------------------------------------------------------------------

ACTIFN          MACRO SOURCE, DEST, ACT
LOCAL		BYE
		IFEDO SOURCE, DEST, BYE
                ACT
BYE:
		ENDM

;------------------------------------------------------------------------

ACTIFNE         MACRO SOURCE, DEST, ACT
LOCAL		BYE
		IFEDO SOURCE, DEST, BYE
                ACT
BYE:
		ENDM

;-------------------------------------------------------------------

ACTIFIN		MACRO DEST, SL, SH, ACT
LOCAL 		BYE
		CMP DEST, SL
                JB BYE
                CMP DEST, SH
                JA BYE
                ACT
BYE:
		ENDM

;------------------------------------------------------------------------

PUSHS		MACRO DEST,VAL

		PUSH DEST
                PUSH VAL
                POP DEST

		ENDM

;--------------------------------------------------------------------------

SUBW		MACRO DEST,SOURCE
		PUSH AX
                MOV AX, SOURCE
                SUB DEST,AX
		POP AX
		ENDM


;--------------------------------------------------------------------------

USEREPV2	MACRO

EXTERNDEF VIDEOSWITCH:PROC
EXTERNDEF LOADOLD:PROC
EXTERNDEF LOADNEW:PROC
EXTERNDEF GETAX:PROC
EXTERNDEF QUIT:PROC

EXTERNDEF OLD_VIDEO_MODE:WORD
EXTERNDEF EXT:PROC

EXTERNDEF STRINGOVERFLOW:BYTE
EXTERNDEF STRINGBUFFER:BYTE
EXTERNDEF SENDERRORMESSAGE:PROC

EXTERNDEF FILEIDCODE:WORD
FILEID EQU WORD PTR FILEIDCODE

EXTERNDEF EHANDLER: PROC
EXTERNDEF EHANDLERTXT: BYTE
EXTERNDEF ERRORHANDLER:WORD

EXTERNDEF EX_: DWORD
EXTERNDEF FX_: DWORD
EXTERNDEF GX_: DWORD

EXTERNDEF HX_: DWORD
EXTERNDEF IX_: DWORD
EXTERNDEF KX_: DWORD
EXTERNDEF LX_: DWORD

EX EQU WORD PTR EX_
EL EQU BYTE PTR EX_
EH EQU BYTE PTR EX_+1
EEX EQU DWORD PTR EX_

FX EQU WORD PTR FX_
FL EQU BYTE PTR FX_
FH EQU BYTE PTR FX_+1
EFX EQU DWORD PTR FX_

GX EQU WORD PTR GX_
GL EQU BYTE PTR GX_
GH EQU BYTE PTR GX_+1
EGX EQU DWORD PTR GX_

HX EQU WORD PTR HX_
HL EQU BYTE PTR HX_
HH EQU BYTE PTR HX_+1
EHX EQU DWORD PTR HX_

IX EQU WORD PTR IX_
IL EQU BYTE PTR IX_
IH EQU BYTE PTR IX_+1
EIX EQU DWORD PTR IX_

KX EQU WORD PTR KX_
KL EQU BYTE PTR KX_
KH EQU BYTE PTR KX_+1
EKX EQU DWORD PTR KX_

LX EQU WORD PTR LX_
LL EQU BYTE PTR LX_
LH EQU BYTE PTR LX_+1
ELX EQU DWORD PTR LX_

F1KEY EQU 59
F2KEY EQU 60
F3KEY EQU 61
F4KEY EQU 62
F5KEY EQU 63
F6KEY EQU 64
F7KEY EQU 65
F8KEY EQU 66
F9KEY EQU 67
F10KEY EQU 68
F11KEY EQU 69
F12KEY EQU 70

UPKEY	EQU 72
DNKEY	EQU 80
LFKEY	EQU 75
RGKEY 	EQU 77
PGUPKEY	EQU 73
PGDNKEY	EQU 81
HOMEKEY	EQU 71
ENDKEY  EQU 79

ENDM

;-----------------------------------------------------------------
USESTATV2	MACRO

EXTERNDEF IMSDEFS:BYTE
EXTERNDEF IMSNAMES:BYTE
EXTERNDEF STODEFS:BYTE
EXTERNDEF SCRDEFS:BYTE
EXTERNDEF SCRTEMP: BYTE

EXTERNDEF MX: BYTE
EXTERNDEF MY: BYTE

EXTERNDEF BKCOLOR: DWORD
EXTERNDEF SCRIPTSIZE: WORD
EXTERNDEF LOADIMS: PROC
EXTERNDEF LOADSCR: PROC
EXTERNDEF DRAWSCREEN:PROC
EXTERNDEF DRAWSOMESCREEN:PROC
EXTERNDEF ERASESCREEN:PROC
EXTERNDEF SCRLEN: BYTE
EXTERNDEF SCRHEI: BYTE

SCREEN SEGMENT PUBLIC 'SCREEN'
SCREEN ENDS
FONT SEGMENT PUBLIC 'FONT'
FONT ENDS
FONT2 SEGMENT PUBLIC 'FONT2'
FONT2 ENDS
FONT3 SEGMENT PUBLIC 'FONT3'
FONT3 ENDS
FONT4 SEGMENT PUBLIC 'FONT4'
FONT4 ENDS
LIBRAIRY SEGMENT PUBLIC 'LIBRAIRY'
LIBRAIRY ENDS
ENDM

;------------------------------------------------------------

USESTATV2_1 	MACRO
_FINDLEADINGCHAR PROTO			NEAR PASCAL  CAR:BYTE
_DRAWENTRY  	PROTO 			NEAR PASCAL  ENTRY:WORD
EXTERNDEF	PASCAL _FINDLEADINGCHAR	: PROC
EXTERNDEF 	PASCAL _DRAWENTRY	: PROC
EXTERNDEF 	MAPLEVEL	 	: PROC
EXTERNDEF 	TRIEROBJS		: PROC
EXTERNDEF 	DRAWBCK			: PROC
EXTERNDEF 	DRAWFOW			: PROC
EXTERNDEF 	SCROLLUP		: PROC
EXTERNDEF 	SCROLLDN		: PROC
EXTERNDEF 	SCROLLRG		: PROC
EXTERNDEF 	SCROLLLF		: PROC
EXTERNDEF	SLOWDOWN		: PROC
EXTERNDEF	MAKEIMAPTRTABLE		: PROC
EXTERNDEF	DRAWSCRIPT		: PROC
EXTERNDEF	PLY2OFFSET		: WORD
EXTERNDEF 	DRAWOFFSET		: WORD
EXTERNDEF	IMAPTRTABLE		: WORD
EXTERNDEF       MAPLEVELEXTENSION	: WORD
CHGINGDEFS      EQU OFFSET STODEFS
ENDM

FINDLEADINGCHAR MACRO CAR
		INVOKE _FINDLEADINGCHAR, CAR
		ENDM


FINDIMAPTR	MACRO
                MOV BX,WORD PTR ES:[SI+4]
                SHL BX,1
                ADD BX, OFFSET IMAPTRTABLE
                MOV BX,[BX]
		ENDM

DRAWENTRY	MACRO ENTRY
		INVOKE _DRAWENTRY, ENTRY
		ENDM

;------------------------------------------------------------

USECOLORS	MACRO
_SETCOLOR	PROTO NEAR PASCAL COLORREG:WORD, RED:BYTE, GREEN:BYTE, BLUE:BYTE
EXTERNDEF 	C_REGISTERS  	: BYTE
EXTERNDEF 	O_REGISTERS  	: BYTE
EXTERNDEF 	GETREGISTERS 	: PROC
EXTERNDEF 	FILLREGISTERS	: PROC
EXTERNDEF 	_SETCOLOR 	: PROC
		ENDM

SETCOLOR	MACRO COLORREG, RED, GREEN, BLUE
		INVOKE _SETCOLOR, COLORREG, RED, GREEN, BLUE
                ENDM
;--------------------------------------------------------------

USEVGAHI	MACRO
EXTERNDEF	DRAWSCRIPTWITHBIOS: PROC
		ENDM

;--------------------------------------------------------------
USESTRINGS	MACRO
_REPLACECHAR 	PROTO NEAR PASCAL DSEG:WORD,DI_:WORD,CX_:WORD,SCAR:BYTE,DCAR:BYTE
_STRLEN	 	PROTO NEAR PASCAL  DSEG:WORD, SOURCE:WORD
_STRCMP		PROTO NEAR PASCAL DSEG:WORD, DOFF:WORD, SSEG:WORD, SOFF:WORD
_STRCMPI	PROTO NEAR PASCAL DSEG:WORD, DOFF:WORD, SSEG:WORD, SOFF:WORD, SIZE_:WORD
EXTERNDEF       _REPLACECHAR	:PROC
EXTERNDEF	_STRLEN 	:PROC
EXTERNDEF	_STRCMP		:PROC
EXTERNDEF	_STRCMPI	:PROC

		ENDM

STRLEN	 	MACRO DSEG, SOURCE
		INVOKE _STRLEN, DSEG, SOURCE
		ENDM

REPLACECHAR 	MACRO DSEG, DI_, CX_, SCAR, DCAR
		INVOKE _REPLACECHAR, DSEG, DI_, CX_, SCAR, DCAR
		ENDM

COLORCHG	MACRO DSEG, DI_, CX_, SCAR, DCAR
		INVOKE _REPLACECHAR, DSEG, DI_, CX_, SCAR, DCAR
       		ENDM

STRCMP		MACRO DSEG, DOFF, SSEG, SOFF
		INVOKE _STRCMP, DSEG, DOFF, SSEG, SOFF
                ENDM

STRCMPI		MACRO DSEG, DOFF, SSEG, SOFF, _SIZE
		INVOKE _STRCMPI, DSEG, DOFF, SSEG, SOFF, _SIZE
                ENDM


;-------------------------------------------------------------------------
