
;---------------------------------------------------------------
;    THE VLAMITS
;    By Francois Blanchette
;---------------------------------------------------------------

SMOUSE         MACRO
               push ax
               mov ax,1
               int 33h
               pop ax
               ENDM

HMOUSE         MACRO
               push ax
               mov ax,2
               int 33h
               pop ax
               ENDM

               ;------------------------------------------------

STACK          SEGMENT STACK
               db 400h DUP (0)
STACK          ENDS

DATA SEGMENT
COPYRIGHT      db "THE VLAMITS: (C) 1993 Francois Blanchette."
MEMBERS        db 0
MOUSE_DOWN     db "Warning: missing mouse and/or driver.$"
FILES_DOWN     db "Warning: missing or modified file.$"
PAUSE_TEXT     db "Press [space] to continue playing...    $"
LEVEL_DATA     db 8192 dup(0)
PATH           db 0
USERS          db "vlausers.mcg",0
ACTORS_MCG     db "vlactors.mcg",0
VLAMITS_MSQ    db "vlamits0.msq",0
VLAMITS_MCG    db "vlagraph.mcg",0
VLAMITS_NUM    db "vlamits1.msq",0
VLASIGNS_MCG   db "vlasigns.mcg",0
VLANIMAT_MCG   db "vlanimat.mcg",0
HISCORES_VLA   db "hiscores.vla",0
LEV00_VLA      db "lev01.vla",0
FILENAME       db 32 dup (0)

TITRE          dw 0605h,0900h ; T
               dw 0a05h,0a00h ; H
               dw 0e05h,0b00h ; E
               dw 060bh,0c00h ; V
               dw 0a0bh,0d00h ; L
               dw 0e0bh,0e00h ; A
               dw 120bh,0f00h ; M
               dw 160bh,1000h ; I
               dw 1a0bh,0900h ; T
               dw 1e0bh,1100h ; S
MAKE_BLUE_FADE db 1,105,104,127,176,177,198,199,255
OLD_VIDEO_MODE db 0

IMAGES_MCG     db 49152 dup (0)
NUMBERS_DATA   db 2560 dup (0)

LIFE_FORCE     db 64
OXYGEN         db 32
TNT            db 0
FLOWERS        db 0
LEVEL_NUMBER   db 0
SCORE          db 8 dup (0)
KEYS           db 0,0,0,0
KEYS_DATA      db 0eh,10h,12h,86h
MX             db 0
MY             db 0

COUNTER        db 0
MCOUNTER       db 0
CFLAG          db 0
CAFLAG         db 0
COAFLAG        db 0
PAFLAG         db 2
PAFFLAG        db 1
PMFLAG         db 1
PCFLAG         db 0
LETFLAG        db 0
INVFLAG        db 0
ODFLAG         db 0
OUTFLAG        db 0
AOMFLAG        db 0
AOFFLAG        db 0
JMPFLAG        db 0
FFLAG          db 0

COSTABLE       db 2,4,1,3
               db 3,1,2,4
               db 4,2,3,1
               db 1,3,4,2
               ;   0123456789012345678901234567890123456789
SORRY          db "sorry you didn't play well enough!",0
WRITE_NAME     db "write name and [enter] when done!",0
ERASEHIS       db "     erase highs scores [yes or no]!    ",0
KEYSELECT      db "  select an actor by pressing [1 to 9]! ",0
SELECT_SPEED   db "       select game speed [1 to 9]!      ",0
CURRENT        db "       current speed is 0",0
TEXT_SP        db 0

ASCII_TABLE   db" abcdefghijklmnopqrstuvwxyz!0123456789",34,"[]'"

                  ;012345678901234567890
CODE_NAMES     db 0
I_THE          db "  the     "
I_VLAMITS      db "  vlamits "
LEVEL          db " level 01 "
GAME_OVER      db "game over!"
YOU_WIN        db "you win!!!"

                  ;12345678901234567890
HIHO           db " highs scores board "

GRAB_FLOWERS   db "  grab the flowers! "
               db "  zoomy zoom zoom!  "
               db "  spiders in realm! "
               db "this is the vlamits!"

               db "prepare for the mega"
               db "the reflex reflexion"
               db "helene made this one"
               db " death your destiny "

               db 255
               db "  punch it arround! "
               db "this is a good stop "
               db " a year has passed! "
               db "   an highs score!  "
               db " hi! hi! hi! ho! ho!"
               db " happy halloween!!! "
               db " merry chrismast!!! "
               db "   april the 1st!   "
               db " save your breath!!!"
               db " this ain't over!!! "
               db "     say cheese!    "
               db 255
MOUSE_CTRL     db 1
HPOINT         db 0
WRITE_HIS      db 0
NO_INTRO       db 0
SPEED          db 1
DATA   ENDS

;----------------------------------------------------------------
MEM1      SEGMENT            
PLAYER_FRAMES  db 20*256 dup (0)
ACTORS_FRAMES  db 20*256 dup (0)
MSQ_TYPE_DATA  db 16384  dup (0)
CCX            db 256    dup (0)
CCY            db 256    dup (0)
CCF            db 256    dup (0)
CCA            db 256    dup (1)
NOA            db 0
CWA            db 0
FONTS          db 43*256 dup (0)
ANIMATIONS     db 6*256  dup (0)
HISCORES       db 40*21  dup (0)

MEM1      ENDS
;----------------------------------------------------------------
MEM2      SEGMENT
db 65535  dup (0)
MEM2      ENDS
;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
VLAMITS  PROC NEAR                                     
;----------------------------------------------------------------

;           INTIALISATION DE LA SOURIS ET DE L'ECRAN
     
     ;-------------------------------------------------------
               .486 

               mov ah,35h
               int 21h
               cmp byte ptr es:[bx],0
               jne YOU_GOT_DRIVER
          
NO_DRIVER:     ;mov dx,data
               ;mov ds,dx
               ;mov dx,offset MOUSE_DOWN
               ;mov ah,9
               ;int 21h

               mov si,offset MOUSE_CTRL
               xor al,al
               mov [si],al
               ;mov ah,4ch
               ;int 21h
               jmp EASY_TO_RUN

YOU_GOT_DRIVER:mov ax,0
               int 33h
               cmp ax,-1
               jne NO_DRIVER  

EASY_TO_RUN:   mov ah,0fh    ; lit le mode vidÈo
               int 10h
               mov dx,DATA
               mov ds,dx
               mov di,offset OLD_VIDEO_MODE 
               mov [di],al   ; sauvegarde l'ancien mode vidÈo

               mov al,13h    
               mov ah,0
               int 10h       ; change le mode vidÈo

               ;///////////////////////////////////////////
               ; PrÇparations relatives Ö l'introduction...
               ;///////////////////////////////////////////
               mov si,offset MEMBERS    ; MEMBERS=0
               mov al,0
               mov [si],al

               ;==========================
               ;Chargement de HISCORES_VLA
               mov dx,DATA
               mov ds,dx
               mov dx,MEM1
               mov es,dx
               mov dx,offset HISCORES_VLA
               mov bx,offset HISCORES
               mov cx,18*40
               call LOADNEW
               jc NOT_FOUND

               ;==========================
               ;Chargement de VLASIGNS.MCG
               mov dx,DATA
               mov ds,dx
               mov dx,MEM1
               mov es,dx
               mov dx,offset VLASIGNS_MCG
               mov bx,offset FONTS
               mov cx,43*256
               call LOADOLD
               jc NOT_FOUND

               ;==========================
               ;Chargement de VLANIMAT.MCG
               mov dx,DATA
               mov ds,dx
               mov dx,MEM1
               mov es,dx
               mov dx,offset VLANIMAT_MCG
               mov bx,offset ANIMATIONS
               mov cx,6*256
               call LOADOLD
               jc NOT_FOUND

               ;=======================
RESTART_GAME:  ;Chargement de USERS.MCG
               mov dx,DATA
               mov ds,dx
               mov es,dx
               mov dx,offset USERS
               mov bx,offset LEVEL_DATA
               mov cx,1400h
               call LOADOLD
               jc NOT_FOUND

               ;=========================
               ;Chargement de VLAMITS.MSQ
               mov dx,DATA
               mov ds,dx
               mov dx,MEM1
               mov es,dx
               mov dx,offset VLAMITS_MSQ
               mov bx,offset MSQ_TYPE_DATA
               mov cx,0a00h*4
               call LOADOLD
               jc NOT_FOUND


               ;==================
               ; SHOW INTRO_SCREEN
               call CONVENSIONS
               mov eax,01010101h
               call MELO_PAINT

               mov si,offset MOUSE_CTRL
               mov al,[si]
               cmp al,0
               je KEYBOARD_INTRO

               ;=================================
               ;Affiche "By Francois Blanchette."
               mov si,offset MSQ_TYPE_DATA
               mov di,17*0a00h
               mov cx,0a00h
CHK_A_PIXEL_FB:mov al,es:[si]
               cmp al,0
               je BLACK_PIXEL_FOR_FB
               mov al,14
               mov ax,di
               and ax,0fh
               or ax,2
               mov gs:[di],al
BLACK_PIXEL_FOR_FB:inc di
               inc si
               loop CHK_A_PIXEL_FB

     ;===================================================
               mov di,offset TITRE-4 ; Affiche le titre du jeu
               mov cx,10             ; en utilisant des graphique
               mov dx,DATA           ; format MGC.
               mov ds,dx
ITK:           xor ax,ax
               xor bx,bx
               add di,4
               mov bl,[di]
               mov al,[di+1]
               mov si,[di+2]
               add si,offset LEVEL_DATA ; modification
P06:           pusha
               ;push ds
               mov di,-0a08h
               mov cx,ax
               inc cx
P07:           add di,8
               loop P07
               mov cx,bx
               inc cx
P08:           add di,0a00h
               loop P08
               mov bx,16
P09:           push di
               mov cx,16
P0A:           ;mov dx,MEM1
               ;mov ds,dx
               mov al,[si]
               and al,al
               je P0B
               ;mov dx,0a000h
               ;mov ds,dx
               mov gs:[di],al
               mov gs:[di+1],al
               mov gs:[di+140h],al
               mov gs:[di+141h],al
P0B:           inc di
               inc di
               inc si
               loop P0A
               pop di
               add di,280h
               mov cx,bx
               dec bx
               loop P09
               ;pop ds
               popa 
               loop ITK

               ;=================================
               ; Affiche neuf membre de la tribue
               mov ax,-1
               mov bx,20
               mov si,-100h
               mov cx,9
S8L1:          add si,100h
               add ax,4
               call PMCG
               loop S8L1

               ;==============================
               ; SELECTION DES MEMBRE DE TRIBU

               SMOUSE

INTROSEL:      call GETAX
               call WBUT      ; Effectue la lecture de la souris
               cmp bx,1
               je LMEM
               ;ja QUIT
               jne INTROSEL

LMEM:          cmp dx,20
               jb INTROSEL
               cmp dx,22
               jae INTROSEL
               mov ax,-1
               mov bx,cx
               xor dx,dx

               mov cx,9
LM01:          add ax,4
               cmp ax,bx
               je CMEM
               inc ax
               cmp ax,bx
               je CMEM
               dec ax
               inc dx
               loop LM01
               jmp INTROSEL

CMEM:          mov si,offset MEMBERS
               mov [si],dl

               mov si,offset MOUSE_CTRL
               mov al,[si]
               cmp al,0
               je B_HMOUSE

               HMOUSE              

B_HMOUSE:      call NEUTRAL_KEYS
               mov bp,sp           ; BP=SP

               ;===================================
               ; Chargement d'un acteur utilisateur

               mov dx,offset USERS
               call MAKEPATH

               mov dx,offset FILENAME   ; USERS.MCG
               xor al,al                ; Lecture seulement
               mov ah,3dh               ; Ouvrir un fichier
               int 21h
               jc NOT_FOUND
               push ax

               mov bx,ax                ; 
               mov si,offset MEMBERS    ; Code de la forme chosie
               xor ax,ax
               mov al,[si]
               inc al
               mov dx,1400h
               mul dx
               add ax,8

               xor cx,cx                ; CX:DX dÇplacement Ö
               mov dx,ax                ; l'intÇrieur du fichier.
               
               xor al,al
               mov ah,42h               ; DÇplace le pointeur du
               int 21h                  ; fichier.
               jc NOT_FOUND

               pop bx
               push bx
               mov dx,MEM1
               mov ds,dx
               mov dx,offset PLAYER_FRAMES
               mov cx,1400h
               mov ah,3fh
               int 21h
               jc NOT_FOUND

               pop bx
               mov ah,3eh
               int 21h
               jc NOT_FOUND

               call CONVENSIONS

               mov si,offset NO_INTRO
               mov al,[si]
               cmp al,0
               jne RETFROMBYFADE
               mov al,1
               mov [si],al

               ;=========================================
               ; Ceci fera changer la couleur de l'Çcran
               mov si,offset MAKE_BLUE_FADE
               xor di,di

               mov bx,8
ONE_MORE_COLOR:mov cx,0
               call GETAX
               call BYFADE
               mov ah,[si]
CHECK_NEXT_PIXEL:mov al,gs:[di]
               cmp al,ah
               jne NOT_THIS_PIXEL
               mov al,[si+1]
               mov gs:[di],al
NOT_THIS_PIXEL:inc di

               ;call BYFADE

               push cx
               mov cx,5
YOU_GOT_TO_WAIT:mov ax,ax
               loop YOU_GOT_TO_WAIT
               pop cx
               loop CHECK_NEXT_PIXEL    
               call BYFADE
               mov cx,bx
               dec bx
               inc si
               loop ONE_MORE_COLOR

               call CLS

               ;================================
               ; L'acteur choisi tombera du ciel

               call CONVENSIONS

               mov si,offset PLAYER_FRAMES
               mov cx,23*8+1
               mov di,19*8

NEXT_BIT_DOWN: push cx
               push di

               mov bx,16
ANOTHER_LINE:  mov cx,4
END_THIS_LINE: mov eax,es:[si]
               mov gs:[di],eax
               add di,4
               add si,4
               loop END_THIS_LINE
               add di,130h
               mov cx,bx
               dec bx
               loop ANOTHER_LINE
               pop di

               mov ax,0d000h
               call SOME_TIME_OFF

               mov cx,4
               xor eax,eax

MORE_BLACK_OUT:mov gs:[di],eax
               add di,4
               loop MORE_BLACK_OUT

               pop cx
               add di,130h
               cmp si,1400h
               jne OK_FRAME_GOOD
               xor si,si
OK_FRAME_GOOD: loop NEXT_BIT_DOWN

               mov si,500h
               mov bl,19
               mov bh,23
               call CUSTOM_INTRO_FRIEND

               ;============================================
               ; Le titre "THE VLAMITS" va maintenant tomber

               mov si,offset MSQ_TYPE_DATA +0a00h
               xor di,di 
               mov bx,11
               
LET_DO_IT_AGAIN:pusha
               mov cx,(3*0a00h)/4
PRINT_TITLE:   mov eax,es:[si]
               mov gs:[di],eax
               add si,4
               add di,4
               loop PRINT_TITLE
               
               mov ax,0d000h
               call SOME_TIME_OFF
               popa

               add di,0a00h
               mov cx,bx
               dec bx
               loop LET_DO_IT_AGAIN

               mov cx,43
               mov ax,0d000h
THIS_WILL_BE_ALL:call SOME_TIME_OFF
               loop THIS_WILL_BE_ALL

               mov bl,19
               mov bh,23
MAKE_FRIEND_MOVE:mov si,0a00h
               call CUSTOM_INTRO_FRIEND
               mov cx,6
JJ_IS_CRAZY:   mov ax,0d000h
               call SOME_TIME_OFF
               loop JJ_IS_CRAZY

               pusha
               mov di,-0a00h*3
               mov cx,0a00h*2
BLACK_ANOTHER: mov al,0
               mov gs:[di],al
               inc di
               loop BLACK_ANOTHER
               popa

               dec bl
               cmp bl,0
               jne MAKE_FRIEND_MOVE

RETFROMBYFADE: call CLS

;--------------------------------------------------------------

;    PARTIE #2: MODULE DE CONTROLE DU JEU...

;----------------------------------------------------------------

               call CONVENSIONS

               mov dx,DATA
               mov ds,dx
               mov es,dx
               mov dx,offset VLAMITS_MCG
               mov bx,offset IMAGES_MCG
               mov cx,49152
               call LOADOLD

               mov dx,DATA
               mov ds,dx
               mov es,dx
               mov dx,offset VLAMITS_NUM
               mov bx,offset NUMBERS_DATA
               ;mov cx,640+960
               mov cx,2560
               call LOADOLD

               mov dx,DATA
               mov ds,dx
               mov dx,MEM1
               mov es,dx
               mov dx,offset ACTORS_MCG
               mov bx,offset ACTORS_FRAMES
               mov cx,6000
               call LOADOLD

               mov dx,DATA
               mov dx,dx
               mov dx,MEM1
               mov es,dx
               mov dx,offset VLASIGNS_MCG
               mov bx,offset FONTS
               mov cx,43*256
               call LOADOLD




               ; ----------------------------------------------
               ; Ajustement gÇnÇral en prÇvision de la 
               ; construction d'une nouvelle partie. Il s'agit 
               ; principalement de remettre Ö zÇro quelques 
               ; registres clefs.
               ; ----------------------------------------------

               call CONVENSIONS

;LIFE_FORCE     db 64
               mov si,offset LIFE_FORCE
               mov al,64
               mov [si],al

;OXYGEN         db 32
               mov si,offset OXYGEN
               mov al,32
               mov [si],al

;TNT            db 0
               xor al,al
               mov si,offset TNT
               mov [si],al

;LEVEL_NUMBER   db 0
               mov si,offset LEVEL_NUMBER
               mov [si],al

;SCORE          db 8 dup (0)
               xor eax,eax
               mov si,offset SCORE
               mov [si],eax
               mov [si+4],eax

;KEYS           db 0,0,0,0
               mov si,offset KEYS
               mov [si],eax

;KEYS_DATA      db 0eh,10h,12h,86h
;MX             db 0
;MY             db 0
;COUNTER        db 0          ; GAME MODULATOR
;CFLAG          db 0          ; CREATURES MODULATOR FLAG
;CAFLAG         db 0          ; CREATURES ANIMATIONS FLAG
;COAFLAG       db 0      ; CREATURES ANIMATIONS MODULATOR FLAG

;PAFLAG         db 2          ; PLAYER ANIMATION FLAG
               mov al,2
               mov si,offset PAFLAG
               mov [si],al

;PAFFLAG        db 1          ; PLAYER AIM FRAME FLAG
               mov al,1
               mov si,offset PAFFLAG
               mov [si],al

;PMFLAG         db 1          ; PLAYER MOVEMENT FLAG
               mov al,1
               mov si,offset PMFLAG
               mov [si],al

;PCFLAG         db 0          ; PLAYER COUNTER FLAG
;LETFLAG        db 0          ; LAST ENERGY TEMPLATE FLAG
;INVFLAG        db 0          ; INVERSE SCREEN FLAG
;ODFLAG         db 0          ; OXYGEN DRAIN FLAG
;OUTFLAG        db 0          ; PLAYER OUT FLAG
;AOMFLAG        db 0          ; ANIMATION OVERFLOW FLAG
;AOFFLAG        db 0          ; ANIMATION OVERFLOW MODULATOR FLAG
;JMPFLAG        db 0          ; JUMP MODULATOR FLAG

               xor al,al
               mov si,offset JMPFLAG
               mov [si],al

;COSTABLE       db 2,4,1,3
;               db 3,1,2,4
;               db 4,2,3,1
;               db 1,3,4,2

;ASCII_TABLE    db " abcdefghijklmnopqrstuvwxyz!0123456789",0

                  ;012345678901234567890


               mov ax,3030h
               mov si,offset LEV00_VLA +3
               mov [si],ax
               mov si,offset LEVEL +7
               mov [si],ax

;CODE_NAMES     db 0
;LEVEL          db "012345601 "
;GAME_OVER      db "game over!"
;YOU_WIN        db "you win!!!"
;GRAB_FLOWERS   db "  grab the flowers!  "

;===============================================================
;         PrÇparation Ö l'entrÇe dans un nouveau tableau
;===============================================================

NEXT_LEVEL:    call CLS
               call CONVENSIONS

               mov si,offset FFLAG
               mov al,1
               mov [si],al

               mov si,offset LEVEL_NUMBER
               mov al,[si]
               inc al
               mov [si],al

               mov bx,3030h
LTAGAIN:       dec al
               inc bl
               cmp al,0
               je LTMATCH

               cmp bl,39h
               ja LTHIGH
               jmp LTAGAIN

LTHIGH:        mov bl,30h
               inc bh
               jmp LTAGAIN

LTMATCH:       mov si,offset LEV00_VLA+3
               mov [si],bh
               mov [si+1],bl

               mov si,offset LEVEL+7
               mov [si],bh
               mov [si+1],bl

               ;-----------------------------------------<<<<

               xor al,al
               mov si,offset TNT
               mov [si],al

               xor eax,eax
               mov si,offset KEYS
               mov [si],eax

               ;==================

               mov si,offset LEVEL
               mov di,8*0a00h
               call BPMCGS

               ; Ceci Ö pour but d'identifiÇ le titre du tableau
               ; et ainsi pouvoir l'afficher.

               xor ax,ax
               mov si,offset LEVEL_NUMBER
               mov al,[si]
               dec al
               mov bl,20
               mul bl

               mov si,ax
               add si,offset GRAB_FLOWERS
               mov al,[si]
               cmp al,255
            je YOU_WIN2

               ;mov si,offset GRAB_FLOWERS
               mov di,15*0a00h
               call PMCGS
               call NEUTRAL_KEYS
               
               mov dx,15
NOP_PST:       mov cx,65535
NOP_ST:        call GETAX
               cmp ax,0
               jne NOP_BR
               loop NOP_ST
               mov cx,dx
               dec dx    
               loop NOP_PST
NOP_BR:



























               ;---------------------------------------------

               ; Chargement de LEV??.VLA
               mov dx,DATA
               mov ds,dx
               mov es,dx
               mov dx,offset LEV00_VLA
               mov bx,offset LEVEL_DATA
               mov cx,8192
               call LOADNEW

               call CONVENSIONS

               ; =============================================
               ; La partie du programme qui suit Ö pour but de
               ; localiser "ply" et d'y placer le joueur.
               ; =============================================

               mov cx,8192
               xor bx,bx
               mov si,offset LEVEL_DATA

CHKMZFPLY:     mov al,[si+bx]
               cmp al,2
               je SQRPLY
               inc bx
               loop CHKMZFPLY
               jmp NOT_FOUND

SQRPLY:        mov al,0
               mov [si+bx],al

               mov al,bl
               and al,127
               mov di,offset MX
               add al,-10
               mov [di],al

               ror bx,7
               add bl,-5
               mov [di+1],bl

               ;=================================================

; CCX          DB 256 dup (0) 
; CCY          DB 256 dup (0)
; CCF          DB 256 dup (0)
; CCA          DB 256 dup (1)
; NOA          DB 0             ; last actor+1
; CWA          DB 0


;================================================================
;              Routine d'identification des crÇatures
;================================================================

               mov cx,8192
               mov si,offset LEVEL_DATA
               mov di,offset CCX
               xor bx,bx

RLVFCRL:       mov al,[si]
               cmp al,77h
               jb XCREA
               cmp al,91h
               ja XCREA
               cmp al,8fh
               jae SCREA
               jmp NCREAC

XCREA:         inc si
               loop RLVFCRL
               mov di,offset NOA
               mov es:[di],bl
               jmp RETNOP

NCREAC:        push cx
               push ax
               add di,bx
     
               ; [CCX+BX]= X       ; POSX 
               mov ax,si
               sub ax,offset LEVEL_DATA
               and ax,127
               mov es:[di],al
               
               ; [CCX+255+BX]= Y   ; POSY
               mov ax,si
               sub ax,offset LEVEL_DATA
               ror ax,7
               mov es:[di+256],al

               ; [CCX+512+BX],     F    ; FORME
               pop cx
               xor ch,ch
               sub cx,77h
               mov ax,cx
               xor ah,ah
               mov dx,3
               div dl              ; AX=FORME
               mov es:[di+512],al

               ; Le "PV" de la crÇature...
               mul dx
               sub cx,ax

               mov al,0
               cmp cl,al
               je WDTYPE

               mov al,34h
               cmp cl,1
               je WDTYPE

               mov al,6
WDTYPE:        mov [si],al
NORCRF:        pop cx
               mov di,offset CCX
               inc bx
               jmp XCREA

               ;=================;

SCREA:         push cx
               push ax
               add di,bx
     
               ; [CCX+BX]= X       ; POSX 
               mov ax,si
               sub ax,offset LEVEL_DATA
               and ax,127
               mov es:[di],al
               
               ; [CCX+255+BX]= Y   ; POSY
               mov ax,si
               sub ax,offset LEVEL_DATA
               ror ax,7
               mov es:[di+256],al

               ; [CCX+512+BX],     F    ; FORME
               pop cx
               xor ch,ch
               ;sub cx,77h
               ;mov ax,cx
               ;mov dx,3
               ;div dx             ; AX=FORME
               ;mov es:[di+512],al

               mov al,8            ; FORM
               mov ah,0            ; PV
               cmp cl,8fh
               je MSCRLIVE
               
               inc al
               mov ah,14h
               cmp cl,90h
               je MSCRLIVE

               inc al
               inc al
               mov ah,0

MSCRLIVE:      mov es:[di+512],al
               mov [si],ah
               jmp NORCRF

RETNOP:

               ;================================================

;COUNTER: game modulator
;CFLAG:   creatures modulator flag
;CAFLAG:  creatures animation flag
;PAFLAG:  player animation flag
;PAFFLAG: player aim frame flag
;PMFLAG:  player movement flag
;PCFLAG:  player counter flag
;LETFLAG: last energy template flag
;INVFLAG: inverse screen flag
;ODFLAG:  oxygen drain flag
;OUTFLAG: player out flag 
;AOFFLAG: animation overflow frame flag
;AOMFLAG: animation overflow modulator flag

               ; ===============================================
               ; Le jeu commence dans la partie ci-dessous; elle
               ; Ö pour d'ajuster l'Çcran en utilisant des 
               ; mÇthodes traditionelles et SSF.
               ; ===============================================

UPDATE_SCREEN: call CONVENSIONS

               ; Let make a master counter to maintain speed
               ; control over everything in this game. MCOUNTER.

               mov si,offset MCOUNTER
               mov al,[si]
               inc al
               mov [si],al

               ; Under this point, is the CREATURES FALLING
               ; ROUTINE requiered to make a creature fall when
               ; it is suspended in the air.

               mov si,offset NOA
               mov cl,es:[si]
               xor ch,ch
               mov bp,offset CCX

CIFNCF:        mov si,bp
               
               mov al,es:[si+512]
               cmp al,8
               je CNOTFLLNG
               cmp al,0
               je CNOTFLLNG

               mov al,es:[si+256]
               xor ah,ah
               rol ax,7            ; AX= Y*128
               add al,es:[si]      ; AX= Y*128+X
               add ax,offset LEVEL_DATA
               mov si,ax

               call GRAVITY
               cmp dl,0
               je CNOTFLLNG
               
               mov si,bp
               mov al,es:[si+256]
               inc al
               mov es:[si+256],al

CNOTFLLNG:     inc bp
               loop CIFNCF

               ; Below this point is the player JUMP and FALL
               ; control routine. These routine were originaly a
               ; a bit higher but were pushed when the creatures
               ; falling routine was added above them.

               mov si,offset JMPFLAG
               mov al,[si]
               cmp al,1
               je BYPFALL

               mov si,offset MX
               mov bl,[si]
               mov bh,[si+1]
               xor ax,ax

               mov al,bh      ; AL= MY
               add al,5       ; AL=MY+5
               rol ax,7       ; AX=(MY+5)*128
               xor bh,bh      ; BL= MX
               add bl,10      ; BX= MX+10
               add ax,bx      ; AX= (MY+5)*128+MX+10
               add ax,offset LEVEL_DATA
               mov si,ax      ; SI=AX

               call GRAVITY
               cmp dl,1
               jne BYPFALL

               call PLAYER_G
               cmp dl,1
               jne BYPFALL

               mov si,offset MX
               mov al,[si+1]
               inc al
               mov [si+1],al

               mov si,offset PAFFLAG
               mov al,[si]
               cmp al,0
               jne NOPAINC
               mov al,1
               mov [si],al

NOPAINC:       mov si,offset PMFLAG
               mov al,1
               mov [si],al

               ; Si le joueur n'est pas en Çtat de chute BYPFALL
               ; se sera intialisÇ permettant de "sauter" par
               ; dessus un chute autrement inÇvitable.
               
BYPFALL:       mov di,offset COUNTER
               mov al,0
               mov [di],al

               ; Ce qui suit affiche le "background" de l'Çcran.
               ; La routine doit faire avec les drapeaux
               ; d'animation.

               ; AOMFLAG : animation overflow modulator
               ; AOFFLAG : animation frame flag

               mov si,offset MX
               mov bl,[si+1]            ; BL=MY
               mov bh,0                 ; BH=0

               rol bx,7                 ; BX=MY*128
               mov di,bx                ; DI=MY*128
               xor bx,bx                ; BX=0
               mov bl,[si]              ; BX=MX
               add di,bx                ; DI=MX+MY*128
               add di,offset LEVEL_DATA ; DI=MX+MY*128+offset

               mov si,di                ; SI=DI
               mov di,0a00h

               mov bx,11                ; nombre de lignes   
NEXT_MCG_:     mov cx,20                ; nombre de colonnes 

NEXT_MCG:      xor ax,ax                ; AX=0
               mov al,[si]              ; Al=[MX+MY*128+offset]

               ; Nous allons ajouter la routine spÇciale
               ; d'animation plus tard.

               jmp NEW_ANIMATIONS

NORMALPRN:     rol ax,8                 ; AX=AX*256
               push si                  ; sauvegarde SI
               mov si,ax                ; SI=AX
               add si,offset IMAGES_MCG  ; SI=SI+offset IMAGE_MCG

               push cx                  ; sauvegarde CX
               push di

               mov dx,16
MCG_NLINE:     mov cx,16/4

MCG_LINE:      mov eax,[si]        ; Boucle d'impression d'une
               mov fs:[di],eax     ; case dans un buffer spÇcial
               add si,4            ; MEM2:0000
               add di,4
               loop MCG_LINE

               mov cx,dx
               dec dx
               add di,130h
               loop MCG_NLINE

               pop di
               pop cx
               pop si
RETWISE:       add di,16
               inc si
               loop NEXT_MCG

               mov cx,bx
               dec bx
               add si,128-20
               add di,140h*15
               loop NEXT_MCG_

               ; Maintenant, il me faut gärÇ AOFFLAG et AOMFLAG
               ; pour permettre les animations au niveau du
               ; "background". Par exemple: l'eau, la lave et
               ; les transporteurs.

               mov si,offset AOMFLAG
               mov al,[si]
               inc al
               mov [si],al
               cmp al,4
               jne LEAVEAOF
               xor al,al
               mov [si],al

               mov si,offset AOFFLAG
               mov al,[si]
               xor al,3
               mov [si],al

LEAVEAOF:

               ; Le joueur est SSF (simulated sprite frame)
               ; son affichage requiere une routine spÇciale

               mov si,offset PAFFLAG    ; Player aim frame flag
               xor ax,ax                ; AX=0
               mov al,[si]              ; AL=[PAFFLAG]
               mov dx,5                 ; DX=5
               mul dx                   ; AX=AX*5
               mov si,offset PAFLAG     ; Player animation flag
               add al,[si]              ; AX=[PAF]*5+[PA]
               rol ax,8                 ; AX=AX*256
               mov si,ax                ; SI=AX
               ;mov di,10*16+5*1400h     ; DI=player screen
               ;MODIFICATION
               mov di,10*16+5*1400h+0a00h

               ; Le JMPFLAG joue un rìle important dans 
               ; dans l'affichage du joueur. Quand JMPFLAG=1
               ; sa position est haussÇ d'une demie case
               ; illustrant le saut.

               push si
               mov si,offset JMPFLAG
               mov al,[si]
               cmp al,1
               jne NOTJMPING
               sub di,0a00h
NOTJMPING:     pop si

               xor dx,dx
               push si
               mov si,offset FFLAG
               mov al,[si]
               cmp al,1
               jne NORMA_POP
               mov si,offset CAFLAG
               mov al,[si]
               cmp al,0
               jne NORMA_POP
               inc dx

NORMA_POP:     pop si
               mov bx,16
CHK_NEXT_LINE: mov cx,16

CHK_NEXT:      mov al,es:[si]
               cmp al,0
               je DO_NOT_PRINT
               cmp dx,1
               jne PRN_NOW
               xor al,0f0h
PRN_NOW:       mov fs:[di],al
DO_NOT_PRINT:  inc di
               inc si
               loop CHK_NEXT

               mov cx,bx
               dec bx
               add di,130h
               loop CHK_NEXT_LINE

BYPASSPLY:

               ;==========================
               ; Affiche les crÇatures...
               ;==========================

               ; MODIFICATION: 17 NOV 93

               mov si,offset COAFLAG
               mov al,[si]
               inc al
               mov [si],al
               cmp al,4
               jne DSYSBL
               xor al,al
               mov [si],al

               mov si,offset CAFLAG
               mov al,[si]
               cmp al,0
               je SETHCA
               xor al,al
               jmp SETCA
SETHCA:        mov al,0bh
SETCA:         mov [si],al

               ; DYSPLAY SYSTEM BELOW ...

DSYSBL:        mov si,offset NOA
               mov al,es:[si]
               cmp al,0
               je NMOREACT

               ;mov al,5
               ;mov es:[si],al

               mov bx,-1
DRENTRY:       inc bx
               mov si,offset NOA
               mov cl,es:[si]
               cmp bl,cl
               je NMOREACT

               mov si,offset CCX
               add si,bx

               mov al,es:[si]
               mov di,offset MX
               mov ah,[di]
               sub al,ah
               cmp al,20
               jae NVISIBLE
               xor cx,cx
               mov cl,al
               rol cx,4

               mov al,es:[si+256]
               mov ah,[di+1]
               sub al,ah
               cmp al,11
               jae NVISIBLE
               xor ah,ah
               mov dx,0a00h*2
               mul dx

               mov di,ax
               add di,cx
               ;MODIFICATION
               add di,0a00h

               xor ax,ax
               mov al,es:[si+512]
               ; MODIFICATION: 17 nov 1993
               mov si,offset CAFLAG
               add al,[si]
               

               rol ax,8
               mov si,ax
               add si,offset ACTORS_FRAMES

               mov dx,16
ACONAA:        mov cx,16
ACONTL:        mov al,es:[si]
               cmp al,0
               je DNULPIXA
               mov fs:[di],al
DNULPIXA:      inc si
               inc di
               loop ACONTL
               
               add di,130h
               mov cx,dx
               dec dx
               loop ACONAA

NVISIBLE:      jmp DRENTRY

NMOREACT:

               ;==============================================
               ; Joue avec LETFLAG (last energy template flag)
               ;==============================================

               mov si,offset LIFE_FORCE
               mov al,[si]
               mov si,offset LETFLAG
               mov ah,[si]
               mov [si],al
               cmp al,ah
               jae PTSCRN
               xor si,si
               mov cx,65536/4
PTSINVSC:      mov eax,fs:[si]
               xor eax,0f0f0f0fh
               mov fs:[si],eax
               add si,4
               loop PTSINVSC

PTSCRN:
               mov di,23*0a00h     ; 22*0a00h
               mov eax,0
               mov cx,0a00h*2/4    ; 3/4
BLBUF3L:       mov fs:[di],eax
               add di,4
               loop BLBUF3L

               ;=============================================
               ; Ajoute au "buffer" des informations telles:
               ; > Le pointage : fait
               ; > L'Çnergie disponible:fait
               ; > Le nombre de fleurs:fait
               ; > Le nombre de TNT:fait
               ; > Les clefs:fait
               ;============================================

               ; CLEAR TOP LINE

               mov cx,0a00h/4
               xor di,di
               xor eax,eax
CLRTLN:        mov fs:[di],eax
               add di,4
               loop CLRTLN

               ; ADD SCORE TO EXISTING GAME SCREEN

               mov cx,8
               mov si,offset SCORE
               mov bl,0
               mov bh,0
MORE_SC_PRNT:  mov al,[si]
               mov ah,15
               call PFNT
               inc si
               inc bl
               loop MORE_SC_PRNT

               ; ADD "FLOWERS LEFT" TO EXISTING GAME SCREEN

               mov si,offset NUMBERS_DATA + 640
               mov di,10*8
               mov bx,8
FLW_PRN2:      mov cx,30*8
FLW_PRNT:      mov al,[si]
               cmp al,0
               je FLW_NTP
               mov fs:[di],al
FLW_NTP:       inc si
               inc di
               loop FLW_PRNT
               add di,140h-30*8
               mov cx,bx
               dec bx
               loop FLW_PRN2
               
               ; Il s'agit de compter les fleurs pour savoir 
               ; combien il en rest Ö ramasser. La valeur sera
               ; retournÇe dans BX.

               mov si,offset LEVEL_DATA
               xor bx,bx
               mov cx,8192

CSQFL:         mov al,[si]
               cmp al,0ch
               je INCFL
               cmp al,1bh
               je INCFL
               cmp al,43h
               jb XINCFL
               cmp al,69h
               ja XINCFL
               and al,1
               cmp al,1
               jne XINCFL

INCFL:         inc bx
XINCFL:        inc si
               loop CSQFL

               mov si,offset FLOWERS
               mov [si],bl

               xor dx,dx           ; DX hold the number frames
FLCOUDN:       cmp bx,0            ; BX has nb of flowers
               je INSFLOU
               inc dl
               cmp dl,9
               jbe FLBYTH
               inc dh
               mov dl,0
FLBYTH:        dec bx
               jmp FLCOUDN

INSFLOU:       mov bl,23
               mov bh,0
               mov ah,14
               mov al,dh
               call PFNT
               inc bl
               mov al,dl
               call PFNT

               xor bx,bx
               mov si,offset TNT
               mov bl,[si]

               ; La quantitÇ de fleurs qui doivent-àtre ramasser
               ; est contenue dans BX. Cette valeur doit-àtre
               ; convertie en deux frames contenus dans DX.

               xor dx,dx           ; DX hold the number frames
TNTCOUDN:      cmp bx,0            ; BX has nb of flowers
               je INSTNTOU
               inc dl
               cmp dl,9
               jbe TNTBYTH
               inc dh
               mov dl,0
TNTBYTH:       dec bx
               jmp TNTCOUDN

               ; Ceci s'occupe d'affiche la quantitÇ de fleurs
               ; qui reste Ö ramasser pour compläter le tableau.

INSTNTOU:      mov bl,38
               mov bh,0
               mov ah,12
               mov al,dh
               call PFNT
               inc bl
               mov al,dl
               call PFNT

               ; Cette partie gäre l'affichage d'une ligne verte
               ; qui indique l'Çnergie de nìtre hÇros. 

               mov si,offset LIFE_FORCE
               mov di,23*0a00h+140h
               mov al,2
               xor bx,bx
               xor dx,dx
               mov dl,[si]
               cmp dx,0
               je LFINOUT
ADDMORECX:     mov cx,6
ADDMOREGREEN:  mov fs:[di+bx],al
               add di,140h
               loop ADDMOREGREEN
               mov di,23*0a00h+140h
               mov cx,dx
               dec dx
               inc bx
               loop ADDMORECX
LFINOUT:

               ; Ajoutons maintenant la magnifique petite ligne 
               ; gris pÉle qui indique le niveau d'oxygäne en
               ; rÇserve.

               mov si,offset OXYGEN
               mov di,24*0a00h+140h
               mov al,7
               xor bx,bx
               xor dx,dx
               mov dl,[si]
               cmp dx,0
               je WHITEOUT
ADDMORECXW:    mov cx,6
ADDMOREW:      mov fs:[di+bx],al
               add di,140h
               loop ADDMOREW
               mov di,24*0a00h+140h
               mov cx,dx
               dec dx
               inc bx
               loop ADDMORECXW
WHITEOUT:
               ; Maintenant, affichons les clefs qui ont ÇtÇ
               ; ramasser. Elles seront installÇes en bas 
               ; complätement de l'Çcran.

               mov si,offset KEYS
               mov bx,offset KEYS_DATA
               mov cx,4
               mov di,23*0a00h+130h
CHKBUKEY:      mov al,[si]
               cmp al,1
               jne XPRNKEY
               xor ax,ax
               mov al,[bx]
               rol ax,8       ; AX=KEY ID *256
               add ax,offset IMAGES_MCG
               pusha
               mov si,ax      ; SI= IMAGE_MCG+ KEY ID *256
               mov bx,16
ETRANKEY2:     mov cx,4
ETRANKEY:      mov eax,[si]
               mov fs:[di],eax
               add di,4
               add si,4
               loop ETRANKEY
               add di,130h
               mov cx,bx
               dec bx
               loop ETRANKEY2
               popa
               add di,-16
XPRNKEY:       inc bx
               inc si
               loop CHKBUKEY

               ; La conditionnel suivante vÇrifie si la force de
               ; vie [LIFE_FORCE] est supÇrieur Ö zÇro. Si tel
               ; n'est pas le cas on affichera "GAME OVER!"

               mov si,offset LIFE_FORCE
               mov al,[si]
               cmp al,0
               jne NOT_GAME_OVER

               mov si,offset GAME_OVER
               mov di,offset 10*0a00h
               
               mov dx,MEM2
               mov gs,dx
               call BPMCGS
               
               call CONVENSIONS

               mov si,offset OXYGEN
               xor al,al
               mov [si],al
NOT_GAME_OVER:

               ; Transfäre l'Çcran du "buffer vidÇo" vers la
               ; mÇmoire vidÇo. OpÇration nÇcessaire Ö cause
               ; du systäme SSF.

               mov cx,65536/4
               xor si,si
               xor di,di

TRANS_SCREEN:  mov eax,fs:[si]
               mov gs:[di],eax
               add si,4
               add di,4
               loop TRANS_SCREEN

               ; Tiens donc, ceci gäre l'animation interne du
               ; programme qui concerne le joueur. [PMFLAG]
               ; est incrÇmentÇ.

               mov si,offset PMFLAG
               mov al,[si]
               cmp al,0
               je PLY_ANI_OFF
               mov si,offset PAFLAG
               mov al,[si]
               inc al
               mov [si],al
               cmp al,5
               jne PLY_ANI_OFF
               mov al,0
               mov [si],al
PLY_ANI_OFF:
               mov di,offset PMFLAG
               mov al,0
               mov [di],al





               ; Le JMPFLAG est utilisÇ pour gÇrer les
               ; dÇplacements du "player actor" pendant qu'il
               ; saute et ainsi facilitÇ la gestion de ce module.

               mov si,offset JMPFLAG
               mov al,[si]
               cmp al,0
               je INIGESJMP
               xor al,al
               mov [si],al

               mov si,offset PMFLAG
               mov al,1
               mov [si],al

               mov si,offset PAFFLAG
               mov al,[si]
               cmp al,2
               je LEFT_J
               
RIGHT_J:       mov si,offset MX
               mov al,[si]
               inc al
               mov [si],al
               jmp INIGESJMP

LEFT_J:        mov si,offset MX
               mov al,[si]
               dec al
               mov [si],al
               jmp INIGESJMP

INIGESJMP:
               ; VÇrfifions maintenant le nombre de fleurs
               ; qui reste toujours Ö àtre ramassÇ. 
               ; si [FLOWERS]=0 donc nous passons Ö NEXT_LEVEL


               mov si,offset FLOWERS
               mov al,[si]
               cmp al,0
               jne POSTLOOP
               mov cx,500
               call ADD_TO_SCORE
               mov si,offset LIFE_FORCE
               mov cl,[si]
               xor ch,ch
               call ADD_TO_SCORE
               jmp NEXT_LEVEL

               ; Ici, il s'agit de la boucle central (MAIN_LOOP)
               ; cette partie gäre la coordination entre les
               ; parties qui lui sont subordonnÇs.
POSTLOOP:

               ;COUNTER 0-127

MAIN_LOOP:     mov si,offset COUNTER
               mov al,[si]
               inc al
               mov [si],al
               cmp al,128
               je UPDATE_SCREEN

               ;mov di,offset MCOUNTER
               ;mov bl,[di]
               ;mov si,offset SPEED
               ;mov bh,[si]
               ;cmp bl,bh
               ;jne MAIN_LOOP
               ;xor bl,bl
               ;mov [di],bl
               
               mov ah,al
               and ah,3
               cmp al,ah
               je PLAYER_MODULE

               cmp al,127
               je COS20
               jmp MAIN_LOOP

               ;===============================================

               ; La partie qui suit porte le nom de COS 2.0
               ; (Creatures operating system v.20). Elle a pour
               ; but la gestion des crÇatures dans leurs
               ; dÇplacement.

               ;===============================================
               ; CREATURES MODULATIONS
COS20:         ; CFLAG

               mov si,offset CFLAG
               mov al,[si]
               inc al
               mov [si],al
               cmp al,2
               jne MAIN_LOOP
               mov al,0
               mov [si],al

               mov bp,-1
NEWACTOR:      inc bp
               mov si,offset NOA
               xor bx,bx
               mov bl,es:[si]
               cmp bp,bx
               je NOTMOREACTOR

               mov si,offset CCX
               add si,bp

               mov bl,es:[si]
               mov bh,es:[si+256]
               
               mov al,es:[si+512]       ; AL=FORM
               cmp al,0
               je C_PLATFORM
               cmp al,7
               je C_SPIDERS
               cmp al,8
               je C_PLATFORM_X
               cmp al,9
               je C_FISH
               cmp al,0ah
               je C_FISH


               ;===================
               ; EMULTATE COS v1.0
               ;===================

               ; La plupart des crÇatures de VLAMITS utlisent
               ; une Çmulation de COS v1.0 pour permettrent
               ; leur dÇplacements. Cependant, quelques unes plus
               ; capricieuses devront àtre gàrÇ par exemple:
               ; par C_SPIDERS (qui s'occupent des araignÇe qui 
               ; est un cas spÇcial).

               xor cx,cx
               mov cl,es:[si+256*3]
               dec cx
               rol cx,2
               mov si,offset COSTABLE
               add si,cx

               ; Ceci est une routine fraåchement ajoutÇe pour
               ; permettre aux crÇatures qui utilisent une
               ; Çmulation de COS V1.0 puissent retirer de
               ; l'Çnergie comme si elles Çtaient dans CS3.

               pusha

               mov si,offset MX
               mov bl,[si]
               add bl,10
               mov bh,[si+1]
               add bh,5

               mov si,offset CCX
               add si,bp
               mov di,offset LIFE_FORCE

               ; AL: CREA X 
               ; AH: CREA Y
               ; BL: PLAYER X
               ; BH: PLAYER Y

               call CREAPOSREAD
               dec al
               call CMPPLAYTOCREA
               dec ah
               call CMPPLAYTOCREA
               inc al
               call CMPPLAYTOCREA
               inc ah
               call CMPPLAYTOCREA
               jmp RETNORMALOP

CREAPOSREAD:   mov al,es:[si]
               mov ah,es:[si+256]
               ret

CMPPLAYTOCREA: cmp al,bl
               jne CMPPTCOUT
               cmp ah,bh
               jne CMPPTCOUT
               mov dl,[di]
               sub dl,4
               cmp dl,[di]
               jbe CPCNOC
               xor dl,dl
CPCNOC:        mov [di],dl
CMPPTCOUT:     call CREAPOSREAD
               ret

               ; Ci-dessous se trouve l'opÇration normale de la
               ; routine de dÇplacement de la crÇature. Son
               ; but est de permettre la dÇmarche logique de
               ; celle-ci selon un schÇma bien prÇcis.

RETNORMALOP:   popa
               mov cx,4
MAKELOOPDES:   mov gs,cx
               mov cl,[si]
               call CHKDEST
               inc si
               cmp dl,0
               je OUTLOOPDES
               push gs
               pop cx
               loop MAKELOOPDES

OUTLOOPDES:    jmp NEWACTOR

NOTMOREACTOR:  call CONVENSIONS
               jmp MAIN_LOOP

               ; La gestions des araignÇes se fait par la
               ; routine C_SPIDERS (routine spÇciale) qui gäre
               ; comme sont nom l'indique que les araignÇes.
               ; Les araignÇes peut marcher sur les autres
               ; crÇatures une certaine possibilitÇ qui n'Çtait
               ; pas disponible avec COS v1.

C_SPIDERS:     pusha
               mov si,offset MX
               mov bl,[si]
               add bl,10
               mov bh,[si+1]
               add bh,5

               mov si,offset CCX
               add si,bp 
               mov di,offset LIFE_FORCE

               ;mov al,es:[si]
               ;mov ah,es:[si+256]

               call CREAPOSREAD
               call CMPPLAYTOCREA
               inc al
               call CMPPLAYTOCREA
               dec al
               call CMPPLAYTOCREA
               inc ah
               call CMPPLAYTOCREA
               dec ah
               call CMPPLAYTOCREA

               ; Cette routine est ci-dessus, elle aura ÇtÇ
               ; poussÇ pour permettre l'ajout de la routine
               ; qui retire de l'Çnergie. 

               popa
               mov dh,es:[si+3*256]
               mov al,dh
               and al,1
               cmp al,0
               jne CSPIDA1
               mov dh,1
               mov es:[si+3*256],dh
CSPIDA1:       mov cx,2
CSPIDA3:       push cx
               mov cl,dh
               call CHKDEST
               pop cx
               cmp dl,0
               je CSPIDA2
               xor dh,02
               loop CSPIDA3
CSPIDA2:       jmp NEWACTOR

               ; The routine below this point is taking
               ; care "Flying platforms". These platforms
               ; have static propreties.

               ; They are two type of platforms, the first type 
               ; are moving verticaly and the second is moving
               ; horizontaly.

               ; Vertical platforms: type 0
               ; uses C_PLATFORM
               ; Horizontal platforms: type 8
               ; uses C_PLATFORM_X

; >-------------------------------------------------------------<

C_PLATFORM:    mov si,offset CCX
               add si,bp
               mov bl,es:[si]
               mov bh,es:[si+256]

               ; Loads CL with direction code for the actor
               ; wanted aim that is to be checked eventualy.

               mov cl,es:[si+3*256]     
               cmp cl,1
               je OK_DIR
               cmp cl,3
               je OK_DIR
               mov cl,1
               mov es:[si+3*256],cl

OK_DIR:        call PLATFORM_CHK   ;(eqv to CHKDEST)
               cmp dl,1
               je CP_CMOV
               jmp PLAYER_A
               ;jmp NEWACTOR

CP_CMOV:       cmp cl,1
               je CL_1TO3
               mov cl,1
               jmp NCL_1TO3
CL_1TO3:       mov cl,3
NCL_1TO3:      mov es:[si+3*256],cl
               jmp NEWACTOR

PLAYER_A:      mov si,offset MX
               mov al,[si]
               add al,10
               mov ah,[si+1]
               add ah,6
               cmp al,bl
               jne NEWACTOR
               cmp ah,bh
               jne NEWACTOR
               
               mov di,offset CCX
               add di,bp
               mov al,es:[di+256]
               sub al,6
               mov [si+1],al
               jmp NEWACTOR

; >-------------------------------------------------------------<

C_PLATFORM_X:  mov si,offset CCX
               add si,bp
               mov bl,es:[si]
               mov bh,es:[si+256]

               ; Loads CL with direction code for the actor
               ; wanted aim that is to be checked eventualy.

               mov cl,es:[si+3*256]     
               cmp cl,1
               je CCXPLATX
               cmp cl,3
               je CCXPLATX
               jmp CCXPLAT

CCXPLATX:      mov cl,2
               mov es:[si+3*256],cl
CCXPLAT:       call CHKDEST
               cmp dl,1
               je XCP_CMOV
               jmp XXX_P

XCP_CMOV:      cmp cl,2
               je XCL_1TO3
               mov cl,2
               jmp XNCL_1TO3
XCL_1TO3:      mov cl,4
XNCL_1TO3:     mov es:[si+3*256],cl
               jmp NEWACTOR

XXX_P:         mov di,offset MX
               mov al,[di]
               add al,10
               mov ah,[di+1]
               add ah,6

               cmp al,bl
               jne PLYXTOPP
               cmp ah,bh
               jne PLYXTOPP

               mov al,es:[si]
               sub al,10
               mov [di],al
PLYXTOPP:      jmp NEWACTOR

; >-------------------------------------------------------------<

               ; C_FISH is used move fishes in water. The routine
               ; first execute a scan for the player actor. Then,
               ; it will scan possible directions.

C_FISH:        mov si,offset MX
               mov bl,[si]
               add bl,10
               mov bh,[si+1]
               add bh,5

               mov si,offset CCX
               add si,bp 
               mov di,offset LIFE_FORCE

               call CREAPOSREAD
               call CMPPLAYTOCREA
               inc al
               call CMPPLAYTOCREA
               dec al
               call CMPPLAYTOCREA
               inc ah
               call CMPPLAYTOCREA
               dec ah
               call CMPPLAYTOCREA

               ; Above is an energie drain routine (in fact it is
               ; the same that is used by C_SPIDER).Below is the
               ; moving routine.

               mov si,offset CCX
               add si,bp

               mov al,es:[si+256*3]
               xor ah,ah
               dec al
               rol ax,2
               add ax,offset COSTABLE

               mov bl,es:[si]
               mov bh,es:[si+256]
               mov si,ax

               mov cx,4
FISHDIRN:      push cx
               mov cl,[si]
               call CHKDEST
               cmp dl,0
               je FISHMOVE
               pop cx
               inc si
               loop FISHDIRN
               jmp NEWACTOR

FISHMOVE:      pop ax
               mov si,offset CCX + 512
               add si,bp
               cmp cl,2
               je SET_RFISH
               cmp cl,4
               je SET_LFISH
               jmp NEWACTOR

SET_RFISH:     mov al,0ah
               mov es:[si],al
               jmp NEWACTOR

SET_LFISH:     mov al,09h
               mov es:[si],al
               jmp NEWACTOR








;=====================================
; PLATFORM_CHK
; INPUTS
; BL,BH        : X & Y
; CL           : direction
; OUTPUTS 
; DL=0         : can move
; DH=1         : can't move
;=====================================

PLATFORM_CHK:  push ax
               push di
               push si
               push cx
               mov ax,bx

               cmp cl,1
               je UP_P
               cmp cl,3
               je DOWN_P
               jmp NOT_FOUND

UP_P:          dec ah
               jmp PDESC
DOWN_P:        inc ah
               jmp PDESC

PDESC:         push cx
               xor cx,cx
               mov cl,ah
               rol cx,7
               add cl,al
               add cx,offset LEVEL_DATA
               mov si,cx
               pop cx

               call CREAINPOS
               cmp dl,1
               je RETWM

               call BL_STOPID
               cmp dl,1
               je RETWM

               call SMART_PLAT
               cmp dl,1
               je RETWM

               jmp RETANDMOV            

;=========================================================
;ROUTINE: CHKDEST FOR EMULATED COS 1.0 CREATURES
;
;         INPUTS:
;         BL,BH          ; X & Y 
;         CL             ; direction
;         OUTPUTS
;         DL=0 can move
;         DH=1 can't move
;=========================================================

CHKDEST:       push ax
               push di
               push si
               push cx
               mov ax,bx      ; AX=new coordonates

               cmp cl,1
               je UP_
               cmp cl,2
               je RIGHT_
               cmp cl,3
               je DOWN_

               cmp cl,4
               je LEFT_

               nop

               jmp QUIT

CDESC:         ; La position source de crÇature est donnÇe dans
               ; SI.
               xor cx,cx
               mov cl,ah
               rol cx,7
               add cl,al
               add cx,offset LEVEL_DATA
               mov si,cx

               ; Fishs are nasty little fellow, they requiere
               ; a special handling routine. If that weren't 
               ; enought, they don't use the same avoid obstacle
               ; routine either.

               push ax
               push si
               mov si,offset CCX + 512
               add si,bp
               mov al,es:[si]
               cmp al,9
               jb NOT_FISH
               cmp al,0ah
               ja NOT_FISH
               pop si
               call FISH_BIT
               cmp dl,1
               je FISH_RETWM
               ;pop si
               pop ax
               jmp NONESPIDER
               
FISH_RETWM:    ;pop si
               pop ax
               jmp RETWM

NOT_FISH:      pop si
               pop ax
               call BL_STOPID
               cmp dl,1
               je RETWM

               ; Platforms actors don't have to obey to gravity
               ; because they have antigravity propreties. The
               ; patch below allows platforms to move upon empty
               ; spaces.

FISH_XXX:      push si
               push ax
               mov si,offset CCX + 512
               add si,bp
               mov al,es:[si]
               cmp al,8
               je XGRAVITY
               cmp al,0
               je XGRAVITY
               pop ax
               pop si

               push ax
               call GRAVITY
               pop ax
               cmp dl,1
               je RETWM

NXGRAVITY:     jmp NGRAVITY
XGRAVITY:      pop ax
               pop si
               ;jmp YPLAT

NGRAVITY:

               ; Nous savons tous comme áa serait dommage si une 
               ; crÇature traditionnelle marchait sur le joueur.
               ; Les araignÇes ont le droit de la faire. Je dois
               ; donc leur donnÇ ce priviläge.

               pusha
               mov si,offset CCX + 512
               add si,bp
               mov al,es:[si]
               cmp al,7
               je SPIDERWALKGO
               popa
               jmp NONESPIDER
SPIDERWALKGO:  popa
               call SPIWALKCOND         ; SPIDER'S WALK CONDITION

               cmp dl,1
               je RETWM
               jmp NEXTNONESPI

               ; A routine to check if you are going to walk
               ; onto our player actor. Such action would be
               ; a shame. NWLONPLY

NONESPIDER:    call NWLONPLY
               cmp dl,1
               je RETWM

YPLAT:         call CREAINPOS
               cmp dl,1
               je RETWM

NEXTNONESPI:

RETANDMOV:     mov di,offset CCX
               add di,bp
               mov es:[di],al
               mov es:[di+256],ah
               pop cx
               mov es:[di+256*3],cl
               pop si
               pop di
               pop ax
               ret

RETWM:         pop cx
               pop si
               pop di
               pop ax
               ret

UP_:           dec ah
               jmp CDESC

DOWN_:         inc ah
               jmp CDESC

LEFT_:         dec al
               jmp CDESC

RIGHT_:        inc al
               jmp CDESC



               ;----------------------------------------
               ; SMART_PLAT   
               ; INPUTS
               ; AL,AH        WX & WY position of actor
               ; CL:          direction
               ; SI:          wanted position
               ; OUTPUTS
               ; DL=0         can move
               ; DL=1         can't move
               ;---------------------------------------

SMART_PLAT:    push si
               xor dl,dl
               call NWLONPLY
               cmp dl,0
               je SP_END

               cmp cl,1
               je SP_UP
               
               add si,128
               jmp SP_SCAN
SP_UP:         sub si,128

SP_SCAN:       call BL_STOPID

SP_END:        pop si
               ret

               ;===================================
               ; BL_STOPID
               ; INPUTS:
               ; SI: CREATURE ABSOLUTE POSITION
               ; OUTPUTS:
               ; DL=0 Can move.
               ; DL=1 Can't move.
               ;===================================

BL_STOPID:     push ax
               push si
               
               xor dl,dl
               mov al,[si]

               cmp al,4
               je BL_STOP

               cmp al,1
               je BL_STOP

               cmp al,0eh
               jb BLXA1
               cmp al,31h
               ja BLXA1
               jmp BL_STOP

BLXA1:         cmp al,33h
               je BL_STOP
               cmp al,41h
               je BL_STOP
               cmp al,42h
               je BL_STOP

               cmp al,44h
               je BL_STOP
               cmp al,46h
               je BL_STOP
               cmp al,48h
               je BL_STOP
               cmp al,49h
               je BL_STOP
               cmp al,4ah
               je BL_STOP
               cmp al,4ch
               je BL_STOP

               cmp al,4eh
               jb BLXA2
               cmp al,5ah
               ja BLXA2
               cmp al,53h
               jb BL_STOP
               mov ah,al
               and ah,1
               cmp ah,0
               je BL_STOP

BLXA2:         cmp al,64h
               jb BLXA3
               cmp al,6ah
               ja BLXA3
               mov ah,al
               and ah,1
               cmp ah,0
               je BL_STOP

BLXA3:         cmp al,6bh
               jb BLXA4
               cmp al,75h
               ja BLXA4
               mov ah,al
               and ah,1
               cmp ah,1
               je BL_STOP          

BLXA4:         cmp al,5
               je BL_STOP
               
BLSOMERET:     pop si
               pop ax
               ret

BL_STOP:       mov dl,1
               jmp BLSOMERET

               ;----------------------------------------------
               ;CREAINPOS
               ;INPUTS:
               ;AL: X; AH: Y
               ;OUTPUTS:
               ;DL=0 can move
               ;DL=1 can't move
               ;-----------------------------------------------

CREAINPOS:     push cx
               push si
               
               xor dl,dl
               mov si,offset NOA
               xor cx,cx
               mov cl,es:[si]

               mov si,offset CCX
MOCRTC:        cmp al,es:[si]
               jne MAYBNT

               cmp ah,es:[si+256]
               jne MAYBNT

               inc dl
RINSPOUT:      pop si
               pop cx
               ret

MAYBNT:        inc si
               loop MOCRTC
               jmp RINSPOUT

               ;-------------------------------------------
               ; NWLONPLY:
               ; INPUTS
               ; AL= X ; AH=Y
               ; OUTPUTS
               ; DL=0 : can move
               ; DL=1 : can't move
               ;-------------------------------------------

NWLONPLY:      push ax
               push si
               xor dl,dl      

               sub al,10
               sub ah,5

               mov si,offset MX
               cmp al,[si]
               jne NOTONPLY
               cmp ah,[si+1]
               jne NOTONPLY

               inc dl
NOTONPLY:      pop si
               pop ax
               ret
























               ;============================================
               ;              PLAYER MODULE:
               ;============================================

PLAYER_MODULE: ; "GAME OVER" IF [LIFE_FORCE]=0
               mov si,offset LIFE_FORCE
               mov al,[si]
               cmp al,0
               jne NGMOVER

               mov si,offset OUTFLAG
               mov al,[si]
               cmp al,0
               jne WAITFORKEY

               call GETAX
               cmp ax,0
               jne MAIN_LOOP

               mov al,[si]
               inc al
               mov [si],al

WAITFORKEY:    call GETAX
               cmp ax,0
               je MAIN_LOOP
               jmp GAME_OVER_MODULE

NGMOVER:

               ; THE ROUTINE BELOW CARRIES OUT THE PLAYER
               ; CONTROL MODULE.

               mov si,offset PCFLAG     ;player counter flag
               mov al,[si]
               inc al
               mov [si],al
               cmp al,3
               jne MAIN_LOOP
               mov al,0
               mov [si],al

               mov si,offset MX
               mov bl,[si]
               mov bh,[si+1]
               add bl,10
               add bh,5
               xor ax,ax
               mov al,bh
               rol ax,7
               xor bh,bh
               add ax,bx
               add ax,offset LEVEL_DATA
               mov si,ax

               mov al,[si]

               cmp al,35h
               jb XBRIDGE
               cmp al,3fh
               ja XBRIDGE
               inc al
               cmp al,40h
               jne XBLANK
               mov al,0
XBLANK:        mov [si],al
XBRIDGE:
               ;==========================================
               ; Les objets suivants accordent des points
               ;
               ; 1)Coffre 50pts
               ; 2)Diamant 25pts

               mov ah,0
               cmp al,0ah; coffre en surface
               je S_COFFRE
               cmp al,0dh; diamand en surface
               je S_DIAMANT
               cmp al,8  ; TNT
               je S_TNT
               cmp al,0ch; Fleur de surface : simple
               je S_FLOWER
               ;cmp al,40h
               ;je BREAK_ROOT

               mov ah,14h
               cmp al,19h
               je S_COFFRE
               cmp al,1ch
               je S_DIAMANT
               cmp al,1bh; Fleur sous-l'eau: simple
               je S_FLOWER

               ; THIS ROUTINE ISOLATE IF YOU ARE ON A TRANSPORTER
               cmp al,6bh
               jb SSUA1VERSAI
               cmp al,75h
               ja SSUA1VERSAI
               mov ah,al
               and ah,1
               cmp ah,1
               jne SSUA1VERSAI
               
               ; THIS ROUTINE IDENTIFY THE DESTINATION OF THAT
               ; TRANSPORTER.
               mov ah,al
               inc ah
               xor bx,bx
               mov si,offset LEVEL_DATA
               mov cx,8192
NDESTRA:       mov al,[si+bx]
               cmp al,ah
               je DESTRA
               inc bx
               loop NDESTRA
               jc NOT_FOUND

DESTRA:        mov ax,bx
               and ax,127          ; AX=MX+10
               ror bx,7            ; BX=MY+5
               add ax,-10          ; AX=MX
               add bx,-5
               mov si,offset MX
               mov [si],al
               mov [si+1],bl
               jmp MAIN_LOOP

SSUA1VERSAI:   ; ==============================================
               ; Dans "The Vlamits" il y a des 
               ; clefs immobiles.
               ;
               ; HKEY    0E 1E
               ; WKEY    10 20
               ; MELKEY  12 22
               ;
               ; Il y a aussi une clef vivante, mais
               ; COS 2.0 n'est pas encore opÇrationelle.
               ;===============================================
               
               mov ah,0
               cmp al,0eh
               je S_HKEY
               cmp al,10h
               je S_WKEY
               cmp al,12h
               je S_MELKEY

               mov ah,14h
               cmp al,1eh
               je S_HKEY
               cmp al,20h
               je S_WKEY
               cmp al,22h
               je S_MELKEY

               cmp al,41h
               je SETGAMEOVER
               cmp al,42h
               je SETGAMEOVER

               ;==============================================
               ; C'est le 5 novembre 1993 Ö 23:45 qu'a dÇbutÇ
               ; la routine qui se charge...
               ;
               ; 1) des bouteilles d'oxygäne 0B/1A
               ; 2) piäge invisible 03
               ;=============================================

               mov ah,0
               cmp al,0bh
               je S_OXY
               cmp al,03
               je S_TRAP
               
               mov ah,14h
               cmp al,1ah
               je S_OXY
               jmp VERSAI

S_TRAP:        mov di,offset LIFE_FORCE
               mov dl,[di]
               mov dh,dl
               add dh,-32
               cmp dh,dl
               jb XLFHI
               mov dh,0
XLFHI:         mov [di],dh
               mov al,0
               mov [si],al
               jmp VERSAI

S_OXY:         mov [si],ah
               mov cx,22
               call ADD_TO_SCORE
               mov al,ah
               mov di,offset OXYGEN
               mov dl,[di]
               mov dh,dl
               add dh,36
               cmp dh,dl
               ja XOXYHI
               mov dh,255
XOXYHI:        mov [di],dh
               jmp VERSAI

S_HKEY:        mov di,offset KEYS 
IMKEYSTA:      mov [si],ah
               mov al,ah
               mov ah,1
               mov [di],ah
               mov cx,50
               call ADD_TO_SCORE
               jmp VERSAI

S_WKEY:        mov di,offset KEYS+1
               jmp IMKEYSTA 

S_MELKEY:      mov di,offset KEYS+2
               jmp IMKEYSTA

S_COFFRE:      mov [si],ah
               mov al,ah
               mov cx,50
               call ADD_TO_SCORE
               jmp VERSAI

S_DIAMANT:     mov [si],ah
               mov al,ah
               mov cx,25
               call ADD_TO_SCORE
               push si
               mov si,offset LIFE_FORCE
               mov al,[si]
               mov ah,al
               add al,3
               cmp al,ah
               ja BLFNOHD
               mov al,255
BLFNOHD:       mov [si],al
               pop si
               mov al,[si]
               jmp VERSAI

S_TNT:         mov [si],ah
               mov cx,20
               call ADD_TO_SCORE
               push si
               mov si,offset TNT
               mov al,[si]
               inc al
               mov [si],al
               xor al,al
               pop si
               jmp VERSAI

S_FLOWER:      mov [si],ah
               mov cx,10
               call ADD_TO_SCORE
               push si
               mov si,offset LIFE_FORCE
               mov al,[si]
               mov ah,al
               add al,4
               cmp al,ah
               ja BLFNOH
               mov al,255
BLFNOH:        mov [si],al
               pop si
               mov al,[si]
               jmp VERSAI

BREAK_ROOT:    mov [si],al
               mov al,ah
               jmp VERSAI

VERSAI:        ; é ce point-ci du programme j'ai dÇcidÇ
               ; d'ajouter la routine qui fait la gestion
               ; des fleurs.

               ; SI := PP
               ; AL := PV 

               ; AL+1 := BL

               ; BRICK -> BLANK
               mov ah,0       
               cmp al,43h
               je FBLANK
               cmp al,45h
               je FBLANK
               cmp al,47h
               je FBLANK
               cmp al,49h
               je FWATER
               
               ; BRICK UNDER WATER -> WATER
               mov ah,14h
               cmp al,4bh
               je FBLANK
               cmp al,4dh
               je FBLANK
               cmp al,4fh
               je FWATER
               cmp al,51h
               je FWATER

               ; BRICK ON SURFACE -> SURFACE WATER
               mov ah,24h
               cmp al,53h
               je FBLANK
               cmp al,55h
               je FBLANK
               cmp al,57h
               je FWATER
               cmp al,59h
               je FWATER

               ; VIDE MUTANOID -> BRICK 
               mov ah,28h
               cmp al,5bh
               je FBLANK
               cmp al,5dh
               je FBLANK
               cmp al,5fh
               je FBLANK
               cmp al,61h
               je FBLANK

               ; EAU MUTANOID -> BRICK
               mov ah,2ah
               cmp al,63h
               je FWATER
               cmp al,65h
               je FWATER
               cmp al,67h
               je FWATER
               cmp al,69h
               je FWATER

               jmp OUTFLOWERS

FBLANK:        mov bl,0            ; FLOWER -> BLANK
               jmp MUTATE_ALL
FWATER:        mov bl,14h          ; FLOWER -> WATER
               jmp MUTATE_ALL

MUTATE_ALL:    pusha
               mov [si],bl         ; FLOWER -> BL
               inc al
               mov cx,8192
               mov si,offset LEVEL_DATA
MUTALL:        mov bl,[si]
               cmp bl,al
               jne NOTINDEN
               mov [si],ah
NOTINDEN:      inc si
               loop MUTALL
               mov cx,10
               call ADD_TO_SCORE
               mov si,offset LIFE_FORCE
               mov al,[si]
               mov ah,al
               add al,4
               cmp al,ah
               ja SBLFNOH
               mov al,255
SBLFNOH:       mov [si],al
               mov al,[si]
               popa
               jmp OUTFLOWERS






































OUTFLOWERS:
               ;=================================================
               ; ítes-vous sous l'eau? Si oui, il y a des
               ; consÇquences.               
               ;=================================================

               cmp al,14h
               jb CWA1A
               cmp al,23h
               ja CWA1A
               jmp REMOXY

CWA1A:         cmp al,2dh
               jb CWA1B
               cmp al,31h
               ja CWA1B
               jmp REMOXY
               
CWA1B:         cmp al,64h
               jb CWA1C
               cmp al,6ah
               ja CWA1C
               mov ah,al
               and ah,1
               cmp ah,1
               je CWA1C
               jmp REMOXY

CWA1C:         cmp al,71h
               jb CWA1D
               cmp al,75h
               ja CWA1D
               mov ah,al
               and ah,1
               cmp ah,0
               je CWA1D
               jmp REMOXY

CWA1D:         cmp al,27
               je REMOXY

               push ax
               push si
               mov si,offset OXYGEN
               mov al,[si]
               cmp al,32
               jae CWA1E      
               inc al
               mov [si],al
CWA1E:         pop si
               pop ax
               jmp CGRAVITY

REMOXY:        ; ===============================================
               ; Cette partie du programme gäre les consÇquences
               ; sous-l'eau.
               ; ===============================================
               push ax
               push si

               ; MODIFICATON: 20 novembre 1993
               mov si,offset ODFLAG     ; oxygen drain flag
               mov al,[si]
               inc al
               mov [si],al
               cmp al,4
               je DRAPP
               jmp OUTOXYD

DRAPP:          xor al,al
               mov [si],al
               mov si,offset OXYGEN
               mov al,[si]
               mov ah,al
               add al,-1
               cmp al,ah
               jb SNOXYL
               mov al,0

SNOXYL:        mov [si],al
               cmp al,0
               jne OUTOXYD
               mov si,offset LIFE_FORCE
               mov al,[si]
               ;MODIFICATION
               mov ah,al
               ;add al,-2
               dec al    ; modification
               cmp al,ah
               jb SNLFL
               mov al,0
SNLFL:         mov [si],al
OUTOXYD:       pop si
               pop ax
               jmp CGRAVITY

;ADD A ROUTINE FOR READING FALLS HERE...
CGRAVITY:      call GRAVITY
               cmp dl,1

               jne PLY_CTRL
               
               call PLAYER_G
               cmp dl,1
               je MAIN_LOOP

               ;je MAIN_LOOP

               ;==========================================
               ; LA PARTIE SUIVANTE GëRE LES DêPLACEMENTS
               ;==========================================
PLY_CTRL:
PLAYER_CONTROL:mov si,offset JMPFLAG
               mov al,[si]
               cmp al,1
               je KEYQUIT

               mov si,offset MX
               mov bl,[si]
               mov bh,[si+1]
               mov di,si

               call GETAX
               cmp al,"8"
               je UP
               cmp al,"2"
               je DOWN
               cmp al,"4"
               je LEFT
               cmp al,"6"
               je RIGHT

               cmp al,"7"
               je JMP_LEFT
               cmp al,"9"
               je JMP_RIGHT

               cmp al,"1"
               je JMP_LEFT
               cmp al,"2"
               je JMP_RIGHT

            ; THIS IS THE CHEAT COMMAND REMOVED
               cmp al,":"
               je NEXT_LEVEL

               cmp al," "
               je PAUSE_GAME
               cmp al,"`"
               je SETGAMEOVER
               cmp al,27
               je QUIT

               cmp ah,59
               je CHANGE_SPEED
               cmp ah,60
               je RESTART_GAME
               cmp ah,61
               je ERASE_HIS
               cmp ah,62
               je EDITOR

               jmp MAIN_LOOP

SETGAMEOVER:   mov si,offset LIFE_FORCE
               xor al,al
               mov [si],al
               jmp MAIN_LOOP

UP:            mov si,offset PAFFLAG
               mov al,0
               mov [si],al
               mov al,1                 ; SET
               mov si,offset PMFLAG     ; player movement flag=1
               mov [si],al              
               dec bh
               cmp bh,64
               ja MAIN_LOOP
               ;mov [di+1],bh
               ;jmp MAIN_LOOP
               jmp MOVE_PLAYER

DOWN:          mov si,offset PAFFLAG
               mov al,0
               mov [si],al
               mov al,1                 ; SET
               mov si,offset PMFLAG     ; player movement flag=1
               mov [si],al              
               inc bh
               cmp bh,64
               ja MAIN_LOOP
               ;mov [di+1],bh
               ;jmp MAIN_LOOP
               jmp MOVE_PLAYER

LEFT:          mov si,offset PAFFLAG
               mov al,2
               mov [si],al
               mov al,1                 ; SET
               mov si,offset PMFLAG     ; player movement flag=1
               mov [si],al              
               dec bl
               cmp bl,128
               ja MAIN_LOOP
               ;mov [di],bl
               ;jmp MAIN_LOOP
               jmp MOVE_PLAYER

RIGHT:         mov si,offset PAFFLAG
               mov al,3
               mov [si],al
               mov al,1                 ; SET
               mov si,offset PMFLAG     ; player movement flag=1
               mov [si],al              
               inc bl
               cmp bl,128
               ja MAIN_LOOP
               ;mov [di],bl
               ;jmp MAIN_LOOP
               jmp MOVE_PLAYER

     ;=================================================

               ; PLAYER MOVEMENT MODULE

     ;=================================================

MOVE_PLAYER:   ; The original routine is pushed lower into the
               ; program. At this points: creatures cannot walk
               ; throught the player. So now I want the player 
               ; not to walk throught creatures.

               mov si,offset FFLAG
               mov al,0
               mov [si],al

               mov dx,bx
               add bl,10
               add bh,5
               
               mov si,offset NOA
               xor ch,ch
               mov cl,es:[si]
               cmp cx,0
               je NOT_FOUND

               mov si,offset CCX
               
               ; AL holds the creature form because later I will
               ; make a little discrimination. The player can
               ; walk throught some but not all the creatures.

CHCREAF:       mov al,es:[si+512]
               cmp al,7                 ; PLAYER CAN WALK
               je NCRECF                ; THROUGHT SPIDERS.

               mov al,es:[si]
               cmp al,bl
               jne NCRECF
               mov ah,es:[si+256]
               cmp ah,bh
               jne NCRECF
               jmp MAIN_LOOP

NCRECF:        inc si
               loop CHCREAF

               ; Down here is the original routine before I add 
               ; something up to it. I will be testing the 
               ; modifications shortly.

;              mov dx,bx
               xor ax,ax
               ;add bl,10
               ;add bh,5
               mov al,bh
               rol ax,7       ; AX=(MY+Y)*128
               xor bh,bh
               add ax,bx      ; AX=(MY+Y)*128+MX+X
               add ax,offset LEVEL_DATA
               mov si,ax      ; SI=AX

               mov al,[si]
               cmp al,01      ; BRICK
               je NO_MOVE
               cmp al,27h     ; IF AL>= 27H AND AL<=31H
               jb NOMOVX      ; THEN NO_MOVE
               ;cmp al,31h
               cmp al,2ch
               ja NOMOVX
               jmp NO_MOVE
NOMOVX:        cmp al,44h     ; IF AL>=44 AND AL<= 5AH AND
               jb NOMOVX2     ; (AL AND 1) =0 THEN NO_MOVE
               cmp al,5ah
               ja NOMOVX2
               mov ah,al
               and ah,1
               cmp ah,0
               je NO_MOVE

NOMOVX2:       cmp al,0fh
               je HDOOR
               cmp al,11h
               je WDOOR
               cmp al,13h
               je MELDOOR
               cmp al,1fh
               je HDOOR
               cmp al,21h
               je WDOOR
               cmp al,23h
               je MELDOOR
               jmp NOMOVX3

HDOOR:         mov si,offset KEYS
DOORIMX:       mov al,[si]
               cmp al,1
               je NOMOVX3
               jmp NO_MOVE

WDOOR:         mov si,offset KEYS+1
               jmp DOORIMX

MELDOOR:       mov si,offset KEYS+2
               jmp DOORIMX

               ; J'ai rÇcemment identifiÇ un groupement de
               ; brique qui Ö travers lesquelles le
               ; joueur pouvait toujours passer Ö travers.
               ; Le code ci-dessous, permettra de corriger 
               ; la situation.

NOMOVX3:       

               ;==============================================
               ; La permission est donnÇe pour permettre le
               ; dÇplacement du joueur.
               ;==============================================

               mov di,offset MX
               mov [di],dl
               mov [di+1],dh
NO_MOVE:       jmp MAIN_LOOP

               mov ah,0
               int 16h
               jmp QUIT

    
;------------------------------------------------------------
               ;SPECIALS ROUTINES
;------------------------------------------------------------

                    ;----------------------------------------
                    ; GRAVITY
                    ; INPUTS:
                    ; SI:PLAYER OFFSET TO LEVEL
                    ; OUTPUTS
                    ; DL=0 NOT FALLING
                    ; DL=1 IF FALLING
                    ;----------------------------------------

               ;===========================================
               ; VÇrifie si le joueur est en Çtat de chute.
               ;===========================================

GRAVITY:       mov dl,0
               mov al,[si]
               cmp al,0
               je CHK_FALL
               cmp al,2
               je CHK_FALL
               cmp al,4
               je CHK_FALL
               cmp al,5ch
               je CHK_FALL
               cmp al,5eh
               je CHK_FALL
               cmp al,60h
               je CHK_FALL
               cmp al,62h
               je CHK_FALL
               cmp al,24h
               je CHK_FALL
               cmp al,40h
               je CHK_FALL

               cmp al,6ch
               jb XTRABLK
               cmp al,76h
               ja XTRABLK
               mov ah,al
               and ah,1
               cmp ah,1
               je XTRABLK
               jmp CHK_FALL

XTRABLK:

               ret
               ;jmp PLAYER_CONTROL

CHK_FALL:      mov al,[si+128]
               cmp al,0
               je FALL
               cmp al,2
               je FALL
               cmp al,3
               je FALL
               cmp al,4
               je FALL
               cmp al,8
               je FALL
               cmp al,9
               je FALL
               cmp al,0ah
               je FALL
               cmp al,0bh
               je FALL
               cmp al,0ch
               je FALL
               cmp al,40h
               je FALL

               cmp al,32h     ; On peut marcher sur un pont
               jb XBR00       ; mais pas par dessus.
               cmp al,3fh
               ja XBR00
               jmp FALL

XBR00:         cmp al,41h
               je FALL
               cmp al,5ch
               je FALL
               cmp al,5eh
               je FALL
               cmp al,60h
               je FALL
               cmp al,62h
               je FALL
               cmp al,24h
               je FALL
               cmp al,92h          ; EAU DE SURFACE AVEC STOP
               je FALL

               cmp al,6ch
               jb UXTRABLK
               cmp al,76h
               ja UXTRABLK
               mov ah,al
               and ah,1
               cmp ah,1
               je UXTRABLK
               jmp FALL
UXTRABLK:
               ret
               ;jmp PLAYER_CONTROL

FALL:          mov dl,1
               ret

                    ;-----------------------------------------
                    ; ADD_TO_SCORE
                    ; INPUTS:
                    ; CX: PTS TO ADD
                    ; OUTPUTS:
                    ; updates scores
                    ;-----------------------------------------

ADD_TO_SCORE:       pusha
ADDXXX:             mov si,offset SCORE+7
                    cmp cx,0
                    je ADDOUT
                    dec cx
ADDAGN:             mov al,[si]
                    inc al
                    mov [si],al
                    cmp al,9
                    jbe ADDXXX
                    mov al,0
                    mov [si],al
                    dec si
                    jmp ADDAGN

ADDOUT:             popa
                    ret

                    ;-----------------------------------------
                    ; GETAX
                    ; INPUTS:
                    ; no inputs
                    ; OUTPUS:
                    ; return a caracter from the buffer
                    ;-----------------------------------------

GETAX:              call NUM_LOCK
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
                    call CONVENSIONS
                    ret
          
               ;---------------------------------------------
               ; COLOR_TRANS
               ; INPUTS:
               ; BL: RESEARCH ; BH: MUTATE TO; DI: HEAD OF LINE
               ; OUTPUTS:
               ; Changes to main screen
               ;----------------------------------------------

COLOR_TRANS:   pusha
               mov cx,0a00h
COLOR_SEARCH:  mov al,gs:[di]
               cmp al,bl
               jne COLOR_NOT_BL
               mov gs:[di],bh
COLOR_NOT_BL:  inc di
               loop COLOR_SEARCH
               popa
               ret

               ;---------------------------------------------
               ; PFNT
               ; INPUTS:
               ; AL: NUMBER OF IMAGE; BL: X; BH: Y
               ; OUTPUTS:
               ; Generate FNT image
               ;---------------------------------------------

PFNT:               pusha
                    push ax
                    xor ah,ah                
                    rol ax,6  
                    mov si,ax      ; SI=images pointers
                    add si,offset NUMBERS_DATA
                    xor ah,ah      ; AH=0
                    mov al,bh      ; AL=BH
                    mov dx,0a00h   
                    mul dx         ; AX=Y*0a00h
                    xor bh,bh
                    rol bx,3       ; BX=X*64
                    mov di,ax
                    add di,bx      
                    pop ax
                    mov bx,8
FNT_NLINE:          mov cx,8
FNT_LINE:           mov al,[si]
                    cmp al,0
                    je FNT_ORIG
                    mov al,ah
FNT_ORIG:           mov fs:[di],al
FNT_OPIX:           inc si
                    inc di
                    loop FNT_LINE
                    add di,138h
                    mov cx,bx
                    dec bx
                    loop FNT_NLINE
                    popa
                    ret

               ;---------------------------------------------
               ; CUSTOM_INTRO_FRIEND
               ; INPUTS:
               ; BL: ACTOR X ; BH: ACTOR Y ; SI: FRAMES SI
               ;---------------------------------------------

CUSTOM_INTRO_FRIEND:pusha
               xor ax,ax
               mov al,bh
               mov dx,0a00h
               mul dx         ; AX= Y*0a00h
               xor bh,bh
               rol bx,3       ; BX= X*8
               add ax,bx      ; AX= Y*0a00h + X*8
               mov di,ax      ; DI= AX

               mov bx,16
MORE_MCG:      mov cx,4

MORE_MCG_:     mov eax,es:[si]
               mov gs:[di],eax
               add si,4
               add di,4
               loop MORE_MCG_
               
               mov cx,bx
               dec bx
               add di,130h
               loop MORE_MCG

               mov cx,0a00h/4
               mov di,-0a00h
               mov eax,01010101h
MORE_BLUE:     mov gs:[di],eax
               add di,4
               loop MORE_BLUE
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
            call BYFADE
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
          add si,offset LEVEL_DATA
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
               jmp MAIN_LOOP

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


               ;============================================
               ; WAITFORAKEY
               ; INPUTS:
               ; no inputs
               ; OUTPUTS:
               ; wait for a key to be pressed
               ;============================================

WAITFORAKEY:   
CALLB:         call GETAX
               and al,al
               jne CALLB
               
CALLA:         call GETAX
               and al,al
               je CALLA
               ret





































               ;==============================================
               ; C'est le temps de mettre un peu d'animation
               ; dans le jeu. J'espäre commencer par la lave
               ; de volcan et puis faire bouger l'eau et les
               ; transporteurs.
               ;================================================

NEW_ANIMATIONS:pusha          
               
               cmp al,41h          ; Subtance dissolvante (haut)
               je LAVA01
               cmp al,24h          ; Eau de surface
               je WATER01
               cmp al,92h          ; Eau de surface avec STOP
               je WATER01
               cmp al,25h          ; êchelle de surface
               je WATER02
               cmp al,26h          ; Racine de surface
               je WATER03

               cmp al,6bh
               je TRANS01
               cmp al,6dh
               je TRANS01
               cmp al,6fh
               je TRANS01

               cmp al,71h
               je TRANS02
               cmp al,73h
               je TRANS02
               cmp al,75h
               je TRANS02

               popa
               jmp NORMALPRN

;-------------------------------------------

LAVA01:        ; Subtance dissolvante (haut)
               mov ax,100h
               call FIRSTOUT
OUTANI:        popa
               jmp RETWISE

;-------------------------------------------

LAVA02:        ; Mur de brique lava-surface
               push di
               mov ax,100h
               call FIRSTOUT
               pop di
               mov ax,2800h
               call PXMCG
               jmp OUTANI

               ;-------------------------------------------
               ; Routine d'impression d'un dÇcors de fond 
               ; possÇdant des propriÇtÇs d'animation
               ; particuliäret qui doit donc àtre manipulÇ
               ; de faáon träs spÇciale.
               ;-------------------------------------------

FIRSTOUT:      mov si,offset AOFFLAG
               xor bh,bh
               mov bl,[si]
               rol bx,8
               mov si,offset ANIMATIONS
               add si,ax
               add si,bx

               mov bx,16
FLINE:         mov cx,4
SLINE:         mov eax,es:[si]
               mov fs:[di],eax
               add si,4
               add di,4
               loop SLINE
               add di,130h
               mov cx,bx
               dec bx
               loop FLINE
               ret

PXMCG:         mov si,offset IMAGES_MCG
               add si,ax
               mov bx,16
PFINLINE:      mov cx,16
PLINE:         mov al,[si]
               cmp al,0
               je NTPNT
               mov fs:[di],al
NTPNT:         inc si
               inc di
               loop PLINE
               mov cx,bx
               dec bx
               add di,130h
               loop PFINLINE
               ret

BLANKIT:       push di
               xor eax,eax
               mov bx,16
XXXL:          mov cx,4
XXL:           mov fs:[di],eax
               add di,4
               loop XXL
               add di,130h
               mov cx,bx
               dec bx
               loop XXXL
               pop di
               ret

RSTOO:         ;===========================
               ; RSTOO
               ; INPUTS:
               ; AX: 0, 100h or 200h
               ; OUTPUTS:
               ; Prints a superposed MCG
               ;==========================

               mov si,offset AOFFLAG
               xor bh,bh
               mov bl,[si]
               rol bx,8

               mov si,ax
               add si,offset ANIMATIONS
               add si,bx

               mov bx,16
RSXXXL:        mov cx,16
RSXXL:         mov al,es:[si]
               cmp al,0
               je RNPIX
               mov fs:[di],al
RNPIX:         inc si
               inc di
               loop RSXXL
               add di,130h
               mov cx,bx
               dec bx
               loop RSXXXL
               ret

               ;=============

WATER01:       ; Eau de surface
               xor ax,ax
               call FIRSTOUT
               jmp OUTANI

WATER02:       ; êchelle de surface
               push di
               xor ax,ax
               call FIRSTOUT
               pop di
               mov ax,600h
               call PXMCG
               jmp OUTANI

WATER03:       ; Racine de surface
               push di
               xor ax,ax
               call FIRSTOUT
               pop di
               mov ax,700h
               call PXMCG
               jmp OUTANI

TRANS01:       ; TRANSPORTERS OUTSIDE WATER
               mov ax,200h
               call FIRSTOUT
               jmp OUTANI

TRANS02:       ; TRANSPORTERS UNDER WATER
               call BLANKIT
               
               push di
               mov ax,1400h
               call PXMCG
               pop di

               push di
               mov ax,200h
               call RSTOO
               pop di
               
               jmp OUTANI

               ;===============================
               ; CHKWP
               ; INPUTS:
               ; SI: offset of wanted position
               ; OUTPUTS:
               ; DL=0 : can move
               ; DL=1 : can't move
               ;===============================

CHKWP:         push ax
               xor dl,dl
               mov al,[si]
               mov ah,al
               and ah,1

               cmp al,1
               je ASTOP
               cmp al,0fh
               je HDOOR_C
               cmp al,11h
               je WDOOR_C
               cmp al,13h
               je MDOOR_C
               
               cmp al,1fh
               je HDOOR_C
               cmp al,21h
               je WDOOR_C
               cmp al,23h
               je MDOOR_C

               cmp al,28h
               jb SOSOEA
               cmp al,2ch
               ja SOSOEA
               jmp ASTOP

SOSOEA:        cmp al,44h
               jb SOSOEB
               cmp al,5ah
               ja SOSOEB
               cmp ah,1
               je SOSOEB
               jmp ASTOP

HDOOR_C:
WDOOR_C:
MDOOR_C:
ASTOP:         inc dl
SOSOEB:        pop ax
               ret

               ;===============================
               ; GETSSI
               ; INPUTS:
               ; no inputs
               ; OUTPUTS
               ; SI= ([MY]+5)*128+MX+10+offset
               ;===============================

GETSSI:        mov si,offset FFLAG
               mov al,0
               mov [si],al

               
               mov si,offset MX
               xor ah,ah
               mov al,[si+1]
               add ax,5
               rol ax,7                 ; AX=(MY+5)*128


               mov bl,[si]              ; AX=(MY+5)*128+MX+10
               xor bh,bh
               add ax,bx
               add ax,10
               add ax,offset LEVEL_DATA ; AX=(MY+5)*128+MX+10+off
               mov si,ax
               ret

               ; Je pense qu'il est temps de se mettre Ö sauter
               ; gauche/droite. Apräs tout, n'est-ce pas lÖ une
               ; des grandes inventions d'unlucky adventurer? Le
               ; principe est simple. 

               ; [JMPFLAG]=1 ; ce qui paralyse PLAYER_CONTROL

               ;--------------------------------
JMP_LEFT:      call GETSSI

               dec si
               call CHKWP
               cmp dl,1
               je MAIN_LOOP

               dec si
               call CHKWP
               cmp dl,1
               je FJUMPL

               mov si,offset JMPFLAG
               mov al,1
               mov [si],al

               mov si,offset PAFFLAG
               mov al,2
               mov [si],al

               mov si,offset PMFLAG
               mov al,1
               mov [si],al

               mov si,offset MX
               mov al,[si]
               dec al
               mov [si],al
               jmp MAIN_LOOP

FJUMPL:        mov si,offset MX
               mov al,[si]
               dec al
               mov [si],al

               mov si,offset PMFLAG
               mov al,1
               mov [si],al

               mov si,offset PAFFLAG
               mov al,2
               mov [si],al

               jmp MAIN_LOOP

               ;-------------------------------
JMP_RIGHT:     call GETSSI

               inc si
               call CHKWP
               cmp dl,1
               je MAIN_LOOP

               inc si
               call CHKWP
               cmp dl,1
               je FJUMPR

               mov si,offset JMPFLAG
               mov al,1
               mov [si],al

               mov si,offset PAFFLAG
               mov al,3
               mov [si],al

               mov si,offset PMFLAG
               mov al,1
               mov [si],al

               mov si,offset MX
               mov al,[si]
               inc al
               mov [si],al
               jmp MAIN_LOOP

FJUMPR:        mov si,offset MX
               mov al,[si]
               inc al
               mov [si],al

               mov si,offset PMFLAG
               mov al,1
               mov [si],al

               mov si,offset PAFFLAG
               mov al,3
               mov [si],al

               jmp MAIN_LOOP

               ;=================================
               
KEYQUIT:       call GETAX
               cmp al,27
               je QUIT
               cmp al," "
               je PAUSE_GAME
               jmp MAIN_LOOP

               ;==================================

NEUTRAL_KEYS:  call GETAX
               cmp ax,0
               jne NEUTRAL_KEYS
               ret

BYFADE:        pusha
               mov si,offset MOUSE_CTRL
               mov al,[si]
               cmp al,0
               je VPOPA_
               call WBUT
               and bx,2
               cmp bx,2
               je NEWTASK
VPOPA_:        popa
               ret
NEWTASK:       mov sp,bp
               jmp RETFROMBYFADE

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

               ;---------------------------------------
               ; SPIWALKCOND
               ; INPUTS:
               ; SI: WANTED POSITION
               ; OUTPUTS:
               ; DL=1 ; can't move
               ;---------------------------------------

SPIWALKCOND:   push ax
               mov al,[si]
               cmp al,0
               je SPIWM
               mov ah,al
               and ah,254

               cmp al,5ch
               jb SPIC1
               cmp al,62h
               ja SPIC1
               cmp al,ah
               jne SPIC1
               jmp SPIWM

SPIC1:         cmp al,6ch
               jb SPIC2
               cmp al,76h
               ja SPIC2
               cmp al,ah
               jne SPIC2
               jmp SPIWM

SPIWM:         inc dl
SPIC2:         pop ax
               ret















































     ;=================================================
     ;         HISCORES_VLA   GESTIONS
     ;=================================================
YOU_WIN2:
GAME_OVER_MODULE:

            ;jmp BYGAMEOVERMODE

               mov si,offset SCORE
               mov di,offset HISCORES + 17*40
               mov dx,18

CMPNHSC:       mov cx,8
               xor bx,bx
CMPMORETHAT:   mov al,[si+bx]
               cmp al,es:[di+bx]
               jb TOO_SMALL
               ja BIGGER_THAN
               inc bx
               loop CMPMORETHAT
               jmp TOO_SMALL
               
BIGGER_THAN:   mov cx,40
               xor bx,bx
TRSC:          mov al,es:[di+bx]
               mov es:[di+bx+40],al
               xor al,al
               mov es:[di+bx],al
               inc bx
               loop TRSC

               push si
               mov si,offset LEV00_VLA + 3
               mov al,[si]
               sub al,30h
               mov es:[di+10-1],al
               mov al,[si+1]
               sub al,30h
               mov es:[di+11-1],al
               pop si

               mov cx,8
               xor bx,bx
TRNSC:         mov al,[si+bx]
               mov es:[di+bx],al
               inc bx
               loop TRNSC

               cmp dx,1
               jbe DYSPLAY_HIS2V

               mov cx,dx
               dec dx
               sub di,40
               loop CMPNHSC
               inc dx

TOO_SMALL:     ;push di            ; MODIFICATION
               ;mov si,offset HPOINT
               ;inc dl
               ;inc dl
               push dx             ; MODIFICATION
               mov al,18
               sub al,dl
               ;mov [si],al
               mov bh,al
               jmp DYSPLAY_HIS

DYSPLAY_HIS2V: dec dx
               push dx           ; MODIFICATION
               mov bh,18

DYSPLAY_HIS:   call CLS

               xor eax,eax
               xor si,si
               mov cx,(0a00h*2)/4
BLANKBFF:      mov fs:[si],eax
               add si,4
               loop BLANKBFF

               mov dx,MEM2
               mov gs,dx

               mov si,offset HIHO
               xor di,di
               call PMCGS

               call CONVENSIONS

               mov cx,0a00h*2
               xor si,si
CHANGEMORE:    mov al,fs:[si]
               cmp al,0
               je NOTCHANGED
               cmp al,19
               je NOTCHANGED
               mov ah,(4*8)+1+1; light orange => blue
               cmp al,5*8+2
               je CHANGE
               mov ah,(4*8)+3+1
CHANGE:        mov al,ah
               mov gs:[si],al
NOTCHANGED:    inc si
               loop CHANGEMORE
               
               ;------------------------------------

               ; Dysplay routine to show score board
               ; to the player when he is dead.

               ;-------------------------------------

               mov di,3*0a00h
               mov si,offset HISCORES

               mov bl,18
TRANSLINE:     cmp bl,bh
               jne LEAVE_BP
               mov bp,si

LEAVE_BP:      push di
               mov cx,40

TRANSSQR:      push si
               push di
               push cx

               mov al,es:[si]
               cmp cl,30+2
               ja THISNUM
               cmp cl,29+2
               je THISNUM
               cmp cl,28+2
               je THISNUM
               jmp NNUMF1
THISNUM:       add al,30h

NNUMF1:        cmp al,0
               jne NNZERO
               mov al,32

NNZERO:        mov si,offset ASCII_TABLE
TRYMASCII:     cmp al,[si]
               je FONTMATCH
               inc si
               cmp si,offset ASCII_TABLE + 100
               je FONTMATCH_ERROR
               jmp TRYMASCII

FONTMATCH_ERROR:nop
FONTMATCH:     sub si,offset ASCII_TABLE
               rol si,8       ; SI=SI*256
               add si,offset FONTS

               mov dx,8
TRANSPIXL2:    mov cx,8
TRANSPIXL:     mov al,es:[si]
               ;cmp bl,bh
               ;jne PRNIMED
               cmp al,0
               je PRNIMED
               cmp al,19
               je PRNIMED
               
               cmp bl,bh
               je YELLOW

               mov ah,bl
               inc ah
               and ah,2
               inc ah
               inc ah
               rol ah,1
               sub al,ah
               jmp PRNIMED


YELLOW:        mov al,14
               ;add al,20

PRNIMED:       mov gs:[di],al
               inc si
               inc si
               inc di
               loop TRANSPIXL

               mov cx,dx
               dec dx
               add di,138h
               add si,16
               loop TRANSPIXL2

               pop cx
               pop di
               pop si
               inc si
               add di,8
               loop TRANSSQR

               pop di
               add di,0a00h
               mov cl,bl
               dec bl
               loop TRANSLINE_LINK
               jmp K9
TRANSLINE_LINK:jmp TRANSLINE
K9:            



               call CONVENSIONS

               add di,0a00h
               mov si,offset WRITE_HIS
               mov [si],bh
     
               cmp bh,0
               je SORRYISP
               
               mov si,offset WRITE_NAME
               call P_COMMENT
               jmp ELSE_
               
SORRYISP:      mov si,offset SORRY
               call P_COMMENT

ELSE_:         cmp bh,0
               je KEYP

               ; Il faut permettre au joueur d'Çcrire son
               ; nom. 

               ;mov al,bh
               ;sub al,15
               pop ax
               add ax,3

               xor ah,ah
               mov cl,0ah
               mul cl
               rol ax,8
               mov di,ax
               add di,8*12
               mov si,bp

               mov bx,12

PRINT_CURSOR:  ;mov al,"ê"
               ;call P_LETTERS
               call P_CURSOR
               mov al,20
               mov es:[si+bx],al

PRINT_NAME_LOOP:call GETAX
               cmp al,"a"
               jb OCSA1
               cmp al,"z"
               ja OCSA1
               jmp CPCOND

OCSA1:         cmp al," "
               je CPCOND
               cmp al,"!"
               je CPCOND
               cmp al,34
               je CPCOND
               cmp al,"["
               je CPCOND
               cmp al,"]"
               je CPCOND
               cmp al,"'"
               je CPCOND

               cmp al,"0"
               jb OCSA2
               cmp al,"9"
               ja OCSA2
               jmp CPCOND

OCSA2:         cmp al,13
               je ENTER_NAME
               cmp al,8
               je BACKSPACE
               jmp PRINT_NAME_LOOP

CPCOND:        cmp bx,39
               je PRINT_NAME_LOOP
               mov es:[si+bx],al
               inc bx
               call P_LETTERS
               add di,8
               jmp PRINT_CURSOR

BACKSPACE:     cmp bx,12
               je PRINT_NAME_LOOP
               mov al," "
               call P_LETTERS
               mov es:[si+bx],al
               sub di,8
               dec bx
               jmp PRINT_CURSOR

ENTER_NAME:    mov al," "
               call P_LETTERS
               mov es:[si+bx],al

               mov si,0dc00h
               mov cx,0a00h/4
               xor eax,eax
CLRWRITE:      mov gs:[si],eax
               add si,4
               loop CLRWRITE

               ; CRêE HISCORES_VLA

               mov dx,offset HISCORES_VLA
               call MAKEPATH
               call CONVENSIONS
               mov ah,3ch
               mov dx,offset FILENAME
               xor cx,cx
               int 21h
               jc NOT_FOUND

               push ax
               mov bx,ax           ; code d'accäs
               mov dx,MEM1         ; SEGMENT SOURCE
               mov ds,dx           ; [DS:DX]
               mov dx,offset HISCORES
               mov cx,20*40
               mov ah,40h          ; êcriture d'un fichier...
               int 21h
               jc NOT_FOUND

               pop bx
               mov ah,3eh               
               int 21h
               jc NOT_FOUND

KEYP:          mov ah,0
               int 16h

               jmp RESTART_GAME
               jmp QUIT























               ;------------------------------------------
               ; P_COMMENT
               ; INPUTS:
               ; [DS:SI] pointers to start of sequence
               ; [GS:DI] destination of sequence
               ; OUTPUTS:
               ; "sorry you didn't play well enough!" or
               ; "enter name and enter when done!"
               ;------------------------------------------

P_COMMENT:     pusha
READCOM:       mov al,[si]
               cmp al,0
               je PCOMMOUT
               call P_LETTERS
               add di,8
               inc si
               jmp READCOM
PCOMMOUT:      popa
               ret

               ;-------------------------------------------
               ; P_LETTERS
               ; INPUTS:
               ; al font
               ; [GS:DI] destination of sequence
               ; OUTPUTS:
               ; a letter is printed
               ;-------------------------------------------


P_LETTERS:     pusha
               mov si,offset ASCII_TABLE
CLETTER:       cmp al,[si]
               je ASCII_MATCH
               inc si
               cmp si,offset ASCII_TABLE +100
               je ASCII_ERR
               jmp CLETTER

ASCII_ERR:     nop
ASCII_MATCH:   sub si,offset ASCII_TABLE
               rol si,8
               add si,offset FONTS
               
               mov bx,8
TRLPIX2:       mov cx,8
TRLPIX:        mov al,es:[si]
               cmp al,0
               je NOTCONV
               cmp al,19
               je NOTCONV
               mov al,14
NOTCONV:       mov gs:[di],al
               inc si
               inc si
               inc di
               loop TRLPIX
               mov cx,bx
               dec bx
               add si,16
               add di,138h
               loop TRLPIX2
               popa
               ret

               ;-----------------------
               ; P_CURSOR
               ; INPUTS:
               ; [GS:DI] = positions
               ; OUTPUTS:

               ; printed yellow cursor
               ;-----------------------
     
P_CURSOR:      pusha 
               mov eax,0e0e0e0eh
               mov cx,8
PCLINE:        mov gs:[di],eax
               add di,4
               mov gs:[di],eax
               add di,138h+4
               loop PCLINE
               popa
               ret

               ;----------------------------------------
               ; THIS IS THE AUXILARY INTRODUCTION
               ; USED WHEN NO MOUSE CONTROL IS AVAILABLE
               ;----------------------------------------
               ;==================================
               ; BPMCGS
               ; INPUTS:
               ; SI: source of string
               ; DI: destination of printed string
               ; OUTPUTS:
               ; string printed
               ;===================================

KEYBOARD_INTRO: 
               call CONVENSIONS
               mov si,offset I_THE
               mov di,0a00h*4
               call BPMCGS

               mov si,offset I_VLAMITS
               add di,0a00h*6
               call BPMCGS

               mov bx,20
               mov ax,-1
               mov si,-100h
               mov cx,9

S8L2:          add si,100h
               add ax,4
               call PMCG
               loop S8L2

               ;Affiche "By Francois Blanchette."
               mov si,offset MSQ_TYPE_DATA
               mov di,17*0a00h
               mov cx,0a00h
CHK_A_PIXEL_FBX:mov al,es:[si]
               cmp al,0
               je BLACK_PIXEL_FOR_FBX
               mov al,14
               mov ax,di
               and ax,0fh
               or ax,2
               mov gs:[di],al
BLACK_PIXEL_FOR_FBX:inc di
               inc si
               loop CHK_A_PIXEL_FBX

               mov di,23*0a00h
               mov si,offset KEYSELECT
               call P_COMMENT

KEYSCAN_:      call GETAX
               cmp al,30h
               jb KEYSCAN_
               cmp al,39h
               ja KEYSCAN_
               
               sub al,31h
               mov dl,al
               jmp CMEM
               jmp QUIT

               ;-----------------------------------------------
               ; PLAYER_G
               ; INPUTS:
               ; no inputs
               ; OUTPUTS:
               ; DL=0 not falling
               ; DL=1 falling
               ;              
               ; NOTE: This routine scan under the player to
               ;       see if a creature below him can support
               ;       him. If so, DL=0 but if not, then DL=1.
               ;-----------------------------------------------

PLAYER_G:      mov si,offset MX
               mov al,[si]
               mov ah,[si+1]
               add al,10
               add ah,6
               mov dl,1

               mov si,offset NOA
               mov cl,es:[si]
               xor ch,ch

               mov di,offset CCX
CNAPU:         cmp es:[di],al
               jne NPAC
               cmp es:[di+256],ah
               jne NPAC
               dec dl
               ret

NPAC:          inc di
               loop CNAPU
               ret

               ;--------------------------------------------
               ; FISH_BIT
               ; INPUTS:
               ; SI = wanted position
               ; OUTPUTS:
               ; DL=0 : can move
               ; DL=1 : can't move
               ;--------------------------------------------

FISH_BIT:      push ax
               mov dl,1
               mov al,[si]

               mov ah,al
               and ah,254

               cmp al,14h          
               je FM

               cmp al,16h          
               jb XFB1
               cmp al,1eh
               ja XFB1
               jmp FM

XFB1:          cmp al,20h
               je FM
               cmp al,22h
               je FM

               cmp al,24h
               jb XFB2
               cmp al,27h
               ja XFB2
               jmp FM

XFB2:          cmp al,2dh
               jb XFB3
               cmp al,31h
               ja XFB3
               jmp FM

XFB3:          cmp al,64h
               jb XFB4
               cmp al,6ah
               ja XFB4
               cmp al,ah
               jne XFB4
               jmp FM

XFB4:          cmp al,71h
               jb XFB5
               cmp al,75
               ja XFB5
               cmp al,ah
               je XFB5
               jmp FM

XFB5:          pop ax
               ret

FM:            dec dl
               pop ax
               ret

               ;-----------------------------------------------

CHANGE_SPEED:  jmp MAIN_LOOP
               call CLS
               ;mov si,offset SELECT_SPEED
               mov di,11*0a00h
               call P_COMMENT

               ;mov si,offset CURRENT
               add di,0a00h*2
               call P_COMMENT

CHECK_AX:      call GETAX
               cmp ah,59
               je CONTINUE_GAME
               jmp CHECK_AX

               ;-----------------------------------------------

CONTINUE_GAME: mov cx,65536/4
               xor si,si
TOCONTGAME:    mov eax,fs:[si]
               mov gs:[si],eax
               add si,4
               loop TOCONTGAME
               jmp MAIN_LOOP

               ;-------------------------------------------------

               jmp QUIT

ERASE_HIS:     xor di,di
               mov si,offset ERASEHIS
               call P_COMMENT

GETAX_WAIT:    call GETAX
               cmp al,"y"
               je ERASEYES
               cmp al,0
               jne CONTINUE_GAME
               jmp GETAX_WAIT

ERASEYES:      mov di,offset HISCORES
               mov al,0
               mov cx,21*40
CLEAR_ALL:     mov es:[di],al
               inc di
               loop CLEAR_ALL

               mov dx,offset HISCORES_VLA
               call MAKEPATH

               mov dx,offset FILENAME   ; NOM DU FICHIER
               mov ah,3ch               ; CRêATION
               mov cx,0                 ; MODE D'ACCëS
               int 21h

               jc NOT_FOUND

               mov bx,ax                ; CODE D'ACCëS
               push ax
               mov dx,offset TEXT_SP    ; ZONE SOURCE
               mov cx,1                 ; DIMENSION
               mov ah,40h               ; êCRITURE
               int 21h
               jc NOT_FOUND

               pop bx
               mov ah,3eh
               int 21h
               jc NOT_FOUND
               jmp CONTINUE_GAME

EDITOR:        jmp MAIN_LOOP

; -----------------------FIN DU PROGRAMME-----------------------
VLAMITS    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END     VLAMITS                           ; Point d'entree
;---------------------------------------------------------------
