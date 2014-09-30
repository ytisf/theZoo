

;; ==================================================================================================== ;;
;; hInternetReadFileExA is a InternetReadFileExA handler procedure                                      ;;
;; ==================================================================================================== ;;
hInternetReadFileExA proc uses ebx edx p1, p2, p3, p4 : dword

	GetBaseDelta ebx

	invokx  _InternetReadFileExA[ebx], p1, p2, p3, p4

	mov  edx, p2
	assume edx : ptr INTERNET_BUFFERS
	DEBUG [edx].lpvBuffer, 0, 0
	assume edx : nothing

	ret
hInternetReadFileExA endp

