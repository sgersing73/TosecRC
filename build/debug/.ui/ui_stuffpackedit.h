/********************************************************************************
** Form generated from reading UI file 'stuffpackedit.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUFFPACKEDIT_H
#define UI_STUFFPACKEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StuffPackEdit
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdCancel;
    QPushButton *cmdExit;
    QLabel *lblIniFile;
    QVBoxLayout *verticalLayout;
    QGroupBox *grpGlobal;
    QGridLayout *gridLayout_2;
    QLineEdit *edtLogo;
    QLineEdit *edtCodeTable;
    QLabel *label;
    QLineEdit *edtSoundtrack;
    QLineEdit *edtLogoDeveloper;
    QLabel *lblLogoDeveloper;
    QLabel *lblWiki;
    QLineEdit *edtWiki;
    QLabel *lblVideo;
    QLabel *label_7;
    QLabel *lblSoundtrack;
    QLineEdit *edtVideo;
    QLabel *label_8;
    QLineEdit *edtManual;
    QLabel *label_9;
    QLineEdit *edtSolution;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_10;
    QLabel *label_2;
    QLineEdit *edtDeveloper;
    QLabel *label_3;
    QLineEdit *edtPublisher;
    QLabel *label_4;
    QLineEdit *edtReleasedate;
    QLabel *label_5;
    QLineEdit *edtRating;
    QLabel *label_6;
    QLineEdit *edtPlayers;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_9;
    QTextEdit *edtInfo;
    QWidget *tabCover;
    QGridLayout *gridLayout_4;
    QGroupBox *grpCover;
    QGridLayout *gridLayout_3;
    QLineEdit *edtAddCoverList;
    QPushButton *cmdCoverAdd;
    QPushButton *cmdCoverRemove;
    QListWidget *lstCovers;
    QWidget *tabMedia;
    QGridLayout *gridLayout_6;
    QGroupBox *grpMedia;
    QGridLayout *gridLayout_5;
    QListWidget *lstMedia;
    QLineEdit *edtAddMediaList;
    QPushButton *cmdMediaRemove;
    QPushButton *cmdMediaAdd;
    QWidget *tab;
    QGridLayout *gridLayout_8;
    QGroupBox *grpScreenshot;
    QGridLayout *gridLayout_7;
    QLineEdit *edtAddScreenshotList;
    QListWidget *lstScreenshot;
    QPushButton *cmdScreenshotRemove;
    QPushButton *cmdScreenshotAdd;
    QWidget *tab_3;
    QGridLayout *gridLayout_12;
    QGroupBox *grpSoundtrack;
    QGridLayout *gridLayout_11;
    QLineEdit *edtAddSoundtrackList;
    QListWidget *lstSoundtrack;
    QPushButton *cmdSoundtrackRemove;
    QPushButton *cmdSoundtrackAdd;
    QWidget *tab_4;
    QGridLayout *gridLayout_14;
    QGroupBox *grpLinks;
    QGridLayout *gridLayout_13;
    QLineEdit *edtAddLinksList;
    QListWidget *lstLinks;
    QPushButton *cmdLinksRemove;
    QPushButton *cmdLinksAdd;
    QWidget *tab_5;
    QGridLayout *gridLayout_15;
    QTableWidget *twQuickLinks;

    void setupUi(QDialog *StuffPackEdit)
    {
        if (StuffPackEdit->objectName().isEmpty())
            StuffPackEdit->setObjectName(QString::fromUtf8("StuffPackEdit"));
        StuffPackEdit->resize(764, 483);
        gridLayout = new QGridLayout(StuffPackEdit);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(498, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdCancel = new QPushButton(StuffPackEdit);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout->addWidget(cmdCancel);

        cmdExit = new QPushButton(StuffPackEdit);
        cmdExit->setObjectName(QString::fromUtf8("cmdExit"));

        horizontalLayout->addWidget(cmdExit);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        lblIniFile = new QLabel(StuffPackEdit);
        lblIniFile->setObjectName(QString::fromUtf8("lblIniFile"));

        gridLayout->addWidget(lblIniFile, 2, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        grpGlobal = new QGroupBox(StuffPackEdit);
        grpGlobal->setObjectName(QString::fromUtf8("grpGlobal"));
        gridLayout_2 = new QGridLayout(grpGlobal);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        edtLogo = new QLineEdit(grpGlobal);
        edtLogo->setObjectName(QString::fromUtf8("edtLogo"));

        gridLayout_2->addWidget(edtLogo, 0, 2, 1, 1);

        edtCodeTable = new QLineEdit(grpGlobal);
        edtCodeTable->setObjectName(QString::fromUtf8("edtCodeTable"));

        gridLayout_2->addWidget(edtCodeTable, 6, 2, 1, 1);

        label = new QLabel(grpGlobal);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        edtSoundtrack = new QLineEdit(grpGlobal);
        edtSoundtrack->setObjectName(QString::fromUtf8("edtSoundtrack"));

        gridLayout_2->addWidget(edtSoundtrack, 4, 2, 1, 1);

        edtLogoDeveloper = new QLineEdit(grpGlobal);
        edtLogoDeveloper->setObjectName(QString::fromUtf8("edtLogoDeveloper"));

        gridLayout_2->addWidget(edtLogoDeveloper, 1, 2, 1, 1);

        lblLogoDeveloper = new QLabel(grpGlobal);
        lblLogoDeveloper->setObjectName(QString::fromUtf8("lblLogoDeveloper"));

        gridLayout_2->addWidget(lblLogoDeveloper, 1, 0, 1, 1);

        lblWiki = new QLabel(grpGlobal);
        lblWiki->setObjectName(QString::fromUtf8("lblWiki"));

        gridLayout_2->addWidget(lblWiki, 2, 0, 1, 1);

        edtWiki = new QLineEdit(grpGlobal);
        edtWiki->setObjectName(QString::fromUtf8("edtWiki"));

        gridLayout_2->addWidget(edtWiki, 2, 2, 1, 1);

        lblVideo = new QLabel(grpGlobal);
        lblVideo->setObjectName(QString::fromUtf8("lblVideo"));

        gridLayout_2->addWidget(lblVideo, 3, 0, 1, 1);

        label_7 = new QLabel(grpGlobal);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 6, 0, 1, 1);

        lblSoundtrack = new QLabel(grpGlobal);
        lblSoundtrack->setObjectName(QString::fromUtf8("lblSoundtrack"));

        gridLayout_2->addWidget(lblSoundtrack, 4, 0, 1, 1);

        edtVideo = new QLineEdit(grpGlobal);
        edtVideo->setObjectName(QString::fromUtf8("edtVideo"));

        gridLayout_2->addWidget(edtVideo, 3, 2, 1, 1);

        label_8 = new QLabel(grpGlobal);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 5, 0, 1, 1);

        edtManual = new QLineEdit(grpGlobal);
        edtManual->setObjectName(QString::fromUtf8("edtManual"));

        gridLayout_2->addWidget(edtManual, 5, 2, 1, 1);

        label_9 = new QLabel(grpGlobal);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 7, 0, 1, 1);

        edtSolution = new QLineEdit(grpGlobal);
        edtSolution->setObjectName(QString::fromUtf8("edtSolution"));

        gridLayout_2->addWidget(edtSolution, 7, 2, 1, 1);


        verticalLayout->addWidget(grpGlobal);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        tabWidget = new QTabWidget(StuffPackEdit);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_2 = new QHBoxLayout(tab_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_10->addWidget(label_2, 0, 0, 1, 1);

        edtDeveloper = new QLineEdit(tab_2);
        edtDeveloper->setObjectName(QString::fromUtf8("edtDeveloper"));

        gridLayout_10->addWidget(edtDeveloper, 0, 1, 1, 1);

        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_10->addWidget(label_3, 1, 0, 1, 1);

        edtPublisher = new QLineEdit(tab_2);
        edtPublisher->setObjectName(QString::fromUtf8("edtPublisher"));

        gridLayout_10->addWidget(edtPublisher, 1, 1, 1, 1);

        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_10->addWidget(label_4, 2, 0, 1, 1);

        edtReleasedate = new QLineEdit(tab_2);
        edtReleasedate->setObjectName(QString::fromUtf8("edtReleasedate"));

        gridLayout_10->addWidget(edtReleasedate, 2, 1, 1, 1);

        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_10->addWidget(label_5, 3, 0, 1, 1);

        edtRating = new QLineEdit(tab_2);
        edtRating->setObjectName(QString::fromUtf8("edtRating"));

        gridLayout_10->addWidget(edtRating, 3, 1, 1, 1);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_10->addWidget(label_6, 4, 0, 1, 1);

        edtPlayers = new QLineEdit(tab_2);
        edtPlayers->setObjectName(QString::fromUtf8("edtPlayers"));

        gridLayout_10->addWidget(edtPlayers, 4, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_10);

        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_9 = new QGridLayout(groupBox);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        edtInfo = new QTextEdit(groupBox);
        edtInfo->setObjectName(QString::fromUtf8("edtInfo"));

        gridLayout_9->addWidget(edtInfo, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox);

        tabWidget->addTab(tab_2, QString());
        tabCover = new QWidget();
        tabCover->setObjectName(QString::fromUtf8("tabCover"));
        gridLayout_4 = new QGridLayout(tabCover);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        grpCover = new QGroupBox(tabCover);
        grpCover->setObjectName(QString::fromUtf8("grpCover"));
        gridLayout_3 = new QGridLayout(grpCover);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        edtAddCoverList = new QLineEdit(grpCover);
        edtAddCoverList->setObjectName(QString::fromUtf8("edtAddCoverList"));

        gridLayout_3->addWidget(edtAddCoverList, 1, 0, 1, 1);

        cmdCoverAdd = new QPushButton(grpCover);
        cmdCoverAdd->setObjectName(QString::fromUtf8("cmdCoverAdd"));
        cmdCoverAdd->setText(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/pipette.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdCoverAdd->setIcon(icon);
        cmdCoverAdd->setIconSize(QSize(20, 20));

        gridLayout_3->addWidget(cmdCoverAdd, 1, 2, 1, 1);

        cmdCoverRemove = new QPushButton(grpCover);
        cmdCoverRemove->setObjectName(QString::fromUtf8("cmdCoverRemove"));
        cmdCoverRemove->setText(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/delete.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdCoverRemove->setIcon(icon1);
        cmdCoverRemove->setIconSize(QSize(20, 20));

        gridLayout_3->addWidget(cmdCoverRemove, 0, 2, 1, 1);

        lstCovers = new QListWidget(grpCover);
        lstCovers->setObjectName(QString::fromUtf8("lstCovers"));

        gridLayout_3->addWidget(lstCovers, 0, 0, 1, 1);


        gridLayout_4->addWidget(grpCover, 0, 0, 1, 1);

        tabWidget->addTab(tabCover, QString());
        tabMedia = new QWidget();
        tabMedia->setObjectName(QString::fromUtf8("tabMedia"));
        gridLayout_6 = new QGridLayout(tabMedia);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        grpMedia = new QGroupBox(tabMedia);
        grpMedia->setObjectName(QString::fromUtf8("grpMedia"));
        gridLayout_5 = new QGridLayout(grpMedia);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        lstMedia = new QListWidget(grpMedia);
        lstMedia->setObjectName(QString::fromUtf8("lstMedia"));

        gridLayout_5->addWidget(lstMedia, 0, 0, 1, 1);

        edtAddMediaList = new QLineEdit(grpMedia);
        edtAddMediaList->setObjectName(QString::fromUtf8("edtAddMediaList"));

        gridLayout_5->addWidget(edtAddMediaList, 1, 0, 1, 1);

        cmdMediaRemove = new QPushButton(grpMedia);
        cmdMediaRemove->setObjectName(QString::fromUtf8("cmdMediaRemove"));
        cmdMediaRemove->setIcon(icon1);
        cmdMediaRemove->setIconSize(QSize(20, 20));

        gridLayout_5->addWidget(cmdMediaRemove, 0, 2, 1, 1);

        cmdMediaAdd = new QPushButton(grpMedia);
        cmdMediaAdd->setObjectName(QString::fromUtf8("cmdMediaAdd"));
        cmdMediaAdd->setIcon(icon);
        cmdMediaAdd->setIconSize(QSize(20, 20));

        gridLayout_5->addWidget(cmdMediaAdd, 1, 2, 1, 1);


        gridLayout_6->addWidget(grpMedia, 0, 0, 1, 1);

        tabWidget->addTab(tabMedia, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_8 = new QGridLayout(tab);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        grpScreenshot = new QGroupBox(tab);
        grpScreenshot->setObjectName(QString::fromUtf8("grpScreenshot"));
        gridLayout_7 = new QGridLayout(grpScreenshot);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        edtAddScreenshotList = new QLineEdit(grpScreenshot);
        edtAddScreenshotList->setObjectName(QString::fromUtf8("edtAddScreenshotList"));

        gridLayout_7->addWidget(edtAddScreenshotList, 1, 0, 1, 1);

        lstScreenshot = new QListWidget(grpScreenshot);
        lstScreenshot->setObjectName(QString::fromUtf8("lstScreenshot"));

        gridLayout_7->addWidget(lstScreenshot, 0, 0, 1, 1);

        cmdScreenshotRemove = new QPushButton(grpScreenshot);
        cmdScreenshotRemove->setObjectName(QString::fromUtf8("cmdScreenshotRemove"));
        cmdScreenshotRemove->setIcon(icon1);
        cmdScreenshotRemove->setIconSize(QSize(20, 20));

        gridLayout_7->addWidget(cmdScreenshotRemove, 0, 2, 1, 1);

        cmdScreenshotAdd = new QPushButton(grpScreenshot);
        cmdScreenshotAdd->setObjectName(QString::fromUtf8("cmdScreenshotAdd"));
        cmdScreenshotAdd->setIcon(icon);
        cmdScreenshotAdd->setIconSize(QSize(20, 20));

        gridLayout_7->addWidget(cmdScreenshotAdd, 1, 2, 1, 1);


        gridLayout_8->addWidget(grpScreenshot, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_12 = new QGridLayout(tab_3);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        grpSoundtrack = new QGroupBox(tab_3);
        grpSoundtrack->setObjectName(QString::fromUtf8("grpSoundtrack"));
        gridLayout_11 = new QGridLayout(grpSoundtrack);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        edtAddSoundtrackList = new QLineEdit(grpSoundtrack);
        edtAddSoundtrackList->setObjectName(QString::fromUtf8("edtAddSoundtrackList"));

        gridLayout_11->addWidget(edtAddSoundtrackList, 1, 0, 1, 1);

        lstSoundtrack = new QListWidget(grpSoundtrack);
        lstSoundtrack->setObjectName(QString::fromUtf8("lstSoundtrack"));

        gridLayout_11->addWidget(lstSoundtrack, 0, 0, 1, 1);

        cmdSoundtrackRemove = new QPushButton(grpSoundtrack);
        cmdSoundtrackRemove->setObjectName(QString::fromUtf8("cmdSoundtrackRemove"));
        cmdSoundtrackRemove->setIcon(icon1);
        cmdSoundtrackRemove->setIconSize(QSize(20, 20));

        gridLayout_11->addWidget(cmdSoundtrackRemove, 0, 2, 1, 1);

        cmdSoundtrackAdd = new QPushButton(grpSoundtrack);
        cmdSoundtrackAdd->setObjectName(QString::fromUtf8("cmdSoundtrackAdd"));
        cmdSoundtrackAdd->setIcon(icon);
        cmdSoundtrackAdd->setIconSize(QSize(20, 20));

        gridLayout_11->addWidget(cmdSoundtrackAdd, 1, 2, 1, 1);


        gridLayout_12->addWidget(grpSoundtrack, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_14 = new QGridLayout(tab_4);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        grpLinks = new QGroupBox(tab_4);
        grpLinks->setObjectName(QString::fromUtf8("grpLinks"));
        gridLayout_13 = new QGridLayout(grpLinks);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        edtAddLinksList = new QLineEdit(grpLinks);
        edtAddLinksList->setObjectName(QString::fromUtf8("edtAddLinksList"));

        gridLayout_13->addWidget(edtAddLinksList, 1, 0, 1, 1);

        lstLinks = new QListWidget(grpLinks);
        lstLinks->setObjectName(QString::fromUtf8("lstLinks"));

        gridLayout_13->addWidget(lstLinks, 0, 0, 1, 1);

        cmdLinksRemove = new QPushButton(grpLinks);
        cmdLinksRemove->setObjectName(QString::fromUtf8("cmdLinksRemove"));
        cmdLinksRemove->setIcon(icon1);
        cmdLinksRemove->setIconSize(QSize(20, 20));

        gridLayout_13->addWidget(cmdLinksRemove, 0, 2, 1, 1);

        cmdLinksAdd = new QPushButton(grpLinks);
        cmdLinksAdd->setObjectName(QString::fromUtf8("cmdLinksAdd"));
        cmdLinksAdd->setIcon(icon);
        cmdLinksAdd->setIconSize(QSize(20, 20));

        gridLayout_13->addWidget(cmdLinksAdd, 1, 2, 1, 1);


        gridLayout_14->addWidget(grpLinks, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_15 = new QGridLayout(tab_5);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        twQuickLinks = new QTableWidget(tab_5);
        if (twQuickLinks->columnCount() < 2)
            twQuickLinks->setColumnCount(2);
        if (twQuickLinks->rowCount() < 10)
            twQuickLinks->setRowCount(10);
        twQuickLinks->setObjectName(QString::fromUtf8("twQuickLinks"));
        twQuickLinks->setAcceptDrops(true);
        twQuickLinks->setRowCount(10);
        twQuickLinks->setColumnCount(2);
        twQuickLinks->horizontalHeader()->setVisible(false);
        twQuickLinks->horizontalHeader()->setCascadingSectionResizes(false);

        gridLayout_15->addWidget(twQuickLinks, 0, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 1);


        retranslateUi(StuffPackEdit);

        tabWidget->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(StuffPackEdit);
    } // setupUi

    void retranslateUi(QDialog *StuffPackEdit)
    {
        StuffPackEdit->setWindowTitle(QApplication::translate("StuffPackEdit", "Dialog", nullptr));
        cmdCancel->setText(QApplication::translate("StuffPackEdit", "Abbrechen", nullptr));
        cmdExit->setText(QApplication::translate("StuffPackEdit", "Beenden", nullptr));
        lblIniFile->setText(QApplication::translate("StuffPackEdit", "TextLabel", nullptr));
        grpGlobal->setTitle(QApplication::translate("StuffPackEdit", "Global", nullptr));
        label->setText(QApplication::translate("StuffPackEdit", "Logo Publisher:", nullptr));
        lblLogoDeveloper->setText(QApplication::translate("StuffPackEdit", "Logo Developer:", nullptr));
        lblWiki->setText(QApplication::translate("StuffPackEdit", "Wiki:", nullptr));
        lblVideo->setText(QApplication::translate("StuffPackEdit", "Video:", nullptr));
        label_7->setText(QApplication::translate("StuffPackEdit", "Codetable:", nullptr));
        lblSoundtrack->setText(QApplication::translate("StuffPackEdit", "Soundtrack", nullptr));
        label_8->setText(QApplication::translate("StuffPackEdit", "Manual:", nullptr));
        label_9->setText(QApplication::translate("StuffPackEdit", "Solution:", nullptr));
        label_2->setText(QApplication::translate("StuffPackEdit", "Developer:", nullptr));
        label_3->setText(QApplication::translate("StuffPackEdit", "Publisher:", nullptr));
        label_4->setText(QApplication::translate("StuffPackEdit", "Releasedate:", nullptr));
        label_5->setText(QApplication::translate("StuffPackEdit", "Rating:", nullptr));
        label_6->setText(QApplication::translate("StuffPackEdit", "Players:", nullptr));
        groupBox->setTitle(QApplication::translate("StuffPackEdit", "Description", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("StuffPackEdit", "Informations", nullptr));
        grpCover->setTitle(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabCover), QApplication::translate("StuffPackEdit", "Cover", nullptr));
        grpMedia->setTitle(QString());
        cmdMediaRemove->setText(QString());
        cmdMediaAdd->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabMedia), QApplication::translate("StuffPackEdit", "Media", nullptr));
        grpScreenshot->setTitle(QString());
        cmdScreenshotRemove->setText(QString());
        cmdScreenshotAdd->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("StuffPackEdit", "Screenshot", nullptr));
        grpSoundtrack->setTitle(QString());
        cmdSoundtrackRemove->setText(QString());
        cmdSoundtrackAdd->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("StuffPackEdit", "Soundtracks", nullptr));
        grpLinks->setTitle(QString());
        cmdLinksRemove->setText(QString());
        cmdLinksAdd->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("StuffPackEdit", "WEB-Links", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("StuffPackEdit", "Quick Links", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StuffPackEdit: public Ui_StuffPackEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUFFPACKEDIT_H
