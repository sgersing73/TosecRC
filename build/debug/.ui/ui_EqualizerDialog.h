/********************************************************************************
** Form generated from reading UI file 'EqualizerDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQUALIZERDIALOG_H
#define UI_EQUALIZERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EqualizerDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *toggleEqualizer;
    QLabel *labelPreset;
    QComboBox *presetComboBox;
    QGridLayout *gridLayout;
    QSlider *preamp;
    QSlider *firstBand;
    QSlider *thirdBand;
    QSlider *seventhBand;
    QSlider *tenthBand;
    QLabel *label_preamp;
    QSlider *eighthBand;
    QSlider *sixthBand;
    QSlider *fifthBand;
    QSlider *fourthBand;
    QSlider *ninethBand;
    QSlider *secondBand;
    QLabel *preampLabel;
    QLabel *firstBandLabel;
    QLabel *label_band_1;
    QLabel *label_band_2;
    QLabel *label_band_3;
    QLabel *label_band_4;
    QLabel *label_band_5;
    QLabel *label_band_6;
    QLabel *label_band_7;
    QLabel *label_band_8;
    QLabel *label_band_9;
    QLabel *label_band_10;
    QLabel *secondBandLabel;
    QLabel *thirdBandLabel;
    QLabel *fourthBandLabel;
    QLabel *fifthBandLabel;
    QLabel *sixthBandLabel;
    QLabel *seventhBandLabel;
    QLabel *eighthBandLabel;
    QLabel *ninethBandLabel;
    QLabel *tenthBandLabel;

    void setupUi(QDialog *EqualizerDialog)
    {
        if (EqualizerDialog->objectName().isEmpty())
            EqualizerDialog->setObjectName(QString::fromUtf8("EqualizerDialog"));
        EqualizerDialog->resize(639, 304);
        verticalLayout_2 = new QVBoxLayout(EqualizerDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toggleEqualizer = new QCheckBox(EqualizerDialog);
        toggleEqualizer->setObjectName(QString::fromUtf8("toggleEqualizer"));
        toggleEqualizer->setChecked(true);

        horizontalLayout->addWidget(toggleEqualizer);

        labelPreset = new QLabel(EqualizerDialog);
        labelPreset->setObjectName(QString::fromUtf8("labelPreset"));

        horizontalLayout->addWidget(labelPreset);

        presetComboBox = new QComboBox(EqualizerDialog);
        presetComboBox->setObjectName(QString::fromUtf8("presetComboBox"));
        presetComboBox->setEnabled(false);

        horizontalLayout->addWidget(presetComboBox);


        verticalLayout_2->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        preamp = new QSlider(EqualizerDialog);
        preamp->setObjectName(QString::fromUtf8("preamp"));
        preamp->setEnabled(false);
        preamp->setMinimum(-20);
        preamp->setMaximum(20);
        preamp->setOrientation(Qt::Vertical);

        gridLayout->addWidget(preamp, 0, 0, 1, 1);

        firstBand = new QSlider(EqualizerDialog);
        firstBand->setObjectName(QString::fromUtf8("firstBand"));
        firstBand->setEnabled(false);
        firstBand->setMinimum(-20);
        firstBand->setMaximum(20);
        firstBand->setOrientation(Qt::Vertical);

        gridLayout->addWidget(firstBand, 0, 1, 1, 1);

        thirdBand = new QSlider(EqualizerDialog);
        thirdBand->setObjectName(QString::fromUtf8("thirdBand"));
        thirdBand->setEnabled(false);
        thirdBand->setMinimum(-20);
        thirdBand->setMaximum(20);
        thirdBand->setOrientation(Qt::Vertical);

        gridLayout->addWidget(thirdBand, 0, 3, 1, 1);

        seventhBand = new QSlider(EqualizerDialog);
        seventhBand->setObjectName(QString::fromUtf8("seventhBand"));
        seventhBand->setEnabled(false);
        seventhBand->setMinimum(-20);
        seventhBand->setMaximum(20);
        seventhBand->setOrientation(Qt::Vertical);

        gridLayout->addWidget(seventhBand, 0, 7, 1, 1);

        tenthBand = new QSlider(EqualizerDialog);
        tenthBand->setObjectName(QString::fromUtf8("tenthBand"));
        tenthBand->setEnabled(false);
        tenthBand->setMinimum(-20);
        tenthBand->setMaximum(20);
        tenthBand->setOrientation(Qt::Vertical);

        gridLayout->addWidget(tenthBand, 0, 10, 1, 1);

        label_preamp = new QLabel(EqualizerDialog);
        label_preamp->setObjectName(QString::fromUtf8("label_preamp"));
        QFont font;
        font.setPointSize(8);
        label_preamp->setFont(font);
        label_preamp->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_preamp, 1, 0, 1, 1);

        eighthBand = new QSlider(EqualizerDialog);
        eighthBand->setObjectName(QString::fromUtf8("eighthBand"));
        eighthBand->setEnabled(false);
        eighthBand->setMinimum(-20);
        eighthBand->setMaximum(20);
        eighthBand->setOrientation(Qt::Vertical);

        gridLayout->addWidget(eighthBand, 0, 8, 1, 1);

        sixthBand = new QSlider(EqualizerDialog);
        sixthBand->setObjectName(QString::fromUtf8("sixthBand"));
        sixthBand->setEnabled(false);
        sixthBand->setMinimum(-20);
        sixthBand->setMaximum(20);
        sixthBand->setOrientation(Qt::Vertical);

        gridLayout->addWidget(sixthBand, 0, 6, 1, 1);

        fifthBand = new QSlider(EqualizerDialog);
        fifthBand->setObjectName(QString::fromUtf8("fifthBand"));
        fifthBand->setEnabled(false);
        fifthBand->setMinimum(-20);
        fifthBand->setMaximum(20);
        fifthBand->setOrientation(Qt::Vertical);

        gridLayout->addWidget(fifthBand, 0, 5, 1, 1);

        fourthBand = new QSlider(EqualizerDialog);
        fourthBand->setObjectName(QString::fromUtf8("fourthBand"));
        fourthBand->setEnabled(false);
        fourthBand->setMinimum(-20);
        fourthBand->setMaximum(20);
        fourthBand->setOrientation(Qt::Vertical);

        gridLayout->addWidget(fourthBand, 0, 4, 1, 1);

        ninethBand = new QSlider(EqualizerDialog);
        ninethBand->setObjectName(QString::fromUtf8("ninethBand"));
        ninethBand->setEnabled(false);
        ninethBand->setMinimum(-20);
        ninethBand->setMaximum(20);
        ninethBand->setOrientation(Qt::Vertical);

        gridLayout->addWidget(ninethBand, 0, 9, 1, 1);

        secondBand = new QSlider(EqualizerDialog);
        secondBand->setObjectName(QString::fromUtf8("secondBand"));
        secondBand->setEnabled(false);
        secondBand->setMinimum(-20);
        secondBand->setMaximum(20);
        secondBand->setOrientation(Qt::Vertical);

        gridLayout->addWidget(secondBand, 0, 2, 1, 1);

        preampLabel = new QLabel(EqualizerDialog);
        preampLabel->setObjectName(QString::fromUtf8("preampLabel"));
        preampLabel->setFont(font);
        preampLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(preampLabel, 2, 0, 1, 1);

        firstBandLabel = new QLabel(EqualizerDialog);
        firstBandLabel->setObjectName(QString::fromUtf8("firstBandLabel"));
        firstBandLabel->setFont(font);
        firstBandLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(firstBandLabel, 2, 1, 1, 1);

        label_band_1 = new QLabel(EqualizerDialog);
        label_band_1->setObjectName(QString::fromUtf8("label_band_1"));
        label_band_1->setFont(font);
        label_band_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_band_1, 1, 1, 1, 1);

        label_band_2 = new QLabel(EqualizerDialog);
        label_band_2->setObjectName(QString::fromUtf8("label_band_2"));
        label_band_2->setFont(font);
        label_band_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_band_2, 1, 2, 1, 1);

        label_band_3 = new QLabel(EqualizerDialog);
        label_band_3->setObjectName(QString::fromUtf8("label_band_3"));
        label_band_3->setFont(font);
        label_band_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_band_3, 1, 3, 1, 1);

        label_band_4 = new QLabel(EqualizerDialog);
        label_band_4->setObjectName(QString::fromUtf8("label_band_4"));
        label_band_4->setFont(font);
        label_band_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_band_4, 1, 4, 1, 1);

        label_band_5 = new QLabel(EqualizerDialog);
        label_band_5->setObjectName(QString::fromUtf8("label_band_5"));
        label_band_5->setFont(font);
        label_band_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_band_5, 1, 5, 1, 1);

        label_band_6 = new QLabel(EqualizerDialog);
        label_band_6->setObjectName(QString::fromUtf8("label_band_6"));
        label_band_6->setFont(font);
        label_band_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_band_6, 1, 6, 1, 1);

        label_band_7 = new QLabel(EqualizerDialog);
        label_band_7->setObjectName(QString::fromUtf8("label_band_7"));
        label_band_7->setFont(font);
        label_band_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_band_7, 1, 7, 1, 1);

        label_band_8 = new QLabel(EqualizerDialog);
        label_band_8->setObjectName(QString::fromUtf8("label_band_8"));
        label_band_8->setFont(font);
        label_band_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_band_8, 1, 8, 1, 1);

        label_band_9 = new QLabel(EqualizerDialog);
        label_band_9->setObjectName(QString::fromUtf8("label_band_9"));
        label_band_9->setFont(font);
        label_band_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_band_9, 1, 9, 1, 1);

        label_band_10 = new QLabel(EqualizerDialog);
        label_band_10->setObjectName(QString::fromUtf8("label_band_10"));
        label_band_10->setFont(font);
        label_band_10->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_band_10, 1, 10, 1, 1);

        secondBandLabel = new QLabel(EqualizerDialog);
        secondBandLabel->setObjectName(QString::fromUtf8("secondBandLabel"));
        secondBandLabel->setFont(font);
        secondBandLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(secondBandLabel, 2, 2, 1, 1);

        thirdBandLabel = new QLabel(EqualizerDialog);
        thirdBandLabel->setObjectName(QString::fromUtf8("thirdBandLabel"));
        thirdBandLabel->setFont(font);
        thirdBandLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(thirdBandLabel, 2, 3, 1, 1);

        fourthBandLabel = new QLabel(EqualizerDialog);
        fourthBandLabel->setObjectName(QString::fromUtf8("fourthBandLabel"));
        fourthBandLabel->setFont(font);
        fourthBandLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(fourthBandLabel, 2, 4, 1, 1);

        fifthBandLabel = new QLabel(EqualizerDialog);
        fifthBandLabel->setObjectName(QString::fromUtf8("fifthBandLabel"));
        fifthBandLabel->setFont(font);
        fifthBandLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(fifthBandLabel, 2, 5, 1, 1);

        sixthBandLabel = new QLabel(EqualizerDialog);
        sixthBandLabel->setObjectName(QString::fromUtf8("sixthBandLabel"));
        sixthBandLabel->setFont(font);
        sixthBandLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(sixthBandLabel, 2, 6, 1, 1);

        seventhBandLabel = new QLabel(EqualizerDialog);
        seventhBandLabel->setObjectName(QString::fromUtf8("seventhBandLabel"));
        seventhBandLabel->setFont(font);
        seventhBandLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(seventhBandLabel, 2, 7, 1, 1);

        eighthBandLabel = new QLabel(EqualizerDialog);
        eighthBandLabel->setObjectName(QString::fromUtf8("eighthBandLabel"));
        eighthBandLabel->setFont(font);
        eighthBandLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(eighthBandLabel, 2, 8, 1, 1);

        ninethBandLabel = new QLabel(EqualizerDialog);
        ninethBandLabel->setObjectName(QString::fromUtf8("ninethBandLabel"));
        ninethBandLabel->setFont(font);
        ninethBandLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(ninethBandLabel, 2, 9, 1, 1);

        tenthBandLabel = new QLabel(EqualizerDialog);
        tenthBandLabel->setObjectName(QString::fromUtf8("tenthBandLabel"));
        tenthBandLabel->setFont(font);
        tenthBandLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(tenthBandLabel, 2, 10, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        retranslateUi(EqualizerDialog);

        QMetaObject::connectSlotsByName(EqualizerDialog);
    } // setupUi

    void retranslateUi(QDialog *EqualizerDialog)
    {
        EqualizerDialog->setWindowTitle(QApplication::translate("EqualizerDialog", "Equalizer", nullptr));
        toggleEqualizer->setText(QApplication::translate("EqualizerDialog", "Activate", nullptr));
        labelPreset->setText(QApplication::translate("EqualizerDialog", "Preset", nullptr));
        label_preamp->setText(QApplication::translate("EqualizerDialog", "Preamp", nullptr));
        preampLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
        firstBandLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
        label_band_1->setText(QApplication::translate("EqualizerDialog", "60 Hz", nullptr));
        label_band_2->setText(QApplication::translate("EqualizerDialog", "170 Hz", nullptr));
        label_band_3->setText(QApplication::translate("EqualizerDialog", "310 Hz", nullptr));
        label_band_4->setText(QApplication::translate("EqualizerDialog", "600 Hz", nullptr));
        label_band_5->setText(QApplication::translate("EqualizerDialog", "1 KHz", nullptr));
        label_band_6->setText(QApplication::translate("EqualizerDialog", "3 KHz", nullptr));
        label_band_7->setText(QApplication::translate("EqualizerDialog", "6 KHz", nullptr));
        label_band_8->setText(QApplication::translate("EqualizerDialog", "12 KHz", nullptr));
        label_band_9->setText(QApplication::translate("EqualizerDialog", "14 KHz", nullptr));
        label_band_10->setText(QApplication::translate("EqualizerDialog", "16 KHz", nullptr));
        secondBandLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
        thirdBandLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
        fourthBandLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
        fifthBandLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
        sixthBandLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
        seventhBandLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
        eighthBandLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
        ninethBandLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
        tenthBandLabel->setText(QApplication::translate("EqualizerDialog", "0 dB", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EqualizerDialog: public Ui_EqualizerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUALIZERDIALOG_H
