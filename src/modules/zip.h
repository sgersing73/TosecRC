#ifndef ZIP_H
#define ZIP_H

#ifdef _WIN32
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#else
#include "quazip5/quazip.h"
#include "quazip5/quazipfile.h"
#endif

#include <qdir.h>
#include <qfile.h>
#include <qdebug.h>
#include <QCoreApplication>

class Zip
{
public:
    Zip();

    void recurseAddDir(QDir d, QStringList & list);

    QStringList extract(const QString & filePath, const QString & extDirPath, const QString & singleFileName, const QString & password ) ;

    bool archive(const QString & filePath, const QDir & dir, const QString & comment );
    bool archive(const QString & filePath, const QStringList & sl, const QString & comment ) ;

};

#endif // ZIP_H
