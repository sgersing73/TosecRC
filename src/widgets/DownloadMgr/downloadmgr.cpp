#include "downloadmgr.h"
#include "ui_downloadmgr.h"

DownloadMgr::DownloadMgr(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DownloadMgr)
{
    ui->setupUi(this);

    this->setGeometry(QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()))   ;

    m_sSettingsFile = INI_FILE;

    m_TempPath = m_settings.loadStringSetting(m_sSettingsFile, "General", "TempPath");

    m_tools.createDir(m_TempPath);

    QSettings settings("DownloadMgr", "Global");

    ui->edtDownloadDir->setText( settings.value("DestDir", "/").toString() );
    ui->edtParameter->setText( settings.value("Parameters", "-c -t 10").toString() );

    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("E&xit"), this, SLOT(closeDownloadMgr()), QKeySequence::Quit);

    // create a timer
    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));

    m_queueFile = "downloads.txt";

    readQueueentries();

    ui->cmdDownload->setStyleSheet("background-color: lightgreen");

    m_DownloadActive = false;

    //m_tools.systemShutdown();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::closeDownloadMgr()
{
    this->close();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::processStarted()
{
    qDebug() << "processStarted()";
    m_DownloadActive = true;

    ui->cmdDownload->setStyleSheet("background-color: red");
    ui->cmdDownload->setEnabled(false);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::printOutput()
{
    QString temp;

    mTranscodingProcess->setReadChannel(QProcess::ProcessChannel::StandardOutput);

    while (mTranscodingProcess->canReadLine()) {

        const QString line = QString::fromLocal8Bit(mTranscodingProcess->readLine());

        if (line.contains("%")) {

            const QStringList responseArr = line.trimmed().split(" ");

            if ( responseArr.count() >= 6 ) {

                QStringList value = responseArr.filter("%");

                if ( ! value.isEmpty() ) {
                    temp = value.at(0);
                }

                ui->progressBar->setValue( temp.remove("%").toInt() );
                ui->lblEstimate->setText( responseArr.last() );
            }
        }

        ui->edtOutput->append( line );
        ui->edtOutput->repaint();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::printError()
{
    mTranscodingProcess->setReadChannel(QProcess::ProcessChannel::StandardError);

    while (mTranscodingProcess->canReadLine()) {
       QString line = QString::fromLocal8Bit(mTranscodingProcess->readLine());
       ui->edtOutput->append( line );
       ui->edtOutput->repaint();
    }
}
/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::encodingFinished()
{
    qDebug() << "processFinished()";

    m_DownloadActive = false;

    ui->cmdDownload->setStyleSheet("background-color: lightgreen");
     ui->cmdDownload->setEnabled(true);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
DownloadMgr::~DownloadMgr()
{
    delete ui;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::on_cmdDownload_clicked()
{
    QString program = "wget.exe";

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

    if ( ui->lisDownload->selectedItems().isEmpty() ) {
        QMessageBox::information(
                this,
                qAppName(),
                tr("no item selected") );
        return;
    }

    if ( ui->edtDownloadDir->text().isEmpty() ) {
        QMessageBox::information(
                this,
                qAppName(),
                tr("please select a destination directory!") );
        return;
    }

    m_OutputString.clear();

    ui->edtOutput->clear();
    ui->edtOutput->setStyleSheet("background-color: none");

    QStringList arguments;

    arguments << ui->edtParameter->text().split(" ") << "-c" << ui->lisDownload->currentItem()->text() << "-P" <<  ui->edtDownloadDir->text();

    qDebug() << program << arguments;

    mTranscodingProcess = new QProcess(this);

    connect(mTranscodingProcess, SIGNAL(started()), this, SLOT(processStarted()));
    connect(mTranscodingProcess, SIGNAL(finished(int)), this, SLOT(encodingFinished()));
    connect(mTranscodingProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(printOutput()));
    connect(mTranscodingProcess, SIGNAL(readyReadStandardError()), this, SLOT(printError()));

    mTranscodingProcess->setProcessChannelMode(QProcess::MergedChannels);

    mTranscodingProcess->start(program, arguments);

    while ( ( mTranscodingProcess->state() == QProcess::Running ) || ( mTranscodingProcess->state() == QProcess::Starting ) ) {
        QCoreApplication::processEvents();
    }

    if ( mTranscodingProcess->exitCode() != 0 )  {

        QString infotxt = QString("Something went wrong - %1\n\nExitCode: %2\n\nContinue?").arg(program).arg(mTranscodingProcess->exitCode());

        qDebug() << infotxt;
    }

    delete mTranscodingProcess;

    if ( ui->chkAutoDownloadNext->isChecked() ) {

        if ( ui->lisDownload->currentRow()+1 < ui->lisDownload->count()  ) {

            ui->lisDownload->setCurrentRow( ui->lisDownload->currentRow() + 1 );

            on_cmdDownload_clicked();

        } else {
            ui->chkAutoDownloadNext->setCheckState( Qt::CheckState::Unchecked );
            ui->lisDownload->setCurrentRow( 0 );
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::on_cmdAdd_clicked()
{
    ui->lisDownload->addItem( ui->edtUrl->text() );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::writeQueueentries()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Downloader Queue File"), "downloads.txt", "Text files (*.txt)");

    QFile pfile(fileName);
    if (!pfile.open(QFile::WriteOnly | QIODevice::Text)) {
       return;
    }

    for(int row = 0; row < ui->lisDownload->count(); row++)
    {
       QListWidgetItem *item = ui->lisDownload->item(row);
       QTextStream out(&pfile);
       out << item->text().simplified() << "\n";
    }

    pfile.close();

    QMessageBox::information(
            this,
            qAppName(),
            tr("Queue entries successfull written!") );

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::readQueueentries()
{
    ui->lisDownload->clear();

    QFile pfile(m_queueFile);
    if (!pfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&pfile);

    while (!in.atEnd())
    {
        QString line = in.readLine();

        if ( (ui->edtFilter->text().isEmpty()) || line.contains(ui->edtFilter->text().trimmed()) ) {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(line);
            ui->lisDownload->addItem(item);
        }

    }

    pfile.close();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::on_cmdLoadList_clicked()
{
    QString lastDir;
    QSettings settings("DownloadMgr", "Global");

    lastDir = settings.value("LastQueueFilePath", "/").toString();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Downloader Queue File"), lastDir, "Text files (*.txt)" );
    if (fileName.isEmpty()) {
        return;
    } else {
        settings.setValue("LastQueueFilePath", QFileInfo(fileName).path() );
        m_queueFile = fileName;
    }

    readQueueentries();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::on_cmdSaveList_clicked()
{
    writeQueueentries();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::on_cmdDelEntry_clicked()
{
   ui->lisDownload->takeItem ( ui->lisDownload->row(ui->lisDownload->currentItem()) );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::on_toolButton_clicked()
{
    ui->edtDownloadDir->setText( QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks) );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::closeEvent(QCloseEvent *event) {

    QSettings settings("DownloadMgr", "Global");

    settings.setValue("DestDir", ui->edtDownloadDir->text());
    settings.setValue("Parameters", ui->edtParameter->text());

    if ( m_DownloadActive ) {

        QMessageBox msgBox;

        msgBox.setWindowTitle("Download Manager");
        msgBox.setText("Exit will cancel the active download?");

        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int retVal = msgBox.exec();

        if ( retVal == QMessageBox::Yes ) {

            mTranscodingProcess->kill();
            event->accept();

        } else if ( retVal == QMessageBox::No ) {

            event->ignore();
        }
    } else {
        event->accept();
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::MyTimerSlot()
{

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void  DownloadMgr::tailLogfile() {

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::on_cmdCancelDownload_clicked()
{
    ui->chkAutoDownloadNext->setCheckState( Qt::CheckState::Unchecked );

    if ( m_DownloadActive ) {

        QMessageBox msgBox;

        msgBox.setWindowTitle("Download Manager");
        msgBox.setText("Cancel the active download?");

        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int retVal = msgBox.exec();

        if ( retVal == QMessageBox::Yes ) {

            mTranscodingProcess->kill();

        } else if ( retVal == QMessageBox::No ) {

        }

    } else {

    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::on_lisDownload_itemDoubleClicked(QListWidgetItem *item)
{
    on_cmdDownload_clicked();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::on_cmdClearList_clicked()
{
    ui->lisDownload->clear();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void DownloadMgr::on_chkHideOutput_clicked()
{
    if ( ui->chkHideOutput->isChecked() ) {
        ui->edtOutput->setVisible(false);
    } else {
        ui->edtOutput->setVisible(true);
    }
}
