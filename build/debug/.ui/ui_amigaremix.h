/********************************************************************************
** Form generated from reading UI file 'amigaremix.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AMIGAREMIX_H
#define UI_AMIGAREMIX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>

QT_BEGIN_NAMESPACE

class Ui_AmigaRemix
{
public:
    QGridLayout *gridLayout;
    QScrollBar *horizontalScrollBar;
    QHBoxLayout *horizontalLayout;
    QLabel *lblPage;
    QLabel *lblSort;
    QPushButton *cmdSortByDate;
    QPushButton *cmdSortByRating;

    void setupUi(QGroupBox *AmigaRemix)
    {
        if (AmigaRemix->objectName().isEmpty())
            AmigaRemix->setObjectName(QString::fromUtf8("AmigaRemix"));
        AmigaRemix->resize(252, 69);
        AmigaRemix->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(AmigaRemix);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalScrollBar = new QScrollBar(AmigaRemix);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setMinimum(1);
        horizontalScrollBar->setMaximum(30);
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalScrollBar, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblPage = new QLabel(AmigaRemix);
        lblPage->setObjectName(QString::fromUtf8("lblPage"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblPage->sizePolicy().hasHeightForWidth());
        lblPage->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lblPage);

        lblSort = new QLabel(AmigaRemix);
        lblSort->setObjectName(QString::fromUtf8("lblSort"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblSort->sizePolicy().hasHeightForWidth());
        lblSort->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lblSort);

        cmdSortByDate = new QPushButton(AmigaRemix);
        cmdSortByDate->setObjectName(QString::fromUtf8("cmdSortByDate"));

        horizontalLayout->addWidget(cmdSortByDate);

        cmdSortByRating = new QPushButton(AmigaRemix);
        cmdSortByRating->setObjectName(QString::fromUtf8("cmdSortByRating"));

        horizontalLayout->addWidget(cmdSortByRating);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(AmigaRemix);

        QMetaObject::connectSlotsByName(AmigaRemix);
    } // setupUi

    void retranslateUi(QGroupBox *AmigaRemix)
    {
        AmigaRemix->setWindowTitle(QApplication::translate("AmigaRemix", "AmigaRemix", nullptr));
        AmigaRemix->setTitle(QString());
        lblPage->setText(QApplication::translate("AmigaRemix", "Page: 1", nullptr));
        lblSort->setText(QApplication::translate("AmigaRemix", "sort:", nullptr));
        cmdSortByDate->setText(QApplication::translate("AmigaRemix", "by date", nullptr));
        cmdSortByRating->setText(QApplication::translate("AmigaRemix", "by rating", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AmigaRemix: public Ui_AmigaRemix {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AMIGAREMIX_H
