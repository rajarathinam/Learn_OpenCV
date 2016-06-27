#include "makeborderwidget.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QDebug>
extern Mat mycopyMakeBorder(InputArray src,int top, int bottom, int left, int right, int borderType, const Scalar value);

MakeBorderWidget::MakeBorderWidget(QWidget *parent) : QWidget(parent)
{
    bordersize = 0.05;
    mainlayout = new QGridLayout;
    imagebutton = new QToolButton;
    toolbutton = new QToolButton;
    combobox = new QComboBox;
    bordersizeSpinBox = new QDoubleSpinBox;
    quitbutton = new QPushButton("Quit");
    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    marqueetext = new WidgetMarqueeLabel;
    movie =  new QMovie(":/images/snow.gif");
    connect(movie,SIGNAL(frameChanged(int)),
            this,SLOT(paintNewFrame(int)));
    movie->start();
    imagebutton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    imagebutton->setStyleSheet("border: 2px solid orange; border-radius: 4px");
    connect(imagebutton,SIGNAL(clicked(bool)),
            this,SLOT(openImage()));

    toolbutton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    toolbutton->setIcon(QIcon(":/images/color_picker.png"));
    toolbutton->setIconSize(QSize(32,32));
    toolbutton->setStyleSheet("QToolButton{background: transparent;}");
    connect(toolbutton,SIGNAL(clicked(bool)),
            this,SLOT(selectColor()));
    connect(combobox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(comboboxValueChanged()));
    combobox->addItems(QStringList() << "BORDER_CONSTANT" << "BORDER_REPLICATE");
    bordersizeSpinBox->setMinimum(0.0);
    bordersizeSpinBox->setMaximum(1.0);
    bordersizeSpinBox->setDecimals(2);
    bordersizeSpinBox->setSingleStep(0.01);
    connect(bordersizeSpinBox,SIGNAL(valueChanged(double)),
            this,SLOT(bordersizeChanged()));
    connect(quitbutton,SIGNAL(clicked(bool)),
            this,SLOT(closWidget()));
    marqueetext->setText("This Tool is developed by A,Raja(E515378).");
    marqueetext->setDirection(1);
    marqueetext->setSpeed(1);
    marqueetext->setMinimumHeight(25);
    mainlayout->addWidget(  imagebutton,0,0,5,1);
    mainlayout->addWidget(toolbutton,0,1);
    mainlayout->addWidget(combobox,1,1);
    mainlayout->addWidget(bordersizeSpinBox,2,1);
    mainlayout->addItem(verticalSpacer, 3, 1);
    mainlayout->addWidget(quitbutton,4,1);
    mainlayout->addWidget(marqueetext,5,0,2,2);

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
    origImg = imread("/home/rajarathinam/My_Stuff/raja.jpg");
#else
    origImg = imread("C:\\Projects\\NGFMS\\My_Stuff\\OpenCV\\Images\\aero.png");
#endif
    updateImage(origImg);
    setLayout(mainlayout);
}

void MakeBorderWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
      // First we extract the current frame
    QPixmap bkgnd = movie->currentPixmap();
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    /*

    QRect frameRect = currentFrame.rect();

    // Only redraw when the frame is in the invalidated area
    frameRect.moveCenter(rect().center());
    if (frameRect.intersects(event->rect()))
    {
       QPainter painter(this);
       painter.drawPixmap(
          frameRect.left(),
          frameRect.top(),
          currentFrame);
    }
    */
}
void MakeBorderWidget::paintNewFrame(int)
{
  repaint();
}

void MakeBorderWidget::openImage()
{
  QString filename = QFileDialog::getOpenFileName(this,"Open Image File","/home/My_Stuff/",tr(".png,*.jpg,*.jpeg"));
  if(!filename.isEmpty())
    {
      origImg = imread(filename.toStdString().c_str());
      updateImage(origImg);

    }
}
void MakeBorderWidget::selectColor()
{
    QColor color = QColorDialog::getColor(Qt::yellow,this,QString("Choose Border Color"));
    Mat disImg;
    if (color.isValid() && !origImg.empty())
    {
        disImg = origImg;
        bordersize = bordersizeSpinBox->value();
        top = (int) (bordersize*origImg.rows);
        bottom = (int) (bordersize*origImg.rows);
        left = (int) (bordersize*origImg.cols);
        right = (int) (bordersize*origImg.cols);
        colour = qcolor2scalar(color);
        Mat disImg =mycopyMakeBorder(origImg,top,bottom,left,right,combobox->currentIndex(),colour);
        updateImage(disImg);
    }
    else
    {
        qDebug() << "Color not Valid";
    }
}

void MakeBorderWidget::updateImage(Mat img)
{
    if(!img.empty())
    {
          imagebutton->setIcon(QPixmap::fromImage(Mat2QImage(img)));
          imagebutton->setIconSize(QSize(200,200));
    }
}

void MakeBorderWidget::comboboxValueChanged()
{
    if(!origImg.empty() )
    {
        Mat disImg =mycopyMakeBorder(origImg,top,bottom,left,right,combobox->currentIndex(),colour);
        updateImage(disImg);
    }
}

void MakeBorderWidget::bordersizeChanged()
{
    if(!origImg.empty() )
    {
        bordersize = bordersizeSpinBox->value();
        top = (int) (bordersize*origImg.rows);
        bottom = (int) (bordersize*origImg.rows);
        left = (int) (bordersize*origImg.cols);
        right = (int) (bordersize*origImg.cols);
        Mat disImg =mycopyMakeBorder(origImg,top,bottom,left,right,combobox->currentIndex(),colour);
        updateImage(disImg);
    }
}

void MakeBorderWidget::closWidget()
{
    this->close();
}

