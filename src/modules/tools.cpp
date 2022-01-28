#include "tools.h"

/*
 * pwgen.c 1.4
 *
 *   Usage: pwgen [length] [specials]
 *
 *          length - an optional argument indicating the length of the password
 *          specials - use '1' to force use of special characters
 *
 * This will generate random passwords of the specified or default length.
 * If the second argument is a 1 then special characters will also be used.
 *
 * Copyright (C) 2013 - Paul E. Jones <paulej@packetizer.com>
 * Permission to use, copy, modify and distribute this software is granted.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef WIN32
#include <windows.h>
#include <Wincrypt.h>
#else
#include <malloc.h>
#include <time.h>
#endif

/* Define the default password length */
#define DEFAULT_PASSWORD_LENGTH 16

tools::tools()
{

}

/*
 * GeneratePassword
 *
 *     Description
 *         This routine will generate a password and return it as a string.
 *         By default, it will not utilize special characters like "~" in
 *         passwords, but if the second argument is a 1, it will.  Note that
 *         use of special characters provides only minimum additional strenth,
 *         yet they are not very friendly for humans. For details, visit
 *         https://secure.packetizer.com/pwgen/.
 *
 *     Parameters
 *         length [in]
 *             The length of the password
 *         special [in]
 *             Indicates whether to use special characters other than
 *             the letters A-Z, a-z, and digits 0-9.
 *         password [out]
 *             Character array containing the produced password
 *
 *     Returns
 *         Return 0 if successful or non-zero if there was a failure.
 */
int tools::_GeneratePassword(int length, int special, char *password)
{
    char pwchars[] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
        's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z', '~', '`', '!', '@', '#', '$', '%', '^',
        '&', '*', '(', ')', '_', '+', '=', '-', '{', '}', '|', '\\', ']', '[',
        ':', '"', '\'', ';', '<', '>', '?', '/', '.'
    };
    int max_random;
    int random_value = 0;
#ifdef WIN32
    HCRYPTPROV hProv;
    DWORD result_code;
#else
    FILE *fp = NULL;
#endif

    /*
     * To avoid modulo bias in selecting random numbers, we will discard
     * any random number greater than max_random.  This value of max_random
     * is determined as per the equations shown below.
     */
    if (special == 1)
    {
        max_random = 255 - (255 % 93) - 1;
    }
    else
    {
        max_random = 255 - (255 % 62) - 1;
    }

    /*
     * Prepare to generate random numbers
     */
#ifdef WIN32
    if (!CryptAcquireContext(   &hProv,
                                nullptr,
                                nullptr,
                                PROV_RSA_FULL,
                                CRYPT_VERIFYCONTEXT))
    {
        result_code = GetLastError();
        if (GetLastError() == NTE_BAD_KEYSET)
        {
            if (!CryptAcquireContext(   &hProv,
                                        nullptr,
                                        nullptr,
                                        PROV_RSA_FULL,
                                        CRYPT_NEWKEYSET|CRYPT_VERIFYCONTEXT))
            {
                result_code = GetLastError();
            }
            else
            {
                result_code = ERROR_SUCCESS;
            }
        }

        if (result_code != ERROR_SUCCESS)
        {
            fprintf(stderr, "Could not acquire handle to crypto context");
            return -1;
        }
    }
#else
    /*
     * We'll use /dev/urandom. It is less preferred over /dev/random,
     * but /dev/random blocks and can take a long time to return
     * a random number.  If /dev/urandom cannot be accessed, we'll use
     * the rand() function in the C libraries.
     */
    if (!(fp = fopen("/dev/urandom", "r")))
    {
        /* We must use the pseudo random number generator */
        srand(time(NULL));
    }
#endif

    while(length > 0)
    {
#ifdef WIN32
        if (!CryptGenRandom(hProv,
                            1,
                            (BYTE *) &random_value))
        {
            fprintf(stderr, "Windows is unable to generate random digits");
            CryptReleaseContext(hProv, 0);
            return -1;
        }
#else
        random_value = (fp) ? fgetc(fp) : rand();
#endif

        /*
         * Reject certain random numbers to avoid modulo bias
         */
        if (random_value > max_random)
        {
            continue;
        }

        if (special == 1)
        {
            *password = pwchars[random_value % 93];
        }
        else
        {
            *password = pwchars[random_value % 62];
        }
        password++;
        length--;
    }

    /* Insert an end-of-line character */
    *password = '\0';

#ifdef WIN32
    CryptReleaseContext(hProv, 0);
#else
    if (fp)
    {
        fclose(fp);
    }
#endif

    return 0;
}

/*
 * main
 *
 *     Description
 *         This is the main routine.
 *
 *     Parameters
 *         argc [in]
 *             The number of command-line arguments
 *         argv [in]
 *             The command-line argument array
 *
 *     Returns
 *         Return 0 if successful or non-zero if there was a failure.
 *
 */
int tools::GeneratePassword(int length, int special, char *password)
{
    int password_length = length;
    int result_code = 0;
    int use_special = special;
    char *tmp;

    /* Allocate space for the password */
    tmp = (char*) malloc(password_length + 1);
    if (tmp != nullptr) {
        if (!_GeneratePassword(password_length, use_special, tmp)) {
            memcpy(password, tmp, length);
        } else {
            result_code = 2;
        }
        free(tmp);
    } else {
        result_code = 1;
    }

    return result_code;
}

QPixmap tools::GetPicturePart (QString filename, QString coord) {

    QPixmap source(filename);
    QPixmap dest;
    QStringList coords;

    coords = coord.split(",");

    //qDebug() << coords;
    //qDebug() << coords.count();

    if ( coords.count() >= 4 )  {
        dest = source.copy(coords.at(0).toInt(), coords.at(1).toInt(), coords.at(2).toInt(), coords.at(3).toInt());
    }

    //if ( coords.count() >= 6 ) {
    //    return(dest.scaled(coords.at(4).toInt(),coords.at(5).toInt()));
    //} else {
        return(dest);
    //}
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void tools::createDir(QString path) {

    QDir dir( path );

    if (!dir.exists()) {

        qDebug() << "create directory" << path;

        dir.mkpath(path);
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool tools::isHost64Bit() {
  static bool h = QSysInfo::currentCpuArchitecture().contains(QLatin1String("64"));
  return h;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool tools::isBuild64Bit() {
  static bool b = QSysInfo::buildCpuArchitecture().contains(QLatin1String("64"));
  return b;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool tools::fileExists(QString path) {

     return QFileInfo::exists(path) && QFileInfo(path).isFile() && QFileInfo(path).size() > 0;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool tools::checkUrlAlive(QUrl theurl) {

    QTextStream out(stdout);
    QTcpSocket socket;
    QByteArray buffer;

    socket.connectToHost(theurl.host(), 80);
    if (socket.waitForConnected()) {
        //Standard http request
        socket.write("GET / HTTP/1.1\r\n"
                 "host: " + theurl.host().toUtf8() + "\r\n\r\n");
        if (socket.waitForReadyRead()) {
            while(socket.bytesAvailable()){
                buffer.append(socket.readAll());
                int packetSize=buffer.size();
                while(packetSize>0)
                {
                    //Output server response for debugging
                    out << "[" << buffer.data() << "]" <<endl;

                    //set Url if 200, 301, or 302 response given assuming that server will redirect
                    if (buffer.contains("200 OK") ||
                        buffer.contains("302 Found") ||
                        buffer.contains("301 Moved")) {
                        return true;
                    }
                    buffer.remove(0,packetSize);
                    //packetSize=getPacketSize(buffer);
                    packetSize=buffer.size();

                } //while packet size >0
            } //while socket.bytesavail

        } //socket wait for ready read
    }//socket write

    return false;
}

/**********************************************************************************************************************
 * FileCopy(filename, m_TempPath + "/Work.zip")
 *********************************************************************************************************************/
bool tools::fileCopy(QString source, QString dest) {

    QFile destfile;
    bool  ende = false;
    bool  retVal = false;
    int   retrycnt = 0;

    if (  this->fileExists( dest ) && ( QFileInfo(source).size() == QFileInfo(dest).size() ) ) {

        qDebug() << "fileCopy" << dest << "already exists!";

        ende = true;
        retVal = true;
    }

    while ( !ende ) {

        destfile.setFileName( dest );

        if ( ! destfile.copy( source, dest ) )  {

            retrycnt++;

            ende = false;

            if ( retrycnt >= 3 ) {

                QMessageBox msgBox;
                msgBox.setText("Something went wrong... ");
                msgBox.setInformativeText("unable to copy " + source +
                                          " to: " + dest + " error:" +
                                          destfile.errorString());
                msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Ignore | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Retry);
                int ret = msgBox.exec();

                switch (ret) {
                  case QMessageBox::Retry:
                      // Save was clicked
                      break;
                  case QMessageBox::Cancel:
                      // Cancel was clicked
                      ende = true;
                      break;
                  case QMessageBox::Ignore:
                      // Ignore was pressen... continue with next one...
                      retVal = true;
                      ende = true;
                      break;
                  default:
                      // should never be reached
                      break;
                }
            }

        } else {
            qDebug() << "file " + source + " copied to " + dest;

            ende = true;
            retVal = true;
        }
    }

    if ( !retVal ) {
        qDebug() << "unable to copy " + source +
                    " to: " + dest + " error:" +
                    destfile.errorString();
    }

    return(retVal);
}

void tools::extractIcons(QString filename, bool large) {

#ifdef WIN32
    PixmapEntryList pixmaps = m_iconExtractor.extractIcons(filename, large);

    for (const auto &entry : pixmaps) {
        const QString fileName = "T:/Cache/Icons/" + entry.name + QLatin1String(".png");
        if (!entry.pixmap.save(fileName)) {
            qDebug() << "Error writing image file " << fileName;
        }
        qDebug() << "Wrote " << QDir::toNativeSeparators(fileName);
    }
#endif
}


bool tools::systemShutdown()
{
#ifdef WIN32
   HANDLE hToken;
   TOKEN_PRIVILEGES tkp;

   // Get a token for this process.

   if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return( FALSE );

   // Get the LUID for the shutdown privilege.

   LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME,
        &tkp.Privileges[0].Luid);

   tkp.PrivilegeCount = 1;  // one privilege to set
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

   // Get the shutdown privilege for this process.

   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
        (PTOKEN_PRIVILEGES)nullptr, nullptr);

   if (GetLastError() != ERROR_SUCCESS)
      return FALSE;

   // Shut down the system and force all applications to close.

   if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
               SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
               SHTDN_REASON_MINOR_UPGRADE |
               SHTDN_REASON_FLAG_PLANNED))
      return FALSE;

   //shutdown was successful
   return TRUE;
#endif
}

QString tools::bytesHumanReadable(float num)
{
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("bytes");

    while(num >= 1024.0 && i.hasNext())
     {
        unit = i.next();
        num /= 1024.0;
    }
    return QString().setNum(num,'f',2)+" "+unit;
}
