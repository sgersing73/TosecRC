#include "valuebar.h"

ValueBar::ValueBar( Qt::Orientation orientation,
              const QString &text, QWidget *parent, double maxValue ):
        QWidget( parent )
{
    d_label = new QLabel(this);
    d_label->setText( text );

    d_thermo = new QwtThermo(this);
    d_thermo->setOrientation( orientation );
    d_thermo->setScale( 0.0, maxValue );
    d_thermo->setPipeWidth( 6 );
    d_thermo->setScaleMaxMajor( 6 );
    d_thermo->setScaleMaxMinor( 5 );
    d_thermo->setFillBrush( Qt::darkGreen );

    QVBoxLayout *layout = new QVBoxLayout( this );
    layout->setMargin( 0 );
    layout->setSpacing( 0 );

    if ( orientation == Qt::Horizontal )
    {
        d_label->setAlignment( Qt::AlignCenter );
        d_thermo->setScalePosition( QwtThermo::LeadingScale );
        layout->addWidget( d_label );
        layout->addWidget( d_thermo );
    }
    else
    {
        d_label->setAlignment( Qt::AlignRight );
        d_thermo->setScalePosition( QwtThermo::TrailingScale );
        layout->addWidget( d_thermo, 10, Qt::AlignHCenter );
        layout->addWidget( d_label, 0 );
    }
}

void ValueBar::setValue( double value )
{
    d_thermo->setValue( value );
}

void ValueBar::setColor( QColor color )
{
    d_thermo->setFillBrush( color );
}

void ValueBar::setCaption( QString text )
{
    d_label->setText( text );
}

void ValueBar::setFontSize( int size )
{
    QFont font = d_label->font();
    font.setPointSize(size);

    d_label->setFont(font);
    d_thermo->setFont(font);
}
