/********************************************************************************
** Form generated from reading UI file 'ftpupload.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FTPUPLOAD_H
#define UI_FTPUPLOAD_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include "3dparty/wwWidgets/widgets/qwwled/qwwled.h"

QT_BEGIN_NAMESPACE

class Ui_FtpUpload
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *fileList;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblServer;
    QLineEdit *uploadUrlLineEdit;
    QLabel *lblPathl;
    QLineEdit *edtPath;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *cmdParent;
    QPushButton *cmdRemove;
    QPushButton *cmdMkdir;
    QPushButton *cmdUpload;
    QPushButton *cmdDownload;
    QwwLed *widLed;
    QLineEdit *fileNameLineEdit;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout;
    QLabel *lblUser;
    QLineEdit *edtUser;
    QLabel *label_2;
    QLineEdit *edtPasswort;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblFtpServer;
    QComboBox *comboBox;
    QPushButton *cmdConnect;
    QPushButton *cmdSave;
    QPushButton *cmdDelete;
    QPushButton *selectFileButton;
    QPushButton *pushButton;

    void setupUi(QDialog *FtpUpload)
    {
        if (FtpUpload->objectName().isEmpty())
            FtpUpload->setObjectName(QString::fromUtf8("FtpUpload"));
        FtpUpload->resize(619, 381);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FtpUpload->sizePolicy().hasHeightForWidth());
        FtpUpload->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(FtpUpload);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        fileList = new QTreeWidget(FtpUpload);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        fileList->setHeaderItem(__qtreewidgetitem);
        fileList->setObjectName(QString::fromUtf8("fileList"));

        gridLayout->addWidget(fileList, 5, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lblServer = new QLabel(FtpUpload);
        lblServer->setObjectName(QString::fromUtf8("lblServer"));

        horizontalLayout_3->addWidget(lblServer);

        uploadUrlLineEdit = new QLineEdit(FtpUpload);
        uploadUrlLineEdit->setObjectName(QString::fromUtf8("uploadUrlLineEdit"));

        horizontalLayout_3->addWidget(uploadUrlLineEdit);

        lblPathl = new QLabel(FtpUpload);
        lblPathl->setObjectName(QString::fromUtf8("lblPathl"));

        horizontalLayout_3->addWidget(lblPathl);

        edtPath = new QLineEdit(FtpUpload);
        edtPath->setObjectName(QString::fromUtf8("edtPath"));

        horizontalLayout_3->addWidget(edtPath);


        gridLayout->addLayout(horizontalLayout_3, 3, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        cmdParent = new QPushButton(FtpUpload);
        cmdParent->setObjectName(QString::fromUtf8("cmdParent"));
        cmdParent->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/ftp/images/farious/dir/up.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdParent->setIcon(icon);

        horizontalLayout_5->addWidget(cmdParent);

        cmdRemove = new QPushButton(FtpUpload);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));
        cmdRemove->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/ftp/images/farious/dir/delete.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdRemove->setIcon(icon1);

        horizontalLayout_5->addWidget(cmdRemove);

        cmdMkdir = new QPushButton(FtpUpload);
        cmdMkdir->setObjectName(QString::fromUtf8("cmdMkdir"));
        cmdMkdir->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/ftp/images/farious/dir/mkdir.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdMkdir->setIcon(icon2);

        horizontalLayout_5->addWidget(cmdMkdir);

        cmdUpload = new QPushButton(FtpUpload);
        cmdUpload->setObjectName(QString::fromUtf8("cmdUpload"));
        cmdUpload->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/ftp/images/farious/dir/upload.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUpload->setIcon(icon3);

        horizontalLayout_5->addWidget(cmdUpload);

        cmdDownload = new QPushButton(FtpUpload);
        cmdDownload->setObjectName(QString::fromUtf8("cmdDownload"));
        cmdDownload->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/ftp/images/farious/dir/download.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdDownload->setIcon(icon4);

        horizontalLayout_5->addWidget(cmdDownload);

        widLed = new QwwLed(FtpUpload);
        widLed->setObjectName(QString::fromUtf8("widLed"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widLed->sizePolicy().hasHeightForWidth());
        widLed->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(widLed);


        gridLayout->addLayout(horizontalLayout_5, 6, 1, 1, 1);

        fileNameLineEdit = new QLineEdit(FtpUpload);
        fileNameLineEdit->setObjectName(QString::fromUtf8("fileNameLineEdit"));
        fileNameLineEdit->setReadOnly(true);

        gridLayout->addWidget(fileNameLineEdit, 0, 1, 1, 1);

        line_2 = new QFrame(FtpUpload);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblUser = new QLabel(FtpUpload);
        lblUser->setObjectName(QString::fromUtf8("lblUser"));

        horizontalLayout->addWidget(lblUser);

        edtUser = new QLineEdit(FtpUpload);
        edtUser->setObjectName(QString::fromUtf8("edtUser"));

        horizontalLayout->addWidget(edtUser);

        label_2 = new QLabel(FtpUpload);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        edtPasswort = new QLineEdit(FtpUpload);
        edtPasswort->setObjectName(QString::fromUtf8("edtPasswort"));
        edtPasswort->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(edtPasswort);


        gridLayout->addLayout(horizontalLayout, 4, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblFtpServer = new QLabel(FtpUpload);
        lblFtpServer->setObjectName(QString::fromUtf8("lblFtpServer"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblFtpServer->sizePolicy().hasHeightForWidth());
        lblFtpServer->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(lblFtpServer);

        comboBox = new QComboBox(FtpUpload);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEditable(true);

        horizontalLayout_2->addWidget(comboBox);

        cmdConnect = new QPushButton(FtpUpload);
        cmdConnect->setObjectName(QString::fromUtf8("cmdConnect"));
        cmdConnect->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(cmdConnect->sizePolicy().hasHeightForWidth());
        cmdConnect->setSizePolicy(sizePolicy3);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/verify.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdConnect->setIcon(icon5);

        horizontalLayout_2->addWidget(cmdConnect);

        cmdSave = new QPushButton(FtpUpload);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));
        cmdSave->setEnabled(false);
        sizePolicy3.setHeightForWidth(cmdSave->sizePolicy().hasHeightForWidth());
        cmdSave->setSizePolicy(sizePolicy3);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSave->setIcon(icon6);

        horizontalLayout_2->addWidget(cmdSave);

        cmdDelete = new QPushButton(FtpUpload);
        cmdDelete->setObjectName(QString::fromUtf8("cmdDelete"));
        cmdDelete->setEnabled(false);
        sizePolicy3.setHeightForWidth(cmdDelete->sizePolicy().hasHeightForWidth());
        cmdDelete->setSizePolicy(sizePolicy3);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/delete.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdDelete->setIcon(icon7);

        horizontalLayout_2->addWidget(cmdDelete);


        gridLayout->addLayout(horizontalLayout_2, 2, 1, 1, 1);

        selectFileButton = new QPushButton(FtpUpload);
        selectFileButton->setObjectName(QString::fromUtf8("selectFileButton"));

        gridLayout->addWidget(selectFileButton, 0, 0, 1, 1);

        pushButton = new QPushButton(FtpUpload);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 6, 0, 1, 1);


        retranslateUi(FtpUpload);

        QMetaObject::connectSlotsByName(FtpUpload);
    } // setupUi

    void retranslateUi(QDialog *FtpUpload)
    {
        FtpUpload->setWindowTitle(QApplication::translate("FtpUpload", "Dialog", nullptr));
        lblServer->setText(QApplication::translate("FtpUpload", "Server URL:", nullptr));
        uploadUrlLineEdit->setPlaceholderText(QApplication::translate("FtpUpload", "upload url", nullptr));
        lblPathl->setText(QApplication::translate("FtpUpload", "Path:", nullptr));
        cmdParent->setText(QString());
        cmdRemove->setText(QString());
        cmdMkdir->setText(QString());
        cmdUpload->setText(QString());
        cmdDownload->setText(QString());
        fileNameLineEdit->setPlaceholderText(QApplication::translate("FtpUpload", "file path", nullptr));
        lblUser->setText(QApplication::translate("FtpUpload", "Benutzer:", nullptr));
        label_2->setText(QApplication::translate("FtpUpload", "Passwort:", nullptr));
        lblFtpServer->setText(QApplication::translate("FtpUpload", "<html><head/><body><p>FTP Verbindungen</p></body></html>", nullptr));
        cmdConnect->setText(QString());
        cmdSave->setText(QString());
        cmdDelete->setText(QString());
        selectFileButton->setText(QApplication::translate("FtpUpload", "&Datei ausw\303\244hlen", nullptr));
        pushButton->setText(QApplication::translate("FtpUpload", "&Beenden", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FtpUpload: public Ui_FtpUpload {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTPUPLOAD_H
