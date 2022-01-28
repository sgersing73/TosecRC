#include <WinAPIShPath.au3>
#include <Array.au3>
#include <File.au3>

Const $EMULATOR = 'T:\Emus\Commodore VIC20\WinVICE-v2.4-x86\xvic.exe'

Local $aCmdLine = _WinAPI_CommandLineToArgv($CmdLineRaw)
Local $bootimage = _GetParaValues($aCmdLine, "/b:")
Local $swapimage = _GetParaValues($aCmdLine, "/d:")

Dim $szDrive, $szDir, $szFName, $szExt
_PathSplit($bootimage, $szDrive, $szDir, $szFName, $szExt)

If $szExt = ".crt" Then
  ShellExecute ($EMULATOR, '-cartgeneric "' & $bootimage & '"' )
Else
  ShellExecute ($EMULATOR, '-autostart "' & $bootimage & '" ' & _makeFlipList($swapimage))
EndIF

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

;===============================================================================
;
;===============================================================================
Func _makeFlipList($sFileString)

    Local $sRetValue = ""

    If $sFileString = "" Then
       return $sRetValue
    EndIf

		   ; Create a constant variable in Local scope of the filepath that will be read/written to.
    Local Const $sFilePath = "B:\fliplist.vfl"

    ; Delete the temporary file.
    FileDelete($sFilePath)			

    Local $hFileOpen = FileOpen($sFilePath, $FO_APPEND)
    If $hFileOpen = -1 Then
        MsgBox($MB_SYSTEMMODAL, "", "An error occurred whilst writing the temporary file.")
        Return $sRetValue
    EndIf

    ; Write data to the file using the handle returned by FileOpen.
    FileWrite($hFileOpen, "# Vice fliplist file" & @CRLF);
    FileWrite($hFileOpen, "UNIT 8" & @CRLF);

    Local $aArray = StringSplit($sFileString, ',', $STR_ENTIRESPLIT)
    For $i = 1 To $aArray[0] ; 
       FileWrite($hFileOpen, $aArray[$i] & @CRLF)
    Next

    ; Close the handle returned by FileOpen.
    FileClose($hFileOpen)

 	$sRetValue = "-flipname " & $sFilePath;
	
    Return $sRetValue

EndFunc