#include "mainwindow.h"
#include "overlaywidget.h"
#include "aspectratiopixmaplabel.h"
#include "videolabel.h"
#include <QApplication>
#include <QLabel>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();


    return a.exec();
}
