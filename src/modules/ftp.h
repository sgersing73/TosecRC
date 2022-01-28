#ifndef FTP_H
#define FTP_H

#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

class Uploader: public QObject
{
    Q_OBJECT
    public:
        Uploader(QObject *p = 0): QObject(p) { }

        void start(const QString &file) {
            QUrl url("ftp://my.server.com:2121/new.jpg");
            url.setUserName("Username");
            url.setPassword("Pa$sw0rd");
            url.setScheme("ftp");

            data = new QFile(file, this);
            if (data->open(QIODevice::ReadOnly)) {
                reply = nam.put(QNetworkRequest(url), data);
                connect(reply, SIGNAL(uploadProgress(qint64, qint64)), SLOT(uploadProgress(qint64, qint64)));
                connect(reply, SIGNAL(finished()), SLOT(uploadDone()));
            }
            else
                qDebug() << "Oops";
            }

        public slots:
            void uploadProgress(qint64 bytesSent, qint64 bytesTotal) {
                qDebug() << "Uploaded" << bytesSent << "of" << bytesTotal;
            }

            void uploadDone() {
                qDebug() << "Finished" << reply->error();
                data->deleteLater();
                reply->deleteLater();
            }

    private:
        QNetworkAccessManager nam;
        QFile *data;
        QNetworkReply *reply;
};

#endif
