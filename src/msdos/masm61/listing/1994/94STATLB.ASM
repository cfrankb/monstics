
TITLE STATICS_LIBRAIRY

EXTERN PATH:BYTE
EXTERN CLS:PROC
EXTERN FILENAME:BYTE
EXTERN LOADNEW:PROC
EXTERN NOT_FOUND:PROC
EXTERN CONVENSIONS:PROC
EXTERN EXT:PROC
EXTERN MAKEPATH:PROC
EXTERN SENDERRORMESSAGE:PROC
EXTERN PAUSE:PROC
EXTERN ROOM_NAMES:BYTE

PUBLIC MX
PUBLIC TEMPDX
PUBLIC SCRIPTDATA
PUBLIC SCRIPT_COMPILER
PUBLIC DRAW_SCREEN
PUBLIC REDRAW_SCREEN
PUBLIC LIB_EXT
PUBLIC LIBTEMP
PUBLIC STATUS_TABLE
PUBLIC SCR_EXT
PUBLIC DES_EXT
PUBLIC RESETSEQUENCE
PUBLIC SHOWMOUSE
PUBLIC LDX
PUBLIC MOUSEBUF
PUBLIC DRAWSOMESCREEN
PUBLIC ERASESCREEN
PUBLIC LOADROOM
PUBLIC DRAWMOUSE,DRAWMOUSE2,DRAWMOUSEX,ICONS

;----------------------------------------------------------

DATA SEGMENT PUBLIC 'DATA'
SSFSERRORTEXT	db "Warning: Unable to read .SSF file.$"
MX	       	db 0
LIB_EXT	       	db ".LIB",0
SCR_EXT	       	db ".SCR",0
DES_EXT	       	db ".DES",0
SCRIPTDATA     	db 4096+4 DUP (0)
STATUS_TABLE   	db 256 DUP (0)

		   ;12345678

RAWNAME    	db 16 DUP (0)
CURSOR_ICON	db 0
SHOWMOUSE	db 0

align 4
MOUSEBUF	db 256 DUP (0)
LDX		dw 0,0
MOUSEBUFDI	dw 0
LIBCODE	       	dw 0
SCRIPTCODE     	dw 0
LIBTEMP	       	dw 0,0
TEMPDX	       	dw 0
ICONS		db 256 DUP (0)

DATA ENDS

STATICS SEGMENT PUBLIC 'STATICS'
DB 65535 DUP (0)
STATICS ENDS

LIBRAIRY SEGMENT PUBLIC 'LIBRAIRY'
DB 65535 DUP (0)
LIBRAIRY ENDS

SCREEN SEGMENT PUBLIC 'SCREEN'
DB 65535 DUP (0)
SCREEN ENDS

FONTS SEGMENT PUBLIC 'FONTS'
DB 65535 DUP (0)
FONTS ENDS

;-------------------------------------------------------------------

CODE SEGMENT READONLY PUBLIC 'CODE'

.386

;------------------------------------------------------------------------

RESETSEQUENCE PROC NEAR
		mov dx,STATICS
		mov gs,dx
		call CLS

		;mov dx,STATICS2
		;mov gs,dx
		;call CLS


		ret

RESETSEQUENCE ENDP

		;--------------------------------------------------------
		; DRAW_SCREEN V1.0
		;--------------------------------------------------------
		;
		; DS:DATA
		; ES:STATICS
		; FS:FONTS
		; GS:SCREENS
		;
		;
		;------------------------------------------------------

DRAW_SCREEN PROC NEAR

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

		mov al,es:[si+4]; Y POS
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
		cmp ax,0
		je XPNULBYTE_
		mov gs:[di],ax
XPNULBYTE_:	inc di
                inc di
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

READTOPSECT:	mov al,es:[si]
		cmp al,0
		je ENDTOPSECTDRAW
		and al,2
		cmp al,2
		jne TONEXTTOPSECTOBJ

		mov al,es:[si+5]
		cmp al,10
		jae TONEXTTOPSECTOBJ
		call DRAWIFNEEDED

TONEXTTOPSECTOBJ:add si,8
		cmp si,0
		jne READTOPSECT
		;mov bp,STATICS2
		;mov es,bp
		jmp READTOPSECT

ENDTOPSECTDRAW:

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
		cmp al,dh
		je DRAWINFORWARD

NOTINFORWARD:	add si,8
		cmp si,0
		jne NEXTSQRINFORWARD

		;mov bp,STATICS2
		;mov es,bp
		jmp NEXTSQRINFORWARD

ANOTHERLINE:	cmp dh,26
		je LEAVEFORWARD

		;call DRAWACTORS

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
		jne READNEXTDEF

		;mov bp,STATICS2
		;mov es,bp
		jmp READNEXTDEF

MAXPRIORITY:    call DRAWIFNEEDED
		jmp FORGETABOUTIT

ENDDRAWPROC:	ret

		;--------------------------------------------------












































DRAW_SCREEN ENDP

		;-------------------------------------------------------
		;*******************************************************
		;-------------------------------------------------------







































REDRAW_SCREEN PROC NEAR

		mov dx,SCREEN
		mov fs,dx
		mov dx,0a000h
		mov gs,dx

		mov cx,65536/4
		mov si,0

REDRAWAG:	mov eax,fs:[si]
		mov gs:[si],eax
		add si,4
		loop REDRAWAG
		ret




REDRAW_SCREEN ENDP

SCRIPT_COMPILER  PROC NEAR

		;-------------------------------------------------------
		; SCRIPT_COMPILER V1.0
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

		mov dx,DATA
		mov ds,dx
		mov dx,LIBRAIRY
		mov es,dx
		mov dx,STATICS
		mov fs,dx

		mov si,offset SCRIPTDATA
		mov di,0
		push si

		pop si
		; MODIFICATION
CHKNEXTSCR:	mov al,[si]
		cmp al,0
		je COMPOVER

		push si

		mov al,[si+1]		; OBJ NUM FROM LIB
		mov bl,[si+2]           ; X POS
		mov bh,[si+3]           ; Y POS
		push bx

		mov si,4
SEEKAL_0:	cmp al,0
		je FOUNDOBJ

		add si,6		; Offset 6-7 are start of next font
		mov si,es:[si]
		dec al
		jmp SEEKAL_0

FOUNDOBJ:       mov bx,8
		pop dx

		push si
		mov si,offset TEMPDX
		mov [si],dx
		pop si

		mov cl,es:[si+4]
		mov ch,0

NEXTLINEX:	push cx
		mov cl,es:[si+3]	; offset3: LENGHT
		mov ch,0

NEXTONLINE:	mov al,es:[si+5]	; ignore byte
		cmp al,0
		je NO_PROBLEM

		mov ax,es:[si+bx]
		cmp ax,0
		je IGNORE_SQR

NO_PROBLEM:	mov al,es:[si]		; READ DESCRIPTOR BYTE
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

		push si
		mov si,offset TEMPDX
		add al,[si+1]		; AL=HEIGHT+Y
		pop si

		mov fs:[di+5],al	; WRITE LOWER Y POS
		add di,8

		;--------------------------------------------
		; TO ADD AN EXTRA SEGMENT WHEN NEEDED
		cmp di,0
		jne NOEXTRANEEDED

		push dx
		;mov dx,STATICS2
		;mov fs,dx
		pop dx
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

		pop si
		add si,4
		jmp CHKNEXTSCR

COMPOVER:       ; MODIFICATION:
		; Add a NUL descriptor to end sequence
		mov al,0
		mov fs:[di],al
		ret

SCRIPT_COMPILER    ENDP


		;--------------------------------
		; LOADROOM
		; INPUTS:
		; CX: ROOM NUMBER
		;-------------------------------

LOADROOM PROC NEAR

		call Convensions
		mov dx,DATA
		mov ds,dx

		mov si,offset ROOM_NAMES
		cmp cx,0
		je FOUNDRMPRT

DOCHKAGAIN:
CHKFORNUL:	mov al,[si]
		inc si
		cmp al,0
		jne CHKFORNUL

		loop DOCHKAGAIN

FOUNDRMPRT:	mov bx,si
		mov di,offset RAWNAME
DOCHKXXX:
		mov al,[bx]
		mov [di],al
		cmp al,0
		je FOUNDENDOFSTR
		inc bx
		inc di
		jmp DOCHKXXX

FOUNDENDOFSTR:	mov si,offset SCR_EXT
		;mov di,bx CORRECTION
		call EXT
		push di

		; LOADING ????.SCR
		mov dx,DATA
		mov ds,dx
		mov es,dx
		mov dx,offset RAWNAME
		mov bx,offset SCRIPTDATA
		mov cx,4096
		call LOADNEW

		mov dx,DATA
		mov ds,dx
		mov si,offset LIB_EXT
		pop di
		call EXT

		; READING HEADER OF ????.LIB
		mov dx,DATA
		mov ds,dx
		mov es,dx
		mov dx,offset RAWNAME
		mov bx,offset LIBTEMP
		mov cx,4
		call LOADNEW

		call CONVENSIONS
		mov dx,offset RAWNAME
		call MAKEPATH

		mov dx,DATA
		mov ds,dx
		mov dx,offset FILENAME		; ????.LIB

		mov ah,3dh		; Ouverture
		mov al,0		; Lecture seule
		int 21h
		jc NOT_FOUND

		mov bp,ax		; Passé le code d'accès à BP
		mov bx,ax		; et a BX.

		call CONVENSIONS
		mov si,offset LIBTEMP+2
		mov cx,[si]		; Dimension des données statiques

		mov dx,LIBRAIRY		; Destination [LIBRAIRY:0000]
		mov ds,dx
		mov dx,0
		mov ah,3fh		; Lecture du fichier
		int 21h
		jc NOT_FOUND

		call CONVENSIONS
		mov bx,bp		; Passe le code d'accès à BX
		mov si,offset LIBTEMP
		mov cx,[si]
		rol cx,6

		mov dx,FONTS		; DESTINATION [FONTS:0000]
		mov ds,dx
		mov dx,0
		mov ah,3fh
		int 21h
		jc NOT_FOUND

		mov bx,bp		; Passe le code à BX
		mov ah,3eh		; Fermeture de l'accès au fichier
		int 21h

		call SCRIPT_COMPILER

		ret     		; Fin de la procédure

LOADROOM ENDP


align 2
ERASESEQ	dw 8,0,1,6,2,5,3,7,4

ERASESCREEN PROC NEAR
		mov cx,50
		call PAUSE

		mov dx,0a000h
		mov gs,dx
		mov dx,SCREEN
		mov es,dx
		mov al,0
		mov si,0
		mov bx,0

		mov bp,2
MANIACLAPX_:	mov cx,65536

DODRAWSCREEN_:  mov di,si
		add di,cs:[bx+offset ERASESEQ]
		inc bx
		inc bx
		cmp bx,10 +4
		jne XNULBXAT_
		mov bx,0
XNULBXAT_:

		mov al,0
		mov gs:[di],al
		add si,5+7

		push cx
		mov cx,64/4
WAITFORCORRINE_:loop WAITFORCORRINE_
		pop cx
		loop DODRAWSCREEN_

		mov cx,bp
		dec bp
		loop MANIACLAPX_

		ret
ERASESCREEN ENDP

		;-----------------------

DRAWSOMESCREEN	PROC NEAR

 		mov cx,50
		call PAUSE

		mov dx,0a000h
		mov gs,dx
		mov dx,SCREEN
		mov es,dx
		mov al,0
		mov si,0
		mov bx,0


		mov bp,2
MANIACLAPX:	mov cx,65536

DODRAWSCREEN:  	mov di,si
		add di,cs:[bx+offset ERASESEQ]
		inc bx
		inc bx
		cmp bx,10 +4
		jne XNULBXAT
		mov bx,0
XNULBXAT:

		mov al,es:[di]
		mov gs:[di],al
		add si,5+7

		push cx
		mov cx,64/4
WAITFORCORRINE: loop WAITFORCORRINE
		pop cx
		loop DODRAWSCREEN

		mov cx,bp
		dec bp
		loop MANIACLAPX

		ret

DRAWSOMESCREEN ENDP

































DRAWMOUSEX PROC NEAR
		;pusha

		;mov dx,0a000h
		;mov gs,dx

		mov dx,DATA
		mov ds,dx
		mov si,offset SHOWMOUSE
		mov al,[si]
		cmp al,1
		jne DOEXITDRAWMOUSE


		;mov dx,SCREEN

		mov ax,3	; Lit l'état de la souris
		int 33h

		mov si,offset LDX
		cmp cx,[si]
		jne XLDXMATCH
		cmp dx,[si+2]
		jne XLDXMATCH
		popa
		ret

XLDXMATCH:      push cx
		push dx

		shr cx,1	; X=X/2
		mov bp,cx

		mov al,dl      	; AL=Y
		mov ah,14h     	; AH=14h
		mul ah		; AX=Y*14h
		rol ax,4	; AX=Y*140h

		add ax,cx
		mov di,ax

		mov si,offset CURSOR_ICON
		mov al,[si]
		mov ah,0
		rol ax,8
		mov si,ax
		add si,offset ICONS

		pop dx
		pop cx

		push di
		push si

		push di

		mov si,offset LDX
		mov ax,-1
		cmp [si],ax
		je DOSWEPINBUF

		mov di,[si+4]		; Screen is targeted
		mov si,offset MOUSEBUF	; MouseBuf is the source

		push cx
		mov bx,16
TRANSBUFSCR:	mov cx,16

TRANSFROMBUFTOSCR:mov al,[si]
		inc si
		mov gs:[di],al
		inc di
		loop TRANSFROMBUFTOSCR

		add di,140h-16
		mov cx,bx
		dec bx
		loop TRANSBUFSCR

		pop cx

DOSWEPINBUF:    pop di

		mov si,offset LDX
		mov [si],cx
		mov [si+2],dx
		mov [si+4],di

		mov si,di		; Source from SCREEN
		mov di,offset MOUSEBUF	; Destination in MEM

		mov bx,16		; Portion to copy under
TRANSCRBUF:	mov cx,16		; mouse to protected buffer.
TRANSFERSCRTOBUF:mov al,gs:[si]
		mov [di],al
		inc si
		inc di
		loop TRANSFERSCRTOBUF

		add si,140h-16
		mov cx,bx
		dec bx
		loop TRANSCRBUF

		pop si
		pop di

		mov bx,16
SHEISNOTMYGIRL:	mov cx,16
		push bp

DOMOREFORHER:   cmp di,25*0a00h
		jae DOENDMDRAW
		cmp bp,140h
		je DONOTCONT
		mov al,[si]
		cmp al,0
		je NODRAWOFMOUSE
		mov gs:[di],al

NODRAWOFMOUSE:  inc si
		inc di
		inc bp
		loop DOMOREFORHER

DOELSEFORSOSO:	pop bp
		mov cx,bx
		dec bx
		add di,140h-16
		loop SHEISNOTMYGIRL

DOEXITDRAWMOUSE:popa
		ret

DONOTCONT:	inc si
		inc di
		loop DONOTCONT
		jmp DOELSEFORSOSO

DOENDMDRAW:	pop bp
		popa
		ret

DRAWMOUSEX ENDP

DRAWMOUSE PROC NEAR
		pusha
		mov dx,0a000h
		mov gs,dx
		jmp DRAWMOUSEX
DRAWMOUSE ENDP


DRAWMOUSE2 PROC NEAR
		pusha
		mov dx,SCREEN
		mov gs,dx
		jmp DRAWMOUSEX
DRAWMOUSE2 ENDP










CODE ENDS

END
