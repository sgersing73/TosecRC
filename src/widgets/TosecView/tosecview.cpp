#include "tosecview.h"
#include "ui_tosecview.h"

TosecView::TosecView(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::TosecView)
{
    ui->setupUi(this);

    tosecLayout = new QHBoxLayout( this );
    tosecLayout->setMargin( 15 );
    tosecLayout->setSpacing( 5 );

    ValueBarTosec = new ValueBar( Qt::Horizontal, "Hallo", this, 100 );
    ValueBarTosec->setFontSize(6);

    tosecLayout->addWidget( ValueBarTosec );
}

TosecView::~TosecView()
{
    delete ui;
}

void TosecView::setText(QString text) {

   ValueBarTosec->setCaption( text );
}

void TosecView::setValue(double value) {

   ValueBarTosec->setValue(value);
}
