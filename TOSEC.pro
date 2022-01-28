#-------------------------------------------------
#
# Project created by QtCreator 2015-10-16T16:57:37
#
#-------------------------------------------------
MAJOR = 1
MINOR = 2
VERSION_HEADER = version.h

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui

versiontarget.target = $$VERSION_HEADER
versiontarget.depends = FORCE
win32:versiontarget.commands = 3dparty/Version/release/Version.exe $$MAJOR $$MINOR $$VERSION_HEADER
unix:versiontarget.commands = 3dparty/Version/Version $$MAJOR $$MINOR $$VERSION_HEADER

PRE_TARGETDEPS += $$VERSION_HEADER

QMAKE_EXTRA_TARGETS += versiontarget

RC_ICONS = images/Mcdo-Design-Cats-2-Dot-Mac-Logo.ico

CONFIG 	 += c++11

win32{
  QMAKE_CXXFLAGS += -D_WIN32_WINNT=0x600 -Wno-deprecated-declarations -static-libgcc -static-libstdc++ -ggdb -Wno-unused-parameter -Wno-unused-but-set-variable -Wno-zero-as-null-pointer-constant -Wimplicit-fallthrough
}

linux {
  QMAKE_CXXFLAGS += -Wno-deprecated-declarations -static-libgcc -static-libstdc++ -ggdb -Wno-unused-parameter -Wno-unused-but-set-variable -Wno-zero-as-null-pointer-constant -Wimplicit-fallthrough
}



TEMPLATE = app
TARGET = TosecRC

INCLUDEPATH += 3dparty/Qt-AES-master
INCLUDEPATH += 3dparty/QtDropbox2/src
INCLUDEPATH += 3dparty/wwWidgets/widgets

win32{

  QT += core gui widgets sql multimedia xml xmlpatterns concurrent printsupport winextras

  INCLUDEPATH += 3dparty/vlc-qt-1.1.0/include
  Debug:LIBS += -L3dparty/vlc-qt-1.1.0/lib -lVLCQtCored -lVLCQtWidgetsd
  Release:LIBS += -L3dparty/vlc-qt-1.1.0/lib  -lVLCQtCore -lVLCQtWidgets

  INCLUDEPATH += 3dparty/QScintilla_gpl-2.10.2/Qt4Qt5
  LIBS += -L3dparty/QScintilla_gpl-2.10.2/Qt4Qt5/release -lqscintilla2_qt5

  Release:LIBS += -L3dparty/wwWidgets/widgets/release -lwwwidgets5
  Debug:LIBS += -L3dparty/wwWidgets/widgets/debug -lwwwidgets5d

  INCLUDEPATH += 3dparty/QtWebKit/include
  LIBS += -L3dparty/QtWebKit/lib -lQt5WebKitWidgets.dll -lQt5WebKit.dll

  INCLUDEPATH += 3dparty/QMinizip
  LIBS += -L3dparty/QMinizip/release -lQMinizip1

  INCLUDEPATH += 3dparty/quazip-0.7.3
  LIBS += -L3dparty/quazip-0.7.3/quazip/release -lquazip

  INCLUDEPATH += 3dparty/Poppler-0.41.0/include
  LIBS += -L3dparty/Poppler-0.41.0/lib -lpoppler-qt5

  LIBS += -L3dparty/QtDropbox2/release -lQtDropbox2

  INCLUDEPATH += 3dparty/qwt-6.1.4/src
  Debug:LIBS += -L3dparty/qwt-6.1.4/lib -lqwtd
  Release:LIBS += -L3dparty/qwt-6.1.4/lib -lqwt

  LIBS += -lPdh
}

unix{

  QT   += core gui widgets sql multimedia xml xmlpatterns concurrent printsupport

  INCLUDEPATH += /usr/local/include

  LIBS += -lquazip5 -lqwt-qt5
  LIBS += -L/opt/Qt/5.14.2/gcc_64/lib -lwwwidgets5
  LIBS += -L/usr/lib/x86_64-linux-gnu -lpoppler-qt5
  LIBS += -L/usr/lib/x86_64-linux-gnu -lQt5WebKit -lQt5WebKitWidgets
  LIBS += -L/usr/local/lib -lVLCQtCore -lVLCQtWidgets
  LIBS += -lqscintilla2_qt5

  include(3dparty/QtDropbox2/qtdropbox2.pri)
  
}

SOURCES += main.cpp\
        mainwindow.cpp \
        src/modules/ftpserver.cpp \
        src/modules/crc32.cpp \
        src/modules/db.cpp \
        src/modules/iconextractor.cpp \
        src/modules/valuebar.cpp \
        src/modules/xml.cpp \
        src/widgets/AmigaFuture/amigafuture.cpp \
        src/widgets/Musik/musik.cpp \
        src/modules/norwegianwoodstyle.cpp \
        src/modules/bronzestyle.cpp \
        src/widgets/Gamebase/gamebase.cpp \
        src/widgets/ScrollText/scrolltext.cpp \
        src/widgets/SidPlayer/sidplayer.cpp \
        src/modules/htmlpageloader.cpp \
        src/widgets/AmigaRemix/amigaremix.cpp \
        src/widgets/EquilizerDialog/EqualizerDialog.cpp \
        src/modules/settings.cpp \
        src/modules/ConvertUTF.c \
        src/modules/tools.cpp \
        src/modules/zip.cpp \
        src/widgets/SettingsDialog/qsettingsdialog.cpp \
        src/stardelegate/stardelegate.cpp \
        src/stardelegate/stareditor.cpp \
        src/stardelegate/starrating.cpp \
        src/widgets/Performance/performance.cpp \
        src/modules/filedownloader.cpp \
        src/widgets/SwitchButton/switchbutton.cpp \
        src/widgets/TheModArchive/themodarchive.cpp \
        src/modules/highlighter.cpp \
        src/widgets/CodeEditor/codeeditor.cpp \
        src/widgets/DownloadMgr/downloadmgr.cpp \
        src/http/requestmapper.cpp \
        src/http/controller/templatecontroller.cpp \
        src/http/controller/dumpcontroller.cpp \
        src/http/controller/formcontroller.cpp \
        src/http/controller/fileuploadcontroller.cpp \
        src/http/controller/sessioncontroller.cpp \
        src/widgets/AesKeyGenerator/aeskeygenerator.cpp \
        src/widgets/DropboxBrowser/dropboxbrowser.cpp \
        src/widgets/StuffPackEdit/stuffpackedit.cpp \
        src/widgets/PDFViewer/pdfviewer.cpp \
        src/widgets/TheGamesDB/thegamesdb.cpp \
        src/widgets/ImageViewer/imageviewer.cpp \
        src/widgets/SystemEditor/systemeditor.cpp \
        src/widgets/TosecView/tosecview.cpp \
        src/widgets/FtpUpload/ftpupload.cpp \
        src/modules/qftp.cpp \
        src/modules/qurlinfo.cpp \
        src/widgets/SQLBrowser/browser.cpp \
        src/widgets/SQLBrowser/connectionwidget.cpp \
        src/widgets/SQLBrowser/qsqlconnectiondialog.cpp \
        src/scraper/abstractscraper.cpp \
        src/scraper/gameentry.cpp \
        src/scraper/mobygames.cpp \
        src/scraper/netcomm.cpp \
        src/scraper/strtools.cpp \
        src/scraper/platform.cpp \
        src/scraper/nametools.cpp \

HEADERS  += config.h \
        build_defs.h \
        src/widgets/AmigaFuture/amigafuture.h \
        src/widgets/ScrollText/scrolltext.h \
        src/widgets/SwitchButton/switchbutton.h \
        version.h \
        mainwindow.h \
        src/modules/checktime.h \
        src/modules/ftpserver.h \
        src/modules/crc32.h \
        src/modules/db.h \
        src/modules/iconextractor.h \
        src/modules/xml.h \
        src/widgets/Musik/musik.h \
        src/modules/norwegianwoodstyle.h \
        src/modules/bronzestyle.h \
        src/widgets/Gamebase/gamebase.h \
        src/widgets/SidPlayer/sidplayer.h \
        src/modules/htmlpageloader.h \
        src/widgets/AmigaRemix/amigaremix.h \
        src/widgets/EquilizerDialog/EqualizerDialog.h \
        src/modules/ConvertUTF.h \
        src/modules/simpleini.h \
        src/modules/settings.h \
        src/modules/zip.h \
        src/stardelegate/stardelegate.h \
        src/stardelegate/stareditor.h \
        src/stardelegate/starrating.h \
        src/widgets/Performance/performance.h \
        src/widgets/FtpUpload/ftpupload.h \
        src/widgets/SettingsDialog/qsettingsdialog.h \
        src/modules/filedownloader.h \
        src/widgets/TheModArchive/themodarchive.h \
        src/modules/highlighter.h \
        src/widgets/CodeEditor/codeeditor.h \
        src/widgets/DownloadMgr/downloadmgr.h \
        src/http/requestmapper.h \
        src/http/controller/templatecontroller.h \
        src/http/controller/dumpcontroller.h \
        src/http/controller/formcontroller.h \
        src/http/controller/fileuploadcontroller.h \
        src/http/controller/sessioncontroller.h \
        src/modules/tools.h \
        src/widgets/AesKeyGenerator/aeskeygenerator.h \
        src/widgets/DropboxBrowser/dropboxbrowser.h \
        src/widgets/StuffPackEdit/stuffpackedit.h \
        src/widgets/PDFViewer/pdfviewer.h \
        src/widgets/TheGamesDB/thegamesdb.h \
        src/widgets/ImageViewer/imageviewer.h \
        src/widgets/SystemEditor/systemeditor.h \
        src/widgets/TosecView/tosecview.h \
        src/modules/valuebar.h \
        src/modules/qftp.h \
        src/modules/qurlinfo.h \        
        src/widgets/SQLBrowser/browser.h \
        src/widgets/SQLBrowser/connectionwidget.h \
        src/widgets/SQLBrowser/qsqlconnectiondialog.h \
        src/scraper/abstractscraper.h \
        src/scraper/gameentry.h \
        src/scraper/mobygames.h \
        src/scraper/netcomm.h \
        src/scraper/settings.h \
        src/scraper/strtools.h \
        src/scraper/platform.h \
        src/scraper/nametools.h \


FORMS    += mainwindow.ui \
        src/widgets/AmigaFuture/amigafuture.ui \
        src/widgets/Gamebase/gamebase.ui \
        src/widgets/Musik/musik.ui \
        src/widgets/SidPlayer/sidplayer.ui \
        src/widgets/EquilizerDialog/EqualizerDialog.ui \
        src/widgets/AmigaRemix/amigaremix.ui \
        src/widgets/Performance/performance.ui \
        src/widgets/SettingsDialog/qsettingsdialog.ui \
        src/widgets/TheModArchive/themodarchive.ui \
        src/widgets/DownloadMgr/downloadmgr.ui \
        src/widgets/AesKeyGenerator/aeskeygenerator.ui \
        src/widgets/DropboxBrowser/dropboxbrowser.ui \
        src/widgets/StuffPackEdit/stuffpackedit.ui \
        src/widgets/PDFViewer/pdfviewer.ui \
        src/widgets/TheGamesDB/thegamesdb.ui \
        src/widgets/SystemEditor/systemeditor.ui \
        src/widgets/TosecView/tosecview.ui \
        src/widgets/SQLBrowser/browserwidget.ui \
        src/widgets/SQLBrowser/qsqlconnectiondialog.ui \
        src/widgets/FtpUpload/ftpupload.ui

include(3dparty/Qt-AES-master/qaesencryption.pri)

include(3dparty/QtWebApp/logging/logging.pri)
include(3dparty/QtWebApp/httpserver/httpserver.pri)
include(3dparty/QtWebApp/templateengine/templateengine.pri)

RESOURCES += tosec.qrc

COPY_FILES += \
    COPYRIGHT.txt \
    INSTALL.txt \
    README.txt \
    directories.ini \
    http.ini \
    tools.ini

