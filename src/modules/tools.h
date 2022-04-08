#ifndef TOOLS_H
#define TOOLS_H

#include "math.h"

#include <QPixmap>
#include <QDebug>
#include <QDir>
#include <QSysInfo>
#include <QTcpSocket>
#include <QUrl>
#include <QMessageBox>

#include "src/modules/iconextractor.h"

class tools
{
public:
    tools();

    int _GeneratePassword( int, int, char* );
    int GeneratePassword( int, int, char* );

    QPixmap GetPicturePart (QString, QString) ;

    void createDir(QString);

    bool isHost64Bit();
    bool isBuild64Bit();

    bool fileExists(QString);
    bool checkUrlAlive(QUrl);
    bool fileCopy(QString, QString);

    bool systemShutdown();

    void extractIcons(QString, bool);

    QString bytesHumanReadable(float);

    float average_of_floats(const float* floats, int count);

    iconExtractor  m_iconExtractor;
};

#endif // TOOLS_H
