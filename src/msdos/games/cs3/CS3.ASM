;----------------------------------------------------------------
;       CREEPSPREAD III: NAN'O lost V2.0
;       by Francois Blanchette
;----------------------------------------------------------------


SMOUSE  MACRO
        push ax
        mov ax,1
        int 33h
        pop ax
        ENDM

HMOUSE  MACRO
        push ax
        mov ax,2
        int 33h
        pop ax
        ENDM


;----------------------------------------------------------------
ASSUME CS:CODE,DS:DATA,SS:STACK
STACK     SEGMENT STACK
          DB 400H DUP  (0)
STACK     ENDS
;----------------------------------------------------------------

;----------------------------------------------------------------
DATA      SEGMENT

COPYRIGHT      db "CREEPSPREAD III: NAN'O LOST V2.0"
               db  " (C) 1993 FRANCOIS BLANCHETTE."
OLD_VIDEO_MODE db 0           

LEVEL_DATA     db 4096  DUP (0)
MCG_IMAGES     db 16384 DUP (0)
MCG_ANI        db 4096  DUP (0)
MSQ_IMAGES     db 4096  DUP (0)
MSQ_MESSAGE    db 640   DUP (0)
HI_SCORES      db 40*(19+1) DUP (0)
LEV00_CS3      db "LEV00.CS3",0
CS3GAME_MCG    db "CS3GAME.MCG",0
CS3EDIT_MCG    db "CS3EDIT.MCG",0
CS3FONT_MSQ    db "CS3FONT.MSQ",0
CS3ANI_MCG     db "CS3ANI.MCG",0
CS3OVER_MSQ    db "CS3OVER.MSQ",0
CS3WIN_MSQ     db "CS3WIN.MSQ",0
HISCORES_CS3   db "HISCORE_.CS3",0
DEFAULTS_CS3   db "DEFAULTS.CS3",0
;PATH           db "C:\other\cs3\",0
PATH           db 0
FILENAME       db 32 DUP (0)
MX             db 0
MY             db 0
WX             db 0
WY             db 0

KEYS           db 0,0,0,0
ACTOR_X        db 255 DUP (0)
ACTOR_Y        db 255 DUP (0)
ACTOR_AIM      db 255 dup (1)
ACTOR_NUMBERS  db 0

LIFE_FORCE     db 64,0
HPOINT         db 0

LV        db 0
PV        db 0
SC        db 8 DUP (0)
DIAMONDS  db 0,0,0
SFLAG     db 0,0
AFLAG     db 0

DIR       db 2,4,1,3
          db 1,3,2,4
          db 4,1,3,2
          db 3,2,4,1

SPEEDA    db 4
SPEEDB    db 6

TITRES      db "Grab the diamonds but don't get killed.",0
            db "Better run fast.",0
            db "Think fast and well.",0
            db "The masterpiece level.",0
            db "Are you smart enought for it?",0
            db "I've a new one for ya.",0
            db "You'll fell deja vu.",0
            db "Prepare for your doom.",0

LEVEL          db "LEVEL ??",0
FILES_DOWN     db "Warning: file not found error.$"
MOUSE_DOWN     db "Warning: missing mouse and/or drive.$"
RESUME         db "Press [space] to resume playing...$"
WRITE_NAME     db "WRITE NAME AND [ENTER] WHEN DONE!",0
SORRY          db "SORRY YOU DIDN'T PLAY WELL ENOUGH.",0
TOP_SCORES     db "               TOP SCORES",0
SELECT_SPEED   db "Please select game's speed: (1-9)$"
CURRENT_SPEED  db "Current speed:0$"
SELECT_SPEEDA  db 0
CONFIRM        db "Erase highs scores, please confirm?$"

;LEVEL EDITOR'S MODIFICATIONS

CLEAR_MAZE_TEXT     db "Are you sure you want to clear maze?$"
LOADNUM  db "Enter level number to be loaded:$"
SAVENUM  db "Enter level number to be saved:$"
CARAC     db 0
;MX       db 0
;MY       db 0

CD        db 0
OUT_OF_THIS_WORLD   db 0,0
NUM       db 3,0,0,0

DATA   ENDS
;----------------------------------------------------------------
CODE    SEGMENT
BEGINN  PROC NEAR                                     
;----------------------------------------------------------------

          .386

READY_FOR_IT:  mov ah,0fh
          int 10h   
          mov dx,DATA
          mov ds,dx
          mov di,offset OLD_VIDEO_MODE
          mov [di],al
          
SET_VIDEO:mov ah,0
          mov al,13h
          ;mov al,9h
          int 10h

          ;-----------------------------------------------------

          ; SETUP CENTRAL:
          ; 1) Chargement des donnÈes permanente
          ; 2) PrÈparation ‡ une nouvelle partie

          ; Chargement de CS3GAME.MCG
PREPARE_GAME:  mov dx,DATA
          mov ds,dx
          mov es,dx
          mov dx,offset CS3GAME_MCG
          mov bx,offset MCG_IMAGES
          mov cx,16384
          call LOADOLD
          jc NOT_FOUND

          ; CHARGEMENT de CS3FONT.MSQ
          mov dx,DATA
          mov ds,dx
          mov es,dx
          mov dx,offset CS3FONT_MSQ
          mov bx,offset MSQ_IMAGES
          mov cx,4096
          call LOADOLD
          jc NOT_FOUND

          ; CHARGEMENT de CS3ANI.MCG
          mov dx,DATA
          mov ds,dx
          mov es,dx
          mov dx,offset CS3ANI_MCG
          mov bx,offset MCG_ANI
          mov cx,4096
          call LOADOLD
          jc NOT_FOUND

          ; CHARGEMENT DE HISCORE_.CS3
          mov dx,DATA
          mov ds,dx
          mov es,dx
          mov dx,offset HISCORES_CS3
          mov bx,offset HI_SCORES
          mov cx,19*40
          call LOADNEW
          jc NOT_FOUND

          ; CHARGEMENT DE DEFAULTS.CS3
          mov dx,DATA
          mov ds,dx
          mov es,dx
          mov dx,offset DEFAULTS_CS3
          mov bx,offset SPEEDA
          mov cx,2
          call LOADNEW
          jc NOT_FOUND

       ; -------------------------------------------------------
          ; Prepare for a new game
NEW_GAME: call CONVENSIONS

          mov al,0
          mov si,offset LV     ; LV=0
          mov [si],al

          mov cx,8
          mov si,offset SC      ; SC=0
ASCSIP:   mov [si],al
          inc si
          loop ASCSIP         

          mov ax,3030h
          mov si,offset LEV00_CS3 +3
          mov [si],ax

          mov al,64
          mov si,offset LIFE_FORCE
          mov [si],al

       ;-------------------------------------------------------

          ; PrÈparation ‡ un nouveau tableau
PREPARE_LEVEL: call CONVENSIONS

          mov si,offset LV         ; LV=LV+1
          mov al,[si]
          inc al
          mov [si],al

          cmp al,8                 ; NUMBER OF ACTIVE LEVELS +1
          je YOU_WIN

          push ax

          ;--------------------------------------------------<<<

          ;mov eax,01010101h        ; NO KEY...
            mov eax,0
          mov si,offset KEYS
          mov [si],eax

          mov si,offset PV         ; PV = 0
          mov [si],al


          ; Conversion de LV en digits

          mov si,offset LEV00_CS3+4
          mov al,[si]
          inc al
          cmp al,03ah
          jne SLVDIGITS
          mov al,30h
          
          mov ah,[si-1]
          inc ah
          mov [si-1],ah

SLVDIGITS:     mov [si],al
          call CLS         ; CLS

          ;---------------------------------------------------<<<

          ; LOCATE 12,16
          ; PRINT "LEVEL ??"

          pop ax
          push ax

          call CLS

          ;push ax
          mov si,offset LEV00_CS3
          mov di,offset LEVEL
          mov bl,[si+3]
          mov bh,[si+4]
          mov [di+6],bl
          mov [di+7],bh
          
          mov cx,8
          mov bl,al
          add bl,32

          mov dl,16-1

NEXT_LEVEL__:  mov bh,0
          ;mov dl,16-1      ; x=16
          mov dh,12-1         ; y=12
          mov ah,2
          pusha
          int 10h        ; SET COORDONATES
          popa

          mov al,[di]
          mov ah,0eh
          pusha
          int 10h        ; AFFICHE UN CHARACTER 
          popa

          inc di
          inc dl

          loop NEXT_LEVEL__

          ;-----------------------------------------------------
          pop ax
          mov bl,al
          add bl,33
          push bx
          ;-----------------------------------------------------

                    ; FIND TITLES' POINTERS
          
          mov si,offset TITRES
          cmp al,1
          je FOUND_TITLES
          xor cx,cx
          mov cl,al
          dec cl

SEEK_A:   xor dl,dl      
SEEK_0:   mov al,[si]
          inc si
          cmp al,0
          je SEEK_1

          jmp SEEK_0

SEEK_1:   loop SEEK_A
          
FOUND_TITLES:  mov cx,40
               xor bx,bx
LOOK_AT_NEXT:  mov al,[si+bx]
               cmp al,0
               je TIT_ONO
               inc bx
               loop LOOK_AT_NEXT

TIT_ONO:       sar cx,1
               pop bx
               mov dl,cl
               mov dh,12
               
PRN_TITRE:     mov ah,2
               mov bh,0  ;page d'Çcran
               pusha
               int 10h
               popa

               mov al,[si]; charactäre source...
               cmp al,0
               je END_TITRE
               mov ah,0eh
               pusha
               int 10h
               popa

               inc si
               inc dl
               
               jmp PRN_TITRE
END_TITRE:

          mov cx,200
AGAIN:    call SOME_TIME_OFF
          call GETAX
          cmp ax,0
          jne OFF_TO_MOON
          loop AGAIN

          ;---------------------------------------------------<<<

          OFF_TO_MOON:

          ;mov ah,0
          ;mov al,13h
          ;int 10h


          ; Chargement de LEV00.CS3
RESTORE_LEVEL:          mov dx,DATA
          mov ds,dx
          mov es,dx
          mov dx,offset LEV00_CS3
          mov bx,offset LEVEL_DATA
          mov cx,4096
          call LOADOLD        
          jc NOT_FOUND

          call CONVENSIONS



                                        
          ; Identification de position de Nancy
          xor ax,ax
          mov si,offset LEVEL_DATA
          mov dx,64
NNANOY:        mov cx,64
NNANOX:        mov bl,[si]
          cmp bl,2
          je NANOPOS
          inc al
          inc si
          loop NNANOX
          mov al,0
          inc ah
          mov cx,dx
          dec dx
          loop NNANOY
          jc NOT_FOUND

NANOPOS:  mov dl,25h
          mov [si],dl
          add al,-10
          add ah,-5
          mov di,offset MX
          mov [di],al
          mov [di+1],ah
          ;call SHOW_SCREEN                  

          ; Affichage de "CREEPSPREAD III by Francois Blanchette"
          mov si,10*64+offset MSQ_IMAGES
          mov di,0a00h*22
          mov cx,0a00h/4
SHOW_FB:  mov eax,[si]
          mov gs:[di],eax
          add di,4
          add si,4
          loop SHOW_FB

          ; Put Gray upon black spots in the score position
GRAY_IN:  mov di,0a00h*22
          mov cx,(3*0a00h)
GRYIN:         mov al,gs:[di]
          cmp al,0
          jne GRYON
          mov al,8
          mov gs:[di],al
GRYON:         inc di
          loop GRYIN

          ; Clear "Actors Aim" ...
          mov cx,255
          mov al,1
          mov di,offset ACTOR_AIM
CL_AC_AIM:mov [di],al
          inc di
          loop CL_AC_AIM

          ; Find "Actors"

          mov si,offset LEVEL_DATA
          mov di,offset ACTOR_X
          xor bx,bx
          xor dx,dx

          mov ah,64
FACT01:   mov cx,64
FACT02:   mov al,[si]
          cmp al,1fh
          jb IS_NOT_ACTOR
          cmp al,22h
          ja IS_NOT_ACTOR
          mov [di+bx],dl
          mov [di+bx+255],dh
          inc bx

IS_NOT_ACTOR:  inc dl
          inc si
          loop FACT02

          xor dl,dl
          inc dh
          mov cl,ah
          dec ah
          loop FACT01

          mov di,offset ACTOR_NUMBERS
          mov [di],bl


;----------------------------------------------------------------

          ; PARTIE #3: UPDATE DE L'…CRAN

;----------------------------------------------------------------


UPDATE_SCREEN: mov di,offset SPEEDB ; modifications
          mov si,offset SFLAG
          mov al,[si+1]
          inc al
          cmp al,[di]         ; modifications
          jne NOT_NOW
          mov al,0
          mov [si+1],al
          jmp ANIMATE_ALL

NOT_NOW:  mov [si+1],al
          jmp NO_ANIMATION

ANIMATE_ALL:   mov al,[si]
          xor al,8
          mov [si],al

          xor bx,bx
          mov bh,al
          add bx,offset MCG_ANI
          mov di,offset MCG_IMAGES
          add di,1E00h

          mov cx,(8*256)/4
MORE_ANI: mov eax,[bx]
          mov [di],eax
          add bx,4
          add di,4
          loop MORE_ANI

NO_ANIMATION:  mov si,offset LIFE_FORCE
          xor ax,ax
          mov al,[si]
          mov ah,[si+1]
          cmp al,ah
          je NO_LF_CHG

          call INVSCR
          call SOME_TIME_OFF
          ;call SHOW_SCREEN

NO_LF_CHG:     call SHOW_SCREEN
          mov di,0a00h*23
          mov si,offset SC

          mov cx,8
NNNUM:         push cx
          xor bx,bx
          mov bl,[si]
          rol bx,6             ; bx=bx*64
          add bx,offset MSQ_IMAGES

          mov dx,8
NNUMLY:        mov cx,8
NNUMLX:        mov al,[bx]
          cmp al,15
          je NBLBYTE
          mov al,8
NBLBYTE:  mov gs:[di],al
          inc bx
          inc di
          loop NNUMLX
          add di,138h
          
          mov cx,dx
          dec dx
          loop NNUMLY

          add di,-0a00h+8
          inc si
          pop cx
          loop NNNUM

          
;-------------------------------------------------------

          ; Show "life force"
          
;-------------------------------------------------------

          mov di,24*0a00h+140h
          
          mov si,offset LIFE_FORCE
          mov dh,[si]
          ;mov dh,64
          mov dl,0
          
          cmp dh,0
          je OUT_LFRC

NGRBIT:        mov cx,6
          mov bx,0
          mov al,2

NGRLFL:        mov gs:[di+bx],al
          add bx,140h
          loop NGRLFL

          inc dl
          inc di
          cmp dh,dl
          jne NGRBIT

          cmp dh,255
          je OUT_GRN_FILL

OUT_LFRC: mov al,8
          ;mov di,24*0a00h+140h         

OUT_GRY_BIT:   mov cx,6
          mov bx,0
          
OUT_GRY_LFL:   mov gs:[di+bx],al
          add bx,140h
          loop OUT_GRY_LFL

          inc dl
          inc di
          cmp dl,255
          jne OUT_GRY_BIT

OUT_GRN_FILL:       mov si,offset LIFE_FORCE
          mov al,[si]
          mov [si+1],al

          ; Diamonds' count

          mov si,offset LEVEL_DATA
          mov cx,4096
          mov ah,0
NEXTSQR_ISDIAM:     mov al,[si]
          cmp al,4
          je MORE_DIAM
          cmp al,26h
          je MORE_DIAM
          cmp al,28h
          je MORE_DIAM
          cmp al,2ah
          je MORE_DIAM
          cmp al,2ch
          je MORE_DIAM
          cmp al,2eh
          je MORE_DIAM
          cmp al,30h
          je MORE_DIAM
NDIAM:         inc si
          loop NEXTSQR_ISDIAM
          jmp SHOWDIAM

MORE_DIAM:     inc ah
          jmp NDIAM
 
SHOWDIAM: mov si,offset DIAMONDS
          mov [si],ah
          mov al,0
          mov [si+1],al
          mov [si+2],al

          mov cl,ah
          cmp cl,0
          je DAWAY3
          
DAWAY1:        mov ah,[si+2]
          inc ah
          
          cmp ah,10
          jne DAWAY2

          mov ah,0
          mov al,[si+1]
          inc al
          mov [si+1],al
          
DAWAY2:        mov [si+2],ah
          loop DAWAY1

DAWAY3:        mov di,(23*0a00h)+(10*8)
          mov cx,2

DPRN3:         xor ax,ax
          mov al,[si+1]
          inc si
          push si
          push cx

          rol ax,6

          mov si,offset MSQ_IMAGES
          add si,ax
          
          xor bx,bx

          mov dx,8
DPRN1:         mov cx,8
DPRN2:         mov al,[si]
          cmp al,15
          je DIAM_NBLACK
          mov al,8
          ;mov al,5

DIAM_NBLACK:   mov gs:[di+bx],al
          ;call PRSX
          inc si
          inc bx
          loop DPRN2

          add bx,140h-8
          mov cx,dx
          dec dx
          loop DPRN1

          pop cx
          pop si
          add di,8
          loop DPRN3

               ;------------------------------------------------

SHOW_KEYS:     mov di,offset KEYS 
               mov si,900h
               add si,offset MCG_IMAGES
               mov ax,39-7
               mov bx,23
               mov cx,4
CHK_KEY:       mov dl,[di]
               cmp dl,1
               jne LOST_KEY
               call PMCG
               call CONVENSIONS
LOST_KEY:      inc di
               add ax,2
               add si,200h
               loop CHK_KEY

          ;-----------------------------------------------------
                    
          xor ax,ax              ; On board counter module
          push ax

;----------------------------------------------------------------


          ;PARTIE #4: OPERATING THE GAME MODULE

;----------------------------------------------------------------

          
MAKE_GAME:     mov si,offset DIAMONDS
          mov al,[si]
          cmp al,0
          ;je PREPARE_LEVEL
          je NEXT_LEVEL

     
          mov si,offset LIFE_FORCE
          mov al,[si]
          cmp al,0
          ;je NOT_FOUND
       je GAME_OVER      ; modification

          pop ax
MK_GM:         inc ax
          cmp ax,64
          je UPDATE_SCREEN

          ; THE CREATURES MUST PLAY, TOO!

          cmp ax,32
          je CREA_PLAY
          jmp PLAYER_TIME

CREA_PLAY:     push ax
          call CREATURES_TIME
CREA_END: pop ax

          ; CAN PLAYER PLAY?

PLAYER_TIME:   mov bx,ax
          and bx,3
          cmp ax,bx
          jne MK_GM
          push ax

          mov si,offset PV
          mov al,[si]
          cmp al,4
          je NDIAMOND
          cmp al,5
          je NECKLESS
          cmp al,6
          je CHEST  
          cmp al,1eh
          je WATER
                    
          mov ah,12h
          cmp al,2ch
          je MAGICAL_DIAM
          cmp al,2eh
          je MAGICAL_DIAM
          cmp al,30h
          je MAGICAL_DIAM

          mov ah,0
          cmp al,26h
          je MAGICAL_DIAM
          cmp al,28h
          je MAGICAL_DIAM
          cmp al,2ah
          je MAGICAL_DIAM

          ; check for type in PV
          cmp al,9
          je APPLIC_KEY

          inc ah
          cmp al,0bh
          je APPLIC_KEY

          inc ah
          cmp al,0dh
          je APPLIC_KEY

          inc ah
          cmp al,0fh
          je APPLIC_KEY

          jmp INPUT_PLAYER


          ; A KEY APPLICATION ROUTINE

APPLIC_KEY:mov al,ah
           ;call PRSX
           mov ah,0
           mov di,offset KEYS
           add di,ax
           mov al,1
           mov [di],al
           mov cx,50
           call ADD_TO_SCORE
           jmp REMOVE_OBJ

          ; THIS IS A NECKLESS
NECKLESS: mov cx,15
          call ADD_TO_SCORE
          mov cx,8
          call ADD_LIFE_FORCE
REMOVE_OBJ:    mov si,offset PV
          mov al,0
          mov [si],al
          jmp INPUT_PLAYER

          ; THIS IS A NORMAL DIAMOND
NDIAMOND: mov cx,10
          call ADD_TO_SCORE
          mov cx,6
          call ADD_LIFE_FORCE
          jmp REMOVE_OBJ

          ; THIS IS A CHEST
CHEST:         mov cx,50
          call ADD_TO_SCORE
          jmp REMOVE_OBJ

WATER:         mov si,offset LIFE_FORCE
          mov al,[si]
          cmp al,0
          je INPUT_PLAYER
          dec al
          mov [si],al
          je INPUT_PLAYER
          dec al
          mov [si],al
          call SOME_TIME_OFF
          call INVSCR
          jmp INPUT_PLAYER

          ; PLAYER MOVE MODULE 


INPUT_PLAYER:  ;mov si,offset LIFE_FORCE
          ;mov al,[si]
          ;cmp al,0
          ;je MAKE_GAME       
          call GETAX
          call GETPP     ; (bl=MX,bh=MY)

;          cmp al,"q"
;          je QUIT
          cmp al,":"
          je PREPARE_LEVEL

          cmp al,"`"
          je GAME_OVER
          
          cmp al,"8"
          je MOVE_UP
          cmp al,"2"
          je MOVE_DOWN
          cmp al,"4"
          je MOVE_LEFT
          cmp al,"6"
          je MOVE_RIGHT

          cmp ah,72
          je MOVE_UP
          cmp ah,80
          je MOVE_DOWN
          cmp ah,75
          je MOVE_LEFT
          cmp ah,77
          je MOVE_RIGHT

          cmp al," "
          je GIVE_A_BREAK

          cmp ah,59           ; [F1]
          je CHANGE_SPEED
          
          cmp ah,60           ; [F2]
          je RESTART_GAME

          cmp ah,61           ; [F3]
          je ERASE_SCORES

          cmp ah,62           ; [F4]
          je GO_ON_EDITING

          jmp MAKE_GAME

RESTART_GAME:  pop ax
               jmp NEW_GAME

ERASE_SCORES:  xor dx,dx
               mov ah,2
               mov bh,0
               int 10h

               mov dx,offset CONFIRM
               mov ah,9
               int 21h

ERS_WAIT:      call GETAX
               cmp ax,0
               jne ERS_WAIT

               
ERS_INK:       call GETAX
               cmp ax,0
               je ERS_INK
               cmp al,"y"
               jne MAKE_GAME

               mov di,offset HI_SCORES
               mov al,0
               mov cx,40 *20
ERS:           mov [di],al
               inc di
               loop ERS

               mov dx,offset HISCORES_CS3
               mov cx,0
               mov ah,3ch
               int 21h
               jc NOT_FOUND

               push ax
               mov bx,ax
               mov cx,1
               mov dx,offset HI_SCORES
               mov ah,40h
               int 21h
               jc NOT_FOUND
               
               pop bx
               mov ah,3eh
               int 21h
               jc NOT_FOUND
               jmp MAKE_GAME



MOVE_UP:  cmp bh,1
          jb MAKE_GAME
          dec bh
          jmp CHECK_WP
MOVE_DOWN:     inc bh
          jmp CHECK_WP
MOVE_LEFT:     dec bl
          jmp CHECK_WP
MOVE_RIGHT:    inc bl
          jmp CHECK_WP

CHECK_WP: ; WANTED POSITION

          mov si,offset WX  ; save WP
          mov [si],bl
          mov [si+1],bh

          xor ax,ax
          mov al,bh
          add ax,5
          rol ax,6          ; WP=(WY+5)*64
          add ax,10
          xor bh,bh
          add ax,bx   ; WP=(WY+5)*64+WX+10
                                                  
          mov si,ax
          add si,offset LEVEL_DATA
          mov al,[si]      ; WV=[WP]

          cmp al,1
          je MAKE_GAME
          cmp al,8
          je MAKE_GAME
          cmp al,10h        ; Check for brick type items
          ja CHK_BRICK_TYPE
RET_FRM_BRTY:mov ah,al
          and ah,254
          
          cmp al,26h        ; Check for 1 out of 2: Brick
          ja CHK_BRICK2            
          
RET_FRM_BR2:cmp al,1eh
          ja CHK_ALIENS

RET_FRM_AL:    ; add a KEYS & LOCKS MODULE later.... 

     ; Check if you have the correct key to open  
     ; a door.

     xor ah,ah
     cmp al,0ah
     je LOCKS

     inc ah
     cmp al,0ch
     je LOCKS

     inc ah
     cmp al,0eh
     je LOCKS

     inc ah
     cmp al,10h
     je LOCKS

          ; You have the OK to move...

MOVE_TO_NEW:   mov ah,2            
          mov [si],ah        ; ah=[WP]=2
          
          mov si,offset PV    ; si = PV
          mov dl,[si]
          mov [si],al         ; [si] = PV = al = WV


          mov bx,bx
          mov si,offset MX
          mov bl,[si+1]
          add bx,5
          rol bx,6            ; PP= (MY+5)*64
          xor ax,ax
          mov al,[si]
          add bx,10     ; PP= (MY+5)*64+MX+10
          add bx,ax
          add bx,offset LEVEL_DATA
                    
          mov [bx],dl

          mov si,offset WX
          mov di,offset MX


          mov al,[si]
          mov [di],al
          mov al,[si+1]
          mov [di+1],al

          jmp MAKE_GAME

          ;------------------------------------------------------

          
               
          ;------------------------------------------------------

CHK_BRICK_TYPE:     cmp al,1eh
          jae RET_FRM_BRTY
          jmp MAKE_GAME

CHK_BRICK2:    cmp al,2ch
          jae RET_FRM_BR2
          cmp al,ah
          jne MAKE_GAME
          jmp RET_FRM_BR2
          
CHK_ALIENS:    cmp al,26h
          jae RET_FRM_AL
          jmp MAKE_GAME

          ;------------------------------------------------------

GAME_OVER:     pop ax
          call GAS_ALL_GREEN
          mov dx,DATA
          mov ds,dx
          mov es,dx
          mov dx,offset CS3OVER_MSQ
          mov bx,offset MSQ_MESSAGE
          mov cx,640
          call LOADOLD
          call PRDESTINY
NO_KEYS_P0:    call GETAX          
          cmp ax,0
          jne NO_KEYS_P0
SO_KEY_P0:     call GETAX
          cmp ax,0
          je SO_KEY_P0
          jmp CLASS_HIGHS      ; modifications <HI-SCORES>

          ;jmp PREPARE_GAME

YOU_WIN:  pop ax
          mov dx,DATA
          mov ds,dx
          mov es,dx
          mov dx,offset CS3WIN_MSQ
          mov bx,offset MSQ_MESSAGE
          mov cx,640
          call LOADOLD
          call PRDESTINY
          jmp NO_KEYS_P0

       ;------------------------------------------------------
          
QUIT:          mov dx,DATA
          mov ds,dx
          mov si,offset OLD_VIDEO_MODE
          mov al,[si]
          mov ah,0
          int 10h
          mov ah,4ch
          int 21h

;----------------------------------------------------------------

; ROUTINES
;----------------------------------------------------------------

GETAX:    call NUM_LOCK
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
GETOUT:   cmp al,27
       je QUIT
       pop ds
          pop dx
          pop bx
          ret
          
;-------------------------------------------------------

GETPP:         push ax
          push si
          mov si,offset MX
          mov bl,[si]
          mov bh,[si+1]
          pop si
          pop ax
          ret

;--------------------------------------------------------

MAKEPATH: pusha
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
ENDPATH:  popa
          mov ax,DATA
          mov ds,ax
          mov dx,offset FILENAME
          ret       

          ;-----------------------------------------------------

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
          jc NOT_FOUND
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
          jc NOT_FOUND
          ret

          
;--------------------------------------------------------

CLS:      pusha
          mov eax,0
          mov si,0
          mov cx,4000h
MKBCK:         mov gs:[si],eax
          add si,4
          loop MKBCK
          popa
          ret

          
;--------------------------------------------------------

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
          mov ah,4ch
          int 21h

          
;-------------------------------------------------------

CONVENSIONS:   push dx
          mov dx,DATA        ; SETUP THE LEVEL EDITOR CONVENSIONS
          mov ds,dx
          ;mov dx,MEM1
          ;mov es,dx
          ;mov dx,MEM1
          ;mov fs,dx
          mov dx,0a000h
          mov gs,dx
          pop dx
          ret

          ;--------------------------------------------------

SHOW_SCREEN:   ; DÈtermine le point initiale designÈ par (0,0)
          ; celui-ci est designÈ par si.

          ; si = MX + MY * 128 + offset LEVEL_DATA

          pusha
          xor di,di
          xor ax,ax
          xor bx,bx
          mov si,offset MX
          mov al,[si]
          mov bl,[si+1]
          ;rol bx,7       bx=bx*128
          rol bx,6      ;  bx=bx*64
          mov si,bx
          add si,ax
          add si,offset LEVEL_DATA    ; si -> (0,0) 

          ; La boucle centrale effectue 11 sweep verticales
          ; de 20 sweep horizontales.

          mov dx,11     ; RANGERS
SCRNEXTY: mov cx,20     ; COLONNES

          ; Determinons la valeur de PV ‡ la position (sur
       ; l'Ècran)
          ; qui Ègale (cx-20,dx-10).

          ; si = [valeur] * 256

SCRNEXTX: xor ax,ax
          mov al,[si]
          rol ax,8
          push si   
          mov si,ax               ; si = PV * 256
          add si,offset MCG_IMAGES

          push dx
          push cx
                    
          ; Passons maintenant au coeur de l'opÈration
       ;            l'affichage.
           
          xor bx,bx 

          mov dx,16     ; SUB_RANGERS
SCRSRAN:        mov cx,4      ; SUB_COLONNES
                    
SCRSCOL:  mov eax,[si]
          add si,4
          mov gs:[di+bx],eax
          add bx,4
          loop SCRSCOL

          mov cx,dx
          dec dx
          add bx,130h
          loop SCRSRAN
     
          ; Une case de faite...

          pop cx
          pop dx
          pop si
          add di,16
          inc si
          loop SCRNEXTX

          mov cx,dx
          dec dx
          add di,(0a00h*2)-140h
          ;add si,108
          add si,44      ; one line down...
          loop SCRNEXTY
          popa
          ret

          
;-------------------------------------------------------


          
;-------------------------------------------------------         
          

ANY_KEYS: xor ax,ax
          int 16h
          jmp QUIT

          
;-------------------------------------------------------

WBUT:          push ax
          mov ax,3
          int 33h
          shr cx,4+1
          shr dx,3+1          
          pop ax
          ret
          
          
;--------------------------------------------------------

SOME_TIME_OFF: pusha
          mov cx,7000h
STOFF:         mov ax,ax
          loop STOFF
          popa
          ret

          
;---------------------------------------------------------

ADD_TO_SCORE:  pusha
          mov si,offset SC
ADDSM_0:  mov bx,7
          mov al,[si+bx]
          inc al
          cmp al,10
          jne ADDSM_3

ADDSM_1:  mov al,0
          mov [si+bx],al
          mov al,[si+bx-1]
          inc al
          mov [si+bx-1],al

          cmp al,10
          jne ADDSM_2

          dec bx
          jmp ADDSM_1

ADDSM_3:  mov [si+bx],al
ADDSM_2:  loop ADDSM_0   
          popa
          ret

          
;-------------------------------------------------------

ADD_LIFE_FORCE:     pusha
          mov si,offset LIFE_FORCE
          mov ah,[si]
          mov al,ah
          add al,cl
          cmp al,ah
          ja ALFOK
          mov al,255
ALFOK:         mov [si],al
          popa
          ret

          
;------------------------------------------------------          

INVSCR:        pusha
          mov cx,(65536-(0a00h*4))/4
          mov di,0
NINVSCR:  mov eax,gs:[di]
          xor eax,0f0f0f0fh
          mov gs:[di],eax
          add di,4
          loop NINVSCR
          popa
          ret

          ;-----------------------------------------------------

CREATURES_TIME:     mov si,offset AFLAG
          mov al,[si]
          inc al
          mov [si],al
          mov di,offset SPEEDA ; modification
          cmp al,[di]          ; modification
          je YOU_HAVE_A_GO
          ret

YOU_HAVE_A_GO: mov al,0
          mov [si],al

          mov bp,-1
NEXT_CREA:     inc bp
          mov si,offset ACTOR_NUMBERS
          xor ax,ax
          mov al,[si]
          cmp ax,bp
          je END_CREA

          mov si,offset ACTOR_X
          add si,bp
          xor ax,ax
          mov al,[si]
          mov ah,[si+255]
          push ax
          xor bx,bx
          mov bl,ah
          xor ah,ah
          rol bx,6
          mov di,offset LEVEL_DATA; SI= offset
          add di,ax           ; SI= SI+X                    
          add di,bx           ; SI= SI+Y*64
          
          mov al,[di]
          cmp al,1fh
          je VAMPIRE

          pop ax

          mov dh,[si+(255*2)]
          mov si,di
          mov cx,4
TRY_NEXT_DIR:  call FIND_DIR
          ;mov dl,dh
          ;add dl,cl
          ;and dl,3
          ;cmp dl,0
          ;jne NOT_DIR4
          ;mov dl,4
NOT_DIR4: mov es,cx              ; ES=CX
          call CHKDIR
          cmp bl,0
          je CAN_MOVE
          push es
          pop cx
          loop TRY_NEXT_DIR
          ;jmp NEXT_CREA
          jmp CATCH_PLAYER

CHKDIR:        mov cx,ax
          mov di,si

          cmp dl,1
          je CHK_UP

          cmp dl,2
          je CHK_DOWN
          
          cmp dl,3
          je CHK_RIGHT
          
          cmp dl,4
          je CHK_LEFT         

CHK_UP:        dec ch
          add di,-64
          jmp TESTX

CHK_DOWN: inc ch
          add di,64
          jmp TESTX

CHK_RIGHT:     inc cl
          add di,1
          jmp TESTX

CHK_LEFT: dec cl
          add di,-1
          jmp TESTX

TESTX:         mov bl,[di]
          ret

CAN_MOVE: push si
          mov al,[si]     ; al = PV
          mov ah,0        ; PV = 0
          mov [si],ah

          mov [di],al    ; WV = PV      
                    
          mov si,offset ACTOR_X
          add si,bp
          
          mov [si],cl
          mov [si+255],ch
          
          mov [si+(255*2)],dl
          pop si
          
          ; NEXT_CREA
          jmp CATCH_PLAYER


          ;---------------------------------------------------

VAMPIRE:  pop ax         
          mov si,di
          mov cx,4

NEXT_VAMP_DIR: mov dl,cl
          push cx
          call CHKDIR

          cmp bl,2
          je BIT_YA
          cmp bl,20h
          jb IS_IT_WATER
          cmp bl,22h
          ja IS_IT_WATER
          
          mov bl,1fh
          mov [di],bl
          jmp LOOP_BACK

IS_IT_WATER:cmp bl,1eh
          je SPREAD_WATER

          cmp bl,23h
          je SPREAD_WATER
          
LOOP_BACK:
          pop cx
          loop NEXT_VAMP_DIR
          

          jmp NEXT_CREA

SPREAD_WATER:  ;mov di,offset ACTOR_X
          ;add di,bp
          ;inc bp

          ;mov [di],cl
          ;mov [di+255],ch

          ;mov di,offset ACTOR_NUMBERS
          ;mov bx,bp
          ;mov [di],bl 
          
          mov bl,1fh
          mov [di],bl

          ;jmp LOOP_BACK

          mov di,offset ACTOR_NUMBERS
          xor bx,bx
          
          mov bl,[di]
          cmp bl,255
          je LOOP_BACK

          inc bl
          mov [di],bl

          mov di,offset ACTOR_X 
          add di,bx
          dec di

          mov [di],cl
          mov [di+255],ch

          ;call PRSX
          jmp LOOP_BACK

BIT_YA:   mov di,offset LIFE_FORCE
          mov bl,[di]
          mov bh,bl

          add bh,-6
          cmp bl,bh
          ja BIT_LF

          mov bh,0
BIT_LF:   mov [di],bh
          jmp LOOP_BACK

END_CREA: ret

FIND_DIR: push bx
          xor bx,bx
          mov bl,dh
          dec bl
          rol bx,2
          add bx,cx
          add bx,offset DIR
          dec bx
          mov dl,[bx]
          pop bx
          ret

CATCH_PLAYER:mov cx,4
CTH_PLY:  mov dl,cl
          mov di,si
          mov es,cx
          call CHKDIR
          cmp bl,2
          je DRN_PLAYER
CTH_PLY2: push es
          pop cx
          loop CTH_PLY
          jmp NEXT_CREA
          
DRN_PLAYER:mov di,offset LIFE_FORCE
          mov bl,[di]         
          mov bh,bl
          add bh,-6
          cmp bl,bh
          ja EN_DR0
          mov bh,0
EN_DR0:   mov [di],bh
          jmp CTH_PLY2
          
          ;----------------------------------------------------

MAGICAL_DIAM:inc al
          mov si,offset LEVEL_DATA
          mov cx,4096
NPMAGS:   mov bl,[si]
          cmp bl,al
          jne NO_MAGIC
          mov bl,ah
          mov [si],bl
NO_MAGIC: inc si
          loop NPMAGS
          ;jmp REMOVE_OBJ
          jmp NDIAMOND

          ;----------------------------------------------------

PMCG:     pusha       ; Routine generique pour  
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
P03:      mov cx,16      ; BX se fait compteur X
          push di       ; CX se fait compteur Y
P04:      ;mov dx,MEM1
          ;mov ds,dx     
          ;mov ax,[si]
          mov al,ds:[si] ; modification
          inc si         
          ;inc si         
          cmp al,0
          je P05
          ;mov dx,0a000h
          ;mov ds,dx      
          mov gs:[di],al ; modification 
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

          ;-----------------------------------------------------

LOCKS:    push bx
          xor bx,bx
          mov bl,ah
          add bx,offset KEYS
          mov ah,[bx]
          cmp ah,1
          jne WRONG_KEY
          pop bx
          jmp MOVE_TO_NEW

WRONG_KEY:pop bx
          jmp MAKE_GAME
               
       ;------------------------------------------------------

GIVE_A_BREAK:mov bh,0
          xor dx,dx
          mov ah,2
          int 10h

          mov dx,offset RESUME
          mov ah,9
          int 21h

HOLD_ON:  call GETAX
          cmp al," "
          jne HOLD_ON
       cmp al,27
       je QUIT
          jmp MAKE_GAME

          ;----------------------------------------------------

       ; PRINT A {GAME OVER / YOU WIN!}  SIGN

PRDESTINY: call SHOW_SCREEN
        mov si,offset MSQ_MESSAGE
        ;mov di,((40-8)/2)*8+((24-4)/2)*0a00h
        mov di,0a00h*4
     
        mov dx,16
PRDLIN2:   mov cx,40
        
PRDLINE:   mov al,[si]      
        inc si
        cmp al,0
           je PRDNOT
        ;mov al,14
        mov eax,0e0e0e0eh
        push cx
        push dx
           push di

        mov dx,8
PRNADA:      mov cx,2

PRNADA_SQR:mov gs:[di],eax
        add di,4
        loop PRNADA_SQR

        add di,140h-8
           mov cx,dx
        dec dx
           loop PRNADA

          pop di
          pop dx
          pop cx
        ;mov gs:[di],al
        ;mov gs:[di+140h],al
        ;mov gs:[di+1],al
        ;mov gs:[di+141h],al

PRDNOT:    add di,8
           loop PRDLINE

        add di,0a00h-140h
        mov cx,dx
        dec dx
        loop PRDLIN2
        ret

       ;-----------------------------------------------------

       ; REMOVE ANY_REMANING GREEN...

GAS_ALL_GREEN:mov di,-0f00h
       mov cx,0f00h
NEXT_COLORED_BYTE:mov al,gs:[di]
          cmp al,2
       jne IT_IS_NOT_A_GREEN_BYTE
       mov al,8
       mov gs:[di],al
IT_IS_NOT_A_GREEN_BYTE:inc di
       loop NEXT_COLORED_BYTE
       ret

       ;-----------------------------------------------------

          ; SET NUMBER LOCK

NUM_LOCK: pusha
          push ds
          mov dx,0
          mov ds,dx
          mov si,1047
          mov al,[si]
          and al,255-64-16
          or al,32
          mov [si],al
          pop ds
          popa
          ret



               ;-----------------------------------------------
               ; GO ONE LEVEL HIGHER!

NEXT_LEVEL:    mov cx,500
               call ADD_TO_SCORE

               mov si,offset LIFE_FORCE
               mov cl,[si]
               call ADD_TO_SCORE
               jmp PREPARE_LEVEL
               
               ;------------------------------------------------



               ;-----------------------------------------<<<
               ; CLASSIFICATION DU SCORE
               ;-----------------------------------------<<<

CLASS_HIGHS:   ; CHANGE VIDêO MODE

;                xor ax,ax                ; VIDêO MODE=0
;               mov al,13 + 128
;                int 10h

               ;-----------------------

               ;jmp PREPARE_GAME

               call CLS            ; CLS

               mov si,offset SC
               mov di,offset HI_SCORES + ((14+3+0)*40)

               mov dx,15+3
CMPNXHISC:     mov cx,8
               xor bx,bx

CMPNXDIG:      mov al,[si+bx]

               cmp al,[di+bx]
               
               jb TOO_SMALL        ; if SC<HI then TOO_SMALL
               ja BIGGER_THAN      ; if SC>HI then BIGGER_THAN

               inc bx

               loop CMPNXDIG       ; compare next digits
               jmp TOO_SMALL       ; if SC=HI then TOO_SMALL

BIGGER_THAN:   mov cx,40
               xor bx,bx
DROP_DOWN:     mov al,[di+bx]
               mov [di+bx+40],al
               mov al,0            ; modification <<<
               mov [di+bx],al      ; modification <<<
               inc bx
               loop DROP_DOWN

               mov cx,8
               xor bx,bx
TRAN_SC_TOHI:  mov al,[si+bx]
               mov [di+bx],al
               inc bx
               loop TRAN_SC_TOHI

               mov bx,offset LEV00_CS3 + 3
               mov al,[bx]
               add al,-30h
               mov [di+9],al
               mov al,[bx+1]
               add al,-30h
               mov [di+10],al

               mov es,di                ; save destination in ES

NEXT_HISC:     mov cx,dx
               dec dx
               add di,-40
               loop CMPNXHISC
               
TOO_SMALL:     mov bx,offset HPOINT
               mov [bx],dl              ; HPOINT= HI LINE
               ;cmp dx,15

               ;mov cx,8
               ;mor bx,bx
               ;mov di,offset HI_SCORES+40
               ;mov al,[si+bx]
               ;mov [di+bx]
               ;loop

               ;------------------------
               mov si,offset TOP_SCORES

               mov bl,15                ; COLOR WHITE
               mov bh,0                 ; page d'Çcran
               mov dl,0                 ; X=0
               mov dh,1                 ; Y=1

NOF_NXT:       mov al,[si]
               cmp al,0
               je NOF_TOP
               
               mov ah,2                 ; SET COORDONATES
               pusha
               int 10h
               popa

               mov ah,0eh               ; AFFICHE UN CARAC
               pusha
               int 10h
               popa

               inc dl
               inc si

               jmp NOF_NXT

NOF_TOP:       mov bp,15+3           ; NUMBERS OF SCORES
               mov si,offset HI_SCORES
               mov dh,1+2          ; Y=3

MORE_SCORES:   mov cx,40           ; NUMBERS OF SQRS TO PRN
               mov dl,0            ; X=0

MORE_LETTERS:  mov al,[si]
               cmp dl,8
               je DO_NOT_ADD       ; IF X=8 THEN don't add ...
               cmp dl,10
               ja DO_NOT_ADD       ; IF X>10 THEN don't add ...
               
               add al,30h

DO_NOT_ADD:    ;-------hmmm!
               mov bx,offset HPOINT
               mov bl,[bx]
               ;xor bh,bh
               add bl,3
               cmp bl,dh
               je YELLOW_LINE
               
               mov bx,bp
               xor bh,bh
               and bl,2
               or bl,1            ; COLOR

               jmp PRINT_HI_NOW

YELLOW_LINE:   mov bh,0
               mov bl,14


PRINT_HI_NOW:  mov ah,2
               int 10h

               mov ah,0eh
               int 10h

               inc dl
               inc si
               loop MORE_LETTERS
  
               mov cx,bp
               dec bp
               inc dh
               loop MORE_SCORES

               mov si,offset HPOINT
               mov al,[si]
               cmp al,18
               jne GOOD_WORK

               mov si,offset SORRY
               call CUSTOM_BOT
               jmp PROMPT

GOOD_WORK:     mov si,offset WRITE_NAME
               call CUSTOM_BOT


               ;-----------------------------------------------

               ; WRITE A HI_SCORE TO MEMORY...


               ;-----------------------------------------------
               mov si,offset HPOINT
               mov dh,[si]
               add dh,3
               mov dl,12

               mov bl,14
               push es
               pop di

               add di,12

AJUST_CURSOR:  mov al,219
               mov ah,2
               mov bh,0
               int 10h

               mov bl,14
               mov ah,0eh
               int 10h

MAIN_WLOOP:    call GETAX
               cmp al," "
               je WRTN
               cmp al,8
               je BACK_SPACE
               cmp al,13
               ;je DONE_WRITE
               je P_PROMPT              ; modification
               ;je WRITE_HIS
               cmp al,"a"
               jb MAIN_WLOOP
               cmp al,"z"
               ja MAIN_WLOOP
               jmp PRINT_LETTER

WRTN:          cmp dl,39
               je MAIN_WLOOP
               mov ah,2
               int 10h
               mov ah,0eh
               int 10h
               inc dl
               mov [di],al
               inc di
               jmp AJUST_CURSOR

;DONE_WRITE:   jmp PREPARE_GAME

BACK_SPACE:    cmp dl,12
               je MAIN_WLOOP
               mov al,32
               mov ah,2
               int 10h
               mov ah,0eh
               int 10h
               dec dl
               mov [di],al
               dec di
               jmp AJUST_CURSOR

PRINT_LETTER:  add al,-32
               jmp WRTN

               ;-----------------------------------------------

               
PROMPT:        call GETAX
               cmp ax,0
               je PROMPT
               jmp NEW_GAME

               xor ax,ax
               int 16h
               jmp SET_VIDEO

               ;------------------------------------------------

P_PROMPT:      mov ah,2
               int 10h
               
               mov al,32
               mov ah,0eh
               int 10h

               mov dh,22
               mov dl,0
               mov cx,40

ERA_CAR:       mov ah,2
               int 10h
               
               mov ah,0eh
               int 10h

               inc dl
               loop ERA_CAR
               jmp WRITE_HIS
               

               ;------------------------------------------------

               ; CUSTOMIZED BOTTOM LINE

CUSTOM_BOT:    pusha
               mov dh,22      ; Y=23
               mov dl,0       ; X=0
               mov bl,14      ; COLOR

CUS_B:         mov al,[si]
               cmp al,0
               je CUST_RET
               mov bh,0
               mov ah,2
               int 10h        ; (X,Y)
               mov ah,0eh
               int 10h        ; CARAC

               inc si
               inc dl
               jmp CUS_B

CUST_RET:      popa
               ret

               ;-------------------------------------------
               ; SAVE HI-SCORES

WRITE_HIS:     mov dx,offset HISCORES_CS3
               call MAKEPATH

               mov cx,0       ; CRêE UN FICHIER
               mov ah,3ch
               int 21h
               jc NOT_FOUND

               push ax
               mov bx,ax
               mov dx,offset HI_SCORES
               mov cx,19*40
               mov ah,40h
               int 21h
               jc NOT_FOUND

               pop bx
               mov ah,3eh     ; FERMETURE 3Eh
               int 21h
               jc NOT_FOUND
               jmp PROMPT

;---------------------------------------------------------
;                   SELECT ACTOR'S SPEED
;---------------------------------------------------------

SELECTASPEED:  call CLS
               mov bh,0       ; PAGE D'êCRAN
               mov dl,0       ; X
               mov dh,2       ; Y
               mov ah,2       ; FONCTION 2
               int 10h

               mov dx,offset SELECT_SPEED
               mov ah,9
               int 21h

               mov si,offset SPEEDA
               mov al,[si]
               mov di,offset SELECT_SPEEDA
               dec di
               dec di

               add al,30h
               mov [di],al

               mov dl,8       ; X
               mov dh,4       ; Y
               mov ah,2       ; FONCTION
               int 10h
               
               mov dx,offset CURRENT_SPEED
               mov ah,9
               int 21h

CHK_INKEYS:    call GETAX
               cmp al,"1"
               jb CHK_INKEYS
               cmp al,"9"
               ja CHK_INKEYS
               add al,-30h
               mov di,offset SPEEDA
               mov [di],al
               inc al
               inc al
               mov [di+1],al

               ; SAVE SETTING TO DISK
               mov dx,offset DEFAULTS_CS3
               call MAKEPATH
               mov cx,0
               mov ah,3ch
               int 21h
               jc NOT_FOUND
               
               push ax
               mov bx,ax
               mov ah,40h
               mov dx,offset SPEEDA
               mov cx,2
               int 21h
               jc NOT_FOUND

               pop bx
               mov ah,3eh
               int 21h
               jc NOT_FOUND
               
               ret

CHANGE_SPEED:  pop ax
               call SELECTASPEED
               mov si,offset AFLAG
               mov al,0
               mov [si],al
               mov si,offset SFLAG
               mov [si+1],al
               jmp NEW_GAME

;-------------------------------------------------------------
          ; CREEPSPREAD III: LEVEL EDITOR
;-------------------------------------------------------------

          ; LEVELS EDITOR CONVENSIONS
          ; DS: DATA SEGMENT
          ; ES: MEM1 - MCG
          ; FS: MEM2 - LEVELS DATA
          ; GS: 0A00H- VIDEO MEMORY     

          ;jmp ANY_KEYS
          

          ;jmp QUIT
          
GO_ON_EDITING: pop ax

               mov ah,35h
               int 21h
               cmp byte ptr es:[bx],0
               jne YOU_GOT_DRIVER

NO_DRIVER:     mov dx,data
               mov ds,dx

               mov si,offset OLD_VIDEO_MODE
               mov al,[si]
               mov ah,0
               int 10h
               
               mov dx,offset MOUSE_DOWN
               mov ah,9
               int 21h
               mov ah,4ch
               int 21h

YOU_GOT_DRIVER:mov ax,0
               int 33h
               cmp ax,-1
               jne NO_DRIVER

               mov dx,DATA
               mov ds,dx
               mov es,dx
               mov dx,offset CS3EDIT_MCG
               mov bx,offset MCG_IMAGES
               mov cx,16384
               call LOADOLD

               mov dx,DATA
               mov ds,dx
               mov es,dx
               mov dx,offset LEV00_CS3
               mov bx,offset LEVEL_DATA
               mov cx,4096
               call LOADOLD

               call CLS
               SMOUSE

          ;-----------------------------------------------------
          ; Initialisation centrale
          
BODY_OF_THE_EDITOR:call CONVENSIONS
          ;jmp ANY_KEYS
          HMOUSE
          ;mov si,offset MX
          ;mov al,0
          ;mov [si],al
          ;mov [si+1],al 
RETURN_TO_EDIT:call PUT_CARAC      
          call BORDERS
          call SHOW_SCREEN
          SMOUSE
          ;jmp ANY_KEYS


          
;--------------------------------------------------------

MBOUCLE   :    ;SMOUSE
          call WBUT
          cmp bx,1
          ;ja QUIT
          je DROPANDPICK
          call GETAX     
          mov si,offset MX
          mov bl,[si]
          mov bh,[si+1]
          ;HMOUSE
          cmp al,"8"
          je MAZE_UP
          cmp al,"2"
          je MAZE_DOWN
          cmp al,"4"
          je MAZE_RIGHT
          cmp al,"6"
          je MAZE_LEFT
          cmp ah,72
          je MAZE_UP
          cmp ah,80
          je MAZE_DOWN
          cmp ah,75
          je MAZE_RIGHT
          cmp ah,77
          je MAZE_LEFT        
          cmp al,"["
          je CAR_RIGHT
          cmp al,"]"
          je CAR_LEFT
          cmp al,"c"
          je CLEAR_MAZE

          cmp al,"-"
          je LOADMAZE

          cmp al,"="
          je SAVEMAZE

          cmp al,"`"
          je RETURN_TO_CS3
         ; cmp al,"e"
         ; je RETURN_TO_CS3

          jmp MBOUCLE

          ;------------------------------------------------


MAZE_UP:  cmp bh,0
          je MBOUCLE
          dec bh
RMB:      mov si,offset MX
          mov [si],bl
          mov [si+1],bh
          HMOUSE
          call SHOW_SCREEN
          mov cx,ax
          call GETAX
          cmp ax,cx
          je TRANSMOVE
          SMOUSE
          jmp MBOUCLE 
          
          HMOUSE
          call SHOW_SCREEN
          SMOUSE
          jmp MBOUCLE

MAZE_DOWN:     cmp bh,64-12
          je MBOUCLE
          inc bh
          jmp RMB

MAZE_RIGHT:    cmp bl,0
          je MBOUCLE
          dec bl
          jmp RMB

MAZE_LEFT:     ;cmp bl,128-10
          cmp bl,64-10
          je MBOUCLE
          inc bl
          jmp RMB

TRANSMOVE:     cmp al,"8"
          je MAZE_UP2
          cmp al,"2"
          je MAZE_DOWN2
          cmp al,"4"
          je MAZE_RIGHT2
          cmp al,"6"
          je MAZE_LEFT2
          cmp ah,72
          je MAZE_UP2
          cmp ah,80
          je MAZE_DOWN2
          cmp ah,75
          je MAZE_RIGHT2
          cmp ah,77
          je MAZE_LEFT2             



          ;cmp al,"["
          ;je CA_RIGHT
          ;cmp

MAZE_UP2: cmp bh,0
          je OUTT
          dec bh
RMB2:          mov si,offset MX
          mov [si],bl
          mov [si+1],bh
          ;HMOUSE
          call SHOW_SCREEN
          mov cx,ax
          call GETAX
          cmp ax,cx
          je TRANSMOVE
OUTT:          SMOUSE
          jmp MBOUCLE 
          
          HMOUSE
          call SHOW_SCREEN
          SMOUSE
          jmp MBOUCLE

MAZE_DOWN2:    cmp bh,64-12
          je OUTT
          inc bh
          jmp RMB2

MAZE_RIGHT2:   cmp bl,0
          je OUTT
          dec bl
          jmp RMB2

MAZE_LEFT2:    ;cmp bl,128-10
          cmp bl,64-10             ; modifications
          je OUTT
          inc bl
          jmp RMB2
          jmp QUIT

CAR_RIGHT:     mov si,offset CARAC
          mov al,[si]
          cmp al,0
          je MBOUCLE
          dec al
          mov [si],al
          HMOUSE
          call PUT_CARAC
          mov cx,ax
          call GETAX
          cmp cx,ax
          je CARAC_MOVE
          SMOUSE
          jmp MBOUCLE

CAR_LEFT: mov si,offset CARAC
          mov al,[si]
          ;cmp al,128-20
          cmp al,64-20   ; modications
          je MBOUCLE
          inc al
          mov [si],al
          HMOUSE
          call PUT_CARAC
          mov cx,ax
          call GETAX
          cmp cx,ax
          je CARAC_MOVE
          SMOUSE
          jmp MBOUCLE

CARAC_MOVE:    cmp al,"["
          je CAR_RIGHT2
          cmp al,"]"
          je CAR_LEFT2

CAR_RIGHT2:    mov si,offset CARAC
          mov al,[si]
          cmp al,0
          je MBOUCLE
          dec al
          mov [si],al
          ;HMOUSE
          call PUT_CARAC
          mov cx,ax
          call GETAX
          cmp cx,ax
          je CARAC_MOVE
          SMOUSE
          jmp MBOUCLE

CAR_LEFT2:     mov si,offset CARAC
          mov al,[si]
          cmp al,128-20
          je MBOUCLE
          inc al
          mov [si],al
          ;HMOUSE
          call PUT_CARAC
          mov cx,ax
          call GETAX
          cmp cx,ax
          je CARAC_MOVE
          SMOUSE
          jmp MBOUCLE


          ;--------------------------------------------------
 
DROPANDPICK:   cmp dx,11
          ja MBOUCLE
          je PICK

DROP:          mov si,offset MX
          add cl,[si]      ; x
          add dl,[si+1]    ; y
          ;rol dx,7 
          rol dx,6       ; modifications
          mov di,cx
          add di,dx
          add di,offset LEVEL_DATA
          mov si,offset CD
          mov al,[si]
          mov [di],al
          call BORDERS
          HMOUSE
          call SHOW_SCREEN
          SMOUSE
          call SOME_TIME_OFF
          jmp MBOUCLE

PICK:          mov si,offset CARAC
          mov al,[si]
          add cl,al
          mov di,offset CD
          mov [di],cl
          jmp MBOUCLE

;----------------------------------------------------------------
 

CLEAR_MAZE:    HMOUSE
          mov bh,0
          mov ah,2
          xor dx,dx
          int 10h

          mov ah,9
          mov dx,offset CLEAR_MAZE_TEXT
          int 21h
          SMOUSE

CLMZINKEY:     call GETAX
          cmp al,"y"
          je APPCLMAZE
          cmp al,0
          je CLMZINKEY
          jmp BODY_OF_THE_EDITOR

APPCLMAZE:     mov di,offset LEVEL_DATA
          ;mov cx,8192/4
          mov cx,4096/4            ; modifications
          mov eax,0
APPCLMZ:  mov [di],eax
          add di,4
          loop APPCLMZ
          jmp BODY_OF_THE_EDITOR

              
;--------------------------------------------------------

LIGHT_OUT: jmp CLS
 
     ;-------------------------------------------------------

PUT_CARAC:     pusha                 ; sauvegarde tous les  
          mov si,offset CARAC
          mov ah,[si]    ; ah = CARAC
          mov di,58880 -0a00h    ; di = destination
          mov dx,20              ; dx = number of caracter left
MCARAC:        push dx                ; save dx
          xor bx,bx              ; bx = 0
          mov bl,ah              ; bx = ah = CARAC
          inc ah                 ; ah = ah + 1
          rol bx,8         ; bx = bx * 256
          mov si,offset MCG_IMAGES;si = MGC_IMAGES
          add si,bx              ; si = si + CARAC * 256
          xor bx,bx        ; bx = 0
          mov dx,16              ; dx = Y
MROWTDO:  mov cx,16        ; cx = X
RONWTBD:  mov al,[si]
          inc si
          mov gs:[di+bx],al
          inc bx
          loop RONWTBD
          add bx,130h
          mov cx,dx
          dec dx
          loop MROWTDO
          add di,16
          pop dx
          mov cx,dx
          dec dx
          loop MCARAC 
          popa
          ret

          ;-----------------------------------------------------

PRINTSAVEORLOAD:call CLS
               mov ah,9
               int 21h

               mov dx,offset NUM
               mov ah,0ah
               int 21h
               mov si,offset NUM
               mov di,offset LEV00_CS3
               mov bl,[si+2]
               mov [di+3],bl
               mov bh,[si+3]
               mov [di+4],bh
               mov al,[si+1]
               cmp al,2
               jne REJETNUM

               cmp bl,30h
               jb REJETNUM
               cmp bl,39h
               ja REJETNUM
               
               cmp bh,30h
               jb REJETNUM
               cmp bh,39h
               ja REJETNUM
     
               ret

REJETNUM:      pop ax
               jmp RETURN_TO_EDIT

TO_TOP:        mov bh,0
               xor dx,dx
               mov ah,2
               int 10h
               ret


LOADMAZE:      mov bp,sp
LOADMAZE2:     call TO_TOP
               HMOUSE
               mov dx,offset LOADNUM
               call PRINTSAVEORLOAD
               
               SMOUSE

               mov dx,DATA
               mov ds,dx
               mov es,dx
               mov dx,offset LEV00_CS3            
               mov bx,offset LEVEL_DATA
               mov cx,4096
               call LOADOLD2
               HMOUSE
               mov sp,bp
               jmp RETURN_TO_EDIT

SAVEMAZE:      mov bp,sp
SAVEMAZE2:     call TO_TOP
               HMOUSE
               mov dx,offset SAVENUM
               call PRINTSAVEORLOAD
               
               SMOUSE

               mov dx,offset LEV00_CS3
               call MAKEPATH
               
               mov dx,DATA
               mov ds,dx
               mov dx,offset FILENAME
               mov cx,0
               mov ah,3ch
               int 21h
               ;jc NOT_FOUND            
               jc SAVEMAZE2

               push ax
               mov bx,ax
               mov ah,40h
               mov dx,offset LEVEL_DATA -7
               mov cx,4096+7
               int 21h
               ;jc NOT_FOUND
               jc SAVEMAZE2

               pop bx
               mov ah,3eh
               int 21h
               ;jc NOT_FOUND
               jc SAVEMAZE2

               HMOUSE
               mov sp,bp
               jmp RETURN_TO_EDIT

               ;-------------------------------------------------

BORDERS:  pusha
          mov di,offset LEVEL_DATA
          mov eax,01010101h
          ;mov cx,((5*128)/4)
          mov cx,((5*64)/4)           ; modifications
PUNDNBORDERS:  mov [di],eax
          ;mov [di+((64-6)*128)],eax
          ;mov [di+((64-6)*64)],eax    ; modifications
         mov [di+((64-5)*64)],eax    ; modifications
 
          add di,4
          loop PUNDNBORDERS

          mov di,offset LEVEL_DATA
          mov dx,64
PRGTSIDEDOWN:  mov cx,5
PRGTSIDEBORDER:     mov [di],ax
          inc di
          inc di
          loop PRGTSIDEBORDER
          ;add di,128-10
          add di,64-10                  ; modifications
          mov cx,dx
          dec dx
          loop PRGTSIDEDOWN   
          popa
          ret       

               ;-------------------------------------------------

LOADOLD2:  call MAKEPATH
          push bx      ; offset destination      
          push cx      ; nombre d'octets a lire
          push es      ; segment destination
          mov al,0
          mov ah,3dh
          int 21h
          jc LOADMAZE2

          push ax      ; sauvegarde du code d'acces au fichier
          mov bx,ax    ; insere le code d'acces dans BX
          xor cx,cx    ; deplace le pointeur du fichier
          mov dx,7  
          mov al,0     ; relatif au debut du fichier
          mov ah,42h
          int 21h
          jc LOADMAZE2

          pop bx         ; retire le code d'acces au fichier
          pop ds       ; segment destination
          pop cx       ; nombre d'octets a lire
          pop dx       ; offset destination
          push bx      ; sauvegarde le code d'acces
          mov ah,3fh
          int 21h
          jc LOADMAZE2

          pop bx       ; retire le code d'acces au fichier
          mov ah,3eh
          int 21h
          jc LOADMAZE2
          ret

RETURN_TO_CS3: HMOUSE
               jmp PREPARE_GAME

; -----------------------FIN DU PROGRAMME-----------------
BEGINN    ENDP                            
CODE ENDS                                
END     BEGINN                                        
;---------------------------------------------------------
