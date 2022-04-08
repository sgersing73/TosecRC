/********************************************************************************
** Form generated from reading UI file 'themodarchive.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THEMODARCHIVE_H
#define UI_THEMODARCHIVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>

QT_BEGIN_NAMESPACE

class Ui_TheModArchive
{
public:
    QGridLayout *gridLayout;
    QScrollBar *horizontalScrollBar;
    QHBoxLayout *horizontalLayout;
    QLabel *lblPage;
    QLabel *lblSort;
    QPushButton *cmdSortByDate;
    QPushButton *cmdSortByRating;

    void setupUi(QGroupBox *TheModArchive)
    {
        if (TheModArchive->objectName().isEmpty())
            TheModArchive->setObjectName(QString::fromUtf8("TheModArchive"));
        TheModArchive->resize(252, 69);
        gridLayout = new QGridLayout(TheModArchive);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalScrollBar = new QScrollBar(TheModArchive);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setMinimum(1);
        horizontalScrollBar->setMaximum(30);
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalScrollBar, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblPage = new QLabel(TheModArchive);
        lblPage->setObjectName(QString::fromUtf8("lblPage"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblPage->sizePolicy().hasHeightForWidth());
        lblPage->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lblPage);

        lblSort = new QLabel(TheModArchive);
        lblSort->setObjectName(QString::fromUtf8("lblSort"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblSort->sizePolicy().hasHeightForWidth());
        lblSort->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lblSort);

        cmdSortByDate = new QPushButton(TheModArchive);
        cmdSortByDate->setObjectName(QString::fromUtf8("cmdSortByDate"));

        horizontalLayout->addWidget(cmdSortByDate);

        cmdSortByRating = new QPushButton(TheModArchive);
        cmdSortByRating->setObjectName(QString::fromUtf8("cmdSortByRating"));

        horizontalLayout->addWidget(cmdSortByRating);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(TheModArchive);

        QMetaObject::connectSlotsByName(TheModArchive);
    } // setupUi

    void retranslateUi(QGroupBox *TheModArchive)
    {
        TheModArchive->setWindowTitle(QApplication::translate("TheModArchive", "GroupBox", nullptr));
        TheModArchive->setTitle(QString());
        lblPage->setText(QApplication::translate("TheModArchive", "Page: 1", nullptr));
        lblSort->setText(QApplication::translate("TheModArchive", "sort:", nullptr));
        cmdSortByDate->setText(QApplication::translate("TheModArchive", "by date", nullptr));
        cmdSortByRating->setText(QApplication::translate("TheModArchive", "by rating", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TheModArchive: public Ui_TheModArchive {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THEMODARCHIVE_H
