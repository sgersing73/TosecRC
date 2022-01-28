#ifndef SCROLLTEXT_H
#define SCROLLTEXT_H

#include <QWidget>
#include <QStaticText>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QPainter>

class ScrollText : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString separator READ separator WRITE setSeparator)

public:
    explicit ScrollText(QWidget *parent = nullptr);

public slots:
    QString text() const;
    void setText(QString text);

    QString separator() const;
    void setSeparator(QString separator);

    void replyFinished (QNetworkReply *reply);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);

private:
    void updateText();
    QString _text;
    QString _separator;
    QStaticText staticText;
    int singleTextWidth;
    QSize wholeTextSize;
    int leftMargin;
    bool scrollEnabled;
    int scrollPos;
    QImage alphaChannel;
    QImage buffer;
    QTimer timer;

    QStringList newsList;
    QStringList linkList;

private slots:
    virtual void timer_timeout();

private:
   QNetworkAccessManager *manager;

   void doDownload();

public:

   QStringList getLinkList();
};

#endif // SCROLLTEXT_H
