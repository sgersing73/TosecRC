#ifndef AUDIOSPECTRUM_H
#define AUDIOSPECTRUM_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QMenu>
#include <QColorDialog>

#include "audiosampler.h"

class AudioSpectrum : public QWidget
{
    Q_OBJECT
public:
    explicit AudioSpectrum(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

private slots:
    void redrawTimerExpired();
    void ShowContextMenu(const QPoint&);

private:
    AudioSampler *m_AudioSampler;
    QTimer       *m_redrawTimer;
    float         m_peakHoldLevel[8];

    QColor        m_BarColor;
};

#endif // AUDIOSPECTRUM_H
