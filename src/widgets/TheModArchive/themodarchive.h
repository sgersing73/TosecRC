#ifndef THEMODARCHIVE_H
#define THEMODARCHIVE_H

#include <QGroupBox>

namespace Ui {
class TheModArchive;
}

class TheModArchive : public QGroupBox
{
    Q_OBJECT

public:
    explicit TheModArchive(QWidget *parent = 0);
    ~TheModArchive();

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
    Ui::TheModArchive *ui;

    int     _sliMinValue;
    int     _sliMaxValue;
    QString _baseUrl;
    QString _url;
    QString _extension;
    QString _sortByDateUrl;
    QString _sortByRatingUrl;
};

#endif // THEMODARCHIVE_H
