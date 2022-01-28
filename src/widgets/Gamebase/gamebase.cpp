#include "gamebase.h"
#include "ui_gamebase.h"

Gamebase::Gamebase(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::Gamebase)
{
    ui->setupUi(this);
}

Gamebase::~Gamebase()
{
    delete ui;
}

void Gamebase::loadGameData(QString database, QString crc) {

    gamebase_type values;
    QString picturePath;

    if(database.isEmpty()) {
        return;
    }

    QFileInfo fi(database);
    QString iniFile = fi.path() + "/Paths.ini";

    QString value = _settings.loadStringSetting(iniFile, "Pictures", "1");

    if( ! value.isEmpty() )
        picturePath = value ;

    values = GetGameBaseInfos(database, crc) ;

    if (  values.Games_name.trimmed() != "" ) {
        this->setHidden( false );
    } else {
        this->setHidden( true );
    }

    ui->lblCopyright->setText( values.Years_Year + ' ' + values. Publishers_Publisher);
    ui->lblDeveloper->setText ( values.Developers_Developer );
    ui->lblCoding->setText( values.Programmers_Programmer );
    ui->lblGameType->setText( values.Musicians_Musician );
    ui->lblArtist->setText ( values.Artists_Artist ) ;
    ui->lblLicense->setText ( values.Licenses_License ) ;

    ui->lblGenre->setText( values.Genres_Genre );
    ui->lblNoOfPlayers->setText( values.Games_NoOfPlayers );
    ui->lblLanguage->setText( values.Languages_Language );
    // Control
    ui->lblRarity->setText( values.Rarities_Rarity );
    // MoreInfo

    emit setWebView(values.Games_WebLink_URL);

    QString picFile = QDir::toNativeSeparators( picturePath + "/" + values.Games_picture );

    const QImage image1 ( picFile );

    if ( ! image1.isNull() ) {
        ui->lblImage1->setPixmap(QPixmap::fromImage(image1.scaled(320*0.75, 256*0.75)));
    } else {
        ui->lblImage1->clear();
    }

    QFileInfo img(picFile);

    const QImage image2 ( picFile.replace( "." + img.suffix(), "_1." + img.suffix() ) );

    if ( ! image2.isNull() ) {
        ui->lblImage2->setPixmap(QPixmap::fromImage(image2.scaled(320*0.75, 256*0.75)));
    } else {
        ui->lblImage2->clear();
    }

}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
gamebase_type Gamebase::GetGameBaseInfos(QString dbpath, QString crc) {

    gamebase_type values;
    int           AR_Id = 0;
    int           CR_Id = 0;
    int           YE_Id = 0;
    int           GE_Id = 0;
    int           PR_Id = 0;
    int           LI_Id = 0;
    int           LA_Id = 0;
    int           RA_Id = 0;
    int           DE_Id = 0;
    int           MU_Id = 0;
    int           PU_Id = 0;
    int           GA_Id = 0;

    qDebug() << "checking gamebase " + dbpath + " for crc32 " + crc;

    if ( dbpath.trimmed() != "" ) {

        if (QSqlDatabase::contains("GameBase")) {
            QSqlDatabase::removeDatabase("GameBase");
        }

        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "GameBase");
        db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=" + dbpath);
        bool success = db.open();

        if ( success ) {

            QSqlQuery q(db);
/*
            q.prepare("select  Games.Name, Artists.Artist, Crackers.Cracker, Genres.Genre, Years.Year, "
                      "        Music.Name, Languages.Language, Programmers.Programmer, Licenses.License,"
                      "        Publishers.Publisher, Games.ScrnshotFilename, Games.SidFilename"
                      " from   Games,"
                      "        Artists,"
                      "        Crackers,"
                      "        Genres,"
                      "        Years,"
                      "        Music,"
                      "        Languages,"
                      "        Programmers,"
                      "        Licenses,"
                      "        Publishers"
                      " where  Games.AR_Id = Artists.AR_Id"
                      " and    Games.CR_Id = Crackers.CR_Id"
                      " and    Games.GE_Id = Genres.GE_Id"
                      " and    Games.YE_Id = Years.YE_Id"
                      " and    Games.GA_Id = Music.GA_Id"
                      " and    Games.LA_Id = Languages.LA_Id"
                      " and    Games.PR_Id = Programmers.PR_Id"
                      " and    Games.LI_Id = Licenses.LI_Id"
                      " and    Games.PU_Id = Publishers.PU_Id"
                      " and    Games.CRC = :CRC"
            );
*/
            q.prepare("select  Games.Name, Games.ScrnshotFilename, Games.SidFilename, "
                      "Games.AR_Id, Games.CR_Id, Games.YE_Id, Games.GE_Id, "
                      "Games.PR_Id, Games.LI_Id, Games.LA_Id, Games.GA_Id, "
                      "Games.RA_Id, Games.PlayersTo, Games.DE_Id, Games.MU_Id, Games.PU_Id, WebLink_URL "
                      " from   Games"
                      " where  Games.CRC = :CRC"
            );

            q.bindValue(":CRC", crc);

            if ( ! q.exec() ) {
                qDebug() << q.lastError();
            } else {

                while (q.next()) {

                    values.Games_name = q.value(0).toString();
                    values.Games_picture = q.value(1).toString();
                    values.Games_sid  = q.value(2).toString();

                    AR_Id = q.value(3).toInt();
                    CR_Id = q.value(4).toInt();
                    YE_Id = q.value(5).toInt();
                    GE_Id = q.value(6).toInt();
                    PR_Id = q.value(7).toInt();
                    LI_Id = q.value(8).toInt();
                    LA_Id = q.value(9).toInt();
                    GA_Id = q.value(10).toInt();
                    RA_Id = q.value(11).toInt();

                    values.Games_NoOfPlayers = q.value(12).toString();

                    DE_Id = q.value(13).toInt();
                    MU_Id = q.value(14).toInt();
                    PU_Id = q.value(15).toInt();
                    values.Games_WebLink_URL = q.value(16).toString();

              /*    values.Artists_Artist = q.value(1).toString();
                    values.Crackers_Cracker = q.value(2).toString();
                    values.Genres_Genre = q.value(3).toString();
                    values.Years_Year = q.value(4).toString();
                    values.Music_Name = q.value(5).toString();
                    values.Languages_Language = q.value(6).toString();
                    values.Programmers_Programmer = q.value(7).toString();
                    values.Licenses_License = q.value(8).toString();
                    values.Publishers_Publisher = q.value(9).toString();
                    values.Games_picture = q.value(10).toString();
                    values.Games_sid  = q.value(11).toString();
                */
                }
            }

            q.clear();

            values.Artists_Artist = "*";

            if ( AR_Id > 0 ) {

                q.prepare("select  Artists.Artist from   Artists where  Artists.AR_Id = :AR_Id" );

                q.bindValue(":AR_Id", AR_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Artists_Artist = q.value(0).toString();
                    }
                }
            }

            q.clear();

            values.Crackers_Cracker = "*";

            if ( CR_Id > 0 ) {

                q.prepare("select  Crackers.Cracker from   Crackers where  Crackers.CR_Id = :CR_Id" );

                q.bindValue(":CR_Id", CR_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Crackers_Cracker = q.value(0).toString();
                    }
                }
            }

            q.clear();

            values.Years_Year = "*";

            if ( YE_Id > 0 ) {

                q.prepare("select Years.Year from Years where YE_Id = :YE_Id" );

                q.bindValue(":YE_Id", YE_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Years_Year = q.value(0).toString();
                    }
                }
            }

            q.clear();

            values.Genres_Genre = "*";

            if ( GE_Id > 0 ) {

                q.prepare("select Genres.Genre from Genres where GE_Id = :GE_Id" );

                q.bindValue(":GE_Id", GE_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Genres_Genre = q.value(0).toString();
                    }
                }
            }

            q.clear();

            values.Programmers_Programmer = "*";

            if ( PR_Id > 0 ) {

                q.prepare("select Programmers.Programmer from Programmers where PR_Id = :PR_Id" );

                q.bindValue(":PR_Id", PR_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Programmers_Programmer = q.value(0).toString();
                    }
                }
            }

            q.clear();

            values.Licenses_License = "*";

            if ( LI_Id > 0 ) {

                q.prepare("select Licenses.License from Licenses where LI_Id = :LI_Id" );

                q.bindValue(":LI_Id", LI_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Licenses_License = q.value(0).toString();
                    }
                }
            }

            q.clear();

            values.Languages_Language = "*";

            if ( LA_Id > 0 ) {

                q.prepare("select Languages.Language from Languages where LA_Id = :LA_Id" );

                q.bindValue(":LA_Id", LA_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Languages_Language = q.value(0).toString();
                    }
                }
            }

            q.clear();

            values.Rarities_Rarity = "*";

            if ( RA_Id > 0 ) {

                q.prepare("select Rarities.Rarity from Rarities where RA_Id = :RA_Id" );

                q.bindValue(":RA_Id", RA_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Rarities_Rarity = q.value(0).toString();
                    }
                }
            }

            q.clear();

            values.Musicians_Musician = "*";

            if ( MU_Id > 0 ) {

                q.prepare("select Musicians.Musician from Musicians where MU_Id = :MU_Id" );

                q.bindValue(":MU_Id", MU_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Musicians_Musician = q.value(0).toString();
                    }
                }
            }

            q.clear();

            values.Developers_Developer = "*";

            if ( DE_Id > 0 ) {

                q.prepare("select Developers.Developer from Developers where DE_Id = :DE_Id" );

                q.bindValue(":DE_Id", DE_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Developers_Developer = q.value(0).toString();
                    }
                }
            }

            q.clear();

            values.Publishers_Publisher = "*";

            if ( DE_Id > 0 ) {

                q.prepare("select Publishers.Publisher from Publishers where PU_Id = :PU_Id" );

                q.bindValue(":PU_Id", PU_Id);

                if ( ! q.exec() ) {
                    qDebug() << q.lastError();
                } else {
                    while (q.next()) {
                        values.Publishers_Publisher = q.value(0).toString();
                    }
                }
            }

            q.clear();
        }

        db.close();
    }

    return (values);
}

/*****************************************************************************
 *
 *
 *****************************************************************************/
void Gamebase::CrcPrepareDb(QString dbpath, QString filepath, QString tmpPath, db database) {

    int         id;
    QString     game;
    QString     gamefile;
    QString     crc;
    QStringList files;
    _crc32      crc32;
    QFileInfo   fi;
    bool        cleanup;
    int         counter = 0;

    if ( dbpath.trimmed() != "" ) {

        if (QSqlDatabase::contains("GameBase")) {
            QSqlDatabase::removeDatabase("GameBase");
        }

        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "GameBase");
        db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=" + dbpath);
        bool success = db.open();

        if ( success ) {

            QSqlQuery c(db);
            c.prepare("select count(*) from Games");
            c.exec();
            int rows= 0;
            if (c.next()) {
                rows = c.value(0).toInt();
            }

            QSqlQuery q(db);
            q.prepare("select * from Games");

            if ( ! q.exec() ) {

                qDebug() << q.lastError();

            } else {

                QProgressDialog progress("generating CRC informations", "Abort", 0, rows , this);
                progress.setWindowModality(Qt::WindowModal);

                QSqlQuery  upd(db);

                while ( q.next() && ( ! progress.wasCanceled() ) ) {

                    progress.setValue(counter);

                    files.clear();

                    id = q.value(0).toInt();
                    gamefile = q.value(3).toString();

                    game = filepath + "/" + gamefile;

                    fi.setFile(game);

                    if ( fi.suffix() == "zip" ) {
                        cleanup = true;
                        files = JlCompress::extractDir(QDir::toNativeSeparators(game), tmpPath);
                    } else {
                        cleanup = false;
                        files << game;
                    }

                    for (int i = 0; i < files.size(); ++i) {

                        if ( files.at(i).right(3).toUpper() != "NFO" ) {

                            crc = crc32.getCRC32(files.at(i));

                            upd.prepare("UPDATE Games SET CRC=:CRC WHERE GA_Id=:GA_Id;");
                            upd.bindValue(":CRC", crc);
                            upd.bindValue(":GA_Id", id);

                            if ( ! upd.exec() ) {
                                qDebug() << q.lastError();
                            } else {
                                qDebug() << game << files.at(i) << crc;
                            }

                            upd.clear();

                            QVariantList gamebasevalues;

                            gamebasevalues << crc << 1;
                            database.updateGamebaseFlag( gamebasevalues );
                        }

                        if ( cleanup ) {
                            QFile::remove(files.at(i));
                        }

                        QCoreApplication::processEvents();
                    }

                    counter++;
                }
            }
        }

        db.close();
    }
}

/*****************************************************************************
 *
 *
 *****************************************************************************/
void Gamebase::setInfoExt(QString text) {

    ui->tabWidget->setCurrentIndex(3);

    ui->textEdit->setText( text );

    ui->lblImage1->setVisible(false);
    ui->lblImage2->setVisible(false);
}
