#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <unistd.h>
#include <vector>
extern Mat QImage2Mat(QImage const& src);
extern QImage Mat2QImage(Mat const& src);
ImageManinpulationWidget* MainWindow::imageManipulationWidget = NULL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    blendwidget = new BlendWidget;
    QMap<QString,QString> mymap;
    mymap.insert("Raja Rathinam A","E515378");
    mymap.insert("[ax]","x");
    setMinimumSize(500,500);
    fullScreenSet = false;
    imageManipulationWidgetVisible = false;
    frameTimer = new QTimer(this);
    mainLayout = new QGridLayout();
    hLayout = new QHBoxLayout;
    hLayout->setSpacing(0);
    hLayout->setSizeConstraint(QLayout::SetFixedSize);
    vlabel = new VideoLabel();
    movie = new QMovie(":/images/arr.gif");
    vlabel->setMovie(movie);
    movie->start();
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
    vlabel->adjustSize();
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
    /*
      Mat tempImage = getCurrentImage();
      if( tempImage.data != nullptr)
      {
          Mat dst(tempImage);
          cv::cvtColor(tempImage,dst,CV_BGR2GRAY);
          QImage imgIn= Mat2QImage(dst);
          vlabel->setPixmap(QPixmap::fromImage(imgIn));
          current_img = dst;
      }
      */
    Mat input_image = imread("/home/rajarathinam/My_Stuff/raja.jpg");
    Mat grey_image = input_image.clone();
    cvtColor(input_image,grey_image,CV_BGR2GRAY);
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::fromImage(Mat2QImage(grey_image)));
    label->resize(grey_image.cols,grey_image.rows);
    label->show();
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
    Q_UNUSED(flag);
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
    initializePlayerControls();
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

void MainWindow::initializePlayerControls()
{
    playButton->setIcon(QIcon(":/images/playbutton.png"));
    playButton->setEnabled(false);
    slider->setValue(0);
    if(capture.isOpened())
    {
        capture.release();
    }
    vlabel->setMovie(movie);
    movie->start();
    frameTimer->stop();
}

void MainWindow::on_actionMy_Blur_triggered()
{
    if(!current_img.empty())
    {
        blurred = myBlurImage(current_img);
        qDebug() << blurred.cols;
        QImage img = Mat2QImage(blurred);
        vlabel->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
}

void MainWindow::on_actionCreate_ChessBoard_triggered()
{
    chessboardwidget = new  ChessBoardWidget;
    chessboardwidget->createChessBoardImage(256,256,64);
    chessboardwidget->displayImage();
}

void MainWindow::on_actionResizeImage_triggered()
{
    Mat orig = imread("/home/rajarathinam/My_Stuff/lovebirds.jpg");
    Mat small_img;
    cv::resize(orig,small_img,Size(orig.cols/4,orig.rows/4));
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::fromImage(Mat2QImage(small_img)));
    label->show();
}

void MainWindow::on_actionInvert_Colour_triggered()
{
    Mat input_image = imread("/home/rajarathinam/My_Stuff/raja.jpg");
    Mat output_image = input_image.clone();
    for (int row=0; row < input_image.rows; row++)
        for (int col=0; col < input_image.cols; col++)
            for (int channel = 0; channel < input_image.channels(); channel++)
            {
                output_image.at<Vec3b>(row,col)[channel] = 255 - input_image.at<Vec3b>(row,col)[channel];
            }
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::fromImage(Mat2QImage(output_image)));
    label->resize(output_image.cols,output_image.rows);
    label->show();
}

void MainWindow::on_actionSplit_RGB_triggered()
{
    Mat input_image = imread("/home/rajarathinam/My_Stuff/raja.jpg");
    Mat otherchannel = Mat::zeros(Size(input_image.cols,input_image.rows),CV_8UC1);
    std::vector<Mat> bgr_images(3);
    split(input_image,bgr_images);
    QLabel *label = new QLabel[3];
    std::vector<Mat> newImage;
    Mat img;
    newImage.push_back(otherchannel);
    newImage.push_back(otherchannel);
    newImage.push_back(bgr_images[0]);
    merge(newImage,img);
    label[0].setPixmap(QPixmap::fromImage(Mat2QImage(img)));
    //label[0].resize(output_image.cols,output_image.rows);
    label[0].show();
    label[1].setPixmap(QPixmap::fromImage(Mat2QImage(bgr_images[1])));
    //label[1].resize(output_image.cols,output_image.rows);
    label[1].show();
    label[2].setPixmap(QPixmap::fromImage(Mat2QImage(bgr_images[2])));
//label[2].resize(output_image.cols,output_image.rows);
    label[2].show();
}

void MainWindow::on_actionBlendImage_triggered()
{
    blendwidget->show();
}

