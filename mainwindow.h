#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QSlider>
#include <QTimer>
#include <QMovie>
#include "myopencv.h"
#include "videolabel.h"
#include "imagemaninpulationwidget.h"
#include "aspectratiopixmaplabel.h"
#include "imagelabel.h"
#include "chessboardwidget.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    Mat rotateImage(int);
    Mat writeTextOnMat(Mat src,const char* text);

    void on_actionOpenImage_triggered();

    void on_actionConvertToGray_triggered();

    void on_actionFlip_Horizontally_triggered();

    void on_actionReset_triggered();

    void on_actionConvertToGrayscale_triggered();

    void on_actionOpenVideo_triggered();
    void getFrame();
    void sliderFrameMove(int);
    void sliderPressed();
    void sliderReleased();

    void on_actionFlip_Vertically_triggered();
    void myShowFullScreen();

    void on_actionImageManipulationWidget_triggered();

    void onPlayButtonToggled(bool);
    void onStopButtonClicked();
    void displayImage();
    void initializePlayerControls();

    void on_actionMy_Blur_triggered();
    void on_actionCreate_ChessBoard_triggered();

protected:
    void resizeEvent(QResizeEvent *);

private:
    Ui::MainWindow *ui;

    QGridLayout *mainLayout;
    QHBoxLayout *hLayout;
    QScrollArea *scrollArea;
    VideoLabel *vlabel;
    QMovie *movie ;

    QLabel *label;
    QSlider *slider;
    QPushButton *playButton;
    QPushButton *stopButton;
    bool fullScreenSet;
    bool imageManipulationWidgetVisible;

    static ImageManinpulationWidget *imageManipulationWidget;
    ChessBoardWidget *chessboardwidget;


    //OpenCV
    Mat img;
    Mat initialImage;
    Mat current_img;
    Mat blurred;
    Mat getCurrentImage();

    VideoCapture capture;
    Mat frame;
    QTimer *frameTimer;
    double frameRate;

    int totalframes;
    int currentframenumber;








};



#endif // MAINWINDOW_H
