' create_shortcut.vbs - Creates shortcut in the app for startup apps this is placed next to GameShell.exe
Option Explicit
Dim Shell, FSO, CurrentDir, TargetEXE, StartupPath, ShortcutFile, Link

Set Shell = CreateObject("WScript.Shell")
Set FSO = CreateObject("Scripting.FileSystemObject")

' Get the folder this script is inside
CurrentDir = FSO.GetParentFolderName(WScript.ScriptFullName)
TargetEXE = CurrentDir & "\GameShell.exe"

If Not FSO.FileExists(TargetEXE) Then
    WScript.Quit 1 ' Failure code
End If

StartupPath = Shell.SpecialFolders("Startup")
ShortcutFile = StartupPath & "\GameShell.lnk"

Set Link = Shell.CreateShortcut(ShortcutFile)
Link.TargetPath = TargetEXE
Link.WorkingDirectory = CurrentDir
Link.Description = "GameShell Console"
Link.IconLocation = TargetEXE & ",0"
Link.Save
