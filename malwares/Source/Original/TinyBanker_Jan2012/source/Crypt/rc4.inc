
.code

RC4SetKey proc lpKeyTable, lpPass, nPass : dword
	pushad

	mov  edi, lpKeyTable
	xor  ecx, ecx
@@:	mov  [edi + ecx], cl
	inc  ecx
	cmp  ecx, 256
	jne  @B

	mov  esi, lpPass
	xor  ebx, ebx
	xor  ecx, ecx
	xor  edx, edx
@@:	mov  al, [edi + ecx]
	add  bl, [esi + edx]
	add  bl, al
	mov  ah, [edi + ebx]
	mov  [edi + ecx], ah
	mov  [edi + ebx], al
	inc  ecx
	cmp  ecx, 256
	je   @F
	inc  edx
	cmp  edx, nPass
	jl   @B
	xor  edx, edx
	jmp  @B

@@:	popad
	ret
RC4SetKey endp



RC4Crypt proc lpKeyTable, lpData, nData : dword
	pushad

	mov  edi, lpKeyTable
	mov  esi, lpData
	xor  eax, eax
	xor  ebx, ebx
	xor  ecx, ecx
	xor  edx, edx
@@:	inc  bl
	mov  dl, [edi + ebx]
	add  al, dl
	mov  cl, [edi + eax]
	mov  [edi + ebx], cl
	mov  [edi + eax], dl
	add  cl, dl
	mov  cl, [edi + ecx]
	xor  [esi], cl
	inc  esi
	dec  nData
	jnz  @B

	popad
	ret
RC4Crypt endp

