

;; ==================================================================================================== ;;
GetBaseDelta macro reg
	local  @delta

	call @delta
@delta:
	pop  reg
	sub  reg, @delta
endm


m2m macro arg1, arg2
	push arg2
	pop  arg1
endm


jmpz macro reg, lbl
	test reg, reg
	jz   lbl
endm

jmpnz macro reg, lbl
	test reg, reg
	jnz  lbl
endm

jmps macro reg, lbl
	test reg, reg
	js   lbl
endm

jmpns macro reg, lbl
	test reg, reg
	jns  lbl
endm

jmple macro reg, lbl
	test reg, reg
	jle  lbl
endm





;; ==================================================================================================== ;;
DEBUG macro arg1, arg2, arg3
	ifdef DEBUGMODE
	pushad
	GetBaseDelta ebx
	mov  esi, arg2
	invokx  _RtlGetLastWin32Error[ebx]
	mov  edi, eax
	invokx  &Debug[ebx], arg1, esi, arg3
	invokx  _RtlSetLastWin32Error[ebx], edi
	popad
	endif
endm


;; ==================================================================================================== ;;
NOPS macro
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
endm



;; ==================================================================================================== ;;
;; Вызывается так:
;; vxinvoke ххх[ebx],var1[ebx],1,&var1[ebx],17
;; где ххх - переменная содержащая адрес вызываемой функции
;; [ebx] - дельта(или любой другой, или вообще без регистра)
;; var1[ebx] - В качестве параметра передаётся значение переменной var1
;; &var1[ebx] - В качестве параметра передаётся адрес переменной var1
;; 
;; 
;; 
;; 
;; небольшое обновление
;; Теперрь можно делать так:
;; vxinvoke ххх[ebx],'some text',"other text",1,&var1[ebx],17
;; 
;; код сгенерируется такой:
;; call label1
;; db 'some text'
;; db 0
;; label1:
;; 
;; и теперь можно передавать параметр в еах в любом месте. Кобанды &var1[ebx]генерируют такой код:
;; push eax
;; lea eax,var1[ebx]
;; xchg [esp],eax
;; и следовательно не портят еах
;; 
;; 
;; 
;; 
;; vxinvoke &xxx[ebx] - vizov polzovatelskoi proceduri
;; 
;; 
;; ==================================================================================================== ;;
vxpush macro arg1, useeax
	local  label1, label2

	fSym substr <arg1>,1,1

	ifidn fSym,<&>
		var1 substr <arg1>,2
		if useeax eq 0
			lea  eax, var1
			push eax
		else
			push eax
			lea  eax, var1
			xchg eax, [esp]
		endif

	elseifidn fSym,<'>
		call label1
		db   arg1
		db   0
		label1:

	elseifidn fSym,<">
		call label2
		flag1 = 0
		forc char, <arg1>
			ifdif <char>, <">
				if flag1 eq 1
					flag1 = 0
					ifidn <char>,<r>
						db 13
					elseifidn <char>,<n>
						db 10
					else
						db "\"
						ifidn <char>,<\>
							flag1 = 1
						else
							db "&char"
						endif
					endif
				elseifidn <char>,<\>	;; trap the escape character and set the flag
					flag1 = 1
				else
					db "&char"
				endif
			endif
		endm
		if flag1 eq 1
			db "\"
		endif
		db   0
		label2:

	else
		push arg1
	endif
endm


invokx macro fName, arglist : vararg

	useeax = 0
	count = 0
	for arg, <arglist>
		count=count+1
		ifidn <arg>, <eax>
			useeax=useeax+1
		endif
	endm

	Len sizestr <fName>
	baseIn substr <fName>,Len-3,3
	ifidn baseIn, <eax>
		useeax=useeax+1
	endif


	while count
		index = 0
		for arg, <arglist>
			index=index+1
			if count eq index
				vxpush arg, useeax
				ifidn <arg>, <eax>
					useeax=useeax-1
				endif
			endif
		endm
		count=count-1
	endm


	firstSymb substr <fName>,1,1
;; User proc call
	ifidn firstSymb, <&>
		funcName substr <fName>,2,Len-1
		lea  eax, funcName
		call eax
;; Call proc addr in var
	else
		call fName
	endif

endm

