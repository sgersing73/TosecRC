#include <Array.au3>
#include <File.au3>

Const $EMULATOR = 'T:\Emus\Enterprise 64 & 128\ep128emu-v2.0.9.1\ep128emu.exe'
 
;msgbox (0,"",$CmdLineRaw)

; Uebergabeparameter in ein Array umwandeln
Local $ResultArray = _ParseCMDLine($CmdLineRaw)
;_ArrayDisplay($ResultArray)

$bootimage =  _GetParaValues($ResultArray, "b");

Opt('SendKeyDelay', 250);
Opt('SendKeyDownDelay', 100);

Dim $szDrive, $szDir, $szFName, $szExt
_PathSplit($bootimage, $szDrive, $szDir, $szFName, $szExt)

Local $tmpImage = "boot" & $szExt
Local $tmpDir = "B:/"

FileMove($bootimage, $tmpDir & "boot" & $szExt)

Local $para = '-cfg "T:\\Emus\\Enterprise 64 & 128\\ep128emu-v2.0.9.1\\config\\gamebase_ep\\6_EP_128k_Tape_FileIO_TASMON__ISDOS_UK.cfg" memory.ram.size=128 fileio.workingDirectory=' & $tmpDir & " floppy.a.imageFile="

;ShellExecute ( $EMULATOR, "-cfg 'T:\\Emus\\Enterprise 64 & 128\\ep128emu-v2.0.9.1\\config6_EP_128k_Tape_FileIO_TASMON__ISDOS_UK.cfg' memory.ram.size=128 fileio.workingDirectory=" & $tmpDir & " floppy.a.imageFile="& $tmpDir & "boot" & $szExt )
ShellExecute ( $EMULATOR, $para )

Local $hWnd = WinWait("[CLASS:EPMainWindow]", "")

Sleep(4000)

ControlSend ($hWnd, "", "", "{ENTER}")

Sleep(7000)

ControlSend ($hWnd, "", "", 'load "' & $tmpImage & '"{ENTER}')
;ControlSend ($hWnd, "", "", 'load "A:"{ENTER}')



;===============================================================================
;
; Function Name:   _ParseCMDLine($CMDString)
; Description:     Parses a CMD-String to Parameters with Values
; Parameter(s):    $CMDString -> String to parse
; Requirement(s):  ?
; Return Value(s): Error: 0 and @error = StringRegExp-Error 
;                  Success: 2 Dimensional Array: 
;                      $array[$i][0] : Parameter including value
;                      $array[$i][1] : Parameter 
;                      $array[$i][2] : Value with quotation marks (only if value has quotaion marks)
;                      $array[$i][3] : Value without quotation marks
; Author(s):       Prog@ndy
;
; Basis: http://regexlib.com/REDetails.aspx?regexp_id=1220
;===============================================================================
;
Func _ParseCMDLine($CMDString)
	
  Local $y, $j, $i, $entry
  Local $x = StringRegExp($CMDString,'(?:\s*)(?<=[-|/])(?<name>[^\s-|/:|=]*)(?:(?:[:|=](?:("(?<value1>.*?)(?<!\\)")|(?<value>\S*)))|\w*?)',4)
	
  If @error Then Return SetError(@error,0,0)

  Local $ResultArray[UBound($x)][4]
  For $i = 0 To UBound($x)-1
    $entry = $x[$i]
    For $y = 0 To UBound($entry)-1
      $j = $y
      If $y > 3 Then $j = 3
        $ResultArray[$i][$j] = $entry[$y]
    Next
  Next
  
  Return $ResultArray

EndFunc

;===============================================================================
;
;===============================================================================
Func _GetParaValues($aArray, $sParam)

  Local $sValue = ""

	  ; Parameterarray nach dem ?bergabeparameter durchsuchen
  	Local $aResult=_ArrayFindAll($aArray, $sParam, Default, Default, Default, Default, 1)
  	;_ArrayDisplay($aResult)

  ; wurde der Parameter gefunden?
  If UBound( $aResult ) >= 0 Then

    For $element IN $aResult
	      $sValue =  $aArray[$element][3]
    Next   
		
  Else 
   		MsgBox(0, "", "Parameter " & $sParam & "not found!!!")
  EndIf

  Return $sValue;

EndFunc