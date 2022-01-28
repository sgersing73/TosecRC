@echo off

SET _ROOT=E:\PortableApps\CommonFiles\Qt\Qt5.12.3

SET QTDIR=%_ROOT%\5.12.3\mingw73_32
SET PATH=%QTDIR%\bin;%_ROOT%\Tools\mingw730_32\bin;%_ROOT%\Tools\QtCreator\bin;C:\Windows\System32

set clean=false
set mode=release
set dest=B:\Tosec

REM TortoiseProc.exe /command:update /path:"T:\Build" /closeonend:1

cd /d 3dparty\zlib-1.2.11 

if "%clean%"=="true" ( mingw32-make -f win32/Makefile.gcc clean )

mingw32-make -f win32/Makefile.gcc 

cd .. 
cd .. 

cd /d 3dparty\QScintilla_gpl-2.10.2\Qt4Qt5

call :compile

cd .. 
cd .. 
cd .. 

cd /d 3dparty\qwt-6.1.4 

call :compile

cd .. 
cd .. 

cd /d 3dparty\wwWidgets 

call :compile

cd .. 
cd .. 

cd /d 3dparty\QMinizip 

if "%clean%"=="true" ( mingw32-make clean ) 

if "%mode%"=="release" (
  qmake "CONFIG+=release" "INCLUDEPATH+=./../zlib-1.2.11" "LIBS+=-L./../zlib-1.2.11 -lz" 
  mingw32-make 
) else (
  qmake "CONFIG+=debug" "INCLUDEPATH+=./../zlib-1.2.11" "LIBS+=-L./../zlib-1.2.11 -lz" 
  mingw32-make 
)

cd .. 
cd .. 
 
cd /d 3dparty\quazip-0.7.3 

if "%clean%"=="true" ( mingw32-make clean ) 

if "%mode%"=="release" (
  qmake "CONFIG+=release" "INCLUDEPATH+=./../zlib-1.2.11" "LIBS+=-L./../zlib-1.2.11 -lz" 
  mingw32-make 
) else (
  qmake "CONFIG+=debug" "INCLUDEPATH+=./../zlib-1.2.11" "LIBS+=-L./../zlib-1.2.11 -lz" 
  mingw32-make 
)

cd .. 
cd .. 
 
cd /d 3dparty\Version 

call :compile

cd .. 
cd .. 
 
cd /d 3dparty\QtDropbox2 

call :compile

cd .. 
cd .. 
 
cd /d 3dparty\TinyAES 

call :compile

cd .. 
cd .. 
 
qmake "CONFIG+=release" TOSEC.pro 

call :compile

pause

mkdir %dest%
mkdir %dest%\images
 
xcopy 3dparty\zlib-1.2.11\zlib1.dll %dest% /DVSY 
xcopy 3dparty\quazip-0.7.3\quazip\release\quazip.dll %dest% /DVSY 
xcopy 3dparty\Poppler-0.41.0\bin\*.dll %dest% /DVSY 
xcopy 3dparty\TinyAES\release\*.dll %dest% /DVSY 
xcopy 3dparty\QtDropbox2\release\*.dll %dest% /DVSY 
xcopy 3dparty\vlc-qt-1.1.0\bin\*.* %dest% /DVSY 
xcopy 3dparty\OpenSSL\*.dll %dest% /DVSY 
xcopy 3dparty\QMinizip\release\*.dll %dest% /DVSY 
xcopy 3dparty\wwWidgets\widgets\release\*.dll %dest% /DVSY 
xcopy 3dparty\QScintilla_gpl-2.10.2\Qt4Qt5\release\*.dll %dest% /DVSY 
xcopy 3dparty\QtWebKit\bin\*.dll %dest% /DVSY 
xcopy 3dparty\qwt-6.1.4\lib\*.dll %dest% /DVSY 

xcopy release\TosecRC.exe %dest% /DVSY 
xcopy images %dest%\images /DVSY 
 
windeployqt %dest% 

.\3dparty\Fonts\addfont.bat 3dparty\Fonts\bitwise\

pause

:eof
exit

:compile

cls

if "%clean%"=="true" ( mingw32-make clean ) 

del Makefile

if "%mode%"=="release" (
  qmake "CONFIG+=release"  
  mingw32-make 
) else (
  qmake "CONFIG+=debug"
  mingw32-make 
)

REM pause

GOTO:EOF