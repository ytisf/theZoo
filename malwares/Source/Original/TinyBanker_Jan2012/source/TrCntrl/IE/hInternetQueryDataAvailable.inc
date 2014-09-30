
.code

;; ==================================================================================================== ;;
;; hInternetQueryDataAvailable is a InternetQueryDataAvailable handler procedure                        ;;
;; ==================================================================================================== ;;
hInternetQueryDataAvailable proc uses ebx ecx p1, p2, p3, p4 : dword

	GetBaseDelta ebx


	invokx  &ArrayKeyPos[ebx], lpReadBuffersArray[ebx], p1
	jmpz eax, @real

	mov  eax, [eax+4]	;; ptr to data buff with its len in 1st dword
	mov  ecx, [eax]		;; data len
	mov  eax, p2		;; ptr to lpdwNumberOfBytesAvailable
	mov  [eax], ecx		;; return data len to caller proc
	xor  eax, eax
	inc  eax
	jmp  @ret


@real:
	invokx  _InternetQueryDataAvailable[ebx], p1, p2, p3, p4

@ret:
	ret
hInternetQueryDataAvailable endp

