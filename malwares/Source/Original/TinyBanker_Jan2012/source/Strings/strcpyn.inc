
.code

;; ==================================================================================================== ;;
;; strcpyn -                                                                                            ;;
;; __in lpDestString -                                                                                  ;;
;; __in lpSrcString  -                                                                                  ;;
;; __in nLength      -                                                                                  ;;
;; Return: eax -                                                                                        ;;
;; ==================================================================================================== ;;
strcpyn proc uses ecx edi esi lpDestString, lpSrcString, nLength : dword

	mov  edi, lpDestString
	mov  esi, lpSrcString
	mov  ecx, nLength

	cmp  edi, esi
	jbe  @F		;; if dest below source
	lea  eax, [esi+ecx]
	cmp  eax, edi
	jbe  @F		;; if last source below dest
	add  edi, ecx
	add  esi, ecx
	inc  ecx
	std
@@:	rep  movsb
	cld

	mov  eax, edi
	ret
strcpyn endp

