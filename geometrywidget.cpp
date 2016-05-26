#include "geometrywidget.h"

GeometryWidget::GeometryWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout;
    rotateDial = new QDial;
    interractiveZoomGroupBox = new QGroupBox;
    transformGroupBox = new QGroupBox;
    rotateGroupBox = new QGroupBox;
    wallGroupBox = new QGroupBox;
    puzzleGameGroupBox = new QGroupBox;
    transformLayout = new QGridLayout;
    rotateLayout    = new QGridLayout;
    wallLayout      = new QGridLayout;
    puzzleLayout    = new QGridLayout;
    rowsWallSpinBox = new QDoubleSpinBox;
    columnsWallSpinBox = new QDoubleSpinBox;
    rowsPuzzleSpinBox = new QDoubleSpinBox;
    columnsPuzzleSpinBox = new QDoubleSpinBox;
    transformGroupBox->setCheckable(true);
    transformGroupBox->setChecked(false);
    transformGroupBox->setTitle("Transform");
    transformOptionsComboBox = new QComboBox;
    transformOptionsComboBox->addItems(QStringList() << "Rotate by 45 degrees"\
                                       << "Rotate by 90 degrees"\
                                       << "Rotate by 180 degrees"\
                                       << "Rotate by 270 degrees"\
                                       << "Flip Horizontally"\
                                       << "Flip Vertically"\
                                      );
    transformLayout->addWidget(transformOptionsComboBox);
    transformGroupBox->setLayout(transformLayout);
    rotateGroupBox->setCheckable(true);
    rotateGroupBox->setChecked(false);
    rotateGroupBox->setTitle("Rotate");
    rotateDial->setNotchesVisible(true);
    rotateDial->setWrapping(true);
    rotateDial->setMinimum(0);
    rotateDial->setMaximum(360);
    rotateLayout->addWidget(rotateDial);
    rotateGroupBox->setLayout(rotateLayout);
    wallGroupBox->setCheckable(true);
    wallGroupBox->setChecked(false);
    wallGroupBox->setTitle("Wall");
    rowsWallSpinBox->setDecimals(0);
    rowsWallSpinBox->setMaximum(10);
    rowsWallSpinBox->setMinimum(0);
    columnsWallSpinBox->setDecimals(0);
    columnsWallSpinBox->setMaximum(10);
    columnsWallSpinBox->setMinimum(0);
    wallLayout->addWidget(rowsWallSpinBox,0,0);
    wallLayout->addWidget(columnsWallSpinBox,1,0);
    wallGroupBox->setLayout(wallLayout);
    puzzleGameGroupBox->setCheckable(true);
    puzzleGameGroupBox->setChecked(false);
    puzzleGameGroupBox->setTitle("Puzzle Game");
    rowsPuzzleSpinBox->setDecimals(0);
    rowsPuzzleSpinBox->setMaximum(10);
    rowsPuzzleSpinBox->setMinimum(0);
    columnsPuzzleSpinBox->setDecimals(0);
    columnsPuzzleSpinBox->setMaximum(10);
    columnsPuzzleSpinBox->setMinimum(0);
    puzzleLayout->addWidget(rowsPuzzleSpinBox,0,0);
    puzzleLayout->addWidget(columnsPuzzleSpinBox,1,0);
    puzzleGameGroupBox->setLayout(puzzleLayout);
    mainLayout->addWidget(transformGroupBox,0,0);
    mainLayout->addWidget(wallGroupBox,0,1);
    mainLayout->addWidget(rotateGroupBox,1,0);
    mainLayout->addWidget(puzzleGameGroupBox,1,1);
    setLayout(mainLayout);

}

int GeometryWidget::getCurrentDialValue()
{
  return rotateDial->value();

}

bool GeometryWidget::isRotateSelected()
{
  return rotateGroupBox->isChecked();

}

void GeometryWidget::closeEvent(QCloseEvent *event)
{

  QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Image Manipulation ",
                                                                  tr("Are you sure?\n"),
                                                                  QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                  QMessageBox::Yes);
      if (resBtn != QMessageBox::Yes) {
          event->ignore();
      } else {
          event->accept();
      }

}



