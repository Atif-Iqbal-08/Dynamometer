QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG -= import_plugins

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcgaugewidget.cpp \
    qcustomplot.cpp

HEADERS += \
    mainwindow.h \
    qcgaugewidget.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui
    INCLUDEPATH +=$$PWD

    CONFIG += unversioned_libname unversioned_soname

    unix:!macx :LIBS += -L$$PWD/./ -lwiringPi

    # Default rules for deployment.
    qnx: target.path = /tmp/$${TARGET}/bin
    else: unix:!android: target.path = /opt/$${TARGET}/bin
    !isEmpty(target.path): INSTALLS += target
    INCLUDEPATH +=$$PWD/.
    DEPENDPATH +=$$PWD/.
