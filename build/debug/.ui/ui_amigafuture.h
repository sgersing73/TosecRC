/********************************************************************************
** Form generated from reading UI file 'amigafuture.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AMIGAFUTURE_H
#define UI_AMIGAFUTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AmigaFuture
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QTreeWidget *treeMagazine;
    QScrollArea *scrDisplay;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *lblDisplay;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lblScalefactor;
    QSpinBox *spinScaleFactor;
    QSpacerItem *horizontalSpacer;
    QPushButton *beenden;

    void setupUi(QDialog *AmigaFuture)
    {
        if (AmigaFuture->objectName().isEmpty())
            AmigaFuture->setObjectName(QString::fromUtf8("AmigaFuture"));
        AmigaFuture->resize(349, 229);
        gridLayout = new QGridLayout(AmigaFuture);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(AmigaFuture);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        treeMagazine = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeMagazine->setHeaderItem(__qtreewidgetitem);
        treeMagazine->setObjectName(QString::fromUtf8("treeMagazine"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeMagazine->sizePolicy().hasHeightForWidth());
        treeMagazine->setSizePolicy(sizePolicy);
        splitter->addWidget(treeMagazine);
        scrDisplay = new QScrollArea(splitter);
        scrDisplay->setObjectName(QString::fromUtf8("scrDisplay"));
        scrDisplay->setWidgetResizable(true);
        scrDisplay->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 69, 178));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lblDisplay = new QLabel(scrollAreaWidgetContents);
        lblDisplay->setObjectName(QString::fromUtf8("lblDisplay"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblDisplay->sizePolicy().hasHeightForWidth());
        lblDisplay->setSizePolicy(sizePolicy1);
        lblDisplay->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        lblDisplay->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblDisplay, 0, 0, 1, 1);

        scrDisplay->setWidget(scrollAreaWidgetContents);
        splitter->addWidget(scrDisplay);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lblScalefactor = new QLabel(AmigaFuture);
        lblScalefactor->setObjectName(QString::fromUtf8("lblScalefactor"));
        lblScalefactor->setScaledContents(true);

        horizontalLayout->addWidget(lblScalefactor);

        spinScaleFactor = new QSpinBox(AmigaFuture);
        spinScaleFactor->setObjectName(QString::fromUtf8("spinScaleFactor"));
        spinScaleFactor->setMinimum(10);
        spinScaleFactor->setMaximum(500);
        spinScaleFactor->setSingleStep(10);
        spinScaleFactor->setValue(40);

        horizontalLayout->addWidget(spinScaleFactor);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        beenden = new QPushButton(AmigaFuture);
        beenden->setObjectName(QString::fromUtf8("beenden"));

        horizontalLayout->addWidget(beenden);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(AmigaFuture);

        QMetaObject::connectSlotsByName(AmigaFuture);
    } // setupUi

    void retranslateUi(QDialog *AmigaFuture)
    {
        AmigaFuture->setWindowTitle(QApplication::translate("AmigaFuture", "Amiga Future", nullptr));
        lblDisplay->setText(QString());
        lblScalefactor->setText(QApplication::translate("AmigaFuture", "Skalierfaktor:", nullptr));
        beenden->setText(QApplication::translate("AmigaFuture", "beenden", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AmigaFuture: public Ui_AmigaFuture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AMIGAFUTURE_H
