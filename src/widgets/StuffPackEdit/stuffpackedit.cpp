#include "stuffpackedit.h"
#include "ui_stuffpackedit.h"

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
StuffPackEdit::StuffPackEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StuffPackEdit)
{
    ui->setupUi(this);

    setAcceptDrops(true);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
StuffPackEdit::~StuffPackEdit()
{
    delete ui;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::setStuffPackIniFile(QString iniFile) {

    QStringList entries;
    QString     entry;
    QString     text;

    ui->lblIniFile->setText( iniFile );

    ui->edtPublisher->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "publisher") );
    ui->edtDeveloper->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "developer") );
    ui->edtReleasedate->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "releasedate") );
    ui->edtRating->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "rating") );
    ui->edtPlayers->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "players") );
    ui->edtInfo->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "info") );
    ui->edtManual->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "manual") );
    ui->edtCodeTable->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "codetable") );
    ui->edtSolution->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "solution") );

    ui->edtLogo->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "logo") ) ;
    ui->edtLogoDeveloper->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "logodeveloper") ) ;
    ui->edtWiki->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "wiki") ) ;
    ui->edtVideo->setText( _settings.loadStringSetting(ui->lblIniFile->text(), "Global", "video") ) ;

    // Cover laden
    entries.clear();
    entries << _settings.GetAllKeys(ui->lblIniFile->text(), "Cover");

    foreach (const QString &str, entries) {

        entry = _settings.loadStringSetting(ui->lblIniFile->text(), "Cover", str);

        ui->lstCovers->addItem( entry );
    }

    // Media laden
    entries.clear();
    entries << _settings.GetAllKeys(ui->lblIniFile->text(), "Media");

    foreach (const QString &str, entries) {

        entry = _settings.loadStringSetting(ui->lblIniFile->text(), "Media", str);

        ui->lstMedia->addItem( entry );
    }

    // Screenshot laden
    entries.clear();
    entries << _settings.GetAllKeys(ui->lblIniFile->text(), "Screenshot");

    foreach (const QString &str, entries) {

        entry = _settings.loadStringSetting(ui->lblIniFile->text(), "Screenshot", str);

        ui->lstScreenshot->addItem( entry );
    }

    // Soundtrack laden
    entries.clear();
    entries << _settings.GetAllKeys(ui->lblIniFile->text(), "Soundtrack");

    foreach (const QString &str, entries) {

        entry = _settings.loadStringSetting(ui->lblIniFile->text(), "Soundtrack", str);

        ui->lstSoundtrack->addItem( entry );
    }


    // Links laden
    entries.clear();
    entries << _settings.GetAllKeys(ui->lblIniFile->text(), "Links");

    foreach (const QString &str, entries) {

        entry = _settings.loadStringSetting(ui->lblIniFile->text(), "Links", str);

        ui->lstLinks->addItem( entry );
    }

    for( int r = 0; r < ui->twQuickLinks->rowCount(); ++r ) {

        for( int c = 0; c < ui->twQuickLinks->columnCount(); ++c ) {

            text = _settings.loadStringSetting(ui->lblIniFile->text(), "QuickLinks", QString("%1%2").arg(r).arg(c) );

            if ( text.trimmed().isEmpty() && ( c == 0 ) ) {

                qDebug() << "test" << c;

                switch (r) {
                    case 0: text = "https://openretro.org/img/link_hol.gif" ; break;
                    case 1: text = "https://openretro.org/img/link_lemonamiga.gif" ; break;
                    case 2: text = "https://openretro.org/img/link_mobygames.gif" ; break;
                    case 3: text = "https://openretro.org/img/link_wikipedia.png" ; break;
                default: text = "";
                }

            }

            ui->twQuickLinks->setItem(r,c,new QTableWidgetItem( text ));

        }
    }

    ui->twQuickLinks->resizeColumnsToContents();

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::setDialogCaption(QString caption) {

    this->setWindowTitle(caption);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::dropEvent(QDropEvent *ev)
{
    QList<QUrl> urls = ev->mimeData()->urls();

    foreach(QUrl url, urls)
    {
            qDebug() << url.toString();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::dragEnterEvent(QDragEnterEvent *ev)
{
    ev->accept();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdExit_clicked()
{
    QFile::remove(ui->lblIniFile->text());

    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "publisher",  ui->edtPublisher->text() );
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "developer", ui->edtDeveloper->text( ) );
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "releasedate", ui->edtReleasedate->text( ) );
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "rating",  ui->edtRating->text( ) );
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "players", ui->edtPlayers->text( ) );
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "info", ui->edtInfo->toPlainText() );
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "manual", ui->edtManual->text( ) );
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "codetable", ui->edtCodeTable->text( ) );
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "solution", ui->edtSolution->text( ) );

    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "logo", ui->edtLogo->text());
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "logodeveloper", ui->edtLogoDeveloper->text());
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "wiki", ui->edtWiki->text());
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "video", ui->edtVideo->text());
    _settings.saveStringSetting(ui->lblIniFile->text(), "Global", "soundtrack", ui->edtSoundtrack->text());

    for(int i = 0; i < ui->lstCovers->count(); ++i) {
        _settings.saveStringSetting(ui->lblIniFile->text(), "Cover", QString("%1").arg(i), ui->lstCovers->item(i)->text());
    }

    for(int i = 0; i < ui->lstMedia->count(); ++i) {
        _settings.saveStringSetting(ui->lblIniFile->text(), "Media", QString("%1").arg(i), ui->lstMedia->item(i)->text());
    }

    for(int i = 0; i < ui->lstScreenshot->count(); ++i) {
        _settings.saveStringSetting(ui->lblIniFile->text(), "Screenshot", QString("%1").arg(i), ui->lstScreenshot->item(i)->text());
    }

    for(int i = 0; i < ui->lstSoundtrack->count(); ++i) {
        _settings.saveStringSetting(ui->lblIniFile->text(), "Soundtrack", QString("%1").arg(i), ui->lstSoundtrack->item(i)->text());
    }

    for(int i = 0; i < ui->lstLinks->count(); ++i) {
        _settings.saveStringSetting(ui->lblIniFile->text(), "Links", QString("%1").arg(i), ui->lstLinks->item(i)->text());
    }

    for( int r = 0; r < ui->twQuickLinks->rowCount(); ++r ) {

        for( int c = 0; c < ui->twQuickLinks->columnCount(); ++c ) {

            QTableWidgetItem* item = ui->twQuickLinks->item(r,c);        //Load items

            if (!item || item->text().isEmpty())                        //Test if there is something at item(r,c)
            {
                ui->twQuickLinks->setItem(r,c,new QTableWidgetItem(""));//IF there is nothing write 0
            }

            _settings.saveStringSetting(ui->lblIniFile->text(), "QuickLinks", QString("%1%2").arg(r).arg(c), ui->twQuickLinks->item(r, c)->text() );
        }
    }

    this->close();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdCancel_clicked()
{
    this->close();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdCoverRemove_clicked()
{
    QList<QListWidgetItem*> items = ui->lstCovers->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->lstCovers->takeItem(ui->lstCovers->row(item));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdCoverAdd_clicked()
{
    ui->lstCovers->addItem( ui->edtAddCoverList->text() );
    ui->edtAddCoverList->clear();

    ui->lstCovers->scrollToBottom();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdMediaRemove_clicked()
{
    QList<QListWidgetItem*> items = ui->lstMedia->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->lstMedia->takeItem(ui->lstMedia->row(item));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdMediaAdd_clicked()
{
    ui->lstMedia->addItem( ui->edtAddMediaList->text() );
    ui->edtAddMediaList->clear();

    ui->lstMedia->scrollToBottom();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdScreenshotRemove_clicked()
{
    QList<QListWidgetItem*> items = ui->lstScreenshot->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->lstScreenshot->takeItem(ui->lstScreenshot->row(item));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdScreenshotAdd_clicked()
{
    ui->lstScreenshot->addItem( ui->edtAddScreenshotList->text() );
    ui->edtAddScreenshotList->clear();

    ui->lstScreenshot->scrollToBottom();
}

/**********************************************************************************************************************
 * Soundtrack
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdSoundtrackRemove_clicked()
{
    QList<QListWidgetItem*> items = ui->lstSoundtrack->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->lstSoundtrack->takeItem(ui->lstSoundtrack->row(item));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdSoundtrackAdd_clicked()
{
    ui->lstSoundtrack->addItem( ui->edtAddSoundtrackList->text() );
    ui->edtAddSoundtrackList->clear();

    ui->lstSoundtrack->scrollToBottom();
}

/**********************************************************************************************************************
 * Links
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdLinksRemove_clicked()
{
    QList<QListWidgetItem*> items = ui->lstLinks->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->lstLinks->takeItem(ui->lstLinks->row(item));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void StuffPackEdit::on_cmdLinksAdd_clicked()
{
    ui->lstLinks->addItem( ui->edtAddLinksList->text() );
    ui->edtAddLinksList->clear();

    ui->lstLinks->scrollToBottom();
}
