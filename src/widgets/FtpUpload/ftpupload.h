#ifndef FTPUPLOAD_H
#define FTPUPLOAD_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QUrl>
#include <QDebug>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QInputDialog>
#include <QProgressDialog>

#include "src/modules/settings.h"
#include "src/modules/qftp.h"

#include "3dparty/wwWidgets/widgets/qwwled/qwwled.h"

namespace Ui {
class FtpUpload;
}

class FtpUpload : public QDialog
{
    Q_OBJECT

public:
    explicit FtpUpload(QWidget *parent = nullptr);
    ~FtpUpload();

    void setFileName(QString);
    void fillComboFtpServer();

private slots:    
    void commandFinished(int commandId, bool error);
    void updateDataTransferProgress(qint64 bytesSent, qint64 bytesTotal);
    void commandStarted(int commandId);
    void done(bool);
    void cancelDownload();
    void addToList(const QUrlInfo &urlInfo);
    void processItem(QTreeWidgetItem *item, int /*column*/);
    void setCurrentItem(QTreeWidgetItem *item, int /*column*/);

    void on_selectFileButton_clicked();    
    void on_pushButton_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_cmdSave_clicked();
    void on_cmdDelete_clicked();

    void on_cmdConnect_clicked();

    void on_cmdParent_clicked();

    void on_cmdMkdir_clicked();

    void on_cmdRemove_clicked();

    void on_cmdUpload_clicked();

    void on_cmdDownload_clicked();

private:

    QString currentPath;
    QHash<QString, bool> isDirectory;

    Ui::FtpUpload   *ui;

    QString          m_fileName;
    QFile           *m_file;
    settings         m_settings;
    QProgressDialog *m_progressDialog;
    QFtp            *m_ftp;

    QTreeWidgetItem *m_item;
};

#endif // FTPUPLOAD_H
