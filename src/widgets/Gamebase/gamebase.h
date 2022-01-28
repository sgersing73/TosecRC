#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <QGroupBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QFileInfo>
#include <QDir>
#include <QSettings>
#include <QProgressDialog>

#ifdef _WIN32
#include "quazip/JlCompress.h"
#else
#include "quazip5/JlCompress.h"
#endif

#include "src/modules/crc32.h"
#include "src/modules/settings.h"
#include "src/modules/db.h"

struct gamebase_type {
    QString Games_name;
    QString Games_NoOfPlayers;
    QString Games_picture;
    QString Games_sid;
    QString Games_WebLink_URL;
    QString Artists_Artist;
    QString Crackers_Cracker;
    QString Genres_Genre;
    QString Years_Year;
    QString Musicians_Musician;
    QString Languages_Language;
    QString Programmers_Programmer;
    QString Licenses_License;
    QString Rarities_Rarity;
    QString Publishers_Publisher;
    QString Developers_Developer;
}  ;

namespace Ui {
class Gamebase;
}

class Gamebase : public QGroupBox
{
    Q_OBJECT

public:
    explicit Gamebase(QWidget *parent = 0);
    ~Gamebase();

    void CrcPrepareDb(QString, QString, QString, db);
    void loadGameData(QString, QString);
    void setInfoExt(QString);
    void disable();

    gamebase_type GetGameBaseInfos(QString, QString);

signals:
    void setWebView(QString);

private:
    Ui::Gamebase *ui;

    settings     _settings;
};

#endif // GAMEBASE_H
