#ifndef AESKEYGENERATOR_H
#define AESKEYGENERATOR_H

#include <QDialog>

#include "src/modules/tools.h"

namespace Ui {
class AesKeyGenerator;
}

class AesKeyGenerator : public QDialog
{
    Q_OBJECT

public:
    explicit AesKeyGenerator(QWidget *parent = 0);
    ~AesKeyGenerator();

private slots:
    void on_cmdGenerate_clicked();

private:
    Ui::AesKeyGenerator *ui;
};

#endif // AESKEYGENERATOR_H
