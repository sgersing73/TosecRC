#include <Array.au3>
#include <File.au3>
#include <WinAPIShPath.au3>

Const $EMULATOR = 'T:\Emus\Commodore Amiga\winuae-v3.2.2\winuae.exe'
Const $BOOTDISK = 'T:\Emus\Commodore Amiga\winuae-v3.2.2\Workbench\Workbench v2.1 rev 38.35 (1992)(Commodore)(M10)(Disk 2 of 5)(Workbench)[Cloanto Amiga Forever Edition].adf'

;msgbox(0,"",$CmdLineRaw)

Local $aCmdLine = _WinAPI_CommandLineToArgv($CmdLineRaw)
Local $bootimage = _GetParaValues($aCmdLine, "/b:")
Local $swapimage = _GetParaValues($aCmdLine, "/d:")

Local $szDrive, $szDir, $szFName, $szExt
_PathSplit($bootimage, $szDrive, $szDir, $szFName, $szExt)

If $szExt = ".cue" or $szExt = ".iso" Then
    $commandstr = '-s quickstart=a1200,1 -s chipmem_size=8 -s fastmem_size=8 -s use_gui=no -s scsi=true -s win32.active_priority=1 -s floppy1type=-1 -s floppy0="' & $BOOTDISK & '" -cdimage="' & $bootimage & '"'  
Else
  If StringInStr($bootimage, "[WB]") Then
    $commandstr = '-s quickstart=a1200,1 -s use_gui=no -s win32.active_priority=1 -s floppy0="' & $BOOTDISK & '" -s floppy1="' & $bootimage & '" -diskswapper="' & $swapimage & '"'
  Else
    $commandstr = '-s quickstart=a1200,1 -s use_gui=no -s win32.active_priority=1 -s floppy0="' & $bootimage & '" -diskswapper="' & $swapimage & '"'
  EndIf
EndIf

ShellExecute ($EMULATOR, $commandstr)

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