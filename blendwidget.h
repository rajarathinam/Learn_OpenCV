#ifndef BLENDWIDGET_H
#define BLENDWIDGET_H

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QToolButton>
#include <QWidget>
#include "myopencv.h"

class BlendWidget : public QWidget
{
  Q_OBJECT
public:
  explicit BlendWidget(QWidget *parent = 0);

signals:

public slots:
  void blendImage();
  void displayImage1();
  void displayImage2();
private:
  QGridLayout *mainlayout;



  QDoubleSpinBox *firstSpinBox;
  QDoubleSpinBox *secondSpinBox;
  QToolButton *toolbutton1;
  QToolButton *toolbutton2;
  QToolButton *toolbutton3;

  QLabel *plusLabel;
  QLabel *equalLabel;

  Mat origImg1;
  Mat origImg2;
};

#endif // BLENDWIDGET_H
