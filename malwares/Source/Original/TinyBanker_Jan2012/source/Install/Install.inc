
.code

;; ==================================================================================================== ;;
;; RegReadValue -                                                                                       ;;
;; ==================================================================================================== ;;
RegReadValue proc hKey, lpszRegPath, lpszValue, lpBuf, lpBufLen: DWORD
	local  hkHandle : dword
	local  DataType : dword


	invoke  RegOpenKeyEx, hKey, lpszRegPath, NULL, KEY_QUERY_VALUE, addr hkHandle
	jmpnz eax, @ret

	invoke  RegQueryValueEx, hkHandle, lpszValue, NULL, addr DataType, lpBuf, lpBufLen
	jmpnz eax, @ret

	invoke  RegCloseKey, hkHandle

@ret:
	ret
RegReadValue endp








;; ==================================================================================================== ;;
;; Install -                                                                                            ;;
;; ==================================================================================================== ;;
Install proc
	local  szRegDst[MAX_PATH] : byte
	local  szDst[MAX_PATH] : byte
	local  BufLen : dword



	invokx  lstrcpy, &szRegDst, "Software"
	invokx  lstrcat, &szRegDst, "\ABCDEFGH"
	invoke  MessageBox, 0, addr szRegDst, 0, MB_OK
	mov  BufLen, MAX_PATH
	invokx  &RegReadValue, HKEY_CURRENT_USER, &szRegDst, "Path", &szDst, &BufLen
	jmpnz eax, @F
	invoke  MessageBox, 0, addr szDst, 0, MB_OK
@@:

;	invoke  GetModuleFileName, 0, addr szDst, MAX_PATH
;	invoke  MessageBox, 0, addr szDst, 0, MB_OK


;	invokx  ExpandEnvironmentStrings, "%AppData%", &szDst, MAX_PATH
;	invokx  lstrcat, &szDst, "\ABCDEFGH"
;	invoke  CreateDirectory, addr szDst, 0
;	invoke  MessageBox, 0, addr szDst, 0, MB_OK
@ret:
	ret
Install endp












