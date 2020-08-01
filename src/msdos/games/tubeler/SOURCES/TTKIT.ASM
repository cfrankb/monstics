;----------------------------------------------------------------
;       The construction kit for PHILIPPE STEMSTRONG'S TUBELER
;       Executive programmer: Francois Blanchette.............
;----------------------------------------------------------------

; This module requiers 94REP

PUBLIC CONVENSIONS
PUBLIC PATH

EXTERN CLS:PROC
EXTERN VIDEOSWITCH:PROC
EXTERN LOADOLD:PROC
EXTERN LOADNEW:PROC
EXTERN GETAX:PROC
EXTERN MAKEPATH:PROC
EXTERN QUIT:PROC
EXTERN NOT_FOUND:PROC
EXTERN MELO_PAINT:PROC

EXTERN FILENAME:WORD
EXTERN OLD_VIDEO_MODE:WORD
EXTERN EXT:PROC
EXTERN WBUT:PROC

HMOUSE  MACRO
        push ax
        mov ax,2
        int 33h
        pop ax
        ENDM

SMOUSE MACRO
       push ax
       mov ax,1
       int 33h
       pop ax
       ENDM

BC 	    EQU 4*8+0
BorderColor EQU BC+BC*100h+BC*10000h+BC*1000000h

;----------------------------------------------------------------
ASSUME CS:CODE,DS:DATA,SS:STACK
STACK     SEGMENT STACK
	  DB 400H DUP  (0)
STACK     ENDS
;----------------------------------------------------------------
;----------------------------------------------------------------
DATA      SEGMENT PUBLIC 'DATA'
COPYRIGHT      db "Tubeler Construction kit (C) 1994 FRANCOIS BLANCHETTE"
PATH           db 0
_TBL	       db ".TBL",0
Save	       db "Save .TBL:$"
Load	       db "Load .TBL:$"
ClearTxt       db "Do you wish to clear maze(Y/N)?$"
Tubeler_MCG    db "Tubeler.MCG",0
TileSet	       db 100 DUP (0)
CD	       db 0
align 4
Tile	       db 1024 DUP (0)
LDX	       dw -1,-1
Name_	       db 8,0
               db 16 DUP (0)
DATA   ENDS
;----------------------------------------------------------------

SCREEN SEGMENT PUBLIC
DB 65535 DUP (0)
SCREEN ENDS

;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
VLAMITS  PROC NEAR
;----------------------------------------------------------------
.386

		call VideoSwitch

                mov dx,Data
                mov ds,dx
                mov es,dx
                mov dx,offset Tubeler_MCG
                mov bx,offset Tile
                mov cx,1024
                call LOADOLD

                mov dx,Screen
                mov gs,dx
                mov cx,65536/4
                mov di,0
                mov eax,00060006h
DrawScr:        mov gs:[di],eax
                add di,4
                loop DrawScr

Restart:	call DrawTiles
                call DrawCD
                call Redraw_screen

                SMOUSE

MainLoop:	call GETAX
                call WBUT
                cmp bx,1
                je PutTile
                cmp bx,2
                je PutTile


                cmp al,"8"
             	je UP
                cmp al,"2"
                je DN
                cmp al,"4"
                je LF
                cmp al,"6"
                je RG
                cmp al,"="
                je SaveTBL
                cmp al,"-"
                je LoadTBL
                cmp al,"c"
                je Clear
                jmp MainLoop


		;--------------------------------------------------

Clear:
		;mov dx,0a000h
		;mov gs,dx
                ;call CLS


                HMOUSE
         	mov dx,offset ClearTxt
		mov ah,9
                int 21h
                SMOUSE

		call Convensions
C2:             call GETAX
		cmp al,"y"
                je C3
                cmp ax,0
                je C2

                HMOUSE
                call DrawTiles
                call Redraw_screen
                SMOUSE
                jmp MainLoop


C3:		mov di,offset TileSet
		mov cx,100
                mov al,0

C1:             mov [di],al
                inc di
                loop C1
                HMOUSE
                call DrawTiles
                call Redraw_screen
                SMOUSE
		jmp MainLoop


                ;-------------------------------------------------------

LoadTBL:	; Set cursor at (0,0)

                HMOUSE
                mov dx,0a000h
                mov gs,dx
                call CLS

		mov bh,0
		mov dx,0
                mov ah,2
                int 10h

		mov dx,Data
                mov ds,dx
                mov dx,offset Load
                mov ah,9
                int 21h

		mov dx,DATA
                mov ds,dx
                mov dx,offset Name_
                mov ah,0ah
                int 21h

		call Convensions
                cmp byte ptr NAME_+1,0
                je Restart

                mov al,byte ptr NAME_+1
                mov ah,0
                add ax,offset NAME_+2
                mov di,ax
                mov si,offset _TBL
                call EXT

                mov dx,DATA
                mov ds,dx
                mov es,dx
                mov dx,offset NAME_+2
                mov bx,offset TileSet
                mov cx,100
                call LoadNew
                jmp Restart


SaveTBL:        ; Set cursor at (0,0)
                HMOUSE
                mov dx,0a000h
                mov gs,dx
                call CLS

		mov bh,0
		mov dx,0
                mov ah,2
                int 10h

		mov dx,Data
                mov ds,dx
                mov dx,offset Save
                mov ah,9
                int 21h

		mov dx,DATA
                mov ds,dx
                mov dx,offset Name_
                mov ah,0ah
                int 21h

		call Convensions
                cmp byte ptr NAME_+1,0
                je Restart

                mov al,byte ptr NAME_+1
                mov ah,0
                add ax,offset NAME_+2
                mov di,ax
                mov si,offset _TBL
                call EXT

                mov dx,DATA
                mov ds,dx
                mov dx,offset NAME_+2
                call MAKEPATH

                mov cx,0
                mov ah,3ch
                int 21h
                jc Not_found

                mov bp,ax
                mov bx,ax

                mov dx,DATA
                mov ds,dx
                mov dx,offset TileSet
                mov cx,100
                mov ah,40h
                int 21h
                jc Not_Found

                mov bx,bp
                mov ah,3eh
                int 21h
                jc Not_found
                jmp Restart


















PutTile:	shr cx,1
                shr dx,1

		cmp cx,word ptr LDX
                jne NoMatch
                cmp dx,word ptr LDX+2
                jne NoMatch
                jmp MainLoop

NoMatch:	mov word ptr LDX,cx
		mov word ptr LDX+2,dx

                cmp cx,10
                jae MainLoop
                cmp dx,10
                jae MainLoop

                rol cx,4
                mov al,dl
                mov ah,0ah*2
                mul ah
                rol ax,8
                add ax,cx
                mov di,ax

                mov ax,word ptr LDX+2
                mov ah,10
                mul ah
                mov si,ax

                mov ax,word ptr LDX
                add si,ax
                add si,offset TileSet


                mov al,byte ptr CD
                or al,16
		cmp bx,1
                je Zero
                and al,15
Zero:           mov [si],al

                HMOUSE
                mov dx,0a000h
                mov gs,dx
                mov bx,offset Tile+256
                cmp al,0
                je ok94
		add bx,256
Ok94:           call DrawATube
                SMOUSE
                jmp MainLoop





		;-----------------------------------------------------

UP:		mov al,byte ptr CD
		xor al,1
ShowCD:         mov byte ptr CD,al
		HMOUSE
                mov dx,0a000h
                mov gs,dx
                call DrawCD
                call Convensions
                SMOUSE
                mov word ptr LDX,-1
                jmp MainLoop

DN:		mov al,byte ptr CD
		xor al,4
                jmp ShowCD

LF:		mov al,byte ptr CD
		xor al,8
                jmp ShowCD

RG:		mov al,byte ptr CD
		xor al,2
                jmp ShowCD



		jmp QUIT


DrawCD:		mov si,offset CD
		mov di,15*16+0a00h*5

                mov bx,offset Tile+256
                mov al,[si]
                cmp al,0
                je ok94b
		add bx,256
Ok94b:
                call DrawATube
                ret

                ;-------------------------------------------------

DrawATube:	; Draw a tile & a tube above that tile, on the screen
		; so it could be seen.

                ; Parameters:
                ; si: current tube
                ; di: destination on screen

		mov bp,di

                ;mov bx,offset Tile
                mov dx,16
DAT2:           mov cx,16/4
DAT:            mov eax,[bx]
                mov gs:[di],eax
                add bx,4
                add di,4
                loop DAT

                add di,140h-16
        	mov cx,dx
                dec dx
		loop DAT2

                call DrawUpBar
                call DrawRgBar
                call DrawDnBar
                call DrawLfBar

                mov di,bp
RetFromCall:    ret


                ;--------------------------------------------------
		; UP BAR
                ;--------------------------------------------------

DrawUpBar:	mov al,[si]
		and al,1
                cmp al,0
                je RetFromCall

              	mov di,bp
CWITHUP:
		mov dx,2
DUB2:           mov cx,16/4
                mov eax,BorderColor
DUB:            mov gs:[di],eax
                add di,4
                loop DUB

                add di,140h-16
                mov cx,dx
                dec dx
                loop DUB2
                ret

DrawRgBar:	mov al,[si]
		and al,2
                cmp al,0
                je RetFromCall

                mov di,bp
                add di,14

CWithRG:        mov cx,16
                mov eax,BorderColor
DLB:            mov gs:[di],ax
                add di,140h
                loop DLB
      		ret

                ;------------------------------------------------------
                ; DN BAR
                ;------------------------------------------------------

DrawDnBar:	mov al,[si]
		and al,4
                cmp al,0
                je RetFromCall

                mov di,bp
                add di,14*140h
                jmp CWITHUP

DrawLfBar:	mov al,[si]
		and al,8
                cmp al,0
                je RetFromCall

                mov di,bp
                jmp CWithRG


                ;-------------------------------------------------
DrawTiles:      call Convensions
                mov di,0
                mov si,offset TileSet

                mov dx,10

DTC2:           push di
                push dx
                mov cx,10

DTC1:		push cx
                mov bx,offset Tile + 256
                mov al,[si]
                and al,31
                cmp al,0
		je DATXYZ
                mov bx,offset Tile + 512

DATXYZ:         call DrawATube
                pop cx

                add di,16
                inc si
                loop DTC1

		pop dx
                pop di
                add di,0a00h*2
		mov cx,dx
                dec dx
                loop DTC2
		ret


		;-----------------------------------------------------
RedrawScreen:
Redraw_Screen:

		pusha
		call Convensions

                mov di,0
                mov cx,65536/4

RS:             mov eax,gs:[di]
                mov fs:[di],eax
                add di,4
                loop RS

                popa
                ret

CONVENSIONS PROC NEAR
		push dx
		mov dx,DATA
		mov ds,dx
                mov dx,0a000h
                mov fs,dx
                mov dx,Screen
                mov gs,dx
		pop dx
		ret
CONVENSIONS ENDP

; -----------------------FIN DU PROGRAMME-----------------------
VLAMITS    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END     VLAMITS                           ; Point d'entree
;---------------------------------------------------------------
