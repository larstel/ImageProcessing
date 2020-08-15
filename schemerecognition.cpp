#include "schemerecognition.h"

SchemeRecognition::SchemeRecognition(){

}

SchemeRecognition::SchemeRecognition(bool stopSign, bool priorityRoadSign, bool prioritySign, bool giveWaySign)
    : m_stopSign(stopSign), m_priorityRoadSign(prioritySign){
}

cv::Mat SchemeRecognition::recognizeScheme(cv::Mat inputImage)
{
    cv::Mat filteredImage = ImageManipulation::mysobel_filter_xy(inputImage);
    ImageManipulation::showImage(filteredImage, "");

    int G;
    int counter = 0;
    int lastCount = 0;
    int numberOfRowsCoord, numberOfColsCoord, rad;
    uchar a,b,c,d,e,f,g,h;
    int maxRadius = 0;

    for(int numberOfRows = 1 + m_numberOfIgnoredBoundsStopSign; numberOfRows <= filteredImage.rows-2 + m_numberOfIgnoredBoundsStopSign*2; numberOfRows += m_checkRateStopSign){ // anzahl reihen
        for(int numberOfCols = 1 + m_numberOfIgnoredBoundsStopSign; numberOfCols < filteredImage.cols-2 + m_numberOfIgnoredBoundsStopSign*2; numberOfCols += m_checkRateStopSign){ // anzahl spalten

            maxRadius = SchemeRecognition::getMaxRadius(numberOfCols, numberOfRows, filteredImage.cols, filteredImage.rows);

            for(int i = 0; i <= maxRadius; i += m_radiusStepsStopSign){ // radius
                G = static_cast<int>(round(tan(22.5*(M_PI/180))*i));
                for(int j = 0; j < G; j++){ // laenge der striche
                    a = filteredImage.at<cv::Vec3b>(numberOfRows+i,numberOfCols+j)[0];
                    b = filteredImage.at<cv::Vec3b>(numberOfRows+i,numberOfCols-j)[0];

                    c = filteredImage.at<cv::Vec3b>(numberOfRows-i,numberOfCols+j)[0];
                    d = filteredImage.at<cv::Vec3b>(numberOfRows-i,numberOfCols-j)[0];

                    e = filteredImage.at<cv::Vec3b>(numberOfRows+j,numberOfCols+i)[0];
                    f = filteredImage.at<cv::Vec3b>(numberOfRows-j,numberOfCols+i)[0];

                    g = filteredImage.at<cv::Vec3b>(numberOfRows+j,numberOfCols-i)[0];
                    h = filteredImage.at<cv::Vec3b>(numberOfRows-j,numberOfCols-i)[0];

                    if(a >= m_minGreyvalueStopSign){
                        counter++;
                    }
                    if(b >= m_minGreyvalueStopSign){
                        counter++;
                    }
                    if(c >= m_minGreyvalueStopSign){
                        counter++;
                    }
                    if(d >= m_minGreyvalueStopSign){
                        counter++;
                    }
                    if(e >= m_minGreyvalueStopSign){
                        counter++;
                    }
                    if(f >= m_minGreyvalueStopSign){
                        counter++;
                    }
                    if(g >= m_minGreyvalueStopSign){
                        counter++;
                    }
                    if(h >= m_minGreyvalueStopSign){
                        counter++;
                    }

                }

                if(lastCount < counter && counter > m_numberOfPixelThresholdStopSign){
                    numberOfColsCoord = numberOfCols;
                    numberOfRowsCoord = numberOfRows;
                    rad = i;
                    lastCount = counter;
                }
                counter = 0;
            }
        }
    }
    if(lastCount != 0){
        cv::circle(inputImage, cv::Point(numberOfColsCoord, numberOfRowsCoord),rad,cv::Scalar(0,255,0),1);
    }

    return inputImage;
}

/**
 * @brief SchemeRecognition::getMaxRadius return the max possible radius (to a border of the image)
 * @param x
 * @param y
 * @param imageWidth
 * @param imageHeight
 * @return
 */
int SchemeRecognition::getMaxRadius(int x, int y, int imageWidth, int imageHeight){
    if(y < floor(imageHeight/2) && x < floor(imageWidth/2)){ //oben links
        if(y < x){
            return y;
        } else {
            return x;
        }
    } else if(y < floor(imageHeight/2) && x >= floor(imageWidth/2)){ //oben rechts
        if(y < (imageWidth - x)){
            return y;
        } else {
            return imageWidth - x;
        }

    } else if(y >= floor(imageHeight/2) && x < floor(imageWidth/2)){ //unten links
        if((imageHeight - y) < x){
            return imageHeight - y;
        } else {
            return x;
        }
    } else if(y >= floor(imageHeight/2) && x >= floor(imageWidth/2)){ //unten rechts
        if((imageHeight - y) < (imageWidth - x)){
            return imageHeight - y;
        } else {
            return imageWidth - x;
        }

    }
}
