#ifndef IMAGEMANIPULATION_H
#define IMAGEMANIPULATION_H
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include <string>

class ImageManipulation
{
public:
    static cv::Mat transpose(cv::Mat image);
    static cv::Mat reverse(cv::Mat image);
    static cv::Mat rotate(cv::Mat image, int degree);
    static cv::Mat mirror(cv::Mat image, int axe);
    static cv::Mat scale(cv::Mat image, float factor);
    static cv::Mat resizePixels(cv::Mat image, int w1, int h1, int w2, int h2);

    static cv::Mat mymean_filter(cv::Mat image, int intensity);
    static cv::Mat mygauss_filter(cv::Mat image);
    static cv::Mat mysobel_filter_x_signed(cv::Mat image);
    static cv::Mat mysobel_filter_y_signed(cv::Mat image);
    static cv::Mat mysobel_filter_xy(cv::Mat image);
    static cv::Mat mysobel_filter_gradient(cv::Mat image);
    static cv::Mat mylaplace_filter(cv::Mat image);
    static void myLaplacePyramide(cv::Mat image);

    static cv::Mat linearScaling(cv::Mat image, int c1, float c2);
    static cv::Mat equidensities(cv::Mat image, int equiOrder = 1 ,float mean = 128);

    //static cv::Mat createPixelBorder(cv::Mat image);
    //static cv::Mat createPixelMirrorBorder(cv::Mat image);
    //static cv::Mat deletePixelBorder(cv::Mat image);

    static cv::Mat toGreyscaleByLightness(cv::Mat image);
    static cv::Mat toGreyscaleByAverage(cv::Mat image);
    static cv::Mat toGreyscaleByLuminosity(cv::Mat image);
    static cv::Mat toGreyscaleByOpenCV(cv::Mat image);
    static bool isGreyImage(cv::Mat image);

    static void showImage(cv::Mat image, std::string text);
    static cv::Mat readImage(std::string path);

    static cv::Vec3b hsvToRgb(int hue, float saturation, float value);
    static cv::Vec3b angleToRgb(float angle);

    static std::list<cv::Point>* getLineCoordinates(cv::Point start, cv::Point end);
};

#endif // IMAGEMANIPULATION_H
