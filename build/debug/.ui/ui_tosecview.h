/********************************************************************************
** Form generated from reading UI file 'tosecview.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOSECVIEW_H
#define UI_TOSECVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TosecView
{
public:

    void setupUi(QWidget *TosecView)
    {
        if (TosecView->objectName().isEmpty())
            TosecView->setObjectName(QString::fromUtf8("TosecView"));
        TosecView->resize(392, 118);

        retranslateUi(TosecView);

        QMetaObject::connectSlotsByName(TosecView);
    } // setupUi

    void retranslateUi(QWidget *TosecView)
    {
        TosecView->setWindowTitle(QApplication::translate("TosecView", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TosecView: public Ui_TosecView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOSECVIEW_H
