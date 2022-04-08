/********************************************************************************
** Form generated from reading UI file 'systemeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMEDITOR_H
#define UI_SYSTEMEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SystemEditor
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdCancel;
    QPushButton *cmdExit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblAnzeige;
    QComboBox *comboBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QLabel *lblExe;
    QLineEdit *edtExe;
    QLabel *lblExeParam;
    QLineEdit *edtExeParam;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *edtPCB;
    QLabel *lblThumb;
    QLabel *lblWiki;
    QLabel *lblPCB;
    QLineEdit *edtWiki;
    QLineEdit *edtThumb;
    QLineEdit *edtYoutube;
    QLabel *lblYoutube;
    QLineEdit *edtLogo;
    QLabel *lblPortrait;
    QLineEdit *edtPortrait;

    void setupUi(QDialog *SystemEditor)
    {
        if (SystemEditor->objectName().isEmpty())
            SystemEditor->setObjectName(QString::fromUtf8("SystemEditor"));
        SystemEditor->resize(564, 378);
        gridLayout = new QGridLayout(SystemEditor);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdCancel = new QPushButton(SystemEditor);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout->addWidget(cmdCancel);

        cmdExit = new QPushButton(SystemEditor);
        cmdExit->setObjectName(QString::fromUtf8("cmdExit"));

        horizontalLayout->addWidget(cmdExit);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        groupBox = new QGroupBox(SystemEditor);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblAnzeige = new QLabel(groupBox);
        lblAnzeige->setObjectName(QString::fromUtf8("lblAnzeige"));

        horizontalLayout_2->addWidget(lblAnzeige);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lblExe = new QLabel(groupBox_2);
        lblExe->setObjectName(QString::fromUtf8("lblExe"));

        gridLayout_4->addWidget(lblExe, 0, 0, 1, 1);

        edtExe = new QLineEdit(groupBox_2);
        edtExe->setObjectName(QString::fromUtf8("edtExe"));

        gridLayout_4->addWidget(edtExe, 0, 1, 1, 1);

        lblExeParam = new QLabel(groupBox_2);
        lblExeParam->setObjectName(QString::fromUtf8("lblExeParam"));

        gridLayout_4->addWidget(lblExeParam, 1, 0, 1, 1);

        edtExeParam = new QLineEdit(groupBox_2);
        edtExeParam->setObjectName(QString::fromUtf8("edtExeParam"));

        gridLayout_4->addWidget(edtExeParam, 1, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        edtPCB = new QLineEdit(groupBox_3);
        edtPCB->setObjectName(QString::fromUtf8("edtPCB"));

        gridLayout_2->addWidget(edtPCB, 3, 3, 1, 1);

        lblThumb = new QLabel(groupBox_3);
        lblThumb->setObjectName(QString::fromUtf8("lblThumb"));

        gridLayout_2->addWidget(lblThumb, 2, 1, 1, 1);

        lblWiki = new QLabel(groupBox_3);
        lblWiki->setObjectName(QString::fromUtf8("lblWiki"));

        gridLayout_2->addWidget(lblWiki, 1, 1, 1, 1);

        lblPCB = new QLabel(groupBox_3);
        lblPCB->setObjectName(QString::fromUtf8("lblPCB"));

        gridLayout_2->addWidget(lblPCB, 3, 1, 1, 1);

        edtWiki = new QLineEdit(groupBox_3);
        edtWiki->setObjectName(QString::fromUtf8("edtWiki"));

        gridLayout_2->addWidget(edtWiki, 1, 3, 1, 1);

        edtThumb = new QLineEdit(groupBox_3);
        edtThumb->setObjectName(QString::fromUtf8("edtThumb"));

        gridLayout_2->addWidget(edtThumb, 2, 3, 1, 1);

        edtYoutube = new QLineEdit(groupBox_3);
        edtYoutube->setObjectName(QString::fromUtf8("edtYoutube"));

        gridLayout_2->addWidget(edtYoutube, 5, 3, 1, 1);

        lblYoutube = new QLabel(groupBox_3);
        lblYoutube->setObjectName(QString::fromUtf8("lblYoutube"));

        gridLayout_2->addWidget(lblYoutube, 5, 1, 1, 1);

        edtLogo = new QLineEdit(groupBox_3);
        edtLogo->setObjectName(QString::fromUtf8("edtLogo"));

        gridLayout_2->addWidget(edtLogo, 0, 3, 1, 1);

        lblPortrait = new QLabel(groupBox_3);
        lblPortrait->setObjectName(QString::fromUtf8("lblPortrait"));

        gridLayout_2->addWidget(lblPortrait, 4, 1, 1, 1);

        edtPortrait = new QLineEdit(groupBox_3);
        edtPortrait->setObjectName(QString::fromUtf8("edtPortrait"));

        gridLayout_2->addWidget(edtPortrait, 4, 3, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 2, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(SystemEditor);

        QMetaObject::connectSlotsByName(SystemEditor);
    } // setupUi

    void retranslateUi(QDialog *SystemEditor)
    {
        SystemEditor->setWindowTitle(QApplication::translate("SystemEditor", "Dialog", nullptr));
        cmdCancel->setText(QApplication::translate("SystemEditor", "Abbrechen", nullptr));
        cmdExit->setText(QApplication::translate("SystemEditor", "Beenden", nullptr));
        groupBox->setTitle(QApplication::translate("SystemEditor", "Einstellungen", nullptr));
        lblAnzeige->setText(QApplication::translate("SystemEditor", "Anzeige:", nullptr));
        groupBox_2->setTitle(QApplication::translate("SystemEditor", "Emulator", nullptr));
        lblExe->setText(QApplication::translate("SystemEditor", "Emulator:", nullptr));
        lblExeParam->setText(QApplication::translate("SystemEditor", "Parameter:", nullptr));
        groupBox_3->setTitle(QApplication::translate("SystemEditor", "Internet Links", nullptr));
        label->setText(QApplication::translate("SystemEditor", "Logo:", nullptr));
        lblThumb->setText(QApplication::translate("SystemEditor", "Thumbnail:", nullptr));
        lblWiki->setText(QApplication::translate("SystemEditor", "Wiki:", nullptr));
        lblPCB->setText(QApplication::translate("SystemEditor", "PCB:", nullptr));
        lblYoutube->setText(QApplication::translate("SystemEditor", "Youtube", nullptr));
        lblPortrait->setText(QApplication::translate("SystemEditor", "Portrait:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SystemEditor: public Ui_SystemEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMEDITOR_H
