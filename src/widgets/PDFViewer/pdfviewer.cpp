#include "pdfviewer.h"
#include "ui_pdfviewer.h"

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
PDFViewer::PDFViewer(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::PDFViewer)
{
    QDir dir;

    ui->setupUi(this);

    m_LibraryPath = m_settings.loadStringSetting("settings.ini", "General", "LibraryPath");
    m_CachePath = m_settings.loadStringSetting("settings.ini", "General", "CachePath");
    m_TempPath = m_settings.loadStringSetting("settings.ini", "General", "TempPath");

    ui->cmdCancelDownload->setVisible ( false );

    ui->listWidgetTitels->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidgetTitels, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenulistWidgetTitels(const QPoint&)));

    m_sSettingsFile = INI_FILE;

    QSettings settings("state.ini", QSettings::IniFormat);

    ui->splitter->restoreState( settings.value("PDFViewerGeometrySplitterState", "" ).toByteArray() );
    restoreGeometry(settings.value("PDFViewerGeometry").toByteArray());

    m_Filename = filename;

    if ( ! m_Filename.isEmpty() ) {

        ui->splitter->setSizes( QList<int>() << 0 << this->width() );
        ui->listWidgetThumb->setVisible(false);

        m_externalView = true;

        this->setWindowTitle("PDF Viewer - " + m_Filename );

    } else {

        ui->listWidgetThumb->setVisible(true);

        m_externalView = false;

        QString thumbs_path = m_LibraryPath + ui->cboSections->currentText() + "/thumbs";

        dir.mkpath( thumbs_path );
    }

    int scaleFactor = m_settings.loadIntSetting("scalefactor.ini", QFileInfo(m_Filename).fileName(), "ScaleFactor");

    if ( scaleFactor > 0 ) {
        ui->spinScaleFactor->setValue( scaleFactor );
    } else {
        ui->spinScaleFactor->setValue( 40 );
    }

    int page = m_settings.loadIntSetting("scalefactor.ini", QFileInfo(m_Filename).fileName(), "Page");

    if ( page > 0 ) {
        ui->edtPage->setText( QString("%1").arg(page) );
    } else {
        page = 1;

        ui->edtPage->setText( QString("%1").arg(page) );
    }

    ui->lblInfo->setText("");
    ui->edtOutput->setVisible(false);

    if ( ! m_externalView ) {

        QStringList sections = m_settings.getAllSection("catalog.ini");

        sections.removeOne("Logos");
        sections.removeOne("Color");

        foreach(QString section, sections) {

            ui->cboSections->addItem( section );
        }
    }

    QPixmap pix(":/cursor/images/cursor/amiga/amiga_original/amiga_arrow.cur");
    QCursor cur(pix,1,1);
    this->setCursor( cur );

    ui->lstInfo->setVisible(false);

    ui->sliPages->setValue( ui->edtPage->text().toInt() );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
PDFViewer::~PDFViewer()
{
    delete ui;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cmdBackward_clicked()
{
    int actPage = ui->edtPage->text().toInt();

    int nextPage = actPage - 1;

    if (nextPage < 1) nextPage = 1;

    this->ui->edtPage->setText( QString("%1").arg(nextPage) );

    ui->sliPages->setValue( nextPage );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cmdForward_clicked()
{
    int actPage = ui->edtPage->text().toInt();

    int nextPage = actPage + 1;

    if (nextPage > ui->sliPages->maximum() ) nextPage = ui->sliPages->maximum();

    ui->edtPage->setText( QString("%1").arg(nextPage) );

    ui->sliPages->setValue( nextPage );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::loadPage(int page, int factor) {

    QString     thumbs_path = m_LibraryPath + ui->cboSections->currentText() + "/thumbs";
    QDir        dir;

    if ( m_Filename.isEmpty() ) {
        return;
    }

    ui->scrollDisplay->verticalScrollBar()->setValue(0);

    Poppler::Document* document = Poppler::Document::load(m_Filename);
    if (!document || document->isLocked()) {
      // ... error message ....
      delete document;
      return;
    }

    ui->sliPages->setMinimum( 1 );
    ui->sliPages->setMaximum( document->numPages() );

    // Paranoid safety check
    if (document == nullptr) {
      // ... error message ...
      return;
    }

    ui->lstInfo->setVisible(false);

    if ( document->infoKeys().count() > 0 ) {

        ui->lstInfo->clear();
        ui->lstInfo->setColumnCount (2);
        ui->lstInfo->setRowCount ( document->infoKeys().count() );

        int counter=0;
        foreach ( QString key, document->infoKeys() ) {
            ui->lstInfo->setItem(counter, 0, new QTableWidgetItem(key));
            ui->lstInfo->setItem(counter, 1, new QTableWidgetItem(document->info(key)));
            counter++;
        }

        ui->lstInfo->resizeRowsToContents();
        ui->lstInfo->resizeColumnsToContents();
        ui->lstInfo->setVisible(true);
    }

    // Access page of the PDF file
    Poppler::Page* pdfPage = document->page(page - 1);  // Document starts at page 0
    if (pdfPage == nullptr) {
      // ... error message ...
      return;
    }

    ui->sliPages->setValue( page );

    // Generate a QImage of the rendered page
    QImage image = pdfPage->renderToImage(  factor * physicalDpiX() / 72.0,
                                            factor * physicalDpiY() / 72.0);
    if (image.isNull()) {
      // ... error message ...
      return;
    }

    ui->lblDisplay->setPixmap(QPixmap::fromImage(image));

    delete pdfPage;
    delete document;

    if ( ( ! m_externalView ) &&
         ( page == 1 ) &&
         ( ! m_tools.fileExists( thumbs_path + "/" + QFileInfo(m_Filename).fileName() + ".jpg") )) {

        const QPixmap* pix = ui->lblDisplay->pixmap();

        dir.mkpath( thumbs_path );

        if ( pix->scaled(49 * 2, 70 * 2, Qt::KeepAspectRatio).save(thumbs_path + "/" + QFileInfo(m_Filename).fileName() + ".jpg") ) {

            qDebug() << "Thumbnail erstellt!";

            this->loadThumbNails( ui->cboSections->currentText() );

        } else {
            qDebug() << "Thumbnail konnte nicht erstellt werden!" << thumbs_path + "/" + QFileInfo(m_Filename).fileName() + ".jpg";
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::closeEvent(QCloseEvent *event) {

    if ( m_Filename.isEmpty() ) {

        QSettings settings("state.ini", QSettings::IniFormat);

        settings.setValue("PDFViewerGeometrySplitterState", ui->splitter->saveState());
        settings.setValue("PDFViewerGeometry", this->saveGeometry());
    }

    event->accept();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cboSections_currentIndexChanged(const QString &arg1)
{
    qDebug() << "on_cboSections_currentIndexChanged" << arg1;

    QFileInfo   fileinfo;
    qint64      size, totalsize = 0;
    qint64      elemente = 0;
    QLocale     locale = this->locale();
    QString     thumbfilename;
    static QString lastSection;

    m_actItemName = "";

    if ( lastSection != ui->cboSections->currentText() ) {

        this->loadThumbNails(arg1);
        this->fillComboYears(arg1);
    }

    lastSection = ui->cboSections->currentText();

    QString value = m_settings.loadStringSetting("catalog.ini", "Logos", ui->cboSections->currentText());

    if ( ! value.isEmpty() ) {

        QString suffix = QFileInfo(value).suffix();

        ui->lblLogo->setHidden(false);

        QString picfilename = this->downloadFile(value, ui->cboSections->currentText() + " (logo)." + suffix, m_CachePath, false) ;

        QPixmap mypix (picfilename);

        ui->lblLogo->setPixmap(mypix.scaled(ui->lblLogo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    } else {
        ui->lblLogo->setHidden(true);
    }

    ui->listWidgetTitels->clear();
    ui->listWidgetBookmarks->clear();
    ui->lstInfo->setVisible(false);

    QStringList values = m_settings.GetAllKeys("catalog.ini", arg1);

    values.sort(Qt::CaseSensitive);

    foreach (QString fileName, values ) {

        elemente++;

        const QString year = m_settings.loadStringSetting("magazin.ini", fileName, "Jahr");

        if ( ( ui->cboYears->currentText().isEmpty() ) || ( ui->cboYears->currentText() == year )  ) {

            QListWidgetItem *item = new QListWidgetItem();

            if ( ! m_tools.fileExists(m_LibraryPath + ui->cboSections->currentText() + "/" + fileName) ) {

                item->setTextColor( Qt::red );
                item->setText( fileName );

            } else {

                fileinfo.setFile( m_LibraryPath + ui->cboSections->currentText() + "/" + fileName);
                size = fileinfo.size();

                const QString number = m_settings.loadStringSetting("magazin.ini", fileName, "Nummer");

                item->setText( QString("%1. %2 (%3)").arg(number).arg(fileName).arg(locale.formattedDataSize(size)) );

                totalsize = totalsize + size;
            }

            item->setToolTip(fileName);

            item->setFont( this->font() );

            ui->listWidgetTitels->addItem( item );

            ui->lblCaption->setText( QString("%1 Einträge geladen/%2 in der Library").arg(elemente).arg(locale.formattedDataSize(totalsize) ) );

            ui->lblDisplay->clear();
        }
    }

    loadInfosMagazin();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_listWidgetTitels_itemClicked(QListWidgetItem *item)
{
    QString     password;
    QDir        dir;
    QStringList arguments;
    QString     unpackpath = m_TempPath + "Unpacked/";

    m_tools.createDir(unpackpath);

    QString     thumbs_path = m_LibraryPath + ui->cboSections->currentText() + "/thumbs";

    this->setWindowTitle("PDF Viewer");

    qDebug() << item->toolTip();

    ui->lblDisplay->clear();
    ui->edtIssueTitle->clear();
    ui->edtVerlag->clear();
    ui->edtErstausgabe->clear();
    ui->edtEinstellung->clear();

    ui->lblInfo->setText(tr("loading data..."));

    QUrl url = m_settings.loadStringSetting("catalog.ini", ui->cboSections->currentText(), item->toolTip());

    if ( url.toString().contains(";") )  {

        QStringList values = url.toString().split(";");

        url = values.at(0);
        password = values.at(1);

    } else {
        password = "";
    }

    QString TempPath = m_settings.loadStringSetting(m_sSettingsFile, "General", "TempPath");

    qDebug() << url;

    QString basename = item->toolTip();
    QString basepath;
    QString suffix =  QFileInfo(item->toolTip()).suffix();

    basepath = m_LibraryPath + ui->cboSections->currentText() + "/";
    basename = basepath + basename;

    m_tools.createDir( QFileInfo(basename).path() );

    qDebug() << "fileExists" << basename;

    if ( ! m_tools.fileExists(basename) ) {

        ui->lblInfo->setText(tr("download data..."));

        ui->edtOutput->clear();
        ui->edtOutput->setVisible(true);
        ui->edtOutput->repaint();

        arguments << "--continue" << "--no-check-certificate" <<  "-O" <<  m_CachePath + url.fileName() << url.toString() ;

        qDebug() << "Download" << arguments;

        if ( this->ExecuteProgram("wget.exe", arguments, true) ) {
            qDebug() << "ExecuteProgram" << "ok";
        } else {
            m_Filename = "";

            qDebug() << "ExecuteProgram" << "failure";
            return;
        }

        if ( m_tools.fileExists( m_CachePath + url.fileName() )) {

            if ( url.fileName().contains("rar") || url.fileName().contains("zip") ) {

                QDir dir( unpackpath );

                if ( ! dir.exists() ) {
                    m_tools.createDir( unpackpath );
                } else {
                    dir.setNameFilters(QStringList() << "*.*");
                    dir.setFilter( QDir::NoDotAndDotDot | QDir::Files );

                    foreach(QString dirFile, dir.entryList()) {
                        dir.remove(dirFile);
                    }
                }

                ui->lblInfo->setText(tr("processing data..."));

                qDebug() << "uncompressing archive" <<  m_CachePath + url.fileName() << "to" << unpackpath ;

                ui->lblInfo->setText(tr("uncompressing data..."));

                arguments.clear();
                arguments << "e" << "-y" << "-o" + unpackpath <<  m_CachePath + url.fileName();

                if ( this->ExecuteProgram("7zip.exe", arguments, true) ) {

                    dir.refresh();
                    dir.setFilter( QDir::NoDotAndDotDot | QDir::Files );
                    foreach(QString dirFile, dir.entryList()) {

                        if ( QFile::copy(unpackpath + dirFile, basename) ) {
                            QFile::remove( unpackpath + dirFile );
                        }

                        qDebug() << "copy file" << unpackpath + dirFile << basename;
                    }

                    qDebug() << "ExecuteProgram" << "ok";

                } else {
                    qDebug() << "ExecuteProgram" << "failure";
                }

                m_Filename = basename;

            } else {

                QFile::copy(  m_CachePath + url.fileName(), basename);

                m_Filename = basename;
            }
        }

    } else {

        qDebug() << "File " << basename << " already in library!";

        m_Filename = basename;
    }

    emit on_cboSections_currentIndexChanged(ui->cboSections->currentText());

    ui->lblInfo->setText(tr("showing data..."));

    int scaleFactor = m_settings.loadIntSetting("scalefactor.ini", QFileInfo(basename).fileName(), "ScaleFactor");

    if ( scaleFactor > 0 ) {
        ui->spinScaleFactor->setValue( scaleFactor );
    } else {
        ui->spinScaleFactor->setValue( 40 );
    }

    int page = m_settings.loadIntSetting("scalefactor.ini", QFileInfo(m_Filename).fileName(), "Page");

    if ( page > 0 ) {
        ui->edtPage->setText( QString("%1").arg(page) );
    } else {
        page = 1;

        ui->edtPage->setText( QString("%1").arg(page) );
    }

    ui->edtOutput->setVisible(false);

    this->loadPage( ui->edtPage->text().toInt(), ui->spinScaleFactor->value() );

    this->setWindowTitle("PDF Viewer - " + basename );

    m_actItemName = QFileInfo(basename).fileName();

    this->loadInfos();

    this->fillBookmarks();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::printOutput()
{
    m_proc->setReadChannel(QProcess::ProcessChannel::StandardOutput);

    while (m_proc->canReadLine()) {

        QString line = QString::fromLocal8Bit(m_proc->readLine());

        ui->edtOutput->append( line );
        ui->edtOutput->repaint();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::printError()
{
    m_proc->setReadChannel(QProcess::ProcessChannel::StandardError);

    while (m_proc->canReadLine()) {
       QString line = QString::fromLocal8Bit(m_proc->readLine());
       ui->edtOutput->append( line );
       ui->edtOutput->repaint();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool PDFViewer::ExecuteProgram(QString program, QStringList arguments, bool wait) {

    bool retVal = true;
    QString errorLine;
    QString infotxt;

    m_proc = new QProcess;

    connect (m_proc, SIGNAL(readyReadStandardOutput()), this, SLOT(printOutput()));
    connect (m_proc, SIGNAL(readyReadStandardError()), this, SLOT(printError()));

    qDebug() << "start..." << QDir::toNativeSeparators(program) << arguments;

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

    QFileInfo fi( QDir::toNativeSeparators(program) );

    m_proc->setWorkingDirectory(fi.absolutePath());
    m_proc->setProcessChannelMode(QProcess::MergedChannels);

 #ifdef WIN32
    if ( arguments.isEmpty() ) {
        m_proc->start("\"" + QDir::toNativeSeparators(program) + "\"");
    } else {
        m_proc->start("\"" + QDir::toNativeSeparators(program) + "\"", arguments);
    }
#endif

#ifdef linux
   if ( arguments.isEmpty() ) {
       m_proc->start( program );
   } else {
       m_proc->start( program, arguments );
   }
#endif

    if (wait) {

        ui->cmdCancelDownload->setVisible ( true );

        while ( ( m_proc->state() == QProcess::Running ) || ( m_proc->state() == QProcess::Starting ) ) {
            QCoreApplication::processEvents();
        }

        if ( m_proc->exitCode() != 0 ) {

            infotxt = QString("Something went wrong - %1\n\nExitCode: %2\n\nContinue?").arg(program).arg(m_proc->exitCode());

            qDebug() << infotxt;

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, this->windowTitle(), infotxt , QMessageBox::Yes|QMessageBox::No );

            if (reply == QMessageBox::Yes) {
            } else {
                retVal = false;
            }
        } else {
            qDebug() << "ExecuteProgram" << program << m_proc->exitCode();
            retVal = true;
        }

        delete m_proc;
    }

    ui->cmdCancelDownload->setVisible ( false );

    return(retVal);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_sliPages_sliderMoved(int position)
{

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_sliPages_valueChanged(int value)
{
    ui->edtPage->setText( QString( "%1" ).arg( value ) );

    this->loadPage( value, ui->spinScaleFactor->value() );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cmdAddLink_clicked()
{
    QUrl url ( ui->edtLink->text() );
    QFileInfo fi( ui->edtTitle->text() ) ;

    qDebug() << url.fileName();

    if (fi.completeSuffix().isEmpty()) {
        ui->edtTitle->text().append(".pdf");
    }

    m_settings.saveStringSetting("catalog.ini", ui->cboSections->currentText(), ui->edtTitle->text(), url.toString() );

    emit on_cboSections_currentIndexChanged(ui->cboSections->currentText());

    ui->edtLink->clear();
    ui->edtTitle->clear();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::ShowContextMenulistWidgetTitels(const QPoint& pos) {

    QList<QListWidgetItem*> items = ui->listWidgetTitels->selectedItems();
    QVariantList values;
    QStringList arglist;
    QString line;
    QDir    dir;

    // for most widgets
    QPoint globalPos = ui->listWidgetTitels->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("delete");
    myMenu.addAction("set page as thumbnail");
    myMenu.addAction("check URL");
    // ...

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( items.count() > 0 && selectedItem ) {

       if ( selectedItem->text().contains("delete") ) {

            QMessageBox::StandardButton reply = QMessageBox::question(this, "PDF Viewer", tr("are you sure to delete the entry?"), QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes) {

                for(int i = 0; i < items.count(); i++) {

                    QListWidgetItem *item = items[i];

                    m_settings.Delete("catalog.ini", ui->cboSections->currentText(), item->toolTip());

                    QMessageBox::information(this, "PDF Viewer",  item->toolTip() + tr(" deleted!") );

                    emit on_cboSections_currentIndexChanged(ui->cboSections->currentText());
                }
            }
       } else if ( selectedItem->text().contains("check URL") ) {

           for(int i = 0; i < items.count(); i++) {

               QListWidgetItem *item = items[i];

               QUrl url = m_settings.loadStringSetting("catalog.ini", ui->cboSections->currentText(), item->toolTip());

               if ( url.toString().contains(";") )  {

                   QStringList values = url.toString().split(";");

                   url = values.at(0);

               }

               if ( ! ( m_tools.checkUrlAlive( url ) ) ) {
                   QMessageBox::warning(this, this->windowTitle(),  "URL:\n" + url.toString() + "\nist nicht erreichbar!!!" );
               } else {
                   QMessageBox::information(this, this->windowTitle(),  "URL:\n" + url.toString() + "\nist erreichbar!!!" );
               }
           }
       } else if ( selectedItem->text().contains("set page as thumbnail") ) {

           for(int i = 0; i < items.count(); i++) {

               QListWidgetItem *item = items[i];

               QUrl url = m_settings.loadStringSetting("catalog.ini", ui->cboSections->currentText(), item->toolTip());

               if ( url.toString().contains(";") )  {

                   QStringList values = url.toString().split(";");

                   url = values.at(0);

               }

               QString thumbs_path = m_LibraryPath + ui->cboSections->currentText() + "/thumbs";

               dir.mkpath( thumbs_path );

               const QPixmap* pix = ui->lblDisplay->pixmap();

               if ( pix->scaled(49 * 2, 70 * 2, Qt::KeepAspectRatio).save(thumbs_path + "/" + item->toolTip() + ".jpg") ) {
                   QMessageBox::warning(this, this->windowTitle(),  "Thumbnail erstellt!" );
               } else {
                   QMessageBox::information(this, this->windowTitle(),  "Thumbnail konnte nicht erstellt werden!" );
               }
           }
       }
   }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QString PDFViewer::downloadFile(QUrl iUrl, QString fileName, QString iDest, bool doLoad) {

    qDebug() << "downloadFile" << iUrl << " to: " << fileName;

    if ( iUrl.isEmpty() ) {
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

    if ( ( ! ( m_tools.fileExists( destFileName ) ) ) || doLoad ) {

        args << "--continue" <<"-O" << destFileName << "--no-check-certificate" << "--user-agent=Mozilla" << iUrl.toString();

        qDebug() << args;

        if ( ExecuteProgram(program, args, true) ) {

            qDebug() << "downloadFile" << destFileName << " retrieved...";
        }
    } else {
        qDebug() << "downloadFile" << destFileName << " already in cache...";
    }

    if ( ! m_tools.fileExists( destFileName ) ) {
        destFileName.clear();
    }

    return destFileName;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_listWidgetThumb_itemClicked(QListWidgetItem *item)
{
    emit on_listWidgetTitels_itemClicked(item);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::loadThumbNails(QString arg1) {

    qDebug() << "loadThumbNails" << arg1;

    QString thumbfilename;

    ui->listWidgetThumb->clear();

    foreach (QString fileName, m_settings.GetAllKeys("catalog.ini", arg1) ) {

        thumbfilename = m_LibraryPath  + arg1 + "/thumbs/" + fileName + ".jpg";

        if ( m_tools.fileExists( thumbfilename ) )  {

            QListWidgetItem *itemThumb = new QListWidgetItem();

            itemThumb->setIcon( QIcon( thumbfilename ) );
            itemThumb->setToolTip(fileName);

            ui->listWidgetThumb->addItem(itemThumb);
        }
        ui->listWidgetThumb->setIconSize(QSize(49, 70));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_edtPage_textChanged(const QString &arg1)
{
    m_settings.saveStringSetting("scalefactor.ini", QFileInfo(m_Filename).fileName(), "Page", arg1);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_spinScaleFactor_valueChanged(int arg1)
{
    m_settings.saveIntSetting("scalefactor.ini", QFileInfo(m_Filename).fileName(), "ScaleFactor", arg1);

    this->loadPage( ui->edtPage->text().toInt(), arg1 );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cmdUpload_clicked()
{
    if ( ! m_Filename.isEmpty() ){

        mMyFtpUpload = new FtpUpload( this );

        mMyFtpUpload->setFileName(m_Filename);
        mMyFtpUpload->show();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cmdExtract_clicked()
{
    QFileInfo   src;
    QFileInfo   dest;

    QStringList files;

    files << m_Filename;

    QString destDir = QFileDialog::getExistingDirectory(this, tr("Save image to..."), "", QFileDialog::ShowDirsOnly);

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

        QMessageBox::information(this, this->windowTitle(),  tr("File creation done in folder ") + destDir );
    }
}

void PDFViewer::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        // qDebug() << "mousePressEvent" << "left";
        this->on_cmdBackward_clicked();
    }

    if (event->button() == Qt::RightButton) {
        // qDebug() << "mousePressEvent" << "right";
        this->on_cmdForward_clicked();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cmdSaveInfos_clicked()
{
    qDebug() << "on_cmdSaveInfos_clicked" << m_actItemName;

    m_settings.saveStringSetting("magazin.ini", m_actItemName, "Nummer", ui->edtNummer->text());
    m_settings.saveStringSetting("magazin.ini", m_actItemName, "Monat", ui->edtMonat->text());
    m_settings.saveStringSetting("magazin.ini", m_actItemName, "Jahr", ui->edtJahr->text());
    m_settings.saveStringSetting("magazin.ini", m_actItemName, "Anmerkung", ui->edtAnmerkung->text());

    m_settings.saveStringSetting("verlag.ini", ui->cboSections->currentText(), "Title", ui->edtIssueTitle->text());
    m_settings.saveStringSetting("verlag.ini", ui->cboSections->currentText(), "Verlag", ui->edtVerlag->text());
    m_settings.saveStringSetting("verlag.ini", ui->cboSections->currentText(), "ISSN", ui->edtISSN->text());
    m_settings.saveStringSetting("verlag.ini", ui->cboSections->currentText(), "Erstausgabe", ui->edtErstausgabe->text());
    m_settings.saveStringSetting("verlag.ini", ui->cboSections->currentText(), "Einstellung", ui->edtEinstellung->text());

    emit on_cboSections_currentIndexChanged(ui->cboSections->currentText());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::loadInfos()
{
    qDebug() << "loadInfos" << m_actItemName << ui->cboSections->currentText();

    ui->edtNummer->setText( m_settings.loadStringSetting("magazin.ini", m_actItemName, "Nummer") ) ;
    ui->edtMonat->setText( m_settings.loadStringSetting("magazin.ini", m_actItemName, "Monat" ) );
    ui->edtJahr->setText( m_settings.loadStringSetting("magazin.ini", m_actItemName, "Jahr" ) );
    ui->edtAnmerkung->setText(m_settings.loadStringSetting("magazin.ini", m_actItemName, "Anmerkung" ));
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::loadInfosMagazin() {

    ui->edtIssueTitle->setText(m_settings.loadStringSetting("verlag.ini", ui->cboSections->currentText(), "Title" ));
    ui->edtVerlag->setText(m_settings.loadStringSetting("verlag.ini", ui->cboSections->currentText(), "Verlag" ));
    ui->edtISSN->setText(m_settings.loadStringSetting("verlag.ini", ui->cboSections->currentText(), "ISSN" ));
    ui->edtErstausgabe->setText(m_settings.loadStringSetting("verlag.ini", ui->cboSections->currentText(), "Erstausgabe" ));
    ui->edtEinstellung->setText(m_settings.loadStringSetting("verlag.ini", ui->cboSections->currentText(), "Einstellung" ));
}

void PDFViewer::on_cboYears_currentTextChanged(const QString &arg1)
{
    emit on_cboSections_currentIndexChanged(ui->cboSections->currentText());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::fillComboYears(const QString arg1) {

    qDebug() << "fillComboYears" << arg1;

    ui->cboYears->blockSignals(true);
    ui->cboYears->clear();

    QStringList years;
    years.clear();

    foreach (QString fileName, m_settings.GetAllKeys("catalog.ini", arg1) ) {

        const QString year = m_settings.loadStringSetting("magazin.ini", fileName, "Jahr");

        years << year;
    }

    years.removeDuplicates();
    years.sort();

    ui->cboYears->addItems( years );

    ui->cboYears->blockSignals(false);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::fillBookmarks() {

    qDebug() << "fillBookmarks" << m_actItemName;

    ui->listWidgetBookmarks->clear();

    foreach (QString name, m_settings.GetAllKeys("bookmarks.ini", m_actItemName) ) {

        const QString page = m_settings.loadStringSetting("bookmarks.ini", m_actItemName, name);

        QListWidgetItem *itemBookmark = new QListWidgetItem();

        itemBookmark->setText(name);
        itemBookmark->setToolTip(page);
        // itemBookmark->setBackgroundColor( Qt::green );

        ui->listWidgetBookmarks->addItem(itemBookmark);
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cmdBookmark_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Bookmark"),
                                         tr("Beschreibung des bookmarks"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {

        m_settings.saveStringSetting("bookmarks.ini", m_actItemName, text, ui->edtPage->text());

        this->fillBookmarks();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_listWidgetBookmarks_itemClicked(QListWidgetItem *item)
{
    int actPage = item->toolTip().toInt();

    ui->edtPage->setText( QString("%1").arg(actPage) );

    ui->sliPages->setValue( actPage );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cmdSectionSettings_clicked()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if( color.isValid() )
    {
      m_settings.saveIntSetting("catalog.ini", "Color", ui->cboSections->currentText(), color.value() );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cmdDownload_clicked()
{
    QDir dir;
    QString basepath;
    QString basename;

    for(int i = 0; i < ui->listWidgetTitels->count(); ++i)
    {

        QListWidgetItem* item = ui->listWidgetTitels->item(i);

        basename = item->toolTip();

        basepath = m_LibraryPath  + ui->cboSections->currentText() + "/";
        basename = basepath + basename;

        if ( ! m_tools.fileExists(basename) ) {
            this->on_listWidgetTitels_itemClicked(item);
        }

        QCoreApplication::processEvents();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void PDFViewer::on_cmdCancelDownload_clicked()
{
    if ( m_proc ) {
        if ( m_proc->state() == QProcess::Running ) {
            m_proc->kill();
        }
    }
}
