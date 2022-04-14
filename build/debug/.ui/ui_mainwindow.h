/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "src/widgets/AmigaRemix/amigaremix.h"
#include "src/widgets/Gamebase/gamebase.h"
#include "src/widgets/Musik/musik.h"
#include "src/widgets/Performance/performance.h"
#include "src/widgets/SidPlayer/sidplayer.h"
#include "src/widgets/TheModArchive/themodarchive.h"
#include "src/widgets/TosecView/tosecview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionRead_DAT_XML_file;
    QAction *actionRead_directroy_of_DAT_XML_files;
    QAction *actionScan_for_new_roms;
    QAction *actionDelete_database;
    QAction *actionToggle_SID_Player;
    QAction *actionUpdate_rom_storage;
    QAction *actionAmigaRemix;
    QAction *actionFlashtro;
    QAction *actionSettings;
    QAction *actionVerifyRomStore;
    QAction *actionSystem_Overview;
    QAction *actionThe_Mod_Archive;
    QAction *actionDownload;
    QAction *actionSqliteBrowser3;
    QAction *actionGamebase;
    QAction *actionLockStorage;
    QAction *actionUnlockStorage;
    QAction *actionMakeAESKey;
    QAction *actionDropbox;
    QAction *actionPDFViewer;
    QAction *actionSQLBrowser;
    QAction *actionAmigaFutureOnlineMag;
    QAction *actionView_Log_File;
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QSplitter *splitter_4;
    QSplitter *splitter_3;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *chkLoadAll;
    QComboBox *cboSystems;
    QPushButton *cmdSystemEdit;
    TosecView *widTosec;
    QLabel *lblLogo;
    QSplitter *splitter_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *chkTailLog;
    QCheckBox *chkSys;
    QCheckBox *chkWikiInfo;
    QCheckBox *chkTosec;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdPortrait;
    QPushButton *cmdPCB;
    QSplitter *splitter;
    QListWidget *listWidget;
    QGroupBox *grpBrowser;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *cmdLink1;
    QPushButton *cmdLink2;
    QPushButton *cmdLink3;
    QPushButton *cmdLink4;
    QLineEdit *edtBrowserUrl;
    QComboBox *cboHtmlLinks;
    QWebView *webView;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *cmdBrowserBack;
    QPushButton *cmdBrowserForward;
    QSpacerItem *horizontalSpacer_3;
    QProgressBar *prgWebViewLoading;
    QCheckBox *chkWebViewLocked;
    Performance *widPerformance;
    QWidget *layoutWidget11;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblImage1;
    QLabel *lblImage2;
    QTableWidget *tableWidgetInfo;
    QGroupBox *gpSelection;
    QGridLayout *gridLayout_7;
    QLineEdit *edtSearch;
    QGridLayout *gridLayout;
    QPushButton *cmdJR;
    QPushButton *cmd09;
    QPushButton *cmdSZ;
    QPushButton *cmdAll;
    QPushButton *cmdAI;
    QPushButton *cmdFavorite;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkOnlyValid;
    QCheckBox *chkOnlyCue;
    QCheckBox *chkOnlyMissing;
    QCheckBox *chkSystemSearch;
    QCheckBox *chkGamebase;
    QLabel *lblAnzRomInfo;
    Gamebase *widGamebase;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_6;
    SidPlayer *widSidPlayer;
    Musik *widMP3;
    TheModArchive *widTheModArchive;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblPublisher;
    QLabel *lblDeveloper;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *cmdShowFile;
    QPushButton *cmdUpload;
    QPushButton *cmdTheGamesDB;
    QPushButton *cmdExtract;
    QPushButton *cmdStartEmu;
    QCheckBox *chkFullscreen;
    QPushButton *edtSystems;
    QHBoxLayout *horizontalLayout_10;
    QLabel *lblCover;
    QLabel *lblMedia;
    AmigaRemix *widAmigaRemix;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *cmdSolution;
    QPushButton *cmdCodeTable;
    QPushButton *cmdManuals;
    QPushButton *cmdSoundtrack;
    QPushButton *cmdYoutubeVideo;
    QHBoxLayout *horizontalLayout_9;
    QComboBox *cboStartups;
    QTextEdit *edtLogFile;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuDatenbank;
    QMenu *menuTools;
    QMenu *menuMusik;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QToolBar *toolBarSystems;
    QToolBar *toolBarLinks;
    QToolBar *toolBarYoutube;
    QToolBar *toolHomeComputersDigital;
    QToolBar *toolNews;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1575, 665);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/program/icon/images/Mcdo-Design-Cats-2-Dot-Mac-Logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAnimated(true);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/toolbar/blue/images/toolbar/blue/exit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionRead_DAT_XML_file = new QAction(MainWindow);
        actionRead_DAT_XML_file->setObjectName(QString::fromUtf8("actionRead_DAT_XML_file"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/files.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionRead_DAT_XML_file->setIcon(icon2);
        actionRead_directroy_of_DAT_XML_files = new QAction(MainWindow);
        actionRead_directroy_of_DAT_XML_files->setObjectName(QString::fromUtf8("actionRead_directroy_of_DAT_XML_files"));
        actionRead_directroy_of_DAT_XML_files->setIcon(icon2);
        actionScan_for_new_roms = new QAction(MainWindow);
        actionScan_for_new_roms->setObjectName(QString::fromUtf8("actionScan_for_new_roms"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/search.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionScan_for_new_roms->setIcon(icon3);
        actionDelete_database = new QAction(MainWindow);
        actionDelete_database->setObjectName(QString::fromUtf8("actionDelete_database"));
        actionToggle_SID_Player = new QAction(MainWindow);
        actionToggle_SID_Player->setObjectName(QString::fromUtf8("actionToggle_SID_Player"));
        actionUpdate_rom_storage = new QAction(MainWindow);
        actionUpdate_rom_storage->setObjectName(QString::fromUtf8("actionUpdate_rom_storage"));
        actionAmigaRemix = new QAction(MainWindow);
        actionAmigaRemix->setObjectName(QString::fromUtf8("actionAmigaRemix"));
        actionFlashtro = new QAction(MainWindow);
        actionFlashtro->setObjectName(QString::fromUtf8("actionFlashtro"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/toolbar/blue/images/toolbar/blue/setttings.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon4);
        actionVerifyRomStore = new QAction(MainWindow);
        actionVerifyRomStore->setObjectName(QString::fromUtf8("actionVerifyRomStore"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/verify.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionVerifyRomStore->setIcon(icon5);
        actionSystem_Overview = new QAction(MainWindow);
        actionSystem_Overview->setObjectName(QString::fromUtf8("actionSystem_Overview"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/systems.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSystem_Overview->setIcon(icon6);
        actionThe_Mod_Archive = new QAction(MainWindow);
        actionThe_Mod_Archive->setObjectName(QString::fromUtf8("actionThe_Mod_Archive"));
        actionDownload = new QAction(MainWindow);
        actionDownload->setObjectName(QString::fromUtf8("actionDownload"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/toolbar/blue/images/toolbar/blue/download.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionDownload->setIcon(icon7);
        actionSqliteBrowser3 = new QAction(MainWindow);
        actionSqliteBrowser3->setObjectName(QString::fromUtf8("actionSqliteBrowser3"));
        actionGamebase = new QAction(MainWindow);
        actionGamebase->setObjectName(QString::fromUtf8("actionGamebase"));
        actionLockStorage = new QAction(MainWindow);
        actionLockStorage->setObjectName(QString::fromUtf8("actionLockStorage"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icon/toolbar/blue/images/toolbar/blue/lock.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionLockStorage->setIcon(icon8);
        actionUnlockStorage = new QAction(MainWindow);
        actionUnlockStorage->setObjectName(QString::fromUtf8("actionUnlockStorage"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icon/toolbar/blue/images/toolbar/blue/unlock.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionUnlockStorage->setIcon(icon9);
        actionMakeAESKey = new QAction(MainWindow);
        actionMakeAESKey->setObjectName(QString::fromUtf8("actionMakeAESKey"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icon/toolbar/blue/images/toolbar/blue/shield.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionMakeAESKey->setIcon(icon10);
        actionDropbox = new QAction(MainWindow);
        actionDropbox->setObjectName(QString::fromUtf8("actionDropbox"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icon/toolbar/blue/images/toolbar/blue/1471905738_Dropbox.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionDropbox->setIcon(icon11);
        actionPDFViewer = new QAction(MainWindow);
        actionPDFViewer->setObjectName(QString::fromUtf8("actionPDFViewer"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/quill.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionPDFViewer->setIcon(icon12);
        actionSQLBrowser = new QAction(MainWindow);
        actionSQLBrowser->setObjectName(QString::fromUtf8("actionSQLBrowser"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/database.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSQLBrowser->setIcon(icon13);
        actionAmigaFutureOnlineMag = new QAction(MainWindow);
        actionAmigaFutureOnlineMag->setObjectName(QString::fromUtf8("actionAmigaFutureOnlineMag"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/gift.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionAmigaFutureOnlineMag->setIcon(icon14);
        actionView_Log_File = new QAction(MainWindow);
        actionView_Log_File->setObjectName(QString::fromUtf8("actionView_Log_File"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        splitter_4 = new QSplitter(centralWidget);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setOrientation(Qt::Horizontal);
        splitter_3 = new QSplitter(splitter_4);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        gridLayout_5 = new QGridLayout(layoutWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        chkLoadAll = new QCheckBox(layoutWidget);
        chkLoadAll->setObjectName(QString::fromUtf8("chkLoadAll"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chkLoadAll->sizePolicy().hasHeightForWidth());
        chkLoadAll->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(chkLoadAll);

        cboSystems = new QComboBox(layoutWidget);
        cboSystems->setObjectName(QString::fromUtf8("cboSystems"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cboSystems->sizePolicy().hasHeightForWidth());
        cboSystems->setSizePolicy(sizePolicy1);
        cboSystems->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_7->addWidget(cboSystems);

        cmdSystemEdit = new QPushButton(layoutWidget);
        cmdSystemEdit->setObjectName(QString::fromUtf8("cmdSystemEdit"));
        sizePolicy.setHeightForWidth(cmdSystemEdit->sizePolicy().hasHeightForWidth());
        cmdSystemEdit->setSizePolicy(sizePolicy);
        cmdSystemEdit->setIcon(icon4);

        horizontalLayout_7->addWidget(cmdSystemEdit);


        gridLayout_5->addLayout(horizontalLayout_7, 1, 0, 1, 1);

        widTosec = new TosecView(layoutWidget);
        widTosec->setObjectName(QString::fromUtf8("widTosec"));

        gridLayout_5->addWidget(widTosec, 4, 0, 1, 1);

        lblLogo = new QLabel(layoutWidget);
        lblLogo->setObjectName(QString::fromUtf8("lblLogo"));
        lblLogo->setMaximumSize(QSize(16777215, 40));
        lblLogo->setScaledContents(false);
        lblLogo->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lblLogo, 0, 0, 1, 1);

        splitter_2 = new QSplitter(layoutWidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        layoutWidget1 = new QWidget(splitter_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        chkTailLog = new QCheckBox(layoutWidget1);
        chkTailLog->setObjectName(QString::fromUtf8("chkTailLog"));
        chkTailLog->setTristate(true);

        horizontalLayout_5->addWidget(chkTailLog);

        chkSys = new QCheckBox(layoutWidget1);
        chkSys->setObjectName(QString::fromUtf8("chkSys"));

        horizontalLayout_5->addWidget(chkSys);

        chkWikiInfo = new QCheckBox(layoutWidget1);
        chkWikiInfo->setObjectName(QString::fromUtf8("chkWikiInfo"));

        horizontalLayout_5->addWidget(chkWikiInfo);

        chkTosec = new QCheckBox(layoutWidget1);
        chkTosec->setObjectName(QString::fromUtf8("chkTosec"));

        horizontalLayout_5->addWidget(chkTosec);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        cmdPortrait = new QPushButton(layoutWidget1);
        cmdPortrait->setObjectName(QString::fromUtf8("cmdPortrait"));

        horizontalLayout_5->addWidget(cmdPortrait);

        cmdPCB = new QPushButton(layoutWidget1);
        cmdPCB->setObjectName(QString::fromUtf8("cmdPCB"));

        horizontalLayout_5->addWidget(cmdPCB);

        splitter_2->addWidget(layoutWidget1);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        listWidget = new QListWidget(splitter);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy2);
        listWidget->setMinimumSize(QSize(0, 100));
        listWidget->setMaximumSize(QSize(16777215, 16777215));
        splitter->addWidget(listWidget);
        grpBrowser = new QGroupBox(splitter);
        grpBrowser->setObjectName(QString::fromUtf8("grpBrowser"));
        grpBrowser->setFlat(false);
        grpBrowser->setCheckable(false);
        gridLayout_2 = new QGridLayout(grpBrowser);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        cmdLink1 = new QPushButton(grpBrowser);
        cmdLink1->setObjectName(QString::fromUtf8("cmdLink1"));

        horizontalLayout_4->addWidget(cmdLink1);

        cmdLink2 = new QPushButton(grpBrowser);
        cmdLink2->setObjectName(QString::fromUtf8("cmdLink2"));

        horizontalLayout_4->addWidget(cmdLink2);

        cmdLink3 = new QPushButton(grpBrowser);
        cmdLink3->setObjectName(QString::fromUtf8("cmdLink3"));

        horizontalLayout_4->addWidget(cmdLink3);

        cmdLink4 = new QPushButton(grpBrowser);
        cmdLink4->setObjectName(QString::fromUtf8("cmdLink4"));

        horizontalLayout_4->addWidget(cmdLink4);


        verticalLayout->addLayout(horizontalLayout_4);

        edtBrowserUrl = new QLineEdit(grpBrowser);
        edtBrowserUrl->setObjectName(QString::fromUtf8("edtBrowserUrl"));

        verticalLayout->addWidget(edtBrowserUrl);

        cboHtmlLinks = new QComboBox(grpBrowser);
        cboHtmlLinks->setObjectName(QString::fromUtf8("cboHtmlLinks"));

        verticalLayout->addWidget(cboHtmlLinks);

        webView = new QWebView(grpBrowser);
        webView->setObjectName(QString::fromUtf8("webView"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(webView->sizePolicy().hasHeightForWidth());
        webView->setSizePolicy(sizePolicy3);
        webView->setMaximumSize(QSize(16777215, 16777215));
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));
        webView->setZoomFactor(0.800000011920929);

        verticalLayout->addWidget(webView);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        cmdBrowserBack = new QPushButton(grpBrowser);
        cmdBrowserBack->setObjectName(QString::fromUtf8("cmdBrowserBack"));
        sizePolicy.setHeightForWidth(cmdBrowserBack->sizePolicy().hasHeightForWidth());
        cmdBrowserBack->setSizePolicy(sizePolicy);
        cmdBrowserBack->setMinimumSize(QSize(1, 0));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icon/player/blue/images/player/blue/backward.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdBrowserBack->setIcon(icon15);

        horizontalLayout_11->addWidget(cmdBrowserBack);

        cmdBrowserForward = new QPushButton(grpBrowser);
        cmdBrowserForward->setObjectName(QString::fromUtf8("cmdBrowserForward"));
        sizePolicy.setHeightForWidth(cmdBrowserForward->sizePolicy().hasHeightForWidth());
        cmdBrowserForward->setSizePolicy(sizePolicy);
        cmdBrowserForward->setMinimumSize(QSize(1, 0));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icon/player/blue/images/player/blue/forward.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdBrowserForward->setIcon(icon16);

        horizontalLayout_11->addWidget(cmdBrowserForward);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_3);

        prgWebViewLoading = new QProgressBar(grpBrowser);
        prgWebViewLoading->setObjectName(QString::fromUtf8("prgWebViewLoading"));
        prgWebViewLoading->setValue(24);
        prgWebViewLoading->setTextVisible(true);

        horizontalLayout_11->addWidget(prgWebViewLoading);

        chkWebViewLocked = new QCheckBox(grpBrowser);
        chkWebViewLocked->setObjectName(QString::fromUtf8("chkWebViewLocked"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(chkWebViewLocked->sizePolicy().hasHeightForWidth());
        chkWebViewLocked->setSizePolicy(sizePolicy4);

        horizontalLayout_11->addWidget(chkWebViewLocked);


        gridLayout_2->addLayout(horizontalLayout_11, 1, 0, 1, 1);

        splitter->addWidget(grpBrowser);
        splitter_2->addWidget(splitter);

        gridLayout_5->addWidget(splitter_2, 2, 0, 1, 1);

        widPerformance = new Performance(layoutWidget);
        widPerformance->setObjectName(QString::fromUtf8("widPerformance"));

        gridLayout_5->addWidget(widPerformance, 3, 0, 1, 1);

        splitter_3->addWidget(layoutWidget);
        layoutWidget11 = new QWidget(splitter_3);
        layoutWidget11->setObjectName(QString::fromUtf8("layoutWidget11"));
        gridLayout_3 = new QGridLayout(layoutWidget11);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lblImage1 = new QLabel(layoutWidget11);
        lblImage1->setObjectName(QString::fromUtf8("lblImage1"));
        lblImage1->setMaximumSize(QSize(16777215, 150));
        lblImage1->setScaledContents(false);
        lblImage1->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lblImage1);

        lblImage2 = new QLabel(layoutWidget11);
        lblImage2->setObjectName(QString::fromUtf8("lblImage2"));
        lblImage2->setMaximumSize(QSize(16777215, 150));
        lblImage2->setScaledContents(false);
        lblImage2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lblImage2);


        gridLayout_3->addLayout(horizontalLayout_3, 6, 0, 1, 1);

        tableWidgetInfo = new QTableWidget(layoutWidget11);
        tableWidgetInfo->setObjectName(QString::fromUtf8("tableWidgetInfo"));
        tableWidgetInfo->setAutoFillBackground(false);
        tableWidgetInfo->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        tableWidgetInfo->setSelectionMode(QAbstractItemView::ExtendedSelection);

        gridLayout_3->addWidget(tableWidgetInfo, 3, 0, 1, 1);

        gpSelection = new QGroupBox(layoutWidget11);
        gpSelection->setObjectName(QString::fromUtf8("gpSelection"));
        gpSelection->setMinimumSize(QSize(0, 0));
        gpSelection->setSizeIncrement(QSize(0, 0));
        gpSelection->setBaseSize(QSize(0, 0));
        gpSelection->setAlignment(Qt::AlignCenter);
        gpSelection->setFlat(false);
        gridLayout_7 = new QGridLayout(gpSelection);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(2, 2, 2, 2);
        edtSearch = new QLineEdit(gpSelection);
        edtSearch->setObjectName(QString::fromUtf8("edtSearch"));

        gridLayout_7->addWidget(edtSearch, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cmdJR = new QPushButton(gpSelection);
        cmdJR->setObjectName(QString::fromUtf8("cmdJR"));

        gridLayout->addWidget(cmdJR, 0, 4, 1, 1);

        cmd09 = new QPushButton(gpSelection);
        cmd09->setObjectName(QString::fromUtf8("cmd09"));
        cmd09->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(cmd09, 0, 2, 1, 1);

        cmdSZ = new QPushButton(gpSelection);
        cmdSZ->setObjectName(QString::fromUtf8("cmdSZ"));

        gridLayout->addWidget(cmdSZ, 0, 5, 1, 1);

        cmdAll = new QPushButton(gpSelection);
        cmdAll->setObjectName(QString::fromUtf8("cmdAll"));

        gridLayout->addWidget(cmdAll, 0, 1, 1, 1);

        cmdAI = new QPushButton(gpSelection);
        cmdAI->setObjectName(QString::fromUtf8("cmdAI"));

        gridLayout->addWidget(cmdAI, 0, 3, 1, 1);

        cmdFavorite = new QPushButton(gpSelection);
        cmdFavorite->setObjectName(QString::fromUtf8("cmdFavorite"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/star.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdFavorite->setIcon(icon17);
        cmdFavorite->setIconSize(QSize(13, 13));

        gridLayout->addWidget(cmdFavorite, 0, 6, 1, 1);


        gridLayout_7->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chkOnlyValid = new QCheckBox(gpSelection);
        chkOnlyValid->setObjectName(QString::fromUtf8("chkOnlyValid"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(chkOnlyValid->sizePolicy().hasHeightForWidth());
        chkOnlyValid->setSizePolicy(sizePolicy5);

        horizontalLayout->addWidget(chkOnlyValid);

        chkOnlyCue = new QCheckBox(gpSelection);
        chkOnlyCue->setObjectName(QString::fromUtf8("chkOnlyCue"));
        sizePolicy5.setHeightForWidth(chkOnlyCue->sizePolicy().hasHeightForWidth());
        chkOnlyCue->setSizePolicy(sizePolicy5);

        horizontalLayout->addWidget(chkOnlyCue);

        chkOnlyMissing = new QCheckBox(gpSelection);
        chkOnlyMissing->setObjectName(QString::fromUtf8("chkOnlyMissing"));

        horizontalLayout->addWidget(chkOnlyMissing);

        chkSystemSearch = new QCheckBox(gpSelection);
        chkSystemSearch->setObjectName(QString::fromUtf8("chkSystemSearch"));
        sizePolicy5.setHeightForWidth(chkSystemSearch->sizePolicy().hasHeightForWidth());
        chkSystemSearch->setSizePolicy(sizePolicy5);

        horizontalLayout->addWidget(chkSystemSearch);

        chkGamebase = new QCheckBox(gpSelection);
        chkGamebase->setObjectName(QString::fromUtf8("chkGamebase"));

        horizontalLayout->addWidget(chkGamebase);


        gridLayout_7->addLayout(horizontalLayout, 3, 0, 1, 1);

        lblAnzRomInfo = new QLabel(gpSelection);
        lblAnzRomInfo->setObjectName(QString::fromUtf8("lblAnzRomInfo"));
        lblAnzRomInfo->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(lblAnzRomInfo, 4, 0, 1, 1);


        gridLayout_3->addWidget(gpSelection, 2, 0, 1, 1);

        widGamebase = new Gamebase(layoutWidget11);
        widGamebase->setObjectName(QString::fromUtf8("widGamebase"));

        gridLayout_3->addWidget(widGamebase, 5, 0, 1, 1);

        splitter_3->addWidget(layoutWidget11);
        splitter_4->addWidget(splitter_3);
        layoutWidget2 = new QWidget(splitter_4);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        gridLayout_6 = new QGridLayout(layoutWidget2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        widSidPlayer = new SidPlayer(layoutWidget2);
        widSidPlayer->setObjectName(QString::fromUtf8("widSidPlayer"));

        gridLayout_6->addWidget(widSidPlayer, 10, 0, 1, 1);

        widMP3 = new Musik(layoutWidget2);
        widMP3->setObjectName(QString::fromUtf8("widMP3"));

        gridLayout_6->addWidget(widMP3, 7, 0, 1, 1);

        widTheModArchive = new TheModArchive(layoutWidget2);
        widTheModArchive->setObjectName(QString::fromUtf8("widTheModArchive"));

        gridLayout_6->addWidget(widTheModArchive, 9, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblPublisher = new QLabel(layoutWidget2);
        lblPublisher->setObjectName(QString::fromUtf8("lblPublisher"));
        lblPublisher->setMinimumSize(QSize(0, 0));
        lblPublisher->setMaximumSize(QSize(16777215, 50));
        lblPublisher->setScaledContents(false);
        lblPublisher->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lblPublisher);

        lblDeveloper = new QLabel(layoutWidget2);
        lblDeveloper->setObjectName(QString::fromUtf8("lblDeveloper"));
        lblDeveloper->setMinimumSize(QSize(0, 0));
        lblDeveloper->setMaximumSize(QSize(16777215, 50));
        lblDeveloper->setScaledContents(false);
        lblDeveloper->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lblDeveloper);


        gridLayout_6->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        tableWidget = new QTableWidget(layoutWidget2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        sizePolicy3.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy3);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(8);
        font.setBold(false);
        font.setWeight(50);
        tableWidget->setFont(font);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget->setAutoScroll(true);

        gridLayout_6->addWidget(tableWidget, 5, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        cmdShowFile = new QPushButton(layoutWidget2);
        cmdShowFile->setObjectName(QString::fromUtf8("cmdShowFile"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(cmdShowFile->sizePolicy().hasHeightForWidth());
        cmdShowFile->setSizePolicy(sizePolicy6);
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/presentation.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdShowFile->setIcon(icon18);

        horizontalLayout_6->addWidget(cmdShowFile);

        cmdUpload = new QPushButton(layoutWidget2);
        cmdUpload->setObjectName(QString::fromUtf8("cmdUpload"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/upload.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUpload->setIcon(icon19);

        horizontalLayout_6->addWidget(cmdUpload);

        cmdTheGamesDB = new QPushButton(layoutWidget2);
        cmdTheGamesDB->setObjectName(QString::fromUtf8("cmdTheGamesDB"));
        sizePolicy6.setHeightForWidth(cmdTheGamesDB->sizePolicy().hasHeightForWidth());
        cmdTheGamesDB->setSizePolicy(sizePolicy6);
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/image.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdTheGamesDB->setIcon(icon20);

        horizontalLayout_6->addWidget(cmdTheGamesDB);

        cmdExtract = new QPushButton(layoutWidget2);
        cmdExtract->setObjectName(QString::fromUtf8("cmdExtract"));
        sizePolicy6.setHeightForWidth(cmdExtract->sizePolicy().hasHeightForWidth());
        cmdExtract->setSizePolicy(sizePolicy6);
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/usbstick.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdExtract->setIcon(icon21);

        horizontalLayout_6->addWidget(cmdExtract);

        cmdStartEmu = new QPushButton(layoutWidget2);
        cmdStartEmu->setObjectName(QString::fromUtf8("cmdStartEmu"));
        sizePolicy6.setHeightForWidth(cmdStartEmu->sizePolicy().hasHeightForWidth());
        cmdStartEmu->setSizePolicy(sizePolicy6);
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/game.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdStartEmu->setIcon(icon22);

        horizontalLayout_6->addWidget(cmdStartEmu);

        chkFullscreen = new QCheckBox(layoutWidget2);
        chkFullscreen->setObjectName(QString::fromUtf8("chkFullscreen"));

        horizontalLayout_6->addWidget(chkFullscreen);

        edtSystems = new QPushButton(layoutWidget2);
        edtSystems->setObjectName(QString::fromUtf8("edtSystems"));
        sizePolicy6.setHeightForWidth(edtSystems->sizePolicy().hasHeightForWidth());
        edtSystems->setSizePolicy(sizePolicy6);
        edtSystems->setIcon(icon4);

        horizontalLayout_6->addWidget(edtSystems);


        gridLayout_6->addLayout(horizontalLayout_6, 2, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        lblCover = new QLabel(layoutWidget2);
        lblCover->setObjectName(QString::fromUtf8("lblCover"));
        lblCover->setMaximumSize(QSize(16777215, 150));
        lblCover->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(lblCover);

        lblMedia = new QLabel(layoutWidget2);
        lblMedia->setObjectName(QString::fromUtf8("lblMedia"));
        lblMedia->setMaximumSize(QSize(16777215, 150));
        lblMedia->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(lblMedia);


        gridLayout_6->addLayout(horizontalLayout_10, 11, 0, 1, 1);

        widAmigaRemix = new AmigaRemix(layoutWidget2);
        widAmigaRemix->setObjectName(QString::fromUtf8("widAmigaRemix"));

        gridLayout_6->addWidget(widAmigaRemix, 8, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        cmdSolution = new QPushButton(layoutWidget2);
        cmdSolution->setObjectName(QString::fromUtf8("cmdSolution"));

        horizontalLayout_12->addWidget(cmdSolution);

        cmdCodeTable = new QPushButton(layoutWidget2);
        cmdCodeTable->setObjectName(QString::fromUtf8("cmdCodeTable"));

        horizontalLayout_12->addWidget(cmdCodeTable);

        cmdManuals = new QPushButton(layoutWidget2);
        cmdManuals->setObjectName(QString::fromUtf8("cmdManuals"));

        horizontalLayout_12->addWidget(cmdManuals);

        cmdSoundtrack = new QPushButton(layoutWidget2);
        cmdSoundtrack->setObjectName(QString::fromUtf8("cmdSoundtrack"));

        horizontalLayout_12->addWidget(cmdSoundtrack);

        cmdYoutubeVideo = new QPushButton(layoutWidget2);
        cmdYoutubeVideo->setObjectName(QString::fromUtf8("cmdYoutubeVideo"));

        horizontalLayout_12->addWidget(cmdYoutubeVideo);


        gridLayout_6->addLayout(horizontalLayout_12, 6, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));

        gridLayout_6->addLayout(horizontalLayout_9, 4, 0, 1, 1);

        cboStartups = new QComboBox(layoutWidget2);
        cboStartups->setObjectName(QString::fromUtf8("cboStartups"));
        sizePolicy6.setHeightForWidth(cboStartups->sizePolicy().hasHeightForWidth());
        cboStartups->setSizePolicy(sizePolicy6);
        cboStartups->setMaximumSize(QSize(16777215, 16777215));
        cboStartups->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout_6->addWidget(cboStartups, 1, 0, 1, 1);

        splitter_4->addWidget(layoutWidget2);

        gridLayout_4->addWidget(splitter_4, 0, 0, 1, 1);

        edtLogFile = new QTextEdit(centralWidget);
        edtLogFile->setObjectName(QString::fromUtf8("edtLogFile"));
        edtLogFile->setEnabled(true);
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(edtLogFile->sizePolicy().hasHeightForWidth());
        edtLogFile->setSizePolicy(sizePolicy7);
        edtLogFile->setMaximumSize(QSize(16777215, 100));
        edtLogFile->setFrameShape(QFrame::Box);
        edtLogFile->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(edtLogFile, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1575, 22));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QString::fromUtf8("menuDatei"));
        menuDatenbank = new QMenu(menuBar);
        menuDatenbank->setObjectName(QString::fromUtf8("menuDatenbank"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuMusik = new QMenu(menuBar);
        menuMusik->setObjectName(QString::fromUtf8("menuMusik"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBarSystems = new QToolBar(MainWindow);
        toolBarSystems->setObjectName(QString::fromUtf8("toolBarSystems"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarSystems);
        toolBarLinks = new QToolBar(MainWindow);
        toolBarLinks->setObjectName(QString::fromUtf8("toolBarLinks"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarLinks);
        MainWindow->insertToolBarBreak(toolBarLinks);
        toolBarYoutube = new QToolBar(MainWindow);
        toolBarYoutube->setObjectName(QString::fromUtf8("toolBarYoutube"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarYoutube);
        toolHomeComputersDigital = new QToolBar(MainWindow);
        toolHomeComputersDigital->setObjectName(QString::fromUtf8("toolHomeComputersDigital"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolHomeComputersDigital);
        toolNews = new QToolBar(MainWindow);
        toolNews->setObjectName(QString::fromUtf8("toolNews"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolNews);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuDatenbank->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuMusik->menuAction());
        menuDatei->addAction(actionView_Log_File);
        menuDatei->addSeparator();
        menuDatei->addAction(actionExit);
        menuDatenbank->addAction(actionRead_DAT_XML_file);
        menuDatenbank->addAction(actionRead_directroy_of_DAT_XML_files);
        menuDatenbank->addSeparator();
        menuDatenbank->addAction(actionScan_for_new_roms);
        menuDatenbank->addAction(actionSystem_Overview);
        menuDatenbank->addSeparator();
        menuDatenbank->addAction(actionDelete_database);
        menuDatenbank->addAction(actionUpdate_rom_storage);
        menuTools->addAction(actionSqliteBrowser3);
        menuTools->addAction(actionGamebase);
        menuMusik->addAction(actionAmigaRemix);
        menuMusik->addAction(actionToggle_SID_Player);
        menuMusik->addAction(actionThe_Mod_Archive);
        menuMusik->addAction(actionAmigaFutureOnlineMag);
        toolBar->addAction(actionExit);
        toolBar->addAction(actionRead_directroy_of_DAT_XML_files);
        toolBar->addAction(actionScan_for_new_roms);
        toolBar->addAction(actionVerifyRomStore);
        toolBar->addAction(actionSystem_Overview);
        toolBar->addAction(actionDownload);
        toolBar->addAction(actionSettings);
        toolBar->addSeparator();
        toolBar->addAction(actionMakeAESKey);
        toolBar->addAction(actionLockStorage);
        toolBar->addAction(actionUnlockStorage);
        toolBar->addSeparator();
        toolBar->addAction(actionSQLBrowser);
        toolBar->addAction(actionDropbox);
        toolBar->addAction(actionPDFViewer);
        toolBar->addSeparator();

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(quit()));
        QObject::connect(actionRead_DAT_XML_file, SIGNAL(triggered()), MainWindow, SLOT(importDatFile()));
        QObject::connect(actionRead_directroy_of_DAT_XML_files, SIGNAL(triggered()), MainWindow, SLOT(importDatFileDir()));
        QObject::connect(actionDelete_database, SIGNAL(triggered()), MainWindow, SLOT(deleteDatabase()));
        QObject::connect(actionScan_for_new_roms, SIGNAL(triggered()), MainWindow, SLOT(scanRoms()));
        QObject::connect(toolBarSystems, SIGNAL(actionTriggered(QAction*)), MainWindow, SLOT(handleToolBarSystem(QAction*)));
        QObject::connect(toolBarLinks, SIGNAL(actionTriggered(QAction*)), MainWindow, SLOT(handleToolBarLinks(QAction*)));
        QObject::connect(toolBarYoutube, SIGNAL(actionTriggered(QAction*)), MainWindow, SLOT(handleToolBarYoutube(QAction*)));
        QObject::connect(toolHomeComputersDigital, SIGNAL(actionTriggered(QAction*)), MainWindow, SLOT(handleToolBarHomeComputersDigital(QAction*)));
        QObject::connect(toolNews, SIGNAL(actionTriggered(QAction*)), MainWindow, SLOT(handleToolBarNews(QAction*)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TOSEC Rom Center (Homage)", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionRead_DAT_XML_file->setText(QApplication::translate("MainWindow", "Import a DAT File", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRead_DAT_XML_file->setToolTip(QApplication::translate("MainWindow", "Import a TOSEC DAT File", nullptr));
#endif // QT_NO_TOOLTIP
        actionRead_directroy_of_DAT_XML_files->setText(QApplication::translate("MainWindow", "Import DAT Files", nullptr));
        actionScan_for_new_roms->setText(QApplication::translate("MainWindow", "Rom scan", nullptr));
        actionDelete_database->setText(QApplication::translate("MainWindow", "Delete Database", nullptr));
        actionToggle_SID_Player->setText(QApplication::translate("MainWindow", "SID/AY Player", nullptr));
#ifndef QT_NO_TOOLTIP
        actionToggle_SID_Player->setToolTip(QApplication::translate("MainWindow", "show/hide SID Player", nullptr));
#endif // QT_NO_TOOLTIP
        actionUpdate_rom_storage->setText(QApplication::translate("MainWindow", "Update Rom Storage", nullptr));
        actionAmigaRemix->setText(QApplication::translate("MainWindow", "AmigaRemix", nullptr));
        actionFlashtro->setText(QApplication::translate("MainWindow", "Flashtro", nullptr));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", nullptr));
        actionVerifyRomStore->setText(QApplication::translate("MainWindow", "Verify Rom Store", nullptr));
        actionSystem_Overview->setText(QApplication::translate("MainWindow", "System Overview", nullptr));
        actionThe_Mod_Archive->setText(QApplication::translate("MainWindow", "The Mod Archive", nullptr));
        actionDownload->setText(QApplication::translate("MainWindow", "Download", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDownload->setToolTip(QApplication::translate("MainWindow", "Downloader", nullptr));
#endif // QT_NO_TOOLTIP
        actionSqliteBrowser3->setText(QApplication::translate("MainWindow", "SqliteBrowser3", nullptr));
        actionGamebase->setText(QApplication::translate("MainWindow", "Gamebase", nullptr));
        actionLockStorage->setText(QApplication::translate("MainWindow", "LockStorage", nullptr));
        actionUnlockStorage->setText(QApplication::translate("MainWindow", "UnlockStorage", nullptr));
        actionMakeAESKey->setText(QApplication::translate("MainWindow", "makeAESKey", nullptr));
        actionDropbox->setText(QApplication::translate("MainWindow", "Dropbox", nullptr));
        actionPDFViewer->setText(QApplication::translate("MainWindow", "PDFViewer", nullptr));
#ifndef QT_NO_TOOLTIP
        actionPDFViewer->setToolTip(QApplication::translate("MainWindow", "PDF Viewer", nullptr));
#endif // QT_NO_TOOLTIP
        actionSQLBrowser->setText(QApplication::translate("MainWindow", "SQLBrowser", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSQLBrowser->setToolTip(QApplication::translate("MainWindow", "SQLBrowser", nullptr));
#endif // QT_NO_TOOLTIP
        actionAmigaFutureOnlineMag->setText(QApplication::translate("MainWindow", "Amiga Future (Online Mag.)", nullptr));
        actionView_Log_File->setText(QApplication::translate("MainWindow", "View Log-File", nullptr));
#ifndef QT_NO_TOOLTIP
        chkLoadAll->setToolTip(QApplication::translate("MainWindow", "Show only valid rom entries", nullptr));
#endif // QT_NO_TOOLTIP
        chkLoadAll->setText(QApplication::translate("MainWindow", "load all", nullptr));
        cmdSystemEdit->setText(QString());
        lblLogo->setText(QApplication::translate("MainWindow", "Logo", nullptr));
        chkTailLog->setText(QApplication::translate("MainWindow", "Tail Logfile", nullptr));
        chkSys->setText(QApplication::translate("MainWindow", "System", nullptr));
        chkWikiInfo->setText(QApplication::translate("MainWindow", "Wiki", nullptr));
        chkTosec->setText(QApplication::translate("MainWindow", "Tosec", nullptr));
        cmdPortrait->setText(QApplication::translate("MainWindow", "Portrait", nullptr));
        cmdPCB->setText(QApplication::translate("MainWindow", "PCB", nullptr));
        grpBrowser->setTitle(QString());
        cmdLink1->setText(QApplication::translate("MainWindow", "Link 1", nullptr));
        cmdLink2->setText(QApplication::translate("MainWindow", "Link 2", nullptr));
        cmdLink3->setText(QApplication::translate("MainWindow", "Link 3", nullptr));
        cmdLink4->setText(QApplication::translate("MainWindow", "Link 4", nullptr));
        cmdBrowserBack->setText(QString());
        cmdBrowserForward->setText(QString());
        chkWebViewLocked->setText(QApplication::translate("MainWindow", "Browserlock", nullptr));
        lblImage1->setText(QApplication::translate("MainWindow", "Screen shot 1", nullptr));
        lblImage2->setText(QApplication::translate("MainWindow", "Screen shot 2", nullptr));
        gpSelection->setTitle(QString());
        cmdJR->setText(QApplication::translate("MainWindow", "J-R", nullptr));
        cmd09->setText(QApplication::translate("MainWindow", "0-9", nullptr));
        cmdSZ->setText(QApplication::translate("MainWindow", "S-Z", nullptr));
        cmdAll->setText(QApplication::translate("MainWindow", "all", nullptr));
        cmdAI->setText(QApplication::translate("MainWindow", "A-I", nullptr));
        cmdFavorite->setText(QString());
        chkOnlyValid->setText(QApplication::translate("MainWindow", "valids", nullptr));
        chkOnlyCue->setText(QApplication::translate("MainWindow", "cue", nullptr));
        chkOnlyMissing->setText(QApplication::translate("MainWindow", "missing", nullptr));
        chkSystemSearch->setText(QApplication::translate("MainWindow", "system search", nullptr));
        chkGamebase->setText(QApplication::translate("MainWindow", "gamebase roms", nullptr));
        lblAnzRomInfo->setText(QApplication::translate("MainWindow", "no roms loaded...", nullptr));
        lblPublisher->setText(QApplication::translate("MainWindow", "Publisher Logo", nullptr));
        lblDeveloper->setText(QApplication::translate("MainWindow", "Developer Logo", nullptr));
#ifndef QT_NO_TOOLTIP
        cmdShowFile->setToolTip(QApplication::translate("MainWindow", "show image in default viewer", nullptr));
#endif // QT_NO_TOOLTIP
        cmdShowFile->setText(QString());
        cmdUpload->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdTheGamesDB->setToolTip(QApplication::translate("MainWindow", "query TheGamesDB", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cmdExtract->setToolTip(QApplication::translate("MainWindow", "save image to disk", nullptr));
#endif // QT_NO_TOOLTIP
        cmdExtract->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdStartEmu->setToolTip(QApplication::translate("MainWindow", "start emulation", nullptr));
#endif // QT_NO_TOOLTIP
        cmdStartEmu->setText(QString());
        chkFullscreen->setText(QApplication::translate("MainWindow", "Fullscreen", nullptr));
#ifndef QT_NO_TOOLTIP
        edtSystems->setToolTip(QApplication::translate("MainWindow", "edit startup files", nullptr));
#endif // QT_NO_TOOLTIP
        edtSystems->setText(QString());
        lblCover->setText(QApplication::translate("MainWindow", "Cover", nullptr));
        lblMedia->setText(QApplication::translate("MainWindow", "Media", nullptr));
        cmdSolution->setText(QApplication::translate("MainWindow", "Solution", nullptr));
        cmdCodeTable->setText(QApplication::translate("MainWindow", "Codetable", nullptr));
        cmdManuals->setText(QApplication::translate("MainWindow", "Manual", nullptr));
        cmdSoundtrack->setText(QApplication::translate("MainWindow", "Soundtrack", nullptr));
        cmdYoutubeVideo->setText(QApplication::translate("MainWindow", "Video", nullptr));
        menuDatei->setTitle(QApplication::translate("MainWindow", "Datei", nullptr));
        menuDatenbank->setTitle(QApplication::translate("MainWindow", "Database", nullptr));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", nullptr));
        menuMusik->setTitle(QApplication::translate("MainWindow", "Multimedia", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "Toolbar Funktionen", nullptr));
        toolBarSystems->setWindowTitle(QApplication::translate("MainWindow", "Toolbar Systems", nullptr));
        toolBarLinks->setWindowTitle(QApplication::translate("MainWindow", "Toolbar Hyperlinks", nullptr));
        toolBarYoutube->setWindowTitle(QApplication::translate("MainWindow", "Toolbar Youtube", nullptr));
        toolHomeComputersDigital->setWindowTitle(QApplication::translate("MainWindow", "Toolbar HomeComputers", nullptr));
        toolNews->setWindowTitle(QApplication::translate("MainWindow", "Toolbar Newsticker", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
