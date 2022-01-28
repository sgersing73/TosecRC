#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QElapsedTimer>

struct rom_type {
    int     ID;
    QString CRC;
    QString SYSTEM;
    QString SETNAME;
    QString TITLE;
    QString NAME;
    int     SIZE;
    QString MD5;
    QString SHA;
    QString PATH;
    QString EMUL;
    QString EATTR;
    int     FAVORIT;
    int     RATEING;
    QString ROMSET;
    int     GAMEBASE;
    int     NONTOSEC;
    int     RANKING;
    int     MULTIROM;
    QString VARIANTS;
    QString MODDATE;
    QString GENDATE;
    QString ROMSETPUP;
}  ;



class db
{
public:

    db();

    bool open_mysql(QString db, QString user, QString pwd);
    bool open_sqlite(QString db);

    void close();
    int storeFilesData(QVariantList);

    bool updateRomPath(QVariantList);
    bool updateEmul(QVariantList);
    bool updateEmulAttr(QVariantList);
    bool updateFavorite(QVariantList);
    bool updateRomSet(QVariantList);
    bool updateGamebaseFlag(QVariantList);
    bool updateUserRanking(QVariantList);
    bool updateRomMultirom(QVariantList);
    bool updateObsoleteFlag(QVariantList);
    bool updateRating(QVariantList);
    bool updateVariants(QVariantList);

    bool releaseRomSet(QVariantList);

    bool deleteFilesData();
    bool deleteSetData(QVariantList);

    QStringList getSystemNames();
    QList<QStringList> getSystemOverview();
    QList<QStringList> getSetNamesOverview(QVariantList);
    QList<QString> getSetNames(QVariantList);
    QList<rom_type> getSoftwareNames(QString, QString, int, QString, int);
    QList<QString> getInfoValues(QVariantList);
    bool selectRomData(int, rom_type&);
    bool updateRomStorage(QVariantList);
    QList<rom_type> selectRomDataByKey(QString, QString, QString, QString, QString);
    QList<rom_type> selectRomDataBySha1(QString, QString);
    QStringList selectMultiRoms(QString, QString, QString) ;
    bool updateRomStateToObsolete(QVariantList);
    QList<QString> selectCorrectAbleSha1Roms();
    QList<rom_type> selectObsoleteRomsBySha1(QString);
    QList<rom_type> selectAvaialableRomsBySha1(QString);
    bool updateRomPathById(QVariantList);
    bool deleteRomById(int);

    enum ROMSTATE { OBSOLETE = 0, NEW = 1, UPDATED = 2 } ;

private:

    QSqlDatabase  m_db;
    QElapsedTimer m_timer;

};

#endif // DB_H
