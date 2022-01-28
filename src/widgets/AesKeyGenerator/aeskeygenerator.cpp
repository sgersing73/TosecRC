#include "aeskeygenerator.h"
#include "ui_aeskeygenerator.h"

AesKeyGenerator::AesKeyGenerator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AesKeyGenerator)
{
    ui->setupUi(this);

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
