;**********************************************************************
; PMODE INCLUDED FILE
;**********************************************************************
; NAME       : _MAIN.INC
; DESCRIPTION: INTRODUCE TO PMODE PROGRAM
;
;**********************************************************************

;_main:

	; Read current Video mode;
	;mov v86r_ah, 0fh       ; mov ah, 0f
	;mov al,10h             ; int 10h
	;int 33h

	;.if byte ptr v86r_al!=3
	; if video mode is not text mode then
	; set video mode to text mode.
	   mov al,10h           ; int 10h
	   mov v86r_ah,0        ; ah = set VGA MODE
	   mov v86r_al,3        ; al = mode
	   int 33h
	;.endif

	; ------------------------------------------------------------------
	; SETUP PMODE ID SCREEN:
	; This is info STUFF.
	; About PMODE, XMS AND BASE MEMORY. Just remove it if you don't care
	; But remember to mention TRAN. Say how great he is.
	;

	;; Afficher PMODE par TRAN
	  print offset return
	  print offset return
	  print offset Tran1
	  print offset Tran2
	  print offset return
	  print offset return

	;; Afficher System Type:
	  print offset SystemType
	  movzx ecx,_sysbyte0
	  and cl,3
	  mov edx,systypestrtbl[ecx*4]
	  print <edx>
	  print offset return

	;; Aficher mainstr1
	  print offset mainstr1
	  call _lomemsize
	  printd <eax>
	  printcr

	;; Aficher mainstr2
	  print offset mainstr2
	  call _himemsize
	  printd <eax>
	  printcr
	  printcr
	  printcr

	;; Verify if LoMem is sufficient
	call _lomemsize
	.if eax<dword ptr MinLowMem
		printc offset ERR_LOW_MEM
		printcr
		print offset TXT_NEED
		printd dword ptr MinLowMem
		print offset __TXT_BYTES_LOW
		printcr
		call _press_a_key
		jmp _leave
	.endif

	;; Verify if HiMem is sufficent
	call _himemsize
	.if eax<dword ptr MinXMSMem
		printc  offset ERR_HI_MEM
		printcr
		print offset TXT_NEED
		printd dword ptr MinXmsMem
		print offset __TXT_BYTES_XMS
		printcr
		call _press_a_key
		jmp _leave
	.endif

	call _press_a_key

;_quiet:

	jmp module_start


_press_a_key:
	mov ah,8ch                      ; put key message
	mov bx,171bh; + BasePos
	mov edx,offset keystr
	call _putstr

	call _waitforkey                ; non-INT16 wait for keypress
	ret

;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�
; Put ASCIIZ string to screen
; In:
;   AH - attribute
;   BL - X
;   BH - Y
;   EDX -> ASCIIZ string
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�
_putstr:
	push ax
	push esi
	push edi

	movzx edi,bh
	imul edi,160
	movzx esi,bl
	shl esi,1
	lea edi,[edi+esi+0b8000h]
	sub edi,_code32a
	mov esi,edx
putstrl0:
	lodsb
	or al,al
	jz short putstrd
	stosw
	jmp putstrl0
putstrd:
	pop edi
	pop esi
	pop ax
	ret

;----------------------------------------------------------------------
_waitforkey PROC
	push ax
waitforkeyl0:
	mov ax,gs:[41ah]
	cmp ax,gs:[41ch]
	je waitforkeyl0
	mov gs:[41ch],ax
	pop ax
	ret
_waitforkey ENDP


