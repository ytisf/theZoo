
.code

;; ==================================================================================================== ;;
;; StrIPos - case insensitive search first entry of char in string                                      ;;
;; __in lpString    - pointer to string                                                                 ;;
;; __in nStringLen  - len of string                                                                     ;;
;; __in lpSubString - pointer to substring                                                              ;;
;; __in nSubStrLen  - len of substring                                                                  ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success, pointer to start of founded substring                                          ;;
;; ==================================================================================================== ;;
StrIPos proc uses ebx ecx edx edi esi lpString, nStringLen, lpSubString, nSubStrLen : dword

	;; Check strings len
	xor  eax, eax
	cmp  nStringLen, eax
	jle  @ret
	cmp  nSubStrLen, eax
	jle  @ret


	;; Init string vars
	mov  esi, lpString		;; esi = first symbol pointer
	dec  esi
	mov  ebx, nStringLen
	add  ebx, esi			;; ebx = last symbol pointer


@nextcycle:
	xor  eax, eax
	cmp  esi, ebx			;; check if last symbol in string
	je   @ret

	inc  esi				;; next symbol ptr search from
	mov  ecx, esi			;; copy symbol ptr search from, for use in compare

	mov  edi, lpSubString	;; init substring var
	mov  edx, nSubStrLen	;; init substring var


	;; Case insensitive symbol compare
@nextchar:
	mov  al, [ecx]
	cmp  al, [edi]
	je   @charmatch

	cmp  al, "z"
	ja   @nextcycle
	cmp  al, "a"
	jb   @cmpupper

	sub  al, 32
	cmp  al, [edi]
	je   @charmatch
	jmp  @nextcycle

@cmpupper:
	cmp  al, "Z"
	ja   @nextcycle
	cmp  al, "A"
	jb   @nextcycle

	add  al, 32
	cmp  al, [edi]
	jne  @nextcycle


@charmatch:
	inc  ecx				;; next symbol in string
	inc  edi				;; next symbol in substring
	dec  edx				;; substring len
	jnz  @nextchar


	;; Substring found
	mov  eax, esi


@ret:
	ret
StrIPos endp

