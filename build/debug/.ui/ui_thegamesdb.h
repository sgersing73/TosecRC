/********************************************************************************
** Form generated from reading UI file 'thegamesdb.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THEGAMESDB_H
#define UI_THEGAMESDB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>

QT_BEGIN_NAMESPACE

class Ui_TheGamesDB
{
public:
    QGridLayout *gridLayout_3;
    QLabel *lblStuffpack;
    QHBoxLayout *horizontalLayout;
    QComboBox *cboPlatform;
    QLineEdit *edtSearch;
    QPushButton *cmdSearch;
    QSplitter *splitter;
    QListWidget *lisGamesList;
    QGroupBox *grpRom;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *lblGameTitle;
    QLabel *label_2;
    QLabel *lblPlatform;
    QLabel *label_3;
    QLabel *lblPlayers;
    QLabel *label_4;
    QLabel *lblReleaseDate;
    QLabel *label_5;
    QLabel *lblPublisher;
    QLabel *label_6;
    QLabel *lblDeveloper;
    QGridLayout *gridLayout;
    QPushButton *cmdScreenshots;
    QPushButton *cmdBoxart;
    QLabel *lblOverview;
    QLabel *lblInfo;
    QPushButton *cmdCreateStuffPack;

    void setupUi(QDialog *TheGamesDB)
    {
        if (TheGamesDB->objectName().isEmpty())
            TheGamesDB->setObjectName(QString::fromUtf8("TheGamesDB"));
        TheGamesDB->resize(731, 401);
        gridLayout_3 = new QGridLayout(TheGamesDB);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lblStuffpack = new QLabel(TheGamesDB);
        lblStuffpack->setObjectName(QString::fromUtf8("lblStuffpack"));

        gridLayout_3->addWidget(lblStuffpack, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        cboPlatform = new QComboBox(TheGamesDB);
        cboPlatform->setObjectName(QString::fromUtf8("cboPlatform"));

        horizontalLayout->addWidget(cboPlatform);

        edtSearch = new QLineEdit(TheGamesDB);
        edtSearch->setObjectName(QString::fromUtf8("edtSearch"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edtSearch->sizePolicy().hasHeightForWidth());
        edtSearch->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(edtSearch);

        cmdSearch = new QPushButton(TheGamesDB);
        cmdSearch->setObjectName(QString::fromUtf8("cmdSearch"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmdSearch->sizePolicy().hasHeightForWidth());
        cmdSearch->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(cmdSearch);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);

        splitter = new QSplitter(TheGamesDB);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        lisGamesList = new QListWidget(splitter);
        lisGamesList->setObjectName(QString::fromUtf8("lisGamesList"));
        splitter->addWidget(lisGamesList);
        grpRom = new QGroupBox(splitter);
        grpRom->setObjectName(QString::fromUtf8("grpRom"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(grpRom->sizePolicy().hasHeightForWidth());
        grpRom->setSizePolicy(sizePolicy2);
        gridLayout_2 = new QGridLayout(grpRom);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(grpRom);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lblGameTitle = new QLabel(grpRom);
        lblGameTitle->setObjectName(QString::fromUtf8("lblGameTitle"));

        gridLayout_2->addWidget(lblGameTitle, 0, 1, 1, 1);

        label_2 = new QLabel(grpRom);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lblPlatform = new QLabel(grpRom);
        lblPlatform->setObjectName(QString::fromUtf8("lblPlatform"));

        gridLayout_2->addWidget(lblPlatform, 1, 1, 1, 1);

        label_3 = new QLabel(grpRom);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        lblPlayers = new QLabel(grpRom);
        lblPlayers->setObjectName(QString::fromUtf8("lblPlayers"));

        gridLayout_2->addWidget(lblPlayers, 2, 1, 1, 1);

        label_4 = new QLabel(grpRom);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        lblReleaseDate = new QLabel(grpRom);
        lblReleaseDate->setObjectName(QString::fromUtf8("lblReleaseDate"));

        gridLayout_2->addWidget(lblReleaseDate, 3, 1, 1, 1);

        label_5 = new QLabel(grpRom);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        lblPublisher = new QLabel(grpRom);
        lblPublisher->setObjectName(QString::fromUtf8("lblPublisher"));

        gridLayout_2->addWidget(lblPublisher, 4, 1, 1, 1);

        label_6 = new QLabel(grpRom);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 5, 0, 1, 1);

        lblDeveloper = new QLabel(grpRom);
        lblDeveloper->setObjectName(QString::fromUtf8("lblDeveloper"));

        gridLayout_2->addWidget(lblDeveloper, 5, 1, 1, 1);

        splitter->addWidget(grpRom);

        gridLayout_3->addWidget(splitter, 2, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cmdScreenshots = new QPushButton(TheGamesDB);
        cmdScreenshots->setObjectName(QString::fromUtf8("cmdScreenshots"));

        gridLayout->addWidget(cmdScreenshots, 0, 0, 1, 1);

        cmdBoxart = new QPushButton(TheGamesDB);
        cmdBoxart->setObjectName(QString::fromUtf8("cmdBoxart"));

        gridLayout->addWidget(cmdBoxart, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 3, 0, 1, 1);

        lblOverview = new QLabel(TheGamesDB);
        lblOverview->setObjectName(QString::fromUtf8("lblOverview"));
        sizePolicy2.setHeightForWidth(lblOverview->sizePolicy().hasHeightForWidth());
        lblOverview->setSizePolicy(sizePolicy2);
        lblOverview->setScaledContents(false);
        lblOverview->setAlignment(Qt::AlignCenter);
        lblOverview->setWordWrap(true);

        gridLayout_3->addWidget(lblOverview, 4, 0, 1, 1);

        lblInfo = new QLabel(TheGamesDB);
        lblInfo->setObjectName(QString::fromUtf8("lblInfo"));

        gridLayout_3->addWidget(lblInfo, 5, 0, 1, 1);

        cmdCreateStuffPack = new QPushButton(TheGamesDB);
        cmdCreateStuffPack->setObjectName(QString::fromUtf8("cmdCreateStuffPack"));

        gridLayout_3->addWidget(cmdCreateStuffPack, 6, 0, 1, 1);


        retranslateUi(TheGamesDB);

        QMetaObject::connectSlotsByName(TheGamesDB);
    } // setupUi

    void retranslateUi(QDialog *TheGamesDB)
    {
        TheGamesDB->setWindowTitle(QApplication::translate("TheGamesDB", "Dialog", nullptr));
        lblStuffpack->setText(QApplication::translate("TheGamesDB", "TextLabel", nullptr));
        cmdSearch->setText(QApplication::translate("TheGamesDB", "suchen", nullptr));
        grpRom->setTitle(QApplication::translate("TheGamesDB", "Image informations", nullptr));
        label->setText(QApplication::translate("TheGamesDB", "Titel:", nullptr));
        lblGameTitle->setText(QApplication::translate("TheGamesDB", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("TheGamesDB", "Platform:", nullptr));
        lblPlatform->setText(QApplication::translate("TheGamesDB", "TextLabel", nullptr));
        label_3->setText(QApplication::translate("TheGamesDB", "Players:", nullptr));
        lblPlayers->setText(QApplication::translate("TheGamesDB", "TextLabel", nullptr));
        label_4->setText(QApplication::translate("TheGamesDB", "Release:", nullptr));
        lblReleaseDate->setText(QApplication::translate("TheGamesDB", "TextLabel", nullptr));
        label_5->setText(QApplication::translate("TheGamesDB", "Publisher:", nullptr));
        lblPublisher->setText(QApplication::translate("TheGamesDB", "TextLabel", nullptr));
        label_6->setText(QApplication::translate("TheGamesDB", "Developer:", nullptr));
        lblDeveloper->setText(QApplication::translate("TheGamesDB", "TextLabel", nullptr));
        cmdScreenshots->setText(QApplication::translate("TheGamesDB", "Screenshots", nullptr));
        cmdBoxart->setText(QApplication::translate("TheGamesDB", "Boxart", nullptr));
        lblOverview->setText(QApplication::translate("TheGamesDB", "Overview", nullptr));
        lblInfo->setText(QApplication::translate("TheGamesDB", "Info", nullptr));
        cmdCreateStuffPack->setText(QApplication::translate("TheGamesDB", "create stuff pack file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TheGamesDB: public Ui_TheGamesDB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THEGAMESDB_H
