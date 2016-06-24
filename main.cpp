#include "mainwindow.h"
#include "overlaywidget.h"
#include "aspectratiopixmaplabel.h"
#include "videolabel.h"
#include <QAction>
#include <QApplication>
#include <QLabel>
#include <QMenu>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();



    return a.exec();
}
