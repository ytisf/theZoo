
.code

;; ==================================================================================================== ;;
;; dwtoa - convert dword value into string                                                              ;;
;; __in dwValue  - value to convert                                                                     ;;
;; __in lpBuffer - pointer to buffer                                                                    ;;
;; Return: eax - pointer to end of buff                                                                 ;;
;; ==================================================================================================== ;;
dwtoa proc uses ebx ecx edx edi dwValue, lpBuffer : dword

	mov  eax, dwValue
	mov  edi, lpBuffer
	xor  ecx, ecx
	mov  ebx, 10

@@:	xor  edx, edx
	div  ebx
	push edx
	inc  ecx
	test eax, eax
	jnz  @B

@@:	pop  eax
	add  eax, "0"
	stosb
	dec  ecx
	jnz  @B

	mov  eax, edi
	ret
dwtoa endp

