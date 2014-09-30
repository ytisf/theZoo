
.code

;; ==================================================================================================== ;;
;; Crypt                                                                                                ;;
;; ==================================================================================================== ;;
Crypt1 proc lpData, dwLen : dword
	local  dwlpKeyTable : dword



	invokx  _VirtualAlloc[ebx], 0, 256, MEM_COMMIT or MEM_RESERVE, PAGE_READWRITE
	mov  dwlpKeyTable, eax

	invokx  &RC4SetKey[ebx], dwlpKeyTable, &sPassword[ebx], sizeof sPassword
	invokx  &RC4Crypt[ebx],  dwlpKeyTable, lpData, dwLen

	invokx  _VirtualFree[ebx], dwlpKeyTable, 0, MEM_RELEASE

	ret
Crypt1 endp

