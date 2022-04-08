/********************************************************************************
** Form generated from reading UI file 'sidplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDPLAYER_H
#define UI_SIDPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_SidPlayer
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *cmdHVSC;
    QPushButton *cmdProjectAY;
    QPushButton *pushButton;
    QTreeView *treeView;

    void setupUi(QGroupBox *SidPlayer)
    {
        if (SidPlayer->objectName().isEmpty())
            SidPlayer->setObjectName(QString::fromUtf8("SidPlayer"));
        SidPlayer->resize(352, 165);
        SidPlayer->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        SidPlayer->setFlat(false);
        SidPlayer->setCheckable(false);
        gridLayout = new QGridLayout(SidPlayer);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cmdHVSC = new QPushButton(SidPlayer);
        cmdHVSC->setObjectName(QString::fromUtf8("cmdHVSC"));
        cmdHVSC->setIconSize(QSize(150, 16));

        horizontalLayout->addWidget(cmdHVSC);

        cmdProjectAY = new QPushButton(SidPlayer);
        cmdProjectAY->setObjectName(QString::fromUtf8("cmdProjectAY"));
        cmdProjectAY->setIconSize(QSize(150, 16));

        horizontalLayout->addWidget(cmdProjectAY);

        pushButton = new QPushButton(SidPlayer);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        treeView = new QTreeView(SidPlayer);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        gridLayout->addWidget(treeView, 1, 0, 1, 1);


        retranslateUi(SidPlayer);

        QMetaObject::connectSlotsByName(SidPlayer);
    } // setupUi

    void retranslateUi(QGroupBox *SidPlayer)
    {
        SidPlayer->setWindowTitle(QApplication::translate("SidPlayer", "GroupBox", nullptr));
        SidPlayer->setTitle(QString());
        cmdHVSC->setText(QApplication::translate("SidPlayer", "HVSC", nullptr));
        cmdProjectAY->setText(QApplication::translate("SidPlayer", "ProjectAY", nullptr));
        pushButton->setText(QApplication::translate("SidPlayer", "CGSC", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SidPlayer: public Ui_SidPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDPLAYER_H
