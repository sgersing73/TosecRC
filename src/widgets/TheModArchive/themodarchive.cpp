#include "themodarchive.h"
#include "ui_themodarchive.h"

TheModArchive::TheModArchive(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::TheModArchive)
{
    ui->setupUi(this);

    emit sliderChanged(QString(_url).arg( 1 ), _baseUrl, _extension );
}

TheModArchive::~TheModArchive()
{
    delete ui;
}

void TheModArchive::setSliMinValue(int value) {

    _sliMinValue = value;
}

void TheModArchive::setSliMaxValue(int value) {

    _sliMaxValue = value;
}

void TheModArchive::setBaseUrl(QString baseUrl) {

    _baseUrl = baseUrl;
}

void TheModArchive::setUrl(QString url) {

    _url = url;
}

void TheModArchive::setSortByDateUrl(QString url) {

    _sortByDateUrl = url;
}

void TheModArchive::setSortByRatingUrl(QString url) {

    _sortByRatingUrl = url;
}

void TheModArchive::setFileExt(QString extension) {

    _extension = extension;
}

void TheModArchive::on_horizontalScrollBar_valueChanged(int value)
{
    emit sliderChanged(QString(_url).arg( value ), _baseUrl, _extension );

    ui->lblPage->setText("Page: " + QString("%1").arg(value));
}

void TheModArchive::on_horizontalScrollBar_sliderMoved(int position)
{
    emit sliderChanged(QString(_url).arg( position ), _baseUrl, _extension );

    ui->lblPage->setText("Page: " + QString("%1").arg(position));
}

void TheModArchive::on_cmdSortByDate_clicked()
{
    emit sliderChanged(QString(_sortByDateUrl), _baseUrl, _extension );
}

void TheModArchive::on_cmdSortByRating_clicked()
{
    emit sliderChanged(QString(_sortByRatingUrl), _baseUrl, _extension );
}
