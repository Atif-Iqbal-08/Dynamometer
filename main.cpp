/*
 *   Copyright (C) 2022 by Atif Iqbal
 *   http://emfluxmotors.com
 */



#include "mainwindow.h"

#include <QApplication>
#include <QProgressBar>
#include <stdio.h>
#include <string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<net/if.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    int fd;
    struct ifreq ifr;
    fd = socket(AF_INET,SOCK_DGRAM , 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "eth0" ,IFNAMSIZ-1 );
    ioctl(fd , SIOCGIFHWADDR , &ifr);
    // pclose(fd);

    unsigned char p1= (unsigned char)ifr.ifr_hwaddr.sa_data[0];
    int i1 = static_cast<int>(p1);
    unsigned char p2=(unsigned char)ifr.ifr_hwaddr.sa_data[1];
    int i2 = static_cast<int>(p2);
    unsigned char p3= (unsigned char)ifr.ifr_hwaddr.sa_data[2];
    int i3 = static_cast<int>(p3);
    unsigned char p4= (unsigned char)ifr.ifr_hwaddr.sa_data[3];
    int i4 = static_cast<int>(p4);
    unsigned char p5= (unsigned char)ifr.ifr_hwaddr.sa_data[4];
    int i5 = static_cast<int>(p5);
    unsigned char p6= (unsigned char)ifr.ifr_hwaddr.sa_data[5];
    int i6 = static_cast<int>(p6);
    // w.show();

  //  qDebug()<<"Mac Id: "<<p1<<p2<<p3<<p4<<p5<<p6;

    if(i1== 228 && i2 == 95 && i3 == 1 && i4 == 111 && i5 == 11 && i6 == 178 )
    {



               w.show();
               return a.exec();


    }
    else
    {
        qDebug()<<"Unauthorized Device";
        w.show();
        return a.exec();


       // w.close();
    }
}
