
.code

;; ==================================================================================================== ;;
;; CheckEOF - check if there is end of file already                                                     ;;
;; __in lpData - data ptr with its len in first dword                                                   ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success                                                                                 ;;
;; ==================================================================================================== ;;
CheckEOF proc uses ecx edi esi lpData : dword

	mov  esi, lpData
	mov  ecx, [esi]		;; data len
	add  esi, 4			;; data begin ptr
	lea  edi, [ecx+esi]	;; data end ptr


;; ================================================== ;;
	invokx  &StrIPos[ebx], esi, ecx, "\r\nContent-Length: ", 18
	jmpz eax, @chunked


	add  eax, 18
	invokx  &atodw[ebx], eax
	mov  ecx, eax	;; content len


	mov  eax, edi
	sub  eax, esi
	invokx  &StrIPos[ebx], esi, eax, "\r\n\r\n", 4
	jmpz eax, @ret


	lea  eax, [eax+ecx+4]
	cmp  eax, edi
	je   @ret		;; end


	xor  eax, eax
	jmp  @ret		;; not end


;; ================================================== ;;
@chunked:
	invokx  &StrIPos[ebx], esi, ecx, "\r\nTransfer-Encoding:", 20
	jmpz eax, @nolen


	sub  edi, 7
	invokx  &StrIPos[ebx], edi, 7, "\r\n0\r\n\r\n", 7


	jmp  @ret


;; ================================================== ;;
@nolen:
	cmp  dword ptr [edi-4], 0A0D0A0Dh
	jne  @ret

	inc  eax


@ret:
	ret
CheckEOF endp

