#include "ftpupload.h"
#include "ui_ftpupload.h"

FtpUpload::FtpUpload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpUpload)
{
    m_file = nullptr;
    m_ftp = nullptr;
    m_item = nullptr;

    ui->setupUi(this);

    ui->fileList->setEnabled(false);
    ui->fileList->setRootIsDecorated(false);
    ui->fileList->setHeaderLabels(QStringList() << tr("Name") << tr("Size") << tr("Owner") << tr("Group") << tr("Time"));
    ui->fileList->header()->setStretchLastSection(false);

    this->setWindowTitle("FTP Upload Client");

    connect(ui->fileList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, SLOT(processItem(QTreeWidgetItem*,int)));
    connect(ui->fileList, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(setCurrentItem(QTreeWidgetItem*,int)));

    //connect(ui->fileList, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
    //        this, SLOT(enableDownloadButton()));


    fillComboFtpServer();
}

FtpUpload::~FtpUpload()
{
    delete ui;
}

void FtpUpload::on_selectFileButton_clicked()
{
    m_fileName = QFileDialog::getOpenFileName(this, "Get Any File");
    ui->fileNameLineEdit->setText(m_fileName);
}

void FtpUpload::updateDataTransferProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug() << "-I- uploadProgress" << bytesSent << bytesTotal ;

    if ( bytesTotal > 0 && bytesSent > 0 ) {

        m_progressDialog->setMaximum(bytesTotal);
        m_progressDialog->setValue(bytesSent);
    }
}

void FtpUpload::setFileName(QString filename)
{
    m_fileName = filename;

    ui->fileNameLineEdit->setText(m_fileName);
}

void FtpUpload::on_pushButton_clicked()
{
    this->close();
}

void FtpUpload::fillComboFtpServer() {

    ui->comboBox->clear();
    ui->comboBox->addItem("");

    QStringList keys = m_settings.GetAllKeys("settings.ini", "FtpServer");

    qDebug() << "-I- fillComboFtpServer" << keys;

    foreach (const QString &key, keys) {

        ui->comboBox->addItem(key);
    }

    on_comboBox_currentTextChanged("");
}

void FtpUpload::on_comboBox_currentTextChanged(const QString &arg1)
{
    if ( arg1.trimmed().isEmpty() ) {

        ui->cmdSave->setEnabled( false );
        ui->cmdConnect->setEnabled( false );
        ui->cmdDelete->setEnabled( false );

    } else {

        ui->cmdSave->setEnabled( true );
        ui->cmdConnect->setEnabled( true );
        ui->cmdDelete->setEnabled( true );

        QString txt =  m_settings.loadStringSetting("settings.ini", "FtpServer", arg1);

        ui->uploadUrlLineEdit->setText( "" );
        ui->edtUser->setText("");
        ui->edtPasswort->setText("");
        ui->edtPath->setText("");

        if ( ! txt.isEmpty() ) {

            QStringList values = txt.split(",");

            if ( values.count() >= 4) {

                ui->uploadUrlLineEdit->setText( values.at(0) );
                ui->edtUser->setText( values.at(1) );
                ui->edtPasswort->setText( values.at(2) );
                ui->edtPath->setText( values.at(3) );
            }
        }
    }

}

void FtpUpload::on_cmdSave_clicked()
{
    QString lastselect = ui->comboBox->currentText();

    QString txt = QString("%1,%2,%3,%4")
            .arg(ui->uploadUrlLineEdit->text())
            .arg(ui->edtUser->text())
            .arg(ui->edtPasswort->text())
            .arg(ui->edtPath->text());

    m_settings.saveStringSetting("settings.ini", "FtpServer", ui->comboBox->currentText(), txt);

    fillComboFtpServer();

    ui->comboBox->setCurrentText( lastselect ) ;

    QMessageBox::information( this, this->windowTitle(), "entry saved" ) ;
}

void FtpUpload::on_cmdDelete_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this, this->windowTitle(), tr("do you realy want to deleted this entry?")))
    {
        m_settings.Delete("settings.ini", "FtpServer", ui->comboBox->currentText());

        fillComboFtpServer();

        QMessageBox::information( this, this->windowTitle(), "entry deleted" ) ;
    }
}

void FtpUpload::commandStarted(int commandId)
{
    qDebug() << "-I- commandStarted" << commandId;
}

void FtpUpload::commandFinished(int commandId, bool error)
{
    if ( m_ftp->currentCommand() == QFtp::ConnectToHost ) {
        if ( error ) {

            qDebug() << "-I- commandFinished" << commandId << m_ftp->errorString() ;

            ui->widLed->setColor( QColor(Qt::gray) ) ;

            ui->cmdUpload->setEnabled(false);
            ui->cmdDownload->setEnabled(false);
            ui->cmdParent->setEnabled(false);
            ui->cmdRemove->setEnabled(false);
            ui->cmdMkdir->setEnabled(false);

        } else {

            ui->fileList->clear();
            ui->cmdUpload->setEnabled(true);
            ui->cmdDownload->setEnabled(true);

            ui->widLed->setColor( QColor(Qt::green) ) ;

            qDebug() << "-I- commandFinished" << commandId ;
        }

        ui->widLed->setChecked(true);

    } else if (m_ftp->currentCommand() == QFtp::Login) {

        m_ftp->list();

    } else if ( m_ftp->currentCommand() == QFtp::List) {

        if (isDirectory.isEmpty()) {
            ui->fileList->addTopLevelItem(new QTreeWidgetItem(QStringList() << tr("<empty>")));
            ui->fileList->setEnabled(false);
        }

    } else if ( m_ftp->currentCommand() == QFtp::Put) {

        ui->fileList->clear();
        m_ftp->list();

        m_progressDialog->deleteLater();

    } else if (m_ftp->currentCommand() == QFtp::Get) {

        m_progressDialog->deleteLater();

    } else if ( m_ftp->currentCommand() == QFtp::Remove || m_ftp->currentCommand() == QFtp::Rmdir || m_ftp->currentCommand() == QFtp::Mkdir ) {

        ui->fileList->clear();
        m_ftp->list();

    } else {

    }

    if ( error ) {
        qDebug() << "-I- commandFinished" << commandId << m_ftp->errorString() ;
        QMessageBox::critical( this, "Failure", m_ftp->errorString() ) ;
    }
}

void FtpUpload::done(bool done)
{
    qDebug() << "-I- done" << done << m_ftp->state();

    if ( m_file && m_file->isOpen() ) {

        qDebug() << "file closed..." ;

        m_file->close();
        m_file->deleteLater();

        m_file = nullptr;

    }
}

void FtpUpload::on_cmdConnect_clicked()
{
    QUrl url(ui->uploadUrlLineEdit->text());

    if ( ui->widLed->color() == Qt::green ) {

        m_ftp->abort();
        m_ftp->deleteLater();
        m_ftp = nullptr;
    }

    m_ftp = new QFtp(this);
    if (m_ftp) {

        connect(m_ftp, SIGNAL(commandFinished(int,bool)), this, SLOT(commandFinished(int,bool)));
        connect(m_ftp, SIGNAL(dataTransferProgress(qint64,qint64)), this, SLOT(updateDataTransferProgress(qint64,qint64)));
        connect(m_ftp, SIGNAL(commandStarted(int)), this, SLOT(commandStarted(int)));
        connect(m_ftp, SIGNAL(done(bool)), this, SLOT(done(bool)));
        connect(m_ftp, SIGNAL(listInfo(QUrlInfo)), this, SLOT(addToList(QUrlInfo)));

        qDebug() << "-I- connectToHost" << url.host() << url.port(21);

        m_ftp->connectToHost(url.host(), url.port(21));

        if ( ! ui->edtUser->text().isEmpty() ) {
            qDebug() << "-I- login"    << ui->edtUser->text() << ui->edtPasswort->text();
            m_ftp->login(ui->edtUser->text(), ui->edtPasswort->text());
        } else {
            qDebug() << "-I- login plain";
            m_ftp->login();
        }

        if ( ! ui->edtPath->text().isEmpty() ) {
            qDebug() << "-I- cd to path" << ui->edtPath->text();
            m_ftp->cd( ui->edtPath->text().trimmed() );            
        }
    }
}

void FtpUpload::addToList(const QUrlInfo &urlInfo)
{

    QLocale   locale = this->locale();

    qDebug() << "addToList" << urlInfo.name();

    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, urlInfo.name());
    item->setText(1, locale.formattedDataSize(urlInfo.size()));
    item->setText(2, urlInfo.owner());
    item->setText(3, urlInfo.group());
    item->setText(4, urlInfo.lastModified().toString("MMM dd yyyy"));

    QPixmap pixmap(urlInfo.isDir() ? ":/images/ftp/images/farious/dir/dir.png" : ":/images/ftp/images/farious/dir/file.png");
    item->setIcon(0, pixmap);

    isDirectory[urlInfo.name()] = urlInfo.isDir();
    ui->fileList->addTopLevelItem(item);

    if (!ui->fileList->currentItem()) {

        ui->fileList->setCurrentItem(ui->fileList->topLevelItem(0));

        ui->fileList->setEnabled(true);
        ui->cmdParent->setEnabled(true);
        ui->cmdRemove->setEnabled(true);
        ui->cmdMkdir->setEnabled(true);
    }
}

void FtpUpload::setCurrentItem(QTreeWidgetItem *item, int /*column*/) {

    qDebug() << "setCurrentItem" << item->text(0);

    m_item = item;

    qDebug() << "setCurrentItem" << currentPath;
}

void FtpUpload::processItem(QTreeWidgetItem *item, int /*column*/)
{        
    QString name = item->text(0);

    qDebug() << "processItem" << name;

    if (isDirectory.value(name)) {

        ui->fileList->clear();
        isDirectory.clear();

        currentPath += '/';
        currentPath += name;

        m_ftp->cd(name);
        m_ftp->list();

    }

    m_item = nullptr;

    qDebug() << "processItem" << currentPath;
}

void FtpUpload::on_cmdParent_clicked()
{
    ui->fileList->clear();
    isDirectory.clear();

    currentPath = currentPath.left(currentPath.lastIndexOf('/'));

    qDebug() << "on_cmdParent_clicked" << currentPath;

    if (currentPath.isEmpty()) {
        m_ftp->cd(ui->edtPath->text());
    } else {
        m_ftp->cd(ui->edtPath->text() + currentPath);
    }

    m_ftp->list();
}

void FtpUpload::on_cmdMkdir_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Directory name"), tr("Directory name:"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {

        m_ftp->mkdir( text );
    }
}

void FtpUpload::on_cmdRemove_clicked()
{
    if ( m_item ) {

        qDebug() << "on_cmdRemove_clicked" << m_item->text(0) ;

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, this->windowTitle(), "Wirklich löschen?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            if ( isDirectory.value(m_item->text(0)) ) {
                m_ftp->rmdir( m_item->text(0) ) ;
            } else {
                m_ftp->remove( m_item->text(0) ) ;
            }

            m_item = nullptr;
        }
    } else {

        QMessageBox::information(this, this->windowTitle(), "no item selected");
    }
}

void FtpUpload::on_cmdUpload_clicked()
{
    m_file = new QFile(m_fileName);

    QFileInfo fileInfo(*m_file);

    QUrl url(ui->uploadUrlLineEdit->text());

    if (m_file->open(QIODevice::ReadOnly)) {

        qDebug() << "-I- starting upload..." << url.url();

        if ( ui->widLed->color() == Qt::green ) {

            m_progressDialog = new QProgressDialog(this);
            connect(m_progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));

            m_progressDialog->setLabelText(tr("Uploading %1...").arg(m_fileName));

            qDebug() << "-I- put" << fileInfo.fileName() ;
            m_ftp->put(m_file, fileInfo.fileName());
        }

    } else {
        qDebug() << "-E-" << "unable to open file" << m_fileName;
    }
}

void FtpUpload::on_cmdDownload_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                "Open Document",
                QDir::currentPath() + "/" + ui->fileList->currentItem()->text(0),
                "All files (*.*)");

    if( fileName.isNull() ) {
        return;
    }

    if (QFile::exists(fileName)) {
        QMessageBox::information(this, tr("FTP"),
                                 tr("There already exists a file called %1 in "
                                    "the current directory.")
                                 .arg(fileName));
        return;
    }

    m_file = new QFile(fileName);
    if (!m_file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("FTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(m_file->errorString()));
        delete m_file;
        return;
    }

    m_progressDialog = new QProgressDialog(this);
    connect(m_progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));

    m_ftp->get(ui->fileList->currentItem()->text(0), m_file);

    m_progressDialog->setLabelText(tr("Downloading %1...").arg(fileName));
}

void FtpUpload::cancelDownload()
{
    if (m_ftp)
        m_ftp->abort();
}
