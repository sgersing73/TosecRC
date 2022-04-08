/********************************************************************************
** Form generated from reading UI file 'aeskeygenerator.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AESKEYGENERATOR_H
#define UI_AESKEYGENERATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_AesKeyGenerator
{
public:
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit;
    QGridLayout *gridLayout;
    QSpinBox *spinBox;
    QLabel *lblLength;
    QPushButton *cmdGenerate;
    QPushButton *cmdSetAsKey;
    QCheckBox *chkSoZe;

    void setupUi(QDialog *AesKeyGenerator)
    {
        if (AesKeyGenerator->objectName().isEmpty())
            AesKeyGenerator->setObjectName(QString::fromUtf8("AesKeyGenerator"));
        AesKeyGenerator->resize(414, 141);
        gridLayout_2 = new QGridLayout(AesKeyGenerator);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        textEdit = new QTextEdit(AesKeyGenerator);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier"));
        font.setPointSize(9);
        textEdit->setFont(font);
        textEdit->setReadOnly(true);

        gridLayout_2->addWidget(textEdit, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinBox = new QSpinBox(AesKeyGenerator);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(128);
        spinBox->setValue(128);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        lblLength = new QLabel(AesKeyGenerator);
        lblLength->setObjectName(QString::fromUtf8("lblLength"));

        gridLayout->addWidget(lblLength, 0, 0, 1, 1);

        cmdGenerate = new QPushButton(AesKeyGenerator);
        cmdGenerate->setObjectName(QString::fromUtf8("cmdGenerate"));

        gridLayout->addWidget(cmdGenerate, 0, 3, 1, 1);

        cmdSetAsKey = new QPushButton(AesKeyGenerator);
        cmdSetAsKey->setObjectName(QString::fromUtf8("cmdSetAsKey"));

        gridLayout->addWidget(cmdSetAsKey, 0, 4, 1, 1);

        chkSoZe = new QCheckBox(AesKeyGenerator);
        chkSoZe->setObjectName(QString::fromUtf8("chkSoZe"));

        gridLayout->addWidget(chkSoZe, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);


        retranslateUi(AesKeyGenerator);

        QMetaObject::connectSlotsByName(AesKeyGenerator);
    } // setupUi

    void retranslateUi(QDialog *AesKeyGenerator)
    {
        AesKeyGenerator->setWindowTitle(QApplication::translate("AesKeyGenerator", "AES Key Generator", nullptr));
        lblLength->setText(QApplication::translate("AesKeyGenerator", "l\303\244nge:", nullptr));
        cmdGenerate->setText(QApplication::translate("AesKeyGenerator", "generate", nullptr));
        cmdSetAsKey->setText(QApplication::translate("AesKeyGenerator", "set AES key", nullptr));
        chkSoZe->setText(QApplication::translate("AesKeyGenerator", "Sonderzeichen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AesKeyGenerator: public Ui_AesKeyGenerator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AESKEYGENERATOR_H
