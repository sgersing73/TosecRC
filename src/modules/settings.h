#ifndef TSETTINGS_H
#define TSETTINGS_H

#include "config.h"

#include <QString>
#include <QDebug>

class settings
{
public:

    settings();

    void saveStringSetting(QString, QString, QString, QString);
    QString loadStringSetting(QString, QString, QString, QString = "");

    void saveBoolSetting(QString, QString, QString, bool);
    bool loadBoolSetting(QString, QString, QString, bool = false);

    void saveIntSetting(QString, QString, QString, int);
    int loadIntSetting(QString, QString, QString, long = 0);

    QStringList getAllSection(QString);
    QStringList GetAllKeys(QString, QString);

    void Delete(QString, QString, QString);
};

#endif // SETTINGS_H
