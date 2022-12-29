#include "dialog.h"
#include "ui_dialog.h"
#include <qdebug.h>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    updatecombo();
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::updatecombo()
{QString fileName = "/home/orxa/.config/Vehicle.csv";
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
            ui->combo->addItem(tokens.at(0),tokens.at(1).toFloat());

        }
        file.close();
    }

}
void Dialog::on_deleteProfile_clicked()
{
    qDebug()<<"delete profile clicked";
    QString c, b;
    QFile file3("vtemp.csv");
    file3.open(QIODevice::ReadWrite);
    file3.close();
    QString a =  ui->combo->currentText();
    QString fileName = "/home/orxa/.config/Vehicle.csv";
    QString filename2 = "/home/orxa/.config/vtemp.csv";
    QFile file(fileName),file2(filename2);
    QVector<QString> row1,row2;
  //  int m =0;
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream2(&file2);
        QString s ;
        while(!file.atEnd())
        { qDebug()<<"hehe";
            s = file.readLine();
            QStringList tokens = s.split(",");
           // m=m+1;
            qDebug()<<"row 1 csv before if " <<tokens.at(0);
            qDebug()<<"row 2 csv before if  " <<tokens.at(1);

            //   ui->combo->addItem(tokens.at(0),tokens.at(1).toFloat());
            if(tokens.at(0)!=a)

            {  row1.append(tokens.at(0));
                row2.append(tokens.at(1));
                qDebug()<<"row 1 csv open" <<row1;
                qDebug()<<"row 2 csv open " <<row2;
            }
        }
        qDebug()<<"row 1" <<row1;
        qDebug()<<"row 2" <<row2;
        file.close();

        if(file2.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file2);
            for(int c=0; c< row1.size(); c++)
                stream<<row1[c]<<","<<row2[c];
            qDebug()<<"row 1 csv" <<row1;
            qDebug()<<"row 2 csv" <<row2;
        }
        row1.clear();
        row2.clear();
        file2.close();
    }
    //file.close();
    //file2.close();
    remove("/home/orxa/.config/Vehicle.csv");
    rename("/home/orxa/.config/vtemp.csv","/home/orxa/.config/Vehicle.csv");
    ui->combo->clear();
    ui->combo->repaint();
    updatecombo();
    ui->combo->setCurrentIndex(0);

}

void Dialog::on_addProfile_clicked()
{
    qDebug()<<"add profile profile clicked";
    QString wdata = ui ->wheelText->text();
    float wdata1=wdata.toFloat(&vok);
    QString name = ui->nameText->text();
    if (wdata1==0 || vok == false  )
    {
        //statusupdate("Enter Valid Number (No Alphanumeric or Special Characetrs) ");
        QMessageBox msgBox3;
        msgBox3.setWindowTitle("Information");
        msgBox3.setText("Enter Proper Information ");
        // msgBox.addButton(QMessageBox::Yes);
        msgBox3.setStandardButtons(QMessageBox::Ok);
        msgBox3.exec();
    }
    else
    {
        qDebug()<<"in else";
        ui->diaTextDisplay->setText(QString::number(wdata1));
        ui->combo->addItem(name,wdata1);
        ui->nameTextDisplay->setText(name);
        ui->diaTextDisplay->setText((wdata));
        QString filename = "/home/orxa/.config/Vehicle.csv";
        QFile file(filename);
        //qDebug()<<filename;
        if(file.open(QIODevice::WriteOnly | QFile::Append))
        {QTextStream stream(&file);
            int i= 0;
            while(!file.atEnd())
            {
                i = i +1 ;
            }
            stream<<name<<","<<wdata<<Qt::endl;
            file.close();
            int index = ui->combo->findData(wdata1);
             ui->combo->setCurrentIndex(index);
        }
   }
}

void Dialog::on_combo_currentIndexChanged(int index)
{   //qDebug()<< ui->combo->currentText();
    //qDebug()<<ui->combo->itemData(ui->combo->currentIndex());
    double d = ui->combo->itemData(ui->combo->currentIndex()).value<float>();
    ui->nameTextDisplay->setText(ui->combo->currentText());
    ui->diaTextDisplay->setText(QString::number(d));

}
