#ifndef IMAGECALCULATION_H
#define IMAGECALCULATION_H
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include <map>
#include <math.h>
#include "imagemanipulation.h"

class ImageCalculation
{
public:
    static float getMean(cv::Mat image);
    static float getStandardDeviation(cv::Mat image);
    static float getEntropy(cv::Mat image);

    static std::map<int, int> getNumberOfGreyvalues(cv::Mat image);

    static uint getNumberOfPixel(cv::Mat image);

    static void showHistogram(cv::Mat image);
    static void showSumFrequency(cv::Mat image);
};

#endif // IMAGECALCULATION_H
