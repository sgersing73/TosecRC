#include "xml.h"

xml::xml()
{
}

QString xml::getNameFromTosecDatFile(QString fileName) {

    QFile   datfile(fileName);
    QString name;

    datfile.open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&datfile);

    xmlReader.readNext();

    while (!xmlReader.atEnd()) {

      if (xmlReader.isStartElement()) {

          const QString tag = xmlReader.name().toString();

          if ( tag == "name" ) {

              name = xmlReader.readElementText();
          }
       }

       xmlReader.readNext();
    }

    datfile.close();

    return(name);
}

int xml::readXMLDatFile(QString fileName, QString RomSetPup) {

    QString system;
    QString setname;
    QString title;
    QString name;
    QString size;
    QString crc;
    QString md5;
    QString sha1;
    QString nontosec = "0";
    int     anzRomInSet = 0;
    int     id;
    QString RomSet;
    QVariantList values;
    int romsfound = 0;
    bool WHDLoadRom = false;

    QElapsedTimer timer;

    QFile   datfile(fileName);

    timer.start();

    //qDebug() << "-I- readXMLFile " << fileName;
    datfile.open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&datfile);

    xmlReader.readNext();

    while (!xmlReader.atEnd()) {

      if (xmlReader.isStartElement()) {

          const QString tag = xmlReader.name().toString();

          if ( tag == "name" ) {

              const QString text  = xmlReader.readElementText();
              const QStringList list = text.split(" - ");

              system = list.at(0);
              setname = text;
          }

          if ( tag == "game" ) {

              anzRomInSet = 0;
              RomSet = "";

              foreach(const QXmlStreamAttribute &attr, xmlReader.attributes()) {

                  if (attr.name().toString() == QLatin1String("name")) {

                      title = attr.value().toString();
                  }
              }
          }

          if ( tag == "machine" ) {
            WHDLoadRom = true;
          }

          if ( tag == "rom" ) {

              foreach(const QXmlStreamAttribute &attr, xmlReader.attributes()) {

                  if (attr.name().toString() == QLatin1String("name")) {
                      name = attr.value().toString();
                  }
                  if (attr.name().toString() == QLatin1String("size")) {
                      size = attr.value().toString();
                  }
                  if (attr.name().toString() == QLatin1String("crc")) {
                      crc = attr.value().toString().toLower();
                  }
                  if (attr.name().toString() == QLatin1String("md5")) {
                      md5 = attr.value().toString().toLower();
                  }
                  if (attr.name().toString() == QLatin1String("sha1")) {
                      sha1 = attr.value().toString().toLower();
                  }



                  if ( WHDLoadRom ) {
                      title = QFileInfo(name).completeBaseName();
                  }
              }

              values.clear();
              values << crc << system << setname << title << name << QString(size).toInt() << md5 << sha1 << nontosec << RomSetPup;

              id = m_db.storeFilesData(values);

              RomSet = RomSet + QString("%1,").arg(id);

              anzRomInSet++;

              romsfound++;
          }

      } else if (xmlReader.isEndElement()) {

          const QString tag = xmlReader.name().toString();

          if ( tag == "game" ) {

              if ( anzRomInSet > 1 ) { // Zu diesen Titel gehören mehrere ROMS

                  values.clear();
                  values << 1 << system << title << RomSet;

                  m_db.updateRomMultirom( values );

                  anzRomInSet = 0;
                  RomSet = "";
              }
          }
      }

      QCoreApplication::processEvents();

      xmlReader.readNext();
    }

    if (xmlReader.hasError()) {
      qDebug() << "-E- XML error: " << xmlReader.errorString().data();
    }

    datfile.close();

    return(romsfound);
}

thegamesdb_type xml::readXMLTheGamesDBFile(QString fileName) {

    QString error;

    thegamesdb_type thegamesdb;

    qDebug() << "-I- readXMLFile " << fileName;

    QFile datfile(fileName);

    datfile.open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&datfile);

    xmlReader.readNext();

    while (!xmlReader.atEnd()) {

      if (xmlReader.isStartElement()) {

          QString tag = xmlReader.name().toString();

          if ( tag == "baseImgUrl" ) { thegamesdb.baseImgUrl = xmlReader.readElementText(); }
          else if ( tag == "Platform" ) { thegamesdb.Platform = xmlReader.readElementText(); }
          else if ( tag == "id" ) { thegamesdb.id.append( xmlReader.readElementText() ); }
          else if ( tag == "GameTitle" ) { thegamesdb.GameTitle = xmlReader.readElementText(); }
          else if ( tag == "ReleaseDate" ) { thegamesdb.ReleaseDate = xmlReader.readElementText(); }
          else if ( tag == "Overview" ) { thegamesdb.Overview = xmlReader.readElementText(); }
          else if ( tag == "genre" ) { thegamesdb.genre.append( xmlReader.readElementText() ) ; }
          else if ( tag == "Players" ) { thegamesdb.Players = xmlReader.readElementText(); }
          else if ( tag == "Youtube" ) { thegamesdb.Youtube = xmlReader.readElementText(); }
          else if ( tag == "Publisher" ) { thegamesdb.Publisher = xmlReader.readElementText(); }
          else if ( tag == "Developer" ) { thegamesdb.Developer = xmlReader.readElementText(); }
          else if ( tag == "Rating" ) { thegamesdb.Rating = xmlReader.readElementText(); }
          else if ( tag == "original" ) { thegamesdb.original = xmlReader.readElementText(); }
          else if ( tag == "thumb" ) { thegamesdb.thumb.append( xmlReader.readElementText() ); }
          else if ( tag == "boxart" ) { thegamesdb.boxart.append( xmlReader.readElementText() ); }
          else if ( tag == "banner" ) { thegamesdb.banner.append(xmlReader.readElementText() ); }
          else if ( tag == "clearlogo" ) { thegamesdb.clearlogo = xmlReader.readElementText(); }
          else if ( tag == "error" ) { error = xmlReader.readElementText(); }


      } else if (xmlReader.isEndElement()) {

          QString tag = xmlReader.name().toString();

          if ( tag == "Data" ) {
            qDebug() << "processing finished...";
          }
          if ( tag == "Error" ) {
            qDebug() << error;
          }
      }

      QCoreApplication::processEvents();

      xmlReader.readNext();
    }

    if (xmlReader.hasError()) {
      qDebug() << "-E- XML error: " << xmlReader.errorString().data();
    }

    datfile.close();

    return(thegamesdb);
}


QList<thegamesdbgamelist_type> xml::readXMLTheGamesDBGameListFile(QString fileName) {

    QList<thegamesdbgamelist_type> thegamesdbgamelist;

    thegamesdbgamelist_type tmp_thegamesdbgamelist;

    qDebug() << "-I- readXMLFile " << fileName;

    QFile datfile(fileName);

    datfile.open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&datfile);

    xmlReader.readNext();

    while (!xmlReader.atEnd()) {

      if (xmlReader.isStartElement()) {

          QString tag = xmlReader.name().toString();

          if ( tag == "id" )               { tmp_thegamesdbgamelist.id           = xmlReader.readElementText(); }
          else if ( tag == "GameTitle" )   { tmp_thegamesdbgamelist.GameTitle    = xmlReader.readElementText(); }
          else if ( tag == "ReleaseDate" ) { tmp_thegamesdbgamelist.ReleaseDate  = xmlReader.readElementText(); }
          else if ( tag == "Platform" )    { tmp_thegamesdbgamelist.Platform     = xmlReader.readElementText(); }

      } else if (xmlReader.isEndElement()) {

          QString tag = xmlReader.name().toString();

          if ( tag == "Game" ) {
            thegamesdbgamelist.append(tmp_thegamesdbgamelist);
          }
      }

      QCoreApplication::processEvents();

      xmlReader.readNext();
    }

    if (xmlReader.hasError()) {
      qDebug() << "-E- XML error: " << xmlReader.errorString().data();
    }

    datfile.close();

    return(thegamesdbgamelist);
}


QList<thegamesdbplatformlist_type> xml::readXMLTheGamesDBPlatformListFile(QString fileName) {

    QList<thegamesdbplatformlist_type> thegamesdbplatformlist;

    thegamesdbplatformlist_type tmp_thegamesdbplatformlist;

    qDebug() << "-I- readXMLFile " << fileName;

    QFile datfile(fileName);

    datfile.open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&datfile);

    xmlReader.readNext();

    while (!xmlReader.atEnd()) {

      if (xmlReader.isStartElement()) {

          QString tag = xmlReader.name().toString();

          if ( tag == "id" )          { tmp_thegamesdbplatformlist.id     = xmlReader.readElementText(); }
          else if ( tag == "name" )   { tmp_thegamesdbplatformlist.Name   = xmlReader.readElementText(); }
          else if ( tag == "alias" )  { tmp_thegamesdbplatformlist.Alias  = xmlReader.readElementText(); }


      } else if (xmlReader.isEndElement()) {

          QString tag = xmlReader.name().toString();

          if ( tag == "Platform" ) {
            thegamesdbplatformlist.append(tmp_thegamesdbplatformlist);
          }
      }

      QCoreApplication::processEvents();

      xmlReader.readNext();
    }

    if (xmlReader.hasError()) {
      qDebug() << "-E- XML error: " << xmlReader.errorString().data();
    }

    datfile.close();

    return(thegamesdbplatformlist);
}
