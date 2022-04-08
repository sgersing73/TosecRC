/********************************************************************************
** Form generated from reading UI file 'gamebase.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEBASE_H
#define UI_GAMEBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gamebase
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLabel *lblGameType;
    QLabel *label_2;
    QLabel *label;
    QLabel *lblCopyright;
    QLabel *label_4;
    QLabel *lblGenre;
    QLabel *lblArtist;
    QLabel *label_5;
    QLabel *lblNoOfPlayers;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *lblCoding;
    QLabel *lblDeveloper;
    QLabel *label_8;
    QLabel *lblLicense;
    QLabel *label_9;
    QLabel *label_6;
    QLabel *lblLanguage;
    QLabel *label_10;
    QLabel *lblControl;
    QLabel *label_11;
    QLabel *lblRarity;
    QLabel *label_12;
    QLabel *lblMoreInfo;
    QWidget *tab_2;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_9;
    QLabel *lblLoadingScreen;
    QLabel *label_20;
    QLabel *label_15;
    QLabel *lnlNoOfTrain;
    QLabel *label_22;
    QLabel *lblOriginal;
    QLabel *label_19;
    QLabel *lblMemoryExp;
    QLabel *label_16;
    QLabel *lblTitleScreen;
    QLabel *label_25;
    QLabel *label_21;
    QLabel *lblPlayable;
    QLabel *lblGameLength;
    QLabel *label_26;
    QLabel *lblIncludedDocs;
    QLabel *label_23;
    QLabel *lblPalNtsc;
    QLabel *label_27;
    QLabel *lblHighScoreSaver;
    QLabel *label_24;
    QLabel *lblDownload;
    QLabel *label_28;
    QLabel *lblTrueDriveEmul;
    QWidget *tab_3;
    QWidget *tab_4;
    QGridLayout *gridLayout_8;
    QTextEdit *textEdit;
    QWidget *tab_5;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_6;
    QLabel *lblPhoto;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *lblMusician;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *lblGroup;
    QLabel *lblNick;
    QHBoxLayout *horizontalLayout;
    QLabel *lblImage1;
    QLabel *lblImage2;

    void setupUi(QGroupBox *Gamebase)
    {
        if (Gamebase->objectName().isEmpty())
            Gamebase->setObjectName(QString::fromUtf8("Gamebase"));
        Gamebase->resize(417, 278);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Gamebase->sizePolicy().hasHeightForWidth());
        Gamebase->setSizePolicy(sizePolicy);
        Gamebase->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(Gamebase);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(Gamebase);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lblGameType = new QLabel(tab);
        lblGameType->setObjectName(QString::fromUtf8("lblGameType"));

        gridLayout_2->addWidget(lblGameType, 3, 1, 1, 1);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lblCopyright = new QLabel(tab);
        lblCopyright->setObjectName(QString::fromUtf8("lblCopyright"));

        gridLayout_2->addWidget(lblCopyright, 0, 1, 1, 1);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);

        lblGenre = new QLabel(tab);
        lblGenre->setObjectName(QString::fromUtf8("lblGenre"));

        gridLayout_2->addWidget(lblGenre, 0, 3, 1, 1);

        lblArtist = new QLabel(tab);
        lblArtist->setObjectName(QString::fromUtf8("lblArtist"));

        gridLayout_2->addWidget(lblArtist, 4, 1, 1, 1);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 2, 1, 1);

        lblNoOfPlayers = new QLabel(tab);
        lblNoOfPlayers->setObjectName(QString::fromUtf8("lblNoOfPlayers"));

        gridLayout_2->addWidget(lblNoOfPlayers, 1, 3, 1, 1);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 3, 0, 1, 1);

        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        lblCoding = new QLabel(tab);
        lblCoding->setObjectName(QString::fromUtf8("lblCoding"));

        gridLayout_2->addWidget(lblCoding, 2, 1, 1, 1);

        lblDeveloper = new QLabel(tab);
        lblDeveloper->setObjectName(QString::fromUtf8("lblDeveloper"));

        gridLayout_2->addWidget(lblDeveloper, 1, 1, 1, 1);

        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 4, 0, 1, 1);

        lblLicense = new QLabel(tab);
        lblLicense->setObjectName(QString::fromUtf8("lblLicense"));

        gridLayout_2->addWidget(lblLicense, 5, 1, 1, 1);

        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 5, 0, 1, 1);

        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 2, 1, 1);

        lblLanguage = new QLabel(tab);
        lblLanguage->setObjectName(QString::fromUtf8("lblLanguage"));

        gridLayout_2->addWidget(lblLanguage, 2, 3, 1, 1);

        label_10 = new QLabel(tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 3, 2, 1, 1);

        lblControl = new QLabel(tab);
        lblControl->setObjectName(QString::fromUtf8("lblControl"));

        gridLayout_2->addWidget(lblControl, 3, 3, 1, 1);

        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 4, 2, 1, 1);

        lblRarity = new QLabel(tab);
        lblRarity->setObjectName(QString::fromUtf8("lblRarity"));

        gridLayout_2->addWidget(lblRarity, 4, 3, 1, 1);

        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 5, 2, 1, 1);

        lblMoreInfo = new QLabel(tab);
        lblMoreInfo->setObjectName(QString::fromUtf8("lblMoreInfo"));

        gridLayout_2->addWidget(lblMoreInfo, 5, 3, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_10 = new QGridLayout(tab_2);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        lblLoadingScreen = new QLabel(tab_2);
        lblLoadingScreen->setObjectName(QString::fromUtf8("lblLoadingScreen"));

        gridLayout_9->addWidget(lblLoadingScreen, 1, 3, 1, 1);

        label_20 = new QLabel(tab_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setMaximumSize(QSize(70, 16777215));

        gridLayout_9->addWidget(label_20, 1, 2, 1, 1);

        label_15 = new QLabel(tab_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_9->addWidget(label_15, 2, 0, 1, 1);

        lnlNoOfTrain = new QLabel(tab_2);
        lnlNoOfTrain->setObjectName(QString::fromUtf8("lnlNoOfTrain"));

        gridLayout_9->addWidget(lnlNoOfTrain, 1, 1, 1, 1);

        label_22 = new QLabel(tab_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_9->addWidget(label_22, 1, 0, 1, 1);

        lblOriginal = new QLabel(tab_2);
        lblOriginal->setObjectName(QString::fromUtf8("lblOriginal"));

        gridLayout_9->addWidget(lblOriginal, 0, 3, 1, 1);

        label_19 = new QLabel(tab_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setMaximumSize(QSize(70, 16777215));

        gridLayout_9->addWidget(label_19, 0, 2, 1, 1);

        lblMemoryExp = new QLabel(tab_2);
        lblMemoryExp->setObjectName(QString::fromUtf8("lblMemoryExp"));

        gridLayout_9->addWidget(lblMemoryExp, 0, 1, 1, 1);

        label_16 = new QLabel(tab_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setScaledContents(false);

        gridLayout_9->addWidget(label_16, 0, 0, 1, 1);

        lblTitleScreen = new QLabel(tab_2);
        lblTitleScreen->setObjectName(QString::fromUtf8("lblTitleScreen"));

        gridLayout_9->addWidget(lblTitleScreen, 2, 3, 1, 1);

        label_25 = new QLabel(tab_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setMaximumSize(QSize(70, 16777215));

        gridLayout_9->addWidget(label_25, 2, 2, 1, 1);

        label_21 = new QLabel(tab_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_9->addWidget(label_21, 3, 0, 1, 1);

        lblPlayable = new QLabel(tab_2);
        lblPlayable->setObjectName(QString::fromUtf8("lblPlayable"));

        gridLayout_9->addWidget(lblPlayable, 2, 1, 1, 1);

        lblGameLength = new QLabel(tab_2);
        lblGameLength->setObjectName(QString::fromUtf8("lblGameLength"));

        gridLayout_9->addWidget(lblGameLength, 3, 1, 1, 1);

        label_26 = new QLabel(tab_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_9->addWidget(label_26, 3, 2, 1, 1);

        lblIncludedDocs = new QLabel(tab_2);
        lblIncludedDocs->setObjectName(QString::fromUtf8("lblIncludedDocs"));

        gridLayout_9->addWidget(lblIncludedDocs, 3, 3, 1, 1);

        label_23 = new QLabel(tab_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_9->addWidget(label_23, 4, 0, 1, 1);

        lblPalNtsc = new QLabel(tab_2);
        lblPalNtsc->setObjectName(QString::fromUtf8("lblPalNtsc"));

        gridLayout_9->addWidget(lblPalNtsc, 4, 1, 1, 1);

        label_27 = new QLabel(tab_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_9->addWidget(label_27, 4, 2, 1, 1);

        lblHighScoreSaver = new QLabel(tab_2);
        lblHighScoreSaver->setObjectName(QString::fromUtf8("lblHighScoreSaver"));

        gridLayout_9->addWidget(lblHighScoreSaver, 4, 3, 1, 1);

        label_24 = new QLabel(tab_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_9->addWidget(label_24, 5, 0, 1, 1);

        lblDownload = new QLabel(tab_2);
        lblDownload->setObjectName(QString::fromUtf8("lblDownload"));

        gridLayout_9->addWidget(lblDownload, 5, 1, 1, 1);

        label_28 = new QLabel(tab_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_9->addWidget(label_28, 5, 2, 1, 1);

        lblTrueDriveEmul = new QLabel(tab_2);
        lblTrueDriveEmul->setObjectName(QString::fromUtf8("lblTrueDriveEmul"));

        gridLayout_9->addWidget(lblTrueDriveEmul, 5, 3, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_8 = new QGridLayout(tab_4);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        textEdit = new QTextEdit(tab_4);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_8->addWidget(textEdit, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_5 = new QGridLayout(tab_5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        lblPhoto = new QLabel(tab_5);
        lblPhoto->setObjectName(QString::fromUtf8("lblPhoto"));

        gridLayout_6->addWidget(lblPhoto, 3, 1, 1, 1);

        label_13 = new QLabel(tab_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMaximumSize(QSize(60, 16777215));

        gridLayout_6->addWidget(label_13, 2, 0, 1, 1);

        label_14 = new QLabel(tab_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMaximumSize(QSize(60, 16777215));

        gridLayout_6->addWidget(label_14, 0, 0, 1, 1);

        lblMusician = new QLabel(tab_5);
        lblMusician->setObjectName(QString::fromUtf8("lblMusician"));

        gridLayout_6->addWidget(lblMusician, 0, 1, 1, 1);

        label_17 = new QLabel(tab_5);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setMaximumSize(QSize(60, 16777215));

        gridLayout_6->addWidget(label_17, 3, 0, 1, 1);

        label_18 = new QLabel(tab_5);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_6->addWidget(label_18, 1, 0, 1, 1);

        lblGroup = new QLabel(tab_5);
        lblGroup->setObjectName(QString::fromUtf8("lblGroup"));

        gridLayout_6->addWidget(lblGroup, 2, 1, 1, 1);

        lblNick = new QLabel(tab_5);
        lblNick->setObjectName(QString::fromUtf8("lblNick"));

        gridLayout_6->addWidget(lblNick, 1, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_6, 0, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblImage1 = new QLabel(Gamebase);
        lblImage1->setObjectName(QString::fromUtf8("lblImage1"));
        lblImage1->setMaximumSize(QSize(320, 256));
        lblImage1->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lblImage1);

        lblImage2 = new QLabel(Gamebase);
        lblImage2->setObjectName(QString::fromUtf8("lblImage2"));
        lblImage2->setMaximumSize(QSize(320, 256));
        lblImage2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lblImage2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Gamebase);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Gamebase);
    } // setupUi

    void retranslateUi(QGroupBox *Gamebase)
    {
        Gamebase->setWindowTitle(QApplication::translate("Gamebase", "GroupBox", nullptr));
        Gamebase->setTitle(QString());
        lblGameType->setText(QApplication::translate("Gamebase", "lblGameType", nullptr));
        label_2->setText(QApplication::translate("Gamebase", "Coding:", nullptr));
        label->setText(QApplication::translate("Gamebase", "Copyright:", nullptr));
        lblCopyright->setText(QApplication::translate("Gamebase", "lblCopyright", nullptr));
        label_4->setText(QApplication::translate("Gamebase", "Genre:", nullptr));
        lblGenre->setText(QApplication::translate("Gamebase", "lblGenre", nullptr));
        lblArtist->setText(QApplication::translate("Gamebase", "lblArtist", nullptr));
        label_5->setText(QApplication::translate("Gamebase", "No. of Players:", nullptr));
        lblNoOfPlayers->setText(QApplication::translate("Gamebase", "lnlNoOfPlayers", nullptr));
        label_3->setText(QApplication::translate("Gamebase", "Game Type:", nullptr));
        label_7->setText(QApplication::translate("Gamebase", "Developer:", nullptr));
        lblCoding->setText(QApplication::translate("Gamebase", "lblCoding", nullptr));
        lblDeveloper->setText(QApplication::translate("Gamebase", "lblDeveloper", nullptr));
        label_8->setText(QApplication::translate("Gamebase", "Artist:", nullptr));
        lblLicense->setText(QApplication::translate("Gamebase", "lblLicense", nullptr));
        label_9->setText(QApplication::translate("Gamebase", "License:", nullptr));
        label_6->setText(QApplication::translate("Gamebase", "Language:", nullptr));
        lblLanguage->setText(QApplication::translate("Gamebase", "lblLanguage", nullptr));
        label_10->setText(QApplication::translate("Gamebase", "Control:", nullptr));
        lblControl->setText(QApplication::translate("Gamebase", "lblControl", nullptr));
        label_11->setText(QApplication::translate("Gamebase", "Rarity:", nullptr));
        lblRarity->setText(QApplication::translate("Gamebase", "lblRarity", nullptr));
        label_12->setText(QApplication::translate("Gamebase", "More Info:", nullptr));
        lblMoreInfo->setText(QApplication::translate("Gamebase", "lblMoreInfo", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Gamebase", "Game", nullptr));
        lblLoadingScreen->setText(QApplication::translate("Gamebase", "lblLoadingScreen", nullptr));
        label_20->setText(QApplication::translate("Gamebase", "Loading Screen:", nullptr));
        label_15->setText(QApplication::translate("Gamebase", "Playable:", nullptr));
        lnlNoOfTrain->setText(QApplication::translate("Gamebase", "lnlNoOfTrain", nullptr));
        label_22->setText(QApplication::translate("Gamebase", "No. of Trainers:", nullptr));
        lblOriginal->setText(QApplication::translate("Gamebase", "lblOriginal", nullptr));
        label_19->setText(QApplication::translate("Gamebase", "Original:", nullptr));
        lblMemoryExp->setText(QApplication::translate("Gamebase", "lblMemoryExp", nullptr));
        label_16->setText(QApplication::translate("Gamebase", "Memory Expansion:", nullptr));
        lblTitleScreen->setText(QApplication::translate("Gamebase", "lblTitleScreen", nullptr));
        label_25->setText(QApplication::translate("Gamebase", "Title Screen:", nullptr));
        label_21->setText(QApplication::translate("Gamebase", "Game Length:", nullptr));
        lblPlayable->setText(QApplication::translate("Gamebase", "lblPlayable", nullptr));
        lblGameLength->setText(QApplication::translate("Gamebase", "lblGameLength", nullptr));
        label_26->setText(QApplication::translate("Gamebase", "Included Docs:", nullptr));
        lblIncludedDocs->setText(QApplication::translate("Gamebase", "lblIncludedDocs", nullptr));
        label_23->setText(QApplication::translate("Gamebase", "PAL/NTSC:", nullptr));
        lblPalNtsc->setText(QApplication::translate("Gamebase", "lblPalNtsc", nullptr));
        label_27->setText(QApplication::translate("Gamebase", "High Score Saver:", nullptr));
        lblHighScoreSaver->setText(QApplication::translate("Gamebase", "lblHighScoreSaver", nullptr));
        label_24->setText(QApplication::translate("Gamebase", "Download:", nullptr));
        lblDownload->setText(QApplication::translate("Gamebase", "lblDownload", nullptr));
        label_28->setText(QApplication::translate("Gamebase", "True Drive Emul:", nullptr));
        lblTrueDriveEmul->setText(QApplication::translate("Gamebase", "lblTrueDriveEmul", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Gamebase", "Version", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Gamebase", "Personal", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Gamebase", "Notes", nullptr));
        lblPhoto->setText(QApplication::translate("Gamebase", "lblPhoto", nullptr));
        label_13->setText(QApplication::translate("Gamebase", "Group:", nullptr));
        label_14->setText(QApplication::translate("Gamebase", "Musician:", nullptr));
        lblMusician->setText(QApplication::translate("Gamebase", "lblMusician", nullptr));
        label_17->setText(QApplication::translate("Gamebase", "Photo:", nullptr));
        label_18->setText(QApplication::translate("Gamebase", "Nick:", nullptr));
        lblGroup->setText(QApplication::translate("Gamebase", "lblGroup", nullptr));
        lblNick->setText(QApplication::translate("Gamebase", "lblNick", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("Gamebase", "Music", nullptr));
        lblImage1->setText(QApplication::translate("Gamebase", "screen shot 1", nullptr));
        lblImage2->setText(QApplication::translate("Gamebase", "screen shot 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gamebase: public Ui_Gamebase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEBASE_H
