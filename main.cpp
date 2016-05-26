#include "mainwindow.h"
#include "overlaywidget.h"
#include "imagelabel.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    //Raja Rathinam A
    /*
    ImageLabel i;
    i.setPixmap(QPixmap::fromImage(QImage("d:\\g500.jpg")));
    i.show();
    */
    return a.exec();
}
