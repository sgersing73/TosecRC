#ifndef CRC32_H
#define CRC32_H

#include <QByteArray>
#include <QString>
#include <QFile>

class _crc32
{
public:
    QByteArray getCRC32(QString);
};

#endif // CRC32_H
