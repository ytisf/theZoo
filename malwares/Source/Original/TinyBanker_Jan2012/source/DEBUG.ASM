
.code

DbgInLog proc uses ecx lpText, dwSize : dword
	local   hFile       : dword
	local   nWritten    : dword


	invokx  _CreateFileA[ebx], 'c:\DEVELOP\DEBUG.TXT', GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
	mov  hFile, eax
	invokx  _SetFilePointer[ebx], hFile, 0, 0, FILE_END
	invokx  _WriteFile[ebx], hFile, lpText, dwSize, &nWritten, 0
	invokx  _CloseHandle[ebx], hFile

	ret
DbgInLog endp


BUFF db "        "
Debug proc lpszStr, dwValue, lpMemory : dword

	invokx  _lstrlenA[ebx], lpszStr
	test eax, eax
	jz   @F
	invokx  &DbgInLog[ebx], lpszStr, eax
@@:	invokx  &DbgInLog[ebx], "\r\nCODE: ", 8


	lea  eax, BUFF[ebx]
	mov  dword ptr[eax], "    "
	mov  dword ptr[eax+4], "    "
	invokx  &dwtoh[ebx], dwValue, &BUFF[ebx]
	invokx  &DbgInLog[ebx], &BUFF[ebx], 8


	invokx  &DbgInLog[ebx], "\r\n\r\n", 4
	mov  eax, lpMemory
	test eax, eax
	jz   @F
	mov  edi, eax
	mov  ecx, [edi]		;; ecx - len of all grabbed data
	add  edi, 4			;; eax - pointer to all grabbed data

	lea  eax, BUFF[ebx]
	mov  dword ptr[eax], "    "
	mov  dword ptr[eax+4], "    "
	invokx  &dwtoa[ebx], ecx, &BUFF[ebx]
	invokx  &DbgInLog[ebx], &BUFF[ebx], 8
	invokx  &DbgInLog[ebx], "\r\n", 2

	invokx  &DbgInLog[ebx], edi, ecx


@@:	invokx  &DbgInLog[ebx], "\r\n\r\n==================================================\r\n\r\n", 58


	ret
Debug endp

