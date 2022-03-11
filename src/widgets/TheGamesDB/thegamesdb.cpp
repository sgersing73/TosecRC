#include "thegamesdb.h"
#include "ui_thegamesdb.h"

#include "src/scraper/strtools.h"

bool namefileLessThan(const thegamesdbplatformlist_type &d1, const thegamesdbplatformlist_type &d2)
{
    return d1.Name < d2.Name; // sort by namefile
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
TheGamesDB::TheGamesDB(QWidget *parent, QString caption, QString search, QString platform, QString tempPath) :
    QDialog(parent),
    ui(new Ui::TheGamesDB)
{
    ui->setupUi(this);

    m_MobiApiKey = "Xv3pGgk06BGX4vO7qlnnxQ==";

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QSettings state("state.ini", QSettings::IniFormat);

    this->ui->splitter->restoreState( state.value("TheGamesDBGeometrySplitterState", "" ).toByteArray() );
    this->restoreGeometry(state.value("TheGamesDBGeometry").toByteArray());

    m_TempPath = tempPath;

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    this->setWindowTitle("Games Metadata Grabber");

    ui->lblStuffpack->setText(caption);

    ui->cboPlatform->setCurrentText( platform );
    ui->edtSearch->setText( search );

    this->initControls();

    this->getPlatformList();

    m_Item = nullptr;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
TheGamesDB::~TheGamesDB()
{
    delete ui;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::closeEvent(QCloseEvent *event) {

    QSettings settings("state.ini", QSettings::IniFormat);

    settings.setValue("TheGamesDBGeometrySplitterState", ui->splitter->saveState());
    settings.setValue("TheGamesDBGeometry", this->saveGeometry());

    event->accept();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::on_cmdSearch_clicked()
{
    qDebug() << "on_cmdSearch_clicked";

    QString id;

    if ( ! ui->cboPlatform->currentText().trimmed().isEmpty() ) {
        id = ui->cboPlatform->currentText().split(" | ").at(1).trimmed();
    } else {
        id = "";
    }

   // QString url = QString("https://api.mobygames.com/v1/games?title=" + ui->edtSearch->text().trimmed().replace(" ","+") + "&platform=" + id + "&api_key=" + m_MobiApiKey;
    QString url = QString("https://api.mobygames.com/v1/games?title=%1&platform=%2&api_key=%3").arg(ui->edtSearch->text().trimmed().replace(" ","+")).arg(id).arg(m_MobiApiKey);

    m_FileName = m_TempPath + "GetGamesList.xml";

    qDebug() << QUrl(url) << m_FileName ;

    ui->lblInfo->setText("requesting list of games...");

    manager->get(QNetworkRequest(QUrl(url)));
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!" << reply->errorString();
        ui->lblInfo->setText(reply->errorString());
        return;
    }
    else
    {
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        QFile *file = new QFile(m_FileName);
        if(file->open(QFile::WriteOnly))
        {
            qDebug() << "make file " << m_FileName;

            file->write(reply->readAll());
            file->flush();
            file->close();
        }
        delete file;
    }

    reply->deleteLater();

    if (m_FileName.contains("Covers.xml")) {
        ui->lblInfo->setText("processing list of covers...");
        this->loadDBCoversListFile();
        ui->lblInfo->setText("done...");
    }

    if (m_FileName.contains("Screenshot.xml")) {
        ui->lblInfo->setText("processing list of screenshots...");
        this->loadDBScreenshotListFile();
        ui->lblInfo->setText("done...");
    }

    if (m_FileName.contains("GetGamesList.xml")) {
        ui->lblInfo->setText("processing list of games...");
        this->loadDBGameListFile();
        ui->lblInfo->setText("done...");
    }

    if (m_FileName.contains("GetGame.xml")) {
        ui->lblInfo->setText("processing game data...");
        this->loadDBGameFile();
        ui->lblInfo->setText("done...");
    }

    if (m_FileName.contains("Platforms.xml")) {
        ui->lblInfo->setText("processing platform data...");
        this->loadDBPlatformFile();
        ui->lblInfo->setText("done...");
    }

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::loadDBGameListFile() {

    ui->lisGamesList->clear();

    QList<thegamesdbgamelist_type> thegamesdbgamelist;

    QFile * file1 = new QFile(m_FileName);
    QByteArray byteArrayFile1;
    if (file1->open(QIODevice::ReadOnly)) {
        byteArrayFile1 = file1->readAll();
        file1->close();
    }

    jsonDoc = QJsonDocument::fromJson(byteArrayFile1);
    if(jsonDoc.isEmpty()) {
        QMessageBox::information(this, this->windowTitle(), tr("No gamelist data received..."));
        return;
    }

    QJsonArray jsonGames = jsonDoc.object()["games"].toArray();

    while(!jsonGames.isEmpty()) {

        QJsonObject jsonGame = jsonGames.first().toObject();

        thegamesdbgamelist_type tmp;

        tmp.id        =  QString::number(jsonGame["game_id"].toInt()) ;
        tmp.GameTitle =  jsonGame["title"].toString() ;
        tmp.miscData  =  QJsonDocument(jsonGame).toJson(QJsonDocument::Compact);

        QJsonArray jsonPlatforms = jsonGame["platforms"].toArray();

        // Wenn keine Platforms enthalten sind...
        if ( jsonPlatforms.isEmpty() ) {

            tmp.Platform    = "na" ;
            tmp.ReleaseDate = "na" ;
            tmp.url         =  QString("https://api.mobygames.com/v1/games/%1/platforms?api_key=%2").arg(tmp.id).arg(m_MobiApiKey);

            thegamesdbgamelist << tmp;
        }

        // Platforms laden
        while(!jsonPlatforms.isEmpty()) {

            QJsonObject jsonPlatform = jsonPlatforms.first().toObject();

            tmp.Platform    =  jsonPlatform["platform_name"].toString() ;
            tmp.ReleaseDate =  jsonPlatform["first_release_date"].toString() ;
            tmp.Platform_id =  QString::number(jsonPlatform["platform_id"].toInt()) ;

            tmp.url         =  QString("https://api.mobygames.com/v1/games/%1/platforms/%2?api_key=%3").arg(tmp.id).arg(tmp.Platform_id).arg(m_MobiApiKey);

            jsonPlatforms.removeFirst();

            thegamesdbgamelist << tmp;
        }

        jsonGames.removeFirst();
    }

    thegamesdbgamelist_type item;
    foreach( item, thegamesdbgamelist ) {

        QListWidgetItem *listitem = new QListWidgetItem();

        listitem->setText( item.id + " - " +  item.GameTitle + " - " + item.Platform + " - " + item.ReleaseDate ) ;
        listitem->setData(Qt::UserRole, item.miscData );
        listitem->setData(Qt::ToolTipRole, item.url );

        ui->lisGamesList->addItem( listitem );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::loadDBGameFile() {

    QFile * file1 = new QFile(m_FileName);
    QByteArray byteArrayFile1;
    if (file1->open(QIODevice::ReadOnly)) {
        byteArrayFile1 = file1->readAll();
        file1->close();
    }

    this->getTitle(qvariant_cast<QByteArray>(m_Item->data(Qt::UserRole)));
    ui->lblGameTitle->setText( m_thegamesdb.GameTitle );

    this->getDescription(qvariant_cast<QByteArray>(m_Item->data(Qt::UserRole)));
    ui->lblOverview->setText ( m_thegamesdb.Description );

    this->getReleaseDate(byteArrayFile1);
    ui->lblReleaseDate->setText( m_thegamesdb.ReleaseDate );

    this->getPlatform(byteArrayFile1);
    ui->lblPlatform->setText( m_thegamesdb.Platform );

    this->getPlayers(byteArrayFile1);
    ui->lblPlayers->setText ( m_thegamesdb.Players );

    this->getPublisher(byteArrayFile1);
    ui->lblPublisher->setText ( m_thegamesdb.Publisher );

    this->getDeveloper(byteArrayFile1);
    ui->lblDeveloper->setText ( m_thegamesdb.Developer );

    this->getGameid(byteArrayFile1);

    this->getPlatformId(byteArrayFile1);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::loadDBPlatformFile()
{
    ui->cboPlatform->clear();

    QList<thegamesdbplatformlist_type> thegamesdbplatformlist;
    thegamesdbplatformlist_type item;

    QFile * file1 = new QFile(m_FileName);
    QByteArray byteArrayFile1;
    if (file1->open(QIODevice::ReadOnly)) {
        byteArrayFile1 = file1->readAll();
        file1->close();
    }

    jsonDoc = QJsonDocument::fromJson(byteArrayFile1);
    if(jsonDoc.isEmpty()) {
        QMessageBox::information(this, this->windowTitle(), tr("No platform data received..."));
        return;
    }

    QJsonArray jsonPlatforms = jsonDoc.object()["platforms"].toArray();

    while(!jsonPlatforms.isEmpty()) {

        QJsonObject jsonPlatform = jsonPlatforms.first().toObject();

        thegamesdbplatformlist_type tmp;

        tmp.id   =  QString::number(jsonPlatform["platform_id"].toInt()) ;
        tmp.Name =  jsonPlatform["platform_name"].toString() ;

        thegamesdbplatformlist << tmp;

        jsonPlatforms.removeFirst();
    }

    std::sort(thegamesdbplatformlist.begin(), thegamesdbplatformlist.end(), namefileLessThan);

    ui->cboPlatform->addItem( " " );

    foreach( item, thegamesdbplatformlist )
       ui->cboPlatform->addItem( item.Name + " | " + item.id);

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::on_lisGamesList_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << "on_lisGamesList_itemDoubleClicked";

    m_Item = item;

    QStringList param;
    param << item->text().split("-");

    QString url =  qvariant_cast<QString>(item->data(Qt::ToolTipRole));

    m_FileName = m_TempPath + "GetGame.xml";

    ui->lblInfo->setText("requesting game data...");

    qDebug() << url << m_FileName;

    manager->get(QNetworkRequest(QUrl(url)));
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getPlatformList()
{
    QString url = QString("https://api.mobygames.com/v1/platforms?api_key=%1").arg(m_MobiApiKey);

    m_FileName = m_TempPath + "/" + "Platforms.xml";

    QFile file(m_FileName);
    if ( !file.exists() ) {

        qDebug() << QUrl(url);

        ui->lblInfo->setText("requesting platform data...");

        manager->get(QNetworkRequest(QUrl(url)));
    } else {
        this->loadDBPlatformFile();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::on_cmdCreateStuffPack_clicked()
{
    QFileInfo fi;
    int       counter;

    qDebug() << m_thegamesdb.baseImgUrl;
    qDebug() << m_thegamesdb.clearlogo;
    qDebug() << m_thegamesdb.boxart;
    qDebug() << m_thegamesdb.thumb;
    qDebug() << m_thegamesdb.Youtube;

    fi.setFile(  ui->lblStuffpack->text() );

    if ( true ) {

        qDebug() << ui->lblStuffpack->text();

        QString outDir = ui->lblStuffpack->text();
        m_tools.createDir( outDir.remove("/info.txt") );

        QFile file( ui->lblStuffpack->text() );
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, this->windowTitle(),  tr("Unable to open stuffpack file: %1").arg( file.errorString() ) );
            return;
        }

        QTextStream out(&file);

        out << "[Global]" << "\n";

        if (! m_thegamesdb.clearlogo.isEmpty()) {
            out << "logo=" << m_thegamesdb.baseImgUrl << m_thegamesdb.clearlogo << "\n";
        } else {
            out << "logo=" << "\n";
        }

        out << "wiki=" << "\n";
        out << "soundtrack=" << "\n";
        out << "video=" <<  m_thegamesdb.Youtube << "\n";
        out << "info=" << m_thegamesdb.Description.replace("\n","<br>") << "\n";
        out << "developer=" << m_thegamesdb.Developer << "\n";
        out << "publisher=" << m_thegamesdb.Publisher << "\n";
        out << "releasedate=" << m_thegamesdb.ReleaseDate << "\n";
        out << "rating=" << m_thegamesdb.Rating << "\n";
        out << "players=" << m_thegamesdb.Players << "\n";
        out << "platforms=" << m_thegamesdb.Platform << "\n\n";

        counter = 1;
        out << "[Cover]" << "\n";
        for (QStringList::iterator it = m_thegamesdb.boxart.begin();
            it != m_thegamesdb.boxart.end(); ++it) {
            QString current = *it;
            out << QString("%1").arg(counter) << "=" <<  m_thegamesdb.baseImgUrl << current << "\n";
            counter++;
        }

        counter = 1;
        out << "[Screenshot]" << "\n";
        for (QStringList::iterator it = m_thegamesdb.thumb.begin();
            it !=  m_thegamesdb.thumb.end(); ++it) {
            QString current = *it;
            out << QString("%1").arg(counter) << "=" <<  m_thegamesdb.baseImgUrl << current << "\n";
            counter++;
        }

        counter = 1;
        out << "[Media]" << "\n\n";
        for (QStringList::iterator it = m_thegamesdb.media.begin();
            it !=  m_thegamesdb.media.end(); ++it) {
            QString current = *it;
            out << QString("%1").arg(counter) << "=" <<  m_thegamesdb.baseImgUrl << current << "\n";
            counter++;
        }

        file.close();
    }

    QMessageBox::information(this, this->windowTitle(),  tr("Stuffpack file successfull generated!") );

    this->close();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::initControls() {

    ui->lisGamesList->clear();
    ui->lblInfo->clear();
    ui->lblGameTitle->clear();
    ui->lblPlatform->clear();
    ui->lblReleaseDate->clear();
    ui->lblPlayers->clear();
    ui->lblPublisher->clear();
    ui->lblDeveloper->clear();
    ui->lblOverview->clear();

    m_thegamesdb.Description.clear();
    m_thegamesdb.baseImgUrl.clear();
    m_thegamesdb.Platform.clear();
    m_thegamesdb.id.clear();
    m_thegamesdb.GameTitle.clear();
    m_thegamesdb.ReleaseDate.clear();
    m_thegamesdb.Overview.clear();
    m_thegamesdb.genre.clear();
    m_thegamesdb.Players.clear();
    m_thegamesdb.Youtube.clear();
    m_thegamesdb.Publisher.clear();
    m_thegamesdb.Developer.clear();
    m_thegamesdb.Rating.clear();
    m_thegamesdb.original.clear();
    m_thegamesdb.thumb.clear();
    m_thegamesdb.boxart.clear();
    m_thegamesdb.media.clear();
    m_thegamesdb.banner.clear();
    m_thegamesdb.tags.clear();
    m_thegamesdb.clearlogo.clear();
    m_thegamesdb.ages.clear();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getReleaseDate(QByteArray data)
{
    jsonDoc = QJsonDocument::fromJson(data);

    m_thegamesdb.ReleaseDate = jsonDoc.object()["first_release_date"].toString();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getGameid(QByteArray data)
{
    jsonDoc = QJsonDocument::fromJson(data);

    m_actGame_id = QString::number(jsonDoc.object()["game_id"].toInt());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getPlatformId(QByteArray data)
{
    jsonDoc = QJsonDocument::fromJson(data);

    m_actPlatform_id = QString::number(jsonDoc.object()["platform_id"].toInt());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getPlayers(QByteArray data)
{
    jsonDoc = QJsonDocument::fromJson(data);
    QJsonArray jsonAttribs = jsonDoc.object()["attributes"].toArray();
    for(int a = 0; a < jsonAttribs.count(); ++a) {
        if(jsonAttribs.at(a).toObject()["attribute_category_name"].toString() == "Number of Players Supported") {
            m_thegamesdb.Players = jsonAttribs.at(a).toObject()["attribute_name"].toString();
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getTags(QByteArray data)
{
     jsonDoc = QJsonDocument::fromJson(data);

     QJsonArray jsonGenres = jsonObj["genres"].toArray();
     for(int a = 0; a < jsonGenres.count(); ++a) {
         m_thegamesdb.tags.append(jsonGenres.at(a).toObject()["genre_name"].toString() + ", ");
     }
     m_thegamesdb.tags = m_thegamesdb.tags.left(m_thegamesdb.tags.length() - 2);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getAges(QByteArray data)
{
  jsonDoc = QJsonDocument::fromJson(data);

  QJsonArray jsonAges = jsonDoc.object()["ratings"].toArray();
  for(int a = 0; a < jsonAges.count(); ++a) {
    if(jsonAges.at(a).toObject()["rating_system_name"].toString() == "PEGI Rating") {
      m_thegamesdb.ages = jsonAges.at(a).toObject()["rating_name"].toString();
      break;
    }
  }
  for(int a = 0; a < jsonAges.count(); ++a) {
    if(jsonAges.at(a).toObject()["rating_system_name"].toString() == "ELSPA Rating") {
      m_thegamesdb.ages = jsonAges.at(a).toObject()["rating_name"].toString();
      break;
    }
  }
  for(int a = 0; a < jsonAges.count(); ++a) {
    if(jsonAges.at(a).toObject()["rating_system_name"].toString() == "ESRB Rating") {
      m_thegamesdb.ages = jsonAges.at(a).toObject()["rating_name"].toString();
      break;
    }
  }
  for(int a = 0; a < jsonAges.count(); ++a) {
    if(jsonAges.at(a).toObject()["rating_system_name"].toString() == "USK Rating") {
      m_thegamesdb.ages = jsonAges.at(a).toObject()["rating_name"].toString();
      break;
    }
  }
  for(int a = 0; a < jsonAges.count(); ++a) {
    if(jsonAges.at(a).toObject()["rating_system_name"].toString() == "OFLC (Australia) Rating") {
      m_thegamesdb.ages = jsonAges.at(a).toObject()["rating_name"].toString();
      break;
    }
  }
  for(int a = 0; a < jsonAges.count(); ++a) {
    if(jsonAges.at(a).toObject()["rating_system_name"].toString() == "SELL Rating") {
      m_thegamesdb.ages = jsonAges.at(a).toObject()["rating_name"].toString();
      break;
    }
  }
  for(int a = 0; a < jsonAges.count(); ++a) {
    if(jsonAges.at(a).toObject()["rating_system_name"].toString() == "BBFC Rating") {
      m_thegamesdb.ages = jsonAges.at(a).toObject()["rating_name"].toString();
      break;
    }
  }
  for(int a = 0; a < jsonAges.count(); ++a) {
    if(jsonAges.at(a).toObject()["rating_system_name"].toString() == "OFLC (New Zealand) Rating") {
      m_thegamesdb.ages = jsonAges.at(a).toObject()["rating_name"].toString();
      break;
    }
  }
  for(int a = 0; a < jsonAges.count(); ++a) {
    if(jsonAges.at(a).toObject()["rating_system_name"].toString() == "VRC Rating") {
      m_thegamesdb.ages = jsonAges.at(a).toObject()["rating_name"].toString();
      break;
    }
  }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getPublisher(QByteArray data)
{
    jsonDoc = QJsonDocument::fromJson(data);

    QJsonArray jsonReleases = jsonDoc.object()["releases"].toArray();
    for(int a = 0; a < jsonReleases.count(); ++a) {

        QJsonArray jsonCompanies = jsonReleases.at(a).toObject()["companies"].toArray();

        for(int b = 0; b < jsonCompanies.count(); ++b) {
            if(jsonCompanies.at(b).toObject()["role"].toString() == "Published by") {
                m_thegamesdb.Publisher = jsonCompanies.at(b).toObject()["company_name"].toString();
                return;
            }
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getDeveloper(QByteArray data)
{
    jsonDoc = QJsonDocument::fromJson(data);

    QJsonArray jsonReleases = jsonDoc.object()["releases"].toArray();

    for(int a = 0; a < jsonReleases.count(); ++a) {

        QJsonArray jsonCompanies = jsonReleases.at(a).toObject()["companies"].toArray();

        for(int b = 0; b < jsonCompanies.count(); ++b) {
            if(jsonCompanies.at(b).toObject()["role"].toString() == "Developed by") {
                m_thegamesdb.Developer = jsonCompanies.at(b).toObject()["company_name"].toString();
                return;
            }
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getDescription(QByteArray data)
{
  jsonDoc = QJsonDocument::fromJson(data);

  m_thegamesdb.Description = jsonDoc.object()["description"].toString();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getRating(QByteArray data)
{
    jsonDoc = QJsonDocument::fromJson(data);

    QJsonValue jsonValue = jsonDoc.object()["moby_score"];

    if(jsonValue != QJsonValue::Undefined) {

        double rating = jsonValue.toDouble();
        if(rating != 0.0) {
            m_thegamesdb.Rating = QString::number(rating / 5.0);
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getTitle(QByteArray data)
{
  jsonDoc = QJsonDocument::fromJson(data);

  m_thegamesdb.GameTitle =  jsonDoc.object()["title"].toString();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getPlatform(QByteArray data)
{
  jsonDoc = QJsonDocument::fromJson(data);

  m_thegamesdb.Platform =  jsonDoc.object()["platform_name"].toString();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getScreenshot(QByteArray data)
{
    m_thegamesdb.thumb.clear();

    jsonDoc = QJsonDocument::fromJson(data);
    if(jsonDoc.isEmpty()) {
        QMessageBox::information(this, this->windowTitle(), tr("No screenshot data treceived..."));
        return;
    }

    QJsonArray jsonScreenshots = jsonDoc.object()["screenshots"].toArray();

    if(jsonScreenshots.count() < 1) {
        QMessageBox::information(this, this->windowTitle(), tr("No screenshot data treceived..."));
        return;
    }

    for(int a = 0; a < jsonScreenshots.count(); ++a) {
        m_thegamesdb.thumb.append( jsonScreenshots.at(a).toObject()["image"].toString() ) ;
    }

    ui->cmdScreenshots->setText( tr("Screenshots - %1 found").arg( m_thegamesdb.thumb.count() ) );

    qDebug() << m_thegamesdb.thumb;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getBoxart(QByteArray data)
{
    m_thegamesdb.boxart.clear();
    m_thegamesdb.media.clear();

    jsonDoc = QJsonDocument::fromJson(data);
    if(jsonDoc.isEmpty()) {
        QMessageBox::information(this, this->windowTitle(), tr("No boxart data received..."));
        return;
    }

    QJsonArray jsonCoverGroup = jsonDoc.object()["cover_groups"].toArray();

    if(jsonCoverGroup.count() < 1) {
        QMessageBox::information(this, this->windowTitle(), tr("No boxart data received..."));
        return;
    }

    for(int a = 0; a < jsonCoverGroup.count(); ++a) {

        QJsonArray jsonCover = jsonCoverGroup.at(a).toObject()["covers"].toArray();

        for(int aa = 0; aa < jsonCover.count(); ++aa) {

            if ( jsonCover.at(aa).toObject()["scan_of"].toString().contains("Media") ) {
                m_thegamesdb.media.append( jsonCover.at(aa).toObject()["image"].toString() ) ;
            } else {
                m_thegamesdb.boxart.append( jsonCover.at(aa).toObject()["image"].toString() ) ;
            }
        }

    }

    ui->cmdBoxart->setText( tr("Boxart - %1 cover/%2 media found").arg( m_thegamesdb.boxart.count() ).arg( m_thegamesdb.media.count() ) );

    qDebug() << m_thegamesdb.boxart;
    qDebug() << m_thegamesdb.media;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getScreenshotList() {

    QString url = QString("https://api.mobygames.com/v1/games/%1/platforms/%2/screenshots?api_key=%3").arg(m_actGame_id).arg(m_actPlatform_id).arg(m_MobiApiKey);

    m_FileName = m_TempPath + "/" + "Screenshot.xml";

    qDebug() << QUrl(url);

    ui->lblInfo->setText("requesting screenshot data...");

    manager->get(QNetworkRequest(QUrl(url)));
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::getCoverList() {

    QString url = QString("https://api.mobygames.com/v1/games/%1/platforms/%2/covers?api_key=%3").arg(m_actGame_id).arg(m_actPlatform_id).arg(m_MobiApiKey);

    m_FileName = m_TempPath + "/" + "Covers.xml";

    qDebug() << QUrl(url);

    ui->lblInfo->setText("requesting cover data...");

    manager->get(QNetworkRequest(QUrl(url)));
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::loadDBScreenshotListFile()
{
    QFile * file1 = new QFile(m_FileName);
    QByteArray byteArrayFile1;
    if (file1->open(QIODevice::ReadOnly)) {
        byteArrayFile1 = file1->readAll();
        file1->close();
    }

    this->getScreenshot(byteArrayFile1);
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::loadDBCoversListFile() {

    QFile * file1 = new QFile(m_FileName);
    QByteArray byteArrayFile1;
    if (file1->open(QIODevice::ReadOnly)) {
        byteArrayFile1 = file1->readAll();
        file1->close();
    }

    this->getBoxart(byteArrayFile1);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::on_cmdScreenshots_clicked()
{
    this->getScreenshotList();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void TheGamesDB::on_cmdBoxart_clicked()
{
    this->getCoverList();
}
