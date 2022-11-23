#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include<QProgressDialog>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void statusupdate(QString );
    float torque(float , int );
    void max(double , double ,double);

    double spi();
    double powercal(double, double);
    void graphsetup();
public slots:
    void realtimeDataSlot();
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

private:
    Ui::MainWindow *ui;
    float wheeldia =0;
    QTimer dataTimer;
    QElapsedTimer timer;
    int p_index =0 ;

    double maxrpm = 0, maxtrq = 0, maxpwr = 0;
    double lastPointKey = 0;
    bool ok=false;
    QVector<double> qrpm, qtrq, qpwr;
    QVector<double> qtime, p1_time, p2_time, p3_time , p4_time;
    QVector<double> p1_rpm , p1_trq ,p1_pwr;
    QVector<double> p2_rpm , p2_trq ,p2_pwr;
    QVector<double> p3_rpm , p3_trq ,p3_pwr;
    QVector<double> p4_rpm , p4_trq ,p4_pwr;




};
#endif // MAINWINDOW_H
