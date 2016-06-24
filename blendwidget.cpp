#include "blendwidget.h"
#include<QFileDialog>
extern QImage Mat2QImage(const Mat &src);
BlendWidget::BlendWidget(QWidget *parent) : QWidget(parent)
{
    mainlayout = new QGridLayout;
    plusLabel = new QLabel("+");
    equalLabel = new QLabel("=");
    toolbutton1 = new QToolButton;
    toolbutton2 = new QToolButton;
    toolbutton3 = new QToolButton;
    firstSpinBox = new QDoubleSpinBox;
    secondSpinBox = new QDoubleSpinBox;
    firstSpinBox->setMaximum(1);
    firstSpinBox->setMinimum(0);
    firstSpinBox->setDecimals(1);
    firstSpinBox->setSingleStep(0.1);
    secondSpinBox->setMaximum(1);
    secondSpinBox->setMinimum(0);
    secondSpinBox->setDecimals(1);
    secondSpinBox->setSingleStep(0.1);


    //toolbutton1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    toolbutton2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    toolbutton3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    mainlayout->addWidget(toolbutton1,0,0);
    mainlayout->addWidget(plusLabel,0,1,1,1);
    mainlayout->addWidget(toolbutton2,0,2,1,1);
    mainlayout->addWidget(equalLabel,0,3,1,1);
    mainlayout->addWidget(toolbutton3,0,3,2,1);
    mainlayout->addWidget(firstSpinBox,1,0);
    mainlayout->addWidget(secondSpinBox,1,2);
    setLayout(mainlayout);

    connect(firstSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(blendImage()));
    connect(secondSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(blendImage()));
    connect(toolbutton1,SIGNAL(clicked(bool)),
            this,SLOT(displayImage1()));
    connect(toolbutton2,SIGNAL(clicked(bool)),
            this,SLOT(displayImage2()));

    setMinimumSize(800,250);
}

void BlendWidget::displayImage1()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open First Image","/home/rajarathinam",tr("Image Files (*.png *.jpg *.jpeg)"));
    origImg1 = imread(filename.toStdString().c_str());
    toolbutton1->setIcon(QPixmap::fromImage(Mat2QImage(origImg1)));
    toolbutton1->setIconSize(QSize(origImg1.cols/2,origImg1.rows/2));
}

void BlendWidget::displayImage2()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Second Image","/home/rajarathinam",tr("Image Files (*.png *.jpg *.jpeg)"));
    origImg2 = imread(filename.toStdString().c_str());
    toolbutton2->setIcon(QPixmap::fromImage(Mat2QImage(origImg2)));
    toolbutton2->setIconSize(QSize(origImg2.cols/2,origImg2.rows/2));
}
void BlendWidget::blendImage()
{

    Mat dst;
    if(!origImg1.empty())
    {
        dst = Mat(origImg1.size(),origImg1.type());
        addWeighted(origImg1,firstSpinBox->value(),origImg2,secondSpinBox->value(),0.0,dst);
        toolbutton3->setIcon(QPixmap::fromImage(Mat2QImage(dst)));
        toolbutton3->setIconSize(QSize(dst.cols/2,dst.rows/2));
    }

}

