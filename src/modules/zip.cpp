#include "zip.h"

Zip::Zip()
{

}

QStringList Zip::extract(const QString & filePath, const QString & extDirPath, const QString & singleFileName = QString(""), const QString & password = QString("") ) {

    QStringList files;

    files.clear();

    QuaZip zip(filePath);

    if (!zip.open(QuaZip::mdUnzip)) {
        qWarning("testRead(): zip.open(): %d", zip.getZipError());
        return files;
    }

    //zip.setFileNameCodec("IBM866");

    qWarning("%d entries\n", zip.getEntriesCount());
    qWarning("Global comment: %s\n", zip.getComment().toLocal8Bit().constData());

    QuaZipFileInfo info;

    QuaZipFile file(&zip);

    QFile out;
    QString name;
    char c;

    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) {

        QCoreApplication::processEvents();

        if (!zip.getCurrentFileInfo(&info)) {
            qWarning("testRead(): getCurrentFileInfo(): %d\n", zip.getZipError());
            return files;
        }

        if (!singleFileName.isEmpty())
            if (!info.name.contains(singleFileName))
                continue;

        if (password.isEmpty() ) {
            if (!file.open(QIODevice::ReadOnly )) {
                qWarning("testRead(): file.open(): %d", file.getZipError());
                return files;
            }
        } else {
            if (!file.open(QIODevice::ReadOnly, password.toLatin1().data() )) {
                qWarning("testRead(): file.open(): %d", file.getZipError());
                return files;
            }
        }

        name = QString("%1/%2").arg(extDirPath).arg(file.getActualFileName());

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return files;
        }

        //out.setFileName("out/" + name);
        out.setFileName(name);

        // this will fail if "name" contains subdirectories, but we don't mind that
        out.open(QIODevice::WriteOnly);
        // Slow like hell (on GNU/Linux at least), but it is not my fault.
        // Not ZIP/UNZIP package's fault either.
        // The slowest thing here is out.putChar(c).
        while (file.getChar(&c)) {

            out.putChar(c);

        }

        out.close();

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return files;
        }

        if (!file.atEnd()) {
            qWarning("testRead(): read all but not EOF");
            return files;
        }

        file.close();

        files.append(name);

        if (file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.close(): %d", file.getZipError());
            return files;
        }
    }

    zip.close();

    if (zip.getZipError() != UNZ_OK) {
        qWarning("testRead(): zip.close(): %d", zip.getZipError());
    }

    return files;
}

bool Zip::archive(const QString & filePath, const QDir & dir, const QString & comment = QString("")) {

    QuaZip zip(filePath);
    //zip.setFileNameCodec("IBM866");

    if (!zip.open(QuaZip::mdCreate)) {
        qDebug() << QString("testCreate(): zip.open(): %1").arg(zip.getZipError());
        return false;
    }

    if (!dir.exists()) {
        qDebug() <<  QString("dir.exists(%1)=FALSE").arg(dir.absolutePath());
        return false;
    }

    QFile inFile;

    // Получаем список файлов и папок рекурсивно
    QStringList sl;
    recurseAddDir(dir, sl);

    // Создаем массив состоящий из QFileInfo объектов
    QFileInfoList files;
    foreach (QString fn, sl) files << QFileInfo(fn);

    QuaZipFile outFile(&zip);

    char c;
    foreach(QFileInfo fileInfo, files) {

        QCoreApplication::processEvents();

        if (!fileInfo.isFile())
            continue;

        // Если файл в поддиректории, то добавляем имя этой поддиректории к именам файлов
        // например: fileInfo.filePath() = "D:\Work\Sources\SAGO\svn\sago\Release\tmp_DOCSWIN\Folder\123.opn"
        // тогда после удаления части строки fileNameWithSubFolders будет равен "Folder\123.opn" и т.д.
        QString fileNameWithRelativePath = fileInfo.filePath().remove(0, dir.absolutePath().length() + 1);

        inFile.setFileName(fileInfo.filePath());

        if (!inFile.open(QIODevice::ReadOnly)) {
            qDebug() << QString("testCreate(): inFile.open(): %1").arg(inFile.errorString().toLocal8Bit().constData());
            return false;
        }

        if (!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(fileNameWithRelativePath, fileInfo.filePath()))) {
            qDebug() << QString("testCreate(): outFile.open(): %1").arg(outFile.getZipError());
            return false;
        }

        while (inFile.getChar(&c) && outFile.putChar(c)) {
        };

        if (outFile.getZipError() != UNZ_OK) {
            qDebug() << QString("testCreate(): outFile.putChar(): %1").arg(outFile.getZipError());
            return false;
        }

        outFile.close();

        if (outFile.getZipError() != UNZ_OK) {
            qDebug() << QString("testCreate(): outFile.close(): %1").arg(outFile.getZipError());
            return false;
        }

        inFile.close();
    }

    // + комментарий
    if (!comment.isEmpty())
        zip.setComment(comment);

    zip.close();

    if (zip.getZipError() != 0) {
        qDebug() << QString("testCreate(): zip.close(): %1").arg(zip.getZipError());
        return false;
    }

    return true;
}

bool Zip::archive(const QString & filePath, const QStringList &sl, const QString & comment = QString("")) {

    QuaZip zip(filePath);
    zip.setFileNameCodec("Windows-1250");

    if (!zip.open(QuaZip::mdAppend)) {
        qDebug() << QString("testCreate(): zip.open(): %1").arg(zip.getZipError());
        return false;
    }

    if (sl.isEmpty()) {
        qDebug() <<  QString("sl is empty");
        return false;
    }

    QFile inFile;

    // Создаем массив состоящий из QFileInfo объектов
    QFileInfoList files;
    foreach (QString fn, sl) files << QFileInfo(fn);

    QuaZipFile outFile(&zip);

    char c;
    foreach(QFileInfo fileInfo, files) {

        if (!fileInfo.isFile())
            continue;

        // Если файл в поддиректории, то добавляем имя этой поддиректории к именам файлов
        // например: fileInfo.filePath() = "D:\Work\Sources\SAGO\svn\sago\Release\tmp_DOCSWIN\Folder\123.opn"
        // тогда после удаления части строки fileNameWithSubFolders будет равен "Folder\123.opn" и т.д.
        QString fileNameWithRelativePath = fileInfo.fileName();

        inFile.setFileName(fileInfo.filePath());

        if (!inFile.open(QIODevice::ReadOnly)) {
            qDebug() << QString("testCreate(): inFile.open(): %1").arg(inFile.errorString().toLocal8Bit().constData());
            return false;
        }

        if (!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(fileNameWithRelativePath, fileInfo.filePath()))) {
            qDebug() << QString("testCreate(): outFile.open(): %1").arg(outFile.getZipError());
            return false;
        }

        while (inFile.getChar(&c) && outFile.putChar(c));

        if (outFile.getZipError() != UNZ_OK) {
            qDebug() << QString("testCreate(): outFile.putChar(): %1").arg(outFile.getZipError());
            return false;
        }

        outFile.close();

        if (outFile.getZipError() != UNZ_OK) {
            qDebug() << QString("testCreate(): outFile.close(): %1").arg(outFile.getZipError());
            return false;
        }

        inFile.close();

        QCoreApplication::processEvents();
    }

    // + комментарий
    if (!comment.isEmpty())
        zip.setComment(comment);

    zip.close();

    if (zip.getZipError() != 0) {
        qDebug() << QString("testCreate(): zip.close(): %1").arg(zip.getZipError());
        return false;
    }

    return true;
}

/* Рекурсивно ищет все файлы в директории \a и добавляет в список \b */
void Zip::recurseAddDir(QDir d, QStringList & list) {

    QStringList qsl = d.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

    foreach (QString file, qsl) {

        QFileInfo finfo(QString("%1/%2").arg(d.path()).arg(file));

        if (finfo.isSymLink())
            return;

        if (finfo.isDir()) {

            QString dirname = finfo.fileName();
            QDir sd(finfo.filePath());

            recurseAddDir(sd, list);

        } else
            list << QDir::toNativeSeparators(finfo.filePath());
    }
}
