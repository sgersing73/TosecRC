#include "qsettingsdialog.h"
#include "ui_qsettingsdialog.h"

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QSettingsDialog::QSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSettingsDialog)
{
    ui->setupUi(this);


    QString currentStyleSheet;

    currentStyleSheet = m_settings.loadStringSetting(INI_FILE, "General", "Stylesheet");

    if ( currentStyleSheet == "NorwegianWood" ) {
        ui->radioButton_7->setChecked(true);
    } else if ( currentStyleSheet == "Bronze" ) {
        ui->radioButton_6->setChecked(true);
    } else if ( currentStyleSheet == "FusionBlack" ) {
        ui->radioButton_5->setChecked(true);
    } else if ( currentStyleSheet == "Fusion" ) {
        ui->radioButton_4->setChecked(true);
    } else if ( currentStyleSheet == "WindowsVista" ) {
        ui->radioButton_3->setChecked(true);
    } else if ( currentStyleSheet == "WindowsXP" ) {
        ui->radioButton_2->setChecked(true);
    } else if ( currentStyleSheet == "Windows" ) {
        ui->radioButton->setChecked(true);
    }

    ui->cboINIFiles->addItems( QStringList() << "settings.ini" << "tools.ini" << "http.ini" ) ;

    this->initCboQssFile( m_settings.loadStringSetting(INI_FILE, "General", "QssFile" ) );
    ui->cboButtonColor->addItems(QStringList() << "red" << "green" << "blue" << "yellow");
    ui->cboButtonColor->setCurrentText( m_settings.loadStringSetting(INI_FILE, "General", "IconColorSchema", "blue" ) );

    ui->lblFontName->setText( m_settings.loadStringSetting(INI_FILE, "General", "FontName" ) );
    ui->lblFontSize->setText( m_settings.loadStringSetting(INI_FILE, "General", "FontSize" ) );

    ui->swProxy->setChecked( m_settings.loadBoolSetting(INI_FILE, "Proxy", "enabled" ) ) ;
    ui->edtProxyUser->setText( m_settings.loadStringSetting(INI_FILE, "Proxy", "user" ) ) ;
    ui->edtProxyPassword->setText( m_settings.loadStringSetting(INI_FILE, "Proxy", "password" ) ) ;
    ui->edtProxyIpAddress->setText( m_settings.loadStringSetting(INI_FILE, "Proxy", "ip" ) ) ;
    ui->edtProxyIpPort->setText( m_settings.loadStringSetting(INI_FILE, "Proxy", "port" ) ) ;

    ui->swHttpEnabled->setChecked( m_settings.loadBoolSetting(INI_FILE, "General", "Httpd" ) ) ;

    /* FTP server settings */
    ui->swFtpEnabled->setChecked( m_settings.loadBoolSetting(INI_FILE, "Ftp", "enabled" ) ) ;
    ui->chkAnonymous->setChecked( m_settings.loadBoolSetting(INI_FILE, "Ftp", "anonymous" ) );
    ui->edtFTPPort->setText( m_settings.loadStringSetting(INI_FILE, "Ftp", "port") );
    ui->edtFTPUser->setText( m_settings.loadStringSetting(INI_FILE, "Ftp", "user") );
    ui->edtFTPPassword->setText (m_settings.loadStringSetting(INI_FILE, "Ftp", "password") );

    /* Dropbox settings */
    ui->edtDropboxKey->setText( m_settings.loadStringSetting("dropbox.ini", "General", "key" ) );
    ui->edtDropboxSecret->setText( m_settings.loadStringSetting("dropbox.ini", "General", "secret" ) );
    ui->edtDropboxDir->setText( m_settings.loadStringSetting("dropbox.ini", "General", "directory" ) );
    ui->edtDropboxToken->setText( m_settings.loadStringSetting("dropbox.ini", "General", "token" ) );

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
QSettingsDialog::~QSettingsDialog()
{
    delete ui;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::initCboQssFile( QString text ) {

    QString path = "qss/";
    QDir dir(path);

    ui->cboQssFiles->addItem(" ");

    foreach(QFileInfo item, dir.entryInfoList() ) {

        if ( item.isFile() && item.suffix() == "qss" )
          ui->cboQssFiles->addItem(item.absoluteFilePath());
    }

    ui->cboQssFiles->setCurrentText ( text ) ;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_cboSections_currentTextChanged(const QString &arg1)
{
    loadData(arg1);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_cmdAddLine_clicked()
{
    qDebug() << ui->grdValues->rowCount();

    ui->grdValues->insertRow( ui->grdValues->rowCount() );
}


/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_cmdCancel_clicked()
{
    this->close();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_cmdOK_clicked()
{
    for (int i = 0; i < ui->grdValues->rowCount(); ++i) {

        if (! ui->grdValues->item(i,0)->text().isEmpty()) {

            m_settings.saveStringSetting(ui->cboINIFiles->currentText(), ui->cboSections->currentText(), ui->grdValues->item(i,0)->text(), ui->grdValues->item(i,1)->text());
        }
    }

    m_settings.saveStringSetting(INI_FILE, "General", "FontName", ui->lblFontName->text() );
    m_settings.saveStringSetting(INI_FILE, "General", "FontSize", ui->lblFontSize->text() );
    m_settings.saveStringSetting(INI_FILE, "General", "IconColorSchema", ui->cboButtonColor->currentText() );

    m_settings.saveBoolSetting(INI_FILE, "General", "Httpd", ui->swHttpEnabled->isChecked() );

    /* FTP Server settings */
    m_settings.saveBoolSetting(INI_FILE, "Ftp", "enabled", ui->swFtpEnabled->isChecked() );
    m_settings.saveBoolSetting(INI_FILE, "Ftp", "anonymous", ui->chkAnonymous->isChecked() );
    m_settings.saveStringSetting(INI_FILE, "Ftp", "port", ui->edtFTPPort->text() );
    m_settings.saveStringSetting(INI_FILE, "Ftp", "user", ui->edtFTPUser->text() );
    m_settings.saveStringSetting(INI_FILE, "Ftp", "password", ui->edtFTPPassword->text() );

    /* Proxy settings */
    m_settings.saveBoolSetting(INI_FILE, "Proxy", "enabled", ui->swProxy->isChecked() );
    m_settings.saveStringSetting(INI_FILE, "Proxy", "user" , ui->edtProxyUser->text() ) ;
    m_settings.saveStringSetting(INI_FILE, "Proxy", "password" , ui->edtProxyPassword->text() ) ;
    m_settings.saveStringSetting(INI_FILE, "Proxy", "ip" , ui->edtProxyIpAddress->text() ) ;
    m_settings.saveStringSetting(INI_FILE, "Proxy", "port" , ui->edtProxyIpPort->text() ) ;

    /* Dropbox settings */
    m_settings.saveStringSetting("dropbox.ini", "General", "key", ui->edtDropboxKey->text() );
    m_settings.saveStringSetting("dropbox.ini", "General", "secret", ui->edtDropboxSecret->text() );
    m_settings.saveStringSetting("dropbox.ini", "General", "directory", ui->edtDropboxDir->text() );
    m_settings.saveStringSetting("dropbox.ini", "General", "token", ui->edtDropboxToken->text() );

    QMessageBox::information(this, tr("Settings Editor"), "Data successfull saved!");

    loadData(ui->cboSections->currentText());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_cmdDelete_clicked()
{
    QList<QTableWidgetItem*> items = ui->grdValues->selectedItems();

    if ( items.count() == 1 ) {

        QMessageBox msgBox;

        msgBox.setWindowTitle("Settings Editor");
        msgBox.setText("Do you really want to delete the key " + items[0]->text() + "?");

        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int retVal = msgBox.exec();

        if( retVal == QMessageBox::Yes ) {
             m_settings.Delete(ui->cboINIFiles->currentText(), ui->cboSections->currentText(), items[0]->text() ) ;
        }

    } else {
        QMessageBox::information(this, tr("Settings Editor"), "Please select only one key!");
    }

    loadData(ui->cboSections->currentText());
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::loadData(QString section) {

    QStringList values = m_settings.GetAllKeys(ui->cboINIFiles->currentText(), section);

    ui->grdValues->horizontalHeader()->setVisible(false);
    ui->grdValues->verticalHeader()->setVisible(false);
    ui->grdValues->setColumnCount(2);
    ui->grdValues->setRowCount(0);
    ui->grdValues->clear();

    int counter = 0;

    for (int i = 0; i < values.size(); ++i) {

        ui->grdValues->insertRow( counter );

        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText( QString( values.at(i) ) );
        ui->grdValues->setItem( counter, 0, item1 );

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText( m_settings.loadStringSetting(ui->cboINIFiles->currentText(), section, QString( values.at(i) ) )  );
        ui->grdValues->setItem( counter, 1, item2 );

        counter++;
    }

    ui->grdValues->resizeColumnsToContents();
    ui->grdValues->resizeRowsToContents();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::closeEvent(QCloseEvent *event) {

     emit finished();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_radioButton_clicked()
{
    qApp->setStyle(QStyleFactory::create("Windows"));

    qApp->setPalette(this->style()->standardPalette());
    qApp->setStyleSheet(styleSheet());

    m_settings.saveStringSetting(INI_FILE, "General", "Stylesheet", "Windows");
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_radioButton_2_clicked()
{
    qApp->setStyle(QStyleFactory::create("WindowsXP"));

    qApp->setPalette(this->style()->standardPalette());
    qApp->setStyleSheet(styleSheet());

    m_settings.saveStringSetting(INI_FILE, "General", "Stylesheet", "WindowsXP");
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_radioButton_3_clicked()
{
    qApp->setStyle(QStyleFactory::create("WindowsVista"));

    qApp->setPalette(this->style()->standardPalette());
    qApp->setStyleSheet(styleSheet());

    m_settings.saveStringSetting(INI_FILE, "General", "Stylesheet", "WindowsVista");
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_radioButton_4_clicked()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));

    qApp->setPalette(this->style()->standardPalette());
    qApp->setStyleSheet(styleSheet());

    m_settings.saveStringSetting(INI_FILE, "General", "Stylesheet", "Fusion");
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_radioButton_5_clicked()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));

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
    qApp->setPalette(palette);

    m_settings.saveStringSetting(INI_FILE, "General", "Stylesheet", "FusionBlack");
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_radioButton_6_clicked()
{
    qApp->setStyle(new BronzeStyle);

    m_settings.saveStringSetting(INI_FILE, "General", "Stylesheet", "Bronze");
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_radioButton_7_clicked()
{
    qApp->setStyle(new NorwegianWoodStyle);

    m_settings.saveStringSetting(INI_FILE, "General", "Stylesheet", "NorwegianWood");
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_cboQssFiles_currentTextChanged(const QString &arg1)
{
    m_settings.saveStringSetting(INI_FILE, "General", "QssFile", arg1);

    if ( ! arg1.trimmed().isEmpty() ) {

        qDebug() << "setQssFile" << arg1;

        QFile file( arg1 );
        file.open( QFile::ReadOnly );

        qApp->setStyleSheet( file.readAll() );

    } else {

        qApp->setStyleSheet( styleSheet() );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::printOutput()
{
    QByteArray byteArray = m_proc->readAllStandardOutput();

    m_stdOutLines.clear();
    m_stdOutLines = QString(byteArray).split("\n");

    foreach (QString line, m_stdOutLines){
       qDebug() << "-E-" << line;
      // ui->edtOutput->append( line );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::printError()
{
    QByteArray byteArray = m_proc->readAllStandardError();

    m_stdErrLines.clear();
    m_stdErrLines = QString(byteArray).split("\n");

    foreach (QString line, m_stdErrLines){
       qDebug() << "-E-" << line;
       //ui->edtOutput->append( line );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool QSettingsDialog::ExecuteProgram(QString program, QStringList arguments, bool wait) {

    bool retVal = true;
    QString errorLine;
    QString infotxt;

    m_proc = new QProcess;

    connect (m_proc, SIGNAL(readyReadStandardOutput()), this, SLOT(printOutput()));
    connect (m_proc, SIGNAL(readyReadStandardError()), this, SLOT(printError()));

    qDebug() << "start..." << QDir::toNativeSeparators(program) << arguments;

    QString value = m_settings.loadStringSetting(INI_FILE, "Executables", program);
    if ( value.isEmpty() ) {

        QString exeFile = QFileDialog::getOpenFileName(this, tr("ExecuteProgram: exe not found! ..." ) + program, QDir::homePath()  );

        m_settings.saveStringSetting(INI_FILE, "Executables", program, exeFile);

        program = exeFile;

    } else {

        QFileInfo fi( QDir::toNativeSeparators(value) );

        if ( ! fi.exists() ) {

            m_settings.Delete(INI_FILE, "Executables", program);

            value = QFileDialog::getOpenFileName(this, tr("ExecuteProgram: exe not found! ..." ) + program, QDir::homePath()  );

            m_settings.saveStringSetting(INI_FILE, "Executables", program, value);

            program = value;

        } else {

            program = value;
        }
    }

    QFileInfo fi( QDir::toNativeSeparators(program) );

    m_proc->setWorkingDirectory(fi.absolutePath());
    m_proc->setProcessChannelMode(QProcess::MergedChannels);

    if ( arguments.isEmpty() ) {
        m_proc->start("\"" + QDir::toNativeSeparators(program) + "\"");
    } else {
        m_proc->start("\"" + QDir::toNativeSeparators(program) + "\"", arguments);
    }

    if (wait) {

        while ( m_proc->state() == QProcess::Running ) {

            QCoreApplication::processEvents();

            QThread::msleep(100);
        } ;

        if ( true ) {

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
            retVal = false;
        }
    }

    return(retVal);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_cmdQssEdit_clicked()
{
    QString program = "QssEditor.exe";
    QStringList arguments;

    if ( ! ui->cboQssFiles->currentText().trimmed().isEmpty() ) {

        arguments << ui->cboQssFiles->currentText();

        this->ExecuteProgram(program, arguments, false);
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_radioButton_8_clicked()
{
    m_settings.saveStringSetting(INI_FILE, "General", "Stylesheet", "none");
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_cmdFontSelect_clicked()
{
    bool ok;

    QFont font = QFontDialog::getFont(&ok, QFont(ui->lblFontName->text(), ui->lblFontSize->text().toInt()), this);

    if (ok) {

        ui->lblFontName->setText( font.family() ) ;
        ui->lblFontSize->setText( QString ( "%1" ).arg( font.pointSize() ) ) ;
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void QSettingsDialog::on_cboINIFiles_currentTextChanged(const QString &arg1)
{
    ui->cboSections->clear();
    ui->cboSections->addItems( m_settings.getAllSection( arg1 ) );
}
