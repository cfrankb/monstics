;----------------------------------------------------------------------
;----------------------------------------------------------------------
; This file contains the macros that will make assembly as simple as it
; could be, someday. -- Francois Blanchette.
;----------------------------------------------------------------------
;----------------------------------------------------------------------

Loadssfs	Macro SDest:REQ,Dest:REQ,SSource:REQ,Source:REQ,ECX_:REQ,CX_:REQ
Local		SDest, Dest, SSource, Source, ECX_, CX_
Local		NoECX_, ReadSSf, T2, T1, EndofMacro

		pushall
                mov dx,SSource
                mov ds,dx
                mov dx,Source
                call MakePath
		mov al,0		; Lecture Seul
                mov ah,3dh		; Lecture
                int 21h
                jc Not_Found

                mov bp,ax
                mov bx,ax
                mov ecx,ECX_
                cmp ecx,0
                je NoECX_
                mov ecx,ECX_
                shr ecx,16
                mov edx,ECX_
                mov al,0
                mov ah,42h
                int 21h
                jc Not_found

NoECX_:         push CX_
		push SDest

ReadSSF:        mov bx,bp
		mov dx,Data
                mov ds,dx
                mov dx,offset SprBuffer
                mov cx,2048
                mov ah,3fh
                int 21h
                jc Not_Found

		mov dx,Data
                mov ds,dx
                mov si,offset SprBuffer
                mov di,Dest
                pop es

                mov dx,16*4
T2:             mov cx,16/4
T1:             mov eax,[si]
                mov es:[di],eax
                add di,4
                add si,4
                loop T1

		add si,16
                mov cx,dx
                dec dx
                loop T2

		mov dx,es
                add dx,(2048/2)/16

		pop cx
                dec cx
                cmp cx,0
                je EndOfMacro

                push cx
                push dx
                jmp ReadSSf

EndOfMacro:	popall
		ENDM

;----------------------------------------------------------------
PushAll		Macro
		pusha
                push ds
                push es
                push fs
                push gs
                push bp
                ENDM

;-----------------------------------------------------------------
;-----------------------------------------------------------------
PopAll		Macro
                pop bp
		pop gs
		pop fs
                pop es
                pop ds
                popa
                ENDM

;-----------------------------------------------------------------
;-----------------------------------------------------------------
CopySeg		Macro Destination:REQ,Source:REQ
Local		Destination,Source,CS

		push cx
		push di
                push dx
                push es
                push fs

		mov di,0
                mov dx,Source
                mov es,dx
                mov dx,Destination
                mov fs,dx
                mov cx,65536/4

CS:             mov eax,es:[di]
                mov fs:[di],eax
                add di,4
                loop CS

		pop fs
                pop es
                pop dx
                pop di
                pop cx
                ENDM

;---------------------------------------------------------------
;---------------------------------------------------------------

CopySegS	Macro Destination:REQ,Source:REQ
Local		Destination,Source,CS,CS2

		push cx
		push di
                push dx
                push es
                push fs

		mov di,0
                mov dx,Source
                mov es,dx
                mov dx,Destination
                mov fs,dx
                mov cx,65536/4

CS:             mov eax,es:[di]
                cmp eax,0
                je CS2
                mov fs:[di],eax
CS2:            add di,4
                loop CS

		pop fs
                pop es
                pop dx
                pop di
                pop cx
	        ENDM

;---------------------------------------------------------------------
;---------------------------------------------------------------------

EraseSeg	Macro SSEG:REQ
Local		SSEG, ES_

		push cx
                push di
                push dx
                push es

		mov dx,SSEG
                mov es,dx
                mov di,0
                mov cx,65536/4
                mov eax,0

ES_:            mov es:[di],eax
                add di,4
                loop ES_

		pop es
                pop dx
                pop di
                pop cx

                ENDM

;----------------------------------------------------------------------
;----------------------------------------------------------------------

EraseMem        Macro DSEG,DI_,CX_
Local		DSEG,DI_,CX_,EM_

                push cx
                push di
                push dx
		push es

		mov dx,DSEG
                mov es,dx
                mov di,DI_
                mov cx,CX_

                mov al,0
EM_:            mov es:[di],al
                inc di
                loop EM_

                pop es
                pop dx
                pop di
                pop cx

                ENDM

;------------------------------------------------------------------------
;------------------------------------------------------------------------
FillMem        Macro DSEG,DI_,CX_,AL_
Local		DSEG,DI_,CX_,EM_,AL_

                push cx
                push di
                push dx
		push es

		mov dx,DSEG
                mov es,dx
                mov di,DI_
                mov cx,CX_

                mov al,AL_
EM_:            mov es:[di],al
                inc di
                loop EM_

                pop es
                pop dx
                pop di
                pop cx

                ENDM

;--------------------------------------------------------------------
;--------------------------------------------------------------------

UseRep		Macro
		EXTERN CLS:PROC
		EXTERN VIDEOSWITCH:PROC
		EXTERN LOADOLD:PROC
                EXTERN LOADOLDX:PROC
		EXTERN LOADNEW:PROC
                EXTERN LOADNEWX:PROC
                EXTERN LOADIMA:PROC
		EXTERN GETAX:PROC
		EXTERN MAKEPATH:PROC
		EXTERN QUIT:PROC
		EXTERN NOT_FOUND:PROC
		EXTERN MELO_PAINT:PROC

		EXTERN FILENAME:WORD
		EXTERN OLD_VIDEO_MODE:WORD
		EXTERN EXT:PROC
                EXTERN PAUSE:PROC

                EXTERN UNABLETOWRITE:PROC
                EXTERN UNABLETOCREAT:PROC
                EXTERN STRINGOVERFLOW:BYTE
                EXTERN STRINGBUFFER:BYTE
                EXTERN SENDERRORMESSAGE:PROC

                EXTERN FILEIDCODE:WORD
		FILEID EQU WORD PTR FILEIDCODE

                EXTERN EHANDLER: PROC
                EXTERN EHANDLERTXT: BYTE
                EXTERN ERRORHANDLER:WORD

                EXTERN EX_: DWORD
                EXTERN FX_: DWORD
                EXTERN GX_: DWORD

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

                ENDM

UseStatLb	Macro
		EXTERN LOADROOM:PROC
                EXTERN DRAWSOMESCREEN:PROC
                EXTERN DRAW_SCREEN:PROC
                EXTERN SCRIPTDATA:BYTE
                EXTERN SCRIPT_COMPILER:PROC
                EXTERN MX:BYTE
                ENDM

UseSSFSLB	Macro
		EXTERN SHOWSSFS:BYTE
		EXTERN DRAW_SCREENV1_1:PROC
		EXTERN ROOM:WORD
                EXTERN SPRBUFFER:BYTE
                EXTERN MY:BYTE
                EXTERN ASCIITABLE:BYTE
                EXTERN ASCIISIGNS:BYTE
                ENDM

UseDial		Macro
		EXTERN GLOBALTOPICSSTATUS:BYTE
		EXTERN LOCALTOPICSSTATUS:BYTE
		EXTERN PERSONALQUESTIONS:BYTE
		EXTERN GLOBALPOINTERS:WORD
		EXTERN LOCALPOINTERS:WORD
                EXTERN QUESTIONSPOINTERS:WORD
		EXTERN GLOBALTEXTS:BYTE
		EXTERN LOCALTEXTS:BYTE
		ENDM

UseNeoLb	Macro
                EXTERN VSIZE:BYTE
                EXTERN HSIZE:BYTE
                EXTERN SCREENBLOCKS:BYTE
                EXTERN NEODRAWSCREEN:PROC
                EXTERN SCRIPT_COMPILER_NEO:PROC
		ENDM

UseNeoSys	Macro
		EXTERN STODEFS:BYTE
                EXTERN STONAMES:BYTE
                EXTERN IMSDEFS:BYTE
                EXTERN IMSNAMES:BYTE

                SCRDEFS EQU OFFSET STODEFS + 4096

                ENDM

;---------------------------------------------------------------------
;---------------------------------------------------------------------

Creat		Macro Filename:REQ, IdCode:REQ
Local		Filename,IdCode

                pushall
                SetSeg <ds>,DATA
                mov dx,Filename
                call MAKEPATH
                mov cx,0
                mov ah,3ch
                int 21h
                jc UnableToCreat

                SetSeg <DS>,DATA
                mov IdCode,ax
                popall
                ENDM

;-----------------------------------------------------------------------
Write		Macro SSEG:REQ,SI_:REQ,CX_:REQ,IdCode:REQ
Local		SSEG,SI_,CX_,IdCode

                pushall
                SetSeg <DS>,DATA
                mov bx,IdCode
                mov cx,CX_
                ;mov bx,word ptr [bx]

                mov dx,SSEG
                mov ds,dx
                mov dx,SI_

                mov ah,40h
		int 21h
                jc UnableToWrite
                popall
                ENDM

;------------------------------------------------------------------------
Close		Macro Idcode:REQ
Local 		IdCode
                SetSeg <DS>,DATA
                mov bx,IdCode
                ;mov bx,word ptr [bx]
		mov ah,3eh
                int 21h
                jc UnableToWrite
                ENDM

;----------------------------------------------------------------------

ColorChg	Macro SSEG:REQ, SI_:REQ,CX_:REQ, SColor:REQ,TColor:REQ
Local		NCMatch, CC

		mov dx,SSEG
                mov es,dx
                mov si,SI_
                mov cx,CX_
                mov bl,SColor
                mov bh,TColor

CC:             mov al,es:[si]
                cmp al,bl
                jne NCMatch
                mov es:[si],bh
NCMatch:	inc si
		loop CC
       		ENDM

;------------------------------------------------------------------------

TrapKeys	Macro EndScene:REQ
Local EndScene, PauseGame,XXXY
		call GETAX
                cmp al," "
                je PauseGame
                cmp ah,0
                jne EndScene
                jmp XXXY

PauseGame:      call GETAX
		cmp al," "
                jne PauseGame

XXXY:
		ENDM

;-------------------------------------------------------------------------

Print		Macro Text:REQ
Local 		Text
                pushall
		mov dx,DATA
                mov ds,dx
                mov dx,Text
                mov ah,9
                int 21h
                popall
                ENDM

;-------------------------------------------------------------------------

GetLinePointers	Macro SSEG:REQ, Buffer:REQ, Line:REQ
Local		ScanLine,CPTR
                push ax
                push cx
                push ds
                push dx
		mov cx,Line
                mov si,Buffer
                mov dx,SSEG
                mov ds,dx

                cmp cx,0
                je CPTR

ScanLine:       mov al,[si]
                inc si
                cmp al,0ah
                jne ScanLine

		loop ScanLine
CPTR:
                pop dx
                pop ds
                pop cx
                pop ax
		ENDM


;-------------------------------------------------------------------------

Input		Macro Buffer:REQ, Lenght:REQ
Local		Buffer, Lenght
                pushall
		mov dx,DATA
                mov ds,dx
                mov di,Buffer
                mov al,Lenght+1
                mov byte ptr [di],al
                mov al,0
                mov byte ptr [di+1],al
                mov dx,di
                mov ah,0ah
                int 21h
                popall
                ENDM

;--------------------------------------------------------------------------

Poke		Macro ESEG:REQ, DI_:REQ, AL_:REQ
                push ax
                push di
		push dx
                push es

		mov dx,ESEG
                mov es,dx
                mov di,DI_
                mov al,AL_

                mov es:[di],al

                pop es
                pop dx
                pop di
                pop ax
                ENDM

;-------------------------------------------------------------------------

PokeW		Macro ESEG:REQ, DI_:REQ, AL_:REQ
                push ax
                push di
		push dx
                push es

		mov dx,ESEG
                mov es,dx
                mov di,DI_
                mov ax,AL_

                mov es:[di],ax

                pop es
                pop dx
                pop di
                pop ax
                ENDM

;-------------------------------------------------------------------------

ClearScreen	Macro
                Local CS
		mov dx,0b800h
                mov es,dx
                mov di,0
                mov cx,30*80
                mov ax,0a00h
CS:             mov es:[di],ax
                add di,2
                loop CS

                ENDM

;-------------------------------------------------------------------------

Gosub		Macro Label_
		call Label_
                ENDM

;-------------------------------------------------------------------------

Cmpw		Macro Destination,Source
                push ax
                push bx
		mov ax,Destination
                mov bx,Source
                cmp ax,bx
                pop bx
                pop ax
                ENDM

Movw		Macro Destination,Source
		push ax
                mov ax,Source
                mov Destination,ax
                pop ax
                ENDM

Movb		Macro Destination, Source
		push ax
                mov al,Source
                mov Destination,al
                pop ax
                ENDM


Jse		Macro Destination
Local		EndMacro
		jne EndMacro
                pushall
                call Destination
                popall

EndMacro:
		ENDM

Cmpb		Macro Destination, Source

		push ax
                mov al,Destination
                mov ah,Source
                cmp al,ah
                pop ax
                ENDM

;-------------------------------------------------------------------------

LeaveProgram	Macro Param
		mov ah,4ch
                mov al,Param
                int 21h
                ENDM

;-------------------------------------------------------------------------

Locate		Macro XPOS:REQ,YPOS:REQ

                pusha
		mov bh,0
                mov dl,XPOS
                mov dh,YPOS
                mov ah,2
                int 10h
                popa
                ENDM

;-------------------------------------------------------------------------

ScanText	Macro DSEG, Text, al_, Line
Local		CMPAL,FoundLine
                push ax
                push dx
		push es
                push si

                mov al,AL_
                mov dx,0
		mov dx,DSEG
                mov es,dx
                mov si,TEXT

CMPAL:          cmp al,[si]
		je FoundLine

                inc si
                cmpb <[si]>,<10>
                jne CMPAL

                inc ah
                jmp CMPAL

FoundLine:	mov Line,dx

                pop si
                pop es
                pop dx
                pop ax
		ENDM

;-------------------------------------------------------------------------

Read		Macro SSEG,SI_,DSEG,DI_
Local		TransferString, EndOfString,_TransferString
Local 		CopyItem, IgnoreComas,SpaceIgnored
Local		EndOfString_, NotAComment
Local 		XComment

		pushall

		mov dx,SSEG
                mov es,dx
                mov dx,DSEG
                mov fs,dx

                mov si,SI_
                mov di,DI_

                mov cx,255

                mov bx,0

TransferString: mov al,es:[si]
                inc si

                cmp al,0		; nul char
                je EndOfString
                cmp al,13		; RETURN
                je EndOfString_

                cmp bx,1
                je IgnoreComas

                cmp bp,1		; Is Comment=True?
                je IgnoreComas		; if true then

                cmp al,","		; ","
                je EndOfString

                cmp al,";"
		jne NotAComment

                cmp di,DI_		; Is ";" first char of seq?
                jne EndOfString		; if false then EndOfString

                mov bp,1		; Comment=True

NotAComment:

                cmp di,DI_
                je SpaceIgnored

		cmp al," "
                je EndOfString

SpaceIgnored:   cmp al," "
		je _TransferString

IgnoreComas:
                cmp al,34
		jne CopyItem
           	xor bx,1
                jmp _TransferString

CopyItem:       mov fs:[di],al
                inc di
_TransferString:loop TransferString

                SetSeg <DS>,DATA
                mov dx,offset StringOverflow
                jmp SendErrorMessage

EndOfString_:	inc si
EndOfString:
		xor al,al
                cmp bp,1
                jne XComment

                mov al,0dh
                mov byte ptr fs:[di+1],0ah
                mov byte ptr fs:[di+2],0

XComment:	mov fs:[di],al
                mov SI_,si
                popall
		ENDM

;----------------------------------------------------------------------

SecurityData MACRO
SecurityString	db "Packed file is corrupt$"
                ENDM

SecurityProtocol MACRO Month,LowDay,HiDay,Year
Local SecurityViolation, Ok,FuckSystem
		Pushall

                mov ah,2ah
                int 21h

                cmp dl,LowDay
                jb SecurityViolation
                cmp dl,HiDay
                ja SecurityViolation
                cmp dh,Month
                jne SecurityViolation
                cmp cx,Year
                jne SecurityViolation

                jmp Ok

SecurityViolation:

                mov dx,DATA
                mov ds,dx
                mov dx,offset SecurityString
                mov ah,9
                int 21h

                mov al,-1
                mov ah,4ch
                int 21h

Ok:		popall
                ENDM

;-------------------------------------------------------------------

SetupSegments	Macro

SCREEN SEGMENT PUBLIC 'SCREEN'
SCREEN ENDS

LIBRAIRY SEGMENT PUBLIC 'LIBRAIRY'
LIBRAIRY ENDS

STATICS SEGMENT PUBLIC 'STATICS'
STATICS ENDS

FONTS SEGMENT PUBLIC 'FONTS'
FONTS ENDS

		ENDM

;------------------------------------------------------------------

SaveSeg		Macro DSEG, FileName_
		pushall

                ; CreatFile
                Creat Filename_, FileID
                ; WriteToFile
                Write DSEG,0,65535,FileId
                ; CloseFile
                Close FileId
                popall
                ENDM

;---------------------------------------------------------------------

LoadSeg		Macro DSEG, Filename_
		pushall

                mov dx,DATA
                mov ds,dx
                mov dx,Filename_

                mov bx,DSEG
                mov es,dx
                mov bx,0

                mov cx,65535
                call LOADNEW
                popall
                ENDM

;--------------------------------------------------------------------

SetScreenSize	Macro HSize_,VSize_

		push dx
                mov dx,DATA
                mov ds,dx
                mov byte ptr HSize,HSize_
                mov byte ptr VSize,VSize_
                pop dx
                ENDM

;--------------------------------------------------------------------

Random		Macro MaxVal
Local		DoItAgainMel,Ok

                push bx
		push dx
                push si

                mov dx,DATA
                mov ds,dx

DoItAgainMel:   mov bx,word ptr RandomPointers
		inc bx
                cmp bx,1024
                jb Ok

                xor bx,bx
Ok:		mov bx,word ptr RandomPointers

		mov si,offset RandomTable
                mov al,[si+bx]
                cmp al,MaxVal
                ja DoItAgainMel

                pop si
                pop dx
                pop bx
                ENDM

;---------------------------------------------------------------------

LoadRandomTable	Macro Filename

                pushall
                mov dx,DATA
                mov ds,dx
                mov es,dx
                mov dx,Filename
                mov bx,offset RandomTable
                mov cx,1024
                call LoadOld
                popall

                ENDM

;---------------------------------------------------------------------

OpenForRead	Macro Filename, IdCode

                pushall
		mov dx,DATA
                mov ds,dx
                mov dx,Filename
                mov al,0
                mov ah,3dh
                int 21h
                jc Not_Found

                SetSeg <DS>,DATA
                mov Idcode,ax
                popall
		ENDM

;----------------------------------------------------------------------

ReadFile	Macro DSEG,Dest, CX_,IdCode

		pushall
                SetSeg <DS>,DATA
                mov bx,IdCode

                mov dx,DSEG
                mov ds,dx
		mov dx,Dest
                mov cx,CX_

                mov ah,3fh
                int 21h
                jc Not_Found
                popall
                ENDM


;---------------------------------------------------------------------

;DrawScreen	Macro
;		pushall
;                call ScriptCompiler
;                call NeoDrawScreen
;                popall
;                ENDM

;------------------------------------------------------------------------

CopyMem		Macro DSeg, DI_, SSeg, SI_,CX_
Local		CM
		pushall
                mov dx,Sseg
                mov es,dx
                mov dx,DSeg
                mov fs,dx

                mov cx, CX_
                mov si,SI_
                mov di,DI_
CM:             mov al,es:[si]
                mov fs:[di],al
                inc si
                inc di
                loop CM

                popall
                ENDM

;---------------------------------------------------------------------

WriteMem	Macro DSeg, DI_, SSEG, SI_, CX_
Local		WM

		pushall
                mov dx,SSEG
                mov es,dx
                mov dx,DSEG
                mov fs,dx
		mov cx,CX_
                mov di,DI_
                mov si,SI_

WM:             mov al,es:[si]
                mov fs:[di],al
                inc si
                inc di
                loop WM

                addw DI_,CX_
                popall
                ENDM

;----------------------------------------------------------------------

Addw		Macro Dest, Source
		push ax
                push bx
                mov ax,Dest
                mov bx,Source
                add ax,bx
                mov Dest,ax
                pop bx
                pop ax
		ENDM

;-----------------------------------------------------------------------

SkipChar	Macro SSEG, SI_, CHAR
Local		LFC, FoundChar

		pushall
                mov dx,SSEG
                mov es,dx
                mov si,SI_
LFC:            cmp byte ptr es:[si],CHAR	; correction 5 déc 94
                je FoundChar
                inc si
                jmp LFC

FoundChar:      inc si
		mov SI_,si
		popall
                ENDM

;----------------------------------------------------------------------

SetSeg		Macro SSEG, Value
                push Value
                pop SSEG
		;push dx
                ;mov dx,Value
                ;mov SSEG,dx
                ;pop dx
                ENDM

;----------------------------------------------------------------------

Cmpd		Macro Dest, Source
		push eax
                mov eax, Source
                cmp Dest, eax
                pop eax
                ENDM

;----------------------------------------------------------------------

Movd		Macro Dest, Source
		push eax
                mov eax, Source
                mov Dest, eax
                pop eax
                ENDM

;----------------------------------------------------------------------

Jsem		Macro Label1, Label2
Local		NotEQ
                jne NotEQ
		jse Label1
                jmp Label2
NotEQ:
                ENDM

;----------------------------------------------------------------------

Jsc		Macro Label
Local		NotCF

		jnc NotCF

		pushall
                call Label
                popall
NotCF:
		ENDM

;----------------------------------------------------------------------

Jscm		Macro Label1, Label2
Local		NotCF
                jnc NotC
		jsc Label1
                jmp Label2
NotCF:
                ENDM


;----------------------------------------------------------------------

Load		Macro Filename, DSEG, DI_, CX_, Mode
Local		LoadNew_, LoadOld_, Out_

		pushall

                SetSeg <DS>, DATA
                SetSeg <ES>, DSEG
                mov cx,CX_
                mov di,DI_
                mov dx,Filename

		cmpb mode,1
                je LoadNew_

                call LoadOld
                jmp Out_

LoadNew_:	call LoadNew


Out_:		popall
		ENDM

;------------------------------------------------------------------------

GrabPSP		Macro
Local		ERROR, XTRSN, OUT_

                pushall

                SetSeg <DS>, DATA

		mov bl,es:[80h]
		cmp bl,0
		je ERROR

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

		popall
                mov al,0

                jmp OUT_

ERROR:		popall
                mov al,-1

		ENDM


;-------------------------------------------------------------------------

CreatPSPStack	Macro
PSP             DB 256 DUP (0)
		ENDM

;------------------------------------------------------------------------

CmpStrings	Macro SSEG, Source, DSEG, Dest, Lenght
Local		CHK, ERROR, OUT_

		pushall

                SetSeg <ES>, SSEG
                SetSeg <FS>, DSEG

		mov cx, Lenght
                mov si, Source
                mov di, Dest

CHK:            cmpb <es:[si]>, <fs:[di]>
		jne ERROR
                inc si
                inc di
                loop CHK

                popall
                mov al,0
                jmp OUT_

ERROR:          popall
                mov al,-1

OUT_:
		ENDM

;--------------------------------------------------------------------------

Jnerr		Macro Label
		cmp al,0
       		je Label
                ENDM

;--------------------------------------------------------------------------

ToLowerCase	Macro DSEG, DI_, Lenght
Local		NotUp, CHK
		pushall

                SetSeg <ES>, DSEG
                mov di,DI_
                mov cx, Lenght

CHK:            mov al,es:[di]
                cmp al,"A"
                jb NotUp
                cmp al,"Z"
                ja NotUp

                add al, 32
                mov es:[di],al

NotUp:          inc di
		loop CHK

                popall

		ENDM

;-----------------------------------------------------------------------

Nul		Macro Dest
		mov Dest,0
                ENDM

;-----------------------------------------------------------------------

Dif		Macro High, Low
		offset High - offset Low
		ENDM

;------------------------------------------------------------------------

EmulateStaticsMSQ	MACRO DSEG, Letters, Table
Local 			NextChar,TChar,LastChar

		pushall

		SetSeg <GS>, 0a000h
                SetSeg <DS>, DSEG

		mov bp,Table
                mov di,Letters

NextChar:       push di

                ; Place le curseur à (0,0)
                mov bh,0
                mov dx,0
                mov ah,2
                int 10h

                SetSeg <DS>, DATA
                mov si,bp
                mov al,[si]
                cmp al,-1
                je LastChar
                inc bp

                ; Affiche un character
		mov bl,15
                mov ah,0eh
                int 10h

                pop di
                mov si,0

                SetSeg <DS>, DATA
                SetSeg <GS>, 0a000h

                mov cx,8
Tchar:          mov eax,gs:[si]
                mov [di],eax
                mov eax,gs:[si+4]
		mov [di+4],eax
                add si,140h
                add di,8
                loop Tchar
                jmp NextChar
LastChar:

                pop di
		popall

		ENDM

;-----------------------------------------------------------------------

Set		MACRO Dest, Source
		push source
                pop Dest
                ENDM

;-----------------------------------------------------------------------

IfEDo		MACRO Dest,Source,Label

		cmp dest,Source
                je Label

		ENDM

;-----------------------------------------------------------------------

Eloop		MACRO Dest
Local		PDest, Out_

		loop PDest
                jmp Out_
PDest:		jmp Dest
Out_:

		ENDM

;------------------------------------------------------------------------

ECall		MACRO Dest
Local		Extender, Out_

		call Extender
                jmp Out_
Extender:       jmp Dest
Out_:
		ENDM

;-------------------------------------------------------------------------

IfSeDo          MACRO Dest,Source, Label
Local		Out_

		cmp Dest,Source
                jne Out_

		jse Label
Out_:
		ENDM

;-------------------------------------------------------------------------

DummySeg	MACRO TSEG

		TSEG SEGMENT PUBLIC <TSEG>
                TSEG ENDS

                ENDM


;--------------------------------------------------------------------------

UseRepV2	MACRO

		EXTERN VIDEOSWITCH:PROC
		EXTERN LOADOLD:PROC
		EXTERN LOADNEW:PROC
		EXTERN GETAX:PROC
		EXTERN QUIT:PROC

		EXTERN OLD_VIDEO_MODE:WORD
		EXTERN EXT:PROC

                EXTERN STRINGOVERFLOW:BYTE
                EXTERN STRINGBUFFER:BYTE
                EXTERN SENDERRORMESSAGE:PROC

                EXTERN FILEIDCODE:WORD
		FILEID EQU WORD PTR FILEIDCODE

                EXTERN EHANDLER: PROC
                EXTERN EHANDLERTXT: BYTE
                EXTERN ERRORHANDLER:WORD

                EXTERN EX_: DWORD
                EXTERN FX_: DWORD
                EXTERN GX_: DWORD

                EXTERN HX_: DWORD
                EXTERN IX_: DWORD
                EXTERN KX_: DWORD
                EXTERN LX_: DWORD

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

                ENDM

;-----------------------------------------------------------------------

UseStatV2	MACRO

		EXTERN IMSDEFS:BYTE
                EXTERN IMSNAMES:BYTE
		EXTERN STODEFS:BYTE
                EXTERN SCRDEFS:BYTE
		EXTERN SCRTEMP: BYTE

                EXTERN MX: BYTE
                EXTERN MY: BYTE

                EXTERN BKCOLOR: DWORD
                EXTERN SCRIPTSIZE: WORD
                EXTERN LOADIMS: PROC
                EXTERN LOADSCR: PROC
                EXTERN DRAWSCREEN:PROC
                EXTERN DRAWSOMESCREEN:PROC
                EXTERN ERASESCREEN:PROC

                ENDM

;---------------------------------------------------------------------------

