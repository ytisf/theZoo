
.code

;; ==================================================================================================== ;;
;; ApiAddrFromLib - restore WinAPI in given library by hash                                             ;;
;; __in lpDllBaseAddr - pointer to library base                                                         ;;
;; ==================================================================================================== ;;
ApiAddrFromCrc proc uses ecx edx edi esi lpDllBaseAddr : dword
	local  dwAddressOfFunctions    : dword
	local  dwAddressOfNameOrdinals : dword



	xor  eax, eax
	cmp  lpDllBaseAddr, eax
	je   @ret


	;; Begin
	mov  esi, lpDllBaseAddr
	assume esi : ptr IMAGE_DOS_HEADER
	add  esi, [esi].e_lfanew
	assume esi : ptr IMAGE_NT_HEADERS
	mov  esi, [esi].OptionalHeader.DataDirectory.VirtualAddress
	add  esi, lpDllBaseAddr
	assume esi : ptr IMAGE_EXPORT_DIRECTORY
	mov  ecx, [esi].NumberOfNames
	mov  eax, [esi].AddressOfFunctions
	mov  dwAddressOfFunctions, eax
	mov  eax, [esi].AddressOfNameOrdinals
	add  eax, lpDllBaseAddr
	mov  dwAddressOfNameOrdinals, eax
	mov  esi, [esi].AddressOfNames
	add  esi, lpDllBaseAddr
	assume esi : nothing


	;; Process API hashes table
@next_api_name:
	mov  edi, lpDllBaseAddr		;; edi points to the name of function
	add  edi, [esi]
	add  esi, 4


	;; Calc function name hash
	xor  edx, edx
@@:	mov  eax, 7
	mul  edx
	mov  edx, eax
	movzx eax, byte ptr [edi]
	add  edx, eax
	inc  edi
	cmp  byte ptr [edi], 0
	jnz  @B		;; if more symbols in api name


	;; Get offset to ordinal
	mov  eax, dwAddressOfNameOrdinals	;; AddressOfNameOrdinals
	add  dwAddressOfNameOrdinals, 2		;; Move to next ordinal word
	mov  edi, @_API_Hashes_table
	add  edi, ebx
	add  edi, 4


@check_next_hash:
	cmp  [edi], edx
	jne  @F


	;; Needed function found
	movzx eax, word ptr [eax]	;; Name ordinal
	shl  eax, 2					;; Multiply by 4
	add  eax, lpDllBaseAddr
	add  eax, dwAddressOfFunctions
	mov  eax, [eax]
	add  eax, lpDllBaseAddr
	mov  [edi-4], eax			;; Store API address


	;; Move to next API hash
@@:	add  edi, 8
	;; Check if last hash or last API
	cmp  dword ptr [edi], 0
	jnz  @check_next_hash


	;; Check if last API in Lib
	dec  ecx
	jnz  @next_api_name

@ret:
	ret
ApiAddrFromCrc endp



;; ==================================================================================================== ;;
;; CleanApiAddrTable - Clean WinAPI addresses table                                                     ;;
;; ==================================================================================================== ;;
CleanApiAddrTable proc uses edi

	mov  edi, @_API_Hashes_table
	add  edi, ebx
	xor  eax, eax

@clean_next:
	mov  [edi], eax
	add  edi, 8
	cmp  [edi+4], eax
	jnz  @clean_next

	ret
CleanApiAddrTable endp



;; ==================================================================================================== ;;
;; RestoreAPIs - restore WinAPI addresses                                                               ;;
;; ==================================================================================================== ;;
RestoreAPIs proc uses ecx edi esi

	invokx  &CleanApiAddrTable[ebx]


	;; Get "kernel32" base address
	assume fs : flat
	mov  esi, [fs:30h]		;; get a pointer to the PEB
	mov  esi, [esi+0Ch]
	mov  esi, [esi+1Ch]
@@:	mov  ecx, [esi+8h]
	mov  edi, [esi+20h]
	mov  esi, [esi]
	cmp  dword ptr [edi+0Ch], 0320033h	;; "32" in unicode
	jne  @B


	;; restore "kernel32" APIs
	invokx  &ApiAddrFromCrc[ebx], ecx


	invokx  _GetModuleHandleA[ebx], "ntdll"
	invokx  &ApiAddrFromCrc[ebx], eax


	invokx  _GetModuleHandleA[ebx], "ws2_32"
	invokx  &ApiAddrFromCrc[ebx], eax


	ret
RestoreAPIs endp

