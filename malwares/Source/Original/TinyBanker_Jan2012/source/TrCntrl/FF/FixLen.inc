
.code

;; ==================================================================================================== ;;
;; FixLen - fixes len of contents                                                                       ;;
;; __in lpData - data ptr with its len in first dword                                                   ;;
;; ==================================================================================================== ;;
FixLen proc lpData : dword
	local  lpEnd : dword



	pushad
	mov  esi, lpData
	lodsd				;; data len
	lea  edi, [eax+esi]	;; data end ptr
	mov  lpEnd, edi


	invokx  &StrIPos[ebx], esi, eax, "\r\n\r\n", 4
	lea  edi, [eax+4]	;; content start


	mov  ecx, edi
	sub  ecx, esi		;; headers len

;; ================================================== ;;
	invokx  &StrIPos[ebx], esi, ecx, "\r\nContent-Length: ", 18
	jmpz eax, @chunked


	lea  esi, [eax+18]
	invokx  &StrIPos[ebx], esi, 12, "\r\n", 2
	jmpz eax, @ret


	;; shift data
	lea  edx, [eax+10]	;; new ptr
	mov  ecx, lpEnd
	sub  ecx, eax		;; data len to shift
	invokx  &strcpyn[ebx], edx, eax, ecx


	mov  eax, lpEnd
	sub  eax, edi		;; content len
	invokx  &dwtoa[ebx], eax, esi	;; put new len in data


	;; shift data back
	invokx  &strcpyn[ebx], eax, edx, ecx


	mov  esi, lpData
	sub  eax, esi
	sub  eax, 4
	mov  [esi], eax		;; new data len


	jmp  @ret


;; ================================================== ;;
@chunked:
	invokx  &StrIPos[ebx], esi, ecx, "\r\nTransfer-Encoding:", 20
	jmpz eax, @ret


	invokx  &StrIPos[ebx], edi, 10, "\r\n", 2
	jmpz eax, @ret


	mov  ecx, lpEnd
	sub  ecx, eax		;; "\r\n" + "content" + "\r\n0\r\n\r\n"


	;; shift data
	lea  edx, [eax+8]	;; new ptr
	invokx  &strcpyn[ebx], edx, eax, ecx


	sub  ecx, 9			;; content len
	invokx  &dwtoh[ebx], ecx, edi	;; new len in data


	;; shift data back
	add  ecx, 9			;; "\r\n" + "content" + "\r\n0\r\n\r\n"
	invokx  &strcpyn[ebx], eax, edx, ecx


	mov  esi, lpData
	sub  eax, esi
	sub  eax, 4
	mov  [esi], eax		;; new data len


@ret:
	popad
	ret
FixLen endp

