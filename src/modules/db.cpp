#include "db.h"

db::db()
{
}

bool db::open_sqlite(QString db) {

    bool retval = false;

    qDebug() << "-I- open database...";

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    // m_db.setDatabaseName("tosec.db3");
    m_db.setDatabaseName(db);

    if ( !m_db.open() ) {
        qDebug() << "-E- unable to open database!";
    } else {

        qDebug() << "-I- open database successfull...";

        qDebug() << "-I- prepare database...";

        /* Datenbank initialisieren */
        QString sql = "CREATE TABLE IF NOT EXISTS files ("
                      "ID        INTEGER  PRIMARY KEY   AUTOINCREMENT,"
                      "CRC       TEXT                   NOT NULL,"
                      "SYSTEM    TEXT                   NOT NULL,"
                      "SETNAME   TEXT                   NOT NULL,"
                      "TITLE     TEXT                   NOT NULL,"
                      "NAME      TEXT                   NOT NULL,"
                      "SIZE      INT                    NOT NULL DEFAULT 0,"
                      "MD5       TEXT                   NOT NULL,"
                      "SHA1      TEXT                   NOT NULL,"
                      "PATH      TEXT                   NOT NULL,"
                      "EMUL      TEXT                   NOT NULL,"
                      "EATTR     TEXT                   NOT NULL,"
                      "FAVORITE  INT                    NOT NULL DEFAULT 0,"
                      "RATEING   INT                    NOT NULL DEFAULT 0,"
                      "ROMSET    TEXT                   NOT NULL,"
                      "GAMEBASE  INT                    NOT NULL DEFAULT 0,"
                      "NONTOSEC  INT                    NOT NULL DEFAULT 0,"
                      "RANKING   INT                    NOT NULL DEFAULT 0,"
                      "MULTIROM  INT                    NOT NULL DEFAULT 0,"
                      "VARIANTS  TEXT                   NOT NULL,"
                      "ROMSTATE  INT                    NOT NULL DEFAULT 0,"
                      "ROMSETPUP TEXT                   NOT NULL,"
                      "GENDATE   DATETIME               NOT NULL DEFAULT 0,"
                      "MODDATE   DATETIME               NOT NULL DEFAULT 0"
                      ");";

        QSqlQuery query;

        if ( ! query.exec(sql) ) {

            qDebug() << query.lastError();

        } else {

            qDebug() << "-I- checking database indexes...";

            m_db.exec("CREATE UNIQUE INDEX IF NOT EXISTS index_system_sha1_name_title ON files (SYSTEM, SETNAME, TITLE, NAME, SHA1);");

            m_db.exec("CREATE INDEX IF NOT EXISTS index_sha1 ON files (SHA1);");
            m_db.exec("CREATE INDEX IF NOT EXISTS index_crc ON files (CRC);");
            m_db.exec("CREATE INDEX IF NOT EXISTS index_romset ON files (ROMSET);");
            m_db.exec("CREATE INDEX IF NOT EXISTS index_system ON files (SYSTEM);");
            m_db.exec("CREATE INDEX IF NOT EXISTS index_system_path ON files (SYSTEM, PATH);");
            m_db.exec("CREATE INDEX IF NOT EXISTS index_system_title ON files (SYSTEM, TITLE);");
            m_db.exec("CREATE INDEX IF NOT EXISTS index_setname ON files (SETNAME);");
            m_db.exec("CREATE INDEX IF NOT EXISTS index_system_setname ON files (SYSTEM, SETNAME);");

            //m_db.exec("ALTER TABLE FILES ADD COLUMN ROMSETPUP TEXT NOT NULL DEFAULT ' ';");

           // m_db.exec("PRAGMA auto_vacuum = FULL");
            m_db.exec("PRAGMA synchronous = OFF");
            m_db.exec("PRAGMA journal_mode = MEMORY");

            retval = true;
        }
    }

    qDebug() << "-I- open database finished...";

    return(retval);
}


bool db::open_mysql(QString db, QString user, QString pwd) {

    bool retval = false;

    QSqlDatabase m_db = QSqlDatabase::addDatabase("QMYSQL3");
    m_db.setDatabaseName(db);
    m_db.setUserName(user);
    m_db.setPassword(pwd);

    if ( !m_db.open() ) {
        qDebug() << "-E- unable to open database!";
    } else {

        /* Datenbank initialisieren */
        QString sql = "CREATE TABLE IF NOT EXISTS files ("
                      "ID        INT                NOT NULL AUTO_INCREMENT ,"
                      "CRC       VARCHAR(20)        NOT NULL,"
                      "SYSTEM    VARCHAR(128)       NOT NULL,"
                      "SETNAME   VARCHAR(128)       NOT NULL,"
                      "TITLE     VARCHAR(128)       NOT NULL,"
                      "NAME      VARCHAR(128)       NOT NULL,"
                      "SIZE      INT                NOT NULL DEFAULT 0,"
                      "MD5       VARCHAR(50)        NOT NULL,"
                      "SHA1      VARCHAR(50)        NOT NULL,"
                      "PATH      VARCHAR(512)       NOT NULL,"
                      "EMUL      VARCHAR(128)       NOT NULL,"
                      "EATTR     VARCHAR(128)       NOT NULL,"
                      "FAVORITE  INT                NOT NULL DEFAULT 0,"
                      "RATEING   INT                NOT NULL DEFAULT 0,"
                      "ROMSET    VARCHAR(512)       NOT NULL,"
                      "GAMEBASE  INT                NOT NULL DEFAULT 0,"
                      "NONTOSEC  INT                NOT NULL DEFAULT 0,"
                      "RANKING   INT                NOT NULL DEFAULT 0,"
                      "MULTIROM  INT                NOT NULL DEFAULT 0,"
                      "VARIANTS  INT                NOT NULL DEFAULT 0,"
                      "ROMSTATE  INT                NOT NULL DEFAULT 0,"
                      "GENDATE   DATETIME           NOT NULL DEFAULT 0,"
                      "MODDATE   DATETIME           NOT NULL DEFAULT 0,"
                      "PRIMARY KEY (`ID`)"
                      ") ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;";

        QSqlQuery query;

        if ( ! query.exec(sql) ) {

            qDebug() << query.lastError();

        } else {

            m_db.exec("CREATE UNIQUE INDEX index_system_sha1_name_title ON files (SYSTEM, TITLE, NAME, SHA1);");

            m_db.exec("CREATE INDEX index_sha1 ON files (SHA1);");
            m_db.exec("CREATE INDEX index_crc ON files (CRC);");
            m_db.exec("CREATE INDEX index_romset ON files (ROMSET);");
            m_db.exec("CREATE INDEX index_system ON files (SYSTEM);");
            m_db.exec("CREATE INDEX index_system_path ON files (SYSTEM, PATH);");
            m_db.exec("CREATE INDEX index_system_title ON files (SYSTEM, TITLE);");
            m_db.exec("CREATE INDEX index_setname ON files (SETNAME);");
            m_db.exec("CREATE INDEX index_system_setname ON files (SYSTEM, SETNAME);");

            retval = true;
        }
    }

    return(retval);
}

void db::close() {

    if ( m_db.isOpen() ) {
        m_db.open();
    }
}

int db::storeFilesData(QVariantList values) {

    QSqlQuery q;

    QString title   = values.at(3).toString();
    QString name    = values.at(4).toString();
    QString sha1    = values.at(7).toString();
    QString system  = values.at(1).toString();
    QString setname = values.at(2).toString();
    QString md5     = values.at(6).toString();

    QList<rom_type> roms;
    rom_type        rom;

    int             retCode = -1;

    // Step 1: Gibt es schon ein Rom mit dem Key?
    roms = this->selectRomDataByKey(system, setname, title, name, sha1);

    if ( roms.count() == 0 ) { // ROM nicht gefunden...

        q.prepare("INSERT INTO files VALUES (NULL,:CRC,:SYSTEM,:SETNAME,:TITLE,:NAME,:SIZE,:MD5,:SHA1,:PATH,:EMUL,:EATTR,:FAVORITE,:RATEING,:ROMSET,:GAMEBASE,:NONTOSEC,:RANKING,:MULTIROM,:VARIANTS,:ROMSTATE,CURRENT_TIMESTAMP,CURRENT_TIMESTAMP,:ROMSETPUP);");
        q.bindValue(":CRC", values.at(0));
        q.bindValue(":SYSTEM", values.at(1));
        q.bindValue(":SETNAME", values.at(2));
        q.bindValue(":TITLE", values.at(3));
        q.bindValue(":NAME", values.at(4));
        q.bindValue(":SIZE", values.at(5).toInt());
        q.bindValue(":MD5", md5);
        q.bindValue(":SHA1", sha1);
        q.bindValue(":PATH", "missing");
        q.bindValue(":EMUL", " ");
        q.bindValue(":EATTR", " ");
        q.bindValue(":FAVORITE", 0);
        q.bindValue(":RATEING", 0);
        q.bindValue(":ROMSET", " ");
        q.bindValue(":GAMEBASE", 0);
        q.bindValue(":NONTOSEC", values.at(8));
        q.bindValue(":RANKING", 0);
        q.bindValue(":MULTIROM", 0);
        q.bindValue(":VARIANTS", " ");
        q.bindValue(":ROMSTATE", db::NEW);
        q.bindValue(":ROMSETPUP", values.at(9));

        if ( ! q.exec() ) {            
            qDebug() << "storeFilesData" << "step 1" << title << name << sha1 << q.lastError();
        } else {
            retCode = q.lastInsertId().toInt();
        }
    } else if ( roms.count() == 1 ) { // eindeutiges ROM gefunden...

        rom = roms.first();

        q.prepare("UPDATE files SET ROMSTATE=:ROMSTATE, MODDATE=CURRENT_TIMESTAMP WHERE ID=:ID;");

        q.bindValue(":ROMSTATE",  db::UPDATED);
        q.bindValue(":ID", rom.ID);

        if ( ! q.exec() ) {
            qDebug() << "storeFilesData" << "step 2" << system << title << name << sha1 << q.lastError();
        } else {
            retCode = rom.ID;
            //qDebug() << "-UPDATE- ROM" << "step 2" << system << title << rom.TITLE << name << rom.NAME << q.numRowsAffected() << rom.ID;
        }

    } else {
        qDebug() << "Multirom found... doing nothing..." << sha1 ;
        exit(0);
    }

    return(retCode);
}

bool db::updateUserRanking(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET ROMSET=:ROMSET, FAVORITE=:FAVORITE, RATEING=:RATEING, RANKING=:RANKING, MODDATE=CURRENT_TIMESTAMP WHERE SHA1=:SHA1;");
    q.bindValue(":SHA1", values.at(0));
    q.bindValue(":ROMSET", values.at(1));
    q.bindValue(":FAVORITE", values.at(2));
    q.bindValue(":RATEING", values.at(3));
    q.bindValue(":RANKING", values.at(4));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateRomPath(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET PATH=:PATH, MODDATE=CURRENT_TIMESTAMP WHERE SHA1=:SHA1;");
    q.bindValue(":PATH", values.at(0));
    q.bindValue(":SHA1", values.at(1));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateRomPathById(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET PATH=:PATH, MODDATE=CURRENT_TIMESTAMP WHERE ID=:ID;");
    q.bindValue(":PATH", values.at(0));
    q.bindValue(":ID", values.at(1));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateRomMultirom(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET MULTIROM=:MULTIROM, ROMSET=:ROMSET, MODDATE=CURRENT_TIMESTAMP WHERE SYSTEM=:SYSTEM AND TITLE=:TITLE;");
    q.bindValue(":MULTIROM", values.at(0));
    q.bindValue(":SYSTEM", values.at(1));
    q.bindValue(":TITLE", values.at(2));
    q.bindValue(":ROMSET", values.at(3));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateEmul(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET EMUL=:EMUL, MODDATE=CURRENT_TIMESTAMP WHERE SETNAME=:SETNAME;");
    q.bindValue(":EMUL", values.at(0));
    q.bindValue(":SETNAME", values.at(1));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateEmulAttr(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET TITLE=:TITLE, NAME=:NAME, NONTOSEC=:NONTOSEC, EATTR=:EATTR, FAVORITE=:FAVORITE, RATEING=:RATEING, EMUL=:EMUL, RANKING=:RANKING, VARIANTS=:VARIANTS, MODDATE=CURRENT_TIMESTAMP WHERE ID=:ID;");
    q.bindValue(":ID", values.at(0));
    q.bindValue(":EATTR", values.at(1));
    q.bindValue(":FAVORITE", values.at(2));
    q.bindValue(":RATEING", values.at(3));
    q.bindValue(":EMUL", values.at(4));
    q.bindValue(":NONTOSEC", values.at(5));
    q.bindValue(":RANKING", values.at(6));
    q.bindValue(":VARIANTS", values.at(7));
    q.bindValue(":TITLE", values.at(8));
    q.bindValue(":NAME", values.at(9));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateRomSet(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    qDebug() << values;

    q.prepare("UPDATE files SET ROMSET=:ROMSET, MODDATE=CURRENT_TIMESTAMP WHERE ID=:ID;");
    q.bindValue(":ROMSET", values.at(0));
    q.bindValue(":ID", values.at(1));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::releaseRomSet(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    qDebug() << values;

    q.prepare("UPDATE files SET ROMSET=' ', MODDATE=CURRENT_TIMESTAMP WHERE ROMSET=:ROMSET;");
    q.bindValue(":ROMSET", values.at(0));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateFavorite(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET FAVORITE = NOT FAVORITE, MODDATE=CURRENT_TIMESTAMP WHERE ID=:ID;");
    q.bindValue(":ID", values.at(0));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateRating(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    qDebug() << "updateRating" << values;

    q.prepare("UPDATE files SET RATEING=:RATEING, MODDATE=CURRENT_TIMESTAMP WHERE ID=:ID;");
    q.bindValue(":RATEING", values.at(0));
    q.bindValue(":ID", values.at(1));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::deleteSetData(QVariantList values) {

    QSqlQuery q;
    bool      deleteDone = false;

    q.prepare("DELETE FROM files WHERE SETNAME=:SETNAME;");
    q.bindValue(":SETNAME", values.at(0));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        deleteDone = q.numRowsAffected() > 0;
    }

    return(deleteDone);
}

bool db::deleteFilesData() {

    QSqlQuery q;
    bool      deleteDone = false;

    q.prepare("DELETE FROM files;");

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        deleteDone = q.numRowsAffected() > 0;
    }

    return(deleteDone);
}

QStringList db::getSystemNames() {

    QSqlQuery q;
    QStringList systems;

    q.prepare("SELECT DISTINCT system FROM files ORDER BY system ASC");

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            systems << q.value(0).toString();
        }
    }

    return (systems);
}

QList<QStringList> db::getSystemOverview() {

    m_timer.start();

    QSqlQuery q;
    QList<QStringList> systems;
    QStringList values ;

    q.prepare("select system,"
              " (select count(*) from files where system = A.system) as 'Total',"
              " (select count(*) from files where PATH <> 'missing' and system = A.system) as 'Valid'"
              " from files A"
              " group by A.system ORDER BY 1 ASC");

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            values.clear();
            values << q.value(0).toString() << q.value(1).toString() << q.value(2).toString();

            systems << values ;
        }
    }

    qDebug() << "db::getSystemOverview" << m_timer.elapsed();

    return (systems);
}

QList<QStringList> db::getSetNamesOverview(QVariantList system) {

    m_timer.start();

    QSqlQuery q;
    QList<QStringList> systems;
    QStringList values;

    q.prepare("SELECT SETNAME, "
              " (select count(*) from files where SETNAME = A.SETNAME) as 'Total',"
              " (select count(*) from files where PATH <> 'missing' and SETNAME = A.SETNAME) as 'Valid'"
              " FROM files A WHERE (SYSTEM=:SYSTEM) "
              " group by SETNAME ORDER BY 1 ASC");
    q.bindValue(":SYSTEM", system.at(0));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            values.clear();
            values << q.value(0).toString() << q.value(1).toString() << q.value(2).toString();

            systems << values ;
        }
    }

    qDebug() << "db::getSetNamesOverview" << m_timer.elapsed();

    return (systems);
}

QList<QString> db::getSetNames(QVariantList values) {

    QSqlQuery q;
    QList<QString> systems;

    if ( values.at(1).toBool() ) { // alles laden
        q.prepare("SELECT DISTINCT SETNAME FROM files WHERE (SYSTEM=:SYSTEM) AND ROMSTATE > 0 ORDER BY 1 ASC;");
        q.bindValue(":SYSTEM", values.at(0));
    } else { // nur Sets laden, wenn valide Roms enthalten sind
        q.prepare("SELECT DISTINCT SETNAME FROM files WHERE (SYSTEM=:SYSTEM) AND ROMSTATE > 0 AND PATH <> 'missing' ORDER BY 1 ASC;");
        q.bindValue(":SYSTEM", values.at(0));
    }

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            systems << q.value(0).toString();
        }
    }

    return (systems);
}

QList<rom_type> db::getSoftwareNames(QString system, QString setname, int mode, QString search, int Gamebase) {

    qDebug() << "getSoftwareNames" << system << setname << mode << search << Gamebase;

    QSqlQuery q;
    QList<rom_type> roms;
    rom_type rom;

    switch (mode){
    case 1:
        q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM AND SETNAME=:SETNAME AND GAMEBASE=:GAMEBASE AND TITLE LIKE :TITLE AND SUBSTR(TITLE, 1, 1) BETWEEN '0' and '9' ORDER BY TITLE;");
        break;
    case 2:
        q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM AND SETNAME=:SETNAME AND GAMEBASE=:GAMEBASE AND TITLE LIKE :TITLE AND SUBSTR(TITLE, 1, 1) BETWEEN 'A' and 'I' ORDER BY TITLE;");
        break;
    case 3:
        q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM AND SETNAME=:SETNAME AND GAMEBASE=:GAMEBASE AND TITLE LIKE :TITLE AND SUBSTR(TITLE, 1, 1) BETWEEN 'J' and 'R' ORDER BY TITLE;");
        break;
    case 4:
        q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM AND SETNAME=:SETNAME AND GAMEBASE=:GAMEBASE AND TITLE LIKE :TITLE AND SUBSTR(TITLE, 1, 1) BETWEEN 'S' and 'Z' ORDER BY TITLE;");
        break;
    case 5:
        q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM AND SETNAME=:SETNAME AND GAMEBASE=:GAMEBASE AND TITLE LIKE :TITLE AND FAVORITE <> 0 ORDER BY RANKING;");
        break;
    case 6:
        q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM AND GAMEBASE=:GAMEBASE AND TITLE LIKE :TITLE ORDER BY TITLE;");
        break;
    case 7:
        q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM;");
        break;
    case 8:
        q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM AND SETNAME=:SETNAME AND RANKING > 0;");
        break;
    case 9:
        q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM AND SETNAME=:SETNAME ORDER BY TITLE;");
        break;
    default:
        q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM AND (GAMEBASE=:GAMEBASE OR :GAMEBASE=0) AND SETNAME=:SETNAME AND TITLE LIKE :TITLE ORDER BY TITLE;");
    }

    q.bindValue(":SYSTEM", system);
    q.bindValue(":SETNAME", setname);
    q.bindValue(":TITLE", search);
    q.bindValue(":GAMEBASE", Gamebase);

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            rom.ID = q.value("ID").toInt();
            rom.CRC = q.value("CRC").toString();
            rom.SYSTEM = q.value("SYSTEM").toString();
            rom.SETNAME = q.value("SETNAME").toString();
            rom.TITLE = q.value("TITLE").toString();
            rom.NAME = q.value("NAME").toString();
            rom.SIZE = q.value("SIZE").toInt();
            rom.MD5 = q.value("MD5").toString();
            rom.SHA = q.value("SHA1").toString();
            rom.PATH = q.value("PATH").toString();
            rom.EMUL = q.value("EMUL").toString();
            rom.EATTR = q.value("EATTR").toString();
            rom.FAVORIT = q.value("FAVORITE").toInt();
            rom.RATEING = q.value("RATEING").toInt();
            rom.ROMSET = q.value("ROMSET").toString();
            rom.GAMEBASE = q.value("GAMEBASE").toInt();
            rom.NONTOSEC = q.value("NONTOSEC").toInt();
            rom.RANKING = q.value("RANKING").toInt();
            rom.MULTIROM = q.value("MULTIROM").toInt();
            rom.VARIANTS = q.value("VARIANTS").toString();
            rom.MODDATE = q.value("MODDATE").toString();
            rom.GENDATE = q.value("GENDATE").toString();

            roms << rom;
        }
    }

    qDebug() << "db::getSoftwareNames" << m_timer.elapsed();

    return (roms);
}

bool db::selectRomData(int id, rom_type &rom) {

    QSqlQuery q;
    bool found = false;

    q.prepare("SELECT * FROM files WHERE ID=:ID;");
    q.bindValue(":ID", id);

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            rom.ID = q.value("ID").toInt();
            rom.CRC = q.value("CRC").toString();
            rom.SYSTEM = q.value("SYSTEM").toString();
            rom.SETNAME = q.value("SETNAME").toString();
            rom.TITLE = q.value("TITLE").toString();
            rom.NAME = q.value("NAME").toString();
            rom.SIZE = q.value("SIZE").toInt();
            rom.MD5 = q.value("MD5").toString();
            rom.SHA = q.value("SHA1").toString();
            rom.PATH = q.value("PATH").toString();
            rom.EMUL = q.value("EMUL").toString();
            rom.EATTR = q.value("EATTR").toString();
            rom.FAVORIT = q.value("FAVORITE").toInt();
            rom.RATEING = q.value("RATEING").toInt();
            rom.ROMSET = q.value("ROMSET").toString();
            rom.GAMEBASE = q.value("GAMEBASE").toInt();
            rom.NONTOSEC = q.value("NONTOSEC").toInt();
            rom.RANKING = q.value("RANKING").toInt();
            rom.MULTIROM = q.value("MULTIROM").toInt();
            rom.VARIANTS = q.value("VARIANTS").toString();
            rom.MODDATE = q.value("MODDATE").toString();
            rom.GENDATE = q.value("GENDATE").toString();

            found = true;
        }
    }

    return(found);
}

QStringList db::selectMultiRoms(QString system, QString setname, QString title) {

    QSqlQuery   q;
    QStringList values;

    q.prepare("SELECT id FROM files WHERE SYSTEM=:SYSTEM AND SETNAME=:SETNAME AND TITLE=:TITLE;");
    q.bindValue(":SYSTEM", system);
    q.bindValue(":SETNAME", setname);
    q.bindValue(":TITLE", title);

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        values.clear();

        while (q.next()) {

            values.append( q.value("ID").toString() );
        }
    }

    return(values);
}

QList<rom_type> db::selectRomDataBySha1(QString system, QString sha1) {

    QSqlQuery q;

    rom_type rom;
    QList<rom_type> roms;

    q.prepare("SELECT * FROM files WHERE SHA1=:SHA1 AND (SYSTEM=:SYSTEM OR :SYSTEM = '');");
    q.bindValue(":SYSTEM", system);
    q.bindValue(":SHA1", sha1);

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            rom.ID = q.value("ID").toInt();
            rom.CRC = q.value("CRC").toString();
            rom.SYSTEM = q.value("SYSTEM").toString();
            rom.SETNAME = q.value("SETNAME").toString();
            rom.TITLE = q.value("TITLE").toString();
            rom.NAME = q.value("NAME").toString();
            rom.SIZE = q.value("SIZE").toInt();
            rom.MD5 = q.value("MD5").toString();
            rom.SHA = q.value("SHA1").toString();
            rom.PATH = q.value("PATH").toString();
            rom.EMUL = q.value("EMUL").toString();
            rom.EATTR = q.value("EATTR").toString();
            rom.FAVORIT = q.value("FAVORITE").toInt();
            rom.RATEING = q.value("RATEING").toInt();
            rom.ROMSET = q.value("ROMSET").toString();
            rom.GAMEBASE = q.value("GAMEBASE").toInt();
            rom.NONTOSEC = q.value("NONTOSEC").toInt();
            rom.RANKING = q.value("RANKING").toInt();
            rom.MULTIROM = q.value("MULTIROM").toInt();
            rom.VARIANTS = q.value("VARIANTS").toString();
            rom.MODDATE = q.value("MODDATE").toString();
            rom.GENDATE = q.value("GENDATE").toString();

            roms.append( rom );
        }
    }

    return(roms);
}

QList<rom_type> db::selectRomDataByKey(QString system, QString setname, QString title, QString name, QString sha1) {

    QSqlQuery q;
    rom_type rom;
    QList<rom_type> roms;

    q.prepare("SELECT * FROM files WHERE SYSTEM=:SYSTEM AND SETNAME=:SETNAME AND TITLE=:TITLE AND NAME=:NAME AND SHA1=:SHA1;");
    q.bindValue(":SHA1", sha1);
    q.bindValue(":TITLE", title);
    q.bindValue(":NAME", name);
    q.bindValue(":SYSTEM", system);
    q.bindValue(":SETNAME", setname);

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            rom.ID = q.value("ID").toInt();
            rom.CRC = q.value("CRC").toString();
            rom.SYSTEM = q.value("SYSTEM").toString();
            rom.SETNAME = q.value("SETNAME").toString();
            rom.TITLE = q.value("TITLE").toString();
            rom.NAME = q.value("NAME").toString();
            rom.SIZE = q.value("SIZE").toInt();
            rom.MD5 = q.value("MD5").toString();
            rom.SHA = q.value("SHA1").toString();
            rom.PATH = q.value("PATH").toString();
            rom.EMUL = q.value("EMUL").toString();
            rom.EATTR = q.value("EATTR").toString();
            rom.FAVORIT = q.value("FAVORITE").toInt();
            rom.RATEING = q.value("RATEING").toInt();
            rom.ROMSET = q.value("ROMSET").toString();
            rom.GAMEBASE = q.value("GAMEBASE").toInt();
            rom.NONTOSEC = q.value("NONTOSEC").toInt();
            rom.RANKING = q.value("RANKING").toInt();
            rom.MULTIROM = q.value("MULTIROM").toInt();
            rom.VARIANTS = q.value("VARIANTS").toString();
            rom.MODDATE = q.value("MODDATE").toString();
            rom.GENDATE = q.value("GENDATE").toString();

            roms.append( rom );
        }
    }

    return(roms);
}


QList<QString> db::getInfoValues(QVariantList values) {

    QSqlQuery q;
    QList<QString> infos;

    q.prepare("SELECT COUNT(*) FROM files WHERE SETNAME=:SETNAME");
    q.bindValue(":SETNAME", values.at(0));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            infos << q.value(0).toString();
        }
    }

    q.prepare("SELECT COUNT(*) FROM files WHERE SETNAME=:SETNAME AND PATH = 'missing'");
    q.bindValue(":SETNAME", values.at(0));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            infos << q.value(0).toString();
        }
    }

    return (infos);
}


bool db::updateRomStorage(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET PATH = replace( PATH, :OLD, :NEW ), MODDATE=CURRENT_TIMESTAMP;");
    q.bindValue(":OLD", values.at(0));
    q.bindValue(":NEW", values.at(1));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateGamebaseFlag(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET GAMEBASE=:GAMEBASE, MODDATE=CURRENT_TIMESTAMP WHERE CRC=:CRC;");
    q.bindValue(":CRC", values.at(0));
    q.bindValue(":GAMEBASE", values.at(1));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateObsoleteFlag(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET OBSOLETE=:OBSOLETE, MODDATE=CURRENT_TIMESTAMP WHERE CRC=:CRC;");
    q.bindValue(":CRC", values.at(0));
    q.bindValue(":OBSOLETE", values.at(1));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateVariants(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = false;

    q.prepare("UPDATE files SET VARIANTS=:VARIANTS, MODDATE=CURRENT_TIMESTAMP WHERE ID=:ID;");
    q.bindValue(":ID", values.at(0));
    q.bindValue(":VARIANTS", values.at(1));

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        updateDone = q.numRowsAffected() > 0;
    }

    return(updateDone);
}

bool db::updateRomStateToObsolete(QVariantList values) {

    QSqlQuery q;
    bool      updateDone = true;

    q.prepare("UPDATE files SET ROMSTATE = (:ROMSTATE), MODDATE = CURRENT_TIMESTAMP WHERE SYSTEM = (:SYSTEM) AND SETNAME = (:SETNAME)");
    q.bindValue(":ROMSTATE", db::OBSOLETE );
    q.bindValue(":SYSTEM", values.at(0).toString());
    q.bindValue(":SETNAME", values.at(1).toString());

    if ( ! q.exec() ) {
        qDebug() << q.lastError().text();
        updateDone = false;
    }

    return(updateDone);
}

QList<QString> db::selectCorrectAbleSha1Roms() {

    QSqlQuery q;
    QList<QString> infos;

    q.prepare("select distinct sha1 from files x where romstate <> 0 and exists (select * from files where romstate = 0 and path <> 'missing' and sha1 = x.sha1)");

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            infos <<  q.value(0).toString();
        }
    }

    return(infos);
}

QList<rom_type> db::selectObsoleteRomsBySha1(QString sha1) {

    QSqlQuery q;
    rom_type rom;
    QList<rom_type> roms;

    q.prepare("select * from files where SHA1=:SHA1 and ROMSTATE=0 and PATH<>'missing'");
    q.bindValue(":SHA1", sha1);

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            rom.ID = q.value("ID").toInt();
            rom.CRC = q.value("CRC").toString();
            rom.SYSTEM = q.value("SYSTEM").toString();
            rom.SETNAME = q.value("SETNAME").toString();
            rom.TITLE = q.value("TITLE").toString();
            rom.NAME = q.value("NAME").toString();
            rom.SIZE = q.value("SIZE").toInt();
            rom.MD5 = q.value("MD5").toString();
            rom.SHA = q.value("SHA1").toString();
            rom.PATH = q.value("PATH").toString();
            rom.EMUL = q.value("EMUL").toString();
            rom.EATTR = q.value("EATTR").toString();
            rom.FAVORIT = q.value("FAVORITE").toInt();
            rom.RATEING = q.value("RATEING").toInt();
            rom.ROMSET = q.value("ROMSET").toString();
            rom.GAMEBASE = q.value("GAMEBASE").toInt();
            rom.NONTOSEC = q.value("NONTOSEC").toInt();
            rom.RANKING = q.value("RANKING").toInt();
            rom.MULTIROM = q.value("MULTIROM").toInt();
            rom.VARIANTS = q.value("VARIANTS").toString();
            rom.MODDATE = q.value("MODDATE").toString();
            rom.GENDATE = q.value("GENDATE").toString();

            roms.append( rom );
        }
    }

    return(roms);
}


QList<rom_type> db::selectAvaialableRomsBySha1(QString sha1) {

    QSqlQuery q;
    rom_type rom;
    QList<rom_type> roms;

    q.prepare("select * from files where SHA1=:SHA1 and ROMSTATE<>0");
    q.bindValue(":SHA1", sha1);

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {

        while (q.next()) {

            rom.ID = q.value("ID").toInt();
            rom.CRC = q.value("CRC").toString();
            rom.SYSTEM = q.value("SYSTEM").toString();
            rom.SETNAME = q.value("SETNAME").toString();
            rom.TITLE = q.value("TITLE").toString();
            rom.NAME = q.value("NAME").toString();
            rom.SIZE = q.value("SIZE").toInt();
            rom.MD5 = q.value("MD5").toString();
            rom.SHA = q.value("SHA1").toString();
            rom.PATH = q.value("PATH").toString();
            rom.EMUL = q.value("EMUL").toString();
            rom.EATTR = q.value("EATTR").toString();
            rom.FAVORIT = q.value("FAVORITE").toInt();
            rom.RATEING = q.value("RATEING").toInt();
            rom.ROMSET = q.value("ROMSET").toString();
            rom.GAMEBASE = q.value("GAMEBASE").toInt();
            rom.NONTOSEC = q.value("NONTOSEC").toInt();
            rom.RANKING = q.value("RANKING").toInt();
            rom.MULTIROM = q.value("MULTIROM").toInt();
            rom.VARIANTS = q.value("VARIANTS").toString();
            rom.MODDATE = q.value("MODDATE").toString();
            rom.GENDATE = q.value("GENDATE").toString();

            roms.append( rom );
        }
    }

    return(roms);
}

bool db::deleteRomById(int ID) {

    QSqlQuery q;
    bool      deleteDone = false;

    qDebug() << "deleteRomById" << ID;

    q.prepare("DELETE FROM files WHERE ID=:ID;");
    q.bindValue(":ID", ID);

    if ( ! q.exec() ) {
        qDebug() << q.lastError();
    } else {
        deleteDone = q.numRowsAffected() > 0;
    }

    return(deleteDone);
}
