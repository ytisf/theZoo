
.code

;; ==================================================================================================== ;;
;;                                                                                                      ;;
;; ==================================================================================================== ;;

	;; Constants
	ARRAYLEN  equ 1024
	KBYTE     equ 1024
	MBYTE     equ 1024*KBYTE
	BUFFERLEN equ 2*MBYTE
	RESERVE   equ 128*KBYTE



	HTTP_REQUEST   equ 1
	HTTPS_REQUEST  equ 2
	INJECT_GRABBED equ 3

