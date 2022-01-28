#include <Array.au3>
#include <File.au3>

Const $EMULATOR = 'T:\Emus\Atari 7800\EMU7800-v1.8\EMU7800.Win.exe'

;msgbox (0,"",$CmdLineRaw)

; Uebergabeparameter in ein Array umwandeln
Local $ResultArray = _ParseCMDLine($CmdLineRaw)
;_ArrayDisplay($ResultArray)

Local $bootimage = _GetParaValues($ResultArray, "b")

Dim $szDrive, $szDir, $szFName, $szExt
_PathSplit($bootimage, $szDrive, $szDir, $szFName, $szExt)

;If $szExt = ".dsk" Then
;  ShellExecute ($EMULATOR, "-diska " & $bootimage )
;ElseIf $szExt = ".rom" Then
;  ShellExecute ($EMULATOR, "-rom 0 " & $bootimage )
;Else
ShellExecute ($EMULATOR, $bootimage)
;EndIF

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