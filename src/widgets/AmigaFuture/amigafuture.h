#ifndef AMIGAFUTURE_H
#define AMIGAFUTURE_H

#include <QDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QProcess>
#include <QFileDialog>
#include <QPixmap>
#include <QSettings>
#include <QCloseEvent>
#include <QInputDialog>

#include "src/modules/settings.h"
#include "src/modules/tools.h"

namespace Ui {
class AmigaFuture;
}

class AmigaFuture : public QDialog
{
    Q_OBJECT

protected:
     void closeEvent(QCloseEvent *event) override;

public:
    explicit AmigaFuture(QWidget *parent = nullptr);
    ~AmigaFuture();

    void initMagazine();

    void addTreeRoot(QString name, QString description, QString url, int from, int to);
    void addTreeChild(QTreeWidgetItem *parent, QString name, QString description, QString url);
    QString downloadFile(QUrl iUrl, QString fileName, QString iDest, bool force);
    bool ExecuteProgram(QString program, QStringList arguments, bool wait) ;

private slots:

    void on_treeMagazine_itemClicked(QTreeWidgetItem *item, int column);

    void on_spinScaleFactor_valueChanged(const QString &arg1);

    void on_beenden_clicked();

    void on_treeMagazine_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::AmigaFuture *ui;

    settings        m_settings;
    tools           m_tools;
    QStringList     m_stdOutLines;
    QStringList     m_stdErrLines;
    QProcess        *m_proc;
    QString         m_sSettingsFile;
    QTreeWidgetItem *m_Item;

};

#endif // AMIGAFUTURE_H
