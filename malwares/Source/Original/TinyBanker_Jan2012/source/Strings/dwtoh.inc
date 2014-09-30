
.code

;; ==================================================================================================== ;;
;; dwtoah - convert dword value into hex string                                                         ;;
;; __in dwValue  - value to convert                                                                     ;;
;; __in lpBuffer - pointer to buffer                                                                    ;;
;; Return: eax - pointer to end of buff                                                                 ;;
;; ==================================================================================================== ;;
dwtoh proc uses ecx edx edi dwValue, lpBuffer : dword

	mov  edi, lpBuffer
	mov  al, "0"
	stosb
	mov  edx, dwValue
	test edx, edx
	jz   @ret

	dec  edi
	mov  ecx, 9
@next:
	dec  ecx
	jz   @ret
	rol  edx, 4
	mov  al, dl
	and  al, 00001111b
	jnz  @F
	cmp  edi, lpBuffer
	je   @next
@@:	and  dl, 11110000b
	.if al < 0Ah
		add  al, 30h	; convert digits 0-9 to ascii
	.else
		add  al, 57h	; convert digits A-F to ascii
	.endif
	stosb
	jmp  @next

@ret:
	mov  eax, edi
	ret
dwtoh endp

