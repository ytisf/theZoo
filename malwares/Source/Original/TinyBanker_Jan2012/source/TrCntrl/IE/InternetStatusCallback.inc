
.code

;; ==================================================================================================== ;;
;; StatusCallback is a IE StatusCallback handler procedure                                              ;;
;; When status is INTERNET_STATUS_REQUEST_COMPLETE                                                      ;;
;; search current handle in status wait array and delete it                                             ;;
;; ==================================================================================================== ;;
InternetStatusCallback proc uses ebx hInternet, dwContext, dwInternetStatus, lpvStatusInformation, dwStatusInformationLength : dword

	GetBaseDelta ebx

	cmp  dwInternetStatus, INTERNET_STATUS_REQUEST_COMPLETE
	jne  @real


	invokx  &ArrayKeyDel[ebx], lpSockHandlesArray[ebx], hInternet
	jmp  @ret


@real:
	invokx  lpRealCallbackProc[ebx], hInternet, dwContext, dwInternetStatus, lpvStatusInformation, dwStatusInformationLength

@ret:
	ret
InternetStatusCallback endp



;; ==================================================================================================== ;;
;; Pending -                                                                                            ;;
;;                                                                                                      ;;
;; ==================================================================================================== ;;
Pending proc uses ecx hInternet

	mov  ecx, hInternet

	invokx  &ArrayKeyPos[ebx], lpSockHandlesArray[ebx], ecx
	jmpz eax, @end


@@:	nop
	cmp  [eax], ecx
	je   @B


@end:
	invokx  &ArrayKeyPos[ebx], lpSockHandlesArray[ebx], 0
	mov  [eax], ecx

	ret
Pending endp

	lpRealCallbackProc dd 0

