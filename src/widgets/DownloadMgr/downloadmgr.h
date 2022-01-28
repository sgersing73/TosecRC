#ifndef DOWNLOADMGR_H
#define DOWNLOADMGR_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QProcess>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QSettings>
#include <QtWidgets>

#include "src/modules/settings.h"
#include "src/modules/tools.h"

namespace Ui {
class DownloadMgr;
}

class DownloadMgr : public QMainWindow
{
    Q_OBJECT

public:
    explicit DownloadMgr(QWidget *parent = nullptr);
    ~DownloadMgr();

    void writeQueueentries();
    void readQueueentries();
    void tailLogfile();

private:
    void closeEvent(QCloseEvent *event) ;

private slots:
    void printOutput();
    void printError();
    void processStarted();
    void encodingFinished();
    void closeDownloadMgr();
    void MyTimerSlot();

    void on_cmdDownload_clicked();
    void on_cmdAdd_clicked();
    void on_cmdLoadList_clicked();
    void on_cmdSaveList_clicked();
    void on_cmdDelEntry_clicked();
    void on_toolButton_clicked();

    void on_cmdCancelDownload_clicked();
    void on_cmdClearList_clicked();

    void on_lisDownload_itemDoubleClicked(QListWidgetItem *item);

    void on_chkHideOutput_clicked();

private:
    Ui::DownloadMgr *ui;
    QProcess        *mTranscodingProcess;
    QTimer          *timer;
    QString         m_OutputString;

    bool            m_DownloadActive;
    QString         m_sSettingsFile;

    QString         m_queueFile;
    QString         m_TempPath;

    settings        m_settings;
    tools           m_tools;

};

#endif // DOWNLOADMGR_H
