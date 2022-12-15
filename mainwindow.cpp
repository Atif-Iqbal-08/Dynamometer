/*
 *   Copyright (C) 2022 by Atif Iqbal
 *   http://emfluxmotors.com
 */



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QtDebug>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <QTime>
#include <QProgressDialog>
#include <QFileDialog>
#include <QString>
#include <numeric>
#include <mainwindow.h>
static int CHANNEL =0;
QCPCurve *torqueC;
QCPCurve *powerC;
QCPTextElement *title ;
//QCPCurve *para1;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pauseButton->setCheckable(true);


    setWindowTitle("Emflux Dynanometer Control");
    wiringPiSPISetup(CHANNEL, 500000);
    //############## title #####################
    ui->customPlot->plotLayout()->insertRow(0);
    title = new QCPTextElement(ui->customPlot,"Power,Torque,RPM vs Time");
    ui->customPlot->plotLayout()->addElement(0,0,title);
    ui->customPlot->plotLayout()->element(0,0)->setVisible(true);
    ui->sframe->setStyleSheet("background-color: rgb(0,255,0)");
    on_combo_p_activated(0);
    ui->progressBar->setVisible(false);
    qtime.clear();  qrpm.clear();qpwr.clear();qtrq.clear();
    // power axis at left
    ui->customPlot->axisRect()->addAxis(QCPAxis::atLeft);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,0) ->setPadding(30);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1) ->setPadding(30);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setLabel("Power (Watts)");
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setLabelColor(Qt::black);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setTickLabelColor(Qt::black);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setTickPen(QPen (Qt::black));
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setBasePen(QPen(Qt::black));
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setRange(0,2000);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(true); // set to true
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->grid()->setVisible(true); // set to true
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->grid()->setSubGridVisible(true);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));

    //############# RPM at a x-axis

    ui->customPlot->axisRect()->addAxis(QCPAxis::atBottom);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,0) ->setPadding(30);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1) ->setPadding(30);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setLabel("RPM");
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setLabelColor(Qt::black);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setTickLabelColor(Qt::black);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setTickPen(QPen (Qt::black));
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setBasePen(QPen(Qt::black));
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setRange(0,1000);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(false); // set to true
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->grid()->setVisible(true); // set to true
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->grid()->setSubGridVisible(true);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));



    // Time Axis



    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->xAxis->setTickPen(QPen (Qt::black));
    ui->customPlot->xAxis->setTickLength(5,0);
    ui->customPlot->xAxis->setTickLabelColor(Qt::black);
    ui->customPlot->xAxis->setLabel("Time Elapsed (seconds) ");
    ui->customPlot->xAxis->setLabelColor(Qt::black);
    ui->customPlot->xAxis->setTickLength(1,2);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::black, 1));
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis2->grid()->setSubGridPen(QPen(QColor(140, 140, 140), 1,Qt::DashDotDotLine));

    //yaxis 2 rpm
    ui->customPlot->yAxis2->setLabel("RPM");
    ui->customPlot->yAxis->setLabel("Torque (Nm) ");
    ui->customPlot->yAxis2->setLabelColor(Qt::black);
    ui->customPlot->yAxis2->setBasePen(QPen(Qt::black, 2));
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis2->grid()->setSubGridPen(QPen(QColor(200, 150, 80), 1,Qt::DashDotDotLine));
    ui->customPlot->yAxis2->grid()->setPen(QPen(QColor(200, 150, 80), 1,Qt::DashDotDotLine));




    ui->customPlot->yAxis->setRange(0,200);
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(150, 150, 80), 1,Qt::DashLine));
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(150, 150, 80), 1,Qt::DashLine));
    ui->customPlot->yAxis2->setRange(0,1500);
    ui->customPlot->yAxis2->setTicks(true);
    ui->customPlot->yAxis2->setTickLabelColor(Qt::black);
    ui->customPlot->yAxis2->setTickLabels(true);
    ui->customPlot->yAxis2->setVisible(true);

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setFont(QFont(font().family(), 12));


    ui->customPlot->legend->setBrush(QColor(255,255,255,150));
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);

    QPen pen0;
    pen0.setWidth(2);
    pen0.setColor(QColor(0,0,255));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    ui->customPlot->graph(0)->setPen(pen0);
    ui->customPlot->graph(0)->setName("Torque");
    ui->customPlot->graph(0)->setVisible(false);
    ui->customPlot->graph(0)->removeFromLegend();

    // tring out new curve plot ####################### umcomment the above if it dosnt work ###########################

    torqueC = new QCPCurve(ui->customPlot->xAxis,ui->customPlot->yAxis);
    torqueC->setPen(pen0);
    torqueC->setName("Torque");
    torqueC->setVisible(true);
    // torqueC->removeFromLegend();

    QPen pen1;
    pen1.setWidth(2);
    pen1.setColor(QColor(0,255,0));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis2);
    ui->customPlot->graph(1)->setPen(pen1);
    ui->customPlot->graph(1)->setName("RPM");
    //ui->customPlot->graph(1)->removeFromLegend();
    ui->customPlot->graph(1)->setVisible(true);


    QPen pen2;
    pen2.setWidth(2);
    pen2.setColor(QColor(255,0,0));

    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(2)->setPen(pen2);
    ui->customPlot->graph(2)->setName("Power");
    ui->customPlot->graph(2)->removeFromLegend();
    ui->customPlot->graph(2)->setVisible(false);

    powerC = new QCPCurve(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    powerC->setPen(pen2);
    powerC->setName("POWER Watts");
    powerC->setVisible(true);
    // powerC->removeFromLegend();





    graphsetup();


    on_p1CheckBox_toggled(false);
    on_p2CheckBox_toggled(false);
    on_p3CheckBox_toggled(false);
    on_p4CheckBox_toggled(false);
    ui->tabWidget->setCurrentIndex(0);
    on_chartviewtype_activated(0);
    ok=true;
    on_clearVprofile_clicked();


    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);



    //----------------------- dials setup -----------------------------//

    //------------------- SPEED DIAL-----------------------------//

    mSpeedGauge = new QcGaugeWidget;
    mSpeedGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::white);
    bkg2->addColor(1.0,Qt::darkGray);

    mSpeedGauge->addArc(55);
    deg1 = mSpeedGauge->addDegrees(65);

    deg1->setValueRange(0,200);
    deg1->setStep(20);
    deg1->setSubDegree(false);


    mSpeedGauge->addColorBand(50);


    v1 = mSpeedGauge->addValues(80);
    v1->setValueRange(0,200);
    v1->setStep(20);

    mSpeedGauge->addLabel(70)->setText("Km/h");


    QcLabelItem *lab = mSpeedGauge->addLabel(55);
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(70);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::red);
    mSpeedNeedle->setValueRange(0,200);
    mSpeedGauge->addBackground(5);
    mSpeedGauge->addGlass(88);
    ui->speedDial->addWidget(mSpeedGauge);

    //------------------- Power DIAL-----------------------------//

    mPowerGuage = new QcGaugeWidget;
    mPowerGuage->addBackground(99);
    QcBackgroundItem *bkg3 = mPowerGuage->addBackground(92);
    bkg3->clearrColors();
    bkg3->addColor(0.1,Qt::black);
    bkg3->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg4 = mPowerGuage->addBackground(88);
    bkg4->clearrColors();
    bkg4->addColor(0.1,Qt::white);
    bkg4->addColor(1.0,Qt::darkGray);

    mPowerGuage->addArc(55);
    deg2 = mPowerGuage->addDegrees(65);
    deg2->setValueRange(0,80);
    deg2->setStep(10);
    mPowerGuage->addColorBand(50);

    v2=mPowerGuage->addValues(80);
    v2->setValueRange(0,80);
    v2->setStep(10);
    //mPowerGuage->addLabel(55)->setText("");
    mPowerGuage->addLabel(70)->setText("KW");

    QcLabelItem *lab2 = mPowerGuage->addLabel(55);
    lab2->setText("0");
    mPowerNeedle = mPowerGuage->addNeedle(60);
    mPowerNeedle->setLabel(lab2);
    mPowerNeedle->setColor(Qt::red);
    mPowerNeedle->setValueRange(0,80);
    mPowerGuage->addBackground(5);
    mPowerGuage->addGlass(88);
    ui->powerDial->addWidget(mPowerGuage);



    //------------------- Torque DIAL-----------------------------//

    mTorqueGuage = new QcGaugeWidget;
    mTorqueGuage->addBackground(99);
    QcBackgroundItem *bkg5 = mTorqueGuage->addBackground(92);
    bkg5->clearrColors();
    bkg5->addColor(0.1,Qt::black);
    bkg5->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg6 = mTorqueGuage->addBackground(88);
    bkg6->clearrColors();
    bkg6->addColor(0.1,Qt::white);
    bkg6->addColor(1.0,Qt::darkGray);

    mTorqueGuage->addArc(45);
    deg3=mTorqueGuage->addDegrees(55);
    deg3->setValueRange(0,1000);
    deg3->setStep(100);
    mTorqueGuage->addColorBand(40);

    v3=mTorqueGuage->addValues(70);
    v3->setValueRange(0,1000);
    v3->setStep(100);

    mTorqueGuage->addLabel(70)->setText("Torque Nm");
    // mTorqueGuage->addLabel(55)->setText("x10");
    QcLabelItem *lab3 = mTorqueGuage->addLabel(55);
    lab3->setText("0");
    mTorqueNeedle = mTorqueGuage->addNeedle(70);
    mTorqueNeedle->setLabel(lab3);
    mTorqueNeedle->setColor(Qt::red);
    mTorqueNeedle->setValueRange(0,1000);
    mTorqueGuage->addBackground(5);
    mTorqueGuage->addGlass(88);
    ui->trqDial->addWidget(mTorqueGuage);



    //------------------- RPM DIAL-----------------------------//

    mRpmGuage = new QcGaugeWidget;
    mRpmGuage->addBackground(99);
    QcBackgroundItem *bkg7 = mRpmGuage->addBackground(92);
    bkg7->clearrColors();
    bkg7->addColor(0.1,Qt::black);
    bkg7->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg8 = mRpmGuage->addBackground(88);
    bkg8->clearrColors();
    bkg8->addColor(0.1,Qt::white);
    bkg8->addColor(1.0,Qt::darkGray);

    mRpmGuage->addArc(40);
    deg4=mRpmGuage->addDegrees(50);
    deg4->setValueRange(0,3000);
    deg4->setStep(500);
    mRpmGuage->addColorBand(35);


    v4= mRpmGuage->addValues(70);
    v4->setValueRange(0,3000);
    v4->setStep(500);
    //mRpmGuage->addLabel(55)->setText("x1000");
    mRpmGuage->addLabel(70)->setText("RPM");

    QcLabelItem *lab4 = mRpmGuage->addLabel(55);
    lab4->setText("0");
    mRpmNeedle = mRpmGuage->addNeedle(50);
    mRpmNeedle->setLabel(lab4);
    mRpmNeedle->setColor(Qt::red);
    mRpmNeedle->setValueRange(0,3000);
    mRpmGuage->addBackground(5);
    mRpmGuage->addGlass(88);
    ui->rpmDial->addWidget(mRpmGuage);
    statusupdate("Welcome to emflux Dynamometer Control");


     update_combo();
     ui->pauseButton->setDown(false);
     ui->pauseButton->setText("Pause");
     ui->pauseButton->setDisabled(true);

     ui->stopCapture->setDisabled(true);
     ui->savetoprofile_r->setDisabled(true);

}
MainWindow::~MainWindow()
{
    delete ui;
}
//####################################################################################################################//
//---------------------------------------------Set diffrent graphs for the plots -------------------------------------//
//####################################################################################################################//
void MainWindow::update_combo()
{ui->mainCombo->clear();
    QString fileName = "/home/orxa/.config/Vehicle.csv";
    QFile file(fileName);
    if(!file.exists())
    {
        QMessageBox msgBox3;
        msgBox3.setWindowTitle("Information");
        msgBox3.setText("File Doesn't exits. Creating new file");
        msgBox3.setStandardButtons(QMessageBox::Ok);
        QFile file("/home/orxa/.config/Vehicle.csv");
        file.open(QIODevice::ReadWrite);
        msgBox3.exec();
        file.close();

    }
    else
    {  file.open(QIODevice::ReadWrite);
        QTextStream stream(&file);
        QString s ;
        while(!file.atEnd())
        {
            s = file.readLine();
            QStringList tokens = s.split(",");
            ui->mainCombo->addItem(tokens.at(0),tokens.at(1).toFloat());

        }
        file.close();
    }

}
void MainWindow::graphsetup()
{



    //##############################--profile 1 setup--##################################////////////////////
    //#########------Power
    QPen pen3;
    pen3.setWidth(2);
    pen3.setColor(QColor(255,0,0));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(3);
    ui->customPlot->graph(3)->setName("P1 Power");

    ui->customPlot->graph(3)->setPen(pen3);
    ui->customPlot->graph(3)->removeFromLegend();
    //#########------Torque
    QPen pen4;
    pen4.setWidth(2);
    pen4.setColor(QColor(0,255,0));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    ui->customPlot->graph(4);
    ui->customPlot->graph(4)->setName("P1 Torque");

    ui->customPlot->graph(4)->setPen(pen4);
    ui->customPlot->graph(4)->removeFromLegend();
    //#########------RPM
    QPen pen5;
    pen5.setWidth(2);
    pen5.setColor(QColor(0,0,255));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis2);
    ui->customPlot->graph(5);
    ui->customPlot->graph(5)->setName("P1 RPM");

    ui->customPlot->graph(5)->setPen(pen5);
    ui->customPlot->graph(5)->removeFromLegend();
    //#########------power vs rpm
    QPen pen6;
    pen6.setWidth(2);
    pen6.setColor(QColor(255,0,0));
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(6);
    ui->customPlot->graph(6)->setName("P1 Power");

    ui->customPlot->graph(6)->setPen(pen6);
    ui->customPlot->graph(6)->removeFromLegend();
    //#########------Torque vs rpm
    QPen pen7;
    pen7.setWidth(2);
    pen7.setColor(QColor(0,255,0));
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->yAxis);
    ui->customPlot->graph(7);
    ui->customPlot->graph(7)->setName("P1 Torque");

    ui->customPlot->graph(7)->setPen(pen7);
    ui->customPlot->graph(7)->removeFromLegend();

    //##############################--profile 2 setup--##################################////////////////////
    //#########------Power
    QPen pen8;
    pen8.setWidth(2);
    pen8.setColor(QColor(255,165,0));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(8);
    ui->customPlot->graph(8)->setName("P2 Power");

    ui->customPlot->graph(8)->setPen(pen8);
    //#########------Torque
    QPen pen9;
    pen9.setWidth(2);
    pen9.setColor(QColor(0,128,0));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    ui->customPlot->graph(9);
    ui->customPlot->graph(9)->setName("P2 Torque");

    ui->customPlot->graph(9)->setPen(pen9);
    //#########------RPM
    QPen pen10;
    pen10.setWidth(2);
    pen10.setColor(QColor(127,0,255));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis2);
    ui->customPlot->graph(10);
    ui->customPlot->graph(10)->setName("P2 RPM");

    ui->customPlot->graph(10)->setPen(pen10);

    //#########------power vs rpm
    QPen pen11;
    pen11.setWidth(2);
    pen11.setColor(QColor(255,165,0));


    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(11);
    ui->customPlot->graph(11)->setName("P2 Power");

    ui->customPlot->graph(11)->setPen(pen11);
    //#########------Torque vs rpm
    QPen pen12;
    pen12.setWidth(2);
    pen12.setColor(QColor(0,128,0));


    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->yAxis);
    ui->customPlot->graph(12);
    ui->customPlot->graph(12)->setName("P2 Torque");
    ui->customPlot->graph(12)->setPen(pen12);
    ui->customPlot->graph(8)->removeFromLegend();
    ui->customPlot->graph(9)->removeFromLegend();
    ui->customPlot->graph(10)->removeFromLegend();
    ui->customPlot->graph(11)->removeFromLegend();
    ui->customPlot->graph(12)->removeFromLegend();

    //##############################--profile 3 setup--##################################////////////////////
    //#########------Power
    QPen pen13;
    pen13.setWidth(2);
    pen13.setColor(QColor(153,153,0));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(13);
    ui->customPlot->graph(13)->setName("P3 Power");

    ui->customPlot->graph(13)->setPen(pen13);
    //#########------Torque
    QPen pen14;
    pen14.setWidth(2);
    pen14.setColor(QColor(255,0,255));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    ui->customPlot->graph(14);
    ui->customPlot->graph(14)->setName("P3 Torque");
    ui->customPlot->graph(14)->setPen(pen14);
    //#########------RPM
    QPen pen15;
    pen15.setWidth(2);
    pen15.setColor(QColor(0,204,204));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis2);
    ui->customPlot->graph(15);
    ui->customPlot->graph(15)->setName("P3 RPM");

    ui->customPlot->graph(15)->setPen(pen15);
    //#########------power vs rpm
    QPen pen16;
    pen16.setWidth(2);
    pen16.setColor(QColor(153,153,0));
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(16);
    ui->customPlot->graph(16)->setName("P3 Power");

    ui->customPlot->graph(16)->setPen(pen16);
    //#########------Torque vs rpm
    QPen pen17;
    pen17.setWidth(2);
    pen17.setColor(QColor(255,0,255));
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->yAxis);
    ui->customPlot->graph(17);
    ui->customPlot->graph(17)->setName("P3 Torque");

    ui->customPlot->graph(17)->setPen(pen17);

    ui->customPlot->graph(13)->removeFromLegend();
    ui->customPlot->graph(14)->removeFromLegend();
    ui->customPlot->graph(15)->removeFromLegend();
    ui->customPlot->graph(16)->removeFromLegend();
    ui->customPlot->graph(17)->removeFromLegend();

    //##############################--profile 4 setup--##################################////////////////////
    //#########------Power
    QPen pen18;
    pen18.setWidth(2);
    pen18.setColor(QColor(255,153,153));

    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(18);
    ui->customPlot->graph(18)->setName("P4 Power");

    ui->customPlot->graph(18)->setPen(pen18);
    //#########------Torque
    QPen pen19;
    pen19.setWidth(2);
    pen19.setColor(QColor(204,255,153));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    ui->customPlot->graph(19);
    ui->customPlot->graph(19)->setName("P4 Torque");

    ui->customPlot->graph(19)->setPen(pen19);
    //#########------RPM
    QPen pen20;
    pen20.setWidth(2);
    pen20.setColor(QColor(128,128,128));
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis2);
    ui->customPlot->graph(20);
    ui->customPlot->graph(20)->setName("P4 RPM");

    ui->customPlot->graph(20)->setPen(pen20);
    //#########------power vs rpm
    QPen pen21;
    pen21.setWidth(2);
    pen21.setColor(QColor(255,153,153));

    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(21);
    ui->customPlot->graph(21)->setName("P4 Power");

    ui->customPlot->graph(21)->setPen(pen21);
    //#########------Torque vs rpm
    QPen pen22;
    pen22.setWidth(2);
    pen22.setColor(QColor(204,255,153));
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->yAxis);
    ui->customPlot->graph(22);
    ui->customPlot->graph(22)->setName("P4 Torque");

    ui->customPlot->graph(22)->setPen(pen22);

    ui->customPlot->graph(18)->removeFromLegend();
    ui->customPlot->graph(19)->removeFromLegend();
    ui->customPlot->graph(20)->removeFromLegend();
    ui->customPlot->graph(21)->removeFromLegend();
    ui->customPlot->graph(22)->removeFromLegend();

}
//####################################################################################################################//
//---------------------------------------------Status Bar Update on each action---------------------------------------//
//####################################################################################################################//
void MainWindow::statusupdate(QString message)
{
    ui->statusbar->showMessage(message);
}
//####################################################################################################################//
//---------------------------------------------data caputing and computing area---------------------------------------//
//####################################################################################################################//
void MainWindow::clearTemp()
{
    qtime.clear();  qrpm.clear();qpwr.clear();qtrq.clear();qspeed.clear();
    powerC->data()->clear(); torqueC->data()->clear(); ui->customPlot->graph(1)->data()->clear();
}
//---- actual loop
void MainWindow::realtimeDataSlot()
{    // calculate two new data points:
    double key = timer.elapsed()/1000.0; // time elapsed since start of demo, in seconds

    if (key-lastPointKey > 0.005) // at most add point every 2 ms
    {
        //double rpm= 0;
        //double torq= 0;
        //double power = 0;
        spi();
        t = torque(instW,instA);
        p = powercal(t);
        if (c1>100)
        {
            if(c<100)
            {  t = torque(instW,instA);
                p = powercal(t);
                MATRQ.append(t);
                MAPWR.append(p);
                //qDebug()<<MAPWR;
                c++;
                lastPointKey = key;
            }else if(c>24)
            {

                MATRQ.pop_front();
                MAPWR.pop_front();

                // qDebug()<<" push_back work";
                //qDebug()<<MAPWR;
                MATRQ.push_back(t);
                MAPWR.push_back(p);
                //qDebug()<<MAPWR;
                avg_trq = avgtrq();
                avg_pwr = avgpwr();
                Vspeed = speed();
                //qDebug()<< " Power avg "<< avg_pwr;
                ui->customPlot->graph(1)->addData(key, RPMWHEEL);
                //ui->customPlot->graph(0)->addData(key, avg_trq);//------------------------- uncomment if qcp graph fails
                torqueC->addData(key, avg_trq);
                //ui->customPlot->graph(2)->addData(key,avg_pwr);// ------------------------- uncomment if qcp graph fails
                powerC->addData(key, avg_pwr);
                //------------------------------dial display ------------------------------//


                mPowerNeedle->setCurrentValue(avg_pwr/1000);
                mTorqueNeedle->setCurrentValue(avg_trq);
                mRpmNeedle->setCurrentValue(RPMWHEEL);
                mSpeedNeedle->setCurrentValue(Vspeed);

                max(RPMWHEEL,avg_trq,avg_pwr,Vspeed);


                //ui->rpm->display(RPMWHEEL);
                //ui->torque->display(avg_trq);
                //ui->power->display(avg_pwr);
                // rescale value (vertical) axis to fit the current data:
                //ui->customPlot->graph(0)->rescaleValueAxis(true);// ------------------------- uncomment if qcp graph fails
                torqueC->rescaleValueAxis(true);
                powerC->rescaleValueAxis(true);

                //ui->customPlot->graph(2)->rescaleValueAxis(true); //------------------------- uncomment if qcp graph fails
                ui->customPlot->graph(1)->rescaleValueAxis(true);
                lastPointKey = key;
                qtime.append(key);
                qrpm.append(RPMWHEEL);
                qpwr.append(avg_pwr);
                qtrq.append(avg_trq);
                qspeed.append(Vspeed);



            }

            c++;

        }

        c1++;
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(0, lastPointKey+8, Qt::AlignLeading);
    //ui->customPlot->yAxis2->setRange(0, RPMWHEEL+50, Qt::AlignLeading);

    ui->customPlot->replot();
    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        ui->statusbar->showMessage(
                    QString("%1 FPS, Total Data points: %2")
                    .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                    .arg(ui->customPlot->graph(1)->data()->size()+ui->customPlot->graph(1)->data()->size())
                    , 0);
        lastFpsKey = key;
        frameCount = 0;
    }
}
//--- spi data receiving part
void MainWindow::spi()
{


    //    long int ltw = 0;
    wiringPiSPIDataRW(CHANNEL, buffer , 4);
    instW = (buffer[1] + 256 * buffer[0]) / 100;
    instA = (buffer[3] + 256 * buffer[2]) / 100;
    //qDebug()<<"buff2 = " << buffer[2] << " buff 3 = " << buffer[3];
    if(instA > 255)
    {
        instA = instA - 655;
    }
    qDebug()<< " rpm = " << instW * 9.56 << " rev/sec";
    qDebug()<< "accel = "<<instA << " rad/sec2\n";
    memset(buffer, 0, 4);

}
//-- function to calculate power
double MainWindow::powercal(double t)
{
    return (t*Ww);
}
//----function to calculate torque
double MainWindow::torque(double Wr, double Ar)
{    //qDebug()<<a;
    if(Wr==0 )
    {
        return 0;
    }

    else

    {
        Rpmr = Wr * 9.55;
        RPMWHEEL = (215/wheeldia)*Rpmr;
        Ww = 0.104*RPMWHEEL;
        double Tr = 1.41 * Ar;
        wr1=Wr;
        return ((Wr/Ww)*Tr);

    }

}
//---- function to determine highest value of reading
void MainWindow::max(double arpm, double atrq, double apwr, double bspeed)
{
    if(arpm>maxrpm && arpm < 5000)
        maxrpm=arpm;
    if(atrq>maxtrq && atrq<2000)
        maxtrq=atrq;
    if(apwr>maxpwr &&  apwr<100000)
        maxpwr=apwr;
    if(bspeed>maxspeed &&  bspeed<200)
        maxspeed=bspeed;

    ui->maxrpm->display(maxrpm);
    ui->maxtrq->display(maxtrq);
    ui->maxpwr->display(maxpwr);
    ui->Maxspeed->display(maxspeed);
}
//---- function to calculate mean of fixed sample size
double MainWindow::avgtrq()
{
    return 1*std::accumulate(MATRQ.begin(),MATRQ.end(), 0LL)/MATRQ.size();


}
//---- function to calculate speed of vehicle
double MainWindow::speed()
{ if(RPMWHEEL==0)
        return 0;
    else

        return 0.001885*RPMWHEEL*(wheeldia/10);
}
//---- function to calculate mean power of fixed sample size
double MainWindow::avgpwr()
{
    return 1*std::accumulate(MAPWR.begin(),MAPWR.end(), 0LL)/MAPWR.size();

}
void MainWindow::setdialreading()
{
    //double max = *std::max_element(vec.constBegin(), vec.constEnd());

    //----------power------ max //


mpwr= 0; mtrq =0; mrpm =0; mspd =0;

    if(p1!=false)
    {       mpwr =*std::max_element(p1_pwr.constBegin(),p1_pwr.constEnd());
            mtrq =*std::max_element(p1_trq.constBegin(),p1_trq.constEnd());
            mrpm =*std::max_element(p1_rpm.constBegin(),p1_rpm.constEnd());
            mspd =*std::max_element(p1_speed.constBegin(),p1_speed.constEnd());


    }else if (p2!=false)
    {
        mpwr =*std::max_element(p2_pwr.constBegin(),p2_pwr.constEnd());
                    mtrq =*std::max_element(p2_trq.constBegin(),p2_trq.constEnd());
                    mrpm =*std::max_element(p2_rpm.constBegin(),p2_rpm.constEnd());
                    mspd =*std::max_element(p2_speed.constBegin(),p2_speed.constEnd());

    }else if (p3!=false)
    {

        mpwr =*std::max_element(p3_pwr.constBegin(),p3_pwr.constEnd());
                    mtrq =*std::max_element(p3_trq.constBegin(),p3_trq.constEnd());
                    mrpm =*std::max_element(p3_rpm.constBegin(),p3_rpm.constEnd());
                    mspd =*std::max_element(p3_speed.constBegin(),p3_speed.constEnd());



    } else if(p4!=false)
    {
        mpwr =*std::max_element(p4_pwr.constBegin(),p4_pwr.constEnd());
                    mtrq =*std::max_element(p4_trq.constBegin(),p4_trq.constEnd());
                    mrpm =*std::max_element(p4_rpm.constBegin(),p4_rpm.constEnd());
                    mspd =*std::max_element(p4_speed.constBegin(),p4_speed.constEnd());

    }





    double Xp=mpwr;
    double Xt=mtrq;

    double Xr=mrpm;
    double Xs = mspd;





    mPowerNeedle->setCurrentValue(Xp/1000);
    mTorqueNeedle->setCurrentValue(Xt);
    mRpmNeedle->setCurrentValue(Xr);
    mSpeedNeedle->setCurrentValue(Xs);
    ui->maxrpm->display(Xr);
    ui->maxtrq->display(Xt);
    ui->maxpwr->display(Xp);
    ui->Maxspeed->display(Xs);



}

void MainWindow::needleclear()
{
    mPowerNeedle->setCurrentValue(0.0);
    mTorqueNeedle->setCurrentValue(0.0);
    mRpmNeedle->setCurrentValue(0.0);
    mSpeedNeedle->setCurrentValue(0.0);
    ui->maxrpm->display(0);
    ui->maxtrq->display(0);
    ui->maxpwr->display(0);
    ui->Maxspeed->display(0);


}

//####################################################################################################################//
//---------------------------------------------Button Assignment and logic computing area-----------------------------//
//####################################################################################################################//
void MainWindow::on_w_button_clicked()
{
    ok = true;


        qDebug()<<"set clicked";
        wheeldia = ui->mainCombo->itemData(ui->mainCombo->currentIndex()).value<float>();
        statusupdate("Wheel diameter entered is: "+QString::number(wheeldia) + " mm . Select Profile To begin ");

       // QString b = QString::number(wheeldia);
        // ui->w_Status->setText(b);
        //on_combo_p_activated(0);
        ui->w_button->setDisabled(true);
        ui->clearVprofile->setDisabled(false);
        qDebug()<<wheeldia;

        ui->openVprofile->setDisabled(true);

}
void MainWindow::on_combo_p_activated(int index)
{
    if (ok!=false)
    {
        switch(index)
        {case 0:
            statusupdate("profile 1 selected");
            if(p1_rpm.isEmpty()!=true)
            { ui->profile_status->setText("Has data");
                ui->sframe->setStyleSheet("background-color: rgb(255,0,0)");
            }
            else
            {       ui->profile_status->setText("Empty");
                ui->sframe->setStyleSheet("background-color: rgb(0,255,0)");
            }

            p_index = 0;

            break;
        case 1:
            statusupdate("profile 2 selected");
            if(p2_rpm.isEmpty()!=true)
            {  ui->profile_status->setText("Has data");
                ui->sframe->setStyleSheet("background-color: rgb(255,0,0)");}
            else
            {   ui->profile_status->setText("Empty");
                ui->sframe->setStyleSheet("background-color: rgb(0,255,0)");}

            p_index = 1;

            break;
        case 2:
            statusupdate("profile 3 selected");
            if(p3_rpm.isEmpty()!=true)
            {   ui->profile_status->setText("Has data");
                ui->sframe->setStyleSheet("background-color: rgb(255,0,0)");}
            else
            {  ui->profile_status->setText("Empty");
                ui->sframe->setStyleSheet("background-color: rgb(0,255,0)");}

            p_index = 2;
            break;
        case 3:
            statusupdate("profile 4 selected");
            if(p4_rpm.isEmpty()!=true)
            {    ui->profile_status->setText("Has data");
                ui->sframe->setStyleSheet("background-color: rgb(255,0,0)");}
            else
            {  ui->profile_status->setText("Empty");
                ui->sframe->setStyleSheet("background-color: rgb(0,255,0)");}

            p_index = 3;
            break;
        }
    }
    else
    {
        statusupdate("Enter WHEEL Diameter to select profile and begin: " );
    }}
void MainWindow::on_savetoprofile_r_clicked()
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("Overwrite warning");
    msgBox.setText("Do you want to overwrite the previous data?");
    // msgBox.addButton(QMessageBox::Yes);
    msgBox.setStandardButtons(QMessageBox::Yes);

    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

needleclear();

    QMessageBox msgBox1;
    msgBox1.setWindowTitle("Information");
    msgBox1.setText("Values has been Written to the selected profile");
    // msgBox.addButton(QMessageBox::Yes);
    msgBox1.setStandardButtons(QMessageBox::Ok);



    if (qtime.isEmpty()==false )
    {
        ui->progressBar->setVisible(true);
        ui->progressBar->setMaximum(qtime.size());
        ui->progressBar->setTextVisible(false);

        switch(p_index)
        {    case 0:

        {

            if(p1_time.isEmpty()==true)
            {   ui->customPlot->graph(3)->data()->clear();
                ui->customPlot->graph(4)->data()->clear();
                ui->customPlot->graph(5)->data()->clear();
                ui->customPlot->graph(6)->data()->clear();
                ui->customPlot->graph(7)->data()->clear();

                for (int i=0 ; i<10000;i++)
                {

                    ui->progressBar->setValue(i);

                   // qDebug()<<"value "<<qtime.at(i);
                   // p1_time.append(qtime.at(i));
                    //p1_pwr.append(qpwr.at(i));
                    //p1_rpm.append(qrpm.at(i));
                    //p1_trq.append(qtrq.at(i));
} ui->progressBar->setVisible(false);

                   // ui->customPlot->graph(3)->addData(p1_time,p1_pwr);
                    //ui->customPlot->graph(4)->addData(p1_time,p1_trq);
                    //ui->customPlot->graph(5)->addData(p1_time,p1_rpm);
                    //ui->customPlot->graph(6)->addData(p1_rpm,p1_pwr);
                    //ui->customPlot->graph(7)->addData(p1_rpm,p1_trq);
                p1_time=qtime;
                p1_pwr=qpwr;
                p1_rpm=qrpm;
                p1_trq=qtrq;
                p1_speed=qspeed;

                ui->customPlot->graph(3)->addData(p1_time,p1_pwr);
                ui->customPlot->graph(4)->addData(p1_time,p1_trq);
                ui->customPlot->graph(5)->addData(p1_time,p1_rpm);
                ui->customPlot->graph(6)->addData(p1_rpm,p1_pwr);
                ui->customPlot->graph(7)->addData(p1_rpm,p1_trq);
                    ui->customPlot->graph(3)->rescaleValueAxis(true);
                    ui->customPlot->graph(4)->rescaleValueAxis(true);
                    ui->customPlot->graph(5)->rescaleValueAxis(true);
                    ui->customPlot->graph(6)->rescaleValueAxis(true);
                    ui->customPlot->graph(7)->rescaleValueAxis(true);
                    ui->customPlot->rescaleAxes();

           //     }  ui->progressBar->setVisible(false);






                //                if (msgBox1.exec()==QMessageBox::Ok)
                //                    on_clear_plot_capture_clicked();
                    clearTemp();
                break;


            }
            else
            {
                if(msgBox.exec()==QMessageBox::Yes)
                {   p1_time.clear();
                    p1_pwr.clear();
                    p1_trq.clear();
                    p1_rpm.clear();
                    p1_speed.clear();
                    ui->customPlot->graph(3)->data()->clear();
                    ui->customPlot->graph(4)->data()->clear();
                    ui->customPlot->graph(5)->data()->clear();
                    ui->customPlot->graph(6)->data()->clear();
                    ui->customPlot->graph(7)->data()->clear();





                    for (int i=0 ; i<10000;i++)
                    {
                        // qDebug()<<"value "<<qtime.at(i);
                      //p1_time.append(qtime.at(i));
                        //p1_pwr.append(qpwr.at(i));
                        //p1_rpm.append(qrpm.at(i));
                        //p1_trq.append(qtrq.at(i));
                        ui->progressBar->setValue(i);
                    }
                    ui->progressBar->setVisible(false);

                    p1_time=qtime;
                    p1_pwr=qpwr;
                    p1_rpm=qrpm;
                    p1_trq=qtrq;
                    p1_speed=qspeed;

                    ui->customPlot->graph(3)->addData(p1_time,p1_pwr);
                    ui->customPlot->graph(4)->addData(p1_time,p1_trq);
                    ui->customPlot->graph(5)->addData(p1_time,p1_rpm);
                    ui->customPlot->graph(6)->addData(p1_rpm,p1_pwr);
                    ui->customPlot->graph(7)->addData(p1_rpm,p1_trq);
                        ui->customPlot->graph(3)->rescaleValueAxis(true);
                        ui->customPlot->graph(4)->rescaleValueAxis(true);
                        ui->customPlot->graph(5)->rescaleValueAxis(true);
                        ui->customPlot->graph(6)->rescaleValueAxis(true);
                        ui->customPlot->graph(7)->rescaleValueAxis(true);
                        ui->customPlot->rescaleAxes();

                    //                    if (msgBox1.exec()==QMessageBox::Ok)

                    //      clearTemp();                 on_clear_plot_capture_clicked();
                    clearTemp();
                        break;
                }
                else
                    break;

            }

        }
        case 1:

        {
            if(p2_time.isEmpty()==true)
            {  ui->customPlot->graph(8)->data()->clear();
                ui->customPlot->graph(9)->data()->clear();
                ui->customPlot->graph(10)->data()->clear();
                ui->customPlot->graph(11)->data()->clear();
                ui->customPlot->graph(12)->data()->clear();
                for (int i=0 ; i<10000;i++)
                {
                   // qDebug()<<"value "<<qtime.at(i);
                    //p2_time.append(qtime.at(i));
                   // p2_pwr.append(qpwr.at(i));
                   // p2_rpm.append(qrpm.at(i));
                   // p2_trq.append(qtrq.at(i));
                    ui->progressBar->setValue(i);
                }
                ui->progressBar->setVisible(false);
                p2_time=qtime;
                p2_pwr=qpwr;
                p2_rpm=qrpm;
                p2_trq=qtrq;
                p2_speed=qspeed;


                    ui->customPlot->graph(8)->addData(p2_time,p2_pwr);
                    ui->customPlot->graph(9)->addData(p2_time,p2_trq);
                    ui->customPlot->graph(10)->addData(p2_time,p2_rpm);
                    ui->customPlot->graph(11)->addData(p2_rpm,p2_pwr);
                    ui->customPlot->graph(12)->addData(p2_rpm,p2_trq);
                    ui->customPlot->graph(8)->rescaleValueAxis(true);
                    ui->customPlot->graph(9)->rescaleValueAxis(true);
                    ui->customPlot->graph(10)->rescaleValueAxis(true);
                    ui->customPlot->graph(11)->rescaleValueAxis(true);
                    ui->customPlot->graph(12)->rescaleValueAxis(true);
                    ui->customPlot->rescaleAxes();



                // qDebug()<<qtime.isEmpty();
                //qDebug()<<p2_time;

                //                if (msgBox1.exec()==QMessageBox::Ok)
                //                    on_clear_plot_capture_clicked();
                clearTemp(); break;


            }
            else
            {
                if(msgBox.exec()==QMessageBox::Yes)
                { p2_time.clear();
                    p2_pwr.clear();
                    p2_trq.clear();
                    p2_rpm.clear();
                    p2_speed.clear();
                    ui->customPlot->graph(8)->data()->clear();
                    ui->customPlot->graph(9)->data()->clear();
                    ui->customPlot->graph(10)->data()->clear();
                    ui->customPlot->graph(11)->data()->clear();
                    ui->customPlot->graph(12)->data()->clear();


                    for (int i=0 ; i<10000;i++)
                    {
                        //      qDebug()<<"value "<<qtime.at(i);
                        //p2_time.append(qtime.at(i));
                        //p2_pwr.append(qpwr.at(i));
                        //p2_rpm.append(qrpm.at(i));
                       // p2_trq.append(qtrq.at(i));
                       // ui->progressBar->setValue(i);
                    }
                    ui->progressBar->setVisible(false);


                        p2_time=qtime;
                        p2_pwr=qpwr;
                        p2_rpm=qrpm;
                        p2_trq=qtrq;
                        p2_speed=qspeed;

                        ui->customPlot->graph(8)->addData(p2_time,p2_pwr);
                        ui->customPlot->graph(9)->addData(p2_time,p2_trq);
                        ui->customPlot->graph(10)->addData(p2_time,p2_rpm);
                        ui->customPlot->graph(11)->addData(p2_rpm,p2_pwr);
                        ui->customPlot->graph(12)->addData(p2_rpm,p2_trq);
                        ui->customPlot->graph(8)->rescaleValueAxis(true);
                        ui->customPlot->graph(9)->rescaleValueAxis(true);
                        ui->customPlot->graph(10)->rescaleValueAxis(true);
                        ui->customPlot->graph(11)->rescaleValueAxis(true);
                        ui->customPlot->graph(12)->rescaleValueAxis(true);
                        ui->customPlot->rescaleAxes();



                    //qDebug()<<qtime.isEmpty();
                    //qDebug()<<p2_time;

                    //                    if (msgBox1.exec()==QMessageBox::Ok)

                    //                        on_clear_plot_capture_clicked();
                    clearTemp(); break;
                }
                else
                    break;

            }

        }

        case 2:
        {
            if(p3_time.isEmpty()==true)

            {
                ui->customPlot->graph(13)->data()->clear();
                ui->customPlot->graph(14)->data()->clear();
                ui->customPlot->graph(15)->data()->clear();
                ui->customPlot->graph(16)->data()->clear();
                ui->customPlot->graph(17)->data()->clear();

                for (int i=0 ; i<qtime.size();i++)
                {
                    //qDebug()<<"value "<<qtime.at(i);
                   // p3_time.append(qtime.at(i));
                   // p3_pwr.append(qpwr.at(i));
                   // p3_rpm.append(qrpm.at(i));
                    //p3_trq.append(qtrq.at(i));
                    //ui->progressBar->setValue(i);
                }
                ui->progressBar->setVisible(false);

                p3_time=qtime;
                p3_pwr=qpwr;
                p3_rpm=qrpm;
                p3_trq=qtrq;
                p3_speed=qspeed;

                    ui->customPlot->graph(13)->addData(p3_time,p3_pwr);
                    ui->customPlot->graph(14)->addData(p3_time,p3_trq);
                    ui->customPlot->graph(15)->addData(p3_time,p3_rpm);
                    ui->customPlot->graph(16)->addData(p3_rpm,p3_pwr);
                    ui->customPlot->graph(17)->addData(p3_rpm,p3_trq);

                    ui->customPlot->graph(13)->rescaleValueAxis(true);
                    ui->customPlot->graph(14)->rescaleValueAxis(true);
                    ui->customPlot->graph(15)->rescaleValueAxis(true);
                    ui->customPlot->graph(16)->rescaleValueAxis(true);
                    ui->customPlot->graph(17)->rescaleValueAxis(true);
                    ui->customPlot->rescaleAxes();






                //qDebug()<<qtime.isEmpty();
                //qDebug()<<p3_time;

                //                if (msgBox1.exec()==QMessageBox::Ok)
                //                    on_clear_plot_capture_clicked();
                clearTemp(); break;


            }
            else
            {
                if(msgBox.exec()==QMessageBox::Yes)
                { p3_time.clear();
                    p3_pwr.clear();
                    p3_trq.clear();
                    p3_rpm.clear();
                    p3_speed.clear();
                    ui->customPlot->graph(13)->data()->clear();
                    ui->customPlot->graph(14)->data()->clear();
                    ui->customPlot->graph(15)->data()->clear();
                    ui->customPlot->graph(16)->data()->clear();
                    ui->customPlot->graph(17)->data()->clear();



                    for (int i=0 ; i<10000;i++)
                    {
                        //qDebug()<<"value "<<qtime.at(i);
                        //p3_time.append(qtime.at(i));
                        //p3_pwr.append(qpwr.at(i));
                        //p3_rpm.append(qrpm.at(i));
                        //p3_trq.append(qtrq.at(i));
                        ui->progressBar->setValue(i);
                    }
                    ui->progressBar->setVisible(false);








                        p3_time=qtime;
                        p3_pwr=qpwr;
                        p3_rpm=qrpm;
                        p3_trq=qtrq;
                        p3_speed=qspeed;



                        ui->customPlot->graph(13)->addData(p3_time,p3_pwr);
                        ui->customPlot->graph(14)->addData(p3_time,p3_trq);
                        ui->customPlot->graph(15)->addData(p3_time,p3_rpm);
                        ui->customPlot->graph(16)->addData(p3_rpm,p3_pwr);
                        ui->customPlot->graph(17)->addData(p3_rpm,p3_trq);


                        ui->customPlot->graph(13)->rescaleValueAxis(true);
                        ui->customPlot->graph(14)->rescaleValueAxis(true);
                        ui->customPlot->graph(15)->rescaleValueAxis(true);
                        ui->customPlot->graph(16)->rescaleValueAxis(true);
                        ui->customPlot->graph(17)->rescaleValueAxis(true);
                        ui->customPlot->rescaleAxes();

                    //qDebug()<<qtime.isEmpty();
                    // qDebug()<<p3_time;

                    //                    if (msgBox1.exec()==QMessageBox::Ok)

                    //                        on_clear_plot_capture_clicked();
                   clearTemp(); break;
                }
                else
                 { clearTemp();
                    break;}

            }

        }

        case 3:
        {
            if(p4_time.isEmpty()==true)
            {  ui->customPlot->graph(18)->data()->clear();
                ui->customPlot->graph(19)->data()->clear();
                ui->customPlot->graph(20)->data()->clear();
                ui->customPlot->graph(21)->data()->clear();
                ui->customPlot->graph(22)->data()->clear();


                for (int i=0 ; i<10000;i++)
                {
                    //qDebug()<<"value "<<qtime.at(i);
                  //  p4_time.append(qtime.at(i));
                   // p4_pwr.append(qpwr.at(i));
                    //p4_rpm.append(qrpm.at(i));
                    //p4_trq.append(qtrq.at(i));
                    //ui->progressBar->setValue(i);
                }
                ui->progressBar->setVisible(false);


                p4_time=qtime;
                p4_pwr=qpwr;
                p4_rpm=qrpm;
                p4_trq=qtrq;
                p4_speed=qspeed;


                    ui->customPlot->graph(18)->addData(p4_time,p4_pwr);
                    ui->customPlot->graph(19)->addData(p4_time,p4_trq);
                    ui->customPlot->graph(20)->addData(p4_time,p4_rpm);
                    ui->customPlot->graph(21)->addData(p4_rpm,p4_pwr);
                    ui->customPlot->graph(22)->addData(p4_rpm,p4_trq);
                    ui->customPlot->graph(18)->rescaleValueAxis(true);
                    ui->customPlot->graph(19)->rescaleValueAxis(true);
                    ui->customPlot->graph(20)->rescaleValueAxis(true);
                    ui->customPlot->graph(21)->rescaleValueAxis(true);
                    ui->customPlot->graph(22)->rescaleValueAxis(true);
                    ui->customPlot->rescaleAxes();




                             //qDebug()<<qtime.isEmpty();
                //qDebug()<<p4_time;

                //                if (msgBox1.exec()==QMessageBox::Ok)
                //                    on_clear_plot_capture_clicked();
               clearTemp(); break;


            }
            else
            {
                if(msgBox.exec()==QMessageBox::Yes)
                {
                    p4_time.clear();
                    p4_pwr.clear();
                    p4_trq.clear();
                    p4_rpm.clear();
                    p4_speed.clear();
                    ui->customPlot->graph(18)->data()->clear();
                    ui->customPlot->graph(19)->data()->clear();
                    ui->customPlot->graph(20)->data()->clear();
                    ui->customPlot->graph(21)->data()->clear();
                    ui->customPlot->graph(22)->data()->clear();

                    for (int i=0 ; i<10000;i++)
                    {
                        //qDebug()<<"value "<<qtime.at(i);
                       // p4_time.append(qtime.at(i));
                       // p4_pwr.append(qpwr.at(i));
                       // p4_rpm.append(qrpm.at(i));
                       // p4_trq.append(qtrq.at(i));
                       // ui->progressBar->setValue(i);
                    }
                    ui->progressBar->setVisible(false);



                        p3_time=qtime;
                        p3_pwr=qpwr;
                        p3_rpm=qrpm;
                        p3_trq=qtrq;
                        p3_speed=qspeed;


                        ui->customPlot->graph(18)->addData(p4_time,p4_pwr);
                        ui->customPlot->graph(19)->addData(p4_time,p4_trq);
                        ui->customPlot->graph(20)->addData(p4_time,p4_rpm);
                        ui->customPlot->graph(21)->addData(p4_rpm,p4_pwr);
                        ui->customPlot->graph(22)->addData(p4_rpm,p4_trq);
                        ui->customPlot->graph(18)->rescaleValueAxis(true);
                        ui->customPlot->graph(19)->rescaleValueAxis(true);
                        ui->customPlot->graph(20)->rescaleValueAxis(true);
                        ui->customPlot->graph(21)->rescaleValueAxis(true);
                        ui->customPlot->graph(22)->rescaleValueAxis(true);
                        ui->customPlot->rescaleAxes();



                    //qDebug()<<qtime.isEmpty();
                    //qDebug()<<p4_time;

                    //                    if (msgBox1.exec()==QMessageBox::Ok)

                    //                        on_clear_plot_capture_clicked();
                   clearTemp(); break;
                }
                else
                    break;

            }

        }

        }}
    else
    { QMessageBox msgBox2;
        msgBox2.setWindowTitle("Information");
        msgBox2.setText("No Chart Data Detected ");
        msgBox2.setStandardButtons(QMessageBox::Ok);
        if (msgBox2.exec()==QMessageBox::Ok)
        { statusupdate("Capture Data First to save Data");
            //qDebug()<<"exited";
        }


    }

    on_combo_p_activated(p_index);


}
void MainWindow::on_clear_plot_capture_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Warning ");
    msgBox.setText("Are you sure you want to clear Temporary data");
    // msgBox.addButton(QMessageBox::Yes);
    msgBox.setStandardButtons(QMessageBox::Yes);

    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec()==QMessageBox::Yes)

    {

       //ui->customPlot->graph(0)->data()->clear();//------------------  uncomment if curve fails
        ui->customPlot->graph(1)->data()->clear();
        //ui->customPlot->graph(2)->data()->clear();// ------------------  uncomment if curve fails
        ui->customPlot->yAxis->setRange(0,200);
        ui->customPlot->yAxis2->setRange(0,2000);
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setRange(0,2000);
        ui->customPlot->xAxis->setRange(0,25);

        torqueC->data()->clear();

        powerC->data()->clear();

        ui->customPlot->replot();
        ui->statusbar->showMessage(
                    QString("%1 FPS, Total Data points: %2")
                    .arg(ui->customPlot->graph(1)->data()->size()+ui->customPlot->graph(1)->data()->size())
                    , 0);
        maxrpm = 0 ;     maxpwr =0;    maxtrq = 0; maxspeed =0;
        qtime.clear();     qpwr.clear();     qtrq.clear();    qrpm.clear() , qspeed.clear();
        ui->maxrpm->display(maxrpm);     ui->maxtrq->display(maxtrq);    ui->maxpwr->display(maxpwr); ui->Maxspeed->display(maxspeed);




        mPowerNeedle->setCurrentValue(0);
        mTorqueNeedle->setCurrentValue(0);
        mRpmNeedle->setCurrentValue(0);
        mSpeedNeedle->setCurrentValue(0);

        statusupdate(" Temporary data Cleared");

    }


}
void MainWindow::on_stopCapture_clicked()
{






    MATRQ.clear();
    MAPWR.clear();



    dataTimer.stop();
    QMessageBox msgBox3;
    msgBox3.setWindowTitle("Information");
    msgBox3.setText("Data Captured in temporary memory \nSelect a profile and click save to store data ");
    // msgBox.addButton(QMessageBox::Yes);
    msgBox3.setStandardButtons(QMessageBox::Ok);
    msgBox3.exec();

    ui->w_button->setDisabled(false);
    ui->clear_plot_capture->setDisabled(false);
    ui->clear_p->setDisabled(false);
    ui->savetoprofile_r->setDisabled(false);
    ui->capture->setDisabled(false);
    ui->chartviewtype->setDisabled(false);

    ui->saveAs->setDisabled(false);
    ui->saveImage->setDisabled(false);
    ui->copyToProfile->setDisabled(false);
    ui->openCSV->setDisabled(false);
    ui->clearAllProfile->setDisabled(false);
    ui->clearplotcompare->setDisabled(false);
    ui->copyProfileCombo->setDisabled(false);
    ui->updatepPlotView->setDisabled(false);
    ui->pauseButton->setDown(false);
    ui->pauseButton->setText("Pause");
    ui->pauseButton->setDisabled(true);
    ui->openVprofile->setDisabled(false);
    ui->clearVprofile->setDisabled(false);
    ui->stopCapture->setDisabled(true);
    //ui->savetoprofile_r->setDisabled(false);
    if(qrpm.isEmpty()==true)
            ui->savetoprofile_r->setDisabled(true);
    else
           ui->savetoprofile_r->setDisabled(false);

}
void MainWindow::on_clear_p_clicked()
{
    QMessageBox msgBox3;
    msgBox3.setWindowTitle("Information");
    msgBox3.setText("Do you Want To Clear Data");
    msgBox3.setStandardButtons(QMessageBox::Yes);
    msgBox3.addButton(QMessageBox::No);

needleclear();
    switch(p_index)
    {

    case 0:

        if(p1_rpm.isEmpty()!=true)
        { if(msgBox3.exec()==QMessageBox::Yes)
            { p1_rpm.clear();
                p1_time.clear();
                p1_trq.clear();
                p1_pwr.clear();
                p1_speed.clear();
                statusupdate("profile 1 data has been cleared");


            }
            else
                statusupdate("profile 1 data has Not been cleared");
        }
        else
            statusupdate("profile 1 is already empty");

        break;


    case 1:

        if(p2_rpm.isEmpty()!=true)
        { if(msgBox3.exec()==QMessageBox::Yes)
            { p2_rpm.clear();
                p2_time.clear();
                p2_trq.clear();
                p2_pwr.clear();
                p2_speed.clear();
                statusupdate("profile 2 data has been cleared");


            }
            else
                statusupdate("profile 2 data has Not been cleared");
        }
        else
            statusupdate("profile 2 is already empty");


        break;

    case 2:

        if(p3_rpm.isEmpty()!=true)
        { if(msgBox3.exec()==QMessageBox::Yes)
            { p3_rpm.clear();
                p3_time.clear();
                p3_trq.clear();
                p3_pwr.clear();
                p3_speed.clear();
                statusupdate("profile 3 data has been cleared");


            }
            else
                statusupdate("profile 3 data has Not been cleared");
        }
        else
            statusupdate("profile 3  is already empty");


        break;


    case 3:

        if(p4_rpm.isEmpty()!=true)
        { if(msgBox3.exec()==QMessageBox::Yes)
            { p4_rpm.clear();
                p4_time.clear();
                p4_trq.clear();
                p4_pwr.clear();
                p4_speed.clear();
                statusupdate("profile 4 data has been cleared");


            }
            else
                statusupdate("profile 4 data has Not been cleared");
        }
        else
            statusupdate("profile 4  is already empty");


        break;


    }
    on_combo_p_activated(p_index);

}
void MainWindow::on_capture_clicked()
{



    if (ok!=false)
    { needleclear();
        timer.restart();
        torqueC->data()->clear();
        powerC->data()->clear();
        ui->customPlot->graph(1)->data()->clear();

        c= 0;
        lastPointKey = 0;
        c1= 0;
        wr1=0;
        Ww=0;
        m_accumulator=0;
        connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
        dataTimer.start(0);
        ui->w_button->setDisabled(true);
        ui->clear_plot_capture->setDisabled(true);
        ui->clear_p->setDisabled(true);
        ui->savetoprofile_r->setDisabled(true);
        ui->capture->setDisabled(true);
        ui->chartviewtype->setDisabled(true);

        ui->saveAs->setDisabled(true);
        ui->saveImage->setDisabled(true);
        ui->copyToProfile->setDisabled(true);
        ui->openCSV->setDisabled(true);
        ui->clearAllProfile->setDisabled(true);
        ui->clearplotcompare->setDisabled(true);
        ui->copyProfileCombo->setDisabled(true);
        ui->updatepPlotView->setDisabled(true);
        ui->pauseButton->setDown(false);
        ui->pauseButton->setText("Pause");
        ui->pauseButton->setDisabled(false);
        ui->stopCapture->setDisabled(false);
        ui->savetoprofile_r->setDisabled(true);
        ui->openVprofile->setDisabled(true);
    ui->clearVprofile->setDisabled(true);
    }
    else
    {    QMessageBox msgBox3;
        msgBox3.setWindowTitle("Information");
        msgBox3.setText("Set Wheel Diameter to Begin");
        // msgBox.addButton(QMessageBox::Yes);
        msgBox3.setStandardButtons(QMessageBox::Ok);
        msgBox3.exec();
    }
}
void MainWindow::on_updatepPlotView_clicked()
{  // ui->customPlot->plotLayout()->addElement(0,0,title);
    needleclear();
    setdialreading();
    ui->customPlot->replot();
    ui->customPlot->repaint();
    on_chartviewtype_activated(chartindex);
    statusupdate(" Plot View Updated ");
}
void MainWindow::on_chartviewtype_activated(int index)
{statusupdate("Click Update Plot to change chart layout");
    chartindex =index;
    switch(index)
    {
    case 0:
    {  //#### pwr, trq , rpm vs time


        title->setText("Power , Torque, RPM Vs Time");

        ui->customPlot->xAxis->setVisible(true);  //time Axis
        ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(false); //RPM Bottom
        ui->customPlot->yAxis->setVisible(true); // Torque
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(true); //Power
        ui->customPlot->yAxis2->setVisible(true);// RPm at Y
        // profile 1
        ui->customPlot->graph(3)->setVisible(p1);
        ui->customPlot->graph(4)->setVisible(p1);
        ui->customPlot->graph(5)->setVisible(p1);
        ui->customPlot->graph(6)->setVisible(false);
        ui->customPlot->graph(7)->setVisible(false);
        ui->customPlot->graph(6)->removeFromLegend();
        ui->customPlot->graph(7)->removeFromLegend();
        if(p1!=true)
        {
            ui->customPlot->graph(3)->removeFromLegend();
            ui->customPlot->graph(4)->removeFromLegend();
            ui->customPlot->graph(5)->removeFromLegend();
            //ui->customPlot->graph(6)->removeFromLegend();
            //ui->customPlot->graph(7)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(3)->addToLegend();
            ui->customPlot->graph(4)->addToLegend();
            ui->customPlot->graph(5)->addToLegend();
            //ui->customPlot->graph(6)->addToLegend();
            //ui->customPlot->graph(7)->addToLegend();1
        }

        // profile 2
        ui->customPlot->graph(8)->setVisible(p2);
        ui->customPlot->graph(9)->setVisible(p2);
        ui->customPlot->graph(10)->setVisible(p2);
        ui->customPlot->graph(11)->setVisible(false);
        ui->customPlot->graph(12)->setVisible(false);
        ui->customPlot->graph(11)->removeFromLegend();
        ui->customPlot->graph(12)->removeFromLegend();
        if(p2!=true)
        {
            ui->customPlot->graph(8)->removeFromLegend();
            ui->customPlot->graph(9)->removeFromLegend();
            ui->customPlot->graph(10)->removeFromLegend();
            //  ui->customPlot->graph(11)->removeFromLegend();
            // ui->customPlot->graph(12)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(8)->addToLegend();
            ui->customPlot->graph(9)->addToLegend();
            ui->customPlot->graph(10)->addToLegend();
            //ui->customPlot->graph(11)->addToLegend();
            //ui->customPlot->graph(12)->addToLegend();
        }
        // profile 3

        ui->customPlot->graph(13)->setVisible(p3);
        ui->customPlot->graph(14)->setVisible(p3);
        ui->customPlot->graph(15)->setVisible(p3);
        ui->customPlot->graph(16)->setVisible(false);
        ui->customPlot->graph(17)->setVisible(false);
        ui->customPlot->graph(16)->removeFromLegend();
        ui->customPlot->graph(17)->removeFromLegend();
        if(p3!=true)
        {
            ui->customPlot->graph(13)->removeFromLegend();
            ui->customPlot->graph(14)->removeFromLegend();
            ui->customPlot->graph(15)->removeFromLegend();
            //ui->customPlot->graph(16)->removeFromLegend();
            //ui->customPlot->graph(17)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(13)->addToLegend();
            ui->customPlot->graph(14)->addToLegend();
            ui->customPlot->graph(15)->addToLegend();
            //  ui->customPlot->graph(16)->addToLegend();
            //   ui->customPlot->graph(17)->addToLegend();
        }
        // profile 4

        ui->customPlot->graph(18)->setVisible(p4);
        ui->customPlot->graph(19)->setVisible(p4);
        ui->customPlot->graph(20)->setVisible(p4);
        ui->customPlot->graph(21)->setVisible(false);
        ui->customPlot->graph(22)->setVisible(false);
        ui->customPlot->graph(21)->removeFromLegend();
        ui->customPlot->graph(22)->removeFromLegend();
        if(p4!=true)
        {
            ui->customPlot->graph(18)->removeFromLegend();
            ui->customPlot->graph(19)->removeFromLegend();
            ui->customPlot->graph(20)->removeFromLegend();
            // ui->customPlot->graph(21)->removeFromLegend();
            // ui->customPlot->graph(22)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(18)->addToLegend();
            ui->customPlot->graph(19)->addToLegend();
            ui->customPlot->graph(20)->addToLegend();
            //  ui->customPlot->graph(21)->addToLegend();
            //  ui->customPlot->graph(22)->addToLegend();
        }
        ui->customPlot->rescaleAxes();



        break;}
    case 1:
    { //##### power torque vs time

        title->setText("Power , Torque Vs Time");
        ui->customPlot->xAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(false);
        ui->customPlot->yAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(true);
        ui->customPlot->yAxis2->setVisible(false);


        // profile 1
        ui->customPlot->graph(3)->setVisible(p1);
        ui->customPlot->graph(4)->setVisible(p1);
        ui->customPlot->graph(5)->setVisible(false);
        ui->customPlot->graph(6)->setVisible(false);
        ui->customPlot->graph(7)->setVisible(false);
        ui->customPlot->graph(5)->removeFromLegend();
        ui->customPlot->graph(6)->removeFromLegend();
        ui->customPlot->graph(7)->removeFromLegend();
        if(p1!=true)
        {
            ui->customPlot->graph(3)->removeFromLegend();
            ui->customPlot->graph(4)->removeFromLegend();
            //  ui->customPlot->graph(5)->removeFromLegend();
            //ui->customPlot->graph(6)->removeFromLegend();
            //ui->customPlot->graph(7)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(3)->addToLegend();
            ui->customPlot->graph(4)->addToLegend();
            // ui->customPlot->graph(5)->addToLegend();
            //ui->customPlot->graph(6)->addToLegend();
            //ui->customPlot->graph(7)->addToLegend();1
        }

        // profile 2
        ui->customPlot->graph(8)->setVisible(p2);
        ui->customPlot->graph(9)->setVisible(p2);
        ui->customPlot->graph(10)->setVisible(false);
        ui->customPlot->graph(11)->setVisible(false);
        ui->customPlot->graph(12)->setVisible(false);
        ui->customPlot->graph(10)->removeFromLegend();
        ui->customPlot->graph(11)->removeFromLegend();
        ui->customPlot->graph(12)->removeFromLegend();
        if(p2!=true)
        {
            ui->customPlot->graph(8)->removeFromLegend();
            ui->customPlot->graph(9)->removeFromLegend();
            // ui->customPlot->graph(10)->removeFromLegend();
            //  ui->customPlot->graph(11)->removeFromLegend();
            // ui->customPlot->graph(12)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(8)->addToLegend();
            ui->customPlot->graph(9)->addToLegend();
            //  ui->customPlot->graph(10)->addToLegend();
            //ui->customPlot->graph(11)->addToLegend();
            //ui->customPlot->graph(12)->addToLegend();
        }
        // profile 3

        ui->customPlot->graph(13)->setVisible(p3);
        ui->customPlot->graph(14)->setVisible(p3);
        ui->customPlot->graph(15)->setVisible(false);
        ui->customPlot->graph(16)->setVisible(false);
        ui->customPlot->graph(17)->setVisible(false);
        ui->customPlot->graph(15)->removeFromLegend();
        ui->customPlot->graph(16)->removeFromLegend();
        ui->customPlot->graph(17)->removeFromLegend();
        if(p3!=true)
        {
            ui->customPlot->graph(13)->removeFromLegend();
            ui->customPlot->graph(14)->removeFromLegend();
            //  ui->customPlot->graph(15)->removeFromLegend();
            //ui->customPlot->graph(16)->removeFromLegend();
            //ui->customPlot->graph(17)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(13)->addToLegend();
            ui->customPlot->graph(14)->addToLegend();
            // ui->customPlot->graph(15)->addToLegend();
            //  ui->customPlot->graph(16)->addToLegend();
            //   ui->customPlot->graph(17)->addToLegend();
        }
        // profile 4

        ui->customPlot->graph(18)->setVisible(p4);
        ui->customPlot->graph(19)->setVisible(p4);
        ui->customPlot->graph(20)->setVisible(false);
        ui->customPlot->graph(21)->setVisible(false);
        ui->customPlot->graph(22)->setVisible(false);
        ui->customPlot->graph(20)->removeFromLegend();
        ui->customPlot->graph(21)->removeFromLegend();
        ui->customPlot->graph(22)->removeFromLegend();
        if(p4!=true)
        {
            ui->customPlot->graph(18)->removeFromLegend();
            ui->customPlot->graph(19)->removeFromLegend();
            // ui->customPlot->graph(20)->removeFromLegend();
            // ui->customPlot->graph(21)->removeFromLegend();
            // ui->customPlot->graph(22)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(18)->addToLegend();
            ui->customPlot->graph(19)->addToLegend();
            // ui->customPlot->graph(20)->addToLegend();
            //  ui->customPlot->graph(21)->addToLegend();
            //  ui->customPlot->graph(22)->addToLegend();
        }
        ui->customPlot->rescaleAxes();





        break;}
    case 2:
    { //##### power vs time



        title->setText("Power Vs Time");
        ui->customPlot->xAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(false);
        ui->customPlot->yAxis->setVisible(false);
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(true);
        ui->customPlot->yAxis2->setVisible(false);


        // profile 1
        ui->customPlot->graph(3)->setVisible(p1);
        ui->customPlot->graph(4)->setVisible(false);
        ui->customPlot->graph(5)->setVisible(false);
        ui->customPlot->graph(6)->setVisible(false);
        ui->customPlot->graph(7)->setVisible(false);
        ui->customPlot->graph(4)->removeFromLegend();
        ui->customPlot->graph(5)->removeFromLegend();
        ui->customPlot->graph(6)->removeFromLegend();
        ui->customPlot->graph(7)->removeFromLegend();
        if(p1!=true)
        {
            ui->customPlot->graph(3)->removeFromLegend();
            // ui->customPlot->graph(4)->removeFromLegend();
            //  ui->customPlot->graph(5)->removeFromLegend();
            //ui->customPlot->graph(6)->removeFromLegend();
            //ui->customPlot->graph(7)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(3)->addToLegend();
            // ui->customPlot->graph(4)->addToLegend();
            // ui->customPlot->graph(5)->addToLegend();
            //ui->customPlot->graph(6)->addToLegend();
            //ui->customPlot->graph(7)->addToLegend();1
        }

        // profile 2
        ui->customPlot->graph(8)->setVisible(p2);
        ui->customPlot->graph(9)->setVisible(false);
        ui->customPlot->graph(10)->setVisible(false);
        ui->customPlot->graph(11)->setVisible(false);
        ui->customPlot->graph(12)->setVisible(false);
        ui->customPlot->graph(9)->removeFromLegend();
        ui->customPlot->graph(10)->removeFromLegend();
        ui->customPlot->graph(11)->removeFromLegend();
        ui->customPlot->graph(12)->removeFromLegend();
        if(p2!=true)
        {
            ui->customPlot->graph(8)->removeFromLegend();
            // ui->customPlot->graph(9)->removeFromLegend();
            // ui->customPlot->graph(10)->removeFromLegend();
            //  ui->customPlot->graph(11)->removeFromLegend();
            // ui->customPlot->graph(12)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(8)->addToLegend();
            //ui->customPlot->graph(9)->addToLegend();
            //ui->customPlot->graph(10)->addToLegend();
            //ui->customPlot->graph(11)->addToLegend();
            //ui->customPlot->graph(12)->addToLegend();
        }
        // profile 3

        ui->customPlot->graph(13)->setVisible(p3);
        ui->customPlot->graph(14)->setVisible(false);
        ui->customPlot->graph(15)->setVisible(false);
        ui->customPlot->graph(16)->setVisible(false);
        ui->customPlot->graph(17)->setVisible(false);
        ui->customPlot->graph(14)->removeFromLegend();
        ui->customPlot->graph(15)->removeFromLegend();
        ui->customPlot->graph(16)->removeFromLegend();
        ui->customPlot->graph(17)->removeFromLegend();
        if(p3!=true)
        {
            ui->customPlot->graph(13)->removeFromLegend();
            // ui->customPlot->graph(14)->removeFromLegend();
            // ui->customPlot->graph(15)->removeFromLegend();
            //ui->customPlot->graph(16)->removeFromLegend();
            //ui->customPlot->graph(17)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(13)->addToLegend();
            //ui->customPlot->graph(14)->addToLegend();
            //ui->customPlot->graph(15)->addToLegend();
            //ui->customPlot->graph(16)->addToLegend();
            //ui->customPlot->graph(17)->addToLegend();
        }
        // profile 4

        ui->customPlot->graph(18)->setVisible(p4);
        ui->customPlot->graph(19)->setVisible(false);
        ui->customPlot->graph(20)->setVisible(false);
        ui->customPlot->graph(21)->setVisible(false);
        ui->customPlot->graph(22)->setVisible(false);
        ui->customPlot->graph(19)->removeFromLegend();
        ui->customPlot->graph(20)->removeFromLegend();
        ui->customPlot->graph(21)->removeFromLegend();
        ui->customPlot->graph(22)->removeFromLegend();
        if(p4!=true)
        {
            ui->customPlot->graph(18)->removeFromLegend();
            //ui->customPlot->graph(19)->removeFromLegend();
            //ui->customPlot->graph(20)->removeFromLegend();
            // ui->customPlot->graph(21)->removeFromLegend();
            // ui->customPlot->graph(22)->removeFromLegend();
        }
        else
        {
            ui->customPlot->graph(18)->addToLegend();
            //ui->customPlot->graph(19)->addToLegend();
            //ui->customPlot->graph(20)->addToLegend();
            //  ui->customPlot->graph(21)->addToLegend();
            //  ui->customPlot->graph(22)->addToLegend();
        }
        ui->customPlot->rescaleAxes();

        break;}
    case 3:
    { //##### torque vs time

        title->setText("Torque Vs Time");
        ui->customPlot->xAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(false);
        ui->customPlot->yAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(false);
        ui->customPlot->yAxis2->setVisible(false);


        // profile 1
        ui->customPlot->graph(3)->setVisible(false);
        ui->customPlot->graph(4)->setVisible(p1);
        ui->customPlot->graph(5)->setVisible(false);
        ui->customPlot->graph(6)->setVisible(false);
        ui->customPlot->graph(7)->setVisible(false);
        ui->customPlot->graph(3)->removeFromLegend();
        ui->customPlot->graph(5)->removeFromLegend();
        ui->customPlot->graph(6)->removeFromLegend();
        ui->customPlot->graph(7)->removeFromLegend();
        if(p1!=true)
        {
            //ui->customPlot->graph(3)->removeFromLegend();
            ui->customPlot->graph(4)->removeFromLegend();
            //  ui->customPlot->graph(5)->removeFromLegend();
            //ui->customPlot->graph(6)->removeFromLegend();
            //ui->customPlot->graph(7)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(3)->addToLegend();
            ui->customPlot->graph(4)->addToLegend();
            // ui->customPlot->graph(5)->addToLegend();
            //ui->customPlot->graph(6)->addToLegend();
            //ui->customPlot->graph(7)->addToLegend();1
        }

        // profile 2
        ui->customPlot->graph(8)->setVisible(false);
        ui->customPlot->graph(9)->setVisible(p2);
        ui->customPlot->graph(10)->setVisible(false);
        ui->customPlot->graph(11)->setVisible(false);
        ui->customPlot->graph(12)->setVisible(false);
        ui->customPlot->graph(8)->removeFromLegend();
        ui->customPlot->graph(10)->removeFromLegend();
        ui->customPlot->graph(11)->removeFromLegend();
        ui->customPlot->graph(12)->removeFromLegend();
        if(p2!=true)
        {
            //ui->customPlot->graph(8)->removeFromLegend();
            ui->customPlot->graph(9)->removeFromLegend();
            // ui->customPlot->graph(10)->removeFromLegend();
            //  ui->customPlot->graph(11)->removeFromLegend();
            // ui->customPlot->graph(12)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(8)->addToLegend();
            ui->customPlot->graph(9)->addToLegend();
            //ui->customPlot->graph(10)->addToLegend();
            //ui->customPlot->graph(11)->addToLegend();
            //ui->customPlot->graph(12)->addToLegend();
        }
        // profile 3

        ui->customPlot->graph(13)->setVisible(false);
        ui->customPlot->graph(14)->setVisible(p3);
        ui->customPlot->graph(15)->setVisible(false);
        ui->customPlot->graph(16)->setVisible(false);
        ui->customPlot->graph(17)->setVisible(false);
        ui->customPlot->graph(13)->removeFromLegend();
        ui->customPlot->graph(15)->removeFromLegend();
        ui->customPlot->graph(16)->removeFromLegend();
        ui->customPlot->graph(17)->removeFromLegend();
        if(p3!=true)
        {
            //ui->customPlot->graph(13)->removeFromLegend();
            ui->customPlot->graph(14)->removeFromLegend();
            // ui->customPlot->graph(15)->removeFromLegend();
            //ui->customPlot->graph(16)->removeFromLegend();
            //ui->customPlot->graph(17)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(13)->addToLegend();
            ui->customPlot->graph(14)->addToLegend();
            //ui->customPlot->graph(15)->addToLegend();
            //ui->customPlot->graph(16)->addToLegend();
            //ui->customPlot->graph(17)->addToLegend();
        }
        // profile 4

        ui->customPlot->graph(18)->setVisible(false);
        ui->customPlot->graph(19)->setVisible(p4);
        ui->customPlot->graph(20)->setVisible(false);
        ui->customPlot->graph(21)->setVisible(false);
        ui->customPlot->graph(22)->setVisible(false);
        ui->customPlot->graph(18)->removeFromLegend();
        ui->customPlot->graph(20)->removeFromLegend();
        ui->customPlot->graph(21)->removeFromLegend();
        ui->customPlot->graph(22)->removeFromLegend();
        if(p4!=true)
        {
            //ui->customPlot->graph(18)->removeFromLegend();
            ui->customPlot->graph(19)->removeFromLegend();
            //ui->customPlot->graph(20)->removeFromLegend();
            // ui->customPlot->graph(21)->removeFromLegend();
            // ui->customPlot->graph(22)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(18)->addToLegend();
            ui->customPlot->graph(19)->addToLegend();
            //ui->customPlot->graph(20)->addToLegend();
            //  ui->customPlot->graph(21)->addToLegend();
            //  ui->customPlot->graph(22)->addToLegend();
        }
        ui->customPlot->rescaleAxes();

        break;}
    case 4:
    { //##### RPM vs time
        title->setText("RPM Vs Time");
        ui->customPlot->xAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(false);
        ui->customPlot->yAxis->setVisible(false);
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(false);
        ui->customPlot->yAxis2->setVisible(true);

        // profile 1
        ui->customPlot->graph(3)->setVisible(false);
        ui->customPlot->graph(4)->setVisible(false);
        ui->customPlot->graph(5)->setVisible(p1);
        ui->customPlot->graph(6)->setVisible(false);
        ui->customPlot->graph(7)->setVisible(false);
        ui->customPlot->graph(3)->removeFromLegend();
        ui->customPlot->graph(4)->removeFromLegend();
        ui->customPlot->graph(6)->removeFromLegend();
        ui->customPlot->graph(7)->removeFromLegend();
        if(p1!=true)
        {
            //ui->customPlot->graph(3)->removeFromLegend();
            //ui->customPlot->graph(4)->removeFromLegend();
            ui->customPlot->graph(5)->removeFromLegend();
            //ui->customPlot->graph(6)->removeFromLegend();
            //ui->customPlot->graph(7)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(3)->addToLegend();
            // ui->customPlot->graph(4)->addToLegend();
            ui->customPlot->graph(5)->addToLegend();
            //ui->customPlot->graph(6)->addToLegend();
            //ui->customPlot->graph(7)->addToLegend();1
        }

        // profile 2
        ui->customPlot->graph(8)->setVisible(false);
        ui->customPlot->graph(9)->setVisible(false);
        ui->customPlot->graph(10)->setVisible(p2);
        ui->customPlot->graph(11)->setVisible(false);
        ui->customPlot->graph(12)->setVisible(false);
        ui->customPlot->graph(8)->removeFromLegend();
        ui->customPlot->graph(9)->removeFromLegend();
        ui->customPlot->graph(11)->removeFromLegend();
        ui->customPlot->graph(12)->removeFromLegend();
        if(p2!=true)
        {
            //ui->customPlot->graph(8)->removeFromLegend();
            //ui->customPlot->graph(9)->removeFromLegend();
            ui->customPlot->graph(10)->removeFromLegend();
            //  ui->customPlot->graph(11)->removeFromLegend();
            // ui->customPlot->graph(12)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(8)->addToLegend();
            //ui->customPlot->graph(9)->addToLegend();
            ui->customPlot->graph(10)->addToLegend();
            //ui->customPlot->graph(11)->addToLegend();
            //ui->customPlot->graph(12)->addToLegend();
        }
        // profile 3

        ui->customPlot->graph(13)->setVisible(false);
        ui->customPlot->graph(14)->setVisible(false);
        ui->customPlot->graph(15)->setVisible(p3);
        ui->customPlot->graph(16)->setVisible(false);
        ui->customPlot->graph(17)->setVisible(false);
        ui->customPlot->graph(13)->removeFromLegend();
        ui->customPlot->graph(14)->removeFromLegend();
        ui->customPlot->graph(16)->removeFromLegend();
        ui->customPlot->graph(17)->removeFromLegend();
        if(p3!=true)
        {
            //ui->customPlot->graph(13)->removeFromLegend();
            //ui->customPlot->graph(14)->removeFromLegend();
            ui->customPlot->graph(15)->removeFromLegend();
            //ui->customPlot->graph(16)->removeFromLegend();
            //ui->customPlot->graph(17)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(13)->addToLegend();
            //ui->customPlot->graph(14)->addToLegend();
            ui->customPlot->graph(15)->addToLegend();
            //ui->customPlot->graph(16)->addToLegend();
            //ui->customPlot->graph(17)->addToLegend();
        }
        // profile 4

        ui->customPlot->graph(18)->setVisible(false);
        ui->customPlot->graph(19)->setVisible(false);
        ui->customPlot->graph(20)->setVisible(p4);
        ui->customPlot->graph(21)->setVisible(false);
        ui->customPlot->graph(22)->setVisible(false);
        ui->customPlot->graph(18)->removeFromLegend();
        ui->customPlot->graph(19)->removeFromLegend();
        ui->customPlot->graph(21)->removeFromLegend();
        ui->customPlot->graph(22)->removeFromLegend();
        if(p4!=true)
        {
            //ui->customPlot->graph(18)->removeFromLegend();
            //ui->customPlot->graph(19)->removeFromLegend();
            ui->customPlot->graph(20)->removeFromLegend();
            // ui->customPlot->graph(21)->removeFromLegend();
            // ui->customPlot->graph(22)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(18)->addToLegend();
            //ui->customPlot->graph(19)->addToLegend();
            ui->customPlot->graph(20)->addToLegend();
            //  ui->customPlot->graph(21)->addToLegend();
            //  ui->customPlot->graph(22)->addToLegend();
        }
        ui->customPlot->rescaleAxes();




        break;}
    case 5:
    {  //##### power vs rpm
        title->setText("Power Vs RPM");
        ui->customPlot->xAxis->setVisible(false);
        ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(true);
        ui->customPlot->yAxis->setVisible(false);
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(true);
        ui->customPlot->yAxis2->setVisible(false);


        // profile 1
        ui->customPlot->graph(3)->setVisible(false);
        ui->customPlot->graph(4)->setVisible(false);
        ui->customPlot->graph(5)->setVisible(false);
        ui->customPlot->graph(6)->setVisible(p1);
        ui->customPlot->graph(7)->setVisible(false);
        ui->customPlot->graph(3)->removeFromLegend();
        ui->customPlot->graph(4)->removeFromLegend();
        ui->customPlot->graph(5)->removeFromLegend();
        ui->customPlot->graph(7)->removeFromLegend();
        if(p1!=true)
        {
            //ui->customPlot->graph(3)->removeFromLegend();
            //ui->customPlot->graph(4)->removeFromLegend();
            //ui->customPlot->graph(5)->removeFromLegend();
            ui->customPlot->graph(6)->removeFromLegend();
            //ui->customPlot->graph(7)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(3)->addToLegend();
            // ui->customPlot->graph(4)->addToLegend();
            // ui->customPlot->graph(5)->addToLegend();
            ui->customPlot->graph(6)->addToLegend();
            //ui->customPlot->graph(7)->addToLegend();1
        }

        // profile 2
        ui->customPlot->graph(8)->setVisible(false);
        ui->customPlot->graph(9)->setVisible(false);
        ui->customPlot->graph(10)->setVisible(false);
        ui->customPlot->graph(11)->setVisible(p2);
        ui->customPlot->graph(12)->setVisible(false);
        ui->customPlot->graph(8)->removeFromLegend();
        ui->customPlot->graph(9)->removeFromLegend();
        ui->customPlot->graph(10)->removeFromLegend();
        ui->customPlot->graph(12)->removeFromLegend();
        if(p2!=true)
        {
            //ui->customPlot->graph(8)->removeFromLegend();
            //ui->customPlot->graph(9)->removeFromLegend();
            //ui->customPlot->graph(10)->removeFromLegend();
            ui->customPlot->graph(11)->removeFromLegend();
            // ui->customPlot->graph(12)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(8)->addToLegend();
            //ui->customPlot->graph(9)->addToLegend();
            //ui->customPlot->graph(10)->addToLegend();
            ui->customPlot->graph(11)->addToLegend();
            //ui->customPlot->graph(12)->addToLegend();
        }
        // profile 3

        ui->customPlot->graph(13)->setVisible(false);
        ui->customPlot->graph(14)->setVisible(false);
        ui->customPlot->graph(15)->setVisible(false);
        ui->customPlot->graph(16)->setVisible(p3);
        ui->customPlot->graph(17)->setVisible(false);
        ui->customPlot->graph(13)->removeFromLegend();
        ui->customPlot->graph(14)->removeFromLegend();
        ui->customPlot->graph(15)->removeFromLegend();
        ui->customPlot->graph(17)->removeFromLegend();
        if(p3!=true)
        {
            //ui->customPlot->graph(13)->removeFromLegend();
            //ui->customPlot->graph(14)->removeFromLegend();
            //ui->customPlot->graph(15)->removeFromLegend();
            ui->customPlot->graph(16)->removeFromLegend();
            //ui->customPlot->graph(17)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(13)->addToLegend();
            //ui->customPlot->graph(14)->addToLegend();
            //ui->customPlot->graph(15)->addToLegend();
            ui->customPlot->graph(16)->addToLegend();
            //ui->customPlot->graph(17)->addToLegend();
        }
        // profile 4

        ui->customPlot->graph(18)->setVisible(false);
        ui->customPlot->graph(19)->setVisible(false);
        ui->customPlot->graph(20)->setVisible(false);
        ui->customPlot->graph(21)->setVisible(p4);
        ui->customPlot->graph(22)->setVisible(false);
        ui->customPlot->graph(18)->removeFromLegend();
        ui->customPlot->graph(19)->removeFromLegend();
        ui->customPlot->graph(20)->removeFromLegend();
        ui->customPlot->graph(22)->removeFromLegend();
        if(p4!=true)
        {
            //ui->customPlot->graph(18)->removeFromLegend();
            //ui->customPlot->graph(19)->removeFromLegend();
            //ui->customPlot->graph(20)->removeFromLegend();
            ui->customPlot->graph(21)->removeFromLegend();
            // ui->customPlot->graph(22)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(18)->addToLegend();
            //ui->customPlot->graph(19)->addToLegend();
            //ui->customPlot->graph(20)->addToLegend();
            ui->customPlot->graph(21)->addToLegend();
            //  ui->customPlot->graph(22)->addToLegend();
        }
        ui->customPlot->rescaleAxes();




        break;}
    case 6:
    { //##### torque vs rpm
        title->setText("Torque Vs RPM");
        ui->customPlot->xAxis->setVisible(false);
        ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(true);
        ui->customPlot->yAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(false);
        ui->customPlot->yAxis2->setVisible(false);


        // profile 1
        ui->customPlot->graph(3)->setVisible(false);
        ui->customPlot->graph(4)->setVisible(false);
        ui->customPlot->graph(5)->setVisible(false);
        ui->customPlot->graph(6)->setVisible(false);
        ui->customPlot->graph(7)->setVisible(p1);
        ui->customPlot->graph(3)->removeFromLegend();
        ui->customPlot->graph(4)->removeFromLegend();
        ui->customPlot->graph(5)->removeFromLegend();
        ui->customPlot->graph(6)->removeFromLegend();
        if(p1!=true)
        {
            //ui->customPlot->graph(3)->removeFromLegend();
            //ui->customPlot->graph(4)->removeFromLegend();
            //ui->customPlot->graph(5)->removeFromLegend();
            //ui->customPlot->graph(6)->removeFromLegend();
            ui->customPlot->graph(7)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(3)->addToLegend();
            // ui->customPlot->graph(4)->addToLegend();
            // ui->customPlot->graph(5)->addToLegend();
            //ui->customPlot->graph(6)->addToLegend();
            ui->customPlot->graph(7)->addToLegend();
        }

        // profile 2
        ui->customPlot->graph(8)->setVisible(false);
        ui->customPlot->graph(9)->setVisible(false);
        ui->customPlot->graph(10)->setVisible(false);
        ui->customPlot->graph(11)->setVisible(false);
        ui->customPlot->graph(12)->setVisible(p2);
        ui->customPlot->graph(8)->removeFromLegend();
        ui->customPlot->graph(9)->removeFromLegend();
        ui->customPlot->graph(10)->removeFromLegend();
        ui->customPlot->graph(11)->removeFromLegend();
        if(p2!=true)
        {
            //ui->customPlot->graph(8)->removeFromLegend();
            //ui->customPlot->graph(9)->removeFromLegend();
            //ui->customPlot->graph(10)->removeFromLegend();
            //ui->customPlot->graph(11)->removeFromLegend();
            ui->customPlot->graph(12)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(8)->addToLegend();
            //ui->customPlot->graph(9)->addToLegend();
            //ui->customPlot->graph(10)->addToLegend();
            //ui->customPlot->graph(11)->addToLegend();
            ui->customPlot->graph(12)->addToLegend();
        }
        // profile 3

        ui->customPlot->graph(13)->setVisible(false);
        ui->customPlot->graph(14)->setVisible(false);
        ui->customPlot->graph(15)->setVisible(false);
        ui->customPlot->graph(16)->setVisible(false);
        ui->customPlot->graph(17)->setVisible(p3);
        ui->customPlot->graph(13)->removeFromLegend();
        ui->customPlot->graph(14)->removeFromLegend();
        ui->customPlot->graph(15)->removeFromLegend();
        ui->customPlot->graph(16)->removeFromLegend();
        if(p3!=true)
        {
            //ui->customPlot->graph(13)->removeFromLegend();
            //ui->customPlot->graph(14)->removeFromLegend();
            //ui->customPlot->graph(15)->removeFromLegend();
            //ui->customPlot->graph(16)->removeFromLegend();
            ui->customPlot->graph(17)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(13)->addToLegend();
            //ui->customPlot->graph(14)->addToLegend();
            //ui->customPlot->graph(15)->addToLegend();
            //ui->customPlot->graph(16)->addToLegend();
            ui->customPlot->graph(17)->addToLegend();
        }
        // profile 4

        ui->customPlot->graph(18)->setVisible(false);
        ui->customPlot->graph(19)->setVisible(false);
        ui->customPlot->graph(20)->setVisible(false);
        ui->customPlot->graph(21)->setVisible(false);
        ui->customPlot->graph(22)->setVisible(p4);
        ui->customPlot->graph(18)->removeFromLegend();
        ui->customPlot->graph(19)->removeFromLegend();
        ui->customPlot->graph(20)->removeFromLegend();
        ui->customPlot->graph(21)->removeFromLegend();
        if(p4!=true)
        {
            //ui->customPlot->graph(18)->removeFromLegend();
            //ui->customPlot->graph(19)->removeFromLegend();
            //ui->customPlot->graph(20)->removeFromLegend();
            //ui->customPlot->graph(21)->removeFromLegend();
            ui->customPlot->graph(22)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(18)->addToLegend();
            //ui->customPlot->graph(19)->addToLegend();
            //ui->customPlot->graph(20)->addToLegend();
            //  ui->customPlot->graph(21)->addToLegend();
            ui->customPlot->graph(22)->addToLegend();
        }
        ui->customPlot->rescaleAxes();

        break;}
    case 7:
    { //##### power , torque vs rpm
        title->setText("Power ,Torque Vs RPM");
        ui->customPlot->xAxis->setVisible(false);
        ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(true);
        ui->customPlot->yAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(true);
        ui->customPlot->yAxis2->setVisible(false);


        // profile 1
        ui->customPlot->graph(3)->setVisible(false);
        ui->customPlot->graph(4)->setVisible(false);
        ui->customPlot->graph(5)->setVisible(false);
        ui->customPlot->graph(6)->setVisible(p1);
        ui->customPlot->graph(7)->setVisible(p1);
        ui->customPlot->graph(3)->removeFromLegend();
        ui->customPlot->graph(4)->removeFromLegend();
        ui->customPlot->graph(5)->removeFromLegend();
        // ui->customPlot->graph(6)->removeFromLegend();
        if(p1!=true)
        {
            //ui->customPlot->graph(3)->removeFromLegend();
            //ui->customPlot->graph(4)->removeFromLegend();
            //ui->customPlot->graph(5)->removeFromLegend();
            ui->customPlot->graph(6)->removeFromLegend();
            ui->customPlot->graph(7)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(3)->addToLegend();
            // ui->customPlot->graph(4)->addToLegend();
            // ui->customPlot->graph(5)->addToLegend();
            ui->customPlot->graph(6)->addToLegend();
            ui->customPlot->graph(7)->addToLegend();
        }

        // profile 2
        ui->customPlot->graph(8)->setVisible(false);
        ui->customPlot->graph(9)->setVisible(false);
        ui->customPlot->graph(10)->setVisible(false);
        ui->customPlot->graph(11)->setVisible(p2);
        ui->customPlot->graph(12)->setVisible(p2);
        ui->customPlot->graph(8)->removeFromLegend();
        ui->customPlot->graph(9)->removeFromLegend();
        ui->customPlot->graph(10)->removeFromLegend();
        // ui->customPlot->graph(11)->removeFromLegend();
        if(p2!=true)
        {
            //ui->customPlot->graph(8)->removeFromLegend();
            //ui->customPlot->graph(9)->removeFromLegend();
            //ui->customPlot->graph(10)->removeFromLegend();
            ui->customPlot->graph(11)->removeFromLegend();
            ui->customPlot->graph(12)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(8)->addToLegend();
            //ui->customPlot->graph(9)->addToLegend();
            //ui->customPlot->graph(10)->addToLegend();
            ui->customPlot->graph(11)->addToLegend();
            ui->customPlot->graph(12)->addToLegend();
        }
        // profile 3

        ui->customPlot->graph(13)->setVisible(false);
        ui->customPlot->graph(14)->setVisible(false);
        ui->customPlot->graph(15)->setVisible(false);
        ui->customPlot->graph(16)->setVisible(p3);
        ui->customPlot->graph(17)->setVisible(p3);
        ui->customPlot->graph(13)->removeFromLegend();
        ui->customPlot->graph(14)->removeFromLegend();
        ui->customPlot->graph(15)->removeFromLegend();
        //ui->customPlot->graph(16)->removeFromLegend();
        if(p3!=true)
        {
            //ui->customPlot->graph(13)->removeFromLegend();
            //ui->customPlot->graph(14)->removeFromLegend();
            //ui->customPlot->graph(15)->removeFromLegend();
            ui->customPlot->graph(16)->removeFromLegend();
            ui->customPlot->graph(17)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(13)->addToLegend();
            //ui->customPlot->graph(14)->addToLegend();
            //ui->customPlot->graph(15)->addToLegend();
            ui->customPlot->graph(16)->addToLegend();
            ui->customPlot->graph(17)->addToLegend();
        }
        // profile 4

        ui->customPlot->graph(18)->setVisible(false);
        ui->customPlot->graph(19)->setVisible(false);
        ui->customPlot->graph(20)->setVisible(false);
        ui->customPlot->graph(21)->setVisible(p4);
        ui->customPlot->graph(22)->setVisible(p4);
        ui->customPlot->graph(18)->removeFromLegend();
        ui->customPlot->graph(19)->removeFromLegend();
        ui->customPlot->graph(20)->removeFromLegend();
        //ui->customPlot->graph(21)->removeFromLegend();
        if(p4!=true)
        {
            //ui->customPlot->graph(18)->removeFromLegend();
            //ui->customPlot->graph(19)->removeFromLegend();
            //ui->customPlot->graph(20)->removeFromLegend();
            ui->customPlot->graph(21)->removeFromLegend();
            ui->customPlot->graph(22)->removeFromLegend();
        }
        else
        {
            //ui->customPlot->graph(18)->addToLegend();
            //ui->customPlot->graph(19)->addToLegend();
            //ui->customPlot->graph(20)->addToLegend();
            ui->customPlot->graph(21)->addToLegend();
            ui->customPlot->graph(22)->addToLegend();
        }
        ui->customPlot->rescaleAxes();

        break;}


    }
    for(int i =3 ;i<=22 ; i++)
    {   ui->customPlot->graph(i)->rescaleValueAxis(true);}

}
void MainWindow::on_p1CheckBox_toggled(bool checked)
{

    if(checked == true)
    {statusupdate("Click Update plot to View the selected profile");}
    p1 = checked;
    on_chartviewtype_activated(chartindex);

}
void MainWindow::on_p2CheckBox_toggled(bool checked)
{    if(checked == true)
    {statusupdate("Click Update plot to View the selected profile");}
    p2 = checked;
     on_chartviewtype_activated(chartindex);
}
void MainWindow::on_p3CheckBox_toggled(bool checked)
{
    if(checked == true)
    {statusupdate("Click Update plot to View the selected profile");}
    //qDebug()<<checked;
    p3 = checked;
    on_chartviewtype_activated(chartindex);
}
void MainWindow::on_p4CheckBox_toggled(bool checked)
{
    if(checked == true)
    {statusupdate("Click Update plot to View the selected profile");}
    p4 = checked;
    on_chartviewtype_activated(chartindex);
}
void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    { case 0:

    {
        //ui->customPlot->graph(0)->addToLegend();//------------------  uncomment if curve fails
        torqueC->addToLegend();
        ui->customPlot->graph(1)->addToLegend();
        powerC->addToLegend();
        //ui->customPlot->graph(2)->addToLegend();// ------------------  uncomment if curve fails
        ui->customPlot->xAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(false);
        ui->customPlot->yAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(true);
        ui->customPlot->yAxis2->setVisible(true);
        for(int i= 0 ; i<=2 ;i++)
        {ui->customPlot->graph(i)->setVisible(true) ;
            ui->customPlot->replot();
            ui->customPlot->repaint();
        }
        for(int i= 3 ; i<=22 ;i++)
        {ui->customPlot->graph(i)->setVisible(false) ;
            ui->customPlot->graph(i)->removeFromLegend(); }
        ui->customPlot->replot();
        ui->customPlot->repaint();



        on_clearplotcompare_clicked();
        ui->customPlot->replot();
        ui->customPlot->repaint();
        on_p1CheckBox_toggled(false);
        on_p2CheckBox_toggled(false);
        on_p3CheckBox_toggled(false);
        on_p4CheckBox_toggled(false);
        // on_chartviewtype_activated(chartindex);



        ui->p1CheckBox->setChecked(false);
        ui->p2CheckBox->setChecked(false);
        ui->p3CheckBox->setChecked(false);
        ui->p4CheckBox->setChecked(false);
        torqueC->setVisible(true);
        powerC->setVisible(true);
        ui->customPlot->graph(1)->setVisible(true);
        powerC->rescaleValueAxis(true);
        torqueC->rescaleValueAxis(true);
        ui->customPlot->graph(1)->rescaleValueAxis(true);

        break;



    }

    case 1:
    {   //ui->customPlot->graph(0)->removeFromLegend();//------------------  uncomment if curve fails
        torqueC->removeFromLegend();
        torqueC->setVisible(false);
        powerC->setVisible(false);
        ui->customPlot->graph(1)->setVisible(false);


        ui->customPlot->graph(1)->removeFromLegend();
        powerC->removeFromLegend();
        //ui->customPlot->graph(2)->removeFromLegend();//------------------  uncomment if curve fails
        ui->customPlot->replot();
        ui->customPlot->repaint();
        ui->copyProfileCombo->setCurrentIndex(p_index);
        break;


    }



    }}
void MainWindow::on_pauseButton_toggled(bool checked)
{    if (checked  == true)
    {  ui->pauseButton->setDown(true);
        qDebug()<<"Pause";
        dataTimer.stop();
       // m_accumulator += timer.elapsed();
        ui->pauseButton->setText("Resume");
    }
    else
    {   ui->pauseButton->setDown(false);
        qDebug()<<"Resume";
        dataTimer.start();
        ui->pauseButton->setText("Pause");
    }
}
void MainWindow::on_openVprofile_clicked()
{
    pdialog  = new Dialog;
    pdialog->exec();

    //connect(pdialog,SIGNAL(destroyed()),this,SLOT( update_combo()));

update_combo();


}
//###################################################################################################################//
//---------------------------------------------Saving CSV and uploading  area ----------------------------------------//
//####################################################################################################################//
void MainWindow::on_saveAs_clicked()
{
    QString outputDir = "/home/pi/Desktop";

    if (p1_time.isEmpty()!=true &&p1!=false && p2!= true  && p3!=true && p4!= true)
    {
        QString filter("CSV files(*.csv);;All Files(*.*)");
        QString defaultFilter("CSV files (*.csv)");
        QString filename = QFileDialog::getSaveFileName(0, "Save File",outputDir,filter, &defaultFilter);
        QFile file(filename+".csv");
        //qDebug()<<filename;
        if(file.open(QIODevice::WriteOnly))
        {QTextStream stream(&file);
            stream<<"Time (sec)"<<","<<"Wheel Speed (RPM)"<<","<<"Power(watts)"<<","<<"Wheel Torque (Nm)"<<","<<"Wheel Speed (Km/hr)"<<Qt::endl;
            for(int c=0; c< p1_time.size(); c++)
                stream<<p1_time[c]<<","<<p1_rpm[c]<<","<<p1_pwr[c]<<","<<p1_trq[c]<<","<<p1_speed[c]<<Qt::endl;
        }
    }
    else if(p2_time.isEmpty()!=true && p1!=true && p2!= false  && p3!=true && p4!= true)
    {

        QString filter("CSV files(*.csv);;All Files(*.*)");
        QString defaultFilter("CSV files (*.csv)");
        QString filename = QFileDialog::getSaveFileName(0, "Save File",outputDir,filter, &defaultFilter);
        QFile file(filename+".csv");
        //qDebug()<<filename;
        if(file.open(QIODevice::WriteOnly))
        {QTextStream stream(&file);
            stream<<"Time (sec)"<<","<<"Wheel Speed (RPM)"<<","<<"Power(watts)"<<","<<"Wheel Torque (Nm)"<<","<<"Wheel Speed (Km/hr)"<<Qt::endl;
            for(int c=0; c< p2_time.size(); c++)
                stream<<p2_time[c]<<","<<p2_rpm[c]<<","<<p2_pwr[c]<<","<<p2_trq[c]<<","<<p2_speed[c]<<Qt::endl;

        }

    }
    else if(p3_time.isEmpty()!=true && p1!=true && p2!= true  && p3!=false && p4!= true)
    {

        QString filter("CSV files(*.csv);;All Files(*.*)");
        QString defaultFilter("CSV files (*.csv)");
        QString filename = QFileDialog::getSaveFileName(0, "Save File", outputDir,filter, &defaultFilter);
        QFile file(filename+".csv");
        //qDebug()<<filename;
        if(file.open(QIODevice::WriteOnly))
        {QTextStream stream(&file);
            stream<<"Time (sec)"<<","<<"Wheel Speed (RPM)"<<","<<"Power(watts)"<<","<<"WheelTorque (Nm)"<<","<<"Wheel Speed (Km/hr)"<<Qt::endl;
            for(int c=0; c< p3_time.size(); c++)
                stream<<p3_time[c]<<","<<p3_rpm[c]<<","<<p3_pwr[c]<<","<<p3_trq[c]<<","<<p3_speed[c]<<Qt::endl;
        }


    }

    else if(p4_time.isEmpty()!=true && p1!=true && p2!= true  && p3!=true && p4!= false)
    {

        QString filter("CSV files(*.csv);;All Files(*.*)");
        QString defaultFilter("CSV files (*.csv)");
        QString filename = QFileDialog::getSaveFileName(0, "Save File", outputDir,filter, &defaultFilter);
        QFile file(filename+".csv");
        //qDebug()<<filename;
        if(file.open(QIODevice::WriteOnly))
        {QTextStream stream(&file);
            stream<<"Time (sec)"<<","<<"Wheel Speed (RPM)"<<","<<"Power(watts)"<<","<<"Wheel Torque (Nm)"<<","<<"Wheel Speed (Km/hr)"<<Qt::endl;
            for(int c=0; c< p4_time.size(); c++)
                stream<<p4_time[c]<<","<<p4_rpm[c]<<","<<p4_pwr[c]<<","<<p4_trq[c]<<","<<p4_speed[c]<<Qt::endl;


        }
    }
    else{
        QMessageBox msgBox3;
        msgBox3.setWindowTitle("Multiple profiles selected");
        msgBox3.setText("Select only one profile to save or \n selected profile has no data ");
        msgBox3.setStandardButtons(QMessageBox::Ok);
        msgBox3.addButton(QMessageBox::No);
        msgBox3.exec();
    }




}
void MainWindow::on_saveImage_clicked()
{

    QString filter("jpg files(*.jpg);;All Files(*.*)");
    QString defaultFilter("JPG files (*.jpg)");

    QString outputDir = "/home/pi/Desktop";
    QString filename2 = QFileDialog::getSaveFileName(0, "Save File",outputDir,filter, &defaultFilter);

    QFile file(filename2+".jpg");
    // QString filename2 = "Graph.jpg";
    if(!file.open(QIODevice::WriteOnly|QFile::WriteOnly))
    {qDebug()<<"Cannot open";}
    ui->customPlot->saveJpg(filename2+".jpg", 0,0,1.0,-1);
    file.close();

}
void MainWindow::on_copyProfileCombo_activated(int index)
{

    p_index =index;


    switch(index)
    {case 0:
        statusupdate("profile 1");
        if(p1_rpm.isEmpty()!=true)
        { ui->copyProfileStatus->setText("Has data");
            ui->copyProfileStatus->setStyleSheet("background-color: rgb(255,0,0)");
        }
        else
        {       ui->copyProfileStatus->setText("Empty");
            ui->sframe->setStyleSheet("background-color: rgb(0,255,0)");
        }

        p_index = 0;

        break;
    case 1:
        statusupdate("profile 2");
        if(p2_rpm.isEmpty()!=true)
        {  ui->copyProfileStatus->setText("Has data");
            ui->copyProfileStatus->setStyleSheet("background-color: rgb(255,0,0)");}
        else
        {   ui->copyProfileStatus->setText("Empty");
            ui->copyProfileStatus->setStyleSheet("background-color: rgb(0,255,0)");}

        p_index = 1;

        break;
    case 2:
        statusupdate("profile 3");
        if(p3_rpm.isEmpty()!=true)
        {   ui->copyProfileStatus->setText("Has data");
            ui->copyProfileStatus->setStyleSheet("background-color: rgb(255,0,0)");}
        else
        {  ui->copyProfileStatus->setText("Empty");
            ui->copyProfileStatus->setStyleSheet("background-color: rgb(0,255,0)");}

        p_index = 2;
        break;
    case 3:
        statusupdate("profile 4");
        if(p4_rpm.isEmpty()!=true)
        {    ui->copyProfileStatus->setText("Has data");
            ui->copyProfileStatus->setStyleSheet("background-color: rgb(255,0,0)");}
        else
        {  ui->copyProfileStatus->setText("Empty");
            ui->copyProfileStatus->setStyleSheet("background-color: rgb(0,255,0)");}

        p_index = 3;
        break;
    }





}
void MainWindow::on_openCSV_clicked()
{
    ui->p1CheckBox->setCheckState(Qt::CheckState (false));
    ui->p2CheckBox->setCheckState(Qt::CheckState (false));
    ui->p3CheckBox->setCheckState(Qt::CheckState (false));
    ui->p4CheckBox->setCheckState(Qt::CheckState (false));
    QString outputDir = "/home/pi/Desktop";
    QStringList firstColumn;
    QString filter("CSV files(*.csv);;All Files(*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString filename = QFileDialog::getOpenFileName(0, "Open File",outputDir,filter, &defaultFilter);
    QFile file(filename);
    //qDebug()<<filename;
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
    { qtime.clear();qrpm.clear();qpwr.clear();qtrq.clear(); qspeed.clear();
        powerC->data()->clear();torqueC->data()->clear(); ui->customPlot->graph(1)->data()->clear();
        QTextStream stream(&file);
        QString s = file.readLine();
        QString line;

        while(!file.atEnd())
        {
            s = file.readLine();
            QStringList tokens = s.split(",");
            qDebug()<<tokens.at(0).toFloat();
            qtime.append(tokens.at(0).toFloat());
            qDebug()<<tokens.at(1).toFloat();
            qrpm.append(tokens.at(1).toFloat());
            qpwr.append(tokens.at(2).toFloat());
            qtrq.append(tokens.at(3).toFloat());
            qspeed.append(tokens.at(4).toFloat());
        }
        statusupdate("data loaded to temp profile");
    }else
        statusupdate("Unable to open");

}
void MainWindow::on_copyToProfile_clicked()
{
    on_savetoprofile_r_clicked();
    on_copyProfileCombo_activated(p_index);
}
void MainWindow::on_clearplotcompare_clicked()
{needleclear();
    ui->p1CheckBox->setCheckState(Qt::CheckState (false));
    ui->p2CheckBox->setCheckState(Qt::CheckState (false));
    ui->p3CheckBox->setCheckState(Qt::CheckState (false));
    ui->p4CheckBox->setCheckState(Qt::CheckState (false));

    p1 = false;
    p2 = false;
    p3=false;
    p4=false;
    //on_chartviewtype_activated(chartindex);
    ui->customPlot->replot();
    ui->customPlot->repaint();


}
void MainWindow::on_clearAllProfile_clicked()
{
    QMessageBox msgBox2;
    msgBox2.setWindowTitle("Information");
    msgBox2.setText("Are you sure you want to delete all profile  ");

needleclear();

    msgBox2.setStandardButtons(QMessageBox::Yes);
    msgBox2.addButton(QMessageBox::No);


    if (msgBox2.exec()==QMessageBox::Yes)
    {   p1_rpm.clear();
        p1_time.clear();
        p1_trq.clear();
        p1_pwr.clear();
        p1_speed.clear();
        statusupdate("profile 1 data has been cleared");


        p2_rpm.clear();
        p2_time.clear();
        p2_trq.clear();
        p2_pwr.clear();
        p2_speed.clear();
        statusupdate("profile 2 data has been cleared");


        p3_rpm.clear();
        p3_time.clear();
        p3_trq.clear();
        p3_pwr.clear();
        p1_speed.clear();

        p4_rpm.clear();
        p4_time.clear();
        p4_trq.clear();
        p4_pwr.clear();
        p1_speed.clear();
        statusupdate("profile 4 data has been cleared");



        //ui->customPlot->graph(0)->data()->clear();// ---------- uncomment QCP CURVE TEST
        torqueC->data()->clear();
        ui->customPlot->graph(1)->data()->clear();
        powerC->data()->clear();
        //ui->customPlot->graph(2)->data()->clear();// ---------- uncomment QCP CURVE TEST
        for(int i = 3 ; i<23 ; i++)
            ui->customPlot->graph(i)->data()->clear();



    }
    else
        statusupdate("Cancled");

}
void MainWindow::on_mainCombo_currentIndexChanged(int index)
{
    double d = ui->mainCombo->itemData(ui->mainCombo->currentIndex()).value<float>();
    ui->vehicleText->setText(ui->mainCombo->currentText());
    ui->diaText->setText(QString::number(d));

}
void MainWindow::on_clearVprofile_clicked()
{
    if(ok==true)
    {
        wheeldia = 0;
        ui->vehicleText->setText("Select Vehicle");
        ui->diaText->setText("Select Vehicle");
    ui->w_button->setDisabled(false);
    ok=false;
    ui->clearVprofile->setDisabled(true);
    ui->openVprofile->setDisabled(false);

    }

}
