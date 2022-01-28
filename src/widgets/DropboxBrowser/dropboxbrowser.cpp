#include "dropboxbrowser.h"
#include "ui_dropboxbrowser.h"

DropboxBrowser::DropboxBrowser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DropboxBrowser)
{
    ui->setupUi(this);

    m_Dropbox2 = NULL;

    m_TempPath = m_Settings.loadStringSetting("settings.ini", "General", "TempPath");

    QFileInfo fi("dropbox.ini");

    if ( ! fi.exists() ) {

        qDebug() << "dropbox.ini nicht gefunden" ;

        ui->cmdDownload->setEnabled( false );
        ui->cmdUpload->setEnabled( false );
        ui->cmdGetFiles->setEnabled( false );

        QMessageBox::information(this, this->windowTitle(),  tr("Please enter your Dropbox settings!!!") );        

    } else {

        m_Token = m_Settings.loadStringSetting("dropbox.ini", "General", "token");
        m_Directory = m_Settings.loadStringSetting("dropbox.ini", "General", "directory");

        ui->edtToken->setText( m_Token );
        ui->edtDir->setText( m_Directory );

        m_Dropbox2 = new QDropbox2(m_Token, this);
    }

    ui->listDropbox->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listDropbox, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    m_dirModel = new QFileSystemModel(this);
    m_dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    m_dirModel->setRootPath(m_TempPath);

    ui->treeView->setModel(m_dirModel);

    m_fileModel = new QFileSystemModel(this);

    m_fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    m_fileModel->setRootPath(m_TempPath);

    ui->listView->setModel(m_fileModel);

    m_File.clear();

    QString picfilename = ":/images/images/Dropbox.png";
    QImage publisher;

    publisher.load( picfilename ) ;

    if ( ! publisher.isNull() ) {
        ui->lblPublisher->setPixmap(QPixmap::fromImage(publisher.scaledToHeight(ui->lblPublisher->maximumHeight())));
    }

    this->on_cmdGetFiles_clicked();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
DropboxBrowser::~DropboxBrowser()
{
    delete ui;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::on_cmdGetFiles_clicked() {

    this->getDirectoryList(ui->edtDir->text());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::on_cmdDownload_clicked() {

    QByteArray data;
    QString filename;

    QList<QListWidgetItem *> items = ui->listDropbox->selectedItems();

    if ( items.count() == 1 ) {

        QDropbox2File db_file(items.at(0)->toolTip(), m_Dropbox2);

        if ( db_file.open(QIODevice::ReadOnly) ) {

            QDropbox2EntityInfo info(db_file.metadata());

            if ( ! info.id().isEmpty() )  {

                data = db_file.readAll();
                db_file.close();

                filename = QFileDialog::getSaveFileName(this, tr("Datei speichern unter..."), m_Path + "/" +  items.at(0)->text());

                if ( ! filename.isEmpty() ) {

                    QFile file(filename);
                    file.open(QIODevice::WriteOnly);
                    file.write(data);
                    file.close();

                    QMessageBox::information(this, this->windowTitle(),  tr("Datei erfolgreich empfangen!") );
                }
            }
        } else {
             QMessageBox::critical(this, this->windowTitle(),  tr("Dropbox Datei kann nicht geöffnet werden!") );
        }
    } else {
        QMessageBox::information(this, this->windowTitle(),  tr("Bitte nur eine Datei auswählen!") );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::on_cmdUpload_clicked()
{
    QString filename;
    QByteArray data;

    filename = m_File;

    if ( QFile::exists(filename) ) {

        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        data = file.readAll();
        file.close();

        QFileInfo fi(file.fileName());

        qDebug() << "on_cmdUpload_clicked" << ui->edtDir->text() + "/" + fi.fileName();

        QDropbox2File db_file(ui->edtDir->text() + "/" + fi.fileName() , m_Dropbox2);

        db_file.setOverwrite();

        if ( db_file.open(QIODevice::WriteOnly|QIODevice::Truncate) ) {

            db_file.write(data);
            db_file.flush();
            db_file.close();

            QMessageBox::information(this, this->windowTitle(),  tr("Datei erfolgreich übertragen!") );
        } else {
            QMessageBox::critical(this, this->windowTitle(),  tr("Dropbox Datei kann nicht geöffnet werden!") );
        }

    } else {
        QMessageBox::information(this, this->windowTitle(),  tr("Ausgewählte Datei nicht gefunden!") );
    }

    this->on_cmdGetFiles_clicked();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::on_treeView_clicked(const QModelIndex &index)
{
    // Get the full path of the item that's user clicked on
    m_Path = m_dirModel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(m_fileModel->setRootPath(m_Path));

    ui->treeView->resizeColumnToContents(0);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::on_listView_clicked(const QModelIndex &index)
{
    m_File = m_fileModel->fileInfo(index).absoluteFilePath();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::closeEvent(QCloseEvent *event) {

    if ( m_Token != ui->edtToken->text() ||  m_Directory != ui->edtDir->text() ) {

        QMessageBox msgBox;

        msgBox.setWindowTitle( this->windowTitle() );
        msgBox.setText("Settings where changed - save?");

        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int retVal = msgBox.exec();

        if(retVal == QMessageBox::Yes){

            m_Settings.saveStringSetting("dropbox.ini", "General", "token", ui->edtToken->text());
            m_Settings.saveStringSetting("dropbox.ini", "General", "directory", ui->edtDir->text());

            qDebug() << "settings saved...";
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::showContextMenu(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = ui->listDropbox->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("Erase",  this, SLOT(eraseItem()));

    // Show context menu at handling position
    myMenu.exec(globalPos);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::eraseItem()
{
    // If multiple selection is on, we need to erase all selected items
    for (int i = 0; i < ui->listDropbox->selectedItems().size(); ++i) {
        // Get curent item on selected row
        QListWidgetItem *item = ui->listDropbox->item( ui->listDropbox->currentRow());
        // And remove it
        qDebug() << item->toolTip();

        if ( item->textColor() != Qt::red ) {

            QDropbox2File db_file(item->toolTip(), m_Dropbox2);
            if ( db_file.remove() ) {
                QMessageBox::information(this, this->windowTitle(),  tr("Dropbox Datei erfolgreich gelöscht!") );
            }
        }
    }

    this->on_cmdGetFiles_clicked();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::on_cmdMakedir_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Name des Ordners"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {

        QDropbox2Folder db_folder(ui->edtDir->text() + "/" + text, m_Dropbox2);
        if ( db_folder.create() ) {
            QMessageBox::information(this, this->windowTitle(),  tr("Dropbox Verzeichniss erfolgreich angelegt!") );
        } else {
            QMessageBox::critical(this, this->windowTitle(),  tr("Dropbox Verzeichniss konnte nicht angelegt werden!") );
        }
    }

    this->on_cmdGetFiles_clicked();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::on_cmdRemove_clicked()
{
    QString item;

    QList<QListWidgetItem *> items = ui->listDropbox->selectedItems();

    if ( items.count() == 1 ) {

        QMessageBox msgBox;

        msgBox.setWindowTitle( this->windowTitle() );
        msgBox.setText("Wirklich löschen?");

        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int retVal = msgBox.exec();

        if(retVal == QMessageBox::Yes){

            item = items.at(0)->toolTip();

            if ( items.at(0)->textColor() == Qt::red ) {

                QDropbox2Folder db_folder(item, m_Dropbox2);

                if ( db_folder.remove() ) {
                    QMessageBox::information(this, this->windowTitle(),  tr("Dropbox Ordner erfolgreich gelöscht!") );
                }
            } else {

                QDropbox2File db_file(item, m_Dropbox2);
                if ( db_file.remove() ) {
                    QMessageBox::information(this, this->windowTitle(),  tr("Dropbox Datei erfolgreich gelöscht!") );
                }
            }
        }
    } else {
        QMessageBox::information(this, this->windowTitle(),  tr("Bitte nur ein Verzeichniss auswählen!") );
    }

    this->on_cmdGetFiles_clicked();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::getDirectoryList(QString directory) {

    if ( m_Dropbox2 == NULL ) {
        return;
    }

    ui->listDropbox->clear();

    QDropbox2Folder db_folder(directory, m_Dropbox2);
    QDropbox2Folder::ContentsList contents;

    if ( db_folder.contents(contents) ) {

        ui->listDropbox->addItem ( ".." );

        foreach(const QDropbox2EntityInfo& entry, contents)
        {
            if( ! entry.isDeleted()) {

                QListWidgetItem *item = new QListWidgetItem();

                item->setToolTip( entry.path() );
                item->setText( entry.filename() );

                if(entry.isDirectory()) {
                    item->setTextColor( Qt::red );
                }

                ui->listDropbox->addItem ( item );
            }
        }
    } else {
         QMessageBox::information(this, this->windowTitle(),  tr("Keine Dateien in Ihrer Dropbox!") );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DropboxBrowser::on_listDropbox_itemDoubleClicked(QListWidgetItem *item)
{
    QString dirpath;

    if ( item->textColor().name().contains("#ff0000") ) {

        ui->edtDir->setText( item->toolTip() );

    } else if ( item->text().contains("..") ) {

        dirpath = ui->edtDir->text();

        if( dirpath.left(dirpath.lastIndexOf('/')).trimmed().isEmpty() ){
            dirpath = ui->edtDir->text();
        } else {
            dirpath = dirpath.left(dirpath.lastIndexOf('/'));
        }

        ui->edtDir->setText( dirpath );
    }

    this->on_cmdGetFiles_clicked();
}
