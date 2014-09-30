
.code

;; ==================================================================================================== ;;
;; InitArr -                                                                                            ;;
;; ==================================================================================================== ;;
InitArr proc

	invokx  _VirtualAlloc[ebx], 0, ARRAYLEN*8, MEM_COMMIT or MEM_RESERVE, PAGE_READWRITE 
	mov  lpSendBuffersArray[ebx], eax


	invokx  _VirtualAlloc[ebx], 0, ARRAYLEN*8, MEM_COMMIT or MEM_RESERVE, PAGE_READWRITE
	mov  lpReadBuffersArray[ebx], eax


	invokx  _VirtualAlloc[ebx], 0, ARRAYLEN*8, MEM_COMMIT or MEM_RESERVE, PAGE_READWRITE
	mov  lpSockHandlesArray[ebx], eax

	ret
InitArr endp

	lpSockHandlesArray dd 0
	lpSendBuffersArray dd 0
	lpReadBuffersArray dd 0
