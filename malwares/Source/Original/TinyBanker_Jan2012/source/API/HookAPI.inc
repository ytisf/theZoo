
.code

;; ==================================================================================================== ;;
;; HookAPI - procedure sets hook on given API address                                                   ;;
;;           replace original API start to push addr and retn to handler procedure                      ;;
;;           creates trampoline contained replaced code of original API and return to code after it     ;;
;;           changes given API pointer to address of trampoline (real API code start)                   ;;
;; __in    lpHandlerProc - pointer to handler procedure                                                 ;;
;; __inout plpAPI        - pointer to API pointer                                                       ;;
;; ==================================================================================================== ;;
HookAPI proc uses ecx edi esi lpHandlerProc, plpAPI : dword
	local  lpAPI : dword
	local  flOldProtect : dword



	mov  eax, plpAPI
	mov  eax, [eax]
	mov  lpAPI, eax


	;; Change API memory protection
	invokx  _VirtualProtect[ebx], lpAPI, 32, PAGE_READWRITE, &flOldProtect
	test eax, eax
	jz   @ret


	;; Allocate memory for trampoline
	invokx  _VirtualAlloc[ebx], 0, 32, MEM_COMMIT or MEM_RESERVE, PAGE_EXECUTE_READWRITE
	test eax, eax
	jz   @oldprotect
	mov  edi, eax


	;; Get size of code to copy
	xor  ecx, ecx
	mov  esi, lpAPI

@@:	mov  eax, ebx
	add  eax, c_Catchy
	call eax
	cmp  eax, -1
	je   @error

	add  esi, eax		;; esi = current code instruction
	add  ecx, eax		;; eax = current instructions len
	cmp  ecx, 5
	jb   @B


	;; Copy original api code to new place
	mov  eax, edi	;; save
	sub  esi, ecx	;; pointer to current API start
	rep  movsb


	;; Write return to original API code + len of copied code
	mov  byte ptr [edi], 68h		;; PUSH offset original API + offsed of copied code
	mov  dword ptr [edi+1], esi		;; addr
	mov  byte ptr [edi+5], 0C3h		;; RETN


	;; New real API address
	mov  edi, plpAPI
	mov  [edi], eax


	;; Edit original API code start
	mov  edi, lpAPI
	mov  eax, lpHandlerProc
	mov  byte ptr [edi], 0E9h		;; JMP FAR
	sub  eax, edi					;;
	sub  eax, 5						;;
	mov  dword ptr [edi+1], eax		;; addr


	jmp  @oldprotect


@error:
	;; Release trampoline memory
	invokx  _VirtualFree[ebx], edi, 0, MEM_RELEASE


@oldprotect:
	;; Restore old API memory protection
	invokx  _VirtualProtect[ebx], lpAPI, 32, flOldProtect, &flOldProtect


@ret:
	ret
HookAPI endp

