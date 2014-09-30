
.code

;; ==================================================================================================== ;;
;; FileRead - read data from file and returns memory pointer                                            ;;
;; __in lpszFileName - pointer to filename                                                              ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success                                                                                 ;;
;;              eax - pointer to memory with file data with its len in first dword                      ;;
;; ==================================================================================================== ;;
FileRead proc uses edi esi lpszFileName : dword
	local  hFile       : dword
	local  lpMemBuffer : dword
	local  dwBytesRead : dword



	mov  lpMemBuffer, 0

	;; Open file lpszFileName
	invokx  _CreateFileA[ebx], lpszFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
	cmp  eax, INVALID_HANDLE_VALUE
	je   @ret

	mov  hFile, eax


	;; Get file size
	invokx  _GetFileSize[ebx], hFile, 0
	cmp  eax, INVALID_FILE_SIZE
	je   @closefile

	mov  esi, eax	;; FileSize


	;; Alloc memory for data
	add  eax, 4
	invokx  _VirtualAlloc[ebx], 0, eax, MEM_COMMIT or MEM_RESERVE, PAGE_READWRITE
	test eax, eax
	jz   @closefile

	;; Store file len in first dword
	mov  lpMemBuffer, eax
	mov  edi, eax
	mov  eax, esi
	stosd


	;; Read data in memory
	invokx  _ReadFile[ebx], hFile, edi, esi, &dwBytesRead, 0
	test eax, eax
	jnz  @closefile


	;; Free memory if ReadFile failed
	invokx  _VirtualFree[ebx], lpMemBuffer, 0, MEM_RELEASE
	mov  lpMemBuffer, 0


@closefile:
	invokx  _CloseHandle[ebx], hFile


@ret:
	mov  eax, lpMemBuffer
	ret
FileRead endp

