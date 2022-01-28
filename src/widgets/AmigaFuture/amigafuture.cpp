#include "amigafuture.h"
#include "ui_amigafuture.h"

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
AmigaFuture::AmigaFuture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AmigaFuture)
{
    m_sSettingsFile = INI_FILE;

    ui->setupUi(this);

    QSettings settings("state.ini", QSettings::IniFormat);

    ui->splitter->restoreState( settings.value("AmigaFutureGeometrySplitterState", "" ).toByteArray() );
    restoreGeometry(settings.value("AmigaFutureGeometry").toByteArray());

    this->initMagazine();

    m_Item = nullptr;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
AmigaFuture::~AmigaFuture()
{
    delete ui;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void AmigaFuture::closeEvent(QCloseEvent *event) {

    QSettings settings("state.ini", QSettings::IniFormat);

    settings.setValue("AmigaFutureGeometrySplitterState", ui->splitter->saveState());
    settings.setValue("AmigaFutureGeometry", this->saveGeometry());

    event->accept();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void AmigaFuture::addTreeRoot(QString name, QString description, QString url, int from, int to)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeMagazine);
    int i, counter = 0;

    treeItem->setText(0, name);
    treeItem->setText(1, description);

    for ( i = from; i <= to; i++ ) {
        counter++;
        addTreeChild(treeItem, QString("Page %1").arg(counter), " ", QString(url).arg(i));
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void AmigaFuture::addTreeChild(QTreeWidgetItem *parent,
                  QString name, QString description, QString url)
{
    QString text;

    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    qDebug() << name << url;

    treeItem->setData(0, 1, url);
    treeItem->setText(0, name);
    treeItem->setToolTip(0, parent->text(0) );

    const QString filename = QString("%1 (%2).jpg").arg(parent->text(0)).arg(name);

    text = m_settings.loadStringSetting("amigafuture.ini", filename, "comment");

    treeItem->setText(1, text);

    parent->addChild(treeItem);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void AmigaFuture::initMagazine()
{
    int from, to;
    QString url, desc;

    ui->treeMagazine->setColumnCount(1);

    ui->treeMagazine->setHeaderLabels(QStringList() << "Magazine" << "Description");

    QStringList magazine = m_settings.GetAllKeys("amigafuture.ini", "Magazine");

    foreach (const QString &magazin, magazine) {

        desc = m_settings.loadStringSetting("amigafuture.ini", "magazine", magazin);

        from = m_settings.loadIntSetting("amigafuture.ini", magazin, "from");
        to = m_settings.loadIntSetting("amigafuture.ini", magazin, "to");
        url = m_settings.loadStringSetting("amigafuture.ini", magazin, "url");

        this->addTreeRoot(magazin, desc, url, from, to);

        ui->treeMagazine->resizeColumnToContents(0);
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void AmigaFuture::on_treeMagazine_itemClicked(QTreeWidgetItem *item, int column)
{
    m_Item = item;

    QString destfile;
    QString LibraryPath = m_settings.loadStringSetting("settings.ini", "General", "LibraryPath");

    QString filename = QString("%1 (%2).jpg").arg(m_Item->toolTip(0)).arg(item->text(0));
    QString url = qvariant_cast<QString>(m_Item->data(0, 1));

    qDebug() << filename << url;

    m_tools.createDir( LibraryPath + "Amiga Future/" + m_Item->toolTip(0) + "/" );

    destfile = this->downloadFile(url, filename, LibraryPath + "Amiga Future/" + m_Item->toolTip(0) + "/", false);

    if ( m_tools.fileExists(destfile) ) {

        QImage image(destfile);

        ui->lblDisplay->setPixmap(QPixmap::fromImage(image.scaled( ui->spinScaleFactor->value() * image.width() / 100,
                                                                   ui->spinScaleFactor->value() * image.height() / 100,
                                                                   Qt::KeepAspectRatio)));

        m_settings.saveIntSetting("scalefactor.ini", filename, "ScaleFactor", ui->spinScaleFactor->value());
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QString AmigaFuture::downloadFile(QUrl iUrl, QString fileName, QString iDest, bool force) {

    if ( ! iUrl.isValid() ) {
        qDebug() << "downloadFile" << iUrl.toString() << "not valid!";
        return "";
    }

    if ( m_tools.fileExists( iUrl.toLocalFile() ) ) {
        qDebug() << "downloadFile" << iUrl.toLocalFile() << "FileExists true!";
        return iUrl.toLocalFile() ;
    } else {
        qDebug() << "downloadFile" << iUrl.toLocalFile() << "FileExists false!";
    }

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

    qDebug() << "downloadFile" << iUrl << " to: " << fileName;

    QFileInfo fi;
    fi.setFile( destFileName ) ;

    if ( ( ! ( fi.exists() && fi.size() > 0 )  ) || force ) {

        args << "-O" << destFileName << "--no-check-certificate" << "--user-agent=Mozilla" << iUrl.toString();

        qDebug() << args;

        if ( ExecuteProgram(program, args, true) ) {
            foreach (QString line, m_stdOutLines){
               output = output + line;
            }

            qDebug() << "downloadFile" << destFileName << " retrieved...";
        }
    } else {
        qDebug() << "downloadFile" << destFileName << " already exists...";
    }

    if ( ! fi.exists() ) {
        destFileName.clear();
    }

    return destFileName;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool AmigaFuture::ExecuteProgram(QString program, QStringList arguments, bool wait) {

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
void AmigaFuture::on_spinScaleFactor_valueChanged(const QString &arg1)
{    
    if (! m_Item) {
        return;
    }

    this->on_treeMagazine_itemClicked(m_Item, 0);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void AmigaFuture::on_beenden_clicked()
{
    this->close();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void AmigaFuture::on_treeMagazine_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString filename;

    bool ok;
    // Ask for birth date as a string.
    QString text = QInputDialog::getText(nullptr, "Input dialog",
                                        "Comment:", QLineEdit::Normal,
                                        "", &ok);
    if (ok && !text.isEmpty()) {

        filename = QString("%1 (%2).jpg").arg(m_Item->toolTip(0)).arg(item->text(0));

        m_settings.saveStringSetting("amigafuture.ini", filename, "comment", text);

        item->setText(1, text);
    }
}
