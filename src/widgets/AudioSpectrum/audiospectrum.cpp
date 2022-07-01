#include "audiospectrum.h"

AudioSpectrum::AudioSpectrum(QWidget *parent) : QWidget(parent), m_redrawTimer(new QTimer(this))
{
#ifdef linux
    m_BarColor = Qt::white;

    m_AudioSampler = new AudioSampler();
    m_AudioSampler->Open(nullptr);		// NULL = default device (runtime-changeable in pavucontrol app)

    this->setMinimumHeight(40);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));

    connect(m_redrawTimer, SIGNAL(timeout()), this, SLOT(redrawTimerExpired()));
    m_redrawTimer->start(1);
#endif
}

void AudioSpectrum::ShowContextMenu(const QPoint& pos) // this is a slot
{
#ifdef linux
    // for most widgets
    QPoint globalPos = this->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    QMenu myMenu;
    myMenu.addAction("set color");
    // ...

    QAction* selectedItem = myMenu.exec(globalPos);

    if ( ! selectedItem ) {
        return;
    }

    if ( selectedItem->text().contains("set color") ) {

        m_BarColor = QColorDialog::getColor(m_BarColor, this);
    }
#endif
}

void AudioSpectrum::redrawTimerExpired()
{
#ifdef linux
    static int counter = 0;

    m_AudioSampler->Update();

    if ( counter % 100 ) {

        this->m_AudioSampler->Analyze();

        update();
    }

    counter++;
#endif
}

void AudioSpectrum::paintEvent(QPaintEvent *event)
{
#ifdef linux
    Q_UNUSED(event)

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    const int numBars = 8;

    QColor clipColor(255, 255, 0);

    // Draw the outline
    const QColor gridColor = m_BarColor.darker();
    QPen gridPen(gridColor);
    painter.setPen(gridPen);
    painter.drawLine(rect().topLeft(), rect().topRight());
    painter.drawLine(rect().topRight(), rect().bottomRight());
    painter.drawLine(rect().bottomRight(), rect().bottomLeft());
    painter.drawLine(rect().bottomLeft(), rect().topLeft());

    QVector<qreal> dashes;
    dashes << 2 << 2;
    gridPen.setDashPattern(dashes);
    painter.setPen(gridPen);

    // Draw vertical lines between bars
    if (numBars) {
        const int numHorizontalSections = numBars;
        QLine line(rect().topLeft(), rect().bottomLeft());
        for (int i=1; i<numHorizontalSections; ++i) {
            line.translate(rect().width()/numHorizontalSections, 0);
            painter.drawLine(line);
        }
    }

    // Draw horizontal lines
    const int numVerticalSections = 10;
    QLine line(rect().topLeft(), rect().topRight());
    for (int i=1; i<numVerticalSections; ++i) {
        line.translate(0, rect().height()/numVerticalSections);
        painter.drawLine(line);
    }

    QColor barColor = m_BarColor.lighter();
    barColor.setAlphaF(0.75);
    clipColor.setAlphaF(0.75);

    // Draw the bars
    if (numBars) {
        // Calculate width of bars and gaps
        const int widgetWidth = rect().width();
        const int barPlusGapWidth = widgetWidth / numBars;
        const int barWidth = 0.8 * barPlusGapWidth;
        const int gapWidth = barPlusGapWidth - barWidth;
        const int paddingWidth = widgetWidth - numBars * (barWidth + gapWidth);
        const int leftPaddingWidth = (paddingWidth + gapWidth) / 2;
        const int barHeight = rect().height() - 2 * gapWidth;

        for (int i=0; i<numBars; i++) {

            const qreal value = m_AudioSampler->GetMagnitudeArray()[i];

            if (value>0) {

                QRect bar = rect();
                bar.setLeft(rect().left() + leftPaddingWidth + (i * (gapWidth + barWidth)));
                bar.setWidth(barWidth);
                bar.setTop(rect().top() + gapWidth + ( 1.0 - value) * barHeight );
                bar.setBottom(rect().bottom() - gapWidth);

                QColor color = barColor;

                painter.fillRect(bar, color);

            }

        }
    }
#endif
}
