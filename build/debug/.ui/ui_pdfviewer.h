/********************************************************************************
** Form generated from reading UI file 'pdfviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFVIEWER_H
#define UI_PDFVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PDFViewer
{
public:
    QGridLayout *gridLayout_5;
    QFrame *frame;
    QGridLayout *gridLayout_4;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QListWidget *listWidgetBookmarks;
    QLabel *lblCaption;
    QLineEdit *edtTitle;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *edtLink;
    QPushButton *cmdAddLink;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *cmdSectionSettings;
    QComboBox *cboSections;
    QComboBox *cboYears;
    QPushButton *cmdDownload;
    QLabel *lblInfo;
    QListWidget *listWidgetTitels;
    QGroupBox *grpInformations;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblAnmerkung;
    QLineEdit *edtAnmerkung;
    QPushButton *cmdSaveInfos;
    QTableWidget *lstInfo;
    QPushButton *cmdRemoveMetaData;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblNummer;
    QLineEdit *edtNummer;
    QLabel *lblMonat;
    QLineEdit *edtMonat;
    QLabel *label;
    QLineEdit *edtJahr;
    QFrame *frame_2;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QVBoxLayout *verticalLayout;
    QLabel *lblLogo;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_9;
    QLabel *lblBerlag;
    QLineEdit *edtVerlag;
    QLabel *lblISSN;
    QLineEdit *edtISSN;
    QLabel *lblErstausgabe;
    QLineEdit *edtErstausgabe;
    QLabel *lblISSN_3;
    QLineEdit *edtEinstellung;
    QLineEdit *edtIssueTitle;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *cmdBackward;
    QPushButton *cmdBookmark;
    QPushButton *cmdForward;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *lblPage;
    QLineEdit *edtPage;
    QLabel *lblScalefactor;
    QSpinBox *spinScaleFactor;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cmdExtract;
    QPushButton *cmdUpload;
    QTextEdit *edtOutput;
    QSlider *sliPages;
    QScrollArea *scrollDisplay;
    QWidget *scrollAreaWidgetContents_3;
    QGridLayout *gridLayout_2;
    QLabel *lblDisplay;
    QPushButton *cmdCancelDownload;
    QListWidget *listWidgetThumb;

    void setupUi(QDialog *PDFViewer)
    {
        if (PDFViewer->objectName().isEmpty())
            PDFViewer->setObjectName(QString::fromUtf8("PDFViewer"));
        PDFViewer->resize(992, 797);
        PDFViewer->setMinimumSize(QSize(0, 0));
        gridLayout_5 = new QGridLayout(PDFViewer);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        frame = new QFrame(PDFViewer);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        splitter = new QSplitter(frame);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        listWidgetBookmarks = new QListWidget(layoutWidget);
        listWidgetBookmarks->setObjectName(QString::fromUtf8("listWidgetBookmarks"));

        gridLayout->addWidget(listWidgetBookmarks, 5, 1, 1, 1);

        lblCaption = new QLabel(layoutWidget);
        lblCaption->setObjectName(QString::fromUtf8("lblCaption"));
        lblCaption->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblCaption, 3, 1, 1, 1);

        edtTitle = new QLineEdit(layoutWidget);
        edtTitle->setObjectName(QString::fromUtf8("edtTitle"));

        gridLayout->addWidget(edtTitle, 7, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        edtLink = new QLineEdit(layoutWidget);
        edtLink->setObjectName(QString::fromUtf8("edtLink"));

        horizontalLayout_2->addWidget(edtLink);

        cmdAddLink = new QPushButton(layoutWidget);
        cmdAddLink->setObjectName(QString::fromUtf8("cmdAddLink"));

        horizontalLayout_2->addWidget(cmdAddLink);


        gridLayout->addLayout(horizontalLayout_2, 8, 1, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        cmdSectionSettings = new QPushButton(layoutWidget);
        cmdSectionSettings->setObjectName(QString::fromUtf8("cmdSectionSettings"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmdSectionSettings->sizePolicy().hasHeightForWidth());
        cmdSectionSettings->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/pipette.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSectionSettings->setIcon(icon);

        horizontalLayout_6->addWidget(cmdSectionSettings);

        cboSections = new QComboBox(layoutWidget);
        cboSections->setObjectName(QString::fromUtf8("cboSections"));
        cboSections->setEditable(true);

        horizontalLayout_6->addWidget(cboSections);

        cboYears = new QComboBox(layoutWidget);
        cboYears->setObjectName(QString::fromUtf8("cboYears"));

        horizontalLayout_6->addWidget(cboYears);

        cmdDownload = new QPushButton(layoutWidget);
        cmdDownload->setObjectName(QString::fromUtf8("cmdDownload"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmdDownload->sizePolicy().hasHeightForWidth());
        cmdDownload->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/toolbar/blue/images/toolbar/blue/download.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdDownload->setIcon(icon1);

        horizontalLayout_6->addWidget(cmdDownload);


        gridLayout->addLayout(horizontalLayout_6, 2, 1, 1, 1);

        lblInfo = new QLabel(layoutWidget);
        lblInfo->setObjectName(QString::fromUtf8("lblInfo"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblInfo->sizePolicy().hasHeightForWidth());
        lblInfo->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(lblInfo, 9, 1, 1, 1);

        listWidgetTitels = new QListWidget(layoutWidget);
        listWidgetTitels->setObjectName(QString::fromUtf8("listWidgetTitels"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(listWidgetTitels->sizePolicy().hasHeightForWidth());
        listWidgetTitels->setSizePolicy(sizePolicy3);
        listWidgetTitels->setSortingEnabled(true);

        gridLayout->addWidget(listWidgetTitels, 4, 1, 1, 1);

        grpInformations = new QGroupBox(layoutWidget);
        grpInformations->setObjectName(QString::fromUtf8("grpInformations"));
        grpInformations->setMinimumSize(QSize(0, 0));
        grpInformations->setBaseSize(QSize(0, 0));
        gridLayout_6 = new QGridLayout(grpInformations);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblAnmerkung = new QLabel(grpInformations);
        lblAnmerkung->setObjectName(QString::fromUtf8("lblAnmerkung"));

        horizontalLayout_4->addWidget(lblAnmerkung);

        edtAnmerkung = new QLineEdit(grpInformations);
        edtAnmerkung->setObjectName(QString::fromUtf8("edtAnmerkung"));

        horizontalLayout_4->addWidget(edtAnmerkung);

        cmdSaveInfos = new QPushButton(grpInformations);
        cmdSaveInfos->setObjectName(QString::fromUtf8("cmdSaveInfos"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSaveInfos->setIcon(icon2);

        horizontalLayout_4->addWidget(cmdSaveInfos);


        gridLayout_6->addLayout(horizontalLayout_4, 5, 0, 1, 1);

        lstInfo = new QTableWidget(grpInformations);
        if (lstInfo->columnCount() < 2)
            lstInfo->setColumnCount(2);
        lstInfo->setObjectName(QString::fromUtf8("lstInfo"));
        lstInfo->setColumnCount(2);
        lstInfo->horizontalHeader()->setVisible(false);
        lstInfo->verticalHeader()->setVisible(true);

        gridLayout_6->addWidget(lstInfo, 0, 0, 1, 1);

        cmdRemoveMetaData = new QPushButton(grpInformations);
        cmdRemoveMetaData->setObjectName(QString::fromUtf8("cmdRemoveMetaData"));

        gridLayout_6->addWidget(cmdRemoveMetaData, 1, 0, 1, 1);

        line = new QFrame(grpInformations);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lblNummer = new QLabel(grpInformations);
        lblNummer->setObjectName(QString::fromUtf8("lblNummer"));

        horizontalLayout_5->addWidget(lblNummer);

        edtNummer = new QLineEdit(grpInformations);
        edtNummer->setObjectName(QString::fromUtf8("edtNummer"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(edtNummer->sizePolicy().hasHeightForWidth());
        edtNummer->setSizePolicy(sizePolicy4);

        horizontalLayout_5->addWidget(edtNummer);

        lblMonat = new QLabel(grpInformations);
        lblMonat->setObjectName(QString::fromUtf8("lblMonat"));

        horizontalLayout_5->addWidget(lblMonat);

        edtMonat = new QLineEdit(grpInformations);
        edtMonat->setObjectName(QString::fromUtf8("edtMonat"));
        sizePolicy4.setHeightForWidth(edtMonat->sizePolicy().hasHeightForWidth());
        edtMonat->setSizePolicy(sizePolicy4);

        horizontalLayout_5->addWidget(edtMonat);

        label = new QLabel(grpInformations);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        edtJahr = new QLineEdit(grpInformations);
        edtJahr->setObjectName(QString::fromUtf8("edtJahr"));
        sizePolicy4.setHeightForWidth(edtJahr->sizePolicy().hasHeightForWidth());
        edtJahr->setSizePolicy(sizePolicy4);

        horizontalLayout_5->addWidget(edtJahr);


        gridLayout_6->addLayout(horizontalLayout_5, 3, 0, 1, 1);


        gridLayout->addWidget(grpInformations, 6, 1, 1, 1);

        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_8 = new QGridLayout(frame_2);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblLogo = new QLabel(frame_2);
        lblLogo->setObjectName(QString::fromUtf8("lblLogo"));
        lblLogo->setMinimumSize(QSize(250, 0));
        lblLogo->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblLogo);


        gridLayout_7->addLayout(verticalLayout, 0, 0, 1, 1);

        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        gridLayout_9 = new QGridLayout(groupBox);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        lblBerlag = new QLabel(groupBox);
        lblBerlag->setObjectName(QString::fromUtf8("lblBerlag"));

        gridLayout_9->addWidget(lblBerlag, 0, 0, 1, 1);

        edtVerlag = new QLineEdit(groupBox);
        edtVerlag->setObjectName(QString::fromUtf8("edtVerlag"));

        gridLayout_9->addWidget(edtVerlag, 0, 1, 1, 3);

        lblISSN = new QLabel(groupBox);
        lblISSN->setObjectName(QString::fromUtf8("lblISSN"));

        gridLayout_9->addWidget(lblISSN, 1, 0, 1, 1);

        edtISSN = new QLineEdit(groupBox);
        edtISSN->setObjectName(QString::fromUtf8("edtISSN"));

        gridLayout_9->addWidget(edtISSN, 1, 1, 1, 3);

        lblErstausgabe = new QLabel(groupBox);
        lblErstausgabe->setObjectName(QString::fromUtf8("lblErstausgabe"));

        gridLayout_9->addWidget(lblErstausgabe, 2, 0, 1, 3);

        edtErstausgabe = new QLineEdit(groupBox);
        edtErstausgabe->setObjectName(QString::fromUtf8("edtErstausgabe"));

        gridLayout_9->addWidget(edtErstausgabe, 2, 3, 1, 1);

        lblISSN_3 = new QLabel(groupBox);
        lblISSN_3->setObjectName(QString::fromUtf8("lblISSN_3"));

        gridLayout_9->addWidget(lblISSN_3, 3, 0, 1, 2);

        edtEinstellung = new QLineEdit(groupBox);
        edtEinstellung->setObjectName(QString::fromUtf8("edtEinstellung"));

        gridLayout_9->addWidget(edtEinstellung, 3, 2, 1, 2);


        gridLayout_7->addWidget(groupBox, 0, 1, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 1, 0, 1, 1);

        edtIssueTitle = new QLineEdit(frame_2);
        edtIssueTitle->setObjectName(QString::fromUtf8("edtIssueTitle"));
        QFont font;
        font.setPointSize(12);
        edtIssueTitle->setFont(font);
        edtIssueTitle->setFrame(false);
        edtIssueTitle->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(edtIssueTitle, 0, 0, 1, 1);


        gridLayout->addWidget(frame_2, 0, 1, 1, 1);

        splitter->addWidget(layoutWidget);
        layoutWidget_2 = new QWidget(splitter);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        gridLayout_3 = new QGridLayout(layoutWidget_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cmdBackward = new QPushButton(layoutWidget_2);
        cmdBackward->setObjectName(QString::fromUtf8("cmdBackward"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/player/images/player/blue/backward.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdBackward->setIcon(icon3);

        horizontalLayout_3->addWidget(cmdBackward);

        cmdBookmark = new QPushButton(layoutWidget_2);
        cmdBookmark->setObjectName(QString::fromUtf8("cmdBookmark"));

        horizontalLayout_3->addWidget(cmdBookmark);

        cmdForward = new QPushButton(layoutWidget_2);
        cmdForward->setObjectName(QString::fromUtf8("cmdForward"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/player/images/player/blue/forward.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdForward->setIcon(icon4);

        horizontalLayout_3->addWidget(cmdForward);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lblPage = new QLabel(layoutWidget_2);
        lblPage->setObjectName(QString::fromUtf8("lblPage"));
        lblPage->setTextFormat(Qt::AutoText);
        lblPage->setScaledContents(true);
        lblPage->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lblPage);

        edtPage = new QLineEdit(layoutWidget_2);
        edtPage->setObjectName(QString::fromUtf8("edtPage"));
        edtPage->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(edtPage);

        lblScalefactor = new QLabel(layoutWidget_2);
        lblScalefactor->setObjectName(QString::fromUtf8("lblScalefactor"));
        lblScalefactor->setScaledContents(true);

        horizontalLayout->addWidget(lblScalefactor);

        spinScaleFactor = new QSpinBox(layoutWidget_2);
        spinScaleFactor->setObjectName(QString::fromUtf8("spinScaleFactor"));
        spinScaleFactor->setMinimum(10);
        spinScaleFactor->setMaximum(500);
        spinScaleFactor->setSingleStep(10);
        spinScaleFactor->setValue(40);

        horizontalLayout->addWidget(spinScaleFactor);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        cmdExtract = new QPushButton(layoutWidget_2);
        cmdExtract->setObjectName(QString::fromUtf8("cmdExtract"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/usbstick.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdExtract->setIcon(icon5);

        horizontalLayout->addWidget(cmdExtract);

        cmdUpload = new QPushButton(layoutWidget_2);
        cmdUpload->setObjectName(QString::fromUtf8("cmdUpload"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/farious/blue/images/farious/blue/upload.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cmdUpload->setIcon(icon6);

        horizontalLayout->addWidget(cmdUpload);


        gridLayout_3->addLayout(horizontalLayout, 5, 0, 1, 1);

        edtOutput = new QTextEdit(layoutWidget_2);
        edtOutput->setObjectName(QString::fromUtf8("edtOutput"));
        edtOutput->setMaximumSize(QSize(16777215, 200));
        edtOutput->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 204, 204);"));
        edtOutput->setFrameShadow(QFrame::Plain);

        gridLayout_3->addWidget(edtOutput, 2, 0, 1, 1);

        sliPages = new QSlider(layoutWidget_2);
        sliPages->setObjectName(QString::fromUtf8("sliPages"));
        sliPages->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(sliPages, 4, 0, 1, 1);

        scrollDisplay = new QScrollArea(layoutWidget_2);
        scrollDisplay->setObjectName(QString::fromUtf8("scrollDisplay"));
        scrollDisplay->setWidgetResizable(true);
        scrollDisplay->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 352, 322));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lblDisplay = new QLabel(scrollAreaWidgetContents_3);
        lblDisplay->setObjectName(QString::fromUtf8("lblDisplay"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lblDisplay->sizePolicy().hasHeightForWidth());
        lblDisplay->setSizePolicy(sizePolicy5);
        lblDisplay->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        lblDisplay->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblDisplay, 0, 0, 1, 1);

        scrollDisplay->setWidget(scrollAreaWidgetContents_3);

        gridLayout_3->addWidget(scrollDisplay, 0, 0, 1, 1);

        cmdCancelDownload = new QPushButton(layoutWidget_2);
        cmdCancelDownload->setObjectName(QString::fromUtf8("cmdCancelDownload"));

        gridLayout_3->addWidget(cmdCancelDownload, 3, 0, 1, 1);

        splitter->addWidget(layoutWidget_2);

        gridLayout_4->addWidget(splitter, 1, 0, 1, 1);

        listWidgetThumb = new QListWidget(frame);
        listWidgetThumb->setObjectName(QString::fromUtf8("listWidgetThumb"));
        listWidgetThumb->setMinimumSize(QSize(0, 100));
        listWidgetThumb->setMaximumSize(QSize(16777215, 100));
        listWidgetThumb->setFlow(QListView::LeftToRight);

        gridLayout_4->addWidget(listWidgetThumb, 0, 0, 1, 1);


        gridLayout_5->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(PDFViewer);

        QMetaObject::connectSlotsByName(PDFViewer);
    } // setupUi

    void retranslateUi(QDialog *PDFViewer)
    {
        PDFViewer->setWindowTitle(QApplication::translate("PDFViewer", "PDFViewer", nullptr));
        lblCaption->setText(QApplication::translate("PDFViewer", "TextLabel", nullptr));
#ifndef QT_NO_TOOLTIP
        edtLink->setToolTip(QApplication::translate("PDFViewer", "Drag and Drop", nullptr));
#endif // QT_NO_TOOLTIP
        cmdAddLink->setText(QApplication::translate("PDFViewer", "add link to catalog", nullptr));
        cmdSectionSettings->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdDownload->setToolTip(QApplication::translate("PDFViewer", "Download missing files", nullptr));
#endif // QT_NO_TOOLTIP
        cmdDownload->setText(QString());
        lblInfo->setText(QApplication::translate("PDFViewer", "TextLabel", nullptr));
        grpInformations->setTitle(QString());
        lblAnmerkung->setText(QApplication::translate("PDFViewer", "Anmerkungen:", nullptr));
        cmdSaveInfos->setText(QString());
        cmdRemoveMetaData->setText(QApplication::translate("PDFViewer", "remove selected tag", nullptr));
        lblNummer->setText(QApplication::translate("PDFViewer", "Nummer:", nullptr));
        lblMonat->setText(QApplication::translate("PDFViewer", "Monat:", nullptr));
        label->setText(QApplication::translate("PDFViewer", "Jahrgang:", nullptr));
        lblLogo->setText(QApplication::translate("PDFViewer", "Logo", nullptr));
        groupBox->setTitle(QString());
        lblBerlag->setText(QApplication::translate("PDFViewer", "Verlag:", nullptr));
        lblISSN->setText(QApplication::translate("PDFViewer", "ISSN:", nullptr));
        lblErstausgabe->setText(QApplication::translate("PDFViewer", "Erstausgabe:", nullptr));
        lblISSN_3->setText(QApplication::translate("PDFViewer", "Einstellung:", nullptr));
        cmdBackward->setText(QString());
        cmdBookmark->setText(QApplication::translate("PDFViewer", "Bookmark this page", nullptr));
        cmdForward->setText(QString());
        lblPage->setText(QApplication::translate("PDFViewer", "Seite:", nullptr));
        edtPage->setText(QApplication::translate("PDFViewer", "1", nullptr));
        lblScalefactor->setText(QApplication::translate("PDFViewer", "Skalierfaktor:", nullptr));
        cmdExtract->setText(QString());
        cmdUpload->setText(QString());
        lblDisplay->setText(QString());
        cmdCancelDownload->setText(QApplication::translate("PDFViewer", "cancle download...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PDFViewer: public Ui_PDFViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFVIEWER_H
