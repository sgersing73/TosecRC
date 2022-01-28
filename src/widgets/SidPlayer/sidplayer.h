#ifndef SIDPLAYER_H
#define SIDPLAYER_H

#include <QMainWindow>
#include <QGroupBox>
#include <QDebug>
#include <QString>
#include <QProcess>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QSettings>

#include "config.h"
#include "src/modules/settings.h"

namespace Ui {
class SidPlayer;
}

class SidPlayer : public QGroupBox
{
    Q_OBJECT

public:
    explicit SidPlayer(QWidget *parent = 0);
    ~SidPlayer();

    void startPlayer();

private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_cmdHVSC_clicked();
    void on_cmdProjectAY_clicked();

    void on_pushButton_clicked();

signals:
    void directoryChanged(QString);
    void setFileExtension(QStringList);
    void setWebView(QString);

private:
    Ui::SidPlayer     *ui;

    QFileSystemModel  *_dirModel;
    QFileSystemModel  *_fileModel;
    QString            _FileName;
    settings           _settings;
};

#endif // SIDPLAYER_H
