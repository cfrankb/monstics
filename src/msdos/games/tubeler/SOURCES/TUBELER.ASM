;----------------------------------------------------------------
;       PHILIPPE STENSTROM'S TUBELER
;       Executive programmer: Francois Blanchette.............
;----------------------------------------------------------------
;----------------------------------------------------------------

CopySeg		Macro Destination,Source
Local		Destination, Source, CS

                push cx
		push dx
                push es
                push fs
                push si

                mov si,0
		mov dx,Source
                mov es,dx
                mov dx,Destination
                mov fs,dx

                mov cx,65536/4
CS:             mov eax,es:[si]
                mov fs:[si],eax
		add si,4
                loop CS

                pop si
                pop fs
                pop es
                pop dx
                pop cx
		ENDM

;----------------------------------------------------------------
;----------------------------------------------------------------

CopySegS	Macro Destination,Source
Local		Destination, Source, CS,CS2

                push cx
		push dx
                push es
                push fs
                push si

                mov si,0
		mov dx,Source
                mov es,dx
                mov dx,Destination
                mov fs,dx

                mov cx,65536/4
CS:             mov eax,es:[si]
		cmp eax,0
                je CS2
                mov fs:[si],eax
CS2:		add si,4
                loop CS

                pop si
                pop fs
                pop es
                pop dx
                pop cx
		ENDM



;----------------------------------------------------------------
; IMPORTANT: This module requiers 94REP & 94STATLB
;----------------------------------------------------------------

PUBLIC ROOM_NAMES
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
EXTERN SENDERRORMESSAGE:PROC
EXTERN LOADROOM:PROC
EXTERN DRAW_SCREEN:PROC
EXTERN DRAWSOMESCREEN:PROC
EXTERN SCRIPT_COMPILER:PROC
EXTERN SCRIPTDATA:BYTE

;-----------------------------------------------------------------
BC 	    EQU 4*8+0
BorderColor EQU BC+BC*100h+BC*10000h+BC*1000000h

LineSize    EQU 20
RowSize	    EQU 12-1
MaxX	    EQU 54+9-5-3+2+6
MaxY	    EQU 63-2
HowManyMcg  EQU 5+4
Ics_Tubeler EQU 33

;----------------------------------------------------------------
ASSUME CS:CODE,DS:DATA,SS:STACK
STACK     SEGMENT STACK
	  DB 400H DUP  (0)
STACK     ENDS
;----------------------------------------------------------------
;----------------------------------------------------------------
DATA      SEGMENT PUBLIC 'DATA'
COPYRIGHT       db "PHILIPPE STENSTROM'S TUBELER:"
	        db "(C) 1994 PHILIPPE STENSTROM & FRANCOIS BLANCHETTE."
PATH           	db 0
Tubeler_MCG    	db "TUBELER.MCG",0
TubLink_TBL    	db "TUBLINK.TBL",0
TubSigns_SSF	db "TUBSIGNS.SSF",0
Intro_scr	db "intro.scr",0
ROOM_NAMES	db "gamemode",0
Tubeler_	db "TUBELER",0
CreatorPS	db "Created by Philippe Stenstrom",0
ProgBy		db "Programmed by Francois Blanchette",0
NumOfPlyTxt	db "How many players? (2,4)? ",0
InternalError	db "Fatal: Execution runtime error. Program halted.$"
SignsTable	db " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
		db "!",34,"/$%?&*()[],.-=+:;_"
                db " abcdefghijklmnopqrstuvwxyz#<>"
EndSignsTable   db -1

		   ;01234567890123456789
_2Ply1		db "Player #1...UP & RG",0
		db "Player #2...DN & LF",0
_4Ply1		db "Player #1........UP",0
		db "Player #2........RG",0
		db "Player #3........DN",0
		db "Player #4........LF",0
CurrentPly	db 0
NumberOfPly	db 0
PlayerNum	db "Player #1.......",0
PlayerTable	db 0,1,2,3
CannotBeDropHereTxt db ", pipes overlaying.",0
WonTxt		db ", won the game!!!",0
BallIsMovingTxt db "Ball is moving.. Please wait!!!",0

align 4
SignsData	db (offset EndSignsTable- offset Signstable)*64 DUP (0)
Tile	       	db HowManyMcg*256 DUP (0)
TileSet	       	db 3000 DUP (0)
TblShape	db 100 DUP (0)
TblBuffer	db 100 DUP (0)
SiPointers	dw offset TileSet
LX		dw 0
LY		dw 0
LASTX		dw 0
LASTY		dw 0
TubeModel	db 0
MX		db 0
MY		db 0
BallX		db 29
BallY		db 29
BallLeft	db -1
BallAim		db 1
BallRight	db -1
ColorIndicator  db 1

		db 64 DUP (128)
Maze		db 64 * 62 DUP (0)
		db 08 * 64 DUP (128)

align 2
RandomPointer	dw 0
RandomTable	db 0,1,2
		db 1,0,2
                db 2,1,0
                db 0,2,1
                db 1,2,0

                db 2,0,1
                db 0,1,0
                db 1,0,2
                db 2,0,1
                db 0,1,2

                db 0,1,2
                db 2,0,1
                db 0,1,2
                db 1,0,2
                db 0,2,1

                db 0,2,1
                db 2,1,0
                db 1,0,2
		db 0,1,2
                db 2,1,0
DATA   ENDS
;----------------------------------------------------------------

SCREEN SEGMENT 'SCREEN' PUBLIC
SCREEN ENDS

STATICS	SEGMENT 'STATICS' PUBLIC
STATICS ENDS

SIGNSEG SEGMENT 'SIGNSEG' PUBLIC
DB 47104 DUP (0)
SIGNSEG ENDS

;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
TUBELER  PROC NEAR
;----------------------------------------------------------------
.386

		call VideoSwitch

;--------------------------------------------------------------
;--------------------------------------------------------------
; 	     	     *** Read All Signs ***
;--------------------------------------------------------------
;--------------------------------------------------------------

                mov bp,offset SignsTable
                mov di,offset SignsData
NextChar:       push di

                ; Place le curseur à (0,0)
                mov bh,0
                mov dx,0
                mov ah,2
                int 10h

                call Convensions
                mov si,bp
                mov al,[si]
                cmp al,-1
                je LastChar
                inc bp

                ; Affiche un character
		mov bl,16
                mov ah,0eh
                int 10h

                pop di
                mov si,0

                call Convensions
                mov cx,8
Tchar:          mov eax,fs:[si]
                mov [di],eax
                mov eax,fs:[si+4]
		mov [di+4],eax
                add si,140h
                add di,8
                loop Tchar
                jmp NextChar
LastChar:

		;-------------------------------------------------
                ;-------------------------------------------------

                ; Chargement de TUBELER.MCG
                mov dx,DATA
                mov ds,dx
                mov es,dx
                mov dx,offset Tubeler_Mcg
                mov bx,offset Tile
		mov cx,HowManyMcg*256
                call LoadOLD

                ; Chargement de TUBLINK.TBL
                mov dx,DATA
                mov ds,dx
                mov es,dx
                mov dx,offset TubLink_TBL
                mov bx,offset TileSet
		mov cx,3000
                call LoadNew

                ; Chargement de TUBSIGNS.SSF
                mov dx,DATA
                mov ds,dx
                mov dx,SIGNSEG
                mov es,dx
                mov dx,offset TubSigns_SSF
                mov bx,0
                mov cx,47104
                call LoadNew

                ;--------------------------------------------------------
                ;--------------------------------------------------------
		;--------------------------------------------------------
		; The part that I will be adding below will serve to
                ; make the intro for Tubeler. This game must have a
                ; cute intro. For the most part because the introduction
                ; is an important part of the game.
                ;--------------------------------------------------------
		;--------------------------------------------------------
                ;--------------------------------------------------------

		; Chargement de GAMEMODE.LIB
                call Convensions
                mov cx,0
                call LoadRoom

ResetProgram:   ; Chargement de INTRO.SCR
                mov dx,Data
                mov ds,dx
                mov es,dx
                mov dx,offset INTRO_SCR
                mov bx,offset ScriptData
                mov cx,200
                call LOADNEW

		call Script_Compiler
                call Draw_Screen
                CopySeg Statics,Screen

		;--------------------------------------------------------
		;--------------------------------------------------------
		;--------------------------------------------------------
                call ClearMaze

                mov al,byte ptr BallX
                mov byte ptr MX,29

                mov al,byte ptr BallY
                inc al
                mov byte ptr MY,29

                call DrawMaze
		CopySegS Screen,Statics

                call Convensions

                mov si,offset TUBELER_
                mov di,6*0a00h+3*16

DrawNextSSF:    mov al,[si]
		cmp al,0
                je EndDraw_
                push di

                mov bx,offset SIGNSTABLE
ST1MATCH:       cmp al,[bx]
		je FoundMatchST1
                inc bx
                jmp ST1MATCH

FoundMatchST1:	sub bx,offset SIGNSTABLE
		shl bx,10

		mov dx,32
VSweep:         mov cx,32

HSweep:         mov al,es:[bx]
                cmp al,0
                je ItIsZero
                and al,1
                add al,ics_Tubeler
                mov gs:[di],al
                mov gs:[di+140h],al
ItIsZero:       inc bx
                inc di
                loop HSweep

        	add di,140h*2-32
                mov cx,dx
                dec dx
                loop VSweep

		pop di
                add di,32
		inc si
                jmp DrawNextSSF

EndDraw_:

		mov di,16*0a00h+6*8
                mov si,offset CREATORPS
                mov ah,1
                call WriteText

		mov di,18*0a00h+4*8
                mov si,offset PROGBY
                mov ah,0
                call WriteText
		call DrawSomeScreen

                mov cx,1000
                call Pause

		CopySeg Screen,Statics

                ;----------------------------------------------------
                ; This portion of the program will make allocation
                ; of player a charm. Well, as soon as get it to work
                ; that is. In the mean time, stick to you boots.
                ;----------------------------------------------------

                mov di,6*0a00h+8*8
                mov si,offset NumOfPlyTxt
                mov ah,15
                call WriteText
		call DrawSomeScreen

HowManyPlayers_:call Getax
                cmp al,"2"
                je NumAccepted
                cmp al,"4"
                je NumAccepted
                jmp HowManyPlayers_

NumAccepted:	sub al,30h
		mov byte ptr NumberOfPly,al

		xor cx,cx
                mov cl,al

                mov si,offset _2Ply1
                mov di,8*0a00h+8*8
                mov ah,1
                cmp cx,4
                jne _2PlyGame

                mov si,offset _4Ply1

_2PlyGame:      push cx
		push di
                push si
		call WriteText
                pop si
                pop di
                pop cx
                add di,0a00h*2
                add si,20

                inc ah
                loop _2PlyGame

                call DrawSomeScreen
		mov cx,19000
		call Pause

                ;-----------------------------------------------------
                ;-----------------------------------------------------

		;*****************************************************

		;-----------------------------------------------------
		;-----------------------------------------------------
		mov cx,0
                call LoadRoom

                call Draw_Screen
		CopySeg Statics,Screen
                ;------------------------------------------------------
                ;------------------------------------------------------


GameModule:     call Convensions

		; Restore ball at center (29,29) position
                mov byte ptr BallY,29
                mov byte ptr BallX,29
                mov byte ptr BallAim,1

                call ClearMaze

                mov al,byte ptr BallX
                mov byte ptr MX,al

                mov al,byte ptr BallY
                inc al
                mov byte ptr MY,al

		mov si,offset TileSet + 200
InputNewTube:   mov di,offset TblShape
                mov cx,100
CopyShape:      mov al,[si]
                mov [di],al
                inc si
                inc di
                loop CopyShape
                call AdjustPosition

Redraw:         mov si,offset TblShape
                call DrawMaze
                call DrawPipe
                call DrawBallIfNeeded
                CopySegS Screen,Statics
                call DrawMap
                call DrawTubeOnMap

                mov si,offset PlayerNum
                mov di,23*0a00h+8
                mov ah,byte ptr CurrentPly
                inc ah
                call WriteText

                call DrawAimArrow
                call Redraw_screen

MainLoop:       push dx
		mov dx,0a000h
		mov gs,dx
		call DrawBallOnMap
                call Convensions
                pop dx

		inc byte ptr TubeModel
                cmp byte ptr TubeModel,30
                jne NotAboveMax
	        mov byte ptr TubeModel,0
NotAboveMax:
		call Getax
                cmp al,"g"
                je Rotate
                cmp al,13
                je Drop
                cmp al,"4"
                je Left
                cmp al,"6"
                je Right
                cmp al,"8"
                je Up
                cmp al,"2"
                je Down
                jmp MainLoop

Left:		cmp byte ptr MX,0
                je MainLoop
                dec byte ptr MX
                jmp Redraw

Right:          mov al,byte ptr MX
		mov ah,0
                add ax,5
                add ax,word ptr LastX
                inc ax
                cmp ax,MaxX
                ja MainLoop
                inc byte ptr MX
                jmp Redraw

Up:		cmp byte ptr (MX+1),1
		jbe MainLoop
                dec byte ptr (MX+1)
                jmp Redraw

Down:           mov al,byte ptr MY
		mov ah,0
                add ax,RowSize-9
                add ax,word ptr LastY
                inc ax
                cmp ax,MaxY
                ja MainLoop
                inc byte ptr MY
                jmp Redraw

Rotate:		call RotateTube
                call ArrangeTube
                call AdjustPosition
		jmp Redraw

                ;----------------------------------------------------
                ;----------------------------------------------------
Drop:

		;-------------------------------------------------------
                ; As Philippe Explained to me, a pipe cannot overlay
                ; another pipe that has already been installed. So
                ; the add-on routine will check for such an unfortunate
                ; circonstance.
                ;------------------------------------------------------

		call ScanDestination
                cmp bp,-1
                je CannotBeDropHereSorry

                ;-------------------------------------
                ; Draw new pipe on the game board...
		;-------------------------------------

		mov al,byte ptr MX+1
		mov ah,0
                add ax,RowSize-9
                shl ax,6

                add al,byte ptr MX
                add ax,5

                mov di,ax
                add di,offset Maze
                mov si,offset TBLShape

                mov dx,9
D1b:            push di
                mov cx,10

D1a:            mov al,[si]
                cmp al,0
                je NulShapeIgnored

                or al,16
                mov [di],al

NulShapeIgnored:inc si
                inc di
                loop D1a

                pop di
                add di,64
		mov cx,dx
                dec dx
                loop D1b

                ;------------------------------------------------
                ; Assimilate pipe with all other tubes currently
                ; installed on the board.
                ;-----------------------------------------------

                mov cx,64*64
		mov si,offset Maze
IT:             mov al,[si]
		and al,15
                cmp al,0
                je IgnoreTile

                call AdjUp
                call AdjDn
                call AdjLf
                call AdjRg

                mov al,[si]
                and al,127
                mov [si],al

IgnoreTile:	inc si
		loop IT

                ;----------------------------------------------
		; Go for the next player

                inc byte ptr CurrentPly
                mov al,byte ptr NumberOfPly
                cmp byte ptr CurrentPly,al
                jne NotPlayerZero
                mov byte ptr CurrentPly,0

NotPlayerZero:	mov bl,byte ptr CurrentPly
		mov bh,0
                mov si,offset PlayerTable
                mov al,[si+bx]
                add al,30h
                mov di,offset PlayerNum+8
                mov [di],al

		;----------------------------------------------------
                ; Change to New shape for current Tube

                mov al,byte ptr TubeModel
                mov ah,100
                mul ah
		add ax,offset TileSet
              	mov si,ax

                call AdjustPosition

                pusha
                call BallCtrlModule
                popa
                jmp InputNewTube

                ;-----------------------------------------------------

AdjUp:          mov al,[si]
                and al,1
                cmp al,1
                je AdjRet

                mov bx,si
                sub bx,64
		mov al,[bx]
                and al,255-4		; DN=4
                mov [bx],al
AdjRet:         ret

AdjRg:		mov al,[si]
		and al,2
                cmp al,2
                je AdjRet

                mov bx,si
                inc bx
                mov al,[bx]
                and al,255-8		; LF=8
                mov [bx],al
                ret

AdjDn:		mov al,[si]
		and al,4
                cmp al,4
                je AdjRet

                mov bx,si
                add bx,64
                mov al,[bx]
                and al,255-1		; UP=1
                mov [bx],al
                ret

AdjLf:		mov al,[si]
		and al,8
                cmp al,8
                je AdjRet

                mov bx,si
                dec bx
                mov al,[bx]
                and al,255-2		; RG=2
                mov [bx],al
                ret

                ;-----------------------------------------------------
		;-----------------------------------------------------

DrawPipe:	mov di,(RowSize-9)*(0a00h*2)+ 5*16
		mov si,offset TBLShape

                mov dx,9

DP2:		push di
                push dx
                mov cx,10

DP:		push cx

                mov bx,offset Tile + 256
                mov al,[si]
                and al,31
                cmp al,0
		je DATXYZ2b
                mov bx,offset Tile + 512+256

DATXYZ2:        call DrawATube
DATXYZ2b:       pop cx

                add di,16
                inc si
                loop DP

		pop dx
                pop di
                add di,0a00h*2
		mov cx,dx
                dec dx
                loop DP2
		ret

		;-----------------------------------------------
		;-----------------------------------------------

DrawMaze:       mov al,byte ptr MX+1
		mov ah,0
                shl ax,6
                or al,byte ptr MX
                add ax,offset Maze
                mov si,ax
                mov di,0a00h*2+16	; modification

                add si,1+64		; modification
                mov dx,RowSize-2	; modification
DTC2:           push di
                push dx

		mov cx,LineSize-2	; modification

DTC1:		push cx

                mov al,byte ptr MX
                mov ah,0
                mov dx,LineSize
                sub dx,cx
                add dx,ax
                cmp dx,64
                jbe Under64
                mov bx,offset Tile
                jmp DATSonia

Under64:        mov bx,offset Tile + 256
                mov al,[si]
                and al,31
                cmp al,0
		je DATXYZ
                mov bx,offset Tile + 512

DATXYZ:         mov al,[si]
		cmp al,128
		jb DATSonia
		mov bx,offset Tile
DATSonia:	call DrawATube
                pop cx

                add di,16
                inc si
                loop DTC1

		pop dx
                pop di
                add di,0a00h*2
                add si,64-LineSize+2
		mov cx,dx
                dec dx
                loop DTC2
		ret

		;------------------------------------------------------

ArrangeTube:    mov bp,sp
		mov bx,0

                mov si,offset TblShape
		mov dx,10
LookY2:         mov cx,10
LookY:          mov al,[si]
                cmp al,0
                jne LYused
                inc si
                loop LookY

           	mov cx,dx
                dec dx
                loop LookY2

                mov dx,offset InternalError
                jmp SendErrorMessage

LYused:		mov bh,10
		sub bh,dl

                mov si,offset TblShape
                mov dx,10
LookX2:         push si
                mov cx,10

LookX:		mov al,[si]
                cmp al,0
                jne LXused
                add si,10
                loop LookX

                pop si
                inc si
		mov cx,dx
                dec dx
         	loop LookX2

                mov dx,offset InternalError
                jmp SendErrorMessage

LXUsed:		mov bl,10
		sub bl,dl

                mov cx,100
                mov di,offset TBLBuffer
                mov al,0
EmptyBuf:       mov [di],al
                inc di
                loop EmptyBuf

                mov al,bh		; AX = Line* 10
                mov ah,10
                mul ah

		mov si,ax

                mov al,bl
                mov ah,0
                add si,ax
                add si,offset TBLShape

                mov al,10
                sub al,bl
                mov ah,0
                mov word ptr LX,ax


                mov al,10
                sub al,bh
                mov ah,0
                mov word ptr LY,ax

                mov di,offset TBLBuffer



                mov dx, word ptr LY
LYT:            push di
                push si

                mov cx, word ptr LX

LXT:            mov al,[si]
                mov [di],al
                inc si
                inc di
                loop LXT


                pop si
                pop di
                add si,10
                add di,10
                mov cx,dx
                dec dx
		loop LYT

                mov si,offset TBLBuffer
                mov di,offset TBLShape
                mov cx,100

TTT:            mov al,[si]
                mov [di],al
                inc si
                inc di
                loop TTT

                mov sp,bp

         	ret

                ;--------------------------------------------------------
                ;--------------------------------------------------------

RotateTube:     pusha
		mov si,offset TblShape
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
                mov di,offset TblShape
                mov cx,100
TR1:            mov al,[si]
                mov [di],al
                inc si
                inc di
                loop TR1
                popa
                ret

		;------------------------------------------------------
                ;------------------------------------------------------
DrawATube:	; Draw a tile & a tube above that tile, on the screen
		; so it could be seen.
       		;
                ; Parameters:
                ; si: current tube
                ; di: destination on screen
                ;------------------------------------------------------
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

                cmp bx,offset Tile+256
                je NoDrawPipe

                call DrawUpBar
                call DrawRgBar
                call DrawDnBar
                call DrawLfBar

NoDrawPipe:     mov di,bp
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

                ;---------------------------------------------
ClearMaze:	mov cx,64*62
		mov di,offset Maze
                mov al,0
CM:             mov [di],al
                inc di
                loop CM

                mov al,128
		mov di,offset Maze
                mov dx,64
CM2:            push di
                mov cx,5
CM1:            mov [di],al
                inc di
                loop CM1

                pop di
                add di,64
		mov cx,dx
                dec dx
                loop CM2

		mov di,offset Maze
                mov cx,64*3
CMb1:           mov [di],al
                inc di
                loop CMb1
                ret

                ;----------------------------------------------------------
                ;----------------------------------------------------------

LowerPositions: pusha
		mov bp,sp

		mov si,offset TBLshape+90
		mov dx,10

FLY2:           push si
                mov cx,10

FLY1:           mov al,[si]
                cmp al,0
                jne FoundLastY
                inc si
		loop FLY1

                pop si
                sub si,10
                mov cx,dx
                dec dx
                loop FLY2

                mov dx,offset InternalError
                jmp SendErrorMessage

FoundLastY:     dec dx
		mov word ptr LastY,DX

                ;--------------------------------------

		mov si,offset TBLShape+99
                mov dx,10

FLX2:           push si

		mov cx,10
FLX1:           mov al,[si]
                cmp al,0
                jne FoundLastX

		sub si,10
                loop FLX1

                pop si
                dec si
                mov cx,dx
                dec dx
		loop FLX2

FoundLastX:	dec dx
		mov word ptr LastX,DX

                mov sp,bp
                popa
                ret

		;----------------------------------------------------------
                ;----------------------------------------------------------

AdjustPosition:	call LowerPositions

TryX:		mov al,byte ptr MX
                mov ah,0
		add ax,5
                add ax,word ptr LastX

                cmp ax,MaxX
                jbe OkForX
                dec byte ptr MX
                jmp TryX


OkForX:		mov al,byte ptr MY
		mov ah,0
                add ax,RowSize-9
                add ax,word ptr LastY

                cmp ax,MaxY
                jbe OkForY
                dec byte ptr MY
                jmp OkForX
OkForY:		ret

		;-------------------------------------------------------
		;-------------------------------------------------------

DrawBallIfNeeded:

		call Convensions
		mov bl,byte ptr BallX
                sub bl,byte ptr MX
                add bl,5
                cmp bl,LineSize
                jae ForgetAboutBall

                cmp bl,0
                je ForgetAboutBall
                cmp bl,LineSize-1
                je ForgetAboutBall

                mov al,byte ptr BallY
                sub al,byte ptr MY
                add al,3
                cmp al,RowSize
                jae ForgetAboutBall
                cmp al,0
                je ForgetAboutBall
                cmp al,RowSize-1
                je ForgetAboutBall

                mov ah,0ah*2
                mul ah
                shl ax,8

                mov bh,0
                shl bx,4

                mov di,ax
                add di,bx
                mov si,offset Tile + 4*256

                mov dx,16
DBIN2:          mov cx,16

DBIN:		mov al,[si]
                cmp al,0
                je IgnoreBlackPix
                mov gs:[di],al
IgnoreBlackPix: inc si
                inc di
                loop DBIN

                add di,140h-16
                mov cx,dx
                dec dx
                loop DBIN2
ForgetAboutBall:ret

		;--------------------------------------------------------
                ;--------------------------------------------------------

WriteText:      call Convensions

WriteNextChar:
		mov al,[si]
		cmp al,0
                je OutWriteText

                mov bx,offset SignsTable
ChkAgain:       cmp al,[bx]
                je SignMatch
                inc bx
                jmp ChkAgain

SignMatch:	push di

		sub bx,offset SignsTable
                rol bx,6
                add bx,offset SignsData

                mov dx,8
WT2:            mov cx,8
WT1:            mov al,[bx]
                cmp al,0
                je NulPix_WT
                mov gs:[di],ah
NulPix_WT:	inc bx
		inc di
                loop WT1

                add di,140h-8
        	mov cx,dx
                dec dx
                loop WT2

		pop di
                add di,8
                inc si
                jmp WriteNextChar

OutWriteText:	ret

                ;---------------------------------------------------------
                ;---------------------------------------------------------
                ;---------------------------------------------------------

ScanDestination:
		mov bp,0

                mov al,byte ptr MY
		mov ah,0
                add ax,RowSize-9
                shl ax,6

                mov bl,byte ptr MX
                mov bh,0
                add bx,5

                mov si,offset Maze
                add si,ax
                add si,bx

                mov bx,offset TBLShape

                mov dx,10
SDest2:         mov cx,10

SDest:          mov al,[bx]
                cmp al,0
                je IgnoreEmpTile

                mov al,[si]
		cmp al,0
                je IgnoreEmpTile

                mov bp,-1

IgnoreEmpTile:  inc si
		inc bx
                loop SDest

                add si,64-10
		mov cx,dx
                dec dx
		loop SDest2

                ret

		;----------------------------------------------------
                ;----------------------------------------------------
                ;----------------------------------------------------

CannotBeDropHereSorry:

		mov si,offset TblShape
                call DrawMaze
                call DrawPipe
                CopySegS Screen,Statics
                call DrawBallIfNeeded
                call DrawMap

                mov si,offset PlayerNum
                mov di,23*0a00h+8
                mov ah,byte ptr CurrentPly
                inc ah
                call WriteText

                mov si,offset CannotBeDropHereTxt
                call WriteText
                call DrawAimArrow
                call Redraw_screen
                jmp MainLoop


		;---------------------------------------------------------
                ;---------------------------------------------------------

BallCtrlModule:	mov cx,10
BallMakesMove:  push cx

		mov al,byte ptr BallX
                ;add al,5
                ;sub al,10
                mov byte ptr MX,al

                mov al,byte ptr BallY
                inc al
                ;add al,3
                ;sub al,5
                mov byte ptr MY,al

                call DrawMaze
                call DrawBallIfNeeded
                CopySegS Screen,Statics
                call DrawMap

                mov si,offset BallIsMovingTxt
                mov di,23*0a00h+8
                mov ah,0
                call WriteText

                call DrawAimArrow
                call Redraw_screen

                mov al,byte ptr BallY
                mov ah,0
                add ax,3
                shl ax,6

		mov bl,byte ptr BallX
		mov bh,0
                add bx,5

                mov si,ax
                add si,bx
                add si,offset Maze

                ;------------------------------------------------
                ;------------------------------------------------

                mov al,byte ptr BallAim
                shr al,1
                cmp al,0
                jne Not8_

                mov al,8
Not8_:		mov byte ptr BallLeft,al

		mov al,byte ptr BallAim
                shl al,1
                cmp al,16
                jne Not1_

     		mov al,1
Not1_:		mov byte ptr BallRight,al

                ;-------------------------------------------------------
                ; Dans un premier temps, je dois vérifié le nombre
                ; d'ouverture de tuyau possible à l'emplacement de
                ; la boule.
                ;-------------------------------------------------------

                mov dx,0
                mov cx,3
                mov bx,0

                ;---------------------------------------------------------
                ; ReportDir vérifie la position de la balle ainsi
                ; que la position potentiel de celle-ci. Il génère
                ; par la suite un résultat dans l'un des registres
                ; suivant.

                ; or al,1: Si le chemin à même la case est bloqué.
                ; or al,2: Si le chemin à partir de la case destination
		;          est bloqué.
                ; or ah,1: Si la destination est un tuyau.
                ; or ah,destination: Si la destination est un "rebounce".
                ;---------------------------------------------------------

ChkNextDirBall: call ReportDir

		cmp al,0
                jne PathBlocked

                ; Si le chemin n'est pas bloqué alors vérifions si la
                ; case destination est un tuyau.

                cmp ah,1
                jne PathBlocked

                ; Si la case destination potentielle est un tuyau et que
                ; le chemin disponible est ouvert alors incrément le
                ; compteur DX.

                inc dx

PathBlocked:	inc bx
		loop ChkNextDirBall

                ;---------------------------------------------------------
                ; À ce stade DX contient le nombre de tuyau ouvert étant
                ; potentiel d'orienté la balle.
                ;
                ; Si DX = 0; aucun tuyau ne peut s'approprié la balle,
                ;            elle continuera dans la direction prédéfinie.
                ;    DX > 0; un ou plusieur tuyau(x) peu(ven)t orienter la
                ;            balle. Le système de hassard déterminera
                ;            la destination potentielle.
		;-----------------------------------------------------------

                cmp dx,0
                je GoAhead

TryAgainWithRandom:
		inc word ptr RandomPointer
                cmp word ptr RandomPointer,16
                jbe PointerNotFar
                mov ax,0
                mov word ptr RandomPointer,ax
PointerNotFar:

                mov bx,word ptr RandomPointer
                add bx,offset RandomTable
                mov bl,[bx]
                mov bh,0

                call ReportDir
                cmp ah,1
                jne JJNotThere_
                cmp al,0
                jne JJNotThere_

                add bx,offset BallLeft
                mov al,[bx]
                mov byte ptr BallAim,al

SimplyMoveBall: cmp al,1
                je BallUP_
                cmp al,2
                je BallRG_
                cmp al,4
                je BallDN_

BallLF_:        dec byte ptr BallX
		jmp BallHasMove

BallUp_:	dec byte ptr BallY
		jmp BallHasMove

BallRG_:	inc byte ptr BallX
		jmp BallHasMove

BallDN_:	inc byte ptr BallY
		jmp BallHasMove

JJNotThere_:	jmp TryAgainWithRandom
		;--------------------------------------------



GoAhead:        mov bx,1
		call ReportDir

                ;---------------------------------------------------------
                ; ReportDir vérifie la position de la balle ainsi
                ; que la position potentiel de celle-ci. Il génère
                ; par la suite un résultat dans l'un des registres
                ; suivant.

                ; or al,1: Si le chemin à même la case est bloqué.
                ; or al,2: Si le chemin à partir de la case destination
		;          est bloqué.
                ; or ah,1: Si la destination est un tuyau.
                ; or ah,destination: Si la destination est un "rebounce".
                ;---------------------------------------------------------

                cmp ah,128
                jae SomeoneHasWon

                cmp ah,1
                ja RebounceHandler

		cmp al,0
                jne MoveWithDifficulty

DoBallWalk:     mov al,byte ptr BallAim
                jmp SimplyMoveBall


MoveWithDifficulty:

		mov al,byte ptr BallAim
                xor al,255
                mov ah,[si]
                and ah,al
                mov [si],ah

                mov ah,byte ptr BallAim
		cmp ah,1
                je BallUp2
                cmp ah,2
                je BallRg2
                cmp ah,4
                je BallDn2

BallLf2:	dec si
		jmp BallDi2

BallUp2:	sub si,64
		jmp BallDi2

BallRg2:	inc si
		jmp BallDi2

BallDn2:	add si,64
		jmp BallDi2

                ;--------;
BallDi2:        shl ah,2
		cmp ah,8
                jbe NoSubXYZ_2

                shr ah,4
NoSubXYZ_2:	xor ah,255
		mov al,[si]
                and al,ah
                mov [si],al
                jmp DoBallWalk





RebounceHandler:

		;---------------------------------------------
BallHasMove:    mov dx,0a000h
                mov gs,dx
		call DrawMap
                mov cx,40
XXX:            CopySegS Screen,Statics
		call DrawBallOnMap

                loop XXX
                call Convensions
                pop cx
                loop DoBallMove
                ret

DoBallMove:	jmp BallMakesMove

		;------------------------------------------
                ; AL=+0  moving is allowed
                ; AL=-1  moving is conditional

ReportDir:      push bx
		push cx
                push di
		xor cx,cx

		mov al,[si]
                add bx,offset BallLeft
                mov ah,[bx]
                and al,ah
                cmp al,0
                je LookFurther

                or cl,1

LookFurther:    mov di,si
		cmp ah,1
                je BallUp
                cmp ah,2
                je BallRg
                cmp ah,4
                je BallDn

BallLf:		dec di
		jmp BallDi

BallUp:		sub di,64
		jmp BallDi

BallRg:		inc di
		jmp BallDi

BallDn:		add di,64
		jmp BallDi

                ;--------;
BallDi:         shl ah,2
		cmp ah,8
                jbe NoSubXYZ_

                shr ah,4
NoSubXYZ_:	mov al,[di]
		cmp al,32
                jae SpecialControl

                and al,31
                cmp al,0
                je NoPipeThere
                or ch,1

		and al,ah
                cmp al,0
                je DiFree
                or cl,2
DIFree:
NoPipeThere:

OutNow:         mov ax,cx
                pop di
                pop cx
                pop bx
                ret

SpecialControl:	mov ch,al
		and ch,255-31
                jmp OutNow

                ;--------------------------------------------------------
                ;--------------------------------------------------------

DrawAimArrow:   call Convensions
		mov bx,offset Tile+5*256
		mov al,byte ptr BallAim
TestAl:		cmp al,1
                je DrawArrow
                add bx,256
                shr al,1
                jmp TestAl

DrawArrow:	mov di,22*0a00h+4*140h+37*8

		mov dx,16
DA2_:           mov cx,16

DA1_:           mov al,[bx]
                cmp al,0
                je DDD
                mov gs:[di],al

DDD:            inc di
                inc bx
                loop DA1_

       		add di,140h-16
       		mov cx,dx
                dec dx
                loop DA2_
                ret

                ;------------------------------------------------------
                ;------------------------------------------------------

DrawMap:
		pusha
		mov di,0a00h*2+(19-4)*16
                mov si,offset Maze+2

                mov dx,64
DrawNextPix2:   mov cx,64
DrawNextPix:

                mov ah,0
                mov al,[si]
                cmp al,128
                jae DBlackPix

                cmp al,32
                ja DRebouncePix

                cmp al,0
                jne DTubePix

                mov ah,3*8+3
DBlackPix:
DrawPixHandler:
		mov gs:[di],ah
                inc si
                inc di
                loop DrawNextPix

                add di,140h-64
                mov cx,dx
                dec dx
            	loop DrawNextPix2

                call DrawBallOnMap

                popa
                ret


DTubePix:      	mov ah,4*8+5
		jmp DrawPixHandler

DRebouncePix:	mov ah,2
		jmp DrawPixHandler

		;------------------------------------------------------
                ;------------------------------------------------------

DrawBallOnMap:  pusha
		mov bl,byte ptr BallX
		add bl,3
                mov bh,0

                mov al,byte ptr BallY
                add al,3
                mov ah,14h
                mul ah
                rol ax,4

                mov di,ax
                add di,bx
                add di,0a00h*2+(19-4)*16

                mov al,byte ptr ColorIndicator
                inc al
                cmp al,15
                jbe ColorInLimit
                mov al,0
ColorInLimit:   mov byte ptr ColorIndicator,al

                mov gs:[di],al
                popa
                ret

                ;-------------------------------------------------------
                ;-------------------------------------------------------

DrawTubeOnMap:	pusha
                mov bl,byte ptr MX
		add bl,3
                mov bh,0

                mov al,byte ptr MY
                add al,2
                mov ah,14h
                mul ah
                rol ax,4

                mov di,ax
                add di,bx
                add di,0a00h*2+(19-4)*16

                mov ah,14
                mov si,offset TBLShape

                call LowerPositions

                mov dl,byte ptr LastY
                mov dh,0
                inc dx

DTOM2:          mov cl,byte ptr LastX
                mov ch,0
                inc cx
                push di
                push si

DTOM1:          mov al,[si]
                cmp al,0
                je NulJulieJean

                mov gs:[di],ah

NulJulieJean:	inc di
		inc si
                loop DTOM1

                pop si
                pop di
                add si,10
                add di,140h

                mov cx,dx
                dec dx
                loop DTOM2

                popa
                ret

                ;---------------------------------------------------------
		;---------------------------------------------------------

Pause:          push cx
		mov cx,65536
P1_:            mov ax,ax
                loop P1_
                pop cx
		call GetAx
                cmp ax,0
                jne Unpause
		loop Pause
Unpause:	ret


		;--------------------------------------------------------
		;--------------------------------------------------------

SomeoneHasWon:	cmp byte ptr NumberOfPly,4
		je _4PlyGame

                mov ah,31h
                mov al,byte ptr BallAim
                cmp al,2
                jbe ShowWinner
                mov ah,32h
                jmp ShowWinner

_4PlyGame:	mov ah,31h
		mov al,byte ptr BallAim
TestAgain:      cmp al,1
                je ShowWinner
                inc ah
                shr al,1
                jmp TestAgain

ShowWinner:
                mov byte ptr PlayerNum+8,ah
                CopySegS Screen,Statics

		mov si,offset PlayerNum
                mov di,23*0a00h+8
                mov ah,0
                call WriteText

                mov si,offset WonTxt
                call WriteText
                call Redraw_Screen

                mov cx,10000
                call Pause

                jmp ResetProgram






                ;---------------------------------------------------------
                ;---------------------------------------------------------

CONVENSIONS PROC NEAR

		push dx

                mov dx,DATA
                mov ds,dx

                mov dx,SIGNSEG
                mov es,dx

                mov dx,0a000h
                mov fs,dx

                mov dx,SCREEN
                mov gs,dx

                pop dx
                ret

CONVENSIONS ENDP

		;------------------------------------------------------
                ;------------------------------------------------------







; -----------------------FIN DU PROGRAMME-----------------------
TUBELER    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END     TUBELER                           ; Point d'entree
;---------------------------------------------------------------
