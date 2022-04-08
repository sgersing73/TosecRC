/********************************************************************************
** Form generated from reading UI file 'downloadmgr.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADMGR_H
#define UI_DOWNLOADMGR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DownloadMgr
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *lblUrl;
    QLineEdit *edtUrl;
    QPushButton *cmdAdd;
    QLineEdit *edtFilter;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *lisDownload;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdClearList;
    QPushButton *cmdDelEntry;
    QSpacerItem *verticalSpacer;
    QPushButton *cmdLoadList;
    QPushButton *cmdSaveList;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *progressBar;
    QLabel *lblEstimate;
    QGridLayout *gridLayout;
    QToolButton *toolButton;
    QCheckBox *chkAutoDownloadNext;
    QPushButton *cmdDownload;
    QLineEdit *edtParameter;
    QLineEdit *edtDownloadDir;
    QLabel *label;
    QPushButton *cmdCancelDownload;
    QCheckBox *chkHideOutput;
    QTextEdit *edtOutput;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DownloadMgr)
    {
        if (DownloadMgr->objectName().isEmpty())
            DownloadMgr->setObjectName(QString::fromUtf8("DownloadMgr"));
        DownloadMgr->resize(740, 371);
        centralWidget = new QWidget(DownloadMgr);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblUrl = new QLabel(centralWidget);
        lblUrl->setObjectName(QString::fromUtf8("lblUrl"));

        horizontalLayout->addWidget(lblUrl);

        edtUrl = new QLineEdit(centralWidget);
        edtUrl->setObjectName(QString::fromUtf8("edtUrl"));

        horizontalLayout->addWidget(edtUrl);

        cmdAdd = new QPushButton(centralWidget);
        cmdAdd->setObjectName(QString::fromUtf8("cmdAdd"));

        horizontalLayout->addWidget(cmdAdd);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        edtFilter = new QLineEdit(centralWidget);
        edtFilter->setObjectName(QString::fromUtf8("edtFilter"));

        gridLayout_2->addWidget(edtFilter, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lisDownload = new QListWidget(centralWidget);
        lisDownload->setObjectName(QString::fromUtf8("lisDownload"));
        lisDownload->setStyleSheet(QString::fromUtf8("show-decoration-selected: 1;\n"
"selection-color: white;\n"
"selection-background-color: #0068d9;\n"
""));

        horizontalLayout_2->addWidget(lisDownload);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cmdClearList = new QPushButton(centralWidget);
        cmdClearList->setObjectName(QString::fromUtf8("cmdClearList"));

        verticalLayout->addWidget(cmdClearList);

        cmdDelEntry = new QPushButton(centralWidget);
        cmdDelEntry->setObjectName(QString::fromUtf8("cmdDelEntry"));

        verticalLayout->addWidget(cmdDelEntry);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        cmdLoadList = new QPushButton(centralWidget);
        cmdLoadList->setObjectName(QString::fromUtf8("cmdLoadList"));

        verticalLayout->addWidget(cmdLoadList);

        cmdSaveList = new QPushButton(centralWidget);
        cmdSaveList->setObjectName(QString::fromUtf8("cmdSaveList"));

        verticalLayout->addWidget(cmdSaveList);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        horizontalLayout_3->addWidget(progressBar);

        lblEstimate = new QLabel(centralWidget);
        lblEstimate->setObjectName(QString::fromUtf8("lblEstimate"));
        lblEstimate->setMinimumSize(QSize(80, 0));
        lblEstimate->setMaximumSize(QSize(80, 16777215));
        lblEstimate->setScaledContents(false);
        lblEstimate->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lblEstimate);


        gridLayout_2->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        gridLayout->addWidget(toolButton, 0, 4, 1, 1);

        chkAutoDownloadNext = new QCheckBox(centralWidget);
        chkAutoDownloadNext->setObjectName(QString::fromUtf8("chkAutoDownloadNext"));

        gridLayout->addWidget(chkAutoDownloadNext, 0, 0, 1, 1);

        cmdDownload = new QPushButton(centralWidget);
        cmdDownload->setObjectName(QString::fromUtf8("cmdDownload"));

        gridLayout->addWidget(cmdDownload, 0, 1, 1, 1);

        edtParameter = new QLineEdit(centralWidget);
        edtParameter->setObjectName(QString::fromUtf8("edtParameter"));

        gridLayout->addWidget(edtParameter, 0, 5, 1, 1);

        edtDownloadDir = new QLineEdit(centralWidget);
        edtDownloadDir->setObjectName(QString::fromUtf8("edtDownloadDir"));

        gridLayout->addWidget(edtDownloadDir, 0, 3, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        cmdCancelDownload = new QPushButton(centralWidget);
        cmdCancelDownload->setObjectName(QString::fromUtf8("cmdCancelDownload"));

        gridLayout->addWidget(cmdCancelDownload, 0, 6, 1, 1);

        chkHideOutput = new QCheckBox(centralWidget);
        chkHideOutput->setObjectName(QString::fromUtf8("chkHideOutput"));

        gridLayout->addWidget(chkHideOutput, 0, 7, 1, 1);


        gridLayout_2->addLayout(gridLayout, 4, 0, 1, 1);

        edtOutput = new QTextEdit(centralWidget);
        edtOutput->setObjectName(QString::fromUtf8("edtOutput"));

        gridLayout_2->addWidget(edtOutput, 5, 0, 1, 1);

        DownloadMgr->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DownloadMgr);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 740, 21));
        DownloadMgr->setMenuBar(menuBar);
        statusBar = new QStatusBar(DownloadMgr);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DownloadMgr->setStatusBar(statusBar);

        retranslateUi(DownloadMgr);

        QMetaObject::connectSlotsByName(DownloadMgr);
    } // setupUi

    void retranslateUi(QMainWindow *DownloadMgr)
    {
        DownloadMgr->setWindowTitle(QApplication::translate("DownloadMgr", "Download Manager", nullptr));
        lblUrl->setText(QApplication::translate("DownloadMgr", "URL:", nullptr));
        cmdAdd->setText(QApplication::translate("DownloadMgr", "add to queue", nullptr));
        cmdClearList->setText(QApplication::translate("DownloadMgr", "clear list", nullptr));
        cmdDelEntry->setText(QApplication::translate("DownloadMgr", "delete entry", nullptr));
        cmdLoadList->setText(QApplication::translate("DownloadMgr", "load queue", nullptr));
        cmdSaveList->setText(QApplication::translate("DownloadMgr", "save queue", nullptr));
        lblEstimate->setText(QString());
        toolButton->setText(QApplication::translate("DownloadMgr", "...", nullptr));
        chkAutoDownloadNext->setText(QApplication::translate("DownloadMgr", "auto", nullptr));
        cmdDownload->setText(QApplication::translate("DownloadMgr", "start download", nullptr));
        label->setText(QApplication::translate("DownloadMgr", "to destination  directory:", nullptr));
        cmdCancelDownload->setText(QApplication::translate("DownloadMgr", "cancel", nullptr));
        chkHideOutput->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DownloadMgr: public Ui_DownloadMgr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADMGR_H
