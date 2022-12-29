/*
 *   Copyright (C) 2022 by Atif Iqbal
 *   http://emfluxmotors.com
 */





#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include<QProgressDialog>
#include "qcustomplot.h"
#include "qcgaugewidget.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addVprofile(QString , double);
    void statusupdate(QString );
    double torque(double , double );
    void max(double , double ,double, double);
    double speed();
    void spi();
    double powercal(double);
    void graphsetup();
    double avgtrq();double avgpwr();
    void clearTemp();

    void needleclear();
public slots:
    void realtimeDataSlot();
      void update_combo();


private slots:



    void on_capture_clicked();


    void on_stopCapture_clicked();


    void on_w_button_clicked();

    void on_combo_p_activated(int index);



    void on_clear_plot_capture_clicked();

    void on_savetoprofile_r_clicked();

    void on_clear_p_clicked();



    void on_updatepPlotView_clicked();

    void on_chartviewtype_activated(int index);

    void on_p1CheckBox_toggled(bool checked);

    void on_p2CheckBox_toggled(bool checked);

    void on_p3CheckBox_toggled(bool checked);

    void on_p4CheckBox_toggled(bool checked);

    void on_tabWidget_currentChanged(int index);

    void on_saveAs_clicked();

    void on_saveImage_clicked();

    void on_copyProfileCombo_activated(int index);

    void on_openCSV_clicked();

    void on_copyToProfile_clicked();

    void on_clearplotcompare_clicked();

    void on_clearAllProfile_clicked();


    void on_pauseButton_toggled(bool checked);
    void setdialreading();



    void on_openVprofile_clicked();

    void on_mainCombo_currentIndexChanged(int index);

    void on_clearVprofile_clicked();

private:
    Ui::MainWindow *ui;
    float wheeldia =0;
    QTimer dataTimer;
    QElapsedTimer timer;
    qint64 m_accumulator;
    int p_index =0 ;

    double wr1, wr2, Ww , Ar, Rpmr;
    double RPMWHEEL, Vspeed,maxspeed;

    double maxrpm = 0, maxtrq = 0, maxpwr = 0;
    double lastPointKey = 0;
    bool ok=false;
    QVector<double> qrpm, qtrq, qpwr,qspeed;
    QVector<double> qtime, p1_time, p2_time, p3_time , p4_time;
    QVector<double> p1_rpm , p1_trq ,p1_pwr,p1_speed;
    QVector<double> p2_rpm , p2_trq ,p2_pwr,p2_speed;
    QVector<double> p3_rpm , p3_trq ,p3_pwr,p3_speed;
    QVector<double> p4_rpm , p4_trq ,p4_pwr,p4_speed;
    int c; //counter

    QVector<double> MATRQ, MAPWR;
    double t,p;
    double avg_trq, avg_pwr , Gpower , Gtrq;


    // dials
    QcGaugeWidget * mSpeedGauge , *mPowerGuage , *mTorqueGuage , *mRpmGuage ;
    QcNeedleItem *mSpeedNeedle , *mPowerNeedle , *mTorqueNeedle , *mRpmNeedle;
    QcDegreesItem *deg1, *deg2 , *deg3 , *deg4;
    QcValuesItem *v1, *v2,*v3,*v4;

    int c1= 0;
    int time_c, i =0;

    int time0;
    int rpm1;
    unsigned char buffer[4]{0};
    int chartindex;
    bool p1,p2,p3,p4;
    double instW, instA;

    double mpwr;
    double mtrq;
    double mspd;
    double mrpm;
Dialog *pdialog;



};
#endif // MAINWINDOW_H
