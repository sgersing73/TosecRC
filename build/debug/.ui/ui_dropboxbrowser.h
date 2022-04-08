/********************************************************************************
** Form generated from reading UI file 'dropboxbrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DROPBOXBROWSER_H
#define UI_DROPBOXBROWSER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DropboxBrowser
{
public:
    QGridLayout *gridLayout_2;
    QTreeView *treeView;
    QListView *listView;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdUpload;
    QPushButton *cmdDownload;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblToken;
    QLineEdit *edtToken;
    QLabel *lblPublisher;
    QPushButton *cmdGetFiles;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblDir;
    QLineEdit *edtDir;
    QListWidget *listDropbox;
    QHBoxLayout *horizontalLayout;
    QPushButton *cmdMakedir;
    QPushButton *cmdRemove;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *DropboxBrowser)
    {
        if (DropboxBrowser->objectName().isEmpty())
            DropboxBrowser->setObjectName(QString::fromUtf8("DropboxBrowser"));
        DropboxBrowser->resize(937, 386);
        gridLayout_2 = new QGridLayout(DropboxBrowser);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        treeView = new QTreeView(DropboxBrowser);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

        gridLayout_2->addWidget(treeView, 0, 0, 1, 1);

        listView = new QListView(DropboxBrowser);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

        gridLayout_2->addWidget(listView, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cmdUpload = new QPushButton(DropboxBrowser);
        cmdUpload->setObjectName(QString::fromUtf8("cmdUpload"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmdUpload->sizePolicy().hasHeightForWidth());
        cmdUpload->setSizePolicy(sizePolicy);
        cmdUpload->setMaximumSize(QSize(25, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/player/images/player/blue/forward.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUpload->setIcon(icon);

        verticalLayout->addWidget(cmdUpload);

        cmdDownload = new QPushButton(DropboxBrowser);
        cmdDownload->setObjectName(QString::fromUtf8("cmdDownload"));
        sizePolicy.setHeightForWidth(cmdDownload->sizePolicy().hasHeightForWidth());
        cmdDownload->setSizePolicy(sizePolicy);
        cmdDownload->setMaximumSize(QSize(25, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/player/images/player/blue/backward.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdDownload->setIcon(icon1);

        verticalLayout->addWidget(cmdDownload);


        gridLayout_2->addLayout(verticalLayout, 0, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblToken = new QLabel(DropboxBrowser);
        lblToken->setObjectName(QString::fromUtf8("lblToken"));

        horizontalLayout_4->addWidget(lblToken);

        edtToken = new QLineEdit(DropboxBrowser);
        edtToken->setObjectName(QString::fromUtf8("edtToken"));

        horizontalLayout_4->addWidget(edtToken);


        gridLayout->addLayout(horizontalLayout_4, 5, 0, 1, 1);

        lblPublisher = new QLabel(DropboxBrowser);
        lblPublisher->setObjectName(QString::fromUtf8("lblPublisher"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblPublisher->sizePolicy().hasHeightForWidth());
        lblPublisher->setSizePolicy(sizePolicy1);
        lblPublisher->setMinimumSize(QSize(0, 0));
        lblPublisher->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe Print"));
        font.setPointSize(19);
        lblPublisher->setFont(font);
        lblPublisher->setScaledContents(false);
        lblPublisher->setAlignment(Qt::AlignCenter);
        lblPublisher->setWordWrap(false);

        gridLayout->addWidget(lblPublisher, 0, 0, 1, 1);

        cmdGetFiles = new QPushButton(DropboxBrowser);
        cmdGetFiles->setObjectName(QString::fromUtf8("cmdGetFiles"));

        gridLayout->addWidget(cmdGetFiles, 4, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblDir = new QLabel(DropboxBrowser);
        lblDir->setObjectName(QString::fromUtf8("lblDir"));
        lblDir->setMinimumSize(QSize(35, 0));

        horizontalLayout_2->addWidget(lblDir);

        edtDir = new QLineEdit(DropboxBrowser);
        edtDir->setObjectName(QString::fromUtf8("edtDir"));

        horizontalLayout_2->addWidget(edtDir);


        gridLayout->addLayout(horizontalLayout_2, 6, 0, 1, 1);

        listDropbox = new QListWidget(DropboxBrowser);
        listDropbox->setObjectName(QString::fromUtf8("listDropbox"));
        listDropbox->setStyleSheet(QString::fromUtf8(""));
        listDropbox->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(listDropbox, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cmdMakedir = new QPushButton(DropboxBrowser);
        cmdMakedir->setObjectName(QString::fromUtf8("cmdMakedir"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cmdMakedir->sizePolicy().hasHeightForWidth());
        cmdMakedir->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(cmdMakedir);

        cmdRemove = new QPushButton(DropboxBrowser);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));
        sizePolicy2.setHeightForWidth(cmdRemove->sizePolicy().hasHeightForWidth());
        cmdRemove->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(cmdRemove);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 3, 1, 1);


        retranslateUi(DropboxBrowser);

        QMetaObject::connectSlotsByName(DropboxBrowser);
    } // setupUi

    void retranslateUi(QDialog *DropboxBrowser)
    {
        DropboxBrowser->setWindowTitle(QApplication::translate("DropboxBrowser", "Dropbox File Manager", nullptr));
        cmdUpload->setText(QString());
        cmdDownload->setText(QString());
        lblToken->setText(QApplication::translate("DropboxBrowser", "Token", nullptr));
        cmdGetFiles->setText(QApplication::translate("DropboxBrowser", "List Dropbox Files", nullptr));
        lblDir->setText(QApplication::translate("DropboxBrowser", "Dir:", nullptr));
        cmdMakedir->setText(QApplication::translate("DropboxBrowser", "mkdir", nullptr));
        cmdRemove->setText(QApplication::translate("DropboxBrowser", "delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DropboxBrowser: public Ui_DropboxBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DROPBOXBROWSER_H
