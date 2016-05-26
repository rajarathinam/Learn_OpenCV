#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <unistd.h>
extern Mat QImage2Mat(QImage const& src);
extern QImage Mat2QImage(Mat const& src);
ImageManinpulationWidget* MainWindow::imageManipulationWidget = NULL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fullScreenSet = false;
    imageManipulationWidgetVisible = false;
    frameTimer = new QTimer(this);
    mainLayout = new QGridLayout();
    hLayout = new QHBoxLayout;
    hLayout->setSpacing(0);
    hLayout->setSizeConstraint(QLayout::SetFixedSize);
    vlabel = new AspectRatioPixmapLabel(this);
    slider = new QSlider(Qt::Horizontal);
    slider->setEnabled(false);
    slider->setStyleSheet("QSlider::groove:horizontal {\
    border: 1px solid #bbb;\
    background: white;\
    height: 6px;\
    border-radius: 4px;\
    }\
    QSlider::sub-page:horizontal {\
    background: qlineargradient(x1: 0, y1: 0,    x2: 0, y2: 1,\
        stop: 0 #16e, stop: 1 #bbf);\
    background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,\
        stop: 0 #bbf, stop: 1 #55f);\
    border: 1px solid #777;\
    height: 10px;\
    border-radius: 4px;\
    }\
    QSlider::add-page:horizontal {\
    background: #fff;\
    border: 1px solid #777;\
    height: 10px;\
    border-radius: 4px;\
    }\
    QSlider::handle:horizontal {\
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\
        stop:0 #eee, stop:1 #ccc);\
    border: 1px solid #777;\
    width: 13px;\
    margin-top: -2px;\
    margin-bottom: -2px;\
    border-radius: 1px;\
    }\
    QSlider::handle:horizontal:hover {\
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\
        stop:0 #fff, stop:1 #ddd);\
    border: 1px solid #444;\
    border-radius: 4px;\
    }\
    QSlider::sub-page:horizontal:disabled {\
    background: #bbb;\
    border-color: #999;\
    }\
    QSlider::add-page:horizontal:disabled {\
    background: #eee;\
    border-color: #999;\
    }\
    QSlider::handle:horizontal:disabled {\
    background: #eee;\
    border: 1px solid #aaa;\
    border-radius: 4px;\
    }");
    playButton = new QPushButton(QIcon(":/images/playbutton.png"),"");
    playButton->setEnabled(false);
    playButton->setIconSize(QSize(32,32));
    playButton->setFixedSize(38,38);
    playButton->setCheckable(true);
    stopButton = new QPushButton(QIcon(":/images/stopbutton.png"),"");
    stopButton->setIconSize(QSize(32,32));
    stopButton->setFixedSize(38,38);
    mainLayout->addWidget(vlabel,0,0,1,0);
    mainLayout->addWidget(slider,1,0,1,0);
    hLayout->addWidget(playButton);
    hLayout->addWidget(stopButton);
    mainLayout->addLayout(hLayout,2,0,1,1,Qt::AlignLeft);
    connect(frameTimer,SIGNAL(timeout()),
            this,SLOT(getFrame()));
    connect(slider,SIGNAL(sliderMoved(int)),
            this, SLOT(sliderFrameMove(int)));
    connect(slider,SIGNAL(sliderPressed()),
            this,SLOT(sliderPressed()));
    connect(slider,SIGNAL(sliderReleased()),
            this,SLOT(sliderReleased()));


    connect(playButton,SIGNAL(toggled(bool)),
            this,SLOT(onPlayButtonToggled(bool)));
    connect(stopButton,SIGNAL(clicked(bool)),
            this,SLOT(onStopButtonClicked()));
    ui->centralWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

Mat MainWindow::rotateImage(int angle)
{
    return rotate(getCurrentImage(),angle);
}
Mat MainWindow::writeTextOnMat(Mat src,const  char *text)
{
    return writeTextOnImage(src,text);
}
void MainWindow::on_actionOpenImage_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/rajarathinam/Pictures", tr("Image Files (*.png *.jpg *.bmp)"));
    img = imread(fileName.toStdString().c_str());
    QImage imgIn= Mat2QImage(img);
    vlabel->setPixmap(QPixmap::fromImage(imgIn));
}

void MainWindow::on_actionConvertToGray_triggered()
{
    if(img.data != NULL)
    {
        Mat temp = img;
        Mat flipped(temp);
        cv::flip(temp,flipped,0);
        QImage imgIn= Mat2QImage(flipped);
        vlabel->setPixmap(QPixmap::fromImage(imgIn));
        current_img = flipped;
    }
}

void MainWindow::on_actionFlip_Horizontally_triggered()
{
    Mat tempImage = getCurrentImage();
    if(tempImage.data != nullptr)
    {
        Mat flipped(tempImage);
        cv::flip(tempImage,flipped,1);
        QImage imgIn= Mat2QImage(flipped);
        vlabel->setPixmap(QPixmap::fromImage(imgIn));
        current_img = flipped;
    }
}

void MainWindow::on_actionReset_triggered()
{
    Mat tempImage = getCurrentImage();
    if(tempImage.data != nullptr)
    {
        QImage imgIn("");
        imgIn= Mat2QImage(tempImage);
        vlabel->setPixmap(QPixmap::fromImage(imgIn));
        current_img = img;
    }
}

void MainWindow::on_actionConvertToGrayscale_triggered()
{
    Mat tempImage = getCurrentImage();
    if( tempImage.data != nullptr)
    {
        Mat dst(tempImage);
        cv::cvtColor(tempImage,dst,CV_BGR2GRAY);
        QImage imgIn= Mat2QImage(dst);
        vlabel->setPixmap(QPixmap::fromImage(imgIn));
        current_img = dst;
    }
}

Mat MainWindow::getCurrentImage()
{
    return current_img;
}

void MainWindow::on_actionOpenVideo_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Video"), "/home/rajarathinam/Videos", tr("Video  Songs (*.avi *.mp4 *.mkv)"));
    capture.open(fileName.toStdString().c_str());
    frameRate = (double)capture.get(CV_CAP_PROP_FPS);
    totalframes =capture.get(CV_CAP_PROP_FRAME_COUNT);
    slider->setMinimum(0);
    slider->setMaximum(totalframes);
    currentframenumber = 0;
    capture >> frame;
    Mat temp_frame(frame);
    QImage imgIn= Mat2QImage(temp_frame);
    vlabel->setPixmap(QPixmap::fromImage(imgIn));
    slider->setEnabled(true);
    playButton->setEnabled(true);
}

void MainWindow::getFrame()
{
    frameTimer->start(1000/frameRate);
    ++currentframenumber;
    capture >> frame;
    current_img = frame;
    displayImage();
}

void MainWindow::sliderFrameMove(int num)
{
    currentframenumber = num;
}

void MainWindow::sliderPressed()
{

    playButton->setIcon(QIcon(":/images/pausebutton.png"));
    frameTimer->stop();
}
void MainWindow::sliderReleased()
{

    playButton->setIcon(QIcon(":/images/playbutton.png"));
    slider->setValue(currentframenumber);
    capture.set(CV_CAP_PROP_POS_FRAMES,currentframenumber);
    capture >>current_img;
    displayImage();
}

void MainWindow::on_actionFlip_Vertically_triggered()
{

}

void MainWindow::myShowFullScreen()
{
    if(fullScreenSet == true)
    {
        fullScreenSet = false;
        this->showNormal();
    }
    else
    {
        fullScreenSet = true;
        this->showFullScreen();
    }
}

void MainWindow::on_actionImageManipulationWidget_triggered()
{
    if(!imageManipulationWidget)
    {
        imageManipulationWidget = new ImageManinpulationWidget;
        imageManipulationWidgetVisible = true;
        imageManipulationWidget->initialize();
    }
    imageManipulationWidget->show();
}

void MainWindow::onPlayButtonToggled(bool flag)
{
    if( frameTimer->isActive())
    {
        frameTimer->stop();
        playButton->setIcon(QIcon(":/images/playbutton.png"));
    }
    else
    {
        playButton->setIcon(QIcon(":/images/pausebutton.png"));
        frameTimer->start(1000/frameRate);
        displayImage();
    }
}

void MainWindow::onStopButtonClicked()
{
    if(capture.isOpened())
    {
        vlabel->setPixmap(QPixmap::fromImage(QImage(":/images/initial.jpg")));

        frameTimer->stop();
        capture.release();
    }
}

void MainWindow::displayImage()
{
    if(ui->actionFlip_Horizontally->isChecked())
    {
        flip(frame,current_img,1);
    }
    if(ui->actionFlip_Vertically->isChecked())
    {
        flip(frame,current_img,0);
    }
    if(imageManipulationWidget)
    {
        if(imageManipulationWidget->getGeometryWidget()->isRotateSelected())
        {
            current_img = rotateImage(imageManipulationWidget->getGeometryWidget()->getCurrentDialValue());
        }
        if(imageManipulationWidget->getOverlayWidget()->isAddTextSelected())
        {
            current_img = writeTextOnMat(current_img,imageManipulationWidget->getOverlayWidget()->getAddText());
        }
    }
    QImage imgIn= Mat2QImage(current_img);
    vlabel->setPixmap(QPixmap::fromImage(imgIn));


}
