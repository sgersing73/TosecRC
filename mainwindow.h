#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QDebug>
#include <QtSql/QtSql>
#include <QVariantList>
#include <QDirIterator>
#include <QStatusBar>
#include <QStandardItemModel>
#include <QListView>
#include <QSettings>
#include <QColor>
#include <QListWidgetItem>
#include <QDesktopServices>
#include <QTimer>
#include <QProgressBar>
#include <QCryptographicHash>
#include <QStandardPaths>

#ifdef _WIN32
#include <QWinTaskbarProgress>
#include <QWinTaskbarButton>
#endif

#include <QHoverEvent>
#include <QSplashScreen>
#include <QTextStream>
#include <QLockFile>
#include <QThread>
#include <QXmlResultItems>
#include <QXmlNodeModelIndex>
#include <QCryptographicHash>

#include "qwwled/qwwled.h"

#ifdef _WIN32
#include "qwt.h"
#else
#include "qwt/qwt.h"
#endif

#include "poppler/qt5/poppler-qt5.h"

#include "httplistener.h"
#include "templatecache.h"
#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "filelogger.h"

#include "qaesencryption.h"

#include "src/http/requestmapper.h"

#ifdef _WIN32
#include "quazip/JlCompress.h"
#else
#include "quazip5/JlCompress.h"
#endif


#include "config.h"
#include "version.h"
#include "build_defs.h"

#include "src/modules/norwegianwoodstyle.h"
#include "src/modules/bronzestyle.h"
#include "src/modules/htmlpageloader.h"
#include "src/modules/filedownloader.h"

#include "src/modules/crc32.h"
#include "src/modules/db.h"
#include "src/modules/xml.h"
#include "src/modules/settings.h"
#include "src/modules/zip.h"
#include "src/modules/ftpserver.h"
#include "src/modules/ftp.h"
#include "src/modules/checktime.h"

#include "src/stardelegate/stardelegate.h"
#include "src/stardelegate/stareditor.h"
#include "src/stardelegate/starrating.h"

#include "src/widgets/ScrollText/scrolltext.h"
#include "src/widgets/SwitchButton/switchbutton.h"
#include "src/widgets/Musik/musik.h"
#include "src/widgets/Gamebase/gamebase.h"
#include "src/widgets/SettingsDialog/qsettingsdialog.h"
#include "src/widgets/CodeEditor/codeeditor.h"
#include "src/widgets/DownloadMgr/downloadmgr.h"
#include "src/widgets/AesKeyGenerator/aeskeygenerator.h"
#include "src/widgets/DropboxBrowser/dropboxbrowser.h"
#include "src/widgets/StuffPackEdit/stuffpackedit.h"
#include "src/widgets/PDFViewer/pdfviewer.h"
#include "src/widgets/TheGamesDB/thegamesdb.h"
#include "src/widgets/ImageViewer/imageviewer.h"
#include "src/widgets/SystemEditor/systemeditor.h"
#include "src/widgets/FtpUpload/ftpupload.h"
#include "src/widgets/SQLBrowser/browser.h"
#include "src/widgets/AmigaFuture/amigafuture.h"

//#include "src/scraper/abstractscraper.h"
//#include "src/scraper/mobygames.h"

#include <qtconcurrentrun.h>

using namespace QtConcurrent;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, QSplashScreen *splash = nullptr);
    ~MainWindow();

    void readXMLFile(QFile *);
    void storeData(QVariantList);
    //void findDatFiles(QFile *);
    void findRomFiles(QFile *, bool);
    void fillSystemCombo();
    void fillSetNameListView(QString, bool);
    void fillSoftwareTableView(QString, QString);
    bool clearDir( QString, bool secure = true, bool onlyTemp = true, QString prefix = "*.*" );
    void ResetStatusBar();
    void SetStatusBar(int, int, int, QString, bool);
    bool FileCopy(QString, QString);
    void setInfoTxt(QString, QColor, QString, bool );
    QByteArray fileChecksum(const QString &, QCryptographicHash::Algorithm);
    void loadSystemCounter();
    void verifyTosecDB();
    int  countFilesInDir(QString);
    void createDirStructure();
    void initYoutubeMenu();
    void initLinkMenu();
    bool currentConnectivityStatus();
    void initToolsMenu();
    void createQtActions();
    void about();
    void license();

    void hoverEnter(QHoverEvent *);
    void hoverLeave(QHoverEvent *);
    void hoverMove(QHoverEvent *);
    bool event(QEvent *);


protected:
    void dropEvent(QDropEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

public slots:

    void loadWebView(QString, bool ignoreLock = false, bool loadWebView = false);
    void webViewLoadFinished(bool ok);

    void loadSettings();
    void saveSettings();
    void importDatFileDir();
    void importDatFile();
    void getCRC32();
    void scanRoms();
    void deleteDatabase();
    void quit();

    void on_cmd09_clicked();
    void on_cmdAI_clicked();
    void on_cmdJR_clicked();
    void on_cmdSZ_clicked();
    void on_cmdAll_clicked();
    void on_cmdFavorite_clicked();
    void on_cboSystems_currentTextChanged(QString);
    void on_chkOnlyValid_clicked();

    void loadScreenshotsTimer();

    void ShowContextMenuSoftwareTable(const QPoint&);
    void ShowContextMenuRomTable(const QPoint&);
    void ShowContextMenuRomInfo(const QPoint&);
    void ShowContextMenuToolBarLinks(const QPoint&);
    void ShowContextMenuToolBarYoutube(const QPoint&);
    void ShowContextMenuToolBarHomeComputersDigital(const QPoint&);
    void ShowContextMenuLabelImage1(const QPoint&);
    void ShowContextMenuLabelImage2(const QPoint&);
    void ShowContextMenuLabelMedia(const QPoint&);
    void ShowContextMenuLabelCover(const QPoint&);
    void ShowContextMenuToolNews(const QPoint&);

    void loadRomList(QString);
    void loadSystemList();
    void setInfos(QString);
    void StartEmu();
    void BuildRomSet();
    void BuildVariantsSet();
    void ReleaseRomSet();
    void ToggleFavorite();
    void SubDialogFinished();

    bool ExecuteProgram(QString, QStringList, bool wait = false) ;
    void getDiskInfo();
    void getAmiKickRomInfo();
    void iniToolBarHomeComputersDigital();
    void iniToolBarSystem();
    void iniToolBarLinks();
    void iniToolBarYoutube();
    void StoreRomParameter();
    void MakeStuffPack(QString, QString);
    void RetrieveStuffPack(QString);
    void ImportStuffPack(QString);
    void loadImage(const QString &fileName, QImage *image);
    QPoint imagePos(const QImage &image) const ;
    void printOutput();
    void printError();
    void setStartButtonMode(bool);
    QString downloadFile(QUrl, QString, QString, bool force = false);
    void loadStuffPackContents(int);
    void setCurrentItem(QListWidgetItem *) ;
    QStringList getStartups(QString);
    void autoDownload();

    QStringList getEmuParameter(QString, QString Section = "Emus");
    QString     getRomSetDiskFiles( QString );
    void        getHexEditor();

    QString GetRandomString();
    void GetYoutubeInformations(QUrl);
    QString GetYoutubeVideoThumbnail(QUrl, QString);
    QString GetYoutubeVideoTitle(QUrl);
    QString GetYoutubeVideoUrl(QUrl);
    QString getMultiRomFiles(QString, QString, QString);
    bool checkFileInCache(QString);
    bool useFileCache();
    void buildUploadZipFiles(QString, QString);
    void buildStuffpackZipFiles(QString, QString);

    void youtubeMenuSelection(QAction*);
    void linkMenuSelection(QAction*);
    void toolsMenuSelection(QAction*);

    void showMessage(QString);

private slots:

    void tailLogfile();
    void checkConnection();
    void saveFile();
    void uploadProgress(qint64, qint64);
    void networkDone();
    void createTrayIcon();

    void handleToolBarNews(QAction *action);
    void handleToolBarSystem(QAction *action);
    void handleToolBarLinks(QAction *action);
    void handleToolBarYoutube(QAction *action);
    void handleToolBarHomeComputersDigital(QAction *action);

    void on_actionToggle_SID_Player_triggered();
    void on_actionUpdate_rom_storage_triggered();
    void on_actionAmigaRemix_triggered();
    void on_actionFlashtro_triggered();
    void on_actionSettings_triggered();
    void on_chkWikiInfo_clicked(bool checked);
    void on_chkOnlyValid_clicked(bool checked);
    void on_chkSys_clicked(bool checked);
    void on_actionVerifyRomStore_triggered();
    void on_chkTosec_clicked(bool checked);
    void on_tableWidgetInfo_itemClicked(QTableWidgetItem *item);
    void on_cmdStartEmu_clicked();
    void on_actionSystem_Overview_triggered();
    void on_actionThe_Mod_Archive_triggered();
    void on_edtSystems_clicked();
    void on_actionDownload_triggered();
    void on_actionLockStorage_triggered();
    void on_actionUnlockStorage_triggered();
    void on_webView_loadProgress(int progress);
    void on_webView_loadStarted();
    void on_webView_loadFinished(bool arg1);
    void on_actionMakeAESKey_triggered();
    void on_actionDropbox_triggered();
    void on_chkLoadAll_clicked();
    void on_cmdShowFile_clicked();
    void on_cmdManuals_clicked();
    void on_cmdBrowserForward_clicked();
    void on_cmdBrowserBack_clicked();
    void on_cmdSoundtrack_clicked();
    void on_cmdYoutubeVideo_clicked();
    void on_edtSearch_returnPressed();
    void on_actionPDFViewer_triggered();
    void on_cmdExtract_clicked();
    void on_chkTailLog_clicked(bool checked);
    void on_chkTailLog_stateChanged(int arg1);
    void on_tableWidgetInfo_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
    void on_chkOnlyCue_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_cmdTheGamesDB_clicked();
    void on_cboHtmlLinks_currentTextChanged(const QString &arg1);
    void on_cmdPCB_clicked();
    void on_cmdSystemEdit_clicked();
    void on_cmdPortrait_clicked();
    void on_cmdLink1_clicked();
    void on_cmdLink2_clicked();
    void on_cmdLink3_clicked();
    void on_cmdLink4_clicked();

    void on_cmdUpload_clicked();

    void on_cmdCodeTable_clicked();

    void on_cmdSolution_clicked();

    void on_actionSQLBrowser_triggered();

    void on_actionAmigaFutureOnlineMag_triggered();

    void on_actionView_Log_File_triggered();

    void on_edtBrowserUrl_returnPressed();

    void on_chkOnlyMissing_clicked();

private:

    Ui::MainWindow        *ui;
    QStandardItemModel    *model;
    QProgressDialog       *mProgressDialog;
    QListWidgetItem       *m_Item;
    QNetworkAccessManager *mNetwManager;
    QNetworkAccessManager *mUploadNetwManager;
    QNetworkReply         *mNetwReply;
    CodeEditor            *mMyCodeEditor;
    SystemEditor          *mSystemEditor;
    Browser               *myBrowser;
    PDFViewer             *myPDFViewer;
    DownloadMgr           *mMyDownloadMgr;
    FtpUpload             *mMyFtpUpload;
    QPropertyAnimation    *mpFadeIn;
    QTimer                *timer;
    QTimer                *mLogFileTimer;
    QTimer                *mConnectionTimer;
    FileDownloader        *m_pImgCtrl;
    TheGamesDB            *mTheGamesDB;
    bool                  m_updateTitleAllow;
    ImageViewer           *m_ImageViewer;
    FtpServer             *m_ftpserver;

    _crc32              m_crc32;
    db                  m_db;
    xml                 m_xml;

    QStringList         m_stdOutLines;
    QStringList         m_stdErrLines;

    QString             m_sSettingsFile;
    QString             m_QssFile;
    bool                m_beenden;
    int                 m_actSelectionMode;
    QString             m_FileStorage;
    QString             m_TempPath;
    QString             m_CachePath;
    QString             m_StartupsPath;
    QString             m_ImageCachePath;
    QString             m_actSystemLink;
    QString             m_Stylesheet;
    QString             m_AesKey;
    QString             m_currentYoutubeChannel;
    QString             m_currentLinkChannel;
    QString             m_lastSelectedSystem;
    QString             m_TosecMain;

    QString             m_actRomMusicValue;
    QString             m_actRomVideoValue;
    QString             m_actManualValue;
    QString             m_actCodetableValue;
    QString             m_actSolutionValue;
    QString             m_actPcbUrl;
    QString             m_actPartraitUrl;

    QStringList         m_screenshotfilelist;
    QStringList         m_coverfilelist;
    QStringList         m_compendiumlist;
    QStringList         m_mediafilelist;
    QStringList         m_soundtracklist;

    bool                m_httpdEnabled;
    bool                m_ftpEnabled;
    bool                m_ftpAnonymous;
    QString             m_FTPPort;
    QString             m_FTPUser;
    QString             m_FTPPassword;

    bool                m_proxyEnabled;
    QString             m_proxyUser;
    QString             m_proxyPassword;
    QString             m_proxyIp;
    int                 m_proxyPort;

    bool                m_StuffSrvEnabled;
    QString             m_StuffSrvUser;
    QString             m_StuffSrvPassword;
    QString             m_StuffSrvIp;
    int                 m_StuffSrvPort;

    // AmigaRemix
    int                 _ARsliMinValue;
    int                 _ARsliMaxValue;
    QString             _ARbaseUrl;
    QString             _ARurl;
    QString             _ARdateurl;
    QString             _ARratingurl;
    QString             _ARextension;

    // TheModArchiv
    int                 _TMAsliMinValue;
    int                 _TMAsliMaxValue;
    QString             _TMAbaseUrl;
    QString             _TMAurl;
    QString             _TMAdateurl;
    QString             _TMAratingurl;
    QString             _TMAextension;

    // Flashtro
    QString             _FTbaseUrl;
    QString             _FTurl;
    QString             _FTextension;

    QString             m_applName;
    int                 m_GridMode;
    tools               m_tools;
    settings            m_settings;
    QString             m_CurrentSystem;
    QString             m_CurrentSet;

    QProcess            *m_proc;
    QwwLed              *m_wwInternetLed;
    QString             m_schema;

    QLabel *httpLabel;
    QLabel *cacheLabel;
    QLabel *storageLabel;
    QLabel *proxyLabel;
    QLabel *aesLabel;
    QLabel *tempLabel;
    QLabel *internetLabel;

    ScrollText *scrollText;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    SwitchButton *sbtn;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    bool                   m_showMsgBox;

#ifdef _WIN32
    QWinTaskbarButton     *mTaskbarButton;
    QWinTaskbarProgress   *mTaskbarProgress;
#endif

};

#endif // MAINWINDOW_H
