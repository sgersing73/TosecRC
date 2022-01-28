#include "amigaremix.h"
#include "ui_amigaremix.h"

AmigaRemix::AmigaRemix(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::AmigaRemix)
{
    ui->setupUi(this);

    emit sliderChanged(QString(_url).arg( 1 ), _baseUrl, _extension );
}

AmigaRemix::~AmigaRemix()
{
    delete ui;
}

void AmigaRemix::setSliMinValue(int value) {

    _sliMinValue = value;
}

void AmigaRemix::setSliMaxValue(int value) {

    _sliMaxValue = value;
}

void AmigaRemix::setBaseUrl(QString baseUrl) {

    _baseUrl = baseUrl;
}

void AmigaRemix::setUrl(QString url) {

    _url = url;
}

void AmigaRemix::setSortByDateUrl(QString url) {

    _sortByDateUrl = url;
}

void AmigaRemix::setSortByRatingUrl(QString url) {

    _sortByRatingUrl = url;
}

void AmigaRemix::setFileExt(QString extension) {

    _extension = extension;
}

void AmigaRemix::on_horizontalScrollBar_valueChanged(int value)
{
    emit sliderChanged(QString(_url).arg( value ), _baseUrl, _extension );

    ui->lblPage->setText("Page: " + QString("%1").arg(value));
}

void AmigaRemix::on_horizontalScrollBar_sliderMoved(int position)
{
    emit sliderChanged(QString(_url).arg( position ), _baseUrl, _extension );

    ui->lblPage->setText("Page: " + QString("%1").arg(position));
}

void AmigaRemix::on_cmdSortByDate_clicked()
{
    emit sliderChanged(QString(_sortByDateUrl), _baseUrl, _extension );
}

void AmigaRemix::on_cmdSortByRating_clicked()
{
    emit sliderChanged(QString(_sortByRatingUrl), _baseUrl, _extension );
}
