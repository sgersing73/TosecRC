#include "systemeditor.h"
#include "ui_systemeditor.h"

SystemEditor::SystemEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemEditor)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->comboBox->addItems(QStringList() << "Menue" << "Toolbar" << "Both" << "Hidden");
}

SystemEditor::~SystemEditor()
{
    delete ui;
}

void SystemEditor::on_cmdExit_clicked()
{   
    this->mSettings.saveStringSetting("system.ini", mSystemName, "kind", ui->comboBox->currentText());
    this->mSettings.saveStringSetting("system.ini", mSystemName, "exe", ui->edtExe->text());

    this->mSettings.saveStringSetting("system.ini", mSystemName, "para", ui->edtExeParam->text());

    this->mSettings.saveStringSetting("system.ini", mSystemName, "logo", ui->edtLogo->text());
    this->mSettings.saveStringSetting("system.ini", mSystemName, "url", ui->edtWiki->text());
    this->mSettings.saveStringSetting("system.ini", mSystemName, "pic", ui->edtThumb->text());
    this->mSettings.saveStringSetting("system.ini", mSystemName, "pcb", ui->edtPCB->text());
    this->mSettings.saveStringSetting("system.ini", mSystemName, "portrait", ui->edtPortrait->text());

    this->mSettings.saveStringSetting("system.ini", mSystemName, "youtube", ui->edtYoutube->text());

    emit this->finished();

    this->close();
}

void SystemEditor::on_cmdCancel_clicked()
{
    this->close();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void SystemEditor::setSystemName(QString systemName) {

    mSystemName = systemName;

    setWindowTitle(tr("System INI Editor") + " - " + mSystemName);

    ui->comboBox->setCurrentText(this->mSettings.loadStringSetting("system.ini", mSystemName, "kind"));

    ui->edtExe->setText(this->mSettings.loadStringSetting("system.ini", mSystemName, "exe"));
    ui->edtExeParam->setText(this->mSettings.loadStringSetting("system.ini", mSystemName, "para"));

    ui->edtLogo->setText(this->mSettings.loadStringSetting("system.ini", mSystemName, "logo"));
    ui->edtWiki->setText(this->mSettings.loadStringSetting("system.ini", mSystemName, "url"));
    ui->edtThumb->setText(this->mSettings.loadStringSetting("system.ini", mSystemName, "pic"));
    ui->edtPCB->setText(this->mSettings.loadStringSetting("system.ini", mSystemName, "pcb"));
    ui->edtPortrait->setText(this->mSettings.loadStringSetting("system.ini", mSystemName, "portrait"));

    ui->edtYoutube->setText(this->mSettings.loadStringSetting("system.ini", mSystemName, "youtube"));
}
