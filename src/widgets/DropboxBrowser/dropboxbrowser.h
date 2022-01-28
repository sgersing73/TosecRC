#ifndef DROPBOXBROWSER_H
#define DROPBOXBROWSER_H

#include <QDialog>
#include <QDir>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QMenu>
#include <QInputDialog>

#include "src/modules/settings.h"

#include "qdropbox2.h"
#include "qdropbox2folder.h"
#include "qdropbox2file.h"

namespace Ui {
class DropboxBrowser;
}

class DropboxBrowser : public QDialog
{
    Q_OBJECT

public:
    DropboxBrowser(QWidget *parent = 0);
    ~DropboxBrowser();

protected:
     void closeEvent(QCloseEvent *event);

private slots:
    void on_cmdGetFiles_clicked();
    void on_cmdDownload_clicked();
    void on_cmdUpload_clicked();
    void on_treeView_clicked(const QModelIndex &index);
    void on_listView_clicked(const QModelIndex &index);

    void showContextMenu(const QPoint&);
    void eraseItem();
    void getDirectoryList(QString) ;

    void on_cmdMakedir_clicked();
    void on_cmdRemove_clicked();

    void on_listDropbox_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::DropboxBrowser *ui;

    QDropbox2 *m_Dropbox2;

    QString   m_Directory;
    QString   m_Token;

    settings  m_Settings;
    QString   m_File;
    QString   m_Path;

    QFileSystemModel *m_dirModel;
    QFileSystemModel *m_fileModel;

    QString           m_TempPath;

};

#endif // DROPBOXBROWSER_H
