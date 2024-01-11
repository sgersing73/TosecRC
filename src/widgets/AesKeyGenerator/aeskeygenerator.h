#ifndef AESKEYGENERATOR_H
#define AESKEYGENERATOR_H

#include "config.h"

#include <QDialog>
#include <QSettings>
#include <QFileDialog>

#include "src/modules/tools.h"
#include "src/modules/settings.h"

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
    void on_cmdSetAsKey_clicked();

private:
    Ui::AesKeyGenerator *ui;

    QString   m_sSettingsFile ;
    settings  m_settings;
};

#endif // AESKEYGENERATOR_H
