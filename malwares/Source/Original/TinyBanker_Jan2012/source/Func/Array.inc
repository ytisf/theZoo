
.code

;; ==================================================================================================== ;;
;; ArrayKeyPos - returns cell ptr of given key                                                          ;;
;; __in lpArray - pointer to array                                                                      ;;
;; __in dwKey   - given key                                                                             ;;
;; Return:  0 - not found                                                                               ;;
;;         !0 - found, cell ptr of given key                                                            ;;
;; ==================================================================================================== ;;
ArrayKeyPos proc uses ecx edx lpArray, dwKey : dword

	mov  eax, lpArray	;; eax - pointer to memory of array
	mov  ecx, ARRAYLEN	;; ecx - number of array cells
	mov  edx, dwKey		;; edx - needed handle

	;; Search current key in array
@@:	cmp  [eax], edx
	je   @ret		;; key found
	add  eax, 8		;; next cell
	dec  ecx
	jnz  @B

	xor  eax, eax

@ret:
	ret
ArrayKeyPos endp



;; ==================================================================================================== ;;
;; ArrayKeyBuff - add key and related memory buffer into array and returns its cell ptr                 ;;
;;                if key already exists then returns its cell ptr                                       ;;
;; __in lpArray - pointer to array                                                                      ;;
;; __in dwKey   - given parameter                                                                       ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success, cell ptr of given key                                                          ;;
;; ==================================================================================================== ;;
ArrayKeyBuff proc uses ecx edi lpArray, dwKey : dword

	invokx  &ArrayKeyPos[ebx], lpArray, dwKey
	jmpnz eax, @ret		;; key already exist

	invokx  &ArrayKeyPos[ebx], lpArray, 0
	jmpz eax, @ret		;; free cell not found
	mov  edi, eax		;; store cell ptr

	invokx  _VirtualAlloc[ebx], 0, BUFFERLEN, MEM_COMMIT or MEM_RESERVE, PAGE_READWRITE
	jmpz eax, @ret		;; failed to alloc memory

	mov  ecx, dwKey
	mov  [edi], ecx		;; save key
	mov  [edi+4], eax	;; save value

	mov  eax, edi		;; restore cell ptr

@ret:
	ret
ArrayKeyBuff endp



;; ==================================================================================================== ;;
;; ArrayKeyDel - delete cell with given key and related memory buffer                                   ;;
;; __in lpArray - pointer to array                                                                      ;;
;; __in dwKey   - given handle key                                                                      ;;
;; ==================================================================================================== ;;
ArrayKeyDel proc uses ecx edx lpArray, dwKey : dword

	invokx  &ArrayKeyPos[ebx], lpArray, dwKey
	jmpz eax, @ret		;; key not found

	mov  edx, [eax+4]	;; store cell value

	xor  ecx, ecx
	mov  [eax+4], ecx	;; del value
	mov  [eax], ecx		;; del key

	jmpz edx, @ret		;; cell value is not memory ptr

	invokx  _VirtualFree[ebx], edx, 0, MEM_RELEASE

@ret:
	ret
ArrayKeyDel endp

