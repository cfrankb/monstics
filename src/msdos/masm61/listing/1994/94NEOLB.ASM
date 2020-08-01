
;------------------------------------------------------------------------
; 94NEOLB was designed to accomodate the new requierements in speed wich
; 94REP & 94STATLB were enable to satisfy. With this new module, the
; STATICS SYSTEM can now redraw the screen with an average 54% speed
; improvement.
;------------------------------------------------------------------------

TITLE 94NEOLB_ASM

ASSUME DS:DATA

Include c:\masm61\listing\ssfsmac.inc

; IMPORTING GLOBAL VARIABLES & PROCEDURES
UseREP		; Use 94REP.ASM
UseSTATLB	; Use 94STATLB.ASM
UseSSFSLB	; Use 94SSFSLB.ASM

Public VSIZE,HSIZE
Public NEODRAWSCREEN
Public SCREENBLOCKS
Public SCRIPT_COMPILER_NEO
Public SELECTIVESCREENREDRAW

; CONSTANTS
StaticCellLenght 	EQU 8
ScriptEntryLenght	EQU 4

DATA SEGMENT 'DATA' PUBLIC

VSize		db 25
HSize		db 40
BaseX		dw 0
ScreenBlocks	db 4096 DUP (0)
LowerYPos	db 40 DUP (0)
align 2
TempDX		dw 0
DATA ENDS

SetupSegments

CODE SEGMENT PUBLIC 'CODE' READONLY
.386

;---------------------------------------------------------------------
NEODRAWSCREEN::
; Objectif: The purpose of this new routine is to redraw the screen
;           and replace DRAW_SCREENV1.x
;
;	DS: DATA
;       ES: STATICS
;       FS: FONTS
;       GS: SCREEN
;
;---------------------------------------------------------------------

		; SetupSegment for NeoDrawScreen

		pushall

                mov dx,DATA
                mov ds,dx
                mov dx,STATICS
                mov es,dx
                mov dx,FONTS
                mov fs,dx
                mov dx,SCREEN
                mov gs,dx

                mov dl,byte ptr MX
                mov dh,byte ptr MY

                call DoFowardGroundScan

		call DoBackGroundDraw
                call DoFowardGroundDraw
                call DoTopPriorityDraw

                call AdjustImage

                EraseMem DATA, offset ScreenBlocks, 25*40

                popall
                ret


                ;--------------------------------------------------------

DoFowardGroundScan:

		EraseMem Data, offset LowerYPos, 40

                ; Setup dumping area
                mov di,offset LowerYPos
                xor si,si
                xor bh,bh
                mov al,1

ScanNextEntryFS:
		mov bl,es:[si]
                or bl,bl
                je EndOfSeqFS

                and bl,2
                je NotFowardOK

		; Proceding with marking that Ypos in the table
                mov bl,es:[si+5]
                mov [di+bx],al

NotFowardOK:
		add si,StaticCellLenght
		jmp ScanNextEntryFS
EndOfSeqFS:     ret

                ;----------------------------------------------
DoBackgroundDraw:
                ; This small loop will scan every statics defintions
                ; and look for those with a descriptor byte of a value
                ; of one. Therefore it will be able to send only those
                ; in background to the draw routine.

		xor si,si

ScanNextObjB:   mov al,es:[si]
                or al,al		; cmp al,0
                je EndOfStaticsDef

                and al,1
                cmp al,1
                jne NextDefB

                call DrawFont

NextDefB:       add si,StaticCellLenght
                jmp ScanNextObjB

EndOfStaticsDef:ret

		;--------------------------------------------------
DoFowardGroundDraw:

		mov cl,byte ptr VSize
                add cl,4
                xor ch,ch
                xor bp,bp
		mov bx,offset LowerYPos

DoKillSoso:     push bx
		push cx
                push bp

                mov al,[bx]
                or al,al		; cmp al,0
                je NextLevelOfPerp

		xor si,si

ScanNextObjFG:  mov al,es:[si]
                or al,al		; cmp al,0
                je NextLevelOfPerp

                and al,2
                cmp al,2
                jne NextDefFG

                mov al,es:[si+5]
                xor ah,ah
                pop bp
                push bp
                cmp ax,bp
                jne NextDefFG
                call DrawFont

NextDefFG:      add si,StaticCellLenght
                jmp ScanNextObjFG

NextLevelOfPerp:pop bp
		pop cx
                pop bx
                inc bx
                inc bp
                loop DoKillSoso
                ret

                ;---------------------------------------------------

DoTopPriorityDraw:
		xor si,si

ScanNextObjTOP: mov al,es:[si]
                or al,al		; cmp al,0
                je EndOfStaticsDef

                and al,4
                cmp al,4
                jne NextDefTOP

                call DrawFont

NextDefTOP:     add si,StaticCellLenght
                jmp ScanNextObjTOP

		;----------------------------------------------------
DrawFont:
		; Step1: See if Font is on screen.

		mov bl,es:[si+3]	; bl = XPOS
                mov bh,es:[si+4]	; bh = YPOS
                mov bp,bx

                sub bl,dl
                cmp bl,byte ptr HSize
                jae NotOnScreen

		sub bh,dh
                cmp bh,byte ptr VSize
                jae NotOnScreen

		; Step2: See if he is first.

                mov al,bl
                mov bl,bh
                xor ah,ah
                xor bh,bh

                mov cx,bx
                shl bx,5	; BX= Y*40
                shl cx,3
                add bx,cx


		add bx,ax	; BX= X+Y*40
                add bx,offset ScreenBlocks
                		; BX= X+Y*40 + offset ScreenBlocks

                mov al,[bx]
                or al,al		;cmp al,0
                jne CompleteRedraw

                		;-------------------------
                inc al		; We go for a QuickRedraw
                mov [bx],al

                call CalcDestOnScr	; BX= Destination
		mov di,es:[si+6]	; DI= Font
		shl di, 6		; DI= Font*64

                ; Please Note:
                ;  DI= Source; BX= Destination

		mov cx,8
QDraw:          mov eax,fs:[di]
                mov gs:[bx],eax
                mov eax,fs:[di+4]
                mov gs:[bx+4],eax
                add di,8
                add bx,140h
                loop QDraw
NotOnScreen:	ret

CompleteRedraw:

                call CalcDestOnScr	; BX= Destination
		mov di,es:[si+6]	; DI= Font
		shl di, 6		; DI= Font*64

                ; Please Note:
                ;  DI= Source; BX= Destination

		mov bp,8
CRDII:          mov cx,8
CRD:            mov al,fs:[di]
                or al,al
                je NulIgnored
                mov gs:[bx],al
NulIgnored:	inc di
		inc bx
                loop CRD

                add bx,140h-8
		mov cx,bp
                dec bp
                loop CRDII
                ret

		;--------------------------------------------------
CalcDestOnScr:

		mov ax,bp 	; AH=Y
                sub ah,dh
                mov al,0ah
                mul ah
                rol ax,8	; Y*0a00h

                mov bx,bp
                xor bh,bh       ; BL=X
                sub bl,dl
                shl bx,3
                add bx,ax	; BX= (X-MX)*8+ (Y-MY)*0a00h
                ret

		;-----------------------------------------------------

SCRIPT_COMPILER_NEO  PROC NEAR

		;-------------------------------------------------------
		; SCRIPT_COMPILER V1.1 modified version
		;-------------------------------------------------------
		; Fonction: Translate script file into dynamic sequences
		; using librairy internal information. Combine all
		; objects description into a set of data sequence easy
		; to read for a quick screen redraw.
		;-------------------------------------------------------
		; SEGMENT DISTRIBUTION:
		; DS: DATA
		; ES: LIBRAIRY
		; FS: DYNAMICS
		;-------------------------------------------------------

                ; Old piece of garbage that it out of date.

		mov dx,DATA
		mov ds,dx
		mov dx,LIBRAIRY
		mov es,dx
		mov dx,STATICS
		mov fs,dx

                mov dl,byte ptr MX
                mov dh,byte ptr MY

		mov si,offset SCRIPTDATA
		mov di,0
		push si

		pop si
		; MODIFICATION
CHKNEXTSCR:	mov al,[si]
		or al,al	;cmp al,0
		je COMPOVER

		push si

		mov al,[si+1]		; OBJ NUM FROM LIB
		mov bl,[si+2]           ; X POS
		mov bh,[si+3]           ; Y POS

		push bx

		mov si,ScriptEntryLenght
SEEKAL_0:	or al,al;	cmp al,0
		je FOUNDOBJ

		add si,6		; Offset 6-7 are start of next font
		mov si,es:[si]
		dec al
		jmp SEEKAL_0

FOUNDOBJ:       mov bx,8
		pop dx

		;push si
		;mov si,offset TEMPDX
		;mov [si],dx
		;pop si

                mov word ptr TEMPDX, DX	; modification 28 sep94

		mov cl,es:[si+4]
		xor ch,ch;	mov ch,0

NEXTLINEX:	push cx
		mov cl,es:[si+3]	; offset3: LENGHT
		xor ch,ch;	mov ch,0

NEXTONLINE:	;mov al,es:[si+5]	; ignore byte
		;cmp al,0
		;je NO_PROBLEM

		mov ax,es:[si+bx]
		or ax,ax;	cmp ax,0
		je IGNORE_SQR

                push dx
                sub dl,byte ptr MX
                cmp dl,byte ptr HSIZE
                jae SkipEntry

                sub dh,byte ptr MY
                cmp dh,byte ptr VSIZE
                jae SkipEntry

                jmp NO_PROBLEM

SkipEntry:	pop dx
		jmp Ignore_Sqr


NO_PROBLEM:     pop dx

		mov al,es:[si]		; READ DESCRIPTOR BYTE
		mov fs:[di],al          ; WRITE "            "

		mov al,es:[si+1]        ; READ ITEM NUMBER
		mov fs:[di+1],al	; WRITE "        "

		mov al,es:[si+2]	; READ STATUS OF ACTIVATION
		mov fs:[di+2],al	; WRITE "                 "

		mov fs:[di+3],dl        ; WRITE X POS
		mov fs:[di+4],dh	; WRITE Y POS

		mov ax,es:[si+bx]       ; READ FONT USED
		mov fs:[di+6],ax        ; WRITE "      "

		mov al,es:[si+4]	; HEIGHT

		;push si
		;mov si,offset TEMPDX
		;add al,[si+1]		; AL=HEIGHT+Y
                add al,byte ptr TEMPDX+1; modification 28 sep 94

		;pop si

		mov fs:[di+5],al	; WRITE LOWER Y POS
		add di,StaticCellLenght

		;--------------------------------------------
		; TO ADD AN EXTRA SEGMENT WHEN NEEDED
		;cmp di,0
		;jne NOEXTRANEEDED

		;push dx
		;mov dx,STATICS2
		;mov fs,dx
		;pop dx
		;--------------------------------------------

NOEXTRANEEDED:

IGNORE_SQR:	add bx,2
		inc dl
		loop NEXTONLINE

		push si
		mov si,offset TEMPDX
		mov dl,[si]
		inc dh
		pop si

		pop cx
		loop NEXTLINEX

ForgetEntry:	pop si
		add si,ScriptEntryLenght	; modification 28 sept 94
		jmp CHKNEXTSCR

COMPOVER:       ; MODIFICATION:
		; Add a NUL descriptor to end sequence
		mov al,0
		mov fs:[di],al
		ret

SCRIPT_COMPILER_NEO    ENDP

        ;-----------------------------------------------------------------
	;-----------------------------------------------------------------
		; This routine will redraw the screen with selective
                ; blocks drawing methode to save time when ever possible.

SelectiveScreenRedraw::
                pushall
                mov dx,DATA
                mov ds,dx
		mov dx,SCREEN
                mov fs,dx
                mov dx,0a000h
                mov gs,dx

                mov bp,25
                mov si,offset ScreenBlocks
                xor di,di

DNextBlock2:    mov dx,40
		push di
DNextBlock:     xor bx,bx

		mov al,[si]
                or al,al	; cmp al,0
                je EraseBlock

                ; Draw block into video memory...
                mov cx,8
DrawBlock:      mov eax,fs:[di+bx]
                mov gs:[di+bx],eax
                add bx,4
                mov eax,fs:[di+bx]
                mov gs:[di+bx],eax
                add bx,140h-4
                loop DrawBlock
                jcxz NextPart

         	; Erase block from video memory...
EraseBlock:     mov cx,8
		xor eax,eax
EraseBlock_:    mov gs:[di+bx],eax
                add bx,4
                mov gs:[di+bx],eax
                add bx,140h-4
                loop EraseBlock_

NextPart:	inc si
                add di,8

		mov cx,dx
                dec dx
                loop DNextBlock

		pop di
                mov cx,bp
                dec bp
                add di,0a00h
                loop DNextBlock2

                popall
                ret

	;---------------------------------------------------------------
        ;---------------------------------------------------------------

        ; The original DRAW_SCREENV1.x was cleaning-up the entire buffer
        ; before drawing the screen into it. Ofcourse, NEODRAWSCREEN
        ; doesn't use this approche but instead draws the screen and
        ; then erase unsed blocks.

        ; The result of the new approche is 108% speed improvement.

AdjustImage::
		pushall
                mov dx,DATA
                mov ds,dx
                mov dx,SCREEN
                mov gs,dx

                mov si,offset ScreenBlocks
                mov bp,25
                xor di,di
                xor eax,eax
                xor bx,bx

NBlock2:        mov dx,40

NBlock:         mov al,[si]
                or al,al	; cmp al,0
                jne NoDelBlock

		mov cx,8
		push bx
DelBlock:	mov gs:[di+bx],eax
                add bx,4
                mov gs:[di+bx],eax
                add bx,140h-4
                loop DelBlock
                pop bx

NoDelBlock:     add bx,8
		inc si
		mov cx,dx
                dec dx
                loop NBlock

		xor bx,bx
                add di,0a00h
                mov cx,bp
                dec bp
                loop NBlock2

         	popall
                ret

;---------------------------------------------------------------------
;---------------------------------------------------------------------

CODE ENDS
END
