#include <WinAPIShPath.au3>
#include <Array.au3>
#include <File.au3>

Const $EMULATOR = 'T:\Emus\RCA Chip-8\Vision8-Windows\VISION8.EXE'

Local $aCmdLine = _WinAPI_CommandLineToArgv($CmdLineRaw)
Local $bootimage = _GetParaValues($aCmdLine, "/b:")
Local $swapimage = _GetParaValues($aCmdLine, "/d:")

Dim $szDrive, $szDir, $szFName, $szExt
_PathSplit($bootimage, $szDrive, $szDir, $szFName, $szExt)

ShellExecute ($EMULATOR, '"' & $bootimage & '"' )

exit

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
