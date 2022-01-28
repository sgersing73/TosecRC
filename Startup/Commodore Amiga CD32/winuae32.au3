#include <Array.au3>
#include <File.au3>
#include <WinAPIShPath.au3>

Const $EMULATOR = 'T:\Emus\Commodore Amiga CD32\winuae-v3.2.2\winuae.exe'

; Uebergabeparameter in ein Array umwandeln
Local $aCmdLine = _WinAPI_CommandLineToArgv($CmdLineRaw)
Local $bootimage = _GetParaValues($aCmdLine, "/b:")

Dim $szDrive, $szDir, $szFName, $szExt
_PathSplit($bootimage, $szDrive, $szDir, $szFName, $szExt)



ShellExecute ($EMULATOR, "-s quickstart=cd32,1 -s use_gui=no -s win32.active_priority=1 -s cdimage0=" &  _ReplaceSpaceInFileName($bootimage) )

;===============================================================================
; 
;===============================================================================
Func _ReplaceSpaceInFileName($filename)

  If StringInStr ( $filename, " " ) Then

    FileMove ( $filename, StringReplace ( $filename, " ", "_") )
    $filename = StringReplace ( $filename, " ", "_")

  EndIf

  Return $filename;

EndFunc

;===============================================================================
; 
;===============================================================================
Func _GetParaValues($aArray, $sParam)

  Local $sValue = ""

  For $element IN $aArray
    If StringInStr ( $element, $sParam ) Then
      $sValue =   StringMid ( $element, 4 )
    EndIf
  Next   

  Return $sValue;

EndFunc