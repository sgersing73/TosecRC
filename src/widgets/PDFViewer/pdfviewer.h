#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QDialog>
#include <QtWidgets>
#include <QSettings>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStatusBar>
#include <QThread>

#include <poppler/qt5/poppler-qt5.h>

#include "src/modules/settings.h"
#include "src/modules/zip.h"
#include "src/modules/tools.h"

#include "src/widgets/FtpUpload/ftpupload.h"

namespace Ui {
class PDFViewer;
}

class PDFViewer : public QDialog
{
    Q_OBJECT
    QNetworkAccessManager manager;
    QList<QNetworkReply *> currentDownloads;

public:
    explicit PDFViewer(QWidget *parent = 0, QString = "");
    ~PDFViewer();

protected:
     void closeEvent(QCloseEvent *event);
     void mousePressEvent(QMouseEvent *event);

private slots:

     void on_cmdBackward_clicked();
     void on_cmdForward_clicked();
     void on_spinScaleFactor_valueChanged(int arg1);
     void on_cboSections_currentIndexChanged(const QString &arg1);
     void on_listWidgetTitels_itemClicked(QListWidgetItem *item);
     void on_sliPages_sliderMoved(int position);
     void on_sliPages_valueChanged(int value);
     void on_cmdAddLink_clicked();

     void printOutput();
     void printError();

     void ShowContextMenulistWidgetTitels(const QPoint& pos);

     void on_listWidgetThumb_itemClicked(QListWidgetItem *item);

     void on_edtPage_textChanged(const QString &arg1);

     void on_cmdUpload_clicked();

     void on_cmdExtract_clicked();

     void on_cmdSaveInfos_clicked();
     void loadInfos();
     void loadInfosMagazin();

     void on_cboYears_currentTextChanged(const QString &arg1);
     void fillComboYears(const QString arg1);
     void fillBookmarks();

     void on_cmdBookmark_clicked();

     void on_listWidgetBookmarks_itemClicked(QListWidgetItem *item);

     void on_cmdSectionSettings_clicked();

     void on_cmdDownload_clicked();

     void on_cmdCancelDownload_clicked();

private:

     Ui::PDFViewer *ui;

     QProcess      *m_proc;
     FtpUpload     *mMyFtpUpload;

     QString       m_Filename;
     QString       m_sSettingsFile;
     settings      m_settings;
     tools         m_tools;
     bool          m_externalView;

     QString       m_actItemName;
     QString       m_LibraryPath;
     QString       m_CachePath;
     QString       m_TempPath;

     QString downloadFile(QUrl, QString, QString, bool doLoad = false) ;
     void loadPage(int, int);
     void doDownload(const QUrl &);
     bool urlExists(QUrl);
     void loadThumbNails(QString);
     bool ExecuteProgram(QString, QStringList, bool);
};

#endif // PDFVIEWER_H
