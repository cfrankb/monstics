;----------------------------------------------------------------
;       LEVELS EDITORS for THE VLAMITS
;       by Francois Blanchette
;----------------------------------------------------------------
SMOUSE    MACRO
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
COPYRIGHT           db "(C) 1993 FRANCOIS BLANCHETTE."
CLEAR_MAZE_TEXT     db "Are you sure you want to clear maze?$"
LOAD_NUM            db "Enter level number to be loaded:$"
SAVE_NUM            db "Enter level number to be saved:$"

CARAC               db 0
MX                  db 0
MY                  db 0
CD                  db 0
NUM                 db 3,0,0,0,0
VLAMITS_MCG         db "vlaedit.mcg",0
LEV00_VLA           db "lev00.vla",0
;PATH		     db "c:\other\vlamits\",0
PATH		   db 0
FILENAME            db 32 dup (0)
FILES_DOWN          db "Warning: missing or corrupted file.$"
LEVEL_DATA          db 8192 dup (0)
MCG_IMAGES          db 50000 dup (1)
OLD_VIDEO_MODE      db 0           
COMMAND             db "LEVXX.vla",0
LDX                 db 0
LDY                 db 0
DATA      ENDS
;----------------------------------------------------------------
CODE SEGMENT READONLY PUBLIC 'CODE'
BEGINN    PROC NEAR
;----------------------------------------------------------------

          .486

          ; Ceci est une proc‚dure exp‚rimentale qui v‚rifie 
          ; l'exitance d'un code du la ligne de d‚marrage.


READY_FOR_IT:  mov ah,0fh
               int 10h   
               mov dx,DATA
               mov ds,dx
               mov di,offset OLD_VIDEO_MODE
               mov [di],al
          
               mov ah,0
               mov al,13h
               int 10h

          ; LEVELS EDITOR CONVENSIONS
          ; DS: DATA SEGMENT
          ; ES: MEM1 - MCG
          ; FS: MEM2 - LEVELS DATA
          ; GS: 0A00H- VIDEO MEMORY     

          ;jmp ANY_KEYS


RE_INIT:  ; Chargement de VLAMITS.MCG
          mov dx,DATA
          mov ds,dx
          mov es,dx
          mov bx,offset MCG_IMAGES
          mov dx,offset VLAMITS_MCG
          mov cx,50000 
          call LOADOLD

          ;jmp QUIT
          
          mov ax,0
          int 33h
RENTRANCE:          SMOUSE

          ;-----------------------------------------------------
          ; Initialisation centrale
          
BODY_OF_THE_EDITOR:call CONVENSIONS
          ;jmp ANY_KEYS
          HMOUSE
          call PUT_CARAC      
          call BORDERS
          call SHOW_SCREEN
          SMOUSE
          ;jmp ANY_KEYS


          
;--------------------------------------------------------

MBOUCLE   :    ;SMOUSE
          call WBUT_1
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
          cmp al,"r"
          je RE_INIT
          cmp al,"s"
          je SOURCE
          cmp al,"-"
          je LOAD_A_LEVEL
          cmp al,"="
          je SAVE_A_LEVEL
       cmp al,"f"
          je SMALL_EDITOR
          cmp al,27
          je QUIT

          jmp MBOUCLE

          ;------------------------------------------------

SOURCE:   xor ah,ah
          mov al,dl
          add al,bh
          rol ax,7       ; AX= (Y+MY)*128
          add al,cl
          add al,bl      ; AX= (Y+MY)*128+X+MX
          add ax,offset LEVEL_DATA
          mov si,ax
          mov di,offset CD
          mov al,[si]
          mov [di],al
          jmp MBOUCLE



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

MAZE_LEFT:     cmp bl,128-10
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

MAZE_LEFT2:    cmp bl,128-10
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
          cmp al,256-20
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
          rol dx,7
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

;---------------------------------------------------------------

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
          mov cx,8192/4
          mov eax,0
APPCLMZ:  mov [di],eax
          add di,4
          loop APPCLMZ

          ; MODIFICATION
       ;mov di,offset NOA
       ;mov cx,32768+1
       ;mov al,0
CLMACTO:  ;mov es:[di],al
       ;inc di
       ;loop CLMACTO

          jmp BODY_OF_THE_EDITOR

          
;-------------------------------------------------------

          ;LOAD_A_LEVEL

LOAD_A_LEVEL:  mov bp,sp
               xor dx,dx
               mov bh,0
               mov ah,2
               int 21h

               HMOUSE
               call CLS
               call CONVENSIONS
               mov dx,offset LOAD_NUM
               mov ah,9
               int 21h

               call READ_A_NUM

               mov si,offset NUM+2
               mov di,offset LEV00_VLA+3
               mov al,[si]
               mov [di],al
               mov al,[si+1]
               mov [di+1],al

               mov dx,DATA
               mov ds,dx
               mov es,dx
               mov dx,offset LEV00_VLA
               mov bx,offset LEVEL_DATA
               mov cx,8192
               call LOADNEW

               jmp RENTRANCE

READ_A_NUM:    mov dx,offset NUM
               mov ah,0ah
               int 21h
               
               mov si,offset NUM

               mov al,[si+1]
               cmp al,2
               jb READ_OUT
     
               mov al,[si+2]
               cmp al,30h
               jb READ_OUT
               cmp al,39h
               ja READ_OUT
               
               mov al,[si+3]
               cmp al,30h
               jb READ_OUT
               cmp al,39h
               ja READ_OUT
               
               ret            

READ_OUT:      pop ax
               pop ax
               jmp RENTRANCE

               ; SAVE A FILE

SAVE_A_LEVEL:  mov bp,sp
               HMOUSE
               xor dx,dx
               mov bh,0
               mov ah,2
               int 21h

               call CLS
               mov dx,DATA
               mov ds,dx
               mov dx,offset SAVE_NUM
               mov ah,9
               int 21h

               call READ_A_NUM

               call CONVENSIONS

               mov si,offset NUM+2
               mov di,offset LEV00_VLA+3
               mov al,[si]
               mov [di],al
               mov al,[si+1]
               mov [di+1],al

               mov dx,offset LEV00_VLA
               call MAKEPATH
               
               mov dx,offset FILENAME
               mov cx,0
               mov ah,3ch               ; Cr‚e un fichier
               int 21h
               jc WRITE_ERROR

               push ax
               mov bx,ax
               mov cx,8192
               mov dx,DATA
               mov ds,dx
               mov dx,offset LEVEL_DATA
               mov ah,40h               ; criture d'un fichier
               int 21h
               jc WRITE_ERROR

               pop bx
               mov ah,3eh               ; Fermeture du fichier
               int 21h
               jc WRITE_ERROR
               jmp RENTRANCE

WRITE_ERROR:   SMOUSE
               mov sp,bp
               jmp SAVE_A_LEVEL
     

;----------------------------------------------------------------
; ROUTINES
;----------------------------------------------------------------

GETAX:         push bx
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
GETOUT:        pop ds
          pop dx
          pop bx
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
          ret

          
;--------------------------------------------------------

CLS:      
LIGHT_OUT:     pusha
          mov eax,0
          mov dx,0a000h
          mov ds,dx 
          mov si,0
          mov cx,4000h
MKBCK:         mov [si],eax
          add si,4
          loop MKBCK
          popa
          ret

QUIT:          mov dx,DATA
          mov ds,dx
          mov si,offset OLD_VIDEO_MODE
          xor ax,ax
          mov al,[si]
          int 10h
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
          mov ah,4ch
          int 21h

          
;-------------------------------------------------------

CONVENSIONS:   push dx
          mov dx,DATA        ; SETUP THE LEVEL EDITOR CONVENSIONS
          mov ds,dx
       ;mov dx,MEM1
          mov es,dx
          ;mov dx,MEM2
          mov fs,dx
          mov dx,0a000h
          mov gs,dx
          pop dx
          ret

          
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

          ;--------------------------------------------------

SHOW_SCREEN:   ; Détermine le point initiale designé par (0,0)
          ; celui-ci est designé par si.

          ; si = MX + MY * 128 + offset LEVEL_DATA

          pusha
          xor di,di
          xor ax,ax
          xor bx,bx
          mov si,offset MX
          mov al,[si]
          mov bl,[si+1]
          rol bx,7
          mov si,bx
          add si,ax
          add si,offset LEVEL_DATA    ; si -> (0,0) 

          ; La boucle centrale effectue 11 sweep verticales
          ; de 20 sweep horizontales.

          mov dx,11     ; RANGERS
SCRNEXTY: mov cx,20     ; COLONNES

          ; Determinons la valeur de PV à la position (sur

          ; qui égale (cx-20,dx-10).

          ; si = [valeur] * 256

SCRNEXTX: xor ax,ax
          mov al,[si]
          rol ax,8
          push si   
          mov si,ax               ; si = PV * 256
          add si,offset MCG_IMAGES

          push dx
          push cx
                    
          ; Passons maintenant au coeur de l'opération

           
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
          add si,108
          loop SCRNEXTY
          popa
          ret

         
;-------------------------------------------------------

BORDERS:  pusha
          mov di,offset LEVEL_DATA
          mov eax,01010101h
          mov cx,((5*128)/4)
PUNDNBORDERS:  mov [di],eax
          mov [di+((64-6)*128)],eax
          add di,4
          loop PUNDNBORDERS

          mov di,offset LEVEL_DATA
          mov dx,64
PRGTSIDEDOWN:  mov cx,5
PRGTSIDEBORDER:     mov [di],ax
          inc di
          inc di
          loop PRGTSIDEBORDER
          add di,128-10
          mov cx,dx
          dec dx
          loop PRGTSIDEDOWN   
          popa
          ret       

          
;-------------------------------------------------------         
          

ANY_KEYS: xor ax,ax
          int 16h
          jmp QUIT

          
;-------------------------------------------------------

WBUT_1:   push ax
          mov ax,3
          int 33h
          shr cx,4+1
          shr dx,3+1          
          pop ax
          ret
          
WBUT:     push ax
          mov ax,3
          int 33h
          shr cx,4
          shr dx,3          
          pop ax
          ret
          
;--------------------------------------------------------

SOME_TIME_OFF: mov cx,7000h
STOFF:         mov ax,ax
          loop STOFF
          ret






























;---------------------------------------------------------------
;    La section ci-dessous … ‚t‚ ‚crite en quatriŠme vitesse.
;    Son but est d'afficher l'‚cran plus petit que d'habitude.
;---------------------------------------------------------------

SMALL_EDITOR:  call CONVENSIONS

SM_SCREEN:     HMOUSE
               call SMALL_SCREEN
               SMOUSE

SM_MBOUCLE:    call GETAX
               call WBUT
               cmp bx,1
               je PUSH_BUTTON

               mov fs,dx

               mov si,offset MX
               mov dl,[si]
               mov dh,[si+1]
               cmp al,"f"
               je FULL_SCREEN
               cmp al,"8"
               je SM_UP
               cmp al,"2"
               je SM_DOWN
               cmp al,"4"
               je SM_LEFT
               cmp al,"6"
               je SM_RIGHT
               cmp al,"["
               je DEC_CARAC_
               cmp al,"]"
               je INC_CARAC_
               cmp al,"s"
               je SOURCE_
               
               cmp al,"-"
               je LOAD_A_LEVEL
               cmp al,"="
               je SAVE_A_LEVEL

               cmp al,27
               je QUIT

               jmp SM_MBOUCLE

DEC_CARAC_:    mov si,offset CARAC
               mov al,[si]
               cmp al,0
               je SM_MBOUCLE
               dec al
SHARED:        mov [si],al
               HMOUSE
               call PUT_CARAC
               SMOUSE
               jmp SM_MBOUCLE

INC_CARAC_:    mov si,offset CARAC
               mov al,[si]
               cmp al,255-20
               je SM_MBOUCLE
               inc al
               jmp SHARED

PICK_ITEM:     ror cx,1
               mov si,offset CARAC
               mov al,[si]
               add al,cl
               mov si,offset CD
               mov [si],al
            jmp SM_MBOUCLE

SOURCE_:       push fs
               pop dx
               mov si,offset MX
               mov al,[si+1]       ; AL=MY
               xor ah,ah
               add al,dl           ; AL=MY+Y
               rol ax,7            ; AX=(MY+Y)*128
               add al,[si]         ; AX=(MY+Y)*128+MX
               add al,cl           ; AX=(MY+Y)*128+MX+X
               add ax,offset LEVEL_DATA; AX=... + LEVEL_DATA
               mov si,ax
               mov al,[si]
               mov si,offset CD
               mov [si],al
               jmp SM_MBOUCLE

PUSH_BUTTON:   cmp dx,21
               ja PICK_ITEM

               mov si,offset LDX
               cmp cl,[si]
               jne LDXOK
               cmp dl,[si+1]
               je SM_MBOUCLE

LDXOK:         mov al,dl
               xor ah,ah
               mov si,offset MX
               add al,[si+1]
               rol ax,7
               add ax,cx
               add al,[si]
               add ax,offset LEVEL_DATA

               mov di,ax
          
               mov si,offset CD
               mov al,[si]
               mov [di],al

               mov di,offset LDX
               mov [di],cl
               mov [di+1],dl
               call BORDERS

               ;jmp SM_SCREEN

               xor ah,ah
               rol ax,8
               mov si,ax      ; SI=I*256
               add si,offset MCG_IMAGES

               rol cx,3       ; CX=X*8
               mov al,0ah
               mul dl
               rol ax,8       ; AX=Y*0a00h
               mov di,ax
               add di,cx      ; DI=X*8+Y*0a00h

               HMOUSE

               mov dx,8
TRSN2:         mov cx,8
TRSN:          mov al,[si]
               mov gs:[di],al
               inc si
               inc si
               inc di
               loop TRSN

               add si,16
               add di,138h
               mov cx,dx
               dec dx
               loop TRSN2

               SMOUSE
               jmp SM_MBOUCLE

               ;--------------
SM_UP:         cmp dh,0
               je SM_MBOUCLE
               dec dh
STORE_MY:      mov [si+1],dh
               call XLDX
               jmp SM_SCREEN
               ;-------------
SM_DOWN:       inc dh
               jmp STORE_MY
               ;-------------
SM_LEFT:       cmp dl,0
               je SM_MBOUCLE
               dec dl
STORE_MX:      mov [si],dl
               jmp SM_SCREEN
               ;---------------
SM_RIGHT:      inc dl
               jmp STORE_MX
               ;-----------------

FULL_SCREEN:   HMOUSE
               call SHOW_SCREEN
               SMOUSE
               call XLDX
               jmp MBOUCLE

XLDX:          pusha
               mov si,offset LDX
               mov ax,0ffffh
               mov [si],ax
               popa           
               ret

               ;--------------------------
               ; SMALL_SCREEN
               ; INPUTS:
               ; no inputs
               ; OUTPUTS:
               ; prints out a small screen
               ;--------------------------
SMALL_SCREEN:  pusha
               mov si,offset MX
               mov al,[si+1]
               xor ah,ah
               rol ax,7       ; AX= [MY]*128
               add al,[si]    ; AX= [MY]*128+[MX]
               mov si,ax
               add si,offset LEVEL_DATA

               xor di,di
               mov dx,22

NMSL:          push di
               mov cx,40
NMS:           mov al,[si]

               push cx
               push di
               push si

               xor ah,ah
               rol ax,8
               add ax,offset MCG_IMAGES
               mov si,ax

               mov bx,8
MS_SCRL:       mov cx,8

MS_SCR:        mov al,[si]
               mov gs:[di],al
               inc si
               inc si
               inc di
               loop MS_SCR

               add di,138h
               mov cx,bx
               add si,16
               dec bx
               loop MS_SCRL

               pop si
               pop di
               pop cx

               add di,8
               inc si
               loop NMS

               mov cx,dx
               dec dx         

               pop di
               add di,0a00h
               add si,128-40
               loop NMSL
               popa
               ret

; -----------------------FIN DU PROGRAMME------------------------
BEGINN    ENDP                           ; Fin de la procedure
CODE ENDS                                ; Fin du programme
END     BEGINN                           ; Point 
;----------------------------------------------------------------
