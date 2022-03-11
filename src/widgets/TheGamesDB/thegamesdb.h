#ifndef THEGAMESDB_H
#define THEGAMESDB_H

#include <QtGlobal>
#include <QDialog>
#include <QtNetwork>

#include <QListWidgetItem>
#include <QStatusBar>
#include <QCloseEvent>
#include "QJsonDocument"

#include "src/modules/xml.h"
#include "src/modules/tools.h"

namespace Ui {
class TheGamesDB;
}

class TheGamesDB : public QDialog
{
    Q_OBJECT

protected:
     void closeEvent(QCloseEvent *event);

public:
    explicit TheGamesDB(QWidget *parent = 0, QString = "", QString = "", QString = "", QString = "");
    ~TheGamesDB();

    void initControls();

    void loadDBGameListFile();
    void loadDBGameFile();    
    void loadDBPlatformFile();
    void loadDBScreenshotListFile();
    void loadDBCoversListFile();

    void getPlatformList();
    void getScreenshotList();
    void getCoverList();

    void getReleaseDate(QByteArray);
    void getPlayers(QByteArray);
    void getTags(QByteArray);
    void getAges(QByteArray);
    void getPublisher(QByteArray);
    void getDeveloper(QByteArray);
    void getDescription(QByteArray);
    void getRating(QByteArray);
    void getTitle(QByteArray);
    void getPlatform(QByteArray);
    void getScreenshot(QByteArray);
    void getBoxart(QByteArray);
    void getGameid(QByteArray);
    void getPlatformId(QByteArray);

public slots:
    void replyFinished (QNetworkReply *reply);

private slots:
    void on_cmdSearch_clicked();
    void on_lisGamesList_itemDoubleClicked(QListWidgetItem *item);
    void on_cmdCreateStuffPack_clicked();
    void on_cmdScreenshots_clicked();
    void on_cmdBoxart_clicked();

private:
    Ui::TheGamesDB        *ui;

    QNetworkAccessManager *manager;

    QString               m_FileName;
    thegamesdb_type       m_thegamesdb;
    tools                 m_tools;

    QString               m_TempPath;
    QString               m_caption;

    QJsonDocument         jsonDoc;
    QJsonObject           jsonObj;

    QListWidgetItem       *m_Item;

    QString               m_actGame_id;
    QString               m_actPlatform_id;
    QString               m_MobiApiKey;
};

#endif // THEGAMESDB_H
