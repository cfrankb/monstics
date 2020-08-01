
TITLE BASIC_REPERTORY

Include c:\masm61\listing\ssfsmac.inc

ASSUME DS:DATA

EXTERN PATH:WORD
EXTERN CONVENSIONS:PROC

PUBLIC CLS
PUBLIC VIDEOSWITCH
PUBLIC LOADOLD,LOADNEW,LOADIMA
PUBLIC LOADOLDX,LOADNEWX
PUBLIC GETAX
PUBLIC MAKEPATH
PUBLIC QUIT,EXIT
PUBLIC MELO_PAINT
PUBLIC NOT_FOUND
PUBLIC MOUSE_DOWN

PUBLIC FILENAME
PUBLIC OLD_VIDEO_MODE
PUBLIC SENDERRORMESSAGE
PUBLIC PAUSE,WBUT,EXT

PUBLIC UNABLETOWRITE
PUBLIC UNABLETOCREAT
PUBLIC STRINGBUFFER
PUBLIC STRINGOVERFLOW

PUBLIC FILEIDCODE
PUBLIC EHANDLERTXT, EHANDLER, ERRORHANDLER
PUBLIC EX_, FX_, GX_

DATA SEGMENT PUBLIC 'DATA'
FILENAME       db 32 DUP (0)
	       db "Warning: FILE NOT FOUND ERROR!",13,10,"$"
MOUSE_DOWN     db "Warning: missing mouse and/or driver.",13,10,"$"
FILES_DOWN     db "Warning: unable to find file.",13,10,"$"
ImaLoadErrorTxt db "Warning: unable to load .IMA file.",10,13,"$"
XCreatTxt	db "Warning: unable to creat file.$",10,13
XWriteTxt	db "Warning: unable to write file.$",10,13
EHandlerTxt	db "Warning: file access error occured.",10,13,"$"
StringOverFlow	db "Warning: string too long exceded buffer$",10,13
StringBuffer	db 256 DUP (0)
ImaSize	       db 0,0
OLD_VIDEO_MODE db 3

align 2
FILEIDCODE	dw 0
ERRORHANDLER 	dw EHANDLER

align 4
EX_		dd 0
FX_		dd 0
GX_		dd 0

DATA ENDS

CODE SEGMENT READONLY PUBLIC 'CODE'

.386

EHANDLER PROC NEAR

	mov dx,offset EHANDLERTXT
        jmp SendErrorMessage

EHANDLER ENDP

VIDEOSWITCH PROC NEAR

                pushall
		mov ah,0fh
		int 10h
		mov dx,DATA
		mov ds,dx
		mov si,offset OLD_VIDEO_MODE
		mov [si],al

		mov ah,0
		mov al,13h
		int 10h
                popall
                ret

VIDEOSWITCH ENDP

LOADNEW PROC NEAR
		  call MAKEPATH
LOADNEWX::	  push bx       ; offset destination
		  push cx       ; nombre d'octets a lire
		  push es       ; segment destination
		  mov al,0
		  mov ah,3dh
		  int 21h
		  jc NOT_FOUND

		  mov bx,ax     ; code d'acces
		  pop ds        ; segment destination
		  pop cx        ; nombre d'octets a lire
		  pop dx        ; offset destination
		  push bx
		  mov ah,3fh
		  int 21h
		  jc NOT_FOUND

		  pop bx        ; fermeture du fichier
		  mov ah,3eh
		  int 21h
		  ret

LOADNEW  ENDP

GETAX PROC NEAR

		    ;-----------------------------------------
		    ; GETAX
		    ; INPUTS:
		    ; no inputs
		    ; OUTPUS:
		    ; return a caracter from the buffer
		    ;-----------------------------------------

		    call NUM_LOCK
		    push bx
		    push dx
		    push ds
		    mov ax,0
		    mov dx,40h
		    mov ds,dx
		    mov dx,word ptr ds:[1ch]
		    mov bx,word ptr ds:[1ah]
		    cmp dx,bx
		    jz GETOUT
		    mov ax,[bx]
		    mov ds:[1ah],dx
GETOUT:             cmp al,27
		    je QUIT

		    pop ds
		    pop dx
		    pop bx
		    ret

NUM_LOCK:	pusha
		push ds
		mov dx,0
		mov ds,dx
		mov si,1047
		mov al,[si]
		and al,255-64-16
		or al,32
		;mov [si],al
		pop ds
		popa
		ret

GETAX ENDP

;------------------------------------------------------------------------

MAKEPATH PROC NEAR

	       pusha
	       mov ax,DATA
	       mov ds,ax
	       mov si,offset PATH
	       mov di,offset FILENAME
TRANS_PATH:    mov al,[si]
	       mov [di],al
	       cmp al,0
	       je AFTERPATH
	       inc si
	       inc di
	       jmp TRANS_PATH
AFTERPATH:     mov si,dx
AFTER_PATH:    mov al,[si]
	       mov [di],al
	       cmp al,0
	       je ENDPATH
	       inc si
	       inc di
	       jmp AFTER_PATH
ENDPATH:       popa
	       mov ax,DATA
	       mov ds,ax
	       mov dx,offset FILENAME
	       ret

MAKEPATH ENDP

;--------------------------------------------------------

LOADOLD PROC NEAR

	  call MAKEPATH
LOADOLDX::push bx      ; offset destination
	  push cx      ; nombre d'octets a lire
	  push es      ; segment destination
	  mov al,0
	  mov ah,3dh
	  int 21h
	  jc NOT_FOUND

	  push ax      ; sauvegarde du code d'acces au fichier
	  mov bx,ax    ; insere le code d'acces dans BX
	  xor cx,cx    ; deplace le pointeur du fichier
	  mov dx,7
	  mov al,0     ; relatif au debut du fichier
	  mov ah,42h
	  int 21h
	  jc NOT_FOUND

	  pop bx         ; retire le code d'acces au fichier
	  pop ds       ; segment destination
	  pop cx       ; nombre d'octets a lire
	  pop dx       ; offset destination
	  push bx      ; sauvegarde le code d'acces
	  mov ah,3fh
	  int 21h
	  jc NOT_FOUND

	  pop bx       ; retire le code d'acces au fichier
	  mov ah,3eh
	  int 21h
	  ret

LOADOLD ENDP

	       ;-------------------------------------------------
	       ; QUIT / NOT_FOUND
	       ; INPUTS:
	       ; no inputs
	       ; OUTPUTS:
	       ; nothing/Warning: missing or write protected file
	       ;-------------------------------------------------

QUIT PROC NEAR
		;mov ah,1
		;int 21h

                ;mov ah,0fh
                ;int 10h
                ;cmp al,03
                ;je Exit

		mov dx,DATA
		mov ds,dx
		mov si,offset OLD_VIDEO_MODE
		xor ax,ax
		mov al,[si]
		int 10h
		xor al,al
                jmp EXIT
		;mov ah,4ch    ; retourne au DOS
		;int 21h
QUIT ENDP

EXIT PROC NEAR
		mov ah,4ch
                int 21h
EXIT ENDP

NOT_FOUND PROC NEAR

                ;mov ah,0fh
                ;int 10h
                ;cmp al,03
                ;je Exit2

		mov dx,DATA
		mov ds,dx
		mov si,offset OLD_VIDEO_MODE
		xor ax,ax
		mov al,[si]
		int 10h

Exit2:		mov ah,9
		mov dx,DATA
		mov ds,dx
		;mov dx,offset FILES_DOWN
                mov dx,offset FILENAME
		int 21h
		mov al,1
                jmp EXIT
		;mov ah,4ch
		;int 21h
NOT_FOUND ENDP

	       ;-----------------------------------------------
	       ; MêLO_PAINT
	       ; INPUTS:
	       ; eax:color
	       ; OUTPUTS:
	       ; full screen redraw
	       ;---------------------------------------------

MELO_PAINT PROC NEAR
	       pusha
	       mov cx,65536/4
	       xor di,di
ML_PAINT_DRAW: mov gs:[di],eax
	       add di,4
	       loop ML_PAINT_DRAW
	       popa
	       ret
MELO_PAINT ENDP

CLS PROC NEAR
		mov eax,0
		jmp MELO_PAINT
CLS ENDP

		;----------------------------------------------
		; EXT:
		; INPUTS:
		; [si] source of extension
		; [di] destination of extension
		;-----------------------------------------------

EXT PROC NEAR
		pusha
		mov cx,6
EXT_:	       	mov al,[si]
		mov [di],al
		inc si
		inc di
		loop EXT_
		popa
		ret
EXT ENDP

	       ; --------------------------------------------
	       ; WBUT
	       ; INPUTS:
	       ; no inputs
	       ; OUTPUTS:
	       ; BX: button ; CX: mouse x ; DX: mouse y
	       ; --------------------------------------------

WBUT PROC NEAR
	       push ax
	       mov ax,3
	       int 33h
	       shr cx,4
	       shr dx,3
	       pop ax
	       ret
WBUT ENDP

		;*************************************************

SENDERRORMESSAGE PROC NEAR
		call CONVENSIONS
		push dx
		call ADJ_VIDEOMODE
		pop dx
		mov ah,9
		int 21h
                jmp EXIT
		;mov ah,4ch
		;int 21h

ADJ_VIDEOMODE:  call CONVENSIONS
		mov ah,0
		mov bx,0
		mov si,offset OLD_VIDEO_MODE
		mov al,[si]
		int 10h
		ret

SENDERRORMESSAGE ENDP


		;---------

PAUSE PROC NEAR
		call GETAX		; Read keyboard
		cmp ax,0		; If a key has been pressed
		jne OUTZZZ		; then exit subroutine.
		push cx
		mov cx,65535
DOWAIT:		mov ax,ax
		mov ax,ax
		loop DOWAIT
		pop cx
		loop PAUSE
OUTZZZ:		ret

PAUSE ENDP

		;--------------------------------------------------
                ;--------------------------------------------------

LOADIMA PROC NEAR
		push es
                push bx

                ; LoadHeader of IMA

                mov bx,Data
                mov es,bx
                mov bx,offset ImaSize
                mov cx,2
                call LoadNew

                call Convensions
		mov dx,offset FileName	; FileName DS:DX
                mov ah,3dh		; Open a file
                mov al,0		; For reading only
                int 21h
		jc ImaLoadError

                mov bp,ax		; BP bears code
                mov bx,ax		; BX bears code too

                mov cx,0
                mov dx,2
                mov al,0
                mov ah,42h
                int 21h
                jc ImaLoadError

                mov bx,bp
                mov dx,Data
                mov ds,dx
                mov al,byte ptr ImaSize	; Size of ImaFile
                mov ah,byte ptr ImaSize+1;will be returned in CX
                mul ah
                rol ax,6
                mov cx,ax

		pop dx			; Destination DS:DX
                pop ds

                mov ah,3fh              ; Read ImaFile
                int 21h
                jc ImaLoadError

		mov bx,bp
                mov ah,3eh
                int 21h
                jc ImaLoadError
                ret

ImaLoadError:	mov dx,offset ImaLoadErrorTxt
		jmp SendErrorMessage

LOADIMA ENDP

UnableToCreat::	mov dx,offset XCreatTxt
		jmp SendErrorMessage

UnableToWrite::	mov dx,offset XWriteTxt
		jmp SendErrorMessage






                ;-------------------------------------------------------
                ;-------------------------------------------------------

CODE ENDS
END
