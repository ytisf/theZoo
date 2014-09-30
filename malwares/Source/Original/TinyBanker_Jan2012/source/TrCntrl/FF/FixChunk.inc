
.code

;; ==================================================================================================== ;;
;; FixChunk - creates solid chunk from many chunks                                                      ;;
;; __in lpData - data ptr with its len in first dword                                                   ;;
;; ==================================================================================================== ;;
FixChunk proc lpData : dword

	pushad
	mov  esi, lpData
	lodsd				;; data len
	lea  edx, [eax+esi]	;; data end ptr


	invokx  &StrIPos[ebx], esi, eax, "\r\n\r\n", 4
	lea  ecx, [eax+4]	;; ptr to first chunk len


	sub  eax, esi		;; headers len
	invokx  &StrIPos[ebx], esi, eax, "\r\nTransfer-Encoding:", 20
	jmpz eax, @ret


	invokx  &htodw[ebx], ecx
	lea  edi, [ecx+2]	;; ptr to first chunk start


@nextchunk:
	lea  edi, [edi+eax+2]	;; ptr to next chunk len
	invokx  &htodw[ebx], edi
	jmpz eax, @F
	sub  edi, 2			;; \r\n
	lea  esi, [ecx+2]	;; ptr to next chunk start
	mov  ecx, edx
	sub  ecx, esi		;; len left
	mov  edx, edi		;; save ptr
	rep  movsb
	xchg edx, edi		;; restore ptr
	jmp  @nextchunk


@@:	mov  eax, lpData
	sub  edx, eax
	sub  edx, 4
	mov  [eax], edx		;; set new len


@ret:
	popad
	ret
FixChunk endp

