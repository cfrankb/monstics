;**********************************************************************
; PMODE MODULE
;**********************************************************************
; NAME       : IMAVIEW3.ASM
; DESCRIPTION:
;
;**********************************************************************
;
; PMODE v2.1232 raw, DPMI, VCPI, & XMS compliant protected mode header.
; By Tran (a.k.a. Thomas Pytel) of Renaissance
;
; IMAVIEW3.ASM written by Francois Blanchette to run under PMODE
; Portion borrowed from EXAMPLE.ASM, written by Tran.
;
; 386.INC written by Francois Blanchette
; Portion borrowed from FILE.INC & PMODE.INC, written by Tran.
;
; 96REPV3.ASM written by Francois Blanchette
; Portion borrowed from FILE.INC & PMODE.INC, written by Tran.
;
; PMODE.OBJ compiled from PMODE.ASM, written by Tran.
;
; SEE PMODE.DOC ABOUT USING PMODE.
;
; CODE COMPILED USING MASM 6.1. (Sorry TASM lovers).
;
;***********************************************************************
.386p

;;; INCLUDE FILES
include \masm61\listing\386.inc

;;; PUBLIC procedure
public  _main
public  _leave

externdef hexcode:byte
externdef stringW:byte
externdef Ima2Bytes:byte
externdef FileFound: byte
externdef nbFiles:WORD

;####################################################################
copyrights segment para public use16
		   db "PMODE v2.1232 raw, DPMI, VCPI, & XMS compliant protected mode header. "
		   db "By Tran (a.k.a. Thomas Pytel) of Renaissance"
copyrights ends
;####################################################################

;----------------------------------------------------------------------
;####################################################################
code16  segment para public use16
	assume cs:code16, ds:code16
;####################################################################
rmirq0:                                 ; real mode IRQ0 handler
	push ax
	push ds

	mov ax,0b800h
	mov ds,ax
;	xor word ptr ds:[(4*160)+(38h*2)+(BasePos/256*160)],0fdbh
	pop ds
	mov al,20h
	out 20h,al
	pop ax
	iret
code16  ends
;####################################################################


;####################################################################
code32  segment para public use32
	assume cs:code32, ds:code32
;####################################################################

ormirq0         dd      ?               ; old real mode IRQ handler seg:off
opmirq0         dd      ?               ; old protected mode IRQ handler off

SystemType      db      "System type         :  $"
mainstr1        db      "Low memory free     :  0x$"
mainstr2        db      "Extended memory free:  0x$"

systypestrtbl   dd      sysstr0,sysstr1,sysstr2,sysstr3
sysstr0         db      'raw',0,"$"
sysstr1         db      'XMS',0,"$"
sysstr2         db      'VCPI',0,"$"
sysstr3         db      'DPMI',0,"$"
return          db      13,10,"$"
keystr          db      'Press any key to go on...',0

;#########################################################################
;;  F. BLANCHETTE ADD-ON
;#########################################################################

Tran1              db "PMODE v2.1232 raw, DPMI, VCPI, & XMS compliant protected mode header.",13,10,"$",0
Tran2              db "By Tran (a.k.a. Thomas Pytel) of Renaissance",13,10,"$",0
ERR_LOW_MEM        db "FATAL: Insuficient base memory to run program.",0
ERR_HI_MEM         db "FATAL: Insuficient XMS memory to run program.",0
ERR_VESA_INIT      db "FATAL: VESA driver intialisation failed.$"
ERR_XVESA_INFO     db "FATAL: No VESA information available.$"
ERR_XVESA_MODEINFO db "FATAL: No VESA mode information available.$"
ERR_XCORR_MODE     db "FATAL: No VESA mode to satisfy demand.$"
TXT_FatalReadErr   db "FATAL: File read error occured.$"
ERR_VESA_RES101    db "FATAL: VESA MODE 0x101 is not 640x480x256.$"

TXT_NEED           db "You need 0x$"
__TXT_BYTES_LOW    db " bytes of free base memory to run this program.$"
__TXT_BYTES_XMS    db " bytes of free XMS to run this program.$"

MinLowMem          dd 256*1024		; Requiered based Memory (in K)
MinXMSMem          dd 1*1024*1024	; Requiered XMS (in K)
oldmode            dw 0			; Old Video mode
FileBuf 	   db 4096 DUP (0)	; File Transfer Buffer

;-----------------------------------------------------------------------
;
; TRAN's handy work. I don't know what it does exactly but I'm keeping
; it there just in case it serves any purpose.
;
pmirq0:                                 ; protected mode IRQ0 handler
	push ds
	mov ds,cs:_selzero
;	xor word ptr ds:[0b8000h+(2*160)+(38h*2)+(BasePos/256*160)],0fdbh
	pop ds
	jmp cs:opmirq0                  ; chain to old IRQ0 redirector

int0d: iret

;----------------------------------------------------------------------
;
; PMODE jumps to _main to turn over control to your program. That is
; where your program begins.
;
_main:
	call SeparateArgs
	jmp module_start

_leave:

	jmp _exit

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

include \masm61\listing\_com386.inc


Syntaxe		db "IMAVIEW3 (C) 1996 FRANCOIS BLANCHETTE",10,13
		db "RUNNING UNDER PMODE by Tran (a.k.a. Thomas Pytel)",10,13
                db 13,10,"USAGE:",13,10
		db "IMAVIEW3 NomFic.IMA",13,10
                db "$"

;########################################################################
 module_start PROC NEAR
;########################################################################


		call ChkMem
                .if NbArgs>=1
		  call InitFileSys2
                  call LoadIma
		  call InitSVGA
                  call ClearBuffer
                  call DrawIma2Buffer
                  call ShowScreen
                  call WriteName
                  call getch
_Remove:
		  ;; Restore your old video mode and leave
		  mov bx, word ptr OldMode
	          ss_setvesamode bx
		  jmp _leave

                .else

                  print offset Syntaxe
                  jmp _leave
                .endif

;----------------------------------------------------

WriteName:
                mov edx,dword ptr Args_table
		invoke _OutText, 0,400-8, edx, 15,1
		ret

;----------------------------------------------------
ChkMem:
		mov eax, _lomemtop
                sub eax, _lomembase
                cmp eax, 256*1024
                jb CONVERR

		mov eax, _himemtop
                sub eax, _himembase
                cmp eax, 256*1024
                jb XMSERR

                ret

CONVERR_TXT	db "FATAL: Insuficient frem base memory.",10,13
		db "You need more free conventional memory to run program.",10,13,"$"
CONVERR:	print offset CONVERR_TXT
		jmp _leave

XMSERR_TXT	db "FATAL: Insuficient free XMS memory.",10,13
		db "You need to free 256k of XMS to run this program.",10,13,"$"
XMSERR:	print offset XMSERR_TXT
		jmp _leave

;----------------------------------------------------
;INT 21 FUNCTION 01 Saisie d'un caractère p.177/444
;Au retour AL contient le code du caractère.CTRL-C

getch:
		mov v86r_ah, 1
                mov al,21h
                int 33h
                ret

;---------------------------------------------------------
InitFileSys2:

	    	;; Define transfer buffer
                push eax
                mov eax, offset TransBuffer
		mov dword ptr _filebufloc, eax;offset FileBuf
		mov word ptr _filebuflen,  4096
                pop eax
		ret

align 4
TransBuffer	dw 0
       		db 4096*2 DUP (0)
;------------------------------------------------------------

align 2
ImaHeader	dw 0
align 4
IMC1sig		db "IMC1"
FILEsig		db 4 DUP (0)


LoadIma:
                ; Open File
		mov edx, dword ptr Args_table
                call _openfile
                jc ErrOpenFile	; v86r_bx = handle

                ; Read the 4st bytes of the .IMA file
                ; into FILESIG

                mov edx, offset FILESIG
                mov ecx, 4
                call _readfile
                jc ErrOpenImaFile

                ; If it is a new .IMA (IMC1 format) then
                ; jump 2 the decompression code.
                mov eax, dword ptr FileSig
                .if eax== dword ptr IMC1Sig

                  jmp LoadIMC1

                .endif

		; This file is an old .IMA
                ; Lseek 2 0 ... na na na >>>!
                mov eax, 0
                mov bl,0
                call _lseekfile

		; Read IMA header
                mov edx, offset ImaHeader
                mov ecx,2
                call _readfile
                jc ErrOpenFile

                ; read IMA to memory
                xor ax,ax
                mov al,byte ptr ImaHeader
                xor bx,bx
                mov bl, byte ptr ImaHeader+1
                mul bx

                ;shl edx,16
                xor edx,edx
                mov dx,ax  		; edx = len*hei
                shl edx, 6              ; edx = len*hei*64

                mov ecx, edx
		mov edx, _lomembase
                call _readfile
                jc ErrOpenFile

CloseImaFile:
                call _closeFile
                jc ErrOpenFile

		ret

ErrOpenFileTxt	db "FATAL: Unable to open file $",0
ErrOpenImaFile:
ErrOpenFile:	print offset ErrOpenFileTxt
                ecrirecar 34
                print dword ptr Args_table
                ecrirecar 8
                ecrirecar 34
                ecrirecar "."
                printcr
		jmp _leave


		;-----------------------------------------------------
                ; I know cut n paste is no good, but you'd rather
                ; type it all again?. No way, I'm not inventing
                ; the IMC1 stupid algo again. Nah!

align 4
SizeImc1	dd 0
TImaLen		db 0
TImaHei		db 0

LoadIMC1:

                ; Read ImaHeader into low memory
                mov edx, offset ImaHeader	; dest buffer
                mov ecx, 2			; lenght
                call _readfile
                jc ErrOpenImaFile

		mov al, byte ptr ImaHeader
                mov byte ptr TImaLen, al
		mov al, byte ptr ImaHeader +1
                mov byte ptr TImaHei, al

		; Get size of IMC1
                mov edx, offset SizeImc1
                mov ecx,4
                call _readfile
                jc ErrOpenImaFile

                ;printd SizeImc1
                ;printcr
                ;debugbreak offset _pressakey
                ;jmp CloseLoadIma

                ; Read IMC1 into memory
                mov edx, _himembase
                mov ecx, SizeIMC1
                call _readfile
                jc ErrOpenImaFile

                mov edi, _lomembase
                ;add edi, 3*256*1024
                mov esi, _himembase

                mov edx, 0
                .while edx <= SizeImc1
                   mov al, [esi]
                   .if al==0ffh
		     mov al, [esi+1]
                     mov cl, [esi+2]
                     mov ch, [esi+3]
                     add esi,4

LI0001:
                     mov [edi],al
                     inc edi
                     dec cx
                     or cx,cx
                     jne LI0001

                     add edx,4

                   .else
                     mov [edi],al
                     inc edi
                     inc edx
                     inc esi

                   .endif
                .endw

             	jmp CloseImaFile

;------------------------------------------------------------

ClearBuffer:
		mov ecx,1024*256/4
                mov edi, _HimemBase
                xor eax,eax
C0001:
                mov [edi],eax
                add edi,4
                dec ecx
                cmp ecx,0
                jne C0001

      		ret








;------------------------------------------------------------
align 4
Hei		dw 0
Len		dw 0
TLen		dw 0

DrawIma2Buffer:
                xor ax,ax
		mov al, byte ptr ImaHeader
                mov TLen, ax
                mov Len,ax
                mov al,byte ptr ImaHeader+1
                mov Hei,ax

                mov esi, _lomembase
                mov edi, _himembase
                add edi, 640*8+(640-512)/2
DI2B003:
		push edi
                mov ax, TLen
                mov Len,ax

DI2B002:
                push edi
                mov cx,8
DI2B001:
                mov eax, [esi]
                mov [edi],eax
                mov eax, [esi+4]
                mov [edi+4],eax
                add esi,8
                add edi,640
                loop DI2B001

                pop edi
                add edi,8
                dec Len
                cmp Len,0
                jne DI2B002

                pop edi
		add edi,640*8
                dec Hei
                cmp hei,0
                jne DI2B003
		ret

;--------------------------------------------------------------------
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



;####################################################################
  module_start ENDP
;####################################################################

 include \masm61\listing\graph.inc

;####################################################################
code32  ends            ; fin du module
	end             ; fin du fichier...
;####################################################################

