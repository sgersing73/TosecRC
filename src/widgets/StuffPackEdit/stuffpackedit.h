#ifndef STUFFPACKEDIT_H
#define STUFFPACKEDIT_H

#include <QDialog>
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>
#include <QTableWidgetItem>
#include <QList>

#include "src/modules/settings.h"

namespace Ui {
class StuffPackEdit;
}

class StuffPackEdit : public QDialog
{
    Q_OBJECT

public:
    explicit StuffPackEdit(QWidget *parent = nullptr);
    ~StuffPackEdit();

    void setStuffPackIniFile(QString);
    void setDialogCaption(QString);

protected:
    void dropEvent(QDropEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);

private slots:
    void on_cmdExit_clicked();
    void on_cmdCancel_clicked();

    void on_cmdCoverRemove_clicked();
    void on_cmdCoverAdd_clicked();

    void on_cmdMediaRemove_clicked();
    void on_cmdMediaAdd_clicked();

    void on_cmdScreenshotRemove_clicked();
    void on_cmdScreenshotAdd_clicked();

    void on_cmdSoundtrackRemove_clicked();
    void on_cmdSoundtrackAdd_clicked();

    void on_cmdLinksRemove_clicked();
    void on_cmdLinksAdd_clicked();

private:
    Ui::StuffPackEdit   *ui;

    settings            _settings;
};

#endif // STUFFPACKEDIT_H
