#include "chessboardwidget.h"
#include <QDebug>

ChessBoardWidget::ChessBoardWidget(QWidget *parent) : QWidget(parent)
{
    label = new QLabel;
}

void ChessBoardWidget::createChessBoardImage(int width, int height, int squareSize)
{
    if(width != 0 && height != 0 && squareSize != 0)
    {
        chessBoardImage = Mat(width,height,CV_8UC3,Scalar::all(0));
        unsigned char color = 0;
        for(int row = 0; row < chessBoardImage.rows; row+=squareSize)
        {
             color =~ color;
            for(int col = 0; col < chessBoardImage.cols ; col+=squareSize)
            {
                Mat ROI = chessBoardImage(Rect(row,col,squareSize,squareSize));
                ROI.setTo(Scalar::all(color));
                color =~ color;

            }

        }
    }
    imwrite("/home/rajarathinam/My_Stuff/chessboard.png",chessBoardImage);
}

void ChessBoardWidget::displayImage()
{
    if(!chessBoardImage.empty())
    {
        label->setPixmap(QPixmap::fromImage(Mat2QImage(chessBoardImage)));
        label->show();
    }
}

