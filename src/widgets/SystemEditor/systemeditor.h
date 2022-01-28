#ifndef SYSTEMEDITOR_H
#define SYSTEMEDITOR_H

#include <QDialog>

#include "src/modules/settings.h"

namespace Ui {
class SystemEditor;
}

class SystemEditor : public QDialog
{
    Q_OBJECT

public:
    explicit SystemEditor(QWidget *parent = 0);
    ~SystemEditor();

    void setSystemName(QString);

private slots:
    void on_cmdExit_clicked();
    void on_cmdCancel_clicked();

signals:
    void finished();

private:
    Ui::SystemEditor *ui;

    settings         mSettings;
    QString          mSystemName;
};

#endif // SYSTEMEDITOR_H
