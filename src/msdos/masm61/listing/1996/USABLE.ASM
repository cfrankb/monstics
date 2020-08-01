;---------------------------------------------------------------------
OutText MACRO _X_, _Y_, _TEXT_, _TCOLOR_, _BCOLOR_
     invoke _OutText, _X_, _Y_, _TEXT_, _TCOLOR_, _BCOLOR_
ENDM
;---------------------------------------------------------------------

;--------------------------------------------------------------------
_OutText PROTO NEAR PASCAL :WORD, :WORD, :DWORD, :BYTE, :BYTE
_OutText PROC NEAR PASCAL, _X_:WORD, _Y_:WORD, _TEXT_:DWORD, _TCOLOR_:BYTE, _BCOLOR_:BYTE
;--------------------------------------------------------------------

Local 		TempDest: DWORD

		pushall
                xor eax,eax
                mov ax, _Y_
                mul mode_info_obj. XResolution

                shl edx, 16
                mov dx,ax  			; edx = y * Xres

                xor eax,eax
                mov ax, _X_
                add edx, eax			; edx= y*res+ x

                mov eax,edx			; eax=edx
                shr eax,2			; eax /4
                shr eax, 10                     ; eax/1024/4

                pushall
                ss_setfastWindow 0, <ax>, mode_info_obj. WinFuncPtr
                popall

                mov ebx,edx
                shl eax,12
                sub ebx,eax

                mov edi,ebx
                add edi, 0a0000h		; abs adresse on screen
		mov tempdest, edi

           	mov esi, _TEXT_
                mov al,[esi]
                .while al!=0 && al!="$"
;                  ecrirecar <al>

		  ;-----------------------------------------
  			mov ebx, offset ascii_table
	                mov ah, [ebx]
			.while al!=[ebx] && ah!=0
	   		   inc ebx
	                   mov ah, [ebx]
        	        .endw

	                sub ebx, offset ascii_table
	                shl ebx, 6
	                add ebx, offset ascii_data
                        add ebx,64
	                ;ret
                  ;call LookInTable	; get ebx for obj
		  ;----------------------------------------
                  mov edi, tempdest
                  add tempdest,8

                  ;gotoxy 0,8
                  ;printd <edi>
    ;
     ;              cmp al," "
      ;             je __TADUM
		  mov dx, 8
XX0002:
                    mov cx, 8
XX0001:
                     mov al,[ebx]
                     or al,al
                     je black
		     cmp al,15
                     je White
                     mov byte ptr gs:[edi],al
                     jmp XBlack

White:
                     mov al, _Tcolor_
                     mov byte ptr gs:[edi], al
                     jmp XBlack
Black:
                     mov al, _Bcolor_
		     mov byte ptr gs:[edi], al
XBlack:

                    inc ebx
		    inc edi
                  loop XX0001

                  xor eax,eax
                  mov ax, mode_info_obj.XResolution
                  add edi, eax
                  sub edi,8

                  mov cx,dx
                  dec dx
                loop XX0002

__TADUM:

                  inc esi
                  mov al,[esi]
                .endw

	        popall
	        ret


_OutText ENDP

;---------------------------------------------------------------------
DrawSqrt MACRO _x_, _y_, _len_, _hei_, _color_
	invoke _DrawSqrt, _X_,_Y_, _LEN_,_HEI_,_COLOR_
ENDM

_DrawSqrt PROTO NEAR PASCAL :WORD,:WORD,:WORD, :WORD,:BYTE
_DrawSqrt PROC  NEAR PASCAL _X_:WORD,_Y_:WORD, _LEN_:WORD,_HEI_:WORD,_COLOR_:BYTE
;-----------------------------------------------------------------------

		pushall
                xor eax,eax
                mov ax, _Y_
                mul mode_info_obj. XResolution

                shl edx, 16
                mov dx,ax  			; edx = y * Xres

                xor eax,eax
                mov ax, _X_
                add edx, eax			; edx= y*res+ x

                mov eax,edx			; eax=edx
                shr eax,2			; eax /4
                shr eax, 10                     ; eax/1024/4

                pushall
                ss_setfastWindow 0, <ax>, mode_info_obj. WinFuncPtr
                popall

                mov ebx,edx
                shl eax,12
                sub ebx,eax

                mov edi,ebx
                add edi, 0a0000h		; abs adresse on screen
		;mov tempdest, edi

;                pushall
 ;               printd <edi>
  ;              popall


                mov al, _color_
                xor ebx,ebx
                mov bx, mode_info_obj. XResolution
                sub bx, _len_

                mov dx,_hei_
DD0002:         mov cx,_len_

DD0001:
                mov gs:[edi],al
                inc edi
                loop DD0001

                add edi, ebx
                mov cx,dx
                dec dx
                loop DD0002
		popall
                ret
_DrawSqrt	ENDP

;-----------------------------------------------------------------------
;---------------------------------------------------------------------
; SS_FINDFIRST
;
; IN
; cx= attribut, EDX = azt name
; OUT
; if carry = failed then ax = error code.


ss_findfirst PROC NEAR PASCAL

;		pushall
;                print <edx>
;                printd DtaPtr
;                popall
                clc
                push edx

                xor eax,eax
                mov ax, Code32
                shl eax, 4
                add eax, edx

                mov edx,eax
                and eax, 15
                shr edx,4

		mov v86r_ah, 4eh	; ah = findfirst
		mov v86r_cx, cx		; cx= cx

                mov v86r_ds, dx
                mov v86r_dx, ax
                mov al, 21h
                int 33h
                mov ax, v86r_ax
                pop edx
                ret

ss_findfirst ENDP

ss_findnext  PROC NEAR PASCAL

		clc
                push edx
                ;mov eax, edx
                ;and eax, 15
                ;shr edx,4

		mov v86r_ah, 4fh	; ah = findfirst
		;mov v86r_cx, cx		; cx= cx

                ;mov v86r_ds, dx
                ;mov v86r_dx, ax
                mov al, 21h
                int 33h
                mov ax, v86r_ax
                pop edx
                ret

ss_findnext  ENDP

;---------------------------------------------------------------------
; Dodir: Read the content of the current directory.
;
; SYNTAXE:  invoke DoDir, [DDptrFileType$]
;
; Structure of an entry
Image_Type EQU 0		; 1 byte image type descriptor
				;  0 unknown
                                ;  1 Ima 1.0
                                ;  3 Ima 3.0
                                ; -1 End of data

Image_Name EQU 1		; 13 bytes name of file
Image_desc EQU 15               ; 16 bytes description

ima0		db " raw/FNT ",0
ima1		db " IMA 1.0 ",0
ima3		db " IMA 3.0 ",0

align 4
DestName	dd 0
ImageAbsSize EQU ((400-16)/8)*64*64
DtaPtr		dd offset Dta

FilenameOffset EQU 1eh

Testing		db "Testing",13,10,"$"
TXT_FindNext	db "FindNext",13,10,"$"

Dta		db 1eh DUP (0)
           	db 0,0
                db 4096 DUP (0)

ALL_FILES	db "*.*",0
NULL_FILES	db 0
		;  0  123456789012345
DriveString	db 3,"A:            ",0
		db 16 DUP (0)
;-------------------------------------------------------------------------
DoDir PROTO NEAR PASCAL :DWORD
DoDir PROC NEAR PASCAL _FILETYPE_:DWORD

		pushall

                call GetDta			; Get the location of
                				; the DTA (disk transfer
                                                ; area)

                mov eax, offset Dta
                xor ebx,ebx
                mov bx, Code32
                shl ebx, 4
                add eax,ebx
                mov ebx,eax

                shr eax, 4
                mov ebx, offset Dta
                and ebx, 15

                mov v86r_ds, ax
                mov v86r_dx, bx
                mov v86r_ah, 1ah		; Set a new DTA (disk
                mov al, 21h			; transfer area) larger
                int 33h				; so we won't have problems

                ; Ajust the destination name
                mov edi, _himembase
                add edi, 512*1024
                mov DestName, edi

                ;; Add 4 drives to list
                mov byte ptr DriveString+1, "A"
                mov dx, 4
                xor ebx,ebx
DD0002:
                mov esi, offset DriveString
                mov cx, 32

DD0001:
                mov al, [esi]
                mov byte ptr [edi+ebx], AL
                inc esi
                inc ebx
                loop DD0001

                inc byte ptr DriveString+1
		dec dx
                or dx,dx
                jne DD0002

		add DestName, 32*4

                ;;---------------------------------
                ;; FindFirst DIR
		mov cx, Directory;Archived
                mov edx, offset ALL_FILES
		call ss_findfirst
                jc NoMoreDirs;

                mov edx, offset Dta
	mov al,[edx+15h]
        and al,Directory
	.if al==Directory && al!=al


                add edx, 1eh ;+1
                mov edi, DestName
                add DestName, 32
                mov byte ptr [edi],2		; TypeDef DIR

                mov cx, 16
                mov ebx,1
GND00:
                mov byte ptr [edi+ebx], 32
                inc ebx
                loop GND00

                mov byte ptr [edi+15],0

                mov al, [edx]
                .while al!=0
                  .if al!=0
                     mov [edi+1], al
                  .else
                     mov byte ptr [edi+1],32
                  .endif
                  mov byte ptr [edi+16], al

                  inc edi
                  inc edx
                  mov al, [edx]
                .endw

                mov byte ptr [edi+16],0

	.endif

GND02:
                ;; FindNext DIR
		call ss_findnext
                jc NoMoreDirs

                mov edx, offset Dta;Ptr
	mov al,[edx+15h]
        and al,Directory
	.if al==Directory


                add edx, 1eh ;+1

                mov edi, DestName
                add DestName, 32
                mov byte ptr [edi],2		; TypeDef DIR

                mov cx, 16
                mov ebx,1
GND01:
                mov byte ptr [edi+ebx], 32
                inc ebx
                loop GND01

		mov byte ptr [edi+15],0


                mov al, [edx]
                .while al!=0
                  .if al!=0
                     mov [edi+1], al
                  .else
                     mov byte ptr [edi+1],32
                  .endif
                  mov byte ptr [edi+16], al

                  inc edi
                  inc edx
                  mov al, [edx]
                .endw
                mov byte ptr [edi+16],0

	.endif
;                sub edi,13
     		jmp GND02

                ;; Ok! We've finished searching for Directories

NoMoreDirs:
                ;; FindFirst File...
		mov cx, 0;Archived
                mov edx, offset ALL_IMA
		call ss_findfirst
                jc NoMoreFiles

                mov edx, offset Dta
                add edx, 1eh ;+1
                mov edi, DestName
                add DestName, 32
                mov byte ptr [edi],1		; TYPEDEF FILE

                mov cx, 16
                mov ebx,1
GN100:
                mov byte ptr [edi+ebx], 32
                inc ebx
                loop GN100

                mov byte ptr [edi+15],0

                mov al, [edx]
                .while al!=0
                  .if al!=0
                     mov [edi+1], al
                  .else
                     mov byte ptr [edi+1],32
                  .endif
                  mov byte ptr [edi+16], al

                  inc edi
                  inc edx
                  mov al, [edx]
                .endw
                mov byte ptr [edi+16],0

GN002:
                ;; FindNext File
		call ss_findnext
                jc NoMoreFiles


                mov edx, offset Dta;Ptr
                add edx, 1eh ;+1

                mov edi, DestName
                add DestName, 32
                mov byte ptr [edi],1		; TYPEDEF FILE

                mov cx, 16
                mov ebx,1
GN101:
                mov byte ptr [edi+ebx], 32
                inc ebx
                loop GN101

		mov byte ptr [edi+15],0


                mov al, [edx]
                .while al!=0
                  .if al!=0
                     mov [edi+1], al
                  .else
                     mov byte ptr [edi+1],32
                  .endif
                  mov byte ptr [edi+16], al

                  inc edi
                  inc edx
                  mov al, [edx]
                .endw
                mov byte ptr [edi+16],0
;                sub edi,13
     		jmp GN002

NoMoreFiles:

		mov edi, DestName
		mov byte ptr [edi], -1
		
                sub edi, _himembase
                sub edi,512*1024
                mov eax,edi
                shr eax, 5
                mov [NbFiles],ax

                mov eax, DtaPtr
                shr eax,4
                mov ebx, DtaPtr
                and ebx,15
                mov v86r_ds, ax
                mov v86r_dx, bx
                mov v86r_ah, 1ah
                mov al, 21h
                int 33h

                popall
                ret

DoDir		ENDP

GetPspAdrr PROC NEAR PASCAL
;---------
; Execute a DOS function call from PMODE. Then return the result
; in ESI.
; IN: none
; OUT: ESI is the PSP address , offset of CODE32

                mov esi, _pspa
                ret


GetPspAdrr	ENDP

;--------------------------------------------------------------------

align 4
Args_data  db 256 DUP (0)		; Data information for each args
Args_table dd 16 DUP (0)                ; Table (array) of args.
PSP_Copy   db 256 DUP (0)		; Copy of the PSP table
NbArgs     dw 0				; Number of Args on command line

SeparateArgs PROC NEAR PASCAL
;-----------
; Fill-in the args_table. Call GetPspAddr. Must be called before
; any disk access or PSP lost. Args_table provide a facility
; similar to those you find in C compiler. Neat. yeah! It also
; copy the PSP to a secure area for further reference.

		pushall

                mov NbArgs,0
                ; Getting PSP addr into ESI
		call GetPspAdrr

                ; copy the PSP to a secure location.
                xor ebx,ebx
                mov edi, offset PSP_Copy
                mov cx, 256
                .while cx!=0
		  mov al, gs:[esi+ebx]
                  mov byte ptr [edi+ebx], al
                  inc ebx
                  dec cx
                .endw
		;debugbreak offset TEXT5

                mov esi,edi
                add esi,80h
                xor dx,dx
                mov dl, [esi]
                inc esi
                mov edi, offset Args_data
                mov ebx, offset args_table
		;debugbreak offset TEXT8

                .while dl!=0
		;debugbreak offset TEXT7

                  mov al, [esi]
                  .while al==32 && dl!=0
                     inc		 esi
                     dec dl
                     mov al,[esi]
                  .endw

                  .if dl!=0
                    inc NbArgs
                    mov [ebx], edi
                    add ebx,4
    		    ;debugbreak offset TEXT6
                  .endif

                  .if al!=32 && dl!=0
                     .if al>="a" && al <="z"
                       add al,"A"
                       sub al,"a"
                     .endif
                     mov [edi],al
                     inc edi
                     inc esi
                     mov al, [esi]
                     dec dl
                  .endif

                  .while al!=32 && al!=0 && al!="/" && dl!=0
                     .if al>="a" && al <="z"
                       add al,"A"
                       sub al,"a"
                     .endif
                    mov [edi],al
                    inc edi
                    inc esi
                    mov al, [esi]
                    dec dl
                  .endw

                   mov byte ptr [edi],0
                   inc edi
                   mov byte ptr [edi],"$"
                   inc edi

                .endw


                ;print Args_table
                ;printcr

                ;print Args_table+4
                ;printcr

                ;print Args_table+8
                ;printcr

                ;print Args_table+12
                ;printcr

                ;print Args_table+16
                ;printcr

                ;debugbreak offset TEXT9

                popall
		ret
SeparateArgs  ENDP

;-------------------------------------------------------------------
;
; PMODE ASM version of STRCMP
; Be sure that string is terminated by a '/0'.
;

StrCmp		MACRO _S_, _D_
                invoke _strcmp, _S_, _D_
		ENDM

_StrCmp		PROC NEAR PASCAL, _S_:DWORD, _D_:DWORD

                push esi
                push edi
		mov esi, _S_
                mov edi, _D_

                xor al,al
                .while byte ptr [esi]!=0 && byte ptr [edi]!=0 && al==0
                   inc edi
                   inc esi
                   mov al, [esi]
                   sub al, [edi]
                .endw

                mov al, [esi]
                sub al, [edi]

                pop edi
                pop esi
                ret

_StrCmp 	ENDP
;-----------------------------------------------------------------------
;--------------------------------------------------------------------
;
; GetDta
;
;

GetDta PROC NEAR PASCAL
		pushall

                mov al, 21h
                mov v86r_ah,2fh
                int 33h

                xor eax,eax
                mov ax, v86r_es
                shl eax,4

                xor ebx,ebx
                mov bx, v86r_bx
                add eax,ebx
                mov DtaPtr, eax

	        popall
	        ret
GetDta ENDP
;----------------------------------------------------------

;-------------------------------------------------------------------
;
; PMODE ASM version of STRCMP
; Be sure that string is terminated by a '/0'.
;

StrCmp		MACRO _S_, _D_
                invoke _strcmp, _S_, _D_
		ENDM

_StrCmp		PROC NEAR PASCAL, _S_:DWORD, _D_:DWORD

                push esi
                push edi
		mov esi, _S_
                mov edi, _D_

                xor al,al
                .while byte ptr [esi]!=0 && byte ptr [edi]!=0 && al==0
                   inc edi
                   inc esi
                   mov al, [esi]
                   sub al, [edi]
                .endw

                mov al, [esi]
                sub al, [edi]

                pop edi
                pop esi
                ret

_StrCmp 	ENDP
;-----------------------------------------------------------------------
ShowScreen:
;---------
		mov edi, 0a0000h
		mov esi,_himembase
		ss_setfastwindow 0, 0, mode_info_obj.WinFuncPtr

		cld
		mov edx, 0
		mov bx,5
XX00014:
		mov cx, 65536/4

		mov edi,0a0000h
XX00013:

		mov eax, ds:[esi]
		mov gs:[edi],eax
		add edi,4
		add esi,4
		loop XX00013


		add edx, 65536/4096
  		ss_setfastwindow 0, <dx>, mode_info_obj.WinFuncPtr

		dec bx
		or bx,bx
		jne XX00014
		ret

;------------------------------------------------------------------------
; Get current drive
; IN:
; OUT: al=drive (0=A, 1=B ...)
;
GetCurrentDrive:

                mov v86r_ah,19h		; mov ah,19h
                mov al,21h              ; int 21h
                int 33h
                mov al, V86r_al		; mov al, al
		ret

GetCurrentDir:
;-------------
                pushall
                xor eax,eax
                mov ax, Code32
                shl eax,4
                add edi,eax

		mov eax, edi
                and eax,15
                shr edi, 4

                mov v86r_ah,47h		; mov ah,47h
                mov v86r_ds, di         ; mov ds,di
                mov v86r_si, ax         ; mov si,ax
                mov v86r_dl,0           ; mov dl,0 	current drive
                mov al,21h		; int 21h
                int 33h

                popall
                ret

MCP_ERR		db "GetCurrentPath issued an error",10,13,"$"
RootPath	db "\",0
MakeCurrentPath:
;---------------
                pushall

		call  GetCurrentDrive
                add al, "A"
                ;inc al
                mov CurrentPath, al
                mov byte ptr CurrentPath+1, ":"
                mov byte ptr CurrentPath+2, "\"

                mov edi,offset CurrentPath+3
                call GetCurrentDir
                jnc MCP0001
                ;print offset MCP_ERR

                pushall
                  invoke _drawtextWindow,DialogFTopx, DialogFTopY ,offset DrvERRDLG, 15,4

                  mov v86r_ah, 0eh
                  mov v86r_dl,2
                  mov al,21h
                  int 33h

                  mov esi,offset RootPath
                  call ChangeDir

                  ss_getax
                  .while al!=27 && al!=9 && ah!=KEY_F1 && al!=13 && al!=32 && ah!=KEY_UP && ah!=KEY_DN
                     ss_getax
                  .endw
                  call showScreen2
                  invoke DoDir, offset ALL_IMA
  		  call DrawImaLoadDialogBox
		popall

MCP0001:
                popall
                ret

