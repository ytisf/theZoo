
.code

;; ==================================================================================================== ;;
;; htodw - convert hex string into dword value                                                          ;;
;; __in lpString - pointer to string                                                                    ;;
;; Return: eax - dword value                                                                            ;;
;;         ecx - ptr to after                                                                           ;;
;; ==================================================================================================== ;;
htodw proc uses edx lpString : dword

	xor  eax, eax
	xor  edx, edx
	mov  ecx, lpString


@next:
	mov  dl, [ecx]

	cmp  dl, "0"
	jb   @ret
	cmp  dl, "9"
	jg   @F
	sub  dl, "0"
	jmp  @add

@@:	cmp  dl, "F"
	ja   @F
	cmp  dl, "A"
	jb   @ret
	sub  dl, "A"-10
	jmp  @add

@@:	cmp  dl, "f"
	ja   @ret
	cmp  dl, "a"
	jb   @ret
	sub  dl, "a"-10


@add:
	shl  eax, 4
	add  eax, edx
	inc  ecx
	jmp  @next


@ret:
	ret
htodw endp

