; ****************************************************************
;
; 	Assembly modules runtime librairy: 95SSV21A.ASM
;
; 		Copyright 1995 FRANCOIS BLANCHETTE
;
; ****************************************************************


.model c, large
.386
include Global.inc


CODE SEGMENT 'CODE'
;---------------------------------------------------------------------------
ss_scrollrg	PROTO C ScrTable: FAR PTR BYTE, ImsTable: FAR PTR BYTE, FowTable: FAR PTR, Font: PTR FAR PTR BYTE, SCREEN: WORD, MX: WORD, MY: WORD, LEN: WORD, HEI: WORD, ScrSize:WORD
ss_scrollrg	PROC C, ScrTable: FAR PTR BYTE, ImsTable: FAR PTR BYTE, FowTable: FAR PTR, Font: PTR FAR PTR BYTE, SCREEN: WORD, MX: WORD, MY: WORD, LEN: WORD, HEI: WORD, ScrSize:WORD

		pushall
		;set ds,DATA
		set gs,SCREEN

                nul dh
		mov dl,byte ptr Hei
                shl dx,3
		mov bx,0

_2:		mov cx,(0140h-8)/4

_1:
		mov eax,gs:[bx+8]
		mov gs:[bx],eax
		add bx,4

		loop _1

                add bx,8

		mov cx,dx
		dec dx
		loop _2

		;push word ptr ScrLen
                ;push word ptr MX

                nul ah
                mov al,byte ptr Len
                dec al
                dec al
                ;shl ax,3
                ;shr ax,4
                shr ax,1
                add ax,SCREEN
                set gs,ax

		mov al, byte ptr MX
                add al,byte ptr Len
                dec al
                mov byte ptr MX,al

                mov byte ptr Len, 2


                ;xor eax,01010101h
                xor eax,eax
                mov di,0

                mov cl,byte ptr Hei
                nul ch
                shl cx,3
_3:
                mov gs:[di+8],eax
                mov gs:[di+4+8],eax
                add di,140h
                loop _3

                invoke DrawScript, ScrTable, Imstable, Font, mx, my, gs, 2, hei, -1, ScrSize

                popall
                ret

ss_scrollrg	ENDP
;-----------------------------------------------------------------------
ss_scrolllf	PROTO C ScrTable: FAR PTR BYTE, ImsTable: FAR PTR BYTE, FowTable: FAR PTR, Font: PTR FAR PTR BYTE, SCREEN: WORD, MX: WORD, MY: WORD, LEN: WORD, HEI: WORD, ScrSize:WORD
ss_scrolllf	PROC C, ScrTable: FAR PTR BYTE, ImsTable: FAR PTR BYTE, FowTable: FAR PTR, Font: PTR FAR PTR BYTE, SCREEN: WORD, MX: WORD, MY: WORD, LEN: WORD, HEI: WORD, ScrSize:WORD

		pushall
		;set ds,DATA
		set gs,SCREEN

                nul dh
		mov dl,byte ptr Hei
                shl dx,3
                mov si,0

_2:		mov cx,39
		mov bx,38*8

_1:
		mov eax,gs:[si+bx]
		mov gs:[si+bx+8],eax
		mov eax,gs:[si+bx+4]
		mov gs:[si+bx+8+4],eax
		sub bx,8

		loop _1

                add si,140h

		mov cx,dx
		dec dx
		loop _2

                ;nul ah
                ;mov al,byte ptr ScrLen
                ;dec al
                ;dec al
                ;shl ax,3
                ;shr ax,4
                ;shr ax,1
                ;add ax,SCREEN
                ;set gs,ax

                set gs,SCREEN

		;mov al, byte ptr MX
                ;add al,byte ptr ScrLen
                ;dec al
                ;mov byte ptr MX,al

                dec byte ptr MX
                mov byte ptr Len, 1

                ;xor eax,01010101h
                xor eax,eax
                mov di,0

                mov cl,byte ptr Hei
                nul ch
                shl cx,3
_3:
                mov gs:[di],eax
                mov gs:[di+4],eax
                add di,140h
                loop _3

                invoke DrawScript, ScrTable, Imstable, Font, mx, my, gs, 1, hei, -1, ScrSize


                ;pop word ptr MX
                ;pop word ptr ScrLen

                popall
                ret

ss_scrolllf	ENDP

;-----------------------------------------------------------------------
ss_scrolldn PROTO C ScrTable: FAR PTR BYTE, ImsTable: FAR PTR BYTE, FowTable: FAR PTR, Font: PTR FAR PTR BYTE, SCREEN: WORD, MX: WORD, MY: WORD, LEN: WORD, HEI: WORD, ScrSize:WORD
ss_scrolldn PROC C, ScrTable: FAR PTR BYTE, ImsTable: FAR PTR BYTE, FowTable: FAR PTR, Font: PTR FAR PTR BYTE, SCREEN: WORD, MX: WORD, MY: WORD, LEN: WORD, HEI: WORD, ScrSize:WORD

		pushall

		set gs,SCREEN

                nul dh
		mov dl,byte ptr Hei
		mov si,0a00h
		mov bx,0

_2:		mov cx,0a00h/4

_1:
		mov eax,gs:[si+bx]
		mov gs:[bx],eax
		add bx,4

		loop _1

		mov cx,dx
		dec dx
		loop _2

		mov al, byte ptr MY
                add al,byte ptr Hei
                mov byte ptr MY,al
                ;dec byte ptr MY

                ;dec byte ptr MY

                ;set gs,SCREEN2
                mov al,byte ptr Hei
                dec al
                mov ah,0ah
                mul ah
                shl ax,8-4
                ;shr ax,4
                add ax,SCREEN
                set gs,ax

                mov cx,0a00h/4
                mov eax,0
                mov di,0

_3:             mov gs:[di],eax
                add di,4
                loop _3

                ;fillmem gs,0,0a00h,3

                mov byte ptr Hei,1


                invoke DrawScript, ScrTable, Imstable, Font, mx, my, gs, len, 1, -1, ScrSize

                ;CopySeg SCREEN,SCREEN

		popall
		ret
ss_scrolldn	ENDP

;-------------------------------------------------------------------------
ss_scrollup PROTO C ScrTable: FAR PTR BYTE, ImsTable: FAR PTR BYTE, FowTable: FAR PTR, Font: PTR FAR PTR BYTE, SCREEN: WORD, MX: WORD, MY: WORD, LEN: WORD, HEI: WORD, ScrSize:WORD
ss_scrollup  PROC C, ScrTable: FAR PTR BYTE, ImsTable: FAR PTR BYTE, FowTable: FAR PTR, Font: PTR FAR PTR BYTE, SCREEN: WORD, MX: WORD, MY: WORD, LEN: WORD, HEI: WORD, ScrSize:WORD

		pushall

		set gs,SCREEN

                nul dh
		mov dl,byte ptr Hei
		mov si,0a00h
		mov bx,0

                mov al,byte ptr Hei
                dec al
                mov ah,0ah
                mul ah
                shl ax,8
		mov bx,ax


_2:		mov cx,0a00h/4

_1:
		mov eax,gs:[bx-0a00h]
		mov gs:[bx],eax
		add bx,4

		loop _1

                sub bx,0a00h*2

		mov cx,dx
		dec dx
		loop _2


                ;push word ptr Len
                ;push word ptr MY

		dec byte ptr MY
                mov byte ptr Hei,1

                set gs,SCREEN

                mov cx,0a00h/4
                ;xor eax,1010101h
                mov eax,0
                mov di,0

_3:             mov gs:[di],eax
                add di,4
                loop _3

                ;fillmem gs,0,0a00h,3

                invoke DrawScript, ScrTable, Imstable, Font, mx, my, gs, len, 1, -1, ScrSize

                ;CopySeg SCREEN,SCREEN2

		popall
		ret

ss_scrollup	ENDP

;-------------------------------------------------------------------------------


CODE ENDS
END