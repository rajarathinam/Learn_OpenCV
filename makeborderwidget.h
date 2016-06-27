#ifndef MAKEBORDERWIDGET_H
#define MAKEBORDERWIDGET_H

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QToolButton>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include "WidgetMarqueeLabel.h"
#include "myopencv.h"

class MakeBorderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MakeBorderWidget(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *event);

signals:

public slots:
    void selectColor();
    void updateImage(Mat);
    void comboboxValueChanged();
    void bordersizeChanged();
    void closWidget();
    void paintNewFrame(int);
    void openImage();

private:
    QGridLayout *mainlayout;
    QToolButton *imagebutton;
    QToolButton *toolbutton;
    QComboBox *combobox;
    QDoubleSpinBox *bordersizeSpinBox;
    QPushButton *quitbutton;
    QSpacerItem *verticalSpacer;
    QMovie *movie;
    WidgetMarqueeLabel *marqueetext;

    Mat origImg;
    cv::Scalar colour;
    int top;
    int bottom;
    int left;
    int right;
    double bordersize;

};

#endif // MAKEBORDERWIDGET_H
