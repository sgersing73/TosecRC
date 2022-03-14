#include "sidplayer.h"
#include "ui_sidplayer.h"

SidPlayer::SidPlayer(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::SidPlayer)
{
    QString path;

    ui->setupUi(this);

    QString value = _settings.loadStringSetting(INI_FILE, "MusicPlayer", "Path");
    qDebug() << value;

    if ( ! value.isEmpty() ) {
       path = value ;
    } else  {
       path = QDir::currentPath();
    }

    // DIRECTORIES
    _dirModel = new QFileSystemModel(this);

    // Set filter
    _dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);

    // QFileSystemModel requires root path
    _dirModel->setRootPath(path);

    // Attach the dir model to the view
    ui->treeView->setModel(_dirModel);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
    ui->treeView->setHeaderHidden( true );
    ui->treeView->setCurrentIndex(_dirModel->index(path));

    // FILES
    _fileModel = new QFileSystemModel(this);

    // Set filter
    _fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);

    // QFileSystemModel requires root path
    _fileModel->setRootPath(path);

    QStringList sDriveFilters;

    sDriveFilters << "*.sid" << "*.ay" << "*.mus" << "*.str" << "*.wds";

    _fileModel->setNameFilters(sDriveFilters);
    _fileModel->setNameFilterDisables(false);
}

SidPlayer::~SidPlayer()
{
    delete ui;
}

void SidPlayer::on_treeView_clicked(const QModelIndex &index)
{
    _settings.saveStringSetting(INI_FILE, "MusicPlayer", "Path", _dirModel->fileInfo(index).absoluteFilePath());

    emit setFileExtension(QStringList() << "*.sid" << "*.ay" << "*.mus" << "*.str" << "*.wds");

    emit directoryChanged(_dirModel->fileInfo(index).absoluteFilePath());
}

void SidPlayer::on_cmdHVSC_clicked()
{
    QString values = _settings.loadStringSetting(INI_FILE, "MusicPlayer", "HVSC");

    if ( ! values.isEmpty() ) {

        if ( values.contains(";") ) {

            // Nach dem Semikolon kommt die URL
            emit setWebView(values.split(";").at(1));
        }

        ui->treeView->setCurrentIndex(_dirModel->index(values.split(";").at(0)));
    }

}

void SidPlayer::on_cmdProjectAY_clicked()
{
    QString values = _settings.loadStringSetting(INI_FILE, "MusicPlayer", "ProjectAY");

    if ( ! values.isEmpty() ) {

        if ( values.contains(";") ) {

            // Nach dem Semikolon kommt die URL
            emit setWebView(values.split(";").at(1));
        }

        ui->treeView->setCurrentIndex(_dirModel->index(values.split(";").at(0)));
    }
}

void SidPlayer::on_pushButton_clicked()
{
    QString values = _settings.loadStringSetting(INI_FILE, "MusicPlayer", "CGSC");

    if ( ! values.isEmpty() ) {

        if ( values.contains(";") ) {

            // Nach dem Semikolon kommt die URL
            emit setWebView(values.split(";").at(1));
        }

        ui->treeView->setCurrentIndex(_dirModel->index(values.split(";").at(0)));
    }
}
