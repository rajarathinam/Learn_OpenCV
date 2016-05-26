#ifndef GEOMETRYWIDGET_H
#define GEOMETRYWIDGET_H

#include <QComboBox>
#include <QDial>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>



class GeometryWidget : public QWidget
{
  Q_OBJECT
public:
  explicit GeometryWidget(QWidget *parent = 0);
  int getCurrentDialValue();
  bool isRotateSelected();
  void closeEvent(QCloseEvent *e);

signals:

public slots:

private:
  QGridLayout *mainLayout;

  QGroupBox *interractiveZoomGroupBox;
  QGroupBox *transformGroupBox;
  QGroupBox *rotateGroupBox;
  QGroupBox *wallGroupBox;
  QGroupBox *puzzleGameGroupBox;

  QGridLayout *transformLayout;
  QGridLayout *rotateLayout;
  QGridLayout *wallLayout;
  QGridLayout *puzzleLayout;

  QComboBox *transformOptionsComboBox;
  QDial *rotateDial;
  QDoubleSpinBox *rowsWallSpinBox;
  QDoubleSpinBox *columnsWallSpinBox;

  QDoubleSpinBox *rowsPuzzleSpinBox;
  QDoubleSpinBox *columnsPuzzleSpinBox;
  ;
};

#endif // GEOMETRYWIDGET_H
