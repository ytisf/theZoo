
.code

;; ==================================================================================================== ;;
;; ltrim - strip whitespace from the beginning of a string                                              ;;
;; __in lpString    - pointer to string                                                                 ;;
;; __in nStringLen  - len of string                                                                     ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success, pointer to ltrimed string                                                      ;;
;;              ecx - len of ltrimed string                                                             ;;
;; ==================================================================================================== ;;
ltrim proc uses edx lpString, nStringLen : dword

	;; Check strings len
	xor  eax, eax
	cmp  nStringLen, eax
	jle  @ret


	mov  eax, lpString
	mov  ecx, nStringLen
	jmp  @F


@nextchar:
	inc  eax
	dec  ecx
	jz   @ret


@@:	mov  dl, [eax]

	cmp  dl, 32		; " " (ASCII 32 (0x20)), an ordinary space. 
	je   @nextchar
	cmp  dl, 9		; "\t" (ASCII 9 (0x09)), a tab. 
	je   @nextchar
	cmp  dl, 10		; "\n" (ASCII 10 (0x0A)), a new line (line feed). 
	je   @nextchar
	cmp  dl, 13		; "\r" (ASCII 13 (0x0D)), a carriage return. 
	je   @nextchar
	cmp  dl, 0		; "\0" (ASCII 0 (0x00)), the NUL-byte. 
	je   @nextchar
	cmp  dl, 11		; "\x0B" (ASCII 11 (0x0B)), a vertical tab.
	je   @nextchar


@ret:
	ret
ltrim endp

