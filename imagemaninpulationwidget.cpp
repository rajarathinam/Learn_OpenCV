#include "imagemaninpulationwidget.h"

#include <QDial>

ImageManinpulationWidget::ImageManinpulationWidget()
{
  setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint );
}

OverlayWidget *ImageManinpulationWidget::getOverlayWidget()
{
  return overlayWidget;
}

GeometryWidget *ImageManinpulationWidget::getGeometryWidget()
{
  return geometryWidget;
}


void ImageManinpulationWidget::initialize()
{
    mainLayout = new QGridLayout();
    tabWidget = new QTabWidget;
    overlayWidget = new OverlayWidget;
    geometryWidget = new GeometryWidget;
    tabWidget->addTab(geometryWidget,"Geometry");
    tabWidget->addTab(overlayWidget,"Overlay");
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}



