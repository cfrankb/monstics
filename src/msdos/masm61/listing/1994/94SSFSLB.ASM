
Title SSFS_Drawing_Librairy_V2

Include \masm61\listing\SSFSMAC.INC

Assume CS:Code, DS: Data

Public DRAW_SCREENV1_1
Public MY
Public SCREENSIZE
Public SHOWSSFS
Public ROOM
Public SPRBUFFER
Public ASCIITABLE,ASCIISIGNS

Extern LOADROOM:PROC
Extern LOADNEW:PROC
Extern LOADNEWX:PROC
Extern CONVENSIONS:PROC
Extern STATUS_TABLE:BYTE
Extern CLS:PROC
Extern ROOM_NAMES:BYTE
Extern FILENAME:BYTE
Extern EXT:PROC
Extern MAKEPATH:PROC
Extern MX:BYTE
Extern SCRIPTDATA:BYTE
Extern TEMPDX:BYTE
Extern SENDERRORMESSAGE:PROC

Data Segment public 'Data'
IllegalRoom	db "Fatal: Illegal Room, var ROOM=0$"
MY		db 0
SCREENSIZE	db 25
SHOWSSFS	db 1
align 2
ROOM		dw 0
align 4
SPRBUFFER	db 2048 DUP (0)
ASCIITABLE	db " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
		db "!",34,"/$%?&*()[],.-=+:;_"
                db " abcdefghijklmnopqrstuvwxyz#<>"
EndASCIITable   db -1
ASCIISIGNS	db (offset EndASCIITable- offset ASCIItable)*64 DUP (0)
Data Ends

TEXTSEG SEGMENT PUBLIC 'TEXTSEG'
TEXTSEG ENDS

Screen Segment public 'Screen'
Screen Ends

Fonts Segment public 'Fonts'
Fonts Ends

Statics Segment public 'Statics'
Statics Ends

;Statics2 Segment public 'Statics2'
;db 65535 DUP (0)
;Statics2 Ends

Librairy Segment public 'Librairy'
Librairy ends



Code Segment 'Code' Public ReadOnly

		.486

		;--------------------------------------------------------
		; DRAW_SCREEN V1.1
                ;
                ; Note: This new modified version of Draw_Screen was
                ;       designed to accomodate TWARDIA.EXE whose's
                ;	drawing engine requiered a faster redraw to
                ;       make the game run at reasonable speed.
                ;--------------------------------------------------------
		;--------------------------------------------------------
		;
		; DS:DATA
		; ES:STATICS
		; FS:FONTS
		; GS:SCREENS
                ;
		;------------------------------------------------------

DRAW_SCREENV1_1 PROC NEAR

		; CLEAR BETA BACKGROUND
		mov dx,SCREEN
		mov gs,dx
		call CLS

		; SETUP SEGMENTS

		mov dx,DATA
		mov ds,dx
		mov dx,STATICS
		mov es,dx
		mov dx,FONTS
		mov fs,dx
		mov dx,SCREEN
		mov gs,dx

		mov si,offset MX
		mov dl,[si]

		mov si,0

READNEXTSQR:	mov al,es:[si]
		cmp al,0
		je ENDBACKDRAW
		and al,3
		cmp al,1
		je BACKGROUNDOBJ
NOTIN_PARAM_RET:  add si,8

		;------------------------------------
		; MOFICATION TO ABLE SEGMENT CHANGE
		cmp si,0
		jne READNEXTSQR

		;push dx
		;mov dx,STATICS2
		;mov es,dx
		;pop dx
		;------------------------------------
		jmp READNEXTSQR

		;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		;***************************************

DRAWIFNEEDED:	mov al,es:[si+3]; X POS
		sub al,dl
		cmp al,40
		jae NOTIN_PARAM

		mov bl,es:[si+1]	; ITEM NUM
		mov bh,0
		add bx,offset STATUS_TABLE
		mov ah,es:[si+2]	; STATUS OF ACTivation
		cmp [bx],ah
		jne NOTIN_PARAM

		mov ah,0
		rol ax,3		; [X POS] *8
		mov di,ax

                ; Modification to able MY to be applied to the display
                ; creating a four ways scrolling background
		mov al,es:[si+4]; Y POS
                sub al,byte ptr MY
                cmp al,byte ptr ScreenSize
                jae Notin_Param

                ;cmp al,byte ptr MY
                ;jb NOTIN_PARAM
                ;mov ah,byte ptr MY
                ;add ah,ScreenSize
                ;cmp al,ah
                ;ja NOTIN_PARAM

		;cmp al,19
		;ja NOTIN_PARAM		; Correction 2 avril 1994

		mov ah,0ah
		mul ah			; AX=[Y POS]*0ah
		rol ax,8		; [Y POS]*0a00h
		add di,ax               ; XPOS*8+YPOS*0a00h

		mov bx,es:[si+6]	; FONT
		rol bx,6		; [FONT*64]
		;push dx

		;mov dx,8
		mov bp,8  ;{MAINTENANT BP}
NEXTROW:	mov cx,4

LINEAG:		mov ax,fs:[bx]		; DATA FROM FONTS SEG
                ;mov dx,ax
		and ax,ax
		je XPNULBYTE_
                jne IndDrawALAH

		mov gs:[di],ax
AHIsNul:
XPNULBYTE_:	inc di
RetFromInd:     inc di
                inc bx
                inc bx
		loop LINEAG

		add di,140h-8
		;mov cx,dx
		;dec dx
		mov cx,bp    ; {MAINTENANT BP}
		dec bp
		loop NEXTROW

		;pop dx
		ret

IndDrawALAH:    and al,al
		je ALISNUL
		mov gs:[di],al
ALISNUL:	and ah,ah
		je AHISNUL
                inc di
                mov gs:[di],ah
                jmp RetFromInd



		jmp NOTIN_PARAM


NOTIN_PARAM:	ret

		;****************************************
		;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

BACKGROUNDOBJ:	call DRAWIFNEEDED
		jmp NOTIN_PARAM_RET


ENDBACKDRAW:    mov bp,STATICS
		mov es,bp
		mov si,offset MX
		mov dl,[si]
		mov si,0

		;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


LOWSECTDRAW:	mov dh,0

NEXTLINE:	mov bp,STATICS
		mov es,bp
		mov si,0

NEXTSQRINFORWARD:mov al,es:[si]			; DESCRIPTOR
		cmp al,0
		je ANOTHERLINE
		and al,3
		cmp al,2
		jne NOTINFORWARD

		mov al,es:[si+5]		; LOWER Y POS
                sub al,byte ptr MY
		cmp al,dh
		je DRAWINFORWARD

NOTINFORWARD:	add si,8
		;cmp si,0
		;jne NEXTSQRINFORWARD

		;mov bp,STATICS2
		;mov es,bp
		jmp NEXTSQRINFORWARD

ANOTHERLINE:   	cmp dh,byte ptr ScreenSize
		ja LEAVEFORWARD

		call DRAWACTORS

		inc dh
		jmp NEXTLINE

DRAWINFORWARD:  call DRAWIFNEEDED
		jmp NOTINFORWARD

LEAVEFORWARD:   mov bp,STATICS
		mov es,bp

		mov si,0

READNEXTDEF:	mov al,es:[si]		; DESCRIPTOR BYTE
		cmp al,0
		je ENDDRAWPROC
		and al,3
		cmp al,3
		je MAXPRIORITY
FORGETABOUTIT:	add si,8
		cmp si,0
		;jne READNEXTDEF

		;mov bp,STATICS2
		;mov es,bp
		jmp READNEXTDEF

MAXPRIORITY:    call DRAWIFNEEDED
		jmp FORGETABOUTIT

ENDDRAWPROC:	ret

		;--------------------------------------------------
DRAW_SCREENV1_1 ENDP

		;--------------------------------------------------
		;*------------------------------------------------*
		;--------------------------------------------------

DrawActors PROC NEAR
                cmp byte ptr SHOWSSFS,0
                je RetOut
RetOut:		ret
DrawActors ENDP



		;---------------------------------------------------
                ;---------------------------------------------------

COMMON	PROC NEAR

		;--------------------------------------------------------

COMMON ENDP

Code Ends
     END