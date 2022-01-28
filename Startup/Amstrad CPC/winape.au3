#include <Array.au3>
#include <File.au3>
#include <WinAPIShPath.au3>

Const $APP_PATH = 'T:\Emus\Amstrad CPC\WinApe-v2.0b2\'

Const $EMULATOR = $APP_PATH & 'WinApe.exe'
Const $INI_FILE = $APP_PATH & 'WinApe.ini'

; Uebergabeparameter in ein Array umwandeln
Local $aCmdLine = _WinAPI_CommandLineToArgv($CmdLineRaw)
Local $bootimage = _GetParaValues($aCmdLine, "/b:")

;Clean any previous disk in drives
IniWrite($INI_FILE, "Drives", "Drive(0)", " ") ; Drive A Side A
IniWrite($INI_FILE, "Drives", "Drive(4)", " ") ; Drive A Side B
IniWrite($INI_FILE, "Drives", "Drive(1)", " ") ; Drive B Side A
IniWrite($INI_FILE, "Drives", "Drive(5)", " ") ; Drive B Side B

;Clean any previous cart
IniWrite($INI_FILE, "ROMS", "Cartridge", " ")

Dim $szDrive, $szDir, $szFName, $szExt
_PathSplit($bootimage, $szDrive, $szDir, $szFName, $szExt)

If $szExt = ".cpr" Then
  IniWrite($INI_FILE, "Configuration", "Enable Plus", "true")
  IniWrite($INI_FILE, "Configuration", "CRTC Type", "3")
  IniWrite($INI_FILE, "ROMS", "Cartridge Enabled", "true")
  IniWrite($INI_FILE, "ROMS", "Lower", " ")
  IniWrite($INI_FILE, "ROMS", "Upper(0)", " ")

  IniWrite($INI_FILE, "ROMS", "Cartridge", $bootimage)	
Else
  IniWrite($INI_FILE, "Configuration", "Enable Plus", "false")
  IniWrite($INI_FILE, "Configuration", "CRTC Type", "0")
  IniWrite($INI_FILE, "ROMS", "Cartridge Enabled", "false")
  IniWrite($INI_FILE, "ROMS", "Lower", "OS6128")
  IniWrite($INI_FILE, "ROMS", "Upper(0)", "BASIC1-1")

  IniWrite($INI_FILE, "Drives", "Drive(0)", $bootimage ) ; Drive A Side A
EndIf

ShellExecute ( $EMULATOR, "/A" )

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