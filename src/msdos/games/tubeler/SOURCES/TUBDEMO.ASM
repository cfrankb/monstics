;----------------------------------------------------------------
;       PHILIPPE STEMSTRONG'S TUBELER DEMO
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
EXTERN EXT:WORD

BC 	    EQU 4*8+0
BorderColor EQU BC+BC*100h+BC*10000h+BC*1000000h
SBC	    EQU 3
SBorderColor EQU SBC+SBC*100h+SBC*10000h+SBC*1000000h


;----------------------------------------------------------------
ASSUME CS:CODE,DS:DATA,SS:STACK
STACK     SEGMENT STACK
	  DB 400H DUP  (0)
STACK     ENDS
;----------------------------------------------------------------
;----------------------------------------------------------------
DATA      SEGMENT PUBLIC 'DATA'
PATH           	db "c:\tubeler\",0
Tubeler_MCG    	db "Tubeler.MCG",0
TubLink_TBL    	db "TubLink.TBL",0
align 4
Tile	       	db 1024 DUP (0)
TileSet	       	db 3000 DUP (0)
SiPointers	dw offset TileSet
TBLBuffer	db 100 DUP (0)

DATA   ENDS
;----------------------------------------------------------------

SCREEN SEGMENT PUBLIC
DB 65535 DUP (0)
SCREEN ENDS

;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
TUBELER  PROC NEAR
;----------------------------------------------------------------
.386

		call VideoSwitch


                mov dx,DATA
                mov ds,dx
                mov es,dx
                mov dx,offset Tubeler_Mcg
                mov bx,offset Tile
		mov cx,1024
                call LoadOLD

                mov dx,DATA
                mov ds,dx
                mov es,dx
                mov dx,offset TubLink_TBL
                mov bx,offset TileSet
		mov cx,3000
                call LoadNew



                call Convensions
Redraw:         mov si,word ptr SiPointers
		call DrawTiles
                call Redraw_Screen

M:              call GETAX
  		cmp al,"n"
                je Next
                cmp al,"b"
                je Back
                cmp al,"g"
                je Rotate

                jmp M

Back:		mov ax,word ptr SiPointers
                cmp ax,offset TileSet
		je M
                mov ax,word ptr SiPointers
                sub ax,100
                mov word ptr SiPointers,ax
                jmp Redraw


Next:		mov ax,word ptr SiPointers
		add ax,100
                mov word ptr SiPointers,ax
                jmp Redraw

		;---------------------------------------------------
Rotate:		mov si,word ptr SiPointers
		mov di,offset TblBuffer +9

                mov dx,10

RT2:            push di
                mov cx,10


RT1:            mov al,[si]
                mov ah,al
                and ah,15
                cmp ah,0
                je EmptySqr

                shl ah,1
                cmp ah,15
                jbe NoSub

                sub ah,15
NoSub:		or ah,16
		mov al,ah

EmptySqr:	mov [di],al

		inc si
                add di,10
                loop Rt1

		pop di
                dec di
                mov cx,dx
                dec dx
                loop RT2

                mov si,offset TblBuffer
                mov di,word ptr SiPointers
                mov cx,100
TR1:            mov al,[si]
                mov [di],al
                inc si
                inc di
                loop TR1

                jmp Redraw


		;-----------------------------------------------------











                jmp Quit


                ;-----------------------------------------------------
DrawATube:	; Draw a tile & a tube above that tile, on the screen
		; so it could be seen.
       		;
                ; Parameters:
                ; si: current tube
                ; di: destination on screen
                ;------------------------------------------------------

		mov bp,di

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

                mov dx,SCREEN
                mov gs,dx

                pop dx
                ret

CONVENSIONS ENDP


; -----------------------FIN DU PROGRAMME-----------------------
TUBELER    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END     TUBELER                           ; Point d'entree
;---------------------------------------------------------------
