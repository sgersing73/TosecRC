#include <Array.au3>
#include <File.au3>
#include <WinAPIShPath.au3>

Const $EMULATOR = 'T:\Emus\Tangerine Oric-1 & Atmos\Oricutron-v12-x86\oricutron.exe'

FileChangeDir ( 'T:\Emus\Tangerine Oric-1 & Atmos\Oricutron-v12-x86' )

#include <ButtonConstants.au3>
#include <ComboConstants.au3>
#include <GUIConstantsEx.au3>
#include <WindowsConstants.au3>

#Region ### START Koda GUI section ### Form=t:\startup\tangerine oric-1 & oric atmos\koda\oricutron.kxf
$Form1_1 = GUICreate("Form1", 246, 165, 198, 123)
$Combo1 = GUICtrlCreateCombo("", 8, 8, 228, 25, BitOR($CBS_DROPDOWN,$CBS_AUTOHSCROLL))
GUICtrlSetData(-1, "atmos|oric1|o16k|telestrat|pravetz")
$Checkbox1 = GUICtrlCreateCheckbox("Fullscreen", 8, 40, 217, 17)
$Checkbox2 = GUICtrlCreateCheckbox("Window", 8, 64, 217, 17)
$Combo2 = GUICtrlCreateCombo("", 8, 88, 225, 25, BitOR($CBS_DROPDOWN,$CBS_AUTOHSCROLL))
GUICtrlSetData(-1, "soft|opengl")
$Button1 = GUICtrlCreateButton("Start", 64, 128, 113, 25)
GUISetState(@SW_SHOW)
#EndRegion ### END Koda GUI section ###

$aClientSize = WinGetClientSize($Form1_1)
WinMove($Form1_1, "", @DesktopWidth/2 - $aClientSize[0]/2, @DesktopHeight/2 - $aClientSize[1]/2)

While 1
    $nMsg = GUIGetMsg()
    Switch $nMsg
        Case $Button1
            START()
        Case $GUI_EVENT_CLOSE
            Exit
    EndSwitch
WEnd

Func Start()

  local $param

  FileChangeDir ( 'T:\Emus\Tangerine Oric-1 & Atmos\Oricutron-v12-x86' )

  ;msgbox (0,"",$CmdLineRaw)

  ; Uebergabeparameter in ein Array umwandeln
  Local $aCmdLine = _WinAPI_CommandLineToArgv($CmdLineRaw)
  Local $bootimage = _GetParaValues($aCmdLine, "/b:")

  Dim $szDrive, $szDir, $szFName, $szExt
  _PathSplit($bootimage, $szDrive, $szDir, $szFName, $szExt)

  If GUICtrlRead($Checkbox1) = $GUI_CHECKED Then
    $param = $param & " --fullscreen "
  EndIf

  If GUICtrlRead($Checkbox2) = $GUI_CHECKED Then
    $param = $param & " --window "
  EndIf

  $param = $param & " --machine " & GUICtrlRead($Combo1)
  $param = $param & " --rendermode " & GUICtrlRead($Combo2)

  If $szExt = ".dsk" Then
    ShellExecute ($EMULATOR, "-d " &  _ReplaceSpaceInFileName($bootimage) & $param)
  ElseIf $szExt = ".tap" Then
    ShellExecute ($EMULATOR, "-t " &  _ReplaceSpaceInFileName($bootimage) & $param)
  Else
    ShellExecute ($EMULATOR,  _ReplaceSpaceInFileName($bootimage) & $param)
  EndIF

  Exit

EndFunc  ;==>START

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
