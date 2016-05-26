#ifndef IMAGEMANINPULATIONWIDGET_H
#define IMAGEMANINPULATIONWIDGET_H

#include "customdial.h"
#include "overlaywidget.h"
#include "geometrywidget.h"

#include <QObject>
#include <QDialog>
#include <QTabWidget>
#include <QGridLayout>
#include <QDial>

class ImageManinpulationWidget : public QDialog
{
public:
  ImageManinpulationWidget();
  OverlayWidget* getOverlayWidget();
  GeometryWidget* getGeometryWidget();
  void initialize();


signals:
private slots:
private:
  QTabWidget *tabWidget;
  CustomDial *dial;
  OverlayWidget *overlayWidget;
  GeometryWidget *geometryWidget;

  QGridLayout *mainLayout;

};

#endif // IMAGEMANINPULATIONWIDGET_H
