#include <QApplication>
#include "mainwindow.h"
#include "makeborderwidget.h"
#include "scrolltext.h"
#include "WidgetMarqueeLabel.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    MakeBorderWidget w;
    //WidgetMarqueeLabel w;

    w.show();
    return a.exec();
}
