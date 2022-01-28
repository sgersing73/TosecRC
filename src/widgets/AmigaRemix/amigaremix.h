#ifndef AMIGAREMIX_H
#define AMIGAREMIX_H

#include <QGroupBox>
#include <QDebug>

namespace Ui {
class AmigaRemix;
}

class AmigaRemix : public QGroupBox
{
    Q_OBJECT

public:
    explicit AmigaRemix(QWidget *parent = nullptr);
    ~AmigaRemix();

    void setSliMinValue(int);
    void setSliMaxValue(int);
    void setBaseUrl(QString);
    void setUrl(QString);
    void setSortByDateUrl(QString);
    void setSortByRatingUrl(QString);
    void setFileExt(QString);

signals:
    void sliderChanged( QString, QString, QString );

private slots:
    void on_horizontalScrollBar_valueChanged(int value);
    void on_horizontalScrollBar_sliderMoved(int position);
    void on_cmdSortByDate_clicked();
    void on_cmdSortByRating_clicked();

private:
    Ui::AmigaRemix *ui;

    int     _sliMinValue;
    int     _sliMaxValue;
    QString _baseUrl;
    QString _url;
    QString _extension;
    QString _sortByDateUrl;
    QString _sortByRatingUrl;
};

#endif // AMIGAREMIX_H
