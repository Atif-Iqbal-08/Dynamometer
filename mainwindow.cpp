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




int time_c, i =0;
static int CHANNEL =0;
int time0;
int rpm1;
unsigned char buffer[4]{0};
int chartindex;
bool p1,p2,p3,p4;

QCPTextElement *title ;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setLabel("Power");
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setLabelColor(Qt::black);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setTickLabelColor(Qt::black);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setTickPen(QPen (Qt::black));
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setBasePen(QPen(Qt::black));
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setRange(0,500);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(true); // set to true
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->grid()->setVisible(true); // set to true
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->grid()->setSubGridVisible(true);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));

    //############# RPM at a x-axis
    // power axis at left
    ui->customPlot->axisRect()->addAxis(QCPAxis::atBottom);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,0) ->setPadding(30);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1) ->setPadding(30);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setLabel("RPM");
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setLabelColor(Qt::black);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setTickLabelColor(Qt::black);
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setTickPen(QPen (Qt::black));
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setBasePen(QPen(Qt::black));
    ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setRange(0,30000);
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
    ui->customPlot->xAxis->setLabel("Time Elapsed");
    ui->customPlot->xAxis->setLabelColor(Qt::black);
    ui->customPlot->xAxis->setTickLength(1,2);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::black, 1));
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));

    //yaxis 2 rpm
    ui->customPlot->yAxis2->setLabel("RPM");
    ui->customPlot->yAxis->setLabel("Torque");
    ui->customPlot->yAxis2->setLabelColor(Qt::black);
    ui->customPlot->yAxis2->setBasePen(QPen(Qt::black, 1));
    ui->customPlot->yAxis2->setVisible(true);




    ui->customPlot->yAxis->setRange(0,600);
    ui->customPlot->yAxis2->setRange(0,15000);
    ui->customPlot->yAxis2->setTicks(true);
    ui->customPlot->yAxis2->setTickLabelColor(Qt::black);
    ui->customPlot->yAxis2->setTickLabels(true);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setBrush(QColor(255,255,255,150));



    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    ui->customPlot->graph(0)->setPen(QPen (Qt::blue));
    ui->customPlot->graph(0)->setName("Torque");
    ui->customPlot->graph(0)->setVisible(true);
    //ui->customPlot->graph(0)->removeFromLegend();


    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis2);
    ui->customPlot->graph(1)->setPen(QPen (Qt::red));
    ui->customPlot->graph(1)->setName("RPM");
    // ui->customPlot->graph(1)->removeFromLegend();
    ui->customPlot->graph(1)->setVisible(true);


    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(2)->setPen(QPen (Qt::green));
    ui->customPlot->graph(2)->setName("Power");
    // ui->customPlot->graph(2)->removeFromLegend();
    ui->customPlot->graph(2)->setVisible(true);


    graphsetup();


    on_p1CheckBox_toggled(false);
    on_p2CheckBox_toggled(false);
    on_p3CheckBox_toggled(false);
    on_p4CheckBox_toggled(false);

    on_chartviewtype_activated(0);


    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);







}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::graphsetup()

{



    //##############################--profile 1 setup--##################################////////////////////
    //#########------Power
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(3);
    ui->customPlot->graph(3)->setName("P1 Power");
    ui->customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->customPlot->graph(3)->setPen(QPen (Qt::green));
    ui->customPlot->graph(3)->removeFromLegend();
    //#########------Torque
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    ui->customPlot->graph(4);
    ui->customPlot->graph(4)->setName("P1 Torque");
    ui->customPlot->graph(4)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->customPlot->graph(4)->setPen(QPen (Qt::blue));
    ui->customPlot->graph(4)->removeFromLegend();
    //#########------RPM
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis2);
    ui->customPlot->graph(5);
    ui->customPlot->graph(5)->setName("P1 RPM");
    ui->customPlot->graph(5)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->customPlot->graph(5)->setPen(QPen (Qt::red));
    ui->customPlot->graph(5)->removeFromLegend();
    //#########------power vs rpm
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(6);
    ui->customPlot->graph(6)->setName("P1 Power");
    ui->customPlot->graph(6)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->customPlot->graph(6)->setPen(QPen (Qt::green));
    ui->customPlot->graph(6)->removeFromLegend();
    //#########------Torque vs rpm
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->yAxis);
    ui->customPlot->graph(7);
    ui->customPlot->graph(7)->setName("P1 Torque");
    ui->customPlot->graph(7)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->customPlot->graph(7)->setPen(QPen (Qt::blue));
    ui->customPlot->graph(7)->removeFromLegend();




    //##############################--profile 2 setup--##################################////////////////////
    //#########------Power
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(8);
    ui->customPlot->graph(8)->setName("P2 Power");
    ui->customPlot->graph(8)->setScatterStyle(QCPScatterStyle::ssSquare);
    ui->customPlot->graph(8)->setPen(QPen (Qt::green));
    //#########------Torque
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    ui->customPlot->graph(9);
    ui->customPlot->graph(9)->setName("P2 Torque");
    ui->customPlot->graph(9)->setScatterStyle(QCPScatterStyle::ssSquare);
    ui->customPlot->graph(9)->setPen(QPen (Qt::blue));
    //#########------RPM
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis2);
    ui->customPlot->graph(10);
    ui->customPlot->graph(10)->setName("P2 RPM");
    ui->customPlot->graph(10)->setScatterStyle(QCPScatterStyle::ssSquare);
    ui->customPlot->graph(10)->setPen(QPen (Qt::red));
    //#########------power vs rpm
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(11);
    ui->customPlot->graph(11)->setName("P2 Power");
    ui->customPlot->graph(11)->setScatterStyle(QCPScatterStyle::ssSquare);
    ui->customPlot->graph(11)->setPen(QPen (Qt::green));
    //#########------Torque vs rpm
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->yAxis);
    ui->customPlot->graph(12);
    ui->customPlot->graph(12)->setName("P2 Torque");
    ui->customPlot->graph(12)->setScatterStyle(QCPScatterStyle::ssSquare);
    ui->customPlot->graph(12)->setPen(QPen (Qt::blue));

    ui->customPlot->graph(8)->removeFromLegend();
    ui->customPlot->graph(9)->removeFromLegend();
    ui->customPlot->graph(10)->removeFromLegend();
    ui->customPlot->graph(11)->removeFromLegend();
    ui->customPlot->graph(12)->removeFromLegend();



    //##############################--profile 3 setup--##################################////////////////////
    //#########------Power
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(13);
    ui->customPlot->graph(13)->setName("P3 Power");
    ui->customPlot->graph(13)->setScatterStyle(QCPScatterStyle::ssTriangle);
    ui->customPlot->graph(13)->setPen(QPen (Qt::green));
    //#########------Torque
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    ui->customPlot->graph(14);
    ui->customPlot->graph(14)->setName("P3 Torque");
    ui->customPlot->graph(14)->setScatterStyle(QCPScatterStyle::ssTriangle);
    ui->customPlot->graph(14)->setPen(QPen (Qt::blue));
    //#########------RPM
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis2);
    ui->customPlot->graph(15);
    ui->customPlot->graph(15)->setName("P3 RPM");
    ui->customPlot->graph(15)->setScatterStyle(QCPScatterStyle::ssTriangle);
    ui->customPlot->graph(15)->setPen(QPen (Qt::red));
    //#########------power vs rpm
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(16);
    ui->customPlot->graph(16)->setName("P3 Power");
    ui->customPlot->graph(16)->setScatterStyle(QCPScatterStyle::ssTriangle);
    ui->customPlot->graph(16)->setPen(QPen (Qt::green));
    //#########------Torque vs rpm
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->yAxis);
    ui->customPlot->graph(17);
    ui->customPlot->graph(17)->setName("P3 Torque");
    ui->customPlot->graph(17)->setScatterStyle(QCPScatterStyle::ssTriangle);
    ui->customPlot->graph(17)->setPen(QPen (Qt::blue));

    ui->customPlot->graph(13)->removeFromLegend();
    ui->customPlot->graph(14)->removeFromLegend();
    ui->customPlot->graph(15)->removeFromLegend();
    ui->customPlot->graph(16)->removeFromLegend();
    ui->customPlot->graph(17)->removeFromLegend();

    //##############################--profile 4 setup--##################################////////////////////
    //#########------Power
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(18);
    ui->customPlot->graph(18)->setName("P4 Power");
    ui->customPlot->graph(18)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(18)->setPen(QPen (Qt::green));
    //#########------Torque
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
    ui->customPlot->graph(19);
    ui->customPlot->graph(19)->setName("P4 Torque");
    ui->customPlot->graph(19)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(19)->setPen(QPen (Qt::blue));
    //#########------RPM
    ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis2);
    ui->customPlot->graph(20);
    ui->customPlot->graph(20)->setName("P4 RPM");
    ui->customPlot->graph(20)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(20)->setPen(QPen (Qt::red));
    //#########------power vs rpm
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1));
    ui->customPlot->graph(21);
    ui->customPlot->graph(21)->setName("P4 Power");
    ui->customPlot->graph(21)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(21)->setPen(QPen (Qt::green));
    //#########------Torque vs rpm
    ui->customPlot->addGraph(ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1),ui->customPlot->yAxis);
    ui->customPlot->graph(22);
    ui->customPlot->graph(22)->setName("P4 Torque");
    ui->customPlot->graph(22)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot->graph(22)->setPen(QPen (Qt::blue));

    ui->customPlot->graph(18)->removeFromLegend();
    ui->customPlot->graph(19)->removeFromLegend();
    ui->customPlot->graph(20)->removeFromLegend();
    ui->customPlot->graph(21)->removeFromLegend();
    ui->customPlot->graph(22)->removeFromLegend();

}


void MainWindow::statusupdate(QString message)
{
    ui->statusbar->showMessage(
                message);
}

void MainWindow::on_capture_clicked()
{wiringPiSPISetup(CHANNEL, 5000000);
    if (ok!=false)
    {  qDebug()<<timer.restart();
        lastPointKey = 0;

        connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
        dataTimer.start(0);}
    else
    {    QMessageBox msgBox3;
        msgBox3.setWindowTitle("Information");
        msgBox3.setText("Set Wheel Diameter to Begin");
        // msgBox.addButton(QMessageBox::Yes);
        msgBox3.setStandardButtons(QMessageBox::Ok);
        msgBox3.exec();


    }

}

void MainWindow::on_stopCapture_clicked()
{
    dataTimer.stop();


}

void MainWindow::on_w_button_clicked()
{
    QString wdata = ui ->wtext->text();
    float wdata1=wdata.toFloat(&ok);
    qDebug()<<wdata;
    if (wdata1==0 || ok == false)
    {
        statusupdate("Enter Valid Number (No Alphanumeric or Special Characetrs) ");
        QMessageBox msgBox3;
        msgBox3.setWindowTitle("Information");
        msgBox3.setText("Set Valid Number");
        // msgBox.addButton(QMessageBox::Yes);
        msgBox3.setStandardButtons(QMessageBox::Ok);
        msgBox3.exec();

    }

    else if (ok==true)
    {

        statusupdate("Wheel diameter entered is: "+ wdata + " mm . Select Profile To begin ");
        wheeldia = wdata1;
        QString b = QString::number(wheeldia);
        ui->w_Status->setText(b);
        on_combo_p_activated(0);
    }
}

void MainWindow::on_combo_p_activated(int index)
{
    if (ok!=false)
    {
        switch(index)
        {case 0:
            statusupdate("profile 1");
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
            statusupdate("profile 2");
            if(p2_rpm.isEmpty()!=true)
            {  ui->profile_status->setText("Has data");
                ui->sframe->setStyleSheet("background-color: rgb(255,0,0)");}
            else
            {   ui->profile_status->setText("Empty");
                ui->sframe->setStyleSheet("background-color: rgb(0,255,0)");}

            p_index = 1;

            break;
        case 2:
            statusupdate("profile 3");
            if(p3_rpm.isEmpty()!=true)
            {   ui->profile_status->setText("Has data");
                ui->sframe->setStyleSheet("background-color: rgb(255,0,0)");}
            else
            {  ui->profile_status->setText("Empty");
                ui->sframe->setStyleSheet("background-color: rgb(0,255,0)");}

            p_index = 2;
            break;
        case 3:
            statusupdate("profile 4");
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
    }

}

//############################################################ data caputing and computing area ######################################
void MainWindow::realtimeDataSlot()
{

    // calculate two new data points:


    double key = timer.elapsed()/1000.0; // time elapsed since start of demo, in seconds

    if (key-lastPointKey > 0.1) // at most add point every 2 ms
    {
        double rpm= 0;
        double torq= 0;
        double power = 0;

        rpm = spi();
        torq=torque(0.05,rpm);
        power = powercal(torq,rpm);


        if(key > 15)

            ui->customPlot->graph(1)->addData(key, rpm);

        ui->customPlot->graph(0)->addData(key, torq);
        ui->customPlot->graph(2)->addData(key,power);


        // add data to lines:
        // ui->customPlot->graph(1)->addData(key, rpm);
        //ui->customPlot->graph(0)->addData(key, torq);
        //ui->customPlot->graph(2)->addData(key,power);
        max(rpm,torq,power);




        ui->rpm->display(rpm);
        ui->torque->display(torq);
        ui->power->display(power);

        // rescale value (vertical) axis to fit the current data:
        ui->customPlot->graph(0)->rescaleValueAxis();
        ui->customPlot->graph(2)->rescaleValueAxis(true);
        ui->customPlot->graph(1)->rescaleValueAxis(true);
        lastPointKey = key;
        qtime.append(key);
        qrpm.append(rpm);
        qpwr.append(power);
        qtrq.append(torq);





    }



    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(0, lastPointKey+8, Qt::AlignLeading);
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
                    .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
                    , 0);
        lastFpsKey = key;
        frameCount = 0;
    }
}

double MainWindow::spi()
{


    long int ltw = 0;

    for(int j= 0; j<4; j++)
    {
        buffer[j] = i + j;
    }
    i++;
    wiringPiSPIDataRW(CHANNEL, buffer , 4);


    ltw = 0;
    //          if((buffer[0]&0x20)==0)
    //                sig = 1;

    //           buffer[0] &= 0x1F;

    ltw += buffer[3];
    //qDebug()<<ltw;
    ltw *=10;
    ltw += buffer[2];
    //qDebug()<<buffer[2];
    ltw *=10;
    ltw += buffer[1];
    //qDebug()<<buffer[1];
    ltw *=10;
    ltw += buffer[0];
    //qDebug()<<buffer[0];

    memset(buffer, 0, 4);
    // qDebug()<< "OG = "<<time;

    //            if(sig) ltw |= 0xf00000000;
    //             ltw = ltw/16;
    //qDebug()<<ltw;
    return ltw;

}

double MainWindow::powercal(double t, double r)
{
    return (t*r)/63025;
}
float MainWindow::torque(float a, int trpm)
{    qDebug()<<a;
     float alpha;
      float inertia = 0.71;
       float deltarpm ;
        float deltatime;
         deltarpm = (2*3.14*trpm) - (2*3.14*rpm1);
          rpm1=trpm;
           deltatime = a-time0;
            time0=time0+a;
             alpha = deltarpm/a;
              return (inertia*alpha);


}

void MainWindow::max(double arpm, double atrq, double apwr)
{


    if(arpm>maxrpm && arpm < 10000)
        maxrpm=arpm;
    if(atrq>maxtrq && atrq<4000)
        maxtrq=atrq;
    if(apwr>maxpwr &&  apwr<300)
        maxpwr=apwr;

    ui->maxrpm->display(maxrpm);
    ui->maxtrq->display(maxtrq);
    ui->maxpwr->display(maxpwr);
}

void MainWindow::on_clear_plot_capture_clicked()
{



    ui->customPlot->graph(0)->data()->clear();
    ui->customPlot->graph(1)->data()->clear();
    ui->customPlot->graph(2)->data()->clear();
    ui->customPlot->yAxis->setRange(0,4000);
    ui->customPlot->yAxis2->setRange(0,10000);
    ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setRange(0,300);
    ui->customPlot->xAxis->setRange(0,14);

    ui->customPlot->replot();
    ui->statusbar->showMessage(
                QString("%1 FPS, Total Data points: %2")
                .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
                , 0);


    maxrpm = 0 ;
    maxpwr =0;
    maxtrq = 0;
    qtime.clear();
    qpwr.clear();
    qtrq.clear();
    qrpm.clear();
    ui->maxrpm->display(maxrpm);
    ui->maxtrq->display(maxtrq);
    ui->maxpwr->display(maxpwr);
    ui->rpm->display(0);
    ui->torque->display(0);
    ui->power->display(0);





}

void MainWindow::on_savetoprofile_r_clicked()
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("Overrite warning");
    msgBox.setText("Do you want to override");
    // msgBox.addButton(QMessageBox::Yes);
    msgBox.setStandardButtons(QMessageBox::Yes);

    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);



    QMessageBox msgBox1;
    msgBox1.setWindowTitle("Information");
    msgBox1.setText("Values Written to the selected profile");
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
            {
                for (int i=0 ; i<qtime.size();i++)
                {
                    qDebug()<<"value "<<qtime.at(i);
                    p1_time.append(qtime.at(i));
                    p1_pwr.append(qpwr.at(i));
                    p1_rpm.append(qrpm.at(i));
                    p1_trq.append(qtrq.at(i));
                    ui->progressBar->setValue(i);
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





                }
                ui->progressBar->setVisible(false);

                qDebug()<<qtime.isEmpty();
                qDebug()<<p1_time;

                if (msgBox1.exec()==QMessageBox::Ok)
                    on_clear_plot_capture_clicked();
                break;


            }
            else
            {
                if(msgBox.exec()==QMessageBox::Yes)
                {
                    for (int i=0 ; i<qtime.size();i++)
                    {
                        qDebug()<<"value "<<qtime.at(i);
                        p1_time.append(qtime.at(i));
                        p1_pwr.append(qpwr.at(i));
                        p1_rpm.append(qrpm.at(i));
                        p1_trq.append(qtrq.at(i));
                        ui->progressBar->setValue(i);

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



                    }
                    ui->progressBar->setVisible(false);

                    qDebug()<<qtime.isEmpty();
                    qDebug()<<p1_time;

                    if (msgBox1.exec()==QMessageBox::Ok)

                        on_clear_plot_capture_clicked();
                    break;
                }
                else
                    break;

            }

        }
        case 1:

        {
            if(p2_time.isEmpty()==true)
            {
                for (int i=0 ; i<qtime.size();i++)
                {
                    qDebug()<<"value "<<qtime.at(i);
                    p2_time.append(qtime.at(i));
                    p2_pwr.append(qpwr.at(i));
                    p2_rpm.append(qrpm.at(i));
                    p2_trq.append(qtrq.at(i));
                    ui->progressBar->setValue(i);

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





                }
                ui->progressBar->setVisible(false);

                qDebug()<<qtime.isEmpty();
                qDebug()<<p2_time;

                if (msgBox1.exec()==QMessageBox::Ok)
                    on_clear_plot_capture_clicked();
                break;


            }
            else
            {
                if(msgBox.exec()==QMessageBox::Yes)
                {
                    for (int i=0 ; i<qtime.size();i++)
                    {
                        qDebug()<<"value "<<qtime.at(i);
                        p2_time.append(qtime.at(i));
                        p2_pwr.append(qpwr.at(i));
                        p2_rpm.append(qrpm.at(i));
                        p2_trq.append(qtrq.at(i));
                        ui->progressBar->setValue(i);

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

                    }
                    ui->progressBar->setVisible(false);

                    qDebug()<<qtime.isEmpty();
                    qDebug()<<p2_time;

                    if (msgBox1.exec()==QMessageBox::Ok)

                        on_clear_plot_capture_clicked();
                    break;
                }
                else
                    break;

            }

        }

        case 2:
        {
            if(p3_time.isEmpty()==true)
            {
                for (int i=0 ; i<qtime.size();i++)
                {
                    qDebug()<<"value "<<qtime.at(i);
                    p3_time.append(qtime.at(i));
                    p3_pwr.append(qpwr.at(i));
                    p3_rpm.append(qrpm.at(i));
                    p3_trq.append(qtrq.at(i));
                    ui->progressBar->setValue(i);
                    ui->customPlot->graph(13)->addData(p3_time,p3_pwr);
                    ui->customPlot->graph(14)->addData(p2_time,p3_trq);
                    ui->customPlot->graph(15)->addData(p3_time,p3_rpm);
                    ui->customPlot->graph(16)->addData(p3_rpm,p3_pwr);
                    ui->customPlot->graph(17)->addData(p3_rpm,p3_trq);

                    ui->customPlot->graph(13)->rescaleValueAxis(true);
                    ui->customPlot->graph(14)->rescaleValueAxis(true);
                    ui->customPlot->graph(15)->rescaleValueAxis(true);
                    ui->customPlot->graph(16)->rescaleValueAxis(true);
                    ui->customPlot->graph(17)->rescaleValueAxis(true);




                }
                ui->progressBar->setVisible(false);

                qDebug()<<qtime.isEmpty();
                qDebug()<<p3_time;

                if (msgBox1.exec()==QMessageBox::Ok)
                    on_clear_plot_capture_clicked();
                break;


            }
            else
            {
                if(msgBox.exec()==QMessageBox::Yes)
                {
                    for (int i=0 ; i<qtime.size();i++)
                    {
                        qDebug()<<"value "<<qtime.at(i);
                        p3_time.append(qtime.at(i));
                        p3_pwr.append(qpwr.at(i));
                        p3_rpm.append(qrpm.at(i));
                        p3_trq.append(qtrq.at(i));
                        ui->progressBar->setValue(i);

                        ui->customPlot->graph(13)->addData(p3_time,p3_pwr);
                        ui->customPlot->graph(14)->addData(p2_time,p3_trq);
                        ui->customPlot->graph(15)->addData(p3_time,p3_rpm);
                        ui->customPlot->graph(16)->addData(p3_rpm,p3_pwr);
                        ui->customPlot->graph(17)->addData(p3_rpm,p3_trq);


                        ui->customPlot->graph(13)->rescaleValueAxis(true);
                        ui->customPlot->graph(14)->rescaleValueAxis(true);
                        ui->customPlot->graph(15)->rescaleValueAxis(true);
                        ui->customPlot->graph(16)->rescaleValueAxis(true);
                        ui->customPlot->graph(17)->rescaleValueAxis(true);
                    }
                    ui->progressBar->setVisible(false);

                    qDebug()<<qtime.isEmpty();
                    qDebug()<<p3_time;

                    if (msgBox1.exec()==QMessageBox::Ok)

                        on_clear_plot_capture_clicked();
                    break;
                }
                else
                    break;

            }

        }

        case 3:
        {
            if(p4_time.isEmpty()==true)
            {
                for (int i=0 ; i<qtime.size();i++)
                {
                    qDebug()<<"value "<<qtime.at(i);
                    p4_time.append(qtime.at(i));
                    p4_pwr.append(qpwr.at(i));
                    p4_rpm.append(qrpm.at(i));
                    p4_trq.append(qtrq.at(i));
                    ui->progressBar->setValue(i);

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




                }
                ui->progressBar->setVisible(false);

                qDebug()<<qtime.isEmpty();
                qDebug()<<p4_time;

                if (msgBox1.exec()==QMessageBox::Ok)
                    on_clear_plot_capture_clicked();
                break;


            }
            else
            {
                if(msgBox.exec()==QMessageBox::Yes)
                {
                    for (int i=0 ; i<qtime.size();i++)
                    {
                        qDebug()<<"value "<<qtime.at(i);
                        p4_time.append(qtime.at(i));
                        p4_pwr.append(qpwr.at(i));
                        p4_rpm.append(qrpm.at(i));
                        p4_trq.append(qtrq.at(i));
                        ui->progressBar->setValue(i);
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

                    }
                    ui->progressBar->setVisible(false);

                    qDebug()<<qtime.isEmpty();
                    qDebug()<<p4_time;

                    if (msgBox1.exec()==QMessageBox::Ok)

                        on_clear_plot_capture_clicked();
                    break;
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
            qDebug()<<"exited";
        }


    }

    on_combo_p_activated(p_index);


}

void MainWindow::on_clear_p_clicked()
{
    QMessageBox msgBox3;
    msgBox3.setWindowTitle("Information");
    msgBox3.setText("Do you Want To Clear Data");
    msgBox3.setStandardButtons(QMessageBox::Yes);
    msgBox3.addButton(QMessageBox::No);


    switch(p_index)
    {

    case 0:

        if(p1_rpm.isEmpty()!=true)
        { if(msgBox3.exec()==QMessageBox::Yes)
            { p1_rpm.clear();
                p1_time.clear();
                p1_trq.clear();
                p1_pwr.clear();
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

void MainWindow::on_updatepPlotView_clicked()
{  // ui->customPlot->plotLayout()->addElement(0,0,title);
    ui->customPlot->replot();
    ui->customPlot->repaint();
    on_chartviewtype_activated(chartindex);
}

void MainWindow::on_chartviewtype_activated(int index)
{
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







        break;}


    }

    ui->customPlot->graph(3)->rescaleValueAxis(true);
    ui->customPlot->graph(4)->rescaleValueAxis(true);
    ui->customPlot->graph(5)->rescaleValueAxis(true);
    ui->customPlot->graph(6)->rescaleValueAxis(true);
    ui->customPlot->graph(7)->rescaleValueAxis(true);
    ui->customPlot->graph(8)->rescaleValueAxis(true);
    ui->customPlot->graph(9)->rescaleValueAxis(true);
    ui->customPlot->graph(10)->rescaleValueAxis(true);
    ui->customPlot->graph(11)->rescaleValueAxis(true);
    ui->customPlot->graph(12)->rescaleValueAxis(true);
    ui->customPlot->graph(13)->rescaleValueAxis(true);
    ui->customPlot->graph(14)->rescaleValueAxis(true);
    ui->customPlot->graph(15)->rescaleValueAxis(true);
    ui->customPlot->graph(16)->rescaleValueAxis(true);
    ui->customPlot->graph(17)->rescaleValueAxis(true);
    ui->customPlot->graph(18)->rescaleValueAxis(true);
    ui->customPlot->graph(19)->rescaleValueAxis(true);
    ui->customPlot->graph(20)->rescaleValueAxis(true);
    ui->customPlot->graph(21)->rescaleValueAxis(true);
    ui->customPlot->graph(22)->rescaleValueAxis(true);
}

void MainWindow::on_p1CheckBox_toggled(bool checked)
{


    p1 = checked;
    on_chartviewtype_activated(chartindex);

}

void MainWindow::on_p2CheckBox_toggled(bool checked)
{
    p2 = checked;
    on_chartviewtype_activated(chartindex);
}

void MainWindow::on_p3CheckBox_toggled(bool checked)
{
    qDebug()<<checked;
    p3 = checked;
    on_chartviewtype_activated(chartindex);
}

void MainWindow::on_p4CheckBox_toggled(bool checked)
{

    p4 = checked;
    on_chartviewtype_activated(chartindex);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    { case 0:
    {
        ui->customPlot->graph(0)->addToLegend();
        ui->customPlot->graph(1)->addToLegend();
        ui->customPlot->graph(2)->addToLegend();
        ui->customPlot->xAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atBottom,1)->setVisible(false);
        ui->customPlot->yAxis->setVisible(true);
        ui->customPlot->axisRect()->axis(QCPAxis::atLeft,1)->setVisible(true);
        ui->customPlot->yAxis2->setVisible(true);



        ui->customPlot->graph(3)->removeFromLegend();
        ui->customPlot->graph(4)->removeFromLegend();
        ui->customPlot->graph(5)->removeFromLegend();
        ui->customPlot->graph(6)->removeFromLegend();
        ui->customPlot->graph(7)->removeFromLegend();
        ui->customPlot->graph(8)->removeFromLegend();
        ui->customPlot->graph(9)->removeFromLegend();
        ui->customPlot->graph(10)->removeFromLegend();
        ui->customPlot->graph(11)->removeFromLegend();
        ui->customPlot->graph(12)->removeFromLegend();
        ui->customPlot->graph(13)->removeFromLegend();
        ui->customPlot->graph(14)->removeFromLegend();
        ui->customPlot->graph(15)->removeFromLegend();
        ui->customPlot->graph(16)->removeFromLegend();
        ui->customPlot->graph(17)->removeFromLegend();
        ui->customPlot->graph(18)->removeFromLegend();
        ui->customPlot->graph(19)->removeFromLegend();
        ui->customPlot->graph(20)->removeFromLegend();
        ui->customPlot->graph(21)->removeFromLegend();
        ui->customPlot->graph(22)->removeFromLegend();
        on_p1CheckBox_toggled(false);
        on_p2CheckBox_toggled(false);
        on_p3CheckBox_toggled(false);
        on_p4CheckBox_toggled(false);
        on_chartviewtype_activated(chartindex);

        ui->customPlot->replot();
        ui->customPlot->repaint();
        ui->p1CheckBox->setChecked(false);
        ui->p2CheckBox->setChecked(false);
        ui->p3CheckBox->setChecked(false);
        ui->p4CheckBox->setChecked(false);
        break;



    }

    case 1:
    {    ui->customPlot->graph(0)->removeFromLegend();
        ui->customPlot->graph(1)->removeFromLegend();
        ui->customPlot->graph(2)->removeFromLegend();
        ui->customPlot->replot();
        ui->customPlot->repaint();
        break;}



    }}



//##################################################################### saving file #######################################################
void MainWindow::on_saveAs_clicked()
{
     QString outputDir = "/home/pi/Desktop";

if (p1_time.isEmpty()!=true &&p1!=false && p2!= true  && p3!=true && p4!= true)
{
    QString filter("CSV files(*.csv);;All Files(*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString filename = QFileDialog::getSaveFileName(0, "Save File",outputDir,filter, &defaultFilter);
    QFile file(filename+".csv");
    qDebug()<<filename;
    if(file.open(QIODevice::WriteOnly))
    {QTextStream stream(&file);
        stream<<"Time"<<","<<"RPM"<<","<<"Power"<<","<<"Torque"<<Qt::endl;
        for(int c=0; c< p1_time.size(); c++)
            stream<<p1_time[c]<<","<<p1_rpm[c]<<","<<p1_pwr[c]<<","<<p1_trq[c]<<Qt::endl;
    }
}
else if(p2_time.isEmpty()!=true && p1!=true && p2!= false  && p3!=true && p4!= true)
{

    QString filter("CSV files(*.csv);;All Files(*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString filename = QFileDialog::getSaveFileName(0, "Save File",outputDir,filter, &defaultFilter);
    QFile file(filename+".csv");
    qDebug()<<filename;
    if(file.open(QIODevice::WriteOnly))
    {QTextStream stream(&file);
        stream<<"Time"<<","<<"RPM"<<","<<"Power"<<","<<"Torque"<<Qt::endl;
        for(int c=0; c< p2_time.size(); c++)
            stream<<p2_time[c]<<","<<p2_rpm[c]<<","<<p2_pwr[c]<<","<<p2_trq[c]<<Qt::endl;

}

}
    else if(p3_time.isEmpty()!=true && p1!=true && p2!= true  && p3!=false && p4!= true)
    {

        QString filter("CSV files(*.csv);;All Files(*.*)");
        QString defaultFilter("CSV files (*.csv)");
        QString filename = QFileDialog::getSaveFileName(0, "Save File", outputDir,filter, &defaultFilter);
        QFile file(filename+".csv");
        qDebug()<<filename;
        if(file.open(QIODevice::WriteOnly))
        {QTextStream stream(&file);
            stream<<"Time"<<","<<"RPM"<<","<<"Power"<<","<<"Torque"<<Qt::endl;
            for(int c=0; c< p3_time.size(); c++)
                stream<<p3_time[c]<<","<<p3_rpm[c]<<","<<p3_pwr[c]<<","<<p3_trq[c]<<Qt::endl;
}


    }

        else if(p4_time.isEmpty()!=true && p1!=true && p2!= true  && p3!=true && p4!= false)
        {

            QString filter("CSV files(*.csv);;All Files(*.*)");
            QString defaultFilter("CSV files (*.csv)");
            QString filename = QFileDialog::getSaveFileName(0, "Save File", outputDir,filter, &defaultFilter);
            QFile file(filename+".csv");
            qDebug()<<filename;
            if(file.open(QIODevice::WriteOnly))
            {QTextStream stream(&file);
                stream<<"Time"<<","<<"RPM"<<","<<"Power"<<","<<"Torque"<<Qt::endl;
                for(int c=0; c< p4_time.size(); c++)
                    stream<<p4_time[c]<<","<<p4_rpm[c]<<","<<p4_pwr[c]<<","<<p4_trq[c]<<Qt::endl;


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
//------------------_##########################  save chart image #########################------------------
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

}
