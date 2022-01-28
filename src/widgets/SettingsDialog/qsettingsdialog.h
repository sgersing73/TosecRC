#ifndef QSETTINGSDIALOG_H
#define QSETTINGSDIALOG_H

#include <QDialog>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QFileDialog>
#include <QStyleFactory>
#include <QThread>
#include <QFontDialog>

#include "config.h"

#include "src/modules/settings.h"
#include "src/modules/norwegianwoodstyle.h"
#include "src/modules/bronzestyle.h"


namespace Ui {
class QSettingsDialog;
}

class QSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QSettingsDialog(QWidget *parent = 0);
    ~QSettingsDialog();

    void loadData(QString);
    void initCboQssFile(QString);

protected:
     void closeEvent(QCloseEvent *event);

signals:
    void finished();

private slots:

    void on_cboSections_currentTextChanged(const QString &arg1);
    void on_cboQssFiles_currentTextChanged(const QString &arg1);

    void printOutput();
    void printError();

    void on_cmdAddLine_clicked();
    void on_cmdCancel_clicked();
    void on_cmdOK_clicked();
    void on_cmdDelete_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();
    void on_radioButton_6_clicked();
    void on_radioButton_7_clicked();
    void on_cmdQssEdit_clicked();
    void on_radioButton_8_clicked();
    void on_cmdFontSelect_clicked();

    void on_cboINIFiles_currentTextChanged(const QString &arg1);

private:
    Ui::QSettingsDialog *ui;

    settings             m_settings;
    QProcess            *m_proc;
    QStringList          m_stdErrLines;
    QStringList          m_stdOutLines;

    bool ExecuteProgram(QString, QStringList, bool);
};

#endif // QSETTINGSDIALOG_H
