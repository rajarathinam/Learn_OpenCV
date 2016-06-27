#ifndef MYOPENCV
#define MYOPENCV
#include <QtGlobal>
#ifdef Q_OS_LINUX
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
using namespace cv;
#endif

#ifdef Q_OS_WIN
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/video/video.hpp"
using namespace cv;
#endif

#include <QImage>


Mat QImage2Mat(QImage const& src);
QImage Mat2QImage(Mat const& src);
Mat rotate(Mat src, double angle);
Mat writeTextOnImage(Mat src,const char* text);
Mat myBlurImage(Mat src);
Mat mycopyMakeBorder(InputArray src,int top, int bottom, int left, int right, int borderType, const Scalar value);
cv::Scalar qcolor2scalar(QColor color);
QColor scalar2qcolor(cv::Scalar color);

#endif // MYOPENCV

