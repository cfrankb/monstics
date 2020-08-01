;----------------------------------------------------------------
;       BATTLE LEGAL
;       by Francois Blanchette
;----------------------------------------------------------------

;----------------------------------------------------------------
ASSUME CS:CODE,DS:DATA,SS:STACK
STACK     SEGMENT STACK
          DB 400H DUP  (0)
STACK     ENDS
;----------------------------------------------------------------

;----------------------------------------------------------------
DATA      	SEGMENT
COPYRIGHT  	db "BATTLE LEGAL: (C) 1994 FRANCOIS BLANCHETTE"
PATH		db "c:\wingames\battlelg\",0
FILENAME       	db 32 DUP (0)
MOUSE_DOWN     	db 0
FILES_DOWN     	db "Warning: missing or modified file.$"
PAUSE_TEXT     	db "Press [space] to continue playing...    $"

BATTLELG_BIT   	db "BATTLELG.BIT",0
BLGSIGNS_MCG   	db "BLGSIGNS.MCG",0
BLGSHIPS_SSF   	db "BLGSHIPS.SSF",0
BLGALIEN_SSF   	db "BLGALIEN.SSF",0
BLGSHOOT_SSF	db "BLGSHOOT.SSF",0
HISCORES_BLG	db "HISCORES.BLG",0
ASCII_TABLE    	db " abcdefghijklmnopqrstuvwxyz0123456789",34,"[]'"
OLD_VIDEO_MODE 	db 3


		 ; 01234567890123456789
BATTLE_LEGAL   	db "    battle legal    "
	         ; 0000000000111111111122222222223333333333
		 ; 0123456789012345678901234567890123456789
descriptor     	db "            an action game              "
               	db "         by francois blanchette         "

MODULATOR	db 0
PX		db 0
PY		db 0
CCX		db 256 dup (0)
CCY		db 256 dup (0)
CCT		db 256 dup (0)
CCA		db 256 dup (0)
CCS		db 256 dup (0)
NOA		db 0

;      		MODULATOR 	:GAME MODULATOR
;		PX		:PLAYER X POSITION
;	        PY		:PLAYER Y POSITIOn
;		CCX		:CREATURE X POSITION (0h)
;		CCY		:CREATURE Y POSITION (100h)
;		CCT		:CREATURE TYPE (200h)
;		CCA		:CREATURE AIM (300h)
;		CCS		:CREATURE STAGE (400h)
;		NOA		:NUMBER OF ACTOR

DATA   ENDS
;----------------------------------------------------------------

MEM1 		SEGMENT
FONTS		db 20000 	DUP (0)
PLAYER		db 8192		DUP (0)
ALIENS		db 8192 	DUP (0)
MEM1 	      	ENDS

MEM2 SEGMENT
MEM2 ENDS

BACK SEGMENT
	DB 65535 DUP (0)
BACK ENDS

BUF SEGMENT
DB 65535 DUP (0)
BUF ENDS
;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
VLAMITS  PROC NEAR
;----------------------------------------------------------------
.386

		mov ah,0
                mov al,13h
		int 10h

                ; CHARGEMENT DE BATTLELG_BIT
                mov dx,DATA
                mov ds,dx
                mov dx,BACK
                mov es,dx
                mov dx,offset BATTLELG_BIT
                mov bx,0
		mov cx,65535-0a00h
                call LOADOLD
                jc NOT_FOUND

                ; CHARGEMENT DE BLGSIGNS_MCG
                mov dx,DATA
                mov ds,dx
                mov dx,MEM1
                mov es,dx
                mov dx,offset BLGSIGNS_MCG
                mov bx,offset FONTS
                mov cx,10752
                call LOADOLD
                jc NOT_FOUND

                xor si,si
                mov di,si

                ;--------------------------------------

                ; Normaly (convensions)
                ; DS=: DATA
                ; ES=: MEM1
                ; FS=: MEM2
                ; GS=: 0a000h

		; New cases (cause problems)
                ; DS=: DATA
                ; ES=: MEM1
                ; FS=: MEM2      (MEM2,BACK,BUF   )
                ; GS=: BUFFER    (BUF ,BUF ,0a000h)

	        ;------------------------------------


AGAIN:          mov dx,BACK                ; ES:BACK
                mov ds,dx

                mov dx,BUF
                mov es,dx

		push si

                xor di,di
                mov cx,65536/4
                rep movsd

                call GETAX
                cmp al,27
                je QUIT
                cmp al," "
                je START

                call CONVENSIONS
                mov dx,BUF                   ; GS:BUF
                mov gs,dx                    ; ES:MEM1
                mov dx,MEM1
                mov es,dx
                mov si,offset BATTLE_LEGAL
                mov di,0a00h*(4+5+1)
                call PMCGS

                add di,0a00h*3
                mov si,offset DESCRIPTOR
                call SMCGS
                add si,40
                add di,0a00h
                call SMCGS

                mov dx,BUF
                mov ds,dx

                mov dx,0a000h
                mov es,dx

                xor si,si
                xor di,di
                mov cx,65536/4
                rep movsd

                pop si
		mov di,0
		sub si,140h
                jmp AGAIN

START:          ; CHARGEMENT BLGSHIPS.SSF
		mov dx,DATA
                mov ds,dx
                mov dx,MEM1
                mov es,dx
                mov dx,offset BLGSHIPS_SSF
                mov bx,offset PLAYER
                mov cx,8192
                call LOADNEW
                jc NOT_FOUND

                ; CHARGEMENT BLGALIEN.SSF
                mov dx,DATA
                mov ds,dx
                mov dx,MEM1
                mov es,dx
                mov dx,offset BLGALIEN_SSF
                mov bx,offset ALIENS
                mov cx,8192
                call LOADNEW
                jc NOT_FOUND

                 ; This a beta test routine used to test the ship appering
                 ; for a while.

                 call CONVENSIONS
                 mov si,offset PX
                 mov al,10
                 mov [si],al
                 mov [si+1],al

		;DYSPLAY is the routine purpose to refresh the screen at
		;regular intervals. In the first part, DYSPLAY will
                ;show the stars on the screen.

DYSPLAY:        mov dx,BACK
		mov ds,dx
                mov dx,BUF
                mov es,dx

		pop si
		sub si,140h
                push si
		xor di,di
                mov cx,65536/4
                rep movsd

                CALL CONVENSIONS

                mov dx,BUF
                mov gs,dx

                ; Here is where we will dysplay the ship the player is
                ; controling. This ship used a SSF based data frames.

                mov si,offset PX
                mov al,[si+1]		; AL=[PY]
		mov ah,0ah
                mul ah			; AX= [PY]*0ah
		rol ax,8		; AX= [PY]*0a00h
                mov bl,[si]		; BX= [PX]
                mov bh,0
                rol bx,3                ; BX= [PX]*8
                add ax,bx
                mov di,ax		; DI= [PX]*8+[PY]*0a00h

		mov si,offset PLAYER
                mov dx,32
INTL2:          push di
                mov cx,32
INTL1:          mov al,es:[si]
                cmp al,0
                je XNOTT
                mov gs:[di],al
XNOTT:		inc si
		inc di
                loop INTL1
                pop di
		add di,140h
                mov cx,dx
                dec dx
                loop INTL2

                ; Now lets add






                ; This takes the buffer back to the video memory
                ; buffer.

                mov dx,BUF		; This takes the screen from
                mov ds,dx		; the buffer to the video memory
                mov dx,0a000h           ; locations used to dysplay the
                mov es,dx               ; screen.

                xor di,di
                mov si,di
                mov cx,65536/4
                rep movsd

                call CONVENSIONS

                mov si,offset MODULATOR		; Restore the modulator
                mov al,0                        ; to zero after a screen
                mov [si],al                     ; refresh.

MAIN_LOOP:      mov si,offset MODULATOR
		mov al,[si]
                inc al
                mov [si],al

                cmp al,64
                je DYSPLAY

                mov ah,al
                and ah,255-3
                cmp al,ah
                je PLAYER_MODULE

                jmp MAIN_LOOP


PLAYER_MODULE:  call GETAX
                call CONVENSIONS
                mov si,offset PX
                mov bl,[si]
                mov bh,[si+1]
                cmp al,"8"
                je UP
                cmp al,"4"
                je LEFT
                cmp al,"6"
                je RIGHT
                cmp al,"2"
                je DOWN
		jmp MAIN_LOOP

UP:             cmp bh,0
		je MAIN_LOOP
		dec bh
		jmp MOVE_CTRL

DOWN:		cmp bh,19+2
		je MAIN_LOOP
                inc bh
                jmp MOVE_CTRL

LEFT:		cmp bl,0
		je MAIN_LOOP
                dec bl
                jmp MOVE_CTRL

RIGHT:		cmp bl,36
		je MAIN_LOOP
                inc bl
                jmp MOVE_CTRL

MOVE_CTRL:	mov [si],bl
                mov [si+1],bh
                jmp MAIN_LOOP

                call GETAX
                jmp DYSPLAY

FIRE:		mov si,offset NOA
		mov al,[si]
                mov ah,0
                mov cx,ax

                mov si,offset CCX
                add si,ax

                add bl,4
                add bh,4-4

;      		MODULATOR 	:GAME MODULATOR
;		PX		:PLAYER X POSITION
;	        PY		:PLAYER Y POSITIOn
;		CCX		:CREATURE X POSITION (0h)
;		CCY		:CREATURE Y POSITION (100h)
;		CCT		:CREATURE TYPE (200h)
;		CCA		:CREATURE AIM (300h)
;		CCS		:CREATURE STAGE (400h)
;		NOA		:NUMBER OF ACTOR

                mov [si],bl
	        mov [si+256],bh
                mov al,64
                mov [si+200h], al		; TYPE
                mov al,0
                mov [si+400h], al		; STAGE

                inc cx
                mov si,offset NOA
                mov [si],cl
                jmp MAIN_LOOP

               ;-----------------------------------------
               ; SMCGS
               ;
               ; INPUTS:
               ; [DS:SI] string to be printed
               ; [GS:DI] string destination
               ; [ES]    string caracter source shape
               ;
               ; OUTPUTS:
               ; print a string of small MCG images
               ;------------------------------------------

SMCGS:		pusha
		mov cx,40

AGAINY:         push si
                push cx
                push di

                mov al,[si]
                mov si,offset ASCII_TABLE

SCANASCC:       cmp al,[si]
                je MATCHXX3
                inc si
                jmp SCANASCC

MATCHXX3:       sub si,offset ASCII_TABLE
		rol si,8
                add si,offset FONTS+32

                mov dx,7
MMPIX:          mov cx,8

MPIX:           mov al,es:[si]
                cmp al,0
                je NOTPIX
                cmp al,19
                je NOTPIX
                mov gs:[di],al
NOTPIX:		inc si
		inc si
                inc di
                loop MPIX

                mov cx,dx
                dec dx
                add di,140h-8
                add si,16
                loop MMPIX

                pop di
                pop cx
                pop si
                add di,8
                inc si
                loop AGAINY
                popa
                ret

               ;=================================
               ; PMCGS:
               ; INPUTS
               ; SI: source pointers for string
               ; BH: head Y
               ; OUTPUTS:
               ; print string
               ;================================

PMCGS:         ; CX = string lenght
               ; SI = string pointers

               ;call CONVENSIONS
               ;mov si,offset GRAB_FLOWERS

               pusha
               mov cx,20
               ;mov di,0a00h
LETDOMORE:     mov al,[si]
               push cx
               push si
               push di

               mov di,offset ASCII_TABLE
TRYAGAIN:      cmp al,[di]
               je GOTITXZ
               inc di
               jmp TRYAGAIN

GOTITXZ:       mov ax,di
               sub ax,offset ASCII_TABLE
               xor ah,ah
               rol ax,8
               mov si,offset FONTS
               add si,ax

               pop di
               push di

               mov bx,16
ADDLPIX:       mov cx,16
ADDPIX:        mov al,es:[si]
               cmp al,0
               je XPNTNUL
               mov gs:[di],al
XPNTNUL:       inc di
               inc si
               loop ADDPIX
               mov cx,bx
               dec bx
               add di,130h
               loop ADDLPIX

               pop di
               pop si
               pop cx

               inc si
               add di,16
               loop LETDOMORE
               popa
               ret

               ;==================================
               ; BPMCGS
               ; INPUTS:
               ; SI: source of string
               ; DI: destination of printed string
               ; OUTPUTS:
               ; string printed
               ;===================================

BPMCGS:        pusha
               mov cx,10
LETDOMORE2:    mov al,[si]
               push cx
               push si
               push di

               mov di,offset ASCII_TABLE
TRYAGAIN2:     cmp al,[di]
               je GOTITXZ2
               inc di
               jmp TRYAGAIN2

GOTITXZ2:      mov ax,di
               sub ax,offset ASCII_TABLE
               xor ah,ah
               rol ax,8
               mov si,offset FONTS
               add si,ax

               pop di
               push di

               mov bx,16
ADDLPIX2:      mov cx,16
ADDPIX2:       mov al,es:[si]
               cmp al,0
               je XPNTNUL2
               mov ah,al
               mov gs:[di],ax
               mov gs:[di+140h],ax

XPNTNUL2:      inc di
               inc di
               inc si
               loop ADDPIX2
               mov cx,bx
               dec bx
               add di,(140h*2)-32
               loop ADDLPIX2

               pop di
               pop si
               pop cx

               inc si
               add di,32
               loop LETDOMORE2
               popa
               ret

               ;---------------------------------------------
               ; SOME_TIME_OFF
               ; INPUTS:
               ; AX: number of cycles
               ; OUTPUTS:
               ; delay system for AX cycles
               ;----------------------------------------------

SOME_TIME_OFF: push cx
               mov cx,ax
WAIT_SONIA:    mov ax,ax
               loop WAIT_SONIA
               pop cx
               ;call BYFADE
               ret

               ; --------------------------------------------
               ; WBUT
               ; INPUTS:
               ; no inputs
               ; OUTPUTS:
               ; BX: button ; CX: mouse x ; DX: mouse y
               ; --------------------------------------------

WBUT:          push ax
               mov ax,3
               int 33h
               shr cx,4
               shr dx,3
               pop ax
               ret

               ;-----------------------------------------------
               ; MêLO_PAINT
               ; INPUTS:
               ; eax:color
               ; OUTPUTS:
               ; full screen redraw
               ;---------------------------------------------

MELO_PAINT:    jmp ML_PAINT
CLS:           mov eax,0
ML_PAINT:      pusha
               mov cx,65536/4
               xor di,di
ML_PAINT_DRAW: mov gs:[di],eax
               add di,4
               loop ML_PAINT_DRAW
               popa
               ret

               ;----------------------------------------------
               ; CONVENSIONS
               ; INPUTS:
               ; no inputs
               ; OUTPUTS:
               ; DS:DATA,ES:MEM1,FS:MEM2,GS:a000h
               ;------------------------------------------------

CONVENSIONS:   push dx
               mov dx,DATA
               mov ds,dx
               mov dx,MEM1
               mov es,dx
               mov dx,MEM2
               mov fs,dx
               mov dx,0a000h
               mov gs,dx
               pop dx
               ret


               ;-------------------------------------------------
               ; QUIT / NOT_FOUND
               ; INPUTS:
               ; no inputs
               ; OUTPUTS:
               ; nothing/Warning: missing or write protected file
               ;-------------------------------------------------

QUIT:          mov ah,1
               int 21h

               mov dx,DATA
               mov ds,dx
               mov si,offset OLD_VIDEO_MODE
               xor ax,ax
               mov al,[si]
               int 10h
               xor al,al
               mov ah,4ch    ; retourne au DOS
               int 21h

NOT_FOUND:     mov dx,DATA
               mov ds,dx
               mov si,offset OLD_VIDEO_MODE
               xor ax,ax
               mov al,[si]
               int 10h
               mov ah,9
               mov dx,DATA
               mov ds,dx
               mov dx,offset FILES_DOWN
               int 21h
               mov al,1
               mov ah,4ch
               int 21h

          ;----------------------------------------------------

MAKEPATH:      pusha
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

;--------------------------------------------------------

LOADOLD:  call MAKEPATH
          push bx      ; offset destination
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


;-------------------------------------------------------

LOADNEW:  call MAKEPATH
          push bx       ; offset destination
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

          ;-----------------------------------------------------

PMCG:     pusha       ; Routine generique pour
       ;add si,offset LEVEL_DATA
          mov di,-0a08h
          mov cx,ax
          inc cx        ; AX contient la position X
P01:      add di,8      ; BX contient la position Y
          loop P01
          mov cx,bx
          inc cx
P02:      add di,0a00h
          loop P02
          mov bx,16     ; Boucle centrale d'affichage
P03:      ;mov cx,8      ; BX se fait compteur X
          mov cx,16
          push di       ; CX se fait compteur Y
P04:      ;mov dx,MEM1
          ;mov ds,dx
          mov ax,[si]
          inc si
          ;inc si
          ;and ax,ax
          and al,al
          je P05
          ;mov dx,0a000h
          ;mov ds,dx
          mov gs:[di],ax
P05:      inc di
          ;inc di
          loop P04
          pop di
          add di,0140h
          mov cx,bx
          dec bx
          loop P03
          popa
          ret

               ;=========================================
               ; PAUSE_GAME
               ; No imputs or outputs
               ;=========================================

PAUSE_GAME:    xor dx,dx      ; X=0; Y=0
               xor bh,bh      ; Page d'Çcran =0
               mov ah,2       ; Position le curseur
               int 10h

               mov dx,offset PAUSE_TEXT
               mov ah,9
               int 21h

PGMR:          call GETAX
               and ax,ax
               jne PGMR

PGMRL:         call GETAX
               cmp al," "
               jne PGMRL                          
               ret
               ;jmp MAIN_LOOP

              ;-----------------------------------------
                    ; GETAX
                    ; INPUTS:
                    ; no inputs
                    ; OUTPUS:
                    ; return a caracter from the buffer
                    ;-----------------------------------------

GETAX:		    push bx
                    push dx
                    push ds
                    call NUM_LOCK
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

            ;-------------------------------------
               ; NUM_LOCK
               ; INPUTS:
               ; no inputs
               ; OUTPUTS
               ; NUM LOCK:    true
               ; CAPS LOCK:   false
               ; SCROLL LOCK: false
               ;------------------------------------

NUM_LOCK:      pusha
               push ds
               mov dx,0
               mov ds,dx
               mov si,1047
               mov al,[si]
               and al,255-64-16
               or al,32
               mov [si],al
               pop si
               popa
               ret

               ;------------------------------
               ; LOADSSF
               ; INPUTS:
               ; DS:DX   FILENAME
               ; ES:BX   DESTINATION
               ; CX      NUMBER OF IMAGES
               ; EAX     OFFSET FROM FILE
               ;-----------------------------

LOADSSF:       push cx
               push es
               push bx
               push eax
               call MAKEPATH

               cmp cx,0
               je NOT_FOUND

               mov al,0            ; LECTURE SEULE
               mov ah,3dh          ; OUVERTURE DU FICHIER
               int 21h
               jc NOT_FOUND

               mov bx,ax           ; NUMERO D'ENTRêE
               pop ecx
               mov dx,cx           ; CX:[DX] DÇplacement pointeur
               ror ecx,7           ; [CX]:DX "
               push bx             ; [SAUVEGARDE CODE D'ACCëS]

               mov al,0            ; RELATIF AU DêBUT DU FICHIER
               mov ah,42h          ; DêPLACE LE POINTEUR DU FICHI
               int 21h
               jc NOT_FOUND

               pop bx
               pop dx
               pop ds
               pop cx

PUSH_AGAIN:    pusha

               mov cx,65535
               mov ah,3fh          ; LECTURE DU FICHIER
               int 21h
               jc NOT_FOUND

               popa
               push ds
               pop ax
               add ax,128
               mov ds,ax

               cmp cx,0
               je FIN_LECTURE
               dec cx
               jmp PUSH_AGAIN

FIN_LECTURE:   mov ah,3eh          ; FERMETURE DU FICHIER
               int 21h
               jc NOT_FOUND
               ret

; -----------------------FIN DU PROGRAMME-----------------------
VLAMITS    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END	VLAMITS 			   ; Point d'entree
;---------------------------------------------------------------
