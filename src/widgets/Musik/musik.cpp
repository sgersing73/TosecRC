#include "musik.h"

#include "ui_musik.h"

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
Musik::Musik(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::Musik),
    _equalizerDialog(new EqualizerDialog(this))
{
    QString schema = m_settings.loadStringSetting("settings.ini", "General", "IconColorSchema", "blue");

    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);    
    _player->setVideoWidget(ui->video);    
    _equalizerDialog->setMediaPlayer(_player);

    ui->volume->setMediaPlayer(_player);
    ui->volume->setVolume(100);

    ui->seek->setMediaPlayer(_player);

    connect(_player, SIGNAL(end()), this, SLOT(playerEnd()));

    connect(ui->cmdEqualizer, &QPushButton::clicked, _equalizerDialog, &EqualizerDialog::show);

    _process = new QProcess(this);

    connect(_process, SIGNAL(started()), this, SLOT(processStarted()));
    connect(_process, SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()));
    connect(_process, SIGNAL(finished(int)), this, SLOT(encodingFinished()));

    ui->cmdEqualizer->setEnabled( false );
    ui->cmdStop->setEnabled( false );
    ui->cmdPlay->setEnabled( false );
    ui->cmdNext->setEnabled ( false );
    ui->cmdPrev->setEnabled( false );

    ui->video->setFixedHeight( 0 );
    ui->listTracks->setVisible(true);

    ui->cmdStop->setIcon(QIcon(QString(":/icon/player/images/player/%1/stop.ico").arg(schema)));
    ui->cmdEqualizer->setIcon(QIcon(QString(":/icon/player/images/player/%1/equalizer.ico").arg(schema)));
    ui->cmdPause->setIcon(QIcon(QString(":/icon/player/images/player/%1/pause.ico").arg(schema)));
    ui->cmdPlay->setIcon(QIcon(QString(":/icon/player/images/player/%1/play.ico").arg(schema)));
    ui->cmdNext->setIcon(QIcon(QString(":/icon/player/images/player/%1/forward.ico").arg(schema)));
    ui->cmdPrev->setIcon(QIcon(QString(":/icon/player/images/player/%1/backward.ico").arg(schema)));
    ui->chkRadio->setIcon(QIcon(QString(":/icon/player/images/player/%1/radio.ico").arg(schema)));
    ui->cmdSave->setIcon(QIcon(QString(":/icon/player/images/player/%1/save.ico").arg(schema)));

    _item = nullptr;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
Musik::~Musik()
{
    delete ui;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void::Musik::playerEnd() {

    ui->cmdPlay->setEnabled(true);
    ui->cmdStop->setEnabled(false);

    if ( ui->chkRadio->isChecked() ) {

        int currentIndex = ui->listTracks->currentRow();

        if (currentIndex + 1 >= ui->listTracks->count() ) {
            currentIndex = 0;
        }

        ui->listTracks->setCurrentRow(currentIndex+1);

        on_listTracks_itemDoubleClicked(ui->listTracks->currentItem() ) ;
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::processStarted()
{

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::encodingFinished()
{
    ui->cmdPlay->setEnabled(true);
    ui->cmdStop->setEnabled(false);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::readyReadStandardOutput()
{

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::setPlayerTitle(QString title) {

    this->setTitle( title );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool Musik::isPlaying() {

    return ( m_playing );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::setFileExtension(QStringList extensions) {

    qDebug() << "setFileExtension" << extensions;

    _extensions = extensions;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::setFilePath(QString directory) {

    qDebug() << directory;

    if(directory.isEmpty()) {
        return;
    }

    ui->listTracks->clear();

    QDir dir(directory);
    QStringList files = dir.entryList( _extensions , QDir::Files);

    this->setHidden( ( ! files.count() )  > 0 );

    qDebug() << "removeDuplicates" << files.removeDuplicates();

    foreach (const QString &f, files)
    {
        QFileInfo fi(f);

        QListWidgetItem *item = new QListWidgetItem();

        item->setText(fi.fileName());
        item->setToolTip(dir.path() + "/" + fi.fileName());

        ui->listTracks->addItem(item);
    }

    ui->cmdPlay->setEnabled(true);

    ui->listTracks->setVisible(true);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::setURL(QString url, QString baseUrl, QString extension) {

    ui->listTracks->clear();

    _htmlpageloader = new HtmlPageLoader(this);
    QObject::connect(_htmlpageloader, &HtmlPageLoader::dataReady, this, &Musik::loadData);

    _htmlpageloader->loadPage(QUrl(url), baseUrl, extension);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::loadData() {

    QList<tag_type> tags;

    tags = _htmlpageloader->getData();

    this->setHidden( ( ! tags.count() ) > 0 );

    foreach(tag_type tag, tags) {

        QListWidgetItem *item = new QListWidgetItem();

        item->setText(tag.Title);
        item->setToolTip(tag.Path);
        item->setData(Qt::UserRole, tag.Path);

        QList<QListWidgetItem *> items = ui->listTracks->findItems(tag.Title, Qt::MatchExactly);

        if ( items.isEmpty() ) {

            ui->listTracks->addItem(item);
        }

    }

    ui->listTracks->setCurrentRow(0);

    _item = ui->listTracks->currentItem() ;

    this->setHidden( false );

    ui->cmdPlay->setEnabled(true);
    ui->cmdStop->setEnabled(true);

    ui->listTracks->setVisible(true);

    ui->video->setFixedHeight(0);
    ui->video->setVisible(false);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::on_cmdPlay_clicked() {

    playFile();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::on_cmdStop_clicked() {

    stopPlayer();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::disable() {

    ui->cmdPlay->setEnabled(false);
    ui->cmdStop->setEnabled(false);
    ui->cmdNext->setEnabled ( false );
    ui->cmdPrev->setEnabled( false );
    ui->cmdEqualizer->setEnabled( false );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::on_listTracks_itemDoubleClicked(QListWidgetItem *item) {

    _item = item;

    playFile();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::on_listTracks_itemClicked(QListWidgetItem *item)
{
    _item = item;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::stopPlayer() {

    QString player;

    if ( ! _item ) {
        player = "intern";
    } else {
        player = getMediaPlayer ( _item->toolTip().mid( _item->toolTip().lastIndexOf(".") ) ) ;
    }

    if ( player == "intern" ) {
        _player->stop();
    } else {
        _process->close();
    }

    ui->video->setFixedHeight(0);
    ui->video->setVisible(false);

    ui->listTracks->setVisible(true);

    ui->cmdStop->setEnabled( false );
    ui->cmdPlay->setEnabled( true );
    ui->cmdEqualizer->setEnabled( false );
    ui->cmdNext->setEnabled ( false );
    ui->cmdPrev->setEnabled( false );
    ui->cmdPause->setEnabled( false );

    m_playing = false;
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::playFile() {

    bool local = true;
    QString player;

    if ( ! _item ) {
        player = "intern";
    } else {
        player = getMediaPlayer ( _item->toolTip().mid( _item->toolTip().lastIndexOf(".") ) ) ;
    }

    if ( _item->toolTip().contains("http") ) {
        local = false;
    }

    ui->cmdStop->setEnabled( true );
    ui->cmdPlay->setEnabled( false );
    ui->cmdPause->setEnabled( true );

    if ( player == "intern" ) {

        qDebug() << "playFile" << _item->toolTip();

        _media = new VlcMedia(QUrl(_item->toolTip()).toString(QUrl::FullyEncoded), local, _instance);
         _player->open(_media);

        ui->cmdEqualizer->setEnabled( true );
        ui->cmdNext->setEnabled ( true );
        ui->cmdPrev->setEnabled( true );

    } else {

        ui->cmdEqualizer->setEnabled( false );
        ui->cmdNext->setEnabled ( false );
        ui->cmdPrev->setEnabled( false );

        ExecuteProgram(player, _item->toolTip());
    }

    m_playing = true;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::playVideoFile(QString url) {

    bool local = false;

    ui->cmdStop->setEnabled( true );
    ui->cmdPause->setEnabled( true );

    ui->cmdPlay->setEnabled( false );
    ui->cmdPrev->setEnabled( false );
    ui->cmdNext->setEnabled( false );
    ui->chkRadio->setEnabled( false );
    ui->listTracks->setVisible ( false );
    ui->cmdPlay->setEnabled(false);

    ui->video->setFixedHeight( 200 );
    ui->video->setVisible(true);

    _media = new VlcMedia(url, local, _instance);
    _player->open(_media);

    ui->cmdEqualizer->setEnabled( true );

    m_playing = true;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::ExecuteProgram(QString program, QString args) {

    QStringList arguments;

    qDebug() << "ExecuteProgram" << program << args;

    arguments << args;

    _process->close();
    _process->setProcessChannelMode(QProcess::MergedChannels);
    _process->start(program, arguments);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QString Musik::getMediaPlayer(QString extension) {

    QString retValue = "intern";

    QString value = _settings.loadStringSetting(INI_FILE, "MusicPlayer", extension);

    if( ! value.isEmpty() ) {

        retValue = value;
    }

    return retValue;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::on_cmdPrev_clicked()
{
    if ( ui->listTracks->count() > 0 ) {

        int currentIndex = ui->listTracks->currentRow();

        ui->listTracks->setCurrentRow(currentIndex - 1);

        on_listTracks_itemDoubleClicked(ui->listTracks->currentItem() ) ;
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::on_cmdNext_clicked()
{
    if ( ui->listTracks->count() > 0 ) {

        int currentIndex = ui->listTracks->currentRow();

        ui->listTracks->setCurrentRow(currentIndex + 1);

        on_listTracks_itemDoubleClicked(ui->listTracks->currentItem() ) ;
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::on_cmdPause_clicked()
{
    QString player;
    static bool paused;

    if ( ! _item ) {
        player = "intern";
    } else {
        player = getMediaPlayer ( _item->toolTip().mid( _item->toolTip().lastIndexOf(".") ) ) ;
    }

    if ( player == "intern" ) {

        if ( paused ) {
           _player->play();
           paused = false;
        } else {
           _player->pause();
           paused = true;
        }
        ui->cmdStop->setEnabled( true );
    }
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::on_cmdSave_clicked()
{
    if ( ! _item ) {
        return;
    }

    QVariant data = _item->data(Qt::UserRole);

    QUrl fileUrl( data.toString() );

    QString fileName = QFileDialog::getSaveFileName(this, tr("Downloader Queue File"), "music_urls.txt", "Text files (*.txt)");

    qDebug() << "-I- Store file url: " + fileUrl.url() + " to: " + fileName;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&file);
        stream << fileUrl.url() << "\r\n";
        file.close();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void Musik::saveFile()
{
    QByteArray data = m_pImgCtrl->downloadedData();

    if ( data.isEmpty() )  {

        qDebug() << "-E- FileDownloader - no data received";
        QMessageBox::information(this, this->windowTitle(),  tr("No data received!") );

    } else {

        QFile file( m_fileName );

        if (!file.open(QIODevice::WriteOnly)) {

            qDebug() << "-E- FileDownloader - unable to open file: " + m_fileName;

        } else {

            file.write( m_pImgCtrl->downloadedData() );
            file.close();

            qDebug() << "-I- FileDownloader - file: " + m_fileName + " written...";
        }
    }
}

void Musik::on_chkSpectrum_clicked(bool checked)
{

}
