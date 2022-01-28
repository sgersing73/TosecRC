#ifndef VALUEBAR_H
#define VALUEBAR_H

#include <QWidget>
#include <QGroupBox>
#include <QDebug>
#include <QTimer>
#include <QStorageInfo>
#include <QLabel>
#include <QLayout>

#ifdef _WIN32
#include <qwt_thermo.h>
#else
#include <qwt/qwt_thermo.h>
#endif

class ValueBar: public QWidget
{    
    Q_OBJECT

public:
    ValueBar( Qt::Orientation orientation, const QString &text, QWidget *parent, double maxValue = 100 );

    void setValue( double value );

    void setColor( QColor color );
    void setCaption( QString text );
    void setFontSize( int size );

private:
    QLabel    *d_label;
    QwtThermo *d_thermo;
};

#endif // VALUEBAR_H
