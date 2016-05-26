#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T15:32:17
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Learn_OpenCV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myopencv.cpp \
    videolabel.cpp \
    imagemaninpulationwidget.cpp \
    customdial.cpp \
    overlaywidget.cpp \
    geometrywidget.cpp \
    aspectratiopixmaplabel.cpp \
    imagelabel.cpp

HEADERS  += mainwindow.h \
    myopencv.h \
    videolabel.h \
    imagemaninpulationwidget.h \
    customdial.h \
    overlaywidget.h \
    geometrywidget.h \
    aspectratiopixmaplabel.h \
    imagelabel.h

FORMS    += mainwindow.ui

unix{

INCLUDEPATH += .
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv2
INCLUDEPATH += /usr/local/include/opencv2/core
INCLUDEPATH += /usr/local/include/opencv2/highgui
INCLUDEPATH += /usr/local/include/opencv2/imgproc
INCLUDEPATH += /usr/local/include/opencv2/flann
INCLUDEPATH += /usr/local/include/opencv2/photo
INCLUDEPATH += /usr/local/include/opencv2/video
INCLUDEPATH += /usr/local/include/opencv2/features2d
INCLUDEPATH += /usr/local/include/opencv2/objdetect
INCLUDEPATH += /usr/local/include/opencv2/calib3d
INCLUDEPATH += /usr/local/include/opencv2/ml
INCLUDEPATH += /usr/local/include/opencv2/contr
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio

RESOURCES += \
    resources.qrc

}


win32{
INCLUDEPATH += "C:\\OpenCV2.4.6\\install\\include"
LIBS +=-LC:\\OpenCV2.4.6\\install\\bin\
        libopencv_core246d\
      libopencv_highgui246d\
        libopencv_imgproc246d
RESOURCES += \
   resources.qrc
RC_ICONS = arrplayer.ico

}

