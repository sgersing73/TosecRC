/********************************************************************************
** Form generated from reading UI file 'musik.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSIK_H
#define UI_MUSIK_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include "VLCQtWidgets/WidgetSeek.h"
#include "VLCQtWidgets/WidgetVideo.h"
#include "VLCQtWidgets/WidgetVolumeSlider.h"
#include "src/widgets/AudioSpectrum/audiospectrum.h"

QT_BEGIN_NAMESPACE

class Ui_Musik
{
public:
    QVBoxLayout *verticalLayout;
    VlcWidgetVideo *video;
    QListWidget *listTracks;
    AudioSpectrum *spectrum;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *chkRadio;
    VlcWidgetSeek *seek;
    QPushButton *cmdSave;
    QHBoxLayout *horizontalLayout;
    QPushButton *cmdEqualizer;
    QPushButton *cmdPrev;
    QPushButton *cmdStop;
    QPushButton *cmdPause;
    QPushButton *cmdPlay;
    QPushButton *cmdNext;
    VlcWidgetVolumeSlider *volume;

    void setupUi(QGroupBox *Musik)
    {
        if (Musik->objectName().isEmpty())
            Musik->setObjectName(QString::fromUtf8("Musik"));
        Musik->resize(326, 210);
        Musik->setFlat(false);
        Musik->setCheckable(false);
        verticalLayout = new QVBoxLayout(Musik);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        video = new VlcWidgetVideo(Musik);
        video->setObjectName(QString::fromUtf8("video"));
        video->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(video);

        listTracks = new QListWidget(Musik);
        listTracks->setObjectName(QString::fromUtf8("listTracks"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listTracks->sizePolicy().hasHeightForWidth());
        listTracks->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(listTracks);

        spectrum = new AudioSpectrum(Musik);
        spectrum->setObjectName(QString::fromUtf8("spectrum"));

        verticalLayout->addWidget(spectrum);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        chkRadio = new QCheckBox(Musik);
        chkRadio->setObjectName(QString::fromUtf8("chkRadio"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(chkRadio->sizePolicy().hasHeightForWidth());
        chkRadio->setSizePolicy(sizePolicy1);
        chkRadio->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8("images/player/blue/radio.ico"), QSize(), QIcon::Normal, QIcon::Off);
        chkRadio->setIcon(icon);

        horizontalLayout_2->addWidget(chkRadio);

        seek = new VlcWidgetSeek(Musik);
        seek->setObjectName(QString::fromUtf8("seek"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(seek->sizePolicy().hasHeightForWidth());
        seek->setSizePolicy(sizePolicy2);
        seek->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(seek);

        cmdSave = new QPushButton(Musik);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(cmdSave->sizePolicy().hasHeightForWidth());
        cmdSave->setSizePolicy(sizePolicy3);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSave->setIcon(icon1);

        horizontalLayout_2->addWidget(cmdSave);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cmdEqualizer = new QPushButton(Musik);
        cmdEqualizer->setObjectName(QString::fromUtf8("cmdEqualizer"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/player/blue/images/player/blue/equalizer.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdEqualizer->setIcon(icon2);
        cmdEqualizer->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(cmdEqualizer);

        cmdPrev = new QPushButton(Musik);
        cmdPrev->setObjectName(QString::fromUtf8("cmdPrev"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/player/blue/images/player/blue/backward.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdPrev->setIcon(icon3);

        horizontalLayout->addWidget(cmdPrev);

        cmdStop = new QPushButton(Musik);
        cmdStop->setObjectName(QString::fromUtf8("cmdStop"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/player/blue/images/player/blue/stop.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdStop->setIcon(icon4);

        horizontalLayout->addWidget(cmdStop);

        cmdPause = new QPushButton(Musik);
        cmdPause->setObjectName(QString::fromUtf8("cmdPause"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/player/blue/images/player/blue/pause.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdPause->setIcon(icon5);

        horizontalLayout->addWidget(cmdPause);

        cmdPlay = new QPushButton(Musik);
        cmdPlay->setObjectName(QString::fromUtf8("cmdPlay"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/player/blue/images/player/blue/play.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdPlay->setIcon(icon6);

        horizontalLayout->addWidget(cmdPlay);

        cmdNext = new QPushButton(Musik);
        cmdNext->setObjectName(QString::fromUtf8("cmdNext"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/player/blue/images/player/blue/forward.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdNext->setIcon(icon7);

        horizontalLayout->addWidget(cmdNext);

        volume = new VlcWidgetVolumeSlider(Musik);
        volume->setObjectName(QString::fromUtf8("volume"));
        volume->setMaximumSize(QSize(16777215, 24));

        horizontalLayout->addWidget(volume);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Musik);

        QMetaObject::connectSlotsByName(Musik);
    } // setupUi

    void retranslateUi(QGroupBox *Musik)
    {
        Musik->setWindowTitle(QApplication::translate("Musik", "Music", nullptr));
        Musik->setTitle(QApplication::translate("Musik", "Media", nullptr));
#ifndef QT_NO_TOOLTIP
        chkRadio->setToolTip(QApplication::translate("Musik", "continuous play", nullptr));
#endif // QT_NO_TOOLTIP
        chkRadio->setText(QString());
        cmdSave->setText(QString());
        cmdEqualizer->setText(QString());
        cmdPrev->setText(QString());
        cmdStop->setText(QString());
        cmdPause->setText(QString());
        cmdPlay->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdNext->setToolTip(QApplication::translate("Musik", "save actual file to disk", nullptr));
#endif // QT_NO_TOOLTIP
        cmdNext->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Musik: public Ui_Musik {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSIK_H
