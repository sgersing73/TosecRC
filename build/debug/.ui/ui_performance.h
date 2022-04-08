/********************************************************************************
** Form generated from reading UI file 'performance.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERFORMANCE_H
#define UI_PERFORMANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>

QT_BEGIN_NAMESPACE

class Ui_Performance
{
public:

    void setupUi(QGroupBox *Performance)
    {
        if (Performance->objectName().isEmpty())
            Performance->setObjectName(QString::fromUtf8("Performance"));
        Performance->resize(344, 107);

        retranslateUi(Performance);

        QMetaObject::connectSlotsByName(Performance);
    } // setupUi

    void retranslateUi(QGroupBox *Performance)
    {
        Performance->setWindowTitle(QApplication::translate("Performance", "GroupBox", nullptr));
        Performance->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class Performance: public Ui_Performance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERFORMANCE_H
