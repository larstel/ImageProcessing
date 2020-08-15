#ifndef SCHEMERECOGNITION_H
#define SCHEMERECOGNITION_H
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include "imagemanipulation.h"

class SchemeRecognition
{
public:
    SchemeRecognition();
    SchemeRecognition(bool stopSign, bool priorityRoadSign, bool prioritySign, bool giveWaySign);
    cv::Mat recognizeScheme(cv::Mat inputImage);
private:
    bool m_stopSign = true;
    bool m_priorityRoadSign = false;
    bool m_prioritySign = false;
    bool m_giveWaySign = false;

    int m_numberOfIgnoredBoundsStopSign = 10; //ignore X border pixel around the image
    int m_checkRateStopSign = 5; // check sign every X pixel
    int m_radiusStepsStopSign = 5; // radius every X steps
    int m_minGreyvalueStopSign = 100; // greyvalue; every pixel over X is counted
    int m_numberOfPixelThresholdStopSign = 20; // min number of pixels which have to be count

    int getMaxRadius(int x, int y, int imageWidth, int imageHeight);
};

#endif // SCHEMERECOGNITION_H
