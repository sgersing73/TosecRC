#ifndef TOSECVIEW_H
#define TOSECVIEW_H

#include "src/modules/valuebar.h"

namespace Ui {
class TosecView;
}

class TosecView : public QGroupBox
{
    Q_OBJECT

public:
    explicit TosecView(QWidget *parent = nullptr);
    ~TosecView();

    void setText(QString);
    void setValue(double);

private:
    Ui::TosecView *ui;

    QHBoxLayout     *tosecLayout;
    ValueBar        *ValueBarTosec;

};

#endif // TOSECVIEW_H
