#include "htmlpageloader.h"

HtmlPageLoader::HtmlPageLoader(QObject *parent) :
    QObject(parent)
{
    m_view = new QWebView();

    connect(m_view, SIGNAL(loadFinished(bool)), this, SLOT(replyFinished(bool)));
}

void HtmlPageLoader::loadPage(const QUrl& url, QString baseUrl, QString extension)
{
    m_extensions = extension;
    m_baseUrl = baseUrl;

    qDebug() << "loadPage" << m_extensions << url;

    m_view->load(url);
}

QList<tag_type> HtmlPageLoader::getData()
{
    return(m_fileList);
}

void HtmlPageLoader::replyFinished(bool ok)
{
    QString link;

    tag_type tag;

    m_fileList.clear();

    elements = m_view->page()->mainFrame()->findAllElements("a");

    qDebug() << "parsing for extention " << m_extensions;

    QFileInfo info;

    foreach (QWebElement e, elements) {

        QUrl url(e.attribute("href"));

        if ( url.hasFragment() ) {
            info.setFile(url.fragment());
        } else {
            info.setFile(url.fileName());
        }

        QString ext = info.suffix();

        if ( ext.contains( QRegExp( m_extensions ) ) ) {

            qDebug() << url.fileName();

            if ( e.attribute("href").left(1) == "/" ) {
                link = e.attribute("href").remove(0,1);
            } else {
                link = e.attribute("href");
            }

            tag.Title = info.fileName();
            tag.Path  = m_baseUrl + link;

            m_fileList.append(tag);
        }
    }

    emit dataReady();
}
