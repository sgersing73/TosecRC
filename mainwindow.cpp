#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>

/** Cache for template files */
TemplateCache         *templateCache;

/** Storage for session cookies */
HttpSessionStore      *sessionStore;

/** Controller for static files */
StaticFileController  *staticFileController;

/** Redirects log messages to a file */
FileLogger            *logger;

#define NDEBUG

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
MainWindow::MainWindow(QWidget *parent, QSplashScreen *splash) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{           
    ui->setupUi(this);

    m_sSettingsFile = INI_FILE;

    this->createDirStructure();

    this->loadSettings();

    QSettings settings("state.ini", QSettings::IniFormat);

    ui->splitter->restoreState( settings.value("mainSplitterState", "" ).toByteArray() );
    ui->splitter_2->restoreState( settings.value("mainSplitterState2", "" ).toByteArray() );
    ui->splitter_3->restoreState( settings.value("mainSplitterState3", "" ).toByteArray() );
    ui->splitter_4->restoreState( settings.value("mainSplitterState4", "" ).toByteArray() );

    restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
    restoreState(settings.value("mainWindowState").toByteArray());

    if ( m_Stylesheet.contains("NorwegianWood") ) {

        QApplication::setStyle(new NorwegianWoodStyle);

    } else if ( m_Stylesheet.contains("Bronze") ) {

        QApplication::setStyle(new BronzeStyle);

    } else if ( m_Stylesheet.contains("FusionBlack") ) {

        QApplication::setStyle(QStyleFactory::create("Fusion"));

        QPalette palette;
        palette.setColor(QPalette::Window, QColor(53,53,53));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(15,15,15));
        palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(53,53,53));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
        palette.setColor(QPalette::HighlightedText, Qt::black);
        palette.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
        palette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
        QApplication::setPalette(palette);

    } else if ( m_Stylesheet.contains("Fusion") ) {

        QApplication::setStyle(QStyleFactory::create("Fusion"));

    } else if ( m_Stylesheet.contains("Windows") ) {

        qApp->setStyle(QStyleFactory::create("Windows"));

        qApp->setPalette(this->style()->standardPalette());
        qApp->setStyleSheet(styleSheet());

    } else if ( m_Stylesheet.contains("WindowsXP") ) {

        qApp->setStyle(QStyleFactory::create("WindowsXP"));

        qApp->setPalette(this->style()->standardPalette());
        qApp->setStyleSheet(styleSheet());

    } else if ( m_Stylesheet.contains("WindowsVista") ) {

        qApp->setStyle(QStyleFactory::create("WindowsVista"));

        qApp->setPalette(this->style()->standardPalette());
        qApp->setStyleSheet(styleSheet());
    }

    qDebug() << "available stylesheete" << QStyleFactory::keys();

    if ( ! m_QssFile.isEmpty() ) {
        QFile file( m_QssFile );
        file.open( QFile::ReadOnly );
        qApp->setStyleSheet( file.readAll() );
    }

    ui->cmdBrowserForward->setIcon(QIcon(QString(":/icon/player/images/player/%1/forward.ico").arg(m_schema)));
    ui->cmdBrowserBack->setIcon(QIcon(QString(":/icon/player/images/player/%1/backward.ico").arg(m_schema)));

#ifdef _WIN32
    mTaskbarButton = new QWinTaskbarButton(this);
    mTaskbarButton->setWindow(windowHandle());
    mTaskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    mTaskbarProgress = mTaskbarButton->progress();
#endif

    mpFadeIn = new QPropertyAnimation( this, "windowOpacity" );
    mpFadeIn->setDuration( 1000 );
    mpFadeIn->setStartValue( 0.0 );
    mpFadeIn->setEndValue( 1.0 );

    m_beenden = false;
    m_actSelectionMode = 0;
    m_Item = nullptr;
    m_proc = nullptr;

    splash->showMessage("clean temp directory... ");

    this->clearDir(m_TempPath);

    splash->showMessage("open database...");

    //m_db.open_mysql("tosec", "tosec", "tosec");    
    if ( ! m_db.open_sqlite("tosec.db3") ) {
        qDebug() << "unable to open database!!!";
        exit(0);
    }

    if ( m_proxyEnabled ) {

        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(m_proxyIp);
        proxy.setPort(m_proxyPort);
        proxy.setUser(m_proxyUser);
        proxy.setPassword(m_proxyPassword);
        QNetworkProxy::setApplicationProxy(proxy);
    }

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenuSoftwareTable(const QPoint&)));

    ui->tableWidgetInfo->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidgetInfo, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenuRomTable(const QPoint&)));

    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenuRomInfo(const QPoint&)));

    ui->toolBar->setVisible(true);

    ui->toolBarLinks->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->toolBarLinks, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenuToolBarLinks(const QPoint&)));

    ui->toolBarYoutube->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->toolBarYoutube, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenuToolBarYoutube(const QPoint&)));

    ui->toolHomeComputersDigital->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->toolHomeComputersDigital, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenuToolBarHomeComputersDigital(const QPoint&)));

    ui->toolNews->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->toolNews, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenuToolNews(const QPoint&)));

    scrollText = new ScrollText();
    scrollText->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    scrollText->setContentsMargins(0, 0, 0, 0);
    ui->toolNews->addWidget(scrollText);
    ui->toolNews->setVisible(true);

    ui->cmdManuals->setVisible(false);
    ui->cmdSoundtrack->setVisible(false);
    ui->cmdYoutubeVideo->setVisible(false);
    ui->cmdSolution->setVisible(false);
    ui->cmdCodeTable->setVisible(false);

    ui->widTosec->setHidden(true);
    ui->widMP3->setHidden(true);
    ui->widGamebase->setHidden(true);
    ui->widSidPlayer->setHidden(true);
    ui->edtLogFile->setHidden (true);

    ui->webView->setStyleSheet("none");

    // Screenshots zyklisch einblenden
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(loadScreenshotsTimer()));  
    timer->start(5000);    // msec

    // create a timer
    mLogFileTimer = new QTimer(this);
    // setup signal and slot
    connect(mLogFileTimer, SIGNAL(timeout()), this, SLOT(tailLogfile()));

    // create a timer
    mConnectionTimer = new QTimer(this);
    // setup signal and slot
    connect(mConnectionTimer, SIGNAL(timeout()), this, SLOT(checkConnection()));
    mConnectionTimer->start(1000);

    // AmigeRemix initialisieren
    ui->widAmigaRemix->setHidden(true);
    ui->widAmigaRemix->setBaseUrl(_ARbaseUrl);
    ui->widAmigaRemix->setUrl(_ARurl);
    ui->widAmigaRemix->setSortByDateUrl(_ARdateurl);
    ui->widAmigaRemix->setSortByRatingUrl(_ARratingurl);
    ui->widAmigaRemix->setSliMinValue(_ARsliMinValue);
    ui->widAmigaRemix->setSliMaxValue(_ARsliMaxValue);
    ui->widAmigaRemix->setFileExt(_ARextension);

    connect(ui->widAmigaRemix, SIGNAL( sliderChanged( QString, QString,  QString ) ),
            ui->widMP3,        SLOT  ( setURL ( QString, QString, QString ) ) );

    // TheModArchive initialisieren
    ui->widTheModArchive->setHidden(true);
    ui->widTheModArchive->setBaseUrl(_TMAbaseUrl);
    ui->widTheModArchive->setUrl(_TMAurl);
    ui->widTheModArchive->setSortByDateUrl(_TMAdateurl);
    ui->widTheModArchive->setSortByRatingUrl(_TMAratingurl);
    ui->widTheModArchive->setSliMinValue(_TMAsliMinValue);
    ui->widTheModArchive->setSliMaxValue(_TMAsliMaxValue);
    ui->widTheModArchive->setFileExt(_TMAextension);

    connect(ui->widTheModArchive, SIGNAL( sliderChanged( QString, QString,  QString ) ),
            ui->widMP3,        SLOT  ( setURL ( QString, QString, QString ) ) );

    // SidPlayer initialiseiren
    connect(ui->widSidPlayer, SIGNAL( directoryChanged(QString) ),
            ui->widMP3,       SLOT  ( setFilePath(QString) ) );
    connect(ui->widSidPlayer, SIGNAL( setFileExtension( QStringList ) ),
            ui->widMP3,       SLOT  ( setFileExtension ( QStringList ) ) );

    connect(ui->widSidPlayer, SIGNAL( setWebView( QString ) ),
            this,             SLOT  ( loadWebView ( QString ) ) );

    connect(ui->widGamebase,  SIGNAL( setWebView( QString ) ),
            this,             SLOT  ( loadWebView ( QString ) ) );


    connect(ui->webView,       SIGNAL( loadFinished( bool ) ),
            this,              SLOT  ( webViewLoadFinished ( bool ) ) );

    splash->showMessage("init controls...");

    // Hauptfenster einblenden
    mpFadeIn->start();

    QString host64info = "Host:x32";
    if ( m_tools.isHost64Bit() ) {
        host64info = "Host:x64";
    }

    QString appli64info = "Appli:x32";
    if ( m_tools.isBuild64Bit() ) {
        appli64info = "Appli:x64";
    }

    m_applName = QString("TOSEC Rom Center %1.%2.%3.%4 - %5 - %6 - Build: %7.%8.%9").arg(Version::MAJOR).arg(Version::MINOR).arg(Version::REVISION).arg(Version::BUILD).arg(host64info).arg(appli64info).arg(BUILD_DAY).arg(BUILD_MONTH).arg(BUILD_YEAR);

    setWindowTitle( m_applName );

    setAcceptDrops(true);

    if ( m_httpdEnabled ) {

        qDebug() << "Httpd enables...";

        // Configure template loader and cache
        QSettings* templateSettings=new QSettings("http.ini",QSettings::IniFormat,qApp);
        templateSettings->beginGroup("templates");
        templateCache=new TemplateCache(templateSettings,qApp);

        // Configure session store
        QSettings* sessionSettings=new QSettings("http.ini",QSettings::IniFormat,qApp);
        sessionSettings->beginGroup("sessions");
        sessionStore=new HttpSessionStore(sessionSettings,qApp);

        // Configure static file controller
        QSettings* fileSettings=new QSettings("http.ini",QSettings::IniFormat,qApp);
        fileSettings->beginGroup("docroot");
        staticFileController=new StaticFileController(fileSettings,qApp);

        // Configure and start the TCP listener
        QSettings* listenerSettings=new QSettings("http.ini",QSettings::IniFormat,qApp);
        listenerSettings->beginGroup("listener");
        new HttpListener(listenerSettings,new RequestMapper(qApp),qApp);
    }

    if ( m_ftpEnabled ) {

        m_ftpserver = new FtpServer(this);
        m_ftpserver->setWelcomeMessage("Hi,\nWelcome to debao's Ftp server.");

        if ( m_ftpAnonymous ) {
            m_ftpserver->addAccount("anonymous"); //Enable anonymous user with ReadOnly access.
        }

        m_ftpserver->addAccount(m_FTPUser,      //User Name
                                m_FTPPassword,  //PassWord
                                m_TosecMain,    //Directory
                                FtpServer::Read | FtpServer::Write | FtpServer::Exec);

        if (m_ftpserver->listen(QHostAddress::LocalHost, m_FTPPort.toInt())) {
            qDebug()<<"Listening at port 2121";
        } else {
            qDebug()<<"Failed.";
        }
    }

    ui->widPerformance->setHidden( ! (ui->chkSys->checkState() == Qt::Checked) );
    ui->grpBrowser->setHidden( ! (ui->chkWikiInfo->checkState() == Qt::Checked) );

    httpLabel = new QLabel(this);
    httpLabel->setText( m_httpdEnabled ? "Httpd ON" : "Httpd OFF" );
    ui->statusBar->addPermanentWidget(httpLabel);

    proxyLabel = new QLabel(this);
    proxyLabel->setText( m_proxyEnabled ? "Proxy ON" : "Proxy OFF" );
    ui->statusBar->addPermanentWidget(proxyLabel);

    aesLabel = new QLabel(this);
    aesLabel->setText( ( m_AesKey == "" ) ? "AES OFF" : "AES ON" );
    ui->statusBar->addPermanentWidget(aesLabel);

    cacheLabel = new QLabel(this);
    cacheLabel->setText( "Cache: " + m_CachePath );
    if ( !QDir(m_CachePath).exists() ) {
        cacheLabel->setStyleSheet( "background-color : red" );
    }
    ui->statusBar->addPermanentWidget(cacheLabel);

    storageLabel = new QLabel(this);
    storageLabel->setText( "Storage: " + m_FileStorage );
    if ( !QDir(m_FileStorage).exists() ) {
        storageLabel->setStyleSheet( "background-color : red" );
    }
    ui->statusBar->addPermanentWidget(storageLabel);

    tempLabel = new QLabel(this);
    tempLabel->setText( "Temp: " + m_TempPath );
    if ( !QDir(m_TempPath).exists() ) {
        tempLabel->setStyleSheet( "background-color : red" );
    }
    ui->statusBar->addPermanentWidget(tempLabel);

    internetLabel = new QLabel(this);
    internetLabel->setText("Internet:");
    ui->statusBar->addPermanentWidget(internetLabel);

    m_wwInternetLed = new QwwLed(this);
    m_wwInternetLed->setShape( QwwLed::RectangularRaised );
    m_wwInternetLed->setChecked(true);
    ui->statusBar->addPermanentWidget( m_wwInternetLed );

    QString picfilename = ":/images/images/tosec.png";

    QImage publisher;
    publisher.load( picfilename ) ;

    if ( ! publisher.isNull() ) {
        ui->lblPublisher->setPixmap(QPixmap::fromImage(publisher.scaledToHeight(ui->lblPublisher->maximumHeight())));
        ui->lblDeveloper->setPixmap(QPixmap::fromImage(publisher.scaledToHeight(ui->lblDeveloper->maximumHeight())));
    }

    QPixmap pix(":/cursor/images/cursor/amiga/amiga_original/amiga_arrow.cur");
    QCursor cur(pix,1,1);
    this->setCursor( cur );

    fillSystemCombo();

    ui->cboSystems->setCurrentText( m_lastSelectedSystem );

    on_cboSystems_currentTextChanged(ui->cboSystems->currentText());

    ui->cboHtmlLinks->setVisible( false );

    ui->cmdLink1->setHidden(true);
    ui->cmdLink2->setHidden(true);
    ui->cmdLink3->setHidden(true);
    ui->cmdLink4->setHidden(true);

    this->createTrayIcon();

    this->initYoutubeMenu();
    this->initLinkMenu();
    this->initToolsMenu();

    this->iniToolBarSystem();
    this->iniToolBarHomeComputersDigital();
    this->iniToolBarLinks();
    this->iniToolBarYoutube();

    setStartButtonMode(false);

 #ifdef _WIN32
    QString fn;
    fn = this->downloadFile(QUrl("https://youtube-dl.org/downloads/latest/youtube-dl.exe"), "", m_CachePath, true) ;
    if ( ! fn.isEmpty() ) {
        qDebug() << "set Youtube-dl" << fn;
        m_settings.saveStringSetting(m_sSettingsFile, "Executables", "Youtube-dl", fn);
    }
#endif

    /*
    SwitchButton* sbtn = new SwitchButton(this); // Default style is Style::ONOFF
    bool current = sbtn->value();
    sbtn->setValue(!current);
    */
}

void MainWindow::hoverEnter(QHoverEvent * event) {
    //qDebug() << Q_FUNC_INFO << this->objectName();
    event->accept();
}
void MainWindow::hoverLeave(QHoverEvent * event) {
    //qDebug() << Q_FUNC_INFO << this->objectName();
    event->accept();
}
void MainWindow::hoverMove(QHoverEvent * event)  {
    //qDebug() << Q_FUNC_INFO << this->objectName();
    event->accept();
}

bool MainWindow::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(e));
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(e));
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(e));
        break;
    default:
        break;
    }
    return QWidget::event(e);
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::initYoutubeMenu() {

    QStringList channels = m_settings.GetAllKeys("youtube.ini", "Channels");
    QMenu *youtubeMenu;

    QList<QMenu*> menus = menuBar()->findChildren<QMenu*>();

    foreach( QMenu* item, menus )
    {
        if (item->title().contains("Youtube")) {

            item->clear();

            delete item;
        }
    }

    if ( ! channels.isEmpty() ) {

        youtubeMenu = menuBar()->addMenu(tr("&Youtube"));

        for (int i = 0; i < channels.size(); ++i) {

            QAction *action = new QAction( channels.at(i), nullptr);

            youtubeMenu->addAction(action);
        }

        connect(youtubeMenu, SIGNAL(triggered(QAction*)), this, SLOT(youtubeMenuSelection(QAction*)));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::initToolsMenu() {

    QStringList channels = m_settings.GetAllKeys("tools.ini", "Global");
    QMenu *Menu;

    QList<QMenu*> menus = menuBar()->findChildren<QMenu*>();

    foreach( QMenu* item, menus )
    {
        if (item->title().contains("Tools")) {

            item->clear();

            delete item;
        }
    }

    if ( ! channels.isEmpty() ) {

        Menu = menuBar()->addMenu(tr("&Tools"));

        for (int i = 0; i < channels.size(); ++i) {

            QAction *action = new QAction( channels.at(i), nullptr);

            Menu->addAction(action);
        }

        connect(Menu, SIGNAL(triggered(QAction*)), this, SLOT(toolsMenuSelection(QAction*)));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::initLinkMenu() {

    QStringList channels = m_settings.GetAllKeys("link.ini", "Channels");
    QMenu *Menu;

    QList<QMenu*> menus = menuBar()->findChildren<QMenu*>();

    foreach( QMenu* item, menus )
    {
        if (item->title().contains("Hyperlinks")) {

            item->clear();

            delete item;
        }
    }

    if ( ! channels.isEmpty() ) {

        Menu = menuBar()->addMenu(tr("&Hyperlinks"));

        for (int i = 0; i < channels.size(); ++i) {

            QAction *action = new QAction( channels.at(i), nullptr);

            Menu->addAction(action);
        }

        connect(Menu, SIGNAL(triggered(QAction*)), this, SLOT(linkMenuSelection(QAction*)));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::youtubeMenuSelection(QAction* action) {

    m_currentYoutubeChannel = action->text();

    this->iniToolBarYoutube( ) ;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::linkMenuSelection(QAction* action) {

    m_currentLinkChannel = action->text();

    this->iniToolBarLinks( ) ;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::toolsMenuSelection(QAction* action) {

    QStringList arguments;

    QString program = m_settings.loadStringSetting("tools.ini", "Global", action->text());

    qDebug() << program;

    ExecuteProgram(program, arguments );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::createDirStructure() {

    QDir dir;

    m_TosecMain = m_settings.loadStringSetting(m_sSettingsFile, "General", "TosecMain");
    if ( m_TosecMain.isEmpty() || ( ! dir.exists(m_TosecMain) ) ) {
        m_TosecMain = QFileDialog::getExistingDirectory(this, tr("Where is my main space directory where the files are going to..."), ".", QFileDialog::ReadOnly);
        if ( ! m_TosecMain.isEmpty() ) {
            m_settings.saveStringSetting(m_sSettingsFile, "General", "TosecMain", m_TosecMain);
        } else {
            QMessageBox::information(this, "Information", "No valid space location specified, exiting now...");
            exit(EXIT_FAILURE);
        }
    } else {
        m_settings.saveStringSetting(m_sSettingsFile, "General", "TosecMain", m_TosecMain);
    }

    QStringList dirs = m_settings.GetAllKeys("directories.ini", "Global");

    for ( int i=0; i < dirs.count(); i++) {

        QDir dir( dirs.at(i).arg(m_TosecMain) );

        if ( !dir.exists() ) {
            qDebug() << "create directory" << dirs.at(i).arg(m_TosecMain);
            dir.mkpath( dirs.at(i).arg(m_TosecMain) );
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::dropEvent(QDropEvent *ev)
{
    QList<QUrl> urls = ev->mimeData()->urls();

    foreach(QUrl url, urls)
    {        
        if (url.toString().contains("www.youtube.com")) {

            GetYoutubeInformations( url );

        } else if (url.toString().contains("http://")) {

            if ( ! m_currentLinkChannel.isEmpty() ) {

                m_settings.saveStringSetting("link.ini", m_currentLinkChannel, url.host(), url.toString() + "|" + url.host());

                this->loadWebView(url.toString(), false, true );

            } else {
                QMessageBox::information(this, this->windowTitle(),  tr("No link channel selected!") );
                return;
            }

        } else if (url.toString().contains("https://")) {

            if ( ! m_currentLinkChannel.isEmpty() ) {

                m_settings.saveStringSetting("link.ini", m_currentLinkChannel, url.host(), url.toString() + "|" + url.host());

                this->loadWebView(url.toString(), false, true );

            } else {
                QMessageBox::information(this, this->windowTitle(),  tr("No link channel selected!") );
                return;
            }

        } else if (url.toString().contains("file://")) {

            ImportStuffPack(url.toString());

        } else {

            qDebug() << url.toString();

        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::dragEnterEvent(QDragEnterEvent *ev)
{
    ev->accept();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::loadScreenshotsTimer() {

   static int  lastIdx;
   static int  lastCoverIdx;
   static int  lastMediaIdx;

   if ( m_screenshotfilelist.count() > 0 ) {

       if ( lastIdx >= m_screenshotfilelist.count() - 1 ) {
           lastIdx = 0;
       }

       if ( lastIdx <= m_screenshotfilelist.count() - 1 ) {

           const QImage image1 ( m_screenshotfilelist.at(lastIdx) );

           if ( ! image1.isNull() ) {
               ui->lblImage1->setPixmap(QPixmap::fromImage(image1.scaledToHeight(ui->lblImage1->maximumHeight())));
               ui->lblImage1->setToolTip( m_screenshotfilelist.at(lastIdx) );
           } else {
               ui->lblImage1->clear();
           }

           lastIdx++;
       }

       if ( lastIdx >= m_screenshotfilelist.count() - 1 ) {
           lastIdx = 0;
       }

       if ( lastIdx <= m_screenshotfilelist.count() - 1 ) {

           const QImage image2 ( m_screenshotfilelist.at(lastIdx) );

           if ( ! image2.isNull() ) {
               ui->lblImage2->setPixmap(QPixmap::fromImage(image2.scaledToHeight(ui->lblImage2->maximumHeight())));
               ui->lblImage2->setToolTip( m_screenshotfilelist.at(lastIdx) );
           } else {
               ui->lblImage2->clear();
           }

           lastIdx++;
       }
   } else {
       ui->lblImage1->clear();
       ui->lblImage2->clear();
   }

   if ( m_coverfilelist.count() > 0 ) {

       if ( lastCoverIdx > m_coverfilelist.count() - 1 ) {
           lastCoverIdx = 0;
       }

       if ( lastCoverIdx <= m_coverfilelist.count() - 1 ) {

           const QImage image3 ( m_coverfilelist.at(lastCoverIdx) );

           if ( ! image3.isNull() ) {
               ui->lblCover->setPixmap(QPixmap::fromImage(image3.scaledToHeight(ui->lblCover->maximumHeight())));
               ui->lblCover->setToolTip( m_coverfilelist.at(lastCoverIdx) );
           } else {
               ui->lblCover->clear();
           }

           lastCoverIdx++;
       }

   } else {
       ui->lblCover->clear();
   }

   if ( m_mediafilelist.count() > 0 ) {

       if ( lastMediaIdx > m_mediafilelist.count() - 1 ) {
           lastMediaIdx = 0;
       }

       if ( lastMediaIdx <= m_mediafilelist.count() - 1 ) {

           const QImage image4 ( m_mediafilelist.at(lastMediaIdx) );

           if ( ! image4.isNull() ) {
               ui->lblMedia->setPixmap(QPixmap::fromImage(image4.scaledToHeight(ui->lblMedia->maximumHeight())));
               ui->lblMedia->setToolTip( m_mediafilelist.at(lastMediaIdx) );
           } else {
               ui->lblMedia->clear();
           }

           lastMediaIdx++;
       }

   } else {
       ui->lblMedia->clear();
   }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuToolNews(const QPoint& pos) {

    QStringList links = this->scrollText->getLinkList();
    QPoint globalPos = ui->toolNews->mapToGlobal(pos);

    QMenu myMenu;

    foreach(QString link, links ){
        myMenu.addAction( link.split("|").at(0).trimmed() );
    }

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( ! selectedItem ) {
        return;
    }

    foreach(QString link, links ) {
        if ( link.contains( selectedItem->text() ) ) {
            this->loadWebView( link.split("|").at(1).trimmed() ) ;
        }
    }
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuToolBarHomeComputersDigital(const QPoint& pos) {

    QAction* action = ui->toolHomeComputersDigital->actionAt(pos);

    if ( ! action ) {
        return;
    }

    qDebug() << action->text();

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuToolBarYoutube(const QPoint& pos) {

    QPoint globalPos = ui->toolBarYoutube->mapToGlobal(pos);

    QMenu myMenu;

    myMenu.addAction("remove entry");
    myMenu.addSeparator();
    myMenu.addAction("set channel as default");
    myMenu.addAction("create new channel");
    myMenu.addAction("delete channel");
    myMenu.addSeparator();
    myMenu.addAction("open extern");

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( ! selectedItem ) {
        return;
    }

    if ( selectedItem->text().contains("set channel as default") ) {

            m_settings.saveStringSetting("youtube.ini", "Global", "defaultChannel", m_currentYoutubeChannel );

            QMessageBox::information(this, m_applName, m_currentYoutubeChannel + tr(" set as default..."));
    }

    if ( selectedItem->text().contains("delete channel") ) {

            m_settings.Delete("youtube.ini", "Channels", m_currentYoutubeChannel );

            this->initYoutubeMenu();

            QMessageBox::information(this, m_applName, m_currentYoutubeChannel + tr(" channel removed..."));
    }

    if ( selectedItem->text().contains("create new channel") ) {

        bool ok;
        QString text = QInputDialog::getText(this, tr("Please input the new channel name..."),
                                             tr("Name:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty()) {

            m_settings.saveStringSetting("youtube.ini", "Channels", text, "" );
        }

        this->initYoutubeMenu();
    }

    QAction* action = ui->toolBarYoutube->actionAt(pos);

    if ( ! action ) {
        return;
    }

    if ( selectedItem->text().contains("remove entry") ) {

        QMessageBox::StandardButton reply = QMessageBox::question(this, m_applName, tr("are you sure to delete the entry?"), QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {

            m_settings.Delete("youtube.ini", m_currentYoutubeChannel, qvariant_cast<QString>(action->data()));

            m_settings.Delete("youtube.ini", qvariant_cast<QString>(action->data()), "baseurl");
            m_settings.Delete("youtube.ini", qvariant_cast<QString>(action->data()), "videurl");
            m_settings.Delete("youtube.ini", qvariant_cast<QString>(action->data()), "title");
            m_settings.Delete("youtube.ini", qvariant_cast<QString>(action->data()), "picture");
        }
    } else if ( selectedItem->text().contains("open extern") ) {

        QString url = m_settings.loadStringSetting("youtube.ini", qvariant_cast<QString>(action->data()), "baseurl");

        QDesktopServices::openUrl ( QUrl ( url, QUrl::TolerantMode )) ;

    }

    this->iniToolBarYoutube( ) ;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuToolBarLinks(const QPoint& pos) {

    QPoint globalPos = ui->toolBarLinks->mapToGlobal(pos);

    QMenu myMenu;

    myMenu.addAction("remove entry");
    myMenu.addAction("modify entry");
    myMenu.addSeparator();
    myMenu.addAction("set channel as default");
    myMenu.addAction("create new channel");
    myMenu.addAction("delete channel");
    myMenu.addSeparator();
    myMenu.addAction("open extern");

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( ! selectedItem ) {
        return;
    }

    if ( selectedItem->text().contains("set channel as default") ) {

        m_settings.saveStringSetting("link.ini", "Global", "defaultChannel", m_currentLinkChannel );

        QMessageBox::information(this, m_applName, m_currentLinkChannel + tr(" set as default..."));
    }

    if ( selectedItem->text().contains("delete channel") ) {

            m_settings.Delete("link.ini", "Channels", m_currentLinkChannel );

            this->initLinkMenu();

            QMessageBox::information(this, m_applName, m_currentLinkChannel + tr(" channel removed..."));
    }

    if ( selectedItem->text().contains("create new channel") ) {

        bool ok;
        QString text = QInputDialog::getText(this, tr("Please input the new channel name..."),
                                             tr("Name:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty()) {

            m_settings.saveStringSetting("link.ini", "Channels", text, "" );
        }

        this->initLinkMenu();
    }

    QAction* action = ui->toolBarLinks->actionAt(pos);

    if ( ! action ) {
        return;
    }

    qDebug() << selectedItem->text();

    if ( selectedItem->text().contains("remove entry") ) {

        QMessageBox::StandardButton reply = QMessageBox::question(this, m_applName, tr("are you sure to delete the entry?"), QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            m_settings.Delete("link.ini", m_currentLinkChannel, qvariant_cast<QString>(action->data()));
        }

    } else if ( selectedItem->text().contains("modify entry") ) {

        bool ok;
        QString text = QInputDialog::getText(this, this->windowTitle(),
                                             tr("Title:"), QLineEdit::Normal,
                                             action->text(), &ok);
        if ( ok && !text.isEmpty() && !text.isEmpty() && !m_currentLinkChannel.isEmpty() ) {
            m_settings.saveStringSetting("link.ini", m_currentLinkChannel, qvariant_cast<QString>(action->data()), action->toolTip() + "|" + text );
        }

    } else if ( selectedItem->text().contains("open extern") ) {

        QDesktopServices::openUrl ( QUrl ( action->toolTip(), QUrl::TolerantMode )) ;

    }

    this->iniToolBarLinks();
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuRomTable(const QPoint& pos) {

    QList<QTableWidgetItem*> items = ui->tableWidgetInfo->selectedItems();

    // for most widgets
    QPoint globalPos = ui->tableWidgetInfo->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;

    if ( m_GridMode == 2 ) { // ROM List

        if ( items.count() > 0 ) {

            if ( items.count() > 1 ) {
                myMenu.addAction("Build Rom Set");
                myMenu.addAction("Build Variants Set");
            }

            myMenu.addAction("Release Rom Set");
            myMenu.addAction("Explorer");
            myMenu.addAction("HexEditor");

            myMenu.addSeparator();

            if ( items[1]->text().contains( QRegExp("adf|ADF|d64|D64|d71|D71|d81|D81|x64|X64|g64|G64") ) ) {
                myMenu.addAction("Disk Contents");
            }

            if ( ui->cboSystems->currentText().contains("Commodore Amiga") ) {
                if ( items[1]->text().contains( QRegExp("rom|ROM") ) ) {
                    myMenu.addAction("AmiKick");
                }
            }
        }
    } else if ( ( m_GridMode == 1 ) || ( m_GridMode == 3 ) ) { // System List / System Zähler

        if ( items.count() > 0 ) {

            myMenu.addAction("Build upload zip files");
            myMenu.addAction("Build stuffpack zip files");

        }
    }

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( items.count() > 0 && selectedItem ) {

        if ( selectedItem->text().contains("Build Rom Set") ) {

            BuildRomSet();

        } else if ( selectedItem->text().contains("Build Variants Set") ) {

            BuildVariantsSet();

        } else if ( selectedItem->text().contains("Release Rom Set") ) {

            ReleaseRomSet();

        } else if ( selectedItem->text().contains("HexEditor") ) {

            getHexEditor();

        } else if ( selectedItem->text().contains("Explorer") ) {

            rom_type rom;

            if ( m_db.selectRomData( items[0]->toolTip().toInt(), rom ) ) {

                //QString storePath = m_FileStorage + rom.SYSTEM + "/" + rom.SETNAME + "/" + rom.TITLE;
                QString storePath = m_FileStorage + rom.SYSTEM ;

                ExecuteProgram("explorer.exe", QStringList() << storePath.replace("/","\\")  );
            } else {
                ExecuteProgram("explorer.exe", QStringList() << items[0]->toolTip().replace("/","\\") );
            }

        } else if ( selectedItem->text().contains("Disk Contents") ) {

            getDiskInfo();

        } else if ( selectedItem->text().contains("AmiKick") ) {

            getAmiKickRomInfo();

        } else if ( selectedItem->text().contains("Build upload zip files") ) {

            if ( m_GridMode == 1 ) { // System overview
                this->buildUploadZipFiles(items[1]->text(), "");
            }

            if ( m_GridMode == 3 ) { // Set overview
                this->buildUploadZipFiles(ui->cboSystems->currentText(), items[0]->text());
            }

        } else if ( selectedItem->text().contains("Build stuffpack zip files") ) {

            if ( m_GridMode == 1 ) { // System overview
                this->buildStuffpackZipFiles(items[1]->text(), "");
            }

            if ( m_GridMode == 3 ) { // Set overview
                this->buildStuffpackZipFiles(ui->cboSystems->currentText(), items[0]->text());
            }

        } else {
            // nothing was chosen
        }
    }
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuRomInfo(const QPoint& pos) {

    // for most widgets
    QPoint globalPos = ui->tableWidget->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("save setting");
    myMenu.addSeparator();
    myMenu.addAction("publish stuffpack");
    myMenu.addAction("retrieve stuffpack");
    myMenu.addAction("download stuffpack");
    myMenu.addAction("open stuffpack editor");
    myMenu.addAction("open stuffpack config file");
    myMenu.addAction("clean stuffpack directory");
    myMenu.addSeparator();
    myMenu.addAction("copy text to clipboard");
    myMenu.addSeparator();
    myMenu.addAction("search text at google");
    myMenu.addAction("search text at youtube");
    myMenu.addAction("search text at mobygames");
    // ...

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( ! selectedItem ) {
        return;
    }

    if ( selectedItem->text().contains("save setting") ) {

        StoreRomParameter();

    } else if ( selectedItem->text().contains("publish stuffpack") ) {

        QTableWidgetItem *sys,*sha1 = new QTableWidgetItem();

        sys = ui->tableWidget->item(0, 1);
        sha1 = ui->tableWidget->item(6, 1); // SHA1

        MakeStuffPack(sys->text(), sha1->text());

    } else if ( selectedItem->text().contains("download stuffpack") ) {

        QTableWidgetItem *s = new QTableWidgetItem();

        s = ui->tableWidget->item(17, 1); // ID

        loadStuffPackContents(s->text().toInt());

    } else if ( selectedItem->text().contains("retrieve stuffpack") ) {

        QTableWidgetItem *s = new QTableWidgetItem();

        s = ui->tableWidget->item(6, 1); // SHA1

        RetrieveStuffPack(s->text());

    } else if ( selectedItem->text().contains("open stuffpack editor") ) {

        QTableWidgetItem *sys,*set,*sha, *tit = new QTableWidgetItem();

        sys = ui->tableWidget->item(0, 1); // System
        set = ui->tableWidget->item(1, 1); // Set
        sha = ui->tableWidget->item(6, 1); // Sha
        tit = ui->tableWidget->item(4, 1); // Title

        QString ss = m_TosecMain + "/Stuffpacks/" + sys->text() + "/" + sha->text() + "/";

        QDir dir;
        dir.mkpath(ss);

        QString infoFile = ss + "info.txt";
        QFileInfo fi;
        fi.setFile( infoFile );

        if ( ! fi.exists() ) {

            QFile file( infoFile );
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;

            QTextStream out(&file);
            out << "[Global]" << "\n";
            out << "wiki=" << "\n";
            out << "video=" << "\n";
            out << "[Cover]" << "\n\n";
            out << "[Media]" << "\n\n";
            out << "[Screenshot]" << "\n";

            file.close();
        }

        StuffPackEdit *dialog = new StuffPackEdit();

        dialog->show();

        dialog->setStuffPackIniFile(infoFile);
        dialog->setDialogCaption(tit->text());

    } else if ( selectedItem->text().contains("open stuffpack config file") ) {

        QTableWidgetItem *sys,*set,*sha = new QTableWidgetItem();

        sys = ui->tableWidget->item(0, 1); // System
        set = ui->tableWidget->item(1, 1); // Set
        sha = ui->tableWidget->item(6, 1); // Sha

        QString ss = m_TosecMain + "/Stuffpacks/" + sys->text() + "/" + sha->text() + "/";

        QDir dir;
        dir.mkpath(ss);

        QString infoFile = ss + "info.txt";
        QFileInfo fi;
        fi.setFile( infoFile );

        if ( ! fi.exists() ) {

            QFile file( infoFile );
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;

            QTextStream out(&file);
            out << "[Global]" << "\n";
            out << "wiki=" << "\n";
            out << "video=" << "\n";
            out << "[Cover]" << "\n\n";
            out << "[Media]" << "\n\n";
            out << "[Screenshot]" << "\n";

            file.close();
        }

        QDesktopServices::openUrl ( QUrl ( "file:///" + ss + "info.txt", QUrl::TolerantMode )) ;

    } else if ( selectedItem->text().contains("clean stuffpack directory") ) {

        QTableWidgetItem *sys,*set,*sha = new QTableWidgetItem();

        sys = ui->tableWidget->item(0, 1); // System
        set = ui->tableWidget->item(1, 1); // Set
        sha = ui->tableWidget->item(6, 1); // Sha

        QString ss = m_TosecMain + "/Stuffpacks/" + sys->text() + "/" + sha->text() + "/";

        m_screenshotfilelist.clear();
        m_soundtracklist.clear();
        m_mediafilelist.clear();
        m_coverfilelist.clear();

        this->clearDir(ss + "cover", false, false);
        this->clearDir(ss + "media", false, false);
        this->clearDir(ss + "screenshot", false, false);
        this->clearDir(ss + "soundtrack", false, false);

    } else if ( selectedItem->text().contains("copy text to clipboard") ) {

        QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();

        if ( items.count() > 0 ) {

            QClipboard *p_Clipboard = QApplication::clipboard();
            p_Clipboard->setText( items.at(1)->text() );
        } else {
            QMessageBox::information(this, "Information", "please select an item");
        }

    } else if ( selectedItem->text().contains("search text at google") ) {

        QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();

        if ( items.count() > 0 ) {

            QString url = QString ( m_settings.loadStringSetting(m_sSettingsFile, "WebSearch", "google") ).arg(items.at(1)->text(), "https://www.google.de/search?q=%1");

            m_settings.saveStringSetting(m_sSettingsFile, "WebSearch", "google", url);

            qDebug() << url;

            QDesktopServices::openUrl( QUrl( url ));
        } else {
            QMessageBox::information(this, "Information", "please select an item");
        }

    } else if ( selectedItem->text().contains("search text at youtube") ) {

        QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();

        if ( items.count() > 0 ) {

            QString url = QString ( m_settings.loadStringSetting(m_sSettingsFile, "WebSearch", "youtube") ).arg(items.at(1)->text(), "https://www.youtube.com/results?search_query=%1");

            m_settings.saveStringSetting(m_sSettingsFile, "WebSearch", "youtube", url);

            qDebug() << url;

            QDesktopServices::openUrl(QUrl( url ));
        } else {
            QMessageBox::information(this, "Information", "please select an item");
        }

    } else if ( selectedItem->text().contains("search text at mobygame") ) {

        QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();

        if ( items.count() > 0 ) {

            QString url = QString ( m_settings.loadStringSetting(m_sSettingsFile, "WebSearch", "mobygames") ).arg(items.at(1)->text(), "http://www.mobygames.com/search/quick?q=%1");

            m_settings.saveStringSetting(m_sSettingsFile, "WebSearch", "mobygames", url);

            qDebug() << url;

            QDesktopServices::openUrl(QUrl( url ));
        } else {
            QMessageBox::information(this, "Information", "please select an item");
        }

    } else {
        // nothing was chosen
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuSoftwareTable(const QPoint& pos) {

    if ( ! m_Item ) {
        return;
    }

    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    QVariantList values;
    QStringList arglist;
    QString line;

    // for most widgets
    QPoint globalPos = ui->listWidget->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    //myMenu.addAction("delete");
    myMenu.addAction("select gamebase database");
    myMenu.addAction("publish ranking");
    myMenu.addAction("import ranking");
    myMenu.addAction("mark item");
    myMenu.addAction("unmark item");
    // ...

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( items.count() > 0 && selectedItem ) {

       if ( selectedItem->text().contains("delete") ) {

            QMessageBox::StandardButton reply = QMessageBox::question(this, m_applName, tr("are you sure to delete the entry?"), QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes) {

                for(int i = 0; i < items.count(); i++) {

                    QListWidgetItem *item = items[i];
                    values.clear();

                    values << item->text() ;

                    if ( m_db.deleteSetData( values ) ) {

                        QMessageBox::information(this, m_applName,  item->text() + tr(" deleted!") );

                        fillSystemCombo();
                    }
                }
            }

       } else if ( selectedItem->text().contains("publish ranking") ) {

           QApplication::setOverrideCursor(Qt::WaitCursor);

           QList<rom_type> roms;
           QString search = "'%%'";
           QString fileName;

           fileName = "../Rankings/" + m_Item->toolTip() + ".txt";

           roms = m_db.getSoftwareNames(ui->cboSystems->currentText(), m_Item->toolTip(), 8, search, 0);

           if ( roms.size() > 0 ) {

               QFile file(fileName);
               if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream out(&file);

               for (int i = 0; i < roms.size(); ++i) {

                   out << roms.at(i).SHA << "|" << roms.at(i).RANKING << "|" << roms.at(i).RATEING << "|" << roms.at(i).ROMSET << endl;
               }

               file.close();

               QMessageBox::information(this, this->windowTitle(),  tr("Ranking saved to ") + fileName );

           } else {

               QMessageBox::information(this, this->windowTitle(),  tr("nothing to publish!") );
           }

           QApplication::restoreOverrideCursor();

       } else if ( selectedItem->text().contains("import ranking") ) {

           QApplication::setOverrideCursor(Qt::WaitCursor);

           QString fileName;
           fileName = "../Rankings/" + m_Item->toolTip() + ".txt";

           QFile file( fileName );
           if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
               QApplication::restoreOverrideCursor();
               QMessageBox::information(this, this->windowTitle(),  tr("Ranking file not found! - ") + fileName );
               return;
           }

           while (!file.atEnd()) {

               line = file.readLine() ;

               if ( ! line.trimmed().isEmpty() ) {

                   arglist = line.split("|");

                   values.clear();
                   values << arglist.at(0) << arglist.at(3) << "1" << arglist.at(2) << arglist.at(1);

                   qDebug() << values;

                   if ( ! m_db.updateUserRanking(values) ) {
                       qDebug() << "updateUserRanking returns FALSE";
                   }
               }
           }

           QApplication::restoreOverrideCursor();

           QMessageBox::information(this, this->windowTitle(),  tr("Ranking import done!") );

       } else if ( selectedItem->text().contains("select gamebase database") ) {

           QFile file(QFileDialog::getOpenFileName(this, "where is the mdb file?"));

           if ( file.exists() ) {

               values << file.fileName() << m_Item->text() ;

               m_settings.saveStringSetting(m_sSettingsFile, "Gamebase",  m_Item->text(), file.fileName());

               QMessageBox::StandardButton reply = QMessageBox::question(this, "Test", "update Gamebase DB with CRC codes?", QMessageBox::Yes|QMessageBox::No);

               if (reply == QMessageBox::Yes) {

                   QFile file2(QFileDialog::getExistingDirectory(this, "where are the ziped rom files?"));

                   if ( file2.exists() ) {

                       ui->widGamebase->CrcPrepareDb( file.fileName(), file2.fileName(), m_TempPath, m_db );
                   }
               }

               QMessageBox::information(this, this->windowTitle(),  tr("Gamebase settings saved to ") + m_Item->text() );
           }

       } else if ( selectedItem->text().contains("mark item") ) {

           QColor color = QColorDialog::getColor(Qt::white, this );
           if( color.isValid() ) {
              m_settings.saveStringSetting(m_sSettingsFile, "Marker",  m_Item->text(), color.name());
           }

       }  else if ( selectedItem->text().contains("unmark item") ) {

           m_settings.Delete(m_sSettingsFile, "Marker",  m_Item->text());

       }
   }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
MainWindow::~MainWindow()
{
    m_beenden = true;

    m_db.close();

    saveSettings();

    trayIcon->hide();

    delete ui;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::importDatFile() {

    int romcnt = 0;

    QString      RomSetPup = "";

    QMessageBox msgBox;

     msgBox.setText("Who is the publisher from this dat files?");

     QAbstractButton *myTosecButton = msgBox.addButton("Tosec", QMessageBox::ActionRole);
     QAbstractButton *myWhdLoadButton = msgBox.addButton("WhdLoad", QMessageBox::ActionRole);
     QAbstractButton *myDatoMaticButton = msgBox.addButton("Dat-o-Matic", QMessageBox::ActionRole);
     QAbstractButton *myCancelButton = msgBox.addButton("cancel", QMessageBox::RejectRole);

     msgBox.setIcon(QMessageBox::Question);
     msgBox.exec();

     qDebug() << msgBox.clickedButton()->text() << "selected...";

     if(msgBox.clickedButton() == myTosecButton) {
         RomSetPup = "Tosec";
     }
     if(msgBox.clickedButton() == myWhdLoadButton) {
         RomSetPup = "WhdLoad";
     }
     if(msgBox.clickedButton() == myDatoMaticButton) {
         RomSetPup = "Dat-o-Matic";
     }
     if(msgBox.clickedButton() == myCancelButton) {
         return;
     }

    QFile file(QFileDialog::getOpenFileName(this, "Open"));

    if(file.exists()) {

        QApplication::setOverrideCursor(Qt::WaitCursor);

        this->showMessage("process: " + file.fileName());

        romcnt = romcnt + m_xml.readXMLDatFile(file.fileName(), RomSetPup);

        fillSystemCombo();

        QApplication::restoreOverrideCursor();

        this->clearDir(m_CachePath, false, false, "*.cache");

        QMessageBox::information(this, this->windowTitle(),  QString("TOSEC DAT import done - %1 Roms found").arg(romcnt));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::importDatFileDir() {

    QString      filename;
    int          filecnt = 0;
    int          loopcnt = 0;
    int          romcnt = 0;
    QVariantList values;

    QString      RomSetPup = "";

    QMessageBox msgBox;

     msgBox.setText("Who is the publisher from this dat files?");

     QAbstractButton *myTosecButton = msgBox.addButton("Tosec", QMessageBox::ActionRole);
     QAbstractButton *myWhdLoadButton = msgBox.addButton("WhdLoad", QMessageBox::ActionRole);
     QAbstractButton *myDatoMaticButton = msgBox.addButton("Dat-o-Matic", QMessageBox::ActionRole);
     QAbstractButton *myCancelButton = msgBox.addButton("cancel", QMessageBox::RejectRole);

     msgBox.setIcon(QMessageBox::Question);
     msgBox.exec();

     qDebug() << msgBox.clickedButton()->text() << "selected...";

     if(msgBox.clickedButton() == myTosecButton) {
         RomSetPup = "Tosec";
     }
     if(msgBox.clickedButton() == myWhdLoadButton) {
         RomSetPup = "WhdLoad";
     }
     if(msgBox.clickedButton() == myDatoMaticButton) {
         RomSetPup = "Dat-o-Matic";
     }
     if(msgBox.clickedButton() == myCancelButton) {
         return;
     }

    QFile file(QFileDialog::getExistingDirectory(this, "Open"));

    if(file.exists()) {

       this->showMessage("processing tosec dat files...");

        QDirIterator it(file.fileName(), QDirIterator::Subdirectories);
        while (it.hasNext()) {

            filename = it.next();

            if ( filename.contains(".dat") ) {

                filecnt++;
            }
        }

        QDirIterator it2(file.fileName(), QDirIterator::Subdirectories);

        SetStatusBar(0, filecnt, loopcnt, "process " + QString("%1").arg(filecnt) + " DAT files...\n\n" + QFileInfo(filename).baseName(), true  ) ;

       this->showMessage("processing... ");

        while (it2.hasNext() && ! m_beenden ) {

            filename = it2.next();

            if ( filename.contains(".dat") ) {

                SetStatusBar(0, filecnt, loopcnt, "process " + QString("%1").arg(filecnt) + " DAT files...\n\n" + QFileInfo(filename).baseName(), false  ) ;

                const QString name = m_xml.getNameFromTosecDatFile(filename);

                values.clear();
                values << name.split("-").at(0).trimmed() << name.split("-").at(1).trimmed();

                if ( m_db.updateRomStateToObsolete(values) ) {
                    romcnt = romcnt + m_xml.readXMLDatFile(filename, RomSetPup);
                }

                this->clearDir(m_CachePath, false, false, values.at(0).toString() + ".cache" );

                loopcnt++;
            }
        }

        ResetStatusBar();

        file.close();

       this->showMessage("check and correct rom paths...");

        /*
        // -------------------------------------------------------------
        QList<QString> sha1s;
        QList<rom_type> obsolete_roms, available_roms;
        rom_type obsolete_rom, available_rom;
        QFile rom;
        QString rompath_new, rompath_old, filename;
        QVariantList values;
        QDir dir;

        // select distinct sha1 from files x where romstate <> 0 and exists (select * from files where romstate = 0 and path <> 'missing' and sha1 = x.sha1)
        sha1s = m_db.selectCorrectAbleSha1Roms();

        QString sha1;
        foreach( sha1, sha1s ) {

            qDebug() << "processing" << sha1;

            obsolete_roms =  m_db.selectObsoleteRomsBySha1(sha1);

            foreach( obsolete_rom, obsolete_roms ) {

                filename.clear();

                if ( m_tools.fileExists( obsolete_rom.PATH ) ) {

                    rompath_old = obsolete_rom.PATH;
                    filename = QFileInfo(obsolete_rom.PATH).fileName();
                    break;
                }

                if ( m_tools.fileExists( obsolete_rom.PATH + ".aes" ) ) {

                    rompath_old = obsolete_rom.PATH + ".aes";
                    filename = QFileInfo(obsolete_rom.PATH).fileName() + ".aes";
                    break;
                }

                qDebug() << "obsolete rom path" << rompath_old << filename ;
            }

            if ( ! filename.isEmpty() ) { // Valide file found....

                available_roms = m_db.selectAvaialableRomsBySha1(sha1);

                foreach( available_rom, available_roms ) {

                    rompath_new = m_FileStorage + available_rom.SYSTEM + "/" + available_rom.SETNAME + "/" + filename;

                    qDebug() << "valid rom path" << rompath_old << "new" << rompath_new;

                    if ( QFile::exists(rompath_new) ) {

                        values.clear();
                        values <<  rompath_old.remove(".aes") << available_rom.ID;

                        if ( m_db.updateRomPathById(values) ) {

                            qDebug() << "1 rom update ok!" << values ;

                            obsolete_roms.clear();
                            obsolete_roms =  m_db.selectObsoleteRomsBySha1(sha1);

                            foreach( obsolete_rom, obsolete_roms ) {

                                if ( m_db.deleteRomById(obsolete_rom.ID) ) {
                                    qDebug() << "111 obsolete rom deleted" << obsolete_rom.ID;
                                }
                            }

                        }

                    } else {

                        qDebug() << "try to copy" << rompath_old << "to" << rompath_new;

                        if ( dir.mkpath(rompath_new) ) {

                            if ( QFile::copy(rompath_old, rompath_new) || QFile::exists(rompath_new) ) {

                                values.clear();
                                values << obsolete_rom.PATH << available_rom.ID;

                                if ( m_db.updateRomPathById(values) ) {

                                    qDebug() << "2 rom update ok!" << rompath_new << available_rom.ID ;

                                    obsolete_roms.clear();
                                    obsolete_roms =  m_db.selectObsoleteRomsBySha1(sha1);

                                    foreach( obsolete_rom, obsolete_roms ) {

                                        if ( m_db.deleteRomById(obsolete_rom.ID) ) {
                                            qDebug() << "3 obsolete rom deleted" << obsolete_rom.ID;
                                        }
                                    }
                                }
                            } else {
                                qDebug() << "error copy" << rompath_old << rompath_new;
                            }
                        }  else {
                            qDebug() << "error mkpath" << rompath_new;
                        }
                    }
                }
            } else {

                obsolete_roms.clear();
                obsolete_roms =  m_db.selectObsoleteRomsBySha1(sha1);

                foreach( obsolete_rom, obsolete_roms ) {

                    if ( m_db.deleteRomById(obsolete_rom.ID) ) {
                        qDebug() << "4 obsolete rom deleted" << obsolete_rom.ID;
                    }
                }
            }
        }
        // --------------------------------------------------------------
        */

        fillSystemCombo();

       this->showMessage("tosec dat import finished...");

        QMessageBox::information(this, this->windowTitle(),  QString("TOSEC DAT import done - %1 Roms found").arg(romcnt));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::findRomFiles(QFile *file, bool verify) {

    QString      filename, newfilename, workfilename;
    int          filecnt = 0;
    int          loopcnt = 0;
    int          romfound = 0;
    QStringList  files;
    QVariantList values;
    rom_type     rom;
    QList<rom_type> roms;
    QString      storePath ;
    QDir         dir;
    QFile        destfile, sourcefile;
    QStringList  compressFile;
    bool         tosecFound;
    bool         autoImport = false;
    QString      autoImportSuffix;
    QString      AesKey;
    QString      AesTool;
    bool         doEncryption = false;
    QFileInfo    fi;
    QStringList  param;
    bool         fileIsEncrypted = false;
    QFile        scrFileName;
    QString      checksum;
    QStringList  fileParts;
    QString      work_tempPath;

    bool         renameSourceFile = false;
    bool         removeSourceFile = false;

    m_showMsgBox = true;
    int reply = QMessageBox::No;

    autoImport = m_settings.loadBoolSetting(m_sSettingsFile, "General", "autoImport");
    autoImportSuffix = m_settings.loadStringSetting(m_sSettingsFile, "General", "autoImportSuffix");
    AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
    AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

    if ( ! AesKey.isEmpty() ) {
        doEncryption = true;
    }

    if ( verify ) {
        ui->tableWidgetInfo->clear();
        ui->tableWidget->setRowCount(0);
    }

    setInfoTxt("searching for rom files in " + file->fileName(), Qt::gray, "", true);

    setInfoTxt("this can take a while...", Qt::gray, "", false);

    filecnt = countFilesInDir(file->fileName());

    setInfoTxt( QString("processing %1 rom file(s)...").arg(filecnt), Qt::gray, "", false);

    if ( ( ! verify ) && ( filecnt > 0 ) ) {

        QMessageBox msgBox;

        msgBox.setText("possible actions on source image after successfull sort in");

        QAbstractButton *myRenameButton = msgBox.addButton("rename file", QMessageBox::YesRole);
        QAbstractButton *myRemoveButton = msgBox.addButton("remove file", QMessageBox::NoRole);
        QAbstractButton *myNothingButton = msgBox.addButton("do nothing", QMessageBox::ActionRole);
        QAbstractButton *myCancelButton = msgBox.addButton("cancel", QMessageBox::RejectRole);

        msgBox.setIcon(QMessageBox::Question);
        msgBox.exec();

        qDebug() << msgBox.clickedButton()->text() << "selected...";

        if(msgBox.clickedButton() == myRenameButton) {
            renameSourceFile = true;
        }
        if(msgBox.clickedButton() == myRemoveButton) {
            removeSourceFile = true;
        }
        if(msgBox.clickedButton() == myNothingButton) {

        }
        if(msgBox.clickedButton() == myCancelButton) {
            setInfoTxt( QString("rom scan canceled"), Qt::red, "", false);
            return;
        }
    }

    SetStatusBar(0, filecnt, loopcnt,  "processing " + QString("%1").arg(filecnt) + " files... roms found: " +  QString("%1").arg(romfound), true );

    QDirIterator it2(file->fileName(), QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    while (it2.hasNext() && ! m_beenden ) {

        filename = it2.next();

        SetStatusBar(0, filecnt, loopcnt,  "processing " + QString("%1").arg(filecnt) + " files... roms found: " +  QString("%1").arg(romfound), false );

        this->showMessage("process: " + filename + " with size " + QString("%1 MB").arg(it2.fileInfo().size() /1024 /1024) );

        if ( it2.fileInfo().isFile() && ( ! it2.fileInfo().suffix().contains("sorted") ) ) {

            // Für Dateien > 512MB auf das TEMP der Platte ausweichen, hat mehr Platz!
            if ( ( it2.fileInfo().size() == 0 ) || ( it2.fileInfo().size() > 512 * 1024 * 1024 ) ) {
                work_tempPath = QStandardPaths::displayName(QStandardPaths::TempLocation);
            } else {
                work_tempPath = m_TempPath;
            }        

            if ( ! this->clearDir(work_tempPath) ) {
                qDebug() << "-E- clearDir" << work_tempPath;
                ResetStatusBar();
                return;
            }

            files.clear();

            if ( ( it2.fileInfo().suffix() == "zip" ) || (it2.fileInfo().suffix() == "aes") ) {

                fileIsEncrypted = false;

                if ( it2.fileInfo().suffix() == "aes" ) {

                    fileIsEncrypted = true;

                    param.clear();
                    param << "-d" << "-p" << AesKey << filename;

                    if ( ExecuteProgram(AesTool, param, true) )  {
                        filename = filename.remove(".aes");
                    }
                }

                qDebug() << "process zip file: " + filename;
                QCoreApplication::processEvents();

                destfile.setFileName( filename );

                if ( destfile.exists() ) {

                    qDebug() << "size of " << destfile.fileName() << destfile.size();

                    // Alle Files des Archives entpacken...
                    files = JlCompress::extractDir(destfile.fileName(), work_tempPath);

                    if ( files.isEmpty() ) {
                        qDebug() << "no files found in zip!";
                    } else {
                        if ( renameSourceFile ) {
                            destfile.rename(destfile.fileName() + "_sorted");
                        }
                        if ( removeSourceFile ) {
                            destfile.remove(destfile.fileName());
                        }
                    }

                    qDebug() << "Work.zip unpacked...";
                } else {
                    qDebug() << "Work.zip does not exists...";
                }
            } else {
                qDebug() << "process file: " + filename;
                files << filename;
            }

            tosecFound = false;

            for (int i = 0; i < files.size(); ++i) {

                QCoreApplication::processEvents();

                values.clear();

                checksum = QString::fromLatin1(fileChecksum(files.at(i), QCryptographicHash::Sha1).toHex());

                qDebug() << "-I- Checksum for: " << files.at(i) << " is SHA1: " << checksum;

                // TOSEC Daten der SHA1 Prüfsumme laden...
                roms = m_db.selectRomDataBySha1( "", checksum );

                if ( roms.count() == 0 ) {

                    if (this->m_showMsgBox) {

                        QCheckBox *cb = new QCheckBox("Don't show this messagebox again");
                        QMessageBox msgbox;

                        msgbox.setText("Rom not found in database - add to actual selection?\n\n" + m_CurrentSystem + " / " + m_CurrentSet);
                        msgbox.setIcon(QMessageBox::Icon::Question);
                        msgbox.addButton(QMessageBox::Yes);
                        msgbox.addButton(QMessageBox::No);
                        msgbox.setDefaultButton(QMessageBox::No);
                        msgbox.setCheckBox(cb);

                        QObject::connect(cb, &QCheckBox::stateChanged, [this](int state){
                            if (static_cast<Qt::CheckState>(state) == Qt::CheckState::Checked) {
                                this->m_showMsgBox = false;
                            }
                        });

                        reply = msgbox.exec();
                    }

                    autoImport = ( reply == QMessageBox::Yes);

                    if ( autoImport ) {

                        QFileInfo info = files.at(i);

                        fileParts = filename.split("/");

                        QFileInfo fi(files.at(i));

                        values << m_crc32.getCRC32(files.at(i)); // 0
                        values << m_CurrentSystem; //1 System
                        values << m_CurrentSet; // 2 Setname
                        values << fi.completeBaseName(); //3
                        values << fi.fileName(); // 4
                        values << fi.size();
                        values << QString::fromLatin1(fileChecksum(files.at(i), QCryptographicHash::Md5).toHex());
                        values << checksum;
                        values << 1;
                        values << " ";

                        if ( m_db.storeFilesData(values) ) {
                            qDebug() << fi.baseName() << "added to TOSEC as nonTosec!";
                        }
                    }
                }

                // TOSEC Daten der SHA1 Prüfsumme laden...
                roms =  m_db.selectRomDataBySha1( "", checksum );

                tosecFound = roms.count() > 0;

                if ( tosecFound ) {

                    qDebug() << roms.count() << "TOSEC entries found for SHA" << checksum;

                    foreach(rom, roms) {

                        QCoreApplication::processEvents();

                        values.clear();

                        qDebug() << "-I- TOSEC data found...";

                        //storePath = m_FileStorage + rom.SYSTEM + "/" + rom.SETNAME;
                        storePath = m_FileStorage + rom.SYSTEM ;
                        newfilename = QDir::toNativeSeparators(storePath + "/" + rom.SHA + ".zip");

                        // File-Pfad speichern
                        values << newfilename << rom.ID;
                        if ( m_db.updateRomPathById(values) ) {

                            qDebug() << "-I- update rom path success..." << values;

                            romfound++;

                            fi.setFile( rom.NAME );
                            workfilename = work_tempPath + "/" + fi.fileName();

                            // ROM Namen dem TOSEC Namen anpassen
                            scrFileName.setFileName(files.at(i));
                            if ( ! scrFileName.rename(workfilename) ) {
                                qDebug() << "-E- unable to rename the file..." << files.at(i) << " to " << workfilename << " error " << scrFileName.errorString();
                            }

                            files[i] = workfilename;

                            filename = work_tempPath + "/" + rom.TITLE + ".zip";

                            compressFile.clear();
                            compressFile.append(workfilename);

                            bool ende = false;
                            int  retrycnt = 0;

                            while ( ! ende ) {

                                destfile.setFileName( filename ) ;
                                destfile.remove();

                                if ( JlCompress::compressFiles ( filename, compressFile ) ) {

                                    qDebug() << "compress for file " + filename + " ok...";
                                    ende = true;

                                } else {

                                    qDebug() << "compress for file " + filename + " error...";
                                    qDebug() << "Files to compress" << compressFile;

                                    retrycnt++;

                                    if ( retrycnt >= 3 ) {

                                        QMessageBox msgBox;
                                        msgBox.setText("Something went wrong... ");
                                        msgBox.setInformativeText("compress of file " + filename + " error");
                                        msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Ignore | QMessageBox::Cancel);
                                        msgBox.setDefaultButton(QMessageBox::Retry);
                                        int ret = msgBox.exec();

                                        switch (ret) {
                                          case QMessageBox::Retry:
                                              // Retry was clicked
                                              break;
                                          case QMessageBox::Cancel:
                                              // Cancel was clicked
                                              m_beenden = true;
                                              ende = true;
                                              break;
                                          case QMessageBox::Ignore:
                                              // Ignore was pressen... continue with next one...
                                              ende = true;
                                              break;
                                          default:
                                              // should never be reached
                                              break;
                                        }
                                    }
                                }
                            }

                            // prüfen, ob das ROM schon im Storage liegt....
                            destfile.setFileName( newfilename ) ;
                            sourcefile.setFileName ( filename ) ;

                            if ( sourcefile.exists() ) {

                                if ( ( ( ! destfile.exists() ) || ( destfile.size() != sourcefile.size() ) ) || ( doEncryption ) ) {

                                    destfile.remove();

                                    dir.mkpath( storePath );

                                    if ( destfile.copy( filename, newfilename ) ) {

                                        qDebug() << sourcefile << "copied to ..." + newfilename;

                                        sourcefile.remove();

                                        if ( doEncryption ) {

                                            param.clear();
                                            param << "-e" << "-p" << AesKey << newfilename;

                                            if ( ExecuteProgram(AesTool, param, true) ) {

                                                fi.setFile(newfilename + ".aes" );

                                                if ( fi.exists() ) {

                                                    destfile.setFileName(newfilename);
                                                    if ( destfile.remove() ) {
                                                        qDebug() << newfilename << "removed...";
                                                    }
                                                }
                                            } else {
                                                qDebug() << "ExecuteProgram fails... " << param;
                                                m_beenden = true;
                                            }
                                        }
                                    } else  {
                                        qDebug() << "unable to copy destfile to ... " + newfilename;
                                        QMessageBox::information(this, this->windowTitle(), "unable to copy destfile to ... " + newfilename );
                                        m_beenden = true;
                                    }
                                } else {
                                    qDebug() << newfilename + " already there...";
                                }

                            } else {
                                qDebug() << filename + " not found... nothing to store...";
                            }
                        } else {
                            qDebug() << "-E- updateRomPath faild..." << values;
                        }

                        QCoreApplication::processEvents();

                    } // foreach

                } else {
                    qDebug() << "-I- TOSEC not found for SHA1" << checksum;
                }
            }

            if ( verify && !tosecFound ) {            
                setInfoTxt ( "TOSEC not found for: " + it2.fileInfo().fileName(),
                             Qt::red,
                             filename, false ) ;
            } else if ( verify && tosecFound ) {            
                romfound++;
            }

            loopcnt++;

        } else {

            if ( ! it2.fileInfo().isDir() ) {
                loopcnt++;
            }
        }

        QCoreApplication::processEvents();
    }

    if ( verify ) {
        setInfoTxt( tr("Rom scan finished - files/matched: ") + QString("%1").arg(filecnt) + "/" + QString("%1").arg(romfound) , Qt::gray, "", false);
    }

    // Storage hat sich geändert - beim nächsten Zugriff den Cache neu aufbauen....
    this->clearDir(m_CachePath, false, false, "*.cache");

    if ( ! this->clearDir(work_tempPath) ) {
        qDebug() << "-E- clearDir" << work_tempPath;
    }

    QMessageBox::information(this, this->windowTitle(),  tr("Rom scan finished - files/matched: ") + QString("%1").arg(filecnt) + "/" + QString("%1").arg(romfound) );

    ResetStatusBar();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool MainWindow::clearDir( const QString path, bool secure, bool onlyTemp, QString prefix )
{
    QStringList filters;

    filters << prefix;

    if ( ! path.toUpper().contains("TEMP") && onlyTemp ) {
        qDebug() << "try to delete none temp dir!!!" << path;
        return false;
    }

    qDebug() << "cleanDir" << path << prefix;

    bool cleanup = true;
    static bool ignore = false;

    QDir dir( path );

    dir.setFilter( QDir::NoDotAndDotDot | QDir::Files );
    dir.setNameFilters( filters );

    if ( ! ignore ) {

        if ( dir.count() >= 20 && secure) {

            QMessageBox::StandardButton reply = QMessageBox::question(this, this->windowTitle(), QString("There are more than 20 files in the \n\n" + path + " directory...\n\nDo you realy want to delete this files?"), QMessageBox::Yes|QMessageBox::No|QMessageBox::Ignore);

            if (reply == QMessageBox::No) {
                cleanup = false;
            }
            if (reply == QMessageBox::Ignore) {
                ignore = true;
            }
        }
    }   

    if ( cleanup ) {

        foreach( QString dirItem, dir.entryList() )
        {
            QFile::setPermissions( dir.absoluteFilePath(dirItem), QFile::permissions( dir.absoluteFilePath(dirItem)) | QFile::WriteUser);
            dir.remove( dirItem );
        }

        dir.setFilter( QDir::NoDotAndDotDot | QDir::Dirs );
        foreach( QString dirItem, dir.entryList() )
        {
            QDir subDir( dir.absoluteFilePath( dirItem ) );
            subDir.removeRecursively();
        }
    }

    return true;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::getCRC32() {

    QFile file(QFileDialog::getOpenFileName(this, "Open"));

    if ( file.exists() ) {

        QMessageBox::information(this, this->windowTitle(),  tr("CRC32 for this file is: ") + m_crc32.getCRC32(file.fileName()));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::quit() {

    m_beenden = true;

    qApp->quit();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::fillSystemCombo() {

    QStringList systems;
    QString     lastSystem;
    int         value;

    ui->cboSystems->blockSignals(true);

    lastSystem = ui->cboSystems->currentText();

    ui->cboSystems->clear();

    systems = m_db.getSystemNames();

    for (int i = 0; i < systems.size(); ++i) {

        value = m_settings.loadIntSetting(m_sSettingsFile, "Hidden Systems", QString(systems.at(i) ));

        if ( value == Qt::Checked ) {

            ui->cboSystems->addItem( systems.at(i) );
        }
    }

    ui->cboSystems->setCurrentText( lastSystem );

    ui->cboSystems->blockSignals(false);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::fillSetNameListView(QString system, bool onlyValid) {

    QList<QString>  sets;
    QVariantList    values;
    QString         setName;
    QString         marker;
    QString         itemText;
    int             selectedRow = 0;

    qDebug() << "fillSetNameListView" << system << onlyValid;

    ui->listWidget->clear();

    values << system << onlyValid;

    QString LastSelectedItem = m_settings.loadStringSetting("system.ini", ui->cboSystems->currentText(), "LastSelectedItem");

    CHECKTIME ( sets = m_db.getSetNames(values); );

    for (int i = 0; i < sets.size(); ++i) {

        setName = sets.at(i);

        itemText = setName.remove(system + " - ");

        QListWidgetItem *item = new QListWidgetItem();

        marker = m_settings.loadStringSetting(m_sSettingsFile, "Marker",  itemText);

        if ( ! marker.isEmpty() )  {
            item->setBackgroundColor( marker );
        }

        item->setToolTip( sets.at(i) );
        item->setText(itemText );

        if ( setName == LastSelectedItem ) {
            item->setSelected(true);
            selectedRow = i;
        }

        ui->listWidget->addItem( item );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::fillSoftwareTableView(QString system, QString setname) {

    QList<rom_type> systems;
    QString search = "'%%'";

    ui->listWidget->clear();

    CHECKTIME ( systems = m_db.getSoftwareNames(system, setname, m_actSelectionMode, search, 0); );

    for (int i = 0; i < systems.size(); ++i) {

        ui->listWidget->addItem( systems.at(i).NAME );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::loadRomList(QString RomSet) {

    qDebug() << "loadRomList" << RomSet;

    m_GridMode = 2; // RomList

    QList<rom_type> software;
    bool validrom = false;
    bool validcue = false;
    bool missingrom = false;
    gamebase_type  gamebase;
    QString info;
    QImage publisher;
    int inStorageCount = 0;

    if ( RomSet.isEmpty() ) {
        QMessageBox::information(this, this->windowTitle(),  tr("no item selected") );
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);

    QString picfilename = ":/images/images/tosec.png";
    publisher.load( picfilename ) ;

    if ( ! publisher.isNull() ) {
        ui->lblPublisher->setPixmap(QPixmap::fromImage(publisher.scaledToHeight(ui->lblPublisher->maximumHeight())));
        ui->lblDeveloper->setPixmap(QPixmap::fromImage(publisher.scaledToHeight(ui->lblDeveloper->maximumHeight())));
    }

    m_screenshotfilelist.clear();
    m_soundtracklist.clear();
    m_mediafilelist.clear();
    m_coverfilelist.clear();

    ui->tableWidgetInfo->clear();
    ui->tableWidget->setRowCount(0);
    ui->lblImage1->clear();
    ui->lblImage2->clear();
    ui->lblCover->clear();
    ui->lblMedia->clear();
    ui->gpSelection->setHidden(false);
    ui->widGamebase->setHidden(true);

    ui->cmdSoundtrack->setVisible(false);
    ui->cmdYoutubeVideo->setVisible(false);

   this->showMessage("query database...");
    QCoreApplication::processEvents();

    if (ui->edtSearch->text().trimmed() == "") {
        ui->edtSearch->setText("%");
    }

    if (ui->chkSystemSearch->isChecked()) {

        software = m_db.getSoftwareNames(ui->cboSystems->currentText(), RomSet, 6, ui->edtSearch->text(), 0);

    } else {

        software = m_db.getSoftwareNames(ui->cboSystems->currentText(), RomSet, m_actSelectionMode, ui->edtSearch->text(), ui->chkGamebase->isChecked());

        if ( software.size() == 0 ) {

            // wenn wir nichts gefunden haben, dann Alle laden
            m_actSelectionMode = 0;

            ui->cmd09->setStyleSheet( "" );
            ui->cmdAI->setStyleSheet( "" );
            ui->cmdJR->setStyleSheet( "" );
            ui->cmdSZ->setStyleSheet( ""  );
            ui->cmdAll->setStyleSheet( "background-color: orange;"  );
            ui->cmdFavorite->setStyleSheet( ""  );

            software = m_db.getSoftwareNames(ui->cboSystems->currentText(), RomSet, m_actSelectionMode, ui->edtSearch->text(), ui->chkGamebase->isChecked());
        }
    }

    ui->tableWidgetInfo->horizontalHeader()->setVisible(true);
    ui->tableWidgetInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidgetInfo->verticalHeader()->setVisible(false);
    ui->tableWidgetInfo->setColumnCount(5);
    ui->tableWidgetInfo->setRowCount(0);
    ui->tableWidgetInfo->setItemDelegate(new StarDelegate);

    ui->tableWidgetInfo->setUpdatesEnabled(false);

    QTableWidgetItem *header0 = new QTableWidgetItem();
    header0->setText("Ranking");
    ui->tableWidgetInfo->setHorizontalHeaderItem(0,header0);
    QTableWidgetItem *header1 = new QTableWidgetItem();
    header1->setText("Rating");
    ui->tableWidgetInfo->setHorizontalHeaderItem(1,header1);
    QTableWidgetItem *header2 = new QTableWidgetItem();
    header2->setText("Favorit");
    ui->tableWidgetInfo->setHorizontalHeaderItem(2,header2);
    QTableWidgetItem *header3 = new QTableWidgetItem();
    header3->setText("Suffix");
    ui->tableWidgetInfo->setHorizontalHeaderItem(3,header3);
    QTableWidgetItem *header4 = new QTableWidgetItem();
    header4->setText("Title");
    ui->tableWidgetInfo->setHorizontalHeaderItem(4,header4);

    int counter = 0;
    int missing = 0;

    for (int i = 0; i < software.size(); ++i) {        

        if ( ( i % 100 ) == 0 ) {

           this->showMessage( QString("loading grid... %1 from %2").arg(i+1).arg(software.size()) );
            QCoreApplication::processEvents();
        }

        validrom = false;
        validcue = false;
        missingrom = false;

        info = "";

        QTableWidgetItem *item = new QTableWidgetItem();

        if ( software.at(i).PATH == "missing" )  {

            QString storePath = m_FileStorage + software.at(i).SYSTEM + "/" + software.at(i).SHA + ".zip" ;

            if ( m_tools.fileExists( storePath ) ||
                 m_tools.fileExists( storePath + ".aes" )) {
                if (m_db.updateRomPathById( QVariantList() << storePath << software.at(i).ID ) ) {
                    validrom = true;
                }
            } else {

                missing++;
                missingrom=true;

                item->setBackgroundColor( Qt::red );
            }
        } else {

            if ( ui->chkOnlyValid->isChecked() ) {
                if ( m_tools.fileExists( software.at(i).PATH ) ||
                     m_tools.fileExists( software.at(i).PATH + ".aes" )) {
                    validrom = true;
                } else {
                    m_db.updateRomPath( QVariantList() << "missing" << software.at(i).SHA );
                }
            }

            // Gamebase nur für Favoriten prüfen
            if ( m_actSelectionMode == 5 ) {

                QString gamebasedb = m_settings.loadStringSetting(m_sSettingsFile, "Gamebase",  RomSet);

                if ( ! gamebasedb.isEmpty() ) {

                    gamebase = ui->widGamebase->GetGameBaseInfos(gamebasedb, QString(software.at(i).CRC));

                    if ( gamebase.Games_name.trimmed() != "" ) {
                        info = " (GB)";
                    }
                }
            }
        }

        if ( software.at(i).NAME.contains("cue") ) {
            validcue = true;
        }

        if ( ( ( ui->chkOnlyValid->isChecked() && validrom ) || ( !ui->chkOnlyValid->isChecked() ) ) &&
             ( ( ui->chkOnlyCue->isChecked() && validcue ) || ( !ui->chkOnlyCue->isChecked() ) ) &&
             ( ( ui->chkOnlyMissing->isChecked() && missingrom ) || ( !ui->chkOnlyMissing->isChecked() ) )
           ) {

            ui->tableWidgetInfo->insertRow( counter );

            // Ranking
            QTableWidgetItem *itemRanking = new QTableWidgetItem;
            itemRanking->setText( QString("%1").arg(software.at(i).RANKING) );
            ui->tableWidgetInfo->setItem( counter, 0, itemRanking);

            // Rating
            QTableWidgetItem *itemRating = new QTableWidgetItem;
            itemRating->setData(0, QVariant::fromValue(StarRating( software.at(i).RATEING )));
            ui->tableWidgetInfo->setItem( counter, 1, itemRating);

            // Favorit
            if ( software.at(i).FAVORIT != 0 ) {
                item->setIcon(QIcon(":/icon/farious/blue/images/farious/blue/star.ico"));
            }                      

//            item->setText( QString(software.at(i).TITLE) + info );
//            item->setToolTip( QString("%1").arg(software.at(i).ID) );

            ui->tableWidgetInfo->setItem( counter, 2, item );

            // Suffix
            QTableWidgetItem *itemIcon = new QTableWidgetItem;
            itemIcon->setIcon(QPixmap("T:/Tools/file-icon-vectors-1.0/dist/icons/classic/cue.svg"));
            itemIcon->setText( QFileInfo(software.at(i).NAME).suffix() );
            ui->tableWidgetInfo->setItem( counter, 3, itemIcon);

            // Title
            QTableWidgetItem *itemName = new QTableWidgetItem;

            if ( validrom ) {

                if ( software.at(i).NONTOSEC == 0 ) {
                    itemName->setBackgroundColor( Qt::green );
                } else {
                    itemName->setBackgroundColor( Qt::yellow );
                }

                inStorageCount++;
            }

            itemName->setToolTip( QString("%1").arg(software.at(i).ID) );
            itemName->setText( software.at(i).NAME );
            ui->tableWidgetInfo->setItem( counter, 4, itemName);

            counter++;
        }
    }

    ui->tableWidgetInfo->resizeColumnsToContents();
    ui->tableWidgetInfo->resizeRowsToContents();

    ui->tableWidgetInfo->setUpdatesEnabled(true);

    if ( ui->chkOnlyValid->isChecked() ) {
        ui->lblAnzRomInfo->setText( QString("%1 title loaded, %2 in storage").arg(ui->tableWidgetInfo->rowCount()).arg(inStorageCount) );
    } else {
        ui->lblAnzRomInfo->setText( QString("%1 title loaded, %2 missing files").arg(ui->tableWidgetInfo->rowCount() ).arg(missing) );
    }

    this->showMessage("");

    QApplication::restoreOverrideCursor();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::loadSettings() {

    QDir dir;

    ui->chkOnlyValid->setChecked ( m_settings.loadBoolSetting(m_sSettingsFile, "General", "OnlyValidRoms") );

    ui->chkWikiInfo->setChecked( m_settings.loadBoolSetting(m_sSettingsFile, "Wiki", "active", true ) );
    ui->chkSys->setChecked( m_settings.loadBoolSetting(m_sSettingsFile, "Sys", "active", true ) );
    ui->chkTosec->setChecked( m_settings.loadBoolSetting(m_sSettingsFile, "Tosec", "active", true ) );

    m_httpdEnabled = m_settings.loadBoolSetting(m_sSettingsFile, "General", "Httpd");
    m_ftpEnabled = m_settings.loadBoolSetting(m_sSettingsFile, "General", "Ftpd");

    m_ftpEnabled = m_settings.loadBoolSetting(INI_FILE, "Ftp", "enabled", false) ;
    m_ftpAnonymous =  m_settings.loadBoolSetting(INI_FILE, "Ftp", "anonymous", false );
    m_FTPPort = m_settings.loadStringSetting(INI_FILE, "Ftp", "port") ;
    m_FTPUser = m_settings.loadStringSetting(INI_FILE, "Ftp", "user") ;
    m_FTPPassword = m_settings.loadStringSetting(INI_FILE, "Ftp", "password");

    m_QssFile = m_settings.loadStringSetting(m_sSettingsFile, "General", "QssFile");

    m_proxyEnabled = m_settings.loadBoolSetting(m_sSettingsFile, "Proxy", "enabled");
    m_proxyUser = m_settings.loadStringSetting(m_sSettingsFile, "Proxy", "user");
    m_proxyPassword = m_settings.loadStringSetting(m_sSettingsFile, "Proxy", "password");
    m_proxyIp = m_settings.loadStringSetting(m_sSettingsFile, "Proxy", "ip");
    m_proxyPort = m_settings.loadIntSetting(m_sSettingsFile, "Proxy", "port");

    m_StuffSrvEnabled = m_settings.loadBoolSetting(m_sSettingsFile, "StuffServer", "enabled");
    m_StuffSrvUser = m_settings.loadStringSetting(m_sSettingsFile, "StuffServer", "user");
    m_StuffSrvPassword = m_settings.loadStringSetting(m_sSettingsFile, "StuffServer", "password");
    m_StuffSrvIp = m_settings.loadStringSetting(m_sSettingsFile, "StuffServer", "ip");
    m_StuffSrvPort = m_settings.loadIntSetting(m_sSettingsFile, "StuffServer", "port");

    m_FileStorage = m_settings.loadStringSetting(m_sSettingsFile, "General", "FileStorage", "/tosec/Storage/");
    if ( m_FileStorage.isEmpty() || ( ! dir.exists(m_FileStorage) ) ) {        
        m_FileStorage = QFileDialog::getExistingDirectory(this, tr("Choose ROM storage location with a lot of space"), ".", QFileDialog::ReadOnly);
        if ( ! m_FileStorage.isEmpty() ) {
            m_settings.saveStringSetting(m_sSettingsFile, "General", "FileStorage", m_FileStorage);
        } else {
            QMessageBox::information(this, "Information", "No valid rom location specified, exiting now...");
            exit(EXIT_FAILURE);
        }
    } else {
        m_settings.saveStringSetting(m_sSettingsFile, "General", "FileStorage", m_FileStorage);
    }

    m_CachePath = m_settings.loadStringSetting(m_sSettingsFile, "General", "CachePath", "/tosec/Cache/");
    if ( m_CachePath.isEmpty() || ( ! dir.exists(m_CachePath) ) ) {
        m_CachePath = QFileDialog::getExistingDirectory(this, tr("Choose cache storage location"), ".", QFileDialog::ReadOnly);
        if ( ! m_CachePath.isEmpty() ) {
            m_settings.saveStringSetting(m_sSettingsFile, "General", "CachePath", m_CachePath);
        } else {
            QMessageBox::information(this, "Information", "No valid cache location specified, exiting now...");
            exit(EXIT_FAILURE);
        }
    } else {
        m_settings.saveStringSetting(m_sSettingsFile, "General", "CachePath", m_CachePath);
    }

    m_ImageCachePath = m_settings.loadStringSetting(m_sSettingsFile, "General", "ImageCachePath", "/tosec/Cache/Images/");
    if ( m_ImageCachePath.isEmpty() || ( ! dir.exists(m_ImageCachePath) ) ) {
        m_ImageCachePath = QFileDialog::getExistingDirectory(this, tr("Choose image cache storage location"), ".", QFileDialog::ReadOnly);
        if ( ! m_ImageCachePath.isEmpty() ) {
            m_settings.saveStringSetting(m_sSettingsFile, "General", "ImageCachePath", m_ImageCachePath);
        } else {
            QMessageBox::information(this, "Information", "No valid image cache location specified, exiting now...");
            exit(EXIT_FAILURE);
        }
    } else {
        m_settings.saveStringSetting(m_sSettingsFile, "General", "ImageCachePath", m_ImageCachePath);
    }

    m_TempPath = m_settings.loadStringSetting(m_sSettingsFile, "General", "TempPath", "/tosec/Temp/");
    if ( m_TempPath.isEmpty() || ( ! dir.exists(m_TempPath) ) ) {
        m_TempPath = QFileDialog::getExistingDirectory(this, tr("Choose temp storage location"), ".", QFileDialog::ReadOnly);
        if ( ! m_TempPath.isEmpty() ) {
            m_settings.saveStringSetting(m_sSettingsFile, "General", "TempPath", m_TempPath);
        } else {
            QMessageBox::information(this, "Information", "No valid temp location specified, exiting now...");
            exit(EXIT_FAILURE);
        }
    } else {
        m_settings.saveStringSetting(m_sSettingsFile, "General", "TempPath", m_TempPath);
    }

    m_StartupsPath = m_settings.loadStringSetting(m_sSettingsFile, "General", "StartupsPath", "/tosec/Startups/");
    if ( m_StartupsPath.isEmpty() || ( ! dir.exists(m_StartupsPath) ) ) {
        m_StartupsPath = QFileDialog::getExistingDirectory(this, tr("Choose startups location"), ".", QFileDialog::ReadOnly);
        if ( ! m_StartupsPath.isEmpty() ) {
            m_settings.saveStringSetting(m_sSettingsFile, "General", "StartupsPath", m_StartupsPath);
        } else {
            QMessageBox::information(this, "Information", "No valid startups location specified, exiting now...");
            exit(EXIT_FAILURE);
        }
    } else {
        m_settings.saveStringSetting(m_sSettingsFile, "General", "StartupsPath", m_StartupsPath);
    }

    m_Stylesheet = m_settings.loadStringSetting(m_sSettingsFile, "General", "Stylesheet");
    m_lastSelectedSystem = m_settings.loadStringSetting(m_sSettingsFile, "General", "LastSelectedSystem");

    m_currentLinkChannel = m_settings.loadStringSetting("link.ini", "Global", "defaultChannel" );
    m_currentYoutubeChannel = m_settings.loadStringSetting("youtube.ini", "Global", "defaultChannel" );

    m_AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");

    //AmigaRemix Values
    _ARsliMinValue = m_settings.loadIntSetting(m_sSettingsFile, "AmigaRemix", "PageMin", 1);
    _ARsliMaxValue = m_settings.loadIntSetting(m_sSettingsFile, "AmigaRemix", "PageMax", 20);
    _ARbaseUrl = m_settings.loadStringSetting(m_sSettingsFile, "AmigaRemix", "Base", "http://www.amigaremix.com/");
    _ARurl = m_settings.loadStringSetting(m_sSettingsFile, "AmigaRemix", "Url", "http://www.amigaremix.com/remixes/%1");
    _ARdateurl = m_settings.loadStringSetting(m_sSettingsFile, "AmigaRemix", "SortByDateUrl", "http://www.amigaremix.com/remixes/sort/added/dn");
    _ARratingurl = m_settings.loadStringSetting(m_sSettingsFile, "AmigaRemix", "SortByRatingUrl", "http://www.amigaremix.com/remixes/sort/rating/up");
    _ARextension = m_settings.loadStringSetting(m_sSettingsFile, "AmigaRemix", "Ext", "mp3");

    //TheModArchiv Values
    _TMAsliMinValue = m_settings.loadIntSetting(m_sSettingsFile, "TheModArchive", "PageMin", 1);
    _TMAsliMaxValue = m_settings.loadIntSetting(m_sSettingsFile, "TheModArchive", "PageMax", 3);
    _TMAbaseUrl = m_settings.loadStringSetting(m_sSettingsFile, "TheModArchive", "Base");
    _TMAurl = m_settings.loadStringSetting(m_sSettingsFile, "TheModArchive", "Url","http://modarchive.org/index.php?request=view_by_rating_comments&query=10&page=%1#mods");
    _TMAdateurl = m_settings.loadStringSetting(m_sSettingsFile, "TheModArchive", "SortByDateUrl");
    _TMAratingurl = m_settings.loadStringSetting(m_sSettingsFile, "TheModArchive", "SortByRatingUrl");
    _TMAextension = m_settings.loadStringSetting(m_sSettingsFile, "TheModArchive", "Ext", "mod|it|xm|s3m");

    //Flashtro Values
    _FTbaseUrl = m_settings.loadStringSetting(m_sSettingsFile, "Flashtro", "base");
    _FTurl = m_settings.loadStringSetting(m_sSettingsFile, "Flashtro", "url");
    _FTextension = m_settings.loadStringSetting(m_sSettingsFile, "Flashtro", "ext");

    m_schema = m_settings.loadStringSetting(m_sSettingsFile, "General", "IconColorSchema", "blue");
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::saveSettings() {

    QSettings settings("state.ini", QSettings::IniFormat);

    settings.setValue("mainWindowGeometry", saveGeometry());
    settings.setValue("mainWindowState", saveState());

    settings.setValue("mainSplitterState", ui->splitter->saveState());
    settings.setValue("mainSplitterState2", ui->splitter_2->saveState());
    settings.setValue("mainSplitterState3", ui->splitter_3->saveState());
    settings.setValue("mainSplitterState4", ui->splitter_4->saveState());

    //QByteArray MyArray = ui->tableWidgetInfo->horizontalHeader()->saveState();
    //settings.setValue(QString("mainTableWidth%1").arg(m_GridMode), MyArray);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::scanRoms() {

    QFile file(QFileDialog::getExistingDirectory(this, "Open"));

    if(file.exists()) {

       this->showMessage("process: " + file.fileName());

        findRomFiles(&file, false);
    }

    file.close();

    fillSystemCombo();

    this->showMessage("");
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::deleteDatabase() {

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Test", "Delete Database?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {

        m_db.deleteFilesData();
    }

    fillSystemCombo();
    fillSoftwareTableView("", "");
}

QString MainWindow::getMultiRomFiles(QString system, QString setname, QString title) {

    QStringList files;
    QString     swapfiles;
    QStringList param;
    QFile       romFile;
    rom_type    rom;
    QFileInfo   fileInfo;
    bool        fileIsEncrypted = false;
    QStringList MultiRoms;

    QString AesKey  = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
    QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

    MultiRoms = m_db.selectMultiRoms(system, setname, title);

    qDebug() << "getMultiRomFiles" << MultiRoms;

    if ( ! MultiRoms.isEmpty() ) {

        foreach(QString id, MultiRoms) {

            if ( m_db.selectRomData( id.toInt(), rom ) ) {

                fileInfo.setFile( rom.NAME );

                if ( checkFileInCache( fileInfo.fileName() ) ) {

                    qDebug() << "use file from cache..." + m_CachePath + fileInfo.fileName() ;
                    files.append( m_CachePath + rom.NAME );

                    swapfiles.append( + """" + QDir::toNativeSeparators(files.at(0)) + """" + "," );

                } else {

                    romFile.setFileName(rom.PATH);
                    if ( ! romFile.exists() ) {

                        romFile.setFileName( rom.PATH + ".aes" );
                        if ( ! romFile.exists() ) {
                            QMessageBox::information(this, this->windowTitle(),  tr("ROM ZIP nicht gefunden - ") + rom.PATH );
                        } else {

                            if ( AesKey.isEmpty() ) {

                                QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );

                            } else {

                                fileIsEncrypted = true;

                                param.clear();
                                param << "-d" << "-p" << AesKey << rom.PATH + ".aes";

                                ExecuteProgram(AesTool, param, true);
                            }
                        }
                    }

                    if ( this->useFileCache() ) {
                        romFile.setFileName(m_CachePath + "/" + rom.NAME);
                    } else {
                        romFile.setFileName(m_TempPath + "/" + rom.NAME);
                    }

                    if ( ! romFile.exists() ) {

                        if ( this->useFileCache() ) {
                            files = JlCompress::extractDir(rom.PATH, m_CachePath);
                        } else {
                            files = JlCompress::extractDir(rom.PATH, m_TempPath);
                        }

                        if ( ! files.isEmpty() ) {
                            swapfiles.append( + """" + QDir::toNativeSeparators(files.at(0)) + """" + "," );
                        } else {

                            QMessageBox msgBox;
                            msgBox.setText("Something went wrong... ");
                            msgBox.setInformativeText("uncompress of file " + rom.PATH + " error!");
                            msgBox.setStandardButtons(QMessageBox::Cancel);
                            int ret = msgBox.exec();

                            switch (ret) {
                              default:
                                  // should never be reached
                                  break;
                            }

                        }

                    } else {
                        qDebug() << "rom already in temp...";
                        swapfiles.append( + """" + QDir::toNativeSeparators(m_TempPath + "/" + rom.NAME) + """" + "," );
                    }

                    if ( fileIsEncrypted ) {

                        // Dann können wir das ZipFile wieder aufräumen...
                        romFile.setFileName( rom.PATH );
                        romFile.remove();
                    }
                }
            }
        }
    }

    qDebug() << swapfiles;

    return swapfiles;
}

QString MainWindow::getRomSetDiskFiles(QString RomSet) {

    QStringList files;
    QString     swapfiles;
    QStringList param;
    QFile       romFile;
    rom_type    rom;
    int         counter = 0;
    QFile       fileInfo;
    bool        fileIsEncrypted = false;
    QString     fileName;
    QString     fileNameNew;
    QFileInfo   fi;

    qDebug() << "getRomSetDiskFiles";

    if ( ! RomSet.trimmed().isEmpty() ) {

        QStringList Roms = RomSet.split(",");

        foreach(QString id, Roms) {

            files.clear();

            if ( m_db.selectRomData( id.toInt(), rom ) ) {

               this->showMessage("preparing: " + rom.NAME );

                QCoreApplication::processEvents();

                fi.setFile( rom.NAME );

                if ( this->useFileCache() && checkFileInCache( fi.fileName() ) ) {

                    qDebug() << "use file from cache..." + m_CachePath + fi.fileName() ;
                    files.append( m_CachePath + fi.fileName() );

                } else {

                    romFile.setFileName(rom.PATH);

                    if ( ! romFile.exists() ) {

                        romFile.setFileName( rom.PATH + ".aes" );
                        if ( ! romFile.exists() ) {
                            QMessageBox::information(this, this->windowTitle(),  tr("ROM ZIP nicht gefunden - ") + rom.PATH );
                        } else {

                            QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
                            QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

                            if ( AesKey.isEmpty() ) {

                                QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );

                            } else {

                               this->showMessage("preparing: " + rom.NAME + " " + " AES decrypting..." );

                                QCoreApplication::processEvents();

                                fileIsEncrypted = true;

                                param.clear();
                                param << "-d" << "-p" << AesKey << rom.PATH + ".aes";

                                ExecuteProgram(AesTool, param, true);
                            }
                        }
                    }

                   this->showMessage("preparing: " + rom.NAME + " " + " uncompressing..." );

                    QCoreApplication::processEvents();

                    if ( this->useFileCache() ) {
                        files = JlCompress::extractDir(rom.PATH, m_CachePath);
                    } else {
                        files = JlCompress::extractDir(rom.PATH, m_TempPath);
                    }

                }

                if ( files.count() > 0 ) {

                    QFileInfo fi(files.at(0));

                    fileInfo.setFileName( files.at(0) );
                    if ( ! fileInfo.rename( fi.absoluteDir().absolutePath() + "/" + rom.NAME) ) {
                        qDebug() << "getRomSetDiskFiles" << "rename FAIL!" << files.at(0) << fi.absoluteDir().absolutePath() + "/" + rom.NAME;
                    }

                    fileName = rom.NAME;

                    fileName = QDir::toNativeSeparators( fileName);

                    swapfiles = swapfiles + """" + fileName + """" + "|";

                    counter++;

                    if ( fileIsEncrypted ) {

                        // Dann können wir das ZipFile wieder aufräumen...
                        romFile.setFileName( rom.PATH );
                        romFile.remove();
                    }
                }
            }
        }
    }

    qDebug() << swapfiles;

   this->showMessage(" ");

    return swapfiles;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool MainWindow::useFileCache() {

    bool  retVal = false;
    QDir  fi;

    if ( ! m_ImageCachePath.isEmpty() ) {

        fi.setPath( m_ImageCachePath );
        if ( ! fi.exists() ) {
            if ( fi.mkpath( m_ImageCachePath ) ) {
                retVal = true;
            }
        } else {
            retVal = true;
        }
    }

    return retVal;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool MainWindow::checkFileInCache(QString filename) {

    QFileInfo fi;
    bool retVal = false;

    qDebug() << "checkFileInCache" << filename;

    // Alle Files des Archives entpacken...
    if ( ! m_CachePath.isEmpty() ) {

        fi.setFile(m_CachePath + "/" + filename );
        if ( fi.exists() ) {
            retVal = true;
        }
    }

    return retVal;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::StartEmu() {

    QString     program = "AutoIt3.exe";
    QString     script;
    QStringList arguments;
    QStringList files;
    QFile       romfile;
    QStringList param;
    bool        fileIsEncrypted = false;
    QFileInfo   fi;

    if ( ui->tableWidget->rowCount() == 0 ) {
        return;
    }

    if (ui->cboStartups->currentText().trimmed().isEmpty()) {
        QMessageBox::information(this, this->windowTitle(),  tr("No startup file found!") );
        return;
    }

    QTableWidgetItem *c, *a, *r, *s, *e, *t, *n  = new QTableWidgetItem();

    c = ui->tableWidget->item(3, 1);  // PATH
    a = ui->tableWidget->item(10, 1); // EATTR
    r = ui->tableWidget->item(13, 1); // ROMSET 

    s = ui->tableWidget->item(0, 1); // SYSTEM
    n = ui->tableWidget->item(2, 1); // NAME
    e = ui->tableWidget->item(1, 1); // SETNAME
    t = ui->tableWidget->item(4, 1); // TITLE

    fi.setFile(n->text());

    if ( this->useFileCache() && checkFileInCache( fi.fileName() ) ) {

        qDebug() << "use file from cache..." + m_CachePath + fi.fileName() ;
        files.append( m_CachePath + fi.fileName() );

    } else {

        // Alle Files des Archives entpacken...

        romfile.setFileName( c->text() );
        if ( ! romfile.exists() ) {

            romfile.setFileName( c->text() + ".aes" );
            if ( ! romfile.exists() ) {
                QMessageBox::information(this, this->windowTitle(),  tr("ROM ZIP nicht gefunden - ") + c->text() );
                return;
            } else {

                QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
                QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

                if ( AesKey.isEmpty() ) {

                    QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );
                    return;

                } else {

                    fileIsEncrypted = true;

                    param.clear();
                    param << "-d" << "-p" << AesKey << c->text() + ".aes";

                    ExecuteProgram(AesTool, param, true);
                }
            }
        }

        qDebug() << "unzip" << c->text();

        if ( this->useFileCache() ) {
            files = JlCompress::extractDir(c->text(), m_CachePath);
        } else {
            files = JlCompress::extractDir(c->text(), m_TempPath);
        }
    }

    if ( fileIsEncrypted ) {

        // Dann können wir das ZipFile wieder aufräumen...
        romfile.setFileName( c->text() );
        romfile.remove();
    }

    if ( ! files.isEmpty() ){

        script = ui->cboStartups->currentText();

        arguments << script;
        arguments << QString("/b:%1").arg(QDir::toNativeSeparators(files.at(0)));
        arguments << QString("/f:%1").arg(ui->chkFullscreen->checkState());
        arguments << QString("/a:%1").arg(a->text());
        arguments << QString("/d:%1").arg(getRomSetDiskFiles(r->text()));

        if ( program.trimmed() != "" ) {

            this->ExecuteProgram(program, arguments);

        } else {
            QMessageBox::information(this, this->windowTitle(),  tr("AutoIt not found - ") + program );
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::printOutput()
{
    if ( m_proc != nullptr ) {

        QByteArray byteArray = m_proc->readAllStandardOutput();

        m_stdOutLines.clear();
        m_stdOutLines = QString(byteArray).split("\n");

        foreach (QString line, m_stdOutLines){
           qDebug() << "-I-" << line;
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::printError()
{
    if ( m_proc != nullptr ) {

        QByteArray byteArray = m_proc->readAllStandardError();

        m_stdErrLines.clear();
        m_stdErrLines = QString(byteArray).split("\n");

        foreach (QString line, m_stdErrLines){
           qDebug() << "-E-" << line;
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool MainWindow::ExecuteProgram(QString program, QStringList arguments, bool wait) {

    bool retVal = true;
    QString errorLine;
    QString infotxt;

    m_proc = new QProcess;

    connect (m_proc, SIGNAL(readyReadStandardOutput()), this, SLOT(printOutput()));
    connect (m_proc, SIGNAL(readyReadStandardError()), this, SLOT(printError()));

    qDebug() << "start..." << QDir::toNativeSeparators(program) << arguments;

    if  ( ! m_tools.fileExists(QDir::toNativeSeparators(program)) ) {

        QString value = m_settings.loadStringSetting(m_sSettingsFile, "Executables", program);

        if ( value.isEmpty() ) {

            QString exeFile = QFileDialog::getOpenFileName(this, tr("ExecuteProgram: exe not found! ..." ) + program, QDir::homePath()  );

            m_settings.saveStringSetting(m_sSettingsFile, "Executables", program, exeFile);

            program = exeFile;

        } else {

            QFileInfo fi( QDir::toNativeSeparators(value) );

            if ( ! fi.exists() ) {

                m_settings.Delete(m_sSettingsFile, "Executables", program);

                value = QFileDialog::getOpenFileName(this, tr("ExecuteProgram: exe not found! ..." ) + program, QDir::homePath()  );

                m_settings.saveStringSetting(m_sSettingsFile, "Executables", program, value);

                program = value;

            } else {

                program = value;
            }
        }
    }

    QFileInfo fi( QDir::toNativeSeparators(program) );

    //@@@m_tools.extractIcons( program, true ) ;

    m_proc->setWorkingDirectory(fi.absolutePath());
    m_proc->setProcessChannelMode(QProcess::SeparateChannels);

    qDebug() << "args" << arguments << "count" << arguments.count() << "empty" << arguments.isEmpty() ;

#ifdef WIN32
    if ( 0 == arguments.count()  ) {
        m_proc->start("\"" + QDir::toNativeSeparators(program) + "\"");
    } else {
        m_proc->start("\"" + QDir::toNativeSeparators(program) + "\"", arguments);
    }
#endif

#ifdef linux
    if ( 0 == arguments.count()  ) {
        m_proc->start( QDir::toNativeSeparators(program) );
    } else {
        m_proc->start( QDir::toNativeSeparators(program), arguments);
    }
#endif

    if (wait) {

        if ( m_proc->waitForFinished(-1) ) {

            qDebug() << m_proc->readAllStandardOutput();

            if ( m_proc->exitCode() != 0 ) {

                errorLine.clear();                

                if ( ! m_stdErrLines.isEmpty() ) {
                    foreach (QString line, m_stdErrLines){
                        if ( ! line.isEmpty() )
                            errorLine.append(line);
                    }
                }

                qDebug() << m_stdErrLines;
                qDebug() << errorLine;

                infotxt = QString("Something went wrong - %1\n\n%2\n\nExitCode: %3\n\nContinue?").arg(program).arg(errorLine).arg(m_proc->exitCode());

                qDebug() << infotxt;

                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, this->windowTitle(), infotxt , QMessageBox::Yes|QMessageBox::No );

                if (reply == QMessageBox::Yes) {
                } else {
                    retVal = false;
                }

            } else {

                qDebug() << "ExecuteProgram" << program << m_proc->exitCode();
            }

            delete m_proc;
            m_proc = nullptr;

        } else {

            qDebug() << m_proc->readAllStandardOutput();

            retVal = false;
        }
    }

    return(retVal);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::getDiskInfo() {

    QString program;
    QStringList arguments;
    QStringList files;
    bool validfilefound = false;
    QFileInfo fi;
    QStringList param;
    bool fileIsEncrypted = false;
    QString result;

    if ( ui->tableWidget->rowCount() == 0 ) {
        return;
    }

    QTableWidgetItem *c = new QTableWidgetItem();

    c = ui->tableWidget->item(3, 1);

    fi.setFile( c->text() );
    if ( ! fi.exists() ) {

        fi.setFile( c->text() + ".aes" );
        if ( ! fi.exists() ) {
            QMessageBox::information(this, this->windowTitle(),  tr("ROM ZIP nicht gefunden - ") + c->text() );
            return;
        } else {

            QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
            QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

            if ( AesKey.isEmpty() ) {

                QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );
                return;

            } else {

                fileIsEncrypted = true;

                param.clear();
                param << "-d" << "-p" << AesKey << c->text() + ".aes";

                ExecuteProgram(AesTool, param, true);
            }
        }
    }

    files = JlCompress::extractDir(QDir::toNativeSeparators(c->text()), m_TempPath);

    //ui->edtDiskInfo->clear();

    for (int i = 0; i < files.size(); ++i) {

        QFileInfo fi( files.at(i) );

        // D64, D71, D81, X64 and G64
        if ( fi.completeSuffix().contains( QRegExp("d64|D64|d71|D71|d81|D81|x64|X64|g64|G64") ) )  {
            program = "c1541.exe";
            arguments << "-attach" << QDir::toNativeSeparators(files.at(i)) << "-dir";
            validfilefound = true;
        }

        // adf
        if ( fi.completeSuffix().contains( QRegExp("adf|ADF") ) )  {
            //program = "../Tools/adfchk/bin_win32/adfchk.exe";
            //arguments << "-f" << QDir::toNativeSeparators(files.at(i)) << "-b";

            program = "dynunadf.exe";
            arguments << "-l" << QDir::toNativeSeparators(files.at(i));

            validfilefound = true;
        }

    }

    if (validfilefound) {

        qDebug() << program << arguments;

        if ( ExecuteProgram(program, arguments, true) ) {

            foreach (QString line, m_stdErrLines){
               result = result + line;
            }

            foreach (QString line, m_stdOutLines){
               result = result + line;
            }

            result.replace("\r", "\r\n");

            QMessageBox::information(this, this->windowTitle(),  result );
        }

        if ( fileIsEncrypted ) {

            // Dann können wir das ZipFile wieder aufräumen...
            QFile file;
            file.setFileName( c->text() );
            file.remove();
        }

        //ui->edtDiskInfo->setVisible( true );
    } else {
        //ui->edtDiskInfo->clear();
        //ui->edtDiskInfo->setVisible( false );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::getAmiKickRomInfo() {

    if ( ui->tableWidget->rowCount() == 0 ) {
        return;
    }

    qDebug() << "getAmiKickRomInfo";

    QString program;
    QStringList param;
    QStringList files;
    bool validfilefound = false;
    bool fileIsEncrypted = false;
    QFile romfile;

    QTableWidgetItem *c = new QTableWidgetItem();

    c = ui->tableWidget->item(3, 1);

    // Alle Files des Archives entpacken...

    romfile.setFileName( c->text() );
    if ( ! romfile.exists() ) {

        romfile.setFileName( c->text() + ".aes" );
        if ( ! romfile.exists() ) {
            QMessageBox::information(this, this->windowTitle(),  tr("ROM ZIP nicht gefunden - ") + c->text() );
            return;
        } else {

            QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
            QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

            if ( AesKey.isEmpty() ) {

                QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );
                return;

            } else {

                fileIsEncrypted = true;

                param.clear();
                param << "-d" << "-p" << AesKey << c->text() + ".aes";

                ExecuteProgram(AesTool, param, true);
            }
        }
    }

    qDebug() << "unzip" << c->text();

    files = JlCompress::extractDir(QDir::toNativeSeparators(c->text()), m_TempPath);

    qDebug() << "getAmiKickRomInfo" << c->text() << files;

    param.clear();

    for (int i = 0; i < files.size(); ++i) {

        QFileInfo fi( files.at(i) );

        if ( fi.completeSuffix().contains(  QRegExp("rom|ROM") ) )  {
            program = "AmiKick.exe";
            param << files.at(i);
            validfilefound = true;
        }
    }

    if (validfilefound) {

        qDebug() << program << param;

        QMessageBox::information(this, this->windowTitle(),  "Image can be found at: " + param.at(0) );

        ExecuteProgram(program, param, false);
    }
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_cmd09_clicked() {

    m_actSelectionMode = 1;

    ui->cmd09->setStyleSheet( "background-color: lightgreen;" );
    ui->cmdAI->setStyleSheet( "" );
    ui->cmdJR->setStyleSheet( "" );
    ui->cmdSZ->setStyleSheet( "" );
    ui->cmdAll->setStyleSheet( ""  );
    ui->cmdFavorite->setStyleSheet( ""  );

    loadRomList(m_Item->toolTip());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_cmdAI_clicked() {

    m_actSelectionMode = 2;

    ui->cmd09->setStyleSheet( "" );
    ui->cmdAI->setStyleSheet( "background-color: lightgreen;" );
    ui->cmdJR->setStyleSheet( "" );
    ui->cmdSZ->setStyleSheet( "" );
    ui->cmdAll->setStyleSheet( ""  );
    ui->cmdFavorite->setStyleSheet( ""  );

    loadRomList(m_Item->toolTip());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_cmdJR_clicked() {

    m_actSelectionMode = 3;

    ui->cmd09->setStyleSheet( "");
    ui->cmdAI->setStyleSheet( "" );
    ui->cmdJR->setStyleSheet( "background-color: lightgreen;"  );
    ui->cmdSZ->setStyleSheet( "" );
    ui->cmdAll->setStyleSheet( ""  );
    ui->cmdFavorite->setStyleSheet( ""  );

    loadRomList(m_Item->toolTip());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_cmdSZ_clicked() {

    m_actSelectionMode = 4;

    ui->cmd09->setStyleSheet( "" );
    ui->cmdAI->setStyleSheet( "" );
    ui->cmdJR->setStyleSheet( "" );
    ui->cmdSZ->setStyleSheet( "background-color: lightgreen;"  );
    ui->cmdAll->setStyleSheet( ""  );
    ui->cmdFavorite->setStyleSheet( ""  );

    loadRomList(m_Item->toolTip());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_cmdAll_clicked() {

    m_actSelectionMode = 0;

    ui->cmd09->setStyleSheet( "" );
    ui->cmdAI->setStyleSheet( "" );
    ui->cmdJR->setStyleSheet( "" );
    ui->cmdSZ->setStyleSheet( ""  );
    ui->cmdAll->setStyleSheet( "background-color: orange;"  );
    ui->cmdFavorite->setStyleSheet( ""  );

    loadRomList(m_Item->toolTip());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_cmdFavorite_clicked() {

    m_actSelectionMode = 5;

    ui->cmd09->setStyleSheet( "" );
    ui->cmdAI->setStyleSheet( "" );
    ui->cmdJR->setStyleSheet( "" );
    ui->cmdSZ->setStyleSheet( "" );
    ui->cmdAll->setStyleSheet( ""  );
    ui->cmdFavorite->setStyleSheet( "background-color: lightgreen;"  );

    loadRomList(m_Item->toolTip());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::StoreRomParameter() {

    QVariantList values;

    QTableWidgetItem *a, *f, *r, *e, *n, *x, *i, *v, *t, *name  = new QTableWidgetItem();

    name = ui->tableWidget->item(2, 1);  // NAME
    t = ui->tableWidget->item(4, 1);  // TITLE
    e = ui->tableWidget->item(8, 1);  // EMUL
    a = ui->tableWidget->item(10, 1); // EATTR
    r = ui->tableWidget->item(11, 1); // RATING
    f = ui->tableWidget->item(12, 1); // FAVORIT
    n = ui->tableWidget->item(15, 1); // NONTOSEC
    x = ui->tableWidget->item(16, 1); // RANKING
    i = ui->tableWidget->item(17, 1); // ID
    v = ui->tableWidget->item(18, 1); // VARIANTS

    if ( true ) {

        StarRating starRating = qvariant_cast<StarRating>(r->data(0));

        QFileInfo fi = name->text();

        //values  << i->text().toInt() << a->text() << f->checkState() << starRating.starCount() << e->text() << n->checkState() << x->text().toInt() << v->text() << t->text() << name->text() ;
        values  << i->text().toInt() << a->text() << f->checkState() << starRating.starCount() << e->text() << n->checkState() << x->text().toInt() << v->text() << fi.completeBaseName() << name->text() ;

        qDebug()  << "StoreRomParameter" << values;

        m_db.updateEmulAttr( values );

        QMessageBox::information(this, this->windowTitle(),  tr("ROM settings saved...") );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_cboSystems_currentTextChanged(QString text) {

    QString     value;
    QStringList startupScripts;
    QString     picfilename;

    m_CurrentSystem = text;

    m_settings.saveStringSetting(m_sSettingsFile, "General", "LastSelectedSystem", text);

    fillSetNameListView(text, ui->chkLoadAll->isChecked());

    startupScripts = getStartups(text);
    if ( startupScripts.isEmpty() ) {
        m_tools.createDir(m_StartupsPath + "/" + m_CurrentSystem);
    }

    ui->cboHtmlLinks->clear();
    ui->cboHtmlLinks->setVisible( false );

    ui->cmdLink1->setHidden(true);
    ui->cmdLink2->setHidden(true);
    ui->cmdLink3->setHidden(true);
    ui->cmdLink4->setHidden(true);

    ui->cboStartups->clear();
    ui->cboStartups->addItems(startupScripts);

    if ( startupScripts.isEmpty() ) {
        setStartButtonMode(false);
    } else {
        setStartButtonMode(true);
    }

    ui->tableWidgetInfo->clear();
    ui->tableWidgetInfo->setColumnCount(0);
    ui->tableWidget->clear();
    ui->lblImage1->clear();
    ui->lblImage2->clear();
    ui->lblCover->clear();
    ui->lblMedia->clear();

    picfilename = ":/images/images/tosec.png";
    QImage publisher;

    publisher.load( picfilename ) ;

    if ( ! publisher.isNull() ) {
        ui->lblDeveloper->setPixmap(QPixmap::fromImage(publisher.scaledToHeight(ui->lblDeveloper->maximumHeight())));
        ui->lblPublisher->setPixmap(QPixmap::fromImage(publisher.scaledToHeight(ui->lblPublisher->maximumHeight())));
    }

    ui->cmdSoundtrack->setVisible(false);
    ui->cmdYoutubeVideo->setVisible(false);

    ui->widGamebase->setHidden(true);
    ui->widTosec->setHidden(true);

    m_screenshotfilelist.clear();
    m_soundtracklist.clear();
    m_mediafilelist.clear();
    m_coverfilelist.clear();

    m_actPcbUrl = m_settings.loadStringSetting("system.ini", text, "pcb");
    m_actPartraitUrl = m_settings.loadStringSetting("system.ini", text, "portrait");

    if ( ui->chkWikiInfo->isChecked() ) {

        value = m_settings.loadStringSetting("system.ini", text, "url");

        if( ! value.isEmpty() ) {

            m_actSystemLink = QUrl( value ).toString() ;

            this->loadWebView(m_actSystemLink);

        } else {

            if ( ! ui->chkWebViewLocked->isChecked() ) {

                ui->grpBrowser->setHidden(true);
            }
        }
    }

    value = m_settings.loadStringSetting("system.ini", text, "logo");

    if( ! value.isEmpty() ) {

        ui->lblLogo->setHidden(false);

        if ( ! value.trimmed().isEmpty() ) {

            picfilename = this->downloadFile(value, "", m_CachePath) ;

            const QImage image2 ( picfilename );

            if ( ! image2.isNull() ) {

                ui->lblLogo->setPixmap(QPixmap::fromImage(image2.scaledToHeight(ui->lblLogo->maximumHeight())));
            }
        }

    } else {
        ui->lblLogo->clear();
        ui->lblLogo->setHidden(true);
    }

    // Zugehörige HTML Links laden
    m_currentLinkChannel = text;

    this->iniToolBarLinks( ) ;

    // Zugehörige Youtube Kanäle laden
    m_currentYoutubeChannel = text;

    this->iniToolBarYoutube();

    loadSystemCounter();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ToggleFavorite() {

    QVariantList values;
    QTableWidgetItem *c  = new QTableWidgetItem();

    c = ui->tableWidget->item(17, 1); // ID

    if (!c) {
        QMessageBox::information(this, this->windowTitle(),  tr("no item selected") );
        return;
    }

    values << c->text().toInt() ;

    m_db.updateFavorite( values );

    loadRomList(m_Item->toolTip());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::BuildRomSet() {

    if (ui->tableWidget->rowCount() == 0 ) {
        return;
    }

    QList<QTableWidgetItem*> items = ui->tableWidgetInfo->selectedItems();
    QString romset;
    QVariantList values;

    for(int i = 0; i < items.count(); i++) {

        if ( ! items[i]->toolTip().isEmpty() ) {
            romset = romset + items[i]->toolTip() + "," ;
        }
    }

    for(int i = 0; i < items.count(); i++) {

        if ( ! items[i]->toolTip().isEmpty() ) {

            values.clear();
            values << romset << items[i]->toolTip();

            if ( ! m_db.updateRomSet( values ) ) {
                qDebug() << "BuildRomSet error!!!";
                QMessageBox::information(this, this->windowTitle(),  tr("Romset build error!") );
                return;
            }
        }
    }

    QMessageBox::information(this, this->windowTitle(),  tr("Romset successfull built!") );
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::BuildVariantsSet() {

    if (ui->tableWidget->rowCount() == 0 ) {
        return;
    }

    QList<QTableWidgetItem*> items = ui->tableWidgetInfo->selectedItems();
    QString      master;
    QVariantList values;

    for(int i = 0; i < items.count(); i++) {

         if ( ! items[i]->toolTip().isEmpty() ) {

            if ( i == 1 ) {
                master = items[i]->toolTip();
            }

            values.clear();
            values << items[i]->toolTip() << master;

            qDebug() << "updateVariants" << values;

            if ( ! m_db.updateVariants( values ) ) {
                qDebug() << "BuildVariantsSet error!!!";
                QMessageBox::information(this, this->windowTitle(),  tr("Variants set error!") );
                return;
            }
        }
    }

    QMessageBox::information(this, this->windowTitle(),  tr("Variants successfull set!") );
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ReleaseRomSet() {

    rom_type     rom;
    QVariantList values;
    QStringList  members;

    if (ui->tableWidget->rowCount() == 0 ) {
        return;
    }

    QList<QTableWidgetItem*> items = ui->tableWidgetInfo->selectedItems();

    for(int i = 0; i < items.count(); i++) {

        if ( ! items[i]->toolTip().isEmpty() ) {

            if ( m_db.selectRomData( items[i]->toolTip().toInt(), rom ) ) {

                members = rom.ROMSET.split(",");

                for(int ii = 0; ii < members.count(); ii++) {

                    if ( ! members[ii].isEmpty() ) {

                        values.clear();
                        values << " " << members[ii];

                        if ( ! m_db.updateRomSet( values ) ) {
                            qDebug() << "ReleaseRomSet error!!!";
                            QMessageBox::information(this, this->windowTitle(),  tr("Romset release error!") );
                            return;
                        }
                    }
                }
            }
        }
    }
/*              values.clear();
                values << rom.ROMSET;

                if ( ! m_db.releaseRomSet( values ) ) {

                    qDebug() << "ReleaseRomSet error!!!";
                    QMessageBox::information(this, this->windowTitle(),  tr("Romset release error!") );
                    return;                 
              }
*/

    QMessageBox::information(this, this->windowTitle(),  tr("Romset successfull released!") );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::setInfos(QString setname) {

    QList<QString> infos;
    double         completed = 0;
    QString        text;

    text.clear();

    infos = m_db.getInfoValues( QVariantList() << setname );

    text.append( infos.at(0) + " TOSEC entries found..." + " - ");

    text.append(infos.at(1) + " ROMS missing..." + " - ");

    completed = 100 / infos.at(0).toDouble() * (infos.at(0).toDouble() - infos.at(1).toDouble());

    text.append( "TOSEC is " + QString::number(completed, 'f', 2) + "% complete...");

    ui->widTosec->setText( text );
    ui->widTosec->setValue( completed );

    ui->widTosec->setHidden( ! (ui->chkTosec->checkState() == Qt::Checked) );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_chkOnlyValid_clicked() {

     this->setCurrentItem( ui->listWidget->currentItem() );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QStringList MainWindow::getEmuParameter(QString Emu, QString Section) {

    QStringList values;

    QString value = m_settings.loadStringSetting("system.ini", Section, Emu);

    if( !value.isEmpty() ) {

        values = value.split("|");
    }

    return values;
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_actionMakeAESKey_triggered()
{

    AesKeyGenerator *dialog = new AesKeyGenerator();

    dialog->setModal(true);
    dialog->show();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_actionToggle_SID_Player_triggered()
{
    if (ui->widSidPlayer->isHidden() ) {        

        ui->widSidPlayer->setHidden(false);

        ui->widMP3->stopPlayer();

        ui->widMP3->setHidden(true);
        ui->widAmigaRemix->setHidden(true);
        ui->widTheModArchive->setHidden(true);

        ui->lblCover->setHidden(true);
        ui->lblMedia->setHidden(true);

    } else {
        ui->widMP3->stopPlayer();

        ui->widSidPlayer->setHidden(true);
        ui->widMP3->setHidden( true );

        ui->lblCover->setHidden(false);
        ui->lblMedia->setHidden(false);
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QByteArray MainWindow::fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm) {

    QFile f(fileName);

    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
            return hash.result();
        }
    }
    return QByteArray();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ResetStatusBar() {

#ifdef WIN32
    mTaskbarProgress->setValue(0);
#endif

    mProgressDialog->close();

    m_beenden = false;

    QCoreApplication::processEvents();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::SetStatusBar(int min, int max, int value, QString info, bool init ) {

    if ( init ) {

        qDebug() << "SetStatusBar" << "init...";

        mProgressDialog = new QProgressDialog ();
        mProgressDialog->setMinimum( min );
        mProgressDialog->setMaximum( max );
        mProgressDialog->setWindowTitle( "Task in progress..." );
        mProgressDialog->setWindowModality(Qt::WindowModal);
        mProgressDialog->setWindowFlags(Qt::WindowStaysOnTopHint);

#ifdef _WIN32
        mTaskbarProgress->setVisible(true);
        mTaskbarProgress->setMinimum( min );
        mTaskbarProgress->setMaximum( max );
#endif

        m_beenden = false;

    } else {

        mProgressDialog->setLabelText( info );
        mProgressDialog->setValue( value );

#ifdef _WIN32
        mTaskbarProgress->setValue( value );
#endif
        if (mProgressDialog->wasCanceled()) {
            m_beenden = true;
        }
    }

    QCoreApplication::processEvents();
}



/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_actionUpdate_rom_storage_triggered()
{
    QVariantList values;

    QFile file(QFileDialog::getExistingDirectory(this, "Open"));

    QMessageBox msgBox;
    msgBox.setText("Update rom storage path");
    msgBox.setInformativeText("replace " + m_FileStorage + " with " + file.fileName() + "/" + "?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    if ( ret ==  QMessageBox::No ) {
        return;
    }

    values << m_FileStorage << file.fileName() + "/";

    if ( m_db.updateRomStorage(values) ) {

        QMessageBox::information(this, this->windowTitle(),  tr("Storage path update success... please restart the application") );

        m_settings.saveStringSetting(m_sSettingsFile, "General", "FileStorage", file.fileName() + "/");

        m_FileStorage =  file.fileName() + "/";

    } else {
        QMessageBox::information(this, this->windowTitle(),  tr("Storage path update failure...") );
    }
}

void MainWindow::on_actionAmigaRemix_triggered()
{
    if ( ui->widAmigaRemix->isHidden() ) {

        ui->widMP3->setPlayerTitle("AmigaRemix");
        ui->widMP3->stopPlayer();

        ui->widSidPlayer->setHidden( true );
        ui->widTheModArchive->setHidden(true);

        ui->widAmigaRemix->setHidden( false );

        ui->widMP3->setURL( QString(_ARurl).arg(1), _ARbaseUrl, _ARextension );

        ui->lblCover->setHidden(true);
        ui->lblMedia->setHidden(true);

    } else {
        ui->widMP3->stopPlayer();
        ui->widMP3->setTitle("");

        ui->widAmigaRemix->setHidden( true );
        ui->widMP3->setHidden( true );

        ui->lblCover->setHidden( false );
        ui->lblMedia->setHidden( false );
    }
}

void MainWindow::on_actionFlashtro_triggered()
{
    if ( ui->widMP3->isHidden() ) {

        ui->widMP3->stopPlayer();

        ui->widAmigaRemix->setHidden( true );
        ui->widSidPlayer->setHidden( true );
        ui->widTheModArchive->setHidden( true );

        ui->lblCover->setHidden(true);
        ui->lblMedia->setHidden(true);

        ui->widMP3->setURL( _FTurl, _FTbaseUrl, _FTextension );

    } else {

        ui->widMP3->setHidden( true );

        ui->lblCover->setHidden( false );
        ui->lblMedia->setHidden( false );
    }
}

void MainWindow::on_actionSettings_triggered()
{
    QSettingsDialog *dialog = new QSettingsDialog();

    dialog->setModal(true);
    dialog->show();

    connect(dialog, SIGNAL(finished()), SLOT(loadSettings()));
}

void MainWindow::on_chkWikiInfo_clicked(bool checked)
{
    m_settings.saveBoolSetting(m_sSettingsFile, "Wiki", "active", checked );

    ui->grpBrowser->setHidden( ! checked );
}

void MainWindow::on_chkOnlyValid_clicked(bool checked)
{
    m_settings.saveBoolSetting(m_sSettingsFile, "General", "OnlyValidRoms", checked );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::handleToolBarNews(QAction *action) {

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::handleToolBarSystem(QAction *action) {

    qDebug() << "handleToolBarSystem" << action->objectName();

    QString system  = action->objectName();

    QString program = m_settings.loadStringSetting("system.ini", system, "exe");
    QString param = m_settings.loadStringSetting("system.ini", system, "para");
    QString html = m_settings.loadStringSetting("system.ini", system, "url");
    QString youtube = m_settings.loadStringSetting("system.ini", system, "youtube");

    m_actPcbUrl = m_settings.loadStringSetting("system.ini", system, "pcb");

    if( ! html.isEmpty() ) { this->loadWebView(html); }

    if( ! system.isEmpty() ) { this->ui->cboSystems->setCurrentText( system ); }

    if ( ! youtube.isEmpty() ) {

        m_actRomVideoValue = GetYoutubeVideoUrl(youtube);

        ui->cmdYoutubeVideo->setVisible(true);

    } else {
        ui->cmdYoutubeVideo->setVisible(false);
    }

    if ( ! program.isEmpty() ) {
        if ( param.isEmpty()) {
            this->ExecuteProgram(program, QStringList(), false );
        } else {
            this->ExecuteProgram(program, QStringList() << param.split(" "), false );
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
    return s1.toLower() < s2.toLower();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::iniToolBarSystem() {

    QStringList systems;
    QString     txt;
    QPixmap     pixmap;
    QString     coord;
    QString     picFile;
    QString     kind;

    QMenu *Menu;

    QList<QMenu*> menus = menuBar()->findChildren<QMenu*>();

    foreach( QMenu* item, menus )
    {
        if (item->title().contains("Systems")) {
            item->clear();
            delete item;
        }
    }

    Menu = menuBar()->addMenu(tr("&Systems"));

    QList<QAction*> lst = ui->toolBarSystems->actions();

    for(int i=0;i < lst.length(); i++)
    {
        delete lst.at(i);
    }

    ui->toolBarSystems->clear();

    systems = m_settings.getAllSection("system.ini");

    qSort(systems.begin(), systems.end(), caseInsensitiveLessThan);

    if ( !systems.isEmpty() ) {        

        connect(Menu, SIGNAL(triggered(QAction*)), this, SLOT(handleToolBarSystem(QAction*)));

        foreach(QString system, systems) {

            if ( system != "Global") {

                txt = m_settings.loadStringSetting("system.ini", system, "exe");
                kind = m_settings.loadStringSetting("system.ini", system, "kind");

                QAction *action = new QAction( QString("actionSystem%1").arg(system), nullptr);

                action->setText ( system );
                action->setObjectName( system );

                picFile = m_settings.loadStringSetting("system.ini", system, "pic");
                coord = m_settings.loadStringSetting("system.ini", system, "coord");

                if ( picFile.contains("http")  ) {
                    pixmap = this->downloadFile( picFile, "", m_CachePath ) ;
                } else {
                    pixmap = m_tools.GetPicturePart(picFile, coord);
                }

                action->setIcon( QIcon( pixmap ) );

                if ( kind == "Both") {
                    ui->toolBarSystems->addAction( action );
                    Menu->addAction(action);
                } else if ( kind == "Toolbar") {
                    ui->toolBarSystems->addAction( action );
                } else if ( kind == "Menue") {
                    Menu->addAction(action);
                } else if ( kind == "Hidden") {
                    // System is hidden
                }

            } else {
                ui->toolBarSystems->setIconSize(QSize(m_settings.loadIntSetting("system.ini", "Global", "sizex"),
                                                      m_settings.loadIntSetting("system.ini", "Global", "sizey")));
            }
        }
    }

    ui->toolBarSystems->setVisible(true);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::handleToolBarHomeComputersDigital(QAction *action) {

    QString page  = action->objectName();

    qDebug() << "handleToolBarHomeComputersDigital" << page;

    QString section = m_settings.loadStringSetting("system.ini", page, "system");

    if ( ! section.isEmpty() ) {

        QString program = m_settings.loadStringSetting("system.ini", section, "exe");
        QString param = m_settings.loadStringSetting("system.ini", section, "para");
        QString html = m_settings.loadStringSetting("system.ini", section, "url");

        if( ! html.isEmpty() ) {

            this->loadWebView(html);
        }

        ExecuteProgram(program, QStringList() << param);

    } else {

        m_ImageViewer = new ImageViewer;
        m_ImageViewer->loadFile( m_ImageCachePath + action->objectName() + ".jpg");
        m_ImageViewer->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, m_ImageViewer->size(), qApp->desktop()->availableGeometry()));
        m_ImageViewer->show();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::iniToolBarHomeComputersDigital() {

    QString url = m_settings.loadStringSetting("settings.ini", "8bitkick", "url", "https://s3.amazonaws.com/www.8bitkick.cc/files/home-computers-digital-01.pdf");
    QString filename = m_CachePath;

    QString urlback = m_settings.loadStringSetting("settings.ini", "8bitkick", "bg", "http://www.8bitkick.cc/uploads/6/5/1/0/65101357/3211776_orig.png");
    QString background = m_ImageCachePath + "/" ;

    qDebug() << "iniToolBarHomeComputersDigital" << url << urlback;

    if ( url.trimmed().isEmpty() || urlback.trimmed().isEmpty() ) {
        qDebug() << "iniToolBarHomeComputersDigital" << "settings.ini not configured!";
        return;
    }

    filename = downloadFile(QUrl(url), "", filename) ;
    background = downloadFile(QUrl(urlback), "", background) ;

    if ( filename.trimmed().isEmpty() || background.trimmed().isEmpty() ) {
        qDebug() << "iniToolBarHomeComputersDigital" << "nothing downloaded!";
        return;
    }

    m_settings.saveStringSetting("settings.ini", "8bitkick", "url", url);
    m_settings.saveStringSetting("settings.ini", "8bitkick", "bg", urlback);

    ui->toolHomeComputersDigital->setStyleSheet("background-image: url(" + background +  ")");
    ui->toolHomeComputersDigital->setIconSize(QSize(30,50));

    //ui->toolHomeComputersDigital->setAttribute(Qt::WA_Hover, true);

    Poppler::Document* document = Poppler::Document::load(filename);
    if (!document || document->isLocked()) {
      // ... error message ....
      delete document;
      return;
    }

    // Paranoid safety check
    if (document == nullptr) {
      // ... error message ...
      return;
    }

    for ( int i=1; i<46; i++) {

        QAction *action = new QAction( QString("actionHomeComputersDigital%1").arg(i), nullptr);

        action->setObjectName( QString("Page%1").arg(i) );
        action->setToolTip( QString("Page %1").arg(i) );

        // Access page of the PDF file
        Poppler::Page* pdfPage = document->page(i);  // Document starts at page 0
        if (pdfPage == nullptr) {
          // ... error message ...
          return;
        }
        // Generate a QImage of the rendered page
        QImage image = pdfPage->renderToImage( );
        if (image.isNull()) {
          // ... error message ...
          return;
        }

        image.save(m_ImageCachePath + action->objectName() + ".jpg");

        action->setIcon( QIcon( QPixmap::fromImage(image) ) );

        ui->toolHomeComputersDigital->addAction( action );

        delete pdfPage;
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::handleToolBarLinks(QAction *action) {

    qDebug() << "handleToolBarLinks" << action->toolTip();

    this->loadWebView(action->toolTip(), true);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::iniToolBarLinks() {

    QString txt;

    ui->toolBarLinks->clear();

    QStringList links = m_settings.GetAllKeys("link.ini", m_currentLinkChannel);

    if ( links.count() > 0 ) {
        ui->toolBarLinks->setVisible(true);
    }

    for ( int i=0; i < links.count(); i++) {

        txt = m_settings.loadStringSetting("link.ini", m_currentLinkChannel, links.at(i));

        if ( ! txt.isEmpty() ) {

            QStringList txtlist = txt.split("|");

            if ( txtlist.count() > 1 ) {

                QAction *action = new QAction( QString("actionLink%1").arg(i), nullptr);

                if ( QString ( txtlist.at(1) ).length() > 20 ) {
                    action->setText ( QString ( txtlist.at(1) ).mid(0,20).append( "..." ) ) ; // Title
                } else {
                    action->setText ( QString ( txtlist.at(1) ) ); // Title
                }

                action->setToolTip( txtlist.at(0) ); // Url
                action->setData( QVariant::fromValue(links.at(i)) ); // Key

                action->setObjectName( QString("Link%1").arg(i) );

                ui->toolBarLinks->addAction( action );
            }
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_actionVerifyRomStore_triggered()
{
    QMessageBox msgBox;
    msgBox.setText(trUtf8("TOSEC Store"));
    msgBox.setInformativeText("Verifies the TOSEC store");
    QAbstractButton *myYesButton = msgBox.addButton(trUtf8("compare database with storage"), QMessageBox::YesRole);
    QAbstractButton *myNoButton = msgBox.addButton(trUtf8("compare storage with database"), QMessageBox::NoRole);
    QAbstractButton *myCancelButton = msgBox.addButton(trUtf8("Cancel"), QMessageBox::RejectRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();

    if( msgBox.clickedButton() == myNoButton ) { // "compare storage with database"

        QFile file;

        file.setFileName( m_FileStorage + "/" + ui->cboSystems->currentText() );

        if(file.exists()) {

           this->showMessage("process: " + file.fileName());

            findRomFiles(&file, true);
        } else {
            qDebug() << "-E- Directory not found... " + file.fileName();
        }

        file.close();
    }

    if( msgBox.clickedButton() == myYesButton ) { // "compare database with storage"

        verifyTosecDB();
    }

    if( msgBox.clickedButton() == myCancelButton ) {

    }

   this->showMessage("");
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::setInfoTxt(QString txt, QColor bgcolor, QString tooltip, bool init) {

    static int counter = 0;

    if ( init ) {
        ui->tableWidgetInfo->horizontalHeader()->setVisible(false);
        ui->tableWidgetInfo->verticalHeader()->setVisible(false);
        ui->tableWidgetInfo->setColumnCount(1);
        ui->tableWidgetInfo->setRowCount(0);

        counter = 0 ;
    }

    ui->tableWidgetInfo->insertRow( counter );

    QTableWidgetItem *item = new QTableWidgetItem();

    item->setToolTip( tooltip );
    item->setBackgroundColor( bgcolor );
    item->setText( txt );

    ui->tableWidgetInfo->setItem( counter, 0, item );

    counter++;

    ui->tableWidgetInfo->resizeColumnsToContents();
    ui->tableWidgetInfo->resizeRowsToContents();

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_chkSys_clicked(bool checked)
{
    m_settings.saveBoolSetting(m_sSettingsFile, "Sys", "active", checked );

    ui->widPerformance->setHidden( ! checked );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_chkTosec_clicked(bool checked)
{
    m_settings.saveBoolSetting(m_sSettingsFile, "Tosec", "active", checked );

    ui->widTosec->setHidden( ! checked );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_tableWidgetInfo_itemClicked(QTableWidgetItem *item)
{
    QFile    romFile;
    rom_type rom;
    QString  id;
    QString  filepath;
    QString  filename;
    QFile    dfile;
    QImage   publisher;
    QImage   developer;
    QString  picfilename;

    ui->tableWidget->setFont( QFont( m_settings.loadStringSetting(INI_FILE, "General", "fontname"),
                                     m_settings.loadIntSetting(INI_FILE, "General", "fontsize") ) );

    if ( m_GridMode == 2 ) { // ROM List

        m_actRomVideoValue.clear();

        if ( ! ui->widMP3->isPlaying() ) {

            ui->widMP3->stopPlayer();

            ui->widMP3->setHidden( true );
            ui->widAmigaRemix->setHidden( true );
            ui->widSidPlayer->setHidden( true );
            ui->widTheModArchive->setHidden( true );
        }

        //ui->edtDiskInfo->setVisible( false );

        id = item->toolTip();

        if ( m_db.selectRomData( id.toInt(), rom ) ) {

            this->loadStuffPackContents( id.toInt() );

            ui->tableWidget->setRowCount(21);
            ui->tableWidget->setColumnCount(2);

            ui->tableWidget->horizontalHeader()->setVisible(false);
            ui->tableWidget->verticalHeader()->setVisible(false);

            ui->tableWidget->setItemDelegate(new StarDelegate);

            ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked
                                            | QAbstractItemView::SelectedClicked);
            ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

            ui->tableWidget->setItem(0, 0, new QTableWidgetItem( "SYSTEM" ));
            ui->tableWidget->setItem(0, 1, new QTableWidgetItem( rom.SYSTEM ));

            ui->tableWidget->setItem(1, 0, new QTableWidgetItem( "SETNAME" ));
            ui->tableWidget->setItem(1, 1, new QTableWidgetItem( rom.SETNAME ));

            ui->tableWidget->setItem(2, 0, new QTableWidgetItem( "NAME" ));
            ui->tableWidget->setItem(2, 1, new QTableWidgetItem( rom.NAME ));

            ui->tableWidget->setItem(3, 0, new QTableWidgetItem( "PATH" ));

            QTableWidgetItem *pathItem = new QTableWidgetItem ( rom.PATH );

            romFile.setFileName(rom.PATH);
            if ( romFile.exists() ) {
                pathItem->setBackgroundColor (Qt::green);
                pathItem->setTextColor(Qt::black);
            } else {
                romFile.setFileName(rom.PATH + ".aes");
                if ( romFile.exists() ) {
                    pathItem->setBackgroundColor (Qt::blue);
                    pathItem->setTextColor(Qt::white);
                } else {
                    pathItem->setBackgroundColor (Qt::red);
                    pathItem->setTextColor(Qt::white);
                }
            }

            ui->tableWidget->setItem(3, 1, pathItem );

            ui->tableWidget->setItem(4, 0, new QTableWidgetItem( "TITLE" ));
            ui->tableWidget->setItem(4, 1, new QTableWidgetItem( rom.TITLE));

            ui->tableWidget->setItem(5, 0, new QTableWidgetItem( "CRC" ));
            ui->tableWidget->setItem(5, 1, new QTableWidgetItem( rom.CRC ));

            ui->tableWidget->setItem(6, 0, new QTableWidgetItem( "SHA" ));
            ui->tableWidget->setItem(6, 1, new QTableWidgetItem( rom.SHA ));

            ui->tableWidget->setItem(7, 0, new QTableWidgetItem( "MD5" ));
            ui->tableWidget->setItem(7, 1, new QTableWidgetItem( rom.MD5 ));

            ui->tableWidget->setItem(8, 0, new QTableWidgetItem( "EMUL" ));
            ui->tableWidget->setItem(8, 1, new QTableWidgetItem( rom.EMUL ));

            ui->tableWidget->setItem(9, 0, new QTableWidgetItem( "SIZE" ));
            ui->tableWidget->setItem(9, 1, new QTableWidgetItem( m_tools.bytesHumanReadable(rom.SIZE) ));

            ui->tableWidget->setItem(10, 0, new QTableWidgetItem( "EATTR" ));
            ui->tableWidget->setItem(10, 1, new QTableWidgetItem( rom.EATTR ));

            // -------------------------------------------------------------------------
            ui->tableWidget->setItem(11, 0, new QTableWidgetItem( "RATEING" ));

            QTableWidgetItem *itemRating = new QTableWidgetItem;
            itemRating->setData(0, QVariant::fromValue(StarRating(rom.RATEING)));
            ui->tableWidget->setItem(11, 1, itemRating);

            // -------------------------------------------------------------------------
            ui->tableWidget->setItem(12, 0, new QTableWidgetItem( "FAVORIT" ));

            QTableWidgetItem *favoritRating = new QTableWidgetItem;
            if ( rom.FAVORIT == 0 ) {
                favoritRating->setCheckState( Qt::Unchecked );
            } else {
                favoritRating->setCheckState( Qt::Checked );
            }

            ui->tableWidget->setItem(12, 1, favoritRating );

            // -------------------------------------------------------------------------
            ui->tableWidget->setItem(13, 0, new QTableWidgetItem( "ROMSET" ));
            ui->tableWidget->setItem(13, 1, new QTableWidgetItem( rom.ROMSET ));

            ui->tableWidget->setItem(14, 0, new QTableWidgetItem( "GAMEBASE" ));
            QTableWidgetItem *gamebase = new QTableWidgetItem;
            if ( rom.GAMEBASE == 0 ) {
                gamebase->setCheckState( Qt::Unchecked );
            } else {
                gamebase->setCheckState( Qt::Checked );
            }
            ui->tableWidget->setItem(14, 1, gamebase );

            ui->tableWidget->setItem(15, 0, new QTableWidgetItem( "NONTOSEC" ));
            QTableWidgetItem *nontosec = new QTableWidgetItem;
            if ( rom.NONTOSEC == 0 ) {
                nontosec->setCheckState( Qt::Unchecked );
            } else {
                nontosec->setCheckState( Qt::Checked );
            }
            ui->tableWidget->setItem(15, 1, nontosec );

            // -------------------------------------------------------------------------
            ui->tableWidget->setItem(16, 0, new QTableWidgetItem( "RANKING" ));
            ui->tableWidget->setItem(16, 1, new QTableWidgetItem( QString ( "%1" ).arg(rom.RANKING) ));

            // -------------------------------------------------------------------------
            ui->tableWidget->setItem(17, 0, new QTableWidgetItem( "ID" ));
            ui->tableWidget->setItem(17, 1, new QTableWidgetItem( QString ( "%1" ).arg(rom.ID) ));

            // -------------------------------------------------------------------------
            ui->tableWidget->setItem(18, 0, new QTableWidgetItem( "VARIANTS" ));
            ui->tableWidget->setItem(18, 1, new QTableWidgetItem( rom.VARIANTS ));

            // -------------------------------------------------------------------------
            ui->tableWidget->setItem(19, 0, new QTableWidgetItem( "MODDATE" ));
            ui->tableWidget->setItem(19, 1, new QTableWidgetItem( rom.MODDATE ));

            // -------------------------------------------------------------------------
            ui->tableWidget->setItem(20, 0, new QTableWidgetItem( "GENDATE" ));
            ui->tableWidget->setItem(20, 1, new QTableWidgetItem( rom.GENDATE ));

            ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

            ui->tableWidget->resizeColumnsToContents();
            ui->tableWidget->resizeRowsToContents();

            ui->tableWidget->item(0,0)->setFlags(ui->tableWidget->item(0,0)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(1,0)->setFlags(ui->tableWidget->item(1,0)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(2,0)->setFlags(ui->tableWidget->item(2,0)->flags() ^ Qt::ItemIsEditable); Name
            ui->tableWidget->item(3,0)->setFlags(ui->tableWidget->item(3,0)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(4,0)->setFlags(ui->tableWidget->item(4,0)->flags() ^ Qt::ItemIsEditable); Title
            ui->tableWidget->item(5,0)->setFlags(ui->tableWidget->item(5,0)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(6,0)->setFlags(ui->tableWidget->item(6,0)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(7,0)->setFlags(ui->tableWidget->item(7,0)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(8,0)->setFlags(ui->tableWidget->item(8,0)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(9,0)->setFlags(ui->tableWidget->item(9,0)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(10,0)->setFlags(ui->tableWidget->item(10,0)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(11,0)->setFlags(ui->tableWidget->item(11,0)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(12,0)->setFlags(ui->tableWidget->item(12,0)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(13,0)->setFlags(ui->tableWidget->item(13,0)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(14,0)->setFlags(ui->tableWidget->item(14,0)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(15,0)->setFlags(ui->tableWidget->item(15,0)->flags() ^ Qt::ItemIsEditable);

            ui->tableWidget->item(0,1)->setFlags(ui->tableWidget->item(0,1)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(1,1)->setFlags(ui->tableWidget->item(1,1)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(2,1)->setFlags(ui->tableWidget->item(2,1)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(3,1)->setFlags(ui->tableWidget->item(3,1)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(4,1)->setFlags(ui->tableWidget->item(4,1)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(5,1)->setFlags(ui->tableWidget->item(5,1)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(6,1)->setFlags(ui->tableWidget->item(6,1)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(7,1)->setFlags(ui->tableWidget->item(7,1)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(8,1)->setFlags(ui->tableWidget->item(8,1)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(9,1)->setFlags(ui->tableWidget->item(9,1)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(10,1)->setFlags(ui->tableWidget->item(10,1)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(11,1)->setFlags(ui->tableWidget->item(11,1)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(12,1)->setFlags(ui->tableWidget->item(12,1)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(13,1)->setFlags(ui->tableWidget->item(13,1)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(14,1)->setFlags(ui->tableWidget->item(14,1)->flags() ^ Qt::ItemIsEditable);
            //ui->tableWidget->item(15,1)->setFlags(ui->tableWidget->item(15,1)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(19,1)->setFlags(ui->tableWidget->item(19,1)->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->item(20,1)->setFlags(ui->tableWidget->item(20,1)->flags() ^ Qt::ItemIsEditable);

            QString ss = m_TosecMain + "/Stuffpacks/" + rom.SYSTEM + "/" + rom.SHA + "/";

            // -----------------------------------------------------------------------------------------

            if ( pathItem->backgroundColor() == Qt::red ) {
                this->setStartButtonMode(false);
            } else {
                this->setStartButtonMode(true);
            }

            // -----------------------------------------------------------------------------------------

            filepath = ss + "screenshot";

            if ( filepath.trimmed() != "" ) {

                m_screenshotfilelist.clear();

                QDirIterator it(filepath, QDirIterator::Subdirectories);
                while (it.hasNext()) {

                    filename = it.next();

                    if ( it.fileInfo().isFile() ) {

                        m_screenshotfilelist.append( filepath + "/" + it.fileName() );
                    }
                }
            }

            if ( ! ( m_screenshotfilelist.count() > 0 ) ) {
                ui->lblImage1->clear();
                ui->lblImage2->clear();
            }

            // -----------------------------------------------------------------------------------------

            filepath = ss + "cover";

            if ( filepath.trimmed() != "" ) {

                m_coverfilelist.clear();

                QDirIterator it(filepath, QDirIterator::Subdirectories);
                while (it.hasNext()) {

                    filename = it.next();

                    if ( it.fileInfo().isFile() ) {

                        m_coverfilelist.append( filepath + "/" + it.fileName() );
                    }
                }
            }

            if ( ! ( m_coverfilelist.count() > 0 ) ) {
                ui->lblCover->clear();
            } else {
                ui->lblCover->setHidden( false );
            }

            // -----------------------------------------------------------------------------------------

            filepath = ss + "media";

            if ( filepath.trimmed() != "" ) {

                m_mediafilelist.clear();

                QDirIterator it(filepath, QDirIterator::Subdirectories);
                while (it.hasNext()) {

                    filename = it.next();

                    if ( it.fileInfo().isFile() ) {

                        m_mediafilelist.append( filepath + "/" + it.fileName() );
                    }
                }
            }

            if ( ! ( m_mediafilelist.count() > 0 ) ) {
                ui->lblMedia->clear();
            } else {
                ui->lblMedia->setHidden( false );
            }

            // -----------------------------------------------------------------------------------------

            filepath = ss + "soundtrack";

            if ( filepath.trimmed() != "" ) {

                m_soundtracklist.clear();

                QDirIterator it(filepath, QDirIterator::Subdirectories);
                while (it.hasNext()) {

                    filename = it.next();

                    if ( it.fileInfo().isFile() ) {

                        m_soundtracklist.append( filepath + "/" + it.fileName() );
                    }
                }
            }

            // -----------------------------------------------------------------------------------------

            filename = ss + "info.txt";

            dfile.setFileName( filename );
            if ( dfile.exists() ) {

                QString url = m_settings.loadStringSetting(filename, "Global", "wiki");

                if ( ui->chkWikiInfo->isChecked() ) {
                    if ( ! url.isEmpty() ) {
                        this->loadWebView( url );
                    }
                }

                if ( m_soundtracklist.count() > 0 ) {
                    ui->cmdSoundtrack->setVisible(true);
                } else {
                    ui->cmdSoundtrack->setVisible(false);
                }

                m_actSolutionValue = m_settings.loadStringSetting(filename, "Global", "solution");
                if ( m_actSolutionValue.trimmed().isEmpty() ) {
                    ui->cmdSolution->setVisible(false);
                } else {
                    ui->cmdSolution->setVisible(true);
                }

                m_actCodetableValue = m_settings.loadStringSetting(filename, "Global", "codetable");
                if ( m_actCodetableValue.trimmed().isEmpty() ) {
                    ui->cmdCodeTable->setVisible(false);
                } else {
                    ui->cmdCodeTable->setVisible(true);
                }

                m_actRomVideoValue = m_settings.loadStringSetting(filename, "Global", "video");
                if ( m_actRomVideoValue.trimmed().isEmpty() ) {
                    ui->cmdYoutubeVideo->setVisible(false);
                } else {
                    ui->cmdYoutubeVideo->setVisible(true);
                }

                m_actManualValue = m_settings.loadStringSetting(filename, "Global", "manual");
                if ( m_actManualValue.trimmed().isEmpty() ) {
                    ui->cmdManuals->setVisible(false);
                } else {
                    ui->cmdManuals->setVisible(true);
                }

                QString actLogoValue = m_settings.loadStringSetting(filename, "Global", "logo");
                if ( actLogoValue.trimmed().isEmpty() ) {
                    picfilename = ":/images/images/tosec.png";
                } else {
                    picfilename = this->downloadFile(actLogoValue, "", m_CachePath) ;
                }

                publisher.load( picfilename ) ;

                if ( ! publisher.isNull() ) {
                    ui->lblPublisher->setPixmap(QPixmap::fromImage(publisher.scaledToHeight(ui->lblPublisher->maximumHeight())));
                }

                QString actLogoDeveloperValue = m_settings.loadStringSetting(filename, "Global", "logodeveloper");
                if ( actLogoDeveloperValue.trimmed().isEmpty() ) {
                    picfilename = ":/images/images/tosec.png";
                } else {
                    picfilename = this->downloadFile(actLogoDeveloperValue, "", m_CachePath) ;
                }

                developer.load( picfilename ) ;

                if ( ! developer.isNull() ) {
                    ui->lblDeveloper->setPixmap(QPixmap::fromImage(developer.scaledToHeight(ui->lblDeveloper->maximumHeight())));
                }

                ui->cboHtmlLinks->clear();

                QStringList htmlLinks = m_settings.GetAllKeys(filename, "Links");

                for (int i = 0; i < htmlLinks.size(); ++i) {

                    QString baseurl = m_settings.loadStringSetting(filename, "Links", htmlLinks.at(i) );

                    ui->cboHtmlLinks->addItem( baseurl );
                }

                ui->cboHtmlLinks->setVisible(  ui->cboHtmlLinks->count() > 0 );

                QString pic;
                QString link;

                for( int r = 0; r < 4; ++r ) {

                    for( int c = 0; c < 2; ++c ) {

                        if ( c == 0 )
                            pic = m_settings.loadStringSetting(filename, "QuickLinks", QString("%1%2").arg(r).arg(c) );

                        if ( c == 1)
                            link = m_settings.loadStringSetting(filename, "QuickLinks", QString("%1%2").arg(r).arg(c) );
                    }

                    if ( r == 0 ) {

                        picfilename = this->downloadFile(pic, "", m_CachePath) ;

                        if ( ( ! picfilename.isEmpty() ) && ( ! link.trimmed().isEmpty() ) ) {

                            QPixmap pix1(picfilename) ;

                            ui->cmdLink1->setText("");
                            ui->cmdLink1->setIconSize( QSize(pix1.width() * 0.5, pix1.height() * 0.5 ));
                            ui->cmdLink1->setIcon(QIcon(pix1));
                            ui->cmdLink1->setToolTip(link);
                            ui->cmdLink1->setHidden(false);
                        } else {
                            ui->cmdLink1->setHidden(true);
                        }
                    }

                    if ( r == 1 ) {

                        picfilename = this->downloadFile(pic, "", m_CachePath) ;

                        if ( ( ! picfilename.isEmpty() ) && ( ! link.trimmed().isEmpty() ) ) {

                            QPixmap pix2(picfilename) ;

                            ui->cmdLink2->setText("");
                            ui->cmdLink2->setIconSize(QSize(pix2.width() * 0.5, pix2.height() * 0.5));
                            ui->cmdLink2->setIcon(QIcon(pix2));
                            ui->cmdLink2->setToolTip(link);
                            ui->cmdLink2->setHidden(false);
                        } else {
                            ui->cmdLink2->setHidden(true);
                        }
                    }

                    if ( r == 2 ) {

                        picfilename = this->downloadFile(pic, "", m_CachePath) ;

                        if ( ( ! picfilename.isEmpty() ) && ( ! link.trimmed().isEmpty() ) ) {

                            QPixmap pix3(picfilename) ;

                            ui->cmdLink3->setText("");
                            ui->cmdLink3->setIconSize(QSize(pix3.width() * 0.5, pix3.height() * 0.5));
                            ui->cmdLink3->setIcon(QIcon(pix3));
                            ui->cmdLink3->setToolTip(link);
                            ui->cmdLink3->setHidden(false);
                        } else {
                            ui->cmdLink3->setHidden(true);
                        }
                    }

                    if ( r == 3 ) {

                        picfilename = this->downloadFile(pic, "", m_CachePath) ;

                        if ( ( ! picfilename.isEmpty() ) && ( ! link.trimmed().isEmpty() ) ) {

                            QPixmap pix4(picfilename) ;

                            ui->cmdLink4->setText("");
                            ui->cmdLink4->setIconSize(QSize(pix4.width() * 0.5, pix4.height() * 0.5));
                            ui->cmdLink4->setIcon(QIcon(pix4));
                            ui->cmdLink4->setToolTip(link);
                            ui->cmdLink4->setHidden(false);
                        } else {
                            ui->cmdLink4->setHidden(true);
                        }
                    }

                    pic.clear();
                    link.clear();
                }

            } else {

                picfilename = ":/images/images/tosec.png";

                publisher.load( picfilename ) ;

                if ( ! publisher.isNull() ) {
                    ui->lblPublisher->setPixmap(QPixmap::fromImage(publisher.scaledToHeight(ui->lblPublisher->maximumHeight())));
                    ui->lblDeveloper->setPixmap(QPixmap::fromImage(publisher.scaledToHeight(ui->lblDeveloper->maximumHeight())));
                }

                ui->cboHtmlLinks->clear();
                ui->cboHtmlLinks->setVisible( false );

                ui->cmdSoundtrack->setVisible(false);
                ui->cmdYoutubeVideo->setVisible(false);
                ui->cmdManuals->setVisible(false);
                ui->cmdCodeTable->setVisible(false);
                ui->cmdSolution->setVisible(false);

                ui->lblImage1->clear();
                ui->lblImage2->clear();
                ui->lblMedia->clear();
                ui->lblCover->clear();

                if ( ui->chkWikiInfo->isChecked() ) {
                    if ( ui->webView->url() != QUrl( m_actSystemLink ) ) {
                        this->loadWebView(m_actSystemLink);
                    }
                }

                ui->cmdLink1->setHidden(true);
                ui->cmdLink2->setHidden(true);
                ui->cmdLink3->setHidden(true);
                ui->cmdLink4->setHidden(true);
            }

            if ( m_Item ) {

                QString gamebasedb = m_settings.loadStringSetting(m_sSettingsFile, "Gamebase",  m_Item->text());

                if ( ! gamebasedb.isEmpty() ) {

                    ui->widGamebase->loadGameData(gamebasedb, rom.CRC );

                } else {

                    QString info = m_settings.loadStringSetting(filename, "Global", "info");

                    if ( ! info.isEmpty() ) {

                        ui->widGamebase->setInfoExt( info );
                        ui->widGamebase->setHidden(false);
                    } else {

                        ui->widGamebase->setHidden(true);
                    }
                }
/*
                QVariantList values;

                QString rating = m_settings.loadStringSetting(filename, "Global", "rating");

                if ( rating.toInt() != rom.RATEING ) {

                    values << rating << rom.ID ;

                    if ( m_db.updateRating( values ) ) {

                    }
                }
*/
            }

            this->repaint();
        }
    }

    if ( m_GridMode == 1 ) { // System List

         if ( item->isSelected() ) {

            m_settings.saveIntSetting(m_sSettingsFile, "Hidden Systems", item->toolTip(), item->checkState());

            if ( item->checkState() == Qt::Checked ) {
                qDebug() << item->toolTip() << "checked";
            } else {
                qDebug() << item->toolTip() << "unchecked";
            }

            fillSystemCombo();
         }
     }

    if ( m_GridMode == 5 ) { // Dokumente

         if ( item->isSelected() ) {

             qDebug() << item->toolTip() <<  item->text();

             if ( ! item->toolTip().isEmpty() ) {

                 QDesktopServices::openUrl ( QUrl ( "file:///" + item->toolTip(), QUrl::TolerantMode )) ;

             }
         }
     }
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_cmdStartEmu_clicked()
{
    StartEmu();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::loadSystemList()
{

    m_GridMode = 1; // SystemList

    QList<QStringList> systems;
    QString info;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    ui->tableWidgetInfo->clear();
    ui->tableWidget->setRowCount(0);
    //ui->edtDiskInfo->clear();
    //ui->edtDiskInfo->setVisible( false );
    ui->cmdManuals->setVisible(false);
    ui->cmdSoundtrack->setVisible(false);
    ui->cmdYoutubeVideo->setVisible(false);
    ui->cmdCodeTable->setVisible(false);
    ui->cmdSolution->setVisible(false);

    ui->lblImage1->clear();
    ui->lblImage2->clear();
    ui->lblCover->clear();
    ui->lblMedia->clear();
    ui->gpSelection->setHidden(true);
    ui->widGamebase->setHidden(true);

    this->setStartButtonMode(false);

   this->showMessage("loading...");

    if (ui->edtSearch->text().trimmed() == "") {
        ui->edtSearch->setText("%");
    }
/*
    QFileInfo fi(m_CachePath + "/Systems.cache");
    if ( ! fi.exists() ) {

        systems = m_db.getSystemOverview();

        QFile ofile( m_CachePath + "/Systems.cache" );
        if( !ofile.open( QIODevice::WriteOnly ) )
          return;

        QDataStream ostream( &ofile );
        ostream.setVersion( QDataStream::Qt_5_5 );

        ostream << systems;

        ofile.close();
    }

    systems.clear();

    QFile ifile( m_CachePath + "/Systems.cache" );
    if( !ifile.open( QIODevice::ReadOnly ) )
      return;

    QDataStream istream( &ifile );
    istream.setVersion( QDataStream::Qt_5_5 );

    istream >> systems;

    ifile.close();
*/
    CHECKTIME ( systems = m_db.getSystemOverview(); );

    ui->tableWidgetInfo->horizontalHeader()->setVisible(true);
    ui->tableWidgetInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetInfo->verticalHeader()->setVisible(false);
    ui->tableWidgetInfo->setColumnCount(5);
    ui->tableWidgetInfo->setRowCount(0);
    ui->tableWidgetInfo->setItemDelegate(new StarDelegate);

    QTableWidgetItem *header0 = new QTableWidgetItem();
    header0->setText("");
    ui->tableWidgetInfo->setHorizontalHeaderItem(0,header0);
    QTableWidgetItem *header1 = new QTableWidgetItem();
    header1->setText("System");
    ui->tableWidgetInfo->setHorizontalHeaderItem(1,header1);
    QTableWidgetItem *header2 = new QTableWidgetItem();
    header2->setText("Available");
    ui->tableWidgetInfo->setHorizontalHeaderItem(2,header2);
    QTableWidgetItem *header3 = new QTableWidgetItem();
    header3->setText("Store");
    ui->tableWidgetInfo->setHorizontalHeaderItem(3,header3);
    QTableWidgetItem *header4 = new QTableWidgetItem();
    header4->setText("Complete");
    ui->tableWidgetInfo->setHorizontalHeaderItem(4,header4);

    int counter = 0;

    for (int i = 0; i < systems.size(); ++i) {

        info = "";

        ui->tableWidgetInfo->insertRow( counter );

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setToolTip( QString(systems.at(i).at(0) ) );

        int value = m_settings.loadIntSetting(m_sSettingsFile, "Hidden Systems", QString(systems.at(i).at(0) ));

        if ( value != Qt::Checked ) {
            item->setCheckState(Qt::Unchecked);
        } else {
            item->setCheckState(Qt::Checked);
        }
        ui->tableWidgetInfo->setItem( counter, 0, item );

        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText( QString(systems.at(i).at(0) ) );
        ui->tableWidgetInfo->setItem( counter, 1, item1 );

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText( QString(systems.at(i).at(1) ) );
        ui->tableWidgetInfo->setItem( counter, 2, item2 );

        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setText( QString(systems.at(i).at(2) ) );
        ui->tableWidgetInfo->setItem( counter, 3, item3 );

        QTableWidgetItem *item4 = new QTableWidgetItem();
        double complete = (100 / QString(systems.at(i).at(1)).toDouble()) * QString(systems.at(i).at(2)).toDouble();
        item4->setText( QString::number(complete, 'f', 2) + "%" );
        if (item4->text() == "100.00%") {
            item4->setBackgroundColor(Qt::green);
        }

        ui->tableWidgetInfo->setItem( counter, 4, item4 );

        counter++;
    }

    ui->tableWidgetInfo->resizeColumnsToContents();   
    ui->tableWidgetInfo->resizeRowsToContents();

 //   QSettings settings("state.ini", QSettings::IniFormat);
 //   QByteArray MyArray = settings.value(QString("mainTableWidth%1").arg(m_GridMode), "").toByteArray();
 //   ui->tableWidgetInfo->horizontalHeader()->restoreState(MyArray);

    this->showMessage("");

    QApplication::restoreOverrideCursor();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_actionSystem_Overview_triggered()
{
    loadSystemList();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::RetrieveStuffPack(QString sha1) {

    qDebug() << sha1;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::MakeStuffPack(QString system, QString sha1) {

    QString  fileCompressed ;
    rom_type rom;
    QList<rom_type> roms;

    roms = m_db.selectRomDataBySha1( system, sha1 );

    if ( roms.count() > 0 ) {

        rom = roms.first();

        //fileCompressed = m_TempPath + "/" + rom.SYSTEM + "/" + rom.SETNAME + "/" + sha1 + ".zip";
        fileCompressed = m_TempPath + "/" + rom.SYSTEM + "/" + sha1 + ".zip";

        QString stuffDir = m_TosecMain + "/Stuffpacks/" + rom.SYSTEM + "/" + rom.SHA ;

        if ( QFile::exists( stuffDir + "/" + "info.txt" ) ) {

            if ( JlCompress::compressDir( fileCompressed, stuffDir, true ) ) {

                QMessageBox::information(this, this->windowTitle(),  tr("Stuffpack successfull generated at ") + fileCompressed );
                qDebug() << "compress for file " + fileCompressed + " ok...";

                if ( m_StuffSrvEnabled ) {

                    qDebug() << "upload to StuffServer " + m_StuffSrvIp;

                    QFile *data = new QFile(fileCompressed, this);
                    if(data->open(QIODevice::ReadOnly)) {

                        QUrl uploadurl(m_StuffSrvIp + sha1 + ".zip");
                        uploadurl.setUserName( m_StuffSrvUser );
                        uploadurl.setPassword( m_StuffSrvPassword );
                        uploadurl.setPort( m_StuffSrvPort );

                        mUploadNetwManager = new QNetworkAccessManager(this);
                        mNetwReply = mUploadNetwManager->put(QNetworkRequest(uploadurl), data);

                        connect(mNetwReply, SIGNAL(uploadProgress(qint64, qint64)), SLOT(uploadProgress(qint64, qint64)));
                        connect(mNetwReply, SIGNAL(finished()), SLOT(networkDone()));
                    }
                }

            } else {

                QMessageBox::information(this, this->windowTitle(),  tr("Unable to generate Stuffpack at ") + fileCompressed );
                qDebug() << "compress for file " + fileCompressed + " error...";
            }
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::uploadProgress(qint64 bytesSent, qint64 bytesTotal)    {

    qDebug() << "uploadProgress " << bytesSent << "of" << bytesTotal;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::networkDone()     {

    qDebug() << "networkDone" << mNetwReply->error();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ImportStuffPack(QString filename) {

    QFileInfo fi (filename);

    QString  fileCompressed ;
    rom_type rom;
    QList<rom_type> roms;

    QString sha1;

    sha1 = fi.baseName();

    roms = m_db.selectRomDataBySha1( "", sha1 );

    if ( roms.count() > 0 ) {

        rom = roms.first();

        fileCompressed = fi.filePath().remove("file:///");

        QString stuffDir = m_TosecMain + "/Stuffpacks/" + rom.SYSTEM + "/" + sha1 ;

        QStringList files = JlCompress::extractDir( fileCompressed, stuffDir ) ;

        if ( files.count() > 0 ) {

            QMessageBox::information(this, this->windowTitle(),  tr("Stuffpack successfull installed") );
            qDebug() << "compress for file " + fileCompressed + " ok...";

        } else {

            QMessageBox::information(this, this->windowTitle(),  tr("Unable to install Stuffpack") );
            qDebug() << "compress for file " + fileCompressed + " error...";
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_actionThe_Mod_Archive_triggered()
{
    if ( ui->widTheModArchive->isHidden() ) {

        ui->widMP3->stopPlayer();

        ui->widSidPlayer->setHidden( true );
        ui->widAmigaRemix->setHidden(true);

        ui->widTheModArchive->setHidden( false );

        ui->widMP3->setURL( QString(_TMAurl).arg(1), _TMAbaseUrl, _TMAextension );

        ui->lblCover->setHidden(true);
        ui->lblMedia->setHidden(true);

    } else {
        ui->widMP3->stopPlayer();

        ui->widTheModArchive->setHidden( true );
        ui->widMP3->setHidden( true );

        ui->lblCover->setHidden( false );
        ui->lblMedia->setHidden( false );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_edtSystems_clicked()
{
    QString filepath = m_StartupsPath + "/" + m_CurrentSystem;

    if ( ! ui->cboStartups->currentText().trimmed().isEmpty() ) {

        mMyCodeEditor = new CodeEditor(this, ui->cboStartups->currentText() );
        mMyCodeEditor->show();

    } else {

       bool ok;
       // Ask for birth date as a string.
       QString filename = QInputDialog::getText(nullptr, "No startup file configured for " + m_CurrentSystem,
                                            "Please enter the filename:", QLineEdit::Normal,
                                            "", &ok);
       if (ok && !filename.isEmpty()) {

           mMyCodeEditor = new CodeEditor(this, filepath + "/" + filename );
           mMyCodeEditor->show();
       }

    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QStringList MainWindow::getStartups(QString system) {

    QString     filepath = m_StartupsPath + "/" + system;

    QStringList tmpList;
    QString     filename;

    QDirIterator it(filepath);
    while (it.hasNext()) {

        filename = it.next();

        if ( it.fileInfo().isFile() ) {

            tmpList.append( it.fileInfo().absoluteFilePath() );
        }
    }

    return(tmpList);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_actionDownload_triggered()
{
    mMyDownloadMgr = new DownloadMgr( this );

    mMyDownloadMgr->show();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::loadSystemCounter()
{
    m_GridMode = 3; // SystemCounter

    QList<QStringList> sets;
    QString            info;
    QVariantList       values;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    ui->tableWidgetInfo->clear();
    ui->tableWidget->setRowCount(0);
    //ui->edtDiskInfo->clear();
    //ui->edtDiskInfo->setVisible( false );
    ui->cmdManuals->setVisible(false);
    ui->cmdSoundtrack->setVisible(false);
    ui->cmdYoutubeVideo->setVisible(false);
    ui->cmdCodeTable->setVisible(false);
    ui->cmdSolution->setVisible(false);

    ui->lblImage1->clear();
    ui->lblImage2->clear();
    ui->lblCover->clear();
    ui->lblMedia->clear();
    ui->gpSelection->setHidden(true);

    this->setStartButtonMode(false);

   this->showMessage("loading...");

    if (ui->edtSearch->text().trimmed() == "") {
        ui->edtSearch->setText("%");
    }

    values << ui->cboSystems->currentText();

    QFileInfo fi(m_CachePath + ui->cboSystems->currentText() + ".cache");
    if ( ! fi.exists() ) {

        sets = m_db.getSetNamesOverview(values);

        QFile ofile( m_CachePath + ui->cboSystems->currentText() + ".cache" );
        if( !ofile.open( QIODevice::WriteOnly ) )
          return;

        QDataStream ostream( &ofile );
        ostream.setVersion( QDataStream::Qt_5_5 );

        ostream << sets;

        ofile.close();
    }

    sets.clear();

    QFile ifile( m_CachePath  + ui->cboSystems->currentText() + ".cache" );
    if( !ifile.open( QIODevice::ReadOnly ) )
      return;

    QDataStream istream( &ifile );
    istream.setVersion( QDataStream::Qt_5_5 );

    istream >> sets;

    ifile.close();

    ui->tableWidgetInfo->horizontalHeader()->setVisible(true);
    ui->tableWidgetInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetInfo->verticalHeader()->setVisible(false);
    ui->tableWidgetInfo->setColumnCount(4);
    ui->tableWidgetInfo->setRowCount(0);
    ui->tableWidgetInfo->setItemDelegate(new StarDelegate);

    ui->tableWidgetInfo->setSelectionBehavior( QAbstractItemView::SelectRows );

    QTableWidgetItem *header0 = new QTableWidgetItem();
    header0->setText("Tosec sets in " +  ui->cboSystems->currentText() );
    ui->tableWidgetInfo->setHorizontalHeaderItem(0,header0);
    QTableWidgetItem *header1 = new QTableWidgetItem();
    header1->setText("Total");
    ui->tableWidgetInfo->setHorizontalHeaderItem(1,header1);
    QTableWidgetItem *header2 = new QTableWidgetItem();
    header2->setText("Available");
    ui->tableWidgetInfo->setHorizontalHeaderItem(2,header2);
    QTableWidgetItem *header3 = new QTableWidgetItem();
    header3->setText("Complete");
    ui->tableWidgetInfo->setHorizontalHeaderItem(3,header3);

    int counter = 0;

    for (int i = 0; i < sets.size(); ++i) {

        info = "";

        ui->tableWidgetInfo->insertRow( counter );

        QTableWidgetItem *item1 = new QTableWidgetItem();

        //QString setName = sets.at(i).at(0);

        item1->setText( QString(sets.at(i).at(0)).remove(ui->cboSystems->currentText() + " - ") ) ;
        item1->setFlags(item1->flags() & ~Qt::ItemIsEditable);
        item1->setToolTip(sets.at(i).at(0));
        ui->tableWidgetInfo->setItem( counter, 0, item1 );

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText( QString(sets.at(i).at(1) ) );
        ui->tableWidgetInfo->setItem( counter, 1, item2 );

        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setText( QString(sets.at(i).at(2) ) );
        ui->tableWidgetInfo->setItem( counter, 2, item3 );

        QTableWidgetItem *item4 = new QTableWidgetItem();
        double complete = (100 / QString(sets.at(i).at(1)).toDouble()) * QString(sets.at(i).at(2)).toDouble();
        item4->setText( QString::number(complete, 'f', 2) + "%" );
        if (item4->text() == "100.00%") {
            item4->setBackgroundColor(Qt::green);
        }

        ui->tableWidgetInfo->setItem( counter, 3, item4 );

        counter++;
    }

    ui->tableWidgetInfo->resizeColumnsToContents();
    ui->tableWidgetInfo->resizeRowsToContents();

   // QSettings settings("state.ini", QSettings::IniFormat);
   // QByteArray MyArray = settings.value(QString("mainTableWidth%1").arg(m_GridMode), "").toByteArray();
   // ui->tableWidgetInfo->horizontalHeader()->restoreState(MyArray);

    this->showMessage("");

    QApplication::restoreOverrideCursor();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::verifyTosecDB() {

    m_GridMode = 4; // VerifyTosec

    m_beenden = false;

    QList<rom_type>    tosecs;
    QFile              finfo;
    int                counter = 0;
    qlonglong          storageSize = 0;
    QStringList        missingSha1;
    QVariantList       values;
    bool               deepAnalyse = false;
    bool               fileIsEncrypted = false;
    QStringList        param;

    QMessageBox::StandardButton reply = QMessageBox::question(this, m_applName, tr("Verify the TOSEC database with the store...\n\nShall I make a deep analyse with unpacking?"), QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
        deepAnalyse = true;
    } else if (reply == QMessageBox::Cancel) {
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);

    ui->tableWidgetInfo->clear();
    ui->tableWidget->setRowCount(0);
    //ui->edtDiskInfo->clear();
    //ui->edtDiskInfo->setVisible( false );
    ui->cmdManuals->setVisible(false);
    ui->cmdSoundtrack->setVisible(false);
    ui->cmdYoutubeVideo->setVisible(false);
    ui->cmdCodeTable->setVisible(false);
    ui->cmdSolution->setVisible(false);

    ui->lblImage1->clear();
    ui->lblImage2->clear();
    ui->lblCover->clear();
    ui->lblMedia->clear();
    ui->gpSelection->setHidden(true);

    QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
    QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

    this->setStartButtonMode(false);

   this->showMessage("loading file information from database for system " + ui->cboSystems->currentText());

    tosecs = m_db.getSoftwareNames(ui->cboSystems->currentText(), "", 7, "", 0);

   this->showMessage( QString("%1").arg(tosecs.count()) + " entries found...");

    ui->tableWidgetInfo->horizontalHeader()->setVisible(true);
    ui->tableWidgetInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetInfo->verticalHeader()->setVisible(false);
    ui->tableWidgetInfo->setColumnCount(1);
    ui->tableWidgetInfo->setRowCount(0);

    QTableWidgetItem *header0 = new QTableWidgetItem();
    header0->setText("Result Overview");
    ui->tableWidgetInfo->setHorizontalHeaderItem(0,header0);

    missingSha1.clear();

    for (int i = 0; ( ( i < tosecs.size() ) && ! m_beenden ); ++i) {

        SetStatusBar(0, tosecs.size(), i,  QString("System: %1 - process file %2 of %3 ").arg(ui->cboSystems->currentText()).arg(i).arg(tosecs.size()), ( i==0 )?true:false  ) ;

        if ( ! ( tosecs.at(i).PATH.contains("missing") ) ) {

            finfo.setFileName(tosecs.at(i).PATH);

            if ( ! finfo.exists() ) {

                finfo.setFileName(tosecs.at(i).PATH + ".aes");

                if ( ! finfo.exists() ) {

                    ui->tableWidgetInfo->insertRow( counter );

                    QTableWidgetItem *item1 = new QTableWidgetItem();
                    item1->setText("-E- File not found - " + QString(tosecs.at(i).PATH ) );
                    ui->tableWidgetInfo->setItem( counter, 0, item1 );

                    missingSha1 << tosecs.at(i).SHA;

                    values.clear();
                    values << "missing" << tosecs.at(i).ID;

                    if ( m_db.updateRomPathById(values) ) {
                        qDebug() << "-E- Rom: " << tosecs.at(i).SHA << " set to missing!";
                    }

                    counter++;

                } else {

                    if ( deepAnalyse ) {

                        fileIsEncrypted = false;

                        if ( AesKey.isEmpty() ) {

                            QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );
                            return;

                        } else {

                            fileIsEncrypted = true;

                            param.clear();
                            param << "-d" << "-p" << AesKey << tosecs.at(i).PATH + ".aes";

                            if ( ! ExecuteProgram(AesTool, param, true)  ) {

                                m_beenden = true;

                                ResetStatusBar();

                                QApplication::restoreOverrideCursor();

                                return;
                            }
                        }

                        // Alle Files des Archives entpacken...
                        QStringList files = JlCompress::extractDir(tosecs.at(i).PATH, m_TempPath);

                        if ( files.isEmpty() ) {

                            ui->tableWidgetInfo->insertRow( counter );

                            QTableWidgetItem *item1 = new QTableWidgetItem();
                            item1->setText( "-E- Zip is empty - " + QString(tosecs.at(i).PATH ) );
                            ui->tableWidgetInfo->setItem( counter, 0, item1 );

                            missingSha1 << tosecs.at(i).SHA;

                            counter++;

                        } else {

                            foreach(QString filename, files) {

                                if (tosecs.at(i).SHA != QString::fromLatin1(fileChecksum(filename, QCryptographicHash::Sha1).toHex())) {

                                    ui->tableWidgetInfo->insertRow( counter );

                                    QTableWidgetItem *item1 = new QTableWidgetItem();
                                    item1->setText( "-E- SHA doesn't match " + QString(tosecs.at(i).PATH ) );
                                    ui->tableWidgetInfo->setItem( counter, 0, item1 );

                                    missingSha1 << tosecs.at(i).SHA;

                                    counter++;
                                }
                            }
                        }

                        if ( fileIsEncrypted ) {

                            // Dann können wir das ZipFile wieder aufräumen...
                            finfo.setFileName( tosecs.at(i).PATH );
                            finfo.remove();
                        }

                        clearDir(m_TempPath);
                    }

                }

            } else {

                if ( deepAnalyse ) {

                    // Alle Files des Archives entpacken...
                    QStringList files = JlCompress::extractDir(tosecs.at(i).PATH, m_TempPath);

                    if ( files.isEmpty() ) {

                        ui->tableWidgetInfo->insertRow( counter );

                        QTableWidgetItem *item1 = new QTableWidgetItem();
                        item1->setText( "-I- Zip is empty - " + QString(tosecs.at(i).PATH ) );
                        ui->tableWidgetInfo->setItem( counter, 0, item1 );

                        missingSha1 << tosecs.at(i).SHA;

                        values.clear();
                        values << "missing" << tosecs.at(i).ID;

                        if ( m_db.updateRomPathById(values) ) {
                            qDebug() << "-I- Rom: " << tosecs.at(i).SHA << " set to missing!";
                        }

                        counter++;
                    } else {

                    }

                    clearDir(m_TempPath);
                }

                storageSize = storageSize + finfo.size();
            }
        } else {

            //const QString storePath = m_FileStorage + tosecs.at(i).SYSTEM + "/" + tosecs.at(i).SETNAME + "/" + tosecs.at(i).SHA + ".zip" ;
            const QString storePath = m_FileStorage + tosecs.at(i).SYSTEM + "/" + tosecs.at(i).SHA + ".zip" ;

            if ( m_tools.fileExists( storePath ) ||
                 m_tools.fileExists( storePath + ".aes" )) {
                if (m_db.updateRomPathById( QVariantList() << storePath << tosecs.at(i).ID ) ) {

                }
            }
        }

        QCoreApplication::processEvents();
    }

    ui->tableWidgetInfo->resizeColumnsToContents();
    ui->tableWidgetInfo->resizeRowsToContents();

   // QSettings settings("state.ini", QSettings::IniFormat);
   // QByteArray MyArray = settings.value(QString("mainTableWidth%1").arg(m_GridMode), "").toByteArray();
   // ui->tableWidgetInfo->horizontalHeader()->restoreState(MyArray);

    this->clearDir(m_CachePath, false, false, ui->cboSystems->currentText() + ".cache");
    this->clearDir(m_CachePath, false, false, "Systems.cache");

    ResetStatusBar();

    QApplication::restoreOverrideCursor();

    if ( missingSha1.count() == 0 ) {
        QMessageBox::information(this, this->windowTitle(),  tr("Your database is equal to your storage") );
    } else {
        QMessageBox::information(this, this->windowTitle(),  tr("%1 discrepancy corrected").arg(missingSha1.count()) );
    }

    on_cboSystems_currentTextChanged(ui->cboSystems->currentText());

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::loadWebView(QString url, bool ignoreLock, bool updateAllowed)  {

    if ( url.isEmpty() ) {
        qDebug() << "loadWebView" << "url is empty...";
        return;
    }

    if ( ignoreLock || ( ! ui->chkWebViewLocked->isChecked() ) ) {

        //if ( QUrl( url ).path() == ui->webView->url().path() ) {
        //    return;
        //}

        qDebug() << "setting: " + url + " in webView...";

        m_updateTitleAllow = false;

        if ( m_settings.loadBoolSetting(m_sSettingsFile, "Link", "extern") ) {
            QDesktopServices::openUrl(QUrl( url ));
        } else {
            ui->grpBrowser->setHidden(false);

            m_updateTitleAllow = updateAllowed ;

            ui->webView->load( QUrl( url ));
        }
    }
}

static const QSize resultSize(50, 50);

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QPoint MainWindow::imagePos(const QImage &image) const
{
    return QPoint((resultSize.width() - image.width()) / 2,
                  (resultSize.height() - image.height()) / 2);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::loadImage(const QString &fileName, QImage *image)
{
    image->load(fileName);

    // Scale the image to given size
    *image = image->scaled(resultSize, Qt::KeepAspectRatio);

    QImage fixedImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&fixedImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(fixedImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(imagePos(*image), *image);
    painter.end();

    *image = fixedImage;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::iniToolBarYoutube( ) {

    QImage imagestripe, imagecontent, resultImage(resultSize, QImage::Format_ARGB32_Premultiplied);

    loadImage(":/images/images/youtube/strip.gif", &imagestripe);

    ui->toolBarYoutube->clear();

    ui->toolBarYoutube->setIconSize(QSize(50,50));

    QStringList videos = m_settings.GetAllKeys("youtube.ini", m_currentYoutubeChannel);

    for (int i = 0; i < videos.size(); ++i) {

        QString baseurl = m_settings.loadStringSetting("youtube.ini", videos.at(i), "baseurl");
        QString title = m_settings.loadStringSetting("youtube.ini", videos.at(i), "title");
        QString pic = m_settings.loadStringSetting("youtube.ini", videos.at(i), "picture");

        qDebug() << "iniToolBarYoutube" << title;

        QFileInfo fi;
        fi.setFile( pic );

        if ( ! fi.exists() ) { // Datei nicht gefunden

            pic = ":/images/images/youtube/missing.png";            
        }

        if ( ! baseurl.isEmpty() ) {

            QAction *action = new QAction( QString("actionYoutube%1").arg(i), nullptr);

            action->setToolTip( title );
            action->setObjectName( QString("Youtube%1").arg(i) );
            action->setData( QVariant::fromValue( videos.at(i) ));

            loadImage(pic, &imagecontent);

            QPainter::CompositionMode mode = QPainter::CompositionMode_Multiply;

            QPainter painter(&resultImage);
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.fillRect(resultImage.rect(), Qt::transparent);
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            painter.drawImage(0, 0, imagecontent);
            painter.setCompositionMode(mode);
            painter.drawImage(0, 0, imagestripe);
            painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
            painter.fillRect(resultImage.rect(), Qt::transparent);
            painter.end();

            action->setIcon( QIcon( QPixmap::fromImage(resultImage) ));

            ui->toolBarYoutube->addAction( action );
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QString MainWindow::GetRandomString()
{
   QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   int randomStringLength = 12; // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::GetYoutubeInformations(QUrl iUrl) {

    QString title, url, thumbnail ;

    if ( m_currentYoutubeChannel.isEmpty() ) {
        QMessageBox::information(this, this->windowTitle(),  tr("No youtube channel selected!") );
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);

    qDebug() << "Gathering datas for " << iUrl.toString();

    SetStatusBar(1, 4, 1,  "gathering youtube url data...", true );
    url =  GetYoutubeVideoUrl(iUrl);
    if ( url.isEmpty() ) {
        qDebug() << "GetYoutubeVideoUrl - no data received...";
        ResetStatusBar();
        return;
    } else {
        qDebug() << "GetYoutubeVideoUrl" << url;
    }

    SetStatusBar(1, 4, 2,  "gathering youtube title data...", false );
    title = GetYoutubeVideoTitle(iUrl);
    qDebug() << "GetYoutubeVideoTitle" << title ;

    SetStatusBar(1, 4, 3,  "gathering youtube thumbnail data...", false );
    thumbnail = GetYoutubeVideoThumbnail(iUrl, GetRandomString() );
    qDebug() << "GetYoutubeVideoThumbnail" << thumbnail ;

    SetStatusBar(1, 4, 4,  "gathering youtube data finished", false );

    m_settings.saveStringSetting("youtube.ini", m_currentYoutubeChannel, title, "");

    m_settings.saveStringSetting("youtube.ini", title, "baseurl", iUrl.toString());
    m_settings.saveStringSetting("youtube.ini", title, "title",   title);
    m_settings.saveStringSetting("youtube.ini", title, "picture", thumbnail);
    m_settings.saveStringSetting("youtube.ini", title, "videurl", url);

    QApplication::restoreOverrideCursor();

    iniToolBarYoutube( ) ;

    ResetStatusBar();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QString MainWindow::GetYoutubeVideoUrl(QUrl iUrl) {

    QString program = "Youtube-dl";
    QString url;
    QStringList args;

    args << "--no-check-certificate" << "--get-url" << iUrl.toString() << "-f" << "best";

    if ( ExecuteProgram(program, args, true) ) {
        foreach (QString line, m_stdOutLines){
           url = url + line;
        }
    }

    return url;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QString MainWindow::GetYoutubeVideoTitle(QUrl iUrl) {

    QString program = "Youtube-dl";
    QString title;
    QStringList args;

    args << "--no-check-certificate" << "--get-title" << iUrl.toString();

    if ( ExecuteProgram(program, args, true) ) {
        foreach (QString line, m_stdOutLines){
           title = title + line;
        }
    }

    return title;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QString MainWindow::GetYoutubeVideoThumbnail(QUrl iUrl, QString iFileName) {

    QString program = "Youtube-dl";
    QString thumb;
    QStringList args;

    args << "--no-check-certificate" << "--get-thumbnail" << iUrl.toString();

    if ( ExecuteProgram(program, args, true) ) {
        foreach (QString line, m_stdOutLines){
           thumb = thumb + line;
        }
    }

    QFileInfo fi;
    fi.setFile( QUrl(thumb).fileName() ) ;

    QString fileName = downloadFile(thumb, iFileName + "." + fi.suffix(), m_ImageCachePath + "/Youtube/" ) ;

    return fileName;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::saveFile()
{
    QByteArray data = m_pImgCtrl->downloadedData();
    QString fileName = m_pImgCtrl->getFileName();

    if ( data.isEmpty() )  {

        qDebug() << "-E- FileDownloader - no data received";
        QMessageBox::information(this, this->windowTitle(),  tr("No data received!") );

    } else {

        QFile file( fileName );

        if (!file.open(QIODevice::WriteOnly)) {

            qDebug() << "-E- FileDownloader - unable to open file: " + fileName;

        } else {

            file.write( m_pImgCtrl->downloadedData() );
            file.close();

            qDebug() << "-I- FileDownloader - file: " + fileName + " written...";
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::handleToolBarYoutube(QAction *action) {

    QFileInfo fi;

    QString section = qvariant_cast<QString>(action->data());

    QString baseurl = m_settings.loadStringSetting("youtube.ini", section, "baseurl");
    QString pic = m_settings.loadStringSetting("youtube.ini", section, "picture");
    QString videourl;

    fi.setFile( pic );
    if ( ! fi.exists() ) {

        QString thumbnail = GetYoutubeVideoThumbnail(baseurl, GetRandomString() );
        if ( thumbnail.isEmpty() ) {
            qDebug() << "GetYoutubeVideoThumbnail" << "thumbnail is empty..." ;
            return;
        }
        qDebug() << "GetYoutubeVideoThumbnail" << thumbnail ;

        m_settings.saveStringSetting("youtube.ini", section, "picture", thumbnail);

        iniToolBarYoutube( ) ;
    }

    videourl = this->GetYoutubeVideoUrl(baseurl);
    if ( videourl.isEmpty() ) {
        qDebug() << "GetYoutubeVideoThumbnail" << "videourl is empty..." ;
        return;
    }

    if ( ! videourl.isEmpty() ) {

        ui->lblCover->setHidden(true);
        ui->lblMedia->setHidden(true);

        ui->widAmigaRemix->setHidden( true );
        ui->widSidPlayer->setHidden( true );
        ui->widTheModArchive->setHidden( true );

        ui->widMP3->stopPlayer();

        ui->widMP3->setHidden(false);
        ui->widMP3->playVideoFile( videourl );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_actionLockStorage_triggered()
{
    QString filename;
    QStringList param;
    QFileInfo fi;
    QFile srcFile;
    int filecnt, loopcnt = 0;

    QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
    QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

    if ( AesKey.isEmpty() ) {

      QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );
      return;
    }

    QFile file(QFileDialog::getExistingDirectory(this, "Open"));

    if ( file.exists() ) {

        filecnt = countFilesInDir(file.fileName());

        QApplication::setOverrideCursor(Qt::WaitCursor);

        QDirIterator it2(file.fileName(), QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

        while (it2.hasNext() && ! m_beenden ) {

            filename = it2.next();

            if ( it2.fileInfo().isFile() ) {

                SetStatusBar(0, filecnt, loopcnt,  "processing " + QString("%1").arg(filecnt) + " files... processed: " +  QString("%1").arg(loopcnt), ( loopcnt==0?true:false ) );

                if ( it2.fileInfo().suffix() != "aes" ) {

                    param.clear();
                    param << "-e" << "-p" << AesKey << filename;

                    if ( ExecuteProgram(AesTool, param, true) ) {

                        fi.setFile(filename + ".aes" );

                        if ( fi.exists() ) {

                            srcFile.setFileName(filename);
                            if ( srcFile.remove() ) {
                                qDebug() << filename << "removed...";
                            }
                        }

                    } else {
                        m_beenden = true;
                    }
                } else {
                   //  qDebug() << filename << "alredy encrypted...";
                }

                loopcnt++;
            }
        }

        QApplication::restoreOverrideCursor();

        QMessageBox::information(this, this->windowTitle(),  tr("AES encryption done!!!") );

        file.close();
    }

    ResetStatusBar();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_actionUnlockStorage_triggered()
{
    QString filename;
    QStringList param;
    QFileInfo fi;
    QFile srcFile;
    int filecnt, loopcnt = 0;

    QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
    QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

    QByteArray sourcefile;
    QByteArray destfile;
    QByteArray key = AesKey.toUtf8();

    if ( AesKey.isEmpty() ) {
      QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );
      return;
    }

    QFile file(QFileDialog::getExistingDirectory(this, "Open"));

    if( file.exists() ) {

        filecnt = countFilesInDir(file.fileName());

        QApplication::setOverrideCursor(Qt::WaitCursor);

        QDirIterator it2(file.fileName(), QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

        while (it2.hasNext() && ! m_beenden ) {

            filename = it2.next();

            if ( it2.fileInfo().isFile() ) {

                SetStatusBar(0, filecnt, loopcnt,  "processing " + QString("%1").arg(filecnt) + " files... processed: " +  QString("%1").arg(loopcnt), ( loopcnt==0?true:false ) );

                if ( it2.fileInfo().suffix().contains("aes") ) {

                    param.clear();
                    param << "-d" << "-p" << AesKey << filename;

                    if ( ExecuteProgram(AesTool, param, true) ) {

                        fi.setFile(filename.remove(".aes") );

                        if ( fi.exists() ) {

                            srcFile.setFileName(filename + ".aes");
                            if ( srcFile.remove() ) {
                                qDebug() << filename << "removed...";
                            }
                        }
                    } else {
                        m_beenden = true;
                    }

                } else {
                    // qDebug() << filename << "alredy decrypted...";
                }

                loopcnt++;
            }
        }

        QApplication::restoreOverrideCursor();

        QMessageBox::information(this, this->windowTitle(),  tr("AES decryption done!!!") );

        file.close();
    }

    ResetStatusBar();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
int MainWindow::countFilesInDir(QString directory) {

    int filecnt = 0;

    QDirIterator it(directory, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {

        if ( filecnt % 100 == 0 ) {
            QCoreApplication::processEvents();
        }

        it.next();

        if ( it.fileInfo().isFile() ) {
            filecnt++;
        }
    }

    return(filecnt);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_webView_loadProgress(int progress)
{
    ui->prgWebViewLoading->setValue(progress);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_webView_loadStarted()
{
    ui->prgWebViewLoading->setVisible( true );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_webView_loadFinished(bool arg1)
{
    ui->prgWebViewLoading->setVisible( ! arg1 );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_actionDropbox_triggered()
{
    DropboxBrowser *dialog = new DropboxBrowser(this);

    dialog->setWindowFlags(Qt::Window);
    dialog->setModal(true);
    dialog->show();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_chkLoadAll_clicked()
{
    on_cboSystems_currentTextChanged(ui->cboSystems->currentText());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_cmdShowFile_clicked()
{
    QString     romimage;
    QStringList files;
    QFile       romfile;
    QStringList param;
    bool        fileIsEncrypted = false;
    QFileInfo   fi;

    if ( ui->tableWidget->rowCount() == 0 ) {
        return;
    }

    clearDir(m_TempPath);

    QTableWidgetItem *c = new QTableWidgetItem();

    c = ui->tableWidget->item(3, 1); // PATH

    romfile.setFileName( c->text() );
    if ( ! romfile.exists() ) {

        romfile.setFileName( c->text() + ".aes" );
        if ( ! romfile.exists() ) {
            QMessageBox::information(this, this->windowTitle(),  tr("ROM ZIP nicht gefunden - ") + c->text() );
            return;
        } else {

            QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
            QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

            if ( AesKey.isEmpty() ) {

                QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );
                return;

            } else {

                fileIsEncrypted = true;

                param.clear();
                param << "-d" << "-p" << AesKey << c->text() + ".aes";

                if ( ! ExecuteProgram(AesTool, param, true) ) {
                    return;
                }
            }
        }
    }

    qDebug() << "unzip" << c->text();

    // Alle Files des Archives entpacken...
    files = JlCompress::extractDir(c->text(), m_TempPath);

    if ( files.size() == 1 ) {

        romimage = files.at(0);

    } else {
        for (int i = 0; i < files.size(); ++i) {

            if ( files.at(i).contains(".cue") ) {
                romimage = files.at(i);
            }
        }
    }

    if ( fileIsEncrypted ) {

        // Dann können wir das ZipFile wieder aufräumen...
        romfile.setFileName( c->text() );
        romfile.remove();
    }

    if ( files.count() > 0 ){

        if ( romimage.contains(".pdf")) {

            PDFViewer *myPDFViewer = new PDFViewer(this, romimage );
            myPDFViewer->setWindowFlags(Qt::Window);
            myPDFViewer->show();

        } else {

            qDebug() << "QDesktopServices::openUrl" << "file://" + romimage;

            QDesktopServices::openUrl ( QUrl ( "file:///" + romimage, QUrl::TolerantMode )) ;
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::setStartButtonMode(bool imode)
{
    ui->cmdStartEmu->setEnabled(imode);
    ui->cmdTheGamesDB->setEnabled(imode);
    ui->cboStartups->setEnabled(imode);
    ui->edtSystems->setEnabled(imode);
    ui->cmdShowFile->setEnabled(imode);
    ui->cmdUpload->setEnabled(imode);
    ui->cmdExtract->setEnabled(imode);

    if ( ! imode ) {
        m_screenshotfilelist.clear();
        m_mediafilelist.clear();
        m_coverfilelist.clear();
        m_soundtracklist.clear();
    }
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::on_cmdManuals_clicked()
{ 
    QString filename = this->downloadFile(m_actManualValue, "", m_CachePath );

    if ( ( ! filename.isEmpty() ) && filename.contains(".pdf") ) {

        PDFViewer *myPDFViewer = new PDFViewer(this, filename );
        myPDFViewer->setWindowFlags(Qt::Window);
        myPDFViewer->show();
    }
}

void MainWindow::on_cmdBrowserForward_clicked()
{
    ui->webView->forward();
}

void MainWindow::on_cmdBrowserBack_clicked()
{
    ui->webView->back();
}

void MainWindow::on_cmdSoundtrack_clicked()
{
    if ( ! m_soundtracklist.isEmpty() && ui->widMP3->isHidden() ) {

        ui->lblCover->setHidden(true);
        ui->lblMedia->setHidden(true);

        ui->widAmigaRemix->setHidden( true );
        ui->widSidPlayer->setHidden( true );
        ui->widTheModArchive->setHidden( true );

        QTableWidgetItem *sys,*set,*sha, *tit = new QTableWidgetItem();

        sys = ui->tableWidget->item(0, 1); // System
        set = ui->tableWidget->item(1, 1); // Set
        sha = ui->tableWidget->item(6, 1); // Sha
        tit = ui->tableWidget->item(4, 1); // Title

        QString ss = m_TosecMain + "/Stuffpacks/" + sys->text() + "/" + sha->text() + "/soundtrack";

        ui->widMP3->setFilePath( ss );

    } else {

        ui->lblCover->setHidden(false);
        ui->lblMedia->setHidden(false);

        ui->widMP3->stopPlayer();

        ui->widMP3->setHidden(true);
    }
}

void MainWindow::on_cmdYoutubeVideo_clicked()
{
    if ( ! m_actRomVideoValue.isEmpty() && ui->widMP3->isHidden() ) {

        ui->lblCover->setHidden(true);
        ui->lblMedia->setHidden(true);

        QString url = GetYoutubeVideoUrl(m_actRomVideoValue);

        ui->widMP3->setHidden(false);
        ui->widMP3->playVideoFile( url );

    } else {

        ui->lblCover->setHidden(false);
        ui->lblMedia->setHidden(false);

        ui->widMP3->stopPlayer();

        ui->widMP3->setHidden(true);
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QString MainWindow::downloadFile(QUrl iUrl, QString fileName, QString iDest, bool force) {

    if ( ! iUrl.isValid() ) {
        if (  ! iUrl.toString().isEmpty() ) {
            qDebug() << "downloadFile" << iUrl.toString() << "not valid!";
        }
        return "";
    }

    if ( m_tools.fileExists( iUrl.toLocalFile() ) ) {
        qDebug() << "downloadFile" << iUrl.toLocalFile() << "FileExists true!";
        return iUrl.toLocalFile() ;
    }

   this->showMessage( QString("getting file from URL: %1").arg(iUrl.toDisplayString()) );
    QCoreApplication::processEvents();

    if ( iUrl.url().isEmpty() ) {
        return "";
    }

    QString program = "wget.exe";
    QString destFileName;
    QString output;
    QStringList args;

    if  ( fileName.isEmpty() ) {
        destFileName = iDest + iUrl.fileName();
    } else {
        destFileName = iDest + fileName;
    }

    QFileInfo fi;
    fi.setFile( destFileName ) ;

    if ( ( ! ( fi.exists() && fi.size() > 0 )  ) || force ) {

        qDebug() << "downloadFile" << iUrl << " to: " << destFileName;

        args << "-O" << destFileName << "--no-check-certificate" << "--user-agent=Mozilla" << iUrl.toString();

        qDebug() << args;

        if ( ExecuteProgram(program, args, true) ) {
            foreach (QString line, m_stdOutLines){
               output = output + line;
            }

            qDebug() << "downloadFile" << destFileName << " retrieved...";
        }
    } else {
        // qDebug() << "downloadFile" << destFileName << " already exists...";
    }

    if ( ! fi.exists() ) {
        destFileName.clear();
    }

    this->showMessage("");

    return destFileName;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::loadStuffPackContents(int id) {

    rom_type    rom;
    QStringList entries, directories;
    QString     entry;
    QDir        directory;
    QString     folder;
    QFileInfo   fi;
    QString     filename;

    directories << "cover" << "media" << "screenshot" << "soundtrack";

    if ( m_db.selectRomData( id, rom ) ) {

        QString stuffDir = m_TosecMain + "/Stuffpacks/" + rom.SYSTEM + "/" + rom.SHA ;

        QString infoFile = stuffDir + "/" + "info.txt";

        fi.setFile(infoFile);
        if ( !fi.exists() ) {
            return;
        }

        foreach (const QString &dir, directories) {

            // Covers laden
            entries << m_settings.GetAllKeys(infoFile, dir);

            foreach (const QString &str, entries) {

                entry = m_settings.loadStringSetting(infoFile, dir, str);

                folder = stuffDir + "/" + dir +"/";

                if ( directory.mkpath( folder ) ) {

                    filename = QUrl(entry).fileName();

                    this->downloadFile(entry, filename, folder );
                }
            }
        }
    }
}

void MainWindow::on_edtSearch_returnPressed()
{
    this->on_cmdAll_clicked();
}

void MainWindow::on_actionPDFViewer_triggered()
{
    PDFViewer *myPDFViewer = new PDFViewer(this, "" );
    myPDFViewer->setWindowFlags(Qt::Window);
    myPDFViewer->show();
}


void MainWindow::on_cmdExtract_clicked()
{
    QStringList files;
    QFile       romfile;
    QStringList param;
    bool        fileIsEncrypted = false;
    QFileInfo   src;
    QFileInfo   dest;
    QFileInfo   fi;

    if ( ui->tableWidget->rowCount() == 0 ) {
        return;
    }

    QString destDir = QFileDialog::getExistingDirectory(this, tr("Save image to..."), "", QFileDialog::ShowDirsOnly);

    if (  destDir.isEmpty() ) {
        return;
    }

    QTableWidgetItem *c, *a, *r, *s, *e, *t, *n  = new QTableWidgetItem();

    c = ui->tableWidget->item(3, 1);  // PATH
    a = ui->tableWidget->item(10, 1); // EATTR
    r = ui->tableWidget->item(13, 1); // ROMSET

    s = ui->tableWidget->item(0, 1); // SYSTEM
    n = ui->tableWidget->item(2, 1); // NAME
    e = ui->tableWidget->item(1, 1); // SETNAME
    t = ui->tableWidget->item(4, 1); // TITLE

    fi.setFile(n->text());

    if ( this->useFileCache() && checkFileInCache( fi.fileName() ) ) {

        qDebug() << "use file from cache..." + m_CachePath + fi.fileName() ;
        files.append( m_CachePath + fi.fileName() );

    } else {

        // Alle Files des Archives entpacken...

        romfile.setFileName( c->text() );
        if ( ! romfile.exists() ) {

            romfile.setFileName( c->text() + ".aes" );
            if ( ! romfile.exists() ) {
                QMessageBox::information(this, this->windowTitle(),  tr("ROM ZIP nicht gefunden - ") + c->text() );
                return;
            } else {

                QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
                QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

                if ( AesKey.isEmpty() ) {

                    QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );
                    return;

                } else {

                    fileIsEncrypted = true;

                    param.clear();
                    param << "-d" << "-p" << AesKey << c->text() + ".aes";

                    ExecuteProgram(AesTool, param, true);
                }
            }
        }

        qDebug() << "unzip" << c->text();

        if ( this->useFileCache() ) {
            files = JlCompress::extractDir(c->text(), m_CachePath);
        } else {
            files = JlCompress::extractDir(c->text(), m_TempPath);
        }
    }

    if ( fileIsEncrypted ) {

        // Dann können wir das ZipFile wieder aufräumen...
        romfile.setFileName( c->text() );
        romfile.remove();
    }

    if ( ! files.isEmpty() ){

        QString childes = this->getRomSetDiskFiles(r->text());
        if ( ! childes.isEmpty() ) {
            files.append(childes.split("|"));
        }

        qDebug() << files;

        if ( ! destDir.isEmpty() ) {

            foreach (const QString &str, files) {

                src = str;
                dest = destDir + "/" + src.fileName();

                qDebug() << "Source: " << src.absoluteFilePath();
                qDebug() << "Dest: " << dest.absoluteFilePath();

                if ( ! dest.exists() && src.isFile() ) {

                    if ( ! ( QFile::copy(str, dest.absoluteFilePath() ) ) ) {
                        qDebug() << "Image copy error!" << str <<  dest.absoluteFilePath();
                    } else {
                        qDebug() << "FileCopy OK!";
                    }
                }
            }
        }

        QMessageBox::information(this, this->windowTitle(),  tr("%1\n\nprepared in folder %2").arg(n->text()).arg(destDir) );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::buildUploadZipFiles(QString system, QString setName) {

    QFile       file;
    QString     filename;
    QStringList files;
    QStringList param;
    QFile       scrFileName;
    QFileInfo   fileInfo;
    bool        doEncryption = false;
    QString     saveFileName;
    Zip         zip;
    int         counter = 0;
    QString     basename;
    rom_type    rom;
    QList<rom_type> roms;

    QString     AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

    if ( setName.isEmpty() ) {

        saveFileName = QFileDialog::getSaveFileName(this, tr("Save Archive"),
                                   m_TempPath + "/" + system + ".zip",
                                   tr("Archives (*.zip)"));


        file.setFileName( m_FileStorage + "/" + system );

    } else {

        saveFileName = QFileDialog::getSaveFileName(this, tr("Save Archive"),
                                   m_TempPath + "/" + setName +".zip",
                                   tr("Archives (*.zip)"));

        file.setFileName( m_FileStorage + "/" + system + "/" + setName );
    }

    if ( saveFileName.isEmpty() ) {
        return;
    }

    if( file.exists() ) {

       this->showMessage("get rom list...");

        QDirIterator it2(file.fileName(), QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

        while ( it2.hasNext() ) {

            filename = it2.next();

            if ( it2.fileInfo().isFile() ) {

                counter++;

               this->showMessage(QString("uncrypt and prepare rom list %1").arg(counter));

                if ( it2.fileInfo().suffix() == "aes" ) {

                    doEncryption = true;

                    param.clear();
                    param << "-d" << "-p" << m_AesKey << filename;

                    if ( ExecuteProgram(AesTool, param, true) ) {

                        filename.remove(".aes");

                        fileInfo.setFile( filename );

                        basename = fileInfo.baseName();

                        roms.clear();
                        roms = m_db.selectRomDataBySha1( system, basename );
                        if ( roms.count() > 0 ) {

                            foreach (rom, roms) {

                                if ( m_tools.fileCopy( filename, m_TempPath + "/" + fileInfo.fileName().replace(basename, rom.NAME) ) ) {
                                    files << m_TempPath + "/" + fileInfo.fileName().replace(basename, rom.NAME) ;
                                } else {
                                    return;
                                }

                                // Dann können wir das ZipFile wieder aufräumen...
                                scrFileName.setFileName( filename );
                                scrFileName.remove();
                            }
                        }
                    } else {
                        return;
                    }

                } else {
                    files << it2.fileInfo().absoluteFilePath();
                }
            }

            QCoreApplication::processEvents();
        }

       this->showMessage("generate zip file: " + saveFileName);

        if ( ! zip.archive ( saveFileName, files, QString("") ) ) {

            qDebug() << "-E- File compress error... ";
            QMessageBox::information(this, this->windowTitle(),  tr("Zip-File creation error!"));

        } else {

            if ( doEncryption ) {
                this->clearDir(m_TempPath, false);
            }

            QMessageBox::information(this, this->windowTitle(),  tr("Zip-File creation successfull - ") + saveFileName );
        }

       this->showMessage("");

    } else {
        qDebug() << "-E- Directory not found... " + file.fileName();
    }

    file.close();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::buildStuffpackZipFiles(QString system, QString setName) {

    QDir       file;
    QString     saveFileName;
    Zip         zip;

    if ( setName.isEmpty() ) {

        saveFileName = QFileDialog::getSaveFileName(this, tr("Save Archive"),
                                   m_TempPath + "/" + system + "_stuffpack.zip",
                                   tr("Archives (*.zip)"));


        file.setPath( m_TosecMain + "/Stuffpacks/" + system );

    } else {

        saveFileName = QFileDialog::getSaveFileName(this, tr("Save Archive"),
                                   m_TempPath + "/" + setName +"_stuffpack.zip",
                                   tr("Archives (*.zip)"));

        file.setPath( m_TosecMain + "/Stuffpacks/" + system + "/" + setName );
    }

    if ( saveFileName.isEmpty() ) {
        return;
    }

    if( file.exists() ) {

       this->showMessage("generate zip file: " + saveFileName);

        if ( ! zip.archive ( saveFileName, file, QString("") ) ) {

            qDebug() << "-E- File compress error... ";

            QMessageBox::information(this, this->windowTitle(),  tr("Zip-File creation error!"));

        } else {

            QMessageBox::information(this, this->windowTitle(),  tr("Zip-File creation successfull - ") + saveFileName );
        }

       this->showMessage("");

    } else {
        qDebug() << "-E- Directory not found... " + file.absolutePath();
    }
}

void MainWindow::on_chkTailLog_clicked(bool checked)
{
    ui->edtLogFile->setHidden ( !checked );

    if ( ! ui->edtLogFile->isHidden() ) {
        this->tailLogfile();
    }
}

void MainWindow::tailLogfile() {

    QFile file("TosecRC.log");

    if(file.open(QIODevice::ReadOnly)) {

        file.seek(file.size()-1);

        int count = 0;
        int lines = 10;

        while ( (count < lines) && (file.pos() > 0) )
        {
            QString ch = file.read(1);
            file.seek(file.pos()-2);
            if (ch == "\n")
                count++;
        }
        ui->edtLogFile->setText( file.readAll() );

        file.close();
    }

    // put the slider at the bottom
    ui->edtLogFile->verticalScrollBar()->setSliderPosition(ui->edtLogFile->verticalScrollBar()->maximum());
}

void MainWindow::on_chkTailLog_stateChanged(int arg1)
{
    if ( arg1 == 1 ) {
        mLogFileTimer->start(1000);
    } else {
        mLogFileTimer->stop();
    }
}

void MainWindow::on_tableWidgetInfo_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    if ( current && ! current->text().isEmpty()) {
        this->on_tableWidgetInfo_itemClicked(current);
    }
}

void MainWindow::webViewLoadFinished(bool ok) {

    if ( ok && m_updateTitleAllow ) {

        QUrl url(ui->webView->url());

        if ( ! QString( m_settings.loadStringSetting("link.ini", m_currentLinkChannel, url.host() ) ).isEmpty() ) {

            m_settings.saveStringSetting("link.ini", m_currentLinkChannel, url.host(), url.toString() + "|" + ui->webView->title());

            this->iniToolBarLinks();
        }        
    }

    ui->edtBrowserUrl->setText( ui->webView->url().toString() );
}

void MainWindow::on_chkOnlyCue_clicked()
{
     this->setCurrentItem( ui->listWidget->currentItem() );
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    this->setCurrentItem( current );
}

void MainWindow::on_cmdTheGamesDB_clicked()
{
    QTableWidgetItem *sys,*set,*sha, *tit = new QTableWidgetItem();

    sys = ui->tableWidget->item(0, 1); // System
    set = ui->tableWidget->item(1, 1); // Set
    sha = ui->tableWidget->item(6, 1); // Sha
    tit = ui->tableWidget->item(4, 1); // Title

    QString ss = m_TosecMain + "/Stuffpacks/" + sys->text() + "/" + sha->text() + "/";

    QDir dir;
    dir.mkpath(ss);

    ss.append( "info.txt" );

    mTheGamesDB = new TheGamesDB( this, ss, tit->text(), ui->cboSystems->currentText(), m_CachePath );

    mTheGamesDB->show();
}

bool MainWindow::currentConnectivityStatus()
{
    bool connected = false;

    QNetworkAccessManager *namanager = new QNetworkAccessManager(this);
    switch (namanager->networkAccessible()) {
        case QNetworkAccessManager::UnknownAccessibility:
            //qDebug() << Q_FUNC_INFO << "QNetworkAccessManager::UnknownAccessibility";
            break;
        case QNetworkAccessManager::NotAccessible:
            //qDebug() << Q_FUNC_INFO << "QNetworkAccessManager::NotAccessible";
            break;
        case QNetworkAccessManager::Accessible:
            //qDebug() << Q_FUNC_INFO << "QNetworkAccessManager::Accessible";
            break;
        default:
            break;
    }

    QNetworkConfigurationManager manager;
    //qDebug()<< Q_FUNC_INFO << " network connection " << manager.isOnline();

    QNetworkConfiguration cfg = manager.defaultConfiguration();
    QNetworkSession *session = new QNetworkSession(cfg);
    session->open();
    session->waitForOpened();

    if(session->isOpen())
    {
        switch (session->state()) {
        case QNetworkSession::Connected:
            //qDebug() << Q_FUNC_INFO << "QNetworkSession::connected";
            connected = true;
            break;
        case QNetworkSession::Disconnected:
            //qDebug() << Q_FUNC_INFO << "QNetworkSession::disconnect";
            break;
        default:
            break;
        }
    }

    return(connected);
}

void MainWindow::checkConnection() {

    if ( this->currentConnectivityStatus() ) {
        m_wwInternetLed->setColor( Qt::green );
    } else {
        m_wwInternetLed->setColor( Qt::red );
    }
}

void MainWindow::on_cboHtmlLinks_currentTextChanged(const QString &arg1)
{
    this->loadWebView( arg1 );
}

void MainWindow::on_cmdPCB_clicked()
{
    qDebug() << m_actPcbUrl;

    QString filename = this->downloadFile(m_actPcbUrl, "", m_CachePath );

    if ( ! filename.isEmpty() ) {

        qDebug() << filename;

        m_ImageViewer = new ImageViewer;
        m_ImageViewer->loadFile( filename );
        m_ImageViewer->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, m_ImageViewer->size(), qApp->desktop()->availableGeometry()));
        m_ImageViewer->show();
    }
}

void MainWindow::on_cmdSystemEdit_clicked()
{
    mSystemEditor = new SystemEditor;
    mSystemEditor->setSystemName( ui->cboSystems->currentText() );

    connect(mSystemEditor, SIGNAL(finished()), this, SLOT(SubDialogFinished()));

    mSystemEditor->show();
}


void MainWindow::createTrayIcon()
{
    QMenu *windowsMenu;

    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon( QIcon(":/program/icon/images/Mcdo-Design-Cats-2-Dot-Mac-Logo.ico") );
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();

    windowsMenu = menuBar()->addMenu(tr("&Windows"));
    windowsMenu->addAction(minimizeAction);
    windowsMenu->addAction(maximizeAction);
    windowsMenu->addAction(restoreAction);

    ui->lblImage1->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->lblImage1, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenuLabelImage1(QPoint)));

    ui->lblImage2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->lblImage2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenuLabelImage2(QPoint)));

    ui->lblCover->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->lblCover, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenuLabelCover(QPoint)));

    ui->lblMedia->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->lblMedia, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenuLabelMedia(QPoint)));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F12)
    {

    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F12)
    {
        //qDebug() << "You released F12";
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuLabelImage1(const QPoint& pos) {

    QPoint globalPos =ui->lblImage1->mapToGlobal(pos);

    QMenu myMenu;

    myMenu.addAction("view");

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( ! selectedItem ) {
        return;
    }

    if ( selectedItem->text().contains("view") ) {

        m_ImageViewer = new ImageViewer;
        m_ImageViewer->loadFile( ui->lblImage1->toolTip() );
        m_ImageViewer->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, m_ImageViewer->size(), qApp->desktop()->availableGeometry()));
        m_ImageViewer->show();
    }

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuLabelImage2(const QPoint& pos) {

    QPoint globalPos =ui->lblImage2->mapToGlobal(pos);

    QMenu myMenu;

    myMenu.addAction("view");

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( ! selectedItem ) {
        return;
    }

    if ( selectedItem->text().contains("view") ) {

        m_ImageViewer = new ImageViewer;
        m_ImageViewer->loadFile( ui->lblImage2->toolTip() );
        m_ImageViewer->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, m_ImageViewer->size(), qApp->desktop()->availableGeometry()));
        m_ImageViewer->show();
    }

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuLabelCover(const QPoint& pos) {

    QPoint globalPos =ui->lblCover->mapToGlobal(pos);

    QMenu myMenu;

    myMenu.addAction("view");

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( ! selectedItem ) {
        return;
    }

    if ( selectedItem->text().contains("view") ) {

        m_ImageViewer = new ImageViewer;
        m_ImageViewer->loadFile( ui->lblCover->toolTip() );
        m_ImageViewer->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, m_ImageViewer->size(), qApp->desktop()->availableGeometry()));
        m_ImageViewer->show();
    }

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::ShowContextMenuLabelMedia(const QPoint& pos) {

    QPoint globalPos =ui->lblMedia->mapToGlobal(pos);

    QMenu myMenu;

    myMenu.addAction("view");

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( ! selectedItem ) {
        return;
    }

    if ( selectedItem->text().contains("view") ) {

        m_ImageViewer = new ImageViewer;
        m_ImageViewer->loadFile( ui->lblMedia->toolTip() );
        m_ImageViewer->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, m_ImageViewer->size(), qApp->desktop()->availableGeometry()));
        m_ImageViewer->show();
    }

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void MainWindow::getHexEditor() {

    if ( ui->tableWidget->rowCount() == 0 ) {
        return;
    }

    QString program;
    QStringList param;
    QStringList files;
    bool validfilefound = false;
    bool fileIsEncrypted = false;
    QFile romfile;

    QTableWidgetItem *c = new QTableWidgetItem();

    c = ui->tableWidget->item(3, 1);

    // Alle Files des Archives entpacken...

    romfile.setFileName( c->text() );
    if ( ! romfile.exists() ) {

        romfile.setFileName( c->text() + ".aes" );
        if ( ! romfile.exists() ) {
            QMessageBox::information(this, this->windowTitle(),  tr("ROM ZIP nicht gefunden - ") + c->text() );
            return;
        } else {

            QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
            QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

            if ( AesKey.isEmpty() ) {

                QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );
                return;

            } else {

                fileIsEncrypted = true;

                param.clear();
                param << "-d" << "-p" << AesKey << c->text() + ".aes";

                ExecuteProgram(AesTool, param, true);
            }
        }
    }

    files = JlCompress::extractDir(QDir::toNativeSeparators(c->text()), m_TempPath);

    param.clear();

    for (int i = 0; i < files.size(); ++i) {

        program = "HexEdit.exe";
        param << files.at(i);
        validfilefound = true;
    }

    if (validfilefound) {

        qDebug() << "getHexEditor" << program << param;

        ExecuteProgram(program, param, false);
    }
}


void MainWindow::on_cmdPortrait_clicked()
{
    qDebug() << m_actPartraitUrl;

    QString filename = this->downloadFile(m_actPartraitUrl, "", m_CachePath );

    if ( ! filename.isEmpty() ) {

        qDebug() << filename;

        m_ImageViewer = new ImageViewer;
        m_ImageViewer->loadFile( filename );
        m_ImageViewer->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, m_ImageViewer->size(), qApp->desktop()->availableGeometry()));
        m_ImageViewer->show();
    }
}

void MainWindow::on_cmdLink1_clicked()
{
    if ( ! ui->cmdLink1->toolTip().isEmpty() ) {
        this->loadWebView( ui->cmdLink1->toolTip() );
    }
}

void MainWindow::on_cmdLink2_clicked()
{
    if ( ! ui->cmdLink2->toolTip().isEmpty() ) {
        this->loadWebView( ui->cmdLink2->toolTip() );
    }
}

void MainWindow::on_cmdLink3_clicked()
{
    if ( ! ui->cmdLink3->toolTip().isEmpty() ) {
        this->loadWebView( ui->cmdLink3->toolTip() );
    }
}

void MainWindow::on_cmdLink4_clicked()
{
    if ( ! ui->cmdLink4->toolTip().isEmpty() ) {
        this->loadWebView( ui->cmdLink4->toolTip() );
    }
}

void MainWindow::setCurrentItem(QListWidgetItem *current) {

    m_Item = current;

    if (! m_Item) {
        return;
    }

    m_CurrentSet = m_Item->toolTip();

    m_settings.saveStringSetting("system.ini", ui->cboSystems->currentText(), "LastSelectedItem", current->text());

    m_screenshotfilelist.clear();
    m_soundtracklist.clear();
    m_mediafilelist.clear();
    m_coverfilelist.clear();

    ui->widGamebase->setHidden(true);
    ui->cmdManuals->setHidden(true);
    ui->cmdSoundtrack->setHidden(true);
    ui->cmdYoutubeVideo->setHidden(true);
    ui->widGamebase->setHidden(true);
    ui->cmdCodeTable->setHidden(true);
    ui->cmdSolution->setHidden(true);

    setInfos(m_Item->toolTip());

    setStartButtonMode(false);

    //on_cmdFavorite_clicked();
    on_cmdAll_clicked();
}

void MainWindow::autoDownload() {

    QStringList keys = m_settings.GetAllKeys("settings.ini", "Autodownload");

    qDebug() << "-I- autoDownload" << keys;

    foreach (const QString &key, keys) {

        const QString value = m_settings.loadStringSetting("settings.ini", "Autodownload", key);

        downloadFile(QUrl(value), "", value, true) ;
    }
}

void MainWindow::on_cmdUpload_clicked()
{
    {
        QString     romimage;
        QStringList files;
        QFile       romfile;
        QStringList param;
        bool        fileIsEncrypted = false;
        QFileInfo   fi;

        if ( ui->tableWidget->rowCount() == 0 ) {
            return;
        }

        clearDir(m_TempPath);

        QTableWidgetItem *c = new QTableWidgetItem();

        c = ui->tableWidget->item(3, 1); // PATH

        romfile.setFileName( c->text() );
        if ( ! romfile.exists() ) {

            romfile.setFileName( c->text() + ".aes" );
            if ( ! romfile.exists() ) {
                QMessageBox::information(this, this->windowTitle(),  tr("ROM ZIP nicht gefunden - ") + c->text() );
                return;
            } else {

                QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
                QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

                if ( AesKey.isEmpty() ) {

                    QMessageBox::information(this, this->windowTitle(),  tr("AES Tools not correctly configured!!!") );
                    return;

                } else {

                    fileIsEncrypted = true;

                    param.clear();
                    param << "-d" << "-p" << AesKey << c->text() + ".aes";

                    if ( ! ExecuteProgram(AesTool, param, true) ) {
                        return;
                    }
                }
            }
        }

        qDebug() << "unzip" << c->text();

        // Alle Files des Archives entpacken...
        files = JlCompress::extractDir(c->text(), m_TempPath);

        if ( files.size() == 1 ) {

            romimage = files.at(0);

        } else {
            for (int i = 0; i < files.size(); ++i) {

                if ( files.at(i).contains(".cue") ) {
                    romimage = files.at(i);
                }
            }
        }

        if ( fileIsEncrypted ) {

            // Dann können wir das ZipFile wieder aufräumen...
            romfile.setFileName( c->text() );
            romfile.remove();
        }

        if ( files.count() > 0 ){

            mMyFtpUpload = new FtpUpload( this );

            mMyFtpUpload->setFileName(romimage);
            mMyFtpUpload->show();
        }
    }
}

void MainWindow::on_cmdCodeTable_clicked()
{
    qDebug() << "on_cmdCodeTable_clicked" << m_actCodetableValue;

    QString filename = this->downloadFile(m_actCodetableValue, "", m_CachePath );

    if ( ( ! filename.isEmpty() ) && filename.contains(".pdf") ) {

        PDFViewer *myPDFViewer = new PDFViewer(this, filename );
        myPDFViewer->setWindowFlags(Qt::Window);
        myPDFViewer->show();
    }
}

void MainWindow::on_cmdSolution_clicked()
{
    qDebug() << "on_cmdSolution_clicked" << m_actSolutionValue;

    QString filename = this->downloadFile(m_actSolutionValue, "", m_CachePath );

    if ( ( ! filename.isEmpty() ) && filename.contains(".pdf") ) {

        PDFViewer *myPDFViewer = new PDFViewer(this, filename );
        myPDFViewer->setWindowFlags(Qt::Window);
        myPDFViewer->show();
    }
}

void MainWindow::SubDialogFinished() {

    this->iniToolBarSystem();

    on_cboSystems_currentTextChanged(ui->cboSystems->currentText());
}

void MainWindow::on_actionSQLBrowser_triggered()
{
    Browser *myBrowser = new Browser(this);
    myBrowser->setWindowFlags(Qt::Window);
    myBrowser->addConnection("","tosec.db3","","","");

    myBrowser->show();
}

void MainWindow::on_actionAmigaFutureOnlineMag_triggered()
{
    AmigaFuture *dialog = new AmigaFuture(this);

    dialog->setWindowFlags(Qt::Window);
    dialog->setModal(true);
    dialog->show();
}

void MainWindow::on_actionView_Log_File_triggered()
{
    QString filename = QString("TosecRC_%1.log").arg(QDateTime::currentDateTime().toString("yyyyMMdd"));

    mMyCodeEditor = new CodeEditor(this, filename );
    mMyCodeEditor->show();
}


void MainWindow::showMessage(QString message) {

    ui->statusBar->setFont( QFont( m_settings.loadStringSetting(m_sSettingsFile, "General", "fontname"),
                                   m_settings.loadIntSetting(m_sSettingsFile, "General", "fontsize") ) );

    ui->statusBar->showMessage( message );

    QCoreApplication::processEvents();
}

void MainWindow::on_edtBrowserUrl_returnPressed()
{
    if ( QUrl( ui->edtBrowserUrl->text() ).isValid() ) {

        this->loadWebView ( QUrl ( ui->edtBrowserUrl->text() ).toString(), false, true );
    }
}

void MainWindow::on_chkOnlyMissing_clicked()
{
    this->setCurrentItem( ui->listWidget->currentItem() );
}
