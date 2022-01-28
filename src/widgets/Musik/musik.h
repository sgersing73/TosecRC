#ifndef MUSIK_H
#define MUSIK_H

#include "config.h"

#include <QGroupBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QListWidgetItem>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

#include "src/widgets/EquilizerDialog/EqualizerDialog.h"

#include "src/modules/htmlpageloader.h"
#include "src/modules/settings.h"
#include "src/modules/filedownloader.h"

namespace Ui {
class Musik;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class EqualizerDialog;

class Musik : public QGroupBox
{
    Q_OBJECT

    settings            m_settings;

public:
    explicit Musik(QWidget *parent = nullptr);
    ~Musik();

    void disable();
    void ExecuteProgram(QString, QString);
    QString getMediaPlayer(QString);
    void playVideoFile(QString url) ;

public slots:
    void stopPlayer();
    void playFile();
    void loadData();
    void on_cmdPlay_clicked();
    void on_cmdStop_clicked();
    void on_listTracks_itemDoubleClicked(QListWidgetItem *);
    void on_listTracks_itemClicked(QListWidgetItem *);

    void setFileExtension(QStringList);

    void setURL(QString, QString, QString);
    void setPlayerTitle(QString);
    void setFilePath(QString);
    bool isPlaying();

    void readyReadStandardOutput();
    void processStarted();
    void encodingFinished();

    void playerEnd();

private slots:

    void on_cmdPrev_clicked();
    void on_cmdNext_clicked();
    void on_cmdPause_clicked();
    void on_cmdSave_clicked();

    void saveFile();

private:
    Ui::Musik       *ui;

    QListWidgetItem *_item;

    VlcInstance     *_instance;
    VlcMedia        *_media;
    VlcMediaPlayer  *_player;

    EqualizerDialog *_equalizerDialog;
    HtmlPageLoader  *_htmlpageloader;
    QProcess        *_process;
    FileDownloader  *m_pImgCtrl;

    QStringList     _extensions;
    settings        _settings;
    QString         m_fileName;

    bool            m_isLocalFile;
    bool            m_playing;
};

#endif // MUSIK_H
