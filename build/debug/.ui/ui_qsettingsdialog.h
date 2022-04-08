/********************************************************************************
** Form generated from reading UI file 'qsettingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSETTINGSDIALOG_H
#define UI_QSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSettingsDialog
{
public:
    QGridLayout *gridLayout_14;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QTableWidget *grdValues;
    QComboBox *cboSections;
    QComboBox *cboINIFiles;
    QHBoxLayout *horizontalLayout;
    QPushButton *cmdAddLine;
    QPushButton *cmdDelete;
    QWidget *tab_3;
    QGridLayout *gridLayout_11;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_10;
    QCheckBox *swHttpEnabled;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *swFtpEnabled;
    QLineEdit *edtFTPPort;
    QCheckBox *chkAnonymous;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblFTPUser;
    QLineEdit *edtFTPUser;
    QLabel *lblFTPPassword;
    QLineEdit *edtFTPPassword;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_7;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *edtProxyUser;
    QLabel *label_3;
    QLineEdit *edtProxyPassword;
    QLabel *label_4;
    QLineEdit *edtProxyIpAddress;
    QLabel *label_5;
    QLineEdit *edtProxyIpPort;
    QCheckBox *swProxy;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_2;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_12;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblFontName;
    QLabel *lblFontSize;
    QPushButton *cmdFontSelect;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *cboQssFiles;
    QPushButton *cmdQssEdit;
    QGroupBox *grpButtonColor;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *cboButtonColor;
    QWidget *tabDropbox;
    QGridLayout *gridLayout_13;
    QGroupBox *grpDropbox;
    QGridLayout *gridLayout_9;
    QLabel *lblDropboxKey;
    QLineEdit *edtDropboxKey;
    QLabel *lblDropboxSecret;
    QLineEdit *edtDropboxSecret;
    QLabel *lblDropboxToken;
    QLineEdit *edtDropboxToken;
    QLabel *lblDropboxDir;
    QLineEdit *edtDropboxDir;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdOK;
    QPushButton *cmdCancel;

    void setupUi(QDialog *QSettingsDialog)
    {
        if (QSettingsDialog->objectName().isEmpty())
            QSettingsDialog->setObjectName(QString::fromUtf8("QSettingsDialog"));
        QSettingsDialog->resize(522, 418);
        gridLayout_14 = new QGridLayout(QSettingsDialog);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        tabWidget = new QTabWidget(QSettingsDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        grdValues = new QTableWidget(tab);
        grdValues->setObjectName(QString::fromUtf8("grdValues"));

        gridLayout->addWidget(grdValues, 2, 0, 1, 1);

        cboSections = new QComboBox(tab);
        cboSections->setObjectName(QString::fromUtf8("cboSections"));

        gridLayout->addWidget(cboSections, 1, 0, 1, 1);

        cboINIFiles = new QComboBox(tab);
        cboINIFiles->setObjectName(QString::fromUtf8("cboINIFiles"));

        gridLayout->addWidget(cboINIFiles, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cmdAddLine = new QPushButton(tab);
        cmdAddLine->setObjectName(QString::fromUtf8("cmdAddLine"));

        horizontalLayout->addWidget(cmdAddLine);

        cmdDelete = new QPushButton(tab);
        cmdDelete->setObjectName(QString::fromUtf8("cmdDelete"));

        horizontalLayout->addWidget(cmdDelete);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_11 = new QGridLayout(tab_3);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_10 = new QGridLayout(groupBox_4);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        swHttpEnabled = new QCheckBox(groupBox_4);
        swHttpEnabled->setObjectName(QString::fromUtf8("swHttpEnabled"));

        gridLayout_10->addWidget(swHttpEnabled, 0, 0, 1, 1);


        gridLayout_11->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(tab_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_8 = new QGridLayout(groupBox_5);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        swFtpEnabled = new QCheckBox(groupBox_5);
        swFtpEnabled->setObjectName(QString::fromUtf8("swFtpEnabled"));

        horizontalLayout_6->addWidget(swFtpEnabled);

        edtFTPPort = new QLineEdit(groupBox_5);
        edtFTPPort->setObjectName(QString::fromUtf8("edtFTPPort"));

        horizontalLayout_6->addWidget(edtFTPPort);


        gridLayout_8->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        chkAnonymous = new QCheckBox(groupBox_5);
        chkAnonymous->setObjectName(QString::fromUtf8("chkAnonymous"));

        gridLayout_8->addWidget(chkAnonymous, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lblFTPUser = new QLabel(groupBox_5);
        lblFTPUser->setObjectName(QString::fromUtf8("lblFTPUser"));

        horizontalLayout_5->addWidget(lblFTPUser);

        edtFTPUser = new QLineEdit(groupBox_5);
        edtFTPUser->setObjectName(QString::fromUtf8("edtFTPUser"));

        horizontalLayout_5->addWidget(edtFTPUser);

        lblFTPPassword = new QLabel(groupBox_5);
        lblFTPPassword->setObjectName(QString::fromUtf8("lblFTPPassword"));

        horizontalLayout_5->addWidget(lblFTPPassword);

        edtFTPPassword = new QLineEdit(groupBox_5);
        edtFTPPassword->setObjectName(QString::fromUtf8("edtFTPPassword"));

        horizontalLayout_5->addWidget(edtFTPPassword);


        gridLayout_8->addLayout(horizontalLayout_5, 2, 0, 1, 1);


        gridLayout_11->addWidget(groupBox_5, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_7 = new QGridLayout(groupBox_3);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_7->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_7->addWidget(label_2, 1, 0, 1, 1);

        edtProxyUser = new QLineEdit(groupBox_3);
        edtProxyUser->setObjectName(QString::fromUtf8("edtProxyUser"));

        gridLayout_7->addWidget(edtProxyUser, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_7->addWidget(label_3, 2, 0, 1, 1);

        edtProxyPassword = new QLineEdit(groupBox_3);
        edtProxyPassword->setObjectName(QString::fromUtf8("edtProxyPassword"));

        gridLayout_7->addWidget(edtProxyPassword, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_7->addWidget(label_4, 3, 0, 1, 1);

        edtProxyIpAddress = new QLineEdit(groupBox_3);
        edtProxyIpAddress->setObjectName(QString::fromUtf8("edtProxyIpAddress"));

        gridLayout_7->addWidget(edtProxyIpAddress, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_7->addWidget(label_5, 4, 0, 1, 1);

        edtProxyIpPort = new QLineEdit(groupBox_3);
        edtProxyIpPort->setObjectName(QString::fromUtf8("edtProxyIpPort"));

        gridLayout_7->addWidget(edtProxyIpPort, 4, 1, 1, 1);

        swProxy = new QCheckBox(groupBox_3);
        swProxy->setObjectName(QString::fromUtf8("swProxy"));

        gridLayout_7->addWidget(swProxy, 0, 1, 1, 1);


        gridLayout_11->addWidget(groupBox_3, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_11->addItem(verticalSpacer_3, 3, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_6 = new QGridLayout(tab_2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBox_6 = new QGroupBox(tab_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_12 = new QGridLayout(groupBox_6);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblFontName = new QLabel(groupBox_6);
        lblFontName->setObjectName(QString::fromUtf8("lblFontName"));

        horizontalLayout_4->addWidget(lblFontName);

        lblFontSize = new QLabel(groupBox_6);
        lblFontSize->setObjectName(QString::fromUtf8("lblFontSize"));

        horizontalLayout_4->addWidget(lblFontSize);

        cmdFontSelect = new QPushButton(groupBox_6);
        cmdFontSelect->setObjectName(QString::fromUtf8("cmdFontSelect"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmdFontSelect->sizePolicy().hasHeightForWidth());
        cmdFontSelect->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/toolbar/blue/images/toolbar/blue/setttings.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdFontSelect->setIcon(icon);

        horizontalLayout_4->addWidget(cmdFontSelect);


        gridLayout_12->addLayout(horizontalLayout_4, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_6, 3, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 89, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_2, 4, 0, 1, 1);

        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        gridLayout_5->addWidget(radioButton_4, 0, 0, 1, 1);

        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        gridLayout_5->addWidget(radioButton, 0, 1, 1, 1);

        radioButton_5 = new QRadioButton(groupBox);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));

        gridLayout_5->addWidget(radioButton_5, 1, 0, 1, 1);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        gridLayout_5->addWidget(radioButton_2, 1, 1, 1, 1);

        radioButton_6 = new QRadioButton(groupBox);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));

        gridLayout_5->addWidget(radioButton_6, 2, 0, 1, 1);

        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        gridLayout_5->addWidget(radioButton_3, 2, 1, 1, 1);

        radioButton_7 = new QRadioButton(groupBox);
        radioButton_7->setObjectName(QString::fromUtf8("radioButton_7"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(radioButton_7->sizePolicy().hasHeightForWidth());
        radioButton_7->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(radioButton_7, 3, 0, 1, 1);

        radioButton_8 = new QRadioButton(groupBox);
        radioButton_8->setObjectName(QString::fromUtf8("radioButton_8"));

        gridLayout_5->addWidget(radioButton_8, 3, 1, 1, 1);


        gridLayout_6->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cboQssFiles = new QComboBox(groupBox_2);
        cboQssFiles->setObjectName(QString::fromUtf8("cboQssFiles"));

        horizontalLayout_3->addWidget(cboQssFiles);

        cmdQssEdit = new QPushButton(groupBox_2);
        cmdQssEdit->setObjectName(QString::fromUtf8("cmdQssEdit"));
        sizePolicy.setHeightForWidth(cmdQssEdit->sizePolicy().hasHeightForWidth());
        cmdQssEdit->setSizePolicy(sizePolicy);
        cmdQssEdit->setIcon(icon);

        horizontalLayout_3->addWidget(cmdQssEdit);


        gridLayout_4->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_2, 1, 0, 1, 1);

        grpButtonColor = new QGroupBox(tab_2);
        grpButtonColor->setObjectName(QString::fromUtf8("grpButtonColor"));
        gridLayout_2 = new QGridLayout(grpButtonColor);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        cboButtonColor = new QComboBox(grpButtonColor);
        cboButtonColor->setObjectName(QString::fromUtf8("cboButtonColor"));

        horizontalLayout_7->addWidget(cboButtonColor);


        gridLayout_2->addLayout(horizontalLayout_7, 0, 0, 1, 1);


        gridLayout_6->addWidget(grpButtonColor, 2, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tabDropbox = new QWidget();
        tabDropbox->setObjectName(QString::fromUtf8("tabDropbox"));
        gridLayout_13 = new QGridLayout(tabDropbox);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        grpDropbox = new QGroupBox(tabDropbox);
        grpDropbox->setObjectName(QString::fromUtf8("grpDropbox"));
        gridLayout_9 = new QGridLayout(grpDropbox);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        lblDropboxKey = new QLabel(grpDropbox);
        lblDropboxKey->setObjectName(QString::fromUtf8("lblDropboxKey"));

        gridLayout_9->addWidget(lblDropboxKey, 0, 0, 1, 1);

        edtDropboxKey = new QLineEdit(grpDropbox);
        edtDropboxKey->setObjectName(QString::fromUtf8("edtDropboxKey"));

        gridLayout_9->addWidget(edtDropboxKey, 0, 1, 1, 1);

        lblDropboxSecret = new QLabel(grpDropbox);
        lblDropboxSecret->setObjectName(QString::fromUtf8("lblDropboxSecret"));

        gridLayout_9->addWidget(lblDropboxSecret, 1, 0, 1, 1);

        edtDropboxSecret = new QLineEdit(grpDropbox);
        edtDropboxSecret->setObjectName(QString::fromUtf8("edtDropboxSecret"));

        gridLayout_9->addWidget(edtDropboxSecret, 1, 1, 1, 1);

        lblDropboxToken = new QLabel(grpDropbox);
        lblDropboxToken->setObjectName(QString::fromUtf8("lblDropboxToken"));

        gridLayout_9->addWidget(lblDropboxToken, 2, 0, 1, 1);

        edtDropboxToken = new QLineEdit(grpDropbox);
        edtDropboxToken->setObjectName(QString::fromUtf8("edtDropboxToken"));

        gridLayout_9->addWidget(edtDropboxToken, 2, 1, 1, 1);

        lblDropboxDir = new QLabel(grpDropbox);
        lblDropboxDir->setObjectName(QString::fromUtf8("lblDropboxDir"));

        gridLayout_9->addWidget(lblDropboxDir, 3, 0, 1, 1);

        edtDropboxDir = new QLineEdit(grpDropbox);
        edtDropboxDir->setObjectName(QString::fromUtf8("edtDropboxDir"));

        gridLayout_9->addWidget(edtDropboxDir, 3, 1, 1, 1);


        gridLayout_13->addWidget(grpDropbox, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 162, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_13->addItem(verticalSpacer, 1, 0, 1, 1);

        tabWidget->addTab(tabDropbox, QString());

        gridLayout_14->addWidget(tabWidget, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(418, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cmdOK = new QPushButton(QSettingsDialog);
        cmdOK->setObjectName(QString::fromUtf8("cmdOK"));

        horizontalLayout_2->addWidget(cmdOK);

        cmdCancel = new QPushButton(QSettingsDialog);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout_2->addWidget(cmdCancel);


        gridLayout_14->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        retranslateUi(QSettingsDialog);

        tabWidget->setCurrentIndex(2);
        cmdCancel->setDefault(true);


        QMetaObject::connectSlotsByName(QSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *QSettingsDialog)
    {
        QSettingsDialog->setWindowTitle(QApplication::translate("QSettingsDialog", "Settings ", nullptr));
        cmdAddLine->setText(QApplication::translate("QSettingsDialog", "Add Key", nullptr));
        cmdDelete->setText(QApplication::translate("QSettingsDialog", "Delete Key", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QSettingsDialog", "INI File", nullptr));
        groupBox_4->setTitle(QApplication::translate("QSettingsDialog", "HTTP Server", nullptr));
        swHttpEnabled->setText(QApplication::translate("QSettingsDialog", "enable HTTP Server", nullptr));
        groupBox_5->setTitle(QApplication::translate("QSettingsDialog", "FTP Server", nullptr));
        swFtpEnabled->setText(QApplication::translate("QSettingsDialog", "enable FTP Server on port", nullptr));
        chkAnonymous->setText(QApplication::translate("QSettingsDialog", "Anonymous login enabled", nullptr));
        lblFTPUser->setText(QApplication::translate("QSettingsDialog", "User:", nullptr));
        lblFTPPassword->setText(QApplication::translate("QSettingsDialog", "Password:", nullptr));
        groupBox_3->setTitle(QApplication::translate("QSettingsDialog", "Proxy", nullptr));
        label->setText(QApplication::translate("QSettingsDialog", " Proxy enable", nullptr));
        label_2->setText(QApplication::translate("QSettingsDialog", " Proxy user", nullptr));
        label_3->setText(QApplication::translate("QSettingsDialog", " Proxy password", nullptr));
        label_4->setText(QApplication::translate("QSettingsDialog", " Proxy IP Address", nullptr));
        label_5->setText(QApplication::translate("QSettingsDialog", " Proxy Port", nullptr));
        swProxy->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("QSettingsDialog", "Network", nullptr));
        groupBox_6->setTitle(QApplication::translate("QSettingsDialog", "Font", nullptr));
        lblFontName->setText(QApplication::translate("QSettingsDialog", "TextLabel", nullptr));
        lblFontSize->setText(QApplication::translate("QSettingsDialog", "TextLabel", nullptr));
        cmdFontSelect->setText(QString());
        groupBox->setTitle(QApplication::translate("QSettingsDialog", "Available StyleSheets", nullptr));
        radioButton_4->setText(QApplication::translate("QSettingsDialog", "Fusion", nullptr));
        radioButton->setText(QApplication::translate("QSettingsDialog", "Windows", nullptr));
        radioButton_5->setText(QApplication::translate("QSettingsDialog", "Fusion (black)", nullptr));
        radioButton_2->setText(QApplication::translate("QSettingsDialog", "WindowsXP", nullptr));
        radioButton_6->setText(QApplication::translate("QSettingsDialog", "Bronze", nullptr));
        radioButton_3->setText(QApplication::translate("QSettingsDialog", "Windows Vista", nullptr));
        radioButton_7->setText(QApplication::translate("QSettingsDialog", "Norwegian Wood", nullptr));
        radioButton_8->setText(QApplication::translate("QSettingsDialog", "none", nullptr));
        groupBox_2->setTitle(QApplication::translate("QSettingsDialog", "Available QSS files", nullptr));
        cmdQssEdit->setText(QString());
        grpButtonColor->setTitle(QApplication::translate("QSettingsDialog", "Button Icon Color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QSettingsDialog", "Style Sheets", nullptr));
        grpDropbox->setTitle(QApplication::translate("QSettingsDialog", "Dropbox settings", nullptr));
        lblDropboxKey->setText(QApplication::translate("QSettingsDialog", "Key:", nullptr));
        lblDropboxSecret->setText(QApplication::translate("QSettingsDialog", "Secret:", nullptr));
        lblDropboxToken->setText(QApplication::translate("QSettingsDialog", "Token:", nullptr));
        lblDropboxDir->setText(QApplication::translate("QSettingsDialog", "Directory:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDropbox), QApplication::translate("QSettingsDialog", "Dropbox", nullptr));
        cmdOK->setText(QApplication::translate("QSettingsDialog", "Save Settings", nullptr));
        cmdCancel->setText(QApplication::translate("QSettingsDialog", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QSettingsDialog: public Ui_QSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSETTINGSDIALOG_H
