#ifndef ICONEXTRACTOR_H
#define ICONEXTRACTOR_H

#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>
#include <QImage>
#include <QPixmap>
#include <QScopedArrayPointer>
#include <QStringList>
#include <QSysInfo>
#include <QDebug>
#include <QFileInfo>

#include <iostream>

#ifdef WIN32

#include <QtWin>

#include <shellapi.h>
#include <comdef.h>
#include <commctrl.h>
#include <objbase.h>
#include <commoncontrols.h>

#endif

struct PixmapEntry {
    QString name;
    QPixmap pixmap;
};
typedef QList<PixmapEntry> PixmapEntryList;
class iconExtractor
{
public:

    iconExtractor();

    PixmapEntryList extractIcons(const QString &sourceFile, bool large);
    PixmapEntryList extractShellIcons(const QString &sourceFile, bool addOverlays);

private:

#ifdef WIN32
    QPixmap pixmapFromShellImageList(int iImageList, const SHFILEINFO &info);
    static QString formatSizeText(const QSize &size);
#endif

};

#endif // ICONEXTRACTOR_H
