/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_18;
    QGridLayout *gridLayout;
    QLabel *diaText;
    QLabel *label_8;
    QLabel *label_13;
    QLabel *vehicleText;
    QPushButton *openVprofile;
    QPushButton *clearVprofile;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *mainCombo;
    QPushButton *w_button;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QComboBox *combo_p;
    QFrame *sframe;
    QLabel *profile_status;
    QPushButton *clear_p;
    QPushButton *clear_plot_capture;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *capture;
    QPushButton *pauseButton;
    QPushButton *stopCapture;
    QPushButton *savetoprofile_r;
    QWidget *tab_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *p1CheckBox;
    QCheckBox *p2CheckBox;
    QCheckBox *p3CheckBox;
    QCheckBox *p4CheckBox;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *updatepPlotView;
    QPushButton *saveAs;
    QPushButton *saveImage;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *openCSV;
    QComboBox *copyProfileCombo;
    QPushButton *copyToProfile;
    QLabel *copyProfileStatus;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QComboBox *chartviewtype;
    QVBoxLayout *verticalLayout_5;
    QPushButton *clearplotcompare;
    QPushButton *clearAllProfile;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *customPlot;
    QProgressBar *progressBar;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *powerDial;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *trqDial;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *rpmDial;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLCDNumber *maxpwr;
    QLabel *label_9;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_9;
    QLCDNumber *maxtrq;
    QLabel *label_10;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_10;
    QLCDNumber *maxrpm;
    QLabel *label_11;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_11;
    QLCDNumber *Maxspeed;
    QLabel *label_12;
    QFrame *line;
    QFrame *line_3;
    QWidget *verticalLayoutWidget_7;
    QVBoxLayout *speedDial;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuDynamometer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1920, 1000);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setMaximumSize(QSize(1920, 1080));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(-10, 540, 471, 391));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(false);
        font1.setWeight(50);
        tabWidget->setFont(font1);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 441, 321));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_18 = new QLabel(verticalLayoutWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setPointSize(15);
        font2.setBold(true);
        font2.setWeight(75);
        label_18->setFont(font2);
        label_18->setFrameShape(QFrame::WinPanel);
        label_18->setFrameShadow(QFrame::Raised);
        label_18->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(label_18);


        verticalLayout->addLayout(horizontalLayout_12);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        diaText = new QLabel(verticalLayoutWidget);
        diaText->setObjectName(QString::fromUtf8("diaText"));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setWeight(50);
        diaText->setFont(font3);
        diaText->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(diaText, 2, 1, 1, 1);

        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font4;
        font4.setPointSize(15);
        font4.setBold(true);
        font4.setUnderline(true);
        font4.setWeight(75);
        label_8->setFont(font4);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        label_13 = new QLabel(verticalLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font4);
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_13, 1, 1, 1, 1);

        vehicleText = new QLabel(verticalLayoutWidget);
        vehicleText->setObjectName(QString::fromUtf8("vehicleText"));
        vehicleText->setFont(font3);
        vehicleText->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(vehicleText, 2, 0, 1, 1);

        openVprofile = new QPushButton(verticalLayoutWidget);
        openVprofile->setObjectName(QString::fromUtf8("openVprofile"));

        gridLayout->addWidget(openVprofile, 1, 2, 1, 1);

        clearVprofile = new QPushButton(verticalLayoutWidget);
        clearVprofile->setObjectName(QString::fromUtf8("clearVprofile"));

        gridLayout->addWidget(clearVprofile, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("PibotoLt"));
        font5.setPointSize(12);
        font5.setBold(true);
        font5.setWeight(75);
        label_2->setFont(font5);

        horizontalLayout->addWidget(label_2);

        mainCombo = new QComboBox(verticalLayoutWidget);
        mainCombo->setObjectName(QString::fromUtf8("mainCombo"));

        horizontalLayout->addWidget(mainCombo);

        w_button = new QPushButton(verticalLayoutWidget);
        w_button->setObjectName(QString::fromUtf8("w_button"));

        horizontalLayout->addWidget(w_button);


        verticalLayout->addLayout(horizontalLayout);

        label_19 = new QLabel(verticalLayoutWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy2.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy2);
        label_19->setFont(font2);
        label_19->setFrameShape(QFrame::WinPanel);
        label_19->setFrameShadow(QFrame::Raised);
        label_19->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_19);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 5);
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setFont(font5);

        horizontalLayout_3->addWidget(label_4);

        combo_p = new QComboBox(verticalLayoutWidget);
        combo_p->addItem(QString());
        combo_p->addItem(QString());
        combo_p->addItem(QString());
        combo_p->addItem(QString());
        combo_p->setObjectName(QString::fromUtf8("combo_p"));
        sizePolicy2.setHeightForWidth(combo_p->sizePolicy().hasHeightForWidth());
        combo_p->setSizePolicy(sizePolicy2);
        combo_p->setFont(font1);

        horizontalLayout_3->addWidget(combo_p);

        sframe = new QFrame(verticalLayoutWidget);
        sframe->setObjectName(QString::fromUtf8("sframe"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(20);
        sizePolicy3.setHeightForWidth(sframe->sizePolicy().hasHeightForWidth());
        sframe->setSizePolicy(sizePolicy3);
        sframe->setMinimumSize(QSize(0, 30));
        sframe->setAutoFillBackground(false);
        sframe->setFrameShape(QFrame::StyledPanel);
        sframe->setFrameShadow(QFrame::Sunken);
        profile_status = new QLabel(sframe);
        profile_status->setObjectName(QString::fromUtf8("profile_status"));
        profile_status->setGeometry(QRect(0, 0, 81, 31));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(profile_status->sizePolicy().hasHeightForWidth());
        profile_status->setSizePolicy(sizePolicy4);
        QFont font6;
        font6.setPointSize(15);
        font6.setBold(false);
        font6.setItalic(true);
        font6.setUnderline(true);
        font6.setWeight(50);
        profile_status->setFont(font6);
        profile_status->setFrameShape(QFrame::NoFrame);
        profile_status->setFrameShadow(QFrame::Plain);
        profile_status->setAlignment(Qt::AlignCenter);
        profile_status->setWordWrap(true);

        horizontalLayout_3->addWidget(sframe);

        clear_p = new QPushButton(verticalLayoutWidget);
        clear_p->setObjectName(QString::fromUtf8("clear_p"));
        sizePolicy2.setHeightForWidth(clear_p->sizePolicy().hasHeightForWidth());
        clear_p->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(clear_p);


        verticalLayout->addLayout(horizontalLayout_3);

        clear_plot_capture = new QPushButton(verticalLayoutWidget);
        clear_plot_capture->setObjectName(QString::fromUtf8("clear_plot_capture"));

        verticalLayout->addWidget(clear_plot_capture);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        capture = new QPushButton(verticalLayoutWidget);
        capture->setObjectName(QString::fromUtf8("capture"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(capture->sizePolicy().hasHeightForWidth());
        capture->setSizePolicy(sizePolicy5);
        QFont font7;
        font7.setPointSize(22);
        font7.setBold(false);
        font7.setWeight(50);
        capture->setFont(font7);

        horizontalLayout_4->addWidget(capture);

        pauseButton = new QPushButton(verticalLayoutWidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        sizePolicy5.setHeightForWidth(pauseButton->sizePolicy().hasHeightForWidth());
        pauseButton->setSizePolicy(sizePolicy5);
        pauseButton->setFont(font7);

        horizontalLayout_4->addWidget(pauseButton);

        stopCapture = new QPushButton(verticalLayoutWidget);
        stopCapture->setObjectName(QString::fromUtf8("stopCapture"));
        sizePolicy5.setHeightForWidth(stopCapture->sizePolicy().hasHeightForWidth());
        stopCapture->setSizePolicy(sizePolicy5);
        stopCapture->setFont(font7);

        horizontalLayout_4->addWidget(stopCapture);

        savetoprofile_r = new QPushButton(verticalLayoutWidget);
        savetoprofile_r->setObjectName(QString::fromUtf8("savetoprofile_r"));
        sizePolicy5.setHeightForWidth(savetoprofile_r->sizePolicy().hasHeightForWidth());
        savetoprofile_r->setSizePolicy(sizePolicy5);
        savetoprofile_r->setFont(font7);

        horizontalLayout_4->addWidget(savetoprofile_r);


        verticalLayout->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayoutWidget_3 = new QWidget(tab_2);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(9, 9, 431, 341));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy4.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy4);
        label_3->setFont(font2);
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setLineWidth(4);
        label_3->setMidLineWidth(2);
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setWordWrap(false);
        label_3->setIndent(-3);

        verticalLayout_2->addWidget(label_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        p1CheckBox = new QCheckBox(verticalLayoutWidget_3);
        p1CheckBox->setObjectName(QString::fromUtf8("p1CheckBox"));
        p1CheckBox->setFont(font1);

        horizontalLayout_5->addWidget(p1CheckBox);

        p2CheckBox = new QCheckBox(verticalLayoutWidget_3);
        p2CheckBox->setObjectName(QString::fromUtf8("p2CheckBox"));
        p2CheckBox->setFont(font1);

        horizontalLayout_5->addWidget(p2CheckBox);

        p3CheckBox = new QCheckBox(verticalLayoutWidget_3);
        p3CheckBox->setObjectName(QString::fromUtf8("p3CheckBox"));
        p3CheckBox->setFont(font1);

        horizontalLayout_5->addWidget(p3CheckBox);

        p4CheckBox = new QCheckBox(verticalLayoutWidget_3);
        p4CheckBox->setObjectName(QString::fromUtf8("p4CheckBox"));
        p4CheckBox->setFont(font1);

        horizontalLayout_5->addWidget(p4CheckBox);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        updatepPlotView = new QPushButton(verticalLayoutWidget_3);
        updatepPlotView->setObjectName(QString::fromUtf8("updatepPlotView"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(updatepPlotView->sizePolicy().hasHeightForWidth());
        updatepPlotView->setSizePolicy(sizePolicy6);
        QFont font8;
        font8.setPointSize(16);
        font8.setBold(false);
        font8.setWeight(50);
        updatepPlotView->setFont(font8);

        horizontalLayout_6->addWidget(updatepPlotView);

        saveAs = new QPushButton(verticalLayoutWidget_3);
        saveAs->setObjectName(QString::fromUtf8("saveAs"));
        sizePolicy6.setHeightForWidth(saveAs->sizePolicy().hasHeightForWidth());
        saveAs->setSizePolicy(sizePolicy6);
        saveAs->setFont(font8);

        horizontalLayout_6->addWidget(saveAs);

        saveImage = new QPushButton(verticalLayoutWidget_3);
        saveImage->setObjectName(QString::fromUtf8("saveImage"));
        sizePolicy5.setHeightForWidth(saveImage->sizePolicy().hasHeightForWidth());
        saveImage->setSizePolicy(sizePolicy5);

        horizontalLayout_6->addWidget(saveImage);


        verticalLayout_2->addLayout(horizontalLayout_6);

        label_6 = new QLabel(verticalLayoutWidget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy4.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy4);
        label_6->setFont(font2);
        label_6->setFrameShape(QFrame::StyledPanel);
        label_6->setLineWidth(4);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        openCSV = new QPushButton(verticalLayoutWidget_3);
        openCSV->setObjectName(QString::fromUtf8("openCSV"));
        sizePolicy6.setHeightForWidth(openCSV->sizePolicy().hasHeightForWidth());
        openCSV->setSizePolicy(sizePolicy6);
        openCSV->setFont(font8);

        horizontalLayout_7->addWidget(openCSV);

        copyProfileCombo = new QComboBox(verticalLayoutWidget_3);
        copyProfileCombo->addItem(QString());
        copyProfileCombo->addItem(QString());
        copyProfileCombo->addItem(QString());
        copyProfileCombo->addItem(QString());
        copyProfileCombo->setObjectName(QString::fromUtf8("copyProfileCombo"));

        horizontalLayout_7->addWidget(copyProfileCombo);

        copyToProfile = new QPushButton(verticalLayoutWidget_3);
        copyToProfile->setObjectName(QString::fromUtf8("copyToProfile"));
        sizePolicy6.setHeightForWidth(copyToProfile->sizePolicy().hasHeightForWidth());
        copyToProfile->setSizePolicy(sizePolicy6);
        copyToProfile->setFont(font8);

        horizontalLayout_7->addWidget(copyToProfile);

        copyProfileStatus = new QLabel(verticalLayoutWidget_3);
        copyProfileStatus->setObjectName(QString::fromUtf8("copyProfileStatus"));
        QFont font9;
        font9.setPointSize(10);
        font9.setBold(false);
        font9.setWeight(50);
        copyProfileStatus->setFont(font9);
        copyProfileStatus->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(copyProfileStatus);


        verticalLayout_2->addLayout(horizontalLayout_7);

        label_5 = new QLabel(verticalLayoutWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font2);
        label_5->setFrameShape(QFrame::StyledPanel);
        label_5->setLineWidth(4);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(verticalLayoutWidget_3);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy4.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy4);
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label);

        chartviewtype = new QComboBox(verticalLayoutWidget_3);
        chartviewtype->addItem(QString());
        chartviewtype->addItem(QString());
        chartviewtype->addItem(QString());
        chartviewtype->addItem(QString());
        chartviewtype->addItem(QString());
        chartviewtype->addItem(QString());
        chartviewtype->addItem(QString());
        chartviewtype->addItem(QString());
        chartviewtype->setObjectName(QString::fromUtf8("chartviewtype"));
        sizePolicy5.setHeightForWidth(chartviewtype->sizePolicy().hasHeightForWidth());
        chartviewtype->setSizePolicy(sizePolicy5);
        chartviewtype->setFont(font3);
        chartviewtype->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_4->addWidget(chartviewtype);


        horizontalLayout_8->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        clearplotcompare = new QPushButton(verticalLayoutWidget_3);
        clearplotcompare->setObjectName(QString::fromUtf8("clearplotcompare"));
        sizePolicy4.setHeightForWidth(clearplotcompare->sizePolicy().hasHeightForWidth());
        clearplotcompare->setSizePolicy(sizePolicy4);

        verticalLayout_5->addWidget(clearplotcompare);

        clearAllProfile = new QPushButton(verticalLayoutWidget_3);
        clearAllProfile->setObjectName(QString::fromUtf8("clearAllProfile"));
        sizePolicy4.setHeightForWidth(clearAllProfile->sizePolicy().hasHeightForWidth());
        clearAllProfile->setSizePolicy(sizePolicy4);

        verticalLayout_5->addWidget(clearAllProfile);


        horizontalLayout_8->addLayout(verticalLayout_5);


        verticalLayout_2->addLayout(horizontalLayout_8);

        tabWidget->addTab(tab_2, QString());
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(480, 10, 1431, 931));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        customPlot = new QCustomPlot(verticalLayoutWidget_2);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setEnabled(true);
        sizePolicy1.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy1);
        customPlot->setFont(font);

        verticalLayout_3->addWidget(customPlot);

        progressBar = new QProgressBar(verticalLayoutWidget_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout_3->addWidget(progressBar);

        verticalLayoutWidget_4 = new QWidget(centralwidget);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(10, 20, 221, 201));
        powerDial = new QVBoxLayout(verticalLayoutWidget_4);
        powerDial->setObjectName(QString::fromUtf8("powerDial"));
        powerDial->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_5 = new QWidget(centralwidget);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(240, 20, 221, 201));
        trqDial = new QVBoxLayout(verticalLayoutWidget_5);
        trqDial->setObjectName(QString::fromUtf8("trqDial"));
        trqDial->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_6 = new QWidget(centralwidget);
        verticalLayoutWidget_6->setObjectName(QString::fromUtf8("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(10, 280, 221, 201));
        rpmDial = new QVBoxLayout(verticalLayoutWidget_6);
        rpmDial->setObjectName(QString::fromUtf8("rpmDial"));
        rpmDial->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 220, 221, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        maxpwr = new QLCDNumber(horizontalLayoutWidget);
        maxpwr->setObjectName(QString::fromUtf8("maxpwr"));
        maxpwr->setAutoFillBackground(false);
        maxpwr->setFrameShape(QFrame::NoFrame);
        maxpwr->setFrameShadow(QFrame::Sunken);
        maxpwr->setLineWidth(3);
        maxpwr->setMidLineWidth(2);
        maxpwr->setDigitCount(5);
        maxpwr->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_2->addWidget(maxpwr);

        label_9 = new QLabel(horizontalLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QFont font10;
        font10.setFamily(QString::fromUtf8("Piboto [Goog]"));
        font10.setPointSize(12);
        font10.setBold(false);
        font10.setItalic(true);
        font10.setWeight(50);
        label_9->setFont(font10);
        label_9->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_2->addWidget(label_9);

        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(240, 220, 221, 41));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        maxtrq = new QLCDNumber(horizontalLayoutWidget_2);
        maxtrq->setObjectName(QString::fromUtf8("maxtrq"));
        maxtrq->setAutoFillBackground(false);
        maxtrq->setFrameShape(QFrame::NoFrame);
        maxtrq->setFrameShadow(QFrame::Sunken);
        maxtrq->setLineWidth(3);
        maxtrq->setMidLineWidth(2);
        maxtrq->setDigitCount(5);
        maxtrq->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_9->addWidget(maxtrq);

        label_10 = new QLabel(horizontalLayoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font10);
        label_10->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_9->addWidget(label_10);

        horizontalLayoutWidget_3 = new QWidget(centralwidget);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 480, 221, 41));
        horizontalLayout_10 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        maxrpm = new QLCDNumber(horizontalLayoutWidget_3);
        maxrpm->setObjectName(QString::fromUtf8("maxrpm"));
        maxrpm->setAutoFillBackground(false);
        maxrpm->setFrameShape(QFrame::NoFrame);
        maxrpm->setFrameShadow(QFrame::Sunken);
        maxrpm->setLineWidth(3);
        maxrpm->setMidLineWidth(2);
        maxrpm->setDigitCount(5);
        maxrpm->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_10->addWidget(maxrpm);

        label_11 = new QLabel(horizontalLayoutWidget_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font10);
        label_11->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_10->addWidget(label_11);

        horizontalLayoutWidget_4 = new QWidget(centralwidget);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(240, 480, 221, 41));
        horizontalLayout_11 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        Maxspeed = new QLCDNumber(horizontalLayoutWidget_4);
        Maxspeed->setObjectName(QString::fromUtf8("Maxspeed"));
        Maxspeed->setAutoFillBackground(false);
        Maxspeed->setFrameShape(QFrame::NoFrame);
        Maxspeed->setFrameShadow(QFrame::Sunken);
        Maxspeed->setLineWidth(3);
        Maxspeed->setMidLineWidth(2);
        Maxspeed->setDigitCount(5);
        Maxspeed->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_11->addWidget(Maxspeed);

        label_12 = new QLabel(horizontalLayoutWidget_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font10);
        label_12->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_11->addWidget(label_12);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 0, 451, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(460, 10, 20, 931));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        verticalLayoutWidget_7 = new QWidget(centralwidget);
        verticalLayoutWidget_7->setObjectName(QString::fromUtf8("verticalLayoutWidget_7"));
        verticalLayoutWidget_7->setGeometry(QRect(240, 280, 221, 201));
        speedDial = new QVBoxLayout(verticalLayoutWidget_7);
        speedDial->setObjectName(QString::fromUtf8("speedDial"));
        speedDial->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 27));
        menuDynamometer = new QMenu(menubar);
        menuDynamometer->setObjectName(QString::fromUtf8("menuDynamometer"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuDynamometer->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Select Vehicle Profile", nullptr));
        diaText->setText(QCoreApplication::translate("MainWindow", "Set Vehicle", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", " Name ", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Wheel Dia (mm)", nullptr));
        vehicleText->setText(QCoreApplication::translate("MainWindow", "Set Vehicle", nullptr));
        openVprofile->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        clearVprofile->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Choose Profile:", nullptr));
        w_button->setText(QCoreApplication::translate("MainWindow", "Set", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Data Capture Control", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Select Profile:", nullptr));
        combo_p->setItemText(0, QCoreApplication::translate("MainWindow", "Profile 1", nullptr));
        combo_p->setItemText(1, QCoreApplication::translate("MainWindow", "Profile 2", nullptr));
        combo_p->setItemText(2, QCoreApplication::translate("MainWindow", "Profile 3", nullptr));
        combo_p->setItemText(3, QCoreApplication::translate("MainWindow", "Profile 4", nullptr));

        profile_status->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        clear_p->setText(QCoreApplication::translate("MainWindow", "Clear Data", nullptr));
        clear_plot_capture->setText(QCoreApplication::translate("MainWindow", "Clear Plot Area", nullptr));
        capture->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        stopCapture->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        savetoprofile_r->setText(QCoreApplication::translate("MainWindow", "Save ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Capture Mode", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Select profile to Compare", nullptr));
        p1CheckBox->setText(QCoreApplication::translate("MainWindow", "Profile 1", nullptr));
        p2CheckBox->setText(QCoreApplication::translate("MainWindow", "Profile 2", nullptr));
        p3CheckBox->setText(QCoreApplication::translate("MainWindow", "Profile 3", nullptr));
        p4CheckBox->setText(QCoreApplication::translate("MainWindow", "Profile 4", nullptr));
#if QT_CONFIG(tooltip)
        updatepPlotView->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        updatepPlotView->setText(QCoreApplication::translate("MainWindow", "Update Plot", nullptr));
        saveAs->setText(QCoreApplication::translate("MainWindow", "save csv", nullptr));
        saveImage->setText(QCoreApplication::translate("MainWindow", "save image", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Upload CSV Data", nullptr));
        openCSV->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        copyProfileCombo->setItemText(0, QCoreApplication::translate("MainWindow", "Profile 1", nullptr));
        copyProfileCombo->setItemText(1, QCoreApplication::translate("MainWindow", "Profile 2", nullptr));
        copyProfileCombo->setItemText(2, QCoreApplication::translate("MainWindow", "Profile 3", nullptr));
        copyProfileCombo->setItemText(3, QCoreApplication::translate("MainWindow", "Profile 4", nullptr));

        copyToProfile->setText(QCoreApplication::translate("MainWindow", "Copy To Profile", nullptr));
        copyProfileStatus->setText(QCoreApplication::translate("MainWindow", "status", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "ChartView Control", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Select Chart View Type:", nullptr));
        chartviewtype->setItemText(0, QCoreApplication::translate("MainWindow", "Power, Torque, RPM vs Time", nullptr));
        chartviewtype->setItemText(1, QCoreApplication::translate("MainWindow", "Power, Torque vs Time", nullptr));
        chartviewtype->setItemText(2, QCoreApplication::translate("MainWindow", "Power vs Time", nullptr));
        chartviewtype->setItemText(3, QCoreApplication::translate("MainWindow", "Torque vs Time", nullptr));
        chartviewtype->setItemText(4, QCoreApplication::translate("MainWindow", "RPM vs Time", nullptr));
        chartviewtype->setItemText(5, QCoreApplication::translate("MainWindow", "Power vs RPM", nullptr));
        chartviewtype->setItemText(6, QCoreApplication::translate("MainWindow", "Torque vs RPM", nullptr));
        chartviewtype->setItemText(7, QCoreApplication::translate("MainWindow", "Power, Torque vs RPM", nullptr));

        clearplotcompare->setText(QCoreApplication::translate("MainWindow", "Clear Plot", nullptr));
        clearAllProfile->setText(QCoreApplication::translate("MainWindow", "Clear All Profiles", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Compare Mode", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "MAX Watts", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "MAX Nm", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "MAX RPM", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "MAX Km/h", nullptr));
        menuDynamometer->setTitle(QCoreApplication::translate("MainWindow", "Dynamometer v1.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
