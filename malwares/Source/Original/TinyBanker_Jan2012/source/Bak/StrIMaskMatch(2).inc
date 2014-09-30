
.code

;; ==================================================================================================== ;;
;; StrIMaskMatch - compare string with mask                                                             ;;
;;                 - "#" - any 1 digit,                                                                 ;;
;;                 - "?" - any 1 symbol,                                                                ;;
;;                 - "*" - any group of symbols or no symbols at all                                    ;;
;; __in lpString    - pointer to string                                                                 ;;
;; __in nStringLen  - len of string                                                                     ;;
;; __in lpStrMask   - pointer to mask                                                                   ;;
;; __in nStrMaskLen - len of mask                                                                       ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success                                                                                 ;;
;; ==================================================================================================== ;;
StrIMaskMatch proc uses ecx ebx edx esi edi lpString, nStringLen, lpStrMask, nStrMaskLen : dword

	;; Check strings len
	xor  eax, eax
	cmp  nStringLen, eax
	jle  @ret
	cmp  nStrMaskLen, eax
	jle  @ret


	;; Init string vars
	mov  esi, lpString
	mov  ebx, nStringLen
	add  ebx, esi
	dec  ebx			;; lpSrting last symbol ptr

	mov  edi, lpStrMask
	mov  ecx, nStrMaskLen
	add  ecx, edi
	dec  ecx			;; lpStrMask last symbol ptr

	xor  edx, edx		;; Group start ptr

	jmp  @F				;; Start compare


@next:
	cmp  ebx, esi
	je   @finish		;; If last symbol in lpSrting
	cmp  ecx, edi
	je   @finish		;; If last symbol in lpStrMask

	inc  esi
	inc  edi


	;; Compare
@@:	mov  al, [edi]		;; Symbol from mask


;; ================================================== ;;
	;; Any single symbol (just skip it)
	cmp  al, "?"
	je   @next


;; ================================================== ;;
	;; Any single digit or actual # symbol
	cmp  al, "#"
	jne  @F

	cmp  al, [esi]
	je   @next

	mov  al, [esi]

	cmp  al, "0"
	jb   @notmatch
	cmp  al, "9"
	ja   @notmatch

	jmp  @next


;; ================================================== ;;
	;; Any group of symbols
@@:	cmp  al, "*"
	jne  @F

	cmp  ecx, edi
	je   @ret		;; if end of lpStrMask

	mov  edx, edi	;; save start of group
	dec  esi
	jmp  @next


	;; Case insensitive symbol compare
@@:	cmp  al, [esi]
	je   @next

	cmp  al, "z"
	ja   @notmatch
	cmp  al, "a"
	jb   @cmpupper

	sub  al, 32
	cmp  al, [esi]
	je   @next
	jmp  @notmatch

@cmpupper:
	cmp  al, "Z"
	ja   @notmatch
	cmp  al, "A"
	jb   @notmatch

	add  al, 32
	cmp  al, [esi]
	je   @next


	;; Symbol not match, check if group state
@notmatch:
	test edx, edx
	jz   @finish

	add  esi, edx
	sub  esi, edi
	inc  esi

	mov  edi, edx
	jmp  @next


;; ================================================== ;;
	;; Finish
@finish:
	xor  eax, eax
	cmp  ebx, esi
	jne  @ret		;; if not end of lpSrting


	mov  al, "*"
@@:	cmp  ecx, edi
	je   @ret		;; if end of lpStrMask

	;; Last * in lpStrMask
	inc  edi
	cmp  al, [edi]
	je   @B
	xor  eax, eax


@ret:
	ret
StrIMaskMatch endp

