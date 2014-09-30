
.code

;; ==================================================================================================== ;;
;; atodw - convert decimal string into dword value                                                      ;;
;; __in lpString - pointer to string                                                                    ;;
;; Return: eax - dword value                                                                            ;;
;;         ecx -                                                                                        ;;
;; ==================================================================================================== ;;
atodw proc uses edx lpString : dword

	xor  eax, eax
	xor  edx, edx
	mov  ecx, lpString


@@:	mov  dl, [ecx]
	cmp  dl, "0"
	jb   @ret
	cmp  dl, "9"
	ja   @ret
	inc  ecx

	sub  dl, "0"
	lea  eax, [eax+4*eax]
	lea  eax, [edx+2*eax]
	jmp  @B


@ret:
	ret
atodw endp

