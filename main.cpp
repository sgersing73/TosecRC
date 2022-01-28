#include <QApplication>

#include "mainwindow.h"

bool logging = false;

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt;

    if ( ! logging ) {
        return;
    }

    switch ( (int)type ) {
    case QtDebugMsg:
        txt = QString("%1 -D-: %2").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz")).arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("%1 -W-: %2").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz")).arg(msg);
    break;
    case QtCriticalMsg:
        txt = QString("%1 -C-: %2").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz")).arg(msg);
    break;
    case QtFatalMsg:
        txt = QString("%1 -F-: %2").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz")).arg(msg);
    break;
    }    

    QString filename = QString("TosecRC_%1.log").arg(QDateTime::currentDateTime().toString("yyyyMMdd"));

    QFile outFile(filename);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;

    QByteArray localMsg = msg.toLocal8Bit();
    fprintf(stderr, "MESSAGE (%s:%u %s): %s\n", context.file, context.line, context.function, localMsg.constData());
    fflush(stderr);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    settings _settings;

    logging  = _settings.loadBoolSetting(INI_FILE, "General", "logging");
    bool fullscreen  = _settings.loadBoolSetting(INI_FILE, "General", "fullscreen");

    qInstallMessageHandler(myMessageHandler);

    QString tmpDir = QDir::tempPath();
    QLockFile lockFile(tmpDir + "/TosecRC.lock");

    if ( !lockFile.tryLock(100) ) {

        QMessageBox msgBox;
        msgBox.setText("You already have this app running.\r\nOnly one instance is allowed.");
        msgBox.setInformativeText("Start the app?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int reply = msgBox.exec();

        if (reply == QMessageBox::Yes) {
            lockFile.unlock();
        } else {
            return 1;
        }
    }

    a.setFont( QFont( _settings.loadStringSetting(INI_FILE, "General", "fontname"),
                      _settings.loadIntSetting(INI_FILE, "General", "fontsize") ) );

    QPixmap pixmap(":/images/images/splash.gif");
    QSplashScreen splash;
    splash.setPixmap(pixmap);
    splash.showMessage("initialize TosecRC...");
    splash.show();

    a.processEvents();

    MainWindow w(nullptr, &splash);
    if (fullscreen) {
        w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    }
    w.show();

    splash.showMessage("initialize done... starting up");

    splash.finish(&w);

    return a.exec();
}
