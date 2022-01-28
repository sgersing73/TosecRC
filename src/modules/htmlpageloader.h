#ifndef HTMLPAGELOADER_H
#define HTMLPAGELOADER_H

#include <QObject>
#include <QFileInfo>
#include <QtWebKitWidgets/QtWebKitWidgets>
#include <QtWebKit/QtWebKit>

struct tag_type {
    QString Title;
    QString Path;
}  ;

class HtmlPageLoader : public QObject
{
    Q_OBJECT
public:
    explicit HtmlPageLoader(QObject *parent = 0);
    void loadPage(const QUrl&, QString, QString);
    QList<tag_type> getData();

public slots:
    void replyFinished(bool);

signals:
    void dataReady();

private:
    QWebView         *m_view;
    QList<tag_type>  m_fileList;
    QString          m_extensions;
    QString          m_baseUrl;
    QWebElementCollection elements;
};

#endif // HTMLPAGELOADER_H
