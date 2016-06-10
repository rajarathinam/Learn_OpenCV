#include "myopencv.h"
Mat QImage2Mat(QImage const& src)
{
    Mat mat = Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    Mat mat2 = Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
    return mat2;
}

QImage Mat2QImage(Mat const& src)
{
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
    const float scale = 255.0;
    if (src.depth() == CV_8U)
    {
        if (src.channels() == 1)
        {
            for (int i = 0; i < src.rows; ++i)
            {
                for (int j = 0; j < src.cols; ++j)
                {
                    int level = src.at<quint8>(i, j);
                    dest.setPixel(j, i, qRgb(level, level, level));
                }
            }
        }
        else if (src.channels() == 3)
        {
            for (int i = 0; i < src.rows; ++i)
            {
                for (int j = 0; j < src.cols; ++j)
                {
                    cv::Vec3b bgr = src.at<cv::Vec3b>(i, j);
                    dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
                }
            }
        }
    }
    else if (src.depth() == CV_32F)
    {
        if (src.channels() == 1)
        {
            for (int i = 0; i < src.rows; ++i)
            {
                for (int j = 0; j < src.cols; ++j)
                {
                    int level = scale * src.at<float>(i, j);
                    dest.setPixel(j, i, qRgb(level, level, level));
                }
            }
        }
        else if (src.channels() == 3)
        {
            for (int i = 0; i < src.rows; ++i)
            {
                for (int j = 0; j < src.cols; ++j)
                {
                    cv::Vec3f bgr = scale * src.at<cv::Vec3f>(i, j);
                    dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
                }
            }
        }
    }
    return dest;
}

Mat writeTextOnImage(Mat src,const char* text)
{
    putText(src, text, Point(10, 70), FONT_HERSHEY_PLAIN, 2, CV_RGB(255, 255, 0), 2, 8, false);
    return src;

}

Mat rotate(Mat src, double angle)
{

    Mat dst;
    Point2f pt(src.cols/2., src.rows/2.);
    Mat r = getRotationMatrix2D(pt, -angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));

    return dst;
}

Mat myBlurImage(Mat src)
{
     Mat dst(src);
    if(!src.empty())
      {
        std::cout <<"Hello\n";

        int w = dst.cols;
        int h = dst.rows;
        for(int row = 0; row < h; row++)
          {
            for(int col = 0;  col< w ; col++)
              {
                  dst.at<Vec3d>(row,col)[0] = 255;
                  dst.at<Vec3d>(row,col)[1] = 255;
                  dst.at<Vec3d>(row,col)[2] = 255;
              }
          }

      }
    return dst;
}
