#ifndef XML_H
#define XML_H

#include <QFile>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>
#include <QElapsedTimer>

#include "db.h"
//#include "checktime.h"

struct thegamesdb_type {
    QString Description;
    QString baseImgUrl;
    QString Platform;
    QStringList id;
    QString GameTitle;
    QString ReleaseDate;
    QString Overview;
    QStringList genre;
    QString Players;
    QString Youtube;
    QString Publisher;
    QString Developer;
    QString Rating;
    QString original;
    QStringList thumb;
    QStringList boxart;
    QStringList media;
    QStringList banner;
    QString tags;
    QString clearlogo;
    QString ages;    
}  ;

struct thegamesdbgamelist_type {
    QString id;
    QString GameTitle;
    QString ReleaseDate;
    QString Platform;
    QString Platform_id;
    QString url;
    QString miscData;
}  ;

struct thegamesdbplatformlist_type {
    QString id;
    QString Name;
    QString Alias;
}  ;

class xml
{
public:
    xml();

    int readXMLDatFile(QString, QString);
    QString getNameFromTosecDatFile(QString fileName);
    thegamesdb_type readXMLTheGamesDBFile(QString);
    QList<thegamesdbgamelist_type>     readXMLTheGamesDBGameListFile(QString);
    QList<thegamesdbplatformlist_type> readXMLTheGamesDBPlatformListFile(QString);

private:

    db  m_db;
};

#endif // XML_H
