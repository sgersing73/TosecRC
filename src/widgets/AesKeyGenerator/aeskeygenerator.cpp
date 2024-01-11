#include "aeskeygenerator.h"
#include "ui_aeskeygenerator.h"

AesKeyGenerator::AesKeyGenerator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AesKeyGenerator)
{
    ui->setupUi(this);

    m_sSettingsFile = INI_FILE;

    ui->textEdit->clear();
}

AesKeyGenerator::~AesKeyGenerator()
{
    delete ui;
}

void AesKeyGenerator::on_cmdGenerate_clicked()
{
    tools myTools;
    int soZe = 0;

    if ( ui->chkSoZe->checkState() == Qt::Checked ) {
        soZe = 1;
    }

    char password[132] = {'\0'};
    int retCode =  myTools.GeneratePassword(ui->spinBox->value(), soZe, password) ;

    if ( retCode == 0 ) {
        ui->textEdit->setText( password );
    } else {
        ui->textEdit->setText( QString("Fehler-Code bei der Code-Generierung: %1").arg(retCode) );
    }

}

void AesKeyGenerator::on_cmdSetAsKey_clicked()
{

    QString AesKey = m_settings.loadStringSetting(m_sSettingsFile, "AES", "key");
    QString AesTool = m_settings.loadStringSetting(m_sSettingsFile, "AES", "tool");

    if ( AesKey.isEmpty() ) {

        m_settings.saveStringSetting( m_sSettingsFile, "AES", "key", ui->textEdit->toPlainText() );

        QMessageBox::information(this, this->windowTitle(), tr("AES Key set to\n\n%1").arg(ui->textEdit->toPlainText()) );

    } else {

        QMessageBox::warning(this, this->windowTitle(), tr("AES Key !!!NOT!!! set - already configured!!!") );
    }

    if ( AesTool.isEmpty() ) {

        QString exeFile = QFileDialog::getOpenFileName(this, tr("Program File: %1 not found! ..." ).arg("aescrypt"), QDir::homePath()  );

        m_settings.saveStringSetting(m_sSettingsFile, "AES", "tool", exeFile);

        QMessageBox::information(this, this->windowTitle(), tr("AES Tool set to %1").arg(exeFile) );
    }
}

