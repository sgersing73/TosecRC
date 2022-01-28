#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

class FileDownloader : public QObject
{
    Q_OBJECT

public:
    explicit FileDownloader (QUrl imageUrl, QObject *parent = 0);

    virtual ~FileDownloader ();

    QByteArray downloadedData() const;

    void SetFileName(QString);
    QString getFileName();

signals:
    void downloaded();

private slots:

    void fileDownloaded(QNetworkReply* pReply);

private:

   QNetworkAccessManager m_WebCtrl;
   QByteArray            m_DownloadedData;
   QString               m_FileName;
};

#endif // FILEDOWNLOADER_H
