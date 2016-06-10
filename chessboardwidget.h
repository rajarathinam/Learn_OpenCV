#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "myopencv.h"

class ChessBoardWidget : public QWidget
{
  Q_OBJECT
public:
  explicit ChessBoardWidget(QWidget *parent = 0);

signals:

public slots:
   void createChessBoardImage(int width,int height,int squareSize);
   void displayImage();
private:
  Mat chessBoardImage;
  QLabel *label;
};

#endif // CHESSBOARDWIDGET_H
